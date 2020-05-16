#include <windows.h>
#include <shlobj.h>
#include "resource.h"
#include "tchar.h"
#include "..\..\..\YaizuComLib\src\commonfunc\msgproc.h"
#include <Lm.h>

int LBA_FIRSTINFO = 1101;
int LBA_PROCCALLFAILED = 1102;
int LBA_ALREADYINSTALLED = 1103;
int LBA_NOTINSTALLED = 1104;
int LBA_OPECOMPLETED = 1105;
int NEEDADMINRIGHTS = 2903;


HINSTANCE InstHndl;

typedef BOOL (WINAPI *LPFN_ISWOW64PROCESS) (HANDLE, PBOOL);

int RunCommand(HWND DlgHndl, int OperationCode)
{
	TCHAR CmdName[40];

	lstrcpy(CmdName, _T("lbadpt64.exe "));
	switch (OperationCode) {
	case 0:
		lstrcat(CmdName, _T("get"));
		break;
	case 1:
		lstrcat(CmdName, _T("install"));
		break;
	case -1:
		lstrcat(CmdName, _T("remove"));
		break;
	}

	PROCESS_INFORMATION pi;
	STARTUPINFO si;
	ZeroMemory(&si,sizeof(si));
	si.cb=sizeof(si);
	if (CreateProcess(NULL, CmdName, NULL, NULL, FALSE, NORMAL_PRIORITY_CLASS, NULL, NULL, &si, &pi) == 0) {
		//MessageProc::StkErr(LBA_PROCCALLFAILED, DlgHndl);
		TCHAR Buf[32];
		wsprintf(Buf, _T("Message ID : %d"), LBA_PROCCALLFAILED);
		MessageBox(DlgHndl, MessageProc::GetMsg(LBA_PROCCALLFAILED), Buf, MB_OK | MB_ICONSTOP);
		return -1;
	}
	DWORD RetCode;
	do {
		Sleep(500);
		GetExitCodeProcess(pi.hProcess, &RetCode);
	} while (RetCode == STILL_ACTIVE);

	return RetCode;
}

void ShowInformation(HWND DlgHndl)
{
	HWND InstallHndl = GetDlgItem(DlgHndl, IDC_INSTALL);
	HWND removeHndl = GetDlgItem(DlgHndl, IDC_REMOVE);
	int AdptStatus = RunCommand(DlgHndl, 0);
	if (AdptStatus == -1) {
		return;
	} else if (AdptStatus == 10) {
		SetDlgItemText(DlgHndl, IDC_STATUS, MessageProc::GetMsg(LBA_ALREADYINSTALLED));
		EnableWindow(InstallHndl, FALSE);
		EnableWindow(removeHndl, TRUE);
	} else {
		SetDlgItemText(DlgHndl, IDC_STATUS, MessageProc::GetMsg(LBA_NOTINSTALLED));
		EnableWindow(InstallHndl, TRUE);
		EnableWindow(removeHndl, FALSE);
	}
}

INT_PTR CALLBACK LbAdptDlg(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	HICON IconHndlrS;
	HICON IconHndlrB;

	HWND InstallHndl = GetDlgItem(hDlg, IDC_INSTALL);
	HWND removeHndl = GetDlgItem(hDlg, IDC_REMOVE);

	switch (message)
	{
	case WM_INITDIALOG:
		{
			EnableWindow(InstallHndl, FALSE);
			EnableWindow(removeHndl, FALSE);
			IconHndlrS = (HICON)LoadImage(InstHndl, (LPCTSTR)IDI_LBADPT, IMAGE_ICON, 16, 16, LR_DEFAULTCOLOR);
			IconHndlrB = (HICON)LoadImage(InstHndl, (LPCTSTR)IDI_LBADPT, IMAGE_ICON, 32, 32, LR_DEFAULTCOLOR);
			SendMessage(hDlg, WM_SETICON, ICON_SMALL, (LPARAM)IconHndlrS);
			SendMessage(hDlg, WM_SETICON, ICON_BIG, (LPARAM)IconHndlrB);
			SetDlgItemText(hDlg, IDC_TEXT, MessageProc::GetMsg(LBA_FIRSTINFO));
			ShowInformation(hDlg);
		}
		break;
	case WM_COMMAND:
		{
			if (LOWORD(wParam) == IDCANCEL) {
				EndDialog(hDlg, (INT_PTR)0);
				return (INT_PTR)TRUE;
			}
			if (LOWORD(wParam) == IDC_INSTALL) {
				EnableWindow(InstallHndl, FALSE);
				EnableWindow(removeHndl, FALSE);
				if (RunCommand(hDlg, 1) == 0) {
					ShowInformation(hDlg);
					// MessageProc::StkInf(LBA_OPECOMPLETED, hDlg);
					TCHAR Buf[32];
					wsprintf(Buf, _T("Message ID : %d"), LBA_OPECOMPLETED);
					MessageBox(hDlg, MessageProc::GetMsg(LBA_OPECOMPLETED), Buf, MB_OK | MB_ICONINFORMATION);
				} else {
					ShowInformation(hDlg);
				}
				return (INT_PTR)TRUE;
			}
			if (LOWORD(wParam) == IDC_REMOVE) {
				EnableWindow(InstallHndl, FALSE);
				EnableWindow(removeHndl, FALSE);
				if (RunCommand(hDlg, -1) == 0) {
					ShowInformation(hDlg);
					//MessageProc::StkInf(LBA_OPECOMPLETED, hDlg);
					TCHAR Buf[32];
					wsprintf(Buf, _T("Message ID : %d"), LBA_OPECOMPLETED);
					MessageBox(hDlg, MessageProc::GetMsg(LBA_OPECOMPLETED), Buf, MB_OK | MB_ICONINFORMATION);
				} else {
					ShowInformation(hDlg);
				}
				return (INT_PTR)TRUE;
			}
		}
		break;
	}
	return (INT_PTR)FALSE;
}

