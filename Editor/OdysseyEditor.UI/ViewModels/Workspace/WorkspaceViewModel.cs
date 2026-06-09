using CommunityToolkit.Mvvm.ComponentModel;
using CommunityToolkit.Mvvm.Messaging;
using OdysseyEditor.Application.Interfaces;

namespace OdysseyEditor.UI.ViewModels.Workspace;

public partial class WorkspaceViewModel(
    IMessenger messenger,
    ILogService logService
) : ObservableObject
{
    public void Init() => messenger.RegisterAll(this);
}