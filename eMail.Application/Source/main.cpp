#include <PCH.h>

#include <Logger.h>
using eMail::Core::Logger;

#include "SocketManager.h"
using eMail::Application::SocketManager;


int main()
{
    Logger& logger = Logger::getInstance();
    logger.setLogLevel(Logger::LogLevel::Info);
    logger.setOutput(Logger::Output::Console);
    logger.info("Hello World!");

    // logger.setOutput(Logger::OutpSocketut::All);
    // SocketManager& socketManager = SocketManager::GetInstance(logger);
    // logger.info(("Is Accepting: ") + std::string(socketManager.IsAccepting() ? "true" : "false"));
    // socketManager.Accept();

    return 0;
}
