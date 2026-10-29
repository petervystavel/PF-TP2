#pragma once
#include "Entity.h"

class SandboxScene;

class Player : public Entity
{
    Vector2f mCoord;

    SandboxScene* mpScene;

public:
    void OnInitialize() override;
};
