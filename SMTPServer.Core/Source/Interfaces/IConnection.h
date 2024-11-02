#pragma once

#include "PCH.h"

namespace SMTPServer::Core::Interfaces { template<typename DataType> class IConnection; }

template<typename MessageType>
class SMTPServer::Core::Interfaces::IConnection : public std::enable_shared_from_this<IConnection<MessageType>>
{
public:
    virtual ~IConnection();

    virtual bool Connect();
    virtual bool Disconnect();
    virtual bool IsConnected() const;

    virtual bool Send(const MessageType& message);
};
