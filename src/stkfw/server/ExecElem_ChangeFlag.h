#pragma once
#include <windows.h>
#include "ExecElem.h"

class ExecElem_ChangeFlag : public ExecElem
{
public:
	// Constructor
	ExecElem_ChangeFlag(int);
	// Destructor
	virtual ~ExecElem_ChangeFlag();

	virtual int Execute();

};
