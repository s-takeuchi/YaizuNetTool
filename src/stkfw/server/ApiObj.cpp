#include "ApiObj.h"
#include "ApiObj_Thread.h"

ApiObj* ApiObj::CreateObject(int Method, wchar_t Url[ApiObj::URL_PATH_LENGTH])
{
	if (Method == METHOD_POST && wcscmp(Url, L"/api/thread/") == 0) {
		return new ApiObj_Thread;
	}
	return NULL;
}
