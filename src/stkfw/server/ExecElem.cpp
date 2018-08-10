#include "..\..\..\..\YaizuComLib\src\\stksocket\stksocket.h"
#include "ExecElem.h"
#include <windows.h>
#include <memory.h>
#include "..\..\..\..\YaizuComLib\src\\\stkthreadgui\stkthreadgui.h"
#include "..\VarController.h"
#include "..\LowDbAccess.h"
#include "..\MyMsgProc.h"
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
			ErrorLog(Id, MyMsgProc::GetMsg(MyMsgProc::STKFW_LOG_NAMESOLVEERR), ParamInt2);
			break;
		case STKSOCKET_LOG_CONNERROR:
			ErrorLog(Id, MyMsgProc::GetMsg(MyMsgProc::STKFW_LOG_CONNERROR), ParamInt2);
			break;
		case STKSOCKET_LOG_SUCCESSCSC:
			wsprintf(DummyBuf, _T("%s  <%s:%d>\r\n"),  MyMsgProc::GetMsg(MyMsgProc::STKFW_LOG_SUCCESSCSC), ParamStr1, ParamInt1);
			AddStkThreadLogWithThreadInfo(Name, DummyBuf);
			break;
		case STKSOCKET_LOG_SOCKCLOSE:
			wsprintf(DummyBuf, _T("%s  <%s:%d>\r\n"),  MyMsgProc::GetMsg(MyMsgProc::STKFW_LOG_SOCKCLOSE), ParamStr1, ParamInt1);
			AddStkThreadLogWithThreadInfo(Name, DummyBuf);
			break;
		case STKSOCKET_LOG_BINDLISTENERR:
			ErrorLog(Id, MyMsgProc::GetMsg(MyMsgProc::STKFW_LOG_BINDLISTENERR), ParamInt2);
			break;
		case STKSOCKET_LOG_SUCCESSCSBNLS:
			wsprintf(DummyBuf, _T("%s  <%s:%d>\r\n"),  MyMsgProc::GetMsg(MyMsgProc::STKFW_LOG_SUCCESSCSBNLS), ParamStr1, ParamInt1);
			AddStkThreadLogWithThreadInfo(Name, DummyBuf);
			break;
		case STKSOCKET_LOG_CLOSEACCEPTSOCK:
			wsprintf(DummyBuf, _T("%s  <%s:%d>\r\n"),  MyMsgProc::GetMsg(MyMsgProc::STKFW_LOG_CLOSEACCEPTSOCK), ParamStr1, ParamInt1);
			AddStkThreadLogWithThreadInfo(Name, DummyBuf);
			break;
		case STKSOCKET_LOG_CREATEACCEPTSOCK:
			wsprintf(DummyBuf, _T("%s  <%s:%d>\r\n"),  MyMsgProc::GetMsg(MyMsgProc::STKFW_LOG_CREATEACCEPTSOCK), ParamStr1, ParamInt1);
			AddStkThreadLogWithThreadInfo(Name, DummyBuf);
			break;
		case STKSOCKET_LOG_ACPTRECV:
			SendReceiveLog(Id, ParamInt1, MyMsgProc::GetMsg(MyMsgProc::STKFW_LOG_ACPTRECV));
			break;
		case STKSOCKET_LOG_CNCTRECV:
			SendReceiveLog(Id, ParamInt1, MyMsgProc::GetMsg(MyMsgProc::STKFW_LOG_ACPTRECV));
			break;
		case STKSOCKET_LOG_RECVERROR:
			ErrorLog(Id, MyMsgProc::GetMsg(MyMsgProc::STKFW_LOG_RECVERROR), ParamInt2);
			break;
		case STKSOCKET_LOG_SENDERROR:
			ErrorLog(Id, MyMsgProc::GetMsg(MyMsgProc::STKFW_LOG_SENDERROR), ParamInt2);
			break;
		case STKSOCKET_LOG_ACPTSEND:
			SendReceiveLog(Id, ParamInt1, MyMsgProc::GetMsg(MyMsgProc::STKFW_LOG_ACPTSEND));
			break;
		case STKSOCKET_LOG_CNCTSEND:
			SendReceiveLog(Id, ParamInt1, MyMsgProc::GetMsg(MyMsgProc::STKFW_LOG_CNCTSEND));
			break;
		case STKSOCKET_LOG_CLOSEACCLISNSOCK:
			wsprintf(DummyBuf, _T("%s  <%s:%d>\r\n"),  MyMsgProc::GetMsg(MyMsgProc::STKFW_LOG_CLOSELISTENACCEPTSOCK), ParamStr1, ParamInt1);
			AddStkThreadLogWithThreadInfo(Name, DummyBuf);
			break;
		case STKSOCKET_LOG_UDPRECV:
			SendReceiveLog(Id, ParamInt1, MyMsgProc::GetMsg(MyMsgProc::STKFW_LOG_UDPRECV));
			break;
		case STKSOCKET_LOG_UDPSEND:
			SendReceiveLog(Id, ParamInt1, MyMsgProc::GetMsg(MyMsgProc::STKFW_LOG_UDPSEND));
			break;
		case STKSOCKET_LOG_SUCCESSCSBN:
			wsprintf(DummyBuf, _T("%s  <%s:%d> Max-message-length=%d\r\n"),  MyMsgProc::GetMsg(MyMsgProc::STKFW_LOG_SUCCESSCSBN), ParamStr1, ParamInt1, ParamInt2);
			AddStkThreadLogWithThreadInfo(Name, DummyBuf);
			break;
		case STKSOCKET_LOG_SUCCESSCS:
			wsprintf(DummyBuf, _T("%s  <%s:%d>\r\n"),  MyMsgProc::GetMsg(MyMsgProc::STKFW_LOG_SUCCESSCS), ParamStr1, ParamInt1);
			AddStkThreadLogWithThreadInfo(Name, DummyBuf);
			break;
		case STKSOCKET_LOG_UDPSOCKCLOSE:
			wsprintf(DummyBuf, _T("%s  <%s:%d>\r\n"),  MyMsgProc::GetMsg(MyMsgProc::STKFW_LOG_UDPSOCKCLOSE), ParamStr1, ParamInt1);
			AddStkThreadLogWithThreadInfo(Name, DummyBuf);
			break;
		case STKSOCKET_LOG_BINDERR:
			ErrorLog(Id, MyMsgProc::GetMsg(MyMsgProc::STKFW_LOG_BINDERR), ParamInt2);
			break;
		default:
			wsprintf(DummyBuf, _T("%s Msg=%d\r\n"),  MyMsgProc::GetMsg(MyMsgProc::COMMON_UNKNOWN), Msg);
			AddStkThreadLogWithThreadInfo(MyMsgProc::GetMsg(MyMsgProc::COMMON_UNKNOWN), DummyBuf);
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
	if (Type == CHECKFLAG) {
		ExecElem_CheckFlag* NewExecElem = new ExecElem_CheckFlag(Id);
		NewExecElem->SetType(Type);
		return (ExecElem*)NewExecElem;
	} if (Type == CHECKDATA) {
		ExecElem_CheckData* NewExecElem = new ExecElem_CheckData(Id);
		NewExecElem->SetType(Type);
		return (ExecElem*)NewExecElem;
	} else if (Type == CHANGEFLAG) {
		ExecElem_ChangeFlag* NewExecElem = new ExecElem_ChangeFlag(Id);
		NewExecElem->SetType(Type);
		return (ExecElem*)NewExecElem;
	} else if (Type == CHANGEDATA) {
		ExecElem_ChangeData* NewExecElem = new ExecElem_ChangeData(Id);
		NewExecElem->SetType(Type);
		return (ExecElem*)NewExecElem;
	}  else if (Type == RECEIVER) {
		ExecElem_Receiver* NewExecElem = new ExecElem_Receiver(Id);
		NewExecElem->SetType(Type);
		return (ExecElem*)NewExecElem;
	} else if (Type == RECEIVERUDP) {
		ExecElem_ReceiverUdp* NewExecElem = new ExecElem_ReceiverUdp(Id);
		NewExecElem->SetType(Type);
		return (ExecElem*)NewExecElem;
	} else if (Type == LOADDATA) {
		ExecElem_LoadData* NewExecElem = new ExecElem_LoadData(Id);
		NewExecElem->SetType(Type);
		return (ExecElem*)NewExecElem;
	} else if (Type == SENDER_R || Type == SENDER) {
		ExecElem_Sender* NewExecElem = new ExecElem_Sender(Id);
		NewExecElem->SetType(Type);
		return (ExecElem*)NewExecElem;
	} else if (Type == SENDERUDP_R || Type == SENDERUDP) {
		ExecElem_SenderUdp* NewExecElem = new ExecElem_SenderUdp(Id);
		NewExecElem->SetType(Type);
		return (ExecElem*)NewExecElem;
	} else if (Type == STOREDATA_R || Type == STOREDATA) {
		ExecElem_StoreData* NewExecElem = new ExecElem_StoreData(Id);
		NewExecElem->SetType(Type);
		return (ExecElem*)NewExecElem;
	} else if (Type == READFILE) {
		ExecElem_ReadFile* NewExecElem = new ExecElem_ReadFile(Id);
		NewExecElem->SetType(Type);
		return (ExecElem*)NewExecElem;
	} else if (Type == WRITEFILE) {
		ExecElem_WriteFile* NewExecElem = new ExecElem_WriteFile(Id);
		NewExecElem->SetType(Type);
		return (ExecElem*)NewExecElem;
	} else if (Type == CLOSESOCKET) {
		ExecElem_CloseSocket* NewExecElem = new ExecElem_CloseSocket(Id);
		NewExecElem->SetType(Type);
		return (ExecElem*)NewExecElem;
	} else if (Type == TIMER) {
		ExecElem_Timer* NewExecElem = new ExecElem_Timer(Id);
		NewExecElem->SetType(Type);
		return (ExecElem*)NewExecElem;
	} else {
		ExecElem* NewExecElem = new ExecElem(Id);
		NewExecElem->SetType(Type);
		return NewExecElem;
	}
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

