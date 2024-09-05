#include<Windows.h>
#include<cstdio>
#include<limits>
#include<uxtheme.h>

#include "resource.h"
#include "Calculator.h"
#include <exception>

enum COLOR{ BLUE, GREEN };

CONST CHAR g_sz_WINDOW_CLASS[] = "Calc_PD_311";

CONST INT g_i_START_X = 10;
CONST INT g_i_START_Y = 10;
CONST INT g_i_TITLE_HEIGHT = 36;

CONST INT g_i_INTERVAL = 5;
CONST INT g_i_BUTTON_SIZE = 50;
CONST INT g_i_BUTTON_DOUBLE_SIZE = g_i_BUTTON_SIZE * 2 + g_i_INTERVAL;
CONST INT g_i_DISPLAY_WIDTH = (g_i_BUTTON_SIZE + g_i_INTERVAL) * 5;
CONST INT g_i_DISPLAY_HEIGHT = 25;
CONST INT g_i_WINDOW_WIDTH = g_i_DISPLAY_WIDTH + g_i_START_X * 2 + 16;
CONST INT g_i_WINDOW_HEIGHT = g_i_DISPLAY_HEIGHT + g_i_START_Y * 2 + g_i_BUTTON_SIZE * 4 + g_i_TITLE_HEIGHT + g_i_INTERVAL * 4 + 30;

CONST INT g_i_START_X_BUTTON = g_i_START_X;
CONST INT g_i_START_Y_BUTTON = g_i_START_Y * 2 + g_i_DISPLAY_HEIGHT;
CONST INT g_i_START_X_OPERATIONS = g_i_START_X_BUTTON + (g_i_BUTTON_SIZE + g_i_INTERVAL) * 3;
CONST INT g_i_START_X_CONTROL_BUTTONS = g_i_START_X_BUTTON + (g_i_BUTTON_SIZE + g_i_INTERVAL) * 4;

CONST COLORREF g_COLORS[][3] =
{
	{ RGB(0, 0, 200), RGB(0, 0, 100), RGB(255, 0, 0) },
	{ RGB(0, 200, 0), RGB(0, 100, 0), RGB(0, 255, 0) },
};

INT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
VOID SetSkin(HWND hwnd, LPSTR skinName);
VOID SetSkinFromDLL(HWND hwnd, LPSTR skinName);
BOOL CALLBACK SetFont(HWND hwnd, LPARAM font);
VOID SetFont(HWND hwnd, INT fontName);


INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{

	WNDCLASSEX wc;

	ZeroMemory(&wc, sizeof(wc));
	wc.style = 0;
	wc.cbSize = sizeof(wc);
	wc.cbWndExtra = 0;
	wc.cbClsExtra = 0;

	wc.hIcon = (HICON)LoadImage(hInstance, "resources\\calc.ico", IMAGE_ICON, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_LOADFROMFILE);
	wc.hIconSm = (HICON)LoadImage(hInstance, "resources\\calc.ico", IMAGE_ICON, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_LOADFROMFILE);
	wc.hCursor = (HCURSOR)LoadCursor(hInstance, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;

	wc.hInstance = hInstance;
	wc.lpszClassName = g_sz_WINDOW_CLASS;
	wc.lpszMenuName = NULL;
	wc.lpfnWndProc = (WNDPROC)WndProc;

	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, "Class Registration failed", "Error", MB_OK | MB_ICONERROR);
		return 0;
	}

	HMENU hMenuBar = CreateMenu();
	HMENU hMenuTheme = CreateMenu();

	AppendMenu(hMenuTheme, MF_STRING, IDM_THEME_DEFAULT, "Default");
	AppendMenu(hMenuTheme, MF_STRING, IDM_THEME_BLUE, "Blue");

	AppendMenu(hMenuBar, MF_POPUP, (UINT_PTR)hMenuTheme, "Themes");

	// window pos
	int posX = (GetSystemMetrics(SM_CXSCREEN) - g_i_WINDOW_WIDTH) / 2;
	int posY = (GetSystemMetrics(SM_CYSCREEN) - g_i_WINDOW_HEIGHT) / 2;

	HWND hwnd = CreateWindowEx(
		NULL,
		g_sz_WINDOW_CLASS,
		g_sz_WINDOW_CLASS,
		WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME ^ WS_MAXIMIZEBOX,
		posX, posY,
		g_i_WINDOW_WIDTH, g_i_WINDOW_HEIGHT,
		NULL,
		hMenuBar,
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

	return 0;
}

