#include "..\..\..\..\YaizuComLib\src\\stksocket\stksocket.h"
#include <windows.h>
#include <memory.h>
#include <mutex>
#include <shared_mutex>
#include <cwchar>
#include <ctime>
#include "VarController.h"
#include "LowDbAccess.h"
#include "ServerMsg.h"
#include "ExecElem.h"
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
#include "ExecElem_HttpHeader.h"
#include "ExecElem_NothingToDo.h"

// Logging functions
wchar_t *ExecElem::log;
std::mutex ExecElem::log_mutex;
int ExecElem::max_log_size;
int ExecElem::log_update_version;
std::once_flag ExecElem::init_log_flag;

// Lock management
std::mutex ExecElem::LockMutex;
ExecElem::LockMgr ExecElem::LockMgrImpl[MAXNUM_LOCK];
int ExecElem::LockMgrCount = 0;

ExecElem::LockMgr* ExecElem::GetLockMgr(int Target)
{
	LockMutex.lock();
	for (int Loop = 0; Loop < LockMgrCount; Loop++) {
		if (Target == LockMgrImpl[Loop].LockTarget) {
			LockMutex.unlock();
			return &LockMgrImpl[Loop];
		}
	}
	LockMutex.unlock();
	return NULL;
}

void ExecElem::LockShared(int Target)
{
	LockMutex.lock();
	for (int Loop = 0; Loop < LockMgrCount; Loop++) {
		if (Target == LockMgrImpl[Loop].LockTarget) {
			LockMgrImpl[Loop].LockObj.lock_shared();
			LockMutex.unlock();
			return;
		}
	}
	LockMgrImpl[LockMgrCount].LockTarget = Target;
	LockMgrImpl[LockMgrCount].LockObj.lock_shared();
	LockMgrCount++;
	LockMutex.unlock();
}

void ExecElem::UnlockShared(int Target)
{
	LockMutex.lock();
	for (int Loop = 0; Loop < LockMgrCount; Loop++) {
		if (Target == LockMgrImpl[Loop].LockTarget) {
			LockMgrImpl[Loop].LockObj.unlock_shared();
			LockMutex.unlock();
			return;
		}
	}
	LockMutex.unlock();
}

bool ExecElem::TryLockShared(int Target)
{
	LockMutex.lock();
	for (int Loop = 0; Loop < LockMgrCount; Loop++) {
		if (Target == LockMgrImpl[Loop].LockTarget) {
			bool Flag = LockMgrImpl[Loop].LockObj.try_lock_shared();
			LockMutex.unlock();
			return Flag;
		}
	}
	LockMgrImpl[LockMgrCount].LockTarget = Target;
	bool Flag = LockMgrImpl[LockMgrCount].LockObj.try_lock_shared();
	LockMgrCount++;
	LockMutex.unlock();
	return Flag;
}

void ExecElem::Lock(int Target)
{
	LockMutex.lock();
	for (int Loop = 0; Loop < LockMgrCount; Loop++) {
		if (Target == LockMgrImpl[Loop].LockTarget) {
			LockMgrImpl[Loop].LockObj.lock();
			LockMutex.unlock();
			return;
		}
	}
	LockMgrImpl[LockMgrCount].LockTarget = Target;
	LockMgrImpl[LockMgrCount].LockObj.lock();
	LockMgrCount++;
	LockMutex.unlock();
}

void ExecElem::Unlock(int Target)
{
	LockMutex.lock();
	for (int Loop = 0; Loop < LockMgrCount; Loop++) {
		if (Target == LockMgrImpl[Loop].LockTarget) {
			LockMgrImpl[Loop].LockObj.unlock();
			LockMutex.unlock();
			return;
		}
	}
	LockMutex.unlock();
}

bool ExecElem::TryLock(int Target)
{
	LockMutex.lock();
	for (int Loop = 0; Loop < LockMgrCount; Loop++) {
		if (Target == LockMgrImpl[Loop].LockTarget) {
			bool Flag = LockMgrImpl[Loop].LockObj.try_lock();
			LockMutex.unlock();
			return Flag;
		}
	}
	LockMgrImpl[LockMgrCount].LockTarget = Target;
	bool Flag = LockMgrImpl[LockMgrCount].LockObj.try_lock();
	LockMgrCount++;
	LockMutex.unlock();
	return Flag;
}

