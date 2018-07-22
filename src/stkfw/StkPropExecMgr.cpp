#include <windows.h>
#include <tchar.h>
#include <memory.h>
#include "StkPropExecMgr.h"
#include "ExecElem.h"
#include "LowDbAccess.h"

StkPropExecMgr* StkPropExecMgr::ThisInstance;
CRITICAL_SECTION StkPropExecMgr::CritSect;
CRITICAL_SECTION StkPropExecMgr::CritSectExe; //#10084

// Constructor
StkPropExecMgr::StkPropExecMgr()
{
	InitializeCriticalSection(&CritSect);
	InitializeCriticalSection(&CritSectExe); //#10084
	NumOfExecElem = 0;
}

// Destructor
StkPropExecMgr::~StkPropExecMgr()
{
}

// Get this instance
StkPropExecMgr* StkPropExecMgr::GetInstance()
{
	static int Init = 1;
	if (Init == 1) {
		ThisInstance = new StkPropExecMgr();
		Init = 0;
	}
	return ThisInstance;
}

// �w�肵��ID��ExecElem��ExecElems�z�񂩂�擾����
// [in] : Id : �擾�Ώۂ�ExecElem��ID
// return : ExecElem�C���X�^���X�B������Ȃ������ꍇNULL�B
ExecElem* StkPropExecMgr::GetExecElem(int Id)
{
	for (int Loop = 0; Loop < NumOfExecElem; Loop++) {
		ExecElem* CurExecElem = ExecElems[Loop];
		if (CurExecElem == NULL) {
			return NULL;
		}
		if (CurExecElem->GetElementId() == Id) {
			return CurExecElem;
		}
	}
	return NULL;
}

// ExecElems�z���Index�Ԗڂɂ���ExecElem���擾����
// [in] : Index : 0����͂��܂�ʂ��ԍ�
// return : ExecElem�C���X�^���X�B������Ȃ������ꍇNULL�B
ExecElem* StkPropExecMgr::GetExecElemByIndex(int Index)
{
	if (Index < 0 || Index >= NumOfExecElem) {
		return NULL;
	}
	return ExecElems[Index];
}

// ExecElems�z��ɑ��݂���ExecElem�C���X�^���X�̐����擾����
// return : ExecElem�C���X�^���X�̐�
int StkPropExecMgr::GetExecElemCount()
{
	return NumOfExecElem;
}

// �w�肵��ID�̗v�f�ƃ����N���Ă���S�Ă̗v�f(ExecElem)���擾����
// [in] : Id : �����N�Ώۂ̗v�f��ID
// [in] : OrgId : �����N�̍��ƂȂ�ID
// [in] : PrevId : �����N���̗v�f��ID
// [in] : Counter : �ċA�I�ȌĂяo����
void StkPropExecMgr::GetLinkedElementIds(int Id, int OrgId, int PrevId, int Counter)
{
	int LinkId[10];
	int LinkType[10];
	int Type;
	int RetCode;

	if (Counter == 100) {
		return;
	}
	RetCode = LowDbAccess::GetInstance()->GetViewElementLinkInfo(Id, &Type, LinkId, LinkType);
	if (RetCode == 0) {
		for (int Loop = 0; Loop < 10; Loop ++) {
			if (LinkId[Loop] != -1 && LinkType[Loop] != 122) {
				Counter++;
				GetLinkedElementIds(LinkId[Loop], OrgId, Id, Counter);
			}
		}
		/////// ����Id, OrgId, PrevId������ExecElems�ɓo�^����Ă���ꍇ�C�ēo�^���Ȃ�
		for (int Loop = 0; Loop < NumOfExecElem; Loop++) {
			ExecElem* CmpExecElem = ExecElems[Loop];
			if (CmpExecElem->GetRootId() == OrgId && CmpExecElem->GetElementId() == Id && CmpExecElem->GetWaitForExecId() == PrevId) {
				return;
			}
		}
		///////
		ExecElem* NewExecElem = ExecElem::CreateExecElem(Id, Type);
		NewExecElem->SetRootId(OrgId);
		NewExecElem->SetWaitForExecId(PrevId);
		ExecElems[NumOfExecElem] = NewExecElem;
		NumOfExecElem++;
	}
}

