using System.Collections.Concurrent;
using System.Diagnostics;
using System.Net;
using System.Net.Sockets;
using System.Text.Json;
using System.Text.Json.Nodes;
using Microsoft.Extensions.Options;
using OdysseyEditor.Domain.Data;
using OdysseyEditor.Domain.Interfaces;

namespace OdysseyEditor.Domain.Services;

public sealed class EngineService(IOptions<EngineConfig> config) : IEngineLauncher, IEngineMessenger, IDisposable
{
    private readonly ConcurrentDictionary<int, TaskCompletionSource<JsonElement>> _pending = new();
    private readonly ConcurrentDictionary<string, List<object>> _handlers = new();
    private readonly Lock _writeLock = new();
    private int _nextId;
    
    private NetworkStream _stream = null!;
    private TcpClient _client = new();
    private volatile bool _running;
    private Thread _reader = null!;
    private Process? _process;
    private Func<Task> _relaunch = null!;
    
    private static readonly TimeSpan DefaultTimeout = TimeSpan.FromSeconds(5);

    public async Task LaunchAsync(Func<Task> relaunch)
    {
        Cache(relaunch);
        KillEngine();
        StartEngine();
        await ConnectToEngine();
    }

    public async Task<TResponse> Send<TRequest, TResponse>(string method, TRequest request)
    {
        try
        {
            return (await RequestAsync<TRequest, TResponse>(method, request, DefaultTimeout))!;
        }
        catch (Exception caughtException)
        {
            FailAll(caughtException);
            await Relaunch();
            return default!;
        }
    }

    public void On<TEvent>(string method, Action<TEvent> callback)
    {
        RegisterHandler(method, callback);
    }

    public void Dispose()
    {
        try
        {
            StopClient();
            KillProcess();
        }
        finally
        {
            ResetProcess();
        }
    }

    private void ReadLoop()
    {
        try
        {
            while (TryRead(out JsonElement message))
            {
                Route(message);
                DispatchEvent(message);
            }
        }
        catch (Exception caughtException)
        {
            FailAll(caughtException);
        }
    }
    
    private static void KillEngine()
    {
        string processName = Path.GetFileNameWithoutExtension("Launcher.exe");
    
        foreach (Process process in Process.GetProcessesByName(processName))
        {
            process.Kill();
            process.WaitForExit();
            process.Dispose();
        }
    }

    private void StartEngine()
    {
        string enginePath = Path.GetFullPath(Path.Combine(config.Value.ProjectRoot, "Build/Launcher/Launcher.exe"));
        
        _process = new Process
        {
            StartInfo = new ProcessStartInfo
            {
                Arguments = $"-host {config.Value.Host} -port {config.Value.Port} -hide -editor -root {config.Value.ProjectRoot}",
                WorkingDirectory = Path.GetDirectoryName(enginePath),
                UseShellExecute = false,
                FileName = enginePath
            }
        };

        _process.Start();
    }
    
    private async Task ConnectToEngine()
    {
        DateTime deadline = DateTime.UtcNow + DefaultTimeout;
        
        while (true)
        {
            TcpClient client = new();
            
            try
            {
                await client.ConnectAsync(config.Value.Host, config.Value.Port);
            }
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
            
            _reader = new Thread(ReadLoop)
            {
                IsBackground = true,
                Name = "engine-reader"
            };
            
            _reader.Start();
            return;
        }
    }

    private void RegisterHandler<TEvent>(string method, Action<TEvent> callback)
    {
        _handlers.TryAdd(method, []);
        _handlers[method].Add(callback);
    }

