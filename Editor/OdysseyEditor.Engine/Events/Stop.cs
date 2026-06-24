namespace OdysseyEditor.Domain.Events;

public static class Stop
{
    public const string Key = "stop";
}

public readonly record struct StopRequest;

public readonly record struct StopResponse;
