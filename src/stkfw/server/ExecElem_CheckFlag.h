#pragma once
#include <windows.h>
#include "ExecElem.h"

class ExecElem_CheckFlag : public ExecElem
{
public:
	// Constructor
	ExecElem_CheckFlag(int);
	// Destructor
	virtual ~ExecElem_CheckFlag();

	virtual int Execute();

};
