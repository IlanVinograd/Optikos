#include <utilities/logger.hpp>

Logger::~Logger() {
    for (auto& log : logs) {
        log.second.running.store(false);
        log.second.cv.notify_all();
    }

    for (auto& log : logs) {
        if (log.second.worker.joinable())
            log.second.worker.join();
        log.second.log.close();
    }
}

void Logger::add_logger(std::string file) {
    auto [it_entry, inserted] = logs.try_emplace(file);
    
    if (!inserted)
        throw std::runtime_error("Logger already exists");

    auto& entry = it_entry->second;

    std::string path = "logs/" + file;
    std::filesystem::create_directories("logs");
    entry.log.open(path, std::ios::app);
    if (!entry.log.is_open())
        throw std::runtime_error("Cannot open log file");

    entry.worker = std::thread([&entry](){
        while(entry.running.load()) {
            std::unique_lock<std::mutex> lock(entry.mutex);
            entry.cv.wait(lock, [&] { return !entry.running.load() || !entry.queue.empty(); });

            while(!entry.queue.empty()) {
                auto [severity, message] = entry.queue.front();
                entry.queue.pop();

                lock.unlock();
                entry.log << message << std::endl;
                lock.lock();
            }
        }
    });
}