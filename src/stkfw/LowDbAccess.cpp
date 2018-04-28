#include <shlwapi.h>
#include "LowDbAccess.h"
#include "..\..\..\YaizuComLib\src\\stkdata\stkdata.h"
#include "..\..\..\YaizuComLib\src\\stkdata\stkdataapi.h"

LowDbAccess* LowDbAccess::ThisInstance;

LowDbAccess::LowDbAccess()
{
}

LowDbAccess::~LowDbAccess()
{
}

// Get this instance
LowDbAccess* LowDbAccess::GetInstance()
{
	static int Init = 1;
	if (Init == 1) {
		ThisInstance = new LowDbAccess();
		Init = 0;
	}
	return ThisInstance;
}










/////////////////////////////////////////////////////////////////////////
//
// For Property table
//
/////////////////////////////////////////////////////////////////////////

// 指定したプロパティのn番目のValueInt値を取得する
// Name: in: プロパティ名
// Index: in: 取得するValueInt属性のインデックス ("ValueInt1"=1, "ValueInt2"=2, "ValueInt3"=3)
// 戻り値: 取得した値
int LowDbAccess::GetPropertyInteger(TCHAR* Name, int Index)
{
	int Ret = 0;
	ColumnData* ColDat[1];
	ColDat[0] = new ColumnDataWStr(_T("Name"), Name);
	RecordData* SearchRd = new RecordData(_T("Property"), ColDat, 1);
	LockTable(_T("Property"), 1);
	RecordData* ResultRd = GetRecord(SearchRd);
	UnlockTable(_T("Property"));
	if (ResultRd != NULL) {
		ColumnDataInt* ValueInt = (ColumnDataInt*)ResultRd->GetColumn(Index);
		Ret = ValueInt->GetValue();
		delete ResultRd;
	}
	delete SearchRd;
	return Ret;
}

// 指定したプロパティのn番目のValueInt値を設定する
// Name: in: プロパティ名
// Index: in: 取得するValueInt属性のインデックス ("ValueInt1"=1, "ValueInt2"=2, "ValueInt3"=3)
// Value: in: 設定する値
void LowDbAccess::SetPropertyInteger(TCHAR* Name, int Index, int Value)
{
	TCHAR* AtrName[3] = {_T("ValueInt1"), _T("ValueInt2"), _T("ValueInt3")};
	// Set record for search
	ColumnData* SchColDat[1];
	SchColDat[0] = new ColumnDataWStr(_T("Name"), Name);
	RecordData* SearchRd = new RecordData(_T("Property"), SchColDat, 1);
	// Set record for update
	ColumnData* UpdColDat[1];
	UpdColDat[0] = new ColumnDataInt(AtrName[Index - 1], Value);
	RecordData* UpdateRd = new RecordData(_T("Property"), UpdColDat, 1);
	// Update record
	LockTable(_T("Property"), 2);
	UpdateRecord(SearchRd, UpdateRd);
	UnlockTable(_T("Property"));
	delete SearchRd;
	delete UpdateRd;
}

// Propertyテーブルにレコードを挿入する
// Name: in: プロパティ名
// ValInt1: in: ValueInt1の値
// ValInt2: in: ValueInt2の値
// ValInt3: in: ValueInt3の値
// ValStr1: in: ValueStr1の値
// ValStr2: in: ValueStr2の値
// ValStr3: in: ValueStr3の値
void LowDbAccess::InsertProperty(TCHAR* Name, int ValInt1, int ValInt2, int ValInt3, TCHAR* ValStr1, TCHAR* ValStr2, TCHAR* ValStr3)
{
	ColumnData* ColDat[7];
	ColDat[0] = new ColumnDataWStr(_T("Name"), Name);
	ColDat[1] = new ColumnDataInt(_T("ValueInt1"), ValInt1);
	ColDat[2] = new ColumnDataInt(_T("ValueInt2"), ValInt2);
	ColDat[3] = new ColumnDataInt(_T("ValueInt3"), ValInt3);
	ColDat[4] = new ColumnDataWStr(_T("ValueStr1"), ValStr1);
	ColDat[5] = new ColumnDataWStr(_T("ValueStr2"), ValStr2);
	ColDat[6] = new ColumnDataWStr(_T("ValueStr3"), ValStr3);
	RecordData* InsertRd = new RecordData(_T("Property"), ColDat, 7);
	LockTable(_T("Property"), 2);
	InsertRecord(InsertRd);
	UnlockTable(_T("Property"));
	delete InsertRd;
}

// 指定したプロパティ名を持つ全レコードを削除する
// Name: in: プロパティ名
void LowDbAccess::DeleteProperty(TCHAR* Name)
{
	ColumnData* ColDat[1];
	ColDat[0] = new ColumnDataWStr(_T("Name"), Name);
	RecordData* DeleteRd = new RecordData(_T("Property"), ColDat, 1);
	LockTable(_T("Property"), 2);
	DeleteRecord(DeleteRd);
	UnlockTable(_T("Property"));
	delete DeleteRd;
}

// ワークスペースサイズおよびグリッド状態を返却する
// Width : out : 現在ワークスペースの幅(pixel)
// Height : out : 現在のワークスペースの高さ(pixel)
// GridType : out : 現在のグリッド状態(1: 1pixel, 8:8pixel)
// 戻り値 : 成功／失敗を示すフラグ (TRUE: 成功, FALSE: 失敗)
BOOL LowDbAccess::GetWorkspaceInfo(int* Width, int* Height, int* GridTypeL)
{
	ColumnData* ColDat[1];
	ColDat[0] = new ColumnDataWStr(_T("Name"), _T("Workspace"));
	RecordData* SearchRd = new RecordData(_T("Property"), ColDat, 1);
	LockTable(_T("Property"), 1);
	RecordData* ResultRd = GetRecord(SearchRd);
	UnlockTable(_T("Property"));
	if (ResultRd != NULL) {
		ColumnDataInt* ValueIntW = (ColumnDataInt*)ResultRd->GetColumn(1);
		ColumnDataInt* ValueIntH = (ColumnDataInt*)ResultRd->GetColumn(2);
		ColumnDataInt* ValueIntG = (ColumnDataInt*)ResultRd->GetColumn(3);
		*Width = ValueIntW->GetValue();
		*Height = ValueIntH->GetValue();
		*GridTypeL = ValueIntG->GetValue();
		if (*GridTypeL != 1 && *GridTypeL != 8) {
			*GridTypeL = 1;
		}
		delete ResultRd;
		delete SearchRd;
		return TRUE;
	} else {
		*Width = 512;
		*Height = 400;
		*GridTypeL = 8;
		delete SearchRd;
		return FALSE;
	}
}

// ワークスペースのグリッド種別を設定する
// GridType [in] : グリッド種別
void LowDbAccess::SetWorkspaceGridType(int GridType)
{
	ColumnData* ColDat[2];
	ColDat[0] = new ColumnDataInt(_T("ValueInt3"), GridType);
	RecordData* UpdateRd = new RecordData(_T("Property"), &ColDat[0], 1);
	ColDat[1] = new ColumnDataWStr(_T("Name"), _T("Workspace"));
	RecordData* SearchRd = new RecordData(_T("Property"), &ColDat[1], 1);
	LockTable(_T("Property"), 2);
	UpdateRecord(SearchRd, UpdateRd);
	UnlockTable(_T("Property"));
	delete UpdateRd;
	delete SearchRd;
}

// ViewElement種別からアイコン種別を取得する
// Type [in] : ViewElement種別
// Return : アイコン種別
int LowDbAccess::GetIconTypeByViewElementType(int Type)
{
	ColumnData* ColDat[2];
	ColDat[0] = new ColumnDataWStr(_T("Name"), _T("ViewElement"));
	ColDat[1] = new ColumnDataInt(_T("ValueInt1"), Type);
	RecordData* SearchRd = new RecordData(_T("Property"), ColDat, 2);
	LockTable(_T("Property"), 1);
	RecordData* ResultRd = GetRecord(SearchRd);
	UnlockTable(_T("Property"));
	ColumnDataInt* ValueInt = (ColumnDataInt*)ResultRd->GetColumn(2);
	int IcnId = ValueInt->GetValue();
	delete SearchRd;
	delete ResultRd;
	return IcnId;
}

// Acquire basic information of ViewElement from property table.
// If more than 100 ViewElement records exit, exceeded 100th elements are dropped.
// Type [out] : Type of ViewElement
// ExecFlag [out] : Execution flag of ViewElement
// Desc [out] : Description of ViewElement
// Return : Number of acquired elements
int LowDbAccess::GetViewElementBasicInfoFromProperty(int Type[100], int ExecFlag[100], TCHAR Desc[100][256])
{
	ColumnData* ColDat[1];
	RecordData* SearchRd;
	RecordData* ResultRd;
	RecordData* CurrentRd;

	int Count = 0;

	// Load ViewElement definition data
	ColDat[0] = new ColumnDataWStr(_T("Name"), _T("ViewElement"));
	SearchRd = new RecordData(_T("Property"), ColDat, 1);
	LockTable(_T("Property"), 1);
	ResultRd = GetRecord(SearchRd);
	UnlockTable(_T("Property"));
	CurrentRd = ResultRd;
	while (CurrentRd != NULL) {
		ColumnDataInt* ValueInt = (ColumnDataInt*)CurrentRd->GetColumn(1);
		ColumnDataInt* ValueIntEx = (ColumnDataInt*)CurrentRd->GetColumn(3);
		ColumnDataWStr* ValueStr = (ColumnDataWStr*)CurrentRd->GetColumn(4);
		Type[Count] = ValueInt->GetValue();
		ExecFlag[Count] = ValueIntEx->GetValue();
		lstrcpy(Desc[Count], ValueStr->GetValue());
		CurrentRd = CurrentRd->GetNextRecord();
		Count++;
		if (Count == 100) {
			break;
		}
	}
	delete ResultRd;
	delete SearchRd;
	return Count;
}

