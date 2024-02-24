#ifndef SLIME_PARTICLE_HPP
#define SLIME_PARTICLE_HPP

#include "vector2.hpp"

class SlimeParticle
{
    Vector2<double> position;
    Vector2<double> direction;
    double speed;
    double forward_sensor_distance;
    double angle_for_two_sensors;

public:
    void _motor_stage(std::vector<std::vector<Tile>>)
};

#endif /* SLIME_PARTICLE_HPP*/