#pragma once
#include "..\..\..\..\YaizuComLib\src\commonfunc\StkObject.h"

class ApiObj
{
public:
	static const unsigned char METHOD_UNDEFINED = 0x00;
	static const unsigned char METHOD_GET = 0x01;
	static const unsigned char METHOD_HEAD = 0x02;
	static const unsigned char METHOD_POST = 0x04;
	static const unsigned char METHOD_PUT = 0x08;
	static const unsigned char METHOD_DELETE = 0x10;
	static const unsigned char METHOD_INVALID = 0x20;

	static const int URL_PATH_LENGTH = 1024;

public:
	virtual StkObject* Execute(StkObject*, int, wchar_t[ApiObj::URL_PATH_LENGTH], int*) = 0;
	static ApiObj* CreateObject(int, wchar_t[ApiObj::URL_PATH_LENGTH]);
};
