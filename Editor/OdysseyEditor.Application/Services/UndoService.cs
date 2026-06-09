using OdysseyEditor.Application.Interfaces;

namespace OdysseyEditor.Application.Services;

public class UndoService(ILogService logService) : IUndoService
{
    public event EventHandler? StackChanged;
    
    private readonly Stack<IUndoableCommand> _undoStack = new();
    private readonly Stack<IUndoableCommand> _redoStack = new();

    public bool CanUndo => _undoStack.Count > 0;
    public bool CanRedo => _redoStack.Count > 0;

    public async Task ExecuteAsync(IUndoableCommand command, CancellationToken ct = default)
    {
        await command.ExecuteAsync(ct);
        _undoStack.Push(command);
        _redoStack.Clear();
        StackChanged?.Invoke(this, EventArgs.Empty);
        logService.LogInfo($"Execute: {command.Description}");
    }

    public async Task UndoAsync(CancellationToken ct = default)
    {
        if (!CanUndo)
        {
            return;
        }

        IUndoableCommand command = _undoStack.Pop();
        await command.UndoAsync(ct);
        _redoStack.Push(command);
        StackChanged?.Invoke(this, EventArgs.Empty);
        logService.LogWarning($"Undo: {command.Description}");
    }

    public async Task RedoAsync(CancellationToken ct = default)
    {
        if (!CanRedo)
        {
            return;
        }

        IUndoableCommand command = _redoStack.Pop();
        await command.ExecuteAsync(ct);
        _undoStack.Push(command);
        StackChanged?.Invoke(this, EventArgs.Empty);
        logService.LogInfo($"Redo: {command.Description}");
    }
}