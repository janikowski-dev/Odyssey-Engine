using CommunityToolkit.Mvvm.ComponentModel;
using OdysseyEditor.Domain.Events;
using OdysseyEditor.Domain.Interfaces;

namespace OdysseyEditor.UI.ViewModels.Inspector;

public class InspectorViewModel(IEngineMessenger messenger) : ObservableObject
{
    public async Task InitAsync()
    {
        GetSchemaResponse response = await messenger.Send<GetSchemaRequest, GetSchemaResponse>(GetSchema.Key, new GetSchemaRequest());
    }
}
