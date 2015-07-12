#pragma once

#include <windows.h>
#include <tchar.h>
#include "GameStatusElement.h"

class GameStatus  
{
private:
	static const int GAME_STATUS_COUNT = 100;

	// Message constants
	static const TCHAR* MSG_TITLE;
	static const TCHAR* MSG_NO_WORK_SCREEN;
	static const TCHAR* MSG_WORK_SCREEN_EXIST;
	static const TCHAR* MSG_INCORRECT_STATUS;
	static const TCHAR* MSG_START_FAILED;
	static const TCHAR* MSG_STOP_FAILED;
	static const TCHAR* MSG_NO_HWND;

	// Current game status ID
	static int m_gameStatus;

	static GameStatusElement *m_gse[GAME_STATUS_COUNT];

	UINT_PTR m_timerId;

	// system handler
	static HWND m_hwnd;
	static HINSTANCE m_hinst;
	static HDC m_hdc;

	// If this flag is TRUE, window frame and scroll bar will be updated.
	BOOL DrawScreenExFlag;

	static LRESULT CALLBACK RefreshScreen(HWND hwnd, UINT uMsg, UINT idEvent, DWORD dwTime);
	void DrawScreen();
	void ChangeWindow();
	void SetMinMaxWindowSize(LPARAM);
	void ResetScrollBarInfo();

	// Critical Section Definition
	CRITICAL_SECTION CritSect;

public:
	// Constructer and destructer
	GameStatus();
	virtual ~GameStatus();

	void SetDrawScreenExFlag();

	// Creating reverse screen
	void CreateReverseScreen(int, int);

	// Functions for getting/setting handlers
	HWND GetHWnd();
	void SetHWnd(HWND);
	HINSTANCE GetHInstance();
	void SetHInstance(HINSTANCE);

	// Operation for game status ID
	void ChangeGameStatus(int);
	int GetGameStatus();
	void SetGameStatus(int);

	// Start and stop of the timer
	void StartRefreshScreen();
	void StopRefreshScreen();

	// Operation for GameStatusElement
	void AddGameStatusElement(int, GameStatusElement*);
	void DeleteGameStatusElement(int);
	GameStatusElement* GetGameStatusElement(int);

	// Conversion from client coordination
	int ChangeClientToWorldX(int);
	int ChangeClientToWorldY(int);
	int ChangeClientToWindowX(int, BOOL);
	int ChangeClientToWindowY(int, BOOL);

	// WM message dispatcher
	void MessageDispatcher(HWND, UINT, WPARAM, LPARAM);
};
