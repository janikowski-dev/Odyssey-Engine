using System.Collections.Concurrent;
using System.Net;
using System.Net.Sockets;
using System.Text.Json;

namespace OdysseyEditor.UI.ViewModels.Workspace;

public sealed class EngineConnection : IDisposable
{
    public event Action<string, JsonElement>? EventReceived;
    public event Action<Exception>? Disconnected;

    private readonly ConcurrentDictionary<int, TaskCompletionSource<JsonElement>> _pending = new();
    private readonly object _writeLock = new();
    private int _nextId;
    
    private TcpClient _client = new();
    private NetworkStream _stream = null!;
    private Thread _reader = null!;
    private volatile bool _running;
    
    public async Task ConnectAsync(string host, int port, TimeSpan retryWindow)
    {
        var deadline = DateTime.UtcNow + retryWindow;
        while (true)
        {
            var client = new TcpClient();
            try { await client.ConnectAsync(host, port); }
            catch (SocketException) when (DateTime.UtcNow < deadline)
            {
                client.Dispose();
                await Task.Delay(150);
                continue;
            }

            client.NoDelay = true;
            _client = client;
            _stream = client.GetStream();
            _running = true;
            _reader = new Thread(ReadLoop) { IsBackground = true, Name = "engine-reader" };
            _reader.Start();
            return;
        }
    }

    public async Task<JsonElement> RequestAsync(string method, object? @params, TimeSpan timeout)
    {
        int id = Interlocked.Increment(ref _nextId);
        TaskCompletionSource<JsonElement> tcs = new TaskCompletionSource<JsonElement>(TaskCreationOptions.RunContinuationsAsynchronously);
        _pending[id] = tcs;

        SendJson(new { id, method, @params });

        using var cts = new CancellationTokenSource(timeout);
        
        await using var reg = cts.Token.Register(() =>
        {
            if (_pending.TryRemove(id, out var t))
            {
                t.TrySetException(new TimeoutException($"request '{method}' timed out"));
            }
        });
        
        return await tcs.Task.ConfigureAwait(false);
    }

    private void SendJson(object message)
    {
        byte[] body = JsonSerializer.SerializeToUtf8Bytes(message);
        byte[] header = BitConverter.GetBytes(IPAddress.HostToNetworkOrder(body.Length));
        
        lock (_writeLock)
        {
            _stream.Write(header, 0, 4);
            _stream.Write(body, 0, body.Length);
        }
    }

    private void ReadLoop()
    {
        try
        {
            while (_running)
            {
                byte[] header = ReadExact(4);
                int len = IPAddress.NetworkToHostOrder(BitConverter.ToInt32(header, 0));
                byte[] body = ReadExact(len);

                using var doc = JsonDocument.Parse(body);
                Route(doc.RootElement.Clone());
            }
        }
        catch (Exception ex)
        {
            FailAll(ex);
            Disconnected?.Invoke(ex);
        }
    }

    private void Route(JsonElement msg)
    {
        bool isResponse = msg.TryGetProperty("id", out var idEl) && (msg.TryGetProperty("result", out _) || msg.TryGetProperty("error", out _));

        if (isResponse)
        {
            if (_pending.TryRemove(idEl.GetInt32(), out var tcs))
            {
                if (msg.TryGetProperty("error", out var err))
                {
                    tcs.TrySetException(new Exception(err.GetString()));
                }
                else
                {
                    tcs.TrySetResult(msg.GetProperty("result"));
                }
            }
        }
        else if (msg.TryGetProperty("event", out JsonElement name))
        {
            JsonElement data = msg.TryGetProperty("data", out JsonElement d) ? d : default;
            EventReceived?.Invoke(name.GetString() ?? "", data);
        }
    }

    private void FailAll(Exception ex)
    {
        _running = false;
        foreach (var key in _pending.Keys)
            if (_pending.TryRemove(key, out var tcs))
                tcs.TrySetException(new Exception("engine disconnected", ex));
    }

    private byte[] ReadExact(int count)
    {
        byte[] buf = new byte[count];
        int got = 0;
        
        while (got < count)
        {
            int n = _stream.Read(buf, got, count - got);
            if (n <= 0) throw new Exception("connection closed");
            got += n;
        }
        
        return buf;
    }

    public void Dispose()
    {
        _running = false;
        
        try
        {
            _client.Close();
        }
        catch
        {
        }
    }
}