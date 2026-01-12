#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <unordered_map>
#include <queue>
#include <thread>
#include <atomic>
#include <mutex>
#include <condition_variable>
#include <utility>

class Logger {
public:

    enum class Severity {
        trace,
        debug,
        info,
        warn,
        error,
        fatal
    };

    struct LoggerEntry {
        std::ofstream log;
        std::queue<std::pair<Severity, std::string>> queue;
        std::mutex mutex;
        std::condition_variable cv;
        std::atomic<bool> running{true};
        std::thread worker;
    };

    using Logs = std::unordered_map<std::string, LoggerEntry>;

    Logger() = default;
    ~Logger();

    void add_logger(std::string file);

private:
    Logs logs;
};

#endif /* LOGGER_H */