// Mapper
int ExecElem::Type17Execution()
{
	BYTE* InputDat = (BYTE*)GetData();
	int InputDatLength = GetDataLength();
	if (InputDat == NULL || InputDatLength == 0) {
		return 2;
	}

	TCHAR SearchVarName[256];
	TCHAR ReplaceVarName[256];
	TCHAR SearchPrefixName[32];
	TCHAR ReplacePrefixName[32];
	int Counter = LowDbAccess::GetInstance()->GetElementInfoParamInt(ElementId, 1);
	int ChkUseOnce = LowDbAccess::GetInstance()->GetElementInfoParamInt(ElementId, 2);
	LowDbAccess::GetInstance()->GetElementInfoParamStr(ElementId, SearchPrefixName, 1);
	LowDbAccess::GetInstance()->GetElementInfoParamStr(ElementId, ReplacePrefixName, 2);
	BYTE TmpDat[4096];
	INT16* TmpDatInt = (INT16*)TmpDat;

	while (TRUE) {
		if (Counter < 0 || Counter > 99999) {
			Counter = 0;
		}
		wsprintf(SearchVarName, _T("%s%05d"), SearchPrefixName, Counter);
		wsprintf(ReplaceVarName, _T("%s%05d"), ReplacePrefixName, Counter);
		int SearchVarId = VarCon_GetCommunicationVariableId(SearchVarName);
		int ReplaceVarId = VarCon_GetCommunicationVariableId(ReplaceVarName);
		if (SearchVarId == -1 || ReplaceVarId == -1) {
			return 2;
		}

		// もしUse Only Onceオプションが設定されていたら
		int TailOfTmpDatInt = 0;
		if (ChkUseOnce == 1) {
			LowDbAccess::GetInstance()->GetElementInfoBin(ElementId, TmpDat);
			BOOL FndFlag = FALSE;
			for (TailOfTmpDatInt = 0; TailOfTmpDatInt < 2048; TailOfTmpDatInt++) {
				INT16 UsedId = (INT16)TmpDatInt[TailOfTmpDatInt];
				if (UsedId == (INT16)Counter) {
					FndFlag = TRUE;
					break;
				}
				if (UsedId == (INT16)-1) {
					break;
				}
			}
			if (FndFlag == TRUE) {
				Counter++;
				continue;
			}
		}

		BYTE* SearchVarDat;
		BYTE* ReplaceVarDat;
		int SearchVarDatSize = VarCon_GetCommunicationVariableSize(SearchVarId);
		int ReplaceVarDatSize = VarCon_GetCommunicationVariableSize(ReplaceVarId);
		if (SearchVarDatSize != -1 && ReplaceVarDatSize != -1) {
			SearchVarDat = new BYTE[SearchVarDatSize];
			VarCon_GetCommunicationVariable(SearchVarId, SearchVarDat, SearchVarDatSize);

			if (memcmp(InputDat, SearchVarDat, SearchVarDatSize) == 0) {
				ReplaceVarDat = new BYTE[ReplaceVarDatSize];
				VarCon_GetCommunicationVariable(ReplaceVarId, ReplaceVarDat, ReplaceVarDatSize);

				delete InputDat;
				delete SearchVarDat;
				SetData((void*)ReplaceVarDat);
				SetDataLength(ReplaceVarDatSize);
				// もしUse Only Onceオプションが設定されていたら
				if (ChkUseOnce == 1) {
					TmpDatInt[TailOfTmpDatInt] = (INT16)Counter;
					LowDbAccess::GetInstance()->SetElementInfoBin(ElementId, TmpDat);
				}
				return 0;
			}
			delete SearchVarDat;
		}
		Counter++;
	}
	return 0;
}

