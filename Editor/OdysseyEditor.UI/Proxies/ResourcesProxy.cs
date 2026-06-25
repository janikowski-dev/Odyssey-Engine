using System.Windows;
using OdysseyEditor.UI.ViewModels.Resources;

namespace OdysseyEditor.UI.Proxies;

public class ResourcesProxy : Freezable
{
    protected override Freezable CreateInstanceCore() => new ResourcesProxy();

    public ResourcesViewModel Data
    {
        get => (ResourcesViewModel)GetValue(DataProperty);
        set => SetValue(DataProperty, value);
    }

    public static readonly DependencyProperty DataProperty = DependencyProperty.Register(nameof(Data), typeof(object), typeof(ResourcesProxy));
}