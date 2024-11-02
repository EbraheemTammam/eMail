#include "SocketMessage.h"

namespace SMTPServer::Core::Models
{
    template<typename DataType>
    std::size_t SocketMessage<DataType>::GetPayloadSize_() const
    {
        std::size_t low = 0;
        std::size_t high = BUFFER_SIZE - 1;
        std::size_t index = -1;

        while (low <= high)
        {
            std::size_t mid = (low + high) / 2;
            if ((std::uint8_t)Payload[mid] == 0)
            {
                index = mid;
                high = mid - 1;
                continue;
            }
            else
            {
                low = mid + 1;
                continue;
            }
        }

        return index == -1 ? BUFFER_SIZE : index;
    }

    template<typename DataType>
    size_t SocketMessage<DataType>::Size() const
    {
        return sizeof(Header) + GetPayloadSize_();
    }

    template<typename DataType>
    SocketMessage<DataType>& operator<<(SocketMessage<DataType>& message, const DataType& data)
    {
        static_assert(std::is_standard_layout<DataType>::value, "Data can't be serialized");

        if(sizeof(DataType) + message.GetPayloadSize_() > BUFFER_SIZE)
            throw std::runtime_error("Buffer overflow");

        std::memcpy(message.Payload.data() + message.GetPayloadSize_(), &data, sizeof(DataType));
        message.Header.size += sizeof(DataType);

        return message;
    }

    template<typename DataType>
    SocketMessage<DataType>& operator>>(SocketMessage<DataType>& message, const DataType& data)
    {
        static_assert(std::is_standard_layout<DataType>::value, "Data can't be serialized");

        size_t startingPoint = message.Payload.data() - message.GetPayloadSize_();

        std::memcpy(&data, startingPoint, sizeof(DataType));

        std::memset(startingPoint, 0, sizeof(DataType));
        message.Header.size -= sizeof(DataType);

        return message;
    }

    template<typename DataType>
    std::ostream& operator<<(std::ostream& os, const SocketMessage<DataType>& message)
    {
        os << "Id: " << int(message.Header.id) << " | Size: " << message.Header.size;
        return os;
    }
}
