using System.Windows;
using System.Windows.Input;
using Microsoft.Xaml.Behaviors;

namespace OdysseyEditor.UI.Behaviors;

public sealed class WindowActivatedBehavior : Behavior<FrameworkElement>
{
    public static readonly DependencyProperty CommandProperty = DependencyProperty.Register(nameof(Command), typeof(ICommand), typeof(WindowActivatedBehavior));

    public ICommand? Command
    {
        get => (ICommand?)GetValue(CommandProperty);
        set => SetValue(CommandProperty, value);
    }

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

    private void OnLoaded(object sender, RoutedEventArgs e)
    {
        Unhook();
        Hook();
    }

    private void OnUnloaded(object sender, RoutedEventArgs e) => Unhook();

    private void Hook()
    {
        _window = Window.GetWindow(AssociatedObject);

        if (_window is not null)
        {
            _window.Activated += OnActivated;
        }
    }

    private void OnActivated(object? sender, EventArgs e)
    {
        if (Command?.CanExecute(null) == true)
        {
            Command.Execute(null);
        }
    }

    private void Unhook()
    {
        if (_window is null)
        {
            return;
        }
        
        _window.Activated -= OnActivated;
        _window = null;
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