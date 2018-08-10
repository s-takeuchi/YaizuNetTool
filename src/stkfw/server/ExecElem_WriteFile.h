#pragma once
#include <windows.h>
#include "ExecElem.h"

class ExecElem_WriteFile : public ExecElem
{
public:
	// Constructor
	ExecElem_WriteFile(int);
	// Destructor
	virtual ~ExecElem_WriteFile();

	virtual int Execute();

};
