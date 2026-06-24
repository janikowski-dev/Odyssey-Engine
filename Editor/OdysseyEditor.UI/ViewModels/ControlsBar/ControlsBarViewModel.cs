using CommunityToolkit.Mvvm.ComponentModel;
using CommunityToolkit.Mvvm.Input;
using OdysseyEditor.Domain.Events;
using OdysseyEditor.Domain.Interfaces;

namespace OdysseyEditor.UI.ViewModels.ControlsBar;

public partial class ControlsBarViewModel(IEngineMessenger engineMessenger) : ObservableObject
{
    [ObservableProperty]
    [NotifyCanExecuteChangedFor(nameof(PlayCommand))]
    [NotifyCanExecuteChangedFor(nameof(StopCommand))]
    private partial bool IsPlaying { get; set; }

    [RelayCommand(CanExecute = nameof(CanPlay))]
    private async Task PlayAsync()
    {
        IsPlaying = true;
        await engineMessenger.Send<PlayRequest, PlayResponse>(Play.Key, new PlayRequest());
    }

    [RelayCommand(CanExecute = nameof(CanStop))]
    private async Task StopAsync()
    {
        IsPlaying = false;
        await engineMessenger.Send<StopRequest, StopResponse>(Stop.Key, new StopRequest());
    }

    private bool CanPlay() => !IsPlaying;

    private bool CanStop() => IsPlaying;
}