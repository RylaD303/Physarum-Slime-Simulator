#include "tile.hpp"
int Tile::get_current_hue()
{ 
    return current_hue;
}

void Tile::set_current_hue_to_max()
{
    this->current_hue = get_max_hue();
}

void Tile::update()
{
    if (this->current_hue > 0)
    {
        current_hue--;
    }
}
