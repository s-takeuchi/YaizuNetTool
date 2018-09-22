#include <windows.h>
#include <tchar.h>
#include <math.h>
#include <stdlib.h>
#include "resource.h"
#include "..\stklib\ActorRequest.h"
#include "..\stklib\StkFont.h"
#include "NetGseEx.h"
#include "stklibtest.h"
#include "..\..\..\YaizuComLib\src\stkthread\stkthread.h"
#include "..\..\..\YaizuComLib\src\stkthreadgui\stkthreadgui.h"
#include "MyMsgProc.h"

CRITICAL_SECTION NetGseEx::CritSect;
int NetGseEx::RtiRefreshInterval;
int NetGseEx::RtiElementCount;
int NetGseEx::RtiRequestCount;
int NetGseEx::RtiRunningCount;

NetGseEx::NetGseEx()
{
}

NetGseEx::~NetGseEx()
{
}

void NetGseEx::DrawOfficeASELink(HINSTANCE hinst, HWND hwnd, HDC hdc, ActorRequest* ActReq)
{
	int r = ActReq->GetRequest();
	int c = ActReq->GetActorId();
	int bottom = ActReq->GetIntParam1();
	int top = ActReq->GetIntParam2();
	int right = ActReq->GetIntParam3();
	int left = ActReq->GetIntParam4();

	SetBkMode(hdc, TRANSPARENT);
	HPEN Pen;
	COLORREF Col;
	int Stl;
	if (r >= 140) {
		Col = RGB(128, 128, 128);
		r -= 140;
	} else if (r >= 130) {
		Col = RGB(128, 128, 255);
		r -= 130;
	} else if (r >= 120) {
		Col = RGB(113, 225, 113);
		r -= 120;
	} else if (r >= 110) {
		Col = RGB(235, 118, 118);
		r -= 110;
	} else if (r >= 100) {
		Col = RGB(215, 215, 215);
		r -= 100;
	}
	if (r == 1) {
		Stl = PS_SOLID;
	} else if (r == 2) {
		Stl = PS_DOT;
	} else if (r == 3) {
		Stl = PS_DASH;
	}

	Pen = CreatePen(Stl, 1, Col);
	HPEN OldPen = (HPEN)SelectObject(hdc, Pen);

	POINT p[2];
	p[0].x = bottom;
	p[0].y = top;
	p[1].x = right;
	p[1].y = left;
	Polyline(hdc, p, 2);

	int ItmX = (p[0].x + p[1].x) / 2;
	int ItmY = (p[0].y + p[1].y) / 2;
	double x = p[0].x - p[1].x;
	double y = p[0].y - p[1].y;
	double ro = atan2(y, x);
	POINT arp[3];
	arp[0].x = int((10) * cos(ro) - (5) * sin(ro)) + ItmX;
	arp[0].y = int((10) * sin(ro) + (5) * cos(ro)) + ItmY;
	arp[1].x = ItmX;
	arp[1].y = ItmY;
	arp[2].x = int((10) * cos(ro) - (-5) * sin(ro)) + ItmX;
	arp[2].y = int((10) * sin(ro) + (-5) * cos(ro)) + ItmY;
	MoveToEx(hdc, arp[1].x, arp[1].y, NULL);
	LineTo(hdc, arp[0].x, arp[0].y);
	MoveToEx(hdc, arp[1].x, arp[1].y, NULL);
	LineTo(hdc, arp[2].x, arp[2].y);

	SelectObject(hdc, OldPen);
	DeleteObject(Pen);
}

