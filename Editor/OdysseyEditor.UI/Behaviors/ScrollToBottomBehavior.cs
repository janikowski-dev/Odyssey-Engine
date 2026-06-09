using System.Collections.Specialized;
using System.ComponentModel;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;
using System.Windows.Threading;
using Microsoft.Xaml.Behaviors;

namespace OdysseyEditor.UI.Behaviors;

public class ScrollToBottomBehavior : Behavior<ListBox>
{
    private INotifyCollectionChanged? _collection;
    private ScrollViewer? _scrollViewer;

    protected override void OnAttached()
    {
        base.OnAttached();
        
        DependencyPropertyDescriptor
            .FromProperty(ItemsControl.ItemsSourceProperty, typeof(ListBox))
            .AddValueChanged(AssociatedObject, HandleValueChange);

        Subscribe(AssociatedObject.ItemsSource as INotifyCollectionChanged);
    }

    protected override void OnDetaching()
    {
        base.OnDetaching();
        
        DependencyPropertyDescriptor
            .FromProperty(ItemsControl.ItemsSourceProperty, typeof(ListBox))
            .RemoveValueChanged(AssociatedObject, HandleValueChange);

        Unsubscribe();
    }

    private void TryScrollingDown(object? sender, NotifyCollectionChangedEventArgs e)
    {
        if (!AddedToCollection(e))
        {
            return;
        }

        if (!HasScrollViewer() && !TryCacheScrollViewer(FindScrollViewer(AssociatedObject)))
        {
            return;
        }

        ScrollDown();
    }

    private void HandleValueChange(object? sender, EventArgs e)
    {
        Unsubscribe();
        Subscribe(AssociatedObject.ItemsSource as INotifyCollectionChanged);
    }

    private void Subscribe(INotifyCollectionChanged? collection)
    {
        _collection = collection;

        if (_collection is not null)
        {
            _collection.CollectionChanged += TryScrollingDown;
        }
    }

    private void Unsubscribe()
    {
        if (_collection is not null)
        {
            _collection.CollectionChanged -= TryScrollingDown;
        }
        
        _collection = null;
    }

    private static bool AddedToCollection(NotifyCollectionChangedEventArgs e) => e.Action == NotifyCollectionChangedAction.Add;
    
    private bool HasScrollViewer() => _scrollViewer is not null;

    private bool TryCacheScrollViewer(ScrollViewer? scrollViewer)
    {
        _scrollViewer = scrollViewer;
        return _scrollViewer is not null;
    }

    private static ScrollViewer? FindScrollViewer(DependencyObject dependency)
    {
        for (int i = 0; i < VisualTreeHelper.GetChildrenCount(dependency); i++)
        {
            DependencyObject child = VisualTreeHelper.GetChild(dependency, i);
            
            if (child is ScrollViewer scrollViewer)
            {
                return scrollViewer;
            }
            
            ScrollViewer? result = FindScrollViewer(child);
            
            if (result is not null)
            {
                return result;
            }
        }
        
        return null;
    }

    private void ScrollDown()
    {
        bool wasAtBottom = _scrollViewer!.VerticalOffset >= _scrollViewer.ScrollableHeight - 1;

        AssociatedObject.Dispatcher.InvokeAsync(() =>
        {
            if (wasAtBottom)
            {
                _scrollViewer!.ScrollToBottom();
            }
        }, DispatcherPriority.Loaded);
    }
}