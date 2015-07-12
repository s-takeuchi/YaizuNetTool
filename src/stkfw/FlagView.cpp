#include <windows.h>
#include <tchar.h>
#include <shlwapi.h>
#include "resource.h"
#include "VarController.h"
#include "..\..\com\\msgproc\msgproc.h"
#include "LowDbAccess.h"

HWND ChgTrue;
HWND ChgFalse;
HWND ChgVar;
HWND CheckTrue;
HWND CheckFalse;
HWND CheckVar;

int StkProp_CollectAndSetFlagVariable(HWND ComboB, int VarId[2000], int SelectedVarId)
{
	// フラグ用変数をコンボボックスの項目として追加する
	int MaxIndex = 0;
	RecordData* VarRecs = VarCon_GetVariableRecords();
	RecordData* CurVarRec = VarRecs;
	while (CurVarRec != NULL) {
		ColumnDataInt* VarTypeCol = (ColumnDataInt*)CurVarRec->GetColumn(3);
		int VarType = VarTypeCol->GetValue();
		if (VarType == 1) {
			ColumnDataInt* VarIdCol = (ColumnDataInt*)CurVarRec->GetColumn(0);
			ColumnDataWStr* VarNameCol = (ColumnDataWStr*)CurVarRec->GetColumn(1);
			TCHAR* VarName = VarNameCol->GetValue();
			VarId[MaxIndex] = VarIdCol->GetValue();
			MaxIndex++;
			SendMessage(ComboB, CB_ADDSTRING, 0, (LPARAM)VarName);
		}
		CurVarRec = CurVarRec->GetNextRecord();
	}
	ClearRecordData(VarRecs);
	for (int Loop = 0; Loop < MaxIndex; Loop++) {
		if (VarId[Loop] == SelectedVarId) {
			SendMessage(ComboB, CB_SETCURSEL, Loop, 0);
		}
	}
	return MaxIndex;
}

void ChangeFlag(int CurrentId, int Type, HINSTANCE InstHndl, HWND WndHndl, UINT message, WPARAM wParam, LPARAM lParam)
{
	static int VarId[2000];
	static int MaxIndex = 0;
	static int SelectedVarId = 0;
	static int SelectedValue = 0;

	if (message == WM_CREATE) {
		ChgVar = CreateWindowEx(WS_EX_CLIENTEDGE, _T("COMBOBOX"), _T(""), WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST | WS_VSCROLL, 150, 160, 150, 200, WndHndl, (HMENU)IDC_CHGFLAG_VAR, InstHndl, NULL);
		ChgTrue = CreateWindow(_T("BUTTON"), MessageProc::GetMsg(MessageProc::PROP_CHANGE_TRUE), WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON, 150, 200, 150, 20, WndHndl, (HMENU)IDC_CHGFLAG_TRUE, InstHndl, NULL);
		ChgFalse = CreateWindow(_T("BUTTON"), MessageProc::GetMsg(MessageProc::PROP_CHANGE_FALSE), WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON, 150, 240, 150, 20, WndHndl, (HMENU)IDC_CHGFLAG_FALSE, InstHndl, NULL);

		SelectedVarId = LowDbAccess::GetInstance()->GetElementInfoInt(CurrentId, 1);
		MaxIndex = StkProp_CollectAndSetFlagVariable(ChgVar, VarId, SelectedVarId);

		SelectedValue = LowDbAccess::GetInstance()->GetElementInfoInt(CurrentId, 2);
		if (SelectedValue == 1) {
			SendMessage(ChgTrue, BM_SETCHECK, BST_CHECKED, 0L);
			SendMessage(ChgFalse, BM_SETCHECK, BST_UNCHECKED, 0L);
		} else {
			SendMessage(ChgTrue, BM_SETCHECK, BST_UNCHECKED, 0L);
			SendMessage(ChgFalse, BM_SETCHECK, BST_CHECKED, 0L);
		}
	}

	if (message == WM_COMMAND) {
		if (HIWORD(wParam) == CBN_SELCHANGE) {
			if (LOWORD(wParam) == IDC_CHGFLAG_VAR) {
				int TmpVarIndex = (int)SendMessage(ChgVar, CB_GETCURSEL, 0, 0);
				SelectedVarId = VarId[TmpVarIndex];
			}
		}
		if (HIWORD(wParam) == BN_CLICKED) {
			if (LOWORD(wParam) == IDC_CHGFLAG_TRUE) {
				SendMessage(ChgTrue, BM_SETCHECK, BST_CHECKED, 0L);
				SendMessage(ChgFalse, BM_SETCHECK, BST_UNCHECKED, 0L);
				SelectedValue = 1;
			}
			if (LOWORD(wParam) == IDC_CHGFLAG_FALSE) {
				SendMessage(ChgTrue, BM_SETCHECK, BST_UNCHECKED, 0L);
				SendMessage(ChgFalse, BM_SETCHECK, BST_CHECKED, 0L);
				SelectedValue = 0;
			}
			if (LOWORD(wParam) == IDC_BTNOK) {
				LowDbAccess::GetInstance()->SetElementInfoInt(CurrentId, SelectedVarId, 1);
				LowDbAccess::GetInstance()->SetElementInfoInt(CurrentId, SelectedValue, 2);
			}
		}
	}
}

