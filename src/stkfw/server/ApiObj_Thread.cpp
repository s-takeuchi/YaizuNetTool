#include "ApiObj_Thread.h"
#include "ExecElemMgr.h"
#include "LowDbAccess.h"
#include "..\..\..\..\YaizuComLib\src\stkthreadgui\stkthreadgui.h"
#include "..\..\..\..\YaizuComLib\src\stkthread\stkthread.h"

int ApiObj_Thread::ElemStkThreadInit(int Id)
{
	LowDbAccess::GetInstance()->UpdateElementInfoFromViewElement();

	ExecElemMgr* ExecMgr = ExecElemMgr::GetInstance();

	// ExecElemMgr‰Šú‰»
	ExecMgr->AddExecElem(Id);
	ExecMgr->ThreadStatusChangedIntoStart(Id); // This line is required for appropriate running.

	return 0;
}

int ApiObj_Thread::ElemStkThreadFinal(int Id)
{
	ExecElemMgr* ExecMgr = ExecElemMgr::GetInstance();

	// ExecElemMgrÅIˆ—
	ExecMgr->ThreadStatusChangedIntoStop(Id);
	ExecMgr->ClearLineType(Id);
	ExecMgr->DeleteExecElem(Id);

	return 0;
}

int ApiObj_Thread::ElemStkThreadMain(int Id)
{
	// If other thread(s) is/are in starting status, wait for the completion of other thread(s).
	int Num;
	do {
		Num = GetNumOfStartingStkThread();
		if (Num != 0) {
			Sleep(10);
		}
	} while (Num);

	ExecElemMgr* ExecMgr = ExecElemMgr::GetInstance();
	ExecMgr->ExecuteElement(Id);
	return 0;
}

int ApiObj_Thread::ElemStkThreadStart(int Id)
{
	ExecElemMgr* ExecMgr = ExecElemMgr::GetInstance();
	ExecMgr->ThreadStatusChangedIntoStart(Id);
	return 0;
}

int ApiObj_Thread::ElemStkThreadStop(int Id)
{
	ExecElemMgr* ExecMgr = ExecElemMgr::GetInstance();
	ExecMgr->ThreadStatusChangedIntoStop(Id);
	return 0;
}

int ApiObj_Thread::ResetThreadController(bool DelAll)
{
	int Type[100];
	int ExecFlag[100];
	TCHAR Desc[100][256];
	int PropCount = 0;

	TCHAR Name[256][32];
	int Id[256];
	int VeCount = 0;

	static int RegThId[256];
	static int RegThCnt = 0;
	int RegThIdTmp[256];
	TCHAR RegThNameTmp[100][256];
	TCHAR RegThDescTmp[100][256];
	int RegThCntTmp = 0;

	// Gather thread information from repository
	PropCount = LowDbAccess::GetInstance()->GetViewElementBasicInfoFromProperty(Type, ExecFlag, Desc);
	for (int LoopProp = 0; LoopProp < PropCount; LoopProp++) {
		VeCount = LowDbAccess::GetInstance()->GetViewElementNamesAndIdsFromType(Name, Id, Type[LoopProp]);
		for (int LoopVe = 0; LoopVe < VeCount; LoopVe++) {
			if (ExecFlag[LoopProp] == 1) {
				if (RegThCntTmp < 100) {
					RegThIdTmp[RegThCntTmp] = Id[LoopVe];
					lstrcpy(RegThNameTmp[RegThCntTmp], Name[LoopVe]);
					lstrcpy(RegThDescTmp[RegThCntTmp], Desc[LoopProp]);
					RegThCntTmp++;
				}
			}
		}
	}

	// Unregister all threads if DelAll flag is true.
	if (DelAll == TRUE) {
		for (int Loop = 0; Loop < RegThCnt; Loop++) {
			DeleteStkThreadForGui(RegThId[Loop]);
		}
		RegThCnt = 0;
	}

	// Register thread information if the thread has not been registered into ThreadController.
	for (int LoopTmp = 0; LoopTmp < RegThCntTmp; LoopTmp++) {
		int FndIdx = -1;
		for (int Loop = 0; Loop < RegThCnt; Loop++) {
			if (RegThIdTmp[LoopTmp] == RegThId[Loop]) {
				FndIdx = Loop;
			}
		}
		if (FndIdx == -1 && RegThCnt < 100) {
			RegThId[RegThCnt] = RegThIdTmp[LoopTmp];
			RegThCnt++;
			AddStkThreadForGui(RegThIdTmp[LoopTmp], RegThNameTmp[LoopTmp], RegThDescTmp[LoopTmp], ElemStkThreadInit, ElemStkThreadFinal, ElemStkThreadMain, ElemStkThreadStart, ElemStkThreadStop);
		}
	}

	// Unregister theread information if the view elements which are associating to the thread does not exist.
	for (int Loop = 0; Loop < RegThCnt; Loop++) {
		int FndIdx = -1;
		for (int LoopTmp = 0; LoopTmp < RegThCntTmp; LoopTmp++) {
			if (RegThIdTmp[LoopTmp] == RegThId[Loop]) {
				FndIdx = Loop;
			}
		}
		if (FndIdx == -1) {
			DeleteStkThreadForGui(RegThId[Loop]);
			RegThId[Loop] = RegThId[RegThCnt - 1];
			RegThCnt--;
			Loop--;
		}
	}

	return 0;
}

StkObject* ApiObj_Thread::Execute(StkObject* ReqObj, int Method, wchar_t Url[ApiObj::URL_PATH_LENGTH], int* ResultCode)
{
	bool ThreadRefreshFlag = false;
	bool DeleteAllFlag = false;

	if (ReqObj != NULL) {
		StkObject* ChildObj = ReqObj->GetFirstChildElement();
		while (ChildObj != NULL) {
			if (wcscmp(ChildObj->GetName(), L"threadStatus") == 0) {
				TCHAR* Val = ChildObj->GetStringValue();
				if (wcscmp(Val, L"refresh") == 0) {
					ThreadRefreshFlag = true;
				}
			}
			if (wcscmp(ChildObj->GetName(), L"deleteAll") == 0) {
				TCHAR* Val = ChildObj->GetStringValue();
				if (wcscmp(Val, L"yes") == 0) {
					DeleteAllFlag = true;
				}
			}
			ChildObj = ChildObj->GetNext();
		}

		ExecElemMgr* ExecMgr = ExecElemMgr::GetInstance();
		if (ThreadRefreshFlag == true) {
			if (DeleteAllFlag == true) {
				ResetThreadController(true);
			} else {
				ResetThreadController(false);
			}
			*ResultCode = 200;
			return NULL;
		}
	}
	*ResultCode = 400;
	return NULL;
}
