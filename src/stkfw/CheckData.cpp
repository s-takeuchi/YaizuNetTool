#include <windows.h>
#include <tchar.h>
#include "resource.h"
#include "server\VarController.h"
#include "MyMsgProc.h"
#include "server\LowDbAccess.h"

HWND ChkDatStartWith;
HWND ChkDatNotStartWith;
HWND ChkDatEndWith;
HWND ChkDatNotEndWith;
HWND ChkDatContains;
HWND ChkDatNotContains;
HWND ChkDatEqual;
HWND ChkDatNotEqual;
HWND ChkDatVarCBox;

int GetChkDatVarId(int CurrentId)
{
	return LowDbAccess::GetInstance()->GetElementInfoParamInt(CurrentId, 1);
}

void SetChkDatVarId(int CurrentId, int VarId)
{
	LowDbAccess::GetInstance()->SetElementInfoParamInt(CurrentId, VarId, 1);
}

int GetChkDatType(int CurrentId)
{
	return LowDbAccess::GetInstance()->GetElementInfoParamInt(CurrentId, 2);
}

void SetChkDatType(int CurrentId, int VarId)
{
	LowDbAccess::GetInstance()->SetElementInfoParamInt(CurrentId, VarId, 2);
}

void ChangeChkDatType(int Type)
{
	SendMessage(ChkDatStartWith, BM_SETCHECK, BST_UNCHECKED, 0L);
	SendMessage(ChkDatNotStartWith, BM_SETCHECK, BST_UNCHECKED, 0L);
	SendMessage(ChkDatEndWith, BM_SETCHECK, BST_UNCHECKED, 0L);
	SendMessage(ChkDatNotEndWith, BM_SETCHECK, BST_UNCHECKED, 0L);
	SendMessage(ChkDatContains, BM_SETCHECK, BST_UNCHECKED, 0L);
	SendMessage(ChkDatNotContains, BM_SETCHECK, BST_UNCHECKED, 0L);
	SendMessage(ChkDatEqual, BM_SETCHECK, BST_UNCHECKED, 0L);
	SendMessage(ChkDatNotEqual, BM_SETCHECK, BST_UNCHECKED, 0L);
	if (Type == 0) {
		SendMessage(ChkDatStartWith, BM_SETCHECK, BST_CHECKED, 0L);
	}
	if (Type == 1) {
		SendMessage(ChkDatNotStartWith, BM_SETCHECK, BST_CHECKED, 0L);
	}
	if (Type == 2) {
		SendMessage(ChkDatEndWith, BM_SETCHECK, BST_CHECKED, 0L);
	}
	if (Type == 3) {
		SendMessage(ChkDatNotEndWith, BM_SETCHECK, BST_CHECKED, 0L);
	}
	if (Type == 4) {
		SendMessage(ChkDatContains, BM_SETCHECK, BST_CHECKED, 0L);
	}
	if (Type == 5) {
		SendMessage(ChkDatNotContains, BM_SETCHECK, BST_CHECKED, 0L);
	}
	if (Type == 6) {
		SendMessage(ChkDatEqual, BM_SETCHECK, BST_CHECKED, 0L);
	}
	if (Type == 7) {
		SendMessage(ChkDatNotEqual, BM_SETCHECK, BST_CHECKED, 0L);
	}
}

