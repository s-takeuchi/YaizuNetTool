#include <windows.h>
#include "..\..\..\..\YaizuComLib\src\\stksocket\stksocket.h"
#include "ExecElem_SenderUdp.h"
#include "LowDbAccess.h"

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
	int Ret = StkSocket_SendUdp(TargetId, ElementId, Dat, DatSize);
	StkPropOutputLog();

	// 送信後ソケットをクローズする場合
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