void ShowLbadptDialog(HWND ParentWndHndl)
{
	DialogBox(InstHndl, MAKEINTRESOURCE(IDD_LBADPT), ParentWndHndl, LbAdptDlg);
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// =====================================================================================================
	//1101 (NC2)
	MessageProc::AddJpn(LBA_FIRSTINFO, _T("���̃v���O�����̓��[�v�o�b�N�E�l�b�g���[�N�A�_�v�^���C���X�g�[���܂��͍폜���܂��B�l�b�g���[�N�̐ݒ��ύX�������Ȃ��ꍇ�� Close �{�^�����N���b�N���Ă��������B"));
	MessageProc::AddEng(LBA_FIRSTINFO, _T("This program will install (or remove) the loopback network adapter to/from your computer. If you do not want to change the network configuration, click Close."));

	//1102 (NC2)
	MessageProc::AddJpn(LBA_PROCCALLFAILED, _T("�R�}���h�̎��s�Ɏ��s���܂����B\r\nlbadpt32.exe�܂���lbadpt64.exe��lbadpt.dll�Ɠ����t�H���_�ɑ��݂��邱�Ƃ��m�F���Ă��������B"));
	MessageProc::AddEng(LBA_PROCCALLFAILED, _T("Failed to execute command.\r\nCheck whether the command file [lbadpt32.exe or lbadpt64.exe] is located in the same folder as this program [lbadpt.dll]."));

	//1103 (NC2)
	MessageProc::AddJpn(LBA_ALREADYINSTALLED, _T("���[�v�o�b�N�A�_�v�^�͊��ɃC���X�g�[������Ă��܂��B"));
	MessageProc::AddEng(LBA_ALREADYINSTALLED, _T("The loopback adapter is already installed."));

	//1104 (NC2)
	MessageProc::AddJpn(LBA_NOTINSTALLED, _T("���[�v�o�b�N�A�_�v�^�̓C���X�g�[������Ă��܂���B"));
	MessageProc::AddEng(LBA_NOTINSTALLED, _T("The loopback adapter is not installed."));

	//1105 (NC2)
	MessageProc::AddJpn(LBA_OPECOMPLETED, _T("����͊������܂����B"));
	MessageProc::AddEng(LBA_OPECOMPLETED, _T("The operation has completed."));

	//2903 (NC1)
	MessageProc::AddJpn(NEEDADMINRIGHTS, _T("���̃v���O���������s���邽�߂ɂ�Local Administrator�̌������K�v�ł��B\r\n�v���O�����͏I�����܂��B\r\n\r\n"));
	MessageProc::AddEng(NEEDADMINRIGHTS, _T("You need local administrator's rights to run this program.\r\nThe program will be terminated.\r\n\r\n"));


	InstHndl = hInstance;

	// Check whether same program is already executed.
	HANDLE MutexHndl = CreateMutex(NULL, TRUE, _T("Lbadpt (S.Takeuchi)"));
	if (MutexHndl == NULL || GetLastError() == ERROR_ALREADY_EXISTS) {
		ExitProcess(0);
	}

	ShowLbadptDialog(NULL);
	return 0;
}
