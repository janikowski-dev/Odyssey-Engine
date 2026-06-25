using System.Collections.ObjectModel;
using System.Diagnostics;
using System.IO;
using CommunityToolkit.Mvvm.ComponentModel;
using CommunityToolkit.Mvvm.Input;
using Microsoft.Extensions.Options;
using OdysseyEditor.Domain.Data;
using OdysseyEditor.Domain.Events;
using OdysseyEditor.Domain.Interfaces;

namespace OdysseyEditor.UI.ViewModels.Resources;

public partial class ResourcesViewModel(IOptions<EngineConfig> config, IEngineMessenger engineMessenger) : ObservableObject
{
    [ObservableProperty]
    public partial ResourceItem? SelectedItem { get; set; }

    public ObservableCollection<ResourceItem> Items { get; } = [];

    private string ResourcesPath => Path.Combine(config.Value.ProjectRoot, "Resources");

    public void Init()
    {
        GetAllFiles();
    }

    [RelayCommand]
    private async Task DropFilesAsync(string[] paths)
    {
        AddFiles(paths);
        await RefreshResources();
    }

    [RelayCommand]
    private async Task DeleteAsync(ResourceItem item)
    {
        DeleteFile(item);
        await RefreshResources();
    }

    [RelayCommand]
    private void Explore(ResourceItem item)
    {
        if (!File.Exists(item.FullPath))
        {
            return;
        }

        string path = Path.GetFullPath(item.FullPath).Replace('/', '\\');

        Process.Start(new ProcessStartInfo
        {
            Arguments = $"/select,\"{path}\"",
            FileName = "explorer.exe",
            UseShellExecute = true
        });
    }

    [RelayCommand]
    private void GetAllFiles()
    {
        Items.Clear();

        foreach (string fullPath in Directory.EnumerateFiles(ResourcesPath).OrderBy(p => p))
        {
            Items.Add(new ResourceItem(fullPath));
        }
    }

    private void AddFiles(string[] paths)
    {
        foreach (string source in paths)
        {
            if (!File.Exists(source))
            {
                continue;
            }

            string name = Path.GetFileNameWithoutExtension(source);
            string extension = Path.GetExtension(source);
            string destination = Path.Combine(ResourcesPath, name + extension);

            int counter = 1;
        
            while (File.Exists(destination))
            {
                destination = Path.Combine(ResourcesPath, $"{name} ({counter}){extension}");
                counter++;
            }

            try
            {
                File.Copy(source, destination);
            }
            catch (IOException)
            {
                continue;
            }

            Items.Add(new ResourceItem(destination));
        }
    }

    private void DeleteFile(ResourceItem item)
    {
        try
        {
            if (File.Exists(item.FullPath))
            {
                File.Delete(item.FullPath);
            }
        }
        catch (IOException)
        {
            return;
        }

        Items.Remove(item);
    }

    private async Task RefreshResources()
    {
        await engineMessenger.Send<RefreshResourcesRequest, RefreshResourcesResponse>(Domain.Events.RefreshResources.Key, new RefreshResourcesRequest());
    }
}