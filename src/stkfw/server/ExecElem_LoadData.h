#pragma once
#include <windows.h>
#include "ExecElem.h"

class ExecElem_LoadData : public ExecElem
{
public:
	// Constructor
	ExecElem_LoadData(int);
	// Destructor
	virtual ~ExecElem_LoadData();

	virtual int Execute();

};
