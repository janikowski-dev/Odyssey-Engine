using System.Globalization;
using System.Text.RegularExpressions;
using System.Windows.Data;

namespace OdysseyEditor.UI.Converters;

public partial class PascalCaseToWordsConverter : IValueConverter
{
    [GeneratedRegex("([a-z0-9])([A-Z])")]
    private static partial Regex LowerUpper();

    [GeneratedRegex("([A-Z]+)([A-Z][a-z])")]
    private static partial Regex AcronymWord();

    public object Convert(object? value, Type targetType, object? parameter, CultureInfo culture)
    {
        if (value is not string text || string.IsNullOrEmpty(text))
        {
            return value ?? string.Empty;
        }

        text = AcronymWord().Replace(text, "$1 $2");
        text = LowerUpper().Replace(text, "$1 $2");
        return text;
    }

    public object ConvertBack(object? value, Type targetType, object? parameter, CultureInfo culture) => throw new NotSupportedException();
}