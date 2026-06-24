using System.Collections.ObjectModel;
using CommunityToolkit.Mvvm.ComponentModel;
using CommunityToolkit.Mvvm.Input;
using CommunityToolkit.Mvvm.Messaging;
using OdysseyEditor.Application.Interfaces;
using OdysseyEditor.Domain.Events;
using OdysseyEditor.Domain.Interfaces;
using OdysseyEditor.UI.Factories;
using OdysseyEditor.UI.ViewModels.Messages;

namespace OdysseyEditor.UI.ViewModels.Inspector;

public partial class InspectorViewModel(
    IEngineMessenger engineMessenger,
    IPropertyFieldFactory fieldFactory,
    ILogService logService,
    IMessenger messenger
) : ObservableObject, IRecipient<SelectedEntityMessage>
{
    [ObservableProperty]
    public partial ObservableCollection<string> AvailableComponentTypes { get; set; } = [];

    [ObservableProperty]
    public partial int SelectedIndex { get; set; } = -1;
    
    public ObservableCollection<ComponentInspector> Components { get; } = [];
    
    public async Task InitAsync()
    {
        InitMessaging();
        await InitFactory();
        await InitSchema();
    }

    public async void Receive(SelectedEntityMessage message)
    {
        try
        {
            CacheSelection(message);
            await Refresh();
        }
        catch (Exception caughtException)
        {
            HandleError(caughtException);
        }
    }

    [RelayCommand(CanExecute = nameof(HasSomethingSelected))]
    private async Task AddComponentAsync(string componentName)
    {
        await SendModifyMessageAsync(componentName);
        await Refresh();
    }
    
    [RelayCommand(CanExecute = nameof(HasSomethingSelected))]
    private async Task RemoveComponentAsync(ComponentInspector inspector)
    {
        await SendRemoveMessageAsync(inspector);
        await Refresh();
    }

    private void CacheSelection(SelectedEntityMessage message)
    {
        SelectedIndex = message.Index;
    }

    private void HandleError(Exception caughtException)
    {
        logService.LogError(caughtException.Message);
    }

    private async Task SendModifyMessageAsync(string componentName)
    {
        await engineMessenger.Send<ModifyEntityRequest, ModifyEntityResponse>(ModifyEntity.Key, new ModifyEntityRequest(
            SelectedIndex,
            new Dictionary<string, object>(),
            componentName
        ));
    }

    private async Task SendRemoveMessageAsync(ComponentInspector inspector)
    {
        await engineMessenger.Send<RemoveComponentRequest, RemoveComponentResponse>(RemoveComponent.Key, new RemoveComponentRequest(SelectedIndex, inspector.Type));
    }

    private async Task Refresh()
    {
        SelectEntityResponse response = await engineMessenger.Send<SelectEntityRequest, SelectEntityResponse>(SelectEntity.Key, new SelectEntityRequest(SelectedIndex));

        Components.Clear();

        foreach (ComponentData component in response.Data)
        {
            Components.Add(new ComponentInspector(component.Name, component.Fields.Select(field => fieldFactory.Create(SelectedIndex, component.Name, field.Key, field.Value))));
        }
    }

    private void InitMessaging()
    {
        messenger.RegisterAll(this);
    }

    private async Task InitFactory()
    {
        await fieldFactory.InitAsync();
    }

    private async Task InitSchema()
    {
        GetSchemaResponse response = await engineMessenger.Send<GetSchemaRequest, GetSchemaResponse>(GetSchema.Key, new GetSchemaRequest());

        if (response == default)
        {
            return;
        }
        
        foreach (ComponentInfo component in response.Schema)
        {
            AvailableComponentTypes.Add(component.Name);
        }
    }

    private bool HasSomethingSelected() => SelectedIndex >= 0;
}
