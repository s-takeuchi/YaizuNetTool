#include <windows.h>
#include <tchar.h>
#include <shlwapi.h>
#include <commctrl.h>
#include "resource.h"
#include "server\VarController.h"
#include "MyMsgProc.h"
#include "server\LowDbAccess.h"

void ChangeOperationType(int Type, HWND RdoBtn1, HWND RdoBtn2, HWND IpHndl, HWND PortHndl, HWND TgtHndl)
{
	if (Type == 0) {
		SendMessage(RdoBtn1, BM_SETCHECK, BST_CHECKED, 0L);
		SendMessage(RdoBtn2, BM_SETCHECK, BST_UNCHECKED, 0L);
		EnableWindow(IpHndl, TRUE);
		EnableWindow(PortHndl, TRUE);
		EnableWindow(TgtHndl, FALSE);
	}
	if (Type == 1) {
		SendMessage(RdoBtn1, BM_SETCHECK, BST_UNCHECKED, 0L);
		SendMessage(RdoBtn2, BM_SETCHECK, BST_CHECKED, 0L);
		EnableWindow(IpHndl, FALSE);
		EnableWindow(PortHndl, FALSE);
		EnableWindow(TgtHndl, TRUE);
	}
}

int GetMsgWidth(HWND WndHndl, TCHAR* Msg)
{
	HDC DevCon = GetDC(WndHndl);
	SIZE Sze;
	HFONT FontHndl = CreateFont(16, 0, 0, 0, FW_REGULAR, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_DONTCARE, _T("Arial"));
	SelectObject(DevCon, FontHndl);
	GetTextExtentPoint32(DevCon, Msg, lstrlen(Msg), &Sze);
	DeleteObject(FontHndl);
	ReleaseDC(WndHndl, DevCon);
	return Sze.cx;
}

int GetMsgHeight(HWND WndHndl, TCHAR* Msg)
{
	HDC DevCon = GetDC(WndHndl);
	SIZE Sze;
	HFONT FontHndl = CreateFont(16, 0, 0, 0, FW_REGULAR, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_DONTCARE, _T("Arial"));
	SelectObject(DevCon, FontHndl);
	GetTextExtentPoint32(DevCon, Msg, lstrlen(Msg), &Sze);
	DeleteObject(FontHndl);
	ReleaseDC(WndHndl, DevCon);
	return Sze.cy;
}

