# pragma once

#include "PCH.h"

#include <Interfaces/ILogger.h>
using SMTPServer::Core::Interfaces::ILogger;

namespace SMTPServer::Application::TCP { class SocketManager; }

class SMTPServer::Application::TCP::SocketManager
{
public:
    static SocketManager& GetInstance(ILogger&, short&& port = 25);
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

    ILogger& _logger;
    mutable std::mutex _mutex;

    void _read();
    void _write();
    std::future<void> _readAsync();
    std::future<void> _writeAsync();

    SocketManager(ILogger&, short&& port = 25);
    SocketManager(const SocketManager&) = delete;

    SocketManager& operator=(const SocketManager&) = delete;
};
