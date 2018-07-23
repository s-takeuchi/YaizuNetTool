#pragma once
#include <windows.h>
#include "ExecElem.h"

class ExecElem_Receiver : public ExecElem
{
public:
	// Constructor
	ExecElem_Receiver(int);
	// Destructor
	virtual ~ExecElem_Receiver();

	virtual int Execute();

};
