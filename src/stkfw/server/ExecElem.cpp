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
#include "ExecElem_Receiver.h"
#include "ExecElem_ReceiverUdp.h"
#include "ExecElem_Sender.h"
#include "ExecElem_SenderUdp.h"

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
	} else if (Type == RECEIVER) {
		ExecElem_Receiver* NewExecElem = new ExecElem_Receiver(Id);
		NewExecElem->SetType(Type);
		return (ExecElem*)NewExecElem;
	} else if (Type == RECEIVERUDP) {
		ExecElem_ReceiverUdp* NewExecElem = new ExecElem_ReceiverUdp(Id);
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
	} else {
		ExecElem* NewExecElem = new ExecElem(Id);
		NewExecElem->SetType(Type);
		return NewExecElem;
	}
}

// �v�f�̎�ʂ��擾����
int ExecElem::GetType()
{
	return ElementType;
}

// �v�f�̎�ʂ�ݒ肷��
void ExecElem::SetType(int Tp)
{
	ElementType = Tp;
}

// �G�������g�̏�Ԃ��擾����
int ExecElem::GetStatus()
{
	return Status;
}

// �G�������g�̏�Ԃ�ݒ肷��
void ExecElem::SetStatus(int St)
{
	Status = St;
}

// ���s�ˑ�Id���擾����
int ExecElem::GetWaitForExecId()
{
	return WaitForExecId;
}

// ���s�ˑ�Id��ݒ肷��
void ExecElem::SetWaitForExecId(int ExecId)
{
	WaitForExecId = ExecId;
}

// ElementId���擾����
int ExecElem::GetElementId()
{
	return ElementId;
}

// ���ƂȂ�v�f��ID���擾����
int ExecElem::GetRootId()
{
	return RootId;
}

// ���ƂȂ�v�f��ID��ݒ肷��
void ExecElem::SetRootId(int Id)
{
	RootId = Id;
}

// �f�[�^���擾����
void* ExecElem::GetData()
{
	return Data;
}

int ExecElem::GetDataLength()
{
	return DataLength;
}

// �f�[�^��ݒ肷��
void ExecElem::SetData(void* Dt)
{
	Data = Dt;
}

void ExecElem::SetDataLength(int Len)
{
	DataLength = Len;
}

// Load Data
int ExecElem::Type2Execution()
{
	int VarId;
	BYTE* VarDat = NULL;
	int VarDatSize = 0;
	// ������=0:"1�̕ϐ���������擾", 1:"�����̕ϐ���������擾"
	if (LowDbAccess::GetInstance()->GetElementInfoParamInt(ElementId, 2) == 0) {
		// �R�~���j�P�[�V�����p�ϐ���ID���擾����
		VarId = LowDbAccess::GetInstance()->GetElementInfoParamInt(ElementId, 1);
	} else {
		TCHAR TmpVarName[256];
		TCHAR TgtName[32];
		int Counter = LowDbAccess::GetInstance()->GetElementInfoParamInt(ElementId, 5);
		LowDbAccess::GetInstance()->GetElementInfoParamStr(ElementId, TmpVarName, 1);
		wsprintf(TmpVarName, _T("%s%05d"), TmpVarName, Counter);
		lstrcpyn(TgtName, TmpVarName, 32);
		VarId = VarCon_GetCommunicationVariableId(TgtName);
		if (VarId == -1) {
			SetDataLength(0);
			SetData(NULL);
			return -1;
		}
		Counter++;
		LowDbAccess::GetInstance()->SetElementInfoParamInt(ElementId, Counter, 5);
	}

	VarDatSize = VarCon_GetCommunicationVariableSize(VarId);
	if (VarDatSize != -1) {
		VarDat = new BYTE[VarDatSize];
		VarCon_GetCommunicationVariable(VarId, VarDat, VarDatSize);
	} else {
		SetDataLength(0);
		SetData(NULL);
		return -1;
	}
	SetDataLength(VarDatSize);
	SetData(VarDat); // �T�C�Y0�̃f�[�^�ł�new�����̈�̃|�C���^���w�肷��
	return 0;
}

