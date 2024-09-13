#define _CRT_SECURE_NO_WARNINGS
#undef UNICODE
#include<Windows.h>
#include<Richedit.h>
#include<CommCtrl.h>
#include<iostream>
#include"resource.h"

//#define CONSOLE_DEBUG

using std::cout;
using std::endl;

CONST CHAR g_sz_WINDOW_CLASS[] = "TextEditor_PD311";
CONST INT g_SIZE = 256;

CONST DWORD g_dw_INDENT = 30;

BOOL CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
CHAR* FormatLastError();
INT GetWordCount(HWND hEdit);
BOOL LoadTextFile(HWND hwnd, LPCSTR lpszFileName);
BOOL SaveTextFile(HWND hwnd, LPCSTR lpszFileName);
BOOL ModifyWindowName(HWND hwnd, BOOL isSaved, BOOL isAster);
BOOL SetFileInfoToStatusBar(HWND hwnd, LPCSTR lpszFileName);
VOID FormatFileTime(FILETIME fileTime, CHAR szBuffer[], CONST CHAR szMessage[]);
VOID SetWindowName(HWND hwnd, CHAR fileName[]);
VOID SetStatusBarDimensions(HWND hStatus, INT winWidth);
VOID SetStatusBar(HWND hStatus, CHAR filePath[]);
VOID SetStatusBarOnChange(HWND hwnd);
VOID SetStatusBarWindowSize(HWND hStatus, INT winWidth, INT winHeight);


INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
#ifdef CONSOLE_DEBUG
	AllocConsole();
	freopen("CONOUT$", "w", stdout);
	setlocale(LC_ALL, "");
	system("chcp 1251");
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
	static HINSTANCE hCommCtrl32 = LoadLibrary("ComCtrl32.dll");

	static CHAR szFileName[MAX_PATH]{};
	static CHAR szTitle[MAX_PATH]{};
	static DWORD statusHeight;

	static BOOL isWordWrap = TRUE;
	static BOOL isSaved = TRUE;
	static BOOL isAster = FALSE;

	switch (uMsg)
	{
	case WM_CREATE:
	{
		RECT clientRect;
		GetClientRect(hwnd, &clientRect);
		INT winHeight = clientRect.bottom - clientRect.top;
		INT winWidth = clientRect.right - clientRect.left;

		// status bar creation
		HWND hStatus = CreateWindowEx(
			NULL, STATUSCLASSNAME, "None",
			WS_CHILD | WS_VISIBLE,
			0, 0, 0, 0,
			hwnd, (HMENU)IDC_STATUSBAR,
			NULL, NULL
		);

		RECT statusRect;
		GetClientRect(hStatus, &statusRect);
		statusHeight = statusRect.bottom - statusRect.top;
		SetStatusBarDimensions(hStatus, winWidth);
		SetStatusBar(hwnd, (CHAR*)"None");
		SetStatusBarWindowSize(hStatus, winWidth, winHeight);

		// edit control edition
		HWND hEdit = CreateWindowEx
		(
			NULL, RICHEDIT_CLASS, "",
			WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_MULTILINE | ES_LEFT | ES_AUTOVSCROLL,
			g_dw_INDENT, g_dw_INDENT,
			winWidth - g_dw_INDENT * 2, winHeight - (g_dw_INDENT * 2 + statusHeight),
			hwnd, (HMENU)IDC_EDIT,
			NULL, NULL
		);
		SendMessage(hEdit, EM_SETEVENTMASK, 0, ENM_CHANGE);
	}
		break;
	case WM_COMMAND:
		if (HIWORD(wParam) == EN_CHANGE)
		{
			isSaved = FALSE;
			isAster = ModifyWindowName(hwnd, isSaved, isAster);
			SetStatusBarOnChange(hwnd);
			break;
		}
		switch (LOWORD(wParam))
		{
		case ID_FILE_OPEN:
		{
			BOOLEAN isCancel = FALSE;
			if (!isSaved)
			{
				switch (MessageBox(hwnd, "Сохранить файл?", "Файл был изменен", MB_YESNOCANCEL | MB_ICONQUESTION))
				{
				case IDOK: SendMessage(hwnd, WM_COMMAND, ID_FILE_SAVE, 0); break;
				case IDNO: break;
				case IDCANCEL: isCancel = TRUE; break;
				default: break;
				}
			}
			if (isCancel) break;

			OPENFILENAME ofn;
			ZeroMemory(&ofn, sizeof(ofn));
			ofn.lStructSize = sizeof(ofn);
			ofn.hwndOwner = hwnd;
			ofn.lpstrFilter = "Text files: (*.txt)\0*.txt\0C++ files: (*.cpp, *.h)\0*.cpp;*.h\0All files (*.*)\0*.*\0";
			ofn.lpstrDefExt = "txt";
			ofn.nMaxFile = MAX_PATH;
			ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
			ofn.lpstrFile = szFileName;

			if (GetOpenFileName(&ofn))
			{
				LoadTextFile(hwnd, szFileName);
				SetFileInfoToStatusBar(hwnd, szFileName);
				SetStatusBar(hwnd, ofn.lpstrFile);
				SetWindowName(hwnd, szFileName);
				isSaved = TRUE;
				isAster = FALSE;
			}
		}
			break;
		case ID_FILE_SAVE:
			if (strlen(szFileName))
			{
				SaveTextFile(hwnd, szFileName);
				SetFileInfoToStatusBar(hwnd, szFileName);
				isSaved = TRUE;
				isAster = ModifyWindowName(hwnd, isSaved, isAster);
			}
			else SendMessage(hwnd, WM_COMMAND, ID_FILE_SAVEAS, 0);
			break;
		case ID_FILE_SAVEAS:
		{
			OPENFILENAME ofn;
			ZeroMemory(&ofn, sizeof(ofn));
			ofn.lStructSize = sizeof(ofn);
			ofn.hwndOwner = hwnd;
			ofn.lpstrFilter = "Text files: (*.txt)\0*.txt\0C++ files: (*.cpp, *.h)\0*.cpp;*.h\0All files (*.*)\0*.*\0";
			ofn.lpstrDefExt = "txt";
			ofn.nMaxFile = MAX_PATH;
			ofn.Flags = OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;
			ofn.lpstrFile = szFileName;

			if (GetSaveFileName(&ofn))
			{
				SaveTextFile(hwnd, szFileName);
				SetFileInfoToStatusBar(hwnd, szFileName);
				isSaved = TRUE;
				isAster = ModifyWindowName(hwnd, isSaved, isAster);
				SetStatusBar(hwnd, ofn.lpstrFile);
				SetWindowName(hwnd, szFileName);
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
			InvalidateRect(hEdit, NULL, TRUE);
			UpdateWindow(hwnd);
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
		INT winWidth = clientRect.right - clientRect.left;
		INT winHeight = clientRect.bottom - clientRect.top;
		HWND hStatus = GetDlgItem(hwnd, IDC_STATUSBAR);

		SetWindowPos(
			GetDlgItem(hwnd, IDC_EDIT), HWND_TOP,
			clientRect.left + g_dw_INDENT, clientRect.top + g_dw_INDENT,
			winWidth - g_dw_INDENT * 2,
			winHeight - (g_dw_INDENT * 2 + statusHeight),
			SWP_SHOWWINDOW | SWP_NOZORDER
		);
		SetStatusBarDimensions(hStatus, winWidth);
		MoveWindow(hStatus, 0, 0, 0, 0 , TRUE);
		SetStatusBarWindowSize(hStatus, winWidth, winHeight);
	}
		break;
	case WM_DESTROY:
		FreeLibrary(hRichEdit20);
		FreeLibrary(hCommCtrl32);
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

BOOL LoadTextFile(HWND hwnd, LPCSTR lpszFileName)
{
	HWND hEdit = GetDlgItem(hwnd, IDC_EDIT);
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

BOOL SaveTextFile(HWND hwnd, LPCSTR lpszFileName)
{
	HWND hEdit = GetDlgItem(hwnd, IDC_EDIT);
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

BOOL SetFileInfoToStatusBar(HWND hwnd, LPCSTR lpszFileName)
{
	BOOL bSuccess = FALSE;
	HWND hStatus = GetDlgItem(hwnd, IDC_STATUSBAR);
	SYSTEMTIME sysTime;
	CHAR szBuffer[g_SIZE]{};
	WIN32_FILE_ATTRIBUTE_DATA fData;

	ZeroMemory(&fData, sizeof(fData));
	ZeroMemory(&szBuffer, sizeof(szBuffer));
	ZeroMemory(&sysTime, sizeof(sysTime));
	if (GetFileAttributesEx(lpszFileName, GetFileExInfoStandard, &fData))
	{
		sprintf(szBuffer, "Размер: %i байт", fData.nFileSizeLow);
		SendMessage(hStatus, SB_SETTEXT, 4, (LPARAM)szBuffer);

		FormatFileTime(fData.ftCreationTime, szBuffer, "Создан");
		SendMessage(hStatus, SB_SETTEXT, 5, (LPARAM)szBuffer);

		FormatFileTime(fData.ftLastWriteTime, szBuffer, "Изменен");
		SendMessage(hStatus, SB_SETTEXT, 6, (LPARAM)szBuffer);
	}
	return bSuccess;
}

VOID FormatFileTime(FILETIME fileTime, CHAR szBuffer[], CONST CHAR szMessage[])
{
	SYSTEMTIME sysTime;
	ZeroMemory(&sysTime, sizeof(sysTime));
	FILETIME localTime;
	ZeroMemory(&localTime, sizeof(localTime));

	FileTimeToLocalFileTime(&fileTime, &localTime);
	FileTimeToSystemTime(&localTime, &sysTime);
	sprintf(szBuffer, "%s: %02d:%02d %02d.%02d.%02d", szMessage, sysTime.wHour, sysTime.wMinute, sysTime.wDay, sysTime.wMonth, sysTime.wYear);
}

BOOL ModifyWindowName(HWND hwnd, BOOL isSaved, BOOL isAster)
{
	if (isSaved == isAster)
	{
		CHAR winName[g_SIZE]{};
		SendMessage(hwnd, WM_GETTEXT, g_SIZE, (LPARAM)winName);
		if (!isSaved)
		{
			strcat_s(winName, g_SIZE, "*");
			SendMessage(hwnd, WM_SETTEXT, 0, (LPARAM)winName);
			return TRUE;
		}
		else if (isSaved)
		{
			winName[strlen(winName) - 1] = '\0';
			SendMessage(hwnd, WM_SETTEXT, 0, (LPARAM)winName);
			return FALSE;
		}
	}
	return isAster;
}

VOID SetWindowName(HWND hwnd, CHAR fileName[])
{
	CHAR szBuffer[g_SIZE]{};
	sprintf(szBuffer, "%s - %s", g_sz_WINDOW_CLASS, strchr(fileName, '\\') + 1);
	SendMessage(hwnd, WM_SETTEXT, 0, (LPARAM)szBuffer);
}

VOID SetStatusBarDimensions(HWND hStatus, INT winWidth)
{
	INT elemPos[] = { winWidth * 0.35, winWidth * 0.4, winWidth * 0.51, winWidth * 0.58, winWidth * 0.7, winWidth * 0.85, -1 };
	SendMessage(hStatus, SB_SETPARTS, sizeof(elemPos) / sizeof(elemPos[0]), (LPARAM)elemPos);
}

VOID SetStatusBar(HWND hwnd, CHAR filePath[])
{
	CHAR szBuffer[g_SIZE]{};
	HWND hStatus = GetDlgItem(hwnd, IDC_STATUSBAR);
	SendMessage(hStatus, SB_SETTEXT, 0, (LPARAM)filePath);
	SendMessage(hStatus, SB_SETTEXT, 1, (LPARAM)"Сохранен");

	sprintf(szBuffer, "Количество слов: %i", GetWordCount(GetDlgItem(hwnd, IDC_EDIT)));
	SendMessage(hStatus, SB_SETTEXT, 2, (LPARAM)szBuffer);
}

VOID SetStatusBarOnChange(HWND hwnd)
{
	HWND hStatus = GetDlgItem(hwnd, IDC_STATUSBAR);
	CHAR szBuffer[g_SIZE]{};

	SendMessage(hStatus, SB_SETTEXT, 1, (LPARAM)"Изменен");
	sprintf(szBuffer, "Количество слов: %i", GetWordCount(GetDlgItem(hwnd, IDC_EDIT)));
	SendMessage(hStatus, SB_SETTEXT, 2, (LPARAM)szBuffer);
}

VOID SetStatusBarWindowSize(HWND hStatus, INT winWidth, INT winHeight)
{
	CHAR szBuffer[g_SIZE]{};
	sprintf(szBuffer, "%i x %i", winWidth, winHeight);
	SendMessage(hStatus, SB_SETTEXT, 3, (LPARAM)szBuffer);
}

INT GetWordCount(HWND hEdit)
{
	DWORD dwTextLen = SendMessage(hEdit, WM_GETTEXTLENGTH, 0, 0);
	LPSTR lpstrBuffer = (LPSTR)GlobalAlloc(GPTR, dwTextLen + 1);
	SendMessage(hEdit, WM_GETTEXT, dwTextLen + 1, (LPARAM)lpstrBuffer);
	const CHAR delimiters[] = " ,.!?;-()[]<>{}:/\"\'\\\n";
	INT count = 0;
	for (char* pch = strtok(lpstrBuffer, delimiters); pch; pch = strtok(NULL, delimiters)) count++;
	GlobalFree(lpstrBuffer);
	return count;
}
