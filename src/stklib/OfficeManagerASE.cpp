#include <windows.h>
#include <tchar.h>
#include "ActorStatus.h"
#include "ActorStatusElement.h"
#include "GameStatus.h"
#include "GameStatusElement.h"
#include "ActorRequest.h"
#include "OfficeASE.h"
#include "OfficeManagerASE.h"

int OfficeManagerASE::GridType;

OfficeManagerASE::OfficeManagerASE()
{
	m_StartPtX = m_StartPtY = m_EndPtX = m_EndPtY = -1;

	// Default ID of OfficeManagerASE
	m_Id = ACTOR_ID; 

	// Initialization of grid type
	GridType = 8;
}

OfficeManagerASE::~OfficeManagerASE()
{

}

// In case of some elements were selected and moved.
void OfficeManagerASE::MoveWithSelectedMany(ActorStatusElement* ase[], int ElementCount, GameStatus* gs, int Id, int mx, int my)
{
	for (int i = 0; i < ElementCount; i++) {
		if (ase[i] != NULL) {
			OfficeASE *OfcAse = dynamic_cast<OfficeASE*>(ase[i]);
			if (OfcAse != NULL) {
				if (OfcAse->GetId() != Id &&
					(OfcAse->GetSelection() == OfficeASE::SELECTED_MANY || OfcAse->GetSelection() == OfficeASE::SELECTED_CHANGEMANY)) {
					int x = OfcAse->GetActorPosX() + mx;
					int y = OfcAse->GetActorPosY() + my;
					x = x - x % GridType + GridType / 2;
					y = y - y % GridType + GridType / 2;
					GameStatusElement *gse = gs->GetGameStatusElement(gs->GetGameStatus());
					int left   = gse->GetActiveReverseScreenLeft();
					int right  = gse->GetActiveReverseScreenRight();
					int top    = gse->GetActiveReverseScreenTop();
					int bottom = gse->GetActiveReverseScreenBottom();
					if (x < left) {
						x = left;
					}
					if (x > right) {
						x = right;
					}
					if (y < top) {
						y = top;
					}
					if (y > bottom) {
						y = bottom;
					}
					OfcAse->SetActorPos(x, y);
				}
				if (OfcAse->GetId() == Id) {
					OfcAse->SetMoveDistance(0, 0);
				}
			}
		}
	}
}

// In case of only one element was selected.
void OfficeManagerASE::OnlyOneElementWasSpecified(ActorStatusElement* ase[], int ElementCount, int Id)
{
	for (int i = 0; i < ElementCount; i++) {
		if (ase[i] != NULL) {
			OfficeASE *OfcAse = dynamic_cast<OfficeASE*>(ase[i]);
			if (OfcAse != NULL) {
				if (OfcAse->GetId() == Id) {
					OfcAse->SetSelection(OfficeASE::SELECTED_ONE);
				} else {
					OfcAse->SetSelection(OfficeASE::SELECTED_NONE);
				}
			}
		}
	}
}

// In case of some elements were selected.
void OfficeManagerASE::SomeElementsWereSpecified(ActorStatusElement* ase[], int ElementCount)
{
	for (int i = 0; i < ElementCount; i++) {
		if (ase[i] != NULL) {
			OfficeASE *OfcAse = dynamic_cast<OfficeASE*>(ase[i]);
			if (OfcAse != NULL) {
				if (OfcAse->GetSelection() == OfficeASE::SELECTED_ONE ||
					OfcAse->GetSelection() == OfficeASE::SELECTED_CHANGEONE ||
					OfcAse->GetSelection() == OfficeASE::SELECTED_CHANGEMANY) {
						OfcAse->SetSelection(OfficeASE::SELECTED_MANY);
				}
			}
		}
	}
}

void OfficeManagerASE::ManagerAction(ActorStatusElement* ase[], int* ElementCount, GameStatus* gs)
{
}

