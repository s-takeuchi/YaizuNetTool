#pragma once
#include <windows.h>
#include "..\stklib\OfficeGSE.h"

class NetGseEx : public OfficeGSE  
{
protected:
	HICON IconHndl[100];

public:
	// "CritSect" avoids to execute "Running process", "Start thread sequence" and "Stop thread sequence" simultaneously.
	static CRITICAL_SECTION CritSect;

	// RunTime Information
	static int RtiRefreshInterval;
	static int RtiElementCount;
	static int RtiRequestCount;
	static int RtiRunningCount;

	NetGseEx();
	virtual ~NetGseEx();

	void DrawOfficeASELink(HINSTANCE, HWND, HDC, ActorRequest*);
	virtual void DrawOfficeASE(HINSTANCE, HWND, HDC, ActorRequest*);
	virtual void RefreshScreenProcess(HINSTANCE, HWND, HDC);
};
