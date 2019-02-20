#pragma once
#include "..\stklib\OfficeManagerASE.h"
#include "NetAseEx.h"

class NetManagerAseEx : public OfficeManagerASE  
{
public:
	NetManagerAseEx();
	virtual void ManagerAction(ActorStatusElement**, int*, GameStatus*);
	virtual void PopupMenuAction(int, int, int, ActorStatusElement**, int*);
	virtual void PopupMenuInit(HMENU, ActorStatusElement**, int*);
};
