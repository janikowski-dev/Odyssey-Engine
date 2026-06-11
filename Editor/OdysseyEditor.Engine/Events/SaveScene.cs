namespace OdysseyEditor.Domain.Events;

public static class SaveScene
{
    public const string Key = "save_scene";
}

public readonly record struct SaveSceneRequest(string Path);

public readonly record struct SaveSceneResponse;
