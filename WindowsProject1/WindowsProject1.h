#pragma once

#include "resource.h"
#include "MenuProvider.h"
#include "Painter.h"
#include "Square.h"
#include "Circle.h"
#include "Filling.h"
#include <memory>
void AddMenus(HWND hWnd);
MenuProvider *menuProvider = new MenuProvider();
Painter* painter = new Painter();
