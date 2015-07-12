#pragma once

#include <windows.h>
#include "GameStatus.h"
#include "ActorStatusElement.h"

class OfficeASE : public ActorStatusElement
{
protected:
	// Type of previous mouse action
	int m_PreviousMouseActionType;

	// For selection control
	int m_Selection;
	int m_ClearSelection;

	// Distance of moving
	int m_dx;
	int m_dy;

	// Flag for clearing manager specified area
	BOOL m_ClearMgrAreaOpFlag;

public:
	// Type of previous mouse action
	static const int PMA_TYPE_NOTSPECIAL  = 0;
	static const int PMA_TYPE_LBUTTONDOWN = 1;
	static const int PMA_TYPE_MOVELDOWN   = 2;

	// Type of selection
	static const int SELECTED_NONE       = 0;
	static const int SELECTED_ONE        = 1;
	static const int SELECTED_MANY       = 2;
	static const int SELECTED_CHANGEONE  = 11;
	static const int SELECTED_CHANGEMANY = 12;

	// Constructer and destructer
	OfficeASE();
	virtual ~OfficeASE();

	// Action functions
	virtual void Action(ActorStatusElement**, int*, GameStatus*);
	virtual void PopupMenuInit(HMENU, ActorStatusElement**, int*);
	virtual void PopupMenuAction(int, int, int, ActorStatusElement**, int*);
	virtual void DoubleClickAction();
	virtual BOOL MouseAction(GameStatus*, int, int, int, ActorStatusElement**, int*);

	// Functions for getting/setting selection
	int GetSelection();
	void SetSelection(int);

	// Functions for getting/setting moving distance 
	int GetMoveDistanceX(void);
	int GetMoveDistanceY(void);
	void SetMoveDistance(int, int);

	// Operation for clearing manager specified area
	BOOL GetClearMgrAreaOpFlag(void);
	void SetClearMgrAreaOpFlag(BOOL);
};
