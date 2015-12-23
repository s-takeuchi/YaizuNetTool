
#define _WINSOCKAPI_

#include <winsock2.h>
#include <windows.h>
#include <tchar.h>
#include <Iphlpapi.h>
#include <shlwapi.h>
#include <shlobj.h>
#include <stdio.h>
#include <Lm.h>
#include "resource.h"
#include "StkIpDlgMsg.h"
#include "..\..\..\YaizuComLib\src\commonfunc\msgproc.h"

#define STK_IP_DLG_IPSTRLEN 20000
#define NEEDADMINRIGHTS 2903

// Global veriable
RECT DlgRect;
DWORD TargetAdIndex;
TCHAR TargetAdName[1024];
HICON IconHndlrS;
HICON IconHndlrB;
HINSTANCE IpDlgInstanceHndl;
HWND ParentWinHndl;
BOOL Init;

// Functions
BOOL StkIpDlg(HINSTANCE);
LRESULT CALLBACK StkIpDlg1( HWND, UINT, WPARAM, LPARAM );
LRESULT CALLBACK StkIpDlg2( HWND, UINT, WPARAM, LPARAM );
LRESULT CALLBACK StkIpDlg3( HWND, UINT, WPARAM, LPARAM );
LRESULT CALLBACK StkIpDlg4( HWND, UINT, WPARAM, LPARAM );

int AddIpAddressToNetworkAdapter(DWORD, TCHAR*, TCHAR*);
int AddIpAddressToNetworkFriendly(TCHAR[1024], TCHAR*, TCHAR*);
int DeleteIpAddressFromNetworkAdapter(DWORD, TCHAR*);
int DeleteIpAddressFromNetworkFriendly(TCHAR[1024], TCHAR*);

int GetIpAddressOnNetworkAdapter(int, TCHAR*);
DWORD GetContextOnNetworkAdapter(int, TCHAR*);
int GetAdapterNames(TCHAR[11][1024], DWORD[11]);
unsigned long ConvertToLongFromIpEle(TCHAR*, TCHAR*, TCHAR*, TCHAR*);
void ConvertToIpStrFromLong(unsigned long, TCHAR*);
int OperationLoop(TCHAR*, TCHAR*, TCHAR*, TCHAR*, TCHAR*, TCHAR*, TCHAR*, TCHAR*, int, BOOL);
int ChangeText(HWND, int, TCHAR*);
int GetInitPosX(HWND);
int GetInitPosY(HWND);


void ShowStkIpDlg(HWND hwnd)
{
	Init = TRUE;
	ParentWinHndl = hwnd;
	StkIpDlg(IpDlgInstanceHndl);
}

/********** Show dialog box **********/
BOOL StkIpDlg(HINSTANCE hInstance)
{
	DlgRect.left = 0;
	DlgRect.right = 0;
	DlgRect.top = 0;
	DlgRect.bottom = 0;

	IconHndlrS = (HICON)LoadImage(hInstance, (LPCTSTR)IDI_STK_IP_DLG, IMAGE_ICON, 16, 16, LR_DEFAULTCOLOR);
	IconHndlrB = (HICON)LoadImage(hInstance, (LPCTSTR)IDI_STK_IP_DLG, IMAGE_ICON, 32, 32, LR_DEFAULTCOLOR);

	int stage = 0;
	int retcode;
	while (TRUE) {
		switch (stage) {
		case 0:
			retcode = DialogBox(hInstance, (LPCTSTR)IDD_STK_IP_DLG_1, ParentWinHndl, (DLGPROC)StkIpDlg1);
			break;
		case 1:
			retcode = DialogBox(hInstance, (LPCTSTR)IDD_STK_IP_DLG_2, ParentWinHndl, (DLGPROC)StkIpDlg2);
			break;
		case 2:
			retcode = DialogBox(hInstance, (LPCTSTR)IDD_STK_IP_DLG_3, ParentWinHndl, (DLGPROC)StkIpDlg3);
			break;
		case 3:
			retcode = DialogBox(hInstance, (LPCTSTR)IDD_STK_IP_DLG_4, ParentWinHndl, (DLGPROC)StkIpDlg4);
			break;
		default:
			return TRUE;
		}
		if (retcode == 0) {
			return TRUE;
		}
		if (retcode == 1) {
			stage++;
		}
		if (retcode == -1) {
			stage--;
		}
	}
	return TRUE;
}