// Store Data
void ExecElem::Type5Execution()
{
	int VarId;
	BYTE* VarDat = (BYTE*)GetData();
	int VarDatSize = GetDataLength();

	// ������=0:"1�̕ϐ��ւ̏��̐ݒ�" ,1:"�����̕ϐ��ւ̏��̐ݒ�"
	if (LowDbAccess::GetInstance()->GetElementInfoParamInt(ElementId, 2) == 0) {
		// �R�~���j�P�[�V�����p�ϐ���ID���擾����
		VarId = LowDbAccess::GetInstance()->GetElementInfoParamInt(ElementId, 1);
		// �ϐ������݂��邩�`�F�b�N����
		if (VarCon_CheckVariableExistence(VarId) == FALSE) {
			return;
		}

		// �o�^�σR�~���j�P�[�V�����ϐ��̃T�C�Y�`�F�b�N
		int CurSize = VarCon_GetCommunicationVariableSize(VarId) + 10000; // �X�V���̂�10000���Z�i���R��VarCon_CheckComm...�Q�Ɓj
		if (VarCon_CheckCommunicationVariableSize(VarDatSize - CurSize) == FALSE) {
			return;
		}
	} else {
		// �o�^�σ��R�[�h�̏���`�F�b�N
		if (VarCon_CheckVariableCount() == FALSE) {
			return;
		}

		TCHAR TmpVarName[256];
		TCHAR TgtName[32];
		TCHAR TgtDesc[64];
		int Counter = LowDbAccess::GetInstance()->GetElementInfoParamInt(ElementId, 5);
		if (Counter < 0 || Counter > 99999) {
			Counter = 0;
		}
		LowDbAccess::GetInstance()->GetElementInfoParamStr(ElementId, TmpVarName, 1);
		wsprintf(TmpVarName, _T("%s%05d"), TmpVarName, Counter);
		lstrcpyn(TgtName, TmpVarName, 32);
		lstrcpyn(TgtDesc, TmpVarName, 64);
		VarId = VarCon_GetCommunicationVariableId(TgtName);

		// �o�^�σR�~���j�P�[�V�����ϐ��̃T�C�Y�`�F�b�N
		int CurSize = 0;
		if (VarId != -1) {
			CurSize = VarCon_GetCommunicationVariableSize(VarId) + 10000; // �X�V���̂�10000���Z�i���R��VarCon_CheckComm...�Q�Ɓj
		}
		if (VarCon_CheckCommunicationVariableSize(VarDatSize - CurSize) == FALSE) {
			return;
		}

		if (VarId == -1) {
			VarId = VarCon_AddVariableRecord(TgtName, TgtDesc, 0);
		}
		Counter++;
		LowDbAccess::GetInstance()->SetElementInfoParamInt(ElementId, Counter, 5);
	}

	BYTE* TmpVarDat = new BYTE[10000000];
	memcpy((void*)TmpVarDat, (void*)VarDat, VarDatSize);
	VarCon_UpdateCommunicationVariable(VarId, TmpVarDat, VarDatSize);
	delete TmpVarDat;
}

// Timer
int ExecElem::Type12Execution()
{
	if (LowDbAccess::GetInstance()->GetElementInfoParamInt(ElementId, 4) == 0) {
		DWORD HighTm = LowDbAccess::GetInstance()->GetElementInfoParamInt(ElementId, 1);
		DWORD LowTm = LowDbAccess::GetInstance()->GetElementInfoParamInt(ElementId, 2);
		if (HighTm != 0 || LowTm != 0) {
			FILETIME LocFileTm;
			SYSTEMTIME SysTm;
			GetLocalTime(&SysTm);
			SystemTimeToFileTime(&SysTm, &LocFileTm);
			if (LocFileTm.dwHighDateTime >= HighTm && LocFileTm.dwLowDateTime >= LowTm) {
				return 0;
			} else {
				return 2;
			}
		}
		return 0;
	} else {
		DWORD WorkTm = LowDbAccess::GetInstance()->GetElementInfoParamInt(ElementId, 5);
		DWORD WaitTm = LowDbAccess::GetInstance()->GetElementInfoParamInt(ElementId, 3);
		DWORD CurrentTm = GetTickCount();
		if (WorkTm == 0) {
			int *TcInt = (int*)&CurrentTm;
			LowDbAccess::GetInstance()->SetElementInfoParamInt(ElementId, *TcInt, 5);
		} else {
			if (CurrentTm - WorkTm > (WaitTm * 1000)) {
				LowDbAccess::GetInstance()->SetElementInfoParamInt(ElementId, 0, 5);
				return 0;
			}
		}
	}
	return 2;
}

