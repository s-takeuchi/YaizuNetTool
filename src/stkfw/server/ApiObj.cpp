#include <cwchar>
#include "ApiObj.h"
#include "ApiObj_Thread.h"
#include "ApiObj_Log.h"

ApiObj* ApiObj::CreateObject(int Method, wchar_t Url[ApiObj::URL_PATH_LENGTH])
{
	if ((Method & METHOD_GET) && wcsstr(Url, L"/api/thread/") != 0) {
		return new ApiObj_Thread;
	}
	if ((Method & METHOD_POST) && wcsstr(Url, L"/api/thread/") != 0) {
		return new ApiObj_Thread;
	}
	if ((Method & METHOD_GET) && wcsstr(Url, L"/api/log/") != 0) {
		return new ApiObj_Log;
	}
	if ((Method & METHOD_POST) && wcsstr(Url, L"/api/log/") != 0) {
		return new ApiObj_Log;
	}
	return NULL;
}
