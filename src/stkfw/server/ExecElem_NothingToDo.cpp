#include "ExecElem_NothingToDo.h"
#include <windows.h>

ExecElem_NothingToDo::ExecElem_NothingToDo(int Id) : ExecElem(Id)
{
}

// Destructor
ExecElem_NothingToDo::~ExecElem_NothingToDo()
{
}

int ExecElem_NothingToDo::Execute()
{
	if (ElementType == NOTHING_R) {
		return 1;
	}
	return 0;
}
