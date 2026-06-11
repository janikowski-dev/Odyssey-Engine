namespace OdysseyEditor.Domain.Interfaces;

public interface IEngineMessenger
{
    Task<TResponse> Send<TRequest, TResponse>(string method, TRequest request);
    void On<TEvent>(string method, Action<TEvent> callback);
}