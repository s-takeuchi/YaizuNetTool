#include "ExecElem_CheckFlag.h"
#include "VarController.h"
#include "LowDbAccess.h"
#include <windows.h>

ExecElem_CheckFlag::ExecElem_CheckFlag(int Id) : ExecElem(Id)
{
}

// Destructor
ExecElem_CheckFlag::~ExecElem_CheckFlag()
{
}

int ExecElem_CheckFlag::Execute()
{
	int VarId = LowDbAccess::GetInstance()->GetElementInfoParamInt(ElementId, 1);
	int VarValue = LowDbAccess::GetInstance()->GetElementInfoParamInt(ElementId, 2);
	if (VarCon_CheckVariableExistence(VarId) == FALSE) {
		return 2;
	}
	int FlagVal = VarCon_GetFlagVariable(VarId);
	if (VarValue == FlagVal) {
		return 0;
	}
	return 2;
}
