#pragma once

#include <windows.h>

class ActorRequest
{
private:
	static const int STR_PARAM_SIZE = 64;

	int m_Request; // Request
	int m_ActorId; // Actor ID
	int m_ReqType; // Type of Request
	TCHAR m_StrParam1[STR_PARAM_SIZE]; // String parameter 1
	TCHAR m_StrParam2[STR_PARAM_SIZE]; // String parameter 2
	int m_IntParam1; // Integer parameter 1
	int m_IntParam2; // Integer parameter 2
	int m_IntParam3; // Integer parameter 3
	int m_IntParam4; // Integer parameter 4

public:
	static const int NORMAL                        = 0;
	static const int SYNCHRO                       = 10;
	static const int IGNORE_SAME_REQ_SAME_ACTOR    = 100;
	static const int IGNORE_SAME_REQ               = 101;
	static const int IGNORE_SAME_ACTOR             = 102;
	static const int OVERWRITE_SAME_REQ_SAME_ACTOR = 200;
	static const int OVERWRITE_SAME_REQ            = 201;
	static const int OVERWRITE_SAME_ACTOR          = 202;

	static BOOL SynchroFlag;

	ActorRequest(int, int, int, LPTSTR, LPTSTR, int, int, int, int);
	~ActorRequest(void);

	int GetRequest();
	void SetRequest(int);
	int GetActorId();
	void SetActorId(int);
	int GetRequestType();
	void SetRequestType(int);
	LPTSTR GetStringParam1();
	void SetStringParam1(LPTSTR);
	LPTSTR GetStringParam2();
	void SetStringParam2(LPTSTR);
	int GetIntParam1();
	void SetIntParam1(int);
	int GetIntParam2();
	void SetIntParam2(int);
	int GetIntParam3();
	void SetIntParam3(int);
	int GetIntParam4();
	void SetIntParam4(int);
};
