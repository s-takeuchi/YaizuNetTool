#include "ExecElem_LoadData.h"
#include "..\VarController.h"
#include "..\LowDbAccess.h"
#include <windows.h>

ExecElem_LoadData::ExecElem_LoadData(int Id) : ExecElem(Id)
{
}

// Destructor
ExecElem_LoadData::~ExecElem_LoadData()
{
}

int ExecElem_LoadData::Execute()
{
	int VarId;
	BYTE* VarDat = NULL;
	int VarDatSize = 0;
	// 操作種別=0:"1つの変数から情報を取得", 1:"複数の変数から情報を取得"
	if (LowDbAccess::GetInstance()->GetElementInfoParamInt(ElementId, 2) == 0) {
		// コミュニケーション用変数のIDを取得する
		VarId = LowDbAccess::GetInstance()->GetElementInfoParamInt(ElementId, 1);
	} else {
		TCHAR TmpVarName[256];
		TCHAR TgtName[32];
		int Counter = LowDbAccess::GetInstance()->GetElementInfoParamInt(ElementId, 5);
		LowDbAccess::GetInstance()->GetElementInfoParamStr(ElementId, TmpVarName, 1);
		wsprintf(TmpVarName, _T("%s%05d"), TmpVarName, Counter);
		lstrcpyn(TgtName, TmpVarName, 32);
		VarId = VarCon_GetCommunicationVariableId(TgtName);
		if (VarId == -1) {
			SetDataLength(0);
			SetData(NULL);
			return 2;
		}
		Counter++;
		LowDbAccess::GetInstance()->SetElementInfoParamInt(ElementId, Counter, 5);
	}

	VarDatSize = VarCon_GetCommunicationVariableSize(VarId);
	if (VarDatSize != -1) {
		VarDat = new BYTE[VarDatSize];
		VarCon_GetCommunicationVariable(VarId, VarDat, VarDatSize);
	} else {
		SetDataLength(0);
		SetData(NULL);
		return 2;
	}
	SetDataLength(VarDatSize);
	SetData(VarDat); // サイズ0のデータでもnewした領域のポインタを指定する
	return 0;
}
