#include <windows.h>
#include <tchar.h>
#include "resource.h"
#include "MyMsgProc.h"
#include "server\LowDbAccess.h"
#include "server\VarController.h"

int GetMsgWidth(HWND WndHndl, TCHAR* Msg);
int GetMsgHeight(HWND WndHndl, TCHAR* Msg);

void HttpHeader(int CurrentId, int Type, HINSTANCE InstHndl, HWND WndHndl, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (message == WM_CREATE) {
		HWND DelHttpHeader = NULL;
		HWND AddHttpHeader = NULL;

		DelHttpHeader = CreateWindow(_T("BUTTON"), MyMsgProc::GetMsg(MyMsgProc::PROP_HTTPHEADER_DELETEFROM), WS_CHILD | WS_VISIBLE | BS_CHECKBOX, 10, 100,
			GetMsgWidth(WndHndl, MyMsgProc::GetMsg(MyMsgProc::PROP_HTTPHEADER_DELETEFROM)) + 30,
			GetMsgHeight(WndHndl, MyMsgProc::GetMsg(MyMsgProc::PROP_HTTPHEADER_DELETEFROM)),
			WndHndl, (HMENU)IDC_NET_CLOSESOCK, InstHndl, NULL);
		AddHttpHeader = CreateWindow(_T("BUTTON"), MyMsgProc::GetMsg(MyMsgProc::PROP_HTTPHEADER_INSERTINTO), WS_CHILD | WS_VISIBLE | BS_CHECKBOX, 10, 130,
			GetMsgWidth(WndHndl, MyMsgProc::GetMsg(MyMsgProc::PROP_HTTPHEADER_INSERTINTO)) + 30,
			GetMsgHeight(WndHndl, MyMsgProc::GetMsg(MyMsgProc::PROP_HTTPHEADER_INSERTINTO)),
			WndHndl, (HMENU)IDC_NET_CLOSESOCK, InstHndl, NULL);
	}
}
