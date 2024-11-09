#include "Server.h"

namespace eMail::Application::Socket
{
    using _endpoint = asio::ip::tcp::endpoint;

    Server::Server(uint16_t port, ILogger& logger) :
        acceptor_(context_, _endpoint(asio::ip::make_address("0.0.0.0"), port)),
        logger_(logger)
    {

    }

    Server::~Server()
    {
        Stop();
    }

    Server& Server::getInstance(uint16_t port, ILogger& logger)
    {
        static Server instance(port, logger);
        return instance;
    }

    bool Server::Start()
    {
        try
        {
            Accept();
            acceptThread_ = std::thread(
                [this](){ context_.run(); }
            );
        }
        catch (const std::exception& e)
        {
            logger_.error(e.what());
            return false;
        }
        logger_.infoAsync("Server started on port " + std::to_string(acceptor_.local_endpoint().port()));
        return true;
    }

    void Server::Stop()
    {
        acceptor_.cancel();
        context_.stop();
        if(acceptThread_.joinable()) acceptThread_.join();
        logger_.infoAsync("Server stopped");
    }

    bool Server::removeGapsFromConnectionList_()
    {
        bool gapFound = false;

        for (unsigned short i = 0; i < connectionCursor_; ++i)
        {
            if(connectionList_[i] && connectionList_[i]->IsConnected()) continue;
            gapFound = true;

            connectionList_[i] = connectionList_[connectionCursor_ - 1];
            connectionList_[connectionCursor_] = nullptr;
            --connectionCursor_;
        }

        return gapFound;

#if 0
        int gaps = 0;

        for (unsigned short i = 0; i < connectionCursor_; ++i)
        {
            if (!connectionList_[i]) continue;

            unsigned short j = i - 1;

            while (j >= 0 && connectionList_[j] == nullptr) --j;
            gaps += i - j - 1;

            connectionList_[j] = connectionList_[i];
            connectionList_[i] = nullptr;
        }

        connectionCursor_ -= gaps;

        return gaps > 0;
#endif
    }

    void Server::Accept()
    {
        acceptor_.async_accept(
            [this](const asio::error_code& error, asio::ip::tcp::socket socket)
            {
                if (error)
                {
                    logger_.error("Error accepting connection: " + error.message());
                    return;
                }

                logger_.infoAsync(
                    "Accepted connection from " +
                    socket.remote_endpoint().address().to_string() +
                    ":" +
                    std::to_string(socket.remote_endpoint().port())
                );

                std::shared_ptr<Connection> connection = std::make_shared<Connection>(
                    Connection::owner::server,
                    context_,
                    std::move(socket),
                    receiveQueue_
                );

                if(!OnClientConnected(connection))
                {
                    logger_.infoAsync("Client connection denied");
                    return;
                }

                if((connectionCursor_ == connectionList_.size()) && !removeGapsFromConnectionList_())
                {
                    logger_.infoAsync("Connection list full, rejecting connection");
                    return;
                }

                connectionList_[connectionCursor_] = std::move(connection);
                connectionList_[connectionCursor_]->Connect(idCounter_++);

                logger_.infoAsync("Client connection approved with id: " + std::to_string(connectionList_[connectionCursor_]->GetId()));
                ++connectionCursor_;

                Accept();
            }
        );
    }

    void Server::Send(connection_ptr<smtp_message> remote, const smtp_message& message)
    {
        if (remote && remote->IsConnected())
        {
            remote->Send(message);
            return;
        }

        OnClientDisconnected(remote);
        remote.reset();
    }

    void Server::Broadcast(const smtp_message& message, connection_ptr<smtp_message> ignoreClient)
    {
        bool invalidClientDetected = false;
        for (auto& remote : connectionList_)
        {
            if(remote == ignoreClient) continue;
            if (remote && remote->IsConnected())
            {
                remote->Send(message);
                continue;
            }
            invalidClientDetected = true;
        }
        if (invalidClientDetected) removeGapsFromConnectionList_();
    }

    bool Server::OnClientConnected(connection_ptr<smtp_message> remote)
    {
        return true;
    }

    bool Server::OnClientDisconnected(connection_ptr<smtp_message> remote)
    {
        return true;
    }

    bool Server::OnMessageReceived(connection_ptr<smtp_message> remote, const smtp_message& message)
    {
        // receiveQueue_.Push(message);

        // TODO: Handle message

        return true;
    }
}
