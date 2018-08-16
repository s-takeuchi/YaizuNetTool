#pragma once
#include "..\..\..\..\YaizuComLib\src\commonfunc\StkObject.h"
#include "ApiObj.h"

class ApiObj_Thread : public ApiObj
{
public:
	static const unsigned char STKWEBAPP_METHOD_UNDEFINED = 0x00;
	static const unsigned char STKWEBAPP_METHOD_GET = 0x01;
	static const unsigned char STKWEBAPP_METHOD_HEAD = 0x02;
	static const unsigned char STKWEBAPP_METHOD_POST = 0x04;
	static const unsigned char STKWEBAPP_METHOD_PUT = 0x08;
	static const unsigned char STKWEBAPP_METHOD_DELETE = 0x10;
	static const unsigned char STKWEBAPP_METHOD_INVALID = 0x20;

	static const int URL_PATH_LENGTH = 1024;

public:
	virtual StkObject* Execute(StkObject*, int, TCHAR[ApiObj::URL_PATH_LENGTH], int*);
};
