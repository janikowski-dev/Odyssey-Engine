namespace OdysseyEditor.Application.Interfaces;

public interface IUndoService
{
    event EventHandler StackChanged;
    
    bool CanUndo { get; }
    bool CanRedo { get; }

    Task ExecuteAsync(IUndoableCommand command, CancellationToken ct = default);
    Task UndoAsync(CancellationToken ct = default);
    Task RedoAsync(CancellationToken ct = default);
}