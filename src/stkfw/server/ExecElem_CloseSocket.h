#pragma once
#include <windows.h>
#include "ExecElem.h"

class ExecElem_CloseSocket : public ExecElem
{
public:
	// Constructor
	ExecElem_CloseSocket(int);
	// Destructor
	virtual ~ExecElem_CloseSocket();

	virtual int Execute();

};
