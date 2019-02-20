#pragma once
#include "..\..\..\..\YaizuComLib\src\commonfunc\StkObject.h"
#include "ApiObj.h"

class ApiObj_Log : public ApiObj
{
public:
	virtual StkObject* Execute(StkObject*, int, wchar_t[ApiObj::URL_PATH_LENGTH], int*);
};
