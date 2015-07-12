// gamestatuselement.cpp: GameStatusElement �N���X�̃C���v�������e�[�V����
//
//////////////////////////////////////////////////////////////////////

#include "windows.h"
#include "GameStatusElement.h"


//////////////////////////////////////////////////////////////////////
// �\�z/����
//////////////////////////////////////////////////////////////////////

GameStatusElement::GameStatusElement()
{
	m_refreshScreenInterval = GAME_STATUS_ELEMENT_REFRESH_SCREEN_INTERVAL;

	// ���݂̃E�B���h�E�T�C�Y�̏�����
	m_CurWinSizeX = m_CurWinSizeY = 0;

	// �ŏ��^�ő�E�B���h�E�T�C�Y�̏������i�������j
	m_MaxWinSizeX = m_MaxWinSizeY = m_MinWinSizeX = m_MinWinSizeY = -1;

	// ����ʂ̓��I�̈�
	m_ActiveRSRight = m_ActiveRSLeft = m_ActiveRSTop = m_ActiveRSBottom = -1;

	// GameStatusElement�ւ̗v���̌��݈ʒu�̏�����
	m_CurrentRequest = 0;

	// �X�N���[���o�[�𖳌��ɂ���
	m_ScrollBar = FALSE;
}

GameStatusElement::~GameStatusElement()
{

}

//////////////////////////////////////////////////////////////////////
// ���̑����
//////////////////////////////////////////////////////////////////////

// RefreshScreen�Ԋu�̐ݒ�
void GameStatusElement::SetRefreshInterval(long refreshScreenInterval)
{
	m_refreshScreenInterval = refreshScreenInterval;
}

// RefreshScreen�Ԋu�̎擾
long GameStatusElement::GetRefreshInterval()
{
	return m_refreshScreenInterval;
}

// RefreshScreen����Ăяo�����֐�
void GameStatusElement::RefreshScreenProcess(HINSTANCE hinst, HWND hwnd, HDC hdc)
{
}

// ���݂̃E�B���h�E�T�C�Y�̐ݒ�
void GameStatusElement::SetCurrentWindowSize(int x, int y)
{
	m_CurWinSizeX = x;
	m_CurWinSizeY = y;
}

// ���݂̃E�B���h�E���T�C�Y�̎擾
int GameStatusElement::GetCurrentWindowSizeX()
{
	return m_CurWinSizeX;
}

// ���݂̃E�B���h�E�c�T�C�Y�̎擾
int GameStatusElement::GetCurrentWindowSizeY()
{
	return m_CurWinSizeY;
}

// �ő�E�B���h�E�T�C�Y�̐ݒ�
void GameStatusElement::SetMaxWindowSize(int x, int y)
{
	m_MaxWinSizeX = x;
	m_MaxWinSizeY = y;
}

// �ő�E�B���h�E���T�C�Y�̎擾
int GameStatusElement::GetMaxWindowSizeX()
{
	return m_MaxWinSizeX;
}

// �ő�E�B���h�E�c�T�C�Y�̎擾
int GameStatusElement::GetMaxWindowSizeY()
{
	return m_MaxWinSizeY;
}

// �ŏ��E�B���h�E�T�C�Y�̐ݒ�
void GameStatusElement::SetMinWindowSize(int x, int y)
{
	m_MinWinSizeX = x;
	m_MinWinSizeY = y;
}

// �ŏ��E�B���h�E���T�C�Y�̎擾
int GameStatusElement::GetMinWindowSizeX()
{
	return m_MinWinSizeX;
}

// �ŏ��E�B���h�E�c�T�C�Y�̎擾
int GameStatusElement::GetMinWindowSizeY()
{
	return m_MinWinSizeY;
}

// ����ʂ̓��I�̈�̐ݒ�
void GameStatusElement::SetActiveReverseScreen(int left, int top, int right, int bottom)
{
	m_ActiveRSRight = right;
	m_ActiveRSLeft = left;
	m_ActiveRSTop = top;
	m_ActiveRSBottom = bottom;
}

// ����ʂ̓��I�̈�E���W�擾
int GameStatusElement::GetActiveReverseScreenRight()
{
	return m_ActiveRSRight;
}

// ����ʂ̓��I�̈捶���W�擾
int GameStatusElement::GetActiveReverseScreenLeft()
{
	return m_ActiveRSLeft;
}

// ����ʂ̓��I�̈����W�擾
int GameStatusElement::GetActiveReverseScreenTop()
{
	return m_ActiveRSTop;
}

// ����ʂ̓��I�̈扺���W�擾
int GameStatusElement::GetActiveReverseScreenBottom()
{
	return m_ActiveRSBottom;
}

// �X�N���[���o�[��L���ɂ���
void GameStatusElement::EnableScrollBar()
{
	m_ScrollBar = TRUE;
}

// �X�N���[���o�[�𖳌��ɂ���
void GameStatusElement::DisableScrollBar()
{
	m_ScrollBar = FALSE;
}

// �X�N���[���o�[�L���^�����t���O���擾����
BOOL GameStatusElement::GetScrollBarFlag()
{
	return m_ScrollBar;
}

// GameStatusElement�ւ̗v���̒ǉ�
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

// GameStatusElement�ւ̗v���̍폜
void GameStatusElement::ClearRequest()
{
	int ReqLoop;
	for (ReqLoop = 0; ReqLoop < m_CurrentRequest; ReqLoop++) {
		delete m_ActReq[ReqLoop];
	}
	m_CurrentRequest = 0;
}
