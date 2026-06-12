#pragma once

#include "Core/Minimal.h"

#include <atomic>
#include <cstdint>
#include <mutex>
#include <queue>
#include <thread>

namespace Source::Editor
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

        bool Listen(std::string Host, uint16 Port);
        bool Send(const std::string& Payload);
        std::vector<std::string> Poll();

    private:
        void AcceptAndRead();
        void ReadLoop();
        bool ReceiveExact(char* Buffer, int Length);
        bool SendExact(const char* Buffer, int Length);
        void Close();

    private:
        SocketHandle ListenSocket = InvalidSocket;
        SocketHandle ClientSocket = InvalidSocket;

        std::atomic<bool> Connected { false };
        std::atomic<bool> Running { false };
        std::thread ReadThread;

        std::queue<std::string> Incoming;
        std::mutex QueueMutex;
    };
}
