#include <winsock2.h>
#include "..\..\..\YaizuComLib\src\\stksocket\stksocket.h"
#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <shlwapi.h>
#include "resource.h"
#include "server\ApiObj.h"
#include "server\ExecElemMgr.h"
#include "server\LowDbAccess.h"
#include "MyMsgProc.h"
#include "StkProp.h"
#include "..\..\..\YaizuComLib\src\\stkthread\stkthread.h"
#include "..\..\..\YaizuComLib\src\\stkthreadgui\stkthreadgui.h"
#include "..\..\..\YaizuComLib\src\\commonfunc\StkObject.h"


void RecvInit(int, int, HINSTANCE, HWND, UINT, WPARAM, LPARAM);
void StoreData(int, int, HINSTANCE, HWND, UINT, WPARAM, LPARAM);
void CheckData(int, int, HINSTANCE, HWND, UINT, WPARAM, LPARAM);
void ChgData(int, int, HINSTANCE, HWND, UINT, WPARAM, LPARAM);
void CloseSock(int, int, HINSTANCE, HWND, UINT, WPARAM, LPARAM);
void Timer(int, int, HINSTANCE, HWND, UINT, WPARAM, LPARAM);
void Mapper(int, int, HINSTANCE, HWND, UINT, WPARAM, LPARAM);
void CheckFlag(int, int, HINSTANCE, HWND, UINT, WPARAM, LPARAM);
void ChangeFlag(int, int, HINSTANCE, HWND, UINT, WPARAM, LPARAM);
void FileAccess(int, int, HINSTANCE, HWND, UINT, WPARAM, LPARAM);
void ExecProg(int, int, HINSTANCE, HWND, UINT, WPARAM, LPARAM);
void UdpRecvSend(int, int, HINSTANCE, HWND, UINT, WPARAM, LPARAM);

HINSTANCE StkPropInstHndl;
int CurrentId;

void GetTypeName(int Type, TCHAR TypeName[64])
{
	TCHAR TypeNames[23][64] = {
		_T("TCP receiver [Initiator]"),
		_T("Load data [Initiator]"),
		_T("Empty box [Initiator]"),
		_T("TCP sender [Terminator]"),
		_T("Store data [Terminator]"),
		_T("Empty box [Terminator]"),
		_T("TCP sender [Stopper]"),
		_T("Store data [Stopper]"),
		_T("Empty box [Stopper]"),
		_T("Check flag [Check point]"),
		_T("Check data [Check point]"),
		_T("Timer [Check point]"),
		_T("Change flag [Action]"),
		_T("Change data [Action]"),
		_T("Aggregation/Distribution [Action]"),
		_T("Close port [Action]"),
		_T("Mapper [Action]"),
		_T("Write file [Action]"),
		_T("Read file [Action]"),
		_T("Execute program [Action]"),
		_T("UDP receiver [Initiator]"),
		_T("UDP sender [Terminator]"),
		_T("UDP sender [Stopper]")
	};
	lstrcpy(TypeName, TypeNames[Type]);
}

BOOL CALLBACK StkPropSetFontProc(HWND hwnd, LPARAM lParam)
{
	static HFONT FontHndl = CreateFont(16, 0, 0, 0, FW_REGULAR, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_DONTCARE, _T("Arial"));
	SendMessage(hwnd, WM_SETFONT, (WPARAM)FontHndl, (LPARAM)TRUE);
	return TRUE;
}

