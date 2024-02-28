#include "vector2.cpp"
#include "task.hpp"
#include "thread_pool.hpp"
#include "slime_particle.hpp"
#include "grid.hpp"


class TaskMotorStageParticles : public Task
{
private:
    std::vector<SlimeParticle>& particles;
    int from_index;
    int to_index;
public:
    TaskMotorStageParticles(std::vector<SlimeParticle>& particles, int from_index, int to_index)
                            : particles(particles), from_index(from_index), to_index(to_index) {}

    virtual void operator()()
    {
        for (int i = from_index; i < to_index; i++)
        {
            particles[i].motor_stage();
        }
    }
};

class TaskSensoryStageParticles : public Task
{
private:
    std::vector<SlimeParticle>& particles;
    int from_index;
    int to_index;
public:
    TaskSensoryStageParticles(std::vector<SlimeParticle>& particles, int from_index, int to_index)
                            : particles(particles), from_index(from_index), to_index(to_index) {}

    virtual void operator()()
    {
        for (int i = from_index; i < to_index; i++)
        {
            particles[i].sensory_stage();
        }
    }
};


class TaskDecayRowsGrid : public Task
{
private:
    Grid& grid;
    int from_row;
    int to_row;
public:
    TaskDecayRowsGrid(Grid& grid, int from_row, int to_row) : grid(grid), from_row(from_row), to_row(to_row) {}

    virtual void operator()()
    {
        grid.decay_rows(from_row, to_row);
    }
};