#include "SocketManager.h"

namespace SMTPServer::Application::TCP
{
    SocketManager::SocketManager(ILogger& logger, short&& port) :
        _logger(logger),
        _port(port),
        _acceptor(_io_context, asio::ip::tcp::endpoint(asio::ip::make_address("0.0.0.0"), port)),
        _socket(_io_context)
    {

    }

    SocketManager& SocketManager::GetInstance(ILogger& logger, short&& port)
    {
        static SocketManager instance(logger, (short&&)port);
        return instance;
    }

    void SocketManager::_read()
    {
        _socket.async_read_some(
            asio::buffer(_bufferRecieve.data(), _bufferRecieve.size()),
            [this](const asio::error_code& error, size_t bytesTransferred)
            {
                if (error)
                {
                    _logger.error("Error reading data from socket: " + error.message());
                    return;
                }
                if (bytesTransferred > 0)
                    _logger.infoAsync("Remote: " + std::string(_bufferRecieve.data(), bytesTransferred));
                std::memset(_bufferRecieve.data(), 0, BUFFER_SIZE);
                _readAsync();
            }
        );
    }

    std::future<void> SocketManager::_readAsync()
    {
        std::lock_guard<std::mutex> lock(_mutex);
        return std::async(std::launch::async, &SocketManager::_read, this);
    }

    size_t BinarySearchBuffer(const std::array<char, BUFFER_SIZE>& buffer)
    {
        int low = 0;
        int high = (BUFFER_SIZE) - 1;
        size_t index = -1;

        while (low <= high)
        {
            int mid = (low + high) / 2;
            if ((size_t)buffer[mid] == 0)
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

        return index == -1 ? (BUFFER_SIZE) : index;
    }

    void SocketManager::_write()
    {
        std::cout << "You: ";
        std::cin.getline(_bufferSend.data(), _bufferSend.size());
        _socket.async_write_some(
            asio::buffer(_bufferSend.data(), _bufferSend.size()),
            [this](const asio::error_code& error, std::size_t bytesTransferred)
            {
                if (error)
                {
                    _logger.error("Error writing data to socket: " + error.message());
                    return;
                }
                if (bytesTransferred > 0)
                    _logger.infoAsync("Local: " + std::string(_bufferSend.data(), BinarySearchBuffer(_bufferSend)));
                std::memset(_bufferSend.data(), 0, BUFFER_SIZE);
                _writeAsync();
            }
        );
    }

    std::future<void> SocketManager::_writeAsync()
    {
        std::lock_guard<std::mutex> lock(_mutex);
        return std::async(std::launch::async, &SocketManager::_write, this);
    }

    bool SocketManager::Accept()
    {
        if (_isAccepting)
            return false;

        _isAccepting = true;

        _acceptor.async_accept(
            _socket,
            [this](const asio::error_code& error)
            {
                _logger.info(
                    "Accepted connection from " +
                    _socket.remote_endpoint().address().to_string() +
                    ":" +
                    std::to_string(_socket.remote_endpoint().port())
                );
                if (error)
                {
                    _isAccepting = false;
                    return;
                }
                _isAccepting = true;

                _readAsync();
                _writeAsync();
            }
        );

        _io_context.run();

        return true;
    }

    bool SocketManager::IsAccepting() const
    {
        return _isAccepting;
    }

    bool SocketManager::Shutdown()
    {
        _acceptor.cancel();
        _isShutdown = true;
        return true;
    }
}