INT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static CONST CHAR skin[MAX_PATH]{};
	static COLOR colorScheme = COLOR::BLUE;

	switch (uMsg)
	{
	case WM_CREATE:
	{
		HWND hDisplay = CreateWindowEx
		(
			NULL, "Edit", "0",
			WS_CHILD | WS_VISIBLE | WS_BORDER | ES_NUMBER /*| ES_READONLY*/ | ES_RIGHT,
			g_i_START_X, g_i_START_Y,
			g_i_DISPLAY_WIDTH, g_i_DISPLAY_HEIGHT,
			hwnd, (HMENU)IDC_EDIT_DISPLAY,
			NULL, NULL
		);

		// buttons
		INT digit = 0;
		CHAR szDigit[2]{};

		for (int i = 2; i >= 0; i--)
		{
			for (int j = 0; j < 3; j++)
			{
				szDigit[0] = '1' + digit;
				CreateWindowEx
				(
					NULL, "Button", szDigit,
					WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_BITMAP,
					g_i_START_X_BUTTON + j * (g_i_BUTTON_SIZE + g_i_INTERVAL),
					g_i_START_Y_BUTTON + i * (g_i_BUTTON_SIZE + g_i_INTERVAL),
					g_i_BUTTON_SIZE, g_i_BUTTON_SIZE,
					hwnd, (HMENU)(IDC_BUTTON_1 + digit++),
					NULL, NULL
				);
			}
		}

		CreateWindowEx
		(
			NULL, "Button", "0",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_BITMAP,
			g_i_START_X_BUTTON,
			g_i_START_Y_BUTTON + (g_i_BUTTON_SIZE + g_i_INTERVAL) * 3,
			g_i_BUTTON_DOUBLE_SIZE, g_i_BUTTON_SIZE,
			hwnd, (HMENU)IDC_BUTTON_0,
			NULL, NULL
		);
		//DWORD dwErrorMsgID = GetLastError(); // ID of last exception
		//LPSTR lpszMsgBuffer = NULL;
		//DWORD dwSize = FormatMessage
		//(
		//	FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		//	NULL, dwErrorMsgID,
		//	MAKELANGID(LANG_NEUTRAL, SUBLANG_RUSSIAN_RUSSIA),
		//	(LPSTR)&lpszMsgBuffer,
		//	0, NULL
		//);
		//MessageBox(hwnd, lpszMsgBuffer, "Error", MB_OK | MB_ICONERROR);

		CreateWindowEx
		(
			NULL, "Button", ".",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_BITMAP,
			g_i_START_X_BUTTON + g_i_BUTTON_DOUBLE_SIZE + g_i_INTERVAL,
			g_i_START_Y_BUTTON + (g_i_BUTTON_SIZE + g_i_INTERVAL) * 3,
			g_i_BUTTON_SIZE, g_i_BUTTON_SIZE,
			hwnd, (HMENU)IDC_BUTTON_POINT,
			NULL, NULL
		);

		// operations
		CONST CHAR operations[5] = "+-*/";
		CHAR operation[2]{};

		for (size_t i = 0; i < 4; i++)
		{
			operation[0] = operations[i];
			CreateWindowEx
			(
				NULL, "Button", (LPCSTR)operation,
				WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_BITMAP,
				g_i_START_X_OPERATIONS,
				g_i_START_Y_BUTTON + (g_i_BUTTON_SIZE + g_i_INTERVAL) * (3 - i),
				g_i_BUTTON_SIZE, g_i_BUTTON_SIZE,
				hwnd, (HMENU)(IDC_BUTTON_PLUS + i),
				NULL, NULL
			);
		}

		CreateWindowEx
		(
			NULL, "Button", "<-",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_BITMAP,
			g_i_START_X_CONTROL_BUTTONS, g_i_START_Y_BUTTON,
			g_i_BUTTON_SIZE, g_i_BUTTON_SIZE,
			hwnd, (HMENU)IDC_BUTTON_BSP,
			NULL, NULL
		);
		CreateWindowEx
		(
			NULL, "Button", "C",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_BITMAP,
			g_i_START_X_CONTROL_BUTTONS,
			g_i_START_Y_BUTTON + g_i_BUTTON_SIZE + g_i_INTERVAL,
			g_i_BUTTON_SIZE, g_i_BUTTON_SIZE,
			hwnd, (HMENU)IDC_BUTTON_CLEAR,
			NULL, NULL
		);

		CreateWindowEx
		(
			NULL, "Button", "=",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_BITMAP,
			g_i_START_X_CONTROL_BUTTONS, 
			g_i_START_Y_BUTTON + g_i_BUTTON_DOUBLE_SIZE + g_i_INTERVAL,
			g_i_BUTTON_SIZE, g_i_BUTTON_DOUBLE_SIZE,
			hwnd, (HMENU)IDC_BUTTON_EQUAL,
			NULL, NULL
		);

		SendMessage(hwnd, WM_COMMAND, LOWORD(IDM_THEME_DEFAULT), 0);
		SetFont(hwnd, CM_FONT_RAVIE);
	}
		break;

	case WM_COMMAND:
	{
		static DOUBLE iResult = DBL_MIN;
		static DOUBLE iOperand = DBL_MIN;
		static INT iOperation = 0;
		static BOOLEAN isResult = FALSE;
		static BOOLEAN isOperation = FALSE;

		SetFocus(hwnd);

		CONST INT SIZE = 256;
		CONST INT DIGIT_SIZE = 2;
		CHAR szDigit[DIGIT_SIZE]{};
		CHAR szBuffer[SIZE]{};
		CHAR szResult[SIZE]{};

		HWND hDisplay = GetDlgItem(hwnd, IDC_EDIT_DISPLAY);

		if (LOWORD(wParam) >= IDC_BUTTON_0 && LOWORD(wParam) <= IDC_BUTTON_POINT)
		{
			szDigit[0] = LOWORD(wParam) - IDC_BUTTON_0 + '0';
			isOperation = FALSE;

			if (isResult)
			{
				SendMessage(hDisplay, WM_SETTEXT, 0, (LPARAM)"0");
				isResult = FALSE;
			}
			SendMessage(hDisplay, WM_GETTEXT, SIZE, (LPARAM)szBuffer);
			if (LOWORD(wParam) == IDC_BUTTON_POINT)
			{
				if (strchr(szBuffer, '.')) break;
				strcat_s(szBuffer, SIZE, ".");
			}
			else
			{
				if (szBuffer[0] == '0' && strlen(szBuffer) == 1) szBuffer[0] = szDigit[0];
				else strcat_s(szBuffer, SIZE, szDigit);
			}
			SendMessage(hDisplay, WM_SETTEXT, 0, (LPARAM)szBuffer);
		}

		else if (LOWORD(wParam) >= IDC_BUTTON_PLUS && LOWORD(wParam) <= IDC_BUTTON_DIVIDE)
		{
			if (isOperation && iOperation != LOWORD(wParam)) iOperation = LOWORD(wParam);

			SendMessage(hwnd, WM_COMMAND, LOWORD(IDC_BUTTON_EQUAL), 0);
			iOperation = LOWORD(wParam);
		}

		else if (LOWORD(wParam) == IDC_BUTTON_EQUAL)
		{
			SendMessage(hDisplay, WM_GETTEXT, SIZE, (LPARAM)szBuffer);
			
			if (iResult == DBL_MIN)
			{
				iResult = Calculator::StringToDouble(szBuffer);
				isResult = TRUE;
			}
			else if (!isOperation) iOperand = Calculator::StringToDouble(szBuffer);

			if (iOperation != 0)
			{
				switch (iOperation)
				{
				case IDC_BUTTON_PLUS: iResult = Calculator::Add(iResult, iOperand); break;
				case IDC_BUTTON_MINUS: iResult = Calculator::Substract(iResult, iOperand); break;
				case IDC_BUTTON_MULTIPLY: iResult = Calculator::Multiply(iResult, iOperand); break;
				case IDC_BUTTON_DIVIDE: iResult = Calculator::Divide(iResult, iOperand); break;
				default: break;
				}

				Calculator::DoubleToString(iResult, szBuffer);
				SendMessage(hDisplay, WM_SETTEXT, SIZE, (LPARAM)szBuffer);
				isResult = TRUE;
				isOperation = TRUE;
			}

		}

		else if (LOWORD(wParam) == IDC_BUTTON_BSP)
		{
			SendMessage(hDisplay, WM_GETTEXT, SIZE, (LPARAM)szBuffer);
			INT bufferLen = strlen(szBuffer);
			if (bufferLen) szBuffer[--bufferLen] = 0;
			if (bufferLen == 0) szBuffer[0] = '0';
			SendMessage(hDisplay, WM_SETTEXT, 0, (LPARAM)szBuffer);
		}

		else if (LOWORD(wParam) == IDC_BUTTON_CLEAR)
		{
			SendMessage(hDisplay, WM_SETTEXT, 0, (LPARAM)"0");
			iResult = DBL_MIN;
			iOperand = DBL_MIN;
			isResult = FALSE;
		}

		else if (LOWORD(wParam) >= IDM_THEME_DEFAULT && LOWORD(wParam) <= IDM_THEME_BLUE)
		{
			//SendMessage(hwnd, WM_THEMECHANGED, 0, 0);
			//CloseThemeData();
			LPSTR themeName = NULL;

			switch (LOWORD(wParam))
			{
			case IDM_THEME_DEFAULT:
				themeName = (LPSTR)"themeGreen";
				break;
			case IDM_THEME_BLUE:
			{
				themeName = (LPSTR)"themeBlue";
				HDC hdc = GetDC(hwnd);
				SendMessage(hwnd, WM_CTLCOLOREDIT, (WPARAM)hdc, 0);
				SendMessage(hwnd, WM_CTLCOLOREDIT, (WPARAM)GetDC(GetDlgItem(hwnd, IDC_EDIT_DISPLAY)), 0);
				ReleaseDC(hwnd, hdc);
			}
				break;
			default:
				break;
			}
			SetSkinFromDLL(hwnd, themeName);
		}
	}
		break;

	case WM_KEYUP:
	{
		if (GetKeyState(VK_SHIFT) < 0 && LOWORD(wParam) == 0x38)
		{
			SendMessage(GetDlgItem(hwnd, LOWORD(IDC_BUTTON_MULTIPLY)), BM_SETSTATE, FALSE, 0);
			SendMessage(hwnd, WM_COMMAND, LOWORD(IDC_BUTTON_MULTIPLY), 0);
		}
		else if (LOWORD(wParam) >= 0x30 && LOWORD(wParam) <= 0x39)
		{
			SendMessage(GetDlgItem(hwnd, LOWORD(wParam - 0x30 + IDC_BUTTON_0)), BM_SETSTATE, FALSE, 0);
			SendMessage(hwnd, WM_COMMAND, LOWORD(wParam - 0x30 + IDC_BUTTON_0), 0);
		}
		else if (LOWORD(wParam) >= 0x60 && LOWORD(wParam) <= 0x69)
		{
			SendMessage(GetDlgItem(hwnd, LOWORD(wParam - 0x69 + IDC_BUTTON_0)), BM_SETSTATE, FALSE, 0);
			SendMessage(hwnd, WM_COMMAND, LOWORD(wParam - 0x69 + IDC_BUTTON_0), 0);
		}
		else
		{
			switch (LOWORD(wParam))
			{
			case VK_OEM_PERIOD:
			case VK_DECIMAL:
				SendMessage(GetDlgItem(hwnd, LOWORD(IDC_BUTTON_POINT)), BM_SETSTATE, FALSE, 0);
				SendMessage(hwnd, WM_COMMAND, LOWORD(IDC_BUTTON_POINT), 0);
				break;
			case VK_OEM_PLUS:
			case VK_ADD:
				SendMessage(GetDlgItem(hwnd, LOWORD(IDC_BUTTON_PLUS)), BM_SETSTATE, FALSE, 0);
				SendMessage(hwnd, WM_COMMAND, LOWORD(IDC_BUTTON_PLUS), 0);
				break;
			case VK_OEM_MINUS:
			case VK_SUBTRACT:
				SendMessage(GetDlgItem(hwnd, LOWORD(IDC_BUTTON_MINUS)), BM_SETSTATE, FALSE, 0);
				SendMessage(hwnd, WM_COMMAND, LOWORD(IDC_BUTTON_MINUS), 0);
				break;
			case VK_MULTIPLY:
				SendMessage(GetDlgItem(hwnd, LOWORD(IDC_BUTTON_MULTIPLY)), BM_SETSTATE, FALSE, 0);
				SendMessage(hwnd, WM_COMMAND, LOWORD(IDC_BUTTON_MULTIPLY), 0);
				break;
			case VK_DIVIDE:
			case VK_OEM_2:
				SendMessage(GetDlgItem(hwnd, LOWORD(IDC_BUTTON_DIVIDE)), BM_SETSTATE, FALSE, 0);
				SendMessage(hwnd, WM_COMMAND, LOWORD(IDC_BUTTON_DIVIDE), 0);
				break;
			case VK_BACK:
				SendMessage(GetDlgItem(hwnd, LOWORD(IDC_BUTTON_BSP)), BM_SETSTATE, FALSE, 0);
				SendMessage(hwnd, WM_COMMAND, LOWORD(IDC_BUTTON_BSP), 0);
				break;
			case VK_RETURN:
				SendMessage(GetDlgItem(hwnd, LOWORD(IDC_BUTTON_EQUAL)), BM_SETSTATE, FALSE, 0);
				SendMessage(hwnd, WM_COMMAND, LOWORD(IDC_BUTTON_EQUAL), 0);
				break;
			case VK_ESCAPE:
				SendMessage(GetDlgItem(hwnd, LOWORD(IDC_BUTTON_CLEAR)), BM_SETSTATE, FALSE, 0);
				SendMessage(hwnd, WM_COMMAND, LOWORD(IDC_BUTTON_CLEAR), 0);
				break;
			default: break;
			}
		}
	}
		break;

	case WM_KEYDOWN:
	{
		if (GetKeyState(VK_SHIFT) < 0 && LOWORD(wParam) == 0x38)
		{
			SendMessage(GetDlgItem(hwnd, LOWORD(IDC_BUTTON_MULTIPLY)), BM_SETSTATE, TRUE, 0);
		}
		else if (LOWORD(wParam) >= 0x30 && LOWORD(wParam) <= 0x39)
		{
			SendMessage(GetDlgItem(hwnd, LOWORD(wParam - 0x30 + IDC_BUTTON_0)), BM_SETSTATE, TRUE, 0);
		}
		else if (LOWORD(wParam) >= 0x60 && LOWORD(wParam) <= 0x69)
		{
			SendMessage(GetDlgItem(hwnd, LOWORD(wParam - 0x69 + IDC_BUTTON_0)), BM_SETSTATE, TRUE, 0);
		}
		else
		{
			switch (LOWORD(wParam))
			{
			case VK_DECIMAL:
			case VK_OEM_PERIOD:
				SendMessage(GetDlgItem(hwnd, LOWORD(IDC_BUTTON_POINT)), BM_SETSTATE, TRUE, 0);
				break;
			case VK_OEM_PLUS:
			case VK_ADD:
				SendMessage(GetDlgItem(hwnd, LOWORD(IDC_BUTTON_PLUS)), BM_SETSTATE, TRUE, 0);
				break;
			case VK_OEM_MINUS:
			case VK_SUBTRACT:
				SendMessage(GetDlgItem(hwnd, LOWORD(IDC_BUTTON_MINUS)), BM_SETSTATE, TRUE, 0);
				break;
			case VK_OEM_2:
			case VK_DIVIDE:
				SendMessage(GetDlgItem(hwnd, LOWORD(IDC_BUTTON_DIVIDE)), BM_SETSTATE, TRUE, 0);
				break;
			case VK_MULTIPLY: SendMessage(GetDlgItem(hwnd, LOWORD(IDC_BUTTON_MULTIPLY)), BM_SETSTATE, TRUE, 0); break;
			case VK_BACK: SendMessage(GetDlgItem(hwnd, LOWORD(IDC_BUTTON_BSP)), BM_SETSTATE, TRUE, 0); break;
			case VK_RETURN: SendMessage(GetDlgItem(hwnd, LOWORD(IDC_BUTTON_EQUAL)), BM_SETSTATE, TRUE, 0); break;
			case VK_ESCAPE: SendMessage(GetDlgItem(hwnd, LOWORD(IDC_BUTTON_CLEAR)), BM_SETSTATE, TRUE, 0); break;
			default: break;
			}
		}
	}
		break;

	case WM_CTLCOLOREDIT:
	{
		HDC hdc = (HDC)wParam;
		SetBkMode(hdc, OPAQUE);
		SetBkColor(hdc, RGB(0, 0, 255));
		HBRUSH hBrush = CreateSolidBrush(RGB(0, 0, 200));
		SetTextColor(hdc, RGB(255, 0, 0));

		SetClassLongPtr(hwnd, GCLP_HBRBACKGROUND, (LONG_PTR)hBrush);
		//SendMessage(hwnd, WM_ERASEBKGND, wParam, 0);
		//SendMessage(GetDlgItem(hwnd, IDC_EDIT_DISPLAY), WM_SETTEXT, 0, (LPARAM)"0");

		return (LRESULT)hBrush;
	}

	case WM_CONTEXTMENU:
	{
		HMENU hMainMenu = CreatePopupMenu();
		HMENU hThemeSubMenu = CreatePopupMenu();
		HMENU hFontSubMenu = CreatePopupMenu();

		InsertMenu(hMainMenu, 0, MF_BYPOSITION | MF_STRING, CM_EXIT, "Exit");
		InsertMenu(hMainMenu, 0, MF_BYPOSITION | MF_SEPARATOR, 0, NULL);
		InsertMenu(hMainMenu, 0, MF_BYPOSITION | MF_POPUP, (UINT_PTR)hThemeSubMenu, "Skins");
		InsertMenu(hMainMenu, 0, MF_BYPOSITION | MF_POPUP, (UINT_PTR)hFontSubMenu, "Fonts");
		InsertMenu(hThemeSubMenu, 0, MF_BYPOSITION | MF_STRING, CM_THEME_GREEN, "Green");
		InsertMenu(hThemeSubMenu, 0, MF_BYPOSITION | MF_STRING, CM_THEME_BLUE, "Blue");
		InsertMenu(hFontSubMenu, 0, MF_BYPOSITION | MF_STRING, CM_FONT_DIGITAL7, "Digital-7");
		InsertMenu(hFontSubMenu, 0, MF_BYPOSITION | MF_STRING, CM_FONT_RAVIE, "Ravie");

		BOOL item = TrackPopupMenuEx(hMainMenu, TPM_BOTTOMALIGN | TPM_LEFTALIGN | TPM_RETURNCMD, LOWORD(lParam), HIWORD(lParam), hwnd, NULL);

		switch (item)
		{
		case CM_THEME_BLUE: SendMessage(hwnd, WM_COMMAND, LOWORD(IDM_THEME_BLUE), 0); break;
		case CM_THEME_GREEN: SendMessage(hwnd, WM_COMMAND, LOWORD(IDM_THEME_DEFAULT), 0); break;
		case CM_FONT_DIGITAL7: SetFont(hwnd, CM_FONT_DIGITAL7); break;
		case CM_FONT_RAVIE: SetFont(hwnd, CM_FONT_RAVIE); break;
		case CM_EXIT: SendMessage(hwnd, WM_CLOSE, 0, 0); break;
		default: break;
		}
	}
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;

	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return 0;
}

