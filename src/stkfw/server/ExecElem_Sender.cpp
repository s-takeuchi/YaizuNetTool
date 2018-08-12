#include <windows.h>
#include "..\..\..\..\YaizuComLib\src\\stksocket\stksocket.h"
#include "ExecElem_Sender.h"
#include "LowDbAccess.h"

ExecElem_Sender::ExecElem_Sender(int Id) : ExecElem(Id)
{
}

// Destructor
ExecElem_Sender::~ExecElem_Sender()
{
}

int ExecElem_Sender::Execute()
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
	int Ret = StkSocket_Send(TargetId, ElementId, Dat, DatSize);
	StkPropOutputLog();

	// ���M��\�P�b�g���N���[�Y����ꍇ
	int IsClose = LowDbAccess::GetInstance()->GetElementInfoParamInt(ElementId, 4);
	if (IsClose != 0) {
		if (SpecType == 0) {
			StkSocket_Disconnect(TargetId, TargetId, (IsClose == 2) ? TRUE : FALSE);
		} else {
			StkSocket_CloseAccept(TargetId, ElementId, (IsClose == 2) ? TRUE : FALSE);
		}
	}
	StkPropOutputLog();
	if (Ret == SOCKET_ERROR) {
		return 2;
	}
	if (ElementType == SENDER_R) {
		return 1;
	}
	return 0;
}
