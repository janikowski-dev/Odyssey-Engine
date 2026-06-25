using System.IO;

namespace OdysseyEditor.UI.ViewModels.Resources;

public sealed class ResourceItem(string fullPath)
{
    public string Name { get; } = Path.GetFileName(fullPath.TrimEnd(Path.DirectorySeparatorChar));
    public string FullPath { get; } = fullPath;
}