// Acquire all link informations regarding 
// LinkFm [out] : Link from
// LinkTo [out] : Link to
// LinkCt [out] : Link count
// LinkTp [out] : Link type
// Return : Number of LinkInfo. If more than 500 records exist, -1 is returned.
int LowDbAccess::GetAllLinkInfos(int LinkFm[500], int LinkTo[500], int LinkCt[500], int LinkTp[500])
{
	ColumnData* ColDat[1];
	ColDat[0] = new ColumnDataWStr(_T("Name"), _T("LinkInfo"));
	RecordData* SearchRd = new RecordData(_T("Property"), ColDat, 1);
	LockTable(_T("Property"), 1);
	RecordData* ResultRd = GetRecord(SearchRd);
	UnlockTable(_T("Property"));
	int Idx = 0;
	while (ResultRd != NULL) {
		ColumnDataInt* ValueLinkFm = (ColumnDataInt*)ResultRd->GetColumn(1);
		ColumnDataInt* ValueLinkTo = (ColumnDataInt*)ResultRd->GetColumn(2);
		ColumnDataInt* ValueLinkCt = (ColumnDataInt*)ResultRd->GetColumn(3);
		ColumnDataWStr* ValueLinkTp = (ColumnDataWStr*)ResultRd->GetColumn(4);
		LinkFm[Idx] = ValueLinkFm->GetValue();
		LinkTo[Idx] = ValueLinkTo->GetValue();
		LinkCt[Idx] = ValueLinkCt->GetValue();
		LinkTp[Idx] = StrToInt(ValueLinkTp->GetValue());
		ResultRd = ResultRd->GetNextRecord();
		Idx++;
		if (Idx >= 1000) {
			Idx = -1;
			break;
		}
	};
	delete SearchRd;
	delete ResultRd;
	return Idx;
}

// Get maximum link count information.
// MaxLinkTo [out] : Link destination's max link count
// MaxLinkFrom [out] : Link origin's max link count
void LowDbAccess::GetMaxLinkInfo(int MaxLinkTo[100], int MaxLinkFrom[100])
{
	// MaxLinkToおよびMaxLinkFrom配列クリア
	for (int MaxLinkLp = 0; MaxLinkLp < 100; MaxLinkLp++) {
		MaxLinkTo[MaxLinkLp] = 0;
		MaxLinkFrom[MaxLinkLp] = 0;
	}
	//"MaxLink"Propertyからの読み込み
	ColumnData* ColDat[1];
	ColDat[0] = new ColumnDataWStr(_T("Name"), _T("MaxLink"));
	RecordData* SearchRd = new RecordData(_T("Property"), ColDat, 1);
	LockTable(_T("Property"), 1);
	RecordData* ResultRd = GetRecord(SearchRd);
	UnlockTable(_T("Property"));
	while (ResultRd != NULL) {
		ColumnDataInt* ValueMaxLinkType = (ColumnDataInt*)ResultRd->GetColumn(1);
		ColumnDataInt* ValueMaxLinkTo   = (ColumnDataInt*)ResultRd->GetColumn(2);
		ColumnDataInt* ValueMaxLinkfrom = (ColumnDataInt*)ResultRd->GetColumn(3);
		int MaxLinkType = ValueMaxLinkType->GetValue();
		MaxLinkTo[MaxLinkType] = ValueMaxLinkTo->GetValue();
		MaxLinkFrom[MaxLinkType] = ValueMaxLinkfrom->GetValue();
		ResultRd = ResultRd->GetNextRecord();
	};
	delete SearchRd;
	delete ResultRd;
}

// Get types and categories of ViewElements.
// VeType [out] : Type ID of the ViewElement
// VeTypeName [out] : Name of the ViewElement
// VeCatName [out] : Category name of the ViewElement
// Return : Found elements count
int LowDbAccess::GetViewElementMenus(int VeType[100], TCHAR VeTypeName[100][256], TCHAR VeCatName[100][256])
{
	ColumnData* ColDat[1];
	ColDat[0] = new ColumnDataWStr(_T("Name"), _T("ViewElement"));
	RecordData* SearchRd = new RecordData(_T("Property"), ColDat, 1);
	LockTable(_T("Property"), 2);
	AzSortRecord(_T("Property"), _T("ValueInt1"));
	RecordData* ResultRd = GetRecord(SearchRd);
	UnlockTable(_T("Property"));
	RecordData* CurrentRd = ResultRd;

	int Loop = 0;
	while (CurrentRd != NULL) {
		ColumnDataInt* ValueInt = (ColumnDataInt*)CurrentRd->GetColumn(1);
		ColumnDataWStr* ValueStr = (ColumnDataWStr*)CurrentRd->GetColumn(4);
		ColumnDataWStr* ValueStrMenu = (ColumnDataWStr*)CurrentRd->GetColumn(6);

		if (ValueInt != NULL && ValueStr != NULL && ValueStrMenu !=NULL) {
			VeType[Loop] = ValueInt->GetValue();
			wsprintf(VeTypeName[Loop], _T("%s"), ValueStr->GetValue());
			wsprintf(VeCatName[Loop], _T("%s"), ValueStrMenu->GetValue());
		}
		CurrentRd = CurrentRd->GetNextRecord();
		Loop++;
		if (Loop == 100) {
			break;
		}
	};
	delete SearchRd;
	delete ResultRd;

	return Loop;
}










/////////////////////////////////////////////////////////////////////////
//
// For ViewElement table
//
/////////////////////////////////////////////////////////////////////////

// ViewElementテーブルを検索し，指定した種別を持つ要素のIDを配列で返却する
// Type: in: 検索対象の種別
// Ids: out: 取得するIDを格納する配列
// NumOfIds: in: 取得するIDが格納される配列のサイズ
// 戻り値: 取得したIDの数
int LowDbAccess::GetViewElementIdsFromType(int* Ids, int NumOfIds, int Type)
{
	ColumnData* ColDat[1];
	ColDat[0] = new ColumnDataInt(_T("Type"), Type);
	RecordData* SearchRd = new RecordData(_T("ViewElement"), ColDat, 1);
	LockTable(_T("ViewElement"), 1);
	RecordData* ResultRootRd = GetRecord(SearchRd);
	UnlockTable(_T("ViewElement"));
	RecordData* TargetRd = ResultRootRd;
	int CurrentNum = 0;
	while (TargetRd != NULL) {
		ColumnDataInt* ValueInt = (ColumnDataInt*)TargetRd->GetColumn(0);
		int Ret = ValueInt->GetValue();
		TargetRd = TargetRd->GetNextRecord();
		if (CurrentNum < NumOfIds) {
			Ids[CurrentNum] = Ret;
			CurrentNum++;
		}
	};
	if (ResultRootRd != NULL) {
		delete ResultRootRd;
	}
	delete SearchRd;
	return CurrentNum;
}

// 指定した条件に一致する全てのViewElementのIDを返却する
// Ids : [out] : Typeで指定した種別を持つ全てのViewElementのIDを格納する配列のポインタ
// Type : [in] : IDを取得する条件
// [return] : Idsに格納したIDの数
int LowDbAccess::GetViewElementIds(int Ids[256], int Type)
{
	ColumnData* ColSch[1];
	ColSch[0] = new ColumnDataInt(_T("Type"), Type);
	RecordData* RecSch = new RecordData(_T("ViewElement"), ColSch, 1);
	LockTable(_T("ViewElement"), 1);
	RecordData* RetRec = GetRecord(RecSch);
	UnlockTable(_T("ViewElement"));
	int Index = 0;
	RecordData* TopRec = RetRec;
	while (RetRec != NULL) {
		ColumnDataInt* RetCol = (ColumnDataInt*)RetRec->GetColumn(0);
		Ids[Index] = RetCol->GetValue();
		Index++;
		RetRec = RetRec->GetNextRecord();
	}
	delete RecSch;
	delete TopRec;
	return Index;
}

// This function acquires array of name and array of ID from the specified type.
// Name [out] : Acquired array of name. Maximum 256 elements can be acquired
// Id [out] : Acquired array of ID. Maximum 256 elements can be acquired
// Type [in] : Acquisition target type of ViewElement
// Return : Number of acquired names and IDs
int LowDbAccess::GetViewElementNamesAndIdsFromType(TCHAR Name[256][32], int Id[256], int Type)
{
	int MaxNumOfName = 0;
	ColumnData* ColSch[1];
	ColSch[0] = new ColumnDataInt(_T("Type"), Type);
	RecordData* RecSch = new RecordData(_T("ViewElement"), ColSch, 1);
	LockTable(_T("ViewElement"), 1);
	RecordData* RetRec = GetRecord(RecSch);
	RecordData* HeadRec = RetRec;
	UnlockTable(_T("ViewElement"));

	while (RetRec) {
		ColumnDataInt* RetColId = (ColumnDataInt*)RetRec->GetColumn(0);
		ColumnDataWStr* RetColName = (ColumnDataWStr*)RetRec->GetColumn(1);
		int CurId = RetColId->GetValue();
		TCHAR* CurName = RetColName->GetValue();
		BOOL FndFlag = FALSE;
		for (int Loop = 0; Loop < MaxNumOfName; Loop++) {
			if (Id[Loop] == CurId) {
				FndFlag = TRUE;
				break;
			}
		}
		if (GetElementInfoInt(CurId, 1) == 0) {
			if (FndFlag == FALSE && MaxNumOfName < 256) {
				Id[MaxNumOfName] = CurId;
				lstrcpyn(Name[MaxNumOfName], CurName, 32);
				MaxNumOfName++;
			}
		}
		RetRec = RetRec->GetNextRecord();
	}
	delete RecSch;
	delete HeadRec;

	return MaxNumOfName;
}

// This function acquires type of ViewElement from the specified ViewElement ID.
// TargetId [in] : ID of the target ViewElement
// Return : Type of ViewElement which caller specified.
int LowDbAccess::GetViewElementTypeFromId(int TargetId)
{
	int Type = -1;
	ColumnData* ColSch[1];
	ColSch[0] = new ColumnDataInt(_T("Id"), TargetId);
	RecordData* RecSch = new RecordData(_T("ViewElement"), ColSch, 1);
	LockTable(_T("ViewElement"), 1);
	RecordData* RetRec = GetRecord(RecSch);
	UnlockTable(_T("ViewElement"));
	if (RetRec != NULL) {
		ColumnDataInt* RetCol = (ColumnDataInt*)RetRec->GetColumn(2);
		Type = RetCol->GetValue();
		delete RetRec;
	}
	delete RecSch;
	return Type;
}

