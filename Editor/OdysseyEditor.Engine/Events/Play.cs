namespace OdysseyEditor.Domain.Events;

public static class Play
{
    public const string Key = "play";
}

public readonly record struct PlayRequest;

public readonly record struct PlayResponse;
