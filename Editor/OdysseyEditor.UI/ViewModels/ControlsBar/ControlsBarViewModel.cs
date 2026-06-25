using CommunityToolkit.Mvvm.ComponentModel;
using CommunityToolkit.Mvvm.Input;
using CommunityToolkit.Mvvm.Messaging;
using Microsoft.Extensions.Options;
using OdysseyEditor.Domain.Data;
using OdysseyEditor.Domain.Events;
using OdysseyEditor.Domain.Interfaces;
using OdysseyEditor.UI.Utility;
using OdysseyEditor.UI.ViewModels.Messages;

namespace OdysseyEditor.UI.ViewModels.ControlsBar;

public partial class ControlsBarViewModel(IOptions<EngineConfig> config, IMessenger messenger, IEngineMessenger engineMessenger) : ObservableObject
{
    [ObservableProperty]
    [NotifyCanExecuteChangedFor(nameof(PlayCommand))]
    [NotifyCanExecuteChangedFor(nameof(StopCommand))]
    [NotifyCanExecuteChangedFor(nameof(SaveCommand))]
    [NotifyCanExecuteChangedFor(nameof(LoadCommand))]
    private partial bool IsPlaying { get; set; }
    
    [RelayCommand]
    private void Package()
    {
        CommandsRunner.Package(config.Value.ProjectRoot);
    }
    
    [RelayCommand]
    private void RebuildAndRestart()
    {
        CommandsRunner.KillEngine();
        CommandsRunner.Rebuild(config.Value.ProjectRoot);
        CommandsRunner.Restart();
    }

    [RelayCommand(CanExecute = nameof(CanPlay))]
    private async Task PlayAsync()
    {
        IsPlaying = true;
        await engineMessenger.Send<PlayRequest, PlayResponse>(Play.Key, new PlayRequest());
        messenger.Send(new ToggledPlayMessage { State = true });
    }

    [RelayCommand(CanExecute = nameof(CanStop))]
    private async Task StopAsync()
    {
        IsPlaying = false;
        await engineMessenger.Send<StopRequest, StopResponse>(Stop.Key, new StopRequest());
        messenger.Send(new ToggledPlayMessage { State = false });
    }

    [RelayCommand(CanExecute = nameof(CanLoadSave))]
    private async Task SaveAsync()
    {
        await engineMessenger.Send<SaveSceneRequest, SaveSceneResponse>(SaveScene.Key, new SaveSceneRequest());
    }

    [RelayCommand(CanExecute = nameof(CanLoadSave))]
    private async Task LoadAsync()
    {
        await engineMessenger.Send<LoadSceneRequest, LoadSceneResponse>(LoadScene.Key, new LoadSceneRequest());
    }

    private bool CanLoadSave() => !IsPlaying;
    
    private bool CanPlay() => !IsPlaying;

    private bool CanStop() => IsPlaying;
}