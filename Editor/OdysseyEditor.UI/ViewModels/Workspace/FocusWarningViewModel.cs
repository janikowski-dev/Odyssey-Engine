using CommunityToolkit.Mvvm.ComponentModel;
using CommunityToolkit.Mvvm.Messaging;
using OdysseyEditor.Domain.Events;
using OdysseyEditor.Domain.Interfaces;
using OdysseyEditor.UI.ViewModels.Messages;

namespace OdysseyEditor.UI.ViewModels.Workspace;

public partial class FocusWarningViewModel(
    IMessenger messenger,
    IEngineMessenger engineMessenger
) : ObservableObject, IRecipient<ToggledPlayMessage>
{
    [ObservableProperty]
    public partial bool IsEngineFocused { get; set; } = false;

    [ObservableProperty]
    public partial bool IsInPlay { get; set; } = false;

    public void Init()
    {
        InitEngineMessaging();
        InitMessaging();
    }

    public void Receive(ToggledPlayMessage message)
    {
        IsInPlay = message.State;
    }
    
    private void InitEngineMessaging()
    {
        engineMessenger.On<WindowFocusChanged>(WindowFocusChanged.Key, value =>
        {
            IsEngineFocused = value.IsFocused;
        });
    }

    private void InitMessaging()
    {
        messenger.RegisterAll(this);
    }
}