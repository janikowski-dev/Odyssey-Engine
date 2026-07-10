using System.Runtime.InteropServices;
using System.Windows;
using System.Windows.Input;
using System.Windows.Interop;
using CommunityToolkit.Mvvm.Input;
using OdysseyEditor.Domain.Events;
using OdysseyEditor.Domain.Interfaces;
using OdysseyEditor.UI.Utility;

namespace OdysseyEditor.UI.ViewModels.Workspace;

public partial class WorkspaceViewModel(IEngineLauncher engineLauncher, IEngineMessenger engineMessenger) : HwndHost
{
    private NativeWindowHost _window = null!;
    private bool _isDragging;

    private static readonly Dictionary<Key, MoveDirection> DirectionsByKey = new()
    {
        { Key.W, MoveDirection.Forward },
        { Key.S, MoveDirection.Back },
        { Key.A, MoveDirection.Left },
        { Key.D, MoveDirection.Right },
        { Key.Q, MoveDirection.Down },
        { Key.E, MoveDirection.Up }
    };
    
    public async Task InitAsync()
    {
        AttachEngine(await LaunchEngine(InitAsync));
    }

    protected override HandleRef BuildWindowCore(HandleRef hwndParent)
    {
        Cache(new NativeWindowHost(HandleButtonUp, HandleButtonDown, HandleMouseDelta));
        return CreateHost(hwndParent);
    }

    protected override void OnWindowPositionChanged(Rect rcBoundingBox)
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

    private async Task<GetViewportResponse> LaunchEngine(Func<Task> relaunch)
    {
        await engineLauncher.LaunchAsync(relaunch);
        return await engineMessenger.Send<GetViewportRequest, GetViewportResponse>(GetViewport.Key, new GetViewportRequest());
    }

    [RelayCommand]
    private async Task FocusEngineAsync()
    {
        _window.Focus();
        await engineMessenger.Send<FocusWindowRequest, FocusWindowResponse>(FocusWindow.Key, new FocusWindowRequest());
    }
    
    [RelayCommand]
    private async Task HandleKeyDownAsync(KeyEventArgs info)
    {
        if (!_isDragging)
        {
            return;
        }
        
        if (!DirectionsByKey.TryGetValue(info.Key, out MoveDirection direction))
        {
            return;
        }

        await engineMessenger.Send<MoveCameraRequest, MoveCameraResponse>(MoveCamera.Key, new MoveCameraRequest(direction, true));
    }

    [RelayCommand]
    private async Task HandleKeyUpAsync(KeyEventArgs info)
    {
        if (!DirectionsByKey.TryGetValue(info.Key, out MoveDirection direction))
        {
            return;
        }

        await engineMessenger.Send<MoveCameraRequest, MoveCameraResponse>(MoveCamera.Key, new MoveCameraRequest(direction, false));
    }
    
    private void HandleButtonDown()
    {
        _isDragging = true;
    }

    private void HandleButtonUp()
    {
        _isDragging = false;
    }
    
    private void HandleMouseDelta(float xDelta, float yDelta)
    {
        if (!_isDragging)
        {
            return;
        }

        engineMessenger.Send<RotateCameraRequest, RotateCameraResponse>(RotateCamera.Key, new RotateCameraRequest(xDelta, yDelta));
    }
    
    private void Cache(NativeWindowHost window) => _window = window;

    private HandleRef CreateHost(HandleRef hwndParent) => new(this, _window.CreateHost(hwndParent.Handle));

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