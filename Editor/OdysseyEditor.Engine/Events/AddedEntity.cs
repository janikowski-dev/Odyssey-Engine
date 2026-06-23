namespace OdysseyEditor.Domain.Events;

public readonly record struct AddedEntity(int Index)
{
    public const string Key = "added_entity";
}