/********** Introduction dialog box **********/
LRESULT CALLBACK StkIpDlg1(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (Init == TRUE) {
		//Following lines for making .exe file.
		//The lines put the dialog box on center of screen
		//
		//GetWindowRect(hDlg, &DlgRect);
		//int PosX = GetInitPosX(hDlg);
		//int PosY = GetInitPosY(hDlg);
		//SetWindowPos(hDlg, HWND_TOP, PosX, PosY, 0, 0, SWP_NOSIZE | SWP_SHOWWINDOW | SWP_DRAWFRAME);
		GetWindowRect(hDlg, &DlgRect);
		Init = FALSE;
	}
	switch(message)	{
	case WM_INITDIALOG:
#ifdef FOR_WIN2K
		SetWindowText(hDlg, _T("Add/Remove IP Address Wizard (Windows 2000)"));
#endif
		SendMessage(hDlg, WM_SETICON, ICON_SMALL, (LPARAM)IconHndlrS);
		SendMessage(hDlg, WM_SETICON, ICON_BIG, (LPARAM)IconHndlrB);
		MoveWindow(hDlg, DlgRect.left, DlgRect.top, DlgRect.right - DlgRect.left, DlgRect.bottom - DlgRect.top, TRUE);
		break;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDC_STK_IP_DLG_NEXT) {
			GetWindowRect(hDlg, &DlgRect);
			EndDialog(hDlg, 1);
			return TRUE;
		}
		if (LOWORD(wParam) == IDC_STK_IP_DLG_CANCEL) {
			if (StkIpDlgMsg::StopStkIpDlg(hDlg) == IDYES) {
				EndDialog(hDlg, 0);
			}
		}
		break;
	case WM_CLOSE:
		if (StkIpDlgMsg::StopStkIpDlg(hDlg) == IDYES) {
			EndDialog(hDlg, 0);
		}
		break;
	}
    return FALSE;
}

/********** Select network adapter dialog box **********/
LRESULT CALLBACK StkIpDlg2(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	int AdLoop;
	int CurAdLoop;
	int TmpSelectedAd;
	static DWORD AdIndex[11];
	static TCHAR AdNames[11][1024];
	static int SelectedAd = 0;

	switch(message)	{
	case WM_INITDIALOG:
		SendMessage(hDlg, WM_SETICON, ICON_SMALL, (LPARAM)IconHndlrS);
		SendMessage(hDlg, WM_SETICON, ICON_BIG, (LPARAM)IconHndlrB);
		MoveWindow(hDlg, DlgRect.left, DlgRect.top, DlgRect.right - DlgRect.left, DlgRect.bottom - DlgRect.top, TRUE);
		AdLoop = GetAdapterNames(AdNames, AdIndex);
		if (AdLoop == -1) {
			StkIpDlgMsg::NetworkConfigAcquisitionError(hDlg);
			EndDialog(hDlg, 0);
			break;
		}
		if (AdLoop == 0) {
			StkIpDlgMsg::NoNetworkAdapterFoundError(hDlg);
			EndDialog(hDlg, 0);
			break;
		}
		for (CurAdLoop = 0; CurAdLoop < AdLoop; CurAdLoop++) {
			SendDlgItemMessage(hDlg, IDC_STK_IP_DLG_2_C0, CB_INSERTSTRING, CurAdLoop, (LPARAM)AdNames[CurAdLoop]);
		}
		if (SelectedAd >= AdLoop) {
			SelectedAd = 0;
		}
		TargetAdIndex = AdIndex[SelectedAd];
		lstrcpy(TargetAdName, AdNames[SelectedAd]);

		SendDlgItemMessage(hDlg, IDC_STK_IP_DLG_2_C0, CB_SETCURSEL, SelectedAd, 0);
		SetFocus(GetDlgItem(hDlg, IDC_STK_IP_DLG_2_C0));
		break;
	case WM_COMMAND:
		if (LOWORD(wParam) == IDC_STK_IP_DLG_NEXT) {
			GetWindowRect(hDlg, &DlgRect);
			EndDialog(hDlg, 1);
			return TRUE;
		}
		if (LOWORD(wParam) == IDC_STK_IP_DLG_BACK) {
			GetWindowRect(hDlg, &DlgRect);
			EndDialog(hDlg, -1);
			return TRUE;
		}
		if (LOWORD(wParam) == IDC_STK_IP_DLG_CANCEL) {
			if (StkIpDlgMsg::StopStkIpDlg(hDlg) == IDYES) {
				EndDialog(hDlg, 0);
			}
		}
		if (HIWORD(wParam) == CBN_SELCHANGE) {
			if (LOWORD(wParam) == IDC_STK_IP_DLG_2_C0) {
				TmpSelectedAd = SendDlgItemMessage(hDlg, IDC_STK_IP_DLG_2_C0, CB_GETCURSEL, 0, 0);
				if (TmpSelectedAd != -1) {
					SelectedAd = TmpSelectedAd;
					TargetAdIndex = AdIndex[SelectedAd];
					lstrcpy(TargetAdName, AdNames[SelectedAd]);
				}
			}
		}
		break;
	case WM_CLOSE:
		if (StkIpDlgMsg::StopStkIpDlg(hDlg) == IDYES) {
			EndDialog(hDlg, 0);
		}
		break;
	}
    return FALSE;
}

