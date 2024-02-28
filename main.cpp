#include <iostream>
#include <iomanip> // For std::setw
#include <vector>
#include <chrono>

#include "vector2.cpp"
#include "task.hpp"
#include "thread_pool.hpp"
#include "slime_particle.hpp"
#include "grid.hpp"
#include "slime_tasks.hpp"
#include "utils.hpp"

double simulate(Grid& grid, int number_of_workers, int number_of_slime_particles)
{
    /* Initial arrays */
    std::vector<TaskMotorStageParticles> motor_stage_tasks;
    motor_stage_tasks.reserve(number_of_workers);

    std::vector<TaskSensoryStageParticles> sensory_stage_tasks;
    sensory_stage_tasks.reserve(number_of_workers);

    std::vector<TaskDecayRowsGrid> rows_grid;
    rows_grid.reserve(number_of_workers);
    
    std::vector<SlimeParticle> slime_particles;
    slime_particles.reserve(number_of_slime_particles);


    /* Create slime particles*/
    for (int i = 0; i < number_of_slime_particles; ++i)
    {
        slime_particles.emplace_back(grid, Vector2<double>(0, 0));
        slime_particles[i].set_direction(Vector2<double>(generate_random_number(), generate_random_number()));
    }


    /* Initialise tasks for thread */
    int particle_task_factor = number_of_slime_particles/number_of_workers;
    int rows_task_factor = grid.tiles.size()/number_of_workers;

    for (int i = 0, size = number_of_workers; i < number_of_workers; i++)
    {
        motor_stage_tasks.emplace_back(slime_particles,
                                       i*particle_task_factor,
                                       i != number_of_workers - 1 ? (i+1)*particle_task_factor : number_of_slime_particles);

        sensory_stage_tasks.emplace_back(slime_particles,
                                         i*particle_task_factor,
                                         i != number_of_workers - 1 ? (i+1)*particle_task_factor : number_of_slime_particles);

        rows_grid.emplace_back(grid,
                               i*rows_task_factor,
                               i != number_of_workers - 1 ? (i+1)*rows_task_factor : grid.tiles.size());
    }

    /* Simulate behaviour*/
    int steps = 10000000;
    ThreadPool thread_pool(number_of_workers);

    std::chrono::time_point<std::chrono::high_resolution_clock> start = std::chrono::high_resolution_clock::now();

    thread_pool.start();

    for (int i = 0; i < steps; i++) 
    {
        for (int j = 0; j < number_of_workers; j++)
        {
            thread_pool.schedule(&(motor_stage_tasks[j]));
        }
        thread_pool.wait_work();

        for (int j = 0; j < number_of_workers; j++)
        {
            thread_pool.schedule(&(sensory_stage_tasks[j]));
        }
        thread_pool.wait_work();

        for (int j = 0; j < number_of_workers; j++)
        {
            thread_pool.schedule(&(rows_grid[j]));
        }
        thread_pool.wait_work();

    }

    std::chrono::time_point<std::chrono::high_resolution_clock> end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration = end - start;

    return duration.count();
}

void run_grid_simulation(std::pair<int, int> resolution, std::vector<int>& workers, std::vector<int>& slime_particle_percentages)
{
    Grid grid = Grid(resolution.second, resolution.first);

    std::vector<std::vector<double>> time_results(workers.size(), std::vector<double>(slime_particle_percentages.size()));

    for (int i = 0, perc_size = slime_particle_percentages.size(); i < perc_size; i++)
    {

        for (int j = 0, worker_size = workers.size(); j < worker_size; j++)
        {
            int slime_particle_percentage = slime_particle_percentages[i];
            int number_of_slime_particles = resolution.second*resolution.first*slime_particle_percentage/100;

            time_results[j][i] = simulate(grid, workers[j], number_of_slime_particles);
        }
    }

    std::cout << std::setw(10) << "Workers";
    for (int percentage : slime_particle_percentages)
    {
        std::cout << std::setw(10) << percentage << "%";
    }
    std::cout << std::endl;

    for (int j = 0, worker_size = workers.size(); j < worker_size; j++) 
    {
        std::cout << std::setw(10) << workers[j];
        for (int i = 0, perc_size = slime_particle_percentages.size(); i < perc_size; i++)
        {
            std::cout << std::setw(10) << time_results[j][i];
        }
        std::cout << std::endl;
    }
    
}

int main() 
{

    int number_of_workers;
    std::vector<int> workers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
    std::vector<int> slime_particle_percentages = {1, 2, 3, 5, 8, 10, 12, 15};
    std::vector<std::pair<int, int>> grid_sizes =
        {
            {1280, 720},  /* HD */
            {1920, 1080}, /* Full HD */
            {2560, 1440}, /* Quad HD */
            {3840, 2160}  /* Ultra HD */
        };
    
    for (int i = 0, size = grid_sizes.size(); i < size; i++)
    {
        run_grid_simulation(grid_sizes[i], workers, slime_particle_percentages);
    }
}
