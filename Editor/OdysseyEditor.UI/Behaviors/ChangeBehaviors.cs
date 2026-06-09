using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using Microsoft.Xaml.Behaviors;

namespace OdysseyEditor.UI.Behaviors;

public class ComboBoxChangeBehavior : TypedChangeBehavior<ComboBox>
{
    protected override void Subscribe(ComboBox target)
    {
        target.DropDownClosed += HandlePostChange;
        target.DropDownOpened += HandlePreChange;
    }

    protected override void Unsubscribe(ComboBox target)
    {
        target.DropDownClosed -= HandlePostChange;
        target.DropDownOpened -= HandlePreChange;
    }
    
    private void HandlePreChange(object? sender, EventArgs e)  => PreChangeCommand.Execute(ChangeCommandParameter);
    
    private void HandlePostChange(object? sender, EventArgs e) => PostChangeCommand.Execute(ChangeCommandParameter);
}

public class TextChangeBehavior : TypedChangeBehavior<TextBox>
{
    protected override void Subscribe(TextBox target)
    {
        target.LostFocus += HandlePostChange;
        target.GotFocus += HandlePreChange;
    }

    protected override void Unsubscribe(TextBox target)
    {
        target.LostFocus -= HandlePostChange;
        target.GotFocus -= HandlePreChange;
    }

    private void HandlePreChange(object sender, RoutedEventArgs e)  => PreChangeCommand.Execute(ChangeCommandParameter);
    
    private void HandlePostChange(object sender, RoutedEventArgs e) => PostChangeCommand.Execute(ChangeCommandParameter);
}

public abstract class TypedChangeBehavior<TElement> : ChangeBehavior where TElement : FrameworkElement
{
    protected override void OnAttached()  => Subscribe((TElement)AssociatedObject);
    
    protected override void OnDetaching() => Unsubscribe((TElement)AssociatedObject);

    protected abstract void Subscribe(TElement target);
    protected abstract void Unsubscribe(TElement target);
}

public abstract class ChangeBehavior : Behavior<FrameworkElement>
{
    public static readonly DependencyProperty ChangeCommandParameterProperty = DependencyProperty.Register(nameof(ChangeCommandParameter), typeof(object), typeof(ChangeBehavior));
    public static readonly DependencyProperty PostChangeCommandProperty = DependencyProperty.Register(nameof(PostChangeCommand), typeof(ICommand), typeof(ChangeBehavior));
    public static readonly DependencyProperty PreChangeCommandProperty = DependencyProperty.Register(nameof(PreChangeCommand), typeof(ICommand), typeof(ChangeBehavior));

    public ICommand PreChangeCommand
    {
        get => (ICommand)GetValue(PreChangeCommandProperty);
        set => SetValue(PreChangeCommandProperty, value);
    }

    public ICommand PostChangeCommand
    {
        get => (ICommand)GetValue(PostChangeCommandProperty);
        set => SetValue(PostChangeCommandProperty, value);
    }

    public object? ChangeCommandParameter
    {
        get => GetValue(ChangeCommandParameterProperty);
        set => SetValue(ChangeCommandParameterProperty, value);
    }
}