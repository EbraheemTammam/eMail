#include "Logger.h"

SMTPServer::Core::Logger& SMTPServer::Core::Logger::getInstance()
{
    static Logger instance;
    return instance;
}

void SMTPServer::Core::Logger::setLogLevel(LogLevel level)
{
    std::lock_guard<std::mutex> lock(mutex_);
    logLevel_ = level;
}

void SMTPServer::Core::Logger::setOutput(Output output)
{
    std::lock_guard<std::mutex> lock(mutex_);
    output_ = output;
}

void SMTPServer::Core::Logger::log(SMTPServer::Core::Logger::LogLevel level, std::string_view message)
{
    if (level < logLevel_) return;

    std::lock_guard<std::mutex> lock(mutex_);
    std::string logEntry = std::format("{} [{}] {}\n", getCurrentTime(), to_string(level), message);

    if (output_ == Output::Console) {
        std::cout << logEntry;
    } else {
        std::ofstream logFile("log.txt", std::ios_base::app);
        logFile << logEntry;
    }
}

void SMTPServer::Core::Logger::info(std::string_view message)
{
    log(LogLevel::Info, message);
}

void SMTPServer::Core::Logger::warning(std::string_view message)
{
    log(LogLevel::Warning, message);
}

void SMTPServer::Core::Logger::error(std::string_view message)
{
    log(LogLevel::Error, message);
}

std::string SMTPServer::Core::Logger::getCurrentTime() const
{
    using std::chrono::_V2::system_clock;
    using std::chrono::duration_cast;
    using std::chrono::milliseconds;
    using millisec = std::chrono::duration<int64_t, std::milli>;

    auto now = system_clock::now();
    time_t in_time_t = system_clock::to_time_t(now);
    millisec milliseconds_ = duration_cast<milliseconds>(now.time_since_epoch()) % 1000;

    std::ostringstream ss;
    ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %H:%M:%S");
    ss << '.' << std::setfill('0') << std::setw(3) << milliseconds_.count();

    return ss.str();
}

const char* SMTPServer::Core::Logger::to_string(LogLevel level) const
{
    switch (level) {
        case LogLevel::Info: return "INFO";
        case LogLevel::Warning: return "WARNING";
        case LogLevel::Error: return "ERROR";
        default: return "UNKNOWN";
    }
}
