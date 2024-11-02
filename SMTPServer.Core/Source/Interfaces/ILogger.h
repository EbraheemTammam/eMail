#pragma once

namespace SMTPServer::Core::Interfaces { class ILogger; }

class SMTPServer::Core::Interfaces::ILogger
{
public:
    enum struct LogLevel { Info, Warning, Error };
    enum struct Output { Console, File, All };

    virtual void setLogLevel(LogLevel level) = 0;
    virtual void setOutput(Output output) = 0;

    // Sync APIs
    virtual void info(std::string_view message) = 0;
    virtual void warning(std::string_view message) = 0;
    virtual void error(std::string_view message) = 0;

    // Async APIs
    virtual std::future<void> infoAsync(std::string_view message) = 0;
    virtual std::future<void> warningAsync(std::string_view message) = 0;
    virtual std::future<void> errorAsync(std::string_view message) = 0;

    virtual ~ILogger() = default;
};
