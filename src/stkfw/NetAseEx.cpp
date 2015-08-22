#include <stdlib.h>
#include <shlwapi.h>
#include "NetAseEx.h"
#include "stklibtest.h"
#include "MyMsgProc.h"
#include "stkprop.h"
#include "LowDbAccess.h"

NetAseEx::NetAseEx()
{
	for (int Loop = 0; Loop < 10; Loop++) {
		LinkTo[Loop] = -1;
		LinkType[Loop] = 101;
	}
	LinkCount = 0;
	m_Type = 1;
	m_Icon = 1;
	lstrcpy(m_Name, _T(""));
}

NetAseEx::~NetAseEx()
{
}

int NetAseEx::GetType()
{
	return m_Type;
}

void NetAseEx::SetType(int Typ)
{
	m_Type = Typ;
}

int NetAseEx::GetIconId()
{
	return m_Icon;
}

void NetAseEx::SetIconId(int Icn)
{
	m_Icon = Icn;
}

TCHAR* NetAseEx::GetName()
{
	return m_Name;
}

void NetAseEx::SetName(TCHAR* Nm)
{
	lstrcpy(m_Name, Nm);
}

void NetAseEx::Action(ActorStatusElement* Ase[], int* ElementCount, GameStatus* Gs)
{
	//////////////////////////////////////////////////////////////////
	// Register element information
	GameStatusElement *Gse = Gs->GetGameStatusElement(Gs->GetGameStatus());

	for (int Loop = 0; Loop < LinkCount; Loop++) {
		int Target = LinkTo[Loop];
		int xx = Ase[Target]->GetActorPosX();
		int yy = Ase[Target]->GetActorPosY();
		Gse->AddRequest(LinkType[Loop], m_Id, ActorRequest::SYNCHRO, _T(""), _T(""), m_x, m_y, xx, yy);
	}

	Gse->AddRequest((m_Selection == 0)? m_Icon : m_Icon * -1, m_Id, ActorRequest::SYNCHRO, m_Name, _T(""), m_y + m_bottom, m_y + m_top, m_x + m_right, m_x + m_left);
}

