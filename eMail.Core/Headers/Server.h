#pragma once

#include "PCH.h"

#include "Logger.h"
using eMail::Core::Logger;

#include "Queue.h"
using eMail::Core::Queue;

#include "Connection.h"
using eMail::Core::Connection;
using connection_ptr = std::shared_ptr<eMail::Core::Connection>;

namespace eMail::Core { class Server; }

class eMail::Core::Server
{
private:
    asio::io_context context_;
    asio::ip::tcp::acceptor acceptor_;

    std::thread acceptThread_;
    std::mutex mutex_;

    Queue<smtp_message> receiveQueue_;
    std::array<std::shared_ptr<Connection>, 100> connectionList_;
    unsigned short connectionCursor_ = 0;

    Logger& logger_;
    uint32_t idCounter_ = 10000;

    Server(uint16_t port);
    Server(const Server&) = delete;
    Server& operator=(const Server&) = delete;

    bool removeGapsFromConnectionList_();

public:
    static Server& getInstance(uint16_t port);
    ~Server();

    bool Start();
    void Stop();

    void Accept();
    void Send(connection_ptr remote, const smtp_message& message);
    void Broadcast(const smtp_message& message, connection_ptr ignoreClient = nullptr);

protected:
    bool OnClientConnected(connection_ptr remote);
    bool OnClientDisconnected(connection_ptr remote);
    bool OnMessageReceived(connection_ptr remote, const smtp_message& message);
};
