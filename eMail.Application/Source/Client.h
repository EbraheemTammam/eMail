#pragma once

#include "PCH.h"

#include <Queue.h>
using eMail::Core::Queue;

#include "TypeSMTPMessage.h"
using smtp_message = SocketMessage<eMail::Core::TypeSMTPMessage>;

#include <Connection.h>
using eMail::Core::Connection;

namespace eMail::Application { class Client; }

class eMail::Application::Client
{
private:
    asio::io_context context_;
    asio::ip::tcp::socket socket_;

    std::thread receiveThread_;
    std::unique_ptr<Connection> connection_;

    Queue<smtp_message> receiveQueue_;

public:
    Client(asio::ip::tcp::socket&& socket);
    ~Client();

    bool Connect(const std::string& ip, uint16_t port);
    bool Disconnect();
    bool IsConnected() const;

    Queue<smtp_message>& IncomingMessages();
};
