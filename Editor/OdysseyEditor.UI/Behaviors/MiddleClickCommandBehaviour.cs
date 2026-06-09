using System.Windows;
using System.Windows.Input;
using Microsoft.Xaml.Behaviors;

namespace OdysseyEditor.UI.Behaviors;

public class MiddleClickCommandBehavior : Behavior<FrameworkElement>
{
    public static readonly DependencyProperty CommandProperty = DependencyProperty.Register(nameof(Command), typeof(ICommand), typeof(MiddleClickCommandBehavior));

    public ICommand Command
    {
        get => (ICommand)GetValue(CommandProperty);
        set => SetValue(CommandProperty, value);
    }

    protected override void OnAttached()
    {
        AssociatedObject.MouseDown += HandleMouseDown;
    }

    protected override void OnDetaching()
    {
        AssociatedObject.MouseDown -= HandleMouseDown;
    }

    private void HandleMouseDown(object sender, MouseButtonEventArgs e)
    {
        if (e.ChangedButton == MouseButton.Middle)
        {
            Command.Execute(AssociatedObject.DataContext);
        }
    }
}