void ExecElem::init_log()
{
	max_log_size = 1000;
	log = new wchar_t[max_log_size];
	log[0] = L'\0';
	log_update_version = 0;
}

void ExecElem::add_log(const wchar_t* name, const wchar_t* msg)
{
	std::call_once(init_log_flag, &init_log);

	log_mutex.lock();

	int tmp_buf_len = max_log_size + (int)wcslen(msg) + 100;
	wchar_t *tmp_buf = new TCHAR[tmp_buf_len];

	time_t now;
	tm local_now;
	time(&now);
	localtime_s(&local_now, &now);
	if (name) {
		swprintf(tmp_buf, tmp_buf_len, L"%02d:%02d:%02d [%s]  %s", local_now.tm_hour, local_now.tm_min, local_now.tm_sec, name, msg);
	} else {
		wcscpy_s(tmp_buf, tmp_buf_len, msg);
	}
	wcscat_s(tmp_buf, tmp_buf_len, log);
	wcsncpy_s(log, max_log_size, tmp_buf, _TRUNCATE);
	delete tmp_buf;

	log_update_version++;

	log_mutex.unlock();
}

void ExecElem::clear_log()
{
	std::call_once(init_log_flag, &init_log);

	log_mutex.lock();
	log[0] = L'\0';
	log_update_version = 0;
	log_mutex.unlock();
}

void ExecElem::get_log(wchar_t* log_data, const int log_data_len)
{
	std::call_once(init_log_flag, &init_log);

	wcsncpy_s(log_data, log_data_len, log, _TRUNCATE);
	return;

}

int ExecElem::get_log_size()
{
	std::call_once(init_log_flag, &init_log);

	return (int)wcslen(log);
}

int ExecElem::get_max_log_size()
{
	std::call_once(init_log_flag, &init_log);

	return max_log_size;
}

void ExecElem::change_size(const int size)
{
	std::call_once(init_log_flag, &init_log);

	log_mutex.lock();
	if (size < 100) {
		max_log_size = 100;
	} else {
		max_log_size = size;
	}
	delete [] log;
	log = new wchar_t[max_log_size];
	log[0] = L'\0';
	log_update_version = 0;
	log_mutex.unlock();
}

void ExecElem::ErrorLog(int LogId, TCHAR* Msg, int Error)
{
	TCHAR Name[32];
	LowDbAccess::GetInstance()->GetViewElementNameFromId(LogId, Name);
	TCHAR DummyBuf[128];
	wsprintf(DummyBuf, _T("*** Error *** %s (%d)\r\n"), Msg, Error);
	add_log(Name, DummyBuf);
}

void ExecElem::SendReceiveLog(int LogId, int Size, TCHAR* Msg)
{
	TCHAR Name[32];
	LowDbAccess::GetInstance()->GetViewElementNameFromId(LogId, Name);
	TCHAR DummyBuf[128];
	wsprintf(DummyBuf, _T("%s  <%d bytes>\r\n"), Msg, Size);
	add_log(Name, DummyBuf);
}

