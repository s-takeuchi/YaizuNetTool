#include <windows.h>
#include <tchar.h>
#include "resource.h"
#include "VarController.h"
#include "..\..\com\\msgproc\msgproc.h"
#include "LowDbAccess.h"

HWND ChgDatStart;
HWND ChgDatEnd;
HWND ChgDatReplace;
HWND ChgDatExtract;
HWND ChgDatDrop;
HWND ChgDatReset;
HWND ChgDatVarCBoxA;
HWND ChgDatVarCBoxB;
HWND ChgDatVarCBoxC;

int GetChgDatVarIdA(int CurrentId)
{
	return LowDbAccess::GetInstance()->GetElementInfoInt(CurrentId, 1);
}

void SetChgDatVarIdA(int CurrentId, int VarId)
{
	LowDbAccess::GetInstance()->SetElementInfoInt(CurrentId, VarId, 1);
}

int GetChgDatVarIdB(int CurrentId)
{
	return LowDbAccess::GetInstance()->GetElementInfoInt(CurrentId, 2);
}

void SetChgDatVarIdB(int CurrentId, int VarId)
{
	LowDbAccess::GetInstance()->SetElementInfoInt(CurrentId, VarId, 2);
}

int GetChgDatVarIdC(int CurrentId)
{
	return LowDbAccess::GetInstance()->GetElementInfoInt(CurrentId, 3);
}

void SetChgDatVarIdC(int CurrentId, int VarId)
{
	LowDbAccess::GetInstance()->SetElementInfoInt(CurrentId, VarId, 3);
}

int GetChgDatType(int CurrentId)
{
	return LowDbAccess::GetInstance()->GetElementInfoInt(CurrentId, 4);
}

void SetChgDatType(int CurrentId, int VarId)
{
	LowDbAccess::GetInstance()->SetElementInfoInt(CurrentId, VarId, 4);
}

void ChangeChgDatType(int Type)
{
	SendMessage(ChgDatStart, BM_SETCHECK, BST_UNCHECKED, 0L);
	SendMessage(ChgDatEnd, BM_SETCHECK, BST_UNCHECKED, 0L);
	SendMessage(ChgDatReplace, BM_SETCHECK, BST_UNCHECKED, 0L);
	SendMessage(ChgDatExtract, BM_SETCHECK, BST_UNCHECKED, 0L);
	SendMessage(ChgDatDrop, BM_SETCHECK, BST_UNCHECKED, 0L);
	SendMessage(ChgDatReset, BM_SETCHECK, BST_UNCHECKED, 0L);
	if (Type == 0) {
		SendMessage(ChgDatStart, BM_SETCHECK, BST_CHECKED, 0L);
	}
	if (Type == 1) {
		SendMessage(ChgDatEnd, BM_SETCHECK, BST_CHECKED, 0L);
	}
	if (Type == 2) {
		SendMessage(ChgDatReplace, BM_SETCHECK, BST_CHECKED, 0L);
	}
	if (Type == 3) {
		SendMessage(ChgDatExtract, BM_SETCHECK, BST_CHECKED, 0L);
	}
	if (Type == 4) {
		SendMessage(ChgDatDrop, BM_SETCHECK, BST_CHECKED, 0L);
	}
	if (Type == 5) {
		SendMessage(ChgDatReset, BM_SETCHECK, BST_CHECKED, 0L);
	}
}

