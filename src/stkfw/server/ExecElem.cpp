#include "..\..\..\..\YaizuComLib\src\\stksocket\stksocket.h"
#include "ExecElem.h"
#include <windows.h>
#include <memory.h>
#include "..\..\..\..\YaizuComLib\src\\\stkthreadgui\stkthreadgui.h"
#include "VarController.h"
#include "LowDbAccess.h"
#include "ServerMsg.h"
#include "ExecElem_CheckFlag.h"
#include "ExecElem_CheckData.h"
#include "ExecElem_ChangeFlag.h"
#include "ExecElem_ChangeData.h"
#include "ExecElem_StoreData.h"
#include "ExecElem_LoadData.h"
#include "ExecElem_Receiver.h"
#include "ExecElem_ReceiverUdp.h"
#include "ExecElem_Sender.h"
#include "ExecElem_SenderUdp.h"
#include "ExecElem_ReadFile.h"
#include "ExecElem_WriteFile.h"
#include "ExecElem_CloseSocket.h"
#include "ExecElem_Timer.h"
#include "ExecElem_Mapper.h"
#include "ExecElem_ExecProg.h"
#include "ExecElem_NothingToDo.h"

void ExecElem::ErrorLog(int LogId, TCHAR* Msg, int Error)
{
	TCHAR Name[32];
	LowDbAccess::GetInstance()->GetViewElementNameFromId(LogId, Name);
	TCHAR DummyBuf[128];
	wsprintf(DummyBuf, _T("*** Error *** %s (%d)\r\n"), Msg, Error);
	AddStkThreadLogWithThreadInfo(Name, DummyBuf);
}

void ExecElem::SendReceiveLog(int LogId, int Size, TCHAR* Msg)
{
	TCHAR Name[32];
	LowDbAccess::GetInstance()->GetViewElementNameFromId(LogId, Name);
	TCHAR DummyBuf[128];
	wsprintf(DummyBuf, _T("%s  <%d bytes>\r\n"), Msg, Size);
	AddStkThreadLogWithThreadInfo(Name, DummyBuf);
}

