#pragma once

#include "PCH.h"

#include "Utilities/Queue.h"
using eMail::Core::Utilities::Queue;

#include "Models/SocketMessage.h"
using eMail::Core::Models::SocketMessage;

namespace eMail::Core::Interfaces { template<typename DataType> class IClient; }

template<typename DataType>
class eMail::Core::Interfaces::IClient
{
public:
    virtual ~IClient();

    virtual bool Connect(const std::string& ip, uint16_t port) = 0;
    virtual bool Disconnect() = 0;
    virtual bool IsConnected() const = 0;

    virtual Queue<SocketMessage<DataType>>& IncomingMessages() = 0;
};
