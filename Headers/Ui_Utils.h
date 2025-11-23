#ifndef UI_UTILS_H
#define UI_UTILS_H

#include <vector>

void gotoxy(int x, int y);
void ClearLine(int x, int y, int length);
void Border(int left, int top, int width, int height);
void Clear_Terminal();
void Clear_Getline();
void verticalLine(int x, int yStart, int yEnd);
void drawVerticalBars(int y, const std::vector<int>& xPositions);

#endif
