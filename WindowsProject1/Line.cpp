#include "Line.h"

Line::Line() {

}

Line::Line(auto_ptr<Point> point1, auto_ptr<Point> point2, int width, COLORREF color){
	this->point1 = point1;
	this->point2 = point2;
	this->width = width;
	this->color = color;
}

void Line::Draw(HDC hdc) {
	HPEN Pen = CreatePen(PS_SOLID, width, color);
	SelectObject(hdc, Pen);

	MoveToEx(hdc, point1->GetX(), point1->GetY(), NULL);
	LineTo(hdc, point2->GetX(), point2->GetY());

	DeleteObject(Pen);
}


