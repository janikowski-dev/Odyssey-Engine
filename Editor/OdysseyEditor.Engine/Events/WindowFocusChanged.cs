namespace OdysseyEditor.Domain.Events;

public readonly record struct WindowFocusChanged(bool IsFocused)
{
    public const string Key = "window_focus_changed";
}
