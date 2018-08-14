#include <tchar.h>
#include "..\..\..\..\YaizuComLib\src\\commonfunc\msgproc.h"
#include "ServerMsg.h"

void ServerMsg::AddMsg()
{
	// =====================================================================================================
	// 2503 (NC3)
	MessageProc::AddJpn(STKFW_LOG_SUCCESSCSC, _T("ソケットの生成およびCONNECTに成功しました。"));
	MessageProc::AddEng(STKFW_LOG_SUCCESSCSC, _T("Creation of socket and connection succeeded."));

	// 2504 (NC3)
	MessageProc::AddJpn(STKFW_LOG_SUCCESSCSBNLS, _T("ソケットの生成，BINDおよびLISTENに成功しました。"));
	MessageProc::AddEng(STKFW_LOG_SUCCESSCSBNLS, _T("Creation of socket, binding and listening succeeded."));

	// 2505 (NC3)
	MessageProc::AddJpn(STKFW_LOG_SOCKCLOSE, _T("ソケットのクローズに成功しました。"));
	MessageProc::AddEng(STKFW_LOG_SOCKCLOSE, _T("Closure of socket succeeded."));

	// 2506 (NC3)
	MessageProc::AddJpn(STKFW_LOG_ACPTRECV, _T("ACCEPT用ソケットでデータを受信しました。"));
	MessageProc::AddEng(STKFW_LOG_ACPTRECV, _T("Data received using the accepting socket."));

	// 2507 (NC3)
	MessageProc::AddJpn(STKFW_LOG_CNCTRECV, _T("接続中のソケットでデータが返信されました。"));
	MessageProc::AddEng(STKFW_LOG_CNCTRECV, _T("Data returned using the communicating socket."));

	// 2508 (NC3)
	MessageProc::AddJpn(STKFW_LOG_ACPTSEND, _T("接続中のソケットでデータを返信しました。"));
	MessageProc::AddEng(STKFW_LOG_ACPTSEND, _T("Data sent back using the communicating socket."));

	// 2509 (NC3)
	MessageProc::AddJpn(STKFW_LOG_CNCTSEND, _T("CONNECTしたソケットでデータを送信しました。"));
	MessageProc::AddEng(STKFW_LOG_CNCTSEND, _T("Data sent using the connected socket."));

	// 2510 (NC3)
	MessageProc::AddJpn(STKFW_LOG_SENDERROR, _T("データ送信時にエラーが発生しました。"));
	MessageProc::AddEng(STKFW_LOG_SENDERROR, _T("An error occurred during data transmission."));

	// 2511 (NC3)
	MessageProc::AddJpn(STKFW_LOG_RECVERROR, _T("データ受信時にエラーが発生しました。"));
	MessageProc::AddEng(STKFW_LOG_RECVERROR, _T("An error occurred during data receipt."));

	// 2512 (NC3)
	MessageProc::AddJpn(STKFW_LOG_NAMESOLVEERR, _T("指定されたホスト名の解決に失敗しました。"));
	MessageProc::AddEng(STKFW_LOG_NAMESOLVEERR, _T("Resolution of the specified host name failed."));

	// 2513 (NC3)
	MessageProc::AddJpn(STKFW_LOG_CONNERROR, _T("指定されたホストへの接続に失敗しました。"));
	MessageProc::AddEng(STKFW_LOG_CONNERROR, _T("Connection to the specified host failed."));

	// 2514 (NC3)
	MessageProc::AddJpn(STKFW_LOG_BINDLISTENERR, _T("BINDまたはLISTENに失敗しました。"));
	MessageProc::AddEng(STKFW_LOG_BINDLISTENERR, _T("Binding or listening failed."));

	// 2515 (NC3)
	MessageProc::AddJpn(STKFW_LOG_CREATEACCEPTSOCK, _T("ACCEPT用ソケットの生成に成功しました。"));
	MessageProc::AddEng(STKFW_LOG_CREATEACCEPTSOCK, _T("Creation of accepting socket succeeded."));

	// 2516 (NC3)
	MessageProc::AddJpn(STKFW_LOG_CLOSEACCEPTSOCK, _T("ACCEPT用ソケットのクローズに成功しました。"));
	MessageProc::AddEng(STKFW_LOG_CLOSEACCEPTSOCK, _T("Closure of accepting socket succeeded."));

	// 2517 (NC5)
	MessageProc::AddJpn(STKFW_LOG_CLOSELISTENACCEPTSOCK, _T("ACCEPT用ソケットおよびLISTEN用ソケットのクローズに成功しました。"));
	MessageProc::AddEng(STKFW_LOG_CLOSELISTENACCEPTSOCK, _T("Closure of accept/listen sockets succeeded."));

	// 2518 (NC5)
	MessageProc::AddJpn(STKFW_LOG_BINDERR, _T("BINDに失敗しました。"));
	MessageProc::AddEng(STKFW_LOG_BINDERR, _T("Binding to port failed."));

	// 2519 (NC5)
	MessageProc::AddJpn(STKFW_LOG_SUCCESSCSBN, _T("UDPソケットの生成およびBINDに成功しました。"));
	MessageProc::AddEng(STKFW_LOG_SUCCESSCSBN, _T("Creation of socket and binding succeeded."));

	// 2520 (NC5)
	MessageProc::AddJpn(STKFW_LOG_UDPRECV, _T("UDPソケットでデータを受信しました。"));
	MessageProc::AddEng(STKFW_LOG_UDPRECV, _T("Data received using UDP socket."));

	// 2521 (NC5)
	MessageProc::AddJpn(STKFW_LOG_UDPSEND, _T("UDPソケットでデータを送信しました。"));
	MessageProc::AddEng(STKFW_LOG_UDPSEND, _T("Data sent using UDP socket."));

	// 2522 (NC5)
	MessageProc::AddJpn(STKFW_LOG_SUCCESSCS, _T("UDPソケットの生成に成功しました。"));
	MessageProc::AddEng(STKFW_LOG_SUCCESSCS, _T("Creation of UDP socket succeeded."));

	// 2523 (NC5)
	MessageProc::AddJpn(STKFW_LOG_UDPSOCKCLOSE, _T("UDPソケットのクローズに成功しました。"));
	MessageProc::AddEng(STKFW_LOG_UDPSOCKCLOSE, _T("Closure of UDP socket succeeded."));

	// 2524 (NC5)
	MessageProc::AddJpn(STKFW_LOG_UNKNOWN, _T("不明"));
	MessageProc::AddEng(STKFW_LOG_UNKNOWN, _T("Unknown"));

	// =====================================================================================================
}

TCHAR* ServerMsg::GetMsg(int Id)
{
	return MessageProc::GetMsg(Id);
}
