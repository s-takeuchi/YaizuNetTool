#include <windows.h>
#include <tchar.h>
#include <shlwapi.h>
#include "resource.h"
#include "server\VarController.h"
#include "MyMsgProc.h"
#include "server\LowDbAccess.h"

int GetMsgWidth(HWND, TCHAR*);
int GetMsgHeight(HWND, TCHAR*);

HWND IconHndl;
HWND IpHndl;
HWND PortHndl;
HWND RdoBtn1;
HWND RdoBtn2;
HWND RdoBtn3;
HWND SendHndl;
HWND RecvHndl;
HWND CloseSockHndl;
HWND CloseForceHndl;

int GetIconId(int CurrentId)
{
	return LowDbAccess::GetInstance()->GetIconId(CurrentId);
}

void SetIconId(int CurrentId, int IconId)
{
	LowDbAccess::GetInstance()->SetIconId(CurrentId, IconId);
}

int GetOperationType(int CurrentId)
{
	return LowDbAccess::GetInstance()->GetElementInfoParamInt(CurrentId, 1);
}

void SetOperationType(int CurrentId, int OperationId)
{
	LowDbAccess::GetInstance()->SetElementInfoParamInt(CurrentId, OperationId, 1);
}

int GetTargetId(int CurrentId)
{
	return LowDbAccess::GetInstance()->GetElementInfoParamInt(CurrentId, 2);
}

void SetTargetId(int CurrentId, int SenderId)
{
	LowDbAccess::GetInstance()->SetElementInfoParamInt(CurrentId, SenderId, 2);
}

int GetPortNumber(int CurrentId)
{
	return LowDbAccess::GetInstance()->GetElementInfoParamInt(CurrentId, 3);
}

void SetPortNumber(int CurrentId, int PortNumber)
{
	LowDbAccess::GetInstance()->SetElementInfoParamInt(CurrentId, PortNumber, 3);
}

int GetCloseSockCheck(int CurrentId)
{
	return LowDbAccess::GetInstance()->GetElementInfoParamInt(CurrentId, 4);
}

void SetCloseSockCheck(int CurrentId, int Check)
{
	LowDbAccess::GetInstance()->SetElementInfoParamInt(CurrentId, Check, 4);
}

int GetCondition(int CurrentId)
{
	return LowDbAccess::GetInstance()->GetElementInfoParamInt(CurrentId, 5);
}

void SetCondition(int CurrentId, int Check)
{
	LowDbAccess::GetInstance()->SetElementInfoParamInt(CurrentId, Check, 5);
}

int GetTimeoutInterval(int CurrentId)
{
	return LowDbAccess::GetInstance()->GetElementInfoParamInt(CurrentId, 6);
}

void SetTimeoutInterval(int CurrentId, int Interval)
{
	LowDbAccess::GetInstance()->SetElementInfoParamInt(CurrentId, Interval, 6);
}

void GetIpAddressOrHostname(int CurrentId, TCHAR GetStr[256])
{
	LowDbAccess::GetInstance()->GetElementInfoParamStr(CurrentId, GetStr, 1);
}

void SetIpAddressOrHostname(int CurrentId, TCHAR SetStr[256])
{
	LowDbAccess::GetInstance()->SetElementInfoParamStr(CurrentId, SetStr, 1);
}

// Flag == TRUE ... sender names and IDs can be acquired.
// Flag == FALSE && RemovalId == -1 ... receiver names and IDs can be acquired.
// Flag == FALSE && RemovalId != -1 ... receiver names and IDs can be acquired. But the information regarding RemovalId cannot be acquired.
int GetTargetNameArray(TCHAR TargetName[256][32], int TargetId[256], BOOL Flag, BOOL MaFlag, int RemovalId)
{
	return LowDbAccess::GetInstance()->GetTcpSenderReceiver(TargetName, TargetId, Flag, MaFlag, RemovalId);
}

void ChangeOperationType(int Type)
{
	if (Type == 0) {
		SendMessage(RdoBtn1, BM_SETCHECK, BST_CHECKED, 0L);
		SendMessage(RdoBtn2, BM_SETCHECK, BST_UNCHECKED, 0L);
		SendMessage(RdoBtn3, BM_SETCHECK, BST_UNCHECKED, 0L);
		EnableWindow(IpHndl, TRUE);
		EnableWindow(PortHndl, TRUE);
		EnableWindow(SendHndl, FALSE);
		EnableWindow(RecvHndl, FALSE);
	}
	if (Type == 1) {
		SendMessage(RdoBtn1, BM_SETCHECK, BST_UNCHECKED, 0L);
		SendMessage(RdoBtn2, BM_SETCHECK, BST_CHECKED, 0L);
		SendMessage(RdoBtn3, BM_SETCHECK, BST_UNCHECKED, 0L);
		EnableWindow(IpHndl, FALSE);
		EnableWindow(PortHndl, FALSE);
		EnableWindow(SendHndl, TRUE);
		EnableWindow(RecvHndl, FALSE);
	}
	if (Type == 2) {
		SendMessage(RdoBtn1, BM_SETCHECK, BST_UNCHECKED, 0L);
		SendMessage(RdoBtn2, BM_SETCHECK, BST_UNCHECKED, 0L);
		SendMessage(RdoBtn3, BM_SETCHECK, BST_CHECKED, 0L);
		EnableWindow(IpHndl, FALSE);
		EnableWindow(PortHndl, FALSE);
		EnableWindow(SendHndl, FALSE);
		EnableWindow(RecvHndl, TRUE);
	}
}

