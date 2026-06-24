namespace OdysseyEditor.Domain.Events;

public static class RemoveComponent
{
    public const string Key = "remove_component";
}

public readonly record struct RemoveComponentRequest(int Index, string Component);

public readonly record struct RemoveComponentResponse;
