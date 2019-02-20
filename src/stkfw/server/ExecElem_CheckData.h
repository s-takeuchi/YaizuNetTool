#pragma once
#include <windows.h>
#include "ExecElem.h"

class ExecElem_CheckData : public ExecElem
{
public:
	// Constructor
	ExecElem_CheckData(int);
	// Destructor
	virtual ~ExecElem_CheckData();

	virtual int Execute();

};