/********** Input parameter dialog box **********/
LRESULT CALLBACK StkIpDlg3(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	static TCHAR ip1[5] = _T("");
	static TCHAR ip2[5] = _T("");
	static TCHAR ip3[5] = _T("");
	static TCHAR ip4[5] = _T("");
	static TCHAR NumOfIp[5] = _T("");
	static TCHAR MaskIp1[5] = _T("");
	static TCHAR MaskIp2[5] = _T("");
	static TCHAR MaskIp3[5] = _T("");
	static TCHAR MaskIp4[5] = _T("");
	static BOOL AddFlag = TRUE;
	TCHAR IpAddrs[STK_IP_DLG_IPSTRLEN] = _T("");
	int RetCode;

	switch(message)	{
	case WM_INITDIALOG:
		SendMessage(hDlg, WM_SETICON, ICON_SMALL, (LPARAM)IconHndlrS);
		SendMessage(hDlg, WM_SETICON, ICON_BIG, (LPARAM)IconHndlrB);
		MoveWindow(hDlg, DlgRect.left, DlgRect.top, DlgRect.right - DlgRect.left, DlgRect.bottom - DlgRect.top, TRUE);
		SendDlgItemMessage(hDlg, IDC_STK_IP_DLG_3_E1, EM_SETSEL, '0', '9');
		SendDlgItemMessage(hDlg, IDC_STK_IP_DLG_3_E1, EM_LIMITTEXT, 3, 0);
		SendDlgItemMessage(hDlg, IDC_STK_IP_DLG_3_E2, EM_SETSEL, '0', '9');
		SendDlgItemMessage(hDlg, IDC_STK_IP_DLG_3_E2, EM_LIMITTEXT, 3, 0);
		SendDlgItemMessage(hDlg, IDC_STK_IP_DLG_3_E3, EM_SETSEL, '0', '9');
		SendDlgItemMessage(hDlg, IDC_STK_IP_DLG_3_E3, EM_LIMITTEXT, 3, 0);
		SendDlgItemMessage(hDlg, IDC_STK_IP_DLG_3_E4, EM_SETSEL, '0', '9');
		SendDlgItemMessage(hDlg, IDC_STK_IP_DLG_3_E4, EM_LIMITTEXT, 3, 0);
		SendDlgItemMessage(hDlg, IDC_STK_IP_DLG_3_E5, EM_SETSEL, '0', '9');
		SendDlgItemMessage(hDlg, IDC_STK_IP_DLG_3_E5, EM_LIMITTEXT, 3, 0);
		SendDlgItemMessage(hDlg, IDC_STK_IP_DLG_3_E6, EM_SETSEL, '0', '9');
		SendDlgItemMessage(hDlg, IDC_STK_IP_DLG_3_E6, EM_LIMITTEXT, 3, 0);
		SendDlgItemMessage(hDlg, IDC_STK_IP_DLG_3_E7, EM_SETSEL, '0', '9');
		SendDlgItemMessage(hDlg, IDC_STK_IP_DLG_3_E7, EM_LIMITTEXT, 3, 0);
		SendDlgItemMessage(hDlg, IDC_STK_IP_DLG_3_E8, EM_SETSEL, '0', '9');
		SendDlgItemMessage(hDlg, IDC_STK_IP_DLG_3_E8, EM_LIMITTEXT, 3, 0);
		SendDlgItemMessage(hDlg, IDC_STK_IP_DLG_3_E9, EM_SETSEL, '0', '9');
		SendDlgItemMessage(hDlg, IDC_STK_IP_DLG_3_E9, EM_LIMITTEXT, 3, 0);
		if (AddFlag == TRUE) {
			SendDlgItemMessage(hDlg, IDC_STK_IP_DLG_3_R1, BM_SETCHECK, BST_CHECKED, 0);
			SendDlgItemMessage(hDlg, IDC_STK_IP_DLG_3_R2, BM_SETCHECK, BST_UNCHECKED, 0);
		} else {
			SendDlgItemMessage(hDlg, IDC_STK_IP_DLG_3_R1, BM_SETCHECK, BST_UNCHECKED, 0);
			SendDlgItemMessage(hDlg, IDC_STK_IP_DLG_3_R2, BM_SETCHECK, BST_CHECKED, 0);
		}
		SetDlgItemText(hDlg, IDC_STK_IP_DLG_3_E1, ip1);
		SetDlgItemText(hDlg, IDC_STK_IP_DLG_3_E2, ip2);
		SetDlgItemText(hDlg, IDC_STK_IP_DLG_3_E3, ip3);
		SetDlgItemText(hDlg, IDC_STK_IP_DLG_3_E4, ip4);
		SetDlgItemText(hDlg, IDC_STK_IP_DLG_3_E5, NumOfIp);
		SetDlgItemText(hDlg, IDC_STK_IP_DLG_3_E6, MaskIp1);
		SetDlgItemText(hDlg, IDC_STK_IP_DLG_3_E7, MaskIp2);
		SetDlgItemText(hDlg, IDC_STK_IP_DLG_3_E8, MaskIp3);
		SetDlgItemText(hDlg, IDC_STK_IP_DLG_3_E9, MaskIp4);

		RetCode = GetIpAddressOnNetworkAdapter(TargetAdIndex, IpAddrs);
		if (RetCode == -2) {
			StkIpDlgMsg::TooMuchIPFoundError(hDlg);
			EndDialog(hDlg, 0);
			break;
		}
		if (RetCode == -1) {
			StkIpDlgMsg::NetworkConfigAcquisitionError(hDlg);
			EndDialog(hDlg, 0);
			break;
		}
		if (RetCode == 0) {
			StkIpDlgMsg::NoNetworkAdapterFoundError(hDlg);
			EndDialog(hDlg, 0);
			break;
		}
		SetDlgItemText(hDlg, IDC_STK_IP_DLG_3_I, IpAddrs);

		SetFocus(GetDlgItem(hDlg, IDC_STK_IP_DLG_3_E1));

		break;
	case WM_COMMAND:
		if (LOWORD(wParam) == IDC_STK_IP_DLG_NEXT) {
			if (StrToInt(ip1) > 255 || StrCmp(ip1, _T("")) == 0 ||
				StrToInt(ip2) > 255 || StrCmp(ip2, _T("")) == 0 ||
				StrToInt(ip3) > 255 || StrCmp(ip3, _T("")) == 0 ||
				StrToInt(ip4) > 255 || StrCmp(ip4, _T("")) == 0 ||
				StrToInt(NumOfIp) > 256 || StrCmp(NumOfIp, _T("")) == 0) {
				StkIpDlgMsg::ParameterError(hDlg);
				break;
			}
			if (AddFlag == TRUE && (
				StrToInt(MaskIp1) > 255 || StrCmp(MaskIp1, _T("")) == 0 ||
				StrToInt(MaskIp2) > 255 || StrCmp(MaskIp2, _T("")) == 0 ||
				StrToInt(MaskIp3) > 255 || StrCmp(MaskIp3, _T("")) == 0 ||
				StrToInt(MaskIp4) > 255 || StrCmp(MaskIp4, _T("")) == 0)) {
				StkIpDlgMsg::ParameterError(hDlg);
				break;
			}
			OSVERSIONINFO VerInfo;
			VerInfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
			GetVersionEx(&VerInfo);
			if (VerInfo.dwMajorVersion == 5 && VerInfo.dwMinorVersion == 0) {
				StkIpDlgMsg::RestrictionOfEffect(hDlg);
			} else {
				StkIpDlgMsg::TakeALongTime(hDlg);
			}
			if (OperationLoop(ip1, ip2, ip3, ip4, MaskIp1, MaskIp2, MaskIp3, MaskIp4, StrToInt(NumOfIp), AddFlag) == -1) {
				StkIpDlgMsg::NetworkConfigChangeError(hDlg);
			}
			GetWindowRect(hDlg, &DlgRect);
			EndDialog(hDlg, 1);
			return TRUE;
		}
		if (LOWORD(wParam) == IDC_STK_IP_DLG_BACK) {
			GetWindowRect(hDlg, &DlgRect);
			EndDialog(hDlg, -1);
			return TRUE;
		}
		if (LOWORD(wParam) == IDC_STK_IP_DLG_CANCEL) {
			if (StkIpDlgMsg::StopStkIpDlg(hDlg) == IDYES) {
				EndDialog(hDlg, 0);
			}
		}
		if (HIWORD(wParam) == BN_CLICKED) {
			if (LOWORD(wParam) == IDC_STK_IP_DLG_3_R1) {
				AddFlag = TRUE;
			}
			if (LOWORD(wParam) == IDC_STK_IP_DLG_3_R2) {
				AddFlag = FALSE;
			}
		}
		if (HIWORD(wParam) == EN_UPDATE) {
			int Len;

			if (LOWORD(wParam) == IDC_STK_IP_DLG_3_E1) {
				Len = ChangeText(hDlg, IDC_STK_IP_DLG_3_E1, ip1);
			}
			if (LOWORD(wParam) == IDC_STK_IP_DLG_3_E2) {
				Len = ChangeText(hDlg, IDC_STK_IP_DLG_3_E2, ip2);
			}
			if (LOWORD(wParam) == IDC_STK_IP_DLG_3_E3) {
				Len = ChangeText(hDlg, IDC_STK_IP_DLG_3_E3, ip3);
			}
			if (LOWORD(wParam) == IDC_STK_IP_DLG_3_E4) {
				Len = ChangeText(hDlg, IDC_STK_IP_DLG_3_E4, ip4);
			}
			if (LOWORD(wParam) == IDC_STK_IP_DLG_3_E5) {
				Len = ChangeText(hDlg, IDC_STK_IP_DLG_3_E5, NumOfIp);
			}
			if (LOWORD(wParam) == IDC_STK_IP_DLG_3_E6) {
				Len = ChangeText(hDlg, IDC_STK_IP_DLG_3_E6, MaskIp1);
			}
			if (LOWORD(wParam) == IDC_STK_IP_DLG_3_E7) {
				Len = ChangeText(hDlg, IDC_STK_IP_DLG_3_E7, MaskIp2);
			}
			if (LOWORD(wParam) == IDC_STK_IP_DLG_3_E8) {
				Len = ChangeText(hDlg, IDC_STK_IP_DLG_3_E8, MaskIp3);
			}
			if (LOWORD(wParam) == IDC_STK_IP_DLG_3_E9) {
				Len = ChangeText(hDlg, IDC_STK_IP_DLG_3_E9, MaskIp4);
			}
			HWND CurEb = GetFocus();
			if (Len >= 3) {
				HWND NextEb = GetNextDlgTabItem(hDlg, CurEb, FALSE);
				SetFocus(NextEb);
			}
		}
		break;
	case WM_CLOSE:
		if (StkIpDlgMsg::StopStkIpDlg(hDlg) == IDYES) {
			EndDialog(hDlg, 0);
		}
		break;
	}
    return FALSE;
}

