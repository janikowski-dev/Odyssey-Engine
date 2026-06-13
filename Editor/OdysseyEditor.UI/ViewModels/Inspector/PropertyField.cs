using CommunityToolkit.Mvvm.ComponentModel;
using OdysseyEditor.Application.Interfaces;
using OdysseyEditor.Domain.Events;
using OdysseyEditor.Domain.Interfaces;

namespace OdysseyEditor.UI.ViewModels.Inspector;

public partial class PropertyField(IEngineMessenger engineMessenger, ILogService logService, int index, string name, string component) : ObservableObject
{
    [ObservableProperty]
    public partial string Name { get; set; } = name;

    protected async void HandleFieldChange(Dictionary<string, object> fields)
    {
        try
        {
            await engineMessenger.Send<ModifyEntityRequest, ModifyEntityResponse>(ModifyEntity.Key, new ModifyEntityRequest
            {
                Component = component,
                Fields = fields,
                Index = index
            });
        }
        catch (Exception caughtException)
        {
            logService.LogError(caughtException.Message);
        }
    }
}