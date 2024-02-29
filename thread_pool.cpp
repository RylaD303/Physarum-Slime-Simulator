#include "thread_pool.hpp"

bool ThreadPool::is_busy()
{
    bool pool_busy;
    {
        std::unique_lock<std::mutex> lock(queue_mutex);
        pool_busy = !jobs.empty();
    }
    return pool_busy;
}


void ThreadPool::wait_work()
{
    while (is_busy())
    {}
}


ThreadPool::ThreadPool(int number_of_workers)
{
    this->terminating = false;
    this->number_of_workers = number_of_workers;
}

void ThreadPool::start()
{
    for (int64_t i = 0; i < number_of_workers; i++)
    {
        workers.push_back(std::thread(&ThreadPool::thread_loop, this, i));
    }
};

void ThreadPool::stop()
{
    std::unique_lock<std::mutex> lock(queue_mutex);
    this->terminating = true;
    lock.unlock();
    queue_cv.notify_all();
    for (auto& worker: workers)
	{
		if (worker.joinable())
		{
			worker.join();
		}
	}
    workers.clear();
}


void ThreadPool::thread_loop(int thread_number)
{
    while(true)
    {
		Task* task;
		{
			std::unique_lock<std::mutex> lock(queue_mutex);
			queue_cv.wait(lock, [this] {return this->terminating || !this->jobs.empty();});

			if (terminating == true)
			{
				return Task()();
			}
			task = jobs.front();
			jobs.pop();
			queue_cv.notify_one();
		}
        if (terminating == true)
        {
            return;
        }
        task->set_thread_id(thread_number);
        (*task)();
    }
}

bool ThreadPool::schedule(Task* job)
{
	{
		std::unique_lock<std::mutex> lock(queue_mutex);
		jobs.push(job);
	}
    queue_cv.notify_one();
    return true;
}
