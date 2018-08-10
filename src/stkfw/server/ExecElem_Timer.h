#pragma once
#include <windows.h>
#include "ExecElem.h"

class ExecElem_Timer : public ExecElem
{
public:
	// Constructor
	ExecElem_Timer(int);
	// Destructor
	virtual ~ExecElem_Timer();

	virtual int Execute();

};
