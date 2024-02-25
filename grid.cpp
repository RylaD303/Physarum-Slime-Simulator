#include "grid.hpp"
Grid::Grid(size_t rows, size_t columns)
{
    tiles = std::vector<std::vector<Tile>>(rows, std::vector<Tile>(columns));
    this->rows = rows;
    this->columns = columns;
}

bool Grid::index_in_bounds(int row, int col) const
{
    if (row < 0 || row >= this->rows || col < 0 || col >= this->columns)
    {
        return false;
    }
    return true;
}

template<typename NumericType>
bool Grid::is_position_in_bounds(const Vector2<NumericType>& vector) const
{
    /* don't forget vectors are reversed in graph */
    int row = std::round(vector.y);
    int col = std::round(vector.x);

    return index_in_bounds(row, col);
}

template<typename NumericType>
void Grid::refresh_hue_on_position(const Vector2<NumericType>& vector)
{
    /* don't forget vectors are reversed in graph */
    int row = std::round(vector.y);
    int col = std::round(vector.x);

    if (!index_in_bounds(row, col))
    {
        std::throw("Bad index.");
    }
    
    tiles[row][col].refresh_hue();
}

void Grid::update_rows(int starting_row = 0, int ending_row = -1)
{
    if (ending_row < starting_row)
    {
        ending_row = this->rows;
    }

    for (int i = 0, i = starting_row; i < ending_row; i++)
    {
        for (int j = 0; j < this->columns; j++)
        {
            this->tiles[i][j].update();
        }
    }
}