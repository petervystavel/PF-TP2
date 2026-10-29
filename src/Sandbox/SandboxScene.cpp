#include "SandboxScene.h"

#include "Player.h"
#include "InputManager.h"
#include "Debug.h"

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

    mCellSize.x = mCellSize.y = std::min(cellWidth, cellHeight);

    mGap.x = (width - (mCellSize.x * mpGrid->ColCount)) / 2;
    mGap.y = (height - (mCellSize.y * mpGrid->RowCount)) / 2;

    mpPlayer = CreateEntity<Player>(mCellSize.x / 2, Color::Blue);
    SetPlayerCoord({ 0,0 });
}

void SandboxScene::OnUpdate()
{
    //Draw grid
    Color emptyColors[2] = { Color::Gray, Color::White };
    int indexColor = 0;

    for (int row = 0; row < mpGrid->RowCount; ++row)
    {
        for (int col = 0; col < mpGrid->ColCount; ++col)
        {
            Color color = mpGrid->GetTile({ row, col })->obstacle ? Color::Red : emptyColors[indexColor];
            Vector2f pos = { mGap.x + col * mCellSize.x,  mGap.y + row * mCellSize.y };
            Debug::DrawRectangle(pos, mCellSize, color, true, { 0, 0 }, false);
            indexColor = (indexColor + 1) % 2;
        }

        if (mpGrid->ColCount % 2 == 0)
            indexColor = (indexColor + 1) % 2;
    }

    //Input
    InputManager* input = InputManager::Get();

    Vector2f mousePos = input->GetMousePosition();
    mousePos -= mGap;

    mMouseCoord.x = (int)(mousePos.x / mCellSize.x);
    mMouseCoord.y = (int)(mousePos.y / mCellSize.y);

    if (mpGrid->IsValidIndex(mMouseCoord))
    {
        Vector2f selectedCellPos = { mGap.x + mMouseCoord.x * mCellSize.x,  mGap.y + mMouseCoord.y * mCellSize.y };
        Debug::DrawRectangle(selectedCellPos, mCellSize, Color::Green, true, { 0, 0 }, false);

        std::vector<Tile*> path = mpGrid->BuildPath(mPlayerCoord, mMouseCoord);

        for (int i = 0; i < path.size(); ++i)
        {
            GridCoord cellCoord = { path[i]->row, path[i]->col };
            Vector2f pathCellPos = { mGap.x + cellCoord.x * mCellSize.x,  mGap.y + cellCoord.y * mCellSize.y };
            Debug::DrawRectangle(pathCellPos, mCellSize, Color::Cyan, true, { 0, 0 }, false);
        }

        if (path.size() > 0 && input->IsMouseDown(SDL_BUTTON_LEFT))
        {
            SetPlayerCoord(mMouseCoord);
        }
    }
}

void SandboxScene::SetPlayerCoord(GridCoord coord)
{
    assert(mpGrid->IsValidIndex(coord));

    mPlayerCoord = coord;

    Vector2f pos;

    pos.x = mGap.x + coord.x * mCellSize.x;
    pos.y = mGap.y + coord.y * mCellSize.y;

    mpPlayer->SetPosition(pos, 0.f, 0.f);
}
