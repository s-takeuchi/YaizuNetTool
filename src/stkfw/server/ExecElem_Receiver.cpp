#include <windows.h>
#include "..\..\..\..\YaizuComLib\src\\stksocket\stksocket.h"
#include "ExecElem_Receiver.h"
#include "VarController.h"
#include "LowDbAccess.h"

ExecElem_Receiver::ExecElem_Receiver(int Id) : ExecElem(Id)
{
	int SockType = 0;
	int ActionType = 0;
	TCHAR TargetAddr[256] = _T("");
	int TargetPort = 0;
	bool CopiedFlag = false;
	if (StkSocket_GetInfo(Id, &SockType, &ActionType, TargetAddr, &TargetPort, &CopiedFlag) == 0) {
		if (CopiedFlag == false) {
			StkSocket_Open(Id);
			StkPropOutputLog();
		}
	}
}

// Destructor
ExecElem_Receiver::~ExecElem_Receiver()
{
	int SockType = 0;
	int ActionType = 0;
	TCHAR TargetAddr[256] = _T("");
	int TargetPort = 0;
	bool CopiedFlag = false;
	if (StkSocket_GetInfo(ElementId, &SockType, &ActionType, TargetAddr, &TargetPort, &CopiedFlag) == 0) {
		if (CopiedFlag == false) {
			StkSocket_Close(ElementId, false);
			StkPropOutputLog();
		}
	}
}

int ExecElem_Receiver::Execute()
{
	int TargetId;
	int SpecType = LowDbAccess::GetInstance()->GetElementInfoParamInt(ElementId, 1);

	// ホスト名/IPアドレス，ポート番号直接指定またはMulti Acceptの場合
	if (SpecType == 0 || SpecType == 2) {
		// ホスト名/IPアドレス，ポート番号直接指定またはMulti Acceptの場合
		TargetId = ElementId;
		if (StkSocket_Accept(TargetId) == -1) {
			StkPropOutputLog();
			return 2;
		}
	} else {
		// Senderの接続対象指定の場合
		TargetId = LowDbAccess::GetInstance()->GetElementInfoParamInt(ElementId, 2);
	}
	StkPropOutputLog();

	// 終了条件設定
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

	// データの受信
	BYTE* Buf = new BYTE[10000000];
	int ActSize = 0;
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
	ActSize = StkSocket_Receive(TargetId, ElementId, Buf, 9999999, RevisedFinishCondition, FinishCondTimeout, VarDat, VarDatSize);
	StkPropOutputLog();

	// If the finish condition shows the string-end condition, release the allocated data area for communication variable.
	if (FinishCondition < 0 && VarDat != NULL) {
		delete VarDat;
	}

	// データ受信中エラー発生／ソケット切断
	if (ActSize == SOCKET_ERROR || ActSize == -1) {
		delete Buf;
		return 2;
	}
	// 接続先ソケットがクローズされた
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
	// タイムアウト
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

	// データを適切なサイズの領域にコピーする
	BYTE* TmpVarDat = new BYTE[ActSize];
	memcpy((void*)TmpVarDat, (void*)Buf, ActSize);
	SetDataLength(ActSize);
	SetData(TmpVarDat);
	delete Buf;

	// 受信後ソケットをクローズする場合
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