VOID SetSkin(HWND hwnd, LPSTR skinName)
{
	CHAR szFile[MAX_PATH]{};
	HWND hButton;
	for (size_t i = IDC_BUTTON_0; i <= IDC_BUTTON_9; i++)
	{
		hButton = GetDlgItem(hwnd, i);
		sprintf_s(szFile, MAX_PATH, "resources\\%s\\button_%i.bmp", skinName, i - IDC_BUTTON_0);
		HANDLE hImage = LoadImage(
			GetModuleHandle(NULL), szFile, IMAGE_BITMAP,
			i == IDC_BUTTON_0 ? g_i_BUTTON_DOUBLE_SIZE : g_i_BUTTON_SIZE,
			g_i_BUTTON_SIZE,
			LR_LOADFROMFILE
		);
		SendMessage(hButton, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hImage);
	}
}

VOID SetSkinFromDLL(HWND hwnd, LPSTR skinName)
{
	HWND hButton;
	HINSTANCE hButtons;

	if (skinName == "themeBlue") hButtons = LoadLibrary("resources/SkinBlue.dll");
	else hButtons = LoadLibrary("resources/SkinGreen.dll");

	for (size_t i = 0; i <= 17; i++)
	{
		hButton = GetDlgItem(hwnd, i + 1000);
		HBITMAP hImage = (HBITMAP)LoadImage(
			hButtons, MAKEINTRESOURCE(100 + i), IMAGE_BITMAP,
			i == (IDC_BUTTON_0 - 1000) ? g_i_BUTTON_DOUBLE_SIZE : g_i_BUTTON_SIZE,
			i == (IDC_BUTTON_EQUAL - 1000) ? g_i_BUTTON_DOUBLE_SIZE : g_i_BUTTON_SIZE,
			LR_SHARED
		);
		SendMessage(hButton, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hImage);
	}
	FreeLibrary(hButtons);
}

VOID SetFont(HWND hwnd, INT fontName)
{
	HFONT font;
	HDC hdc = GetDC(NULL);
	LONG fontHeight = -MulDiv(12, GetDeviceCaps(hdc, LOGPIXELSY), 72);
	ReleaseDC(NULL, hdc);


	if (fontName == CM_FONT_DIGITAL7)
	{
		AddFontResourceEx("resources\\digital-7.ttf", FR_PRIVATE, 0);
		font = CreateFont(fontHeight, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, "digital-7");
	}
	else
	{
		font = CreateFont(fontHeight, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, "Ravie");
	}
	if (!font) MessageBox(hwnd, "Font creation failed!", "Error", MB_OK | MB_ICONEXCLAMATION);

	EnumChildWindows(hwnd, (WNDENUMPROC)SetFont, (LPARAM)font);
}

BOOL CALLBACK SetFont(HWND hwnd, LPARAM font)
{
	SendMessage(hwnd, WM_SETFONT, font, TRUE);
	return TRUE;
}
