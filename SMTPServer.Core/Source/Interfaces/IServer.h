#pragma once

#include "PCH.h"

#include <Interfaces/IConnection.h>
using SMTPServer::Core::Interfaces::IConnection;

#include <Models/SocketMessage.h>
using SMTPServer::Core::Models::SocketMessage;

namespace SMTPServer::Core::Interfaces { template<typename DataType> class IServer; }

template<typename DataType>
class SMTPServer::Core::Interfaces::IServer
{
public:
    virtual ~IServer() = default;

    virtual bool Start() = 0;
    virtual bool Stop() = 0;

    virtual std::future<void> AcceptAsync() = 0;
    virtual bool Send(std::shared_ptr<IConnection<DataType>> remote, const SocketMessage<DataType>& message) = 0;
    virtual bool Broadcast(const SocketMessage<DataType>& message, std::vector<std::shared_ptr<IConnection<DataType>>> ignoranceList = {}) = 0;

protected:
    virtual bool OnClientConnected(std::shared_ptr<IConnection<DataType>> remote) = 0;
    virtual bool OnClientDisconnected(std::shared_ptr<IConnection<DataType>> remote) = 0;
    virtual bool OnMessageReceived(std::shared_ptr<IConnection<DataType>> remote, const SocketMessage<DataType>& message) = 0;
};
