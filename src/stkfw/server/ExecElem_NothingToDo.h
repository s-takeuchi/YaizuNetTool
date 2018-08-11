#pragma once
#include <windows.h>
#include "ExecElem.h"

class ExecElem_NothingToDo : public ExecElem
{
public:
	// Constructor
	ExecElem_NothingToDo(int);
	// Destructor
	virtual ~ExecElem_NothingToDo();

	virtual int Execute();

};
