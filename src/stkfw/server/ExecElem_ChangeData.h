#pragma once
#include <windows.h>
#include "ExecElem.h"

class ExecElem_ChangeData : public ExecElem
{
public:
	// Constructor
	ExecElem_ChangeData(int);
	// Destructor
	virtual ~ExecElem_ChangeData();

	virtual int Execute();

};
