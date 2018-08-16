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

																					 // ホスト名/IPアドレス，ポート番号直接指定の場合
	if (SpecType == 0) {
		// ホスト名/IPアドレス，ポート番号直接指定の場合
		TargetId = ElementId;
	} else {
		// Senderの接続対象指定の場合
		TargetId = LowDbAccess::GetInstance()->GetElementInfoParamInt(ElementId, 2);
	}
	StkPropOutputLog();

	// データの受信
	BYTE* Buf = new BYTE[10000000];
	int ActSize = 0;
	ActSize = StkSocket_ReceiveUdp(TargetId, ElementId, Buf, 9999999);
	StkPropOutputLog();

	// データ受信中エラー発生／ソケット切断
	if (ActSize == SOCKET_ERROR || ActSize == -1 || ActSize == -2) {
		delete Buf;
		return 2;
	}

	// データを適切なサイズの領域にコピーする
	BYTE* TmpVarDat = new BYTE[ActSize];
	memcpy((void*)TmpVarDat, (void*)Buf, ActSize);
	SetDataLength(ActSize);
	SetData(TmpVarDat);
	delete Buf;

	// 受信後ソケットをクローズする場合
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
