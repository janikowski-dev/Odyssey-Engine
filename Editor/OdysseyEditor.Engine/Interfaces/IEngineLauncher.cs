namespace OdysseyEditor.Domain.Interfaces;

public interface IEngineLauncher
{
    Task LaunchAsync(Func<Task> relaunch);
}