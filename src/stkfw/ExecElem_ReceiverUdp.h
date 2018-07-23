#pragma once
#include <windows.h>
#include "ExecElem.h"

class ExecElem_ReceiverUdp : public ExecElem
{
public:
	// Constructor
	ExecElem_ReceiverUdp(int);
	// Destructor
	virtual ~ExecElem_ReceiverUdp();

	virtual int Execute();

};
