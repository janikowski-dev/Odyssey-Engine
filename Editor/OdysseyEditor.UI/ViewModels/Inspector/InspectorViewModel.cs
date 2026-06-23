using System.Collections.ObjectModel;
using CommunityToolkit.Mvvm.ComponentModel;
using CommunityToolkit.Mvvm.Messaging;
using OdysseyEditor.Application.Interfaces;
using OdysseyEditor.Domain.Events;
using OdysseyEditor.Domain.Interfaces;
using OdysseyEditor.UI.Factories;
using OdysseyEditor.UI.ViewModels.Messages;

namespace OdysseyEditor.UI.ViewModels.Inspector;

public class InspectorViewModel(
    IEngineMessenger engineMessenger,
    IPropertyFieldFactory fieldFactory,
    ILogService logService,
    IMessenger messenger
) : ObservableObject, IRecipient<SelectedEntityMessage>
{
    public ObservableCollection<ComponentInspector> Components { get; } = [];

    public async Task InitAsync()
    {
        InitMessaging();
        await InitFactory();
    }

    private void InitMessaging()
    {
        messenger.RegisterAll(this);
    }

    private async Task InitFactory()
    {
        await fieldFactory.InitAsync();
    }

    public async void Receive(SelectedEntityMessage message)
    {
        try
        {
            SelectEntityResponse response = await engineMessenger.Send<SelectEntityRequest, SelectEntityResponse>(SelectEntity.Key, new SelectEntityRequest(message.Index));

            Components.Clear();

            foreach (ComponentData component in response.Data)
            {
                Components.Add(new ComponentInspector(component.Name, component.Fields.Select(field => fieldFactory.Create(message.Index, component.Name, field.Key, field.Value))));
            }
        }
        catch (Exception caughtException)
        {
            logService.LogError(caughtException.Message);
        }
    }
}
