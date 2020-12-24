#pragma once
	#include "DrawableEntity.h"
	#include "framework.h"

class Square : public DrawableEntity
{
public:
	Square(int left, int top, int right, int bottom, int width, COLORREF color);
	void Draw(HDC hdc);

private:
	int left, top, right, bottom, width;
	COLORREF color;
};

