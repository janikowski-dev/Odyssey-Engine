namespace OdysseyEditor.Domain.Events;

public static class CreateEntity
{
    public const string Key = "create_entity";
}

public readonly record struct CreateEntityRequest;

public readonly record struct CreateEntityResponse;