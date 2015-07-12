#pragma once

#include <windows.h>
#include "GameStatus.h"
#include "ActorStatusElement.h"

class OfficeManagerASE : public ActorStatusElement  
{
protected:
	// Selected area by mouse operation
	int m_StartPtX;
	int m_StartPtY;
	int m_EndPtX;
	int m_EndPtY;

	// Area operation
	void MoveWithSelectedMany(ActorStatusElement**, int, GameStatus* gs, int, int, int);
	void OnlyOneElementWasSpecified(ActorStatusElement**, int, int);
	void SomeElementsWereSpecified(ActorStatusElement**, int);

public:
	static const int ACTOR_ID = 0;

	// Grid type (1:N/S, 8:8X8, 16:16X16)
	static int GridType;

	OfficeManagerASE();
	virtual ~OfficeManagerASE();

	// Action functions
	virtual void Action(ActorStatusElement**, int*, GameStatus*);
	virtual void ManagerAction(ActorStatusElement**, int*, GameStatus*);
	virtual void PopupMenuAction(int, int, int, ActorStatusElement**, int*);
	virtual void PopupMenuInit(HMENU, ActorStatusElement**, int*);
	virtual BOOL MouseAction(GameStatus*, int, int, int, ActorStatusElement**, int*);
};
