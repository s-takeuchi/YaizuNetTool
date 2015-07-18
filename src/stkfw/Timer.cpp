#include <windows.h>
#include <tchar.h>
#include <shlwapi.h>
#include "resource.h"
#include "VarController.h"
#include "..\..\..\YaizuComLib\src\\msgproc\msgproc.h"
#include "LowDbAccess.h"

HWND DateSpec;
HWND SleepSpec;
HWND CbYearHndl;
HWND CbMonthHndl;
HWND CbDayHndl;
HWND CbHourHndl;
HWND CbMinuteHndl;
HWND CbSecondHndl;
HWND EdWaitHndl;

void ChangeTimerType(int Type)
{
	if (Type == 0) {
		SendMessage(DateSpec, BM_SETCHECK, BST_CHECKED, 0L);
		SendMessage(SleepSpec, BM_SETCHECK, BST_UNCHECKED, 0L);
		EnableWindow(CbYearHndl, TRUE);
		EnableWindow(CbMonthHndl, TRUE);
		EnableWindow(CbDayHndl, TRUE);
		EnableWindow(CbHourHndl, TRUE);
		EnableWindow(CbMinuteHndl, TRUE);
		EnableWindow(CbSecondHndl, TRUE);
		EnableWindow(EdWaitHndl, FALSE);
	} else {
		SendMessage(DateSpec, BM_SETCHECK, BST_UNCHECKED, 0L);
		SendMessage(SleepSpec, BM_SETCHECK, BST_CHECKED, 0L);
		EnableWindow(CbYearHndl, FALSE);
		EnableWindow(CbMonthHndl, FALSE);
		EnableWindow(CbDayHndl, FALSE);
		EnableWindow(CbHourHndl, FALSE);
		EnableWindow(CbMinuteHndl, FALSE);
		EnableWindow(CbSecondHndl, FALSE);
		EnableWindow(EdWaitHndl, TRUE);
	}
}

