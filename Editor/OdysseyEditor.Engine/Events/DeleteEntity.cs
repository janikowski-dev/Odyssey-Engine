namespace OdysseyEditor.Domain.Events;

public static class DestroyEntity
{
    public const string Key = "destroy_entity";
}

public readonly record struct DestroyEntityRequest(int Index);

public readonly record struct DestroyEntityResponse;
