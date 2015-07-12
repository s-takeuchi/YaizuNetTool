#include <windows.h>
#include <tchar.h>
#include "GameStatus.h"
#include "GameStatusElement.h"
#include "ActorRequest.h"

// Definition of message constants
const TCHAR* GameStatus::MSG_TITLE             = _T("StkLib error");
const TCHAR* GameStatus::MSG_NO_WORK_SCREEN    = _T("The work screen does not exist.");
const TCHAR* GameStatus::MSG_WORK_SCREEN_EXIST = _T("The work screen has already been created.");
const TCHAR* GameStatus::MSG_INCORRECT_STATUS  = _T("An incorrect status was specified.");
const TCHAR* GameStatus::MSG_START_FAILED      = _T("Refresh screen process start has failed.");
const TCHAR* GameStatus::MSG_STOP_FAILED       = _T("Refresh screen process stop has failed.");
const TCHAR* GameStatus::MSG_NO_HWND           = _T("No HWND is set.");

// �Q�[���̏��
#define GAME_STATUS_INIT 0

// �^�C�}�[ID�̏����l
#define GAME_STATUS_TIMER_ID_INIT 0
#define GAME_STATUS_TIMER_ID 101

int GameStatus::m_gameStatus; // �Q�[���̏��
HWND GameStatus::m_hwnd; // window handler
HINSTANCE GameStatus::m_hinst; // instance handler
HDC GameStatus::m_hdc; // �f�o�C�X�R���e�L�X�g�n���h��
GameStatusElement *GameStatus::m_gse[GAME_STATUS_COUNT]; // �Q�[���̏�Ԗ��̏���

//////////////////////////////////////////////////////////////////////
// �\�z/����
//////////////////////////////////////////////////////////////////////

GameStatus::GameStatus()
{
	// �Q�[���̏�Ԃ̐��̐ݒ�
	m_gameStatus = GAME_STATUS_INIT;

	// �^�C�}�[ID�̏�����
	m_timerId = GAME_STATUS_TIMER_ID_INIT;

	// ����ʂ̏�����
	m_hwnd = NULL;
	m_hinst = NULL;
	m_hdc = NULL;

	// �Q�[���̏�Ԗ��̏���������������
	for (int i = 0; i < GAME_STATUS_COUNT; i++) {
		m_gse[i] = NULL;
	}

	DrawScreenExFlag = TRUE;

	InitializeCriticalSection(&CritSect);
}

GameStatus::~GameStatus()
{

}

//////////////////////////////////////////////////////////////////////
// �v���C�x�[�g���\�b�h
//////////////////////////////////////////////////////////////////////

// �ő�^�ŏ��E�B���h�E�T�C�Y�̐ݒ�
void GameStatus::SetMinMaxWindowSize(LPARAM lParam)
{
	if (m_gse[m_gameStatus] == NULL) {
		return;
	}
	LPMINMAXINFO lpmmi;
	lpmmi = (LPMINMAXINFO)lParam;
	int minx = m_gse[m_gameStatus]->GetMinWindowSizeX();
	int miny = m_gse[m_gameStatus]->GetMinWindowSizeY();
	int maxx = m_gse[m_gameStatus]->GetMaxWindowSizeX();
	int maxy = m_gse[m_gameStatus]->GetMaxWindowSizeY();
	if (minx != -1) {
		lpmmi->ptMinTrackSize.x = minx;
	}
	if (miny != -1) {
		lpmmi->ptMinTrackSize.y = miny;
	}
	if (maxx != -1) {
		lpmmi->ptMaxTrackSize.x = maxx;
	}
	if (maxy != -1) {
		lpmmi->ptMaxTrackSize.y = maxy;
	}
}

