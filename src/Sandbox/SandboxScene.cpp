#include "SandboxScene.h"

#include "Debug.h"
#include "InputManager.h"

std::vector<std::vector<char>> map =
{
    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ' },
    {'#','#','#','#','#',' ','#',' ',' ',' ' },
    {' ','#','#','#',' ',' ','#',' ',' ',' ' },
    {' ',' ','#',' ',' ',' ','#',' ',' ',' ' },
    {' ',' ',' ',' ',' ',' ','#',' ',' ',' ' },
    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ' },
    {' ',' ',' ',' ',' ',' ','#',' ',' ',' ' },
    {' ',' ',' ',' ',' ',' ','#',' ',' ',' ' },
    {' ',' ',' ',' ',' ',' ','#','#',' ',' ' },
    {' ',' ',' ',' ',' ',' ','#','#','#',' ' },
};

void SandboxScene::OnInitialize()
{
    mpGrid = new Grid(map);

    int width = GetWindowWidth();
    int height = GetWindowHeight();

    float cellWidth = width / mpGrid->ColCount;
    float cellHeight = height / mpGrid->RowCount;

    mTileSize.x = mTileSize.y = std::min(cellWidth, cellHeight);

    mOffset.x = (width - (mTileSize.x * mpGrid->ColCount)) / 2;
    mOffset.y = (height - (mTileSize.y * mpGrid->RowCount)) / 2;

    mpPlayer = CreateEntity<Entity>(mTileSize.x / 2, Color::Blue);
    SetPlayerCoord({ 0,0 });
}

Color SandboxScene::GetTileColor(int row, int col)
{
    Tile* tile = mpGrid->GetTile({ row, col });
    assert(tile);

    if (mMouseCoord.Is(row, col))
        return Color::Green;

    if (tile->obstacle)
        return Color::Red;

    if (tile->path)
        return Color::Cyan;

    return Color::Gray;
}

void SandboxScene::OnUpdate()
{
    //Input
    InputManager* input = InputManager::Get();

    Vector2f mousePos = input->GetMousePosition();
    mousePos -= mOffset;

    mMouseCoord.x = (int)(mousePos.x / mTileSize.x);
    mMouseCoord.y = (int)(mousePos.y / mTileSize.y);

    //Update
    if (mpGrid->IsValidIndex(mMouseCoord))
    {
        bool found = mpGrid->BuildPath(mPlayerCoord, mMouseCoord);

        if (found && input->IsMouseDown(SDL_BUTTON_LEFT))
        {
            SetPlayerCoord(mMouseCoord);
        }
    }

    //Draw
    for (int row = 0; row < mpGrid->RowCount; ++row)
    {
        for (int col = 0; col < mpGrid->ColCount; ++col)
        {
            Vector2f pos = { mOffset.x + col * mTileSize.x,  mOffset.y + row * mTileSize.y };
            Color color = GetTileColor(row, col);

            Debug::DrawRectangle(pos, mTileSize, color, true, { 0, 0 }, false);
        }
    }
}

void SandboxScene::SetPlayerCoord(GridCoord coord)
{
    assert(mpGrid->IsValidIndex(coord));

    mPlayerCoord = coord;

    Vector2f pos;

    pos.x = mOffset.x + coord.x * mTileSize.x;
    pos.y = mOffset.y + coord.y * mTileSize.y;

    mpPlayer->SetPosition(pos, 0.f, 0.f);
}
