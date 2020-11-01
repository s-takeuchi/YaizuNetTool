#include <windows.h>
#include "..\..\..\..\YaizuComLib\src\\stksocket\stksocket.h"
#include "ExecElem_CloseSocket.h"
#include "LowDbAccess.h"

ExecElem_CloseSocket::ExecElem_CloseSocket(int Id) : ExecElem(Id)
{
}

// Destructor
ExecElem_CloseSocket::~ExecElem_CloseSocket()
{
}

int ExecElem_CloseSocket::Execute()
{
	int TargetId = LowDbAccess::GetInstance()->GetElementInfoParamInt(ElementId, 1);
	int TargetType = LowDbAccess::GetInstance()->GetViewElementTypeFromId(TargetId);
	if (TargetType == -1) {
		return 0;
	}
	int IsClose = LowDbAccess::GetInstance()->GetElementInfoParamInt(ElementId, 2);
	while (TryLock(TargetId) == false) {
		Sleep(1);
	}
	if (TargetType == 1) {
		StkSocket_CloseAccept(TargetId, ElementId, (IsClose == 1) ? TRUE : FALSE);
	}
	if (TargetType == 4 || TargetType == 7) {
		StkSocket_Disconnect(TargetId, ElementId, (IsClose == 1) ? TRUE : FALSE);
	}
	if (TargetType == 22 || TargetType == 23) {
		StkSocket_Disconnect(TargetId, ElementId, FALSE);
	}
	Unlock(TargetId);
	StkPropOutputLog();
	return 0;
}