// Change data
int ExecElem::Type14Execution()
{
	BYTE* VarDatA = NULL;
	int VarDatSizeA = 0;
	BYTE* VarDatB = NULL;
	int VarDatSizeB = 0;
	BYTE* VarDatC = NULL;
	int VarDatSizeC = 0;
	BYTE* InputVarDat = (BYTE*)GetData();
	int InputVarDatSize = GetDataLength();

	int OpType = LowDbAccess::GetInstance()->GetElementInfoParamInt(ElementId, 4);
	// ��ʂ��s���̂Ƃ��́C�����������̗v�f�Ɉڍs
	if (OpType < 0 || OpType > 5) {
		return 0;
	}
	int VarIdA = LowDbAccess::GetInstance()->GetElementInfoParamInt(ElementId, 1);
	int VarIdB = LowDbAccess::GetInstance()->GetElementInfoParamInt(ElementId, 2);
	int VarIdC = LowDbAccess::GetInstance()->GetElementInfoParamInt(ElementId, 3);

	if (OpType == 0 || OpType == 1) {
		VarDatSizeA = VarCon_GetCommunicationVariableSize(VarIdA);
		if (VarDatSizeA != -1) {
			VarDatA = new BYTE[VarDatSizeA];
			VarCon_GetCommunicationVariable(VarIdA, VarDatA, VarDatSizeA);
		} else {
			// �ϐ�(A)���s���̂Ƃ��͉����������̗v�f�Ɉڂ�
			return 0;
		}
		if ((InputVarDatSize + VarDatSizeA) > 9999999) {
			delete VarDatA;
			return 0;
		}
		BYTE* NewVarDat = new BYTE[InputVarDatSize + VarDatSizeA];
		int NewVarDatSize = InputVarDatSize + VarDatSizeA;
		if (OpType == 0) {
			memcpy(NewVarDat, VarDatA, VarDatSizeA);
			memcpy(NewVarDat + VarDatSizeA, InputVarDat, InputVarDatSize);
		}
		if (OpType == 1) {
			memcpy(NewVarDat, InputVarDat, InputVarDatSize);
			memcpy(NewVarDat + InputVarDatSize, VarDatA, VarDatSizeA);
		}
		delete VarDatA;
		delete InputVarDat;
		SetData((BYTE*)NewVarDat);
		SetDataLength(InputVarDatSize + VarDatSizeA);
		return 0;
	}
	if (OpType == 2) {
		VarDatSizeA = VarCon_GetCommunicationVariableSize(VarIdA);
		VarDatSizeB = VarCon_GetCommunicationVariableSize(VarIdB);
		if (VarDatSizeA != -1 && VarDatSizeB != -1) {
			VarDatA = new BYTE[VarDatSizeA];
			VarDatB = new BYTE[VarDatSizeB];
			VarCon_GetCommunicationVariable(VarIdA, VarDatA, VarDatSizeA);
			VarCon_GetCommunicationVariable(VarIdB, VarDatB, VarDatSizeB);
		} else {
			// �ϐ�(A)�܂���(B)���s���̂Ƃ��͉����������̗v�f�Ɉڂ�
			return 0;
		}
		int DiffSize = VarDatSizeB - VarDatSizeA; // 1��̒u�������ɂ�����f�[�^�T�C�Y�̍���
		// ���̓f�[�^�ɑ��݂��錟���Ώە�����̌������߂�
		int FndCount = 0; // ���̓f�[�^�ɑ��݂��錟���Ώە�����̌�
		for (int Loop = 0; Loop < InputVarDatSize - VarDatSizeA + 1; Loop++) {
			if (memcmp(InputVarDat + Loop, VarDatA, VarDatSizeA) == 0) {
				FndCount++;
				Loop += VarDatSizeA - 1;
			}
		}

		// �o�̓f�[�^�̈�̊m��
		int NewDatSize = InputVarDatSize + DiffSize * FndCount;
		if (NewDatSize > 9999999) {
			delete VarDatA;
			delete VarDatB;
			return 0;
		}
		BYTE* NewDat = new BYTE[NewDatSize];
		
		// �u������
		BOOL LastOp = 0;
		BYTE* NewDatPtr = NewDat;
		for (int Loop = 0; Loop < InputVarDatSize - VarDatSizeA + 1; Loop++) {
			if (memcmp(InputVarDat + Loop, VarDatA, VarDatSizeA) == 0) {
				memcpy(NewDatPtr, VarDatB, VarDatSizeB);
				NewDatPtr += VarDatSizeB;
				Loop += VarDatSizeA - 1;
				LastOp = TRUE;
			} else {
				*NewDatPtr = InputVarDat[Loop];
				NewDatPtr++;
				LastOp = FALSE;
			}
		}
		if (LastOp == FALSE) {
			for (int Loop = InputVarDatSize - VarDatSizeA + 1; Loop < InputVarDatSize; Loop++) {
				*NewDatPtr = InputVarDat[Loop];
				NewDatPtr++;
			}
		}

		delete VarDatA;
		delete VarDatB;
		delete InputVarDat;
		SetData((BYTE*)NewDat);
		SetDataLength(NewDatSize);

		return 0;
	}
	if (OpType == 3) {
		BYTE* InputDat = (BYTE*)GetData();
		int InputDatSize = GetDataLength();

		VarDatSizeA = VarCon_GetCommunicationVariableSize(VarIdA);
		VarDatSizeB = VarCon_GetCommunicationVariableSize(VarIdB);
		if (VarDatSizeA != -1 && VarDatSizeB != -1) {
			VarDatA = new BYTE[VarDatSizeA];
			VarCon_GetCommunicationVariable(VarIdA, VarDatA, VarDatSizeA);
			VarDatB = new BYTE[VarDatSizeB];
			VarCon_GetCommunicationVariable(VarIdB, VarDatB, VarDatSizeB);

			int Start = -1;
			int End = -1;
			for (int Loop = 0; Loop <= InputDatSize - VarDatSizeA; Loop++) {
				int Ret = memcmp(InputDat + Loop, VarDatA, VarDatSizeA);
				if (Ret == 0) {
					Start = Loop;
					break;
				}
			}
			for (int Loop = 0; Loop <= InputDatSize - VarDatSizeB; Loop++) {
				int Ret = memcmp(InputDat + Loop, VarDatB, VarDatSizeB);
				if (Ret == 0) {
					End = Loop + VarDatSizeB - 1;
					break;
				}
			}

			delete VarDatA;
			delete VarDatB;
			if (Start == -1 || End == -1 || End < Start) {
				return 0;
			}
			int NewDatSize = End - Start + 1;
			BYTE* NewDat = new BYTE[NewDatSize];
			memcpy(NewDat, InputDat + Start, NewDatSize);

			delete InputDat;
			SetData((BYTE*)NewDat);
			SetDataLength(NewDatSize);
			return 0;
		} else {
			// �ϐ�(A)�܂���(B)���s���̂Ƃ��͉����������̗v�f�Ɉڂ�
			return 0;
		}
	}
	if (OpType == 4) {
		BYTE* InputDat = (BYTE*)GetData();
		delete InputDat;
		BYTE* ZeroDat = new BYTE[0];
		SetData(ZeroDat);
		SetDataLength(0);

		return 0;
	}
	if (OpType == 5) {
		VarDatSizeA = VarCon_GetCommunicationVariableSize(VarIdA);
		if (VarDatSizeA != -1) {
			VarDatA = new BYTE[VarDatSizeA];
			VarCon_GetCommunicationVariable(VarIdA, VarDatA, VarDatSizeA);
		} else {
			// �ϐ�(A)���s���̂Ƃ��͉����������̗v�f�Ɉڂ�
			return 0;
		}
		delete InputVarDat;
		SetData((BYTE*)VarDatA);
		SetDataLength(VarDatSizeA);
		return 0;
	}
	return 0;
}

