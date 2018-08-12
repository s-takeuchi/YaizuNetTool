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

	// データ送信
	int DatSize = GetDataLength();
	BYTE* Dat = (BYTE*)GetData();
	int Ret = StkSocket_Send(TargetId, ElementId, Dat, DatSize);
	StkPropOutputLog();

	// 送信後ソケットをクローズする場合
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
