#include "ApiObj_Log.h"
#include "ExecElem.h"
#include "..\..\..\..\YaizuComLib\src\commonfunc\StkObject.h"

StkObject* ApiObj_Log::Execute(StkObject* ReqObj, int Method, wchar_t Url[ApiObj::URL_PATH_LENGTH], int* ResultCode)
{
	if (Method & ApiObj::METHOD_GET) {
		wchar_t acquired_log[1000];
		ExecElem::get_log(acquired_log, 1000);
		StkObject* obj = new StkObject(L"");
		obj->AppendChildElement(new StkObject(L"log", acquired_log));
		*ResultCode = 200;
		return obj;
	}
	if (Method & ApiObj::METHOD_POST) {
		if (ReqObj != NULL) {
			if (wcscmp(ReqObj->GetName(), L"operation") == NULL && wcscmp(ReqObj->GetStringValue(), L"clearLog") == NULL) {
				ExecElem::clear_log();
			}
		}
		*ResultCode = 200;
		return NULL;
	}
	*ResultCode = 400;
	return NULL;
}
