namespace OdysseyEditor.Domain.Events;

public static class FocusWindow
{
    public const string Key = "focus_window";
}

public readonly record struct FocusWindowRequest;

public readonly record struct FocusWindowResponse;
