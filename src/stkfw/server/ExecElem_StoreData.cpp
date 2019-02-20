#include "ExecElem_StoreData.h"
#include "VarController.h"
#include "LowDbAccess.h"
#include <windows.h>

ExecElem_StoreData::ExecElem_StoreData(int Id) : ExecElem(Id)
{
	//Initialize counter
	int InitCounter = LowDbAccess::GetInstance()->GetElementInfoParamInt(Id, 4);
	LowDbAccess::GetInstance()->SetElementInfoParamInt(Id, InitCounter, 5);
}

// Destructor
ExecElem_StoreData::~ExecElem_StoreData()
{
}

int ExecElem_StoreData::Execute()
{
	int VarId;
	BYTE* VarDat = (BYTE*)GetData();
	int VarDatSize = GetDataLength();

	int Ret = 0;
	if (ElementType == STOREDATA_R) {
		Ret = 1;
	}

	// 操作種別=0:"1つの変数への情報の設定" ,1:"複数の変数への情報の設定"
	if (LowDbAccess::GetInstance()->GetElementInfoParamInt(ElementId, 2) == 0) {
		// コミュニケーション用変数のIDを取得する
		VarId = LowDbAccess::GetInstance()->GetElementInfoParamInt(ElementId, 1);
		// 変数が存在するかチェックする
		if (VarCon_CheckVariableExistence(VarId) == FALSE) {
			return Ret;
		}

		// 登録済コミュニケーション変数のサイズチェック
		int CurSize = VarCon_GetCommunicationVariableSize(VarId) + 10000; // 更新時のみ10000加算（理由はVarCon_CheckComm...参照）
		if (VarCon_CheckCommunicationVariableSize(VarDatSize - CurSize) == FALSE) {
			return Ret;
		}
	} else {
		// 登録済レコードの上限チェック
		if (VarCon_CheckVariableCount() == FALSE) {
			return Ret;
		}

		TCHAR TmpVarName[256];
		TCHAR TgtName[32];
		TCHAR TgtDesc[64];
		int Counter = LowDbAccess::GetInstance()->GetElementInfoParamInt(ElementId, 5);
		if (Counter < 0 || Counter > 99999) {
			Counter = 0;
		}
		LowDbAccess::GetInstance()->GetElementInfoParamStr(ElementId, TmpVarName, 1);
		wsprintf(TmpVarName, _T("%s%05d"), TmpVarName, Counter);
		lstrcpyn(TgtName, TmpVarName, 32);
		lstrcpyn(TgtDesc, TmpVarName, 64);
		VarId = VarCon_GetCommunicationVariableId(TgtName);

		// 登録済コミュニケーション変数のサイズチェック
		int CurSize = 0;
		if (VarId != -1) {
			CurSize = VarCon_GetCommunicationVariableSize(VarId) + 10000; // 更新時のみ10000加算（理由はVarCon_CheckComm...参照）
		}
		if (VarCon_CheckCommunicationVariableSize(VarDatSize - CurSize) == FALSE) {
			return Ret;
		}

		if (VarId == -1) {
			VarId = VarCon_AddVariableRecord(TgtName, TgtDesc, 0);
		}
		Counter++;
		LowDbAccess::GetInstance()->SetElementInfoParamInt(ElementId, Counter, 5);
	}

	BYTE* TmpVarDat = new BYTE[10000000];
	memcpy((void*)TmpVarDat, (void*)VarDat, VarDatSize);
	VarCon_UpdateCommunicationVariable(VarId, TmpVarDat, VarDatSize);
	delete TmpVarDat;
	return Ret;
}
