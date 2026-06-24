using OdysseyEditor.Application.Enums;
using OdysseyEditor.Application.Interfaces;
using OdysseyEditor.Application.Models;

namespace OdysseyEditor.Application.Services;

public class LogService : ILogService
{
    public event EventHandler<LogEntry>? EntryAdded;

    public void LogInfo(string message) => Log(message, LogLevel.Info);
    public void LogError(string message) => Log(message, LogLevel.Error);
    public void LogWarning(string message) => Log(message, LogLevel.Warning);

    private void Log(string message, LogLevel level)
    {
        EntryAdded?.Invoke(this, new LogEntry { Message = message, Level = level });
    }
}