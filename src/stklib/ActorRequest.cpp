#include "windows.h"
#include "ActorRequest.h"

BOOL ActorRequest::SynchroFlag;

ActorRequest::ActorRequest(int Req, int ActorId, int ReqType, LPTSTR StrParam1, LPTSTR StrParam2, int IntParam1, int IntParam2, int IntParam3, int IntParam4)
{
	m_Request = Req;
	m_ActorId = ActorId;
	m_ReqType = ReqType;
	lstrcpy(m_StrParam1, StrParam1);
	lstrcpy(m_StrParam2, StrParam2);
	m_IntParam1 = IntParam1;
	m_IntParam2 = IntParam2;
	m_IntParam3 = IntParam3;
	m_IntParam4 = IntParam4;
	SynchroFlag = FALSE;
}

ActorRequest::~ActorRequest(void)
{
}

int ActorRequest::GetRequest()
{
	return m_Request;
}

void ActorRequest::SetRequest(int Req)
{
	m_Request = Req;
}

int ActorRequest::GetActorId()
{
	return m_ActorId;
}

void ActorRequest::SetActorId(int ActorId)
{
	m_ActorId = ActorId;
}

int ActorRequest::GetRequestType()
{
	return m_ReqType;
}

void ActorRequest::SetRequestType(int ReqType)
{
	m_ReqType = ReqType;
}

LPTSTR ActorRequest::GetStringParam1()
{
	return m_StrParam1;
}

void ActorRequest::SetStringParam1(LPTSTR StrParam1)
{
	lstrcpyn(m_StrParam1, StrParam1, ActorRequest::STR_PARAM_SIZE - 1);
}

LPTSTR ActorRequest::GetStringParam2()
{
	return m_StrParam2;
}

void ActorRequest::SetStringParam2(LPTSTR StrParam2)
{
	lstrcpyn(m_StrParam2, StrParam2, ActorRequest::STR_PARAM_SIZE - 1);
}

int ActorRequest::GetIntParam1()
{
	return m_IntParam1;
}

void ActorRequest::SetIntParam1(int IntParam1)
{
	m_IntParam1 = IntParam1;
}

int ActorRequest::GetIntParam2()
{
	return m_IntParam2;
}

void ActorRequest::SetIntParam2(int IntParam2)
{
	m_IntParam2 = IntParam2;
}

int ActorRequest::GetIntParam3()
{
	return m_IntParam3;
}

void ActorRequest::SetIntParam3(int IntParam3)
{
	m_IntParam3 = IntParam3;
}

int ActorRequest::GetIntParam4()
{
	return m_IntParam4;
}

void ActorRequest::SetIntParam4(int IntParam4)
{
	m_IntParam4 = IntParam4;
}