/********** Result dialog box **********/
LRESULT CALLBACK StkIpDlg4(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	int RetCode;
	TCHAR IpAddrs[STK_IP_DLG_IPSTRLEN] = _T("");

	switch(message)	{
	case WM_INITDIALOG:
		SendMessage(hDlg, WM_SETICON, ICON_SMALL, (LPARAM)IconHndlrS);
		SendMessage(hDlg, WM_SETICON, ICON_BIG, (LPARAM)IconHndlrB);
		MoveWindow(hDlg, DlgRect.left, DlgRect.top, DlgRect.right - DlgRect.left, DlgRect.bottom - DlgRect.top, TRUE);
		RetCode = GetIpAddressOnNetworkAdapter(TargetAdIndex, IpAddrs);
		if (RetCode == -2) {
			StkIpDlgMsg::TooMuchIPFoundError(hDlg);
			EndDialog(hDlg, 0);
			break;
		}
		if (RetCode == -1) {
			StkIpDlgMsg::NetworkConfigAcquisitionError(hDlg);
			EndDialog(hDlg, 0);
			break;
		}
		if (RetCode == 0) {
			StkIpDlgMsg::NoNetworkAdapterFoundError(hDlg);
			EndDialog(hDlg, 0);
			break;
		}
		SetDlgItemText(hDlg, IDC_STK_IP_DLG_4_I, IpAddrs);
		break;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDC_STK_IP_DLG_NEXT) {
			GetWindowRect(hDlg, &DlgRect);
			EndDialog(hDlg, 1);
			return TRUE;
		}
		break;
	}
    return FALSE;
}

