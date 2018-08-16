#include "ApiObj_Thread.h"
#include "ExecElemMgr.h"

StkObject* ApiObj_Thread::Execute(StkObject* ReqObj, int Method, wchar_t Url[ApiObj::URL_PATH_LENGTH], int* ResultCode)
{
	int TargetId = -1;
	bool ThreadStartFlag = false;
	bool ThreadStopFlag = false;
	if (ReqObj != NULL) {
		StkObject* ChildObj = ReqObj->GetFirstChildElement();
		while (ChildObj != NULL) {
			if (wcscmp(ChildObj->GetName(), L"threadStatus") == 0) {
				TCHAR* Val = ChildObj->GetStringValue();
				if (wcscmp(Val, L"start") == 0) {
					ThreadStartFlag = true;
				}
				if (wcscmp(Val, L"stop") == 0) {
					ThreadStopFlag = true;
				}
			}
			if (wcscmp(ChildObj->GetName(), L"id") == 0) {
				TargetId = ChildObj->GetIntValue();
			}
			ChildObj = ChildObj->GetNext();
		}

		ExecElemMgr* ExecMgr = ExecElemMgr::GetInstance();
		if (ThreadStartFlag == false && ThreadStopFlag == true && TargetId != -1) {
			ExecMgr->ThreadStatusChangedIntoStop(TargetId);
			*ResultCode = 200;
			return NULL;
		}
		if (ThreadStartFlag == true && ThreadStopFlag == false && TargetId != -1) {
			ExecMgr->ThreadStatusChangedIntoStart(TargetId);
			*ResultCode = 200;
			return NULL;
		}
	}
	*ResultCode = 400;
	return NULL;
}
