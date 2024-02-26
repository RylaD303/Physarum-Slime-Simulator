#ifndef GRID_HPP
#define GRID_HPP
#include <vector>
#include <cmath>

#include "vector2.hpp"
#include "tile.hpp"

struct Grid
{
    std::vector<std::vector<Tile>> tiles;
    int rows;
    int columns;

    Grid(size_t rows, size_t columns);

    bool is_index_in_bounds(int row, int col) const;

    template<typename NumericType>
    bool is_position_in_bounds(const Vector2<NumericType>& vector) const;

    template<typename NumericType>
    void refresh_hue_on_position(const Vector2<NumericType>& vector);

    void update_rows(int starting_row = 0, int ending_row = -1);

    template<typename NumericType>
    Vector2<NumericType> Grid::cast_ray_in_grid(Vector2<NumericType> start, Vector2<NumericType> ray);
};

#endif /* SLIME_PARTICLE_HPP*/