#define _CRT_SECURE_NO_WARNINGS
#undef UNICODE
#include<Windows.h>
#include<iostream>
#include"resource.h"

#define CONSOLE_DEBUG

using std::cout;
using std::endl;

CONST CHAR g_sz_WINDOW_CLASS[] = "TextEditor_PD311";

BOOL CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
CHAR* FormatLastError();
INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
#ifdef CONSOLE_DEBUG
	AllocConsole();
	freopen("CONOUT$", "w", stdout);
#endif

	WNDCLASSEX wClass;
	ZeroMemory(&wClass, sizeof(WNDCLASSEX));

	wClass.style = 0;
	wClass.cbSize = sizeof(WNDCLASSEX);
	wClass.cbWndExtra = 0;
	wClass.cbClsExtra = 0;

	wClass.hIcon = (HICON)LoadImage(hInstance, "resources\\text.ico", IMAGE_ICON, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_LOADFROMFILE);
	wClass.hIconSm = (HICON)LoadImage(hInstance, "resources\\text.ico", IMAGE_ICON, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_LOADFROMFILE);
	wClass.hCursor = LoadCursor(hInstance, IDC_ARROW);

	HBITMAP hBgImage = (HBITMAP)LoadImage(hInstance, "resources\\bg.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	wClass.hbrBackground = CreatePatternBrush(hBgImage);

	wClass.hInstance = hInstance;
	wClass.lpfnWndProc = (WNDPROC)WndProc;
	wClass.lpszClassName = g_sz_WINDOW_CLASS;
	wClass.lpszMenuName = MAKEINTRESOURCE(IDR_MAIN_MENU);

	if (!RegisterClassEx(&wClass))
	{
		MessageBox(NULL, "Class Registration failed", "Error", MB_OK | MB_ICONERROR);
		cout << FormatLastError() << endl;
		return 0;
	}

	/*int posX = (GetSystemMetrics(SM_CXSCREEN) - CW_USEDEFAULT) / 2;
	int posY = (GetSystemMetrics(SM_CYSCREEN) - CW_USEDEFAULT) / 2;*/

	HWND hwnd = CreateWindowEx(
		NULL,
		g_sz_WINDOW_CLASS,
		g_sz_WINDOW_CLASS,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		CW_USEDEFAULT, CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	if (hwnd == NULL)
	{
		MessageBox(NULL, "Window creation failed", "Error", MB_OK | MB_ICONERROR);
		return 0;
	}

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	MSG msg;
	while (GetMessage(&msg, 0, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

#ifdef CONSOLE_DEBUG
	FreeConsole();
#endif
	return 0;
}

BOOL CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:
	{
		RECT clientRect;
		GetClientRect(hwnd, &clientRect);
		INT winHeight = clientRect.bottom - clientRect.top;
		INT winWidth = clientRect.right - clientRect.left;
		HWND hEdit = CreateWindowEx
		(
			NULL, "Edit", "Workspace",
			WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_MULTILINE | ES_LEFT | ES_AUTOVSCROLL,
			0, 0,
			winWidth, winHeight,
			hwnd, (HMENU)IDC_EDIT,
			NULL, NULL
			);
	}
		break;
	case WM_COMMAND:
		break;
	case WM_SIZING:
	case WM_SIZE:
	case WM_MOVE:
	case WM_MOVING:
	{
		HWND hEdit = GetDlgItem(hwnd, IDC_EDIT);
		RECT clientRect;
		GetClientRect(hwnd, &clientRect);
		INT winHeight = clientRect.bottom - clientRect.top;
		INT winWidth = clientRect.right - clientRect.left;
		SetWindowPos(hEdit, HWND_TOP, clientRect.left, clientRect.top, winWidth, winHeight, SWP_SHOWWINDOW | SWP_NOZORDER);
	}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_CLOSE:
		DestroyWindow(hwnd);
	default: return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return FALSE;
}

CHAR* FormatLastError()
{
	DWORD errorID = GetLastError();
	LPSTR lpszBuffer = NULL;
	DWORD dwSize = FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL, errorID,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_RUSSIAN_RUSSIA),
		(LPSTR)&lpszBuffer,
		0, NULL
	);
	return lpszBuffer;
}
