#include "SampleScene.h"

#include "DummyEntity.h"
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

void SanboxScene::OnInitialize()
{
    mpGrid = new Grid(map);

    mPlayer = CreateEntity<Player>(10, Color::Blue);

    int width = GetWindowWidth();
    int height = GetWindowHeight();

    mRowSize = height / mpGrid->RowCount;
    mColSize = width / mpGrid->ColCount;

}

void SanboxScene::OnUpdate()
{
    int top = 0;
    int bottom = GetWindowHeight();

    for (int col = 0; col <= mpGrid->ColCount; ++col)
    {
        int colPos = col * mColSize;
        Debug::DrawLine({ colPos, top }, { colPos, bottom }, Color::Cyan);
    }
}
