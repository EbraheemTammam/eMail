#pragma once

#include "PCH.h"
#include "Interfaces/ILogger.h"

namespace eMail::Core::Utilities { class Logger; }

class eMail::Core::Utilities::Logger : public eMail::Core::Interfaces::ILogger
{
public:
    static Logger& getInstance();
    void setLogLevel(LogLevel level) override;
    void setOutput(Output output) override;

    // Sync APIs
    void info(std::string_view message) override;
    void warning(std::string_view message) override;
    void error(std::string_view message) override;

    // Async APIs
    std::future<void> infoAsync(std::string_view message) override;
    std::future<void> warningAsync(std::string_view message) override;
    std::future<void> errorAsync(std::string_view message) override;

    ~Logger() override = default;

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
    std::future<void> logAsync(LogLevel level, std::string_view message);
};
