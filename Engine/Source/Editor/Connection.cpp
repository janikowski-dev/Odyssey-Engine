#include "Connection.h"

#include "../Core/Types.h"

#define WIN32_LEAN_AND_MEAN

#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "Ws2_32.lib")

namespace Source::Editor
{
    namespace
    {
        struct WinsockGuard
        {
            WinsockGuard()  { WSADATA Data; WSAStartup(MAKEWORD(2, 2), &Data); }
            ~WinsockGuard() { WSACleanup(); }
        };

        void EnsureWinsock()
        {
            static WinsockGuard Guard;
        }

        constexpr uint32 MaxMessage = 16u * 1024 * 1024;
    }

    Connection::~Connection() { Close(); }

    bool Connection::Listen(uint16 Port)
    {
        EnsureWinsock();

        SOCKET Sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

        if (Sock == INVALID_SOCKET)
        {
            return false;
        }

        int Yes = 1;
        setsockopt(Sock, SOL_SOCKET, SO_REUSEADDR, (char*)&Yes, sizeof(Yes));

        sockaddr_in Address{};
        Address.sin_family = AF_INET;
        Address.sin_port   = htons(Port);
        inet_pton(AF_INET, "127.0.0.1", &Address.sin_addr);

        if (bind(Sock, (sockaddr*)&Address, sizeof(Address)) == SOCKET_ERROR ||
            listen(Sock, 1) == SOCKET_ERROR)
        {
            closesocket(Sock);
            return false;
        }

        ListenSocket = (SocketHandle)Sock;
        Running = true;
        ReadThread = std::thread(&Connection::AcceptAndRead, this);
        return true;
    }

    void Connection::AcceptAndRead()
    {
        SOCKET Client = accept((SOCKET)ListenSocket, nullptr, nullptr);

        if (Client == INVALID_SOCKET)
        {
            return;
        }

        int Yes = 1;
        setsockopt(Client, IPPROTO_TCP, TCP_NODELAY, (char*)&Yes, sizeof(Yes));

        ClientSocket = (SocketHandle)Client;
        Connected = true;
        ReadLoop();
    }

    bool Connection::ReceiveExact(char* Buffer, int Length)
    {
        int Got = 0;

        while (Got < Length)
        {
            int N = recv((SOCKET)ClientSocket, Buffer + Got, Length - Got, 0);

            if (N <= 0)
            {
                return false;
            }

            Got += N;
        }

        return true;
    }

    bool Connection::SendExact(const char* Buffer, int Length)
    {
        int Sent = 0;

        while (Sent < Length)
        {
            int N = send((SOCKET)ClientSocket, Buffer + Sent, Length - Sent, 0);

            if (N <= 0)
            {
                return false;
            }

            Sent += N;
        }
        return true;
    }

    void Connection::ReadLoop()
    {
        while (Running)
        {
            uint32 NetLength = 0;

            if (!ReceiveExact((char*)&NetLength, 4))
            {
                break;
            }

            uint32 Length = ntohl(NetLength);

            if (Length == 0 || Length > MaxMessage)
            {
                break;
            }

            std::string Payload;
            Payload.resize(Length);

            if (!ReceiveExact(&Payload[0], (int)Length))
            {
                break;
            }

            {
                std::lock_guard<std::mutex> Lock(QueueMutex);
                Incoming.push(std::move(Payload));
            }
        }

        Connected = false;
    }

    std::vector<std::string> Connection::Poll()
    {
        std::vector<std::string> Out;
        std::lock_guard<std::mutex> Lock(QueueMutex);

        while (!Incoming.empty())
        {
            Out.push_back(std::move(Incoming.front()));
            Incoming.pop();
        }

        return Out;
    }

    bool Connection::Send(const std::string& Payload)
    {
        if (!Connected)
        {
            return false;
        }

        uint32 NetLength = htonl((uint32)Payload.size());

        if (!SendExact((char*)&NetLength, 4) || !SendExact(Payload.data(), (int)Payload.size()))
        {
            Connected = false;
            return false;
        }

        return true;
    }

    void Connection::Close()
    {
        Running = false;

        if (ClientSocket != InvalidSocket)
        {
            closesocket((SOCKET)ClientSocket);
            ClientSocket = InvalidSocket;
        }
        
        if (ListenSocket != InvalidSocket)
        {
            closesocket((SOCKET)ListenSocket);
            ListenSocket = InvalidSocket;
        }

        if (ReadThread.joinable())
        {
            ReadThread.join();
        }

        Connected = false;
    }
}
