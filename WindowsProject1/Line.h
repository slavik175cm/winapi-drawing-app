#pragma once
#include "Point.h"
#include "framework.h"
#include "Resource.h"
#include "DrawableEntity.h"
#include <memory>
using namespace std;
class Line : public DrawableEntity {
public:

	Line();

	Line(auto_ptr<Point> point1, auto_ptr<Point> point2, int width, COLORREF color);

	void virtual Draw(HDC hdc);

private:
	//Point *point1, *point2;
	auto_ptr<Point> point1, point2;
	int width;
	COLORREF color;
};