/********** Add IP address into system **********/
// Return code  1 : Success
// Return code  0 : The IP address has already been registered
// Return code -1 : An error occurred
int AddIpAddressToNetworkAdapter(DWORD AdIndex, TCHAR* IpAddr, TCHAR* IpMask)
{
	char IpAddrS[16];
	char IpMaskS[16];

	sprintf_s(IpAddrS, "%S", IpAddr);
	sprintf_s(IpMaskS, "%S", IpMask);
	UINT InetIpAddr = inet_addr(IpAddrS);
	UINT InetIpMask = inet_addr(IpMaskS);
	ULONG NTEContext = 0;
	ULONG NTEInstance = 0;
	DWORD RetCode;

	RetCode = AddIPAddress(InetIpAddr, InetIpMask, AdIndex, &NTEContext, &NTEInstance);
	if (RetCode == NO_ERROR) {
		return 1;
	} else if (RetCode == 0xC000022A ||    // Windows 2000 'STATUS_DUPLICATE_OBJECTID'
			   RetCode == ERROR_DUP_DOMAINNAME ||    // Windows XP
			   RetCode == ERROR_OBJECT_ALREADY_EXISTS) {    // Windows Vista
		return 0;
	} else {
		return -1;
	}
}

/********** Add IP address into system. **********/
// Return Code     1 : Success
// Return code    -1 : An error occurred
int AddIpAddressToNetworkFriendly(TCHAR TargetAdName[1024], TCHAR* IpAddr, TCHAR* IpMask)
{
#ifndef FOR_WIN2K
	IP_ADAPTER_ADDRESSES TmpAdptAddr;
	ULONG BufSize = 0;
	GetAdaptersAddresses(AF_INET, 0, NULL, &TmpAdptAddr, &BufSize);
	PIP_ADAPTER_ADDRESSES Buf = (PIP_ADAPTER_ADDRESSES)new BYTE[BufSize];
	GetAdaptersAddresses(AF_INET, 0, NULL, Buf, &BufSize);
	while (Buf) {
		if (lstrcmp(Buf->Description, TargetAdName) == 0) {
			PROCESS_INFORMATION pi;
			STARTUPINFO si;
			ZeroMemory(&si,sizeof(si));
			si.cb=sizeof(si);
			TCHAR CmdLine[512];
			wsprintf(CmdLine, _T("netsh interface ip add address name=\"%s\" addr=%s mask=%s"), Buf->FriendlyName, IpAddr, IpMask);
			CreateProcess(NULL, CmdLine, NULL, NULL, FALSE, NORMAL_PRIORITY_CLASS | CREATE_NO_WINDOW, NULL, NULL, &si, &pi);
			DWORD RetCode;
			do {
				Sleep(10);
				GetExitCodeProcess(pi.hProcess, &RetCode);
			} while (RetCode == STILL_ACTIVE);
			return 1;
		}
		Buf = Buf->Next;
	}
#endif
	return -1;
}

