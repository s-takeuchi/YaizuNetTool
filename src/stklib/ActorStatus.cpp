// ActorStatus.cpp: ActorStatus �N���X�̃C���v�������e�[�V����
//
//////////////////////////////////////////////////////////////////////

#include <windows.h>
#include <tchar.h>
#include "GameStatus.h"
#include "ActorStatus.h"
#include "ActorStatusElement.h"
#include "ActorRequest.h"

// Definition of message constants
const TCHAR* ActorStatus::MSG_TITLE        = _T("StkLib error");
const TCHAR* ActorStatus::MSG_START_FAILED = _T("Action process start has failed.");
const TCHAR* ActorStatus::MSG_STOP_FAILED  = _T("Action process stop has failed.");
const TCHAR* ActorStatus::MSG_NO_HWND      = _T("No HWND is set to the ActorStatus instance.");
const TCHAR* ActorStatus::MSG_NO_GS        = _T("No GameStatus is set to the ActorStatus instance.");

// �L�����N�^�����삷�鎞�ԊԊu�̏����l
#define ACTOR_STATUS_INIT_INTERVAL 100

// �^�C�}�[ID�̏����l
#define ACTOR_STATUS_TIMER_ID_INIT 0
#define ACTOR_STATUS_TIMER_ID 102

ActorStatusElement* ActorStatus::m_ase[ActorStatus::ACTOR_STATUS_COUNT]; // �L�����N�^�̏�Ԗ��̏���
GameStatus* ActorStatus::m_gs; // GameStatus�C���X�^���X�ւ̃|�C���^
int ActorStatus::m_ActorStatusElementCount; // �L�����N�^�̏�Ԗ��̏����̐�

//////////////////////////////////////////////////////////////////////
// �\�z/����
//////////////////////////////////////////////////////////////////////

ActorStatus::ActorStatus()
{
	m_gs = NULL;
	m_actorActionInterval = ACTOR_STATUS_INIT_INTERVAL;
	m_timerId = ACTOR_STATUS_TIMER_ID_INIT;
	m_ActorStatusElementCount = 0;
	InitializeCriticalSection(&CritSect);
}

ActorStatus::~ActorStatus()
{

}

//////////////////////////////////////////////////////////////////////
// ���̑����
//////////////////////////////////////////////////////////////////////

// �L�����N�^�̓�����J�n����
void ActorStatus::StartActorAction()
{
	EnterCriticalSection(&CritSect);
	// Check whether the actor has already been worked.
	if (m_timerId != ACTOR_STATUS_TIMER_ID_INIT) {
		MessageBox(NULL,
					MSG_START_FAILED,
					MSG_TITLE,
					MB_OK | MB_ICONEXCLAMATION | MB_SYSTEMMODAL);
		ExitProcess(-1);
	}

	// Check whether GameStatus is set or not.
	if (m_gs == NULL) {
		MessageBox(NULL,
					MSG_NO_GS,
					MSG_TITLE,
					MB_OK | MB_ICONEXCLAMATION | MB_SYSTEMMODAL);
		ExitProcess(-1);
	}

	// Check whether HWND is set into GameStatus or not.
	if (m_gs->GetHWnd() == NULL) {
		MessageBox(NULL,
					MSG_NO_HWND,
					MSG_TITLE,
					MB_OK | MB_ICONEXCLAMATION | MB_SYSTEMMODAL);
		ExitProcess(-1);
	}

	// ����I��RefreshScreen�̌Ăяo�����J�n
	m_timerId = SetTimer(m_gs->GetHWnd(), ACTOR_STATUS_TIMER_ID, m_actorActionInterval, (TIMERPROC)ActorStatus::ActorAction);
	if (m_timerId == 0) {
		MessageBox(NULL,
					MSG_START_FAILED,
					MSG_TITLE,
					MB_OK | MB_ICONEXCLAMATION | MB_SYSTEMMODAL);
		ExitProcess(-1);
	}
	LeaveCriticalSection(&CritSect);
}

