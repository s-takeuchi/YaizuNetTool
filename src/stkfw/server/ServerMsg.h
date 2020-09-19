#pragma once
#include <tchar.h>

class ServerMsg
{
public:
	static const int STKFW_LOG_SUCCESSCSC = 2503;
	static const int STKFW_LOG_SUCCESSCSBNLS = 2504;
	static const int STKFW_LOG_SOCKCLOSE = 2505;
	static const int STKFW_LOG_ACPTRECV = 2506;
	static const int STKFW_LOG_CNCTRECV = 2507;
	static const int STKFW_LOG_ACPTSEND = 2508;
	static const int STKFW_LOG_CNCTSEND = 2509;
	static const int STKFW_LOG_SENDERROR = 2510;
	static const int STKFW_LOG_RECVERROR = 2511;
	static const int STKFW_LOG_NAMESOLVEERR = 2512;
	static const int STKFW_LOG_CONNERROR = 2513;
	static const int STKFW_LOG_BINDLISTENERR = 2514;
	static const int STKFW_LOG_CREATEACCEPTSOCK = 2515;
	static const int STKFW_LOG_CLOSEACCEPTSOCK = 2516;
	static const int STKFW_LOG_CLOSELISTENACCEPTSOCK = 2517;
	static const int STKFW_LOG_BINDERR = 2518;
	static const int STKFW_LOG_SUCCESSCSBN = 2519;
	static const int STKFW_LOG_UDPRECV = 2520;
	static const int STKFW_LOG_UDPSEND = 2521;
	static const int STKFW_LOG_SUCCESSCS = 2522;
	static const int STKFW_LOG_UDPSOCKCLOSE = 2523;
	static const int STKFW_LOG_UNKNOWN = 2524;
	static const int STKFW_LOG_PRIVATEKEYLOAD = 2525;
	static const int STKFW_LOG_SERVERCERTLOAD = 2526;
	static const int STKFW_LOG_CACERTLOAD = 2527;

	static void AddMsg();
	static TCHAR* GetMsg(int);
};
