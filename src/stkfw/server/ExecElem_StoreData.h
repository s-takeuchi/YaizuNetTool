#pragma once
#include <windows.h>
#include "ExecElem.h"

class ExecElem_StoreData : public ExecElem
{
public:
	// Constructor
	ExecElem_StoreData(int);
	// Destructor
	virtual ~ExecElem_StoreData();

	virtual int Execute();

};
