#include<Windows.h>
#include"resource.h"

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	//MessageBox(NULL, "Hello World?", "Hello WinAPI", MB_YESNOCANCEL | MB_ICONQUESTION | MB_DEFBUTTON3);
	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)DlgProc, 0);
	return 0;
}

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	// hwnd = handler to window, дескриптор окна
	// hInstance - *.exe модуль программы
	// hPrevInst - параметр, использовавшийся в Win98, на сегодня некатуален и оставлен для совместимости
	// lpCmdLine - Long Pointer to Command prompt, командная строка, передающаяся в WinMain при запуске программы
	switch (uMsg)
	{
		// WM = Windows Message
	case WM_INITDIALOG: // отрабатывает только один раз, при создании окна
	{
		HICON hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(ID_ICON_MOON));
		SendMessage(hwnd, WM_SETICON, 0, (LPARAM)hIcon);

		/*HWND hwndEditLogin = GetDlgItem(hwnd, IDC_EDIT_LOGIN);
		SetFocus(hwndEditLogin);*/

		SetFocus(GetDlgItem(hwnd, IDC_EDIT_LOGIN));
	}
	break;
	case WM_COMMAND: // обрабатывает нажатия на кнопки, ввод текста, любые изменения состояния
		switch (LOWORD(wParam))
		{
		case IDC_BUTTON_COPY:
		{
			HWND hEditLogin = GetDlgItem(hwnd, IDC_EDIT_LOGIN);
			HWND hEditPassword = GetDlgItem(hwnd, IDC_EDIT_PASSWORD);
			CONST INT SIZE = 256;
			CHAR szBuffer[SIZE]{};
			SendMessage(hEditLogin, WM_GETTEXT, SIZE, (LPARAM)szBuffer);
			SendMessage(hEditPassword, WM_SETTEXT, 0, (LPARAM)szBuffer);
		}
		break;
		case IDOK:
			MessageBox(hwnd, "You pressed OK button", "Info", MB_OK | MB_ICONINFORMATION);
			break;
		case IDCANCEL:
			EndDialog(hwnd, 0);
			break;
		}
		break;
	case WM_CLOSE: // отрабатывает при нажатии на кнопку Х (закрыть)
		EndDialog(hwnd, 0);
		break;
	}
	return FALSE;
}