/********** Delete IP address from system **********/
// Return code  1 : Success (The IP address has been deleted)
// Return code  0 : The IP address has already been deleted)
// Return code -1 : An error occurred
int DeleteIpAddressFromNetworkAdapter(DWORD AdIndex, TCHAR* IpAddr)
{
	DWORD TargetContext;

	TargetContext = GetContextOnNetworkAdapter(AdIndex, IpAddr);
	if (TargetContext == 0) {
		return 0;
	}
	if (TargetContext != -1) {
		if (DeleteIPAddress(TargetContext) == NO_ERROR) {
			return 1;
		}
	}
	return -1;
}

/********** Delete IP address from system **********/
// Return code  1 : Success (The IP address has been deleted)
// Return code -1 : An error occurred
int DeleteIpAddressFromNetworkFriendly(TCHAR TargetAdName[1024], TCHAR* IpAddr)
{
#ifndef FOR_WIN2K
	IP_ADAPTER_ADDRESSES TmpAdptAddr;
	ULONG BufSize = 0;
	GetAdaptersAddresses(AF_INET, 0, NULL, &TmpAdptAddr, &BufSize);
	PIP_ADAPTER_ADDRESSES Buf = (PIP_ADAPTER_ADDRESSES)new BYTE[BufSize];
	GetAdaptersAddresses(AF_INET, 0, NULL, Buf, &BufSize);
	while (Buf) {
		if (lstrcmp(Buf->Description, TargetAdName) == 0) {
			PROCESS_INFORMATION pi;
			STARTUPINFO si;
			ZeroMemory(&si,sizeof(si));
			si.cb=sizeof(si);
			TCHAR CmdLine[512];
			wsprintf(CmdLine, _T("netsh interface ip delete address name=\"%s\" addr=%s"), Buf->FriendlyName, IpAddr);
			CreateProcess(NULL, CmdLine, NULL, NULL, FALSE, NORMAL_PRIORITY_CLASS | CREATE_NO_WINDOW, NULL, NULL, &si, &pi);
			DWORD RetCode;
			do {
				Sleep(10);
				GetExitCodeProcess(pi.hProcess, &RetCode);
			} while (RetCode == STILL_ACTIVE);
			return 1;
		}
		Buf = Buf->Next;
	}
#endif
	return -1;
}

/********** This function adds to system the IP addresses which caller passed **********/
int OperationLoop(TCHAR* Ip1, TCHAR* Ip2, TCHAR* Ip3, TCHAR* Ip4, TCHAR* Mask1, TCHAR* Mask2, TCHAR* Mask3, TCHAR* Mask4, int NumOfIp, BOOL AddFlag)
{
	TCHAR Mask[16];
	lstrcpy(Mask, _T(""));
	lstrcat(Mask, Mask1);
	lstrcat(Mask, _T("."));
	lstrcat(Mask, Mask2);
	lstrcat(Mask, _T("."));
	lstrcat(Mask, Mask3);
	lstrcat(Mask, _T("."));
	lstrcat(Mask, Mask4);
	unsigned long Ret = ConvertToLongFromIpEle(Ip1, Ip2, Ip3, Ip4);

	OSVERSIONINFO VerInfo;
	VerInfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	GetVersionEx(&VerInfo);

	for (unsigned long i = Ret; i < Ret + NumOfIp; i++) {
		TCHAR IpStr[16];
		ConvertToIpStrFromLong(i, IpStr);
		if (AddFlag == TRUE) {
			DWORD RetAdd;
			if (VerInfo.dwMajorVersion == 5 && VerInfo.dwMinorVersion == 0) {
				RetAdd = AddIpAddressToNetworkAdapter(TargetAdIndex, IpStr, Mask); // Windows 2000
			} else {
				RetAdd = AddIpAddressToNetworkFriendly(TargetAdName, IpStr, Mask); // Windows XP, Vista
			}
			if (RetAdd == -1) {
				return -1;
			}
		} else {
			DWORD RetDel;
			if (VerInfo.dwMajorVersion == 5 && VerInfo.dwMinorVersion == 0) {
				RetDel = DeleteIpAddressFromNetworkAdapter(TargetAdIndex, IpStr); // Windows 2000
			} else {
				RetDel = DeleteIpAddressFromNetworkFriendly(TargetAdName, IpStr); // Windows XP, Vista
			}
			if (RetDel == -1) {
				return -1;
			}
		}
	}
	return 1;
}