void PropTypeProc(HWND WndHndl, UINT message, WPARAM wParam, LPARAM lParam)
{
	int Type = LowDbAccess::GetInstance()->GetViewElementTypeFromId(CurrentId);

	// TCP Sender または TCP Receiver のディスパッチ処理
	if (Type == 1 || Type == 4 || Type == 7) {
		RecvInit(CurrentId, Type, StkPropInstHndl, WndHndl, message, wParam, lParam);
	}
	// Store data または LoadDataのディスパッチ処理
	if (Type == 2 || Type == 5 || Type == 8) {
		StoreData(CurrentId, Type, StkPropInstHndl, WndHndl, message, wParam, lParam);
	}
	// Check flagのディスパッチ処理
	if (Type == 10) {
		CheckFlag(CurrentId, Type, StkPropInstHndl, WndHndl, message, wParam, lParam);
	}
	// Check dataのディスパッチ処理
	if (Type == 11) {
		CheckData(CurrentId, Type, StkPropInstHndl, WndHndl, message, wParam, lParam);
	}
	if (Type == 12) {
		Timer(CurrentId, Type, StkPropInstHndl, WndHndl, message, wParam, lParam);
	}
	// Change flagのディスパッチ処理
	if (Type == 13) {
		ChangeFlag(CurrentId, Type, StkPropInstHndl, WndHndl, message, wParam, lParam);
	}
	// Change dataのディスパッチ処理
	if (Type == 14) {
		ChgData(CurrentId, Type, StkPropInstHndl, WndHndl, message, wParam, lParam);
	}
	// Close portのディスパッチ処理
	if (Type == 16) {
		CloseSock(CurrentId, Type, StkPropInstHndl, WndHndl, message, wParam, lParam);
	}
	// Mapperのディスパッチ処理
	if (Type == 17) {
		Mapper(CurrentId, Type, StkPropInstHndl, WndHndl, message, wParam, lParam);
	}
	// Write file, Read fileのディスパッチ処理
	if (Type == 18 || Type == 19) {
		FileAccess(CurrentId, Type, StkPropInstHndl, WndHndl, message, wParam, lParam);
	}
	// Execute external program
	if (Type == 20) {
		ExecProg(CurrentId, Type, StkPropInstHndl, WndHndl, message, wParam, lParam);
	}
	// UDP Sender または UDP Receiver のディスパッチ処理
	if (Type == 21 || Type == 22 || Type == 23) {
		UdpRecvSend(CurrentId, Type, StkPropInstHndl, WndHndl, message, wParam, lParam);
	}

	if (message == WM_CREATE) {
		EnumChildWindows(WndHndl, StkPropSetFontProc, NULL);
	}
}

