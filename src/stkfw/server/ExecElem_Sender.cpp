#include <windows.h>
#include "..\..\..\..\YaizuComLib\src\\stksocket\stksocket.h"
#include "ServerMsg.h"
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
		// ホスト名/IPアドレス，ポート番号直接指定の場合
		TargetId = ElementId;
		if (StkSocket_Connect(TargetId) == -1) {
			StkPropOutputLog();
			return 2;
		}
	} else {
		// Receiverの接続対象指定の場合
		TargetId = LowDbAccess::GetInstance()->GetElementInfoParamInt(ElementId, 2);
	}
	StkPropOutputLog();

	while (TryLockShared(TargetId) == false) {
		Sleep(1);
	}

	// データ送信
	int DatSize = GetDataLength();
	BYTE* Dat = (BYTE*)GetData();
	int Ret = StkSocket_Send(TargetId, ElementId, Dat, DatSize);
	StkPropOutputLog();

	// 送信後ソケットをクローズする場合
	int IsClose = LowDbAccess::GetInstance()->GetElementInfoParamInt(ElementId, 4);
	if (IsClose != 0) {
		bool CorElemExistFlag = LowDbAccess::GetInstance()->DoesCorrespondingElementExist(ElementId);
		if (!CorElemExistFlag) {
			if (SpecType == 0) {
				StkSocket_Disconnect(TargetId, TargetId, (IsClose == 2) ? TRUE : FALSE);
			} else {
				StkSocket_CloseAccept(TargetId, ElementId, (IsClose == 2) ? TRUE : FALSE);
			}
		} else {
			TCHAR Name[32] = _T("");
			TCHAR DummyBuf[128] = _T("");
			wsprintf(DummyBuf, _T("%s\r\n"), ServerMsg::GetMsg(ServerMsg::STKFW_LOG_CANNOTCLOSE));
			LowDbAccess::GetInstance()->GetViewElementNameFromId(ElementId, Name);
			add_log(Name, DummyBuf);
		}
	}
	StkPropOutputLog();
	if (Ret == SOCKET_ERROR) {
		UnlockShared(TargetId);
		return 2;
	}
	if (ElementType == SENDER_R) {
		UnlockShared(TargetId);
		return 1;
	}
	UnlockShared(TargetId);
	return 0;
}
