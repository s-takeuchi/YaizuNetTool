#pragma once

#include <windows.h>

class StkFont  
{
private:
	static const int STK_FONT_MAX_POINT = 20;
	static const int STK_FONT_MAX_LINE  = 20;
	static const int STK_FONT_MAX_CHARA = 100;

	class Chara
	{
	public:
		class Line
		{
		public:
			class Point
			{
			public:
				int x, y;
				void p(int x0, int y0) {
					x = x0;
					y = y0;
				}
			} point[STK_FONT_MAX_POINT];
			int length;
		} line[STK_FONT_MAX_LINE];
		int length;
		int width;
		int height;
	} chara[STK_FONT_MAX_CHARA];

	// Variables of scrolling text
	TCHAR ScrollText[256][128];
	int disp_offset;
	int disp_end;
	int rgst_offset;
	DWORD LastScrollTextOutTime;

	// Font handler of Arial
	HFONT TinyArialFontHndl;
	HFONT SmallArialFontHndl;
	HFONT MediumArialFontHndl;
	HFONT LargeArialFontHndl;

	StkFont();
	void DrawChara(HDC, int, int, int, float, float);
	void StkFontTextOut(HDC, int, int, float, float, int, LPCTSTR, COLORREF);
	void ArialFontTextOut(HDC, int, int, LPCTSTR, COLORREF);

public:
	static StkFont* GetInstance();
	virtual ~StkFont();

	void StkFontTinyTextOut(HDC, int, int, LPCTSTR, COLORREF);
	void StkFontSmallTextOut(HDC, int, int, LPCTSTR, COLORREF);
	void StkFontMediumTextOut(HDC, int, int, LPCTSTR, COLORREF);
	void StkFontLargeTextOut(HDC, int, int, LPCTSTR, COLORREF);

	void ArialFontTinyTextOut(HDC, int, int, LPCTSTR, COLORREF, BOOL);
	void ArialFontSmallTextOut(HDC, int, int, LPCTSTR, COLORREF, BOOL);
	void ArialFontMediumTextOut(HDC, int, int, LPCTSTR, COLORREF, BOOL);
	void ArialFontLargeTextOut(HDC, int, int, LPCTSTR, COLORREF, BOOL);

	void StkFontAddScrollText(LPTSTR str);
	void StkFontClearScrollText();
	void StkFontScrollTextOut(HDC, int, int, int, COLORREF);
};
