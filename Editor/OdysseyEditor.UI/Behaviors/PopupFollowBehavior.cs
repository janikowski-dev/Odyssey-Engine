using System.Windows;
using System.Windows.Controls.Primitives;
using Microsoft.Xaml.Behaviors;

namespace OdysseyEditor.UI.Behaviors;

public sealed class PopupFollowWindowBehavior : Behavior<Popup>
{
    private Window? _window;

    protected override void OnAttached()
    {
        AddCallbacks();
    }

    protected override void OnDetaching()
    {
        RemoveCallbacks();
        Unhook();
    }

    private void OnUnloaded(object sender, RoutedEventArgs e) => Unhook();

    private void OnLoaded(object sender, RoutedEventArgs e)
    {
        _window = Window.GetWindow(AssociatedObject);

        if (_window == null)
        {
            return;
        }
        
        _window.LocationChanged += Reposition;
        _window.SizeChanged += Reposition;
    }

    private void Unhook()
    {
        if (_window == null)
        {
            return;
        }
        
        _window.LocationChanged -= Reposition;
        _window.SizeChanged -= Reposition;
        _window = null;
    }

    private void Reposition(object? sender, EventArgs e)
    {
        if (!AssociatedObject.IsOpen)
        {
            return;
        }
        
        AssociatedObject.HorizontalOffset += 1;
        AssociatedObject.HorizontalOffset -= 1;
    }

    private void AddCallbacks()
    {
        AssociatedObject.Unloaded += OnUnloaded;
        AssociatedObject.Loaded += OnLoaded;
    }

    private void RemoveCallbacks()
    {
        AssociatedObject.Unloaded -= OnUnloaded;
        AssociatedObject.Loaded -= OnLoaded;
    }
}