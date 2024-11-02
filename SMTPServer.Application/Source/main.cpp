#include <PCH.h>

#include <Utilities/Logger.h>
using SMTPServer::Core::Utilities::Logger;

#include "TCP/SocketManager.h"
using SMTPServer::Application::TCP::SocketManager;


int main()
{
    Logger& logger = Logger::getInstance();
    logger.setLogLevel(Logger::LogLevel::Info);
    logger.setOutput(Logger::Output::Console);
    logger.info("Hello World!");

    int a;
    int b{};

    logger.setOutput(Logger::Output::All);
    SocketManager& socketManager = SocketManager::GetInstance(logger);
    // logger.info(("Is Accepting: ") + std::string(socketManager.IsAccepting() ? "true" : "false"));
    socketManager.Accept();

    return 0;
}
