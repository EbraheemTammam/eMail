#include "Connection.h"

namespace eMail::Core
{
    Connection::Connection(
        owner owner,
        asio::io_context& context,
        asio::ip::tcp::socket&& socket,
        Queue<smtp_message>& receiveQueue
    ) :
        owner_(owner),
        socket_(std::move(socket)),
        context_(context),
        receiveQueue_(receiveQueue)
    {

    }

    Connection::~Connection()
    {
        Disconnect();
    }

    bool Connection::Connect(uint32_t id)
    {
        return true;
    }

    bool Connection::Disconnect()
    {
        return true;
    }

    bool Connection::IsConnected() const
    {
        return socket_.is_open();
    }

    uint32_t Connection::GetId() const
    {
        return 0;
    }

    bool Connection::Send(const smtp_message& message)
    {
        return true;
    }
}
