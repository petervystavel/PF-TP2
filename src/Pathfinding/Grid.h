#pragma once

#include <iostream>
#include <vector>

#define BG_RED "\033[41m"
#define BG_GREEN "\033[42m"
#define DEFAULT "\033[0m"

#define EMPTY ' '
#define OBSTACLE '#'
#define PLAYER 'O'

struct Tile
{
    int row, col;
    bool obstacle;

    bool path;
    bool added;
    Tile* cameFrom;
};

struct GridCoord
{
    union
    {
        int row;
        int y;
    };

    union
    {
        int col;
        int x;
    };

    bool Is(int row, int col)
    {
        return this->row == row && this->col == col;
    }
};

class Grid
{
    std::vector<std::vector<Tile>> mTiles;

public:
    int RowCount;
    int ColCount;

    Grid(const std::vector<std::vector<char>>& map);
        
    void Reset();

    bool IsValidIndex(GridCoord coord);

    Tile* GetTile(GridCoord coord);

    std::vector<Tile*> BuildPath(GridCoord startCoord, GridCoord endCoord);
};
