#pragma once

#include <atomic>
#include <cstdint>
#include <mutex>
#include <queue>
#include <string>
#include <thread>
#include <vector>

namespace Core::Editor
{
    class Connection
    {
    public:
        using SocketHandle = std::uintptr_t;
        static constexpr SocketHandle InvalidSocket = static_cast<SocketHandle>(-1);

        Connection() = default;
        ~Connection();

        Connection(const Connection&) = delete;
        Connection& operator=(const Connection&) = delete;

        bool Listen(std::uint16_t Port);

        std::vector<std::string> Poll();

        bool Send(const std::string& Payload);

        bool IsConnected() const { return Connected.load(); }

        void Close();

    private:
        void AcceptAndRead();
        void ReadLoop();
        bool ReceiveExact(char* Buffer, int Length);
        bool SendExact(const char* Buffer, int Length);

    private:
        SocketHandle ListenSocket = InvalidSocket;
        SocketHandle ClientSocket = InvalidSocket;

        std::atomic<bool> Connected{ false };
        std::atomic<bool> Running{ false };
        std::thread ReadThread;

        std::queue<std::string> Incoming;
        std::mutex QueueMutex;
    };
}
