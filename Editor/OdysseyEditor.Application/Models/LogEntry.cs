using OdysseyEditor.Application.Enums;

namespace OdysseyEditor.Application.Models;

public record LogEntry
{
    private readonly DateTime _timestamp = DateTime.Now;
    
    public string Message { get; init; } = string.Empty;
    public LogLevel Level { get; init; }
    
    public string FormattedTimestamp => _timestamp.ToString("HH:mm:ss");
}