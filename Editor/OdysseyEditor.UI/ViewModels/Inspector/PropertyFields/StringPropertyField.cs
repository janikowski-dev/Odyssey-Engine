using CommunityToolkit.Mvvm.ComponentModel;
using OdysseyEditor.Application.Interfaces;
using OdysseyEditor.Domain.Interfaces;

namespace OdysseyEditor.UI.ViewModels.Inspector.PropertyFields;

public partial class StringPropertyField(
    IEngineMessenger engineMessenger,
    ILogService logService,
    int index,
    string name,
    string component,
    string value
) : PropertyField(engineMessenger, logService, index, name, component)
{
    [ObservableProperty]
    public partial string Value { get; set; } = value;

    partial void OnValueChanged(string value)
    {
        HandleFieldChange(new Dictionary<string, object>
        {
            { Name, Value }
        });
    }
}