using System.Text.Json;
using CommunityToolkit.Mvvm.ComponentModel;
using OdysseyEditor.Domain.Events;
using OdysseyEditor.Domain.Interfaces;

namespace OdysseyEditor.UI.ViewModels.Inspector;

public class InspectorViewModel(IEngineMessenger messenger) : ObservableObject
{
    private const string ModifiedComponentName = "TransformComponent";
    private const string ModifiedFieldName = "Position";
    
    public async Task InitAsync()
    {
        await GetSchema();
        await CreateAndModifyEntity();
    }

    private async Task GetSchema()
    {
        await messenger.Send<GetSchemaRequest, GetSchemaResponse>(Domain.Events.GetSchema.Key, new GetSchemaRequest());
    }

    private async Task CreateAndModifyEntity()
    {
        CreateEntityResponse response = await messenger.Send<CreateEntityRequest, CreateEntityResponse>(CreateEntity.Key, new CreateEntityRequest());
        
        ComponentData transform = response.Info.First(data => data.Type == ModifiedComponentName);
        Dictionary<string, JsonElement> fields = new(transform.Fields);
        float[] newPosition = [0f, 0f, 0f];
        fields[ModifiedFieldName] = JsonSerializer.SerializeToElement(newPosition);

        await messenger.Send<ModifyEntityRequest, ModifyEntityResponse>(ModifyEntity.Key, new ModifyEntityRequest
        {
            Type = ModifiedComponentName,
            Fields = fields,
            Index = response.Index,
        });
    }
}
