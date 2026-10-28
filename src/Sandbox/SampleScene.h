#pragma once

#include "Scene.h"
#include "Grid.h"

class Player;

class SanboxScene : public Scene
{
    Player* mPlayer;

    Grid* mpGrid;

    int mRowSize;
    int mColSize;

public:
    void OnInitialize() override;
    void OnUpdate() override;
};
