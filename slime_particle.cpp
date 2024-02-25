#include "slime_particle.hpp"

SlimeParticle::SlimeParticle(std::vector<std::vector<Tile>>& tiles) : tiles(tiles)
{

}

void SlimeParticle::set_position(Vector2<double> position)
{
    this->position = position;
}
void SlimeParticle::motor_stage()
{
    int x = this->position.x + this->direction.x*speed;
    int y = this->position.y + this->direction.y*speed;
    if ()
}

void SlimeParticle::sensory_stage()
{

}