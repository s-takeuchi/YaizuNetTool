#include "..\stklib\ActorStatus.h"
#include "NetAseEx.h"
#include "NetManagerAseEx.h"
#include "stklibtest.h"
#include "..\..\com\\msgproc\msgproc.h"
#include "LowDbAccess.h"


NetManagerAseEx::NetManagerAseEx()
{
}

void NetManagerAseEx::ManagerAction(ActorStatusElement* ase[], int* ElementCount, GameStatus* gs)
{
}

void NetManagerAseEx::PopupMenuInit(HMENU MenuHndlTop, ActorStatusElement* ase[], int* ElementCount)
{
	HMENU MenuHndlAdd = CreatePopupMenu();
	HMENU MenuHndlMenu[20];
	for (int Loop = 0; Loop < 20; Loop++) {
		MenuHndlMenu[Loop] = CreatePopupMenu();
	}

	int VeType[100];
	TCHAR VeTypeName[100][256];
	TCHAR VeCatName[100][256];
	int VeCount = LowDbAccess::GetInstance()->GetViewElementMenus(VeType, VeTypeName, VeCatName);

	AppendMenu(MenuHndlTop, MF_POPUP | MF_STRING | MF_ENABLED | MF_UNCHECKED, (UINT_PTR)MenuHndlAdd, MessageProc::GetMsg(MessageProc::STKFW_ADD_PROCESSING_ELEMENT));

	int MenuCategoryCount = 0;
	TCHAR MenuCategoryName[20][256];

	for (int LoopVe = 0; LoopVe < VeCount; LoopVe++) {
		int FndIndex;

		// Check whether the MenuCategoryName contains the target string or not.
		// If target is found, FndCetegoryName = TRUE is set.
		BOOL FndCategoryName = FALSE;
		for (int Loop = 0; Loop < MenuCategoryCount; Loop++) {
			if (lstrcmp(MenuCategoryName[Loop], VeCatName[LoopVe]) == 0) {
				FndCategoryName = TRUE;
				FndIndex = Loop;
				break;
			}
		}
		if (FndCategoryName == FALSE && MenuCategoryCount < 20) {
			lstrcpy(MenuCategoryName[MenuCategoryCount], VeCatName[LoopVe]);
			// Menu category added
			AppendMenu(MenuHndlAdd, MF_POPUP | MF_STRING | MF_ENABLED | MF_UNCHECKED, (UINT_PTR)MenuHndlMenu[MenuCategoryCount], VeCatName[LoopVe]);
			FndIndex = MenuCategoryCount;
			MenuCategoryCount++;
		}
		if (FndIndex < 20) {
			AppendMenu(MenuHndlMenu[FndIndex], MF_STRING | MF_ENABLED | MF_UNCHECKED, VeType[LoopVe], VeTypeName[LoopVe]);
		}
	}

	// Grid menu
	HMENU MenuHndlGrid = CreatePopupMenu();
	AppendMenu(MenuHndlGrid, MF_STRING | MF_ENABLED | MF_UNCHECKED, 4001, _T("On"));
	AppendMenu(MenuHndlGrid, MF_STRING | MF_ENABLED | MF_UNCHECKED, 4002, _T("Off"));
	AppendMenu(MenuHndlTop, MF_POPUP | MF_STRING | MF_ENABLED | MF_UNCHECKED, (UINT_PTR)MenuHndlGrid, MessageProc::GetMsg(MessageProc::STKFW_GRID_ONOFF));

	// Workspace size change menu
	AppendMenu(MenuHndlTop, MF_POPUP | MF_STRING | MF_ENABLED | MF_UNCHECKED, (UINT_PTR)4003, MessageProc::GetMsg(MessageProc::STKFW_CHG_WORKSPACE_SIZE));
}

void NetManagerAseEx::PopupMenuAction(int MenuId, int x, int y, ActorStatusElement* ase[], int* ElementCount)
{
	// Write grid information
	if (MenuId == 4001 || MenuId == 4002) {
		if (MenuId == 4001) {
			GridType = 8;
		} else if (MenuId == 4002) {
			GridType = 1;
		}

		LowDbAccess::GetInstance()->SetWorkspaceGridType(GridType);
		return;
	}
	if (MenuId == 4003) {
		SetViewToDb();
		if (ResetWorkspace(4) == 0) {
			GetViewFromDb();
		}
		return;
	}

	// Add new element
	// Read Icon ID from database
	int IcnId = LowDbAccess::GetInstance()->GetIconTypeByViewElementType(MenuId);

	// Create new element
	NetAseEx* NewNetAseEx = new NetAseEx();
	NewNetAseEx->EnableAction();
	NewNetAseEx->EnableMouseAction();
	NewNetAseEx->SetActorPos(x - x % GridType + GridType / 2, y - y % GridType + GridType / 2);
	if (IcnId >= 50 && IcnId < 70) {
		NewNetAseEx->SetActorRect(8, -8, 8, -8);
	} else {
		NewNetAseEx->SetActorRect(16, -16, 16, -16);
	}
	NewNetAseEx->SetType(MenuId);
	NewNetAseEx->SetIconId(IcnId);

	if (*ElementCount < ActorStatus::ACTOR_STATUS_COUNT) {
		static int MaxId = 1;
		MaxId = LowDbAccess::GetInstance()->GetPropertyInteger(_T("MaxId"), 1);
		NewNetAseEx->SetId(MaxId);
		TCHAR Buf[32];
		wsprintf(Buf, _T("%05d"), MaxId);
		NewNetAseEx->SetName(Buf);
		ase[*ElementCount] = NewNetAseEx;
		(*ElementCount)++;
		MaxId++;
		LowDbAccess::GetInstance()->SetPropertyInteger(_T("MaxId"), 1, MaxId);
		ResetThreadController(FALSE);
	} else {
		delete NewNetAseEx;
	}
}
