#include<Windows.h>
#include "resource.h"

//#define TEXT_ELEMENTS

#ifdef TEXT_ELEMENTS
#define IDC_STATIC_TEXT 1000
#define IDC_EDIT 1001
#define IDC_BUTTON 1002  
#endif // TEXT_ELEMENTS

#define CUR_SIZE 30

#define IDC_STATIC 1000
#define IDC_COMBO 1001
#define IDC_BUTTON 1002


CONST CHAR g_sz_WINDOW_CLASS[] = "My First Window"; // class name

INT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	// регистрация класса
	WNDCLASSEX wc; // создаем экземпляр структуры, описывающей класс окна

	ZeroMemory(&wc, sizeof(wc)); // обнуляем данный экземпляр
	// инициализация полей объекта:
	// размеры
	wc.style = 0;
	wc.cbSize = sizeof(wc);
	wc.cbWndExtra = 0;
	wc.cbClsExtra = 0;

	// внешний вид
	/*wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);*/
	wc.hIcon = (HICON)LoadImage(hInstance, "full_moon.ico", IMAGE_ICON, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_LOADFROMFILE);
	wc.hIconSm = (HICON)LoadImage(hInstance, "half_moon.ico", IMAGE_ICON, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_LOADFROMFILE);
	//wc.hCursor = LoadCursor(hInstance, MAKEINTRESOURCE(IDC_CURSOR_STAR));
	wc.hCursor = (HCURSOR)LoadImage(hInstance, "cursors/north_star.cur", IMAGE_CURSOR, CUR_SIZE, CUR_SIZE, LR_LOADFROMFILE);
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;

	// основные параметры класса
	wc.lpszClassName = g_sz_WINDOW_CLASS;
	wc.lpszMenuName = NULL;
	wc.lpfnWndProc = (WNDPROC)WndProc; // указатель на процедуру окна
	wc.hInstance = hInstance;

	// класс окна создан, теперь нужно зарегистрировать его в ОС.
	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, "Class Registration failed", "Error", MB_OK | MB_ICONERROR);
		return 0;
	}

	// window size
	int winWidth = GetSystemMetrics(SM_CXSCREEN) * 0.75;
	int winHeight = GetSystemMetrics(SM_CYSCREEN) * 0.75;

	// window pos
	int posX = (GetSystemMetrics(SM_CXSCREEN) - winWidth) / 2;
	int posY = (GetSystemMetrics(SM_CYSCREEN) - winHeight) / 2;

	// создание окна
	HWND hwnd = CreateWindowEx(
		NULL, // dwExStyle - расширенные стили
		g_sz_WINDOW_CLASS, // Window class
		g_sz_WINDOW_CLASS, // Window title / Window Name
		WS_OVERLAPPEDWINDOW, // WS = Window Style, стиль главного окна, которое будет родительским
		posX, posY, //X, Y
		winWidth, winHeight, // размер окна
		NULL, // родительское окно
		NULL, // для главного окна - это hMenu (строка меню), для дочернего окна - ID, по которому его можно найти функцией GetDlgItem
		hInstance,
		NULL
	);

	if (hwnd == NULL)
	{
		MessageBox(NULL, "Window creation failed", "Error", MB_OK | MB_ICONERROR);
		return 0;
	}

	ShowWindow(hwnd, nCmdShow); // Задает режим отображения окна: Свернуто в окно, в панель задач, развернуто на весь экран
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
#ifdef TEXT_ELEMENTS
		HWND hStatic = CreateWindowEx
		(
			NULL, "Static", ":3c",
			WS_CHILDWINDOW | WS_VISIBLE,
			100, 10, 200, 20,
			hwnd, (HMENU)IDC_STATIC_TEXT,
			NULL, // GetModuleHandle(NULL) - если оставить NULL, используется HINSTANCE родительского окна
			NULL
		);

		HWND hEdit = CreateWindowEx
		(
			NULL, "Edit", "Введите текст:",
			WS_CHILD | WS_VISIBLE | ES_CENTER | WS_BORDER,
			100, 30, 200, 20,
			hwnd, (HMENU)IDC_EDIT,
			NULL, NULL
		);

		HWND hButton = CreateWindowEx
		(
			NULL, "Button", "Применить",
			WS_CHILD | WS_VISIBLE,
			200, 55, 100, 30,
			hwnd, (HMENU)IDC_BUTTON,
			NULL, NULL
		);
