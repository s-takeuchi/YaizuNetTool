// ActorStatusElement.cpp: ActorStatusElement クラスのインプリメンテーション
//
//////////////////////////////////////////////////////////////////////

#include <windows.h>
#include "GameStatus.h"
#include "ActorStatusElement.h"

//////////////////////////////////////////////////////////////////////
// 構築/消滅
//////////////////////////////////////////////////////////////////////

ActorStatusElement::ActorStatusElement()
{
	m_Id = -1;
	m_x = 0;
	m_y = 0;
	m_bottom = m_top = m_left = m_right = 0;
	m_Action = TRUE;
	m_MouseAction = TRUE;
}

ActorStatusElement::~ActorStatusElement()
{

}

//////////////////////////////////////////////////////////////////////
// その他一般
//////////////////////////////////////////////////////////////////////

void ActorStatusElement::SetId(int Id)
{
	m_Id = Id;
}

int ActorStatusElement::GetId(void)
{
	return m_Id;
}

void ActorStatusElement::EnableAction()
{
	m_Action = TRUE;
}

void ActorStatusElement::DisableAction()
{
	m_Action = FALSE;
}

BOOL ActorStatusElement::GetActionFlag()
{
	return m_Action;
}

void ActorStatusElement::EnableMouseAction()
{
	m_MouseAction = TRUE;
}

void ActorStatusElement::DisableMouseAction()
{
	m_MouseAction = FALSE;
}

BOOL ActorStatusElement::GetMouseActionFlag()
{
	return m_MouseAction;
}

void ActorStatusElement::SetActorPos(int x, int y)
{
	m_x = x;
	m_y = y;
}

int ActorStatusElement::GetActorPosX()
{
	return m_x;
}

int ActorStatusElement::GetActorPosY()
{
	return m_y;
}

void ActorStatusElement::SetActorRect(int bottom, int top, int right, int left)
{
	m_bottom = bottom;
	m_top = top;
	m_right = right;
	m_left = left;
}

int ActorStatusElement::GetActorRectBottom()
{
	return m_bottom;
}

int ActorStatusElement::GetActorRectTop()
{
	return m_top;
}

int ActorStatusElement::GetActorRectRight()
{
	return m_right;
}

int ActorStatusElement::GetActorRectLeft()
{
	return m_left;
}

// Action of the actor
void ActorStatusElement::Action(ActorStatusElement* ase[], int* ElementCount, GameStatus* gs)
{
}

// Mouse action of the actor
BOOL ActorStatusElement::MouseAction(GameStatus* gs, int x, int y, int type, ActorStatusElement* ase[], int* ElementCount)
{
	return FALSE;
}