// Execute program
int ExecElem::Type20Execution()
{
	// Acquire input data
	BYTE* InputDat = (BYTE*)GetData();
	int InputDatLength = GetDataLength();
	// Acquire path for the external program
	TCHAR BufPath[256];
	LowDbAccess::GetInstance()->GetElementInfoParamStr(ElementId, BufPath, 1);
	// Acquire current folder for the external program
	TCHAR BufCurr[256];
	LowDbAccess::GetInstance()->GetElementInfoParamStr(ElementId, BufCurr, 2);
	TCHAR* SpecBufCurr = BufCurr;
	if (lstrlen(BufCurr) == 0) {
		SpecBufCurr = (TCHAR*)NULL;
	}
	// Acquire "WAIT FLAG"
	int ExecType = LowDbAccess::GetInstance()->GetElementInfoParamInt(ElementId, 1);

	// Wait for the command completion
	if (ExecType & 0x00000001 && ExeProcInfo.dwProcessId != NULL) {
		DWORD RetCode;
		GetExitCodeProcess(ExeProcInfo.hProcess, &RetCode);
		if (RetCode == STILL_ACTIVE) {
			return 2;
		} else {
			// Pass the output data of the external program to next element
			BYTE* StdoutBuf = NULL;
			DWORD SizeBuf = 0;
			if (ExecType & 0x00000002) {

				FlushFileBuffers(StdOutD);

				LARGE_INTEGER StdoutSize;
				GetFileSizeEx(StdOutD, &StdoutSize);
				if (StdoutSize.QuadPart == 0) {
					CloseHandle(StdOutD);
					ExeProcInfo.dwProcessId = NULL;
					delete InputDat;
					SetData(NULL);
					SetDataLength(0);
					return 0;
				}

				StdoutBuf = new BYTE[10000000];
				ReadFile(StdOutD, StdoutBuf, 10000000, &SizeBuf, NULL);
				if (SizeBuf >= 10000000) {
					CloseHandle(StdOutD);
					ExeProcInfo.dwProcessId = NULL;
					delete InputDat;
					delete StdoutBuf;
					SetData(NULL);
					SetDataLength(0);
					return 0;
				}

				BYTE* TmpStdoutBuf = new BYTE[SizeBuf];
				memcpy(TmpStdoutBuf, StdoutBuf, SizeBuf);
				delete StdoutBuf;
				StdoutBuf = TmpStdoutBuf;
			}
			delete InputDat;
			SetData((void*)StdoutBuf);
			SetDataLength(SizeBuf);
			CloseHandle(StdOutD);
			ExeProcInfo.dwProcessId = NULL;
			return 0;
		}
	}

	// Setting input/output for the target program
	HANDLE StdOutR, StdOutW;
	HANDLE StdInR,  StdInW;
	HANDLE ParentProc = GetCurrentProcess();
	// Security setting for pipe
	SECURITY_ATTRIBUTES sa;
	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	sa.bInheritHandle = TRUE;
	sa.lpSecurityDescriptor = NULL;
	// creating pipes
	CreatePipe(&StdOutR, &StdOutW, &sa, 10000000 - 1);
	DuplicateHandle(ParentProc, StdOutR, ParentProc, &StdOutD, 0, FALSE, DUPLICATE_SAME_ACCESS);
	CloseHandle(StdOutR);
	CreatePipe(&StdInR, &StdInW, &sa, 10000000 - 1);
	DuplicateHandle(ParentProc, StdInW, ParentProc, &StdInD, 0, FALSE, DUPLICATE_SAME_ACCESS);
	CloseHandle(StdInW);
	// setting startup infor
	STARTUPINFO si;
	ZeroMemory(&si,sizeof(si));
	si.cb = sizeof(si);
	si.dwFlags = STARTF_USESTDHANDLES;
	si.wShowWindow = SW_HIDE;
	si.hStdOutput = StdOutW;
	si.hStdInput = StdInR;
	// creating process
	if (CreateProcess(NULL, BufPath, NULL, NULL, TRUE, NORMAL_PRIORITY_CLASS | CREATE_NO_WINDOW, NULL, SpecBufCurr, &si, &ExeProcInfo) == 0) {
		CloseHandle(StdOutD);
		CloseHandle(StdInD);
		ExeProcInfo.dwProcessId = NULL;
		return 2;
	}

	// Pass the input data to the external program
	if (ExecType & 0x00000004) {
		DWORD SizeBuf = 0;
		WriteFile(StdInD, InputDat, InputDatLength, &SizeBuf, NULL);
		CloseHandle(StdInD);
	}

	// If the element waits for the command completion...
	if (ExecType & 0x00000001) {
		return 2;
	}

	delete InputDat;
	SetData(NULL);
	SetDataLength(0);
	CloseHandle(StdOutD);
	ExeProcInfo.dwProcessId = NULL;
	return 0;
}

// 要素の処理を実行する
// 戻り値: (0:Terminator以外の処理が正常終了, 1:Terminatorの処理が正常終了, 2:異常終了(処理を進めない))
int ExecElem::Execute()
{
	if (ElementType == 3) {
		return 0;
	}
	if (ElementType == 6) {
		return 1;
	}
	if (ElementType == 9) {
		return 0;
	}
	if (ElementType == 17) { // Mapper
		return Type17Execution();
	}
	if (ElementType == 20) { // Execute program
		return Type20Execution();
	}

	return 0;
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
