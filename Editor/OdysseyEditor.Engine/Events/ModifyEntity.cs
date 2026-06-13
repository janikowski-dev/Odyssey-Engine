namespace OdysseyEditor.Domain.Events;

public static class ModifyEntity
{
    public const string Key = "modify_entity";
}

public readonly record struct ModifyEntityRequest(int Index, Dictionary<string, object> Fields, string Component);

public readonly record struct ModifyEntityResponse;