#ifndef SLIME_PARTICLE_HPP
#define SLIME_PARTICLE_HPP
#include <vector>

#include "vector2.hpp"
#include "grid.hpp"

class SlimeParticle
{
    Vector2<double> position;
    Vector2<double> direction;


    double speed = 1;
    double sensor_offset_distance = 9;
    double left_right_sensor_angle = 45;
    double chemoattachant_deposition_factor = 3;
    double rotation_angle = 5;
    Grid& grid;

public:
    SlimeParticle(Grid& grid, Vector2<double> starting_position);

    void set_position(Vector2<double> position);
    void set_direction(Vector2<double> direction);
    void motor_stage();
    void sensory_stage();
};

#endif /* SLIME_PARTICLE_HPP*/