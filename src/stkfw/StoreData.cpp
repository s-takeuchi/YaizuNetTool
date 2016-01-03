#include <windows.h>
#include <tchar.h>
#include <shlwapi.h>
#include "resource.h"
#include "VarController.h"
#include "MyMsgProc.h"
#include "LowDbAccess.h"

HWND StDtVarHndl;
HWND StDtPrefixHndl;
HWND StDtNumHndl;
HWND StDtRdoBtn1;
HWND StDtRdoBtn2;

int GetStoreVarId(int CurrentId)
{
	return LowDbAccess::GetInstance()->GetElementInfoInt(CurrentId, 1);
}

void SetStoreVarId(int CurrentId, int VarId)
{
	LowDbAccess::GetInstance()->SetElementInfoInt(CurrentId, VarId, 1);
}

int GetLoadStoreType(int CurrentId)
{
	return LowDbAccess::GetInstance()->GetElementInfoInt(CurrentId, 2);
}

void SetLoadStoreType(int CurrentId, int Type)
{
	LowDbAccess::GetInstance()->SetElementInfoInt(CurrentId, Type, 2);
}

int GetLoadStoreStartNum(int CurrentId)
{
	return LowDbAccess::GetInstance()->GetElementInfoInt(CurrentId, 4);
}

void SetLoadStoreStartNum(int CurrentId, int StartNum)
{
	LowDbAccess::GetInstance()->SetElementInfoInt(CurrentId, StartNum, 4);
}

void GetLoadStorePrefix(int CurrentId, TCHAR Prefix[256])
{
	LowDbAccess::GetInstance()->GetElementInfoStr(CurrentId, Prefix, 6);
}

void SetLoadStorePrefix(int CurrentId, TCHAR Prefix[256])
{
	LowDbAccess::GetInstance()->SetElementInfoStr(CurrentId, Prefix, 6);
}

void ChangeSettingType(int Type)
{
	if (Type == 0) {
		SendMessage(StDtRdoBtn1, BM_SETCHECK, BST_CHECKED, 0L);
		SendMessage(StDtRdoBtn2, BM_SETCHECK, BST_UNCHECKED, 0L);
		EnableWindow(StDtVarHndl, TRUE);
		EnableWindow(StDtPrefixHndl, FALSE);
		EnableWindow(StDtNumHndl, FALSE);
	}
	if (Type == 1) {
		SendMessage(StDtRdoBtn1, BM_SETCHECK, BST_UNCHECKED, 0L);
		SendMessage(StDtRdoBtn2, BM_SETCHECK, BST_CHECKED, 0L);
		EnableWindow(StDtVarHndl, FALSE);
		EnableWindow(StDtPrefixHndl, TRUE);
		EnableWindow(StDtNumHndl, TRUE);
	}
}

