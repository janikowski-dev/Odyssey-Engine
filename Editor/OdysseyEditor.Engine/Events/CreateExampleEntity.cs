namespace OdysseyEditor.Domain.Events;

public static class CreateExampleEntity
{
    public const string Key = "create_example_entity";
}

public readonly record struct CreateExampleEntityRequest;

public readonly record struct CreateExampleEntityResponse(int Index);
