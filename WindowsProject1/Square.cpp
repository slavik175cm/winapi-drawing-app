#include "Square.h"

Square::Square(int left, int top, int right, int bottom, int width, COLORREF color) {
	this->left = left;
	this->top = top;
	this->right = right;
	this->bottom = bottom;
	this->width = width;
	this->color = color;
}

void Square::Draw(HDC hdc) {
	HPEN Pen = CreatePen(PS_SOLID, width, color);
	SelectObject(hdc, Pen);
	
	Rectangle(hdc, left, top, right, bottom);
	
	DeleteObject(Pen);
}