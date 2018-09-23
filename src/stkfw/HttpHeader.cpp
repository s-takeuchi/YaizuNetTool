#include <windows.h>
#include <tchar.h>
#include "server\VarController.h"
#include "MyMsgProc.h"
#include "server\LowDbAccess.h"

void HttpHeader(int CurrentId, int Type, HINSTANCE InstHndl, HWND WndHndl, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (message == WM_CREATE) {
	}
}
