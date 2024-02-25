#ifndef SLIME_PARTICLE_HPP
#define SLIME_PARTICLE_HPP
#include <vector>

#include "vector2.hpp"
#include "tile.hpp"
class SlimeParticle
{
    Vector2<double> position;
    Vector2<double> direction;
    double speed;
    double forward_sensor_distance;
    double side_sensor_angle;

    std::vector<std::vector<Tile>>& tiles;
    int rows;
    int cols;

public:
    SlimeParticle(std::vector<std::vector<Tile>>& tiles);

    void set_position(Vector2<double> position)
    {
        this->position = position;
    }
    
    void motor_stage()
    {

    }

    void sensory_stage();
};

#endif /* SLIME_PARTICLE_HPP*/