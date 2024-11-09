#pragma once

#include "PCH.h"

#include <Interfaces/IConnection.h>
using eMail::Core::Interfaces::IConnection;

template<typename MessageType>
using connection_ptr = std::shared_ptr<IConnection<MessageType>>;

namespace eMail::Core::Interfaces { template<typename MessageType> class IServer; }

template<typename MessageType>
class eMail::Core::Interfaces::IServer
{
public:
    virtual ~IServer() = default;

    virtual bool Start() = 0;
    virtual void Stop() = 0;

    virtual void Accept() = 0;
    virtual void Send(connection_ptr<MessageType> remote, const MessageType& message) = 0;
    virtual void Broadcast(const MessageType& message, connection_ptr<MessageType> ignoreClient = nullptr) = 0;

protected:
    virtual bool OnClientConnected(connection_ptr<MessageType> remote) = 0;
    virtual bool OnClientDisconnected(connection_ptr<MessageType> remote) = 0;
    virtual bool OnMessageReceived(connection_ptr<MessageType> remote, const MessageType& message) = 0;
};