// This function acquires name of ViewElement from the specified ViewElement ID.
// TargetId [in] : ID of the target ViewElement
// Name [out] : Acquired ViewElement name
// Return : none
void LowDbAccess::GetViewElementNameFromId(int TargetId, TCHAR Name[32])
{
	ColumnData* ColSch[1];
	ColSch[0] = new ColumnDataInt(_T("Id"), TargetId);
	RecordData* RecSch = new RecordData(_T("ViewElement"), ColSch, 1);
	LockTable(_T("ViewElement"), 1);
	RecordData* RecRes = GetRecord(RecSch);
	UnlockTable(_T("ViewElement"));
	if (RecRes != NULL) {
		ColumnDataWStr* ColRes = (ColumnDataWStr*)RecRes->GetColumn(1);
		lstrcpy(Name, ColRes->GetValue());
		delete RecRes;
	} else {
		lstrcpy(Name, _T(""));
	}
	delete RecSch;
}

// This function updates the name of ViewElement which can be identified by the specified TargetId.
// TargetId [in] : ID of target ViewElement
// Name[in] : New name of ViewElement
void LowDbAccess::UpdateViewElementName(int TargetId, TCHAR Name[32])
{
	ColumnData* ColSch[1];
	ColumnData* ColUpd[1];
	ColSch[0] = new ColumnDataInt(_T("Id"), TargetId);
	ColUpd[0] = new ColumnDataWStr(_T("Name"), Name);
	RecordData* RecSch = new RecordData(_T("ViewElement"), ColSch, 1);
	RecordData* RecUpd = new RecordData(_T("ViewElement"), ColUpd, 1);
	LockTable(_T("ViewElement"), 2);
	UpdateRecord(RecSch, RecUpd);
	UnlockTable(_T("ViewElement"));
	delete RecUpd;
	delete RecSch;
}

int LowDbAccess::GetViewElementLinkInfo(int TargetId, int* Type, int LinkId[10], int LinkType[10])
{
	ColumnData* ColSch[1];
	ColSch[0] = new ColumnDataInt(_T("Id"), TargetId);
	RecordData* RecSch = new RecordData(_T("ViewElement"), ColSch, 1);
	LockTable(_T("ViewElement"), 1);
	RecordData* RetRec = GetRecord(RecSch);
	UnlockTable(_T("ViewElement"));
	delete RecSch;
	if (RetRec != NULL) {
		for (int Loop = 0; Loop < 20; Loop += 2) {
			LinkId[Loop / 2] = ((ColumnDataInt*)RetRec->GetColumn(Loop + 6))->GetValue();
			LinkType[Loop / 2] = ((ColumnDataInt*)RetRec->GetColumn(Loop + 7))->GetValue();
		}
		*Type = ((ColumnDataInt*)RetRec->GetColumn(2))->GetValue();
		delete RetRec;
		return 0;
	} else {
		return -1;
	}
}

// This function gets ID which the element is linking to the element identified by TargetId.
// Link type is also acquired.
// TargetId [in] : Target ID 
// LinkOrgId [out] : Acquired ID
// LinkType [out] : Link type
// Return 0 : Success, -1 :Failed
int LowDbAccess::GetViewElementLinkOriginInfo(int TargetId, int* LinkOrgId, int* LinkType)
{
	ColumnData* ColSch[1];
	ColSch[0] = new ColumnDataInt(_T("LinkId0"), TargetId);
	RecordData* RecSch = new RecordData(_T("ViewElement"), ColSch, 1);
	LockTable(_T("ViewElement"), 1);
	RecordData* RetRec = GetRecord(RecSch);
	UnlockTable(_T("ViewElement"));
	delete RecSch;
	if (RetRec != NULL) {
		*LinkOrgId = ((ColumnDataInt*)RetRec->GetColumn(0))->GetValue();
		*LinkType = ((ColumnDataInt*)RetRec->GetColumn(7))->GetValue();
		delete RetRec;
		return 0;
	} else {
		return -1;
	}
}

// This function updates the specified link information.
// Index [in] : Index of link information for ToId
// FromId [in] : Id linked from
// ToId[in] : Destination Id
// LinkType [in] : Type of link
// Return : Always zero returned
int LowDbAccess::UpdateViewElementLinkType(int Index, int FromId, int ToId, int LinkType)
{
	ColumnData* ColSch[2];
	ColumnData* ColUpd[1];
	RecordData* RecSch;
	RecordData* RecUpd;
	TCHAR Buf[20];

	wsprintf(Buf, _T("LinkId%d"), Index);
	ColSch[1] = new ColumnDataInt(Buf, ToId);
	ColSch[0] = new ColumnDataInt(_T("Id"), FromId);
	RecSch = new RecordData(_T("ViewElement"), ColSch, 2);

	wsprintf(Buf, _T("LinkTp%d"), Index);
	ColUpd[0] = new ColumnDataInt(Buf, 106 - LinkType);
	RecUpd = new RecordData(_T("ViewElement"), ColUpd, 1);

	LockTable(_T("ViewElement"), 2);
	UpdateRecord(RecSch, RecUpd);
	UnlockTable(_T("ViewElement"));

	delete RecSch;
	delete RecUpd;
	return 0;
}

// This function gets TCP or UDP element's names and IDs.
// AcquiredName [out] : Array of acquired names
// AcquiredId [out] : Array of acquired IDs
// UdpFlag [in] : If 1, UDP names and IDs are acquired. Otherwise TCP names and IDs are acquired.
// Return : Number of acquired informations
int LowDbAccess::GetTargetTcpUdpNameAndId(TCHAR AcquiredName[256][32], int AcquiredId[256], int UdpFlag)
{
	int TargetId1 = 1;
	int TargetId2 = 4;
	int TargetId3 = 7;
	if (UdpFlag == 1) {
		TargetId1 = 22;
		TargetId2 = 23;
		TargetId3 = -1;
	}

	int MaxNumOfName = 0;
	ColumnData* ColSch1[1];
	ColumnData* ColSch2[1];
	ColumnData* ColSch3[1];
	ColSch1[0] = new ColumnDataInt(_T("Type"), TargetId1);
	ColSch2[0] = new ColumnDataInt(_T("Type"), TargetId2);
	ColSch3[0] = new ColumnDataInt(_T("Type"), TargetId3);
	RecordData* RecSch1 = new RecordData(_T("ViewElement"), ColSch1, 1);
	RecordData* RecSch2 = new RecordData(_T("ViewElement"), ColSch2, 1);
	RecordData* RecSch3 = new RecordData(_T("ViewElement"), ColSch3, 1);
	LockTable(_T("ViewElement"), 1);
	RecordData* RetRec1 = GetRecord(RecSch1);
	RecordData* RetRec2 = GetRecord(RecSch2);
	RecordData* RetRec3 = GetRecord(RecSch3);
	UnlockTable(_T("ViewElement"));
	RecordData* CurRec[3];
	CurRec[0] = RetRec1;
	CurRec[1] = RetRec2;
	CurRec[2] = RetRec3;

	for (int LoopType = 0; LoopType < 3; LoopType++) {
		while (CurRec[LoopType]) {
			ColumnDataInt* RetColId = (ColumnDataInt*)CurRec[LoopType]->GetColumn(0);
			ColumnDataWStr* RetColName = (ColumnDataWStr*)CurRec[LoopType]->GetColumn(1);
			int Id = RetColId->GetValue();
			TCHAR* Name = RetColName->GetValue();
			BOOL FndFlag = FALSE;
			for (int Loop = 0; Loop < MaxNumOfName; Loop++) {
				if (AcquiredId[Loop] == Id) {
					FndFlag = TRUE;
					break;
				}
			}
			// If it is not port direct specification, name and ID are not inserted to the array.
			// Operation type of sender/receiver element is indicating 1.
			if (LowDbAccess::GetInstance()->GetElementInfoInt(Id, 1) == 0 || LowDbAccess::GetInstance()->GetElementInfoInt(Id, 1) == 2) {
				if (FndFlag == FALSE && MaxNumOfName < 256) {
					AcquiredId[MaxNumOfName] = Id;
					lstrcpyn(AcquiredName[MaxNumOfName], Name, 32);
					MaxNumOfName++;
				}
			}
			CurRec[LoopType] = CurRec[LoopType]->GetNextRecord();
		}
	}
	delete RecSch1;
	delete RetRec1;
	delete RecSch2;
	delete RetRec2;
	delete RecSch3;
	delete RetRec3;

	return MaxNumOfName;
}

// Get TCP sender/reciver names and IDs.
// TargetName [out] : Acquired names
// TargetId [out] : Acquired IDs
// Flag [in] : TRUE - sender information is returned, FALSE - receiver information is returned.
// MaFlag [in] : TRUE - Receiver for multi accepting is returned, FALSE -  Receiver for multi accepting is not returned
// RemovalId [in] : Name and ID regarding this parameter are not returned.
// Flag == TRUE ... sender names and IDs can be acquired.
// Flag == FALSE && RemovalId == -1 ... receiver names and IDs can be acquired.
// Flag == FALSE && RemovalId != -1 ... receiver names and IDs can be acquired. But the information regarding RemovalId cannot be acquired.
// Return : Number of acquired names and IDs
int LowDbAccess::GetTcpSenderReceiver(TCHAR TargetName[256][32], int TargetId[256], BOOL Flag, BOOL MaFlag, int RemovalId)
{
	int TargetId1 = 0;
	int TargetId2 = 0;
	if (Flag == TRUE) {
		TargetId1 = 4;
		TargetId2 = 7;
	} else {
		TargetId1 = 1;
		TargetId2 = 1;
	}

	int MaxNumOfName = 0;
	ColumnData* ColSch1[1];
	ColumnData* ColSch2[1];
	ColSch1[0] = new ColumnDataInt(_T("Type"), TargetId1);
	ColSch2[0] = new ColumnDataInt(_T("Type"), TargetId2);
	RecordData* RecSch1 = new RecordData(_T("ViewElement"), ColSch1, 1);
	RecordData* RecSch2 = new RecordData(_T("ViewElement"), ColSch2, 1);
	LockTable(_T("ViewElement"), 1);
	RecordData* RetRec1 = GetRecord(RecSch1);
	RecordData* RetRec2 = GetRecord(RecSch2);
	UnlockTable(_T("ViewElement"));
	RecordData* CurRec[2];
	CurRec[0] = RetRec1;
	CurRec[1] = RetRec2;

	for (int LoopType = 0; LoopType < 2; LoopType++) {
		while (CurRec[LoopType]) {
			ColumnDataInt* RetColId = (ColumnDataInt*)CurRec[LoopType]->GetColumn(0);
			ColumnDataWStr* RetColName = (ColumnDataWStr*)CurRec[LoopType]->GetColumn(1);
			int Id = RetColId->GetValue();
			TCHAR* Name = RetColName->GetValue();
			BOOL FndFlag = FALSE;
			for (int Loop = 0; Loop < MaxNumOfName; Loop++) {
				if (TargetId[Loop] == Id) {
					FndFlag = TRUE;
					break;
				}
			}
			if (((GetElementInfoInt(Id, 1) == 0 || GetElementInfoInt(Id, 1) == 2) && RemovalId != Id && MaFlag == TRUE) ||
				(GetElementInfoInt(Id, 1) == 0 && RemovalId != Id && MaFlag == FALSE)) {
				if (FndFlag == FALSE && MaxNumOfName < 256) {
					TargetId[MaxNumOfName] = Id;
					lstrcpyn(TargetName[MaxNumOfName], Name, 32);
					MaxNumOfName++;
				}
			}
			CurRec[LoopType] = CurRec[LoopType]->GetNextRecord();
		}
	}
	delete RecSch1;
	delete RetRec1;
	delete RecSch2;
	delete RetRec2;

	return MaxNumOfName;
}

