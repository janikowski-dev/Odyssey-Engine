using System.Runtime.InteropServices;

namespace OdysseyEditor.UI.Utility;

public sealed class NativeWindowHost(Action buttonUpCallback, Action buttonDownCallback, Action<float, float> mouseDeltaCallback) : IDisposable
{
    private LowLevelMouseProc? _hookProc;
    private IntPtr _hookHandle;
    private IntPtr _childHwnd;
    private IntPtr _hostHwnd;

    private bool _rmbHeld;
    private Point _lastPos;
    private bool _hasLastPos;

    private const int WsChild = 0x40000000;
    private const int WsVisible = 0x10000000;
    private const int WsClipChildren = 0x02000000;
    private const int WsClipSiblings = 0x04000000;

    private const int GwlStyle = -16;

    private const uint SwpNoMove = 0x0002;
    private const uint SwpNoSize = 0x0001;
    private const uint SwpNoZOrder = 0x0004;
    private const uint SwpFrameChanged = 0x0020;

    private const int WhMouseLl = 14;
    private const int HcAction = 0;

    private const uint WmRButtonDown = 0x0204;
    private const uint WmRButtonUp = 0x0205;
    private const uint WmMouseMove = 0x0200;

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
        InstallMouseHook(HookProc, proc => SetWindowsHookEx(WhMouseLl, proc, GetModuleHandle(null), 0));
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
        UnhookWindowsHookEx(_hookHandle);
        DisposeHook();

        if (HasHost())
        {
            DestroyWindow(_hostHwnd);
        }
    }

    private bool IsInsideChild(Point screenPt)
    {
        ScreenToClient(_childHwnd, ref screenPt);
        GetClientRect(_childHwnd, out Rect rect);
        return IsInsideChild(screenPt, rect);
    }

    private IntPtr HookProc(int nCode, IntPtr wParam, IntPtr lParam)
    {
        if (nCode >= HcAction)
        {
            HandleMouse((uint)wParam, Marshal.PtrToStructure<MsllHookStruct>(lParam).Point);
        }
        
        return CallNextHookEx(_hookHandle, nCode, wParam, lParam);
    }

    private void HandleMouse(uint msg, Point screenPt)
    {
        switch (msg)
        {
            case WmRButtonDown:
                if (IsInsideChild(screenPt))
                {
                    BeginRmbHold();
                }
                break;

            case WmRButtonUp:
                EndRmbHold();
                break;

            case WmMouseMove:
                PropagateMouseDelta(screenPt);
                break;
        }
    }

    private IntPtr CacheHost(IntPtr hostHwnd) => _hostHwnd = hostHwnd;

    private void CacheChild(IntPtr childHwnd) => _childHwnd = childHwnd;

    private bool HasHost() => _hostHwnd != IntPtr.Zero;

    private bool HasChild() => _childHwnd != IntPtr.Zero;

    private void InstallMouseHook(LowLevelMouseProc proc, Func<LowLevelMouseProc, IntPtr> callback)
    {
        if (_hookHandle != IntPtr.Zero)
        {
            return;
        }

        _hookHandle = callback.Invoke(proc);
        _hookProc = proc;
    }

    private void PropagateMouseDelta(Point screenPt)
    {
        if (!_rmbHeld)
        {
            return;
        }

        if (_hasLastPos)
        {
            float dx = screenPt.X - _lastPos.X;
            float dy = screenPt.Y - _lastPos.Y;
                    
            if (dx != 0 || dy != 0)
            {
                mouseDeltaCallback.Invoke(dx, dy);
            }
        }

        _lastPos = screenPt;
        _hasLastPos = true;
    }

    private void EndRmbHold()
    {
        if (!_rmbHeld)
        {
            return;
        }
        
        _rmbHeld = false;
        _hasLastPos = false;
        buttonUpCallback.Invoke();
    }

    private void BeginRmbHold()
    {
        _rmbHeld = true;
        _hasLastPos = false;
        buttonDownCallback.Invoke();
    }

    private void DisposeHook() => _hookHandle = IntPtr.Zero;

    private static bool IsInsideChild(Point screenPt, Rect rect) => screenPt.X >= rect.Left && screenPt.X < rect.Right && screenPt.Y >= rect.Top && screenPt.Y < rect.Bottom;

    [DllImport("user32.dll", SetLastError = true)]
    private static extern IntPtr SetWindowsHookEx(int idHook, LowLevelMouseProc lpfn, IntPtr hMod, uint dwThreadId);

    [DllImport("user32.dll", SetLastError = true)]
    private static extern bool UnhookWindowsHookEx(IntPtr hhk);

    [DllImport("user32.dll")]
    private static extern IntPtr CallNextHookEx(IntPtr hhk, int nCode, IntPtr wParam, IntPtr lParam);

    [DllImport("user32.dll")]
    private static extern bool ScreenToClient(IntPtr hwnd, ref Point pt);

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

    [DllImport("kernel32.dll", CharSet = CharSet.Unicode)]
    private static extern IntPtr GetModuleHandle(string? moduleName);
    
    private delegate IntPtr LowLevelMouseProc(int nCode, IntPtr wParam, IntPtr lParam);

    [StructLayout(LayoutKind.Sequential)]
    private struct Point { public int X, Y; }

    [StructLayout(LayoutKind.Sequential)]
    private struct MsllHookStruct
    {
        public Point Point;
        public uint MouseData;
        public uint Flags;
        public uint Time;
        public UIntPtr ExtraInfo;
    }

    [StructLayout(LayoutKind.Sequential)]
    private struct Rect { public int Left, Top, Right, Bottom; }
}