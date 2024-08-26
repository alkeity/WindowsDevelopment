#include<Windows.h>
#include<cstdio>

#include "resource.h"
#include "Calculator.h"

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
CONST INT g_i_WINDOW_HEIGHT = g_i_DISPLAY_HEIGHT + g_i_START_Y * 2 + g_i_BUTTON_SIZE * 4 + g_i_TITLE_HEIGHT + g_i_INTERVAL * 5;

CONST INT g_i_START_X_BUTTON = g_i_START_X;
CONST INT g_i_START_Y_BUTTON = g_i_START_Y * 2 + g_i_DISPLAY_HEIGHT;
CONST INT g_i_START_X_OPERATIONS = g_i_START_X_BUTTON + (g_i_BUTTON_SIZE + g_i_INTERVAL) * 3;
CONST INT g_i_START_X_CONTROL_BUTTONS = g_i_START_X_BUTTON + (g_i_BUTTON_SIZE + g_i_INTERVAL) * 4;

DOUBLE iResult = NULL;
BOOLEAN isResult = FALSE;

INT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	WNDCLASSEX wc;

	ZeroMemory(&wc, sizeof(wc));
	wc.style = 0;
	wc.cbSize = sizeof(wc);
	wc.cbWndExtra = 0;
	wc.cbClsExtra = 0;

	wc.hIcon = (HICON)LoadImage(hInstance, "icons\\calc.ico", IMAGE_ICON, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_LOADFROMFILE);
	wc.hIconSm = (HICON)LoadImage(hInstance, "icons\\calc.ico", IMAGE_ICON, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_LOADFROMFILE);
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

	HWND hwnd = CreateWindowEx(
		NULL,
		g_sz_WINDOW_CLASS,
		g_sz_WINDOW_CLASS,
		WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME ^ WS_MAXIMIZEBOX,
		CW_USEDEFAULT, CW_USEDEFAULT,
		g_i_WINDOW_WIDTH, g_i_WINDOW_HEIGHT,
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

	return 0;
}