LRESULT CALLBACK PropProc(HWND WndHndl, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HWND BkGndWndHndl;
	static HWND BtmGndWndHndl;
	static HWND TextWndHndl;
	static HWND BmpWndHndl;
	static HWND NameTextHndl;
	static HWND NameEditHndl;
	static HWND IdTextHndl;
	static HWND IdEditHndl;
	static HWND OkButton;
	static HWND CancelButton;

	static int RetCode = 0; // 0:OK, -1:Canceled // ##10085

	HBITMAP PropBitMap;
	RECT Rect;

	TCHAR TypeName[64];

	switch (message) {
	case WM_CREATE:
		GetClientRect(WndHndl, &Rect);

		GetTypeName(LowDbAccess::GetInstance()->GetViewElementTypeFromId(CurrentId) - 1, TypeName);

		BkGndWndHndl  = CreateWindow(_T("STATIC"), _T(""), WS_CHILD | WS_VISIBLE, 0, 0, 520, 470, WndHndl, NULL, StkPropInstHndl, NULL);
		BtmGndWndHndl = CreateWindow(_T("STATIC"), _T(""), WS_CHILD | WS_VISIBLE | WS_DLGFRAME, Rect.left, 50, Rect.right, Rect.bottom - 50, WndHndl, NULL, StkPropInstHndl, NULL);
		TextWndHndl   = CreateWindow(_T("STATIC"), TypeName, WS_CHILD | WS_VISIBLE, 20, 32, 430, 18, WndHndl, NULL, StkPropInstHndl, NULL);
		BmpWndHndl    = CreateWindow(_T("STATIC"), _T(""), WS_CHILD | WS_VISIBLE | SS_BITMAP, 0, 0, 30, 2048, WndHndl, NULL, StkPropInstHndl, NULL);
		IdTextHndl    = CreateWindow(_T("STATIC"), _T("ID"), WS_CHILD | WS_VISIBLE, 20, 62, 20, 20, WndHndl, NULL, StkPropInstHndl, NULL);
		IdEditHndl    = CreateWindowEx(WS_EX_CLIENTEDGE, _T("EDIT"), _T(""), WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL, 40, 60, 50, 24, WndHndl, NULL, StkPropInstHndl, NULL);
		NameTextHndl  = CreateWindow(_T("STATIC"), MyMsgProc::GetMsg(MyMsgProc::PROP_NAME), WS_CHILD | WS_VISIBLE, 180, 62, 40, 20, WndHndl, NULL, StkPropInstHndl, NULL);
		NameEditHndl  = CreateWindowEx(WS_EX_CLIENTEDGE, _T("EDIT"), _T(""), WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL, 225, 60, 270, 24, WndHndl, NULL, StkPropInstHndl, NULL);
		OkButton      = CreateWindow(_T("BUTTON"), _T("OK"), WS_CHILD | WS_VISIBLE, Rect.right - 180, Rect.bottom - 40, 80, 30, WndHndl, (HMENU)IDC_BTNOK, StkPropInstHndl, NULL);
		CancelButton  = CreateWindow(_T("BUTTON"), _T("Cancel"), WS_CHILD | WS_VISIBLE, Rect.right - 90, Rect.bottom - 40, 80, 30, WndHndl, (HMENU)IDC_BTNCANCEL, StkPropInstHndl, NULL);

		// ビットマップの設定
		PropBitMap = LoadBitmap(StkPropInstHndl, MAKEINTRESOURCE(IDB_BITMAP1));
		SendMessage(BmpWndHndl, STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)PropBitMap);

		// ID表示用エディットボックスの設定
		{
			SendMessage(IdEditHndl, EM_SETREADONLY, (WPARAM)TRUE, (LPARAM)0);
			TCHAR IdEditBuf[20];
			wsprintf(IdEditBuf, _T("%d"), CurrentId);
			SendMessage(IdEditHndl, WM_SETTEXT, (WPARAM)0, (LPARAM)IdEditBuf);
		}

		// Name編集用エディットボックスの設定
		TCHAR Name[32];
		LowDbAccess::GetInstance()->GetViewElementNameFromId(CurrentId, Name);
		SendMessage(NameEditHndl, WM_SETTEXT, (WPARAM)0, (LPARAM)Name);
		SendMessage(NameEditHndl, EM_SETLIMITTEXT, (WPARAM)31, (LPARAM)0);

		EnumChildWindows(WndHndl, StkPropSetFontProc, NULL);

		PropTypeProc(WndHndl, message, wParam, lParam);
		return 0;
	case WM_COMMAND:
		if (HIWORD(wParam) == BN_CLICKED) {
			if (LOWORD(wParam) == IDC_BTNOK) {
				TCHAR NameStr[32];
				GetWindowText(NameEditHndl, NameStr, 32);
				LowDbAccess::GetInstance()->UpdateViewElementName(CurrentId, NameStr);
				PropTypeProc(WndHndl, message, wParam, lParam);
				RetCode = 0; // ##10085
				DestroyWindow(WndHndl);
				return 0;
			}
			if (LOWORD(wParam) == IDC_BTNCANCEL) {
				PropTypeProc(WndHndl, message, wParam, lParam);
				RetCode = -1; // ##10085
				DestroyWindow(WndHndl);
				return 0;
			}
		}
		// タイプ毎の表示切り替え処理を呼び出す
		PropTypeProc(WndHndl, message, wParam, lParam);
		return DefWindowProc(WndHndl, message, wParam, lParam);
	case WM_CLOSE:
		RetCode = -1; // ##10085
		DestroyWindow(WndHndl);
		PropTypeProc(WndHndl, message, wParam, lParam);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(RetCode); // ##10085
		PropTypeProc(WndHndl, message, wParam, lParam);
		return 0;
	default:
		// タイプ毎の表示切り替え処理を呼び出す
		PropTypeProc(WndHndl, message, wParam, lParam);
		return DefWindowProc(WndHndl, message, wParam, lParam);
	}
	// タイプ毎の表示切り替え処理を呼び出す
	PropTypeProc(WndHndl, message, wParam, lParam);
	return 0;
}

void StkPropSetIconToWnd(HWND TargetWndHndl)
{
	static HICON IconHndlrS = NULL;
	static HICON IconHndlrB = NULL;
	if (IconHndlrS == NULL) {
		IconHndlrS = (HICON)LoadImage(StkPropInstHndl, (LPCTSTR)IDI_ICON0, IMAGE_ICON, 16, 16, LR_DEFAULTCOLOR);
	}
	if (IconHndlrB == NULL) {
		IconHndlrB = (HICON)LoadImage(StkPropInstHndl, (LPCTSTR)IDI_ICON0, IMAGE_ICON, 32, 32, LR_DEFAULTCOLOR);
	}
	if (IconHndlrS != NULL && IconHndlrB != NULL) {
		SendMessage(TargetWndHndl, WM_SETICON, ICON_SMALL, (LPARAM)IconHndlrS);
		SendMessage(TargetWndHndl, WM_SETICON, ICON_BIG, (LPARAM)IconHndlrB);
	}
}

