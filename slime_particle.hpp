#ifndef SLIME_PARTICLE_HPP
#define SLIME_PARTICLE_HPP
#include <vector>

#include "vector2.hpp"
#include "Grid.hpp"

class SlimeParticle
{
    Vector2<double> position;
    Vector2<double> direction;
    double speed;
    double forward_sensor_distance;
    double side_sensor_angle;

    Grid& grid;
    int rows;
    int cols;

public:
    SlimeParticle(Grid& grid, Vector2<double> starting_position);

    void set_position(Vector2<double> position);

    void motor_stage();
    void sensory_stage();
};

#endif /* SLIME_PARTICLE_HPP*/