void Timer(int CurrentId, int Type, HINSTANCE InstHndl, HWND WndHndl, UINT message, WPARAM wParam, LPARAM lParam)
{
	RECT Rect;
	GetClientRect(WndHndl, &Rect);
	static int SelectedType = 0;

	if (message == WM_CREATE) {
		DateSpec = CreateWindow(_T("BUTTON"), MessageProc::GetMsg(MessageProc::PROP_TIMER_PAST), WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON, Rect.left + 20, 110, Rect.right - 40, 20, WndHndl, (HMENU)IDC_TIMER_CHKTIME, InstHndl, NULL);
		CbYearHndl = CreateWindowEx(WS_EX_CLIENTEDGE, _T("COMBOBOX"), _T(""), WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST | WS_VSCROLL, 100, 140, 60, 200, WndHndl, (HMENU)IDC_TIMER_YEAR, InstHndl, NULL);
		CbMonthHndl = CreateWindowEx(WS_EX_CLIENTEDGE, _T("COMBOBOX"), _T(""), WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST | WS_VSCROLL, 170, 140, 40, 200, WndHndl, (HMENU)IDC_TIMER_MONTH, InstHndl, NULL);
		CbDayHndl = CreateWindowEx(WS_EX_CLIENTEDGE, _T("COMBOBOX"), _T(""), WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST | WS_VSCROLL, 220, 140, 40, 200, WndHndl, (HMENU)IDC_TIMER_DAY, InstHndl, NULL);
		CbHourHndl = CreateWindowEx(WS_EX_CLIENTEDGE, _T("COMBOBOX"), _T(""), WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST | WS_VSCROLL, 300, 140, 40, 200, WndHndl, (HMENU)IDC_TIMER_HOUR, InstHndl, NULL);
		CbMinuteHndl = CreateWindowEx(WS_EX_CLIENTEDGE, _T("COMBOBOX"), _T(""), WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST | WS_VSCROLL, 350, 140, 40, 200, WndHndl, (HMENU)IDC_TIMER_MINUTE, InstHndl, NULL);
		CbSecondHndl = CreateWindowEx(WS_EX_CLIENTEDGE, _T("COMBOBOX"), _T(""), WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST | WS_VSCROLL, 400, 140, 40, 200, WndHndl, (HMENU)IDC_TIMER_SECOND, InstHndl, NULL);
		SleepSpec = CreateWindow(_T("BUTTON"), MessageProc::GetMsg(MessageProc::PROP_TIMER_WAIT), WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON, Rect.left + 20, 200, 260, 20, WndHndl, (HMENU)IDC_TIMER_CHKWAIT, InstHndl, NULL);
		CreateWindow(_T("STATIC"), MessageProc::GetMsg(MessageProc::PROP_TIMER_SEC), WS_CHILD | WS_VISIBLE, 360, 202, 80, 20, WndHndl, NULL, InstHndl, NULL);
		EdWaitHndl = CreateWindowEx(WS_EX_CLIENTEDGE, _T("EDIT"), _T(""), WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL, 300, 200, 50, 24, WndHndl, NULL, InstHndl, NULL);
		SendMessage(EdWaitHndl, EM_SETLIMITTEXT, (WPARAM)4, (LPARAM)0);

		for (int Loop = 2009; Loop <= 2029; Loop++) {
			TCHAR TmpBuf[10];
			wsprintf(TmpBuf, _T("%d"), Loop);
			SendMessage(CbYearHndl, CB_ADDSTRING, 0, (LPARAM)TmpBuf);
		}
		for (int Loop = 1; Loop <= 12; Loop++) {
			TCHAR TmpBuf[10];
			wsprintf(TmpBuf, _T("%d"), Loop);
			SendMessage(CbMonthHndl, CB_ADDSTRING, 0, (LPARAM)TmpBuf);
		}
		for (int Loop = 1; Loop <= 31; Loop++) {
			TCHAR TmpBuf[10];
			wsprintf(TmpBuf, _T("%d"), Loop);
			SendMessage(CbDayHndl, CB_ADDSTRING, 0, (LPARAM)TmpBuf);
		}
		for (int Loop = 0; Loop <= 23; Loop++) {
			TCHAR TmpBuf[10];
			wsprintf(TmpBuf, _T("%d"), Loop);
			SendMessage(CbHourHndl, CB_ADDSTRING, 0, (LPARAM)TmpBuf);
		}
		for (int Loop = 0; Loop <= 59; Loop++) {
			TCHAR TmpBuf[10];
			wsprintf(TmpBuf, _T("%d"), Loop);
			SendMessage(CbMinuteHndl, CB_ADDSTRING, 0, (LPARAM)TmpBuf);
		}
		for (int Loop = 0; Loop <= 59; Loop++) {
			TCHAR TmpBuf[10];
			wsprintf(TmpBuf, _T("%d"), Loop);
			SendMessage(CbSecondHndl, CB_ADDSTRING, 0, (LPARAM)TmpBuf);
		}

		// 年月日時分秒の初期化
		SYSTEMTIME SysTm;
		DWORD HighTm = LowDbAccess::GetInstance()->GetElementInfoInt(CurrentId, 1);
		DWORD LowTm = LowDbAccess::GetInstance()->GetElementInfoInt(CurrentId, 2);
		if (HighTm == 0 && LowTm == 0) {
			GetLocalTime(&SysTm);
		} else {
			FILETIME FileTm;
			FileTm.dwHighDateTime = HighTm;
			FileTm.dwLowDateTime = LowTm;
			FileTimeToSystemTime(&FileTm, &SysTm);
		}
		SendMessage(CbYearHndl, CB_SETCURSEL, SysTm.wYear - 2009, 0);
		SendMessage(CbMonthHndl, CB_SETCURSEL, SysTm.wMonth - 1, 0);
		SendMessage(CbDayHndl, CB_SETCURSEL, SysTm.wDay - 1, 0);
		SendMessage(CbHourHndl, CB_SETCURSEL, SysTm.wHour, 0);
		SendMessage(CbMinuteHndl, CB_SETCURSEL, SysTm.wMinute, 0);
		SendMessage(CbSecondHndl, CB_SETCURSEL, SysTm.wSecond, 0);

		// 待ち時間の初期化
		int WaitTm = LowDbAccess::GetInstance()->GetElementInfoInt(CurrentId, 3);
		TCHAR WaitTmBuf[20];
		wsprintf(WaitTmBuf, _T("%d"), WaitTm);
		SendMessage(EdWaitHndl, WM_SETTEXT, (WPARAM)0, (LPARAM)WaitTmBuf);

		// ラジオボタン初期化
		SelectedType = LowDbAccess::GetInstance()->GetElementInfoInt(CurrentId, 4);
		ChangeTimerType(SelectedType);
	}

	if (message == WM_COMMAND) {
		if (HIWORD(wParam) == BN_CLICKED) {
			if (LOWORD(wParam) == IDC_BTNOK) {
				SYSTEMTIME SysTm;
				SysTm.wYear = (int)SendMessage(CbYearHndl, CB_GETCURSEL, 0, 0) + 2009;
				SysTm.wMonth = (int)SendMessage(CbMonthHndl, CB_GETCURSEL, 0, 0) + 1;
				SysTm.wDay = (int)SendMessage(CbDayHndl, CB_GETCURSEL, 0, 0) + 1;
				SysTm.wHour = (int)SendMessage(CbHourHndl, CB_GETCURSEL, 0, 0);
				SysTm.wMinute = (int)SendMessage(CbMinuteHndl, CB_GETCURSEL, 0, 0);
				SysTm.wSecond = (int)SendMessage(CbSecondHndl, CB_GETCURSEL, 0, 0);
				SysTm.wMilliseconds = 0;
				SysTm.wDayOfWeek = 0;
				FILETIME FileTm;
				SystemTimeToFileTime(&SysTm, &FileTm);
				int *HighTm = (int*)&FileTm.dwHighDateTime;
				int *LowTm = (int*)&FileTm.dwLowDateTime;
				LowDbAccess::GetInstance()->SetElementInfoInt(CurrentId, *HighTm, 1);
				LowDbAccess::GetInstance()->SetElementInfoInt(CurrentId, *LowTm, 2);
				TCHAR Buf[10];
				SendMessage(EdWaitHndl, WM_GETTEXT, (WPARAM)10, (LPARAM)Buf);
				int WaitTime = StrToInt(Buf);
				if (WaitTime < 0) {
					WaitTime = 0;
				}
				if (WaitTime > 3600) {
					WaitTime = 3600;
				}
				LowDbAccess::GetInstance()->SetElementInfoInt(CurrentId, WaitTime, 3);
				LowDbAccess::GetInstance()->SetElementInfoInt(CurrentId, SelectedType, 4);
			}
			if (LOWORD(wParam) == IDC_TIMER_CHKTIME) {
				ChangeTimerType(0);
				SelectedType = 0;
			}
			if (LOWORD(wParam) == IDC_TIMER_CHKWAIT) {
				ChangeTimerType(1);
				SelectedType = 1;
			}
		}
	}
}