INT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:
	{
		HWND hDisplay = CreateWindowEx
		(
			NULL, "Edit", "0",
			WS_CHILD | WS_VISIBLE | WS_BORDER | ES_NUMBER | ES_READONLY | ES_RIGHT,
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
					WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
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
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			g_i_START_X_BUTTON,
			g_i_START_Y_BUTTON + (g_i_BUTTON_SIZE + g_i_INTERVAL) * 3,
			g_i_BUTTON_DOUBLE_SIZE, g_i_BUTTON_SIZE,
			hwnd, (HMENU)IDC_BUTTON_0,
			NULL, NULL
		);

		CreateWindowEx
		(
			NULL, "Button", ".",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
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
				WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
				g_i_START_X_OPERATIONS,
				g_i_START_Y_BUTTON + (g_i_BUTTON_SIZE + g_i_INTERVAL) * (3 - i),
				g_i_BUTTON_SIZE, g_i_BUTTON_SIZE,
				hwnd, (HMENU)(IDC_BUTTON_PLUS + i), // as usual, the mistake was very oblivious
				NULL, NULL
			);
		}

		CreateWindowEx
		(
			NULL, "Button", "<-",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			g_i_START_X_CONTROL_BUTTONS, g_i_START_Y_BUTTON,
			g_i_BUTTON_SIZE, g_i_BUTTON_SIZE,
			hwnd, (HMENU)IDC_BUTTON_BSP,
			NULL, NULL
		);
		CreateWindowEx
		(
			NULL, "Button", "C",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			g_i_START_X_CONTROL_BUTTONS,
			g_i_START_Y_BUTTON + g_i_BUTTON_SIZE + g_i_INTERVAL,
			g_i_BUTTON_SIZE, g_i_BUTTON_SIZE,
			hwnd, (HMENU)IDC_BUTTON_CLEAR,
			NULL, NULL
		);

		CreateWindowEx
		(
			NULL, "Button", "=",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			g_i_START_X_CONTROL_BUTTONS, 
			g_i_START_Y_BUTTON + g_i_BUTTON_DOUBLE_SIZE + g_i_INTERVAL,
			g_i_BUTTON_SIZE, g_i_BUTTON_DOUBLE_SIZE,
			hwnd, (HMENU)IDC_BUTTON_EQUAL,
			NULL, NULL
		);
	}
		break;

	case WM_COMMAND:
	{
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

		if (LOWORD(wParam) >= IDC_BUTTON_PLUS && LOWORD(wParam) <= IDC_BUTTON_DIVIDE)
		{
			SendMessage(hDisplay, WM_GETTEXT, SIZE, (LPARAM)szBuffer);
			isResult = TRUE;
			iResult = Calculator::StringToDouble(szBuffer);
		}

		if (LOWORD(wParam) == IDC_BUTTON_EQUAL)
		{
			//
		}

		if (LOWORD(wParam) == IDC_BUTTON_BSP)
		{
			SendMessage(hDisplay, WM_GETTEXT, SIZE, (LPARAM)szBuffer);
			INT bufferLen = strlen(szBuffer);
			if (bufferLen)
				szBuffer[--bufferLen] = 0;
			if (bufferLen == 0) szBuffer[0] = '0';
			SendMessage(hDisplay, WM_SETTEXT, 0, (LPARAM)szBuffer);
		}

		if (LOWORD(wParam) == IDC_BUTTON_CLEAR)
		{
			SendMessage(hDisplay, WM_SETTEXT, 0, (LPARAM)"0");
		}
	}
		break;

	case WM_KEYDOWN:
	{
		if (LOWORD(wParam) >= 0x30 && LOWORD(wParam) <= 0x39)
		{
			SendMessage(GetDlgItem(hwnd, LOWORD(wParam - 0x30 + IDC_BUTTON_0)), BM_SETSTATE, TRUE, 0);
			SendMessage(hwnd, WM_COMMAND, LOWORD(wParam - 0x30 + IDC_BUTTON_0), 0);
		}
		else if (LOWORD(wParam) >= 0x60 && LOWORD(wParam) <= 0x69)
		{
			SendMessage(GetDlgItem(hwnd, LOWORD(wParam - 0x69 + IDC_BUTTON_0)), BM_SETSTATE, TRUE, 0);
			SendMessage(hwnd, WM_COMMAND, LOWORD(wParam - 0x69 + IDC_BUTTON_0), 0);
		}
		else
		{
			switch (LOWORD(wParam))
			{
			case VK_OEM_PERIOD:
				SendMessage(GetDlgItem(hwnd, LOWORD(IDC_BUTTON_POINT)), BM_SETSTATE, TRUE, 0);
				SendMessage(hwnd, WM_COMMAND, LOWORD(IDC_BUTTON_POINT), 0);
				break;
			case VK_OEM_PLUS:
				SendMessage(GetDlgItem(hwnd, LOWORD(IDC_BUTTON_PLUS)), BM_SETSTATE, TRUE, 0);
				SendMessage(hwnd, WM_COMMAND, LOWORD(IDC_BUTTON_PLUS), 0);
				break;
			case VK_OEM_MINUS:
				SendMessage(GetDlgItem(hwnd, LOWORD(IDC_BUTTON_MINUS)), BM_SETSTATE, TRUE, 0);
				SendMessage(hwnd, WM_COMMAND, LOWORD(IDC_BUTTON_MINUS), 0);
				break;
			case VK_MULTIPLY:
				SendMessage(GetDlgItem(hwnd, LOWORD(IDC_BUTTON_MULTIPLY)), BM_SETSTATE, TRUE, 0);
				SendMessage(hwnd, WM_COMMAND, LOWORD(IDC_BUTTON_MULTIPLY), 0);
				break;
			case VK_DIVIDE:
				SendMessage(GetDlgItem(hwnd, LOWORD(IDC_BUTTON_DIVIDE)), BM_SETSTATE, TRUE, 0);
				SendMessage(hwnd, WM_COMMAND, LOWORD(IDC_BUTTON_DIVIDE), 0);
				break;
			case VK_BACK:
				SendMessage(GetDlgItem(hwnd, LOWORD(IDC_BUTTON_BSP)), BM_SETSTATE, TRUE, 0);
				SendMessage(hwnd, WM_COMMAND, LOWORD(IDC_BUTTON_BSP), 0);
				break;
			case VK_ESCAPE:
				SendMessage(GetDlgItem(hwnd, LOWORD(IDC_BUTTON_CLEAR)), BM_SETSTATE, TRUE, 0);
				SendMessage(hwnd, WM_COMMAND, LOWORD(IDC_BUTTON_CLEAR), 0);
				break;
			default: break;
			}
		}
	}
		break;

	case WM_KEYUP:
	{
		if (LOWORD(wParam) >= 0x30 && LOWORD(wParam) <= 0x39)
		{
			SendMessage(GetDlgItem(hwnd, LOWORD(wParam - 0x30 + IDC_BUTTON_0)), BM_SETSTATE, FALSE, 0);
		}
		else if (LOWORD(wParam) >= 0x60 && LOWORD(wParam) <= 0x69)
		{
			SendMessage(GetDlgItem(hwnd, LOWORD(wParam - 0x69 + IDC_BUTTON_0)), BM_SETSTATE, FALSE, 0);
		}
		else
		{
			switch (LOWORD(wParam))
			{
			case VK_OEM_PERIOD:
				SendMessage(GetDlgItem(hwnd, LOWORD(IDC_BUTTON_POINT)), BM_SETSTATE, FALSE, 0);
				break;
			case VK_OEM_PLUS:
				SendMessage(GetDlgItem(hwnd, LOWORD(IDC_BUTTON_PLUS)), BM_SETSTATE, FALSE, 0);
				break;
			case VK_OEM_MINUS:
				SendMessage(GetDlgItem(hwnd, LOWORD(IDC_BUTTON_MINUS)), BM_SETSTATE, FALSE, 0);
				break;
			case VK_MULTIPLY:
				SendMessage(GetDlgItem(hwnd, LOWORD(IDC_BUTTON_MULTIPLY)), BM_SETSTATE, FALSE, 0);
				break;
			case VK_DIVIDE:
				SendMessage(GetDlgItem(hwnd, LOWORD(IDC_BUTTON_DIVIDE)), BM_SETSTATE, FALSE, 0);
				break;
			case VK_BACK:
				SendMessage(GetDlgItem(hwnd, LOWORD(IDC_BUTTON_BSP)), BM_SETSTATE, FALSE, 0);
				break;
			case VK_ESCAPE:
				SendMessage(GetDlgItem(hwnd, LOWORD(IDC_BUTTON_CLEAR)), BM_SETSTATE, FALSE, 0);
				break;
			default: break;
			}
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