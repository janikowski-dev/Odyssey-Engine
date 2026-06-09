using System.Globalization;
using System.Windows;
using System.Windows.Data;

namespace OdysseyEditor.UI.Converters;

public class InverseZeroToVisibilityConverter : IValueConverter
{
    public object Convert(object? value, Type targetType, object? parameter, CultureInfo culture) => value is not 0 ? Visibility.Collapsed : Visibility.Visible;
    public object ConvertBack(object? value, Type targetType, object? parameter, CultureInfo culture) => throw new NotSupportedException();
}