#pragma once

#include "GameStatus.h"

class ActorStatusElement  
{
protected:
	// ActorElement's identifier
	int m_Id;

	// Position of the actor
	int m_x;
	int m_y;

	// Area of the actor
	int m_bottom;
	int m_top;
	int m_right;
	int m_left;

	// Enable the timer action
	BOOL m_Action;

	// Enable the action when mouse button was clicked
	BOOL m_MouseAction;

public:
	ActorStatusElement();
	virtual ~ActorStatusElement();

	void SetId(int);
	int GetId();

	void EnableAction();
	void DisableAction();
	BOOL GetActionFlag();

	void EnableMouseAction();
	void DisableMouseAction();
	BOOL GetMouseActionFlag();

	void SetActorPos(int, int);
	int GetActorPosX();
	int GetActorPosY();

	void SetActorRect(int, int, int, int);
	int GetActorRectBottom();
	int GetActorRectTop();
	int GetActorRectRight();
	int GetActorRectLeft();

	virtual void Action(ActorStatusElement**, int*, GameStatus*);
	virtual BOOL MouseAction(GameStatus*, int, int, int, ActorStatusElement**, int*);
};
