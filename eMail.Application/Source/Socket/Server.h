#pragma once

#include "PCH.h"

#include <Interfaces/IServer.h>
using eMail::Core::Interfaces::IServer;

#include <Interfaces/ILogger.h>
using eMail::Core::Interfaces::ILogger;

#include <Utilities/Queue.h>
using eMail::Core::Utilities::Queue;

#include "Connection.h"
using eMail::Application::Socket::Connection;

namespace eMail::Application::Socket { class Server; }

class eMail::Application::Socket::Server : public IServer<smtp_message>
{
private:
    asio::io_context context_;
    asio::ip::tcp::acceptor acceptor_;

    std::thread acceptThread_;
    std::mutex mutex_;

    Queue<smtp_message> receiveQueue_;
    std::array<std::shared_ptr<Connection>, 100> connectionList_;
    unsigned short connectionCursor_ = 0;

    ILogger& logger_;
    uint32_t idCounter_ = 10000;

    Server(uint16_t port, ILogger& logger);
    Server(const Server&) = delete;
    Server& operator=(const Server&) = delete;

    bool removeGapsFromConnectionList_();

public:
    static Server& getInstance(uint16_t port, ILogger& logger);
    ~Server();

    bool Start() override;
    void Stop() override;

    void Accept() override;
    void Send(connection_ptr<smtp_message> remote, const smtp_message& message) override;
    void Broadcast(const smtp_message& message, connection_ptr<smtp_message> ignoreClient = nullptr) override;

protected:
    bool OnClientConnected(connection_ptr<smtp_message> remote) override;
    bool OnClientDisconnected(connection_ptr<smtp_message> remote) override;
    bool OnMessageReceived(connection_ptr<smtp_message> remote, const smtp_message& message) override;
};
