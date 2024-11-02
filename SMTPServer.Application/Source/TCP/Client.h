#pragma once

#include "PCH.h"

#include <Interfaces/IClient.h>
using SMTPServer::Core::Interfaces::IClient;

#include <Utilities/Queue.h>
using SMTPServer::Core::Utilities::Queue;

#include <Models/SocketMessage.h>
using SMTPServer::Core::Models::SocketMessage;

namespace SMTPServer::Application::TCP { template<typename DataType> class Client; }

template<typename DataType>
class SMTPServer::Application::TCP::Client : public SMTPServer::Core::Interfaces::IClient<DataType>
{
private:
    asio::io_context context_;
    asio::ip::tcp::socket socket_;

    std::thread receiveThread_;
    std::unique_ptr<IConnection<DataType>> connection_;

    Queue<SocketMessage<DataType>> receiveQueue_;

public:
    Client();
    ~Client();

    bool Connect(const std::string& ip, uint16_t port) override;
    bool Disconnect() override;
    bool IsConnected() const override;

    Queue<SocketMessage<DataType>>& IncomingMessages() override;
};
