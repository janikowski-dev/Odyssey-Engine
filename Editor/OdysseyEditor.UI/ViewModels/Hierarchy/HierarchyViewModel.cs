using System.Collections.ObjectModel;
using CommunityToolkit.Mvvm.ComponentModel;
using CommunityToolkit.Mvvm.Messaging;
using OdysseyEditor.Domain.Events;
using OdysseyEditor.Domain.Interfaces;
using OdysseyEditor.UI.ViewModels.Messages;

namespace OdysseyEditor.UI.ViewModels.Hierarchy;

public partial class HierarchyViewModel(IMessenger messenger, IEngineMessenger engineMessenger) : ObservableObject, IRecipient<AddedEntityMessage>
{
    [ObservableProperty]
    public partial int? SelectedEntity { get; set; }
    
    public ObservableCollection<int> Entities { get; } = [];

    public void Init()
    {
        engineMessenger.On<AddedEntity>(AddedEntity.Key, addedEntity => Entities.Add(addedEntity.Index));
        messenger.RegisterAll(this);
    }

    public void Receive(AddedEntityMessage message) => Entities.Add(message.Index);

    partial void OnSelectedEntityChanged(int? value)
    {
        if (!value.HasValue)
        {
            return;
        }
        
        messenger.Send(new SelectedEntityMessage { Index = value.Value });
    }
}