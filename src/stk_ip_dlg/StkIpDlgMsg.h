#pragma once

class StkIpDlgMsg
{
public:
	StkIpDlgMsg(void);
public:
	~StkIpDlgMsg(void);
	static int StopStkIpDlg(HWND);
	static int NetworkConfigAcquisitionError(HWND);
	static int TooMuchIPFoundError(HWND);
	static int NetworkConfigChangeError(HWND);
	static int NoNetworkAdapterFoundError(HWND);
	static int ParameterError(HWND);
	static int TakeALongTime(HWND);
};
