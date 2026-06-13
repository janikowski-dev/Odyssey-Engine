using CommunityToolkit.Mvvm.ComponentModel;
using OdysseyEditor.Application.Interfaces;
using OdysseyEditor.Domain.Interfaces;

namespace OdysseyEditor.UI.ViewModels.Inspector.PropertyFields;

public partial class Vector2PropertyField(
    IEngineMessenger engineMessenger,
    ILogService logService,
    int index,
    string name,
    string component,
    float x,
    float y
) : PropertyField(engineMessenger, logService, index, name, component)
{
    [ObservableProperty]
    public partial float X { get; set; } = x;

    [ObservableProperty]
    public partial float Y { get; set; } = y;

    partial void OnXChanged(float value) => HandleFieldChange();

    partial void OnYChanged(float value) => HandleFieldChange();
    
    private void HandleFieldChange()
    {
        HandleFieldChange(new Dictionary<string, object>
        {
            { Name, new[] { X, Y } }
        });
    }
}