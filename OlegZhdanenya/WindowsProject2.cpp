#include "stdafx.h"
#include "WindowsProject2.h"
#include <cstdlib>
#include "targetver.h"

//#pragma comment(linker, "/STACK:5000000000")
#define MAX_LOADSTRING 100
//
int* xArr;
int* yArr;
int index;
int capasity = 50;
void MyRegisterClass(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK About(HWND, UINT, WPARAM, LPARAM);
void Draw(HDC, int, int);
//

HINSTANCE hInst;
WCHAR szWindowClass[MAX_LOADSTRING];
HWND hWnd2;
int X = 0, Y = 0;
bool todraw = false;

int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	PSTR lpCmdLine,
	int nCmdShow)
{
	xArr = (int*)malloc(capasity * sizeof(int));
	yArr = (int*)malloc(capasity * sizeof(int));
	MyRegisterClass(hInstance);

	if (!InitInstance(hInstance, nCmdShow))
		return FALSE;

	HACCEL hAccelTable = LoadAccelerators(hInstance,
		MAKEINTRESOURCE(IDC_WINDOWSPROJECT2) //The return value is the specified value in the low-order word and zero in the high-order word
	);

	MSG msg;
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	return (int)msg.wParam;
}

void MyRegisterClass(HINSTANCE hInstance)
{
	LoadStringW(hInstance, //A handle to an instance of the module whose executable file contains the string resource
		IDC_WINDOWSPROJECT2,
		szWindowClass,
		MAX_LOADSTRING);
	WNDCLASSEXW wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = NULL;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0; //The number of extra bytes to allocate following the window-class structure.
	wcex.cbWndExtra = 0; //The number of extra bytes to allocate following the window instance
	wcex.hInstance = hInstance;
	wcex.hIcon = NULL;
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = NULL;
	RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance;
	HWND hWnd = CreateWindowW(szWindowClass,
		L"Lab 7",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		nullptr, //parent
		nullptr, //menu
		hInstance,
		nullptr
	);
	if (!hWnd)
		return FALSE;
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CREATE:
	{
		hWnd2 = CreateWindowEx(NULL,
			L"BUTTON",
			L"Clear",
			WS_CHILD,
			0,
			0,
			100,
			25,
			hWnd,
			HMENU(IDC_MyButton),
			hInst,
			NULL);
		ShowWindow(hWnd2, SW_SHOWNORMAL);
		break;
	}
	case WM_LBUTTONDOWN:
	{
		todraw = true;
		X = LOWORD(lParam);
		Y = HIWORD(lParam);
		InvalidateRect(hWnd, NULL, FALSE);
		break;
	}
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case IDC_MyButton:
			todraw = false;
			index = 0;
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		default:
			DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	}
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		Draw(hdc, X, Y);
		EndPaint(hWnd, &ps);
		break;
	}
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		break;
	}
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}