// �X�N���[���o�[�̒���
void GameStatus::ResetScrollBarInfo()
{
	int ARSright, ARSleft, ARStop, ARSbottom;
	int ARSxlen, ARSylen;
	int xlen, ylen;
	RECT rt;
	SCROLLINFO Info;

	if (m_gse[m_gameStatus] == NULL) {
		return;
	}

	if (!m_gse[m_gameStatus]->GetScrollBarFlag()) {
		ShowScrollBar(m_hwnd, SB_HORZ, FALSE);
		Info.cbSize = sizeof(SCROLLINFO);
		Info.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS | SIF_DISABLENOSCROLL;
		Info.nMin   = 0;
		Info.nMax   = 0;
		Info.nPos   = 0;
		Info.nPage  = 0;
		SetScrollInfo(m_hwnd, SB_HORZ, &Info, 0);

		ShowScrollBar(m_hwnd, SB_VERT, FALSE);
		Info.cbSize = sizeof(SCROLLINFO);
		Info.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS | SIF_DISABLENOSCROLL;
		Info.nMin   = 0;
		Info.nMax   = 0;
		Info.nPos   = 0;
		Info.nPage  = 0;
		SetScrollInfo(m_hwnd, SB_VERT, &Info, 0);
		return;
	}

	ARSright = m_gse[m_gameStatus]->GetActiveReverseScreenRight();
	ARSleft = m_gse[m_gameStatus]->GetActiveReverseScreenLeft();
	ARStop = m_gse[m_gameStatus]->GetActiveReverseScreenTop();
	ARSbottom = m_gse[m_gameStatus]->GetActiveReverseScreenBottom();

	if (ARSright < 0 || ARSleft < 0 || ARStop < 0 || ARSbottom < 0) {
		return;
	}

	ARSxlen = ARSright - ARSleft;
	ARSylen = ARSbottom - ARStop;

	GetClientRect(m_hwnd, &rt);
	xlen = rt.right - rt.left;
	ylen = rt.bottom - rt.top;

	if (xlen < ARSxlen) {
		ShowScrollBar(m_hwnd, SB_HORZ, TRUE);
	} else {
		ShowScrollBar(m_hwnd, SB_HORZ, FALSE);
	}
	if (ylen < ARSylen) {
		ShowScrollBar(m_hwnd, SB_VERT, TRUE);
	} else {
		ShowScrollBar(m_hwnd, SB_VERT, FALSE);
	}

	GetClientRect(m_hwnd, &rt);
	xlen = rt.right - rt.left;
	ylen = rt.bottom - rt.top;

	Info.cbSize = sizeof(SCROLLINFO);
	Info.nMin   = 0;
	Info.nPos   = 0;
	if (xlen < ARSxlen) {
		Info.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS;
		Info.nMax   = ARSxlen;
		Info.nPage  = xlen;
		SetScrollInfo(m_hwnd, SB_HORZ, &Info, 1);
	} else {
		Info.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS | SIF_DISABLENOSCROLL;
		Info.nMax   = 0;
		Info.nPage  = 0;
		SetScrollInfo(m_hwnd, SB_HORZ, &Info, 0);
	}

	Info.cbSize = sizeof(SCROLLINFO);
	Info.nMin   = 0;
	Info.nPos   = 0;
	if (ylen < ARSylen) {
		Info.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS;
		Info.nMax   = ARSylen;
		Info.nPage  = ylen;
		SetScrollInfo(m_hwnd, SB_VERT, &Info, 1);
	} else {
		Info.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS | SIF_DISABLENOSCROLL;
		Info.nMax   = 0;
		Info.nPage  = 0;
		SetScrollInfo(m_hwnd, SB_VERT, &Info, 0);
	}
}

// ��ʂ̃T�C�Y���̕ύX
void GameStatus::ChangeWindow()
{
	int cx, cy;
	RECT rt;

	cx = m_gse[m_gameStatus]->GetCurrentWindowSizeX();
	cy = m_gse[m_gameStatus]->GetCurrentWindowSizeY();
	GetWindowRect(m_hwnd, &rt);
	MoveWindow(m_hwnd, rt.left, rt.top, cx, cy, TRUE);
	ResetScrollBarInfo();
}

// ����I�ȉ�ʂ̍X�V
LRESULT CALLBACK GameStatus::RefreshScreen(HWND hwnd, UINT uMsg, UINT idEvent, DWORD dwTime)
{
	if (m_hwnd == NULL || m_hdc == NULL) {
		return TRUE;
	}

	if (m_gse[m_gameStatus] != NULL) {
		m_gse[m_gameStatus]->RefreshScreenProcess(m_hinst, m_hwnd, m_hdc);
	}
	ActorRequest::SynchroFlag = FALSE;

	RedrawWindow(m_hwnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);

	return TRUE;
}

