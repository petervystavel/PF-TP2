#pragma once

#include <iostream>
#include <vector>

#define BG_RED "\033[41m"
#define BG_GREEN "\033[42m"
#define DEFAULT "\033[0m"

#define EMPTY ' '
#define OBSTACLE '#'
#define PLAYER 'O'

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

    GridCoord operator+(const GridCoord& coord)
    {
        return { row + coord.row, col + coord.col };
    }
};

struct Tile
{
    GridCoord coord;
    bool obstacle;

    bool path;
    bool added;
    Tile* cameFrom;
};

class Grid
{
    std::vector<std::vector<Tile>> mTiles;
    std::vector<Tile*> mBuiltPath;

public:
    int RowCount;
    int ColCount;

    Grid(const std::vector<std::vector<char>>& map);
        
    void Reset();

    bool IsValidIndex(GridCoord coord);

    Tile* GetTile(GridCoord coord);

    bool BuildPath(GridCoord startCoord, GridCoord endCoord);

    const std::vector<Tile*>& GeBuiltPath() { return mBuiltPath; }
};