void CheckFlag(int CurrentId, int Type, HINSTANCE InstHndl, HWND WndHndl, UINT message, WPARAM wParam, LPARAM lParam)
{
	static int VarId[256];
	static int MaxIndex = 0;
	static int SelectedVarId = 0;
	static int SelectedValue = 0;

	if (message == WM_CREATE) {
		CheckVar = CreateWindowEx(WS_EX_CLIENTEDGE, _T("COMBOBOX"), _T(""), WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST | WS_VSCROLL, 150, 160, 150, 200, WndHndl, (HMENU)IDC_CHECKFLAG_VAR, InstHndl, NULL);
		CheckTrue = CreateWindow(_T("BUTTON"), MessageProc::GetMsg(MessageProc::PROP_CHECK_TRUE), WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON, 110, 200, 250, 20, WndHndl, (HMENU)IDC_CHECKFLAG_TRUE, InstHndl, NULL);
		CheckFalse = CreateWindow(_T("BUTTON"), MessageProc::GetMsg(MessageProc::PROP_CHECK_FALSE), WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON, 110, 240, 250, 20, WndHndl, (HMENU)IDC_CHECKFLAG_FALSE, InstHndl, NULL);

		SelectedVarId = LowDbAccess::GetInstance()->GetElementInfoInt(CurrentId, 1);
		MaxIndex = StkProp_CollectAndSetFlagVariable(CheckVar, VarId, SelectedVarId);

		SelectedValue = LowDbAccess::GetInstance()->GetElementInfoInt(CurrentId, 2);
		if (SelectedValue == 1) {
			SendMessage(CheckTrue, BM_SETCHECK, BST_CHECKED, 0L);
			SendMessage(CheckFalse, BM_SETCHECK, BST_UNCHECKED, 0L);
		} else {
			SendMessage(CheckTrue, BM_SETCHECK, BST_UNCHECKED, 0L);
			SendMessage(CheckFalse, BM_SETCHECK, BST_CHECKED, 0L);
		}
	}

	if (message == WM_COMMAND) {
		if (HIWORD(wParam) == CBN_SELCHANGE) {
			if (LOWORD(wParam) == IDC_CHECKFLAG_VAR) {
				int TmpVarIndex = (int)SendMessage(CheckVar, CB_GETCURSEL, 0, 0);
				SelectedVarId = VarId[TmpVarIndex];
			}
		}
		if (HIWORD(wParam) == BN_CLICKED) {
			if (LOWORD(wParam) == IDC_CHECKFLAG_TRUE) {
				SendMessage(CheckTrue, BM_SETCHECK, BST_CHECKED, 0L);
				SendMessage(CheckFalse, BM_SETCHECK, BST_UNCHECKED, 0L);
				SelectedValue = 1;
			}
			if (LOWORD(wParam) == IDC_CHECKFLAG_FALSE) {
				SendMessage(CheckTrue, BM_SETCHECK, BST_UNCHECKED, 0L);
				SendMessage(CheckFalse, BM_SETCHECK, BST_CHECKED, 0L);
				SelectedValue = 0;
			}
			if (LOWORD(wParam) == IDC_BTNOK) {
				LowDbAccess::GetInstance()->SetElementInfoInt(CurrentId, SelectedVarId, 1);
				LowDbAccess::GetInstance()->SetElementInfoInt(CurrentId, SelectedValue, 2);
			}
		}
	}
}