// Gets icon ID
// TargetId [in] : ID for acquiring icon ID
// Return : Icon ID
int LowDbAccess::GetIconId(int TargetId)
{
	int Icon = 0;
	ColumnData* ColSch[1];
	ColSch[0] = new ColumnDataInt(_T("Id"), TargetId);
	RecordData* RecSch = new RecordData(_T("ViewElement"), ColSch, 1);
	LockTable(_T("ViewElement"), 1);
	RecordData* RetRec = GetRecord(RecSch);
	UnlockTable(_T("ViewElement"));
	if (RetRec != NULL) {
		ColumnDataInt* RetCol = (ColumnDataInt*)RetRec->GetColumn(3);
		Icon = RetCol->GetValue();
		delete RetRec;
	}
	delete RecSch;
	return Icon;
}

// Sets icon ID
// TargetId [in] : ID for acquiring icon ID
// IconId [in] : Icon ID
void LowDbAccess::SetIconId(int TargetId, int IconId)
{
	ColumnData* ColSch[1];
	ColumnData* ColUpd[1];
	ColSch[0] = new ColumnDataInt(_T("Id"), TargetId);
	ColUpd[0] = new ColumnDataInt(_T("Icon"), IconId);
	RecordData* RecSch = new RecordData(_T("ViewElement"), ColSch, 1);
	RecordData* RecUpd = new RecordData(_T("ViewElement"), ColUpd, 1);
	LockTable(_T("ViewElement"), 2);
	UpdateRecord(RecSch, RecUpd);
	UnlockTable(_T("ViewElement"));
	delete RecUpd;
	delete RecSch;
}

// Insert record into ViewElement table.
// Id [in] : ID of ViewElement
// Name [in] : Name of ViewElement
// Type [in] : Type of ViewElement
// Icon [in] : Icon ID of ViewElement
// PosX [in] : Position
// PosY [in] : Position
// LinkInfo [in] : Link information (Link ID and Link Type)
void LowDbAccess::InsertViewElement(int Id, TCHAR Name[32], int Type, int Icon, int PosX, int PosY, int LinkInfo[20])
{
	LockTable(_T("ViewElement"), 2);
	ColumnData* ColDat[32];
	ColDat[0] = new ColumnDataInt(_T("Id"), Id);
	ColDat[1] = new ColumnDataWStr(_T("Name"), Name);
	ColDat[2] = new ColumnDataInt(_T("Type"), Type);
	ColDat[3] = new ColumnDataInt(_T("Icon"), Icon);
	ColDat[4] = new ColumnDataInt(_T("x"), PosX);
	ColDat[5] = new ColumnDataInt(_T("y"), PosY);
	for (int LoopLnk = 0; LoopLnk < 10; LoopLnk++) {
		TCHAR BufLnk[10];
		wsprintf(BufLnk, _T("LinkId%d"), LoopLnk);
		ColDat[LoopLnk * 2 + 6] = new ColumnDataInt(BufLnk, LinkInfo[LoopLnk * 2]);
		wsprintf(BufLnk, _T("LinkTp%d"), LoopLnk);
		ColDat[LoopLnk * 2 + 7] = new ColumnDataInt(BufLnk, LinkInfo[LoopLnk * 2 + 1]);
	}
	RecordData* InsertRd = new RecordData(_T("ViewElement"), ColDat, 26);
	InsertRecord(InsertRd);
	delete InsertRd;
	UnlockTable(_T("ViewElement"));
}

// Get all ViewElement records.
// Id [out] : ID of ViewElement
// Name [out] : Name of ViewElement
// Type [out] : Type of ViewElement
// Icon [out] : Icon ID of ViewElement
// PosX [out] : Position
// PosY [out] : Position
// LnkId [out] : Link ID
// LnkTp [out] : Link Type
// Return : Acquired record count. If more than 1000 records exist, -1 is returned.
int LowDbAccess::GetAllViewElementRecords(int Id[1000], TCHAR Name[1000][32], int Type[1000], int Icon[1000], int PosX[1000], int PosY[1000], int LnkId[1000][10], int LnkTp[1000][10])
{
	int CurElem = 0;
	LockTable(_T("ViewElement"), 1);
	RecordData* ResultRd = GetRecord(_T("ViewElement"));
	RecordData* CurrentRd = ResultRd;
	while (CurrentRd) {
		ColumnDataInt* ColId = (ColumnDataInt*)CurrentRd->GetColumn(0);
		Id[CurElem] = ColId->GetValue();
		ColumnDataWStr* ColName = (ColumnDataWStr*)CurrentRd->GetColumn(1);
		lstrcpyn(Name[CurElem], ColName->GetValue(), 32);
		ColumnDataInt* ColType = (ColumnDataInt*)CurrentRd->GetColumn(2);
		Type[CurElem] = ColType->GetValue();
		ColumnDataInt* ColIcon = (ColumnDataInt*)CurrentRd->GetColumn(3);
		Icon[CurElem] = ColIcon->GetValue();
		ColumnDataInt* ColX = (ColumnDataInt*)CurrentRd->GetColumn(4);
		PosX[CurElem] = ColX->GetValue();
		ColumnDataInt* ColY = (ColumnDataInt*)CurrentRd->GetColumn(5);
		PosY[CurElem] = ColY->GetValue();
		for (int Loop = 0; Loop < 10; Loop++) {
			ColumnDataInt* ColLnkId = (ColumnDataInt*)CurrentRd->GetColumn(6 + Loop * 2);
			LnkId[CurElem][Loop] = ColLnkId->GetValue();
		}
		for (int Loop = 0; Loop < 10; Loop++) {
			ColumnDataInt* ColLnkTp = (ColumnDataInt*)CurrentRd->GetColumn(7 + Loop * 2);
			LnkTp[CurElem][Loop] = ColLnkTp->GetValue();
		}
		CurrentRd = CurrentRd->GetNextRecord();
		CurElem++;
		if (CurElem >= 1000) {
			CurElem = -1;
			break;
		}
	}
	delete ResultRd;
	UnlockTable(_T("ViewElement"));

	return CurElem;
}










/////////////////////////////////////////////////////////////////////////
//
// For ElementInfo table
//
/////////////////////////////////////////////////////////////////////////

int LowDbAccess::GetElementInfoInt(int CurrentId, int Index)
{
	int IntValue = 0;
	ColumnData* ColSch[1];
	ColSch[0] = new ColumnDataInt(_T("Id"), CurrentId);
	RecordData* RecSch = new RecordData(_T("ElementInfo"), ColSch, 1);
	LockTable(_T("ElementInfo"), 1);
	RecordData* RetRec = GetRecord(RecSch);
	UnlockTable(_T("ElementInfo"));
	if (RetRec != NULL) {
		ColumnDataInt* RetCol = (ColumnDataInt*)RetRec->GetColumn(Index);
		IntValue = RetCol->GetValue();
		delete RetRec;
	}
	delete RecSch;
	return IntValue;
}

void LowDbAccess::SetElementInfoInt(int CurrentId, int IntValue, int Index)
{
	TCHAR ParamIntName[5][10] = {_T("ParamInt1"), _T("ParamInt2"), _T("ParamInt3"), _T("ParamInt4"), _T("ParamInt5")};
	ColumnData* ColSch[1];
	ColumnData* ColUpd[1];
	ColSch[0] = new ColumnDataInt(_T("Id"), CurrentId);
	ColUpd[0] = new ColumnDataInt(ParamIntName[Index - 1], IntValue);
	RecordData* RecSch = new RecordData(_T("ElementInfo"), ColSch, 1);
	RecordData* RecUpd = new RecordData(_T("ElementInfo"), ColUpd, 1);
	LockTable(_T("ElementInfo"), 2);
	UpdateRecord(RecSch, RecUpd);
	UnlockTable(_T("ElementInfo"));
	delete RecUpd;
	delete RecSch;
}

void LowDbAccess::GetElementInfoStr(int CurrentId, TCHAR GetStr[256], int Index)
{
	ColumnData* ColSch[1];
	ColSch[0] = new ColumnDataInt(_T("Id"), CurrentId);
	RecordData* RecSch = new RecordData(_T("ElementInfo"), ColSch, 1);
	LockTable(_T("ElementInfo"), 1);
	RecordData* RetRec = GetRecord(RecSch);
	UnlockTable(_T("ElementInfo"));
	if (RetRec != NULL) {
		ColumnDataWStr* RetCol = (ColumnDataWStr*)RetRec->GetColumn(Index);
		lstrcpyn(GetStr, RetCol->GetValue(), 256);
		delete RetRec;
	}
	delete RecSch;
}