void ExecElem::StkPropOutputLog()
{
	int Msg;
	int Id;
	int ParamInt1, ParamInt2;
	TCHAR ParamStr1[256], ParamStr2[256];
	static BOOL BlkFlag = FALSE;

	for (; BlkFlag == TRUE;); // Wait for BlkFlag == FALSE;
	BlkFlag = TRUE;

	int NumOfLogs = StkSocket_GetNumOfLogs();
	for (int Loop = 0; Loop < NumOfLogs; Loop++) {
		StkSocket_TakeFirstLog(&Msg, &Id, ParamStr1, ParamStr2, &ParamInt1, &ParamInt2);
		if (Msg == 0) {
			continue;
		}
		TCHAR Name[32];
		LowDbAccess::GetInstance()->GetViewElementNameFromId(Id, Name);
		TCHAR DummyBuf[128];
		switch (Msg) {
		case STKSOCKET_LOG_NAMESOLVEERR:
			ErrorLog(Id, ServerMsg::GetMsg(ServerMsg::STKFW_LOG_NAMESOLVEERR), ParamInt2);
			break;
		case STKSOCKET_LOG_CONNERROR:
			ErrorLog(Id, ServerMsg::GetMsg(ServerMsg::STKFW_LOG_CONNERROR), ParamInt2);
			break;
		case STKSOCKET_LOG_SUCCESSCSC:
			wsprintf(DummyBuf, _T("%s  <%s:%d>\r\n"),  ServerMsg::GetMsg(ServerMsg::STKFW_LOG_SUCCESSCSC), ParamStr1, ParamInt1);
			AddStkThreadLogWithThreadInfo(Name, DummyBuf);
			break;
		case STKSOCKET_LOG_SOCKCLOSE:
			wsprintf(DummyBuf, _T("%s  <%s:%d>\r\n"),  ServerMsg::GetMsg(ServerMsg::STKFW_LOG_SOCKCLOSE), ParamStr1, ParamInt1);
			AddStkThreadLogWithThreadInfo(Name, DummyBuf);
			break;
		case STKSOCKET_LOG_BINDLISTENERR:
			ErrorLog(Id, ServerMsg::GetMsg(ServerMsg::STKFW_LOG_BINDLISTENERR), ParamInt2);
			break;
		case STKSOCKET_LOG_SUCCESSCSBNLS:
			wsprintf(DummyBuf, _T("%s  <%s:%d>\r\n"),  ServerMsg::GetMsg(ServerMsg::STKFW_LOG_SUCCESSCSBNLS), ParamStr1, ParamInt1);
			AddStkThreadLogWithThreadInfo(Name, DummyBuf);
			break;
		case STKSOCKET_LOG_CLOSEACCEPTSOCK:
			wsprintf(DummyBuf, _T("%s  <%s:%d>\r\n"),  ServerMsg::GetMsg(ServerMsg::STKFW_LOG_CLOSEACCEPTSOCK), ParamStr1, ParamInt1);
			AddStkThreadLogWithThreadInfo(Name, DummyBuf);
			break;
		case STKSOCKET_LOG_CREATEACCEPTSOCK:
			wsprintf(DummyBuf, _T("%s  <%s:%d>\r\n"),  ServerMsg::GetMsg(ServerMsg::STKFW_LOG_CREATEACCEPTSOCK), ParamStr1, ParamInt1);
			AddStkThreadLogWithThreadInfo(Name, DummyBuf);
			break;
		case STKSOCKET_LOG_ACPTRECV:
			SendReceiveLog(Id, ParamInt1, ServerMsg::GetMsg(ServerMsg::STKFW_LOG_ACPTRECV));
			break;
		case STKSOCKET_LOG_CNCTRECV:
			SendReceiveLog(Id, ParamInt1, ServerMsg::GetMsg(ServerMsg::STKFW_LOG_ACPTRECV));
			break;
		case STKSOCKET_LOG_RECVERROR:
			ErrorLog(Id, ServerMsg::GetMsg(ServerMsg::STKFW_LOG_RECVERROR), ParamInt2);
			break;
		case STKSOCKET_LOG_SENDERROR:
			ErrorLog(Id, ServerMsg::GetMsg(ServerMsg::STKFW_LOG_SENDERROR), ParamInt2);
			break;
		case STKSOCKET_LOG_ACPTSEND:
			SendReceiveLog(Id, ParamInt1, ServerMsg::GetMsg(ServerMsg::STKFW_LOG_ACPTSEND));
			break;
		case STKSOCKET_LOG_CNCTSEND:
			SendReceiveLog(Id, ParamInt1, ServerMsg::GetMsg(ServerMsg::STKFW_LOG_CNCTSEND));
			break;
		case STKSOCKET_LOG_CLOSEACCLISNSOCK:
			wsprintf(DummyBuf, _T("%s  <%s:%d>\r\n"),  ServerMsg::GetMsg(ServerMsg::STKFW_LOG_CLOSELISTENACCEPTSOCK), ParamStr1, ParamInt1);
			AddStkThreadLogWithThreadInfo(Name, DummyBuf);
			break;
		case STKSOCKET_LOG_UDPRECV:
			SendReceiveLog(Id, ParamInt1, ServerMsg::GetMsg(ServerMsg::STKFW_LOG_UDPRECV));
			break;
		case STKSOCKET_LOG_UDPSEND:
			SendReceiveLog(Id, ParamInt1, ServerMsg::GetMsg(ServerMsg::STKFW_LOG_UDPSEND));
			break;
		case STKSOCKET_LOG_SUCCESSCSBN:
			wsprintf(DummyBuf, _T("%s  <%s:%d> Max-message-length=%d\r\n"),  ServerMsg::GetMsg(ServerMsg::STKFW_LOG_SUCCESSCSBN), ParamStr1, ParamInt1, ParamInt2);
			AddStkThreadLogWithThreadInfo(Name, DummyBuf);
			break;
		case STKSOCKET_LOG_SUCCESSCS:
			wsprintf(DummyBuf, _T("%s  <%s:%d>\r\n"),  ServerMsg::GetMsg(ServerMsg::STKFW_LOG_SUCCESSCS), ParamStr1, ParamInt1);
			AddStkThreadLogWithThreadInfo(Name, DummyBuf);
			break;
		case STKSOCKET_LOG_UDPSOCKCLOSE:
			wsprintf(DummyBuf, _T("%s  <%s:%d>\r\n"),  ServerMsg::GetMsg(ServerMsg::STKFW_LOG_UDPSOCKCLOSE), ParamStr1, ParamInt1);
			AddStkThreadLogWithThreadInfo(Name, DummyBuf);
			break;
		case STKSOCKET_LOG_BINDERR:
			ErrorLog(Id, ServerMsg::GetMsg(ServerMsg::STKFW_LOG_BINDERR), ParamInt2);
			break;
		default:
			wsprintf(DummyBuf, _T("%s Msg=%d\r\n"),  ServerMsg::GetMsg(ServerMsg::STKFW_LOG_UNKNOWN), Msg);
			AddStkThreadLogWithThreadInfo(ServerMsg::GetMsg(ServerMsg::STKFW_LOG_UNKNOWN), DummyBuf);
			break;
		}
	}
	BlkFlag = FALSE;
}

