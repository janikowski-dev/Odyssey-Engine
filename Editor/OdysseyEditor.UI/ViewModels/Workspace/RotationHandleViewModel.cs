using System.Windows;
using System.Windows.Input;
using CommunityToolkit.Mvvm.ComponentModel;
using CommunityToolkit.Mvvm.Input;
using CommunityToolkit.Mvvm.Messaging;
using OdysseyEditor.Domain.Events;
using OdysseyEditor.Domain.Interfaces;
using OdysseyEditor.UI.ViewModels.Messages;

namespace OdysseyEditor.UI.ViewModels.Workspace;

public partial class RotationHandleViewModel(
    IMessenger messenger,
    IEngineMessenger engineMessenger
) : ObservableObject, IRecipient<ToggledPlayMessage>
{
    [ObservableProperty]
    public partial bool IsInPlay { get; set; } = false;
    
    private Point _lastMousePosition;
    private bool _isRotating;

    public void Init()
    {
        InitMessaging();
    }

    public void Receive(ToggledPlayMessage message) => IsInPlay = message.State;
    
    [RelayCommand]
    private void HandleRmbDown(MouseButtonEventArgs info)
    {
        BeginRotation(info);
        Mouse.Capture(info.MouseDevice.Target);
    }

    [RelayCommand]
    private void HandleRmbUp(MouseButtonEventArgs info)
    {
        EndRotation();
        Mouse.Capture(null);
    }

    [RelayCommand]
    private async Task HandleMouseDeltaAsync(MouseEventArgs info)
    {
        if (!_isRotating)
        {
            return;
        }

        Point current = info.GetPosition(null);
        double deltaX = current.X - _lastMousePosition.X;
        double deltaY = current.Y - _lastMousePosition.Y;
        _lastMousePosition = current;

        await engineMessenger.Send<RotateCameraRequest, RotateCameraResponse>(RotateCamera.Key, new RotateCameraRequest((float)deltaX, (float)deltaY));
    }

    private void BeginRotation(MouseButtonEventArgs e)
    {
        _lastMousePosition = e.GetPosition(null);
        _isRotating = true;
    }

    private void EndRotation()
    {
        _isRotating = false;
    }

    private void InitMessaging()
    {
        messenger.RegisterAll(this);
    }
}