#ifndef THREAD_POOL_HPP 
#define THREAD_POOL_HPP

#include <thread>
#include <mutex>
#include <condition_variable>
#include <array>
#include <queue>
#include <chrono>
#include <atomic>
#include "task.hpp"

class ThreadPool
{
private:
    unsigned int number_of_workers;
    std::vector<std::thread> workers;
    std::queue<Task*> jobs;
    std::atomic<int> currently_working_tasks;
    std::mutex queue_mutex;
    std::condition_variable queue_cv;
    std::atomic<bool> terminating;

    void thread_loop(const int index);

public:
    ThreadPool(int number_of_workers);
    void start();
    void stop();
    bool schedule(Task* job);
    bool is_busy();
    void wait_work();

};

#endif /* THREAD_POOL_HPP */