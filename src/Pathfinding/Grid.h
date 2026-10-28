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

class GridCoord
{
public:
    int GetRow() const { return mRow; }
    int GetCol() const { return mCol; }

    bool AddRow(int row)
    {
        return SetRow(mRow + row);
    }
    bool AddCol(int col)
    {
        return SetCol(mCol + col);
    }

    bool SetRow(int row)
    {
        if (row < 0 || row >= mMaxRow)
            return false;

        mRow = row;
        return true;
    }
    bool SetCol(int col)
    {
        if (col < 0 || col >= mMaxCol)
            return false;

        mCol = col;
        return true;
    }

    void Set(const GridCoord* coord)
    {
        mRow = coord->mRow;
        mCol = coord->mCol;
    }

    bool Is(int row, int col) const
    {
        return mRow == row && mCol == col;
    }

private:
    GridCoord(int row, int col, int maxRow, int maxCol)
    {
        mRow = row;
        mCol = col;
        mMaxRow = maxRow;
        mMaxCol = maxCol;
    }

    int mRow, mCol;
    int mMaxRow, mMaxCol;

    friend class Grid;
};

class Grid
{
    std::vector<std::vector<Tile>> mTiles;

public:
    int RowCount;
    int ColCount;

    Grid(const std::vector<std::vector<char>>& map);

    void ResetTiles();

    Tile* GetTile(int row, int col);

    Tile* GetTile(const GridCoord* coord);

    bool BuildPath(const GridCoord* startCoord, const GridCoord* endCoord);

    GridCoord* CreateCoord(int row = 0, int col = 0);
};
