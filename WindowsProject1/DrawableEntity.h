#pragma once
#include "framework.h"
#include "Resource.h"

class DrawableEntity
{
public:
	DrawableEntity();
	void virtual Draw(HDC hdc);
	void DoSomething();
};

