#include "Grid.h"

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
            tile.row = row;
            tile.col = col;
            tile.obstacle = map[row][col] == OBSTACLE;
            tile.added = false;
            tile.path = false;
            tile.cameFrom = nullptr;
        }
    }
}

void Grid::ResetTiles()
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
}

Tile* Grid::GetTile(int row, int col)
{
    if (row < 0 || row >= RowCount)
        return nullptr;

    if (col < 0 || col >= ColCount)
        return nullptr;

    return &mTiles[row][col];
}

Tile* Grid::GetTile(const GridCoord* coord)
{
    return &mTiles[coord->mRow][coord->mCol];
}

bool Grid::BuildPath(const GridCoord* startCoord, const GridCoord* endCoord)
{
    ResetTiles();

    Tile* start = GetTile(startCoord);
    Tile* end = GetTile(endCoord);

    std::vector<Tile*> remains;
    start->added = true;
    remains.push_back(start);

    while (remains.size() > 0)
    {
        Tile* current = remains[0];
        remains.erase(remains.begin());

        if (current == end)
        {
            while (current != nullptr)
            {
                current->path = true;
                current = current->cameFrom;
            }

            return true;
        }

        constexpr int directions[4][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };

        for (int i = 0; i < 4; ++i)
        {
            int row = current->row + directions[i][0];
            int col = current->col + directions[i][1];

            Tile* neighbor = GetTile(row, col);
            if (neighbor == nullptr)
                continue;

            if (neighbor->obstacle)
                continue;

            if (neighbor->added)
                continue;

            neighbor->added = true;
            neighbor->cameFrom = current;
            remains.push_back(neighbor);
        }
    }

    return false;
}

GridCoord* Grid::CreateCoord(int row, int col)
{
    GridCoord* out = new GridCoord(row, col, RowCount, ColCount);

    return out;
}