// Constructor
ExecElem::ExecElem(int Id)
{
	ElementId = Id;
	Status = STATUS_NOTINSCOPE;
	WaitForExecId = -1;
	RootId = -1;
	Data = NULL;
	DataLength = 0;
	StartStopFlag = FALSE;
}

// Destructor
ExecElem::~ExecElem()
{
}

// Create ExecElem instance
// Id [in] : ID of newly created ExecElem
// Type [in] : Type of newly created ExecElem
ExecElem* ExecElem::CreateExecElem(int Id, int Type)
{
	ExecElem* NewExecElem = NULL;
	if (Type == CHECKFLAG) {
		NewExecElem = new ExecElem_CheckFlag(Id);
	} if (Type == CHECKDATA) {
		NewExecElem = new ExecElem_CheckData(Id);
	} else if (Type == CHANGEFLAG) {
		NewExecElem = new ExecElem_ChangeFlag(Id);
	} else if (Type == CHANGEDATA) {
		NewExecElem = new ExecElem_ChangeData(Id);
	}  else if (Type == RECEIVER) {
		NewExecElem = new ExecElem_Receiver(Id);
	} else if (Type == RECEIVERUDP) {
		NewExecElem = new ExecElem_ReceiverUdp(Id);
	} else if (Type == LOADDATA) {
		NewExecElem = new ExecElem_LoadData(Id);
	} else if (Type == SENDER_R || Type == SENDER) {
		NewExecElem = new ExecElem_Sender(Id);
	} else if (Type == SENDERUDP_R || Type == SENDERUDP) {
		NewExecElem = new ExecElem_SenderUdp(Id);
	} else if (Type == STOREDATA_R || Type == STOREDATA) {
		NewExecElem = new ExecElem_StoreData(Id);
	} else if (Type == READFILE) {
		NewExecElem = new ExecElem_ReadFile(Id);
	} else if (Type == WRITEFILE) {
		NewExecElem = new ExecElem_WriteFile(Id);
	} else if (Type == CLOSESOCKET) {
		NewExecElem = new ExecElem_CloseSocket(Id);
	} else if (Type == TIMER) {
		NewExecElem = new ExecElem_Timer(Id);
	} else if (Type == MAPPER) {
		NewExecElem = new ExecElem_Mapper(Id);
	} else if (Type == EXECPROGRAM) {
		NewExecElem = new ExecElem_ExecProg(Id);
	} else {
		NewExecElem = new ExecElem_NothingToDo(Id);
	}
	NewExecElem->SetType(Type);
	return NewExecElem;
}

// 要素の種別を取得する
int ExecElem::GetType()
{
	return ElementType;
}

// 要素の種別を設定する
void ExecElem::SetType(int Tp)
{
	ElementType = Tp;
}

// エレメントの状態を取得する
int ExecElem::GetStatus()
{
	return Status;
}

// エレメントの状態を設定する
void ExecElem::SetStatus(int St)
{
	Status = St;
}

// 実行依存Idを取得する
int ExecElem::GetWaitForExecId()
{
	return WaitForExecId;
}

// 実行依存Idを設定する
void ExecElem::SetWaitForExecId(int ExecId)
{
	WaitForExecId = ExecId;
}

// ElementIdを取得する
int ExecElem::GetElementId()
{
	return ElementId;
}

// 根となる要素のIDを取得する
int ExecElem::GetRootId()
{
	return RootId;
}

// 根となる要素のIDを設定する
void ExecElem::SetRootId(int Id)
{
	RootId = Id;
}

// データを取得する
void* ExecElem::GetData()
{
	return Data;
}

int ExecElem::GetDataLength()
{
	return DataLength;
}

// データを設定する
void ExecElem::SetData(void* Dt)
{
	Data = Dt;
}

void ExecElem::SetDataLength(int Len)
{
	DataLength = Len;
}

// Thread status was changed into "Start"
void ExecElem::ThreadStatusChangedIntoStart()
{
	StartStopFlag = TRUE;
}

// Thread status was changed into "Stop"
void ExecElem::ThreadStatusChangedIntoStop()
{
	StartStopFlag = FALSE;
}
