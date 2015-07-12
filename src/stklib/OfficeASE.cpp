#include <windows.h>
#include <tchar.h>
#include "ActorStatus.h"
#include "ActorStatusElement.h"
#include "GameStatus.h"
#include "GameStatusElement.h"
#include "ActorRequest.h"
#include "OfficeASE.h"
#include "OfficeManagerASE.h"

OfficeASE::OfficeASE()
{
	m_PreviousMouseActionType = PMA_TYPE_NOTSPECIAL;
	m_Selection = SELECTED_NONE;
	m_ClearSelection = FALSE;
	m_dx = 0;
	m_dy = 0;
	m_ClearMgrAreaOpFlag = FALSE;
}

OfficeASE::~OfficeASE()
{

}

// Getting vertical distance of moving
int OfficeASE::GetMoveDistanceX(void)
{
	return m_dx;
}

// Getting horizontal distance of moving
int OfficeASE::GetMoveDistanceY(void)
{
	return m_dy;
}

// Setting distance of moving
void OfficeASE::SetMoveDistance(int mx, int my)
{
	m_dx = mx;
	m_dy = my;
}

// Functions for getting selection
int OfficeASE::GetSelection()
{
	return m_Selection;
}

// Functions for setting selection
void OfficeASE::SetSelection(int Selection)
{
	m_Selection = Selection;
}

void OfficeASE::Action(ActorStatusElement* ase[], int* ElementCount, GameStatus* gs)
{
	GameStatusElement *gse = gs->GetGameStatusElement(gs->GetGameStatus());
	gse->AddRequest(m_Selection, m_Id, ActorRequest::IGNORE_SAME_REQ_SAME_ACTOR, _T(""), _T(""), m_y + m_bottom, m_y + m_top, m_x + m_right, m_x + m_left);
}

BOOL OfficeASE::MouseAction(GameStatus* gs, int x, int y, int type, ActorStatusElement* ase[], int* ElementCount)
{
	// When left button was double-clicked, DoubleClickAction() is called.
	if (type == ActorStatus::LBUTTONDBLCLK) {
		m_Selection = SELECTED_CHANGEONE;
		DoubleClickAction();
		return TRUE;
	}

	// When mouse cursor was move through on the element, the cursor image is changed.
	if (type == ActorStatus::MOVE) {
		SetCursor(LoadCursor(NULL, IDC_HAND));
		m_PreviousMouseActionType = PMA_TYPE_NOTSPECIAL;
		return TRUE;
	}

	// When the element was selected and moved, variables for move distance are changed.
	if (type == ActorStatus::MOVELDOWN &&
		(m_PreviousMouseActionType == PMA_TYPE_LBUTTONDOWN || m_PreviousMouseActionType == PMA_TYPE_MOVELDOWN)) {
		SetCursor(LoadCursor(NULL, IDC_HAND));
		m_dx += ((x - x % OfficeManagerASE::GridType) - m_x + OfficeManagerASE::GridType / 2);	
		m_dy += ((y - y % OfficeManagerASE::GridType) - m_y + OfficeManagerASE::GridType / 2);
		m_x = x - x % OfficeManagerASE::GridType + OfficeManagerASE::GridType / 2;
		m_y = y - y % OfficeManagerASE::GridType + OfficeManagerASE::GridType / 2;
		m_ClearSelection = FALSE;
		m_PreviousMouseActionType = PMA_TYPE_MOVELDOWN;
		return TRUE;
	}

	// Left button was clicked down.
	if (type == ActorStatus::LBUTTONDOWN) {
		SetCursor(LoadCursor(NULL, IDC_HAND));
		if (m_Selection == SELECTED_NONE) {
			m_Selection = SELECTED_CHANGEONE;
		}
		m_PreviousMouseActionType = PMA_TYPE_LBUTTONDOWN;
		return TRUE;
	}

	// Left button was clicked down while shift key had been pushed.
	if (type == ActorStatus::LBUTTONDOWN_S) {
		SetCursor(LoadCursor(NULL, IDC_HAND));
		if (m_Selection != SELECTED_MANY) {
			m_Selection = SELECTED_CHANGEMANY;
			m_ClearSelection = FALSE;
		} else {
			m_ClearSelection = TRUE;
		}
		m_PreviousMouseActionType = PMA_TYPE_LBUTTONDOWN;
		return TRUE;
	}

	// Left button was released.
	if (type == ActorStatus::LBUTTONUP) {
		SetCursor(LoadCursor(NULL, IDC_HAND));
		if (m_Selection != SELECTED_ONE && m_PreviousMouseActionType != PMA_TYPE_MOVELDOWN) {
			m_Selection = SELECTED_CHANGEONE;
		}
		m_ClearMgrAreaOpFlag = TRUE;
		m_PreviousMouseActionType = PMA_TYPE_NOTSPECIAL;
		return TRUE;
	}

	// Left button was released while shift key had been pushed.
	if (type == ActorStatus::LBUTTONUP_S) {
		SetCursor(LoadCursor(NULL, IDC_HAND));
		if (m_ClearSelection == TRUE) {
			m_Selection = SELECTED_NONE;
			m_ClearSelection = FALSE;
		}
		m_ClearMgrAreaOpFlag = TRUE;
		m_PreviousMouseActionType = PMA_TYPE_NOTSPECIAL;
		return TRUE;
	}

	// When right button was released, pop up menu is appeared.
	if (type == ActorStatus::RBUTTONUP) {
		if (m_Selection == SELECTED_NONE) {
			m_Selection = SELECTED_CHANGEONE;
		}
		m_PreviousMouseActionType = PMA_TYPE_NOTSPECIAL;

		HMENU MenuHndl = CreatePopupMenu();
		PopupMenuInit(MenuHndl, ase, ElementCount);

		POINT pt;
		GetCursorPos(&pt);
		int Ret = TrackPopupMenu(MenuHndl, TPM_LEFTALIGN | TPM_RETURNCMD | TPM_NONOTIFY, pt.x, pt.y, 0, gs->GetHWnd(), NULL);
		DestroyMenu(MenuHndl);
		if (Ret != 0) {
			PopupMenuAction(Ret, x, y, ase, ElementCount);
		}
		return TRUE;
	}

	// When other mouse action was presented, process below is invoked.
	m_PreviousMouseActionType = PMA_TYPE_NOTSPECIAL;
	return FALSE;
}

