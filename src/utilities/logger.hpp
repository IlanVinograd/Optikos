#ifndef LOGGER_H
#define LOGGER_H

#include <atomic>
#include <chrono>
#include <condition_variable>
#include <filesystem>
#include <format>
#include <fstream>
#include <iostream>
#include <mutex>
#include <queue>
#include <sstream>
#include <string>
#include <thread>
#include <unordered_map>
#include <utility>


#define LOG_TRACE(msg, file) Logger::log(msg, Logger::Severity::trace, file)
#define LOG_DEBUG(msg, file) Logger::log(msg, Logger::Severity::debug, file)
#define LOG_INFO(msg, file) Logger::log(msg, Logger::Severity::info, file)
#define LOG_WARN(msg, file) Logger::log(msg, Logger::Severity::warn, file)
#define LOG_ERROR(msg, file) Logger::log(msg, Logger::Severity::error, file)
#define LOG_FATAL(msg, file) Logger::log(msg, Logger::Severity::fatal, file)

class Logger
{
   public:
    enum class Severity
    {
        trace,
        debug,
        info,
        warn,
        error,
        fatal
    };

    struct LoggerEntry
    {
        std::ofstream           log;
        std::queue<std::string> queue;
        std::mutex              mutex;
        std::condition_variable cv;
        std::atomic<bool>       running{true};
        std::thread             worker;
    };

    using Logs = std::unordered_map<std::string, LoggerEntry>;

    Logger(const Logger&)  = delete;
    Logger&        operator=(const Logger&) = delete;
    static Logger& getInstance()
    {
        static Logger logger;
        return logger;
    }

    ~Logger();

    static void add_logger(const std::string& file = "log");
    static void log(const std::string& msg, const Severity severity,
                    const std::string& file = "log");

   private:
    Logger()
    {
    }

    Logs logs;

    static constexpr std::string_view severity_to_string(Severity severity) noexcept
    {
        switch (severity)
        {
            case Severity::trace:
                return "TRACE";
            case Severity::debug:
                return "DEBUG";
            case Severity::info:
                return "INFO";
            case Severity::warn:
                return "WARN";
            case Severity::error:
                return "ERROR";
            case Severity::fatal:
                return "FATAL";
        }
        std::unreachable();
    }
};

#endif /* LOGGER_H */