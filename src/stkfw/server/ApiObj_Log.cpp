#include <cwchar>
#include "ApiObj_Log.h"
#include "ExecElem.h"
#include "..\..\..\..\YaizuComLib\src\commonfunc\StkObject.h"

StkObject* ApiObj_Log::Execute(StkObject* ReqObj, int Method, wchar_t Url[ApiObj::URL_PATH_LENGTH], int* ResultCode)
{
	if (Method & ApiObj::METHOD_GET) {
		int max_log_size = ExecElem::get_max_log_size();
		wchar_t* acquired_log = new wchar_t[max_log_size];
		ExecElem::get_log(acquired_log, max_log_size);
		StkObject* obj = NULL;
		if (wcscmp(acquired_log, L"") != NULL) {
			obj = new StkObject(L"");
			obj->AppendChildElement(new StkObject(L"log", acquired_log));
		}
		delete[] acquired_log;
		*ResultCode = 200;
		return obj;
	}
	if (Method & ApiObj::METHOD_POST) {
		if (ReqObj != NULL) {
			if (wcscmp(ReqObj->GetName(), L"clearLog") == NULL && wcscmp(ReqObj->GetStringValue(), L"yes") == NULL) {
				ExecElem::clear_log();
			} else if (wcscmp(ReqObj->GetName(), L"changeSize") == NULL) {
				int size = ReqObj->GetIntValue();
				ExecElem::change_size(size);
			}
		}
		*ResultCode = 200;
		return NULL;
	}
	*ResultCode = 400;
	return NULL;
}
