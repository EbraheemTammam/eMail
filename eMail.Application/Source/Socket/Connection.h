#pragma once

#include <Interfaces/IConnection.h>
using eMail::Core::Interfaces::IConnection;

#include <Utilities/Queue.h>
using eMail::Core::Utilities::Queue;

#include "SMTPMessageType.h"
using smtp_message = SocketMessage<eMail::Application::Socket::SMTPMessageType>;

namespace eMail::Application::Socket { class Connection; }

class eMail::Application::Socket::Connection : public IConnection<smtp_message>
{
public:
    enum struct owner { server, client };

    Connection(
        owner owner,
        asio::io_context& context,
        asio::ip::tcp::socket&& socket,
        Queue<smtp_message>& receiveQueue
    );
    ~Connection();

    bool Connect(uint32_t id) override;
    bool Disconnect() override;
    bool IsConnected() const override;
    uint32_t GetId() const override;

    bool Send(const smtp_message& message) override;

private:
    asio::ip::tcp::socket socket_;
    asio::io_context& context_;

    owner owner_;
    Queue<smtp_message> sendQueue_;
    Queue<smtp_message>& receiveQueue_;
};
