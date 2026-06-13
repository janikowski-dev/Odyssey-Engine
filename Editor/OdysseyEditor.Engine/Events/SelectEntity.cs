using System.Text.Json;

namespace OdysseyEditor.Domain.Events;

public static class SelectEntity
{
    public const string Key = "select_entity";
}

public readonly record struct SelectEntityRequest(int Index);

public readonly record struct SelectEntityResponse(IReadOnlyList<ComponentData> Data);

public readonly record struct ComponentData(string Name, IReadOnlyDictionary<string, JsonElement> Fields);