int ShowProperty() // ##10085 戻り値を変更
{
	MSG msg;

	WNDCLASSEX wcex;
	wcex.cbSize        = sizeof(WNDCLASSEX); 
	wcex.style         = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc   = (WNDPROC)PropProc;
	wcex.cbClsExtra    = 0;
	wcex.cbWndExtra    = 0;
	wcex.hInstance     = StkPropInstHndl;
	wcex.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
	wcex.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);
	wcex.hCursor       = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName  = NULL;
	wcex.lpszClassName = _T("Properties");
	RegisterClassEx(&wcex);

	HWND WndHndl = CreateWindow(_T("Properties"), _T("Properties"), WS_CAPTION | WS_SYSMENU | WS_DLGFRAME, CW_USEDEFAULT, CW_USEDEFAULT, 520, 580, GetForegroundWindow(), NULL, StkPropInstHndl, NULL);
	ShowWindow(WndHndl, SW_SHOW);
	UpdateWindow(WndHndl);
	StkPropSetIconToWnd(WndHndl);
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}

void SyncElementInfoAndViewElement()
{
	LowDbAccess::GetInstance()->UpdateElementInfoFromViewElement();
}

int DllShowProperty(int Id) // ##10085 戻り値を変更
{
	CurrentId = Id;
	StkPropInstHndl = GetModuleHandle(NULL);
	SyncElementInfoAndViewElement();
	return ShowProperty();
}

void AddAllSocketInfo()
{
	SyncElementInfoAndViewElement();

	ExecElemMgr* ExecMgr = ExecElemMgr::GetInstance();

	// StkSocketMgr初期化
	// 0: Receiver, 1: Sender-Stopper, 2: Sender-Terminator, 21: UDP-Receiver, 22: UDP-Sender-Terminator, 23: UDP-Sender-Stopper
	int TmpIds[6][256];
	int NumOfElem[6];
	// Receiver, Senderの全IDを取得する
	NumOfElem[0] = LowDbAccess::GetInstance()->GetViewElementIds(TmpIds[0], 1);
	NumOfElem[1] = LowDbAccess::GetInstance()->GetViewElementIds(TmpIds[1], 7);
	NumOfElem[2] = LowDbAccess::GetInstance()->GetViewElementIds(TmpIds[2], 4);
	NumOfElem[3] = LowDbAccess::GetInstance()->GetViewElementIds(TmpIds[3], 21);
	NumOfElem[4] = LowDbAccess::GetInstance()->GetViewElementIds(TmpIds[4], 22);
	NumOfElem[5] = LowDbAccess::GetInstance()->GetViewElementIds(TmpIds[5], 23);
	// ReceiverとSenderの合計が最大値を超えた場合
	if (NumOfElem[0] + NumOfElem[1] + NumOfElem[2] + NumOfElem[3] + NumOfElem[4] + NumOfElem[5] >= 256) {
		return;
	}
	// SocketInfoメンバ配列を生成する
	TCHAR TmpHostOrIpAddr[256];
	int TmpPort;
	for (int LoopType = 0; LoopType < 6; LoopType++ ) {
		for (int Loop = 0; Loop < NumOfElem[LoopType]; Loop++) {
			if (LowDbAccess::GetInstance()->GetHostIpAddrPort(TmpIds[LoopType][Loop], TmpHostOrIpAddr, &TmpPort) == 0 &&
				LowDbAccess::GetInstance()->GetTcpRecvOperationTypeInElementInfo(TmpIds[LoopType][Loop]) == 0) { // Listen socket case
				if (LoopType <= 2) {
					StkSocket_AddInfo(TmpIds[LoopType][Loop], STKSOCKET_TYPE_STREAM, (LoopType == 0)? STKSOCKET_ACTIONTYPE_RECEIVER : STKSOCKET_ACTIONTYPE_SENDER, TmpHostOrIpAddr, TmpPort);
				} else {
					StkSocket_AddInfo(TmpIds[LoopType][Loop], STKSOCKET_TYPE_DGRAM, (LoopType == 3)? STKSOCKET_ACTIONTYPE_RECEIVER : STKSOCKET_ACTIONTYPE_SENDER, TmpHostOrIpAddr, TmpPort);
				}
			} else if (LowDbAccess::GetInstance()->GetTcpRecvOperationTypeInElementInfo(TmpIds[LoopType][Loop]) == 2) { // Accept socket case
				if (LoopType <= 2) {
					int CorrId = LowDbAccess::GetInstance()->GetTcpRecvCorrespodingIdInElementInfo(TmpIds[LoopType][Loop]);
					LowDbAccess::GetInstance()->GetHostIpAddrPort(CorrId, TmpHostOrIpAddr, &TmpPort);
					if (StkSocket_GetStatus(CorrId) == -1) {
						StkSocket_AddInfo(CorrId, STKSOCKET_TYPE_STREAM, (LoopType == 0)? STKSOCKET_ACTIONTYPE_RECEIVER : STKSOCKET_ACTIONTYPE_SENDER, TmpHostOrIpAddr, TmpPort);
					}
					StkSocket_CopyInfo(TmpIds[LoopType][Loop], CorrId);
				}
			}
		}
	}
}

