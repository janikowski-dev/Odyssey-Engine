namespace OdysseyEditor.Domain.Events;

public static class GetViewport
{
    public const string Key = "get_viewport";
}

public readonly record struct GetViewportRequest;

public readonly record struct GetViewportResponse(long Hwnd)
{
    public IntPtr Handle => new(Hwnd);
}