void OfficeASE::PopupMenuInit(HMENU MenuHndlTop, ActorStatusElement* ase[], int* ElementCount)
{
	HMENU MenuHndlAdd = CreatePopupMenu();
	AppendMenu(MenuHndlAdd, MF_STRING | MF_ENABLED | MF_UNCHECKED, 1, _T("Item 1"));
	AppendMenu(MenuHndlAdd, MF_STRING | MF_ENABLED | MF_UNCHECKED, 2, _T("Item 2"));
	AppendMenu(MenuHndlAdd, MF_STRING | MF_ENABLED | MF_UNCHECKED, 3, _T("Item 3"));
	AppendMenu(MenuHndlTop, MF_POPUP | MF_STRING | MF_ENABLED | MF_UNCHECKED, (UINT_PTR)MenuHndlAdd, _T("Add"));
	AppendMenu(MenuHndlTop, MF_STRING | MF_ENABLED | MF_UNCHECKED, 4, _T("Properties"));
}

void OfficeASE::PopupMenuAction(int MenuId, int x, int y, ActorStatusElement* ase[], int* ElementCount)
{
	MessageBox(NULL, _T("Popup menu item was clicked."), _T("OfficeASE"), MB_OK);
}

void OfficeASE::DoubleClickAction()
{
	MessageBox(NULL, _T("Double clicked."), _T("OfficeASE"), MB_OK);
}

// Getting flag for clearing manager specified area
BOOL OfficeASE::GetClearMgrAreaOpFlag(void)
{
	return m_ClearMgrAreaOpFlag;
}

// Setting flag for clearing manager specified area
void OfficeASE::SetClearMgrAreaOpFlag(BOOL ClrMgrOpFlag)
{
	m_ClearMgrAreaOpFlag = ClrMgrOpFlag;
}
