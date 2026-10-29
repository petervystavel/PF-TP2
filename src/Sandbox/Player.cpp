#include "Player.h"

#include "SandboxScene.h"

void Player::OnInitialize()
{
    mpScene = GetScene<SandboxScene>();
}
