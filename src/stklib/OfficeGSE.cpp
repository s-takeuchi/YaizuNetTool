#include <windows.h>
#include "ActorRequest.h"
#include "OfficeGSE.h"
#include "OfficeManagerASE.h"

OfficeGSE::OfficeGSE()
{

}

OfficeGSE::~OfficeGSE()
{
}

// Draw background
void OfficeGSE::DrawBackground(HINSTANCE hinst, HWND hwnd, HDC hdc)
{
	RECT rt;
	rt.right = GetActiveReverseScreenRight();
	rt.left = GetActiveReverseScreenLeft();
	rt.top = GetActiveReverseScreenTop();
	rt.bottom = GetActiveReverseScreenBottom();

	HBRUSH b = CreateSolidBrush(RGB(64, 64, 64));
	HBRUSH OldB = (HBRUSH)SelectObject(hdc, b);
	FillRect(hdc, &rt, b);
	SelectObject(hdc, OldB);
	DeleteObject(b);

	if (OfficeManagerASE::GridType == 8) {
		SetBkMode(hdc, TRANSPARENT);
		HPEN Pen = CreatePen(PS_DOT, 1, RGB(128, 128, 128));
		HPEN OldPen = (HPEN)SelectObject(hdc, Pen);
		POINT p[2];
		for (int i = rt.left + OfficeManagerASE::GridType / 2; i < rt.right; i += OfficeManagerASE::GridType * 4) {
			p[0].x = i;
			p[0].y = rt.top;
			p[1].x = i;
			p[1].y = rt.bottom;
			Polyline(hdc, p, 2);
		}
		for (int i = rt.top + OfficeManagerASE::GridType / 2; i < rt.bottom; i += OfficeManagerASE::GridType * 4) {
			p[0].y = i;
			p[0].x = rt.left;
			p[1].y = i;
			p[1].x = rt.right;
			Polyline(hdc, p, 2);
		}
		SelectObject(hdc, OldPen);
		DeleteObject(Pen);
	}
}

// Draw OfficeASE
void OfficeGSE::DrawOfficeASE(HINSTANCE hinst, HWND hwnd, HDC hdc, ActorRequest* ActReq)
{
	int r = ActReq->GetRequest();
	int c = ActReq->GetActorId();
	int bottom = ActReq->GetIntParam1();
	int top = ActReq->GetIntParam2();
	int right = ActReq->GetIntParam3();
	int left = ActReq->GetIntParam4();

	if (r) {
		RECT rt;
		HBRUSH b1 = CreateSolidBrush(RGB(255, 255, 255));
		SelectObject(hdc, b1);
		rt.right = right;
		rt.left = left;
		rt.top = top;
		rt.bottom = bottom;
		FillRect(hdc, &rt, b1);
		DeleteObject(b1);
	}
	HPEN Pen = CreatePen(PS_SOLID, 0, RGB(255, 0, 0));
	SelectObject(hdc, Pen);
	POINT p[4];
	p[0].x = (right + left) / 2; p[0].y = top + 2;
	p[1].x = right - 2;          p[1].y = bottom - 2;
	p[2].x = left + 2;           p[2].y = bottom - 2;
	p[3].x = (right + left) / 2; p[3].y = top + 2;
	Polyline(hdc, p, 4);
	DeleteObject(Pen);
}

// Draw OfficeManagerASE
void OfficeGSE::DrawOfficeManagerASE(HINSTANCE hinst, HWND hwnd, HDC hdc, ActorRequest* ActReq)
{
	int r = ActReq->GetRequest();
	int c = ActReq->GetActorId();
	int bottom = ActReq->GetIntParam1();
	int top = ActReq->GetIntParam2();
	int right = ActReq->GetIntParam3();
	int left = ActReq->GetIntParam4();

	SetBkMode(hdc, TRANSPARENT);
	HPEN Pen = CreatePen(PS_DOT, 0, RGB(255, 255, 255));
	SelectObject(hdc, Pen);
	POINT p[5];
	p[0].x = left;  p[0].y = top;
	p[1].x = right; p[1].y = top;
	p[2].x = right; p[2].y = bottom;
	p[3].x = left;  p[3].y = bottom;
	p[4].x = left;  p[4].y = top;
	Polyline(hdc, p, 5);
	DeleteObject(Pen);
}

// A function which is called from RefreshScreen
void OfficeGSE::RefreshScreenProcess(HINSTANCE hinst, HWND hwnd, HDC hdc)
{
	// Draw background
	DrawBackground(hinst, hwnd, hdc);

	for (int i = 0; i < m_CurrentRequest; i++) {
		ActorRequest* ActReq = m_ActReq[i];
		int c = ActReq->GetActorId();

		// Draw OfficeASE
		if (c != 0) {
			DrawOfficeASE(hinst, hwnd, hdc, ActReq);
		}
		// Draw OfficeManagerASE
		else if (c == 0) {
			DrawOfficeManagerASE(hinst, hwnd, hdc, ActReq);
		}
	}

	ClearRequest();
}
