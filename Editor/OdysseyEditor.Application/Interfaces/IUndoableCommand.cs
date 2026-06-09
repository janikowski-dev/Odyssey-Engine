namespace OdysseyEditor.Application.Interfaces;

public interface IUndoableCommand
{
    string Description { get; }
    
    Task ExecuteAsync(CancellationToken ct = default);
    Task UndoAsync(CancellationToken ct = default);
}