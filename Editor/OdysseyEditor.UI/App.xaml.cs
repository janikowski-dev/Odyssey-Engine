using System.Windows;
using CommunityToolkit.Mvvm.Messaging;
using Microsoft.Extensions.DependencyInjection;
using Microsoft.Extensions.Hosting;
using OdysseyEditor.Application.Interfaces;
using OdysseyEditor.Application.Services;
using OdysseyEditor.UI.ViewModels.Console;
using OdysseyEditor.UI.ViewModels.ControlsBar;
using OdysseyEditor.UI.ViewModels.Hierarchy;
using OdysseyEditor.UI.ViewModels.Inspector;
using OdysseyEditor.UI.ViewModels.Main;
using OdysseyEditor.UI.ViewModels.Workspace;
using OdysseyEditor.UI.Views;

namespace OdysseyEditor.UI;

public partial class App
{
    private IHost _host = null!;

    protected override void OnStartup(StartupEventArgs eventArgs)
    {
        base.OnStartup(eventArgs);

        Start(Host.CreateDefaultBuilder()
            .ConfigureServices((context, services) =>
            {
                ConfigureApplication(services);
                ConfigureViews(services);
            })
            .Build()
        );

        OpenWindow();
    }

    // ReSharper disable once AsyncVoidEventHandlerMethod
    protected override async void OnExit(ExitEventArgs eventArgs)
    {
        await Stop();
        base.OnExit(eventArgs);
    }

    private static void ConfigureApplication(IServiceCollection services)
    {
        services.AddSingleton<IUndoService, UndoService>();
        services.AddSingleton<ILogService, LogService>();
    }

    private static void ConfigureViews(IServiceCollection services)
    {
        services.AddSingleton<IMessenger>(WeakReferenceMessenger.Default);
        services.AddSingleton<ControlsBarViewModel>();
        services.AddSingleton<HierarchyViewModel>();
        services.AddSingleton<InspectorViewModel>();
        services.AddSingleton<WorkspaceViewModel>();
        services.AddSingleton<ConsoleViewModel>();
        services.AddSingleton<MainWindowViewModel>();
    }

    private void OpenWindow()
    {
        MainWindow mainWindow = new()
        {
            DataContext = _host.Services.GetRequiredService<MainWindowViewModel>()
        };
        
        mainWindow.Show();
    }

    private void Start(IHost host)
    {
        _host = host;
        _host.Start();
    }

    private async Task Stop()
    {
        await _host.StopAsync();
        _host.Dispose();
    }
}