void ExecElem::StkPropOutputLog()
{
	int Msg;
	int Id;
	int ParamInt1, ParamInt2;
	TCHAR ParamStr1[256], ParamStr2[256];

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
			add_log(Name, DummyBuf);
			break;
		case STKSOCKET_LOG_SOCKCLOSE:
			wsprintf(DummyBuf, _T("%s  <%s:%d>\r\n"),  ServerMsg::GetMsg(ServerMsg::STKFW_LOG_SOCKCLOSE), ParamStr1, ParamInt1);
			add_log(Name, DummyBuf);
			break;
		case STKSOCKET_LOG_BINDLISTENERR:
			ErrorLog(Id, ServerMsg::GetMsg(ServerMsg::STKFW_LOG_BINDLISTENERR), ParamInt2);
			break;
		case STKSOCKET_LOG_SUCCESSCSBNLS:
			wsprintf(DummyBuf, _T("%s  <%s:%d>\r\n"),  ServerMsg::GetMsg(ServerMsg::STKFW_LOG_SUCCESSCSBNLS), ParamStr1, ParamInt1);
			add_log(Name, DummyBuf);
			break;
		case STKSOCKET_LOG_CLOSEACCEPTSOCK:
			wsprintf(DummyBuf, _T("%s  <%s:%d>\r\n"),  ServerMsg::GetMsg(ServerMsg::STKFW_LOG_CLOSEACCEPTSOCK), ParamStr1, ParamInt1);
			add_log(Name, DummyBuf);
			break;
		case STKSOCKET_LOG_CREATEACCEPTSOCK:
			wsprintf(DummyBuf, _T("%s  <%s:%d>\r\n"),  ServerMsg::GetMsg(ServerMsg::STKFW_LOG_CREATEACCEPTSOCK), ParamStr1, ParamInt1);
			add_log(Name, DummyBuf);
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
			add_log(Name, DummyBuf);
			break;
		case STKSOCKET_LOG_UDPRECV:
			SendReceiveLog(Id, ParamInt1, ServerMsg::GetMsg(ServerMsg::STKFW_LOG_UDPRECV));
			break;
		case STKSOCKET_LOG_UDPSEND:
			SendReceiveLog(Id, ParamInt1, ServerMsg::GetMsg(ServerMsg::STKFW_LOG_UDPSEND));
			break;
		case STKSOCKET_LOG_SUCCESSCSBN:
			wsprintf(DummyBuf, _T("%s  <%s:%d> Max-message-length=%d\r\n"),  ServerMsg::GetMsg(ServerMsg::STKFW_LOG_SUCCESSCSBN), ParamStr1, ParamInt1, ParamInt2);
			add_log(Name, DummyBuf);
			break;
		case STKSOCKET_LOG_SUCCESSCS:
			wsprintf(DummyBuf, _T("%s  <%s:%d>\r\n"), ServerMsg::GetMsg(ServerMsg::STKFW_LOG_SUCCESSCS), ParamStr1, ParamInt1);
			add_log(Name, DummyBuf);
			break;
		case STKSOCKET_LOG_UDPSOCKCLOSE:
			wsprintf(DummyBuf, _T("%s  <%s:%d>\r\n"), ServerMsg::GetMsg(ServerMsg::STKFW_LOG_UDPSOCKCLOSE), ParamStr1, ParamInt1);
			add_log(Name, DummyBuf);
			break;
		case STKSOCKET_LOG_BINDERR:
			ErrorLog(Id, ServerMsg::GetMsg(ServerMsg::STKFW_LOG_BINDERR), ParamInt2);
			break;
		case STKSOCKET_LOG_PRIVATEKEY:
			wsprintf(DummyBuf, _T("%s %s \"%s\"\r\n"), ServerMsg::GetMsg(ServerMsg::STKFW_LOG_PRIVATEKEYLOAD), (ParamInt1 == 0) ? L"Success" : L"Failure", ParamStr1);
			add_log(Name, DummyBuf);
			break;
		case STKSOCKET_LOG_SERVERCERT:
			wsprintf(DummyBuf, _T("%s %s \"%s\"\r\n"), ServerMsg::GetMsg(ServerMsg::STKFW_LOG_SERVERCERTLOAD), (ParamInt1 == 0) ? L"Success" : L"Failure", ParamStr1);
			add_log(Name, DummyBuf);
			break;
		case STKSOCKET_LOG_CACERT:
			wsprintf(DummyBuf, _T("%s %s \"%s\"\r\n"), ServerMsg::GetMsg(ServerMsg::STKFW_LOG_CACERTLOAD), (ParamInt1 == 0) ? L"Success" : L"Failure", ParamStr1);
			add_log(Name, DummyBuf);
			break;
		default:
			wsprintf(DummyBuf, _T("%s Msg=%d\r\n"),  ServerMsg::GetMsg(ServerMsg::STKFW_LOG_UNKNOWN), Msg);
			add_log(Name, DummyBuf);
			break;
		}
	}
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
	} else if (Type == CHECKDATA) {
		NewExecElem = new ExecElem_CheckData(Id);
	} else if (Type == CHANGEFLAG) {
		NewExecElem = new ExecElem_ChangeFlag(Id);
	} else if (Type == CHANGEDATA) {
		NewExecElem = new ExecElem_ChangeData(Id);
	} else if (Type == RECEIVER) {
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
	} else if (Type == HTTPHEADER) {
		NewExecElem = new ExecElem_HttpHeader(Id);
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
}

// Thread status was changed into "Stop"
void ExecElem::ThreadStatusChangedIntoStop()
{
	StkSocket_ForceStop(ElementId);
}