// ���s�ˑ�Id�̐ݒ�i�w�肵��Id�������N���Ƃ���v�f��WaitForExecId��ݒ肷��j
// [in] : Id : �����N���̗v�f��ID
void StkPropExecMgr::SetWaitForThreadEnd(int Id)
{
	int LinkOrgId;
	int LinkType;
	int RetCode;
	
	RetCode = LowDbAccess::GetInstance()->GetViewElementLinkOriginInfo(Id, &LinkOrgId, &LinkType);
	if (RetCode == 0) {
		ExecElem* CurrentExecElem = GetExecElem(Id);
		if (CurrentExecElem == NULL) {
			return;
		}
		if (LinkType != 122) {
			return;
		}
		CurrentExecElem->SetWaitForExecId(LinkOrgId);
	} else {
		ExecElem* CurrentExecElem = GetExecElem(Id);
		CurrentExecElem->SetStatus(ExecElem::STATUS_WAITING);
	}
}

// Store Data�܂���Load Data�̃J�E���^�[������������
// [in] : Id : ���s�n�v�f��ID
void StkPropExecMgr::InitStoreAndLoadDataCounter(int Id)
{
	for (int Loop = 0; Loop < NumOfExecElem; Loop++) {
		ExecElem* CurExecElem = ExecElems[Loop];
		if (CurExecElem == NULL) {
			continue;
		}
		if (CurExecElem->GetRootId() == Id) {
			int TargetId = CurExecElem->GetElementId();
			int Type = LowDbAccess::GetInstance()->GetViewElementTypeFromId(TargetId);
			if (Type == 2 || Type == 5 || Type == 8) {
				int InitCounter = LowDbAccess::GetInstance()->GetElementInfoParamInt(TargetId, 4);
				LowDbAccess::GetInstance()->SetElementInfoParamInt(TargetId, InitCounter, 5);
			}
		}
	}
}

// Timer�̓����J�E���^�[������������
// [in] : Id : ���s�n�v�f��ID
void StkPropExecMgr::InitTimer(int Id)
{
	for (int Loop = 0; Loop < NumOfExecElem; Loop++) {
		ExecElem* CurExecElem = ExecElems[Loop];
		if (CurExecElem == NULL) {
			continue;
		}
		if (CurExecElem->GetRootId() == Id) {
			int TargetId = CurExecElem->GetElementId();
			int Type = LowDbAccess::GetInstance()->GetViewElementTypeFromId(TargetId);
			if (Type == 12) {
				LowDbAccess::GetInstance()->SetElementInfoParamInt(TargetId, 0, 5);
			}
		}
	}
}

// Mapper�̃}�b�v�ϕϐ���ID������������
void StkPropExecMgr::InitMappingIds(int Id)
{
	for (int Loop = 0; Loop < NumOfExecElem; Loop++) {
		ExecElem* CurExecElem = ExecElems[Loop];
		if (CurExecElem == NULL) {
			continue;
		}
		if (CurExecElem->GetRootId() == Id) {
			BYTE TmpDat[4096];
			INT16* TmpDatInt = (INT16*)TmpDat;
			for (int Loop = 0; Loop < 2048; Loop++) {
				TmpDatInt[Loop] = (INT16)-1;
			}
			int TargetId = CurExecElem->GetElementId();
			int Type = LowDbAccess::GetInstance()->GetViewElementTypeFromId(TargetId);
			if (Type == 17) {
				LowDbAccess::GetInstance()->SetElementInfoBin(TargetId, TmpDat);
			}
		}
	}
}

// Initialization of execute program
void StkPropExecMgr::InitExecProgram(int Id)
{
	// Initialize attributes for the "Execute Program"
	for (int Loop = 0; Loop < NumOfExecElem; Loop++) {
		ExecElem* CurExecElem = ExecElems[Loop];
		if (CurExecElem == NULL) {
			continue;
		}
		if (CurExecElem->GetRootId() == Id) {
			int TargetId = CurExecElem->GetElementId();
			int Type = LowDbAccess::GetInstance()->GetViewElementTypeFromId(TargetId);
			if (Type == 20) {
				CurExecElem->ExeProcInfo.dwProcessId = NULL;
			}
		}
	}
}

