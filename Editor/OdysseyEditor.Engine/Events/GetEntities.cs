namespace OdysseyEditor.Domain.Events;

public static class GetEntities
{
    public const string Key = "get_entities";
}

public readonly record struct GetEntitiesRequest;

public readonly record struct GetEntitiesResponse(IReadOnlyList<int> Indexes);
