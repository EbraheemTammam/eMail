#pragma once

#include "PCH.h"

#include "Utilities/Queue.h"
using SMTPServer::Core::Utilities::Queue;

#include "Models/SocketMessage.h"
using SMTPServer::Core::Models::SocketMessage;

namespace SMTPServer::Core::Interfaces { template<typename DataType> class IClient; }

template<typename DataType>
class SMTPServer::Core::Interfaces::IClient
{
public:
    virtual ~IClient();

    virtual bool Connect(const std::string& ip, uint16_t port) = 0;
    virtual bool Disconnect() = 0;
    virtual bool IsConnected() const = 0;

    virtual Queue<SocketMessage<DataType>>& IncomingMessages() = 0;
};
