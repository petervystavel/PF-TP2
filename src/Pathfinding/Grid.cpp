#include "Grid.h"

#include <queue>
#include <algorithm>

Grid::Grid(const std::vector< std::vector<char>>& map)
{
    RowCount = map.size();
    ColCount = map[0].size();

    mTiles.resize(RowCount);
    for (int row = 0; row < RowCount; ++row)
    {
        mTiles[row].resize(ColCount);
        for (int col = 0; col < ColCount; ++col)
        {
            Tile& tile = mTiles[row][col];
            tile.coord = { row, col };
            tile.obstacle = map[row][col] == OBSTACLE;
            tile.added = false;
            tile.path = false;
            tile.cameFrom = nullptr;
        }
    }
}

void Grid::Reset()
{
    for (int row = 0; row < RowCount; row++)
    {
        for (int col = 0; col < ColCount; col++)
        {
            Tile& tile = mTiles[row][col];
            tile.added = false;
            tile.path = false;
            tile.cameFrom = nullptr;
        }
    }

    mBuiltPath.clear();
}

bool Grid::IsValidIndex(GridCoord coord)
{
    if (coord.row < 0 || coord.row >= RowCount)
        return false;

    if (coord.col < 0 || coord.col >= ColCount)
        return false;
}

Tile* Grid::GetTile(GridCoord coord)
{
    if (IsValidIndex(coord) == false)
        return nullptr;

    return &mTiles[coord.row][coord.col];
}

bool Grid::BuildPath(GridCoord startCoord, GridCoord endCoord)
{
    Reset();

    Tile* start = GetTile(startCoord);
    Tile* end = GetTile(endCoord);

    std::queue<Tile*> remains;
    start->added = true;
    remains.push(start);

    while (remains.size() > 0)
    {
        Tile* current = remains.front();
        remains.pop();

        if (current == end)
        {
            while (current != nullptr)
            {
                current->path = true;
                mBuiltPath.push_back(current);
                current = current->cameFrom;
            }

            std::reverse(mBuiltPath.begin(), mBuiltPath.end());

            return true;
        }

        constexpr GridCoord directions[4] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };

        for (int i = 0; i < 4; ++i)
        {
            GridCoord coord = current->coord + directions[i];

            Tile* neighbor = GetTile(coord);
            if (neighbor == nullptr)
                continue;

            if (neighbor->obstacle)
                continue;

            if (neighbor->added)
                continue;

            neighbor->added = true;
            neighbor->cameFrom = current;
            remains.push(neighbor);
        }
    }

    return false;
}
