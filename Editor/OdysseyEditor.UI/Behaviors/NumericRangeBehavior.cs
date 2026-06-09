using System.Windows.Controls;
using System.Windows.Input;
using Microsoft.Xaml.Behaviors;

namespace OdysseyEditor.UI.Behaviors;

public class NumericRangeBehavior : Behavior<TextBox>
{
    public int Min { get; set; }
    public int Max { get; set; }

    protected override void OnAttached() => AssociatedObject.PreviewTextInput += ProcessInput;

    protected override void OnDetaching() => AssociatedObject.PreviewTextInput -= ProcessInput;

    private void ProcessInput(object sender, TextCompositionEventArgs e)
    {
        string newText = AssociatedObject.Text + e.Text;

        if (Min < 0 && newText == "-")
        {
            return;
        }

        if (!int.TryParse(newText, out int value) || value < Min || value > Max)
        {
            e.Handled = true;
        }
    }
}