// Close port
int ExecElem::Type16Execution()
{
	int TargetId = LowDbAccess::GetInstance()->GetElementInfoParamInt(ElementId, 1);
	int TargetType = LowDbAccess::GetInstance()->GetViewElementTypeFromId(TargetId);
	if (TargetType == -1) {
		return 0;
	}
	int IsClose = LowDbAccess::GetInstance()->GetElementInfoParamInt(ElementId, 2);
	if (TargetType == 1) {
		StkSocket_CloseAccept(TargetId, ElementId, (IsClose == 1)? TRUE : FALSE);
	}
	if (TargetType == 4 || TargetType == 7) {
		StkSocket_Disconnect(TargetId, ElementId, (IsClose == 1)? TRUE : FALSE);
	}
	if (TargetType == 22 || TargetType == 23) {
		StkSocket_Disconnect(TargetId, ElementId, FALSE);
	}
	StkPropOutputLog();
	return 0;
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

		// ����Use Only Once�I�v�V�������ݒ肳��Ă�����
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
				// ����Use Only Once�I�v�V�������ݒ肳��Ă�����
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

// Write file
int ExecElem::Type18Execution()
{
	// �������ݑΏۃt�@�C���p�X�̎擾
	TCHAR BufPath[256];
	LowDbAccess::GetInstance()->GetElementInfoParamStr(ElementId, BufPath, 1);
	// �A�N�Z�X��ʂ̎擾
	int AccessType = LowDbAccess::GetInstance()->GetElementInfoParamInt(ElementId, 1);

	// ���̓f�[�^�̎擾
	BYTE* InputDat = (BYTE*)GetData();
	int InputDatLength = GetDataLength();

	// ��Ɨp�̈�
	BYTE* WorkDat;
	int WorkDatLength;
	int WorkDatLenForFile;
	int WorkDatLenForInput;
	DWORD TmpSize = 0;

	// ��Ɨp�̈�ւ̃f�[�^�̊i�[
	if (AccessType == 0) {
		WorkDat = InputDat;
		WorkDatLength = InputDatLength;
	} else {
		HANDLE ReadFileHndl = CreateFile(BufPath, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		if (ReadFileHndl != INVALID_HANDLE_VALUE) {
			LARGE_INTEGER ExistingFileSize;
			GetFileSizeEx(ReadFileHndl, &ExistingFileSize);
			if (ExistingFileSize.QuadPart + InputDatLength >= 10000000) {
					CloseHandle(ReadFileHndl);
					return 2;
			}

			WorkDatLength = (int)(ExistingFileSize.QuadPart + InputDatLength);
			WorkDat = new BYTE[WorkDatLength];

			if (AccessType == 1) {
				WorkDatLenForFile = (int)ExistingFileSize.QuadPart;
				WorkDatLenForInput = WorkDatLength - WorkDatLenForFile;
				memcpy(WorkDat, InputDat, WorkDatLenForInput);
				if (ReadFile(ReadFileHndl, (LPVOID)(WorkDat + WorkDatLenForInput), WorkDatLenForFile, &TmpSize, NULL) == 0) {
					delete WorkDat;
					CloseHandle(ReadFileHndl);
					return 2;
				}
			}
			if (AccessType == 2) {
				WorkDatLenForInput = InputDatLength;
				WorkDatLenForFile = WorkDatLength - WorkDatLenForInput;
				if (ReadFile(ReadFileHndl, (LPVOID)WorkDat, WorkDatLenForFile, &TmpSize, NULL) == 0) {
					delete WorkDat;
					CloseHandle(ReadFileHndl);
					return 2;
				}
				memcpy(WorkDat + WorkDatLenForFile, InputDat, WorkDatLenForInput);
			}

			delete InputDat;
			SetData((void*)WorkDat);
			SetDataLength(WorkDatLength);

			CloseHandle(ReadFileHndl);
		} else {
			// �����̃t�@�C�������݂��Ȃ��ꍇ
			WorkDat = InputDat;
			WorkDatLength = InputDatLength;
		}
	}

	// �t�@�C���ւ̏�������
	HANDLE FileHndl = CreateFile(BufPath, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (FileHndl == INVALID_HANDLE_VALUE) {
		delete WorkDat;
		SetData(NULL);
		SetDataLength(0);
		return 2;
	};
	if (WriteFile(FileHndl, (LPCVOID)WorkDat, WorkDatLength, &TmpSize, NULL) == 0) {
		delete WorkDat;
		SetData(NULL);
		SetDataLength(0);
		CloseHandle(FileHndl);
		return 2;
	}
	CloseHandle(FileHndl);
	return 0;
}

// Read file
int ExecElem::Type19Execution()
{
	// �ǂݍ��ݑΏۃt�@�C���p�X�̎擾
	TCHAR BufPath[256];
	LowDbAccess::GetInstance()->GetElementInfoParamStr(ElementId, BufPath, 1);
	// �A�N�Z�X��ʂ̎擾
	int AccessType = LowDbAccess::GetInstance()->GetElementInfoParamInt(ElementId, 1);

	// ���̓f�[�^�̎擾
	BYTE* InputDat = (BYTE*)GetData();
	int InputDatLength = GetDataLength();

	// ��Ɨp�̈�
	BYTE* WorkDat;
	int WorkDatLength;
	DWORD TmpSize = 0;

	// �ǂݍ��ݑΏۃt�@�C���̃I�[�v��
	HANDLE ReadFileHndl = CreateFile(BufPath, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (ReadFileHndl == INVALID_HANDLE_VALUE) {
		return 2;
	}

	// �T�C�Y�̃`�F�b�N
	LARGE_INTEGER ExistingFileSize;
	GetFileSizeEx(ReadFileHndl, &ExistingFileSize);

	// Overwrite data
	if (AccessType == 0) {
		if (ExistingFileSize.QuadPart >= 10000000) {
			CloseHandle(ReadFileHndl);
			return 2;
		}
		WorkDatLength = (int)ExistingFileSize.QuadPart;
		WorkDat = new BYTE[WorkDatLength];

		if (ReadFile(ReadFileHndl, (LPVOID)WorkDat, WorkDatLength, &TmpSize, NULL) == 0) {
			CloseHandle(ReadFileHndl);
			delete WorkDat;
			return 2;
		}
	}
	// Insert data / join data
	if (AccessType == 1 || AccessType == 2) {
		if (ExistingFileSize.QuadPart + InputDatLength >= 10000000) {
			CloseHandle(ReadFileHndl);
			return 2;
		}
		WorkDatLength = (int)ExistingFileSize.QuadPart + InputDatLength;
		WorkDat = new BYTE[WorkDatLength];

		if (AccessType == 1) {
			if (ReadFile(ReadFileHndl, (LPVOID)WorkDat, (int)ExistingFileSize.QuadPart, &TmpSize, NULL) == 0) {
				CloseHandle(ReadFileHndl);
				delete WorkDat;
				return 2;
			}
			memcpy(WorkDat + (int)ExistingFileSize.QuadPart, InputDat, InputDatLength);
		}
		if (AccessType == 2) {
			memcpy(WorkDat, InputDat, InputDatLength);
			if (ReadFile(ReadFileHndl, (LPVOID)(WorkDat + InputDatLength), (int)ExistingFileSize.QuadPart, &TmpSize, NULL) == 0) {
				CloseHandle(ReadFileHndl);
				delete WorkDat;
				return 2;
			}
		}
	}

	delete InputDat;
	CloseHandle(ReadFileHndl);
	SetData((void*)WorkDat);
	SetDataLength(WorkDatLength);

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

// �v�f�̏��������s����
// �߂�l: (0:Terminator�ȊO�̏���������I��, 1:Terminator�̏���������I��, 2:�ُ�I��(������i�߂Ȃ�))
int ExecElem::Execute()
{
	if (ElementType == 2) { // Load data
		if (Type2Execution() == -1) {
			return 2;
		}
		return 0;
	}
	if (ElementType == 3) {
		return 0;
	}
	if (ElementType == 5) { // Store data
		Type5Execution();
		return 1;
	}
	if (ElementType == 6) {
		return 1;
	}
	if (ElementType == 8) { // Store data
		Type5Execution();
		return 0;
	}
	if (ElementType == 9) {
		return 0;
	}
	if (ElementType == 12) { // Timer
		return Type12Execution();
	}
	if (ElementType == 14) { // Change data
		return Type14Execution();
	}
	if (ElementType == 16) { // Close socket
		return Type16Execution();
	}
	if (ElementType == 17) { // Mapper
		return Type17Execution();
	}
	if (ElementType == 18) { // Write file
		return Type18Execution();
	}
	if (ElementType == 19) { // Read file
		return Type19Execution();
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