    private async Task<TResponse?> RequestAsync<TRequest, TResponse>(string method, TRequest request, TimeSpan timeout)
    {
        int id = Interlocked.Increment(ref _nextId);
        TaskCompletionSource<JsonElement> tcs = new(TaskCreationOptions.RunContinuationsAsynchronously);
        _pending[id] = tcs;

        JsonObject json = new()
        {
            ["data"] = JsonSerializer.SerializeToNode(request),
            ["method"] = method,
            ["id"] = id
        };

        byte[] body = JsonSerializer.SerializeToUtf8Bytes(json);
        byte[] header = BitConverter.GetBytes(IPAddress.HostToNetworkOrder(body.Length));
        
        lock (_writeLock)
        {
            _stream.Write(header, 0, 4);
            _stream.Write(body, 0, body.Length);
        }
        
        using CancellationTokenSource cts = new(timeout);
        
        await using CancellationTokenRegistration registration = cts.Token.Register(() =>
        {
            if (_pending.TryRemove(id, out TaskCompletionSource<JsonElement>? t))
            {
                t.TrySetException(new TimeoutException($"Request '{method}' timed out!"));
            }
        });

        JsonElement responseJson = await tcs.Task.ConfigureAwait(false);
        return responseJson.Deserialize<TResponse>();
    }

    private bool TryRead(out JsonElement element)
    {
        element = default;
        
        if (!_running)
        {
            return false;
        }
        
        byte[] header = ReadExact(4);
        int length = IPAddress.NetworkToHostOrder(BitConverter.ToInt32(header, 0));
        byte[] body = ReadExact(length);
        using JsonDocument document = JsonDocument.Parse(body);
        element = document.RootElement.Clone();
        return true;
    }

    private void Route(JsonElement message)
    {
        bool isResponse = message.TryGetProperty("id", out JsonElement idElement) && (message.TryGetProperty("result", out _) || message.TryGetProperty("error", out _));

        if (!isResponse)
        {
            return;
        }

        if (!_pending.TryRemove(idElement.GetInt32(), out TaskCompletionSource<JsonElement>? tcs))
        {
            return;
        }
        
        if (message.TryGetProperty("error", out JsonElement error))
        {
            tcs.TrySetException(new Exception(error.GetString()));
        }
        else
        {
            tcs.TrySetResult(message.GetProperty("result"));
        }
    }

    private void DispatchEvent(JsonElement message)
    {
        if (!message.TryGetProperty("method", out JsonElement methodElement))
        {
            return;
        }

        string? method = methodElement.GetString();
        
        if (method is null || !_handlers.TryGetValue(method, out List<object>? handlers))
        {
            return;
        }

        message.TryGetProperty("data", out JsonElement data);

        object[] snapshot;
        
        lock (handlers)
        {
            snapshot = handlers.ToArray();
        }

        try
        {
            foreach (object handler in snapshot)
            {
                Type eventType = handler.GetType().GetGenericArguments()[0];
                object? payload = data.Deserialize(eventType);
                handler.GetType().GetMethod("Invoke")!.Invoke(handler, [payload]);
            }
        }
        catch
        {
            // If you throw in your own handler lambda, it's between you and your god, sorry.
        }
    }

    private byte[] ReadExact(int count)
    {
        byte[] buffer = new byte[count];
        int got = 0;
        
        while (got < count)
        {
            int n = _stream.Read(buffer, got, count - got);
            
            if (n == 0)
            {
                throw new IOException("Engine closed the connection.");
            }
            
            got += n;
        }
        
        return buffer;
    }

    private void FailAll(Exception caughtException)
    {
        _running = false;
        
        foreach (int key in _pending.Keys)
        {
            if (_pending.TryRemove(key, out TaskCompletionSource<JsonElement>? tcs))
            {
                tcs.TrySetException(new Exception("Engine disconnected!", caughtException));
            }
        }
    }

    private void Cache(Func<Task> relaunch) => _relaunch = relaunch;

    private async Task Relaunch() => await _relaunch();

    private void StopClient()
    {
        _running = false;
        _client.Close();
    }

    private void KillProcess()
    {
        if (_process is not { HasExited: false })
        {
            return;
        }

        if (!_process.WaitForExit(1_000))
        {
            _process.Kill(entireProcessTree: true);
        }
    }

    private void ResetProcess()
    {
        _process?.Dispose();
        _process = null;
    }
}