void LowDbAccess::SetElementInfoStr(int CurrentId, TCHAR SetStr[256], int Index)
{
	TCHAR ParamStrName[5][10] = {_T("ParamStr1"), _T("ParamStr2"), _T("ParamStr3"), _T("ParamStr4"), _T("ParamStr5")};
	ColumnData* ColSch[1];
	ColumnData* ColUpd[1];
	ColSch[0] = new ColumnDataInt(_T("Id"), CurrentId);
	ColUpd[0] = new ColumnDataWStr(ParamStrName[Index - 6], SetStr);
	RecordData* RecSch = new RecordData(_T("ElementInfo"), ColSch, 1);
	RecordData* RecUpd = new RecordData(_T("ElementInfo"), ColUpd, 1);
	LockTable(_T("ElementInfo"), 2);
	UpdateRecord(RecSch, RecUpd);
	UnlockTable(_T("ElementInfo"));
	delete RecUpd;
	delete RecSch;
}

void LowDbAccess::GetElementInfoBin(int CurrentId, BYTE BinDat[4096])
{
	ColumnData* ColSch[1];
	ColSch[0] = new ColumnDataInt(_T("Id"), CurrentId);
	RecordData* RecSch = new RecordData(_T("ElementInfo"), ColSch, 1);
	LockTable(_T("ElementInfo"), 1);
	RecordData* RetRec = GetRecord(RecSch);
	UnlockTable(_T("ElementInfo"));
	if (RetRec != NULL) {
		ColumnDataBin* RetCol = (ColumnDataBin*)RetRec->GetColumn(11);
		memcpy(BinDat, RetCol->GetValue(), 4096);
		delete RetRec;
	}
	delete RecSch;
}

void LowDbAccess::SetElementInfoBin(int CurrentId, BYTE BinDat[4096])
{
	ColumnData* ColSch[1];
	ColumnData* ColUpd[1];
	ColSch[0] = new ColumnDataInt(_T("Id"), CurrentId);
	ColUpd[0] = new ColumnDataBin(_T("ParamBin"), BinDat, 4096);
	RecordData* RecSch = new RecordData(_T("ElementInfo"), ColSch, 1);
	RecordData* RecUpd = new RecordData(_T("ElementInfo"), ColUpd, 1);
	LockTable(_T("ElementInfo"), 2);
	UpdateRecord(RecSch, RecUpd);
	UnlockTable(_T("ElementInfo"));
	delete RecUpd;
	delete RecSch;
}

// Acquire integer value from string column.
// CurrentId [in] : ID for the target element
// Index [in] : Index for the string (6:ParamStr1, 7:ParamStr2, ..., 10:ParamStr5)
// Return : Acquired value
int LowDbAccess::GetElementInfoStrAsInt(int CurrentId, int Index)
{
	TCHAR TmpBuf[256];
	ColumnData* ColSch[1];
	ColSch[0] = new ColumnDataInt(_T("Id"), CurrentId);
	RecordData* RecSch = new RecordData(_T("ElementInfo"), ColSch, 1);
	LockTable(_T("ElementInfo"), 1);
	RecordData* RetRec = GetRecord(RecSch);
	UnlockTable(_T("ElementInfo"));
	if (RetRec != NULL) {
		ColumnDataWStr* RetCol = (ColumnDataWStr*)RetRec->GetColumn(Index);
		lstrcpyn(TmpBuf, RetCol->GetValue(), 256);
		delete RetRec;
	}
	delete RecSch;
	DWORD Ret = (DWORD)*TmpBuf;
	return Ret;
}

// Set integer value to string column.
// CurrentId [in] : ID for the target element
// Index [in] : Index for the string (6:ParamStr1, 7:ParamStr2, ..., 10:ParamStr5)
// Value [in] : Integer value to be stored
void LowDbAccess::SetElementInfoStrAsInt(int CurrentId, int Index, int Value)
{
	TCHAR TmpBuf[256];
	DWORD *PtrTmpBuf = (DWORD*)TmpBuf;
	*PtrTmpBuf = (DWORD)Value;
	TCHAR ParamStrName[5][10] = {_T("ParamStr1"), _T("ParamStr2"), _T("ParamStr3"), _T("ParamStr4"), _T("ParamStr5")};
	ColumnData* ColSch[1];
	ColumnData* ColUpd[1];
	ColSch[0] = new ColumnDataInt(_T("Id"), CurrentId);
	ColUpd[0] = new ColumnDataWStr(ParamStrName[Index - 6], TmpBuf);
	RecordData* RecSch = new RecordData(_T("ElementInfo"), ColSch, 1);
	RecordData* RecUpd = new RecordData(_T("ElementInfo"), ColUpd, 1);
	LockTable(_T("ElementInfo"), 2);
	UpdateRecord(RecSch, RecUpd);
	UnlockTable(_T("ElementInfo"));
	delete RecUpd;
	delete RecSch;
}

// 指定したIDのホスト名またはIPアドレスとポート番号を返却する
// TargetId : [in] : 取得する対象のID
// HostOrIpAddr : [out] : 取得したホスト名またはIPアドレス
// Port : [out] : 取得したポート番号
// [return] : 結果コード (0: 有効, -1: 無効)
int LowDbAccess::GetHostIpAddrPort(int TargetId, TCHAR HostOrIpAddr[256], int* Port)
{
	int ResultCode = 0;
	int IntValue = 0;
	ColumnData* ColSch[1];
	ColSch[0] = new ColumnDataInt(_T("Id"), TargetId);
	RecordData* RecSch = new RecordData(_T("ElementInfo"), ColSch, 1);
	LockTable(_T("ElementInfo"), 1);
	RecordData* RetRec = GetRecord(RecSch);
	UnlockTable(_T("ElementInfo"));
	if (RetRec != NULL) {
		ColumnDataInt* RetColType = (ColumnDataInt*)RetRec->GetColumn(1);
		int Type = RetColType->GetValue();
		// ホスト名／IPアドレスおよびポート番号が直指定の場合のみ
		if (Type == 0 || Type == 2) {
			ColumnDataInt* RetColPort = (ColumnDataInt*)RetRec->GetColumn(3);
			*Port = RetColPort->GetValue();
			ColumnDataWStr* RetColNameOrIpAddr = (ColumnDataWStr*)RetRec->GetColumn(6);
			TCHAR* NameOrIpAddr = RetColNameOrIpAddr->GetValue();
			lstrcpy(HostOrIpAddr, NameOrIpAddr);
		} else {
			ResultCode = -1;
		}
	}
	delete RecSch;
	delete RetRec;
	return ResultCode;
}

int LowDbAccess::GetTcpRecvOperationTypeInElementInfo(int TargetId)
{
	return LowDbAccess::GetInstance()->GetElementInfoInt(TargetId, 1);
}

void LowDbAccess::SetTcpRecvOperationTypeInElementInfo(int TargetId, int OpeType)
{
	LowDbAccess::GetInstance()->SetElementInfoInt(TargetId, OpeType, 1);
}

int LowDbAccess::GetTcpRecvCorrespodingIdInElementInfo(int TargetId)
{
	return LowDbAccess::GetInstance()->GetElementInfoInt(TargetId, 2);
}

void LowDbAccess::SetTcpRecvCorrespodingIdInElementInfo(int TargetId, int CorrId)
{
	LowDbAccess::GetInstance()->SetElementInfoInt(TargetId, CorrId, 2);
}

void LowDbAccess::ModifyElementInfoScheme()
{
	TableDef TabDefElementInfo(_T("NewElementInfo"), 500);
	ColumnDef* ElementInfoColDef[17];
	ElementInfoColDef[0] = new ColumnDefInt(_T("Id"));
	ElementInfoColDef[1] = new ColumnDefInt(_T("ParamInt1"));
	ElementInfoColDef[2] = new ColumnDefInt(_T("ParamInt2"));
	ElementInfoColDef[3] = new ColumnDefInt(_T("ParamInt3"));
	ElementInfoColDef[4] = new ColumnDefInt(_T("ParamInt4"));
	ElementInfoColDef[5] = new ColumnDefInt(_T("ParamInt5"));
	ElementInfoColDef[6] = new ColumnDefInt(_T("ParamInt6"));
	ElementInfoColDef[7] = new ColumnDefInt(_T("ParamInt7"));
	ElementInfoColDef[8] = new ColumnDefWStr(_T("ParamStr1"), 256);
	ElementInfoColDef[9] = new ColumnDefWStr(_T("ParamStr2"), 256);
	ElementInfoColDef[10] = new ColumnDefWStr(_T("ParamStr3"), 256);
	ElementInfoColDef[11] = new ColumnDefWStr(_T("ParamStr4"), 256);
	ElementInfoColDef[12] = new ColumnDefWStr(_T("ParamStr5"), 256);
	ElementInfoColDef[13] = new ColumnDefWStr(_T("ParamStr6"), 256);
	ElementInfoColDef[14] = new ColumnDefWStr(_T("ParamStr7"), 256);
	ElementInfoColDef[15] = new ColumnDefBin(_T("ParamBin"), 4096);
	for (int Loop = 0; Loop < 16; Loop++) {
		TabDefElementInfo.AddColumnDef(ElementInfoColDef[Loop]);
	}
	CreateTable(&TabDefElementInfo);
	LockTable(_T("ElementInfo"), LOCK_SHARE);
	RecordData* RecDat = GetRecord(_T("ElementInfo"));
	UnlockTable(_T("ElementInfo"));
	while (RecDat) {
		int ColDatId = ((ColumnDataInt*)RecDat->GetColumn(0))->GetValue();
		int ColDatParamInt1 = ((ColumnDataInt*)RecDat->GetColumn(1))->GetValue();
		int ColDatParamInt2 = ((ColumnDataInt*)RecDat->GetColumn(2))->GetValue();
		int ColDatParamInt3 = ((ColumnDataInt*)RecDat->GetColumn(3))->GetValue();
		int ColDatParamInt4 = ((ColumnDataInt*)RecDat->GetColumn(4))->GetValue();
		int ColDatParamInt5 = ((ColumnDataInt*)RecDat->GetColumn(5))->GetValue();
		TCHAR* ColDatParamStr1 = ((ColumnDataWStr*)RecDat->GetColumn(6))->GetValue();
		TCHAR* ColDatParamStr2 = ((ColumnDataWStr*)RecDat->GetColumn(7))->GetValue();
		TCHAR* ColDatParamStr3 = ((ColumnDataWStr*)RecDat->GetColumn(8))->GetValue();
		TCHAR* ColDatParamStr4 = ((ColumnDataWStr*)RecDat->GetColumn(9))->GetValue();
		TCHAR* ColDatParamStr5 = ((ColumnDataWStr*)RecDat->GetColumn(10))->GetValue();
		BYTE* ColDatParamBin = ((ColumnDataBin*)RecDat->GetColumn(11))->GetValue();
		ColumnData* ColDat[16];
		ColDat[0] = new ColumnDataInt(_T("Id"), ColDatId);
		ColDat[1] = new ColumnDataInt(_T("ParamInt1"), ColDatParamInt1);
		ColDat[2] = new ColumnDataInt(_T("ParamInt2"), ColDatParamInt2);
		ColDat[3] = new ColumnDataInt(_T("ParamInt3"), ColDatParamInt3);
		ColDat[4] = new ColumnDataInt(_T("ParamInt4"), ColDatParamInt4);
		ColDat[5] = new ColumnDataInt(_T("ParamInt5"), ColDatParamInt5);
		ColDat[6] = new ColumnDataInt(_T("ParamInt6"), 0);
		ColDat[7] = new ColumnDataInt(_T("ParamInt7"), 0);
		ColDat[8] = new ColumnDataWStr(_T("ParamStr1"), ColDatParamStr1);
		ColDat[9] = new ColumnDataWStr(_T("ParamStr2"), ColDatParamStr2);
		ColDat[10] = new ColumnDataWStr(_T("ParamStr3"), ColDatParamStr3);
		ColDat[11] = new ColumnDataWStr(_T("ParamStr4"), ColDatParamStr4);
		ColDat[12] = new ColumnDataWStr(_T("ParamStr5"), ColDatParamStr5);
		ColDat[13] = new ColumnDataWStr(_T("ParamStr6"), _T(""));
		ColDat[14] = new ColumnDataWStr(_T("ParamStr7"), _T(""));
		ColDat[15] = new ColumnDataBin(_T("ParamBin"), ColDatParamBin, 4096);
		RecordData* NewRecDat = new RecordData(_T("NewElementInfo"), ColDat, 16);
		LockTable(_T("NewElementInfo"), LOCK_EXCLUSIVE);
		InsertRecord(NewRecDat);
		UnlockTable(_T("NewElementInfo"));
		RecDat = RecDat->GetNextRecord();
	}
	UnlockTable(_T("ElementInfo"));
	DeleteTable(_T("ElementInfo"));
	RenameTable(_T("NewElementInfo"), _T("ElementInfo"));
}










