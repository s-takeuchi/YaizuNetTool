#pragma once
#include <windows.h>
#include "ExecElem.h"

class ExecElem_HttpHeader : public ExecElem
{
public:
	// Constructor
	ExecElem_HttpHeader(int);
	// Destructor
	virtual ~ExecElem_HttpHeader();

	virtual int Execute();

};
