using System.Collections.ObjectModel;
using CommunityToolkit.Mvvm.ComponentModel;

namespace OdysseyEditor.UI.ViewModels.Inspector;

public partial class ComponentInspector(string type, IEnumerable<PropertyField> properties) : ObservableObject
{
    [ObservableProperty]
    public partial string Type { get; set; } = type;
    
    [ObservableProperty]
    public partial ObservableCollection<PropertyField> Properties { get; set; } = new(properties);
}