namespace OdysseyEditor.Domain.Data;

public sealed class EngineConfig
{
    public string ProjectRoot { get; set; } = "";
    public string Host { get; set; } = "";
    public int Port { get; set; }
}