void DeleteAllSocketInfo()
{
	ExecElemMgr* ExecMgr = ExecElemMgr::GetInstance();

	// StkSocketMgr終了処理
	// 0: Receiver, 1: Sender-Stopper, 2: Sender-Terminator
	int TmpIds[6][256];
	int NumOfElem[6];
	// Receiverの全IDを取得する
	NumOfElem[0] = LowDbAccess::GetInstance()->GetViewElementIds(TmpIds[0], 1);
	NumOfElem[1] = LowDbAccess::GetInstance()->GetViewElementIds(TmpIds[1], 7);
	NumOfElem[2] = LowDbAccess::GetInstance()->GetViewElementIds(TmpIds[2], 4);
	NumOfElem[3] = LowDbAccess::GetInstance()->GetViewElementIds(TmpIds[3], 21);
	NumOfElem[4] = LowDbAccess::GetInstance()->GetViewElementIds(TmpIds[4], 22);
	NumOfElem[5] = LowDbAccess::GetInstance()->GetViewElementIds(TmpIds[5], 23);
	// ReceiverとSenderの合計が最大値を超えた場合
	if (NumOfElem[0] + NumOfElem[1] + NumOfElem[2] +NumOfElem[3] + NumOfElem[4] + NumOfElem[5] >= 256) {
		return;
	}
	// SocketInfoメンバ配列から要素を削除する
	for (int LoopType = 0; LoopType < 6; LoopType++ ) {
		for (int Loop = 0; Loop < NumOfElem[LoopType]; Loop++) {
			StkSocket_DeleteInfo(TmpIds[LoopType][Loop]);
		}
	}
}

int ElemStkThreadInit(int Id)
{
	SyncElementInfoAndViewElement();

	ExecElemMgr* ExecMgr = ExecElemMgr::GetInstance();

	// ExecElemMgr初期化
	ExecMgr->AddExecElem(Id);
	ExecMgr->ThreadStatusChangedIntoStart(Id);

	return 0;
}

int ElemStkThreadFinal(int Id)
{
	ExecElemMgr* ExecMgr = ExecElemMgr::GetInstance();

	// ExecElemMgr最終処理
	ExecMgr->ThreadStatusChangedIntoStop(Id);
	ExecMgr->ClearLineType(Id);
	ExecMgr->DeleteExecElem(Id);

	return 0;
}

int ElemStkThreadMain(int Id)
{
	// If other thread(s) is/are in starting status, wait for the completion of other thread(s).
	int Num;
	do {
		Num = GetNumOfStartingStkThread();
		if (Num != 0) {
			Sleep(10);
		}
	} while(Num);

	ExecElemMgr* ExecMgr = ExecElemMgr::GetInstance();
	ExecMgr->ExecuteElement(Id);
	return 0;
}

int ElemStkThreadStart(int Id)
{
	StkObject* ReqObj = new StkObject(L"");
	StkObject* ReqObjTs = new StkObject(L"threadStatus", L"start");
	StkObject* ReqObjId = new StkObject(L"id", Id);
	ReqObj->AppendChildElement(ReqObjId);
	ReqObj->AppendChildElement(ReqObjTs);
	ApiObj* Obj = ApiObj::CreateObject(ApiObj::METHOD_POST, L"/api/thread/");
	int StatusCode = 0;
	Obj->Execute(ReqObj, ApiObj::METHOD_POST, L"/api/thread/", &StatusCode);
	delete Obj;
	delete ReqObj;
	return 0;
}

int ElemStkThreadStop(int Id)
{
	StkObject* ReqObj = new StkObject(L"");
	StkObject* ReqObjTs = new StkObject(L"threadStatus", L"stop");
	StkObject* ReqObjId = new StkObject(L"id", Id);
	ReqObj->AppendChildElement(ReqObjId);
	ReqObj->AppendChildElement(ReqObjTs);
	ApiObj* Obj = ApiObj::CreateObject(ApiObj::METHOD_POST, L"/api/thread/");
	int StatusCode = 0;
	Obj->Execute(ReqObj, ApiObj::METHOD_POST, L"/api/thread/", &StatusCode);
	delete Obj;
	delete ReqObj;
	return 0;
}