void NetAseEx::PopupMenuInit(HMENU MenuHndlTop, ActorStatusElement* Ase[], int* ElementCount)
{
	UINT AddLinkMenuType = MF_STRING | MF_ENABLED | MF_UNCHECKED;
	UINT DelLinkMenuType = MF_STRING | MF_ENABLED | MF_UNCHECKED;

	// Check whether "Add Link" and "Delete Link" menu items are available.
	if (GetSelection() != OfficeASE::SELECTED_MANY) {
		// If user does not specify the current element with few other element,
		// the menu items are not activated.
		AddLinkMenuType |= MF_GRAYED;
		DelLinkMenuType |= MF_GRAYED;
	} else {
		/////////////////////////////////////////////////////////////
		// Check whether all of selected elements are linked to current element.
		// If true, "Delete Link" is available.
		BOOL FndFlg = FALSE;
		int ElCnt = 0;
		for (int LoopEle = 0; LoopEle < *ElementCount; LoopEle++) {
			int AseId = Ase[LoopEle]->GetId();
			if (AseId == 0 || AseId == m_Id) {
				continue;
			}
			NetAseEx* Nase = reinterpret_cast<NetAseEx*>(Ase[LoopEle]);
			if (Nase->GetSelection() == OfficeASE::SELECTED_MANY) {
				ElCnt++;
				FndFlg = FALSE;
				for (int LoopLnk = 0; LoopLnk < LinkCount; LoopLnk++) {
					if (LinkTo[LoopLnk] == LoopEle) {
						FndFlg = TRUE;
					}
				}
				if (FndFlg == FALSE) {
					break;
				}
			}
		}
		if (ElCnt == 0) {
			AddLinkMenuType |= MF_GRAYED;
		}
		if (FndFlg == FALSE) {
			DelLinkMenuType |= MF_GRAYED;
		}

		/////////////////////////////////////////////////////////////
		// Check LinkCond and show "Add Link" menu item.

		// リポジトリからProperty.LinkInfoを読込み，LinkCondを初期化する。
		int TmpLinkFm[500];
		int TmpLinkTo[500];
		int TmpLinkCt[500];
		int TmpLinkTp[500];
		LinkCondCount = LowDbAccess::GetInstance()->GetAllLinkInfos(TmpLinkFm, TmpLinkTo, TmpLinkCt, TmpLinkTp);
		for (int Loop = 0; Loop < LinkCondCount; Loop++) {
			LinkCond[Loop].LinkFrom = TmpLinkFm[Loop];
			LinkCond[Loop].LinkTo = TmpLinkTo[Loop];
			LinkCond[Loop].LinkCount = TmpLinkCt[Loop];
			LinkCond[Loop].LinkType = TmpLinkTp[Loop];
		}

		// MaxLinkToおよびMaxLinkFrom配列の値を"MaxLink"Propertyから読込む
		int MaxLinkTo[100]; //ViewElementの種別毎のリンク接続先最大数
		int MaxLinkFrom[100]; //ViewElementの種別毎のリンク接続元最大数
		LowDbAccess::GetInstance()->GetMaxLinkInfo(MaxLinkTo, MaxLinkFrom);

		// ViewElement(アイコン)の種別毎，現在選択されている件数をTypeAry配列に格納します。
		int TypeAry[100];
		for (int Loop = 0; Loop < 100; Loop++) {
			TypeAry[Loop] = 0;
		}
		for (int LoopEle = 0; LoopEle < *ElementCount; LoopEle++) {
			int AseId = Ase[LoopEle]->GetId();
			if (AseId == 0) {
				continue;
			}
			NetAseEx* Nase = reinterpret_cast<NetAseEx*>(Ase[LoopEle]);
			if (Nase->GetSelection() == OfficeASE::SELECTED_MANY) {
				TypeAry[Nase->GetType()]++;
				// If the specified element pair has already been linked, the menu item is grayed out.
				for (int LoopCurLink = 0; LoopCurLink < LinkCount; LoopCurLink++) {
					if (LinkTo[LoopCurLink] == LoopEle) {
						AddLinkMenuType |= MF_GRAYED;
					}
				}
			}
		}
		int MyType = GetType();
		if (TypeAry[MyType] > 0) {
			TypeAry[MyType]--;
		}

		// 操作対象要素とある種別の要素の対に関して，既に設定されているリンク数に現在選択されているリンク数を加算した
		// うえで，加算したリンク数が上限を超えていないかチェックする。上限を超えている場合，メニューはグレイアウトする。
		int DummyTypeAry[100];
		for (int Loop = 0; Loop < 100; Loop++) {
			DummyTypeAry[Loop] = TypeAry[Loop];
		}
		for (int Loop = 0; Loop < LinkCount; Loop++) {
			int AseId = Ase[LinkTo[Loop]]->GetId();
			if (AseId == 0) {
				continue;
			}
			NetAseEx* Nase = reinterpret_cast<NetAseEx*>(Ase[LinkTo[Loop]]);
			DummyTypeAry[Nase->GetType()]++;
		}
		for (int Loop = 0; Loop < 100; Loop++) {
			for (int LoopCnd = 0; LoopCnd < LinkCondCount; LoopCnd++) {
				if (LinkCond[LoopCnd].LinkFrom == GetType() &&
					LinkCond[LoopCnd].LinkTo == Loop &&
					LinkCond[LoopCnd].LinkCount < DummyTypeAry[Loop]) {
					AddLinkMenuType |= MF_GRAYED;
					break;
				}
			}
		}

		if ((AddLinkMenuType & MF_GRAYED) != MF_GRAYED) {
			// 操作対象の要素からはられているリンクの総計を求める
			int Total = 0;
			for (int Loop = 0; Loop < LinkCondCount; Loop++) {
				if (LinkCond[Loop].LinkFrom == MyType) {
					Total += TypeAry[LinkCond[Loop].LinkTo];
					TypeAry[LinkCond[Loop].LinkTo] = 0;
				}
			}
			// リンク接続先の数がMaxLinkToを超える場合はメニューをグレイアウトする
			int MxLkTo = MaxLinkTo[GetType()];
			if (MxLkTo < 0) {
				MxLkTo = 0;
			}
			if (MxLkTo > 10) {
				MxLkTo = 10;
			}
			if (Total > MxLkTo - LinkCount) {
				AddLinkMenuType |= MF_GRAYED;
			} else {
				// LinkCondで定義されていない種別のViewElementが選択されている場合，メニューはグレイアウトする
				Total = 0;
				for (int Loop = 0; Loop < 100; Loop++) {
					Total += TypeAry[Loop];
				}
				if (Total > 0) {
					AddLinkMenuType |= MF_GRAYED;
				}
			}
		}

		// リンク接続元の数がMaxLinkFromを超える場合はメニューをグレイアウトする
		if ((AddLinkMenuType & MF_GRAYED) != MF_GRAYED) {
			for (int LoopEle = 0; LoopEle < *ElementCount; LoopEle++) {
				int AseId = Ase[LoopEle]->GetId();
				if (AseId == 0 || AseId == m_Id) {
					continue;
				}
				NetAseEx* Nase = reinterpret_cast<NetAseEx*>(Ase[LoopEle]);
				if (Nase->GetSelection() == OfficeASE::SELECTED_MANY) {
					int Counter = 0;
					for (int ChkLoop = 0; ChkLoop < *ElementCount; ChkLoop++) {
						int ChkAseId = Ase[ChkLoop]->GetId();
						if (ChkAseId == 0) {
							continue;
						}
						NetAseEx* ChkNase = reinterpret_cast<NetAseEx*>(Ase[ChkLoop]);
						for (int LoopLnk = 0; LoopLnk < ChkNase->LinkCount; LoopLnk++) {
							if (ChkNase->LinkTo[LoopLnk] == LoopEle) {
								Counter++;
							}
						}
					}
					if (MaxLinkFrom[Nase->GetType()] < 0) {
						continue;
					}
					if (MaxLinkFrom[Nase->GetType()] <= Counter) {
						AddLinkMenuType |= MF_GRAYED;
						break;
					}
				}
			}
		}
	}

	AppendMenu(MenuHndlTop, AddLinkMenuType, 1, MyMsgProc::GetMsg(MyMsgProc::STKFW_ADD_LINK));
	AppendMenu(MenuHndlTop, DelLinkMenuType, 2, MyMsgProc::GetMsg(MyMsgProc::STKFW_DEL_LINK));
	AppendMenu(MenuHndlTop, MF_SEPARATOR, -1, _T(""));
	AppendMenu(MenuHndlTop, MF_STRING | MF_ENABLED | MF_UNCHECKED, 3, MyMsgProc::GetMsg(MyMsgProc::STKFW_DEL_PROCESSING_ELEMENT));
	AppendMenu(MenuHndlTop, MF_SEPARATOR, -1, _T(""));
	AppendMenu(MenuHndlTop, MF_STRING | MF_ENABLED | MF_UNCHECKED, 4, _T("Properties"));
}

