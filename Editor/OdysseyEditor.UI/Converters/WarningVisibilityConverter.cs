using System.Globalization;
using System.Windows.Data;

namespace OdysseyEditor.UI.Converters;

public sealed class WarningVisibilityConverter : IMultiValueConverter
{
    public object Convert(object[] values, Type targetType, object parameter, CultureInfo culture)
    {
        bool isEngineFocused = values.Length > 0 && values[0] is true;
        bool isWindowActive  = values.Length > 1 && values[1] is true;
        return !isEngineFocused && isWindowActive;
    }

    public object[] ConvertBack(object value, Type[] targetTypes, object parameter, CultureInfo culture) => throw new NotSupportedException();
}