#ifndef TASK_HPP
#define TASK_HPP

class Task
{
    int thread_id;

public:
    void set_thread_id(const int thread_id)
    {
        this->thread_id= this->thread_id;
    }
    
    virtual void operator()(){};
};

#endif /* TASK_HPP */