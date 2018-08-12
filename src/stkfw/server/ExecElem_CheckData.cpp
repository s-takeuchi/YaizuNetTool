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

	// �����̓f�[�^�T�C�Y��0�̂Ƃ����]�����ׂ�

	int RetCode = 2; // ���̊֐��̖߂�l�i���FOpType���s���̂Ƃ��͂��̒l�������l��ԋp�j

	if (OpType == 0) { // ���̓f�[�^�͎w�肵���ϐ��̒l����J�n����B
		if (SrcVarDatSize < VarDatSize) {
			RetCode = 2;
		} else if (memcmp(SrcVarDat, VarDat, VarDatSize) == 0) {
			RetCode = 0;
		} else {
			RetCode = 2;
		}
	}
	if (OpType == 1) { // ���̓f�[�^�͎w�肵���ϐ��̒l����J�n���Ȃ��B
		if (SrcVarDatSize < VarDatSize) {
			RetCode = 0;
		} else if (memcmp(SrcVarDat, VarDat, VarDatSize) == 0) {
			RetCode = 2;
		} else {
			RetCode = 0;
		}
	}
	if (OpType == 2) { // ���̓f�[�^�͎w�肵���ϐ��̒l�ŏI������B
		if (SrcVarDatSize < VarDatSize) {
			RetCode = 2;
		} else if (memcmp(SrcVarDat + SrcVarDatSize - VarDatSize, VarDat, VarDatSize) == 0) {
			RetCode = 0;
		} else {
			RetCode = 2;
		}
	}
	if (OpType == 3) { // ���̓f�[�^�͎w�肵���ϐ��̒l�ŏI�����Ȃ��B
		if (SrcVarDatSize < VarDatSize) {
			RetCode = 0;
		} else if (memcmp(SrcVarDat + SrcVarDatSize - VarDatSize, VarDat, VarDatSize) == 0) {
			RetCode = 2;
		} else {
			RetCode = 0;
		}
	}
	if (OpType == 4) { // ���̓f�[�^�͎w�肵���ϐ��̒l���܂ށB
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
	if (OpType == 5) { // ���̓f�[�^�͎w�肵���ϐ��̒l���܂܂Ȃ��B
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
	if (OpType == 6) { // ���̓f�[�^�͎w�肵���ϐ��̒l�Ɗ��S��v����B
		if (SrcVarDatSize < VarDatSize) {
			RetCode = 2;
		} else if (memcmp(SrcVarDat, VarDat, VarDatSize) == 0 && SrcVarDatSize == VarDatSize) {
			RetCode = 0;
		} else {
			RetCode = 2;
		}
	}
	if (OpType == 7) { // ���̓f�[�^�͎w�肵���ϐ��̒l�Ɗ��S��v���Ȃ��B
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
