#include "Client.h"

namespace SMTPServer::Application::TCP
{
    template<typename DataType>
    Client<DataType>::Client()
    {

    }

    template<typename DataType>
    Client<DataType>::~Client()
    {
        Disconnect();
    }

    template<typename DataType>
    bool Client<DataType>::Connect(const std::string& ip, uint16_t port)
    {
        connection_ = std::make_unique<IConnection<DataType>>();

        asio::ip::tcp::resolver resolver(context_);
        auto endpoints = resolver.resolve(ip, std::to_string(port));

        connection_->Connect();

        receiveThread_ = std::thread(
            [this](){ context_.run(); }
        );

        return true;
    }

    template<typename DataType>
    bool Client<DataType>::Disconnect()
    {
        if (this->IsConnected()) connection_->Disconnect();

        context_.stop();
        if(receiveThread_.joinable()) receiveThread_.join();

        connection_.release();

        return true;
    }
}
