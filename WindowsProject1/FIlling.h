#pragma once
#include "DrawableEntity.h"
#include "framework.h"
#include <vector>
#include "Point.h";
#include <map>
#include <memory>
using namespace std;
class Filling : public DrawableEntity
{
public:
	COLORREF color;
	Filling(int x, int y, int type, COLORREF color);
	void Draw(HDC hdc);

private:
	int x, y, type;
	void Fill(HDC hdc, int x, int y, COLORREF newColor);
	void RadialFill(HDC hdc, int x, int y, COLORREF newColor);
	COLORREF GetNewColor(COLORREF oldColor, COLORREF newColor, int diffX, int diffY);
};

