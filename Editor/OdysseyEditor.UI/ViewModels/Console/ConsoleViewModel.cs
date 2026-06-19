using System.Collections.ObjectModel;
using System.Collections.Specialized;
using System.Globalization;
using CommunityToolkit.Mvvm.ComponentModel;
using CommunityToolkit.Mvvm.Input;
using OdysseyEditor.Application.Interfaces;
using OdysseyEditor.Application.Models;
using OdysseyEditor.Domain.Events;
using OdysseyEditor.Domain.Interfaces;

namespace OdysseyEditor.UI.ViewModels.Console;

public partial class ConsoleViewModel(ILogService logService, IEngineMessenger engineMessenger) : ObservableObject
{
    [ObservableProperty]
    [NotifyPropertyChangedFor(nameof(HeaderText))]
    public partial bool IsExpanded { get; set; }
    
    public ObservableCollection<LogEntry> Messages { get; } = [];

    public string HeaderText
    {
        get
        {
            if (IsExpanded)
            {
                return DefaultHeader;
            }

            return Messages.Count > 0 ? Messages[^1].Message : string.Empty;
        }
    }

    private const string DefaultHeader = "Console";

    public void Init()
    {
        InitCollections();
        InitServices();
    }

    private void UpdateHeader(object? sender, NotifyCollectionChangedEventArgs e)
    {
        OnPropertyChanged(nameof(HeaderText));
    }

    [RelayCommand]
    private void Toggle() => IsExpanded = !IsExpanded;

    private void AddMessage(object? sender, LogEntry entry)
    {
        Messages.Add(entry);
    }

    private void InitCollections()
    {
        Messages.CollectionChanged += UpdateHeader;
    }

    private void InitServices()
    {
        logService.EntryAdded += AddMessage;
    }
}