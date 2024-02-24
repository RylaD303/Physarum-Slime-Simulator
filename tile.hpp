#ifndef TILE_PARTICLE_HPP
#define TILE_PARTICLE_HPP

#include "vector2.hpp"

class Tile
{
#define MAX_HUE 10
    int current_hue;

public:
    static inline int get_max_hue() 
    {
        return MAX_HUE;
    }
    int get_current_hue();
    void set_current_hue_to_max();
    void update();
};

#endif /* TILE_PARTICLE_HPP*/