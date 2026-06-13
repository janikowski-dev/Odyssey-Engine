using CommunityToolkit.Mvvm.ComponentModel;
using OdysseyEditor.Application.Interfaces;
using OdysseyEditor.Domain.Interfaces;

namespace OdysseyEditor.UI.ViewModels.Inspector.PropertyFields;

public partial class BoolPropertyField(
    IEngineMessenger engineMessenger,
    ILogService logService,
    int index,
    string name,
    string component,
    bool value
) : PropertyField(engineMessenger, logService, index, name, component)
{
    [ObservableProperty]
    public partial bool Value { get; set; } = value;

    partial void OnValueChanged(bool value)
    {
        HandleFieldChange(new Dictionary<string, object>
        {
            { Name, Value }
        });
    }
}