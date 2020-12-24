#pragma once
#include "MenuProvider.h"
#include "framework.h"
#include "Resource.h"
#include <vector>
#include "ColorButton.h"
using namespace std;
class MenuProvider
{
public:
	void CreateMenus(HWND hWnd, HINSTANCE hInst);
	bool IsButton(int wmId);
	void ClickOnButton(HWND hWnd, int wmId);
	COLORREF GetCurrentColor();
	int GetCurrentWidth();
	bool IsSimpleBrush();
	int GetActiveTool();
	void DrawColorButtons(HDC hdc);
private:
	vector<ColorButton> colorButtons;

	const int ColorMin = 10000;
	const int ColorMax = 10007;

	const int WidthMin = 11000;
	const int WidthMax = 11004;

	const int BrushMin = 12000;
	const int BrushMax = 12001;

	const int ToolMin = 13000;
	const int ToolMax = 13002;

	COLORREF currentColor;
	int currentWidth;
	bool isSimpleBrush;
	int ActiveTool;
};

