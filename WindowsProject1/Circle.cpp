#include "Circle.h"

Circle::Circle(int left, int top, int right, int bottom, int width, COLORREF color) {
	this->left = left;
	this->top = top;
	this->right = right;
	this->bottom = bottom;
	this->width = width;
	this->color = color;
}

void Circle::Draw(HDC hdc) {
	HPEN Pen = CreatePen(PS_SOLID, width, color);
	SelectObject(hdc, Pen);

	Ellipse(hdc, left, top, right, bottom);

	DeleteObject(Pen);
}