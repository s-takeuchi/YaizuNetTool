// gamestatuselement.cpp: GameStatusElement クラスのインプリメンテーション
//
//////////////////////////////////////////////////////////////////////

#include "windows.h"
#include "GameStatusElement.h"


//////////////////////////////////////////////////////////////////////
// 構築/消滅
//////////////////////////////////////////////////////////////////////

GameStatusElement::GameStatusElement()
{
	m_refreshScreenInterval = GAME_STATUS_ELEMENT_REFRESH_SCREEN_INTERVAL;

	// 現在のウィンドウサイズの初期化
	m_CurWinSizeX = m_CurWinSizeY = 0;

	// 最小／最大ウィンドウサイズの初期化（無制限）
	m_MaxWinSizeX = m_MaxWinSizeY = m_MinWinSizeX = m_MinWinSizeY = -1;

	// 裏画面の動的領域
	m_ActiveRSRight = m_ActiveRSLeft = m_ActiveRSTop = m_ActiveRSBottom = -1;

	// GameStatusElementへの要求の現在位置の初期化
	m_CurrentRequest = 0;

	// スクロールバーを無効にする
	m_ScrollBar = FALSE;
}

GameStatusElement::~GameStatusElement()
{

}

//////////////////////////////////////////////////////////////////////
// その他一般
//////////////////////////////////////////////////////////////////////

// RefreshScreen間隔の設定
void GameStatusElement::SetRefreshInterval(long refreshScreenInterval)
{
	m_refreshScreenInterval = refreshScreenInterval;
}

// RefreshScreen間隔の取得
long GameStatusElement::GetRefreshInterval()
{
	return m_refreshScreenInterval;
}

// RefreshScreenから呼び出される関数
void GameStatusElement::RefreshScreenProcess(HINSTANCE hinst, HWND hwnd, HDC hdc)
{
}

// 現在のウィンドウサイズの設定
void GameStatusElement::SetCurrentWindowSize(int x, int y)
{
	m_CurWinSizeX = x;
	m_CurWinSizeY = y;
}

// 現在のウィンドウ横サイズの取得
int GameStatusElement::GetCurrentWindowSizeX()
{
	return m_CurWinSizeX;
}

// 現在のウィンドウ縦サイズの取得
int GameStatusElement::GetCurrentWindowSizeY()
{
	return m_CurWinSizeY;
}

// 最大ウィンドウサイズの設定
void GameStatusElement::SetMaxWindowSize(int x, int y)
{
	m_MaxWinSizeX = x;
	m_MaxWinSizeY = y;
}

// 最大ウィンドウ横サイズの取得
int GameStatusElement::GetMaxWindowSizeX()
{
	return m_MaxWinSizeX;
}

// 最大ウィンドウ縦サイズの取得
int GameStatusElement::GetMaxWindowSizeY()
{
	return m_MaxWinSizeY;
}

// 最小ウィンドウサイズの設定
void GameStatusElement::SetMinWindowSize(int x, int y)
{
	m_MinWinSizeX = x;
	m_MinWinSizeY = y;
}

// 最小ウィンドウ横サイズの取得
int GameStatusElement::GetMinWindowSizeX()
{
	return m_MinWinSizeX;
}

// 最小ウィンドウ縦サイズの取得
int GameStatusElement::GetMinWindowSizeY()
{
	return m_MinWinSizeY;
}

// 裏画面の動的領域の設定
void GameStatusElement::SetActiveReverseScreen(int left, int top, int right, int bottom)
{
	m_ActiveRSRight = right;
	m_ActiveRSLeft = left;
	m_ActiveRSTop = top;
	m_ActiveRSBottom = bottom;
}

// 裏画面の動的領域右座標取得
int GameStatusElement::GetActiveReverseScreenRight()
{
	return m_ActiveRSRight;
}

// 裏画面の動的領域左座標取得
int GameStatusElement::GetActiveReverseScreenLeft()
{
	return m_ActiveRSLeft;
}

// 裏画面の動的領域上座標取得
int GameStatusElement::GetActiveReverseScreenTop()
{
	return m_ActiveRSTop;
}

// 裏画面の動的領域下座標取得
int GameStatusElement::GetActiveReverseScreenBottom()
{
	return m_ActiveRSBottom;
}

// スクロールバーを有効にする
void GameStatusElement::EnableScrollBar()
{
	m_ScrollBar = TRUE;
}

