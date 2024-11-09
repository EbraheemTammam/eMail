#pragma once

#include "PCH.h"

namespace eMail::Core { template<typename T> class SocketMessage; }

template<typename DataType>
class eMail::Core::SocketMessage
{
private:
    struct MessageHeader
    {
        DataType id{};
        uint32_t size{};
    };

    std::size_t GetPayloadSize_() const;

public:
    MessageHeader Header{};
    std::array<uint8_t, BUFFER_SIZE> Payload{};

    std::size_t Size() const;

    template<typename FriendDataType>
    friend SocketMessage& operator<<(SocketMessage& message, const FriendDataType& data);

    template<typename FriendDataType>
    friend SocketMessage& operator>>(SocketMessage& message, const FriendDataType& data);

    template<typename FriendDataType>
    friend std::ostream& operator<<(std::ostream& os, const SocketMessage& message);
};
