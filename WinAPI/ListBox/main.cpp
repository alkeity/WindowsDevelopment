#include <Windows.h>
#include<cstdio>
#include "resource.h"

CONST CHAR* VALUES[] = { "Zero", "One", "Two", "Three", "Four", "Five" };

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);


INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG2), NULL, (DLGPROC)DlgProc, 0);
	return 0;
}

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
		HWND hListBox = GetDlgItem(hwnd, IDC_LIST_BOX);
		for (size_t i = 0; i < sizeof(VALUES) / sizeof(VALUES[0]); i++)
		{
			SendMessage(hListBox, LB_ADDSTRING, 0, (LPARAM)VALUES[i]);
		}
		SendMessage(hListBox, LB_SETCURSEL, 0, 0);
	}
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
		{
			CONST INT SIZE = 256;
			CHAR szBuffer[SIZE]{};
			CHAR szMessage[SIZE]{};
			HWND hListBox = GetDlgItem(hwnd, IDC_LIST_BOX);
			INT index = SendMessage(hListBox, LB_GETCURSEL, 0, 0);
			SendMessage(hListBox, LB_GETTEXT, index, (LPARAM)szBuffer);
			sprintf_s(szMessage, "You choose №%i (%s)", index, szBuffer);
			MessageBox(hwnd, szMessage, "Your choice", MB_OK | MB_ICONINFORMATION);
		}
			break;
		case IDCANCEL:
			EndDialog(hwnd, 0);
		}
		break;
	case WM_CLOSE:
		EndDialog(hwnd, 0);
	}

	return FALSE;
}
