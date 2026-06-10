using System.Diagnostics;
using System.IO;
using System.Runtime.InteropServices;
using System.Text.Json;
using System.Windows.Interop;

namespace OdysseyEditor.UI.ViewModels.Workspace;

public class WorkspaceViewModel(string enginePath, int port) : HwndHost
{
    public static readonly EngineConnection _connection = new();

    private const int GwlStyle = -16;
    private const int WsChild = 0x40000000;
    private const int WsVisible = 0x10000000;
    private const int WsClipSiblings = 0x04000000;
    private const int WsClipChildren = 0x02000000;
    private const int SwShow = 5;

    private const uint SwpNoMove = 0x0002;
    private const uint SwpNoSize = 0x0001;
    private const uint SwpNoZOrder = 0x0004;
    private const uint SwpFrameChanged = 0x0020;

    private Process? _process;
    private IntPtr _engineHwnd;

    public async Task InitAsync()
    {
        Show(await GetHandle());
        await _connection.RequestAsync("create_entity", null, TimeSpan.FromSeconds(3));
    }

    protected override void OnWindowPositionChanged(System.Windows.Rect rcBoundingBox)
    {
        base.OnWindowPositionChanged(rcBoundingBox);
        ResizeEngine();
    }

    protected override HandleRef BuildWindowCore(HandleRef hwndParent)
    {
        IntPtr host = CreateWindowEx(
            0,
            "STATIC", "",
            WsChild | WsVisible | WsClipChildren,
            0, 0, 100, 100,
            hwndParent.Handle,
            IntPtr.Zero, IntPtr.Zero, IntPtr.Zero);

        return new HandleRef(this, host);
    }

    private void ResizeEngine()
    {
        GetClientRect(Handle, out Rect rect);
        MoveWindow(_engineHwnd, 0, 0, rect.Right - rect.Left, rect.Bottom - rect.Top, true);
    }

    protected override void DestroyWindowCore(HandleRef hwnd)
    {
        DestroyWindow(hwnd.Handle);
        _engineHwnd = IntPtr.Zero;
    }

    protected override void Dispose(bool disposing)
    {
        base.Dispose(disposing);

        if (disposing && _process is { HasExited: false })
        {
            try
            {
                _connection.Dispose();

                if (!_process.WaitForExit(1000))
                {
                    _process.Kill(entireProcessTree: true);
                }
            }
            catch
            {
            }
        }
        
        _process?.Dispose();
    }
    
    private void Show(IntPtr engineHwnd)
    {
        _engineHwnd = engineHwnd;
        SetParent(engineHwnd, Handle);
        SetWindowLongPtr(engineHwnd, GwlStyle, WsChild | WsVisible | WsClipSiblings);
        SetWindowPos(engineHwnd, IntPtr.Zero, 0, 0, 0, 0,SwpNoMove | SwpNoSize | SwpNoZOrder | SwpFrameChanged);
        ShowWindow(engineHwnd, SwShow);
        ResizeEngine();
    }
    
    private async Task<IntPtr> GetHandle()
    {
        _process?.Dispose();
        _process = new Process
        {
            StartInfo = new ProcessStartInfo
            {
                WorkingDirectory = Path.GetDirectoryName(enginePath) ?? ".",
                Arguments = $"-port {port} -hide",
                UseShellExecute = false,
                FileName = enginePath
            },
            EnableRaisingEvents = true
        };
        _process.Start();

        await _connection.ConnectAsync("127.0.0.1", port, TimeSpan.FromSeconds(10));

        JsonElement viewport = await _connection.RequestAsync("get_viewport", null, TimeSpan.FromSeconds(3));
        return new IntPtr(viewport.GetProperty("hwnd").GetInt64());
    }

    [DllImport("user32.dll", SetLastError = true, CharSet = CharSet.Unicode)]
    private static extern IntPtr CreateWindowEx(
        int exStyle, string className, string windowName, uint style,
        int x, int y, int width, int height,
        IntPtr parent, IntPtr menu, IntPtr instance, IntPtr param);

    [DllImport("user32.dll")] private static extern bool DestroyWindow(IntPtr hwnd);
    [DllImport("user32.dll")] private static extern IntPtr SetParent(IntPtr child, IntPtr newParent);
    [DllImport("user32.dll")] private static extern bool ShowWindow(IntPtr hwnd, int cmd);
    [DllImport("user32.dll")] private static extern bool MoveWindow(IntPtr hwnd, int x, int y, int w, int h, bool repaint);
    [DllImport("user32.dll")] private static extern bool GetClientRect(IntPtr hwnd, out Rect rect);

    [DllImport("user32.dll", SetLastError = true)]
    private static extern bool SetWindowPos(IntPtr hwnd, IntPtr insertAfter, int x, int y, int cx, int cy, uint flags);

    [DllImport("user32.dll", EntryPoint = "SetWindowLongPtrW")]
    private static extern IntPtr SetWindowLongPtr(IntPtr hwnd, int index, IntPtr value);

    [StructLayout(LayoutKind.Sequential)]
    private struct Rect { public int Left, Top, Right, Bottom; }
}