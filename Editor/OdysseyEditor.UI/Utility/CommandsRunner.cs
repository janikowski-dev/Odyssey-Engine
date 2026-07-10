using System.Diagnostics;
using System.IO;
using Microsoft.Win32;

namespace OdysseyEditor.UI.Utility;

public static class CommandsRunner
{
    public static void Package(string projectRoot)
    {
        OpenFolderDialog dialog = new()
        {
            Title = "Select Output Directory",
            Multiselect = false
        };

        if (dialog.ShowDialog() != true)
        {
            return;
        }
        
        ProcessStartInfo psi = new()
        {
            WorkingDirectory = Path.GetFullPath(Path.Combine(AppContext.BaseDirectory, "..", "..")),
            UseShellExecute = false,
            FileName = "cmd.exe"
        };
        psi.ArgumentList.Add("/c");
        psi.ArgumentList.Add("just");
        psi.ArgumentList.Add("build-and-pack");
        psi.ArgumentList.Add(projectRoot);
        psi.ArgumentList.Add(dialog.FolderName);
        psi.ArgumentList.Add("&");
        psi.ArgumentList.Add("pause");

        using Process? process = Process.Start(psi);
        process?.WaitForExit();
    }
    
    public static void KillEngine()
    {
        string processName = Path.GetFileNameWithoutExtension("Launcher.exe");
    
        foreach (Process process in Process.GetProcessesByName(processName))
        {
            process.Kill();
            process.WaitForExit();
            process.Dispose();
        }
    }
    
    public static void Rebuild(string projectRoot)
    {
        ProcessStartInfo psi = new()
        {
            WorkingDirectory = Path.GetFullPath(Path.Combine(AppContext.BaseDirectory, "..", "..")),
            UseShellExecute = false,
            FileName = "cmd.exe"
        };
        psi.ArgumentList.Add("/c");
        psi.ArgumentList.Add("just");
        psi.ArgumentList.Add("build-project");
        psi.ArgumentList.Add(projectRoot);
        psi.ArgumentList.Add("&");
        psi.ArgumentList.Add("pause");

        using Process? process = Process.Start(psi);
        process?.WaitForExit();
    }

    public static void Restart()
    {
        ProcessStartInfo psi = new()
        {
            FileName = Environment.ProcessPath,
            UseShellExecute = false
        };
        
        foreach (string arg in Environment.GetCommandLineArgs().Skip(1))
        {
            psi.ArgumentList.Add(arg);
        }

        Process.Start(psi);
        System.Windows.Application.Current.Shutdown();
    }
}