#include "ExecElem_ChangeFlag.h"
#include "VarController.h"
#include "LowDbAccess.h"
#include <windows.h>

ExecElem_ChangeFlag::ExecElem_ChangeFlag(int Id) : ExecElem(Id)
{
}

// Destructor
ExecElem_ChangeFlag::~ExecElem_ChangeFlag()
{
}

int ExecElem_ChangeFlag::Execute()
{
	int VarId = LowDbAccess::GetInstance()->GetElementInfoParamInt(ElementId, 1);
	int VarValue = LowDbAccess::GetInstance()->GetElementInfoParamInt(ElementId, 2);
	if (VarCon_CheckVariableExistence(VarId) == FALSE) {
		return 0;
	}
	if (VarValue == 0) {
		VarCon_ChangeFlagVariable(VarId, FALSE);
	} else {
		VarCon_ChangeFlagVariable(VarId, TRUE);
	}
	return 0;
}
