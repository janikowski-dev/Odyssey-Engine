namespace OdysseyEditor.Domain.Events;

public static class GetSchema
{
    public const string Key = "get_schema";
}

public readonly record struct GetSchemaRequest;

public readonly record struct GetSchemaResponse(object Schema);