// Thread status was changed into "Start"
// Id [in] : Thread ID
void StkPropExecMgr::ThreadStatusChangedIntoStart(int Id)
{
	for (int Loop = 0; Loop < NumOfExecElem; Loop++) {
		ExecElem* CurExecElem = ExecElems[Loop];
		if (CurExecElem == NULL) {
			continue;
		}
		if (CurExecElem->GetRootId() == Id) {
			CurExecElem->ThreadStatusChangedIntoStart();
		}
	}
}

// Thread status was changed into "Stop"
// Id [in] : Thread ID
void StkPropExecMgr::ThreadStatusChangedIntoStop(int Id)
{
	for (int Loop = 0; Loop < NumOfExecElem; Loop++) {
		ExecElem* CurExecElem = ExecElems[Loop];
		if (CurExecElem == NULL) {
			continue;
		}
		if (CurExecElem->GetRootId() == Id) {
			CurExecElem->ThreadStatusChangedIntoStop();
		}
	}
}

// Id�Ɗ֘A�t���S�Ă̎��s�n�v�f�C�f�[�^�n�v�f��ExecElem�ɓW�J
// [in] : Id : ���s�n�v�f��ID
void StkPropExecMgr::AddExecElem(int Id)
{
	EnterCriticalSection(&CritSect);
	GetLinkedElementIds(Id, Id, -1, 1);
	SetWaitForThreadEnd(Id);
	LeaveCriticalSection(&CritSect);
}

// �S�Ă�ExecElem���폜����
// [in] : Id : ���s�n�v�f��ID
void StkPropExecMgr::DeleteExecElem(int Id)
{
	EnterCriticalSection(&CritSect);
	for (int Loop = 0; Loop < NumOfExecElem; Loop++) {
		ExecElem* CurExecElem = ExecElems[Loop];
		if (CurExecElem == NULL) {
			continue;
		}
		if (CurExecElem->GetRootId() == Id) {
			void* TmpDat = CurExecElem->GetData();
			if (TmpDat != NULL) {
				delete TmpDat;
			}
			delete CurExecElem;
			ExecElems[Loop] = ExecElems[NumOfExecElem - 1];
			ExecElems[NumOfExecElem - 1] = NULL;
			NumOfExecElem--;
			Loop--;
		}
	}
	LeaveCriticalSection(&CritSect);
}

// ���̏����̃X�e�[�^�X��NotInScope����Waiting/DWaiting�ɕύX����
void StkPropExecMgr::ChangeNotInScopeToWaiting(int Id, int RootId)
{
	for (int Loop = 0; Loop < NumOfExecElem; Loop++) {
		ExecElem* CurExecElem = ExecElems[Loop];
		if (CurExecElem->GetWaitForExecId() == Id && CurExecElem->GetStatus() == ExecElem::STATUS_NOTINSCOPE) {
			int Tp = CurExecElem->GetType();
			if (Tp == 1 || Tp == 2 || Tp == 3 || Tp == 21) {
				CurExecElem->SetStatus(ExecElem::STATUS_DWAITING);
			} else {
				if (CurExecElem->GetRootId() == RootId) {
					CurExecElem->SetStatus(ExecElem::STATUS_WAITING);
				}
			}
		}
	}
}

// �����N�̎�ʂ�ύX����
// [in] : LkTp : �����N��� (LkTp == -5 : 101��111, LkTp == +5 : 111��101)
void StkPropExecMgr::ChangeLineType(int From, int To, int LkTp)
{
	BOOL FndFlag;
	int Loop;

	int LinkId[10];
	int LinkType[10];
	int Type;
	LowDbAccess::GetInstance()->GetViewElementLinkInfo(From, &Type, LinkId, LinkType);
	for (Loop = 0; Loop < 10; Loop++) {
		if (LinkId[Loop] == To && LinkType[Loop] == (106 + LkTp)) {
			FndFlag = TRUE;
			break;
		}	
	}
	if (FndFlag == TRUE) {
		LowDbAccess::GetInstance()->UpdateViewElementLinkType(Loop, From, To, LkTp);
	}
}

