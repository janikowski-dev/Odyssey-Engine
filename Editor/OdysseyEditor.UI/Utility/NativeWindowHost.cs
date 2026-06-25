using System.Runtime.InteropServices;

namespace OdysseyEditor.UI.Utility;

public sealed class NativeWindowHost : IDisposable
{
    private IntPtr _childHwnd;
    private IntPtr _hostHwnd;

    private const int WsChild = 0x40000000;
    private const int WsVisible = 0x10000000;
    private const int WsClipChildren = 0x02000000;
    private const int WsClipSiblings = 0x04000000;

    private const int GwlStyle = -16;

    private const uint SwpNoMove = 0x0002;
    private const uint SwpNoSize = 0x0001;
    private const uint SwpNoZOrder = 0x0004;
    private const uint SwpFrameChanged = 0x0020;

    public IntPtr CreateHost(IntPtr parent)
    {
        return CacheHost(CreateWindowEx(
            0,
            "STATIC",
            "",
            WsChild | WsVisible | WsClipChildren,
            0, 0, 100, 100,
            parent,
            IntPtr.Zero,
            IntPtr.Zero,
            IntPtr.Zero)
        );
    }

    public void Attach(IntPtr childHwnd)
    {
        CacheChild(childHwnd);
        SetParent(childHwnd, _hostHwnd);
        SetWindowLongPtr(childHwnd, GwlStyle, WsChild | WsVisible | WsClipSiblings);
        SetWindowPos(childHwnd, IntPtr.Zero, 0, 0, 0, 0, SwpNoMove | SwpNoSize | SwpNoZOrder | SwpFrameChanged);
        ShowWindow(childHwnd, 5);
        AttachThreadInput(GetCurrentThreadId(), GetWindowThreadProcessId(_childHwnd, IntPtr.Zero), true);
    }

    public void Focus()
    {
        if (!HasChild())
        {
            return;
        }

        SetFocus(_childHwnd);
    }

    public void Resize()
    {
        GetClientRect(_hostHwnd, out Rect rect);

        MoveWindow(
            _childHwnd,
            0, 0,
            rect.Right - rect.Left,
            rect.Bottom - rect.Top,
            true
        );
    }

    public void Dispose()
    {
        if (HasHost())
        {
            DestroyWindow(_hostHwnd);
        }
    }

    private IntPtr CacheHost(IntPtr hostHwnd) =>  _hostHwnd = hostHwnd;

    private void CacheChild(IntPtr childHwnd) => _childHwnd = childHwnd;

    private bool HasHost() => _hostHwnd != IntPtr.Zero;
    
    private bool HasChild() => _childHwnd != IntPtr.Zero;

    [StructLayout(LayoutKind.Sequential)]
    private struct Rect { public int Left, Top, Right, Bottom; }

    [DllImport("user32.dll")]
    private static extern bool DestroyWindow(IntPtr hwnd);
    
    [DllImport("user32.dll")]
    private static extern IntPtr SetParent(IntPtr child, IntPtr parent);
    
    [DllImport("user32.dll")]
    private static extern bool ShowWindow(IntPtr hwnd, int cmd);
    
    [DllImport("user32.dll")]
    private static extern bool MoveWindow(IntPtr hwnd, int x, int y, int w, int h, bool repaint);
    
    [DllImport("user32.dll")]
    private static extern bool GetClientRect(IntPtr hwnd, out Rect rect);

    [DllImport("user32.dll", SetLastError = true)]
    private static extern bool SetWindowPos(IntPtr hwnd, IntPtr insertAfter, int x, int y, int cx, int cy, uint flags);

    [DllImport("user32.dll", EntryPoint = "SetWindowLongPtrW")]
    private static extern IntPtr SetWindowLongPtr(IntPtr hwnd, int index, IntPtr value);

    [DllImport("user32.dll", CharSet = CharSet.Unicode)]
    private static extern IntPtr CreateWindowEx(
        int exStyle, string className, string windowName, uint style,
        int x, int y, int width, int height,
        IntPtr parent, IntPtr menu, IntPtr instance, IntPtr param
    );
    
    [DllImport("user32.dll")]
    private static extern IntPtr SetFocus(IntPtr hwnd);

    [DllImport("user32.dll", SetLastError = true)]
    private static extern bool AttachThreadInput(uint idAttach, uint idAttachTo, bool fAttach);

    [DllImport("user32.dll")]
    private static extern uint GetWindowThreadProcessId(IntPtr hwnd, IntPtr processId);

    [DllImport("kernel32.dll")]
    private static extern uint GetCurrentThreadId();
}