using CommunityToolkit.Mvvm.ComponentModel;
using CommunityToolkit.Mvvm.Input;
using OdysseyEditor.Domain.Events;
using OdysseyEditor.Domain.Interfaces;

namespace OdysseyEditor.UI.ViewModels.ControlsBar;

public partial class ControlsBarViewModel(IEngineMessenger messenger) : ObservableObject
{
    private const string ScenePath = @"C:\\Projekty\\Odyssey-Engine\\Save.odyssey";
    
    [RelayCommand]
    private async Task LoadAsync()
    {
        await messenger.Send<LoadSceneRequest, LoadSceneResponse>(LoadScene.Key, new LoadSceneRequest(ScenePath));
    }

    [RelayCommand]
    private async Task SaveAsync()
    {
        await messenger.Send<SaveSceneRequest, SaveSceneResponse>(SaveScene.Key, new SaveSceneRequest(ScenePath));
    }
}