// ����ʂ���\��ʂւ̃R�s�[
// WM_PAINT���n���h��������ɌĂяo��
void GameStatus::DrawScreen()
{
	PAINTSTRUCT ps;
	RECT rt;
	SCROLLINFO Info;
	int x, y;
	int ARSleft, ARSright, ARStop, ARSbottom;
	int lx, ly;
	//static int LastGameStatus = -1;

	x = y = 0;
	GetClientRect(m_hwnd, &rt);
	lx = rt.left;
	ly = rt.top;

	if (m_gse[m_gameStatus] != NULL) {
		if (DrawScreenExFlag == TRUE) {
			ChangeWindow();
			DrawScreenExFlag = FALSE;
		}

		ARSleft = m_gse[m_gameStatus]->GetActiveReverseScreenLeft();
		ARSright = m_gse[m_gameStatus]->GetActiveReverseScreenRight();
		ARStop = m_gse[m_gameStatus]->GetActiveReverseScreenTop();
		ARSbottom = m_gse[m_gameStatus]->GetActiveReverseScreenBottom();

		if (ARSleft != -1 && ARSright != -1) {
			if ((ARSright - ARSleft) < (rt.right - rt.left)) {
				lx = rt.left + (ARSright - ARSleft);
			} else {
				lx = rt.right;
			}
		}
		if (ARSbottom != -1 && ARStop != -1) {
			if ((ARSbottom - ARStop) < (rt.bottom - rt.top)) {
				ly = rt.top + (ARSbottom - ARStop);
			} else {
				ly = rt.bottom;
			}
		}

		Info.fMask  = SIF_RANGE | SIF_POS;
		Info.cbSize = sizeof(SCROLLINFO);
		if (ARSleft != -1) {
			x = ARSleft;
			if (m_gse[m_gameStatus]->GetScrollBarFlag()) {
				GetScrollInfo(m_hwnd, SB_HORZ, &Info);
				if (Info.nMin == 0 && Info.nMax >= Info.nPos && Info.nPos > 0) {
					x = ARSleft + Info.nPos;
				}
			}
		}
		if (ARStop != -1) {
			y = ARStop;
			if (m_gse[m_gameStatus]->GetScrollBarFlag()) {
				GetScrollInfo(m_hwnd, SB_VERT, &Info);
				if (Info.nMin == 0 && Info.nMax >= Info.nPos && Info.nPos > 0) {
					y = ARStop + Info.nPos;
				}
			}
		}
	}

	HDC hdc = BeginPaint(m_hwnd, &ps);
	BitBlt(hdc, rt.left, rt.top, lx, ly, m_hdc, x, y, SRCCOPY);
	EndPaint(m_hwnd, &ps);
}

//////////////////////////////////////////////////////////////////////
// ���̑����
//////////////////////////////////////////////////////////////////////

void GameStatus::SetDrawScreenExFlag()
{
	DrawScreenExFlag = TRUE;
}

// ����ʂ̍쐬
void GameStatus::CreateReverseScreen(int x, int y)
{
	if (m_hwnd == NULL) {
		MessageBox(NULL,
					MSG_NO_HWND,
					MSG_TITLE,
					MB_OK | MB_ICONEXCLAMATION | MB_SYSTEMMODAL);
		ExitProcess(-1);
	}
	if (m_hdc != NULL) {
		MessageBox(NULL,
					MSG_WORK_SCREEN_EXIST,
					MSG_TITLE,
					MB_OK | MB_ICONEXCLAMATION | MB_SYSTEMMODAL);
		ExitProcess(-1);
	}

	HDC hdc = GetDC(m_hwnd);
	m_hdc = CreateCompatibleDC(hdc);
	HBITMAP bitmap = CreateCompatibleBitmap(hdc, x, y);
	HBITMAP _bitmap = (HBITMAP)SelectObject(m_hdc, bitmap);
	DeleteObject(_bitmap);
	ReleaseDC(m_hwnd, hdc);
}

// Get window handler
HWND GameStatus::GetHWnd()
{
	return m_hwnd;
}

// Set window handler
void GameStatus::SetHWnd(HWND hwnd)
{
	m_hwnd = hwnd;
}

// Get instance handler
HINSTANCE GameStatus::GetHInstance()
{
	return m_hinst;
}

// Set instance handler
void GameStatus::SetHInstance(HINSTANCE hinst)
{
	m_hinst = hinst;
}

// �Q�[���̏�Ԃ̎擾
int GameStatus::GetGameStatus()
{
	return m_gameStatus;
}

// �Q�[���̏�Ԃ̐ݒ�
void GameStatus::SetGameStatus(int gameStatus)
{
	m_gameStatus = gameStatus;
}

