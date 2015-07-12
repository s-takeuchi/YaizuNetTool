#include <windows.h>
#include <tchar.h>
#include "StkIpDlgMsg.h"

#define STK_IP_DLG_TITLE _T("Add/Remove IP Address Wizard")

StkIpDlgMsg::StkIpDlgMsg(void)
{
}

StkIpDlgMsg::~StkIpDlgMsg(void)
{
}

int StkIpDlgMsg::StopStkIpDlg(HWND hDlg) {
	return MessageBox(hDlg, 
		_T("Are you sure you want to stop the wizard?"), 
		STK_IP_DLG_TITLE, 
		MB_YESNO | MB_ICONQUESTION | MB_APPLMODAL);
}

int StkIpDlgMsg::NetworkConfigAcquisitionError(HWND hDlg)
{
	return MessageBox(hDlg, 
		_T("An error has occurred in obtaining the network configuration.\r\nThe wizard will be stopped."), 
		STK_IP_DLG_TITLE, 
		MB_OK | MB_ICONEXCLAMATION | MB_APPLMODAL);
}

int StkIpDlgMsg::TooMuchIPFoundError(HWND hDlg)
{
	return MessageBox(hDlg, 
		_T("The number of IP addresses acquired has exceeded the program's limit.\r\nThe wizard will be stopped."), 
		STK_IP_DLG_TITLE, 
		MB_OK | MB_ICONEXCLAMATION | MB_APPLMODAL);
}

int StkIpDlgMsg::NetworkConfigChangeError(HWND hDlg)
{
	return MessageBox(hDlg, 
		_T("An error has occurred in changing the network configuration.\r\n- Check the user rights and execute the program with administrator's rights.\r\n- If the host bits of the IP address are all 0 or 1, the operation cannot be executed correctly.\r\n- Check that the target IP address is not reserved by the operating system."), 
		STK_IP_DLG_TITLE, 
		MB_OK | MB_ICONEXCLAMATION | MB_APPLMODAL);
}

int StkIpDlgMsg::NoNetworkAdapterFoundError(HWND hDlg)
{
	return MessageBox(hDlg, 
		_T("No network adapter has been found.\r\nThe wizard will be stopped."), 
		STK_IP_DLG_TITLE, 
		MB_OK | MB_ICONEXCLAMATION | MB_APPLMODAL);
}

int StkIpDlgMsg::ParameterError(HWND hDlg)
{
	return MessageBox(hDlg, 
		_T("Incorrect parameter specification\r\n- Each edit box of the IP address must be in the range 0-255.\r\n- The max value for \"Number of IP addresses\" is 256.\r\n- In the case of adding IP addresses, the subnet mask must be presented."), 
		STK_IP_DLG_TITLE, 
		MB_OK | MB_ICONEXCLAMATION | MB_APPLMODAL);
}

int StkIpDlgMsg::TakeALongTime(HWND hDlg)
{
	return MessageBox(hDlg, 
		_T("This operation will take a while to finish.\r\nPlease wait for the next screen to appear."),
		STK_IP_DLG_TITLE, 
		MB_OK | MB_ICONINFORMATION | MB_APPLMODAL);
}

int StkIpDlgMsg::RestrictionOfEffect(HWND hDlg)
{
	return MessageBox(hDlg, 
		_T("The changes performed by this wizard will be effective until the operating system is shut down."),
		STK_IP_DLG_TITLE, 
		MB_OK | MB_ICONINFORMATION | MB_APPLMODAL);
}
