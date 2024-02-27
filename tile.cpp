#include "tile.hpp"

Tile::Tile()
{
    this->current_chemoattractant_factor = 0;
}

double Tile::get_chemoattractant_value() const
{
    return this->current_chemoattractant_factor;
}


void Tile::deposit_chemoattractant_value(int value)
{
    this->current_chemoattractant_factor = value;
}

void Tile::decay()
{
    if (this->current_chemoattractant_factor > 0)
    {
        current_chemoattractant_factor-= 0.1;
    }
}
