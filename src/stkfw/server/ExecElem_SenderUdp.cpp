#include <windows.h>
#include "..\..\..\..\YaizuComLib\src\\stksocket\stksocket.h"
#include "ExecElem_SenderUdp.h"
#include "..\LowDbAccess.h"

ExecElem_SenderUdp::ExecElem_SenderUdp(int Id) : ExecElem(Id)
{
}

// Destructor
ExecElem_SenderUdp::~ExecElem_SenderUdp()
{
}

int ExecElem_SenderUdp::Execute()
{
	int TargetId;
	int SpecType = LowDbAccess::GetInstance()->GetElementInfoParamInt(ElementId, 1);
	if (SpecType == 0) {
		// �z�X�g��/IP�A�h���X�C�|�[�g�ԍ����ڎw��̏ꍇ
		TargetId = ElementId;
		if (StkSocket_Connect(TargetId) == -1) {
			StkPropOutputLog();
			return 2;
		}
	} else {
		// Receiver�̐ڑ��Ώێw��̏ꍇ
		TargetId = LowDbAccess::GetInstance()->GetElementInfoParamInt(ElementId, 2);
	}
	StkPropOutputLog();

	// �f�[�^���M
	int DatSize = GetDataLength();
	BYTE* Dat = (BYTE*)GetData();
	int Ret = StkSocket_SendUdp(TargetId, ElementId, Dat, DatSize);
	StkPropOutputLog();

	// ���M��\�P�b�g���N���[�Y����ꍇ
	int IsClose = LowDbAccess::GetInstance()->GetElementInfoParamInt(ElementId, 4);
	if (IsClose != 0) {
		if (SpecType == 0) {
			StkSocket_Disconnect(TargetId, TargetId, FALSE);
			StkPropOutputLog();
		} else {
			//nothing to do
		}
	}
	if (Ret == SOCKET_ERROR) {
		return 2;
	}
	if (ElementType == SENDERUDP_R) {
		return 1;
	}

	return 0;
}
