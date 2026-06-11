namespace OdysseyEditor.Domain.Events;

public static class Viewport
{
    public const string Key = "get_viewport";
}

public readonly record struct ViewportRequest;

public readonly record struct ViewportResponse(long Hwnd)
{
    public IntPtr Handle => new(Hwnd);
}