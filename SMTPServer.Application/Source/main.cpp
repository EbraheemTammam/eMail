#include <PCH.h>
#include <Logger.h>

using SMTPServer::Core::Logger;

int main()
{
    Logger& logger = Logger::getInstance();
    logger.setLogLevel(Logger::LogLevel::Info);
    logger.setOutput(Logger::Output::Console);
    logger.info("Hello World!");

    return 0;
}