/////////////////////////////////////////////////////////////////////////
//
// For multiple tables
//
/////////////////////////////////////////////////////////////////////////

void LowDbAccess::UpdateElementInfoFromViewElement()
{
	LockTable(_T("ViewElement"), 2);
	LockTable(_T("ElementInfo"), 2);

	RecordData* ResultRdVelem = GetRecord(_T("ViewElement"));
	RecordData* ResultRdEleIf = GetRecord(_T("ElementInfo"));

	RecordData* CurrentRdVelem;
	RecordData* CurrentRdEleIf;

	// Check ViewElement table.
	// If associated ElementInfo records do not exist, insert the ElementInfo records.
	CurrentRdVelem = ResultRdVelem;
	while (CurrentRdVelem != NULL) {
		ColumnDataInt* ClVelemId = (ColumnDataInt*)CurrentRdVelem->GetColumn(0);
		int VelemId = ClVelemId->GetValue();
		BOOL FndFlag = FALSE;
		CurrentRdEleIf = ResultRdEleIf;
		while (CurrentRdEleIf != NULL) {
			ColumnDataInt* ClVolId = (ColumnDataInt*)CurrentRdEleIf->GetColumn(0);
			int VolId = ClVolId->GetValue();
			if (VolId == VelemId) {
				FndFlag = TRUE;
				break;
			}
			CurrentRdEleIf = CurrentRdEleIf->GetNextRecord();
		}
		if (FndFlag == FALSE) {
			ColumnData* ColDatIns[12];
			ColDatIns[0]  = new ColumnDataInt(_T("Id"), VelemId);
			ColDatIns[1]  = new ColumnDataInt(_T("ParamInt1"), 0);
			ColDatIns[2]  = new ColumnDataInt(_T("ParamInt2"), 0);
			ColDatIns[3]  = new ColumnDataInt(_T("ParamInt3"), 0);
			ColDatIns[4]  = new ColumnDataInt(_T("ParamInt4"), 0);
			ColDatIns[5]  = new ColumnDataInt(_T("ParamInt5"), 0);
			ColDatIns[6]  = new ColumnDataWStr(_T("ParamStr1"), _T(""));
			ColDatIns[7]  = new ColumnDataWStr(_T("ParamStr2"), _T(""));
			ColDatIns[8]  = new ColumnDataWStr(_T("ParamStr3"), _T(""));
			ColDatIns[9]  = new ColumnDataWStr(_T("ParamStr4"), _T(""));
			ColDatIns[10] = new ColumnDataWStr(_T("ParamStr5"), _T(""));
			BYTE DummyBin[4096];
			ColDatIns[11] = new ColumnDataBin(_T("ParamBin"), DummyBin, 4096);
			RecordData* NewRdElemIf = new RecordData(_T("ElementInfo"), ColDatIns, 12);
			InsertRecord(NewRdElemIf);
			delete NewRdElemIf;
		}
		CurrentRdVelem = CurrentRdVelem->GetNextRecord();
	}

	// Check Volume table.
	// If associated ViewElement records do not exist, remove the ElementInfo records.
	RecordData* ResultRdEleIfIm = GetRecord(_T("ElementInfo"));
	CurrentRdEleIf = ResultRdEleIfIm;
	while (CurrentRdEleIf != NULL) {
		ColumnDataInt* ClEleIfId = (ColumnDataInt*)CurrentRdEleIf->GetColumn(0);
		int EleIfId = ClEleIfId->GetValue();
		BOOL FndFlag = FALSE;
		CurrentRdVelem = ResultRdVelem;
		while (CurrentRdVelem != NULL) {
			ColumnDataInt* ClVelemId = (ColumnDataInt*)CurrentRdVelem->GetColumn(0);
			int VelemId = ClVelemId->GetValue();
			if (EleIfId == VelemId) {
				FndFlag = TRUE;
				break;
			}
			CurrentRdVelem = CurrentRdVelem->GetNextRecord();
		}
		if (FndFlag == FALSE) {
			ColumnData* ColDatDel[1];
			ColDatDel[0] = new ColumnDataInt(_T("Id"), EleIfId);
			RecordData* DelRdVol = new RecordData(_T("ElementInfo"), ColDatDel, 1);
			DeleteRecord(DelRdVol);
			delete DelRdVol;
		}
		CurrentRdEleIf = CurrentRdEleIf->GetNextRecord();
	}

	UnlockTable(_T("ElementInfo"));
	UnlockTable(_T("ViewElement"));

	delete ResultRdVelem;
	delete ResultRdEleIf;
	delete ResultRdEleIfIm;
}

// テーブルが更新されている場合TRUEを返す
// OpType : in : 操作種別 (0:全体チェック, 1:全体リセット, 2:ElementInfoのみチェック, 3:ElementInfoのみリセット)
// 戻り値 : 何か変更されていればTRUE, そうでなければFALSEを返却する
BOOL LowDbAccess::IsUpdated(int OpType)
{
	BOOL Ret = FALSE;

	static int UpdPropertyVer = -1;
	static int UpdElementInfoVer = -1;
	static int UpdVariableVer = -1;

	if (OpType == 0 || OpType == 1) {
		int PropertyVer = GetTableVersion(_T("Property"));
		if (UpdPropertyVer != PropertyVer) {
			if (OpType == 1) {
				UpdPropertyVer = PropertyVer;
			}
			Ret = TRUE;
		}
	}
	if (OpType == 0 || OpType == 1 || OpType == 2 || OpType == 3) {
		int ElementInfoVer = GetTableVersion(_T("ElementInfo"));
		if (UpdElementInfoVer != ElementInfoVer) {
			if (OpType == 1 || OpType == 3) {
				UpdElementInfoVer = ElementInfoVer;
			}
			Ret = TRUE;
		}
	}
	if (OpType == 0 || OpType == 1) {
		int VariableVer = GetTableVersion(_T("Variable"));
		if (UpdVariableVer != VariableVer) {
			if (OpType == 1) {
				UpdVariableVer = VariableVer;
			}
			Ret = TRUE;
		}
	}

	return Ret;
}

// ワークスペースサイズおよびグリッド状態を設定する
// Width : in : 現在ワークスペースの幅(pixel)
// Height : in : 現在のワークスペースの高さ(pixel)
// GridType : in : 現在のグリッド状態(1: 1pixel, 8:8pixel)
// 戻り値 : 成功／失敗を示すフラグ (TRUE: 成功, FALSE: 失敗)
BOOL LowDbAccess::ChangeWorkspace(int Width, int Height, int GridTypeL)
{
	ColumnData* ColDat[4];
	ColDat[0] = new ColumnDataInt(_T("ValueInt1"), Width);
	ColDat[1] = new ColumnDataInt(_T("ValueInt2"), Height);
	ColDat[2] = new ColumnDataInt(_T("ValueInt3"), GridTypeL);
	RecordData* UpdateRdWs = new RecordData(_T("Property"), &ColDat[0], 3);
	ColDat[3] = new ColumnDataWStr(_T("Name"), _T("Workspace"));
	RecordData* SearchRdWs = new RecordData(_T("Property"), &ColDat[3], 1);
	LockTable(_T("Property"), 2);
	UpdateRecord(SearchRdWs, UpdateRdWs);
	UnlockTable(_T("Property"));
	delete UpdateRdWs;
	delete SearchRdWs;

	LockTable(_T("ViewElement"), LOCK_SHARE);
	RecordData* ResultRd = GetRecord(_T("ViewElement"));
	UnlockTable(_T("ViewElement"));

	RecordData* LoopRd = ResultRd;
	while (LoopRd != NULL) {
		ColumnDataInt* ColId = (ColumnDataInt*)LoopRd->GetColumn(0);
		ColumnDataInt* ColX = (ColumnDataInt*)LoopRd->GetColumn(4);
		ColumnDataInt* ColY = (ColumnDataInt*)LoopRd->GetColumn(5);
		LoopRd = LoopRd->GetNextRecord();
		if (ColId == NULL || ColX == NULL || ColY == NULL) {
			continue;
		}
		int Id = ColId->GetValue();
		int X = ColX->GetValue();
		int Y = ColY->GetValue();
		int ModX = X;
		int ModY = Y;
		if (X > Width - 32) {
			ModX = Width - 32;
		}
		if (Y > Height - 32) {
			ModY = Height - 32;
		}
		if (ModX == X && ModY == Y) {
			continue;
		}

		// Record for search
		ColumnData* ColDatSrh[1];
		ColDatSrh[0] = new ColumnDataInt(_T("Id"), Id);
		RecordData* SearchRd = new RecordData(_T("ViewElement"), &ColDatSrh[0], 1);

		// Record for update
		ColumnData* ColDatUpd[2];
		ColDatUpd[0] = new ColumnDataInt(_T("x"), ModX);
		ColDatUpd[1] = new ColumnDataInt(_T("y"), ModY);
		RecordData* UpdateRd = new RecordData(_T("ViewElement"), &ColDatUpd[0], 2);

		// Update record
		LockTable(_T("ViewElement"), LOCK_EXCLUSIVE);
		UpdateRecord(SearchRd, UpdateRd);
		UnlockTable(_T("ViewElement"));

		delete SearchRd;
		delete UpdateRd;
	}
	delete ResultRd;

	return TRUE;
}

