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

// Function to initialize slime particles
void initialize_slime_particles(Grid& grid, std::vector<SlimeParticle>& slime_particles, int number_of_slime_particles) 
{
    slime_particles.reserve(number_of_slime_particles);
    for (int i = 0; i < number_of_slime_particles; ++i) 
    {
        slime_particles.emplace_back(grid, Vector2<double>(0, 0));
        slime_particles[i].set_direction(Vector2<double>(generate_random_number(), generate_random_number()));
    }
}

// Function to initialize tasks for thread
void initialize_tasks(Grid& grid, std::vector<TaskMotorStageParticles>& motor_stage_tasks,
                     std::vector<TaskSensoryStageParticles>& sensory_stage_tasks,
                     std::vector<TaskDecayRowsGrid>& rows_grid,
                     std::vector<SlimeParticle>& slime_particles, int number_of_workers, int number_of_slime_particles) 
{
    motor_stage_tasks.reserve(number_of_workers);
    sensory_stage_tasks.reserve(number_of_workers);
    rows_grid.reserve(number_of_workers);

    int particle_task_factor = number_of_slime_particles / number_of_workers;
    int rows_task_factor = grid.tiles.size() / number_of_workers;

    for (int i = 0; i < number_of_workers; i++) 
    {
        motor_stage_tasks.emplace_back(slime_particles,
                                       i * particle_task_factor,
                                       i != number_of_workers - 1 ? (i + 1) * particle_task_factor : number_of_slime_particles);

        sensory_stage_tasks.emplace_back(slime_particles,
                                         i * particle_task_factor,
                                         i != number_of_workers - 1 ? (i + 1) * particle_task_factor : number_of_slime_particles);

        rows_grid.emplace_back(grid,
                               i * rows_task_factor,
                               i != number_of_workers - 1 ? (i + 1) * rows_task_factor : grid.tiles.size());
    }
}

// Function to simulate behavior
double simulate_behavior(ThreadPool& thread_pool, std::vector<TaskMotorStageParticles>& motor_stage_tasks,
                        std::vector<TaskSensoryStageParticles>& sensory_stage_tasks,
                        std::vector<TaskDecayRowsGrid>& rows_grid, int number_of_workers,
                        int steps) 
{
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
    thread_pool.stop();

    std::chrono::time_point<std::chrono::high_resolution_clock> end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration = end - start;

    return duration.count();
}

// Main simulation function
double simulate(Grid& grid, std::vector<SlimeParticle>& slime_particles, int number_of_workers, int number_of_slime_particles, int steps) 
{
    ThreadPool thread_pool(number_of_workers);
    std::vector<TaskMotorStageParticles> motor_stage_tasks;
    std::vector<TaskSensoryStageParticles> sensory_stage_tasks;
    std::vector<TaskDecayRowsGrid> rows_grid;

    initialize_tasks(grid, motor_stage_tasks, sensory_stage_tasks, rows_grid, slime_particles, number_of_workers, number_of_slime_particles);

    return simulate_behavior(thread_pool, motor_stage_tasks, sensory_stage_tasks, rows_grid, number_of_workers, steps);
}

// Function to run grid simulation
void run_grid_simulation(const std::pair<int, int>& resolution, const std::vector<int>& workers, const std::vector<int>& slime_particle_percentages) 
{
    Grid grid = Grid(resolution.second, resolution.first);
    std::vector<std::vector<double>> time_results(workers.size(), std::vector<double>(slime_particle_percentages.size()));

    for (size_t i = 0; i < slime_particle_percentages.size(); i++) 
    {
        for (size_t j = 0; j < workers.size(); j++) 
        {
            int slime_particle_percentage = slime_particle_percentages[i];
            int number_of_slime_particles = resolution.second * resolution.first * slime_particle_percentage / 100;

            std::vector<SlimeParticle> slime_particles;
            initialize_slime_particles(grid, slime_particles, number_of_slime_particles);
            time_results[j][i] = simulate(grid, slime_particles, workers[j], number_of_slime_particles, 10);
        }
    }

    std::cout << "Resolution: " << resolution.first << "x" << resolution.second << std::endl;

    std::cout << std::setw(15) << "Workers";
    for (int percentage : slime_particle_percentages) 
    {
        std::cout << std::setw(14) << percentage << std::setw(1) << "%";
    }
    std::cout << std::endl;

    for (size_t j = 0; j < workers.size(); j++) 
    {
        std::cout << std::setw(15) << workers[j];
        for (size_t i = 0; i < slime_particle_percentages.size(); i++) 
        {
            std::cout << std::setw(15) << time_results[j][i];
        }
        std::cout << std::endl;
    }

    std::cout << std::endl;
    std::cout << std::endl;
}


void compute()
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

int main() 
{
    compute();
}
