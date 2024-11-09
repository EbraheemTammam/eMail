#pragma once

#include "PCH.h"

#include "Queue.h"
using eMail::Core::Queue;

#include "TypeSMTPMessage.h"
using smtp_message = SocketMessage<eMail::Core::TypeSMTPMessage>;

namespace eMail::Core { class Connection; }

class eMail::Core::Connection : public std::enable_shared_from_this<Connection>
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

    bool Connect(uint32_t id);
    bool Disconnect();
    bool IsConnected() const;
    uint32_t GetId() const;

    bool Send(const smtp_message& message);

private:
    asio::ip::tcp::socket socket_;
    asio::io_context& context_;

    owner owner_;
    Queue<smtp_message> sendQueue_;
    Queue<smtp_message>& receiveQueue_;
};
