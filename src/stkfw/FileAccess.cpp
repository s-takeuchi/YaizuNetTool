#include <windows.h>
#include <tchar.h>
#include <shlwapi.h>
#include "resource.h"
#include "server\VarController.h"
#include "MyMsgProc.h"
#include "server\LowDbAccess.h"

// �A�N�Z�X��ʂɊւ��郉�W�I�{�^���̃`�F�b�N��؂�ւ���
// Type: in: �A�N�Z�X���(0: �㏑��, 1:�}��, 2:�A��)
// FileAcAddHndl: in: �A���p���W�I�{�^���n���h��
// FileAcOverwHndl: in: �㏑���p���W�I�{�^���n���h��
// FileAcInsertHndl: in: �}���p���W�I�{�^���n���h��
// �߂�l: �Ȃ�
void ChangeAccessType(int Type, HWND FileAcAddHndl, HWND FileAcOverwHndl, HWND FileAcInsertHndl)
{
	if (Type == 0) {
		SendMessage(FileAcAddHndl, BM_SETCHECK, BST_UNCHECKED, 0L);
		SendMessage(FileAcOverwHndl, BM_SETCHECK, BST_CHECKED, 0L);
		SendMessage(FileAcInsertHndl, BM_SETCHECK, BST_UNCHECKED, 0L);
	}
	if (Type == 1) {
		SendMessage(FileAcAddHndl, BM_SETCHECK, BST_UNCHECKED, 0L);
		SendMessage(FileAcOverwHndl, BM_SETCHECK, BST_UNCHECKED, 0L);
		SendMessage(FileAcInsertHndl, BM_SETCHECK, BST_CHECKED, 0L);
	}
	if (Type == 2) {
		SendMessage(FileAcAddHndl, BM_SETCHECK, BST_CHECKED, 0L);
		SendMessage(FileAcOverwHndl, BM_SETCHECK, BST_UNCHECKED, 0L);
		SendMessage(FileAcInsertHndl, BM_SETCHECK, BST_UNCHECKED, 0L);
	}
}

void FileAccess(int CurrentId, int Type, HINSTANCE InstHndl, HWND WndHndl, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HWND FileNameEditHndl;
	static HWND FileAcAddHndl;
	static HWND FileAcOverwHndl;
	static HWND FileAcInsertHndl;
	RECT Rect;
	GetClientRect(WndHndl, &Rect);
	static int AccessType = 0;

	if (message == WM_CREATE) {
		// �t�@�C���p�X�̐ݒ�
		CreateWindow(_T("STATIC"), MyMsgProc::GetMsg(MyMsgProc::PROP_FILEACCESS_NAME), WS_CHILD | WS_VISIBLE, Rect.left + 40, 110, Rect.right - 60, 60, WndHndl, NULL, InstHndl, NULL);
		FileNameEditHndl = CreateWindowEx(WS_EX_CLIENTEDGE, _T("EDIT"), _T(""), WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL, 200, 180, 250, 24, WndHndl, NULL, InstHndl, NULL);
		SendMessage(FileNameEditHndl, EM_SETLIMITTEXT, (WPARAM)254, (LPARAM)0);
		TCHAR BufPath[256];
		LowDbAccess::GetInstance()->GetElementInfoParamStr(CurrentId, BufPath, 1);
		SendMessage(FileNameEditHndl, WM_SETTEXT, (WPARAM)0, (LPARAM)BufPath);
		// �������ݎ�ʂ̐ݒ�
		int OverwMsg;
		int AddMsg;
		int InsertMsg;
		if (Type == 18) {
			OverwMsg = MyMsgProc::PROP_FILEACCESSW_OVERWRITE;
			AddMsg = MyMsgProc::PROP_FILEACCESSW_ADD;
			InsertMsg = MyMsgProc::PROP_FILEACCESSW_INSERT;
		} else {
			OverwMsg = MyMsgProc::PROP_FILEACCESSR_OVERWRITE;
			AddMsg = MyMsgProc::PROP_FILEACCESSR_ADD;
			InsertMsg = MyMsgProc::PROP_FILEACCESSR_INSERT;
		}
		FileAcOverwHndl = CreateWindow(_T("BUTTON"), MyMsgProc::GetMsg(OverwMsg), WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON, 40, 220, 350, 20, WndHndl, (HMENU)IDC_FILEAC_OVERWRITE, InstHndl, NULL);
		FileAcInsertHndl = CreateWindow(_T("BUTTON"), MyMsgProc::GetMsg(InsertMsg), WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON, 40, 250, 350, 20, WndHndl, (HMENU)IDC_FILEAC_INSERT, InstHndl, NULL);
		FileAcAddHndl = CreateWindow(_T("BUTTON"), MyMsgProc::GetMsg(AddMsg), WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON, 40, 280, 350, 20, WndHndl, (HMENU)IDC_FILEAC_ADD, InstHndl, NULL);
		AccessType = LowDbAccess::GetInstance()->GetElementInfoParamInt(CurrentId, 1);
		ChangeAccessType(AccessType, FileAcAddHndl, FileAcOverwHndl, FileAcInsertHndl);
	}
	if (message == WM_COMMAND) {
		if (HIWORD(wParam) == BN_CLICKED) {
			// �������ݎ�ʂ̕ύX�����m
			if (LOWORD(wParam) == IDC_FILEAC_OVERWRITE) {
				ChangeAccessType(0, FileAcAddHndl, FileAcOverwHndl, FileAcInsertHndl);
				AccessType = 0;
			}
			if (LOWORD(wParam) == IDC_FILEAC_INSERT) {
				ChangeAccessType(1, FileAcAddHndl, FileAcOverwHndl, FileAcInsertHndl);
				AccessType = 1;
			}
			if (LOWORD(wParam) == IDC_FILEAC_ADD) {
				ChangeAccessType(2, FileAcAddHndl, FileAcOverwHndl, FileAcInsertHndl);
				AccessType = 2;
			}
			// OK�{�^�����������m
			if (LOWORD(wParam) == IDC_BTNOK) {
				TCHAR BufPath[256];
				SendMessage(FileNameEditHndl, WM_GETTEXT, (WPARAM)255, (LPARAM)BufPath);
				LowDbAccess::GetInstance()->SetElementInfoParamStr(CurrentId, BufPath, 1);
				LowDbAccess::GetInstance()->SetElementInfoParamInt(CurrentId, AccessType, 1);
			}
		}
	}
}
