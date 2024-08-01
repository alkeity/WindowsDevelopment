#include <Windows.h>
#include<cstdio>
#include "resource.h"

CONST CHAR* VALUES[] = { "Zero", "One", "Two", "Three", "Four", "Five" };

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG_LIST), NULL, (DLGPROC)DlgProc, 0);
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
		{
			HWND hListBox = GetDlgItem(hwnd, IDC_LIST_BOX);
			CONST INT SIZE = 256;
			CHAR szBuffer[SIZE]{};
			CHAR szMessage[SIZE]{};

			switch (LOWORD(wParam))
			{
			case IDC_BUTTON_ADD:
			{
				// dialog box that requests value to added item, add item
			}
			break;
			case IDC_BUTTON_REMOVE:
				// just remove selected item
			{
				INT index = SendMessage(hListBox, LB_GETCURSEL, 0, 0);
				SendMessage(hListBox, LB_DELETESTRING, (WPARAM)index, 0);
				SendMessage(hListBox, LB_SETCURSEL, 0, 0);
			}
			break;
			case IDC_CHECK_SORT:
				// sort on/off (????)
			{
				//
			}
				break;
			case IDOK:
			{
				INT index = SendMessage(hListBox, LB_GETCURSEL, 0, 0);
				if (index == CB_ERR) MessageBox(hwnd, "You need to make a choice", "Nah", MB_OK | MB_ICONWARNING);
				else
				{
					SendMessage(hListBox, LB_GETTEXT, index, (LPARAM)szBuffer);
					sprintf_s(szMessage, "You choose №%i (%s)", index, szBuffer);
					MessageBox(hwnd, szMessage, "Your choice", MB_OK | MB_ICONINFORMATION);
				}
			}
			break;
			case IDCANCEL:
				EndDialog(hwnd, 0);
			}
		}
		break;
	case WM_CLOSE:
		EndDialog(hwnd, 0);
	}

	return FALSE;
}
