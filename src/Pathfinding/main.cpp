#include <vector>
#include <conio.h>

#include "Grid.h"

#define NOMINMAX
#include <windows.h>

void gotoxy(short x, short y)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD position = { x, y };
    SetConsoleCursorPosition(hConsole, position);
}

void hidecursor()
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
}

class App
{
    Grid* mGrid;

    GridCoord* mPlayerCoord;
    GridCoord* mCursorCoord;

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

public:
    App()
    {
        mGrid = new Grid(map);
        mPlayerCoord = mGrid->CreateCoord();
        mCursorCoord = mGrid->CreateCoord();
    }

    ~App()
    {
        delete mGrid;
        delete mPlayerCoord;
        delete mCursorCoord;
    }

    void Run()
    {
        hidecursor();

        while (true)
        {
            Display();
            Input();
            mGrid->BuildPath(mPlayerCoord, mCursorCoord);
        }
    }

private:
    void Display()
    {
        gotoxy(0, 0); //refresh

        for (int row = 0; row < mGrid->RowCount; row++)
        {
            for (int col = 0; col < mGrid->ColCount; col++)
            {
                std::cout << "[";

                if (mCursorCoord->Is(row, col))
                {
                    std::cout << BG_GREEN;
                }
                else if (mGrid->GetTile(row, col)->path)
                {
                    std::cout << BG_RED;
                }

                if (mPlayerCoord->Is(row, col))
                {
                    std::cout << PLAYER;
                }
                else
                {
                    std::cout << map[row][col];
                }

                std::cout << DEFAULT;

                std::cout << "]";
            }

            std::cout << std::endl;
        }
    }

    void Input()
    {
        while (true)
        {
            int input = _getch();
            switch (input)
            {
            case 'z':
                mCursorCoord->AddRow(-1);
                return;

            case 's':
                mCursorCoord->AddRow(1);
                return;

            case 'q':
                mCursorCoord->AddCol(-1);
                return;

            case 'd':
                mCursorCoord->AddCol(1);
                return;

            case '\r':
                mPlayerCoord->Set(mCursorCoord);
                return;
            }
        }
    }
};

int main()
{
    App app;

    app.Run();

    return 0;
}
