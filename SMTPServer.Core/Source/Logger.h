#pragma once

#include "PCH.h"

namespace SMTPServer::Core { class Logger; }

class SMTPServer::Core::Logger
{
    public: enum struct LogLevel { Info, Warning, Error };
    public: enum struct Output { Console,File };
    public: static Logger& getInstance();
    public: void setLogLevel(LogLevel level);
    public: void setOutput(Output output);
    public: void log(LogLevel level, std::string_view message);
    public: void info(std::string_view message);
    public: void warning(std::string_view message);
    public: void error(std::string_view message);

    private: Logger(const Logger&) = delete;
    private: Logger() : logLevel_(LogLevel::Info), output_(Output::Console) {}
    private: Logger& operator=(const Logger&) = delete;
    private: std::string getCurrentTime() const;
    private: const char* to_string(LogLevel level) const;
    private: LogLevel logLevel_;
    private: Output output_;
    private: mutable std::mutex mutex_;
};