// This function switches the description of finish condition.
// Only "Type" in second parameter is 1, this function can be processed.
// CurrentId [in] : ID for the processing element
// Type [in] : Element type (1:TCP receiver, otherwise:Non target element type)
// FinishCondHndl [in] : Handle of finish condition combo box
// LabelTimeoutIntvl [in] : A label of timeout interval
// WaitCondHndl [in] : Handle of wait condition edit box
// LenCondHndl [in] : Handle of length condition edit box
// SpecVarRecvHndl [in] : Variable name for string
// ProceedNoDatRecvHndl [in] : Check box for proceeding next with no data
// SelectedProceedNoDatRecv [in] : Initial state of check box
void UpdateFinishCondition(int CondValue, int Type, HWND FinishCondHndl, HWND LabelTimeoutIntvl, HWND WaitCondHndl, HWND LenCondHndl, HWND SpecVarRecvHndl, HWND ProceedNoDatRecvHndl, HWND ChunkOptionHndl, int SelectedProceedNoDatRecv, int TimeoutIntvl)
{
	if (Type == 1) {
		TCHAR Buf[10];
		if (CondValue == 0) {
			SendMessage(FinishCondHndl, CB_SETCURSEL, 0, 0);
			ShowWindow(LabelTimeoutIntvl, SW_HIDE);
			ShowWindow(WaitCondHndl, SW_HIDE);
			ShowWindow(ProceedNoDatRecvHndl, SW_HIDE);
			ShowWindow(LenCondHndl, SW_HIDE);
			ShowWindow(SpecVarRecvHndl, SW_HIDE);
			ShowWindow(ChunkOptionHndl, SW_HIDE);
		} else if (CondValue == 2) {
			SendMessage(FinishCondHndl, CB_SETCURSEL, 1, 0);
			ShowWindow(LabelTimeoutIntvl, SW_HIDE);
			ShowWindow(WaitCondHndl, SW_HIDE);
			ShowWindow(ProceedNoDatRecvHndl, SW_HIDE);
			ShowWindow(LenCondHndl, SW_HIDE);
			ShowWindow(SpecVarRecvHndl, SW_HIDE);
			ShowWindow(ChunkOptionHndl, SW_HIDE);
		} else if (CondValue == 1) {
			SendMessage(FinishCondHndl, CB_SETCURSEL, 2, 0);
			ShowWindow(LabelTimeoutIntvl, SW_SHOW);
			wsprintf(Buf, _T("%d"), TimeoutIntvl);
			SendMessage(WaitCondHndl, WM_SETTEXT, (WPARAM)0, (LPARAM)Buf);
			ShowWindow(WaitCondHndl, SW_SHOW);
			ShowWindow(ProceedNoDatRecvHndl, SW_SHOW);
			if (SelectedProceedNoDatRecv == 0) {
				SendMessage(ProceedNoDatRecvHndl, BM_SETCHECK, BST_UNCHECKED, 0L);
			} else {
				SendMessage(ProceedNoDatRecvHndl, BM_SETCHECK, BST_CHECKED, 0L);
			}
			ShowWindow(LenCondHndl, SW_HIDE);
			ShowWindow(SpecVarRecvHndl, SW_HIDE);
			ShowWindow(ChunkOptionHndl, SW_HIDE);
		} else if (CondValue < 0) {
			SendMessage(FinishCondHndl, CB_SETCURSEL, 3, 0);
			CondValue = CondValue * -1;
			ShowWindow(LabelTimeoutIntvl, SW_SHOW);
			wsprintf(Buf, _T("%d"), TimeoutIntvl);
			SendMessage(WaitCondHndl, WM_SETTEXT, (WPARAM)0, (LPARAM)Buf);
			ShowWindow(WaitCondHndl, SW_SHOW);
			ShowWindow(ProceedNoDatRecvHndl, SW_SHOW);
			if (SelectedProceedNoDatRecv == 0) {
				SendMessage(ProceedNoDatRecvHndl, BM_SETCHECK, BST_UNCHECKED, 0L);
			} else {
				SendMessage(ProceedNoDatRecvHndl, BM_SETCHECK, BST_CHECKED, 0L);
			}
			ShowWindow(LenCondHndl, SW_HIDE);
			ShowWindow(SpecVarRecvHndl, SW_SHOW);
			SendMessage(SpecVarRecvHndl, CB_SETCURSEL, 0, 0);
			ShowWindow(ChunkOptionHndl, SW_HIDE);
		} else if (CondValue == 3) {
			SendMessage(FinishCondHndl, CB_SETCURSEL, 5, 0);
			ShowWindow(LabelTimeoutIntvl, SW_SHOW);
			wsprintf(Buf, _T("%d"), TimeoutIntvl);
			SendMessage(WaitCondHndl, WM_SETTEXT, (WPARAM)0, (LPARAM)Buf);
			ShowWindow(WaitCondHndl, SW_SHOW);
			ShowWindow(ProceedNoDatRecvHndl, SW_SHOW);
			if (SelectedProceedNoDatRecv == 0) {
				SendMessage(ProceedNoDatRecvHndl, BM_SETCHECK, BST_UNCHECKED, 0L);
			} else {
				SendMessage(ProceedNoDatRecvHndl, BM_SETCHECK, BST_CHECKED, 0L);
			}
			ShowWindow(LenCondHndl, SW_HIDE);
			ShowWindow(SpecVarRecvHndl, SW_HIDE);
			ShowWindow(ChunkOptionHndl, SW_SHOW);
		} else {
			SendMessage(FinishCondHndl, CB_SETCURSEL, 4, 0);
			ShowWindow(LabelTimeoutIntvl, SW_SHOW);
			wsprintf(Buf, _T("%d"), TimeoutIntvl);
			SendMessage(WaitCondHndl, WM_SETTEXT, (WPARAM)0, (LPARAM)Buf);
			ShowWindow(WaitCondHndl, SW_SHOW);
			ShowWindow(ProceedNoDatRecvHndl, SW_SHOW);
			if (SelectedProceedNoDatRecv == 0) {
				SendMessage(ProceedNoDatRecvHndl, BM_SETCHECK, BST_UNCHECKED, 0L);
			} else {
				SendMessage(ProceedNoDatRecvHndl, BM_SETCHECK, BST_CHECKED, 0L);
			}
			wsprintf(Buf, _T("%d"), CondValue - 10000000);
			SendMessage(LenCondHndl, WM_SETTEXT, (WPARAM)0, (LPARAM)Buf);
			ShowWindow(LenCondHndl, SW_SHOW);
			ShowWindow(SpecVarRecvHndl, SW_HIDE);
			ShowWindow(ChunkOptionHndl, SW_HIDE);
		}
	}
}

