#include <windows.h>
#include <tchar.h>
#include <cwchar>
#include <cstring>
#include "resource.h"
#include "MyMsgProc.h"
#include "server\LowDbAccess.h"
#include "server\VarController.h"


int GetMsgWidth(HWND WndHndl, TCHAR* Msg);
int GetMsgHeight(HWND WndHndl, TCHAR* Msg);

HWND HttpHdDelHttp = NULL;
bool HttpHdDelHttpFlag = false;
HWND HttpHdAddHttp = NULL;
bool HttpHdAddHttpFlag = false;
HWND HttpHdContentLen = NULL;
bool HttpHdContentLenFlag = false;
HWND HttpHdDate = NULL;
bool HttpHdDateFlag = false;
HWND HttpHdRequest = NULL;
bool HttpHdRequestFlag = false;
HWND HttpHdResponse = NULL;
HWND HttpHeaderEd = NULL;

wchar_t HttpHeaderEdBox[1024] = L"hello";

void ChangeHttpHeader()
{
	if (HttpHdDelHttpFlag == true) {
		SendMessage(HttpHdDelHttp, BM_SETCHECK, BST_CHECKED, 0L);
		EnableWindow(HttpHdDelHttp, true);
	} else {
		SendMessage(HttpHdDelHttp, BM_SETCHECK, BST_UNCHECKED, 0L);
		EnableWindow(HttpHdDelHttp, true);
	}
	bool HttpHdFlag = false;
	if (HttpHdAddHttpFlag == false) {
		HttpHdFlag = false;
		SendMessage(HttpHdAddHttp, BM_SETCHECK, BST_UNCHECKED, 0L);
		EnableWindow(HttpHdAddHttp, true);
	} else {
		HttpHdFlag = true;
		SendMessage(HttpHdAddHttp, BM_SETCHECK, BST_CHECKED, 0L);
		EnableWindow(HttpHdAddHttp, true);
	}
	EnableWindow(HttpHdContentLen, HttpHdFlag);
	EnableWindow(HttpHdDate, HttpHdFlag);
	EnableWindow(HttpHdRequest, HttpHdFlag);
	EnableWindow(HttpHdResponse, HttpHdFlag);
	EnableWindow(HttpHeaderEd, HttpHdFlag);
	SendMessage(HttpHdContentLen, BM_SETCHECK, (HttpHdContentLenFlag == false) ? BST_UNCHECKED : BST_CHECKED, 0L);
	SendMessage(HttpHdDate, BM_SETCHECK, (HttpHdDateFlag == false) ? BST_UNCHECKED : BST_CHECKED, 0L);
	SendMessage(HttpHdRequest, BM_SETCHECK, (HttpHdRequestFlag == false) ? BST_UNCHECKED : BST_CHECKED, 0L);
	SendMessage(HttpHdResponse, BM_SETCHECK, (HttpHdRequestFlag == true) ? BST_UNCHECKED : BST_CHECKED, 0L);
}

void UpdateHttpHeaderEdBoxForDate(bool Enable)
{
	wchar_t HttpHeaderEdBoxTmp[1024] = L"";
	wchar_t* tmp_ptr = HttpHeaderEdBoxTmp;
	wchar_t* begin_ptr = NULL;
	wchar_t* end_ptr = NULL;
	SendMessage(HttpHeaderEd, WM_GETTEXT, (WPARAM)1024, (LPARAM)HttpHeaderEdBox);
	begin_ptr = wcsstr(HttpHeaderEdBox, L"Date");
	if (begin_ptr) {
		end_ptr = wcsstr(begin_ptr, L"\r\n");
	}
	if (begin_ptr && end_ptr) {
		//memcpy((char*)HttpHeaderEdBoxTmp, (char*)HttpHeaderEdBox, (char*)begin_ptr - (char*)HttpHeaderEdBox);
		for (wchar_t* i = HttpHeaderEdBox; i < begin_ptr; i++) {
			*tmp_ptr = *i;
			tmp_ptr++;
		}
		for (wchar_t* i = end_ptr + 2; *i != '\0'; i++) {
			*tmp_ptr = *i;
			tmp_ptr++;
		}
		SendMessage(HttpHeaderEd, WM_SETTEXT, (WPARAM)0, (LPARAM)HttpHeaderEdBoxTmp);
	}
}

