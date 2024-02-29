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
    void deposit_chemoattractant_on_position(const Vector2<NumericType>& vector, double chemoattractant);

    template<typename NumericType>
    double get_chemoattractant_on_position(const Vector2<NumericType>& vector) const;

    void decay_rows(int starting_row = 0, int ending_row = -1);

    template<typename NumericType>
    Vector2<NumericType> cast_ray_in_grid(Vector2<NumericType> start, Vector2<NumericType> ray);
};


template<typename NumericType>
bool Grid::is_position_in_bounds(const Vector2<NumericType>& vector) const
{
    /* don't forget vectors are reversed in graph */
    int row = std::floor(vector.y);
    int col = std::floor(vector.x);

    return is_index_in_bounds(row, col);
}

template<typename NumericType>
void Grid::deposit_chemoattractant_on_position(const Vector2<NumericType>& vector, double chemoattractant)
{
    /* don't forget vectors are reversed in graph */
    int row = std::floor(vector.y);
    int col = std::floor(vector.x);

    if (!is_index_in_bounds(row, col))
    {
        throw std::runtime_error("Bad index for hue refresh in grid.");
    }
    
    this->tiles[row][col].deposit_chemoattractant_value(chemoattractant);
}

template<typename NumericType>
double Grid::get_chemoattractant_on_position(const Vector2<NumericType>& vector) const
{
    /* don't forget vectors are reversed in graph */
    int row = std::floor(vector.y);
    int col = std::floor(vector.x);

    if (!is_index_in_bounds(row, col))
    {
       return 0;
    }

    return this->tiles[row][col].get_chemoattractant_value();
}


template<typename NumericType>
void calculate_remaining_ray_axis(NumericType distance_to_wall, Vector2<NumericType>& position, Vector2<NumericType>& ray, bool is_x_val = true)
{
    NumericType t = distance_to_wall / (is_x_val ? ray.x : ray.y);
    position += ray * t;
    if (is_x_val)
    {
        ray.x = -ray.x;
    }
    else
    {
        ray.y = -ray.y;
    }
    ray *= (1 - t);
}

template<typename NumericType>
Vector2<NumericType> Grid::cast_ray_in_grid(Vector2<NumericType> start, Vector2<NumericType> ray)
{
    Vector2<NumericType> position = start;

    while (true)
    {
        Vector2<NumericType> next_position = position + ray;

        bool out_of_bounds = false;

        if (next_position.x < 0)
        {
            calculate_remaining_ray_axis(-position.x, position, ray);
            out_of_bounds = true;
        }
        else if (next_position.x >= this->columns)
        {
            calculate_remaining_ray_axis(this->columns - 1 - position.x, position, ray);
            out_of_bounds = true;
        }

        if (next_position.y < 0)
        {
            calculate_remaining_ray_axis(-position.y, position, ray, false);
            out_of_bounds = true;
        }
        else if (next_position.y >= this->rows)
        {
            calculate_remaining_ray_axis(this->rows - 1 - position.y, position, ray, false);
            out_of_bounds = true;
        }

        if (!out_of_bounds)
        {
            break;
        }
    }

    return position;
}


#endif /* SLIME_PARTICLE_HPP*/