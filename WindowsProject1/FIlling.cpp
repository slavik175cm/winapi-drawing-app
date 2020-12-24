#include "FIlling.h"

Filling::Filling(int x, int y, int type, COLORREF color) {
    this->x = x;
    this->y = y;
    this->type = type;
    this->color = color;
}

void Filling::Draw(HDC hdc) {
    if (type == 0)
        Fill(hdc, x, y, color);
    else RadialFill(hdc, x, y, color);
}

void Filling::Fill(HDC hdc, int x, int y, COLORREF newColor) {
    HBRUSH brush = CreateSolidBrush(newColor);
    SelectObject(hdc, brush);
    ExtFloodFill(hdc, x, y, GetPixel(hdc, x, y), FLOODFILLSURFACE);
    DeleteObject(brush);
}

COLORREF Filling::GetNewColor(COLORREF oldColor, COLORREF newColor, int diffX, int diffY) {
    int oldRed = GetRValue(oldColor);
    int oldGreen = GetGValue(oldColor);
    int oldBlue = GetBValue(oldColor);

    int newRed = GetRValue(newColor);
    int newGreen = GetGValue(newColor);
    int newBlue = GetBValue(newColor);

    double coeff = pow((diffX * diffX) + (diffY * diffY), 0.5) / (double)100;
    if (coeff >= 1) return oldColor;

    double red = newRed + (oldRed - newRed) * coeff;
    double green = newGreen + (oldGreen - newGreen) * coeff;
    double blue = newBlue + (oldBlue - newBlue) * coeff;
    return RGB(red, green, blue);
}

void Filling::RadialFill(HDC hdc, int x, int y, COLORREF newColor) {
    COLORREF oldColor = GetPixel(hdc, x, y);
    if (oldColor == newColor) return;
    vector<auto_ptr<Point>> queue(0);
    queue.push_back(auto_ptr<Point>(new Point(x, y)));

    int steps[4][2] = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };
    int i = 0;
    map<pair<int, int>, bool> mem;
    mem.clear();

    while (i != queue.size()) {
        COLORREF gradColor = GetNewColor(oldColor, newColor, x - queue[i]->GetX(), y - queue[i]->GetY());
        if (gradColor == oldColor) {
            i++; 
            continue;
        }
        SetPixel(hdc, queue[i]->GetX(), queue[i]->GetY(), gradColor);
        for (int j = 0; j < 4; j++) {
            if (mem[make_pair(queue[i]->GetX() + steps[j][0], queue[i]->GetY() + steps[j][1])]) continue;
            if (GetPixel(hdc, queue[i]->GetX() + steps[j][0], queue[i]->GetY() + steps[j][1]) == oldColor) {
                queue.push_back((auto_ptr<Point>(new Point(queue[i]->GetX() + steps[j][0], queue[i]->GetY() + steps[j][1]))));
                mem[make_pair(queue[i]->GetX() + steps[j][0], queue[i]->GetY() + steps[j][1])] = true;
            }
        }
        i++;
    }
}

