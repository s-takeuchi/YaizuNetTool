﻿#pragma once
#include <Windows.h>

class MyMsgProc
{
public:
	static const int STKFW_RUNNINGORPROPOPEN = 2101;
	static const int STKFW_OUTOFRANGE = 2102;
	static const int STKFW_DATASAVEFAILED = 2103;
	static const int STKFW_FILEINVALID = 2104;
	static const int STKFW_RUNNING = 2106;
	static const int STKFW_NODLL = 2107;
	static const int STKFW_DLLINVALID = 2108;
	static const int STKFW_ADD_PROCESSING_ELEMENT = 2110;
	static const int STKFW_DEL_PROCESSING_ELEMENT = 2111;
	static const int STKFW_ADD_LINK = 2112;
	static const int STKFW_DEL_LINK = 2113;
	static const int STKFW_DBVERSION_OLD = 2120;
	static const int STKFW_DBVERSION_UNKNOWN = 2121;
	static const int STKFW_COMPARAM_INVALID = 2123;
	static const int STKFW_COMPARAM_NOFILE = 2124;
	static const int STKFW_MANUAL_PLACE = 2125;
	static const int STKFW_CHG_WORKSPACE_SIZE = 2126;
	static const int STKFW_GRID_ONOFF = 2127;

	static const int VAR_SELECTEDNOTONE = 2201;
	static const int VAR_AREYOUSUREDELETE = 2202;
	static const int VAR_NOITEMSELECTED = 2203;
	static const int VAR_NOTTRANSUTF8 = 2204;
	static const int VAR_INVALIDNAME = 2205;
	static const int VAR_ALREADYDELETED = 2206;
	static const int VAR_INVALIDTYPE = 2207;
	static const int VAR_BUFOVERFLOW = 2208;
	static const int VAR_MAXVARSIZE = 2209;
	static const int VAR_FLAGVARNOT = 2210;
	static const int VAR_FOLDERSETERR = 2211;
	static const int VAR_EXPERR = 2212;
	static const int VAR_IMPERR = 2213;
	static const int VAR_NOIMPTARGET = 2214;
	static const int VAR_NOEXPTARGET = 2215;

	static const int PROP_NAME = 2300;
	static const int PROP_CHKDAT_START = 2301;
	static const int PROP_CHKDAT_NSTART = 2302;
	static const int PROP_CHKDAT_END = 2303;
	static const int PROP_CHKDAT_NEND = 2304;
	static const int PROP_CHKDAT_CONT = 2305;
	static const int PROP_CHKDAT_NCONT = 2306;
	static const int PROP_CHKDAT_EQUAL = 2307;
	static const int PROP_CHKDAT_NEQUAL = 2308;
	static const int PROP_CHGDAT_INSERT = 2311;
	static const int PROP_CHGDAT_JOIN = 2312;
	static const int PROP_CHGDAT_REPLACE = 2313;
	static const int PROP_CHGDAT_EXTRACT = 2314;
	static const int PROP_CHGDAT_DROP = 2315;
	static const int PROP_CHGDAT_RESET = 2316;
	static const int PROP_CLOSEPORT = 2320;
	static const int PROP_TIMER_PAST = 2321;
	static const int PROP_TIMER_WAIT = 2322;
	static const int PROP_TIMER_SEC = 2323;
	static const int PROP_MAP_SEARCH = 2324;
	static const int PROP_MAP_REPLACE = 2325;
	static const int PROP_MAP_START = 2326;
	static const int PROP_MAP_USEONCE = 2327;
	static const int PROP_CHECK_TRUE = 2331;
	static const int PROP_CHECK_FALSE = 2332;
	static const int PROP_CHANGE_TRUE = 2333;
	static const int PROP_CHANGE_FALSE = 2334;
	static const int PROP_LOAD_VAR = 2341;
	static const int PROP_LOAD_CONT = 2342;
	static const int PROP_STORE_VAR = 2343;
	static const int PROP_STORE_CONT = 2344;
	static const int PROP_DATA_COMM = 2345;
	static const int PROP_DATA_PREF = 2346;
	static const int PROP_DATA_NUM = 2347;
	static const int PROP_NET_RECV = 2351;
	static const int PROP_NET_RECVTGT = 2352;
	static const int PROP_NET_SEND = 2353;
	static const int PROP_NET_SENDTGT = 2354;
	static const int PROP_NET_CLOSE_AFTERSEND = 2355;
	static const int PROP_NET_CLOSE_AFTERRECV = 2356;
	static const int PROP_NET_TIMEOUT = 2357;
	static const int PROP_NET_SENDER = 2358;
	static const int PROP_NET_RECEIVER = 2359;
	static const int PROP_NET_ICON = 2360;
	static const int PROP_NET_IPADDR = 2361;
	static const int PROP_NET_PORT = 2362;
	static const int PROP_FILEACCESS_NAME = 2363;
	static const int PROP_FILEACCESSW_ADD = 2364;
	static const int PROP_FILEACCESSW_INSERT = 2365;
	static const int PROP_FILEACCESSW_OVERWRITE = 2366;
	static const int PROP_FILEACCESSR_ADD = 2367;
	static const int PROP_FILEACCESSR_INSERT = 2368;
	static const int PROP_FILEACCESSR_OVERWRITE = 2369;
	static const int PROP_EXECPROG_COMMAND = 2370;
	static const int PROP_EXECPROG_WAIT = 2371;
	static const int PROP_EXECPROG_CURRDIR = 2372;
	static const int PROP_EXECPROG_STDOUT = 2373;
	static const int PROP_EXECPROG_STDIN = 2374;
	static const int PROP_NET_UNCOND = 2375;
	static const int PROP_NET_EXCEEDSIZE = 2376;
	static const int PROP_NET_RECVSTR = 2377;
	static const int PROP_NET_TERMCOND = 2378;
	static const int PROP_NET_CLOSEDETECT = 2379;
	static const int PROP_NET_CLOSEFORCE = 2380;
	static const int PROP_NET_CLOSEUDPPORT = 2381;
	static const int PROP_NET_CLOSETCPPORT = 2382;
	static const int PROP_NET_PROCEEDEVENIFNODATARECV = 2383;
	static const int PROP_NET_RECVMULTI = 2384;
	static const int PROP_NET_HTTPCONTLEN = 2385;
	static const int PROP_NET_TIMEOUTINTERVAL = 2386;
	static const int PROP_HTTPHEADER_DELETEFROM = 2387;
	static const int PROP_HTTPHEADER_INSERTINTO = 2388;
	static const int PROP_HTTPHEADER_CONTLEN = 2389;
	static const int PROP_HTTPHEADER_DATE = 2390;
	static const int PROP_HTTPHEADER_REQUEST = 2391;
	static const int PROP_HTTPHEADER_RESPONSE = 2392;
	static const int PROP_NET_CHUNKOPTION = 2393;
	static const int PROP_NET_ALL_CHUNKS_NOCONT = 2394;
	static const int PROP_NET_SINGLE_CHUNK_NOCONT = 2395;
	static const int PROP_NET_ALL_CHUNKS_CONT = 2396;
	static const int PROP_NET_SINGLE_CHUNK_CONT = 2397;
	static const int PROP_NET_SSLTLS = 2398;
	static const int PROP_NET_SSLTLS_PATH_TO_SVR_CRT = 2399;
	static const int PROP_NET_SSLTLS_PATH_TO_KEYFILE = 2400;
	static const int PROP_NET_SSLTLS_PATH_TO_CA_CRT = 2401;