void StoreData(int CurrentId, int Type, HINSTANCE InstHndl, HWND WndHndl, UINT message, WPARAM wParam, LPARAM lParam)
{
	static int SelectedVarId = 0;
	static int VarId[2000];
	static int MaxIndex = 0;
	static int SelectedType = 0;
	static TCHAR SpecifiedPrefix[32];
	static int SpecifiedStartNum = 0;

	static TCHAR Msg1[100];
	static TCHAR Msg2[100];

	if (Type == 2) {
		lstrcpyn(Msg1, MyMsgProc::GetMsg(MyMsgProc::PROP_LOAD_VAR), 100);
		lstrcpyn(Msg2, MyMsgProc::GetMsg(MyMsgProc::PROP_LOAD_CONT), 100);
	} else {
		lstrcpyn(Msg1, MyMsgProc::GetMsg(MyMsgProc::PROP_STORE_VAR), 100);
		lstrcpyn(Msg2, MyMsgProc::GetMsg(MyMsgProc::PROP_STORE_CONT), 100);
	}

	RECT Rect;
	GetClientRect(WndHndl, &Rect);

	if (message == WM_CREATE) {
		StDtRdoBtn1  = CreateWindow(_T("BUTTON"), Msg1, WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON, Rect.left + 10, 110, Rect.right - 20, 20, WndHndl, (HMENU)IDC_LOADSTORE_RADIO1, InstHndl, NULL);
		CreateWindow(_T("STATIC"), MyMsgProc::GetMsg(MyMsgProc::PROP_DATA_COMM), WS_CHILD | WS_VISIBLE, 30, 142, 150, 20, WndHndl, NULL, InstHndl, NULL);
		StDtVarHndl = CreateWindowEx(WS_EX_CLIENTEDGE, _T("COMBOBOX"), _T(""), WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST | WS_VSCROLL, 200, 140, 230, 200, WndHndl, (HMENU)IDC_LOADDATA_VAR, InstHndl, NULL);
		StDtRdoBtn2 = CreateWindow(_T("BUTTON"), Msg2, WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON, Rect.left + 10, 200, Rect.right - 20, 20, WndHndl, (HMENU)IDC_LOADSTORE_RADIO2, InstHndl, NULL);
		CreateWindow(_T("STATIC"), MyMsgProc::GetMsg(MyMsgProc::PROP_DATA_PREF), WS_CHILD | WS_VISIBLE, 60, 232, 180, 20, WndHndl, NULL, InstHndl, NULL);
		StDtPrefixHndl = CreateWindowEx(WS_EX_CLIENTEDGE, _T("EDIT"), _T(""), WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL, 300, 230, 150, 24, WndHndl, NULL, InstHndl, NULL);
		CreateWindow(_T("STATIC"), MyMsgProc::GetMsg(MyMsgProc::PROP_DATA_NUM), WS_CHILD | WS_VISIBLE, 60, 262, 230, 20, WndHndl, NULL, InstHndl, NULL);
		StDtNumHndl = CreateWindowEx(WS_EX_CLIENTEDGE, _T("EDIT"), _T(""), WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL, 300, 260, 100, 24, WndHndl, NULL, InstHndl, NULL);
		SendMessage(StDtPrefixHndl, EM_SETLIMITTEXT, (WPARAM)26, (LPARAM)0);
		SendMessage(StDtNumHndl, EM_SETLIMITTEXT, (WPARAM)5, (LPARAM)0);

		// コミュニケーション用変数をコンボボックスの項目として追加する
		MaxIndex = 0;
		RecordData* VarRecs = VarCon_GetVariableRecords();
		RecordData* CurVarRec = VarRecs;
		while (CurVarRec != NULL) {
			ColumnDataInt* VarTypeCol = (ColumnDataInt*)CurVarRec->GetColumn(3);
			int VarType = VarTypeCol->GetValue();
			if (VarType == 0) {
				ColumnDataInt* VarIdCol = (ColumnDataInt*)CurVarRec->GetColumn(0);
				ColumnDataWStr* VarNameCol = (ColumnDataWStr*)CurVarRec->GetColumn(1);
				TCHAR* VarName = VarNameCol->GetValue();
				VarId[MaxIndex] = VarIdCol->GetValue();
				MaxIndex++;
				SendMessage(StDtVarHndl, CB_ADDSTRING, 0, (LPARAM)VarName);
			}
			CurVarRec = CurVarRec->GetNextRecord();
		}
		delete VarRecs;
		SelectedVarId = GetStoreVarId(CurrentId);
		for (int Loop = 0; Loop < MaxIndex; Loop++) {
			if (VarId[Loop] == SelectedVarId) {
				SendMessage(StDtVarHndl, CB_SETCURSEL, Loop, 0);
			}
		}

		// 操作種別の初期化
		SelectedType = GetLoadStoreType(CurrentId);
		ChangeSettingType(SelectedType);

		// プレフィックス設定
		GetLoadStorePrefix(CurrentId, SpecifiedPrefix);
		SendMessage(StDtPrefixHndl, WM_SETTEXT, (WPARAM)0, (LPARAM)SpecifiedPrefix);

		// プレフィックス後の採番開始番号設定
		SpecifiedStartNum = GetLoadStoreStartNum(CurrentId);
		TCHAR Buf[10];
		wsprintf(Buf, _T("%d"), SpecifiedStartNum);
		SendMessage(StDtNumHndl, WM_SETTEXT, (WPARAM)0, (LPARAM)Buf);
	}
	if (message == WM_COMMAND) {
		if (HIWORD(wParam) == CBN_SELCHANGE) {
			if (LOWORD(wParam) == IDC_LOADDATA_VAR) {
				int TmpVarIndex = (int)SendMessage(StDtVarHndl, CB_GETCURSEL, 0, 0);
				SelectedVarId = VarId[TmpVarIndex];
			}
		}
		if (HIWORD(wParam) == BN_CLICKED) {
			if (LOWORD(wParam) == IDC_BTNOK) {
				SetStoreVarId(CurrentId, SelectedVarId);
				SetLoadStoreType(CurrentId, SelectedType);
				SendMessage(StDtPrefixHndl, WM_GETTEXT, (WPARAM)256, (LPARAM)SpecifiedPrefix);
				SetLoadStorePrefix(CurrentId, SpecifiedPrefix);
				TCHAR Buf[10];
				SendMessage(StDtNumHndl, WM_GETTEXT, (WPARAM)10, (LPARAM)Buf);
				SpecifiedStartNum = StrToInt(Buf);
				SetLoadStoreStartNum(CurrentId, SpecifiedStartNum);
			}
			if (LOWORD(wParam) == IDC_LOADSTORE_RADIO1) {
				ChangeSettingType(0);
				SelectedType = 0;
			}
			if (LOWORD(wParam) == IDC_LOADSTORE_RADIO2) {
				ChangeSettingType(1);
				SelectedType = 1;
			}
		}
	}
}