void Draw(HDC hdc, int x, int y)
{
	HPEN hPenOld;
	HPEN hlinePen;
	COLORREF lineColor = RGB(25, 47, 212);
	hlinePen = CreatePen(PS_SOLID, 5, lineColor);
	if (todraw) {
		xArr[index] = x;
		yArr[index] = y;
		index++;
		if (index == capasity) {
			capasity *= 2;
			xArr = (int*)realloc(xArr, capasity * sizeof(int));
			yArr = (int*)realloc(yArr, capasity * sizeof(int));
		}
	}
	hPenOld = (HPEN)SelectObject(hdc, hlinePen);
	for (int i = 0; i < index; i++)
	{
		
		MoveToEx(hdc, xArr[i], yArr[i], NULL);
		lineColor = RGB(500, 500, 500);
		hlinePen = CreatePen(PS_SOLID, 0, lineColor);
		hPenOld = (HPEN)SelectObject(hdc, hlinePen); 
		Rectangle(hdc, xArr[i] - 270, yArr[i] - 5, xArr[i] + 270, yArr[i] + 55);

		lineColor = RGB(25, 47, 212);
		hlinePen = CreatePen(PS_SOLID, 5, lineColor);
		hPenOld = (HPEN)SelectObject(hdc, hlinePen);
		
		//blade
		MoveToEx(hdc, xArr[i] , yArr[i], NULL);
		LineTo(hdc, xArr[i] + 250, yArr[i]);
		LineTo(hdc, xArr[i] + 180, yArr[i] + 50);
		LineTo(hdc, xArr[i], yArr[i] + 50);
		LineTo(hdc, xArr[i], yArr[i]);
		MoveToEx(hdc, xArr[i], yArr[i] + 30, NULL);
		LineTo(hdc, xArr[i] + 160, yArr[i] + 30);
		LineTo(hdc, xArr[i] + 180, yArr[i] + 50);
		MoveToEx(hdc, xArr[i] + 160, yArr[i] + 30, NULL);
		LineTo(hdc, xArr[i] + 200, yArr[i]);

		lineColor = RGB(100, 100, 100);
		hlinePen = CreatePen(PS_SOLID, 1, lineColor);
		hPenOld = (HPEN)SelectObject(hdc, hlinePen);

		for (int j = 0; j <= 26; j++) {
			MoveToEx(hdc, xArr[i]+2, yArr[i]+2 + j, NULL);
			LineTo(hdc, xArr[i] + 194-j*4/3, yArr[i]+2+j);
		}

		MoveToEx(hdc, xArr[i]-5, yArr[i], NULL);

		lineColor = RGB(0, 0, 0);
		hlinePen = CreatePen(PS_SOLID, 5, lineColor);
		hPenOld = (HPEN)SelectObject(hdc, hlinePen);
		//handle
		LineTo(hdc, xArr[i] - 250, yArr[i]);
		LineTo(hdc, xArr[i] - 265, yArr[i] + 15);
		LineTo(hdc, xArr[i] - 265, yArr[i] + 15 +20);
		LineTo(hdc, xArr[i] - 250, yArr[i] + 15 + 20 + 15);
		LineTo(hdc, xArr[i] - 5, yArr[i] + 50);
		
		MoveToEx(hdc, xArr[i], yArr[i] + 25, NULL);

		lineColor = RGB(0, 0, 0);

		hlinePen = CreatePen(PS_SOLID, 1, lineColor);
		hPenOld = (HPEN)SelectObject(hdc, hlinePen);
		for (int j = 0; j <= 50; j++) {
			MoveToEx(hdc, xArr[i], yArr[i] +j, NULL);
			LineTo(hdc, xArr[i] - 250, yArr[i] + j);
		}
		MoveToEx(hdc, xArr[i]-250, yArr[i], NULL);
		for (int j = 0; j <= 15; j++) {
			
			LineTo(hdc, xArr[i] - 265, yArr[i] + j + 15);
			MoveToEx(hdc, xArr[i] -250, yArr[i] + j, NULL);
		}

		MoveToEx(hdc, xArr[i] - 250, yArr[i]+50, NULL);
		for (int j = 0; j <= 15; j++) {

			LineTo(hdc, xArr[i] - 265, yArr[i] - j + 35);
			MoveToEx(hdc, xArr[i] - 250, yArr[i] - j + 50, NULL);
		}

		MoveToEx(hdc, xArr[i] - 250, yArr[i] + 15, NULL);
		for (int j = 0; j <= 22; j++) {

			LineTo(hdc, xArr[i] - 265, yArr[i] + j + 15);
			MoveToEx(hdc, xArr[i] - 250, yArr[i] + j + 15, NULL);
		}

		lineColor = RGB(219, 63, 35);
		hlinePen = CreatePen(PS_SOLID, 5, lineColor);
		hPenOld = (HPEN)SelectObject(hdc, hlinePen);
		for (int j = 0; j <= 6; j++) {

			MoveToEx(hdc, xArr[i] - 20 - 30*j, yArr[i] + 25, NULL);
			LineTo(hdc, xArr[i] - 30 - 30*j, yArr[i] + 45);
			LineTo(hdc, xArr[i] - 40 - 30*j, yArr[i] + 25);
			LineTo(hdc, xArr[i] - 30 - 30*j, yArr[i] + 5);
			LineTo(hdc, xArr[i] - 20 - 30*j, yArr[i] + 25);

			for (int k = 0; k <= 20; k++) {
				MoveToEx(hdc, xArr[i] - 20 - 30 * j-k/2, yArr[i] + 25 -k, NULL);
				LineTo(hdc, xArr[i] - 30 - 30 * j-k/2, yArr[i] + 45-k);
			}
		}
		/*for (int j = 0; j < 3; j++) {
			MoveToEx(hdc, xArr[i] + 20 - j*30, yArr[i] - 25, NULL);
			LineTo(hdc, xArr[i]+20 + j*30 + 10, yArr[i]+25+20);
		}*/
	}
	todraw = false;

	SelectObject(hdc, hPenOld);
	DeleteObject(hlinePen);
}