	static const int STKFW_LOG_TITLE = 2490;
	static const int STKFW_LOG_START = 2491;
	static const int STKFW_LOG_STOP = 2492;

	// 2500 - 2899 : Reserved by server code

	static const int FILEACCESSERROR = 2902;
	static const int NEEDADMINRIGHTS = 2903;
	static const int DATAUPDATED = 2904;
	static const int COMMON_ADD = 2931;
	static const int COMMON_DELETE = 2932;
	static const int COMMON_EDIT = 2933;
	static const int COMMON_REFRESH = 2934;
	static const int COMMON_TRUE = 2935;
	static const int COMMON_FALSE = 2936;
	static const int COMMON_UNKNOWN = 2937;
	static const int COMMON_OK = 2941;
	static const int COMMON_CANCEL = 2942;

	static const int SFW_100_1 = 9100;
	static const int SFW_100_110_1 = 9101;
	static const int SFW_100_110_2 = 9102;
	static const int SFW_100_110_3 = 9103;
	static const int SFW_100_110_4 = 9104;
	static const int SFW_100_110_5 = 9105;
	static const int SFW_100_110_6 = 9106;
	static const int SFW_110_120_1 = 9107;
	static const int SFW_110_120_2 = 9108;
	static const int SFW_110_120_3 = 9109;
	static const int SFW_110_120_4 = 9110;
	static const int SFW_110_120_5 = 9111;
	static const int SFW_110_120_6 = 9112;
	static const int SFW_110_120_7 = 9113;
	static const int SFW_110_120_8 = 9114;
	static const int SFW_120_130_1 = 9115;
	static const int SFW_120_130_2 = 9116;
	static const int SFW_120_130_3 = 9117;
	static const int SFW_120_130_4 = 9118;
	static const int SFW_130_140_1 = 9119;
	static const int SFW_130_140_2 = 9120;
	static const int SFW_130_140_3 = 9121;
	static const int SFW_130_140_4 = 9122;
	static const int SFW_130_140_5 = 9123;
	static const int SFW_130_140_6 = 9124;
	static const int SFW_140_150_1 = 9125;
	static const int SFW_140_150_2 = 9126;
	static const int SFW_140_150_3 = 9127;
	static const int SFW_140_150_4 = 9128;
	static const int SFW_140_150_5 = 9129;
	static const int SFW_140_150_6 = 9130;
	static const int SFW_150_160_1 = 9131;
	static const int SFW_150_160_2 = 9132;
	static const int SFW_150_160_3 = 9133;
	static const int SFW_160_170_1 = 9134;
	static const int SFW_160_170_2 = 9135;
	static const int SFW_160_170_3 = 9136;
	static const int SFW_160_170_4 = 9137;
	static const int SFW_160_170_5 = 9138;

	static void AddMsg();
	static TCHAR* GetMsg(int);
	static void StkErr(int, HWND);
	static void StkErr(int, TCHAR*, HWND);
	static void StkInf(int, HWND);
	static void StkInf(int, TCHAR*, HWND);
	static int StkYesNo(int, HWND);
	static int StkYesNo(int, TCHAR*, HWND);
};
