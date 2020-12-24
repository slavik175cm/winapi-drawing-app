#include "Painter.h"


void Painter::AddEntity(auto_ptr<DrawableEntity> newEntity) {
	//entities.push_back(newEntity);
	entities[kol++] = newEntity;
}

void Painter::PaintAll(HDC hdc) {
	for (int i = 0; i < kol; i++) {
		entities[i]->Draw(hdc);
	}
	//for (int i = 0; i < entities.size(); i++) 
	{
		//entities[i]->Draw(hdc);
	}
}

void Painter::PaintLast(HDC hdc) {
	entities[kol - 1]->Draw(hdc);
	//entities[entities.size() - 1]->Draw(hdc);
}

void Painter::ClearAll() {
	//entities.clear();
}
