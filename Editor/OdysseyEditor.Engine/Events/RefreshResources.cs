namespace OdysseyEditor.Domain.Events;

public static class RefreshResources
{
    public const string Key = "refresh_resources";
}

public readonly record struct RefreshResourcesRequest;

public readonly record struct RefreshResourcesResponse;
