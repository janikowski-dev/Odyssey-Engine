using CommunityToolkit.Mvvm.ComponentModel;
using CommunityToolkit.Mvvm.Input;
using OdysseyEditor.Domain.Events;
using OdysseyEditor.Domain.Interfaces;

namespace OdysseyEditor.UI.ViewModels.ControlsBar;

public partial class ControlsBarViewModel(IEngineMessenger engineMessenger) : ObservableObject
{
    private const string ScenePath = @"C:\\Projekty\\Odyssey-Engine\\Save.odyscene";
    
    [RelayCommand]
    private async Task LoadAsync()
    {
        await engineMessenger.Send<LoadSceneRequest, LoadSceneResponse>(LoadScene.Key, new LoadSceneRequest(ScenePath));
    }

    [RelayCommand]
    private async Task SaveAsync()
    {
        await engineMessenger.Send<SaveSceneRequest, SaveSceneResponse>(SaveScene.Key, new SaveSceneRequest(ScenePath));
    }
}