void HttpHeader(int CurrentId, int Type, HINSTANCE InstHndl, HWND WndHndl, UINT message, WPARAM wParam, LPARAM lParam)
{
	RECT Rect;
	GetClientRect(WndHndl, &Rect);

	if (message == WM_CREATE) {
		HttpHdDelHttp = CreateWindow(_T("BUTTON"), MyMsgProc::GetMsg(MyMsgProc::PROP_HTTPHEADER_DELETEFROM), WS_CHILD | WS_VISIBLE | BS_CHECKBOX, 10, 100,
			GetMsgWidth(WndHndl, MyMsgProc::GetMsg(MyMsgProc::PROP_HTTPHEADER_DELETEFROM)) + 30,
			GetMsgHeight(WndHndl, MyMsgProc::GetMsg(MyMsgProc::PROP_HTTPHEADER_DELETEFROM)),
			WndHndl, (HMENU)IDC_HTTPHD_DELETE, InstHndl, NULL);
		HttpHdAddHttp = CreateWindow(_T("BUTTON"), MyMsgProc::GetMsg(MyMsgProc::PROP_HTTPHEADER_INSERTINTO), WS_CHILD | WS_VISIBLE | BS_CHECKBOX, 10, 130,
			GetMsgWidth(WndHndl, MyMsgProc::GetMsg(MyMsgProc::PROP_HTTPHEADER_INSERTINTO)) + 30,
			GetMsgHeight(WndHndl, MyMsgProc::GetMsg(MyMsgProc::PROP_HTTPHEADER_INSERTINTO)),
			WndHndl, (HMENU)IDC_HTTPHD_ADD, InstHndl, NULL);
		HttpHdContentLen = CreateWindow(_T("BUTTON"), MyMsgProc::GetMsg(MyMsgProc::PROP_HTTPHEADER_CONTLEN), WS_CHILD | WS_VISIBLE | BS_CHECKBOX, 40, 160,
			GetMsgWidth(WndHndl, MyMsgProc::GetMsg(MyMsgProc::PROP_HTTPHEADER_CONTLEN)) + 30,
			GetMsgHeight(WndHndl, MyMsgProc::GetMsg(MyMsgProc::PROP_HTTPHEADER_CONTLEN)),
			WndHndl, (HMENU)IDC_HTTPHD_CONTLEN, InstHndl, NULL);
		HttpHdDate = CreateWindow(_T("BUTTON"), MyMsgProc::GetMsg(MyMsgProc::PROP_HTTPHEADER_DATE), WS_CHILD | WS_VISIBLE | BS_CHECKBOX, 40, 190,
			GetMsgWidth(WndHndl, MyMsgProc::GetMsg(MyMsgProc::PROP_HTTPHEADER_DATE)) + 30,
			GetMsgHeight(WndHndl, MyMsgProc::GetMsg(MyMsgProc::PROP_HTTPHEADER_DATE)),
			WndHndl, (HMENU)IDC_HTTPHD_DATE, InstHndl, NULL);
		HttpHdRequest = CreateWindow(_T("BUTTON"), MyMsgProc::GetMsg(MyMsgProc::PROP_HTTPHEADER_REQUEST), WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON, 40, 220,
			GetMsgWidth(WndHndl, MyMsgProc::GetMsg(MyMsgProc::PROP_HTTPHEADER_REQUEST)) + 30,
			GetMsgHeight(WndHndl, MyMsgProc::GetMsg(MyMsgProc::PROP_HTTPHEADER_REQUEST)),
			WndHndl, (HMENU)IDC_HTTPHD_REQUEST, InstHndl, NULL);
		HttpHdResponse = CreateWindow(_T("BUTTON"), MyMsgProc::GetMsg(MyMsgProc::PROP_HTTPHEADER_RESPONSE), WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON, 40, 250,
			GetMsgWidth(WndHndl, MyMsgProc::GetMsg(MyMsgProc::PROP_HTTPHEADER_RESPONSE)) + 30,
			GetMsgHeight(WndHndl, MyMsgProc::GetMsg(MyMsgProc::PROP_HTTPHEADER_RESPONSE)),
			WndHndl, (HMENU)IDC_HTTPHD_RESPONSE, InstHndl, NULL);
		HttpHeaderEd = CreateWindowEx(WS_EX_CLIENTEDGE, _T("EDIT"), _T(""), WS_CHILD | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL | ES_AUTOHSCROLL | ES_AUTOVSCROLL | ES_MULTILINE, Rect.left + 40, 280, Rect.right - 50, 210, WndHndl, NULL, InstHndl, NULL);
		SendMessage(HttpHeaderEd, EM_SETLIMITTEXT, (WPARAM)1024, (LPARAM)0);
		SendMessage(HttpHeaderEd, WM_SETTEXT, (WPARAM)0, (LPARAM)HttpHeaderEdBox);

		ChangeHttpHeader();
	}
	if (message == WM_COMMAND) {
		if (HIWORD(wParam) == BN_CLICKED) {
			if (LOWORD(wParam) == IDC_HTTPHD_DELETE) {
				if (HttpHdDelHttpFlag == false) {
					HttpHdDelHttpFlag = true;
				} else {
					HttpHdDelHttpFlag = false;
				}
			}
			if (LOWORD(wParam) == IDC_HTTPHD_ADD) {
				if (HttpHdAddHttpFlag == false) {
					HttpHdAddHttpFlag = true;
				} else {
					HttpHdAddHttpFlag = false;
				}
			}
			if (LOWORD(wParam) == IDC_HTTPHD_CONTLEN) {
				if (HttpHdContentLenFlag == false) {
					HttpHdContentLenFlag = true;
				} else {
					HttpHdContentLenFlag = false;
				}
			}
			if (LOWORD(wParam) == IDC_HTTPHD_DATE) {
				if (HttpHdDateFlag == false) {
					HttpHdDateFlag = true;
				} else {
					HttpHdDateFlag = false;
				}
				UpdateHttpHeaderEdBoxForDate(HttpHdDateFlag);
			}
			if (LOWORD(wParam) == IDC_HTTPHD_REQUEST) {
				HttpHdRequestFlag = true;
			}
			if (LOWORD(wParam) == IDC_HTTPHD_RESPONSE) {
				HttpHdRequestFlag = false;
			}
			ChangeHttpHeader();
		}
	}
}
