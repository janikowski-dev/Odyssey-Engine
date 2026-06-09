using System.Windows.Controls;
using System.Windows.Input;
using Microsoft.Xaml.Behaviors;

namespace OdysseyEditor.UI.Behaviors;

public class MoveFocusBehavior : Behavior<TextBox>
{
    protected override void OnAttached() => AssociatedObject.KeyDown += TryMovingFocus;

    protected override void OnDetaching() => AssociatedObject.KeyDown -= TryMovingFocus;

    private void TryMovingFocus(object sender, KeyEventArgs e)
    {
        if (e.Key != Key.Enter)
        {
            return;
        }
        
        AssociatedObject.MoveFocus(new TraversalRequest(FocusNavigationDirection.Next));
    }
}