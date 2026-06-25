using CommunityToolkit.Mvvm.ComponentModel;
using OdysseyEditor.Domain.Events;
using OdysseyEditor.Domain.Interfaces;

namespace OdysseyEditor.UI.ViewModels.Workspace;

public partial class FocusWarningViewModel(IEngineMessenger engineMessenger) : ObservableObject
{
    [ObservableProperty]
    public partial bool IsEngineFocused { get; set; }

    public void Init()
    {
        engineMessenger.On<WindowFocusChanged>(WindowFocusChanged.Key, value =>
        {
            IsEngineFocused = value.IsFocused;
        });
    }
}