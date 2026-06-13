using System.Collections.ObjectModel;
using CommunityToolkit.Mvvm.ComponentModel;
using OdysseyEditor.Domain.Events;
using OdysseyEditor.Domain.Interfaces;
using OdysseyEditor.UI.Factories;

namespace OdysseyEditor.UI.ViewModels.Inspector;

public class InspectorViewModel(IEngineMessenger engineMessenger, IPropertyFieldFactory factory) : ObservableObject
{
    public ObservableCollection<ComponentInspector> Components { get; } = [];

    public async Task InitAsync()
    {
        await GetSchema();
        await CreateAndModifyEntity();
    }

    private async Task GetSchema()
    {
        await factory.InitAsync();
    }

    private async Task CreateAndModifyEntity()
    {
        CreateEntityResponse response = await engineMessenger.Send<CreateEntityRequest, CreateEntityResponse>(CreateEntity.Key, new CreateEntityRequest());
        
        Components.Clear();
        
        foreach (ComponentData component in response.Data)
        {
            Components.Add(new ComponentInspector(component.Name, component.Fields.Select(field => factory.Create(response.Index, component.Name, field.Key, field.Value))));
        }
    }
}
