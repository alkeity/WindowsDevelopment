#include <Windows.h>
#include<cstdio>
#include "resource.h"

CONST CHAR* values[] = {"This", "is", "my", "first", "Combo", "Box"};

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);


INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)DlgProc, 0);
	return 0;
}

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
		HWND hCombo = GetDlgItem(hwnd, IDC_COMBO);
		for (size_t i = 0; i < sizeof(values)/sizeof(values[0]); i++)
		{
			SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)values[i]);
		}
		SendMessage(hCombo, CB_SETCURSEL, 0, 0);
	}
	break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
		{
			CONST INT SIZE = 256;
			CHAR szBuffer[SIZE]{}; // строка из ComboBox
			CHAR szMessage[SIZE]{}; // конечное сообщение, которое выводитс€ в MessageBox
			HWND hComboBox = GetDlgItem(hwnd, IDC_COMBO);
			INT i = SendMessage(hComboBox, CB_GETCURSEL, 0, 0); // получаем индекс выбранного элемента
			if (i == CB_ERR)
			{
				MessageBox(hwnd, szMessage, "You need to make a choice!!", MB_OK | MB_ICONWARNING);
			}
			SendMessage(hComboBox, CB_GETLBTEXT, i, (LPARAM)szBuffer);
			sprintf(szMessage, "¬ы выбрали пункт є%i со значением %s", i, szBuffer);
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
