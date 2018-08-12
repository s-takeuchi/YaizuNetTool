#include <windows.h>
#include <tchar.h>
#include <memory.h>
#include "ExecElemMgr.h"
#include "server\ExecElem.h"
#include "LowDbAccess.h"

ExecElemMgr* ExecElemMgr::ThisInstance;
CRITICAL_SECTION ExecElemMgr::CritSect;
CRITICAL_SECTION ExecElemMgr::CritSectExe; //#10084

// Constructor
ExecElemMgr::ExecElemMgr()
{
	InitializeCriticalSection(&CritSect);
	InitializeCriticalSection(&CritSectExe); //#10084
	NumOfExecElem = 0;
}

// Destructor
ExecElemMgr::~ExecElemMgr()
{
}

// Get this instance
ExecElemMgr* ExecElemMgr::GetInstance()
{
	static int Init = 1;
	if (Init == 1) {
		ThisInstance = new ExecElemMgr();
		Init = 0;
	}
	return ThisInstance;
}

// 指定したIDのExecElemをExecElems配列から取得する
// [in] : Id : 取得対象のExecElemのID
// return : ExecElemインスタンス。見つからなかった場合NULL。
ExecElem* ExecElemMgr::GetExecElem(int Id)
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

// ExecElems配列のIndex番目にあるExecElemを取得する
// [in] : Index : 0からはじまる通し番号
// return : ExecElemインスタンス。見つからなかった場合NULL。
ExecElem* ExecElemMgr::GetExecElemByIndex(int Index)
{
	if (Index < 0 || Index >= NumOfExecElem) {
		return NULL;
	}
	return ExecElems[Index];
}

// ExecElems配列に存在するExecElemインスタンスの数を取得する
// return : ExecElemインスタンスの数
int ExecElemMgr::GetExecElemCount()
{
	return NumOfExecElem;
}

// 指定したIDの要素とリンクしている全ての要素(ExecElem)を取得する
// [in] : Id : リンク対象の要素のID
// [in] : OrgId : リンクの根となるID
// [in] : PrevId : リンク元の要素のID
// [in] : Counter : 再帰的な呼び出し回数
void ExecElemMgr::GetLinkedElementIds(int Id, int OrgId, int PrevId, int Counter)
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
		/////// 同じId, OrgId, PrevIdが既にExecElemsに登録されている場合，再登録しない
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

// 実行依存Idの設定（指定したIdをリンク元とする要素のWaitForExecIdを設定する）
// [in] : Id : リンク元の要素のID
void ExecElemMgr::SetWaitForThreadEnd(int Id)
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

// Thread status was changed into "Start"
// Id [in] : Thread ID
void ExecElemMgr::ThreadStatusChangedIntoStart(int Id)
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
void ExecElemMgr::ThreadStatusChangedIntoStop(int Id)
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

// Idと関連付く全ての実行系要素，データ系要素をExecElemに展開
// [in] : Id : 実行系要素のID
void ExecElemMgr::AddExecElem(int Id)
{
	EnterCriticalSection(&CritSect);
	GetLinkedElementIds(Id, Id, -1, 1);
	SetWaitForThreadEnd(Id);
	LeaveCriticalSection(&CritSect);
}

// 全てのExecElemを削除する
// [in] : Id : 実行系要素のID
void ExecElemMgr::DeleteExecElem(int Id)
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

// 次の処理のステータスをNotInScopeからWaiting/DWaitingに変更する
void ExecElemMgr::ChangeNotInScopeToWaiting(int Id, int RootId)
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

// リンクの種別を変更する
// [in] : LkTp : リンク種別 (LkTp == -5 : 101→111, LkTp == +5 : 111→101)
void ExecElemMgr::ChangeLineType(int From, int To, int LkTp)
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

void ExecElemMgr::ClearLineType(int Id)
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

