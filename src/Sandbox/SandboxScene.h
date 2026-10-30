#pragma once

#include "Scene.h"
#include "Grid.h"

class SandboxScene : public Scene
{
    Entity* mpPlayer;
    Grid* mpGrid;

    Vector2f mTileSize;
    Vector2f mOffset;

    GridCoord mMouseCoord;
    GridCoord mPlayerCoord;

protected:
    void OnInitialize() override;
    void OnUpdate() override;

    Color GetTileColor(int row, int col);
    void SetPlayerCoord(GridCoord coord);
};
