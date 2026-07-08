namespace OdysseyEditor.Domain.Events;

public static class MoveCamera
{
    public const string Key = "move_camera";
}

public readonly record struct MoveCameraRequest(MoveDirection Direction, bool Move);

public readonly record struct MoveCameraResponse;

public enum MoveDirection
{
    None = 0,
    Up = 1 << 0,
    Down = 1 << 1,
    Left = 1 << 2,
    Right = 1 << 3,
    Forward = 1 << 4,
    Back = 1 << 5
}