#endif // TEXT_ELEMENTS
		HWND hStatic = CreateWindowEx
		(
			NULL, "Static", "Выберите указатель мыши:",
			WS_CHILD | WS_VISIBLE,
			10, 10, 200, 20,
			hwnd, (HMENU)IDC_STATIC,
			NULL, NULL
		);

		HWND hCombo = CreateWindowEx
		(
			NULL, "ComboBox", "",
			WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST | CBS_HASSTRINGS | WS_VSCROLL,
			10, 30, 200, 200,
			hwnd, (HMENU)IDC_COMBO,
			NULL, NULL
		);

		HWND hButton = CreateWindowEx
		(
			NULL, "Button", "Применить",
			WS_CHILD | WS_VISIBLE,
			55, 55, 100, 28,
			hwnd, (HMENU)IDC_BUTTON,
			NULL, NULL
		);

		CHAR szCurDir[MAX_PATH]{};
		SetCurrentDirectory("cursors");
		GetCurrentDirectory(MAX_PATH, szCurDir);
		strcat_s(szCurDir, MAX_PATH, "\\*");

		WIN32_FIND_DATA data;
		ZeroMemory(&data, sizeof(data));
		HANDLE hFind = FindFirstFile(szCurDir, &data);
		if (hFind != INVALID_HANDLE_VALUE)
		{
			do
			{
				if (strcmp(data.cFileName, ".") && strcmp(data.cFileName, ".."))
				{
					SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)data.cFileName);
				}
			} while (FindNextFile(hFind, &data));
			FindClose(hFind);
		}
	}
		break;
	case WM_COMMAND:
	{
#ifdef TEXT_ELEMENTS
		switch (LOWORD(wParam))
		{
		case IDC_BUTTON:
		{
			CONST INT SIZE = 256;
			CHAR szBuffer[SIZE]{};
			HWND hStatic = GetDlgItem(hwnd, IDC_STATIC_TEXT);
			HWND hEdit = GetDlgItem(hwnd, IDC_EDIT);

			SendMessage(hEdit, WM_GETTEXT, SIZE, (LPARAM)szBuffer);
			SendMessage(hStatic, WM_SETTEXT, 0, (LPARAM)szBuffer);
			SendMessage(hwnd, WM_SETTEXT, 0, (LPARAM)szBuffer);
		}
			break;
		default:
			break;
		}
#endif
		switch (LOWORD(wParam))
		{
		case IDC_BUTTON:
		{
			HWND hCombo = GetDlgItem(hwnd, IDC_COMBO);
			int item = SendMessage(hCombo, CB_GETCURSEL, 0, 0);
			CHAR szSelCursor[_MAX_FNAME]{};
			SendMessage(hCombo, CB_GETLBTEXT, item, (LPARAM)szSelCursor);
			HCURSOR newCursor = (HCURSOR)LoadImage(NULL, szSelCursor, IMAGE_CURSOR, CUR_SIZE, CUR_SIZE, LR_LOADFROMFILE);
			SetClassLongPtr(hwnd, GCLP_HCURSOR, (LONG_PTR)newCursor);
		}
		default:
			break;
		}
	}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_CLOSE:
		/*if (MessageBox(hwnd, "Вы действительно хотите закрыть окно?", "Подтверждение закрытия окна", MB_YESNO | MB_ICONQUESTION) == IDYES)
		{
			MessageBox(hwnd, "Ну ладно", "Пассивно-агрессивное окно о глобже", MB_OK | MB_ICONINFORMATION);
			DestroyWindow(hwnd);
		}*/
		DestroyWindow(hwnd);
		break;
	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
}