void NetGseEx::DrawOfficeASE(HINSTANCE hinst, HWND hwnd, HDC hdc, ActorRequest* ActReq)
{
	static BOOL Init = TRUE;
	if (Init == TRUE) {
		Init = FALSE;
		IconHndl[1] = LoadIcon(hinst, MAKEINTRESOURCE(IDI_ICON1));
		IconHndl[2] = LoadIcon(hinst, MAKEINTRESOURCE(IDI_ICON2));
		IconHndl[3] = LoadIcon(hinst, MAKEINTRESOURCE(IDI_ICON3));
		IconHndl[4] = LoadIcon(hinst, MAKEINTRESOURCE(IDI_ICON4));
		IconHndl[5] = LoadIcon(hinst, MAKEINTRESOURCE(IDI_ICON5));
		IconHndl[6] = LoadIcon(hinst, MAKEINTRESOURCE(IDI_ICON6));
		IconHndl[7] = LoadIcon(hinst, MAKEINTRESOURCE(IDI_ICON7));
		IconHndl[8] = LoadIcon(hinst, MAKEINTRESOURCE(IDI_ICON8));
		IconHndl[9] = LoadIcon(hinst, MAKEINTRESOURCE(IDI_ICON9));
		IconHndl[10] = LoadIcon(hinst, MAKEINTRESOURCE(IDI_ICON10));
		IconHndl[11] = LoadIcon(hinst, MAKEINTRESOURCE(IDI_ICON11));
		IconHndl[12] = LoadIcon(hinst, MAKEINTRESOURCE(IDI_ICON12));
		IconHndl[13] = LoadIcon(hinst, MAKEINTRESOURCE(IDI_ICON13));
		IconHndl[14] = LoadIcon(hinst, MAKEINTRESOURCE(IDI_ICON14));
		IconHndl[15] = LoadIcon(hinst, MAKEINTRESOURCE(IDI_ICON15));
		IconHndl[16] = LoadIcon(hinst, MAKEINTRESOURCE(IDI_ICON16));
		IconHndl[17] = LoadIcon(hinst, MAKEINTRESOURCE(IDI_ICON17));
		IconHndl[18] = LoadIcon(hinst, MAKEINTRESOURCE(IDI_ICON18));
		IconHndl[19] = LoadIcon(hinst, MAKEINTRESOURCE(IDI_ICON19));
		IconHndl[20] = LoadIcon(hinst, MAKEINTRESOURCE(IDI_ICON20));
		IconHndl[21] = LoadIcon(hinst, MAKEINTRESOURCE(IDI_ICON21));
		IconHndl[22] = LoadIcon(hinst, MAKEINTRESOURCE(IDI_ICON22));
		IconHndl[23] = LoadIcon(hinst, MAKEINTRESOURCE(IDI_ICON23));
		IconHndl[24] = LoadIcon(hinst, MAKEINTRESOURCE(IDI_ICON24));
		IconHndl[25] = LoadIcon(hinst, MAKEINTRESOURCE(IDI_ICON25));
		IconHndl[26] = LoadIcon(hinst, MAKEINTRESOURCE(IDI_ICON26));
		IconHndl[27] = LoadIcon(hinst, MAKEINTRESOURCE(IDI_ICON27));
		IconHndl[28] = LoadIcon(hinst, MAKEINTRESOURCE(IDI_ICON28));
		IconHndl[29] = LoadIcon(hinst, MAKEINTRESOURCE(IDI_ICON29));
		IconHndl[30] = LoadIcon(hinst, MAKEINTRESOURCE(IDI_ICON30));
		IconHndl[31] = LoadIcon(hinst, MAKEINTRESOURCE(IDI_ICON31));
		IconHndl[32] = LoadIcon(hinst, MAKEINTRESOURCE(IDI_ICON32));
		IconHndl[33] = LoadIcon(hinst, MAKEINTRESOURCE(IDI_ICON33));
		IconHndl[34] = LoadIcon(hinst, MAKEINTRESOURCE(IDI_ICON34));
		IconHndl[35] = LoadIcon(hinst, MAKEINTRESOURCE(IDI_ICON35));
		IconHndl[36] = LoadIcon(hinst, MAKEINTRESOURCE(IDI_ICON36));
		IconHndl[37] = LoadIcon(hinst, MAKEINTRESOURCE(IDI_ICON37));
		IconHndl[38] = LoadIcon(hinst, MAKEINTRESOURCE(IDI_ICON38));
		IconHndl[39] = LoadIcon(hinst, MAKEINTRESOURCE(IDI_ICON39));
		IconHndl[40] = LoadIcon(hinst, MAKEINTRESOURCE(IDI_ICON40));
		IconHndl[41] = LoadIcon(hinst, MAKEINTRESOURCE(IDI_ICON41));
		IconHndl[42] = LoadIcon(hinst, MAKEINTRESOURCE(IDI_ICON42));
		IconHndl[43] = LoadIcon(hinst, MAKEINTRESOURCE(IDI_ICON43));
		IconHndl[44] = LoadIcon(hinst, MAKEINTRESOURCE(IDI_ICON44));
		IconHndl[45] = LoadIcon(hinst, MAKEINTRESOURCE(IDI_ICON45));
		IconHndl[46] = LoadIcon(hinst, MAKEINTRESOURCE(IDI_ICON46));
		IconHndl[47] = LoadIcon(hinst, MAKEINTRESOURCE(IDI_ICON47));
		IconHndl[48] = LoadIcon(hinst, MAKEINTRESOURCE(IDI_ICON48));
		IconHndl[50] = (HICON)LoadImage(hinst, MAKEINTRESOURCE(IDI_ICON50), IMAGE_ICON, 16, 16, LR_DEFAULTCOLOR);
		IconHndl[51] = (HICON)LoadImage(hinst, MAKEINTRESOURCE(IDI_ICON51), IMAGE_ICON, 16, 16, LR_DEFAULTCOLOR);
		IconHndl[52] = (HICON)LoadImage(hinst, MAKEINTRESOURCE(IDI_ICON52), IMAGE_ICON, 16, 16, LR_DEFAULTCOLOR);
		IconHndl[53] = (HICON)LoadImage(hinst, MAKEINTRESOURCE(IDI_ICON53), IMAGE_ICON, 16, 16, LR_DEFAULTCOLOR);
		IconHndl[54] = (HICON)LoadImage(hinst, MAKEINTRESOURCE(IDI_ICON54), IMAGE_ICON, 16, 16, LR_DEFAULTCOLOR);
		IconHndl[55] = (HICON)LoadImage(hinst, MAKEINTRESOURCE(IDI_ICON55), IMAGE_ICON, 16, 16, LR_DEFAULTCOLOR);
		IconHndl[56] = (HICON)LoadImage(hinst, MAKEINTRESOURCE(IDI_ICON56), IMAGE_ICON, 16, 16, LR_DEFAULTCOLOR);
		IconHndl[60] = (HICON)LoadImage(hinst, MAKEINTRESOURCE(IDI_ICON60), IMAGE_ICON, 16, 16, LR_DEFAULTCOLOR);
		IconHndl[61] = (HICON)LoadImage(hinst, MAKEINTRESOURCE(IDI_ICON61), IMAGE_ICON, 16, 16, LR_DEFAULTCOLOR);
		IconHndl[62] = (HICON)LoadImage(hinst, MAKEINTRESOURCE(IDI_ICON62), IMAGE_ICON, 16, 16, LR_DEFAULTCOLOR);
		IconHndl[71] = LoadIcon(hinst, MAKEINTRESOURCE(IDI_ICON71));
		IconHndl[72] = LoadIcon(hinst, MAKEINTRESOURCE(IDI_ICON72));
		IconHndl[73] = LoadIcon(hinst, MAKEINTRESOURCE(IDI_ICON73));
		IconHndl[74] = LoadIcon(hinst, MAKEINTRESOURCE(IDI_ICON74));
	}

	int r = ActReq->GetRequest();
	int c = ActReq->GetActorId();
	int bottom = ActReq->GetIntParam1();
	int top = ActReq->GetIntParam2();
	int right = ActReq->GetIntParam3();
	int left = ActReq->GetIntParam4();
	TCHAR* NameBuf = ActReq->GetStringParam1();

	StkFont* Fon = StkFont::GetInstance();

	if (r < 0) {
		RECT rt;
		HBRUSH b1 = CreateSolidBrush(RGB(255, 255, 255));
		SelectObject(hdc, b1);
		rt.right = right;
		rt.left = left;
		rt.top = top;
		rt.bottom = bottom;
		FillRect(hdc, &rt, b1);
		DeleteObject(b1);
		r *= -1;
	}
	int SizeW = right - left;
	int SizeH = bottom - top;
	DrawIconEx(hdc, left, top, IconHndl[r], SizeW, SizeH, NULL, NULL, DI_NORMAL);
	Fon->ArialFontSmallTextOut(hdc, left + SizeW / 2, bottom + 5, NameBuf, RGB(255, 255, 255), TRUE);
}

