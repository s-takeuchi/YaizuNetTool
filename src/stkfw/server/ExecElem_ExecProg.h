#pragma once
#include <windows.h>
#include "ExecElem.h"

class ExecElem_ExecProg : public ExecElem
{
private:
	// Attributes for the "Execute Program"
	PROCESS_INFORMATION ExeProcInfo;
	HANDLE StdInD, StdOutD;

public:
	// Constructor
	ExecElem_ExecProg(int);
	// Destructor
	virtual ~ExecElem_ExecProg();

	virtual int Execute();

};
