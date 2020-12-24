#pragma once
#include "MenuProvider.h"
#include "framework.h"
#include "Resource.h"
#include <vector>
#include "Point.h"
#include "Line.h"
#include "DrawableEntity.h"
#include <memory>
using namespace std;

class Painter
{
public:
	void AddEntity(auto_ptr<DrawableEntity> newEntity);
	void PaintAll(HDC hdc);
	void PaintLast(HDC hdc);
	void ClearAll();
private:
	//vector<auto_ptr<DrawableEntity>> entities;
	int kol;
	auto_ptr<DrawableEntity> entities[100000];
};

