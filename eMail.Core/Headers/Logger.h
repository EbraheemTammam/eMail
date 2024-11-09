#pragma once

#include "PCH.h"

namespace eMail::Core { class Logger; }

class eMail::Core::Logger
{
public:
    enum struct LogLevel { Info, Warning, Error };
    enum struct Output { Console, File, All };

    static Logger& getInstance();
    void setLogLevel(LogLevel level);
    void setOutput(Output output);

    void info(std::string_view message);
    void warning(std::string_view message);
    void error(std::string_view message);

    ~Logger() = default;

private:
    LogLevel logLevel_;
    Output output_;
    mutable std::mutex mutex_;

    Logger(const Logger&) = delete;
    Logger() : logLevel_(LogLevel::Info), output_(Output::Console) {}

    Logger& operator=(const Logger&) = delete;

    std::string getCurrentTime() const;
    const char* to_string(LogLevel level) const;
    void log(LogLevel level, std::string_view message);
};