// �L�����N�^�̓�����~����
void ActorStatus::StopActorAction()
{
	EnterCriticalSection(&CritSect);
	// ���ɃL�����N�^�̓��삪��~���Ă���
	if (m_timerId == ACTOR_STATUS_TIMER_ID_INIT) {
		MessageBox(NULL,
					MSG_STOP_FAILED,
					MSG_TITLE,
					MB_OK | MB_ICONEXCLAMATION | MB_SYSTEMMODAL);
		ExitProcess(-1);
	}

	BOOL res = KillTimer(m_gs->GetHWnd(), m_timerId);

	// �ΏۂƂȂ�^�C�}�[�C�x���g�����݂��Ȃ�
	if (res == 0) {
		MessageBox(NULL,
					MSG_STOP_FAILED,
					MSG_TITLE,
					MB_OK | MB_ICONEXCLAMATION | MB_SYSTEMMODAL);
		ExitProcess(-1);
	}

	m_timerId = ACTOR_STATUS_TIMER_ID_INIT; // �^�C�}�[ID�̏�����
	LeaveCriticalSection(&CritSect);
}

// �L�����N�^�̓���
LRESULT CALLBACK ActorStatus::ActorAction(HWND hwnd, UINT uMsg, UINT idEvent, DWORD dwTime)
{
	for (int i = 0; i < m_ActorStatusElementCount; i++) {
		if (m_ase[i] != NULL) {
			if (m_ase[i]->GetActionFlag()) {
				m_ase[i]->Action(m_ase, &m_ActorStatusElementCount, m_gs);
			}
		}
	}
	ActorRequest::SynchroFlag = TRUE;
	return TRUE;
}

void ActorStatus::MouseAction(int xx, int yy, int type)
{
	BOOL RetCode = FALSE;
	int x = m_gs->ChangeClientToWorldX(xx);
	int y = m_gs->ChangeClientToWorldY(yy);
	for (int i = m_ActorStatusElementCount - 1; i >= 0 ; i--) {
		if (m_ase[i] != NULL) {
			if (m_ase[i]->GetMouseActionFlag() == FALSE) {
				continue;
			}
			if ((m_ase[i]->GetActorPosY() + m_ase[i]->GetActorRectBottom()) > y &&
				(m_ase[i]->GetActorPosY() + m_ase[i]->GetActorRectTop()) < y &&
				(m_ase[i]->GetActorPosX() + m_ase[i]->GetActorRectRight()) > x &&
				(m_ase[i]->GetActorPosX() + m_ase[i]->GetActorRectLeft()) < x) {
				RetCode = m_ase[i]->MouseAction(m_gs, x, y, type, m_ase, &m_ActorStatusElementCount);
			} else if (type == ActorStatus::MOVELDOWN || type == ActorStatus::MOVERDOWN) {
				RetCode = m_ase[i]->MouseAction(m_gs, x, y, type, m_ase, &m_ActorStatusElementCount);
			}
			if (RetCode == TRUE) {
				break;
			}
		}
	}
}

// �L�����N�^�̏�ԂɑΉ����������̒ǉ�
void ActorStatus::AddActorStatusElement(ActorStatusElement *ase)
{
	EnterCriticalSection(&CritSect);
	m_ase[m_ActorStatusElementCount] = ase;
	m_ActorStatusElementCount++;
	LeaveCriticalSection(&CritSect);
}

ActorStatusElement* ActorStatus::GetActorStatusElement(int Idx)
{
	return m_ase[Idx];
}

int ActorStatus::GetActorStatusElementCount()
{
	return m_ActorStatusElementCount;
}

 // �L�����N�^�̏�ԂɑΉ����������̍폜
