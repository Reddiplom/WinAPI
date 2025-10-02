#define _CRT_SECURE_NO_WARNINGS
#include<Windows.h>
#include<cstdio>
#include "resource.h"

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	//hInstance - экземпляр запущенного *.exe-файла нашей программы;
	//hPrevInst - предыдущий запущенный экземпляр нашей программы. Этот параметр использовался только в Win98 , далее уже не используется. 
	//lpCmdLine - это командная строка с которой была запущена программа 
	//nCmdShow - режим отображения окна: Развернуто на весь экран , свернуто и тд 

	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)DlgProc, 0);
	return 0;
}

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
		HWND EditStd = GetDlgItem(hwnd, IDC_EDIT_STUDENT);
		SetWindowText(EditStd, "Введите ФИО студента");

		return true;
	}
	break;
	case WM_COMMAND:
	{
		HWND EditStd = GetDlgItem(hwnd, IDC_EDIT_STUDENT);
			
			if (LOWORD(wParam) == IDC_EDIT_STUDENT)
			{
				if (HIWORD(wParam) == EN_SETFOCUS)
				{

					char text[FILENAME_MAX];
					GetWindowTextA(EditStd, text, FILENAME_MAX);
					if (strcmp(text, "Введите ФИО студента") == 0)
					{
						SetWindowTextA(EditStd, "");
					}
				}
				else if (HIWORD(wParam) == EN_KILLFOCUS)
				{
					char text[FILENAME_MAX];
					GetWindowTextA(EditStd, text, FILENAME_MAX);
					if (strlen(text) == 0)
					{
						SetWindowTextA(EditStd, "Введите ФИО студента");
					}
				}
			}
		
		switch (LOWORD(wParam))
		{
			case ID_OK:
			{

				HWND hDescription = GetDlgItem(hwnd, IDC_DESCRIPTION);
				int checkBoxIDs[] = { IDC_CHECK1,IDC_CHECK2 ,IDC_CHECK3 , IDC_CHECK4 , IDC_CHECK5 , IDC_CHECK6 };
				const char* checkBoxTexts[] = { "Активный на занятиях","Выполняет ДЗ" ,"Посещает занятия" , "Нарушает дисциплину" , "Не выполняет ДЗ" , "Пропускает занятия" };
				char advantages[FILENAME_MAX] = "Преимущества студента:\r\n";
				char disadvantages[FILENAME_MAX] = "\r\nНедостатки студента:\r\n";
				for (int i = 0; i < 3; i++)
				{
					HWND hCheckBox = GetDlgItem(hwnd, checkBoxIDs[i]);
					if (SendMessage(hCheckBox, BM_GETCHECK, 0, 0) == BST_CHECKED)
					{
						strcat(advantages, "• ");
						strcat(advantages, checkBoxTexts[i]);
						strcat(advantages, "\r\n");
					}
				}
				for (int i = 3; i < 6; i++)
				{
					HWND hCheckBox = GetDlgItem(hwnd, checkBoxIDs[i]);
					if (SendMessage(hCheckBox, BM_GETCHECK, 0, 0) == BST_CHECKED)
					{
						strcat(disadvantages, "• ");
						strcat(disadvantages, checkBoxTexts[i]);
						strcat(disadvantages, "\r\n");
					}
				}
				strcat(advantages, disadvantages);
				SetWindowTextA(hDescription, advantages);


				return true;
			}
			case ID_CANCEL:  
			{
				
				HWND hEditStudent = GetDlgItem(hwnd, IDC_EDIT_STUDENT);
				SetWindowTextA(hEditStudent, "Введите ФИО студента");
				HWND hDescription = GetDlgItem(hwnd, IDC_DESCRIPTION);
				SetWindowTextA(hDescription, "");
				int checkBoxIDs[] = { IDC_CHECK1, IDC_CHECK2, IDC_CHECK3, IDC_CHECK4, IDC_CHECK5, IDC_CHECK6 };
				for (int i = 0; i < 6; i++)
				{
					HWND hCheckBox = GetDlgItem(hwnd, checkBoxIDs[i]);
					SendMessage(hCheckBox, BM_SETCHECK, BST_UNCHECKED, 0);
				}

				MessageBoxA(hwnd, "Все поля очищены!", "Информация", MB_OK);

				return TRUE;
			}

		}
	}
		break;

	case WM_CLOSE:
		EndDialog(hwnd, 0);
		break;
	}
	return 0;
}