using CommunityToolkit.Mvvm.ComponentModel;
using CommunityToolkit.Mvvm.Messaging;
using OdysseyEditor.Application.Interfaces;

namespace OdysseyEditor.UI.ViewModels.Inspector;

public partial class InspectorViewModel(
    IMessenger messenger,
    IUndoService undoService
) : ObservableObject
{
    public void Init() => InitMessaging();

    private void InitMessaging()
    {
        messenger.RegisterAll(this);
    }
}