void CheckData(int CurrentId, int Type, HINSTANCE InstHndl, HWND WndHndl, UINT message, WPARAM wParam, LPARAM lParam)
{
	static int MaxIndex = 0;
	static TCHAR VarId[256];
	static int SelectedVarId = 0;
	static int SelectedType = 0;

	RECT Rect;
	GetClientRect(WndHndl, &Rect);

	if (message == WM_CREATE) {
		ChkDatStartWith = CreateWindow(_T("BUTTON"), MyMsgProc::GetMsg(MyMsgProc::PROP_CHKDAT_START), WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON, Rect.left + 20, 110, Rect.right - 40, 20, WndHndl, (HMENU)IDC_CHKDAT_START, InstHndl, NULL);
		ChkDatNotStartWith = CreateWindow(_T("BUTTON"), MyMsgProc::GetMsg(MyMsgProc::PROP_CHKDAT_NSTART), WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON, Rect.left + 20, 140, Rect.right - 40, 20, WndHndl, (HMENU)IDC_CHKDAT_NOTSTART, InstHndl, NULL);
		ChkDatEndWith = CreateWindow(_T("BUTTON"), MyMsgProc::GetMsg(MyMsgProc::PROP_CHKDAT_END), WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON, Rect.left + 20, 170, Rect.right - 40, 20, WndHndl, (HMENU)IDC_CHKDAT_END, InstHndl, NULL);
		ChkDatNotEndWith = CreateWindow(_T("BUTTON"), MyMsgProc::GetMsg(MyMsgProc::PROP_CHKDAT_NEND), WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON, Rect.left + 20, 200, Rect.right - 40, 20, WndHndl, (HMENU)IDC_CHKDAT_NOTEND, InstHndl, NULL);
		ChkDatContains = CreateWindow(_T("BUTTON"), MyMsgProc::GetMsg(MyMsgProc::PROP_CHKDAT_CONT), WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON, Rect.left + 20, 230, Rect.right - 40, 20, WndHndl, (HMENU)IDC_CHKDAT_CONTAIN, InstHndl, NULL);
		ChkDatNotContains = CreateWindow(_T("BUTTON"), MyMsgProc::GetMsg(MyMsgProc::PROP_CHKDAT_NCONT), WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON, Rect.left + 20, 260, Rect.right - 40, 20, WndHndl, (HMENU)IDC_CHKDAT_NOTCONTAIN, InstHndl, NULL);
		ChkDatEqual = CreateWindow(_T("BUTTON"), MyMsgProc::GetMsg(MyMsgProc::PROP_CHKDAT_EQUAL), WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON, Rect.left + 20, 290, Rect.right - 40, 20, WndHndl, (HMENU)IDC_CHKDAT_EQUAL, InstHndl, NULL);
		ChkDatNotEqual = CreateWindow(_T("BUTTON"), MyMsgProc::GetMsg(MyMsgProc::PROP_CHKDAT_NEQUAL), WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON, Rect.left + 20, 320, Rect.right - 40, 20, WndHndl, (HMENU)IDC_CHKDAT_NOTEQUAL, InstHndl, NULL);
		ChkDatVarCBox = CreateWindowEx(WS_EX_CLIENTEDGE, _T("COMBOBOX"), _T(""), WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST | WS_VSCROLL, 230, 350, 200, 200, WndHndl, (HMENU)IDC_CHKDAT_VAR, InstHndl, NULL);

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
				SendMessage(ChkDatVarCBox, CB_ADDSTRING, 0, (LPARAM)VarName);
			}
			CurVarRec = CurVarRec->GetNextRecord();
		}
		delete VarRecs;
		SelectedVarId = GetChkDatVarId(CurrentId);
		for (int Loop = 0; Loop < MaxIndex; Loop++) {
			if (VarId[Loop] == SelectedVarId) {
				SendMessage(ChkDatVarCBox, CB_SETCURSEL, Loop, 0);
			}
		}

		// ラジオボタンの設定
		SelectedType = GetChkDatType(CurrentId);
		ChangeChkDatType(SelectedType);
	}
	if (message == WM_COMMAND) {
		if (HIWORD(wParam) == BN_CLICKED) {
			if (LOWORD(wParam) == IDC_BTNOK) {
				SetChkDatVarId(CurrentId, SelectedVarId);
				SetChkDatType(CurrentId, SelectedType);
			}
			if (LOWORD(wParam) >= IDC_CHKDAT_START && LOWORD(wParam) <= IDC_CHKDAT_NOTEQUAL) {
				ChangeChkDatType(LOWORD(wParam) - IDC_CHKDAT_START);
				SelectedType = LOWORD(wParam) - IDC_CHKDAT_START;
			}
		}
		if (HIWORD(wParam) == CBN_SELCHANGE) {
			if (LOWORD(wParam) == IDC_CHKDAT_VAR) {
				int TmpVarIndex = (int)SendMessage(ChkDatVarCBox, CB_GETCURSEL, 0, 0);
				SelectedVarId = VarId[TmpVarIndex];
			}
		}
	}
}
