using System.Windows;
using System.Windows.Input;
using CommunityToolkit.Mvvm.ComponentModel;
using CommunityToolkit.Mvvm.Input;
using OdysseyEditor.UI.ViewModels.Resources;
using OdysseyEditor.UI.ViewModels.Console;
using OdysseyEditor.UI.ViewModels.ControlsBar;
using OdysseyEditor.UI.ViewModels.Hierarchy;
using OdysseyEditor.UI.ViewModels.Inspector;
using OdysseyEditor.UI.ViewModels.Workspace;

namespace OdysseyEditor.UI.ViewModels.Main;

public partial class MainWindowViewModel(
    RotationHandleViewModel rotationHandle,
    FocusWarningViewModel focusWarning,
    ControlsBarViewModel controlsBar,
    HierarchyViewModel hierarchy,
    WorkspaceViewModel workspace,
    InspectorViewModel inspector,
    ConsoleViewModel console,
    ResourcesViewModel resources
) : ObservableObject
{
    public RotationHandleViewModel RotationHandle { get; } = rotationHandle;
    public FocusWarningViewModel FocusWarning { get; } = focusWarning;
    public ControlsBarViewModel ControlsBar { get; } = controlsBar;
    public HierarchyViewModel Hierarchy { get; } = hierarchy;
    public WorkspaceViewModel Workspace { get; } = workspace;
    public InspectorViewModel Inspector { get; } = inspector;
    public ResourcesViewModel Resources { get; } = resources;
    public ConsoleViewModel Console { get; } = console;

    public ICommand FocusEngineCommand => Workspace.FocusEngineCommand;
    public ICommand KeyDownCommand => Workspace.HandleKeyDownCommand;
    public ICommand KeyUpCommand => Workspace.HandleKeyUpCommand;

    [RelayCommand]
    private async Task InitAsync()
    {
        RotationHandle.Init();
        FocusWarning.Init();
        Console.Init();
        await Workspace.InitAsync();
        await Resources.InitAsync();
        await Inspector.InitAsync();
        await Hierarchy.InitAsync();
    }
    
    [RelayCommand]
    private void Minimize(Window? window)
    {
        window?.WindowState = WindowState.Minimized;
    }

    [RelayCommand]
    private void Resize(Window? window)
    {
        window?.WindowState = window.WindowState == WindowState.Maximized ? WindowState.Normal : WindowState.Maximized;
    }

    [RelayCommand]
    private void Close(Window? window)
    {
        window?.Close();
    }
}