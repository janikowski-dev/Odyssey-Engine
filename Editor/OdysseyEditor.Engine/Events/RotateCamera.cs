namespace OdysseyEditor.Domain.Events;

public static class RotateCamera
{
    public const string Key = "rotate_camera";
}

public readonly record struct RotateCameraRequest(float XDelta, float YDelta);

public readonly record struct RotateCameraResponse;