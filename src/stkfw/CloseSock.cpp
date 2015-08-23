#include <windows.h>
#include <tchar.h>
#include <shlwapi.h>
#include "resource.h"
#include "MyMsgProc.h"
#include "LowDbAccess.h"

int GetTargetTcpUdpNameArray(TCHAR Name[256][32], int Id[256], int UdpFlag)
{
	return LowDbAccess::GetInstance()->GetTargetTcpUdpNameAndId(Name, Id, UdpFlag);
}

int GetForceClose(int CurrentId)
{
	return LowDbAccess::GetInstance()->GetElementInfoInt(CurrentId, 2);
}

void SetForceClose(int CurrentId, int Check)
{
	LowDbAccess::GetInstance()->SetElementInfoInt(CurrentId, Check, 2);
}

void ChangeUdpTcpOperationType(int Type, HWND RdoBtn1, HWND RdoBtn2, HWND CloseForceHndl)
{
	if (Type == 0) {
		SendMessage(RdoBtn1, BM_SETCHECK, BST_CHECKED, 0L);
		SendMessage(RdoBtn2, BM_SETCHECK, BST_UNCHECKED, 0L);
		EnableWindow(CloseForceHndl, TRUE);
	}
	if (Type == 1) {
		SendMessage(RdoBtn1, BM_SETCHECK, BST_UNCHECKED, 0L);
		SendMessage(RdoBtn2, BM_SETCHECK, BST_CHECKED, 0L);
		EnableWindow(CloseForceHndl, FALSE);
	}
}

void CloseSockSetMenu(HWND CloseHndl, int UdpFlag, int SelectedTargetId, int CurrentId)
{
	// Sender nameÇÃèâä˙âª
	TCHAR SenderName[256][32];
	int SenderId[256];
	int MaxNum;
	SendMessage(CloseHndl, CB_RESETCONTENT, 0, 0);
	MaxNum = GetTargetTcpUdpNameArray(SenderName, SenderId, UdpFlag);
	for (int Loop = 0; Loop < MaxNum; Loop++) {
		SendMessage(CloseHndl, CB_ADDSTRING, 0, (LPARAM)SenderName[Loop]);
	}
	for (int Loop = 0; Loop < MaxNum; Loop++) {
		if (SenderId[Loop] == SelectedTargetId) {
			SendMessage(CloseHndl, CB_SETCURSEL, Loop, 0);
		}
	}
}

void CloseSock(int CurrentId, int Type, HINSTANCE InstHndl, HWND WndHndl, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HWND CloseHndl;
	static HWND CloseForceHndl;
	static HWND RdoBtn1;
	static HWND RdoBtn2;

	static int SelectedTargetId = 0;
	static int SelectedCloseType = 0;
	static int SelectedOpeType = 0;

	TCHAR CloseForceMsg[50];
	static const TCHAR* CloseForce = MyMsgProc::GetMsg(MyMsgProc::PROP_NET_CLOSEFORCE);
	lstrcpy(CloseForceMsg, CloseForce);

	if (message == WM_CREATE) {
		CreateWindow(_T("STATIC"), MyMsgProc::GetMsg(MyMsgProc::PROP_CLOSEPORT), WS_CHILD | WS_VISIBLE, 50, 207, 160, 20, WndHndl, NULL, InstHndl, NULL);
		CloseHndl = CreateWindowEx(WS_EX_CLIENTEDGE, _T("COMBOBOX"), _T(""), WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST | WS_VSCROLL, 220, 205, 200, 200, WndHndl, (HMENU)IDC_CLOSEPORT, InstHndl, NULL);
		CloseForceHndl = CreateWindow(_T("BUTTON"), CloseForceMsg, WS_CHILD | WS_VISIBLE | BS_CHECKBOX, 220, 240, 160, 20, WndHndl, (HMENU)IDC_NET_CLOSEFORCE, InstHndl, NULL);
		RdoBtn1  = CreateWindow(_T("BUTTON"), MyMsgProc::GetMsg(MyMsgProc::PROP_NET_CLOSETCPPORT), WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON, 30, 135, 180, 20, WndHndl, (HMENU)IDC_NET_OPETYPE_TCP, InstHndl, NULL);
		RdoBtn2  = CreateWindow(_T("BUTTON"), MyMsgProc::GetMsg(MyMsgProc::PROP_NET_CLOSEUDPPORT), WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON, 30, 165, 180, 20, WndHndl, (HMENU)IDC_NET_OPETYPE_UDP, InstHndl, NULL);

		// Initialize check box
		SelectedOpeType = LowDbAccess::GetInstance()->GetElementInfoInt(CurrentId, 3); // Get operation type
		ChangeUdpTcpOperationType(SelectedOpeType, RdoBtn1, RdoBtn2, CloseForceHndl);

		// initialize combo box
		SelectedTargetId = LowDbAccess::GetInstance()->GetElementInfoInt(CurrentId, 1);
		CloseSockSetMenu(CloseHndl, SelectedOpeType, SelectedTargetId, CurrentId);

		// Configure force close button
		SelectedCloseType = GetForceClose(CurrentId);
		if (SelectedCloseType == 1) {
			SendMessage(CloseForceHndl, BM_SETCHECK, BST_UNCHECKED, 0L);
		} else {
			SendMessage(CloseForceHndl, BM_SETCHECK, BST_CHECKED, 0L);
		}
	}
	if (message == WM_COMMAND) {
		if (HIWORD(wParam) == CBN_SELCHANGE) {
			if (LOWORD(wParam) == IDC_CLOSEPORT) {
				TCHAR SenderName[256][32];
				int SenderId[256];
				GetTargetTcpUdpNameArray(SenderName, SenderId, SelectedOpeType);
				int TmpIndex = (int)SendMessage(CloseHndl, CB_GETCURSEL, 0, 0);
				SelectedTargetId = SenderId[TmpIndex];
			}
		}
		if (HIWORD(wParam) == BN_CLICKED) {
			if (LOWORD(wParam) == IDC_NET_CLOSEFORCE) {
				if (SelectedCloseType == 1) {
					SelectedCloseType = 0;
					SendMessage(CloseForceHndl, BM_SETCHECK, BST_CHECKED, 0L);
				} else {
					SelectedCloseType = 1;
					SendMessage(CloseForceHndl, BM_SETCHECK, BST_UNCHECKED, 0L);
				}
			}
			if (LOWORD(wParam) == IDC_BTNOK) {
				LowDbAccess::GetInstance()->SetElementInfoInt(CurrentId, SelectedTargetId, 1);
				SetForceClose(CurrentId, SelectedCloseType);
				LowDbAccess::GetInstance()->SetElementInfoInt(CurrentId, SelectedOpeType, 3); // Set operation type
			}
			if (LOWORD(wParam) == IDC_BTNCANCEL) {
			}
			if (LOWORD(wParam) == IDC_NET_OPETYPE_TCP) {
				ChangeUdpTcpOperationType(0, RdoBtn1, RdoBtn2, CloseForceHndl);
				SelectedOpeType = 0;
				CloseSockSetMenu(CloseHndl, SelectedOpeType, SelectedTargetId, CurrentId);
			}
			if (LOWORD(wParam) == IDC_NET_OPETYPE_UDP) {
				ChangeUdpTcpOperationType(1, RdoBtn1, RdoBtn2, CloseForceHndl);
				SelectedOpeType = 1;
				CloseSockSetMenu(CloseHndl, SelectedOpeType, SelectedTargetId, CurrentId);
			}
		}
	}
}
