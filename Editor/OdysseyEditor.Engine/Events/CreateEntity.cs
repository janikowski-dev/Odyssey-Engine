using System.Text.Json;

namespace OdysseyEditor.Domain.Events;

public static class CreateEntity
{
    public const string Key = "create_entity";
}

public readonly record struct CreateEntityRequest;

public readonly record struct CreateEntityResponse(int Index, IReadOnlyList<ComponentData> Info);

public readonly record struct ComponentData(string Type, IReadOnlyDictionary<string, JsonElement> Fields);
