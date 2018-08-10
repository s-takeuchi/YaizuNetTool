#pragma once
#include <windows.h>
#include "ExecElem.h"

class ExecElem_Mapper : public ExecElem
{
public:
	// Constructor
	ExecElem_Mapper(int);
	// Destructor
	virtual ~ExecElem_Mapper();

	virtual int Execute();

};
