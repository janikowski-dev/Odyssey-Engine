using System.Windows;
using System.Windows.Controls;
using OdysseyEditor.UI.ViewModels.Inspector;
using BoolPropertyField = OdysseyEditor.UI.ViewModels.Inspector.PropertyFields.BoolPropertyField;
using FloatPropertyField = OdysseyEditor.UI.ViewModels.Inspector.PropertyFields.FloatPropertyField;
using IntPropertyField = OdysseyEditor.UI.ViewModels.Inspector.PropertyFields.IntPropertyField;
using StringPropertyField = OdysseyEditor.UI.ViewModels.Inspector.PropertyFields.StringPropertyField;
using Vector2PropertyField = OdysseyEditor.UI.ViewModels.Inspector.PropertyFields.Vector2PropertyField;
using Vector3PropertyField = OdysseyEditor.UI.ViewModels.Inspector.PropertyFields.Vector3PropertyField;
using Vector4PropertyField = OdysseyEditor.UI.ViewModels.Inspector.PropertyFields.Vector4PropertyField;

namespace OdysseyEditor.UI.Selectors;

public class PropertyFieldTemplateSelector : DataTemplateSelector
{
    public DataTemplate? Vector2Template { get; set; }
    public DataTemplate? Vector3Template { get; set; }
    public DataTemplate? Vector4Template { get; set; }
    public DataTemplate? StringTemplate { get; set; }
    public DataTemplate? FloatTemplate { get; set; }
    public DataTemplate? BoolTemplate { get; set; }
    public DataTemplate? IntTemplate { get; set; }

    public override DataTemplate? SelectTemplate(object? item, DependencyObject container) => item switch
    {
        StringPropertyField => StringTemplate,
        Vector2PropertyField => Vector2Template,
        Vector3PropertyField => Vector3Template,
        Vector4PropertyField => Vector4Template,
        FloatPropertyField => FloatTemplate,
        BoolPropertyField => BoolTemplate,
        IntPropertyField => IntTemplate,
        _ => base.SelectTemplate(item, container)
    };
}