#include "ExecElem_HttpHeader.h"
#include "LowDbAccess.h"
#include <windows.h>

ExecElem_HttpHeader::ExecElem_HttpHeader(int Id) : ExecElem(Id)
{
}

// Destructor
ExecElem_HttpHeader::~ExecElem_HttpHeader()
{
}

int ExecElem_HttpHeader::Execute()
{
	return 0;
}
