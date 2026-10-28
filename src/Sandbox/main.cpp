#include "GameManager.h"
#include "SampleScene.h"

int main()
{
    GameManager* game = GameManager::Get();

    game->LaunchScene<SanboxScene>(1280, 720, "Sandbox", Color{ 25, 25, 35 });

    return 0;
}
