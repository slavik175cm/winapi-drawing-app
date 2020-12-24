#pragma once
#include "framework.h"

class ColorButton
{
public:
	ColorButton(int left, int top, int right, int bottom, COLORREF color);
	void Draw(HDC hdc);
private:
	int left, top, right, bottom;
	COLORREF color;
};

