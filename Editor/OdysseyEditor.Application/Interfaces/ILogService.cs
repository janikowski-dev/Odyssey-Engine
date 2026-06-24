using OdysseyEditor.Application.Models;

namespace OdysseyEditor.Application.Interfaces;

public interface ILogService
{
    event EventHandler<LogEntry> EntryAdded;
    
    void LogInfo(string message);
    void LogError(string message);
    void LogWarning(string message);
}