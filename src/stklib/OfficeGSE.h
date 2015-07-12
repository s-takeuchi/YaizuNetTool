#pragma once

#include <windows.h>
#include "ActorRequest.h"
#include "GameStatusElement.h"

class OfficeGSE : public GameStatusElement  
{
public:
	OfficeGSE();
	virtual ~OfficeGSE();

	virtual void DrawBackground(HINSTANCE, HWND, HDC);
	virtual void DrawOfficeASE(HINSTANCE, HWND, HDC, ActorRequest*);
	virtual void DrawOfficeManagerASE(HINSTANCE, HWND, HDC, ActorRequest*);

	// A function which is called from RefreshScreen
	virtual void RefreshScreenProcess(HINSTANCE, HWND, HDC);
};
