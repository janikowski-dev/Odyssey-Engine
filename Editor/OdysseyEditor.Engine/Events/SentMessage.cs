namespace OdysseyEditor.Domain.Events;

public readonly record struct SentMessage(string Content)
{
    public const string Key = "sent_message";
}