// スクロールバーを無効にする
void GameStatusElement::DisableScrollBar()
{
	m_ScrollBar = FALSE;
}

// スクロールバー有効／無効フラグを取得する
BOOL GameStatusElement::GetScrollBarFlag()
{
	return m_ScrollBar;
}

// GameStatusElementへの要求の追加
void GameStatusElement::AddRequest(int Req, int ActorId, int ReqType, LPTSTR StrParam1, LPTSTR StrParam2, int IntParam1, int IntParam2, int IntParam3, int IntParam4)
{
	BOOL FoundFlag = FALSE;
	int ReqLoop;
	ActorRequest* ActReq;

	if (m_CurrentRequest >= GAME_STATUS_ELEMENT_REQUEST) {
		return;
	}

	if (ReqType == ActorRequest::SYNCHRO) {
		if (ActorRequest::SynchroFlag == TRUE) {
			return;
		}
	} else
	if (ReqType == ActorRequest::IGNORE_SAME_REQ_SAME_ACTOR) {
		for (ReqLoop = 0; ReqLoop < m_CurrentRequest; ReqLoop++) {
			if (m_ActReq[ReqLoop]->GetRequest() == Req &&
				m_ActReq[ReqLoop]->GetActorId() == ActorId) {
					FoundFlag = TRUE;
					break;
			}
		}
	} else
	if (ReqType == ActorRequest::IGNORE_SAME_REQ) {
		for (ReqLoop = 0; ReqLoop < m_CurrentRequest; ReqLoop++) {
			if (m_ActReq[ReqLoop]->GetRequest() == Req) {
					FoundFlag = TRUE;
					break;
			}
		}
	} else
	if (ReqType == ActorRequest::IGNORE_SAME_REQ_SAME_ACTOR) {
		for (ReqLoop = 0; ReqLoop < m_CurrentRequest; ReqLoop++) {
			if (m_ActReq[ReqLoop]->GetActorId() == ActorId) {
					FoundFlag = TRUE;
					break;
			}
		}
	} else
	if (ReqType == ActorRequest::OVERWRITE_SAME_REQ_SAME_ACTOR) {
		for (ReqLoop = 0; ReqLoop < m_CurrentRequest; ReqLoop++) {
			if (m_ActReq[ReqLoop]->GetRequest() == Req &&
				m_ActReq[ReqLoop]->GetActorId() == ActorId) {
					FoundFlag = TRUE;
					delete m_ActReq[ReqLoop];
					ActReq = new ActorRequest(Req, ActorId, ReqType, StrParam1, StrParam2, IntParam1, IntParam2, IntParam3, IntParam4);
					m_ActReq[ReqLoop] = ActReq;
			}
		}
	} else
	if (ReqType == ActorRequest::OVERWRITE_SAME_REQ) {
		for (ReqLoop = 0; ReqLoop < m_CurrentRequest; ReqLoop++) {
			if (m_ActReq[ReqLoop]->GetRequest() == Req) {
					FoundFlag = TRUE;
					delete m_ActReq[ReqLoop];
					ActReq = new ActorRequest(Req, ActorId, ReqType, StrParam1, StrParam2, IntParam1, IntParam2, IntParam3, IntParam4);
					m_ActReq[ReqLoop] = ActReq;
			}
		}
	} else
	if (ReqType == ActorRequest::OVERWRITE_SAME_ACTOR) {
		for (ReqLoop = 0; ReqLoop < m_CurrentRequest; ReqLoop++) {
			if (m_ActReq[ReqLoop]->GetActorId() == ActorId) {
					FoundFlag = TRUE;
					delete m_ActReq[ReqLoop];
					ActReq = new ActorRequest(Req, ActorId, ReqType, StrParam1, StrParam2, IntParam1, IntParam2, IntParam3, IntParam4);
					m_ActReq[ReqLoop] = ActReq;
			}
		}
	}
	if (FoundFlag == TRUE) {
		return;
	}
	ActReq = new ActorRequest(Req, ActorId, ReqType, StrParam1, StrParam2, IntParam1, IntParam2, IntParam3, IntParam4);
	m_ActReq[m_CurrentRequest] = ActReq;
	m_CurrentRequest++;
}

// GameStatusElementへの要求の削除
void GameStatusElement::ClearRequest()
{
	int ReqLoop;
	for (ReqLoop = 0; ReqLoop < m_CurrentRequest; ReqLoop++) {
		delete m_ActReq[ReqLoop];
	}
	m_CurrentRequest = 0;
}