void OfficeManagerASE::Action(ActorStatusElement* ase[], int* ElementCount, GameStatus* gs)
{
	// In case of a rectangle area was specfied using mouse operation, all of elements in the area become operation targets.
	if (m_StartPtX != -1 && m_StartPtY != -1 && m_EndPtX != -1 && m_EndPtY != -1) {
		GameStatusElement *gse = gs->GetGameStatusElement(gs->GetGameStatus());
		gse->AddRequest(-1, m_Id, ActorRequest::IGNORE_SAME_REQ_SAME_ACTOR, _T(""), _T(""), m_EndPtY, m_StartPtY, m_EndPtX, m_StartPtX);
		for (int i = 0; i < *ElementCount; i++) {
			if (ase[i] != NULL) {
				OfficeASE *OfcAse = dynamic_cast<OfficeASE*>(ase[i]);
				if (OfcAse != NULL) {
					if (OfcAse->GetMouseActionFlag() == FALSE) {
						continue;
					}
					if ((m_StartPtX == m_EndPtX) && (m_StartPtY == m_EndPtY)) {
						OfcAse->SetSelection(OfficeASE::SELECTED_NONE);
						continue;
					}
					if (((OfcAse->GetActorPosX() - m_StartPtX) * (OfcAse->GetActorPosX() - m_EndPtX) <= 0) &&
						((OfcAse->GetActorPosY() - m_StartPtY) * (OfcAse->GetActorPosY() - m_EndPtY) <= 0)) {
							OfcAse->SetSelection(OfficeASE::SELECTED_MANY);
					} else {
							OfcAse->SetSelection(OfficeASE::SELECTED_NONE);
					}
				}
			}
		}
	}

	for (int i = 0; i < *ElementCount; i++) {
		if (ase[i] != NULL) {
			OfficeASE *OfcAse = dynamic_cast<OfficeASE*>(ase[i]);
			if (OfcAse != NULL) {
				// In case of some elements were selected and moved.
				int mx = OfcAse->GetMoveDistanceX();
				int my = OfcAse->GetMoveDistanceY();
				if (mx != 0 || my != 0) {
					MoveWithSelectedMany(ase, *ElementCount, gs, OfcAse->GetId(), mx, my);
				}

				// In case of only one element was selected.
				if (OfcAse->GetSelection() == OfficeASE::SELECTED_CHANGEONE) {
					OnlyOneElementWasSpecified(ase, *ElementCount, OfcAse->GetId());
				}

				// In case of some elements were selected.
				if (OfcAse->GetSelection() == OfficeASE::SELECTED_CHANGEMANY) {
					SomeElementsWereSpecified(ase, *ElementCount);
				}

				// Clear manager specified area
				if (OfcAse->GetClearMgrAreaOpFlag()) {
					OfcAse->SetClearMgrAreaOpFlag(FALSE);
					m_StartPtX = m_StartPtY = m_EndPtX = m_EndPtY = -1;
				}
			}
		}
	}

	ManagerAction(ase, ElementCount, gs);
}

BOOL OfficeManagerASE::MouseAction(GameStatus* gs, int x, int y, int type, ActorStatusElement* ase[], int* ElementCount)
{
	// Left button was clicked down
	if (type == ActorStatus::LBUTTONDOWN) {
		SetCursor(LoadCursor(NULL, IDC_ARROW));
		m_StartPtX = x;
		m_StartPtY = y;
		m_EndPtX   = -1;
		m_EndPtY   = -1;
		return TRUE;
	}

	// Left button was clicked and moved
	if (type == ActorStatus::MOVELDOWN) {
		SetCursor(LoadCursor(NULL, IDC_ARROW));
		m_EndPtX = x;
		m_EndPtY = y;
		return TRUE;
	}

	// Left button was released
	if (type == ActorStatus::LBUTTONUP) {
		if ((m_StartPtX != x) || (m_StartPtY != y)) {
			m_StartPtX = -1;
			m_StartPtY = -1;
			m_EndPtX   = -1;
			m_EndPtY   = -1;
		} else {
			m_EndPtX = x;
			m_EndPtY = y;
		}
		return TRUE;
	}

	// When right button was released, pop up menu is appeared.
	if (type == ActorStatus::RBUTTONUP) {
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
	m_StartPtX = -1;
	m_StartPtY = -1;
	m_EndPtX   = -1;
	m_EndPtY   = -1;
	return FALSE;
}

void OfficeManagerASE::PopupMenuInit(HMENU MenuHndlTop, ActorStatusElement* ase[], int* ElementCount)
{
	HMENU MenuHndlAdd = CreatePopupMenu();
	AppendMenu(MenuHndlAdd, MF_STRING | MF_ENABLED | MF_UNCHECKED, 4001, _T("On"));
	AppendMenu(MenuHndlAdd, MF_STRING | MF_ENABLED | MF_UNCHECKED, 4002, _T("Off"));
	AppendMenu(MenuHndlTop, MF_POPUP | MF_STRING | MF_ENABLED | MF_UNCHECKED, (UINT_PTR)MenuHndlAdd, _T("Grid"));
}

void OfficeManagerASE::PopupMenuAction(int MenuId, int x, int y, ActorStatusElement* ase[], int* ElementCount)
{
	if (MenuId == 4001) {
		GridType = 8;
	} else if (MenuId == 4002) {
		GridType = 1;
	}
}
