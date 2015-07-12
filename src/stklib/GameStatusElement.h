#pragma once

#include "ActorRequest.h"

class GameStatusElement  
{
protected:
	static const int GAME_STATUS_ELEMENT_REFRESH_SCREEN_INTERVAL = 200;
	static const int GAME_STATUS_ELEMENT_REQUEST = 10000;

	long m_refreshScreenInterval;

	// Window size
	int m_CurWinSizeX, m_CurWinSizeY;
	int m_MaxWinSizeX, m_MaxWinSizeY;
	int m_MinWinSizeX, m_MinWinSizeY;

	// Reverse screen area
	int m_ActiveRSRight;
	int m_ActiveRSLeft;
	int m_ActiveRSTop;
	int m_ActiveRSBottom;

	// Whether activate scroll bar or not
	BOOL m_ScrollBar;

	// ActorRequest queue
	ActorRequest* m_ActReq[GAME_STATUS_ELEMENT_REQUEST];
	int m_CurrentRequest;

public:
	GameStatusElement();
	virtual ~GameStatusElement();

	void SetRefreshInterval(long);
	long GetRefreshInterval();

	void SetCurrentWindowSize(int, int);
	int GetCurrentWindowSizeX();
	int GetCurrentWindowSizeY();

	void SetMaxWindowSize(int, int);
	int GetMaxWindowSizeX();
	int GetMaxWindowSizeY();

	void SetMinWindowSize(int, int);
	int GetMinWindowSizeX();
	int GetMinWindowSizeY();

	// Operation for reverse screen
	void SetActiveReverseScreen(int, int, int, int);
	int GetActiveReverseScreenRight();
	int GetActiveReverseScreenLeft();
	int GetActiveReverseScreenTop();
	int GetActiveReverseScreenBottom();

	void EnableScrollBar();
	void DisableScrollBar();
	BOOL GetScrollBarFlag();

	void AddRequest(int, int, int, LPTSTR, LPTSTR, int, int, int, int);
	void ClearRequest();

	virtual void RefreshScreenProcess(HINSTANCE, HWND, HDC);
};
