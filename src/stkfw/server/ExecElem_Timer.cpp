#include "ExecElem_Timer.h"
#include "..\LowDbAccess.h"
#include <windows.h>

ExecElem_Timer::ExecElem_Timer(int Id) : ExecElem(Id)
{
}

// Destructor
ExecElem_Timer::~ExecElem_Timer()
{
}

int ExecElem_Timer::Execute()
{
	if (LowDbAccess::GetInstance()->GetElementInfoParamInt(ElementId, 4) == 0) {
		DWORD HighTm = LowDbAccess::GetInstance()->GetElementInfoParamInt(ElementId, 1);
		DWORD LowTm = LowDbAccess::GetInstance()->GetElementInfoParamInt(ElementId, 2);
		if (HighTm != 0 || LowTm != 0) {
			FILETIME LocFileTm;
			SYSTEMTIME SysTm;
			GetLocalTime(&SysTm);
			SystemTimeToFileTime(&SysTm, &LocFileTm);
			if (LocFileTm.dwHighDateTime >= HighTm && LocFileTm.dwLowDateTime >= LowTm) {
				return 0;
			} else {
				return 2;
			}
		}
		return 0;
	} else {
		DWORD WorkTm = LowDbAccess::GetInstance()->GetElementInfoParamInt(ElementId, 5);
		DWORD WaitTm = LowDbAccess::GetInstance()->GetElementInfoParamInt(ElementId, 3);
		DWORD CurrentTm = GetTickCount();
		if (WorkTm == 0) {
			int *TcInt = (int*)&CurrentTm;
			LowDbAccess::GetInstance()->SetElementInfoParamInt(ElementId, *TcInt, 5);
		} else {
			if (CurrentTm - WorkTm > (WaitTm * 1000)) {
				LowDbAccess::GetInstance()->SetElementInfoParamInt(ElementId, 0, 5);
				return 0;
			}
		}
	}
	return 2;
}
