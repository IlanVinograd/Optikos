#include <utilities/logger.hpp>

Logger::~Logger()
{
    for (auto& log : logs)
    {
        log.second.running.store(false);
        log.second.cv.notify_all();
    }

    for (auto& log : logs)
    {
        if (log.second.worker.joinable()) log.second.worker.join();
        log.second.log.close();
    }
}

void Logger::add_logger(const std::string& file)
{
    auto& logger              = getInstance();
    auto [it_entry, inserted] = logger.logs.try_emplace(file);

    if (!inserted) throw std::runtime_error("Logger already exists");

    auto& entry = it_entry->second;

    std::string path = "logs/" + file;
    std::filesystem::create_directories("logs");
    entry.log.open(path, std::ios::out | std::ios::trunc);
    if (!entry.log.is_open()) throw std::runtime_error("Cannot open log file");

    auto* ptr    = &it_entry->second;
    entry.worker = std::thread(
        [ptr]()
        {
            while (ptr->running.load())
            {
                std::unique_lock<std::mutex> lock(ptr->mutex);
                ptr->cv.wait(lock, [ptr] { return !ptr->running.load() || !ptr->queue.empty(); });

                while (!ptr->queue.empty())
                {
                    auto message = std::move(ptr->queue.front());
                    ptr->queue.pop();

                    lock.unlock();
                    ptr->log << message << std::endl;
                    ptr->log.flush();
                    lock.lock();
                }
            }
        });
}

void Logger::log(const std::string& msg, const Severity severity, const std::string& file)
{
    auto& logger = getInstance();
    auto  it     = logger.logs.find(file);
    if (it == logger.logs.end())
    {
        // throw std::runtime_error("file not exist");
        return;
    }

    auto        now   = std::chrono::system_clock::now();
    auto        local = std::chrono::zoned_time{std::chrono::current_zone(), now}.get_local_time();
    auto        sec   = std::chrono::time_point_cast<std::chrono::seconds>(local);
    std::string logMsg =
        std::format("[{:%H:%M:%S}] [{}] {}", sec, severity_to_string(severity), msg);
    {
        std::lock_guard<std::mutex> lock(it->second.mutex);
        it->second.queue.push(std::move(logMsg));
    }
    it->second.cv.notify_one();
}