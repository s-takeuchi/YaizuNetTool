#include <windows.h>
#include <tchar.h>
#include <shlwapi.h>

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	PROCESS_INFORMATION pi;
	STARTUPINFO si;
	ZeroMemory(&si,sizeof(si));
	si.cb=sizeof(si);
	TCHAR Buf[256];
	TCHAR CmdLine[512];
	GetModuleFileName(NULL, Buf, 255);
	LPTSTR Addr = StrStr(Buf, _T("\\fwdel.exe"));
	lstrcpy(Addr, _T("\\stkfw.exe"));
	wsprintf(CmdLine, _T("netsh firewall delete allowedprogram \"%s\""), Buf);
	CreateProcess(NULL, CmdLine, NULL, NULL, FALSE, NORMAL_PRIORITY_CLASS | CREATE_NO_WINDOW, NULL, NULL, &si, &pi);
	WaitForSingleObject(pi.hProcess, INFINITE);
	CloseHandle(pi.hProcess);
	return 0;
}
