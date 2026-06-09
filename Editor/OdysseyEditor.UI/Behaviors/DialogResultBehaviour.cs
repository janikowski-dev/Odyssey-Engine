using System.Windows;
using System.Windows.Controls;
using Microsoft.Xaml.Behaviors;

namespace OdysseyEditor.UI.Behaviors;

public class DialogResultBehavior : Behavior<Button>
{
    public static readonly DependencyProperty DialogResultProperty = DependencyProperty.Register(nameof(DialogResult), typeof(bool), typeof(DialogResultBehavior));

    public bool DialogResult
    {
        get => (bool)GetValue(DialogResultProperty);
        set => SetValue(DialogResultProperty, value);
    }

    protected override void OnAttached()
    {
        AssociatedObject.Click += CloseWindowWithResult;
    }

    protected override void OnDetaching()
    {
        AssociatedObject.Click -= CloseWindowWithResult;
    }

    private void CloseWindowWithResult(object sender, RoutedEventArgs e)
    {
        Window.GetWindow(AssociatedObject)!.DialogResult = DialogResult;
    }
}