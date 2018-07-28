#include <windows.h>
#include "..\..\..\..\YaizuComLib\src\\stksocket\stksocket.h"
#include "ExecElem_Receiver.h"
#include "..\VarController.h"
#include "..\LowDbAccess.h"

ExecElem_Receiver::ExecElem_Receiver(int Id) : ExecElem(Id)
{
}

// Destructor
ExecElem_Receiver::~ExecElem_Receiver()
{
}

int ExecElem_Receiver::Execute()
{
	int TargetId;
	int SpecType = LowDbAccess::GetInstance()->GetElementInfoParamInt(ElementId, 1);

	// �z�X�g��/IP�A�h���X�C�|�[�g�ԍ����ڎw��܂���Multi Accept�̏ꍇ
	if (SpecType == 0 || SpecType == 2) {
		// �z�X�g��/IP�A�h���X�C�|�[�g�ԍ����ڎw��܂���Multi Accept�̏ꍇ
		TargetId = ElementId;
		if (StkSocket_Accept(TargetId) == -1) {
			StkPropOutputLog();
			return 2;
		}
	} else {
		// Sender�̐ڑ��Ώێw��̏ꍇ
		TargetId = LowDbAccess::GetInstance()->GetElementInfoParamInt(ElementId, 2);
	}
	StkPropOutputLog();

	// �I�������ݒ�
	int FinishCondition = LowDbAccess::GetInstance()->GetElementInfoParamInt(ElementId, 5);
	int FinishCondTimeout = LowDbAccess::GetInstance()->GetElementInfoParamInt(ElementId, 6);

	// If the finish condition shows the string-end condition, load communication variable.
	BYTE* VarDat = NULL;
	int VarDatSize = 0;
	if (FinishCondition < 0) {
		int VarId = -1 * FinishCondition;
		VarDatSize = VarCon_GetCommunicationVariableSize(VarId);
		if (VarDatSize != -1) {
			VarDat = new BYTE[VarDatSize];
			VarCon_GetCommunicationVariable(VarId, VarDat, VarDatSize);
		} else {
			return 2;
		}
	}

	// �f�[�^�̎�M
	BYTE* Buf = new BYTE[10000000];
	int ActSize = 0;
	BOOL ForceStop = (StartStopFlag == TRUE) ? FALSE : TRUE;
	int RevisedFinishCondition = 0;
	if (FinishCondition < 0) {
		RevisedFinishCondition = STKSOCKET_RECV_FINISHCOND_STRING;
	} else if (FinishCondition == 0) {
		RevisedFinishCondition = STKSOCKET_RECV_FINISHCOND_UNCONDITIONAL;
	} else if (FinishCondition == 1) {
		RevisedFinishCondition = STKSOCKET_RECV_FINISHCOND_TIMEOUT;
	} else if (FinishCondition == 3) {
		RevisedFinishCondition = STKSOCKET_RECV_FINISHCOND_CONTENTLENGTH;
	} else if (FinishCondition == 2) {
		RevisedFinishCondition = STKSOCKET_RECV_FINISHCOND_PEERCLOSURE;
	} else if (FinishCondition >= 10000001 && FinishCondition <= 19999999) {
		RevisedFinishCondition = FinishCondition - 10000000;
	}
	ActSize = StkSocket_Receive(TargetId, ElementId, Buf, 9999999, RevisedFinishCondition, FinishCondTimeout, VarDat, VarDatSize, ForceStop);
	StkPropOutputLog();

	// If the finish condition shows the string-end condition, release the allocated data area for communication variable.
	if (FinishCondition < 0 && VarDat != NULL) {
		delete VarDat;
	}

	// �f�[�^��M���G���[�����^�\�P�b�g�ؒf
	if (ActSize == SOCKET_ERROR || ActSize == -1) {
		delete Buf;
		return 2;
	}
	// �ڑ���\�P�b�g���N���[�Y���ꂽ
	if (ActSize == 0) {
		if (SpecType == 0 || SpecType == 2) {
			StkSocket_CloseAccept(TargetId, TargetId, FALSE);
		} else {
			StkSocket_Disconnect(TargetId, ElementId, FALSE);
		}
		delete Buf;
		StkPropOutputLog();
		return 2;
	}
	// �^�C���A�E�g
	if (ActSize == -2) {
		TCHAR TmpBuf[256];
		LowDbAccess::GetInstance()->GetElementInfoParamStr(ElementId, TmpBuf, 2);
		if (lstrcmp(TmpBuf, _T("PROCEED;")) == 0) {
			BYTE* TmpVarDat = new BYTE[0];
			SetDataLength(0);
			SetData(TmpVarDat);
			delete Buf;
			return 0;
		} else {
			delete Buf;
			return 2;
		}
	}

	// �f�[�^��K�؂ȃT�C�Y�̗̈�ɃR�s�[����
	BYTE* TmpVarDat = new BYTE[ActSize];
	memcpy((void*)TmpVarDat, (void*)Buf, ActSize);
	SetDataLength(ActSize);
	SetData(TmpVarDat);
	delete Buf;

	// ��M��\�P�b�g���N���[�Y����ꍇ
	int IsClose = LowDbAccess::GetInstance()->GetElementInfoParamInt(ElementId, 4);
	if (IsClose != 0) {
		if (SpecType == 0 || SpecType == 2) {
			StkSocket_CloseAccept(TargetId, TargetId, (IsClose == 2) ? TRUE : FALSE);
		} else {
			StkSocket_Disconnect(TargetId, ElementId, (IsClose == 2) ? TRUE : FALSE);
		}
	}
	StkPropOutputLog();
	return 0;
}
