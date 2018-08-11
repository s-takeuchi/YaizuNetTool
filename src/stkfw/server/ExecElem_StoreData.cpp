#include "ExecElem_StoreData.h"
#include "..\VarController.h"
#include "..\LowDbAccess.h"
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

	// ������=0:"1�̕ϐ��ւ̏��̐ݒ�" ,1:"�����̕ϐ��ւ̏��̐ݒ�"
	if (LowDbAccess::GetInstance()->GetElementInfoParamInt(ElementId, 2) == 0) {
		// �R�~���j�P�[�V�����p�ϐ���ID���擾����
		VarId = LowDbAccess::GetInstance()->GetElementInfoParamInt(ElementId, 1);
		// �ϐ������݂��邩�`�F�b�N����
		if (VarCon_CheckVariableExistence(VarId) == FALSE) {
			return Ret;
		}

		// �o�^�σR�~���j�P�[�V�����ϐ��̃T�C�Y�`�F�b�N
		int CurSize = VarCon_GetCommunicationVariableSize(VarId) + 10000; // �X�V���̂�10000���Z�i���R��VarCon_CheckComm...�Q�Ɓj
		if (VarCon_CheckCommunicationVariableSize(VarDatSize - CurSize) == FALSE) {
			return Ret;
		}
	} else {
		// �o�^�σ��R�[�h�̏���`�F�b�N
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

		// �o�^�σR�~���j�P�[�V�����ϐ��̃T�C�Y�`�F�b�N
		int CurSize = 0;
		if (VarId != -1) {
			CurSize = VarCon_GetCommunicationVariableSize(VarId) + 10000; // �X�V���̂�10000���Z�i���R��VarCon_CheckComm...�Q�Ɓj
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
