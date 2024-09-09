#define _CRT_SECURE_NO_WARNINGS
#undef UNICODE
#include<Windows.h>
#include<Richedit.h>
#include<iostream>
#include"resource.h"

//#define CONSOLE_DEBUG

using std::cout;
using std::endl;

CONST CHAR g_sz_WINDOW_CLASS[] = "TextEditor_PD311";

BOOL CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
CHAR* FormatLastError();
BOOL LoadTextFile(HWND hEdit, LPCSTR lpszFileName);
BOOL SaveTextFile(HWND hEdit, LPCSTR lpszFileName);


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
	static HINSTANCE hRichEdit20 = LoadLibrary("RichEd20.dll");
	static BOOLEAN isWordWrap = TRUE;

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
			NULL, RICHEDIT_CLASS, "Workspace",
			WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_MULTILINE | ES_LEFT | ES_AUTOVSCROLL,
			30, 30,
			winWidth - 60, winHeight - 60,
			hwnd, (HMENU)IDC_EDIT,
			NULL, NULL
			);
	}
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_FILE_OPEN:
		{
			CHAR szFileName[MAX_PATH]{};

			OPENFILENAME ofn;
			ZeroMemory(&ofn, sizeof(ofn));
			ofn.lStructSize = sizeof(ofn);
			ofn.hwndOwner = hwnd;
			ofn.lpstrFilter = "Text files: (*.txt)\0*.txt\0All files (*.*)\0*.*\0";
			ofn.lpstrDefExt = "txt";
			ofn.nMaxFile = MAX_PATH;
			ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
			ofn.lpstrFile = szFileName;

			if (GetOpenFileName(&ofn))
			{
				HWND hEdit = GetDlgItem(hwnd, IDC_EDIT);
				LoadTextFile(hEdit, szFileName);
			}
		}
			break;
		case ID_FORMAT_WORDWRAP:
		{
			RECT clientRect;
			GetClientRect(hwnd, &clientRect);
			HWND hEdit = GetDlgItem(hwnd, IDC_EDIT);

			if (isWordWrap)
			{
				SetWindowLongPtr(hEdit, GWL_STYLE, WS_CHILD | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL | ES_MULTILINE | ES_AUTOHSCROLL | ES_AUTOVSCROLL);
				isWordWrap = FALSE;
			}
			else
			{
				SetWindowLongPtr(hEdit, GWL_STYLE, WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_MULTILINE | ES_LEFT | ES_AUTOVSCROLL);
				isWordWrap = TRUE;
			}
			// TODO: repaint doesn't really works... same with horisontal scroll
			MoveWindow
			(
				hEdit, clientRect.left + 30, clientRect.top + 30,
				clientRect.right - clientRect.left - 60,
				clientRect.bottom - clientRect.top - 60,
				TRUE
			);
		}
			break;
		default:
			break;
		}
		break;

	case WM_SIZE:
	{
		RECT clientRect;
		GetClientRect(hwnd, &clientRect);
		SetWindowPos(
			GetDlgItem(hwnd, IDC_EDIT), HWND_TOP,
			clientRect.left + 30, clientRect.top + 30,
			clientRect.right - clientRect.left - 60, clientRect.bottom - clientRect.top - 60,
			SWP_SHOWWINDOW | SWP_NOZORDER
		);
	}
		break;
	case WM_DESTROY:
		FreeLibrary(hRichEdit20);
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

BOOL LoadTextFile(HWND hEdit, LPCSTR lpszFileName)
{
	BOOL bSuccess = FALSE;
	HANDLE hFile = CreateFile(lpszFileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, 0);

	if (hFile != INVALID_HANDLE_VALUE)
	{
		DWORD dwFileSize = GetFileSize(hFile, NULL);
		if (dwFileSize != UINT_MAX)
		{
			LPSTR lpszFileText = (LPSTR)GlobalAlloc(GPTR, dwFileSize + 1);
			if (lpszFileText)
			{
				DWORD dwRead = 0;
				if (ReadFile(hFile, lpszFileText, dwFileSize, &dwRead, NULL))
				{
					if (SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM)lpszFileText)) bSuccess = TRUE;
				}
				GlobalFree(lpszFileText);
			}
			CloseHandle(hFile);
		}
	}
	return bSuccess;
}

BOOL SaveTextFile(HWND hEdit, LPCSTR lpszFileName)
{
	BOOL bSuccess = FALSE;
	HANDLE hFile = CreateFile(lpszFileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hFile != INVALID_HANDLE_VALUE)
	{
		DWORD dwTextLen = SendMessage(hEdit, WM_GETTEXTLENGTH, 0, 0);
		if (dwTextLen)
		{
			LPSTR lpszText = (LPSTR)GlobalAlloc(GPTR, dwTextLen + 1);
			if (lpszText)
			{
				if (SendMessage(hEdit, WM_GETTEXT, dwTextLen + 1, (LPARAM)lpszText))
				{
					DWORD dwWrite;
					if (WriteFile(hFile, lpszText, dwTextLen, &dwWrite, NULL)) bSuccess = TRUE;
				}
				GlobalFree(lpszText);
			}
		}
		CloseHandle(hFile);
	}
	return bSuccess;
}
