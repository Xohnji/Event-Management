#include "Headers/Ui_Utils.h"
#include <iostream>
#include <limits>
#include <windows.h>

using std::cout;
using std::cin;
using std::vector;
using std::endl;
using std::getline;
using std::numeric_limits;
using std::string;
using std::max;
using std::fixed;
using std::streamsize;

// Design Functions
void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void ClearLine(int x, int y, int length)
{
    gotoxy(x, y);
    cout << string(length, ' '); // overwrite with spaces
}

void Border(int left, int top, int width, int height)
{
    // Draw corners
    gotoxy(left, top);
    cout << "O";
    gotoxy(left + width, top);
    cout << "O";
    gotoxy(left, top + height);
    cout << "O";
    gotoxy(left + width, top + height);
    cout << "O";

    // Draw top and bottom edges
    for (int x = left + 1; x < left + width; x++)
    {
        gotoxy(x, top);
        cout << "-";
        gotoxy(x, top + height);
        cout << "-";
    }

    // Draw left and right edges
    for (int y = top + 1; y < top + height; y++)
    {
        gotoxy(left, y);
        cout << "|";
        gotoxy(left + width, y);
        cout << "|";
    }
}

// Clear Terminal Function
void Clear_Terminal()
{
#ifdef _WIN32
    std::system("cls");
#else
    std::system("clear");
#endif
}

// Clear Getline Input Buffer
void Clear_Getline()
{
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void verticalLine(int x, int yStart, int yEnd)
{
    for (int y = yStart; y <= yEnd; ++y)
    {
        gotoxy(x, y);
        cout << "|";
    }
}

void drawVerticalBars(int y, const vector<int> &xPositions)
{
    for (int x : xPositions)
    {
        gotoxy(x, y);
        cout << "|";
    }
}
