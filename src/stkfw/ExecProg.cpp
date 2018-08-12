#include <windows.h>
#include <tchar.h>
#include <shlwapi.h>
#include "resource.h"
#include "server\VarController.h"
#include "MyMsgProc.h"
#include "server\LowDbAccess.h"


void ExecProg(int CurrentId, int Type, HINSTANCE InstHndl, HWND WndHndl, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HWND ProgNameHndl;
	static HWND CurrDirHndl;
	static HWND CheckWaitHndl;
	static HWND CheckStdoutHndl;
	static HWND CheckStdinHndl;

	static int SelectedCheck = 0;

	RECT Rect;
	GetClientRect(WndHndl, &Rect);

	if (message == WM_CREATE) {
		CreateWindow(_T("STATIC"), MyMsgProc::GetMsg(MyMsgProc::PROP_EXECPROG_COMMAND), WS_CHILD | WS_VISIBLE, 40, 100, 400, 20, WndHndl, NULL, InstHndl, NULL);
		ProgNameHndl = CreateWindowEx(WS_EX_CLIENTEDGE, _T("EDIT"), _T(""), WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL, 80, 125, 380, 24, WndHndl, NULL, InstHndl, NULL);
		SendMessage(ProgNameHndl, EM_SETLIMITTEXT, (WPARAM)254, (LPARAM)0);
		CreateWindow(_T("STATIC"), MyMsgProc::GetMsg(MyMsgProc::PROP_EXECPROG_CURRDIR), WS_CHILD | WS_VISIBLE, 40, 160, 400, 60, WndHndl, NULL, InstHndl, NULL);
		CurrDirHndl = CreateWindowEx(WS_EX_CLIENTEDGE, _T("EDIT"), _T(""), WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL, 80, 220, 380, 24, WndHndl, NULL, InstHndl, NULL);
		SendMessage(CurrDirHndl, EM_SETLIMITTEXT, (WPARAM)254, (LPARAM)0);
		CheckWaitHndl = CreateWindow(_T("BUTTON"), MyMsgProc::GetMsg(MyMsgProc::PROP_EXECPROG_WAIT), WS_CHILD | WS_VISIBLE | BS_CHECKBOX, Rect.left + 20, 260, Rect.right - 40, 20, WndHndl, (HMENU)IDC_EXECPROG_WAIT, InstHndl, NULL);
		CheckStdoutHndl = CreateWindow(_T("BUTTON"), MyMsgProc::GetMsg(MyMsgProc::PROP_EXECPROG_STDOUT), WS_CHILD | WS_VISIBLE | BS_CHECKBOX, Rect.left + 20, 290, Rect.right - 40, 20, WndHndl, (HMENU)IDC_EXECPROG_STDOUT, InstHndl, NULL);
		CheckStdinHndl = CreateWindow(_T("BUTTON"), MyMsgProc::GetMsg(MyMsgProc::PROP_EXECPROG_STDIN), WS_CHILD | WS_VISIBLE | BS_CHECKBOX, Rect.left + 20, 320, Rect.right - 40, 20, WndHndl, (HMENU)IDC_EXECPROG_STDIN, InstHndl, NULL);

		TCHAR BufPath[256];
		LowDbAccess::GetInstance()->GetElementInfoParamStr(CurrentId, BufPath, 1);
		SendMessage(ProgNameHndl, WM_SETTEXT, (WPARAM)0, (LPARAM)BufPath);
		LowDbAccess::GetInstance()->GetElementInfoParamStr(CurrentId, BufPath, 2);
		SendMessage(CurrDirHndl, WM_SETTEXT, (WPARAM)0, (LPARAM)BufPath);

		SelectedCheck = LowDbAccess::GetInstance()->GetElementInfoParamInt(CurrentId, 1);
		if (SelectedCheck & 0x00000001) {
			SendMessage(CheckWaitHndl, BM_SETCHECK, BST_CHECKED, 0L);
			EnableWindow(CheckStdoutHndl, TRUE);
		} else {
			SendMessage(CheckWaitHndl, BM_SETCHECK, BST_UNCHECKED, 0L);
			EnableWindow(CheckStdoutHndl, FALSE);
		}
		if (SelectedCheck & 0x00000002) {
			SendMessage(CheckStdoutHndl, BM_SETCHECK, BST_CHECKED, 0L);
		} else {
			SendMessage(CheckStdoutHndl, BM_SETCHECK, BST_UNCHECKED, 0L);
		}
		if (SelectedCheck & 0x00000004) {
			SendMessage(CheckStdinHndl, BM_SETCHECK, BST_CHECKED, 0L);
		} else {
			SendMessage(CheckStdinHndl, BM_SETCHECK, BST_UNCHECKED, 0L);
		}
	}
	if (message == WM_COMMAND) {
		if (HIWORD(wParam) == BN_CLICKED) {
			if (LOWORD(wParam) == IDC_EXECPROG_WAIT) {
				if (SelectedCheck & 0x00000001) {
					SelectedCheck &= 0xfffffffe;
					SendMessage(CheckWaitHndl, BM_SETCHECK, BST_UNCHECKED, 0L);
					EnableWindow(CheckStdoutHndl, FALSE);
				} else {
					SelectedCheck |= 0x00000001;
					SendMessage(CheckWaitHndl, BM_SETCHECK, BST_CHECKED, 0L);
					EnableWindow(CheckStdoutHndl, TRUE);
				}
			}
			if (LOWORD(wParam) == IDC_EXECPROG_STDOUT) {
				if (SelectedCheck & 0x00000002) {
					SelectedCheck &= 0xfffffffd;
					SendMessage(CheckStdoutHndl, BM_SETCHECK, BST_UNCHECKED, 0L);
				} else {
					SelectedCheck |= 0x00000002;
					SendMessage(CheckStdoutHndl, BM_SETCHECK, BST_CHECKED, 0L);
				}
			}
			if (LOWORD(wParam) == IDC_EXECPROG_STDIN) {
				if (SelectedCheck & 0x00000004) {
					SelectedCheck &= 0xfffffffb;
					SendMessage(CheckStdinHndl, BM_SETCHECK, BST_UNCHECKED, 0L);
				} else {
					SelectedCheck |= 0x00000004;
					SendMessage(CheckStdinHndl, BM_SETCHECK, BST_CHECKED, 0L);
				}
			}
			if (LOWORD(wParam) == IDC_BTNOK) {
				TCHAR BufPath[256];
				SendMessage(ProgNameHndl, WM_GETTEXT, (WPARAM)255, (LPARAM)BufPath);
				LowDbAccess::GetInstance()->SetElementInfoParamStr(CurrentId, BufPath, 1);
				SendMessage(CurrDirHndl, WM_GETTEXT, (WPARAM)255, (LPARAM)BufPath);
				LowDbAccess::GetInstance()->SetElementInfoParamStr(CurrentId, BufPath, 2);
				LowDbAccess::GetInstance()->SetElementInfoParamInt(CurrentId, SelectedCheck, 1);
			}
		}
	}
}
