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
	BOOL Wow64Flag = FALSE;
	LPFN_ISWOW64PROCESS FnIsWow64Process = (LPFN_ISWOW64PROCESS)GetProcAddress(GetModuleHandle(_T("kernel32")), "IsWow64Process");
	TCHAR CmdName[40];

	if (NULL != FnIsWow64Process) {
		if (!FnIsWow64Process(GetCurrentProcess(), &Wow64Flag)) {
			Wow64Flag = FALSE;
		}
	}
	if (Wow64Flag) {
		lstrcpy(CmdName, _T("lbadpt64.exe "));
	} else {
		lstrcpy(CmdName, _T("lbadpt32.exe "));
	}
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
		MessageProc::StkErr(LBA_PROCCALLFAILED, DlgHndl);
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
					MessageProc::StkInf(LBA_OPECOMPLETED, hDlg);
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
					MessageProc::StkInf(LBA_OPECOMPLETED, hDlg);
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

void CheckExecutorLocalGroup(void)
{
	TCHAR ErrorMessage[1024] = _T("");
	TCHAR Buf[64];
	DWORD BufSize = 64;

	lstrcpy(ErrorMessage, MessageProc::GetMsg(NEEDADMINRIGHTS));
	lstrcat(ErrorMessage, _T("User name = "));
	GetUserName(Buf, &BufSize);
	lstrcat(ErrorMessage, Buf);
	lstrcat(ErrorMessage, _T("\r\n"));

	lstrcat(ErrorMessage, _T("Local group :\r\n"));
    DWORD EntriesRead = 0;
    DWORD TotalEntries = 0;
	LPLOCALGROUP_USERS_INFO_0 GrpBuf = NULL;
	NetUserGetLocalGroups(NULL, Buf, 0, LG_INCLUDE_INDIRECT, (LPBYTE*)&GrpBuf, MAX_PREFERRED_LENGTH, &EntriesRead, &TotalEntries);
	for (int Loop = 0; Loop < (int)EntriesRead; Loop++) {
		lstrcat(ErrorMessage, _T("    "));
		lstrcat(ErrorMessage, GrpBuf->lgrui0_name);
		lstrcat(ErrorMessage, _T("\r\n"));
		GrpBuf++;
	}
	NetApiBufferFree(GrpBuf);
	if (IsUserAnAdmin() == FALSE) {
		MessageBox(NULL, ErrorMessage, _T("Error"), MB_OK | MB_ICONERROR);
		ExitProcess(0);
	}
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// =====================================================================================================
	//1101 (NC2)
	MessageProc::AddJpn(LBA_FIRSTINFO, _T("このプログラムはループバック・ネットワークアダプタをインストールまたは削除します。ネットワークの設定を変更したくない場合は Close ボタンをクリックしてください。"));
	MessageProc::AddEng(LBA_FIRSTINFO, _T("This program will install (or remove) the loopback network adapter to/from your computer. If you do not want to change the network configuration, click Close."));

	//1102 (NC2)
	MessageProc::AddJpn(LBA_PROCCALLFAILED, _T("コマンドの実行に失敗しました。\r\nlbadpt32.exeまたはlbadpt64.exeがlbadpt.dllと同じフォルダに存在することを確認してください。"));
	MessageProc::AddEng(LBA_PROCCALLFAILED, _T("Failed to execute command.\r\nCheck whether the command file [lbadpt32.exe or lbadpt64.exe] is located in the same folder as this program [lbadpt.dll]."));

	//1103 (NC2)
	MessageProc::AddJpn(LBA_ALREADYINSTALLED, _T("ループバックアダプタは既にインストールされています。"));
	MessageProc::AddEng(LBA_ALREADYINSTALLED, _T("The loopback adapter is already installed."));

	//1104 (NC2)
	MessageProc::AddJpn(LBA_NOTINSTALLED, _T("ループバックアダプタはインストールされていません。"));
	MessageProc::AddEng(LBA_NOTINSTALLED, _T("The loopback adapter is not installed."));

	//1105 (NC2)
	MessageProc::AddJpn(LBA_OPECOMPLETED, _T("操作は完了しました。"));
	MessageProc::AddEng(LBA_OPECOMPLETED, _T("The operation has completed."));

	//2903 (NC1)
	MessageProc::AddJpn(NEEDADMINRIGHTS, _T("このプログラムを実行するためにはLocal Administratorの権限が必要です。\r\nプログラムは終了します。\r\n\r\n"));
	MessageProc::AddEng(NEEDADMINRIGHTS, _T("You need local administrator's rights to run this program.\r\nThe program will be terminated.\r\n\r\n"));


	InstHndl = hInstance;

	CheckExecutorLocalGroup();

	// Check whether same program is already executed.
	HANDLE MutexHndl = CreateMutex(NULL, TRUE, _T("Lbadpt (S.Takeuchi)"));
	if (MutexHndl == NULL || GetLastError() == ERROR_ALREADY_EXISTS) {
		ExitProcess(0);
	}

	ShowLbadptDialog(NULL);
	return 0;
}