// A function which is called from RefreshScreen
void NetGseEx::RefreshScreenProcess(HINSTANCE hinst, HWND hwnd, HDC hdc)
{
	int EleCnt = 0;

	// Draw background
	OfficeGSE::DrawBackground(hinst, hwnd, hdc);

	for (int i = 0; i < m_CurrentRequest; i++) {
		int c = m_ActReq[i]->GetActorId();
		int r = m_ActReq[i]->GetRequest();
		if (c != 0 && r >= 100) {
			// Draw Link of each element
			DrawOfficeASELink(hinst, hwnd, hdc, m_ActReq[i]);
		} else if (c == 0) {
			// Draw OfficeManagerASE
			OfficeGSE::DrawOfficeManagerASE(hinst, hwnd, hdc, m_ActReq[i]);
		}
	}
	for (int i = 0; i < m_CurrentRequest; i++) {
		int c = m_ActReq[i]->GetActorId();
		int r = m_ActReq[i]->GetRequest();
		// Draw OfficeASE
		if (c != 0 && r < 100) {
			EleCnt++;
			DrawOfficeASE(hinst, hwnd, hdc, m_ActReq[i]);
		}
	}

	// RunTime information
	static DWORD ctime = 0;
	static DWORD ptime = 0;
	ctime = GetTickCount();
	if (ptime != 0) {
		RtiRefreshInterval = ctime - ptime;
	} else {
		RtiRefreshInterval = 0;
	}
	ptime = ctime;
	RtiElementCount = EleCnt;
	RtiRequestCount = m_CurrentRequest;
	RtiRunningCount = GetNumOfRunStkThread();

	SetMouseAction(0);

	// When some threads are running...
	if (GetNumOfRunStkThread() != 0) {
		int ArsWidth = m_ActiveRSRight - m_ActiveRSLeft;
		int ArsHeight = m_ActiveRSBottom - m_ActiveRSTop;
		static int StatusRunX[4];
		static int StatusRunY[4];
		static int RunningRefreshInterval = 0;
		if (RunningRefreshInterval >= 1000) {
			RunningRefreshInterval = 0;
		}
		if (RunningRefreshInterval == 0) {
			for (int Loop = 0; Loop < 4; Loop++) {
				StatusRunX[Loop] = rand() % (ArsWidth - 200) + m_ActiveRSLeft;
				StatusRunY[Loop] = rand() % (ArsHeight - 80) + m_ActiveRSTop;
			}
		}
		RunningRefreshInterval += RtiRefreshInterval;

		int NumOfOut = 1;
		if (ArsWidth * ArsHeight >= 1310720) { // >= SXGA
			NumOfOut = 4;
		} else if (ArsWidth * ArsHeight >= 786432) { // >= XGA
			NumOfOut = 3;
		} else if (ArsWidth * ArsHeight >= 480000) { // >= SVGA
			NumOfOut = 2;
		}
		for (int Loop = 0; Loop < NumOfOut; Loop++) {
			StkFont::GetInstance()->ArialFontLargeTextOut(hdc, StatusRunX[Loop], StatusRunY[Loop], MyMsgProc::GetMsg(MyMsgProc::STKFW_RUNNING), RGB(255, 255, 255), FALSE);
		}

		EnterCriticalSection(&CritSect);
		ResetWorkspace(3);
		GetViewFromDb();
		LeaveCriticalSection(&CritSect);
	}

	ClearRequest();
}
