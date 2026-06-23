namespace OdysseyEditor.Domain.Events;

public static class GetTelemetry
{
    public const string Key = "get_telemetry";
}

public readonly record struct GetTelemetryRequest;

public readonly record struct GetTelemetryResponse(float Fps);
