#pragma once

#include <windows.h>
#include "GameStatus.h"
#include "ActorStatusElement.h"

class ActorStatus  
{
public:
	static const int ACTOR_STATUS_COUNT = 1000;

private:
	// Message constants
	static const TCHAR* MSG_TITLE;
	static const TCHAR* MSG_START_FAILED;
	static const TCHAR* MSG_STOP_FAILED;
	static const TCHAR* MSG_NO_HWND;
	static const TCHAR* MSG_NO_GS;

	// Critical Section Definition
	CRITICAL_SECTION CritSect;

	int m_actorActionInterval;
	UINT_PTR m_timerId;
	static ActorStatusElement *m_ase[ACTOR_STATUS_COUNT];
	static int m_ActorStatusElementCount;
	static GameStatus *m_gs;

	static LRESULT CALLBACK ActorAction(HWND hwnd, UINT uMsg, UINT idEvent, DWORD dwTime);
	void MouseAction(int, int, int);

public:
	// Mouse action type
	static const int LBUTTONUP       = 10;
	static const int LBUTTONUP_S     = 11;
	static const int LBUTTONDOWN     = 12;
	static const int LBUTTONDOWN_S   = 13;
	static const int LBUTTONDBLCLK   = 14;
	static const int RBUTTONUP       = 20;
	static const int RBUTTONUP_S     = 21;
	static const int RBUTTONDOWN     = 22;
	static const int RBUTTONDOWN_S   = 23;
	static const int RBUTTONDBLCLK   = 24;
	static const int MOVE            = 100;
	static const int MOVELDOWN       = 111;
	static const int MOVERDOWN       = 121;

	ActorStatus();
	virtual ~ActorStatus();

	void AddActorStatusElement(ActorStatusElement*);
	ActorStatusElement* GetActorStatusElement(int);
	int GetActorStatusElementCount();
	void ClearActorStatusElement();

	int GetActorActionInterval();
	void SetActorActionInterval(int actorActionInterval);

	void StartActorAction();
	void StopActorAction();

	void SetGameStatus(GameStatus*);
	GameStatus* GetGameStatus();

	// WM message dispatcher
	void MessageDispatcher(HWND, UINT, WPARAM, LPARAM);
};