void ChgData(int CurrentId, int Type, HINSTANCE InstHndl, HWND WndHndl, UINT message, WPARAM wParam, LPARAM lParam)
{
	static int MaxIndex = 0;
	static TCHAR VarId[256];
	static int SelectedVarIdA = 0;
	static int SelectedVarIdB = 0;
	static int SelectedVarIdC = 0;
	static int SelectedType = 0;

	RECT Rect;
	GetClientRect(WndHndl, &Rect);

	if (message == WM_CREATE) {
		ChgDatStart = CreateWindow(_T("BUTTON"), MessageProc::GetMsg(MessageProc::PROP_CHGDAT_INSERT), WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON, Rect.left + 20, 110, Rect.right - 40, 20, WndHndl, (HMENU)IDC_CHGDAT_START, InstHndl, NULL);
		ChgDatEnd = CreateWindow(_T("BUTTON"), MessageProc::GetMsg(MessageProc::PROP_CHGDAT_JOIN), WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON, Rect.left + 20, 140, Rect.right - 40, 20, WndHndl, (HMENU)IDC_CHGDAT_END, InstHndl, NULL);
		ChgDatReplace = CreateWindow(_T("BUTTON"), MessageProc::GetMsg(MessageProc::PROP_CHGDAT_REPLACE), WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON, Rect.left + 20, 170, Rect.right - 40, 20, WndHndl, (HMENU)IDC_CHGDAT_REPLACE, InstHndl, NULL);
		ChgDatExtract = CreateWindow(_T("BUTTON"), MessageProc::GetMsg(MessageProc::PROP_CHGDAT_EXTRACT), WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON, Rect.left + 20, 200, Rect.right - 40, 20, WndHndl, (HMENU)IDC_CHGDAT_EXTRACT, InstHndl, NULL);
		ChgDatDrop = CreateWindow(_T("BUTTON"), MessageProc::GetMsg(MessageProc::PROP_CHGDAT_DROP), WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON, Rect.left + 20, 230, Rect.right - 40, 20, WndHndl, (HMENU)IDC_CHGDAT_DROP, InstHndl, NULL);
		ChgDatReset = CreateWindow(_T("BUTTON"), MessageProc::GetMsg(MessageProc::PROP_CHGDAT_RESET), WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON, Rect.left + 20, 260, Rect.right - 40, 20, WndHndl, (HMENU)IDC_CHGDAT_RESET, InstHndl, NULL);
		CreateWindow(_T("STATIC"), _T("(A)"), WS_CHILD | WS_VISIBLE, 200, 292, 20, 20, WndHndl, NULL, InstHndl, NULL);
		ChgDatVarCBoxA = CreateWindowEx(WS_EX_CLIENTEDGE, _T("COMBOBOX"), _T(""), WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST | WS_VSCROLL, 230, 290, 200, 200, WndHndl, (HMENU)IDC_CHGDAT_VARA, InstHndl, NULL);
		CreateWindow(_T("STATIC"), _T("(B)"), WS_CHILD | WS_VISIBLE, 200, 322, 20, 20, WndHndl, NULL, InstHndl, NULL);
		ChgDatVarCBoxB = CreateWindowEx(WS_EX_CLIENTEDGE, _T("COMBOBOX"), _T(""), WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST | WS_VSCROLL, 230, 320, 200, 200, WndHndl, (HMENU)IDC_CHGDAT_VARB, InstHndl, NULL);
		CreateWindow(_T("STATIC"), _T("(C)"), WS_DISABLED | WS_CHILD | WS_VISIBLE, 200, 352, 20, 20, WndHndl, NULL, InstHndl, NULL);
		ChgDatVarCBoxC = CreateWindowEx(WS_EX_CLIENTEDGE, _T("COMBOBOX"), _T(""), WS_DISABLED | WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST | WS_VSCROLL, 230, 350, 200, 200, WndHndl, (HMENU)IDC_CHGDAT_VARC, InstHndl, NULL);

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
				SendMessage(ChgDatVarCBoxA, CB_ADDSTRING, 0, (LPARAM)VarName);
				SendMessage(ChgDatVarCBoxB, CB_ADDSTRING, 0, (LPARAM)VarName);
				SendMessage(ChgDatVarCBoxC, CB_ADDSTRING, 0, (LPARAM)VarName);
			}
			CurVarRec = CurVarRec->GetNextRecord();
		}
		ClearRecordData(VarRecs);
		SelectedVarIdA = GetChgDatVarIdA(CurrentId);
		SelectedVarIdB = GetChgDatVarIdB(CurrentId);
		SelectedVarIdC = GetChgDatVarIdC(CurrentId);
		for (int Loop = 0; Loop < MaxIndex; Loop++) {
			if (VarId[Loop] == SelectedVarIdA) {
				SendMessage(ChgDatVarCBoxA, CB_SETCURSEL, Loop, 0);
			}
			if (VarId[Loop] == SelectedVarIdB) {
				SendMessage(ChgDatVarCBoxB, CB_SETCURSEL, Loop, 0);
			}
			if (VarId[Loop] == SelectedVarIdC) {
				SendMessage(ChgDatVarCBoxC, CB_SETCURSEL, Loop, 0);
			}
		}

		// ラジオボタンの設定
		SelectedType = GetChgDatType(CurrentId);
		ChangeChgDatType(SelectedType);
	}
	if (message == WM_COMMAND) {
		if (HIWORD(wParam) == BN_CLICKED) {
			if (LOWORD(wParam) == IDC_BTNOK) {
				SetChgDatVarIdA(CurrentId, SelectedVarIdA);
				SetChgDatVarIdB(CurrentId, SelectedVarIdB);
				SetChgDatVarIdC(CurrentId, SelectedVarIdC);
				SetChgDatType(CurrentId, SelectedType);
			}
			if (LOWORD(wParam) >= IDC_CHGDAT_START && LOWORD(wParam) <= IDC_CHGDAT_RESET) {
				ChangeChgDatType(LOWORD(wParam) - IDC_CHGDAT_START);
				SelectedType = LOWORD(wParam) - IDC_CHGDAT_START;
			}
		}
		if (HIWORD(wParam) == CBN_SELCHANGE) {
			if (LOWORD(wParam) == IDC_CHGDAT_VARA) {
				int TmpVarIndex = (int)SendMessage(ChgDatVarCBoxA, CB_GETCURSEL, 0, 0);
				SelectedVarIdA = VarId[TmpVarIndex];
			}
			if (LOWORD(wParam) == IDC_CHGDAT_VARB) {
				int TmpVarIndex = (int)SendMessage(ChgDatVarCBoxB, CB_GETCURSEL, 0, 0);
				SelectedVarIdB = VarId[TmpVarIndex];
			}
			if (LOWORD(wParam) == IDC_CHGDAT_VARC) {
				int TmpVarIndex = (int)SendMessage(ChgDatVarCBoxC, CB_GETCURSEL, 0, 0);
				SelectedVarIdC = VarId[TmpVarIndex];
			}
		}
	}
}
