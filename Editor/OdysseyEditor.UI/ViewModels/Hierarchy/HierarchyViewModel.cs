using System.Collections.ObjectModel;
using CommunityToolkit.Mvvm.ComponentModel;
using CommunityToolkit.Mvvm.Input;
using CommunityToolkit.Mvvm.Messaging;
using OdysseyEditor.Domain.Events;
using OdysseyEditor.Domain.Interfaces;
using OdysseyEditor.UI.ViewModels.Messages;

namespace OdysseyEditor.UI.ViewModels.Hierarchy;

public partial class HierarchyViewModel(IMessenger messenger, IEngineMessenger engineMessenger) : ObservableObject, IRecipient<CreatedEntityMessage>
{
    [ObservableProperty]
    public partial int? SelectedEntity { get; set; }
    
    public ObservableCollection<int> Entities { get; } = [];

    public async Task InitAsync()
    {
        InitEngineMessaging();
        InitMessaging();
        await InitEntities();
    }

    public void Receive(CreatedEntityMessage message) => Entities.Add(message.Index);

    partial void OnSelectedEntityChanged(int? value)
    {
        if (!value.HasValue)
        {
            return;
        }
        
        messenger.Send(new SelectedEntityMessage { Index = value.Value });
    }

    private void InitEngineMessaging()
    {
        engineMessenger.On<DestroyedEntity>(DestroyedEntity.Key, entity => System.Windows.Application.Current.Dispatcher.Invoke(() =>
        {
            if (!Entities.Contains(entity.Index))
            {
                return;
            }
            
            Entities.Remove(entity.Index);
        }));
        
        engineMessenger.On<CreatedEntity>(CreatedEntity.Key, entity => System.Windows.Application.Current.Dispatcher.Invoke(() =>
        {
            if (Entities.Contains(entity.Index))
            {
                return;
            }
            
            Entities.Add(entity.Index);
        }));
    }

    private void InitMessaging()
    {
        messenger.RegisterAll(this);
    }

    private async Task InitEntities()
    {
        GetEntitiesResponse response = await engineMessenger.Send<GetEntitiesRequest, GetEntitiesResponse>(GetEntities.Key, new GetEntitiesRequest());

        foreach (int index in response.Indexes)
        {
            if (Entities.Contains(index))
            {
                continue;
            }
            
            Entities.Add(index);
        }
    }

    [RelayCommand]
    private async Task CreateEntityAsync()
    {
        await engineMessenger.Send<CreateEntityRequest, CreateEntityResponse>(CreateEntity.Key, new CreateEntityRequest());
    }

    [RelayCommand]
    private async Task DestroyEntityAsync(int index)
    {
        await engineMessenger.Send<DestroyEntityRequest, DestroyEntityResponse>(DestroyEntity.Key, new DestroyEntityRequest(index));
    }
}