#include "MenuProvider.h"

void MenuProvider::CreateMenus(HWND hWnd, HINSTANCE hInst) {
    CreateWindow(_T("Button"), _T("1px"), WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON,
        0, 200, 75, 20,
        hWnd, (HMENU)BUTTON_ID_WIDTH_1, hInst, NULL);

    CreateWindow(_T("Button"), _T("5px"), WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON,
        0, 220, 75, 20,
        hWnd, (HMENU)BUTTON_ID_WIDTH_5, hInst, NULL);

    CreateWindow(_T("Button"), _T("10px"), WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON,
        0, 240, 75, 20,
        hWnd, (HMENU)BUTTON_ID_WIDTH_10, hInst, NULL);

    CreateWindow(_T("Button"), _T("25px"), WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON,
        0, 260, 75, 20,
        hWnd, (HMENU)BUTTON_ID_WIDTH_25, hInst, NULL);

    CreateWindow(_T("Button"), _T("50px"), WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON,
        0, 280, 75, 20,
        hWnd, (HMENU)BUTTON_ID_WIDTH_50, hInst, NULL);

    CreateWindow(_T("Button"), _T("Simple"), WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON,
        0, 320, 75, 20,
        hWnd, (HMENU)BUTTON_ID_BRUSH, hInst, NULL);

    CreateWindow(_T("Button"), _T("Radial"), WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON,
        0, 340, 75, 20,
        hWnd, (HMENU)BUTTON_ID_RADIAL_BRUSH, hInst, NULL);

    CreateWindow(_T("Button"), _T("Pen"), WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON,
        0, 400, 75, 20,
        hWnd, (HMENU)BUTTON_ID_TOOL_PEN, hInst, NULL);

    CreateWindow(_T("Button"), _T("Square"), WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON,
        0, 420, 75, 20,
        hWnd, (HMENU)BUTTON_ID_TOOL_SQUARE, hInst, NULL);
    
    CreateWindow(_T("Button"), _T("Circle"), WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON,
        0, 440, 75, 20,
        hWnd, (HMENU)BUTTON_ID_TOOL_CIRCLE, hInst, NULL);
    


    ColorButton redButton(20, 20, 40, 40, RED_COLOR);
    colorButtons.push_back(redButton);
    CreateWindow(_T("Button"), _T(""), WS_CHILD | WS_VISIBLE | BS_OWNERDRAW,
        20, 20, 20, 20,
        hWnd, (HMENU)BUTTON_ID_RED_COLOR, hInst, NULL);

    ColorButton greenButton(20, 45, 40, 65, GREEN_COLOR);
    colorButtons.push_back(greenButton);
    CreateWindow(_T("Button"), _T(""), WS_CHILD | WS_VISIBLE | BS_OWNERDRAW,
        20, 45, 20, 20,
        hWnd, (HMENU)BUTTON_ID_GREEN_COLOR, hInst, NULL);

    ColorButton blueButton(20, 70, 40, 90, BLUE_COLOR);
    colorButtons.push_back(blueButton);
    CreateWindow(_T("Button"), _T("Blue"), WS_CHILD | WS_VISIBLE | BS_OWNERDRAW,
        20, 70, 20, 20,
        hWnd, (HMENU)BUTTON_ID_BLUE_COLOR, hInst, NULL);

    ColorButton blackButton(45, 20, 65, 40, BLACK_COLOR);
    colorButtons.push_back(blackButton);
    CreateWindow(_T("Button"), _T("Black"), WS_CHILD | WS_VISIBLE | BS_OWNERDRAW,
        45, 20, 20, 20,
        hWnd, (HMENU)BUTTON_ID_BLACK_COLOR, hInst, NULL);

    ColorButton yellowButton(45, 45, 65, 65, YELLOW_COLOR);
    colorButtons.push_back(yellowButton);
    CreateWindow(_T("Button"), _T("Yellow"), WS_CHILD | WS_VISIBLE | BS_OWNERDRAW,
        45, 45, 20, 20,
        hWnd, (HMENU)BUTTON_ID_YELLOW_COLOR, hInst, NULL);

    ColorButton purpleButton(45, 70, 65, 90, PURPLE_COLOR);
    colorButtons.push_back(purpleButton);
    CreateWindow(_T("Button"), _T("Purple"), WS_CHILD | WS_VISIBLE | BS_OWNERDRAW,
        45, 70, 20, 20,
        hWnd, (HMENU)BUTTON_ID_PURPLE_COLOR, hInst, NULL);

    CreateWindow(_T("Button"), _T("Eraser"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        17, 95, 50, 20,
        hWnd, (HMENU)BUTTON_ID_ERASER_COLOR, hInst, NULL);

    currentColor = RED_COLOR;
    //CheckRadioButton(hWnd, ColorMin, ColorMax, BUTTON_ID_RED_COLOR);
    
    currentWidth = 5;
    CheckRadioButton(hWnd, WidthMin, WidthMax, BUTTON_ID_WIDTH_5);

    isSimpleBrush = true;
    CheckRadioButton(hWnd, BrushMin, BrushMax, BUTTON_ID_BRUSH);

    ActiveTool = BUTTON_ID_TOOL_PEN;
    CheckRadioButton(hWnd, ToolMin, ToolMax, BUTTON_ID_TOOL_PEN);


}

bool MenuProvider::IsButton(int wmId) {
    return (wmId >= ColorMin && wmId <= ColorMax) || (wmId >= WidthMin && wmId <= WidthMax)
        || (wmId >= BrushMin && wmId <= BrushMax) || (wmId >= ToolMin && wmId <= ToolMax);
}

void MenuProvider::ClickOnButton(HWND hWnd, int wmId) {
    //colors
    if (ColorMin <= wmId && wmId <= ColorMax)
    {
        CheckRadioButton(hWnd, ColorMin, ColorMax, wmId);
        
        switch (wmId) 
        {
            case BUTTON_ID_RED_COLOR:
                currentColor = RED_COLOR;
                break;
            case BUTTON_ID_GREEN_COLOR:
                currentColor = GREEN_COLOR;
                break;
            case BUTTON_ID_BLUE_COLOR:
                currentColor = BLUE_COLOR;
                break;
            case BUTTON_ID_BLACK_COLOR:
                currentColor = BLACK_COLOR;
                break;
            case BUTTON_ID_YELLOW_COLOR:
                currentColor = YELLOW_COLOR;
                break;
            case BUTTON_ID_PURPLE_COLOR:
                currentColor = PURPLE_COLOR;
                break;
            case BUTTON_ID_ERASER_COLOR:
                currentColor = ERASER_COLOR;
                break;
        }
    }

    if (WidthMin <= wmId && wmId <= WidthMax)
    {
        CheckRadioButton(hWnd, WidthMin, WidthMax, wmId);

        switch (wmId)
        {
            case BUTTON_ID_WIDTH_1:
                currentWidth = 1;
                break;
            case BUTTON_ID_WIDTH_5:
                currentWidth = 5;
                break;
            case BUTTON_ID_WIDTH_10:
                currentWidth = 10;
                break;
            case BUTTON_ID_WIDTH_25:
                currentWidth = 25;
                break;
            case BUTTON_ID_WIDTH_50:
                currentWidth = 50;
                break;

        }
    }

    if (BrushMin <= wmId && wmId <= BrushMax)
    {
        CheckRadioButton(hWnd, BrushMin, BrushMax, wmId);

        switch (wmId)
        {
        case BUTTON_ID_BRUSH:
            isSimpleBrush = 1;
            break;
        case BUTTON_ID_RADIAL_BRUSH:
            isSimpleBrush = 0;
            break;
        }
    }

    if (ToolMin <= wmId && wmId <= ToolMax)
    {
        CheckRadioButton(hWnd, ToolMin, ToolMax, wmId);
        ActiveTool = wmId;
    }
}



COLORREF MenuProvider::GetCurrentColor()
{
    return currentColor;
}


int MenuProvider::GetCurrentWidth()
{
    return currentWidth;
}

bool MenuProvider::IsSimpleBrush()
{
    return isSimpleBrush;
}

int MenuProvider::GetActiveTool()
{
    return ActiveTool;
}

void MenuProvider::DrawColorButtons(HDC hdc)
{
    for (int i = 0; i < colorButtons.size(); i++) {
        colorButtons[i].Draw(hdc);
    }
}