void ActorStatus::ClearActorStatusElement()
{
	EnterCriticalSection(&CritSect);
	for (int Loop = 0; Loop < m_ActorStatusElementCount; Loop++) {
		delete m_ase[Loop];
	}
	m_ActorStatusElementCount = 0;
	LeaveCriticalSection(&CritSect);
}

// �L�����N�^�����삷�鎞�ԊԊu�̎擾
int ActorStatus::GetActorActionInterval()
{
	return m_actorActionInterval;
}

// �L�����N�^�����삷�鎞�ԊԊu�̐ݒ�
void ActorStatus::SetActorActionInterval(int actorActionInterval)
{
	m_actorActionInterval = actorActionInterval;
}

// GameStatus�̐ݒ�
void ActorStatus::SetGameStatus(GameStatus* gs)
{
	m_gs = gs;
}

// GameStatus�̎擾
GameStatus* ActorStatus::GetGameStatus()
{
	return m_gs;
}

// WM Message dispatcher
void ActorStatus::MessageDispatcher(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (m_gs != NULL) {
		if (m_gs->GetHWnd() == NULL) {
			return;
		}
	} else {
		return;
	}

	switch(message) {
		case WM_CREATE:
			break;
		case WM_PAINT:
			break;
		case WM_GETMINMAXINFO:
			break;
		case WM_SIZE:
			break;
		case WM_LBUTTONDBLCLK:
			MouseAction((int)LOWORD(lParam), (int)HIWORD(lParam), ActorStatus::LBUTTONDBLCLK);
			break;
		case WM_LBUTTONDOWN:
			if ((wParam & MK_SHIFT) == MK_SHIFT) {
				MouseAction((int)LOWORD(lParam), (int)HIWORD(lParam), ActorStatus::LBUTTONDOWN_S); 
			} else {
				MouseAction((int)LOWORD(lParam), (int)HIWORD(lParam), ActorStatus::LBUTTONDOWN); 
			}
			break;
		case WM_LBUTTONUP:
			if ((wParam & MK_SHIFT) == MK_SHIFT) {
				MouseAction((int)LOWORD(lParam), (int)HIWORD(lParam), ActorStatus::LBUTTONUP_S); 
			} else {
				MouseAction((int)LOWORD(lParam), (int)HIWORD(lParam), ActorStatus::LBUTTONUP);
			}
			break;
		case WM_RBUTTONDBLCLK:
			MouseAction((int)LOWORD(lParam), (int)HIWORD(lParam), ActorStatus::RBUTTONDBLCLK);
			break;
		case WM_RBUTTONDOWN:
			if ((wParam & MK_SHIFT) == MK_SHIFT) {
				MouseAction((int)LOWORD(lParam), (int)HIWORD(lParam), ActorStatus::RBUTTONDOWN_S); 
			} else {
				MouseAction((int)LOWORD(lParam), (int)HIWORD(lParam), ActorStatus::RBUTTONDOWN); 
			}
			break;
		case WM_RBUTTONUP:
			if ((wParam & MK_SHIFT) == MK_SHIFT) {
				MouseAction((int)LOWORD(lParam), (int)HIWORD(lParam), ActorStatus::RBUTTONUP_S);
			} else {
				MouseAction((int)LOWORD(lParam), (int)HIWORD(lParam), ActorStatus::RBUTTONUP);
			}
			break;
		case WM_MOUSEMOVE:
			if ((wParam & MK_LBUTTON) == MK_LBUTTON) {
				MouseAction((int)LOWORD(lParam), (int)HIWORD(lParam), ActorStatus::MOVELDOWN);
				break;
			}
			if ((wParam & MK_RBUTTON) == MK_RBUTTON) {
				MouseAction((int)LOWORD(lParam), (int)HIWORD(lParam), ActorStatus::MOVERDOWN);
				break;
			}
			MouseAction((int)LOWORD(lParam), (int)HIWORD(lParam), ActorStatus::MOVE); 
			break;
	}
}
