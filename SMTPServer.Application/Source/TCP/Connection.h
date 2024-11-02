#pragma once

#include <Interfaces/IConnection.h>
using SMTPServer::Core::Interfaces::IConnection;

#include <Utilities/Queue.h>
using SMTPServer::Core::Utilities::Queue;

#include <Models/SocketMessage.h>
using SMTPServer::Core::Models::SocketMessage;

#include "SMTPMessageType.h"
using SMTPServer::Application::TCP::SMTPMessageType;

namespace SMTPServer::Application::TCP { class Connection; }

class SMTPServer::Application::TCP::Connection : public IConnection<SocketMessage<SMTPMessageType>>
{
private:
    asio::ip::tcp::socket socket_;
    asio::io_context& context_;

    Queue<SocketMessage<SMTPMessageType>> sendQueue_;
    Queue<SocketMessage<SMTPMessageType>>& receiveQueue_;

public:
    Connection();
    virtual ~Connection();

    bool Connect() override;
    bool Disconnect() override;
    bool IsConnected() const override;

    bool Send(const SocketMessage<SMTPMessageType>& message) override;
};