void UdpRecvSend(int CurrentId, int Type, HINSTANCE InstHndl, HWND WndHndl, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HWND IpHndl;
	static HWND PortHndl;
	static HWND CloseSockHndl;
	static HWND RdoBtn1;
	static HWND RdoBtn2;
	static HWND TgtHndl;

	static int SelectedOpeType = 0;
	static int SelectedTargetId = 0;
	static int SelectedCheck = 0;

	if (message == WM_CREATE) {
		if (Type == 21) {
			RdoBtn1  = CreateWindow(_T("BUTTON"), MyMsgProc::GetMsg(MyMsgProc::PROP_NET_RECV), WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON, 10, 135, 
				GetMsgWidth(WndHndl, MyMsgProc::GetMsg(MyMsgProc::PROP_NET_RECV)) + 30, 
				GetMsgHeight(WndHndl, MyMsgProc::GetMsg(MyMsgProc::PROP_NET_RECV)), 
				WndHndl, (HMENU)IDC_NET_OPETYPE_ID, InstHndl, NULL);
			RdoBtn2  = CreateWindow(_T("BUTTON"), MyMsgProc::GetMsg(MyMsgProc::PROP_NET_RECVTGT), WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON, 10, 235, 
				GetMsgWidth(WndHndl, MyMsgProc::GetMsg(MyMsgProc::PROP_NET_RECVTGT)) + 30, 
				GetMsgHeight(WndHndl, MyMsgProc::GetMsg(MyMsgProc::PROP_NET_RECVTGT)), 
				WndHndl, (HMENU)IDC_NET_OPETYPE_SD, InstHndl, NULL);
		} else {
			RdoBtn1  = CreateWindow(_T("BUTTON"), MyMsgProc::GetMsg(MyMsgProc::PROP_NET_SEND), WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON, 10, 135, 
				GetMsgWidth(WndHndl, MyMsgProc::GetMsg(MyMsgProc::PROP_NET_SEND)) + 30, 
				GetMsgHeight(WndHndl, MyMsgProc::GetMsg(MyMsgProc::PROP_NET_SEND)), 
				WndHndl, (HMENU)IDC_NET_OPETYPE_ID, InstHndl, NULL);
			RdoBtn2  = CreateWindow(_T("BUTTON"), MyMsgProc::GetMsg(MyMsgProc::PROP_NET_SENDTGT), WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON, 10, 235, 
				GetMsgWidth(WndHndl, MyMsgProc::GetMsg(MyMsgProc::PROP_NET_SENDTGT)) + 30, 
				GetMsgHeight(WndHndl, MyMsgProc::GetMsg(MyMsgProc::PROP_NET_SENDTGT)), 
				WndHndl, (HMENU)IDC_NET_OPETYPE_SD, InstHndl, NULL);
		}
		SIZE BtnWidth;
		SendMessage(RdoBtn1, BCM_GETIDEALSIZE, 0, (LPARAM)&BtnWidth);
		CreateWindow(_T("STATIC"), MyMsgProc::GetMsg(MyMsgProc::PROP_NET_IPADDR), WS_CHILD | WS_VISIBLE, 50, 167, 140, 20, WndHndl, NULL, InstHndl, NULL);
		IpHndl   = CreateWindowEx(WS_EX_CLIENTEDGE, _T("EDIT"), _T(""), WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL, 190, 165, 200, 24, WndHndl, NULL, InstHndl, NULL);
		CreateWindow(_T("STATIC"), MyMsgProc::GetMsg(MyMsgProc::PROP_NET_PORT), WS_CHILD | WS_VISIBLE, 60, 202, 80, 20, WndHndl, NULL, InstHndl, NULL);
		PortHndl = CreateWindowEx(WS_EX_CLIENTEDGE, _T("EDIT"), _T(""), WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL, 190, 200, 70, 24, WndHndl, NULL, InstHndl, NULL);
		if (Type != 21) {
			CloseSockHndl = CreateWindow(_T("BUTTON"), MyMsgProc::GetMsg(MyMsgProc::PROP_NET_CLOSE_AFTERSEND), WS_CHILD | WS_VISIBLE | BS_CHECKBOX, 10, 295, 
				GetMsgWidth(WndHndl, MyMsgProc::GetMsg(MyMsgProc::PROP_NET_CLOSE_AFTERSEND)) + 30, 
				GetMsgHeight(WndHndl, MyMsgProc::GetMsg(MyMsgProc::PROP_NET_CLOSE_AFTERSEND)), 
				WndHndl, (HMENU)IDC_NET_CLOSESOCK, InstHndl, NULL);
			CreateWindow(_T("STATIC"), MyMsgProc::GetMsg(MyMsgProc::PROP_NET_RECEIVER), WS_CHILD | WS_VISIBLE, 70, 267, 100, 20, WndHndl, NULL, InstHndl, NULL);
		} else {
			CloseSockHndl = CreateWindow(_T("BUTTON"), MyMsgProc::GetMsg(MyMsgProc::PROP_NET_CLOSE_AFTERRECV), WS_CHILD | WS_VISIBLE | BS_CHECKBOX, 10, 295, 
				GetMsgWidth(WndHndl, MyMsgProc::GetMsg(MyMsgProc::PROP_NET_CLOSE_AFTERRECV)) + 30, 
				GetMsgHeight(WndHndl, MyMsgProc::GetMsg(MyMsgProc::PROP_NET_CLOSE_AFTERRECV)), 
				WndHndl, (HMENU)IDC_NET_CLOSESOCK, InstHndl, NULL);
			CreateWindow(_T("STATIC"), MyMsgProc::GetMsg(MyMsgProc::PROP_NET_SENDER), WS_CHILD | WS_VISIBLE, 70, 267, 100, 20, WndHndl, NULL, InstHndl, NULL);
		}
		TgtHndl = CreateWindowEx(WS_EX_CLIENTEDGE, _T("COMBOBOX"), _T(""), WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST | WS_VSCROLL, 190, 265, 200, 200, WndHndl, (HMENU)IDC_NET_SENDER, InstHndl, NULL);

		// Length limitation for edit boxes of the IP address and the port
		SendMessage(IpHndl, EM_SETLIMITTEXT, (WPARAM)255, (LPARAM)0);
		SendMessage(PortHndl, EM_SETLIMITTEXT, (WPARAM)5, (LPARAM)0);

		// 操作種別の初期化
		SelectedOpeType = LowDbAccess::GetInstance()->GetElementInfoParamInt(CurrentId, 1); // Get operation type
		ChangeOperationType(SelectedOpeType, RdoBtn1, RdoBtn2, IpHndl, PortHndl, TgtHndl);

		// Switch enable/disable close check box
		if (Type == 21 && SelectedOpeType == 0) {
			EnableWindow(CloseSockHndl, FALSE);
		}
		if (Type == 21 && SelectedOpeType == 1) {
			EnableWindow(CloseSockHndl, TRUE);
		}
		if (Type != 21 && SelectedOpeType == 0) {
			EnableWindow(CloseSockHndl, TRUE);
		}
		if (Type != 21 && SelectedOpeType == 1) {
			EnableWindow(CloseSockHndl, FALSE);
		}

		// Initialize send/receive target name
		TCHAR TargetName[256][32];
		int TargetId[256];
		int MaxNum;
		if (Type == 21) {
			int TmpMaxNum1 = LowDbAccess::GetInstance()->GetViewElementNamesAndIdsFromUdpType(TargetName, TargetId, 22);
			int TmpMaxNum2 = LowDbAccess::GetInstance()->GetViewElementNamesAndIdsFromUdpType(&TargetName[TmpMaxNum1], &TargetId[TmpMaxNum1], 23);
			MaxNum = TmpMaxNum1 + TmpMaxNum2;
		} else {
			MaxNum = LowDbAccess::GetInstance()->GetViewElementNamesAndIdsFromUdpType(TargetName, TargetId, 21);
		}
		for (int Loop = 0; Loop < MaxNum; Loop++) {
			SendMessage(TgtHndl, CB_ADDSTRING, 0, (LPARAM)TargetName[Loop]);
		}
		SelectedTargetId = LowDbAccess::GetInstance()->GetElementInfoParamInt(CurrentId, 2); // Get target ID
		for (int Loop = 0; Loop < MaxNum; Loop++) {
			if (TargetId[Loop] == SelectedTargetId) {
				SendMessage(TgtHndl, CB_SETCURSEL, Loop, 0);
			}
		}

		// IP address/hostnameの初期化
		TCHAR IpAddrHostname[256];
		LowDbAccess::GetInstance()->GetElementInfoParamStr(CurrentId, IpAddrHostname, 1);
		SendMessage(IpHndl, WM_SETTEXT, (WPARAM)0, (LPARAM)IpAddrHostname);

		// Portの初期化
		int PortNum = LowDbAccess::GetInstance()->GetElementInfoParamInt(CurrentId, 3); // Get port number
		TCHAR Buf[10];
		wsprintf(Buf, _T("%d"), PortNum);
		SendMessage(PortHndl, WM_SETTEXT, (WPARAM)0, (LPARAM)Buf);

		// チェックボックスの初期化
		SelectedCheck = LowDbAccess::GetInstance()->GetElementInfoParamInt(CurrentId, 4); // Close check box
		if (SelectedCheck == 0) {
			SendMessage(CloseSockHndl, BM_SETCHECK, BST_UNCHECKED, 0L);
		} else if (SelectedCheck == 1) {
			SendMessage(CloseSockHndl, BM_SETCHECK, BST_CHECKED, 0L);
		}
	}
	if (message == WM_COMMAND) {
		if (HIWORD(wParam) == CBN_SELCHANGE) {
			if (LOWORD(wParam) == IDC_NET_SENDER) {
				TCHAR TgtName[256][32];
				int TgtId[256];
				if (Type == 21) {
					int TmpMaxNum = LowDbAccess::GetInstance()->GetViewElementNamesAndIdsFromUdpType(TgtName, TgtId, 22);
					LowDbAccess::GetInstance()->GetViewElementNamesAndIdsFromUdpType(&TgtName[TmpMaxNum], &TgtId[TmpMaxNum], 23);
				} else {
					LowDbAccess::GetInstance()->GetViewElementNamesAndIdsFromUdpType(TgtName, TgtId, 21);
				}
				int TmpIndex = (int)SendMessage(TgtHndl, CB_GETCURSEL, 0, 0);
				SelectedTargetId = TgtId[TmpIndex];
			}
		}
		if (HIWORD(wParam) == BN_CLICKED) {
			if (LOWORD(wParam) == IDC_NET_CLOSESOCK) {
				if (SelectedCheck == 0) {
					SelectedCheck = 1;
					SendMessage(CloseSockHndl, BM_SETCHECK, BST_CHECKED, 0L);
				} else if (SelectedCheck == 1) {
					SelectedCheck = 0;
					SendMessage(CloseSockHndl, BM_SETCHECK, BST_UNCHECKED, 0L);
				}
			}
			if (LOWORD(wParam) == IDC_BTNOK) {
				// Set Ip Address
				TCHAR IpAddrHostname[256];
				SendMessage(IpHndl, WM_GETTEXT, (WPARAM)256, (LPARAM)IpAddrHostname);
				LowDbAccess::GetInstance()->SetElementInfoParamStr(CurrentId, IpAddrHostname, 1);
				// Set port number
				TCHAR PortNum[10] = L"";
				SendMessage(PortHndl, WM_GETTEXT, (WPARAM)10, (LPARAM)PortNum);
				int PortNumber = StrToInt(PortNum);
				if (PortNumber < 0) {
					PortNumber = 0;
				}
				if (PortNumber > 65535) {
					PortNumber = 65535;
				}
				LowDbAccess::GetInstance()->SetElementInfoParamInt(CurrentId, PortNumber, 3);
				// Operation type
				LowDbAccess::GetInstance()->SetElementInfoParamInt(CurrentId, SelectedOpeType, 1);
				// Target ID
				LowDbAccess::GetInstance()->SetElementInfoParamInt(CurrentId, SelectedTargetId, 2);
				// Close sock check
				LowDbAccess::GetInstance()->SetElementInfoParamInt(CurrentId, SelectedCheck, 4);
			}
			if (LOWORD(wParam) == IDC_NET_OPETYPE_ID) {
				ChangeOperationType(0, RdoBtn1, RdoBtn2, IpHndl, PortHndl, TgtHndl);
				SelectedOpeType = 0;
				if (Type == 21 && SelectedOpeType == 0) {
					EnableWindow(CloseSockHndl, FALSE);
				}
				if (Type != 21 && SelectedOpeType == 0) {
					EnableWindow(CloseSockHndl, TRUE);
				}
			}
			if (LOWORD(wParam) == IDC_NET_OPETYPE_SD) {
				ChangeOperationType(1, RdoBtn1, RdoBtn2, IpHndl, PortHndl, TgtHndl);
				SelectedOpeType = 1;
				if (Type == 21 && SelectedOpeType == 1) {
					EnableWindow(CloseSockHndl, TRUE);
				}
				if (Type != 21 && SelectedOpeType == 1) {
					EnableWindow(CloseSockHndl, FALSE);
				}
			}
		}
	}
}
