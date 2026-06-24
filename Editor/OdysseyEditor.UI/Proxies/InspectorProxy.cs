using System.Windows;
using OdysseyEditor.UI.ViewModels.Inspector;

namespace OdysseyEditor.UI.Proxies;

public class InspectorProxy : Freezable
{
    protected override Freezable CreateInstanceCore() => new InspectorProxy();

    public InspectorViewModel Data
    {
        get => (InspectorViewModel)GetValue(DataProperty);
        set => SetValue(DataProperty, value);
    }

    public static readonly DependencyProperty DataProperty = DependencyProperty.Register(nameof(Data), typeof(object), typeof(InspectorProxy));
}