// �Q�[���̏�Ԃ̕ύX
void GameStatus::ChangeGameStatus(int gameStatus)
{
	if (gameStatus < 0 || gameStatus >= GAME_STATUS_COUNT) {
		MessageBox(NULL,
					MSG_INCORRECT_STATUS,
					MSG_TITLE,
					MB_OK | MB_ICONEXCLAMATION | MB_SYSTEMMODAL);
		ExitProcess(-1);
	}

	if (gameStatus != m_gameStatus) {
		StopRefreshScreen();
		m_gameStatus = gameStatus;
		StartRefreshScreen();
	}

	DrawScreenExFlag = TRUE;
}

// ����I��RefreshScreen�̌Ăяo�����J�n����
void GameStatus::StartRefreshScreen()
{
	EnterCriticalSection(&CritSect);

	// ���ɒ���I��RefreshScreen�̌Ăяo�����J�n����Ă���
	if (m_timerId != GAME_STATUS_TIMER_ID_INIT) {
		MessageBox(NULL,
					MSG_START_FAILED,
					MSG_TITLE,
					MB_OK | MB_ICONEXCLAMATION | MB_SYSTEMMODAL);
		ExitProcess(-1);
	}

	// Check whether HWND is set or not.
	if (m_hwnd == NULL) {
		MessageBox(NULL, MSG_NO_HWND, MSG_TITLE, MB_OK | MB_ICONEXCLAMATION | MB_SYSTEMMODAL);
		ExitProcess(-1);
	}
	// Check whether HDC is set or not.
	if (m_hdc == NULL) {
		MessageBox(NULL, MSG_NO_WORK_SCREEN, MSG_TITLE, MB_OK | MB_ICONEXCLAMATION | MB_SYSTEMMODAL);
		ExitProcess(-1);
	}

	// �Q�[���̏�Ԗ��̏��������݂��邩
	if (m_gse[m_gameStatus] == NULL) {
		MessageBox(NULL,
					MSG_START_FAILED,
					MSG_TITLE,
					MB_OK | MB_ICONEXCLAMATION | MB_SYSTEMMODAL);
		ExitProcess(-1);
	}

	// ����I��RefreshScreen�̌Ăяo�����J�n
	m_timerId = SetTimer(m_hwnd, GAME_STATUS_TIMER_ID, m_gse[m_gameStatus]->GetRefreshInterval(), (TIMERPROC)GameStatus::RefreshScreen);
	if (m_timerId == 0) {
		MessageBox(NULL,
					MSG_START_FAILED,
					MSG_TITLE,
					MB_OK | MB_ICONEXCLAMATION | MB_SYSTEMMODAL);
		ExitProcess(-1);
	}

	LeaveCriticalSection(&CritSect);
}

// ����I��RefreshScreen�̌Ăяo�����~����
void GameStatus::StopRefreshScreen()
{
	EnterCriticalSection(&CritSect);

	// ���ɒ���I��RefreshScreen�̌Ăяo������~����Ă���
	if (m_timerId == GAME_STATUS_TIMER_ID_INIT) {
		MessageBox(NULL,
					MSG_STOP_FAILED,
					MSG_TITLE,
					MB_OK | MB_ICONEXCLAMATION | MB_SYSTEMMODAL);
		ExitProcess(-1);
	}

	BOOL res = KillTimer(m_hwnd, m_timerId);

	// �ΏۂƂȂ�^�C�}�[�C�x���g�����݂��Ȃ�
	if (res == 0) {
		MessageBox(NULL,
					MSG_STOP_FAILED,
					MSG_TITLE,
					MB_OK | MB_ICONEXCLAMATION | MB_SYSTEMMODAL);
		ExitProcess(-1);
	}
	m_timerId = GAME_STATUS_TIMER_ID_INIT; // �^�C�}�[ID�̏�����

	LeaveCriticalSection(&CritSect);
}

// �Q�[���̏�ԂɑΉ����������̒ǉ�
void GameStatus::AddGameStatusElement(int gameStatus, GameStatusElement *gse)
{
	m_gse[gameStatus] = gse;
}

 // �Q�[���̏�ԂɑΉ����������̍폜
void GameStatus::DeleteGameStatusElement(int gameStatus)
{
	delete m_gse[gameStatus];
}

// �Q�[���̏�ԂɑΉ����������̎擾
GameStatusElement* GameStatus::GetGameStatusElement(int gameStatus)
{
	return m_gse[gameStatus];
}

