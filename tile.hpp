#ifndef TILE_HPP
#define TILE_HPP

#include "vector2.hpp"

class Tile
{
#define MAX_HUE 10
    double current_chemoattractant_factor;

public:
    Tile();
    double get_chemoattractant_value() const;
    void deposit_chemoattractant_value(int value);
    void decay();
};

#endif /* TILE_HPP*/