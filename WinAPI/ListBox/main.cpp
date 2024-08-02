#include <Windows.h>
#include<cstdio>
#include "resource.h"

CONST CHAR* VALUES[] = { "Zero", "One", "Two", "Three", "Four", "Five" };

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK DlgAddOption(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

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
				// dialog box that requests value to added item, add item
			{
				if (DialogBoxParam(NULL, MAKEINTRESOURCE(IDD_DIALOG_OPTION), GetDlgItem(hwnd, IDD_DIALOG_LIST), (DLGPROC)DlgAddOption, (LPARAM)szBuffer) == IDOK)
				{
					SendMessage(hListBox, LB_ADDSTRING, 0, (LPARAM)szBuffer);
				}
			}
			break;
			case IDC_BUTTON_REMOVE:
				// just remove selected item
			{
				INT index = SendMessage(hListBox, LB_GETCURSEL, 0, 0);
				if (index == CB_ERR) MessageBox(hwnd, "There's nothing left to remove", "Nah", MB_OK | MB_ICONWARNING);
				else
				{
					SendMessage(hListBox, LB_DELETESTRING, (WPARAM)index, 0);
					SendMessage(hListBox, LB_SETCURSEL, 0, 0);
				}
			}
			break;
			case IDC_CHECK_SORT:
				// sort on/off (????)
				// TODO read on this more, docs say sort is set in stone after window creation
			{
				INT state = SendMessage(GetDlgItem(hwnd, IDC_CHECK_SORT), BM_GETCHECK, 0, 0);
				if (state == BST_CHECKED)
				{
					//
				}
				else
				{
					//
				}
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

BOOL CALLBACK DlgAddOption(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static CHAR* pBuffer;
	INT SIZE = 256;
	switch (uMsg)
	{
	case WM_INITDIALOG:
		pBuffer = (CHAR*)lParam;
	break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
		{
			HWND hEditOption = GetDlgItem(hwnd, IDC_EDIT_OPTION);
			SendMessage(hEditOption, WM_GETTEXT, SIZE, (LPARAM)pBuffer);
			if (strlen(pBuffer) == 0) MessageBox(hwnd, "There's nothing to add", "Nah", MB_OK | MB_ICONWARNING);
			else
			{
				/*HWND hParent = GetParent(hwnd);
				HWND hListBox = GetDlgItem(hParent, IDC_LIST_BOX);
				SendMessage(hListBox, LB_ADDSTRING, SIZE, (LPARAM)szBuffer);*/
				EndDialog(hwnd, IDOK);
			}
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

