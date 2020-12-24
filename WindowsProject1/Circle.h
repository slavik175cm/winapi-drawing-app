#pragma once
#include "DrawableEntity.h"
#include "framework.h"

class Circle : public DrawableEntity
{

public:
	Circle(int left, int top, int right, int bottom, int width, COLORREF color);
	void Draw(HDC hdc);

private:
	int left, top, right, bottom, width;
	COLORREF color;
};

