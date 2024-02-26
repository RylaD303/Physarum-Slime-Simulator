#include "slime_particle.hpp"

SlimeParticle::SlimeParticle(Grid& grid, Vector2<double> starting_position) : grid(grid)
{
    this->set_position(starting_position);
    this->grid.refresh_hue_on_position(this->position);
}

void SlimeParticle::set_position(Vector2<double> position)
{
    if (!(this->grid.is_position_in_bounds(this->position)))
    {
        throw std::runtime_error("Setting position not in grid.");
    }
    this->position = position;
}

void SlimeParticle::motor_stage()
{
    Vector2<double> move_vec = this->direction*this->speed;
    
    Vector2<double> new_position = this->grid.cast_ray_in_grid(this->position, move_vec);

    this->set_position(new_position);
    this->grid.refresh_hue_on_position(this->position);
}

void SlimeParticle::sensory_stage()
{

}