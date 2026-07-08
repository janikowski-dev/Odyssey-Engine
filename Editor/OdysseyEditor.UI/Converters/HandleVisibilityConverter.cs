using System.Globalization;
using System.Windows.Data;

namespace OdysseyEditor.UI.Converters;

public sealed class HandleVisibilityConverter : IMultiValueConverter
{
    public object Convert(object[] values, Type targetType, object parameter, CultureInfo culture)
    {
        bool isWindowActive  = values.Length > 0 && values[0] is true;
        bool isInPlay = values.Length > 1 && values[1] is true;
        return isWindowActive && !isInPlay;
    }

    public object[] ConvertBack(object value, Type[] targetTypes, object parameter, CultureInfo culture) => throw new NotSupportedException();
}