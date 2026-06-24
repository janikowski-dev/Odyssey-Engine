namespace OdysseyEditor.Domain.Events;

public readonly record struct CreatedEntity(int Index)
{
    public const string Key = "created_entity";
}
