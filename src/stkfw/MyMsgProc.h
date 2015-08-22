#pragma once

class MyMsgProc
{
public:
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
};