void RecvInit(int CurrentId, int Type, HINSTANCE InstHndl, HWND WndHndl, UINT message, WPARAM wParam, LPARAM lParam)
{
	static int SelectedIcon = 0;
	static int SelectedOpeType = 0;
	static int SelectedTargetId = 0;
	static int SelectedCheck = 0;
	static int SelectedCondition = 0;
	static int SelectedProceedNoDatRecv = 0;

	TCHAR ComboMenu[10][64] = {_T("Desktop PC A"), _T("Rack servers"), _T("Midrange storage device"),
								_T("Server"), _T("Thin client"), _T("Mainframe A"),
								_T("Enterprise storage device"), _T("Mainframe B"), _T("Note PC"), _T("Desktop PC B")};

	TCHAR ComboFinishCond[6][128];
	lstrcpy(ComboFinishCond[0], MyMsgProc::GetMsg(MyMsgProc::PROP_NET_UNCOND));
	lstrcpy(ComboFinishCond[1], MyMsgProc::GetMsg(MyMsgProc::PROP_NET_CLOSEDETECT));
	lstrcpy(ComboFinishCond[2], MyMsgProc::GetMsg(MyMsgProc::PROP_NET_TIMEOUT));
	lstrcpy(ComboFinishCond[3], MyMsgProc::GetMsg(MyMsgProc::PROP_NET_RECVSTR));
	lstrcpy(ComboFinishCond[4], MyMsgProc::GetMsg(MyMsgProc::PROP_NET_EXCEEDSIZE));
	lstrcpy(ComboFinishCond[5], MyMsgProc::GetMsg(MyMsgProc::PROP_NET_HTTPCONTLEN));

	static const TCHAR* Receiver1 = MyMsgProc::GetMsg(MyMsgProc::PROP_NET_RECV);
	static const TCHAR* Receiver2 = MyMsgProc::GetMsg(MyMsgProc::PROP_NET_RECVTGT);
	static const TCHAR* Sender1 = MyMsgProc::GetMsg(MyMsgProc::PROP_NET_SEND);
	static const TCHAR* Sender2 = MyMsgProc::GetMsg(MyMsgProc::PROP_NET_SENDTGT);
	static const TCHAR* TargetSender = MyMsgProc::GetMsg(MyMsgProc::PROP_NET_SENDER);
	static const TCHAR* TargetRecver = MyMsgProc::GetMsg(MyMsgProc::PROP_NET_RECEIVER);
	static const TCHAR* CloseSender = MyMsgProc::GetMsg(MyMsgProc::PROP_NET_CLOSE_AFTERSEND);
	static const TCHAR* CloseRecver = MyMsgProc::GetMsg(MyMsgProc::PROP_NET_CLOSE_AFTERRECV);
	static const TCHAR* CloseForce = MyMsgProc::GetMsg(MyMsgProc::PROP_NET_CLOSEFORCE);

	static int IconOffset = 0;

	static TCHAR VarId[256];
	static int MaxIndex = 0;

	TCHAR Radio1[100];
	TCHAR Radio2[100];
	TCHAR Target[25];
	TCHAR CloseMsg[50];
	TCHAR CloseForceMsg[50];

	// Finish conditions for TCP receiver
	static HWND FinishCondHndl; // For combo box of receiver finish condition
	static HWND LabelTimeoutIntvl; // Timeout interval label
	static HWND WaitCondHndl; // For edit box of wait time
	static HWND ProceedNoDatRecvHndl;
	static HWND LenCondHndl; // For edit box of length
	static HWND SpecVarRecvHndl; // For combo box of comm-variables
	static HWND ChunkOptionHndl; // For chunk options

	// Drop down menu for finish condition "string"
	static int FinConVarIds[1000];
	static TCHAR FinConVarNames[1000][32];
	static int FinConVarCnt;

	if (Type == 1) {
		lstrcpy(Radio1, Receiver1);
		lstrcpy(Radio2, Receiver2);
		lstrcpy(Target, TargetSender);
		lstrcpy(CloseMsg, CloseRecver);
		lstrcpy(CloseForceMsg, CloseForce);
		IconOffset = 11;
	} else if (Type == 4) {
		lstrcpy(Radio1, Sender1);
		lstrcpy(Radio2, Sender2);
		lstrcpy(Target, TargetRecver);
		lstrcpy(CloseMsg, CloseSender);
		lstrcpy(CloseForceMsg, CloseForce);
		IconOffset = 21;
	} else if (Type == 7) {
		lstrcpy(Radio1, Sender1);
		lstrcpy(Radio2, Sender2);
		lstrcpy(Target, TargetRecver);
		lstrcpy(CloseMsg, CloseSender);
		lstrcpy(CloseForceMsg, CloseForce);
		IconOffset = 1;
	}

	RECT Rect;
	GetClientRect(WndHndl, &Rect);

	if (message == WM_CREATE) {
		CreateWindow(_T("STATIC"), MyMsgProc::GetMsg(MyMsgProc::PROP_NET_ICON), WS_CHILD | WS_VISIBLE, 100, 102, 80, 20, WndHndl, NULL, InstHndl, NULL);
		IconHndl = CreateWindowEx(WS_EX_CLIENTEDGE, _T("COMBOBOX"), _T(""), WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST | WS_VSCROLL, 190, 100, 200, 200, WndHndl, (HMENU)IDC_RECVINIT_ICON, InstHndl, NULL);
		RdoBtn1  = CreateWindow(_T("BUTTON"), Radio1, WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON, Rect.left + 10, 135, Rect.right - 20, 20, WndHndl, (HMENU)IDC_NET_OPETYPE_ID, InstHndl, NULL);
		CreateWindow(_T("STATIC"), MyMsgProc::GetMsg(MyMsgProc::PROP_NET_IPADDR), WS_CHILD | WS_VISIBLE, 50, 167, 140, 20, WndHndl, NULL, InstHndl, NULL);
		IpHndl   = CreateWindowEx(WS_EX_CLIENTEDGE, _T("EDIT"), _T(""), WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL, 190, 165, 200, 24, WndHndl, NULL, InstHndl, NULL);
		CreateWindow(_T("STATIC"), MyMsgProc::GetMsg(MyMsgProc::PROP_NET_PORT), WS_CHILD | WS_VISIBLE, 60, 202, 80, 20, WndHndl, NULL, InstHndl, NULL);
		PortHndl = CreateWindowEx(WS_EX_CLIENTEDGE, _T("EDIT"), _T(""), WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL, 190, 200, 70, 24, WndHndl, NULL, InstHndl, NULL);
		RdoBtn2  = CreateWindow(_T("BUTTON"), Radio2, WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON, Rect.left + 10, 230, Rect.right - 20, 20, WndHndl, (HMENU)IDC_NET_OPETYPE_SD, InstHndl, NULL);
		CreateWindow(_T("STATIC"), Target, WS_CHILD | WS_VISIBLE, 70, 262, 100, 20, WndHndl, NULL, InstHndl, NULL);
		SendHndl = CreateWindowEx(WS_EX_CLIENTEDGE, _T("COMBOBOX"), _T(""), WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST | WS_VSCROLL, 190, 260, 200, 200, WndHndl, (HMENU)IDC_NET_SENDER, InstHndl, NULL);

		if (Type == 1) {
			RdoBtn3  = CreateWindow(_T("BUTTON"), MyMsgProc::GetMsg(MyMsgProc::PROP_NET_RECVMULTI), WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON, Rect.left + 10, 290, Rect.right - 20, 20, WndHndl, (HMENU)IDC_NET_OPETYPE_RC, InstHndl, NULL);
			CreateWindow(_T("STATIC"), TargetRecver, WS_CHILD | WS_VISIBLE, 70, 322, 100, 20, WndHndl, NULL, InstHndl, NULL);
			RecvHndl = CreateWindowEx(WS_EX_CLIENTEDGE, _T("COMBOBOX"), _T(""), WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST | WS_VSCROLL, 190, 320, 200, 200, WndHndl, (HMENU)IDC_NET_RECEIVER, InstHndl, NULL);
		}

		CloseSockHndl = CreateWindow(_T("BUTTON"), CloseMsg, WS_CHILD | WS_VISIBLE | BS_CHECKBOX, 10, 355, 240, 20, WndHndl, (HMENU)IDC_NET_CLOSESOCK, InstHndl, NULL);
		CloseForceHndl = CreateWindow(_T("BUTTON"), CloseForceMsg, WS_CHILD | WS_VISIBLE | BS_CHECKBOX, 270, 355, 160, 20, WndHndl, (HMENU)IDC_NET_CLOSEFORCE, InstHndl, NULL);

		// If TCP receiver, finish condition can be specified.
		if (Type == 1) {
			CreateWindow(_T("STATIC"), MyMsgProc::GetMsg(MyMsgProc::PROP_NET_TERMCOND), WS_CHILD | WS_VISIBLE, 10, 387, 200, 20, WndHndl, NULL, InstHndl, NULL);
			FinishCondHndl = CreateWindowEx(WS_EX_CLIENTEDGE, _T("COMBOBOX"), _T(""), WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST | WS_VSCROLL, Rect.left + 20, 412, Rect.right - 30, 200, WndHndl, (HMENU)IDC_RECVINIT_FINISHCOND, InstHndl, NULL);
			for (int Loop = 0; Loop < 6; Loop++) {
				SendMessage(FinishCondHndl, CB_ADDSTRING, 0, (LPARAM)ComboFinishCond[Loop]);
			}
			SendMessage(FinishCondHndl, CB_SETCURSEL, 0, 0);

			LabelTimeoutIntvl = CreateWindow(_T("STATIC"), MyMsgProc::GetMsg(MyMsgProc::PROP_NET_TIMEOUTINTERVAL), WS_CHILD | WS_VISIBLE, Rect.left + 20, 477,
				GetMsgWidth(WndHndl, MyMsgProc::GetMsg(MyMsgProc::PROP_NET_TIMEOUTINTERVAL)) + 30,
				GetMsgHeight(WndHndl, MyMsgProc::GetMsg(MyMsgProc::PROP_NET_TIMEOUTINTERVAL)),
				WndHndl, NULL, InstHndl, NULL);
			WaitCondHndl = CreateWindowEx(WS_EX_CLIENTEDGE, _T("EDIT"), _T(""), WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL,
				Rect.left + 25 + GetMsgWidth(WndHndl, MyMsgProc::GetMsg(MyMsgProc::PROP_NET_TIMEOUTINTERVAL)), 475, 70, 24, WndHndl, NULL, InstHndl, NULL);
			SendMessage(WaitCondHndl, EM_SETLIMITTEXT, (WPARAM)6, (LPARAM)0);
			ProceedNoDatRecvHndl = CreateWindow(_T("BUTTON"), MyMsgProc::GetMsg(MyMsgProc::PROP_NET_PROCEEDEVENIFNODATARECV), WS_CHILD | WS_VISIBLE | BS_CHECKBOX, Rect.left + 205, 477, 
				GetMsgWidth(WndHndl, MyMsgProc::GetMsg(MyMsgProc::PROP_NET_PROCEEDEVENIFNODATARECV)) + 30, 
				GetMsgHeight(WndHndl, MyMsgProc::GetMsg(MyMsgProc::PROP_NET_PROCEEDEVENIFNODATARECV)), 
				WndHndl, (HMENU)IDC_RECVINIT_PROCEEDNODATRECV, InstHndl, NULL);

			LenCondHndl = CreateWindowEx(WS_EX_CLIENTEDGE, _T("EDIT"), _T(""), WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL, Rect.right - 80, 445, 70, 24, WndHndl, NULL, InstHndl, NULL);
			SendMessage(LenCondHndl, EM_SETLIMITTEXT, (WPARAM)7, (LPARAM)0);

			SpecVarRecvHndl = CreateWindowEx(WS_EX_CLIENTEDGE, _T("COMBOBOX"), _T(""), WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST | WS_VSCROLL, Rect.right - 240, 440, 230, 200, WndHndl, (HMENU)IDC_RECVINIT_RECVCOND, InstHndl, NULL);
			FinConVarCnt = VarCon_GetAllCommVariableNames(FinConVarIds, FinConVarNames);
			for (int Loop = 0; Loop < FinConVarCnt; Loop++) {
				SendMessage(SpecVarRecvHndl, CB_ADDSTRING, 0, (LPARAM)FinConVarNames[Loop]);
			}

			ChunkOptionHndl = CreateWindowEx(WS_EX_CLIENTEDGE, _T("COMBOBOX"), _T(""), WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST | WS_VSCROLL, Rect.right - 240, 440, 230, 200, WndHndl, (HMENU)IDC_RECVINIT_CHUNKOPT, InstHndl, NULL);
			//FinConVarCnt = VarCon_GetAllCommVariableNames(FinConVarIds, FinConVarNames);
			//for (int Loop = 0; Loop < FinConVarCnt; Loop++) {
			//	SendMessage(SpecVarRecvHndl, CB_ADDSTRING, 0, (LPARAM)FinConVarNames[Loop]);
			//}
		}

		// Length limitation for edit boxes of the IP address and the port
		SendMessage(IpHndl, EM_SETLIMITTEXT, (WPARAM)255, (LPARAM)0);
		SendMessage(PortHndl, EM_SETLIMITTEXT, (WPARAM)5, (LPARAM)0);

		// アイコン設用ドロップダウンリストの初期化
		for (int Loop = 0; Loop < 10; Loop++) {
			SendMessage(IconHndl, CB_ADDSTRING, 0, (LPARAM)ComboMenu[Loop]);
		}
		SelectedIcon = GetIconId(CurrentId);
		SendMessage(IconHndl, CB_SETCURSEL, SelectedIcon - IconOffset, 0);

		// 操作種別の初期化
		SelectedOpeType = GetOperationType(CurrentId);
		ChangeOperationType(SelectedOpeType);

		// Initialization of the target name
		{
			TCHAR TargetName[256][32];
			int TargetId[256];
			int MaxNum;
			if (Type == 1) {
				MaxNum = GetTargetNameArray(TargetName, TargetId, TRUE, FALSE, -1);
			} else {
				MaxNum = GetTargetNameArray(TargetName, TargetId, FALSE, TRUE, -1);
			}
			for (int Loop = 0; Loop < MaxNum; Loop++) {
				SendMessage(SendHndl, CB_ADDSTRING, 0, (LPARAM)TargetName[Loop]);
			}
			if (SelectedOpeType == 1) {
				SelectedTargetId = GetTargetId(CurrentId);
				for (int Loop = 0; Loop < MaxNum; Loop++) {
					if (TargetId[Loop] == SelectedTargetId) {
						SendMessage(SendHndl, CB_SETCURSEL, Loop, 0);
					}
				}
			}
		}

		// Initialization of the target name for multi accept
		if (Type == 1) {
			TCHAR TargetName[256][32];
			int TargetId[256];
			int MaxNum;
			MaxNum = GetTargetNameArray(TargetName, TargetId, FALSE, FALSE, CurrentId);
			for (int Loop = 0; Loop < MaxNum; Loop++) {
				SendMessage(RecvHndl, CB_ADDSTRING, 0, (LPARAM)TargetName[Loop]);
			}
			if (SelectedOpeType == 2) {
				SelectedTargetId = GetTargetId(CurrentId);
				for (int Loop = 0; Loop < MaxNum; Loop++) {
					if (TargetId[Loop] == SelectedTargetId) {
						SendMessage(RecvHndl, CB_SETCURSEL, Loop, 0);
					}
				}
			}
		}

		// Initialize for each finish conditions
		if (Type == 1) {
			TCHAR TmpBuf[256];
			LowDbAccess::GetInstance()->GetElementInfoParamStr(CurrentId, TmpBuf, 2);
			if (lstrcmp(TmpBuf, _T("PROCEED;")) == 0) {
				SelectedProceedNoDatRecv = 1;
			} else {
				SelectedProceedNoDatRecv = 0;
			}

			int CondValue = GetCondition(CurrentId);
			int TimeoutIntvl = GetTimeoutInterval(CurrentId);
			UpdateFinishCondition(CondValue, Type, FinishCondHndl, LabelTimeoutIntvl, WaitCondHndl, LenCondHndl, SpecVarRecvHndl, ProceedNoDatRecvHndl, ChunkOptionHndl, SelectedProceedNoDatRecv, TimeoutIntvl);
			if (CondValue < 0) {
				CondValue *= -1;
				for (int Loop = 0; Loop < FinConVarCnt; Loop++) {
					if (FinConVarIds[Loop] == CondValue) {
						SendMessage(SpecVarRecvHndl, CB_SETCURSEL, Loop, 0);
					}
				}
			}
		}

		// IP address/hostnameの初期化
		TCHAR IpAddrHostname[256];
		GetIpAddressOrHostname(CurrentId, IpAddrHostname);
		SendMessage(IpHndl, WM_SETTEXT, (WPARAM)0, (LPARAM)IpAddrHostname);

		// Portの初期化
		int PortNum = GetPortNumber(CurrentId);
		TCHAR Buf[10];
		wsprintf(Buf, _T("%d"), PortNum);
		SendMessage(PortHndl, WM_SETTEXT, (WPARAM)0, (LPARAM)Buf);

		// チェックボックスの初期化
		SelectedCheck = GetCloseSockCheck(CurrentId);
		if (SelectedCheck == 0) {
			SendMessage(CloseSockHndl, BM_SETCHECK, BST_UNCHECKED, 0L);
			SendMessage(CloseForceHndl, BM_SETCHECK, BST_UNCHECKED, 0L);
			EnableWindow(CloseForceHndl, FALSE);
		} else if (SelectedCheck == 1) {
			SendMessage(CloseSockHndl, BM_SETCHECK, BST_CHECKED, 0L);
			SendMessage(CloseForceHndl, BM_SETCHECK, BST_CHECKED, 0L);
			EnableWindow(CloseForceHndl, TRUE);
		} else if (SelectedCheck == 2) {
			SendMessage(CloseSockHndl, BM_SETCHECK, BST_CHECKED, 0L);
			SendMessage(CloseForceHndl, BM_SETCHECK, BST_UNCHECKED, 0L);
			EnableWindow(CloseForceHndl, TRUE);
		}
	}
	if (message == WM_COMMAND) {
		if (HIWORD(wParam) == CBN_SELCHANGE) {
			if (LOWORD(wParam) == IDC_RECVINIT_ICON) {
				SelectedIcon = (int)SendMessage(IconHndl, CB_GETCURSEL, 0, 0) + IconOffset;
			}
			if (LOWORD(wParam) == IDC_NET_SENDER) {
				TCHAR TargetName[256][32];
				int TargetId[256];
				if (Type == 1) {
					GetTargetNameArray(TargetName, TargetId, TRUE, FALSE, -1);
				} else {
					GetTargetNameArray(TargetName, TargetId, FALSE, TRUE, -1);
				}
				int TmpIndex = (int)SendMessage(SendHndl, CB_GETCURSEL, 0, 0);
				SelectedTargetId = TargetId[TmpIndex];
			}
			if (LOWORD(wParam) == IDC_NET_RECEIVER) {
				TCHAR TargetName[256][32];
				int TargetId[256];
				if (Type == 1) {
					GetTargetNameArray(TargetName, TargetId, FALSE, FALSE, CurrentId);
				}
				int TmpIndex = (int)SendMessage(RecvHndl, CB_GETCURSEL, 0, 0);
				SelectedTargetId = TargetId[TmpIndex];
			}
			if (LOWORD(wParam) == IDC_RECVINIT_FINISHCOND) {
				int SelectedFinishCond = (int)SendMessage(FinishCondHndl, CB_GETCURSEL, 0, 0);
				int CondValue = 0;
				int TimeoutIntvl = 0;
				if (SelectedFinishCond == 0) {
					CondValue = 0;
					TimeoutIntvl = 0;
					SelectedProceedNoDatRecv = 0;
				} else if (SelectedFinishCond == 1) {
					CondValue = 2;
					TimeoutIntvl = 0;
					SelectedProceedNoDatRecv = 0;
				} else if (SelectedFinishCond == 2) {
					CondValue = 1;
					TimeoutIntvl = 500;
					SelectedProceedNoDatRecv = 0;
				} else if (SelectedFinishCond == 3) {
					CondValue = -1;
					TimeoutIntvl = 500;
					SelectedProceedNoDatRecv = 0;
				} else if (SelectedFinishCond == 4) {
					CondValue = 10000001;
					TimeoutIntvl = 500;
					SelectedProceedNoDatRecv = 0;
				} else if (SelectedFinishCond == 5) {
					CondValue = 3;
					TimeoutIntvl = 500;
					SelectedProceedNoDatRecv = 0;
				} else {
				}
				UpdateFinishCondition(CondValue, Type, FinishCondHndl, LabelTimeoutIntvl, WaitCondHndl, LenCondHndl, SpecVarRecvHndl, ProceedNoDatRecvHndl, ChunkOptionHndl, 0, TimeoutIntvl);
			}
		}
		if (HIWORD(wParam) == BN_CLICKED) {
			if (LOWORD(wParam) == IDC_NET_CLOSESOCK) {
				if (SelectedCheck == 0) {
					SelectedCheck = 2;
					SendMessage(CloseSockHndl, BM_SETCHECK, BST_CHECKED, 0L);
					SendMessage(CloseForceHndl, BM_SETCHECK, BST_UNCHECKED, 0L);
					EnableWindow(CloseForceHndl, TRUE);
				} else if (SelectedCheck == 1 || SelectedCheck == 2) {
					SelectedCheck = 0;
					SendMessage(CloseSockHndl, BM_SETCHECK, BST_UNCHECKED, 0L);
					SendMessage(CloseForceHndl, BM_SETCHECK, BST_UNCHECKED, 0L);
					EnableWindow(CloseForceHndl, FALSE);
				}
			}
			if (LOWORD(wParam) == IDC_NET_CLOSEFORCE) {
				if (SelectedCheck == 1) {
					SelectedCheck = 2;
					SendMessage(CloseForceHndl, BM_SETCHECK, BST_UNCHECKED, 0L);
					EnableWindow(CloseForceHndl, TRUE);
				} else if (SelectedCheck == 2) {
					SelectedCheck = 1;
					SendMessage(CloseForceHndl, BM_SETCHECK, BST_CHECKED, 0L);
					EnableWindow(CloseForceHndl, TRUE);
				}
			}
			if (LOWORD(wParam) == IDC_RECVINIT_PROCEEDNODATRECV) {
				if (SelectedProceedNoDatRecv == 0) {
					SendMessage(ProceedNoDatRecvHndl, BM_SETCHECK, BST_CHECKED, 0L);
					SelectedProceedNoDatRecv = 1;
				} else {
					SendMessage(ProceedNoDatRecvHndl, BM_SETCHECK, BST_UNCHECKED, 0L);
					SelectedProceedNoDatRecv = 0;
				}
			}
			if (LOWORD(wParam) == IDC_BTNOK) {
				SetIconId(CurrentId, SelectedIcon);
				SetCondition(CurrentId, SelectedCondition);
				SetOperationType(CurrentId, SelectedOpeType);
				SetTargetId(CurrentId, SelectedTargetId);
				SetCloseSockCheck(CurrentId, SelectedCheck);
				TCHAR IpAddrHostname[256];
				SendMessage(IpHndl, WM_GETTEXT, (WPARAM)256, (LPARAM)IpAddrHostname);
				SetIpAddressOrHostname(CurrentId, IpAddrHostname);

				TCHAR PortNum[10];
				SendMessage(PortHndl, WM_GETTEXT, (WPARAM)10, (LPARAM)PortNum);
				int PortNumber = StrToInt(PortNum);
				if (PortNumber < 0) {
					PortNumber = 0;
				}
				if (PortNumber > 65535) {
					PortNumber = 65535;
				}
				SetPortNumber(CurrentId, PortNumber);

				// Set finish condition
				if (Type == 1) {
					TCHAR CondDummyStr[10];

					int SelFinCnd = (int)SendMessage(FinishCondHndl, CB_GETCURSEL, 0, 0);
					if (SelFinCnd == 0) {
						SetCondition(CurrentId, 0);
						SetTimeoutInterval(CurrentId, 0);
					} else if (SelFinCnd == 1) {
						SetCondition(CurrentId, 2);
						SetTimeoutInterval(CurrentId, 0);
					} else if (SelFinCnd == 2) {
						SetCondition(CurrentId, 1);
						SendMessage(WaitCondHndl, WM_GETTEXT, (WPARAM)10, (LPARAM)CondDummyStr);
						int CondDummy = StrToInt(CondDummyStr);
						if (CondDummy < 0) {
							CondDummy = 0;
						}
						if (CondDummy > 180000) {
							CondDummy = 180000;
						}
						SetTimeoutInterval(CurrentId, CondDummy);
					} else if (SelFinCnd == 3) {
						int SelFinCnd = (int)SendMessage(SpecVarRecvHndl, CB_GETCURSEL, 0, 0);
						int CondDummy = FinConVarIds[SelFinCnd];
						if (CondDummy == 0) {
							CondDummy = -1;
						} else {
							CondDummy *= -1;
						}
						SetCondition(CurrentId, CondDummy);
						SendMessage(WaitCondHndl, WM_GETTEXT, (WPARAM)10, (LPARAM)CondDummyStr);
						CondDummy = StrToInt(CondDummyStr);
						if (CondDummy < 0) {
							CondDummy = 0;
						}
						if (CondDummy > 180000) {
							CondDummy = 180000;
						}
						SetTimeoutInterval(CurrentId, CondDummy);
					} else if (SelFinCnd == 4) {
						SendMessage(LenCondHndl, WM_GETTEXT, (WPARAM)10, (LPARAM)CondDummyStr);
						int CondDummy = StrToInt(CondDummyStr);
						if (CondDummy < 1) {
							CondDummy = 1;
						}
						if (CondDummy > 9999999) {
							CondDummy = 9999999;
						}
						CondDummy += 10000000;
						SetCondition(CurrentId, CondDummy);
						SendMessage(WaitCondHndl, WM_GETTEXT, (WPARAM)10, (LPARAM)CondDummyStr);
						CondDummy = StrToInt(CondDummyStr);
						if (CondDummy < 0) {
							CondDummy = 0;
						}
						if (CondDummy > 180000) {
							CondDummy = 180000;
						}
						SetTimeoutInterval(CurrentId, CondDummy);
					} else if (SelFinCnd == 5) {
						SetCondition(CurrentId, 3);
						SendMessage(WaitCondHndl, WM_GETTEXT, (WPARAM)10, (LPARAM)CondDummyStr);
						int CondDummy = StrToInt(CondDummyStr);
						if (CondDummy < 0) {
							CondDummy = 0;
						}
						if (CondDummy > 180000) {
							CondDummy = 180000;
						}
						SetTimeoutInterval(CurrentId, CondDummy);
					} else {
					}
					if (SelectedProceedNoDatRecv == 1) {
						LowDbAccess::GetInstance()->SetElementInfoParamStr(CurrentId, _T("PROCEED;"), 2);
					} else {
						LowDbAccess::GetInstance()->SetElementInfoParamStr(CurrentId, _T(""), 2);
					}
				}
			}
			if (LOWORD(wParam) == IDC_BTNCANCEL) {
			}
			if (LOWORD(wParam) == IDC_NET_OPETYPE_ID) {
				ChangeOperationType(0);
				SelectedOpeType = 0;
			}
			if (LOWORD(wParam) == IDC_NET_OPETYPE_SD) {
				ChangeOperationType(1);
				SelectedOpeType = 1;
			}
			if (LOWORD(wParam) == IDC_NET_OPETYPE_RC) {
				ChangeOperationType(2);
				SelectedOpeType = 2;
			}
		}
	}
}
