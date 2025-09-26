#include<Windows.h>
#include"resource.h"

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	/*MessageBox
	(
		NULL,
		"Привет WinAPI!Как Ваше настроение?",
		"Hello",
		MB_YESNOCANCEL | MB_ICONWARNING | MB_HELP | MB_DEFBUTTON3
	);*/

	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)DlgProc , NULL);
	return 0;
}

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
		HWND hEditLogin = GetDlgItem(hwnd, IDC_EDIT_LOGIN);
		SetWindowText(hEditLogin, "Введите имя пользователя");


		//SetFocus(hEditLogin);
		HICON hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1));
		SendMessage(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)hIcon);
	}
	break;
	case WM_COMMAND:
	{
		HWND hEditLogin = GetDlgItem(hwnd, IDC_EDIT_LOGIN);

		if (LOWORD(wParam) == IDC_EDIT_LOGIN) 
		{
			
			if (HIWORD(wParam) == EN_SETFOCUS)
			{
				char text[256];
				GetWindowText(hEditLogin, (LPSTR)text, 256);

				
				if (strcmp(text, "Введите имя пользователя") == 0)
				{
					SetWindowText(hEditLogin, "");
				}
			}
			
			else if (HIWORD(wParam) == EN_KILLFOCUS)
			{
				char text[256];
				GetWindowText(hEditLogin, (LPSTR)text, 256);

				
				if (strlen(text) == 0)
				{
					SetWindowText(hEditLogin, "Введите имя пользователя");
				}
			}
		}
		switch (LOWORD(wParam))
		{

		case IDC_BUTTON_COPY:
		{
			const int SIZE = 256;
			char sz_buffer[SIZE] = {};
			HWND hEditLogin = GetDlgItem(hwnd, IDC_EDIT_LOGIN);
			HWND hEditPassword = GetDlgItem(hwnd, IDC_EDIT_PASSWORD);
			SendMessage(hEditLogin, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);
			SendMessage(hEditPassword, WM_SETTEXT, 0, (LPARAM)sz_buffer);
		}
		break;
		case IDOK: MessageBox(hwnd, "Была нажата кнопка ОК", "Info", MB_OK | MB_ICONINFORMATION); break;
		case IDCANCEL: EndDialog(hwnd, 0);break;


		}


	}
	break;
		case WM_CLOSE:
			EndDialog(hwnd, 0);
			break;

			

		
		
	}
	return FALSE;
}