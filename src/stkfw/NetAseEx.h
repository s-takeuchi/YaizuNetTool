#pragma once
#include "..\stklib\OfficeASE.h"

class NetAseEx : public OfficeASE  
{
protected:
	int m_Type;
	int m_Icon;
	TCHAR m_Name[32];

public:
	// Link information
	int LinkTo[10];
	int LinkType[10];
	int LinkCount;

	// Class for link condition
	class LinkCondition
	{
	public:
		int LinkFrom;
		int LinkTo;
		int LinkCount;
		int LinkType;
	} LinkCond[500];
	int LinkCondCount;

	NetAseEx();
	virtual ~NetAseEx();

	int GetType();
	void SetType(int);
	int GetIconId();
	void SetIconId(int);
	TCHAR* GetName();
	void SetName(TCHAR*);

	virtual void Action(ActorStatusElement**, int*, GameStatus*);
	virtual void DoubleClickAction();
	virtual void PopupMenuInit(HMENU, ActorStatusElement**, int*);
	virtual void PopupMenuAction(int, int, int, ActorStatusElement**, int*);
};
