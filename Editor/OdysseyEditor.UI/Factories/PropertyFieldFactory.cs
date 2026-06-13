using System.Text.Json;
using OdysseyEditor.Application.Interfaces;
using OdysseyEditor.Domain.Events;
using OdysseyEditor.Domain.Interfaces;
using OdysseyEditor.UI.ViewModels.Inspector;
using BoolPropertyField = OdysseyEditor.UI.ViewModels.Inspector.PropertyFields.BoolPropertyField;
using FloatPropertyField = OdysseyEditor.UI.ViewModels.Inspector.PropertyFields.FloatPropertyField;
using IntPropertyField = OdysseyEditor.UI.ViewModels.Inspector.PropertyFields.IntPropertyField;
using StringPropertyField = OdysseyEditor.UI.ViewModels.Inspector.PropertyFields.StringPropertyField;
using Vector2PropertyField = OdysseyEditor.UI.ViewModels.Inspector.PropertyFields.Vector2PropertyField;
using Vector3PropertyField = OdysseyEditor.UI.ViewModels.Inspector.PropertyFields.Vector3PropertyField;
using Vector4PropertyField = OdysseyEditor.UI.ViewModels.Inspector.PropertyFields.Vector4PropertyField;

namespace OdysseyEditor.UI.Factories;

public interface IPropertyFieldFactory
{
    PropertyField Create(int entityIndex, string componentName, string fieldKey, JsonElement fieldValue);
    Task InitAsync();
}

public class PropertyFieldFactory(IEngineMessenger engineMessenger, ILogService logService) : IPropertyFieldFactory
{
    private static readonly Dictionary<string, Dictionary<string, string>> Schema = new();

    public PropertyField Create(int entityIndex, string componentName, string fieldKey, JsonElement fieldValue)
    {
        string fieldType = Schema[componentName][fieldKey];
        
        return fieldType switch
        {
            "Int" => new IntPropertyField(engineMessenger, logService, entityIndex, fieldKey, componentName, fieldValue.Deserialize<int>()),
            "Float" => new FloatPropertyField(engineMessenger, logService, entityIndex, fieldKey, componentName, fieldValue.Deserialize<float>()),
            "Bool" => new BoolPropertyField(engineMessenger, logService, entityIndex, fieldKey, componentName, fieldValue.Deserialize<bool>()),
            "String" => new StringPropertyField(engineMessenger, logService, entityIndex, fieldKey, componentName, fieldValue.Deserialize<string>()!),
            "Vector2" => new Vector2PropertyField(engineMessenger, logService, entityIndex, fieldKey, componentName, fieldValue.Deserialize<float[]>()![0], fieldValue.Deserialize<float[]>()![1]),
            "Vector3" => new Vector3PropertyField(engineMessenger, logService, entityIndex, fieldKey, componentName, fieldValue.Deserialize<float[]>()![0], fieldValue.Deserialize<float[]>()![1], fieldValue.Deserialize<float[]>()![2]),
            "Vector4" => new Vector4PropertyField(engineMessenger, logService, entityIndex, fieldKey, componentName, fieldValue.Deserialize<float[]>()![0], fieldValue.Deserialize<float[]>()![1], fieldValue.Deserialize<float[]>()![2], fieldValue.Deserialize<float[]>()![3]),
            _ => throw new NotSupportedException()
        };
    }

    public async Task InitAsync()
    {
        GetSchemaResponse response = await engineMessenger.Send<GetSchemaRequest, GetSchemaResponse>(GetSchema.Key, new GetSchemaRequest());
            
        foreach (ComponentInfo component in response.Schema)
        {
            Schema[component.Name] = component.Fields.ToDictionary(field => field.Name, field => field.Type);
        }
    }
}