// WindowsProject1.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "WindowsProject1.h"
#include "vector"
#define MAX_LOADSTRING 100
#define TOOLBAR_HEIGHT 1000
#define TOOLBAR_WIDTH 75
//void AddMenus(HWND hWnd);
// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

RECT toolsRect = { 0, TOOLBAR_HEIGHT, TOOLBAR_WIDTH, 0 };

// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Разместите код здесь.

    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WINDOWSPROJECT1, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWSPROJECT1));

    MSG msg;

    // Цикл основного сообщения:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  ФУНКЦИЯ: MyRegisterClass()
//
//  ЦЕЛЬ: Регистрирует класс окна.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWSPROJECT1));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WINDOWSPROJECT1);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   ЦЕЛЬ: Сохраняет маркер экземпляра и создает главное окно
//
//   КОММЕНТАРИИ:
//
//        В этой функции маркер экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ЦЕЛЬ: Обрабатывает сообщения в главном окне.
//
//  WM_COMMAND  - обработать меню приложения
//  WM_PAINT    - Отрисовка главного окна
//  WM_DESTROY  - отправить сообщение о выходе и вернуться
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static bool isMouseDown = false, isMoving = false;
    static int lastX = 0, lastY = 0;
    switch (message)
    {

    case WM_CREATE:
        menuProvider->CreateMenus(hWnd, hInst);
        AddMenus(hWnd);
        break;

    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            if (menuProvider->IsButton(wmId)) {
                menuProvider->ClickOnButton(hWnd, wmId);
                break;
            }

            // Разобрать выбор в меню:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            case CLEAR_ALL:
            {
                painter->ClearAll();
                InvalidateRect(hWnd, NULL, TRUE);
            }
                
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    
    case WM_LBUTTONDOWN:
        isMouseDown = true;
        lastX = LOWORD(lParam);
        lastY = HIWORD(lParam);
        break;
    
    case WM_EXITSIZEMOVE:
    {
        HDC hdc = GetDC(hWnd);
        InvalidateRect(hWnd, NULL, true);
        painter->PaintAll(hdc);
        ReleaseDC(hWnd, hdc);
        InvalidateRect(hWnd, &toolsRect, true);
        break;
    }
    case WM_LBUTTONUP:

        if (menuProvider->GetActiveTool() == BUTTON_ID_TOOL_CIRCLE) {
            HDC hdc = GetDC(hWnd);
            int x = LOWORD(lParam), y = HIWORD(lParam);
            int radius = abs(y - lastY);
            auto_ptr<DrawableEntity> circle = auto_ptr<DrawableEntity>(
                (DrawableEntity*)(new Circle(lastX - radius, lastY + radius, lastX + radius, lastY - radius, 
                    menuProvider->GetCurrentWidth(), menuProvider->GetCurrentColor())));
            painter->AddEntity(circle);
            painter->PaintLast(hdc);

            ReleaseDC(hWnd, hdc);
        }

        if (menuProvider->GetActiveTool() == BUTTON_ID_TOOL_SQUARE) {
            HDC hdc = GetDC(hWnd);
            int x = LOWORD(lParam), y = HIWORD(lParam);
            int halfSide = abs(y - lastY);
            auto_ptr<DrawableEntity> square = auto_ptr<DrawableEntity>(
                (DrawableEntity*) (new Square(lastX - halfSide, lastY + halfSide, lastX + halfSide, lastY - halfSide, 
                    menuProvider->GetCurrentWidth(), menuProvider->GetCurrentColor())));
            painter->AddEntity(square);
            painter->PaintLast(hdc);
            ReleaseDC(hWnd, hdc);

        }
        isMouseDown = false;
        InvalidateRect(hWnd, &toolsRect, true);
        break;
    case WM_DRAWITEM:
    {
        HDC hdc = GetDC(hWnd);
        menuProvider->DrawColorButtons(hdc);
        ReleaseDC(hWnd, hdc);
        break;

    }
    case WM_RBUTTONDOWN:
    {
        HDC hdc = GetDC(hWnd);

        auto_ptr<DrawableEntity> filling = auto_ptr<DrawableEntity>((DrawableEntity*)
            (new Filling(LOWORD(lParam), HIWORD(lParam),
                menuProvider->IsSimpleBrush() ? 0 : 1,
                menuProvider->GetCurrentColor())));
        painter->AddEntity(filling);
        painter->PaintLast(hdc);

        ReleaseDC(hWnd, hdc);
        break;
    }
    case WM_MOUSEMOVE:
        if (isMouseDown)
        {

            if (menuProvider->GetActiveTool() == BUTTON_ID_TOOL_PEN) {
                int currentX = LOWORD(lParam), currentY = HIWORD(lParam);
                HDC hdc = GetDC(hWnd);
                
                auto_ptr<DrawableEntity> line = auto_ptr<DrawableEntity>(
                    (new Line(auto_ptr<Point>(new Point(lastX, lastY)),
                        auto_ptr<Point>(new Point(currentX, currentY)),
                     menuProvider->GetCurrentWidth(), 
                     menuProvider->GetCurrentColor())));
                painter->AddEntity(line);
                painter->PaintLast(hdc);
            
                lastX = currentX;
                lastY = currentY;
                ReleaseDC(hWnd, hdc);
            }
        }
        break;

    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);

            painter->PaintAll(hdc);
            
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

void AddMenus(HWND hWnd) {
    HMENU hMenubar;
    HMENU hMenu;

    hMenubar = CreateMenu();

    hMenu = CreateMenu();

    AppendMenuW(hMenu, MF_STRING, CLEAR_ALL, L"&Clear all");
    AppendMenuW(hMenu, MF_STRING, IDM_ABOUT, L"&About");
    AppendMenuW(hMenu, MF_STRING, IDM_EXIT, L"&Exit");

    AppendMenuW(hMenubar, MF_POPUP, (UINT_PTR)hMenu, L"&Program");

    SetMenu(hWnd, hMenubar);
}

// Обработчик сообщений для окна "О программе".
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
