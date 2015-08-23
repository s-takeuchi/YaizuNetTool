#include <windows.h>
#include <tchar.h>
#include <shlwapi.h>
#include "resource.h"
#include "VarController.h"
#include "MyMsgProc.h"
#include "LowDbAccess.h"

HWND MapperSpec1;
HWND MapperSpec2;
HWND MapperEdit1Hndl;
HWND MapperEdit2Hndl;
HWND UseOnceHndl;
HWND NumHndl;

void Mapper(int CurrentId, int Type, HINSTANCE InstHndl, HWND WndHndl, UINT message, WPARAM wParam, LPARAM lParam)
{
	RECT Rect;
	GetClientRect(WndHndl, &Rect);
	static int UseOnceChk = 0;

	if (message == WM_CREATE) {
		CreateWindow(_T("STATIC"), MyMsgProc::GetMsg(MyMsgProc::PROP_MAP_SEARCH), WS_CHILD | WS_VISIBLE, 40, 110, 250, 20, WndHndl, NULL, InstHndl, NULL);
		MapperEdit1Hndl = CreateWindowEx(WS_EX_CLIENTEDGE, _T("EDIT"), _T(""), WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL, 200, 140, 100, 24, WndHndl, NULL, InstHndl, NULL);
		CreateWindow(_T("STATIC"), MyMsgProc::GetMsg(MyMsgProc::PROP_MAP_REPLACE), WS_CHILD | WS_VISIBLE, 40, 180, 250, 20, WndHndl, NULL, InstHndl, NULL);
		MapperEdit2Hndl = CreateWindowEx(WS_EX_CLIENTEDGE, _T("EDIT"), _T(""), WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL, 200, 210, 100, 24, WndHndl, NULL, InstHndl, NULL);
		CreateWindow(_T("STATIC"), MyMsgProc::GetMsg(MyMsgProc::PROP_MAP_START), WS_CHILD | WS_VISIBLE, 40, 250, 290, 20, WndHndl, NULL, InstHndl, NULL);
		NumHndl = CreateWindowEx(WS_EX_CLIENTEDGE, _T("EDIT"), _T(""), WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL, 200, 280, 100, 24, WndHndl, NULL, InstHndl, NULL);
		UseOnceHndl = CreateWindow(_T("BUTTON"), MyMsgProc::GetMsg(MyMsgProc::PROP_MAP_USEONCE), WS_CHILD | WS_VISIBLE | BS_CHECKBOX, Rect.left + 40, 330, Rect.right - 60, 20, WndHndl, (HMENU)IDC_MAP_USEONCE, InstHndl, NULL);
		SendMessage(MapperEdit1Hndl, EM_SETLIMITTEXT, (WPARAM)26, (LPARAM)0);
		SendMessage(MapperEdit2Hndl, EM_SETLIMITTEXT, (WPARAM)26, (LPARAM)0);
		SendMessage(NumHndl, EM_SETLIMITTEXT, (WPARAM)5, (LPARAM)0);

		TCHAR Prefix1[32];
		TCHAR Prefix2[32];
		TCHAR NumBuf[10];
		LowDbAccess::GetInstance()->GetElementInfoStr(CurrentId, Prefix1, 6);
		LowDbAccess::GetInstance()->GetElementInfoStr(CurrentId, Prefix2, 7);
		int Num = LowDbAccess::GetInstance()->GetElementInfoInt(CurrentId, 1);
		wsprintf(NumBuf, _T("%d"), Num);
		SendMessage(MapperEdit1Hndl, WM_SETTEXT, (WPARAM)0, (LPARAM)Prefix1);
		SendMessage(MapperEdit2Hndl, WM_SETTEXT, (WPARAM)0, (LPARAM)Prefix2);
		SendMessage(NumHndl, WM_SETTEXT, (WPARAM)0, (LPARAM)NumBuf);

		// チェックボックスの初期化
		UseOnceChk = LowDbAccess::GetInstance()->GetElementInfoInt(CurrentId, 2);
		if (UseOnceChk == 0) {
			SendMessage(UseOnceHndl, BM_SETCHECK, BST_UNCHECKED, 0L);
		} else {
			SendMessage(UseOnceHndl, BM_SETCHECK, BST_CHECKED, 0L);
		}
	}

	if (message == WM_COMMAND) {
		if (HIWORD(wParam) == BN_CLICKED) {
			if (LOWORD(wParam) == IDC_MAP_USEONCE) {
				if (UseOnceChk == 0) {
					UseOnceChk = 1;
					SendMessage(UseOnceHndl, BM_SETCHECK, BST_CHECKED, 0L);
				} else {
					UseOnceChk = 0;
					SendMessage(UseOnceHndl, BM_SETCHECK, BST_UNCHECKED, 0L);
				}
			} else if (LOWORD(wParam) == IDC_BTNOK) {
				TCHAR Buf1[32];
				TCHAR Buf2[32];
				TCHAR NumBuf[10];
				SendMessage(MapperEdit1Hndl, WM_GETTEXT, (WPARAM)32, (LPARAM)Buf1);
				SendMessage(MapperEdit2Hndl, WM_GETTEXT, (WPARAM)32, (LPARAM)Buf2);
				SendMessage(NumHndl, WM_GETTEXT, (WPARAM)10, (LPARAM)NumBuf);
				LowDbAccess::GetInstance()->SetElementInfoStr(CurrentId, Buf1, 6);
				LowDbAccess::GetInstance()->SetElementInfoStr(CurrentId, Buf2, 7);
				int Num = StrToInt(NumBuf);
				LowDbAccess::GetInstance()->SetElementInfoInt(CurrentId, Num, 1);
				LowDbAccess::GetInstance()->SetElementInfoInt(CurrentId, UseOnceChk, 2);
			}
		}
	}
}
