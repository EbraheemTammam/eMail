#pragma once

#include "PCH.h"

#include <Interfaces/IServer.h>
using SMTPServer::Core::Interfaces::IServer;

#include <Utilities/Queue.h>
using SMTPServer::Core::Utilities::Queue;

#include <Models/SocketMessage.h>
using SMTPServer::Core::Models::SocketMessage;

#include "SMTP/SMTPMessageType.h"
using SMTPServer::Application::SMTP::SMTPMessageType;

namespace SMTPServer::Application::TCP { class Server; }

class SMTPServer::Application::TCP::Server : public IServer<SMTPMessageType>
{
private:
    asio::io_context context_;
    asio::ip::tcp::acceptor acceptor_;

    std::thread acceptThread_;
    std::mutex mutex_;
    Queue<std::shared_ptr<IConnection<SMTPMessageType>>> connectionQueue_;

    Server();
    Server(const Server&) = delete;
    Server& operator=(const Server&) = delete;

public:
    ~Server();

    bool Start() override;
    bool Stop() override;

    std::future<void> AcceptAsync() override;
    bool Send(std::shared_ptr<IConnection<SMTPMessageType>> remote, const SocketMessage<SMTPMessageType>& message) override;
    bool Broadcast(const SocketMessage<SMTPMessageType>& message, std::vector<std::shared_ptr<IConnection<SMTPMessageType>>> ignoranceList = {}) override;

protected:
    bool OnClientConnected(std::shared_ptr<IConnection<SMTPMessageType>> remote) override;
    bool OnClientDisconnected(std::shared_ptr<IConnection<SMTPMessageType>> remote) override;
    bool OnMessageReceived(std::shared_ptr<IConnection<SMTPMessageType>> remote, const SocketMessage<SMTPMessageType>& message) override;
};
