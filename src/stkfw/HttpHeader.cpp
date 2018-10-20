#include <windows.h>
#include <tchar.h>
#include <cwchar>
#include <cstring>
#include "resource.h"
#include "MyMsgProc.h"
#include "server\LowDbAccess.h"
#include "server\VarController.h"

#define HTTPHD_TARGET_DATE 1
#define HTTPHD_TARGET_CONTLEN 2
#define HTTPHD_TARGET_REQUEST 3
#define HTTPHD_TARGET_RESPONSE 4

#define HTTPHD_LEN 1024

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

wchar_t HttpHeaderEdBox[HTTPHD_LEN] = L"HTTP/1.1 200 OK\r\n";

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

void UpdateHttpHeaderEdBox(int target, bool Enable)
{
	wchar_t HttpHeaderEdBoxTmp[HTTPHD_LEN] = L"";
	wchar_t* tmp_ptr = HttpHeaderEdBoxTmp;
	wchar_t* begin_ptr = NULL;
	wchar_t* end_ptr = NULL;
	SendMessage(HttpHeaderEd, WM_GETTEXT, (WPARAM)HTTPHD_LEN, (LPARAM)HttpHeaderEdBox);

	wchar_t search_target[32] = L"";
	wchar_t replace_target[64] = L"";
	if (target == HTTPHD_TARGET_DATE) {
		wcscpy_s(search_target, 32, L"Date: ");
		wcscpy_s(replace_target, 64, L"Date: <automatically replaced>\r\n");
	}
	if (target == HTTPHD_TARGET_CONTLEN) {
		wcscpy_s(search_target, 32, L"Content-Length: ");
		wcscpy_s(replace_target, 64, L"Content-Length: <automatically replaced>\r\n");
	}

	if (target == HTTPHD_TARGET_REQUEST) {
		wcscpy_s(search_target, 32, L"");
		wcscpy_s(replace_target, 64, L"GET / HTTP/1.1\r\n");

		if (wcsncmp(HttpHeaderEdBox, L"GET", 3) == 0 ||
			wcsncmp(HttpHeaderEdBox, L"HEAD", 4) == 0 ||
			wcsncmp(HttpHeaderEdBox, L"POST", 4) == 0 ||
			wcsncmp(HttpHeaderEdBox, L"PUT", 3) == 0 ||
			wcsncmp(HttpHeaderEdBox, L"DELETE", 5) == 0 ||
			wcsncmp(HttpHeaderEdBox, L"CONNECT", 6) == 0 ||
			wcsncmp(HttpHeaderEdBox, L"OPTIONS", 6) == 0 ||
			wcsncmp(HttpHeaderEdBox, L"TRACE", 5) == 0 ||
			wcsncmp(HttpHeaderEdBox, L"PATCH", 5) == 0) {
			begin_ptr = HttpHeaderEdBox;
		}
	} else if (target == HTTPHD_TARGET_RESPONSE) {
		wcscpy_s(search_target, 32, L"");
		wcscpy_s(replace_target, 64, L"HTTP/1.1 200 OK\r\n");

		if (wcsncmp(HttpHeaderEdBox, L"HTTP/", 5) == 0) {
			begin_ptr = HttpHeaderEdBox;
		}
	} else {
		begin_ptr = wcsstr(HttpHeaderEdBox, search_target);
	}
	if (begin_ptr) {
		end_ptr = wcsstr(begin_ptr, L"\r\n");
	}
	if (begin_ptr && end_ptr) {
		for (wchar_t* i = HttpHeaderEdBox; i < begin_ptr; i++) {
			*tmp_ptr = *i;
			if (tmp_ptr - HttpHeaderEdBoxTmp == HTTPHD_LEN - 1) {
				*tmp_ptr = L'\0';
			} else {
				tmp_ptr++;
			}
		}
		if (Enable) {
			if (tmp_ptr - HttpHeaderEdBoxTmp + wcslen(replace_target) + 1 <= HTTPHD_LEN - 1) {
				wcscpy_s(tmp_ptr, wcslen(replace_target) + 1, replace_target);
				tmp_ptr += wcslen(replace_target);
			}
		}
		for (wchar_t* i = end_ptr + 2; *i != '\0'; i++) {
			*tmp_ptr = *i;
			if (tmp_ptr - HttpHeaderEdBoxTmp == HTTPHD_LEN - 1) {
				*tmp_ptr = L'\0';
			} else {
				tmp_ptr++;
			}
		}
	} else {
		if (Enable && target != HTTPHD_TARGET_REQUEST && target != HTTPHD_TARGET_RESPONSE) {
			wcsncpy(HttpHeaderEdBoxTmp, HttpHeaderEdBox, HTTPHD_LEN - 1);
			if (wcslen(HttpHeaderEdBoxTmp) + wcslen(replace_target) < HTTPHD_LEN) {
				wcscat(HttpHeaderEdBoxTmp, replace_target);
			}
		} else if (Enable && (target == HTTPHD_TARGET_REQUEST || target == HTTPHD_TARGET_RESPONSE)) {
			wcsncpy(HttpHeaderEdBoxTmp, replace_target, HTTPHD_LEN - 1);
			if (wcslen(HttpHeaderEdBoxTmp) + wcslen(HttpHeaderEdBox) < HTTPHD_LEN) {
				wcscat(HttpHeaderEdBoxTmp, HttpHeaderEdBox);
			}
		} else {
			wcsncpy(HttpHeaderEdBoxTmp, HttpHeaderEdBox, HTTPHD_LEN - 1);
		}
	}
	SendMessage(HttpHeaderEd, WM_SETTEXT, (WPARAM)0, (LPARAM)HttpHeaderEdBoxTmp);
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
		SendMessage(HttpHeaderEd, EM_SETLIMITTEXT, (WPARAM)HTTPHD_LEN - 1, (LPARAM)0);
		int intput_bin = 0;
		LowDbAccess::GetInstance()->GetHttpHeaderInfo(CurrentId, &intput_bin, HttpHeaderEdBox);
		if (intput_bin & 0x01) {
			HttpHdDelHttpFlag = true;
		}
		if (intput_bin & 0x02) {
			HttpHdAddHttpFlag = true;
		}
		if (intput_bin & 0x04) {
			HttpHdContentLenFlag = true;
		}
		if (intput_bin & 0x08) {
			HttpHdDateFlag = true;
		}
		if (intput_bin & 0x10) {
			HttpHdRequestFlag = true;
		}
		ChangeHttpHeader();
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
				UpdateHttpHeaderEdBox(HTTPHD_TARGET_CONTLEN, HttpHdContentLenFlag);
			}
			if (LOWORD(wParam) == IDC_HTTPHD_DATE) {
				if (HttpHdDateFlag == false) {
					HttpHdDateFlag = true;
				} else {
					HttpHdDateFlag = false;
				}
				UpdateHttpHeaderEdBox(HTTPHD_TARGET_DATE, HttpHdDateFlag);
			}
			if (LOWORD(wParam) == IDC_HTTPHD_REQUEST) {
				if (!HttpHdRequestFlag) {
					UpdateHttpHeaderEdBox(HTTPHD_TARGET_RESPONSE, false);
					UpdateHttpHeaderEdBox(HTTPHD_TARGET_REQUEST, true);
					HttpHdRequestFlag = true;
				}
			}
			if (LOWORD(wParam) == IDC_HTTPHD_RESPONSE) {
				if (HttpHdRequestFlag) {
					UpdateHttpHeaderEdBox(HTTPHD_TARGET_REQUEST, false);
					UpdateHttpHeaderEdBox(HTTPHD_TARGET_RESPONSE, true);
					HttpHdRequestFlag = false;
				}
			}
			ChangeHttpHeader();
			if (LOWORD(wParam) == IDC_BTNOK) {
				int input_bin = 0;
				input_bin += (HttpHdDelHttpFlag ? 0x01 : 0);
				input_bin += (HttpHdAddHttpFlag ? 0x02 : 0);
				input_bin += (HttpHdContentLenFlag ? 0x04 : 0);
				input_bin += (HttpHdDateFlag ? 0x08 : 0);
				input_bin += (HttpHdRequestFlag ? 0x10 : 0);
				SendMessage(HttpHeaderEd, WM_GETTEXT, (WPARAM)HTTPHD_LEN, (LPARAM)HttpHeaderEdBox);
				LowDbAccess::GetInstance()->UpdateHttpHeaderInfo(CurrentId, input_bin, HttpHeaderEdBox);
			}
		}
	}
}
