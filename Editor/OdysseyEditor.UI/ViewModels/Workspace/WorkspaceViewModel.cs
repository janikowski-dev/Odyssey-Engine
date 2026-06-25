using System.Runtime.InteropServices;
using System.Windows.Interop;
using CommunityToolkit.Mvvm.Input;
using OdysseyEditor.Domain.Events;
using OdysseyEditor.Domain.Interfaces;
using OdysseyEditor.UI.Utility;

namespace OdysseyEditor.UI.ViewModels.Workspace;

public partial class WorkspaceViewModel(IEngineLauncher engineLauncher, IEngineMessenger engineMessenger) : HwndHost
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

    private async Task<GetViewportResponse> LaunchEngine()
    {
        await engineLauncher.LaunchAsync();
        return await engineMessenger.Send<GetViewportRequest, GetViewportResponse>(GetViewport.Key, new GetViewportRequest());
    }

    [RelayCommand]
    private async Task FocusEngineAsync()
    {
        _window.Focus();
        await engineMessenger.Send<FocusWindowRequest, FocusWindowResponse>(FocusWindow.Key, new FocusWindowRequest());
    }

    private void AttachEngine(GetViewportResponse response)
    {
        _window.Attach(response.Handle);
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