int GameStatus::ChangeClientToWorldX(int x)
{
	if (m_gse[m_gameStatus] == NULL) {
		return -1;
	}
	x += m_gse[m_gameStatus]->GetActiveReverseScreenLeft();
	if (m_gse[m_gameStatus]->GetScrollBarFlag()) {
		SCROLLINFO Info;
		Info.fMask = SIF_POS;
		Info.cbSize = sizeof(SCROLLINFO);
		GetScrollInfo(m_hwnd, SB_HORZ, &Info);
		x += Info.nPos;
	}
	return x;
}

int GameStatus::ChangeClientToWorldY(int y)
{
	if (m_gse[m_gameStatus] == NULL) {
		return -1;
	}
	y += m_gse[m_gameStatus]->GetActiveReverseScreenTop();
	if (m_gse[m_gameStatus]->GetScrollBarFlag()) {
		SCROLLINFO Info;
		Info.fMask = SIF_POS;
		Info.cbSize = sizeof(SCROLLINFO);
		GetScrollInfo(m_hwnd, SB_VERT, &Info);
		y += Info.nPos;
	}
	return y;
}

int GameStatus::ChangeClientToWindowX(int x, BOOL ScrollBarFlag)
{
	int Ret = 0;
	if (ScrollBarFlag) {
		Ret += GetSystemMetrics(SM_CXVSCROLL);
	}
	Ret += (x + GetSystemMetrics(SM_CXSIZEFRAME) * 2 - 1);
	return Ret;
}

int GameStatus::ChangeClientToWindowY(int y, BOOL ScrollBarFlag)
{
	int Ret = 0;
	if (ScrollBarFlag) {
		Ret += GetSystemMetrics(SM_CYHSCROLL);
	}
	if (m_hwnd) {
		HMENU MenHndl = GetMenu(m_hwnd);
		if (MenHndl != NULL) {
			Ret += GetSystemMetrics(SM_CYMENU);
		}
	}
	Ret += (y + GetSystemMetrics(SM_CYSIZEFRAME) * 2 + GetSystemMetrics(SM_CYCAPTION) - 1);
	return Ret;
}

// WM Message dispatcher
void GameStatus::MessageDispatcher(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (m_hwnd == NULL || m_hdc == NULL || m_gse[m_gameStatus] == NULL) {
		return;
	}

	switch(message) {
		case WM_CREATE:
			break;
		case WM_PAINT:
			DrawScreen();
			break;
		case WM_GETMINMAXINFO:
			SetMinMaxWindowSize(lParam);
			break;
		case WM_SIZE:
			ResetScrollBarInfo();
			break;
		case WM_HSCROLL:
			{
				SCROLLINFO Info;
				Info.fMask = SIF_POS;
				Info.cbSize = sizeof(SCROLLINFO);
				GetScrollInfo(m_hwnd, SB_HORZ, &Info);
				WORD nScrollCode = (WORD)LOWORD(wParam);
				WORD nPos = (WORD)HIWORD(wParam);
				switch (nScrollCode) {
					case SB_LINELEFT:
						Info.nPos -= 10;
						break;
					case SB_LINERIGHT:
						Info.nPos += 10;
						break;
					case SB_PAGELEFT:
						Info.nPos -= 100;
						break;
					case SB_PAGERIGHT:
						Info.nPos += 100;
						break;
					case SB_THUMBPOSITION:
						Info.nPos = nPos;
						break;
					case SB_THUMBTRACK:
						Info.nPos = nPos;
						break;
					default:
						return;
				}
				SetScrollInfo(m_hwnd, SB_HORZ, &Info, 1);
				RedrawWindow(m_hwnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
			}
			break;
		case WM_VSCROLL:
			{
				SCROLLINFO Info;
				Info.fMask = SIF_POS;
				Info.cbSize = sizeof(SCROLLINFO);
				GetScrollInfo(m_hwnd, SB_VERT, &Info);
				WORD nScrollCode = (WORD)LOWORD(wParam);
				WORD nPos = (WORD)HIWORD(wParam);
				switch (nScrollCode) {
					case SB_LINEUP:
						Info.nPos -= 10;
						break;
					case SB_LINEDOWN:
						Info.nPos += 10;
						break;
					case SB_PAGEUP:
						Info.nPos -= 100;
						break;
					case SB_PAGEDOWN:
						Info.nPos += 100;
						break;
					case SB_THUMBPOSITION:
						Info.nPos = nPos;
						break;
					case SB_THUMBTRACK:
						Info.nPos = nPos;
						break;
					default:
						return;
				}
				SetScrollInfo(m_hwnd, SB_VERT, &Info, 1);
				RedrawWindow(m_hwnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
			}
			break;
	}
}