/********** Acuire context which is regarding the specified IP address. /**********/
// Return Code     0 : Success
// Return Code    -1 : An error occurred
// Return Code other : Context
DWORD GetContextOnNetworkAdapter(int AdIndex, TCHAR* TargetIpAddr)
{
	IP_ADAPTER_INFO *IpAdInfo;
	IP_ADDR_STRING *IpAddr;
	ULONG LenIpAdInfo = 0;
	BYTE *Buf;

	GetAdaptersInfo(NULL, &LenIpAdInfo);
	Buf = new BYTE[LenIpAdInfo];
	IpAdInfo = (IP_ADAPTER_INFO*)Buf;
	if (GetAdaptersInfo(IpAdInfo, &LenIpAdInfo) != ERROR_SUCCESS) {
		delete Buf;
		return -1;
	}
	do {
		if (IpAdInfo->Index == AdIndex) {
			break;
		}
		IpAdInfo = IpAdInfo->Next;
		if (IpAdInfo == NULL) {
			delete Buf;
			return -1;
		}
	} while (IpAdInfo);
	IpAddr = &(IpAdInfo->IpAddressList);
	do {
		TCHAR BufIpAddr[16];
		wsprintf(BufIpAddr, _T("%S"), IpAddr->IpAddress.String);
		if (lstrcmp(TargetIpAddr, BufIpAddr) == 0) {
			delete Buf;
			return IpAddr->Context;
		}
		IpAddr = IpAddr->Next;
	} while (IpAddr);
	delete Buf;
	return 0;
}

/********** Acuire the IP addresses which is on the specified network adapter. **********/
// Return Code  1 : Success
// Return Code  0 : No IP address exists on the specified network adapter
// Return Code -1 : An error occurred
// Return Code -2 : Too much IP addresses has been acuired
int GetIpAddressOnNetworkAdapter(int AdIndex, TCHAR* IpAddrs)
{
	IP_ADAPTER_INFO *IpAdInfo;
	IP_ADDR_STRING *IpAddr;
	ULONG LenIpAdInfo = 0;
	BYTE *Buf;
	DWORD RetCode;

	GetAdaptersInfo(NULL, &LenIpAdInfo);
	Buf = new BYTE[LenIpAdInfo];
	IpAdInfo = (IP_ADAPTER_INFO*)Buf;
	RetCode = GetAdaptersInfo(IpAdInfo, &LenIpAdInfo);
	if (RetCode == ERROR_NO_DATA) {
		delete Buf;
		return 0;
	}
	if (RetCode != ERROR_SUCCESS) {
		delete Buf;
		return -1;
	}
	do {
		if (IpAdInfo->Index == AdIndex) {
			break;
		}
		IpAdInfo = IpAdInfo->Next;
		if (IpAdInfo == NULL) {
			delete Buf;
			return -1;
		}
	} while (IpAdInfo);
	IpAddr = &(IpAdInfo->IpAddressList);
	do {
		if (lstrlen(IpAddrs) > (STK_IP_DLG_IPSTRLEN - 100)) {
			delete Buf;
			return -2;
		}
		TCHAR BufIpAddr[16];
		wsprintf(BufIpAddr, _T("%S"), IpAddr->IpAddress.String);
		lstrcat(IpAddrs, BufIpAddr);
		lstrcat(IpAddrs, _T("\r\n"));
		IpAddr = IpAddr->Next;
	} while (IpAddr);
	delete Buf;
	return 1;
}