int LowDbAccess::DeleteAllRecords(TCHAR TableName[TABLE_NAME_SIZE])
{
	LockTable(TableName, LOCK_EXCLUSIVE);
	DeleteRecord(TableName);
	UnlockTable(TableName);
	return 0;
}

int LowDbAccess::StkFwRepositoryCreateTable()
{
	// Create ViewElement table
	TableDef TabDefViewElement(_T("ViewElement"), 500);
	ColumnDef* ViewElementColDef[26];
	ViewElementColDef[0] = new ColumnDefInt(_T("Id"));
	ViewElementColDef[1] = new ColumnDefWStr(_T("Name"), 32);
	ViewElementColDef[2] = new ColumnDefInt(_T("Type"));
	ViewElementColDef[3] = new ColumnDefInt(_T("Icon"));
	ViewElementColDef[4] = new ColumnDefInt(_T("x"));
	ViewElementColDef[5] = new ColumnDefInt(_T("y"));
	ViewElementColDef[6] = new ColumnDefInt(_T("LinkId0"));
	ViewElementColDef[7] = new ColumnDefInt(_T("LinkTp0"));
	ViewElementColDef[8] = new ColumnDefInt(_T("LinkId1"));
	ViewElementColDef[9] = new ColumnDefInt(_T("LinkTp1"));
	ViewElementColDef[10] = new ColumnDefInt(_T("LinkId2"));
	ViewElementColDef[11] = new ColumnDefInt(_T("LinkTp2"));
	ViewElementColDef[12] = new ColumnDefInt(_T("LinkId3"));
	ViewElementColDef[13] = new ColumnDefInt(_T("LinkTp3"));
	ViewElementColDef[14] = new ColumnDefInt(_T("LinkId4"));
	ViewElementColDef[15] = new ColumnDefInt(_T("LinkTp4"));
	ViewElementColDef[16] = new ColumnDefInt(_T("LinkId5"));
	ViewElementColDef[17] = new ColumnDefInt(_T("LinkTp5"));
	ViewElementColDef[18] = new ColumnDefInt(_T("LinkId6"));
	ViewElementColDef[19] = new ColumnDefInt(_T("LinkTp6"));
	ViewElementColDef[20] = new ColumnDefInt(_T("LinkId7"));
	ViewElementColDef[21] = new ColumnDefInt(_T("LinkTp7"));
	ViewElementColDef[22] = new ColumnDefInt(_T("LinkId8"));
	ViewElementColDef[23] = new ColumnDefInt(_T("LinkTp8"));
	ViewElementColDef[24] = new ColumnDefInt(_T("LinkId9"));
	ViewElementColDef[25] = new ColumnDefInt(_T("LinkTp9"));
	for (int Loop = 0; Loop < 26; Loop++) {
		TabDefViewElement.AddColumnDef(ViewElementColDef[Loop]);
	}
	if (CreateTable(&TabDefViewElement) != 0) {
		return -1;
	}

	// Create Property table
	TableDef TabDefProperty(_T("Property"), 1000);
	ColumnDef* PropertyColDef[7];
	PropertyColDef[0] = new ColumnDefWStr(_T("Name"), 32);
	PropertyColDef[1] = new ColumnDefInt(_T("ValueInt1"));
	PropertyColDef[2] = new ColumnDefInt(_T("ValueInt2"));
	PropertyColDef[3] = new ColumnDefInt(_T("ValueInt3"));
	PropertyColDef[4] = new ColumnDefWStr(_T("ValueStr1"), 256);
	PropertyColDef[5] = new ColumnDefWStr(_T("ValueStr2"), 256);
	PropertyColDef[6] = new ColumnDefWStr(_T("ValueStr3"), 256);
	for (int Loop = 0; Loop < 7; Loop++) {
		TabDefProperty.AddColumnDef(PropertyColDef[Loop]);
	}
	if (CreateTable(&TabDefProperty) != 0) {
		return -1;
	}

	// Create Variable table
	TableDef TabDefVariable(_T("Variable"), 1000);
	ColumnDef* VariableColDef[7];
	VariableColDef[0] = new ColumnDefInt(_T("ID"));
	VariableColDef[1] = new ColumnDefWStr(_T("Name"), 32);
	VariableColDef[2] = new ColumnDefWStr(_T("Desc"), 64);
	VariableColDef[3] = new ColumnDefInt(_T("Type"));
	VariableColDef[4] = new ColumnDefInt(_T("Flag"));
	VariableColDef[5] = new ColumnDefInt(_T("Size"));
	VariableColDef[6] = new ColumnDefStr(_T("UdTime"), 20);
	for (int Loop = 0; Loop < 7; Loop++) {
		TabDefVariable.AddColumnDef(VariableColDef[Loop]);
	}
	if (CreateTable(&TabDefVariable) != 0) {
		return -1;
	}

	// Create VarCommDat table
	TableDef TabDefVarCommDat(_T("VarCommDat"), 10000);
	ColumnDef* VarCommDatColDef[3];
	VarCommDatColDef[0] = new ColumnDefInt(_T("ID"));
	VarCommDatColDef[1] = new ColumnDefInt(_T("Index"));
	VarCommDatColDef[2] = new ColumnDefBin(_T("CommDat"), 10000);
	for (int Loop = 0; Loop < 3; Loop++) {
		TabDefVarCommDat.AddColumnDef(VarCommDatColDef[Loop]);
	}
	if (CreateTable(&TabDefVarCommDat) != 0) {
		return -1;
	}

	// Create ElementInfo table
	TableDef TabDefElementInfo(_T("ElementInfo"), 500);
	ColumnDef* ElementInfoColDef[12];
	ElementInfoColDef[0] = new ColumnDefInt(_T("Id"));
	ElementInfoColDef[1] = new ColumnDefInt(_T("ParamInt1"));
	ElementInfoColDef[2] = new ColumnDefInt(_T("ParamInt2"));
	ElementInfoColDef[3] = new ColumnDefInt(_T("ParamInt3"));
	ElementInfoColDef[4] = new ColumnDefInt(_T("ParamInt4"));
	ElementInfoColDef[5] = new ColumnDefInt(_T("ParamInt5"));
	ElementInfoColDef[6] = new ColumnDefWStr(_T("ParamStr1"), 256);
	ElementInfoColDef[7] = new ColumnDefWStr(_T("ParamStr2"), 256);
	ElementInfoColDef[8] = new ColumnDefWStr(_T("ParamStr3"), 256);
	ElementInfoColDef[9] = new ColumnDefWStr(_T("ParamStr4"), 256);
	ElementInfoColDef[10] = new ColumnDefWStr(_T("ParamStr5"), 256);
	ElementInfoColDef[11] = new ColumnDefBin(_T("ParamBin"), 4096);
	for (int Loop = 0; Loop < 12; Loop++) {
		TabDefElementInfo.AddColumnDef(ElementInfoColDef[Loop]);
	}
	if (CreateTable(&TabDefElementInfo) != 0) {
		return -1;
	}

	return 0;
}