void StkPropExecMgr::ClearLineType(int Id)
{
	EnterCriticalSection(&CritSect);
	for (int LoopClr = 0; LoopClr < NumOfExecElem; LoopClr++) {
		ExecElem* ExecElemClr = ExecElems[LoopClr];
		if (ExecElemClr->GetRootId() == Id) {
			if (ExecElemClr->GetWaitForExecId() != -1) {
				ChangeLineType(ExecElemClr->GetWaitForExecId(), ExecElemClr->GetElementId(), 5);
			}
		}
	}
	LeaveCriticalSection(&CritSect);
}

// �e�v�f�̏��������s����
void StkPropExecMgr::ExecuteElement(int Id)
{
	// STATUS_CLEAR�̏���
	EnterCriticalSection(&CritSect);
	for (int Loop = 0; Loop < NumOfExecElem; Loop++) {
		ExecElem* CurExecElem = ExecElems[Loop];
		if (CurExecElem->GetRootId() == Id && CurExecElem->GetStatus() == ExecElem::STATUS_CLEAR) {
			for (int LoopClr = 0; LoopClr < NumOfExecElem; LoopClr++) {
				ExecElem* ExecElemClr = ExecElems[LoopClr];

				// Timer���N���A
				if (ExecElemClr->GetRootId() == Id && ExecElemClr->GetType() == 12) {
					LowDbAccess::GetInstance()->SetElementInfoParamInt(ExecElemClr->GetElementId(), 0, 5);
				}

				// STATUS_CLEAR���I�[�̏�ԂƂ���X���b�h�Ɋւ��ă����N��ʂ̃N���A�ƃf�[�^�̈�̊J��
				if (ExecElemClr->GetRootId() == Id) {
					if (ExecElemClr->GetWaitForExecId() != -1) {
						ChangeLineType(ExecElemClr->GetWaitForExecId(), ExecElemClr->GetElementId(), 5);
					}
					ExecElemClr->SetStatus(ExecElem::STATUS_NOTINSCOPE);
					void* FreeData = ExecElemClr->GetData();
					if (FreeData != NULL)  {
						delete FreeData;
						ExecElemClr->SetData(NULL);
						ExecElemClr->SetDataLength(0);
					}
				}

				// �w�肵��ID�����X���b�h�J�n�v�f�ŁC���O�̃X���b�h�͑��݂��Ȃ�
				if (ExecElemClr->GetElementId() == Id && ExecElemClr->GetWaitForExecId() == -1) {
					ExecElemClr->SetStatus(ExecElem::STATUS_WAITING);
				}

				// �w�肵��ID�����X���b�h�J�n�v�f�ŁC���O�̃X���b�h����A�����Ă���
				if (ExecElemClr->GetElementId() == Id && ExecElemClr->GetWaitForExecId() != -1) {
					for (int LoopClr2 = 0; LoopClr2 < NumOfExecElem; LoopClr2++) {
						ExecElem* ExecElemClr2 = ExecElems[LoopClr2];
						if (ExecElemClr2->GetElementId() == ExecElemClr->GetWaitForExecId() &&
							ExecElemClr2->GetStatus() == ExecElem::STATUS_DONE) {
							ExecElemClr2->SetStatus(ExecElem::STATUS_CLEAR);
							Loop = 0;
						}
					}
				}
			}
		}
	}
	LeaveCriticalSection(&CritSect);

	EnterCriticalSection(&CritSect);
	for (int Loop = 0; Loop < NumOfExecElem; Loop++) {
		ExecElem* CurExecElem = ExecElems[Loop];
		if (CurExecElem->GetRootId() == Id &&
			(CurExecElem->GetStatus() == ExecElem::STATUS_WAITING ||
			CurExecElem->GetStatus() == ExecElem::STATUS_DWAITING ||
			CurExecElem->GetStatus() == ExecElem::STATUS_BWAITING)) {
			int PrevId = CurExecElem->GetWaitForExecId();
			if (PrevId != -1 && CurExecElem->GetStatus() != ExecElem::STATUS_BWAITING) {
				ChangeLineType(PrevId, CurExecElem->GetElementId(), -5);
				// �f�[�^��O�̗v�f��������p��
				for (int LoopDt = 0; LoopDt < NumOfExecElem; LoopDt++) {
					ExecElem* ExecElemDt = ExecElems[LoopDt];
					// �O�̗v�f��Aggregation/Destribution�łȂ���΃|�C���^���ړ�
					if (ExecElemDt->GetRootId() == CurExecElem->GetRootId() && ExecElemDt->GetElementId() == PrevId && ExecElemDt->GetType() != 15) {
						if (CurExecElem->GetData() == NULL) {
							CurExecElem->SetData(ExecElemDt->GetData());
							CurExecElem->SetDataLength(ExecElemDt->GetDataLength());
							ExecElemDt->SetData(NULL);
							ExecElemDt->SetDataLength(0);
							break;
						}
					}
					// �O�̗v�f��Aggregation/Destribution�Ȃ�΃f�[�^���R�s�[
					if (ExecElemDt->GetRootId() == CurExecElem->GetRootId() && ExecElemDt->GetElementId() == PrevId && ExecElemDt->GetType() == 15) {
						if (CurExecElem->GetData() == NULL) {
							int TargetDatLen = ExecElemDt->GetDataLength();
							void* TargetDat = ExecElemDt->GetData();
							if (TargetDatLen == 0 || TargetDat == NULL) {
								CurExecElem->SetData(NULL);
								CurExecElem->SetDataLength(0);
							} else {
								BYTE* LocalDat = new BYTE[TargetDatLen];
								memcpy(LocalDat, TargetDat, TargetDatLen);
								CurExecElem->SetData((void*)LocalDat);
								CurExecElem->SetDataLength(TargetDatLen);
							}
						}
					}
				}
			}
			LeaveCriticalSection(&CritSect);

			// ##10084 begin
			// �f�[�^���㏑������邱�Ƃւ̑Ώ�
			TCHAR Buf[MAX_PATH];
			wsprintf(Buf, _T("%d-%d"), GetCurrentProcessId(), CurExecElem->GetElementId());
			HANDLE Mutx = OpenMutex(SYNCHRONIZE, FALSE, Buf);
			if (!Mutx) {
				Mutx = CreateMutex(NULL, FALSE, Buf);
				Mutx = OpenMutex(SYNCHRONIZE, FALSE, Buf);
			}
			WaitForSingleObject(Mutx, INFINITE);
			// ##10084 end

			// �e�v�f�̏��������s����
			int Ret = CurExecElem->Execute();

			// ##10084 begin
			// �f�[�^���㏑������邱�Ƃւ̑Ώ�
			ReleaseMutex(Mutx);
			CloseHandle(Mutx);
			// ##10084 end

			EnterCriticalSection(&CritSect);

			if (CurExecElem->GetStatus() == ExecElem::STATUS_CLEAR) {
				break;
			}

			if (Ret == 0 || Ret == 1) {
				ChangeNotInScopeToWaiting(CurExecElem->GetElementId(), CurExecElem->GetRootId());
				// Terminator��
				if (Ret == 1) {
					// ExecElem�̎��̗v�f��DWAITING�Ȃ��ExecElem�̏�Ԃ�DONE�ɂ���
					int LoopWt;
					for (LoopWt = 0; LoopWt < NumOfExecElem; LoopWt++) {
						ExecElem* ExecElemWt = ExecElems[LoopWt];
						if (ExecElemWt->GetWaitForExecId() == CurExecElem->GetElementId()) {
							// ##10084 if (ExecElemWt->GetStatus() == ExecElem::STATUS_DWAITING) {
							// �f�[�^���]���ɏ�������邱�Ƃւ̑Ώ�
							CurExecElem->SetStatus(ExecElem::STATUS_DONE);
							// ##10084 }
							break;
						}
					}
					// ExecElem�̎��̗v�f�����݂��Ȃ���Ώ�Ԃ�CLEAR�ɂ���
					if (LoopWt == NumOfExecElem) {
						CurExecElem->SetStatus(ExecElem::STATUS_CLEAR);
					}
				} else {
					CurExecElem->SetStatus(ExecElem::STATUS_DONE);
				}
			} else if (Ret == 2) {
				CurExecElem->SetStatus(ExecElem::STATUS_BWAITING);
			}
		}
	}
	LeaveCriticalSection(&CritSect);
}
