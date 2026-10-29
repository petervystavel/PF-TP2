#pragma once

#include "Scene.h"
#include "Grid.h"

class Player;

class SandboxScene : public Scene
{
    Player* mpPlayer;
    Grid* mpGrid;

    Vector2f mCellSize;
    Vector2f mGap;

    GridCoord mMouseCoord;
    GridCoord mPlayerCoord;

public:
    void OnInitialize() override;
    void OnUpdate() override;
    Grid* GetGrid() { return mpGrid; }
    void SetPlayerCoord(GridCoord coord);
};
