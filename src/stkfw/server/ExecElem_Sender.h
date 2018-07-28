#pragma once
#include <windows.h>
#include "ExecElem.h"

class ExecElem_Sender : public ExecElem
{
public:
	// Constructor
	ExecElem_Sender(int);
	// Destructor
	virtual ~ExecElem_Sender();

	virtual int Execute();

};
