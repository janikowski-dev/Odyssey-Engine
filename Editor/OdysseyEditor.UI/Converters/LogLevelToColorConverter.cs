using System.Globalization;
using System.Windows.Data;
using System.Windows.Media;
using OdysseyEditor.Application.Enums;

namespace OdysseyEditor.UI.Converters;

public class LogLevelToColorConverter : IValueConverter
{
    public object Convert(object? value, Type targetType, object? parameter, CultureInfo culture)
    {
        return (LogLevel?)value switch
        {
            LogLevel.Error => new SolidColorBrush(Color.FromRgb(0xFF, 0x6B, 0x6B)),
            LogLevel.Warning => new SolidColorBrush(Color.FromRgb(0xFF, 0xD9, 0x3D)),
            LogLevel.Info => new SolidColorBrush(Color.FromRgb(0xAB, 0xB2, 0xBF)),
            _ => new SolidColorBrush(Colors.White)
        };
    }

    public object ConvertBack(object? value, Type targetType, object? parameter, CultureInfo culture) => throw new NotSupportedException();
}