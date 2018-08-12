#include "ExecElem_CheckData.h"
#include "VarController.h"
#include "LowDbAccess.h"
#include <windows.h>

ExecElem_CheckData::ExecElem_CheckData(int Id) : ExecElem(Id)
{
}

// Destructor
ExecElem_CheckData::~ExecElem_CheckData()
{
}

int ExecElem_CheckData::Execute()
{
	BYTE* VarDat = NULL;
	int VarDatSize = 0;
	BYTE* SrcVarDat = NULL;
	int SrcVarDatSize = 0;
	int VarId = LowDbAccess::GetInstance()->GetElementInfoParamInt(ElementId, 1);
	int OpType = LowDbAccess::GetInstance()->GetElementInfoParamInt(ElementId, 2);
	VarDatSize = VarCon_GetCommunicationVariableSize(VarId);
	if (VarDatSize != -1) {
		VarDat = new BYTE[VarDatSize];
		VarCon_GetCommunicationVariable(VarId, VarDat, VarDatSize);
	} else {
		return 2;
	}
	SrcVarDatSize = GetDataLength();
	SrcVarDat = (BYTE*)GetData();

	// ※入力データサイズが0のときも評価すべき

	int RetCode = 2; // この関数の戻り値（注：OpTypeが不正のときはこの値を初期値を返却）

	if (OpType == 0) { // 入力データは指定した変数の値から開始する。
		if (SrcVarDatSize < VarDatSize) {
			RetCode = 2;
		} else if (memcmp(SrcVarDat, VarDat, VarDatSize) == 0) {
			RetCode = 0;
		} else {
			RetCode = 2;
		}
	}
	if (OpType == 1) { // 入力データは指定した変数の値から開始しない。
		if (SrcVarDatSize < VarDatSize) {
			RetCode = 0;
		} else if (memcmp(SrcVarDat, VarDat, VarDatSize) == 0) {
			RetCode = 2;
		} else {
			RetCode = 0;
		}
	}
	if (OpType == 2) { // 入力データは指定した変数の値で終了する。
		if (SrcVarDatSize < VarDatSize) {
			RetCode = 2;
		} else if (memcmp(SrcVarDat + SrcVarDatSize - VarDatSize, VarDat, VarDatSize) == 0) {
			RetCode = 0;
		} else {
			RetCode = 2;
		}
	}
	if (OpType == 3) { // 入力データは指定した変数の値で終了しない。
		if (SrcVarDatSize < VarDatSize) {
			RetCode = 0;
		} else if (memcmp(SrcVarDat + SrcVarDatSize - VarDatSize, VarDat, VarDatSize) == 0) {
			RetCode = 2;
		} else {
			RetCode = 0;
		}
	}
	if (OpType == 4) { // 入力データは指定した変数の値を含む。
		if (SrcVarDatSize < VarDatSize) {
			RetCode = 2;
		} else {
			RetCode = 2;
			for (int Loop = 0; Loop <= SrcVarDatSize - VarDatSize; Loop++) {
				if (memcmp(SrcVarDat + Loop, VarDat, VarDatSize) == 0) {
					RetCode = 0;
				}
			}
		}
	}
	if (OpType == 5) { // 入力データは指定した変数の値を含まない。
		if (SrcVarDatSize < VarDatSize) {
			RetCode = 0;
		} else {
			RetCode = 0;
			for (int Loop = 0; Loop <= SrcVarDatSize - VarDatSize; Loop++) {
				if (memcmp(SrcVarDat + Loop, VarDat, VarDatSize) == 0) {
					RetCode = 2;
				}
			}
		}
	}
	if (OpType == 6) { // 入力データは指定した変数の値と完全一致する。
		if (SrcVarDatSize < VarDatSize) {
			RetCode = 2;
		} else if (memcmp(SrcVarDat, VarDat, VarDatSize) == 0 && SrcVarDatSize == VarDatSize) {
			RetCode = 0;
		} else {
			RetCode = 2;
		}
	}
	if (OpType == 7) { // 入力データは指定した変数の値と完全一致しない。
		if (SrcVarDatSize < VarDatSize) {
			RetCode = 0;
		} else if (memcmp(SrcVarDat, VarDat, VarDatSize) == 0 && SrcVarDatSize == VarDatSize) {
			RetCode = 2;
		} else {
			RetCode = 0;
		}
	}

	delete VarDat;
	return RetCode;
}
