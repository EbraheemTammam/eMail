# pragma once

#include "PCH.h"

#include <Logger.h>
using eMail::Core::Logger;

namespace eMail::Application { class SocketManager; }

class eMail::Application::SocketManager
{
public:
    static SocketManager& GetInstance(Logger&, short&& port = 25);
    bool Shutdown();
    bool Accept();
    bool IsAccepting() const;

private:
    std::array<char, BUFFER_SIZE> _bufferSend;
    std::array<char, BUFFER_SIZE> _bufferRecieve;
    short _port;

    asio::io_context _io_context;
    asio::ip::tcp::acceptor _acceptor;
    asio::ip::tcp::socket _socket;

    bool _isShutdown = false;
    bool _isAccepting = false;

    Logger& _logger;
    mutable std::mutex _mutex;

    void _read();
    void _write();
    std::future<void> _readAsync();
    std::future<void> _writeAsync();

    SocketManager(Logger&, short&& port = 25);
    SocketManager(const SocketManager&) = delete;

    SocketManager& operator=(const SocketManager&) = delete;
};
