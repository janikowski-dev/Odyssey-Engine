using CommunityToolkit.Mvvm.ComponentModel;
using OdysseyEditor.Application.Interfaces;
using OdysseyEditor.Domain.Interfaces;

namespace OdysseyEditor.UI.ViewModels.Inspector.PropertyFields;

public partial class IntPropertyField(
    IEngineMessenger engineMessenger,
    ILogService logService,
    int index,
    string name,
    string component,
    int value
) : PropertyField(engineMessenger, logService, index, name, component)
{
    [ObservableProperty]
    public partial int Value { get; set; } = value;

    partial void OnValueChanged(int value)
    {
        HandleFieldChange(new Dictionary<string, object>
        {
            { Name, Value }
        });
    }
}