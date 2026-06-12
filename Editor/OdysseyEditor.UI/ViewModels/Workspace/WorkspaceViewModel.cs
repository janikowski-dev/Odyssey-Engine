using System.Runtime.InteropServices;
using System.Windows.Interop;
using OdysseyEditor.Domain.Events;
using OdysseyEditor.Domain.Interfaces;
using OdysseyEditor.UI.Utility;

namespace OdysseyEditor.UI.ViewModels.Workspace;

public class WorkspaceViewModel(IEngineLauncher engine, IEngineMessenger messenger) : HwndHost
{
    private readonly NativeWindowHost _window = new();

    public async Task InitAsync()
    {
        AttachEngine(await LaunchEngine());
    }

    protected override HandleRef BuildWindowCore(HandleRef hwndParent) => new(this, _window.CreateHost(hwndParent.Handle));

    protected override void OnWindowPositionChanged(System.Windows.Rect rcBoundingBox)
    {
        base.OnWindowPositionChanged(rcBoundingBox);
        ResizeWindow();
    }

    protected override void DestroyWindowCore(HandleRef hwnd)
    {
        DisposeWindow(true);
    }

    protected override void Dispose(bool disposing)
    {
        DisposeWindow(disposing);
        base.Dispose(disposing);
    }

    private async Task<ViewportResponse> LaunchEngine()
    {
        await engine.LaunchAsync();
        return await messenger.Send<ViewportRequest, ViewportResponse>(Viewport.Key, new ViewportRequest());
    }

    private void AttachEngine(ViewportResponse viewportResponse)
    {
        _window.Attach(viewportResponse.Handle);
        _window.Resize();
    }

    private void ResizeWindow()
    {
        _window.Resize();
    }

    private void DisposeWindow(bool disposing)
    {
        if (!disposing)
        {
            return;
        }
        
        _window.Dispose();
    }
}