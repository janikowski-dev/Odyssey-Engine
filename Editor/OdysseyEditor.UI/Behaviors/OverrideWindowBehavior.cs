using System.Reflection;
using System.Windows;
using System.Windows.Controls.Primitives;
using Microsoft.Xaml.Behaviors;

namespace OdysseyEditor.UI.Behaviors;

public sealed class OverrideWindowBehavior : Behavior<Popup>
{
    private Window? _window;

    public static readonly DependencyProperty TargetProperty = DependencyProperty.Register(nameof(Target), typeof(FrameworkElement), typeof(OverrideWindowBehavior), new PropertyMetadata(null, OnTargetChanged));
        
    private static readonly MethodInfo? UpdatePosition = typeof(Popup).GetMethod("UpdatePosition", BindingFlags.Instance | BindingFlags.NonPublic);

    public FrameworkElement Target
    {
        get => (FrameworkElement)GetValue(TargetProperty);
        set => SetValue(TargetProperty, value);
    }

    protected override void OnAttached()
    {
        base.OnAttached();
        AssociatedObject.Placement = PlacementMode.Relative;
        Hook(Target);
    }

    protected override void OnDetaching()
    {
        Unhook(Target);
        UnhookWindow();
        base.OnDetaching();
    }

    private static void OnTargetChanged(DependencyObject d, DependencyPropertyChangedEventArgs e)
    {
        var self = (OverrideWindowBehavior)d;
        self.Unhook(e.OldValue as FrameworkElement);
        self.Hook(e.NewValue as FrameworkElement);
    }

    private void Hook(FrameworkElement target)
    {
        if (target == null) return;
        AssociatedObject.PlacementTarget = target;
        target.SizeChanged += (_, __) => Sync();
        if (target.IsLoaded) HookWindow();
        else target.Loaded += (_, __) => { HookWindow(); Sync(); };
    }

    private void Unhook(FrameworkElement target)
    {
        if (target != null) target.SizeChanged -= (_, __) => Sync();
    }

    private void HookWindow()
    {
        if (_window != null) return;
        _window = Window.GetWindow(Target);
        if (_window == null) return;
        _window.LocationChanged += (_, __) => Reposition();
        _window.SizeChanged     += (_, __) => Reposition();
        _window.StateChanged    += (_, __) => Sync();
    }

    private void UnhookWindow() => _window = null;

    private void Sync()
    {
        if (Target == null) return;
        AssociatedObject.Width  = Target.ActualWidth;
        AssociatedObject.Height = Target.ActualHeight;
        Reposition();
    }

    private void Reposition()
    {
        if (AssociatedObject.IsOpen)
            UpdatePosition?.Invoke(AssociatedObject, null);
    }
}