/********** Acuire all network adapter names on the system. **********/
// Return Code     0 : No network adapter exists
// Return Code    -1 : An error occurred
// Return Code other : Number of adapters which have been found
int GetAdapterNames(TCHAR AdNames[11][1024], DWORD AdIndex[11])
{
	IP_ADAPTER_INFO *IpAdInfo;
	ULONG LenIpAdInfo = 0;
	BYTE *Buf;
	int AdLoop = 0;
	DWORD RetCode;

	GetAdaptersInfo(NULL, &LenIpAdInfo);
	Buf = new BYTE[LenIpAdInfo];
	IpAdInfo = (IP_ADAPTER_INFO*)Buf;
	RetCode = GetAdaptersInfo(IpAdInfo, &LenIpAdInfo);
	if (RetCode == ERROR_NO_DATA) {
		delete Buf;
		return 0;
	}
	if (RetCode != ERROR_SUCCESS) {
		delete Buf;
		return -1;
	}
	do {
		wsprintf(AdNames[AdLoop], _T("%S"), IpAdInfo->Description);
		AdIndex[AdLoop] = IpAdInfo->Index;
		IpAdInfo = IpAdInfo->Next;
		AdLoop++;
		if (AdLoop == 11) {
			break;
		}
	} while (IpAdInfo);
	delete Buf;
	return AdLoop;
}

/********** This function makes a long variable from IP address string **********/
unsigned long ConvertToLongFromIpEle(TCHAR* Ip1, TCHAR* Ip2, TCHAR* Ip3, TCHAR* Ip4)
{
	unsigned long Ip1Int = StrToInt(Ip1);
	unsigned long Ip2Int = StrToInt(Ip2);
	unsigned long Ip3Int = StrToInt(Ip3);
	unsigned long Ip4Int = StrToInt(Ip4);
	unsigned long Ret =  Ip1Int * 16777216L + Ip2Int * 65536L + Ip3Int * 256L + Ip4Int;
	return Ret;
}

/********** This function makes a IP address string from long variable **********/
void ConvertToIpStrFromLong(unsigned long IpLong, TCHAR* IpStr)
{
	unsigned long Ip4Int = IpLong % 256L;
	IpLong = (IpLong - Ip4Int) / 256;
	unsigned long Ip3Int = IpLong % 256L;
	IpLong = (IpLong - Ip3Int) / 256;
	unsigned long Ip2Int = IpLong % 256L;
	IpLong = (IpLong - Ip2Int) / 256;
	unsigned long Ip1Int = IpLong;
	wsprintf(IpStr, _T("%d.%d.%d.%d"), Ip1Int, Ip2Int, Ip3Int, Ip4Int);
}

/********** This function makes a string which contains only numeric character **********/
int ChangeText(HWND hDlg, int EditBoxId, TCHAR* Text)
{
	TCHAR ChangedText[4];
	GetDlgItemText(hDlg, EditBoxId, Text, 4);
	if (StrCmp(Text, _T("")) == 0) {
		return 0;
	}
	int Num = StrToInt(Text);
	wsprintf(ChangedText, _T("%d"), Num);
	if (StrCmp(Text, ChangedText) == 0) {
		return lstrlen(Text);
	}
	StrCpy(Text, ChangedText);
	SetDlgItemText(hDlg, EditBoxId, Text);
	return lstrlen(Text);
}

// This method returns new horz position which keeps the target window in center of the screen.
int GetInitPosX(HWND HWnd)
{
	int RetSize;
	int ScrSize;
	int WndSize;
	RECT WndRect;
	HDC DevContx;

	DevContx = GetDC(HWnd);
	ScrSize = GetDeviceCaps(DevContx, HORZRES);
	ReleaseDC(HWnd, DevContx);
	GetWindowRect(HWnd, &WndRect);
	WndSize = WndRect.right - WndRect.left;
	RetSize = (ScrSize - WndSize) / 2;
	return RetSize;
}

// This method returns new vert position which keeps the target window in center of the screen.
int GetInitPosY(HWND HWnd)
{
	int RetSize;
	int ScrSize;
	int WndSize;
	RECT WndRect;
	HDC DevContx;

	DevContx = GetDC(HWnd);
	ScrSize = GetDeviceCaps(DevContx, VERTRES);
	ReleaseDC(HWnd, DevContx);
	GetWindowRect(HWnd, &WndRect);
	WndSize = WndRect.bottom - WndRect.top;
	RetSize = (ScrSize - WndSize) / 2;
	return RetSize;
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
	IpDlgInstanceHndl = hInstance;

	MessageProc::AddJpn(NEEDADMINRIGHTS, _T("このプログラムを実行するためにはLocal Administratorの権限が必要です。\r\nプログラムは終了します。\r\n\r\n"));
	MessageProc::AddEng(NEEDADMINRIGHTS, _T("You need local administrator's rights to run this program.\r\nThe program will be terminated.\r\n\r\n"));

	CheckExecutorLocalGroup();

	// Check whether same program is already executed.
	HANDLE MutexHndl = CreateMutex(NULL, TRUE, _T("IP Addr Dialog (S.Takeuchi)"));
	if (MutexHndl == NULL || GetLastError() == ERROR_ALREADY_EXISTS) {
		ExitProcess(0);
	}

	ShowStkIpDlg(NULL);
	return 0;
}