int LowDbAccess::StkFwRepositoryInitialize(int CurrentDbVersion)
{
	DeleteAllRecords(_T("ViewElement"));
	DeleteAllRecords(_T("ElementInfo"));
	DeleteAllRecords(_T("Variable"));
	DeleteAllRecords(_T("VarCommDat"));

	DeleteProperty(_T("ViewElement"));
	InsertProperty(_T("ViewElement"), 1, 11, 1, _T("TCP receiver"), _T(""), _T("Initiator"));
	InsertProperty(_T("ViewElement"), 2, 42, 1, _T("Load Data"), _T(""), _T("Initiator"));
	InsertProperty(_T("ViewElement"), 3, 39, 1, _T("Empty box"), _T(""), _T("Initiator"));
	InsertProperty(_T("ViewElement"), 4, 21, 0, _T("TCP sender"), _T(""), _T("Terminator"));
	InsertProperty(_T("ViewElement"), 5, 43, 0, _T("Store Data"), _T(""), _T("Terminator"));
	InsertProperty(_T("ViewElement"), 6, 40, 0, _T("Empty box"), _T(""), _T("Terminator"));
	InsertProperty(_T("ViewElement"), 7, 1, 0, _T("TCP sender"), _T(""), _T("Stopper"));
	InsertProperty(_T("ViewElement"), 8, 41, 0, _T("Store Data"), _T(""), _T("Stopper"));
	InsertProperty(_T("ViewElement"), 9, 38, 0, _T("Empty box"), _T(""), _T("Stopper"));
	InsertProperty(_T("ViewElement"), 10, 37, 0, _T("Check flag"), _T(""), _T("Check point"));
	InsertProperty(_T("ViewElement"), 11, 33, 0, _T("Check data"), _T(""), _T("Check point"));
	InsertProperty(_T("ViewElement"), 12, 35, 0, _T("Timer"), _T(""), _T("Check point"));
	InsertProperty(_T("ViewElement"), 13, 36, 0, _T("Change flag"), _T(""), _T("Action"));
	InsertProperty(_T("ViewElement"), 14, 32, 0, _T("Change data"), _T(""), _T("Action"));
	InsertProperty(_T("ViewElement"), 15, 34, 0, _T("Aggregation/Distribution"), _T(""), _T("Action"));
	InsertProperty(_T("ViewElement"), 16, 44, 0, _T("Close port"), _T(""), _T("Action"));
	InsertProperty(_T("ViewElement"), 17, 45, 0, _T("Mapper"), _T(""), _T("Action"));
	InsertProperty(_T("ViewElement"), 18, 46, 0, _T("Write file"), _T(""), _T("Action"));
	InsertProperty(_T("ViewElement"), 19, 47, 0, _T("Read file"), _T(""), _T("Action"));
	InsertProperty(_T("ViewElement"), 20, 48, 0, _T("Execute program"), _T(""), _T("Action"));
	InsertProperty(_T("ViewElement"), 21, 72, 1, _T("UDP receiver"), _T(""), _T("Initiator"));
	InsertProperty(_T("ViewElement"), 22, 73, 0, _T("UDP sender"), _T(""), _T("Terminator"));
	InsertProperty(_T("ViewElement"), 23, 71, 0, _T("UDP sender"), _T(""), _T("Stopper"));

	DeleteProperty(_T("LinkInfo"));
	InsertProperty(_T("LinkInfo"), 1, 4, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 1, 5, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 1, 6, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 1, 7, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 1, 8, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 1, 9, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 1, 10, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 1, 11, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 1, 12, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 1, 13, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 1, 14, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 1, 15, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 1, 16, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 1, 17, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 1, 18, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 1, 19, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 1, 20, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 1, 22, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 1, 23, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 2, 4, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 2, 5, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 2, 6, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 2, 7, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 2, 8, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 2, 9, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 2, 10, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 2, 11, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 2, 12, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 2, 13, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 2, 14, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 2, 15, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 2, 16, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 2, 17, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 2, 18, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 2, 19, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 2, 20, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 2, 22, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 2, 23, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 3, 4, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 3, 5, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 3, 6, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 3, 7, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 3, 8, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 3, 9, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 3, 10, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 3, 11, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 3, 12, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 3, 13, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 3, 14, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 3, 15, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 3, 16, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 3, 17, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 3, 18, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 3, 19, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 3, 20, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 3, 22, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 3, 23, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 4, 1, 1, _T("122"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 4, 2, 1, _T("122"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 4, 3, 1, _T("122"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 4, 21, 1, _T("122"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 5, 1, 1, _T("122"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 5, 2, 1, _T("122"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 5, 3, 1, _T("122"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 5, 21, 1, _T("122"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 6, 1, 1, _T("122"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 6, 2, 1, _T("122"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 6, 3, 1, _T("122"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 6, 21, 1, _T("122"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 10, 4, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 10, 5, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 10, 6, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 10, 7, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 10, 8, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 10, 9, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 10, 10, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 10, 11, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 10, 12, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 10, 13, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 10, 14, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 10, 15, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 10, 16, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 10, 17, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 10, 18, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 10, 19, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 10, 20, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 10, 22, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 10, 23, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 11, 4, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 11, 5, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 11, 6, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 11, 7, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 11, 8, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 11, 9, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 11, 10, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 11, 11, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 11, 12, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 11, 13, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 11, 14, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 11, 15, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 11, 16, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 11, 17, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 11, 18, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 11, 19, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 11, 20, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 11, 22, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 11, 23, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 12, 4, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 12, 5, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 12, 6, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 12, 7, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 12, 8, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 12, 9, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 12, 10, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 12, 11, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 12, 12, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 12, 13, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 12, 14, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 12, 15, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 12, 16, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 12, 17, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 12, 18, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 12, 19, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 12, 20, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 12, 22, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 12, 23, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 13, 4, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 13, 5, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 13, 6, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 13, 7, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 13, 8, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 13, 9, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 13, 10, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 13, 11, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 13, 12, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 13, 13, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 13, 14, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 13, 15, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 13, 16, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 13, 17, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 13, 18, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 13, 19, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 13, 20, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 13, 22, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 13, 23, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 14, 4, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 14, 5, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 14, 6, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 14, 7, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 14, 8, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 14, 9, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 14, 10, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 14, 11, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 14, 12, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 14, 13, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 14, 14, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 14, 15, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 14, 16, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 14, 17, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 14, 18, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 14, 19, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 14, 20, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 14, 22, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 14, 23, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 15, 4, 10, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 15, 5, 10, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 15, 6, 10, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 15, 7, 10, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 15, 8, 10, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 15, 9, 10, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 15, 10, 10, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 15, 11, 10, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 15, 12, 10, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 15, 13, 10, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 15, 14, 10, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 15, 15, 10, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 15, 16, 10, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 15, 17, 10, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 15, 18, 10, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 15, 19, 10, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 15, 20, 10, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 15, 22, 10, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 15, 23, 10, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 16, 4, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 16, 5, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 16, 6, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 16, 7, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 16, 8, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 16, 9, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 16, 10, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 16, 11, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 16, 12, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 16, 13, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 16, 14, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 16, 15, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 16, 16, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 16, 17, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 16, 18, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 16, 19, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 16, 20, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 17, 4, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 17, 5, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 17, 6, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 17, 7, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 17, 8, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 17, 9, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 17, 10, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 17, 11, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 17, 12, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 17, 13, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 17, 14, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 17, 15, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 17, 16, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 17, 17, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 17, 18, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 17, 19, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 17, 20, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 17, 22, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 17, 23, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 18, 4, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 18, 5, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 18, 6, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 18, 7, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 18, 8, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 18, 9, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 18, 10, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 18, 11, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 18, 12, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 18, 13, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 18, 14, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 18, 15, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 18, 16, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 18, 17, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 18, 18, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 18, 19, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 18, 20, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 18, 22, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 18, 23, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 19, 4, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 19, 5, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 19, 6, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 19, 7, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 19, 8, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 19, 9, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 19, 10, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 19, 11, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 19, 12, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 19, 13, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 19, 14, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 19, 15, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 19, 16, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 19, 17, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 19, 18, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 19, 19, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 19, 20, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 19, 22, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 19, 23, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 20, 4, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 20, 5, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 20, 6, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 20, 7, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 20, 8, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 20, 9, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 20, 10, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 20, 11, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 20, 12, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 20, 13, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 20, 14, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 20, 15, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 20, 16, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 20, 17, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 20, 18, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 20, 19, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 20, 20, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 20, 22, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 20, 23, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 21, 4, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 21, 5, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 21, 6, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 21, 7, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 21, 8, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 21, 9, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 21, 10, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 21, 11, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 21, 12, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 21, 13, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 21, 14, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 21, 15, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 21, 16, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 21, 17, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 21, 18, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 21, 19, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 21, 20, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 21, 22, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 21, 23, 1, _T("101"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 22, 1, 1, _T("122"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 22, 2, 1, _T("122"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 22, 3, 1, _T("122"), _T(""), _T(""));
	InsertProperty(_T("LinkInfo"), 22, 21, 1, _T("122"), _T(""), _T(""));

	DeleteProperty(_T("MaxLink"));
	InsertProperty(_T("MaxLink"), 1, 1, 1, _T(""), _T(""), _T(""));
	InsertProperty(_T("MaxLink"), 2, 1, 1, _T(""), _T(""), _T(""));
	InsertProperty(_T("MaxLink"), 3, 1, 1, _T(""), _T(""), _T(""));
	InsertProperty(_T("MaxLink"), 4, 1, 1, _T(""), _T(""), _T(""));
	InsertProperty(_T("MaxLink"), 5, 1, 1, _T(""), _T(""), _T(""));
	InsertProperty(_T("MaxLink"), 6, 1, 1, _T(""), _T(""), _T(""));
	InsertProperty(_T("MaxLink"), 7, 1, 1, _T(""), _T(""), _T(""));
	InsertProperty(_T("MaxLink"), 8, 1, 1, _T(""), _T(""), _T(""));
	InsertProperty(_T("MaxLink"), 9, 1, 1, _T(""), _T(""), _T(""));
	InsertProperty(_T("MaxLink"), 10, 1, 1, _T(""), _T(""), _T(""));
	InsertProperty(_T("MaxLink"), 11, 1, 1, _T(""), _T(""), _T(""));
	InsertProperty(_T("MaxLink"), 12, 1, 1, _T(""), _T(""), _T(""));
	InsertProperty(_T("MaxLink"), 13, 1, 1, _T(""), _T(""), _T(""));
	InsertProperty(_T("MaxLink"), 14, 1, 1, _T(""), _T(""), _T(""));
	InsertProperty(_T("MaxLink"), 15, 10, 10, _T(""), _T(""), _T(""));
	InsertProperty(_T("MaxLink"), 16, 1, 1, _T(""), _T(""), _T(""));
	InsertProperty(_T("MaxLink"), 17, 1, 1, _T(""), _T(""), _T(""));
	InsertProperty(_T("MaxLink"), 18, 1, 1, _T(""), _T(""), _T(""));
	InsertProperty(_T("MaxLink"), 19, 1, 1, _T(""), _T(""), _T(""));
	InsertProperty(_T("MaxLink"), 20, 1, 1, _T(""), _T(""), _T(""));
	InsertProperty(_T("MaxLink"), 21, 1, 1, _T(""), _T(""), _T(""));
	InsertProperty(_T("MaxLink"), 22, 1, 1, _T(""), _T(""), _T(""));
	InsertProperty(_T("MaxLink"), 23, 1, 1, _T(""), _T(""), _T(""));

	DeleteProperty(_T("Workspace"));
	InsertProperty(_T("Workspace"), 512, 400, 8, _T(""), _T(""), _T(""));
	DeleteProperty(_T("RefreshInterval"));
	InsertProperty(_T("RefreshInterval"), 30, 0, 0, _T(""), _T(""), _T(""));
	DeleteProperty(_T("DbVersion"));
	InsertProperty(_T("DbVersion"), CurrentDbVersion, 0, 0, _T(""), _T(""), _T(""));
	DeleteProperty(_T("MaxId"));
	InsertProperty(_T("MaxId"), 1, 0, 0, _T(""), _T(""), _T(""));
	DeleteProperty(_T("MaxVarId"));
	InsertProperty(_T("MaxVarId"), 0, 0, 0, _T(""), _T(""), _T(""));

	return 0;
}
