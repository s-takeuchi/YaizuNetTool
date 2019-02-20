#pragma once
#include <windows.h>
#include "ExecElem.h"

class ExecElem_ReadFile : public ExecElem
{
public:
	// Constructor
	ExecElem_ReadFile(int);
	// Destructor
	virtual ~ExecElem_ReadFile();

	virtual int Execute();

};
