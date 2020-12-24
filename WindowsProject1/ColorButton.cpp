#include "ColorButton.h"
#include "FIlling.h"
ColorButton::ColorButton(int left, int top, int right, int bottom, COLORREF color)
{
	this->left = left;
	this->top = top;
	this->right = right;
	this->bottom = bottom;
	this->color = color;
}

void ColorButton::Draw(HDC hdc)
{
	HPEN Pen = CreatePen(PS_SOLID, 1, color);
	SelectObject(hdc, Pen);

	Rectangle(hdc, left, top, right, bottom);
	Filling filling(left + 1, top + 1, 0, color);
	filling.Draw(hdc);

	DeleteObject(Pen);
}
