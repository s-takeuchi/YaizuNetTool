#include "ExecElem_ChangeData.h"
#include "..\VarController.h"
#include "..\LowDbAccess.h"
#include <windows.h>

ExecElem_ChangeData::ExecElem_ChangeData(int Id) : ExecElem(Id)
{
}

// Destructor
ExecElem_ChangeData::~ExecElem_ChangeData()
{
}

int ExecElem_ChangeData::Execute()
{
	BYTE* VarDatA = NULL;
	int VarDatSizeA = 0;
	BYTE* VarDatB = NULL;
	int VarDatSizeB = 0;
	BYTE* VarDatC = NULL;
	int VarDatSizeC = 0;
	BYTE* InputVarDat = (BYTE*)GetData();
	int InputVarDatSize = GetDataLength();

	int OpType = LowDbAccess::GetInstance()->GetElementInfoParamInt(ElementId, 4);
	// ��ʂ��s���̂Ƃ��́C�����������̗v�f�Ɉڍs
	if (OpType < 0 || OpType > 5) {
		return 0;
	}
	int VarIdA = LowDbAccess::GetInstance()->GetElementInfoParamInt(ElementId, 1);
	int VarIdB = LowDbAccess::GetInstance()->GetElementInfoParamInt(ElementId, 2);
	int VarIdC = LowDbAccess::GetInstance()->GetElementInfoParamInt(ElementId, 3);

	if (OpType == 0 || OpType == 1) {
		VarDatSizeA = VarCon_GetCommunicationVariableSize(VarIdA);
		if (VarDatSizeA != -1) {
			VarDatA = new BYTE[VarDatSizeA];
			VarCon_GetCommunicationVariable(VarIdA, VarDatA, VarDatSizeA);
		} else {
			// �ϐ�(A)���s���̂Ƃ��͉����������̗v�f�Ɉڂ�
			return 0;
		}
		if ((InputVarDatSize + VarDatSizeA) > 9999999) {
			delete VarDatA;
			return 0;
		}
		BYTE* NewVarDat = new BYTE[InputVarDatSize + VarDatSizeA];
		int NewVarDatSize = InputVarDatSize + VarDatSizeA;
		if (OpType == 0) {
			memcpy(NewVarDat, VarDatA, VarDatSizeA);
			memcpy(NewVarDat + VarDatSizeA, InputVarDat, InputVarDatSize);
		}
		if (OpType == 1) {
			memcpy(NewVarDat, InputVarDat, InputVarDatSize);
			memcpy(NewVarDat + InputVarDatSize, VarDatA, VarDatSizeA);
		}
		delete VarDatA;
		delete InputVarDat;
		SetData((BYTE*)NewVarDat);
		SetDataLength(InputVarDatSize + VarDatSizeA);
		return 0;
	}
	if (OpType == 2) {
		VarDatSizeA = VarCon_GetCommunicationVariableSize(VarIdA);
		VarDatSizeB = VarCon_GetCommunicationVariableSize(VarIdB);
		if (VarDatSizeA != -1 && VarDatSizeB != -1) {
			VarDatA = new BYTE[VarDatSizeA];
			VarDatB = new BYTE[VarDatSizeB];
			VarCon_GetCommunicationVariable(VarIdA, VarDatA, VarDatSizeA);
			VarCon_GetCommunicationVariable(VarIdB, VarDatB, VarDatSizeB);
		} else {
			// �ϐ�(A)�܂���(B)���s���̂Ƃ��͉����������̗v�f�Ɉڂ�
			return 0;
		}
		int DiffSize = VarDatSizeB - VarDatSizeA; // 1��̒u�������ɂ�����f�[�^�T�C�Y�̍���
												  // ���̓f�[�^�ɑ��݂��錟���Ώە�����̌������߂�
		int FndCount = 0; // ���̓f�[�^�ɑ��݂��錟���Ώە�����̌�
		for (int Loop = 0; Loop < InputVarDatSize - VarDatSizeA + 1; Loop++) {
			if (memcmp(InputVarDat + Loop, VarDatA, VarDatSizeA) == 0) {
				FndCount++;
				Loop += VarDatSizeA - 1;
			}
		}

		// �o�̓f�[�^�̈�̊m��
		int NewDatSize = InputVarDatSize + DiffSize * FndCount;
		if (NewDatSize > 9999999) {
			delete VarDatA;
			delete VarDatB;
			return 0;
		}
		BYTE* NewDat = new BYTE[NewDatSize];

		// �u������
		BOOL LastOp = 0;
		BYTE* NewDatPtr = NewDat;
		for (int Loop = 0; Loop < InputVarDatSize - VarDatSizeA + 1; Loop++) {
			if (memcmp(InputVarDat + Loop, VarDatA, VarDatSizeA) == 0) {
				memcpy(NewDatPtr, VarDatB, VarDatSizeB);
				NewDatPtr += VarDatSizeB;
				Loop += VarDatSizeA - 1;
				LastOp = TRUE;
			} else {
				*NewDatPtr = InputVarDat[Loop];
				NewDatPtr++;
				LastOp = FALSE;
			}
		}
		if (LastOp == FALSE) {
			for (int Loop = InputVarDatSize - VarDatSizeA + 1; Loop < InputVarDatSize; Loop++) {
				*NewDatPtr = InputVarDat[Loop];
				NewDatPtr++;
			}
		}

		delete VarDatA;
		delete VarDatB;
		delete InputVarDat;
		SetData((BYTE*)NewDat);
		SetDataLength(NewDatSize);

		return 0;
	}
	if (OpType == 3) {
		BYTE* InputDat = (BYTE*)GetData();
		int InputDatSize = GetDataLength();

		VarDatSizeA = VarCon_GetCommunicationVariableSize(VarIdA);
		VarDatSizeB = VarCon_GetCommunicationVariableSize(VarIdB);
		if (VarDatSizeA != -1 && VarDatSizeB != -1) {
			VarDatA = new BYTE[VarDatSizeA];
			VarCon_GetCommunicationVariable(VarIdA, VarDatA, VarDatSizeA);
			VarDatB = new BYTE[VarDatSizeB];
			VarCon_GetCommunicationVariable(VarIdB, VarDatB, VarDatSizeB);

			int Start = -1;
			int End = -1;
			for (int Loop = 0; Loop <= InputDatSize - VarDatSizeA; Loop++) {
				int Ret = memcmp(InputDat + Loop, VarDatA, VarDatSizeA);
				if (Ret == 0) {
					Start = Loop;
					break;
				}
			}
			for (int Loop = 0; Loop <= InputDatSize - VarDatSizeB; Loop++) {
				int Ret = memcmp(InputDat + Loop, VarDatB, VarDatSizeB);
				if (Ret == 0) {
					End = Loop + VarDatSizeB - 1;
					break;
				}
			}

			delete VarDatA;
			delete VarDatB;
			if (Start == -1 || End == -1 || End < Start) {
				return 0;
			}
			int NewDatSize = End - Start + 1;
			BYTE* NewDat = new BYTE[NewDatSize];
			memcpy(NewDat, InputDat + Start, NewDatSize);

			delete InputDat;
			SetData((BYTE*)NewDat);
			SetDataLength(NewDatSize);
			return 0;
		} else {
			// �ϐ�(A)�܂���(B)���s���̂Ƃ��͉����������̗v�f�Ɉڂ�
			return 0;
		}
	}
	if (OpType == 4) {
		BYTE* InputDat = (BYTE*)GetData();
		delete InputDat;
		BYTE* ZeroDat = new BYTE[0];
		SetData(ZeroDat);
		SetDataLength(0);

		return 0;
	}
	if (OpType == 5) {
		VarDatSizeA = VarCon_GetCommunicationVariableSize(VarIdA);
		if (VarDatSizeA != -1) {
			VarDatA = new BYTE[VarDatSizeA];
			VarCon_GetCommunicationVariable(VarIdA, VarDatA, VarDatSizeA);
		} else {
			// �ϐ�(A)���s���̂Ƃ��͉����������̗v�f�Ɉڂ�
			return 0;
		}
		delete InputVarDat;
		SetData((BYTE*)VarDatA);
		SetDataLength(VarDatSizeA);
		return 0;
	}
	return 0;
}
