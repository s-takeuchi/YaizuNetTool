#include <cwchar>
#include "ApiObj_Thread.h"
#include "ExecElemMgr.h"
#include "LowDbAccess.h"
#include "..\..\..\..\YaizuComLib\src\commonfunc\StkObject.h"
#include "..\..\..\..\YaizuComLib\src\stkthreadgui\stkthreadgui.h"
#include "..\..\..\..\YaizuComLib\src\stkthread\stkthread.h"

int ApiObj_Thread::ElemStkThreadInit(int Id)
{
	LowDbAccess::GetInstance()->UpdateElementInfoFromViewElement();

	ExecElemMgr* ExecMgr = ExecElemMgr::GetInstance();

	// ExecElemMgr初期化
	ExecMgr->AddExecElem(Id);
	ExecMgr->ThreadStatusChangedIntoStart(Id); // This line is required for appropriate running.

	return 0;
}

int ApiObj_Thread::ElemStkThreadFinal(int Id)
{
	ExecElemMgr* ExecMgr = ExecElemMgr::GetInstance();

	// ExecElemMgr最終処理
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
	if (Method & ApiObj::METHOD_POST) {
		bool RefreshFlag = false;
		bool RefreshWithDelFlag = false;
		bool StartAllFlag = false;
		bool StopAllFlag = false;

		if (ReqObj != NULL) {
			StkObject* ChildObj = ReqObj->GetFirstChildElement();
			while (ChildObj != NULL) {
				if (wcscmp(ChildObj->GetName(), L"threadStatus") == 0) {
					TCHAR* Val = ChildObj->GetStringValue();
					if (wcscmp(Val, L"refresh") == 0) {
						RefreshFlag = true;
					}
					if (wcscmp(Val, L"refreshWithDelete") == 0) {
						RefreshWithDelFlag = true;
					}
					if (wcscmp(Val, L"startAll") == 0) {
						StartAllFlag = true;
					}
					if (wcscmp(Val, L"stopAll") == 0) {
						StopAllFlag = true;
					}
				}
				ChildObj = ChildObj->GetNext();
			}

			ExecElemMgr* ExecMgr = ExecElemMgr::GetInstance();
			if (RefreshFlag == true) {
				ResetThreadController(true);
			}
			if (RefreshWithDelFlag == true) {
				ResetThreadController(true);
			}
			*ResultCode = 200;
			return NULL;
		}
	}
	if (Method & ApiObj::METHOD_GET) {
		StkObject* obj = new StkObject(L"");
		for (int i = 0; i < GetNumOfStkThread(); i++) {
			int thread_id = GetStkThreadIdByIndex(i);
			int thread_status_type = GetStkThreadStatusByIndex(i);
			wchar_t thread_status[32];
			if (thread_status_type == STKTHREAD_STATUS_READY) {
				wcscpy_s(thread_status, 32, L"ready");
			}
			if (thread_status_type == STKTHREAD_STATUS_STARTING) {
				wcscpy_s(thread_status, 32, L"starting");
			}
			if (thread_status_type == STKTHREAD_STATUS_RUNNING) {
				wcscpy_s(thread_status, 32, L"running");
			}
			if (thread_status_type == STKTHREAD_STATUS_STOPPING) {
				wcscpy_s(thread_status, 32, L"stopping");
			}
			wchar_t thread_name[MAX_LENGTH_OF_STKTHREAD_NAME];
			GetStkThreadNameByIndex(i, thread_name);
			wchar_t thread_desc[MAX_LENGTH_OF_STKTHREAD_DESCRIPTION];
			GetStkThreadDescriptionByIndex(i, thread_desc);
			StkObject* thread_obj = new StkObject(L"threadInfo");
			thread_obj->AppendChildElement(new StkObject(L"id", thread_id));
			thread_obj->AppendChildElement(new StkObject(L"status", thread_status));
			thread_obj->AppendChildElement(new StkObject(L"name", thread_name));
			thread_obj->AppendChildElement(new StkObject(L"description", thread_desc));
			obj->AppendChildElement(thread_obj);
		}
		*ResultCode = 200;
		return obj;
	}
	*ResultCode = 400;
	return NULL;
}
