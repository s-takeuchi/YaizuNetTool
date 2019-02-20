#pragma once
#include "..\..\..\..\YaizuComLib\src\commonfunc\StkObject.h"
#include "ApiObj.h"

class ApiObj_Thread : public ApiObj
{
private:
	static int ElemStkThreadInit(int);
	static int ElemStkThreadFinal(int);
	static int ElemStkThreadMain(int);
	static int ElemStkThreadStart(int);
	static int ElemStkThreadStop(int);

public:
	virtual StkObject* Execute(StkObject*, int, wchar_t[ApiObj::URL_PATH_LENGTH], int*);
	int ResetThreadController(bool DelAll);
};