// 各要素の処理を実行する
void ExecElemMgr::ExecuteElement(int Id)
{
	// STATUS_CLEARの処理
	EnterCriticalSection(&CritSect);
	for (int Loop = 0; Loop < NumOfExecElem; Loop++) {
		ExecElem* CurExecElem = ExecElems[Loop];
		if (CurExecElem->GetRootId() == Id && CurExecElem->GetStatus() == ExecElem::STATUS_CLEAR) {
			for (int LoopClr = 0; LoopClr < NumOfExecElem; LoopClr++) {
				ExecElem* ExecElemClr = ExecElems[LoopClr];

				// Timerをクリア
				if (ExecElemClr->GetRootId() == Id && ExecElemClr->GetType() == 12) {
					LowDbAccess::GetInstance()->SetElementInfoParamInt(ExecElemClr->GetElementId(), 0, 5);
				}

				// STATUS_CLEARを終端の状態とするスレッドに関してリンク種別のクリアとデータ領域の開放
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

				// 指定したIDを持つスレッド開始要素で，直前のスレッドは存在しない
				if (ExecElemClr->GetElementId() == Id && ExecElemClr->GetWaitForExecId() == -1) {
					ExecElemClr->SetStatus(ExecElem::STATUS_WAITING);
				}

				// 指定したIDを持つスレッド開始要素で，直前のスレッドから連鎖している
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
				// データを前の要素から引き継ぐ
				for (int LoopDt = 0; LoopDt < NumOfExecElem; LoopDt++) {
					ExecElem* ExecElemDt = ExecElems[LoopDt];
					// 前の要素がAggregation/Destributionでなければポインタを移動
					if (ExecElemDt->GetRootId() == CurExecElem->GetRootId() && ExecElemDt->GetElementId() == PrevId && ExecElemDt->GetType() != 15) {
						if (CurExecElem->GetData() == NULL) {
							CurExecElem->SetData(ExecElemDt->GetData());
							CurExecElem->SetDataLength(ExecElemDt->GetDataLength());
							ExecElemDt->SetData(NULL);
							ExecElemDt->SetDataLength(0);
							break;
						}
					}
					// 前の要素がAggregation/Destributionならばデータをコピー
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
			// データが上書きされることへの対処
			TCHAR Buf[MAX_PATH];
			wsprintf(Buf, _T("%d-%d"), GetCurrentProcessId(), CurExecElem->GetElementId());
			HANDLE Mutx = OpenMutex(SYNCHRONIZE, FALSE, Buf);
			if (!Mutx) {
				Mutx = CreateMutex(NULL, FALSE, Buf);
				Mutx = OpenMutex(SYNCHRONIZE, FALSE, Buf);
			}
			WaitForSingleObject(Mutx, INFINITE);
			// ##10084 end

			// 各要素の処理を実行する
			int Ret = CurExecElem->Execute();

			// ##10084 begin
			// データが上書きされることへの対処
			ReleaseMutex(Mutx);
			CloseHandle(Mutx);
			// ##10084 end

			EnterCriticalSection(&CritSect);

			if (CurExecElem->GetStatus() == ExecElem::STATUS_CLEAR) {
				break;
			}

			if (Ret == 0 || Ret == 1) {
				ChangeNotInScopeToWaiting(CurExecElem->GetElementId(), CurExecElem->GetRootId());
				// Terminatorか
				if (Ret == 1) {
					// ExecElemの次の要素がDWAITINGならばExecElemの状態をDONEにする
					int LoopWt;
					for (LoopWt = 0; LoopWt < NumOfExecElem; LoopWt++) {
						ExecElem* ExecElemWt = ExecElems[LoopWt];
						if (ExecElemWt->GetWaitForExecId() == CurExecElem->GetElementId()) {
							// ##10084 if (ExecElemWt->GetStatus() == ExecElem::STATUS_DWAITING) {
							// データが余分に処理されることへの対処
							CurExecElem->SetStatus(ExecElem::STATUS_DONE);
							// ##10084 }
							break;
						}
					}
					// ExecElemの次の要素が存在しなければ状態をCLEARにする
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
