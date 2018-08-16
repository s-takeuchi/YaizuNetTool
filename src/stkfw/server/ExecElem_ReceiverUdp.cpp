#include <windows.h>
#include "..\..\..\..\YaizuComLib\src\\stksocket\stksocket.h"
#include "ExecElem_ReceiverUdp.h"
#include "LowDbAccess.h"

ExecElem_ReceiverUdp::ExecElem_ReceiverUdp(int Id) : ExecElem(Id)
{
	int SockType = 0;
	int ActionType = 0;
	TCHAR TargetAddr[256] = _T("");
	int TargetPort = 0;
	BOOL CopiedFlag = FALSE;
	if (StkSocket_GetInfo(Id, &SockType, &ActionType, TargetAddr, &TargetPort, &CopiedFlag) == 0) {
		if (CopiedFlag == FALSE) {
			StkSocket_Open(Id);
			StkPropOutputLog();
		}
	}
}

// Destructor
ExecElem_ReceiverUdp::~ExecElem_ReceiverUdp()
{
	int SockType = 0;
	int ActionType = 0;
	TCHAR TargetAddr[256] = _T("");
	int TargetPort = 0;
	BOOL CopiedFlag = FALSE;
	if (StkSocket_GetInfo(ElementId, &SockType, &ActionType, TargetAddr, &TargetPort, &CopiedFlag) == 0) {
		if (CopiedFlag == FALSE) {
			StkSocket_Close(ElementId, FALSE);
			StkPropOutputLog();
		}
	}
}

int ExecElem_ReceiverUdp::Execute()
{
	int TargetId;
	int SpecType = LowDbAccess::GetInstance()->GetElementInfoParamInt(ElementId, 1); // Specified type

																					 // �z�X�g��/IP�A�h���X�C�|�[�g�ԍ����ڎw��̏ꍇ
	if (SpecType == 0) {
		// �z�X�g��/IP�A�h���X�C�|�[�g�ԍ����ڎw��̏ꍇ
		TargetId = ElementId;
	} else {
		// Sender�̐ڑ��Ώێw��̏ꍇ
		TargetId = LowDbAccess::GetInstance()->GetElementInfoParamInt(ElementId, 2);
	}
	StkPropOutputLog();

	// �f�[�^�̎�M
	BYTE* Buf = new BYTE[10000000];
	int ActSize = 0;
	ActSize = StkSocket_ReceiveUdp(TargetId, ElementId, Buf, 9999999);
	StkPropOutputLog();

	// �f�[�^��M���G���[�����^�\�P�b�g�ؒf
	if (ActSize == SOCKET_ERROR || ActSize == -1 || ActSize == -2) {
		delete Buf;
		return 2;
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
		if (SpecType == 0) {
			//nothing to do
		} else {
			StkSocket_Disconnect(TargetId, ElementId, FALSE);
			StkPropOutputLog();
		}
	}

	return 0;
}
