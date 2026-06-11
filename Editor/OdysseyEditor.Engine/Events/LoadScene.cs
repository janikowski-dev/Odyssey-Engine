namespace OdysseyEditor.Domain.Events;

public static class LoadScene
{
    public const string Key = "load_scene";
}

public readonly record struct LoadSceneRequest(string Path);

public readonly record struct LoadSceneResponse;
