#pragma once
#include <windows.h>
#include "ExecElem.h"

class ExecElem_SenderUdp : public ExecElem
{
public:
	// Constructor
	ExecElem_SenderUdp(int);
	// Destructor
	virtual ~ExecElem_SenderUdp();

	virtual int Execute();

};
