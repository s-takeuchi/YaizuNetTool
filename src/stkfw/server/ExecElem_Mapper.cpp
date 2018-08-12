#include <windows.h>
#include "..\..\..\..\YaizuComLib\src\\stksocket\stksocket.h"
#include "ExecElem_Mapper.h"
#include "VarController.h"
#include "LowDbAccess.h"

ExecElem_Mapper::ExecElem_Mapper(int Id) : ExecElem(Id)
{
	//Mapperのマップ済変数のIDを初期化する
	BYTE TmpDat[4096];
	INT16* TmpDatInt = (INT16*)TmpDat;
	for (int Loop = 0; Loop < 2048; Loop++) {
		TmpDatInt[Loop] = (INT16)-1;
	}
	LowDbAccess::GetInstance()->SetElementInfoBin(Id, TmpDat);
}

// Destructor
ExecElem_Mapper::~ExecElem_Mapper()
{
}

int ExecElem_Mapper::Execute()
{
	BYTE* InputDat = (BYTE*)GetData();
	int InputDatLength = GetDataLength();
	if (InputDat == NULL || InputDatLength == 0) {
		return 2;
	}

	TCHAR SearchVarName[256];
	TCHAR ReplaceVarName[256];
	TCHAR SearchPrefixName[32];
	TCHAR ReplacePrefixName[32];
	int Counter = LowDbAccess::GetInstance()->GetElementInfoParamInt(ElementId, 1);
	int ChkUseOnce = LowDbAccess::GetInstance()->GetElementInfoParamInt(ElementId, 2);
	LowDbAccess::GetInstance()->GetElementInfoParamStr(ElementId, SearchPrefixName, 1);
	LowDbAccess::GetInstance()->GetElementInfoParamStr(ElementId, ReplacePrefixName, 2);
	BYTE TmpDat[4096];
	INT16* TmpDatInt = (INT16*)TmpDat;

	while (TRUE) {
		if (Counter < 0 || Counter > 99999) {
			Counter = 0;
		}
		wsprintf(SearchVarName, _T("%s%05d"), SearchPrefixName, Counter);
		wsprintf(ReplaceVarName, _T("%s%05d"), ReplacePrefixName, Counter);
		int SearchVarId = VarCon_GetCommunicationVariableId(SearchVarName);
		int ReplaceVarId = VarCon_GetCommunicationVariableId(ReplaceVarName);
		if (SearchVarId == -1 || ReplaceVarId == -1) {
			return 2;
		}

		// もしUse Only Onceオプションが設定されていたら
		int TailOfTmpDatInt = 0;
		if (ChkUseOnce == 1) {
			LowDbAccess::GetInstance()->GetElementInfoBin(ElementId, TmpDat);
			BOOL FndFlag = FALSE;
			for (TailOfTmpDatInt = 0; TailOfTmpDatInt < 2048; TailOfTmpDatInt++) {
				INT16 UsedId = (INT16)TmpDatInt[TailOfTmpDatInt];
				if (UsedId == (INT16)Counter) {
					FndFlag = TRUE;
					break;
				}
				if (UsedId == (INT16)-1) {
					break;
				}
			}
			if (FndFlag == TRUE) {
				Counter++;
				continue;
			}
		}

		BYTE* SearchVarDat;
		BYTE* ReplaceVarDat;
		int SearchVarDatSize = VarCon_GetCommunicationVariableSize(SearchVarId);
		int ReplaceVarDatSize = VarCon_GetCommunicationVariableSize(ReplaceVarId);
		if (SearchVarDatSize != -1 && ReplaceVarDatSize != -1) {
			SearchVarDat = new BYTE[SearchVarDatSize];
			VarCon_GetCommunicationVariable(SearchVarId, SearchVarDat, SearchVarDatSize);

			if (memcmp(InputDat, SearchVarDat, SearchVarDatSize) == 0) {
				ReplaceVarDat = new BYTE[ReplaceVarDatSize];
				VarCon_GetCommunicationVariable(ReplaceVarId, ReplaceVarDat, ReplaceVarDatSize);

				delete InputDat;
				delete SearchVarDat;
				SetData((void*)ReplaceVarDat);
				SetDataLength(ReplaceVarDatSize);
				// もしUse Only Onceオプションが設定されていたら
				if (ChkUseOnce == 1) {
					TmpDatInt[TailOfTmpDatInt] = (INT16)Counter;
					LowDbAccess::GetInstance()->SetElementInfoBin(ElementId, TmpDat);
				}
				return 0;
			}
			delete SearchVarDat;
		}
		Counter++;
	}
	return 0;
}
