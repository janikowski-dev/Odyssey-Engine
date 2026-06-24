using CommunityToolkit.Mvvm.ComponentModel;
using CommunityToolkit.Mvvm.Input;
using OdysseyEditor.UI.ViewModels.Console;
using OdysseyEditor.UI.ViewModels.ControlsBar;
using OdysseyEditor.UI.ViewModels.Hierarchy;
using OdysseyEditor.UI.ViewModels.Inspector;
using OdysseyEditor.UI.ViewModels.Workspace;

namespace OdysseyEditor.UI.ViewModels.Main;

public partial class MainWindowViewModel(
    ControlsBarViewModel controlsBar,
    HierarchyViewModel hierarchy,
    WorkspaceViewModel workspace,
    InspectorViewModel inspector,
    ConsoleViewModel console
) : ObservableObject
{
    public ControlsBarViewModel ControlsBar { get; } = controlsBar;
    public HierarchyViewModel Hierarchy { get; } = hierarchy;
    public WorkspaceViewModel Workspace { get; } = workspace;
    public InspectorViewModel Inspector { get; } = inspector;
    public ConsoleViewModel Console { get; } = console;

    [RelayCommand]
    private async Task InitAsync()
    {
        Console.Init();
        await Workspace.InitAsync();
        await Inspector.InitAsync();
        await Hierarchy.InitAsync();
    }
}