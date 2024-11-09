#pragma once

#include "PCH.h"

namespace eMail::Core::Interfaces { template<typename DataType> class IConnection; }

template<typename MessageType>
class eMail::Core::Interfaces::IConnection : public std::enable_shared_from_this<IConnection<MessageType>>
{
public:
    virtual ~IConnection() = default;

    virtual bool Connect(uint32_t id) = 0;
    virtual bool Disconnect() = 0;
    virtual bool IsConnected() const = 0;
    virtual uint32_t GetId() const = 0;

    virtual bool Send(const MessageType& message) = 0;
};
