using CommunityToolkit.Mvvm.ComponentModel;
using CommunityToolkit.Mvvm.Input;
using CommunityToolkit.Mvvm.Messaging;
using OdysseyEditor.Application.Interfaces;

namespace OdysseyEditor.UI.ViewModels.ControlsBar;

public partial class ControlsBarViewModel(
    IUndoService undoService,
    IMessenger messenger,
    ILogService logService
) : ObservableObject
{
    public void Init()
    {
        InitMessaging();
        InitUndoRedo();
        InitSave();
    }
    
    [RelayCommand(CanExecute = nameof(HasSomethingToSave))]
    private async Task SaveAsync()
    {
    }

    [RelayCommand(CanExecute = nameof(HasSomethingToRedo))]
    private async Task RedoAsync()
    {
        await undoService.RedoAsync();
    }

    [RelayCommand(CanExecute = nameof(HasSomethingToUndo))]
    private async Task UndoAsync()
    {
        await undoService.UndoAsync();
    }

    private bool HasSomethingToSave() => false;

    private bool HasSomethingToRedo() => undoService.CanRedo;
    
    private bool HasSomethingToUndo() => undoService.CanUndo;
    
    private void InitSave()
    {
    }

    private void InitUndoRedo()
    {
        undoService.StackChanged += (_, _) =>
        {
            UndoCommand.NotifyCanExecuteChanged();
            RedoCommand.NotifyCanExecuteChanged();
        };
    }

    private void InitMessaging()
    {
        messenger.RegisterAll(this);
    }
}
