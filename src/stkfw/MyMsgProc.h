#pragma once

class MyMsgProc
{
public:
	static const int STKFW_RUNNINGORPROPOPEN = 2101;
	static const int STKFW_OUTOFRANGE = 2102;
	static const int STKFW_DATASAVEFAILED = 2103;
	static const int STKFW_FILEINVALID = 2104;
	static const int STKFW_RUNNING = 2106;
	static const int STKFW_NODLL = 2107;
	static const int STKFW_DLLINVALID = 2108;
	static const int STKFW_ADD_PROCESSING_ELEMENT = 2110;
	static const int STKFW_DEL_PROCESSING_ELEMENT = 2111;
	static const int STKFW_ADD_LINK = 2112;
	static const int STKFW_DEL_LINK = 2113;
	static const int STKFW_DBVERSION_OLD = 2120;
	static const int STKFW_DBVERSION_UNKNOWN = 2121;
	static const int STKFW_COMPARAM_INVALID = 2123;
	static const int STKFW_COMPARAM_NOFILE = 2124;
	static const int STKFW_MANUAL_PLACE = 2125;
	static const int STKFW_CHG_WORKSPACE_SIZE = 2126;
	static const int STKFW_GRID_ONOFF = 2127;

	static const int SFW_100_1 = 9100;
	static const int SFW_100_110_1 = 9101;
	static const int SFW_100_110_2 = 9102;
	static const int SFW_100_110_3 = 9103;
	static const int SFW_100_110_4 = 9104;
	static const int SFW_100_110_5 = 9105;
	static const int SFW_100_110_6 = 9106;
	static const int SFW_110_120_1 = 9107;
	static const int SFW_110_120_2 = 9108;
	static const int SFW_110_120_3 = 9109;
	static const int SFW_110_120_4 = 9110;
	static const int SFW_110_120_5 = 9111;
	static const int SFW_110_120_6 = 9112;
	static const int SFW_110_120_7 = 9113;
	static const int SFW_110_120_8 = 9114;
	static const int SFW_120_130_1 = 9115;
	static const int SFW_120_130_2 = 9116;
	static const int SFW_120_130_3 = 9117;
	static const int SFW_120_130_4 = 9118;
	static const int SFW_130_140_1 = 9119;
	static const int SFW_130_140_2 = 9120;
	static const int SFW_130_140_3 = 9121;
	static const int SFW_130_140_4 = 9122;
	static const int SFW_130_140_5 = 9123;
	static const int SFW_130_140_6 = 9124;
	static const int SFW_140_150_1 = 9125;

	static void AddMsg();
	static TCHAR* GetMsg(int);
	static void StkErr(int, HWND);
	static void StkErr(int, TCHAR*, HWND);
	static void StkInf(int, HWND);
	static void StkInf(int, TCHAR*, HWND);
	static int StkYesNo(int, HWND);
	static int StkYesNo(int, TCHAR*, HWND);
};
