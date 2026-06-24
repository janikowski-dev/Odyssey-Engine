namespace OdysseyEditor.Domain.Events;

public readonly record struct DestroyedEntity(int Index)
{
    public const string Key = "destroyed_entity";
}
