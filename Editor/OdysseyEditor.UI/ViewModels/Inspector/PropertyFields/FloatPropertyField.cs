using CommunityToolkit.Mvvm.ComponentModel;
using OdysseyEditor.Application.Interfaces;
using OdysseyEditor.Domain.Interfaces;

namespace OdysseyEditor.UI.ViewModels.Inspector.PropertyFields;

public partial class FloatPropertyField(
    IEngineMessenger engineMessenger,
    ILogService logService,
    int index,
    string name,
    string component,
    float value
) : PropertyField(engineMessenger, logService, index, name, component)
{
    [ObservableProperty]
    public partial float Value { get; set; } = value;

    partial void OnValueChanged(float value)
    {
        HandleFieldChange(new Dictionary<string, object>
        {
            { Name, Value }
        });
    }
}