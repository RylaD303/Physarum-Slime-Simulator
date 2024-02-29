#include "grid.hpp"
Grid::Grid(size_t rows, size_t columns)
{
    tiles = std::vector<std::vector<Tile>>(rows, std::vector<Tile>(columns));
    this->rows = rows;
    this->columns = columns;
}

bool Grid::is_index_in_bounds(int row, int col) const
{
    if (row < 0 || row >= this->rows || col < 0 || col >= this->columns)
    {
        return false;
    }
    return true;
}

void Grid::decay_rows(int starting_row, int ending_row)
{
    if (ending_row < starting_row)
    {
        ending_row = this->rows;
    }

    for (int i = starting_row; i < ending_row; i++)
    {
        for (int j = 0; j < this->columns; j++)
        {
            this->tiles[i][j].decay();
        }
    }
}

