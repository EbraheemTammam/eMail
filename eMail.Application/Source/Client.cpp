#include "Client.h"

namespace eMail::Application
{
    Client::Client(asio::ip::tcp::socket&& socket) :  socket_(std::move(socket))
    {

    }

    Client::~Client()
    {
        Disconnect();
    }

    bool Client::Connect(const std::string& ip, uint16_t port)
    {
        // connection_ = std::make_unique<Connection>();

        asio::ip::tcp::resolver resolver(context_);
        auto endpoints = resolver.resolve(ip, std::to_string(port));

        // connection_->Connect();

        receiveThread_ = std::thread(
            [this](){ context_.run(); }
        );

        return true;
    }

    bool Client::Disconnect()
    {
        if (this->IsConnected()) connection_->Disconnect();

        context_.stop();
        if(receiveThread_.joinable()) receiveThread_.join();

        connection_.release();

        return true;
    }

    bool Client::IsConnected() const
    {
        return connection_ && connection_->IsConnected();
    }

    Queue<smtp_message>& Client::IncomingMessages()
    {
        return receiveQueue_;
    }
}