void NetAseEx::PopupMenuAction(int MenuId, int x, int y, ActorStatusElement* Ase[], int* ElementCount)
{
	if (MenuId == 1) {
		//////////////////////////////////////////////////////////////////
		// Add link
		for (int Loop = 0; Loop < *ElementCount; Loop++) {
			int AseId = Ase[Loop]->GetId();
			if (AseId == 0 || AseId == m_Id) {
				continue;
			}
			NetAseEx* Nase = reinterpret_cast<NetAseEx*>(Ase[Loop]);
			if (Nase->GetSelection() == OfficeASE::SELECTED_MANY) {
				if (LinkCount < 10) {
					int LoopLnk;
					for (LoopLnk = 0; LoopLnk < LinkCount; LoopLnk++) {
						if (LinkTo[LoopLnk] == Loop) {
							break;
						}
					}
					// It is a new link.
					if (LoopLnk == LinkCount) {
						// Check link type and set it
						for (int LoopLnkCond = 0; LoopLnkCond < LinkCondCount; LoopLnkCond++) {
							if (LinkCond[LoopLnkCond].LinkFrom == GetType() &&
								LinkCond[LoopLnkCond].LinkTo == Nase->GetType()) {
									LinkType[LinkCount] = LinkCond[LoopLnkCond].LinkType;
							}
						}
						// Add new link
						LinkTo[LinkCount] = Loop;
						LinkCount++;
					}
				}
			}
		}
	} else if (MenuId == 2) {
		//////////////////////////////////////////////////////////////////
		// Delete link
		for (int Loop = 0; Loop < *ElementCount; Loop++) {
			int AseId = Ase[Loop]->GetId();
			if (AseId == 0 || AseId == m_Id) {
				continue;
			}
			NetAseEx* Nase = reinterpret_cast<NetAseEx*>(Ase[Loop]);
			if (Nase->GetSelection() == OfficeASE::SELECTED_MANY) {
				int LoopLnk;
				for (LoopLnk = 0; LoopLnk < LinkCount; LoopLnk++) {
					if (LinkTo[LoopLnk] == Loop) {
						LinkTo[LoopLnk] = LinkTo[LinkCount - 1];
						LinkType[LoopLnk] = LinkType[LinkCount - 1];
						LinkTo[LinkCount - 1] = -1;
						LinkType[LinkCount - 1] = -1;
						LinkCount--;
						LoopLnk--;
					}
				}
			}
		}
	} else if (MenuId == 3) {
		//////////////////////////////////////////////////////////////////
		// Delete element.
		for (int Loop = 0; Loop < *ElementCount; Loop++) {
			int AseId = Ase[Loop]->GetId();
			if (AseId == 0) {
				continue;
			}
			NetAseEx* Nase = reinterpret_cast<NetAseEx*>(Ase[Loop]);
			// Delete selected elements.
			if (Nase->GetSelection() == OfficeASE::SELECTED_ONE ||
				Nase->GetSelection() == OfficeASE::SELECTED_MANY) {
				// Begin : Delete links which are associating the target element.
				for (int LoopObj = 0; LoopObj < *ElementCount; LoopObj++) {
					int AseId2 = Ase[LoopObj]->GetId();
					if (AseId2 == 0) {
						continue;
					}
					NetAseEx* Nase2 = reinterpret_cast<NetAseEx*>(Ase[LoopObj]);
					for (int LoopLnk = 0; LoopLnk < Nase2->LinkCount; LoopLnk++) {
						if (Nase2->LinkTo[LoopLnk] == Loop) {
							Nase2->LinkTo[LoopLnk] = Nase2->LinkTo[Nase2->LinkCount - 1];
							Nase2->LinkType[LoopLnk] = Nase2->LinkType[Nase2->LinkCount - 1];
							Nase2->LinkTo[Nase2->LinkCount - 1] = -1;
							Nase2->LinkType[Nase2->LinkCount - 1] = -1;
							Nase2->LinkCount--;
							LoopLnk--;
							continue;
						}
						// If a link is associating to the last element,
						// the link is changed into the link for current loop element.
						// Because, the last element will be moved to current loop element.
						if (Nase2->LinkTo[LoopLnk] == (*ElementCount) - 1) {
							Nase2->LinkTo[LoopLnk] = Loop;
							continue;
						}
					}
				}
				// End : Delete links which are associating the target element.
				delete Nase;
				Ase[Loop] = Ase[(*ElementCount) - 1];
				(*ElementCount)--;
				Loop--;
			}
		}
		ResetThreadController(FALSE);
	} else if (MenuId == 4) {
		//////////////////////////////////////////////////////////////////
		// Property
		DoubleClickAction();
	}
}

void NetAseEx::DoubleClickAction()
{
	SetViewToDb();

	SetMouseAction(-1);
	int RetCode = DllShowProperty(m_Id); // ##10085
	SetMouseAction(1);

	// #10085 begin
	if (RetCode == 0) {
		ResetWorkspace(3);
		GetViewFromDb();
		ResetThreadController(TRUE);
	}
	// ##10085 end
}
