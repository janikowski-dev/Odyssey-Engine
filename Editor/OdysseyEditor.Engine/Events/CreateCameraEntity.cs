namespace OdysseyEditor.Domain.Events;

public static class CreateCameraEntity
{
    public const string Key = "create_camera_entity";
}

public readonly record struct CreateCameraEntityRequest;

public readonly record struct CreateCameraEntityResponse(int Index);
