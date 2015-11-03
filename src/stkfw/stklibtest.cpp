#include "..\..\..\YaizuComLib\src\\stksocket\stksocket.h"
#include <windows.h>
#include <shlwapi.h>
#include <tchar.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <shlobj.h>
#include <shellapi.h>
#include <shlwapi.h>
#include <psapi.h>
#include <Lm.h>

#include "resource.h"

#include "..\stklib\GameStatus.h"
#include "..\stklib\GameStatusElement.h"
#include "..\stklib\ActorStatus.h"
#include "..\stklib\ActorStatusElement.h"

#include "..\..\..\YaizuComLib\src\\stk_about\stk_about.h"
#include "..\..\..\YaizuComLib\src\stkthread\stkthread.h"
#include "..\..\..\YaizuComLib\src\stkthreadgui\stkthreadgui.h"
#include "..\..\..\YaizuComLib\src\commonfunc\StkGeneric.h"
#include "VarCon.h"

#include "NetGseEx.h"
#include "NetManagerAseEx.h"
#include "NetAseEx.h"

#include "..\stklib\StkFont.h"

#include "stklibtest.h"
#include "stkprop.h"
#include "LowDbAccess.h"
#include "MyMsgProc.h"

#define DB_VERSION 3

TCHAR szTitle[32];
TCHAR szWindowClass[32];

TCHAR StartDir[MAX_PATH];
TCHAR CurrentStdFileName[1024];

HWND hWnd;
HINSTANCE Inst;

GameStatus Gs;
ActorStatus As;

int NewWidth;
int NewHeight;

int MouseActionStatus = 0;

// スレッド実行中にStkFwは内部的に使用するデータをElementInfoに書き込む。
// このため，ユーザーから見えるデータが実際には何も更新されていないにも
// かかわらず，スレッド実行後にファイルOpenやNewを選択すると，データが
// 更新されているというダイアログが表示されてしまう。
// IsUdtElemInfoはこの問題を回避するためのフラグで，スレッド実行前に既に
// ElementInfoが更新されていればTRUEになる。
BOOL IsUdtElemInfo;

void SetWindowTitle(TCHAR[1024]);
ATOM MyRegisterClass( HINSTANCE hInstance);
BOOL InitInstance( HINSTANCE, int);
LRESULT CALLBACK WndProc( HWND, UINT, WPARAM, LPARAM);
DWORD WINAPI NthShowStkThreadController(LPVOID);
DWORD WINAPI NthShowStkDataWindow(LPVOID);
DWORD WINAPI NthShowVariableController(LPVOID);
int SetAboutInfo();
INT_PTR CALLBACK NewWorkSpaceDialog(HWND, UINT, WPARAM, LPARAM);
void StartProc(void);
void StopProc(void);
void StartProcForCmd(void);
void StopProcForCmd(void);
void CheckExecutorLocalGroup(void);
void ShowRunTimeInformation(void);

// Version 1.1.0 → Version 1.2.0
int DbMigration_00_01()
{
	LowDbAccess* Lda = LowDbAccess::GetInstance();
	// PropertyテーブルにDbVersion = 1を追加する
	Lda->InsertProperty(_T("DbVersion"), 1, 0, 0, _T(""), _T(""), _T(""));
	// MapperのUseOnlyOnce属性を設定する
	int AcquiredIds[ActorStatus::ACTOR_STATUS_COUNT];
	int IdCnt = Lda->GetViewElementIdsFromType(AcquiredIds, ActorStatus::ACTOR_STATUS_COUNT, 17);
	for (int Loop = 0; Loop < IdCnt; Loop++) {
		Lda->SetElementInfoInt(AcquiredIds[Loop], 0, 2);
	}
	return 1;
}

// Version 1.2.0 → Version 1.3.0
int DbMigration_01_02()
{
	LowDbAccess* Lda = LowDbAccess::GetInstance();
	// PropertyテーブルのDbVersionを2に変更する
	Lda->SetPropertyInteger(_T("DbVersion"), 1, 2);
	// Propertyテーブル:ViewElementを追加
	Lda->InsertProperty(_T("ViewElement"), 18, 46, 0, _T("Write file [Action]"), _T(""), _T("Menu"));
	Lda->InsertProperty(_T("ViewElement"), 19, 47, 0, _T("Read file [Action]"), _T(""), _T("Menu"));
	Lda->InsertProperty(_T("ViewElement"), 20, 48, 0, _T("Execute program [Action]"), _T(""), _T("Menu"));
	// Propertyテーブル:LinkInfoを追加
	for (int LoopOrg = 1; LoopOrg <= 3; LoopOrg++) {
		for (int LoopTgt = 18; LoopTgt <= 20; LoopTgt++) {
			Lda->InsertProperty(_T("LinkInfo"), LoopOrg, LoopTgt, 1, _T("101"), _T(""), _T(""));
		}
	}
	for (int LoopOrg = 10; LoopOrg <= 17; LoopOrg++) {
		for (int LoopTgt = 18; LoopTgt <= 20; LoopTgt++) {
			Lda->InsertProperty(_T("LinkInfo"), LoopOrg, LoopTgt, 1, _T("101"), _T(""), _T(""));
		}
	}
	for (int LoopOrg = 18; LoopOrg <= 20; LoopOrg++) {
		for (int LoopTgt = 4; LoopTgt <= 20; LoopTgt++) {
			Lda->InsertProperty(_T("LinkInfo"), LoopOrg, LoopTgt, 1, _T("101"), _T(""), _T(""));
		}
	}
	// Propertyテーブル:MaxLinkを追加
	Lda->InsertProperty(_T("MaxLink"), 18, 1, 1, _T(""), _T(""), _T(""));
	Lda->InsertProperty(_T("MaxLink"), 19, 1, 1, _T(""), _T(""), _T(""));
	Lda->InsertProperty(_T("MaxLink"), 20, 1, 1, _T(""), _T(""), _T(""));

	return 2;
}

// Version 1.3.0 → Version 1.4.0
int DbMigration_02_03()
{
	LowDbAccess* Lda = LowDbAccess::GetInstance();
	// PropertyテーブルのDbVersionを3に変更する
	Lda->SetPropertyInteger(_T("DbVersion"), 1, 3);
	// Update existing ViewElement in property table
	Lda->DeleteProperty(_T("ViewElement"));
	Lda->InsertProperty(_T("ViewElement"), 1, 11, 1, _T("TCP receiver"), _T(""), _T("Initiator"));
	Lda->InsertProperty(_T("ViewElement"), 2, 42, 1, _T("Load Data"), _T(""), _T("Initiator"));
	Lda->InsertProperty(_T("ViewElement"), 3, 39, 1, _T("Empty box"), _T(""), _T("Initiator"));
	Lda->InsertProperty(_T("ViewElement"), 4, 21, 0, _T("TCP sender"), _T(""), _T("Terminator"));
	Lda->InsertProperty(_T("ViewElement"), 5, 43, 0, _T("Store Data"), _T(""), _T("Terminator"));
	Lda->InsertProperty(_T("ViewElement"), 6, 40, 0, _T("Empty box"), _T(""), _T("Terminator"));
	Lda->InsertProperty(_T("ViewElement"), 7, 1, 0, _T("TCP sender"), _T(""), _T("Stopper"));
	Lda->InsertProperty(_T("ViewElement"), 8, 41, 0, _T("Store Data"), _T(""), _T("Stopper"));
	Lda->InsertProperty(_T("ViewElement"), 9, 38, 0, _T("Empty box"), _T(""), _T("Stopper"));
	Lda->InsertProperty(_T("ViewElement"), 10, 37, 0, _T("Check flag"), _T(""), _T("Check point"));
	Lda->InsertProperty(_T("ViewElement"), 11, 33, 0, _T("Check data"), _T(""), _T("Check point"));
	Lda->InsertProperty(_T("ViewElement"), 12, 35, 0, _T("Timer"), _T(""), _T("Check point"));
	Lda->InsertProperty(_T("ViewElement"), 13, 36, 0, _T("Change flag"), _T(""), _T("Action"));
	Lda->InsertProperty(_T("ViewElement"), 14, 32, 0, _T("Change data"), _T(""), _T("Action"));
	Lda->InsertProperty(_T("ViewElement"), 15, 34, 0, _T("Aggregation/Distribution"), _T(""), _T("Action"));
	Lda->InsertProperty(_T("ViewElement"), 16, 44, 0, _T("Close port"), _T(""), _T("Action"));
	Lda->InsertProperty(_T("ViewElement"), 17, 45, 0, _T("Mapper"), _T(""), _T("Action"));
	Lda->InsertProperty(_T("ViewElement"), 18, 46, 0, _T("Write file"), _T(""), _T("Action"));
	Lda->InsertProperty(_T("ViewElement"), 19, 47, 0, _T("Read file"), _T(""), _T("Action"));
	Lda->InsertProperty(_T("ViewElement"), 20, 48, 0, _T("Execute program"), _T(""), _T("Action"));
	// Propertyテーブル:ViewElementを追加
	Lda->InsertProperty(_T("ViewElement"), 21, 72, 1, _T("UDP receiver"), _T(""), _T("Initiator"));
	Lda->InsertProperty(_T("ViewElement"), 22, 73, 0, _T("UDP sender"), _T(""), _T("Terminator"));
	Lda->InsertProperty(_T("ViewElement"), 23, 71, 0, _T("UDP sender"), _T(""), _T("Stopper"));
	// Propertyテーブル:LinkInfoを追加
	Lda->InsertProperty(_T("LinkInfo"), 4, 21, 1, _T("122"), _T(""), _T(""));
	Lda->InsertProperty(_T("LinkInfo"), 5, 21, 1, _T("122"), _T(""), _T(""));
	Lda->InsertProperty(_T("LinkInfo"), 6, 21, 1, _T("122"), _T(""), _T(""));
	Lda->InsertProperty(_T("LinkInfo"), 22, 1, 1, _T("122"), _T(""), _T(""));
	Lda->InsertProperty(_T("LinkInfo"), 22, 2, 1, _T("122"), _T(""), _T(""));
	Lda->InsertProperty(_T("LinkInfo"), 22, 3, 1, _T("122"), _T(""), _T(""));
	Lda->InsertProperty(_T("LinkInfo"), 22, 21, 1, _T("122"), _T(""), _T(""));
	for (int LoopTgt = 4; LoopTgt <= 20; LoopTgt++) {
		Lda->InsertProperty(_T("LinkInfo"), 21, LoopTgt, 1, _T("101"), _T(""), _T(""));
	}
	for (int LoopOrg = 1; LoopOrg <= 3; LoopOrg++) {
		for (int LoopTgt = 22; LoopTgt <= 23; LoopTgt++) {
			Lda->InsertProperty(_T("LinkInfo"), LoopOrg, LoopTgt, 1, _T("101"), _T(""), _T(""));
		}
	}
	for (int LoopOrg = 10; LoopOrg <= 21; LoopOrg++) {
		if (LoopOrg == 15) {
			continue;
		}
		for (int LoopTgt = 22; LoopTgt <= 23; LoopTgt++) {
			Lda->InsertProperty(_T("LinkInfo"), LoopOrg, LoopTgt, 1, _T("101"), _T(""), _T(""));
		}
	}
	Lda->InsertProperty(_T("LinkInfo"), 15, 22, 1, _T("101"), _T(""), _T(""));
	Lda->InsertProperty(_T("LinkInfo"), 15, 23, 1, _T("101"), _T(""), _T(""));
	// Propertyテーブル:MaxLinkを追加
	Lda->InsertProperty(_T("MaxLink"), 21, 1, 1, _T(""), _T(""), _T(""));
	Lda->InsertProperty(_T("MaxLink"), 22, 1, 1, _T(""), _T(""), _T(""));
	Lda->InsertProperty(_T("MaxLink"), 23, 1, 1, _T(""), _T(""), _T(""));

	return 3;
}

// この関数を実行する前にLoadAllTableで全てのテーブルをロックしておく必要がある
// return == 0  :  DbVersion == LATEST_DB_VERSION または 無効
// return == -1 :  DbVersion > LATEST_DB_VERSION
// return == 1  :  DbVersion < LATEST_DB_VERSION
int DbMigration()
{
	int DbVersion = 0;

	DbVersion = LowDbAccess::GetInstance()->GetPropertyInteger(_T("DbVersion"), 1);

	if (DbVersion > DB_VERSION) {
		MyMsgProc::StkErr(MyMsgProc::STKFW_DBVERSION_UNKNOWN, hWnd);
		return -1;
	}
	if (DbVersion == DB_VERSION) {
		return 0;
	}
	MyMsgProc::StkInf(MyMsgProc::STKFW_DBVERSION_OLD, hWnd);

	if (DbVersion == 0) {
		DbVersion = DbMigration_00_01(); // Version 1.1.0 → Version 1.2.0
	}
	if (DbVersion == 1) {
		DbVersion = DbMigration_01_02(); // Version 1.2.0 → Version 1.3.0
	}
	if (DbVersion == 2) {
		DbVersion = DbMigration_02_03(); // Version 1.3.0 → Version 1.4.0
	}

	return 1;
}

// ActorStatusが更新されている場合TRUEを返す
// OpType : in : 操作種別 (0:取得, 1:更新)
// 戻り値 : out : 何か変更されていればTRUE
BOOL IsActorStatusUpdated(int OpType)
{
	static int UpdAceCnt = -1;
	static NetAseEx UpdAce[ActorStatus::ACTOR_STATUS_COUNT];

	if (OpType == 1) {
		UpdAceCnt = As.GetActorStatusElementCount();
		for (int Loop = 0; Loop < UpdAceCnt; Loop++) {
			ActorStatusElement* Ase = As.GetActorStatusElement(Loop);
			int AseId = Ase->GetId();
			if (AseId == 0) {
				continue;
			}
			NetAseEx* Nase = reinterpret_cast<NetAseEx*>(Ase);
			UpdAce[Loop].SetId(Nase->GetId());
			UpdAce[Loop].SetActorPos(Nase->GetActorPosX(), Nase->GetActorPosY());
			UpdAce[Loop].SetName(Nase->GetName());
			UpdAce[Loop].LinkCount = Nase->LinkCount;
			for (int LpCnt = 0; LpCnt < 10; LpCnt++) {
				UpdAce[Loop].LinkTo[LpCnt] = Nase->LinkTo[LpCnt];
				UpdAce[Loop].LinkType[LpCnt] = Nase->LinkType[LpCnt];
			}
		}
		return TRUE;
	} else {
		if (UpdAceCnt != As.GetActorStatusElementCount()) {
			return TRUE;
		}
		for (int Loop = 0; Loop < UpdAceCnt; Loop++) {
			ActorStatusElement* Ase = As.GetActorStatusElement(Loop);
			int AseId = Ase->GetId();
			if (AseId == 0) {
				continue;
			}
			NetAseEx* Nase = reinterpret_cast<NetAseEx*>(Ase);
			if (UpdAce[Loop].GetId() != Nase->GetId() ||
				UpdAce[Loop].GetActorPosX() != Nase->GetActorPosX() || 
				UpdAce[Loop].GetActorPosY() != Nase->GetActorPosY() ||
				UpdAce[Loop].LinkCount != Nase->LinkCount) {
				return TRUE;
			}
			if (lstrcmp(UpdAce[Loop].GetName(), Nase->GetName())) {
				return TRUE;
			}
			for (int LpCnt = 0; LpCnt < UpdAce[Loop].LinkCount; LpCnt++) {
				if (UpdAce[Loop].LinkTo[LpCnt] != Nase->LinkTo[LpCnt] || UpdAce[Loop].LinkType[LpCnt] != Nase->LinkType[LpCnt]) {
					return TRUE;
				}
			}
		}
	}
	return FALSE;
}

int ResetThreadController(BOOL DelAll)
{
	int Type[100];
	int ExecFlag[100];
	TCHAR Desc[100][256];
	int Count = 0;

	static int RegThId[256];
	static int RegThCnt = 0;
	int RegThIdTmp[256];
	TCHAR RegThNameTmp[100][256];
	TCHAR RegThDescTmp[100][256];
	int RegThCntTmp = 0;

	Count = LowDbAccess::GetInstance()->GetViewElementBasicInfoFromProperty(Type, ExecFlag, Desc);

	for (int Loop = 0; Loop < As.GetActorStatusElementCount(); Loop++) {
		ActorStatusElement* Ase = As.GetActorStatusElement(Loop);
		if (Ase->GetId() == 0) {
			continue;
		}
		NetAseEx* Nase = reinterpret_cast<NetAseEx*>(Ase);
		for (int LoopVe = 0; LoopVe < Count; LoopVe++) {
			if (Type[LoopVe] == Nase->GetType() && ExecFlag[LoopVe] == 1) {
				if (RegThCntTmp < 100) {
					RegThIdTmp[RegThCntTmp] = Nase->GetId();
					lstrcpy(RegThNameTmp[RegThCntTmp], Nase->GetName());
					lstrcpy(RegThDescTmp[RegThCntTmp], Desc[LoopVe]);
					RegThCntTmp++;
				}
			}
		}
	}

	// Unregister all threads if DelAll flag is true.
	if (DelAll == TRUE) {
		for (int Loop = 0; Loop < RegThCnt; Loop++) {
			DeleteStkThreadForGui(RegThId[Loop]);
		}
		RegThCnt = 0;
	}

	// Register thread information if the thread has not been registered into ThreadController.
	for (int LoopTmp = 0; LoopTmp < RegThCntTmp; LoopTmp++) {
		int FndIdx = -1;
		for (int Loop = 0; Loop < RegThCnt; Loop++) {
			if (RegThIdTmp[LoopTmp] == RegThId[Loop]) {
				FndIdx = Loop;
			}
		}
		if (FndIdx == -1 && RegThCnt < 100) {
			RegThId[RegThCnt] = RegThIdTmp[LoopTmp];
			RegThCnt++;
			AddStkThreadForGui(RegThIdTmp[LoopTmp], RegThNameTmp[LoopTmp], RegThDescTmp[LoopTmp], ElemStkThreadInit, ElemStkThreadFinal, ElemStkThreadMain, ElemStkThreadStart, ElemStkThreadStop);
		}
	}

	// Unregister theread information if the view element which are associating to the thread does not exist.
	for (int Loop = 0; Loop < RegThCnt; Loop++) {
		int FndIdx = -1;
		for (int LoopTmp = 0; LoopTmp < RegThCntTmp; LoopTmp++) {
			if (RegThIdTmp[LoopTmp] == RegThId[Loop]) {
				FndIdx = Loop;
			}
		}
		if (FndIdx == -1) {
			DeleteStkThreadForGui(RegThId[Loop]);
			RegThId[Loop] = RegThId[RegThCnt - 1];
			RegThCnt--;
			Loop--;
		}
	}

	return 0;
}

void SetWindowTitle(TCHAR FilePath[1024])
{
	TCHAR Buf[512];

	lstrcpy(Buf, _T("StkFw"));


	if (FilePath != NULL) {
		lstrcat(Buf, _T("  ["));
		if (lstrlen(FilePath) > 32) {
			lstrcat(Buf, _T("....."));
			lstrcat(Buf, FilePath + lstrlen(FilePath) - 32);
		} else {
			lstrcat(Buf, FilePath);
		}
		lstrcat(Buf, _T("]"));
	}
	SetWindowText(hWnd, Buf);
}

int AnalizeCommandParameter(TCHAR CmdParam[1024], TCHAR FileName[1024])
{
	lstrcpy(FileName, _T(""));

	// Operation == 0 : Nothing
	// Operation == 1 : open
	// Operation == 2 : start
	// Operation == 4 : stopall
	int Operation = 0;

	int Ptr = 0;
	while (CmdParam[Ptr]) {
		if (CmdParam[Ptr] == '/') {
			TCHAR ParamName[1024];
			wsprintf(ParamName, _T("%s"), &CmdParam[Ptr + 1]);
			if (StrCmpN(ParamName, _T("open"), 4) == 0) {
				Operation = 1;
				Ptr += 5;
				break;
			}
			if (StrCmpN(ParamName, _T("start"), 5) == 0) {
				Operation = 2;
				Ptr += 6;
				break;
			}
			if (StrCmpN(ParamName, _T("stopall"), 7) == 0) {
				Operation = 4;
				Ptr += 8;
				break;
			}
			MyMsgProc::StkErr(MyMsgProc::STKFW_COMPARAM_INVALID, NULL);
			ExitProcess(0);
		}
		if (CmdParam[Ptr] != ' ') {
			MyMsgProc::StkErr(MyMsgProc::STKFW_COMPARAM_INVALID, NULL);
			ExitProcess(0);
		}
		Ptr++;
	}

	switch (Operation) {
	case 0:
		break;
	case 1:
	case 2:
		// パラメータ文字列の直後にスペースが無ければエラー出力&プロセス停止
		if (CmdParam[Ptr] != ' ') {
			MyMsgProc::StkErr(MyMsgProc::STKFW_COMPARAM_NOFILE, CmdParam, NULL);
			ExitProcess(0);
		}
		while (CmdParam[Ptr] == ' ') {
			Ptr++;
		}
		for (int Loop = Ptr; Loop < 1024; Loop++) {
			if (CmdParam[Loop] == '\"') {
				wmemmove(&CmdParam[Loop], &CmdParam[Loop + 1], 1024 - Loop - 1);
				Loop--;
			}
		}
		lstrcpyn(FileName, &CmdParam[Ptr], 1024);
		break;
	case 4:
		// パラメータ文字列の直後にスペースまたは\0が無ければエラー出力&プロセス停止
		if (CmdParam[Ptr] != ' ' && CmdParam[Ptr] != 0) {
			MyMsgProc::StkErr(MyMsgProc::STKFW_COMPARAM_INVALID, CmdParam, NULL);
			ExitProcess(0);
		}
		// stkfwのプロセスを検索し，プロセスを停止する
		{
			DWORD ProcessIds[2048];
			DWORD Size;
			HANDLE ProcHndl;
			HMODULE	Module[1024];
			TCHAR Name[MAX_PATH];
			int ProcCnt;

			if (EnumProcesses(ProcessIds, sizeof(ProcessIds), &Size) == FALSE ) {
			}
			ProcCnt = Size / sizeof(DWORD);
			for (int i = 0; i < ProcCnt; i++) {
				if ((ProcHndl = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ | PROCESS_TERMINATE, FALSE, ProcessIds[i])) != NULL) {
					// 対象のプロセスが自分自身ならば次のプロセスに移る
					if (ProcessIds[i] == GetCurrentProcessId()) {
						CloseHandle(ProcHndl);
						continue;
					}
					// プロセスにマップしているファイルパスが自プロセスのものと一致する場合それを終了させる
					if (EnumProcessModules(ProcHndl, Module, sizeof(Module), &Size) != FALSE) {
						if (GetModuleFileNameEx(ProcHndl, Module[0], Name, MAX_PATH) > 0) {
							TCHAR ThisFile[MAX_PATH];
							GetModuleFileName(NULL, ThisFile, MAX_PATH);
							CharUpper(ThisFile);
							CharUpper(Name);
							if (lstrcmp(Name, ThisFile) == 0) {
								TerminateProcess(ProcHndl, 0);
							}
						}
					}
					CloseHandle(ProcHndl);
				}
			}
			ExitProcess(0);
		}
		break;
	default:
		break;
	}
	return Operation;
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// Define messages
	MyMsgProc::AddMsg();


	// コマンド・パラメータを解析する
	TCHAR CmdParam[1024];
	wsprintf(CmdParam, _T("%S"), lpCmdLine);
	int OpeType = AnalizeCommandParameter(CmdParam, CurrentStdFileName);


	// バックグラウンド実行
	if (OpeType == 2) {
		LockAllTable(2);
		if (LoadData(CurrentStdFileName) != 0) {
			UnlockAllTable();
			MyMsgProc::StkErr(MyMsgProc::STKFW_FILEINVALID, CurrentStdFileName, NULL);
			ExitProcess(0);
		}
		UnlockAllTable();

		// Change current folder
		TCHAR ConvFullPath[MAX_PATH];
		StkGeneric::GetInstance()->GetFullPathWithoutFileName(CurrentStdFileName, ConvFullPath);
		SetCurrentDirectory(ConvFullPath);

		DbMigration();
		GetViewFromDb();
		ResetThreadController(TRUE);
		SetProcBeforeFirstStkThreadStarts(StartProcForCmd);
		StartAllStkThreads();
		while (TRUE) {
			Sleep(60000);
		};
	}


	// EXEファイルが存在するパスを取得する
	GetModuleFileName(NULL, StartDir, MAX_PATH);
	for (int Loop = lstrlen(StartDir) - 1; Loop > 0; Loop--) {
		if (StartDir[Loop] == '\\') {
			StartDir[Loop] = 0;
			break;
		}
		StartDir[Loop] = 0;
	}

	// Initialize random generator
	srand((unsigned int)time(NULL));

	// ウィンドウ基本情報設定
	lstrcpy(szTitle, _T("StkFw"));
	lstrcpy(szWindowClass, _T("StkFw"));
	Inst = hInstance;
	MyRegisterClass(hInstance);
	if (!InitInstance(hInstance, nCmdShow)) {
		return FALSE;
	}

	// Configure GameStatusElement
	Gs.SetHWnd(hWnd);
	Gs.SetHInstance(hInstance);
	Gs.CreateReverseScreen(2500, 2500);

	NetGseEx *Gse = NULL;

	Gse = new NetGseEx();
	Gse->SetRefreshInterval(10);
	Gse->EnableScrollBar();
	Gse->SetCurrentWindowSize(512, 400);
	Gse->SetMinWindowSize(320, 240);
	Gse->SetMaxWindowSize(Gs.ChangeClientToWindowX(1024, TRUE), Gs.ChangeClientToWindowY(768, TRUE));
	Gse->SetActiveReverseScreen(0, 0, 1024, 768);
	Gs.AddGameStatusElement(0, (GameStatusElement*)Gse);

	InitializeCriticalSection(&NetGseEx::CritSect);

	Gs.StartRefreshScreen();

	As.SetActorActionInterval(10);
	As.SetGameStatus(&Gs);
	As.StartActorAction();

	LowDbAccess::GetInstance()->StkFwRepositoryCreateTable();
	ResetWorkspace(0);

	// /openパラメータが指定されていた場合，.stdファイルを読み込む
	if (lstrcmp(CurrentStdFileName, _T("")) != 0) {
		LockAllTable(2);
		if (LoadData(CurrentStdFileName) != 0) {
			UnlockAllTable();
			MyMsgProc::StkErr(MyMsgProc::STKFW_FILEINVALID, CurrentStdFileName, hWnd);
		} else {
			UnlockAllTable();

			// Change current folder
			TCHAR ConvFullPath[MAX_PATH];
			StkGeneric::GetInstance()->GetFullPathWithoutFileName(CurrentStdFileName, ConvFullPath);
			SetCurrentDirectory(ConvFullPath);

			DbMigration();
			ResetWorkspace(2);
			GetViewFromDb();
			Var_RefreshVariables();
			ResetThreadController(TRUE);
			SetWindowTitle(CurrentStdFileName);
		}
	} else {
		TCHAR WorkDir[MAX_PATH];

		SHGetFolderPath(NULL, CSIDL_PERSONAL, NULL, 0, WorkDir);
		SetCurrentDirectory(WorkDir);
	}

	AddStkThreadLog(_T("==========================================\r\n"));
	AddStkThreadLog(MyMsgProc::GetMsg(MyMsgProc::STKFW_LOG_TITLE));
	AddStkThreadLog(_T("==========================================\r\n"));

	LowDbAccess::GetInstance()->IsUpdated(1);
	IsActorStatusUpdated(1);

	MSG msg;
	while (GetMessage(&msg, hWnd, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize        = sizeof(WNDCLASSEX); 
	wcex.style         = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	wcex.lpfnWndProc   = (WNDPROC)WndProc;
	wcex.cbClsExtra    = 0;
	wcex.cbWndExtra    = 0;
	wcex.hInstance     = hInstance;
	wcex.hIcon         = LoadIcon(NULL, MAKEINTRESOURCE(IDI_APPLICATION));
	wcex.hIconSm       = LoadIcon(NULL, MAKEINTRESOURCE(IDI_APPLICATION));
	wcex.hCursor       = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName  = (LPCTSTR)IDR_MENU;
	wcex.lpszClassName = szWindowClass;

	return RegisterClassEx(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPED | WS_MAXIMIZEBOX | WS_MINIMIZEBOX | WS_SYSMENU | WS_SIZEBOX,
		CW_USEDEFAULT, 0, 512, 256, NULL, NULL, hInstance, NULL);

	if(!hWnd) {
		return FALSE;
	}

	// Sets icon information for the window
	HICON IconHndlrS = (HICON)LoadImage(hInstance, (LPCTSTR)IDI_ICON0, IMAGE_ICON, 16, 16, LR_DEFAULTCOLOR);
	HICON IconHndlrB = (HICON)LoadImage(hInstance, (LPCTSTR)IDI_ICON0, IMAGE_ICON, 32, 32, LR_DEFAULTCOLOR);
	if (IconHndlrS != NULL && IconHndlrB != NULL) {
		SendMessage(hWnd, WM_SETICON, ICON_SMALL, (LPARAM)IconHndlrS);
		SendMessage(hWnd, WM_SETICON, ICON_BIG, (LPARAM)IconHndlrB);
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

DWORD WINAPI NthShowStkThreadController(LPVOID Param)
{
	SetProcBeforeFirstStkThreadStarts(StartProc);
	SetProcAfterLastStkThreadStops(StopProc);
	ShowStkThreadController(NULL, IDI_ICON0, _T("Thread controller"));
	return 0;
}

DWORD WINAPI NthShowStkDataWindow(LPVOID Param)
{
	//DisableFileAccessFlag();
	//ShowStkDataWindow(_T("Repository"), NULL);
	return 0;
}

DWORD WINAPI NthShowVariableController(LPVOID Param)
{
	Var_DisplayMainWindow();
	return 0;
}

// Return < 0 : Threads are running or property dialog is opened.
// Return == 0 : User can not perform mouse operation on the main console.
int GetMouseAction()
{
	return MouseActionStatus;
}

// Flag == -1 : Set the type as mouse-action = disable
// Flag == 1  : Set the type as mouse-action = enable
// Flag == 0  : Enable / disable mouse action along with the type.
void SetMouseAction(int Flag)
{
	static int PrevFlag = 0;

	if (Flag == PrevFlag) {
		return;
	}
	PrevFlag = Flag;
	if (Flag == 1 || Flag == -1) {
		MouseActionStatus += Flag;
		return;
	}
	int Cnt = As.GetActorStatusElementCount();
	for (int Loop = 0; Loop < Cnt; Loop++) {
		ActorStatusElement* Ase = As.GetActorStatusElement(Loop);
		if (MouseActionStatus >= 0) {
			Ase->EnableMouseAction();
		} else {
			Ase->DisableMouseAction();
		}
	}
}

void StartProc(void)
{
	AddStkThreadLog(MyMsgProc::GetMsg(MyMsgProc::STKFW_LOG_START));

	StkSocket_ClearLog();

	// スレッド実行前にElementInfoが更新されているかチェック
	IsUdtElemInfo = LowDbAccess::GetInstance()->IsUpdated(2);

	EnterCriticalSection(&NetGseEx::CritSect);

	SetMouseAction(-1);
	SetViewToDb();

	Gs.StopRefreshScreen();
	As.StopActorAction();
	int RefreshInterval = 1000;
	RefreshInterval = LowDbAccess::GetInstance()->GetPropertyInteger(_T("RefreshInterval"), 1);
	GameStatusElement* Gse = Gs.GetGameStatusElement(0);
	Gse->SetRefreshInterval(RefreshInterval);
	As.SetActorActionInterval(RefreshInterval);
	Gs.StartRefreshScreen();
	As.StartActorAction();

	AddAllSocketInfo();

	LeaveCriticalSection(&NetGseEx::CritSect);
}

void StopProc(void)
{
	EnterCriticalSection(&NetGseEx::CritSect);

	DeleteAllSocketInfo();

	Var_RefreshVariables();
	ResetThreadController(FALSE);

	////////////////////////////////////////
	// この関数呼び出しの位置をVar_RefreshVariables()よりも前に置くとデバッグ実行で"出力"コンソールにエラーが
	// 出力されることがある。原因不明だが，ココの位置に置くとエラーは出力されなくなる。
	ResetWorkspace(3);//
	GetViewFromDb();//
	////////////////////////////////////////

	Gs.StopRefreshScreen();
	As.StopActorAction();
	GameStatusElement* Gse = Gs.GetGameStatusElement(0);
	Gse->SetRefreshInterval(10);
	As.SetActorActionInterval(10);
	Gs.StartRefreshScreen();
	As.StartActorAction();

	SetMouseAction(1);

	LeaveCriticalSection(&NetGseEx::CritSect);

	// スレッド実行前にElementInfoが更新されていなければリセット
	if (!IsUdtElemInfo) {
		LowDbAccess::GetInstance()->IsUpdated(3);
	}

	AddStkThreadLog(MyMsgProc::GetMsg(MyMsgProc::STKFW_LOG_STOP));
}

void StartProcForCmd(void)
{
	AddStkThreadLog(MyMsgProc::GetMsg(MyMsgProc::STKFW_LOG_START));
	AddAllSocketInfo();
}

void StopProcForCmd(void)
{
	DeleteAllSocketInfo();
	AddStkThreadLog(MyMsgProc::GetMsg(MyMsgProc::STKFW_LOG_STOP));
}

int SetAboutInfo()
{
	SetStkAboutIconAbout(IDI_ICON0);
	SetStkAboutIconBug(IDI_ABOUTBUG);
	SetStkAboutIconEnhance(IDI_ABOUTENH);
	TCHAR Title[512];
	wsprintf(Title, _T("StkFw\r\nVersion 1.5.0  ,  Build date:[%S, %S]\r\nCopyright (C) 2015  Shinya Takeuchi.  All Rights Reserved."), __DATE__, __TIME__);
	SetAboutTitle(Title);

	ClearHistoryItem();
	AddHistoryItem(1, _T("0000"), _T("1.0.0"), MyMsgProc::GetMsg(MyMsgProc::SFW_100_1));
	AddHistoryItem(0, _T("0015"), _T("1.1.0"), MyMsgProc::GetMsg(MyMsgProc::SFW_100_110_1));
	AddHistoryItem(0, _T("0017"), _T("1.1.0"), MyMsgProc::GetMsg(MyMsgProc::SFW_100_110_2));
	AddHistoryItem(1, _T("0018"), _T("1.1.0"), MyMsgProc::GetMsg(MyMsgProc::SFW_100_110_3));
	AddHistoryItem(1, _T("0034"), _T("1.1.0"), MyMsgProc::GetMsg(MyMsgProc::SFW_100_110_4));
	AddHistoryItem(0, _T("0040"), _T("1.1.0"), MyMsgProc::GetMsg(MyMsgProc::SFW_100_110_5));
	AddHistoryItem(1, _T("0052"), _T("1.1.0"), MyMsgProc::GetMsg(MyMsgProc::SFW_100_110_6));
	AddHistoryItem(1, _T("0074"), _T("1.2.0"), MyMsgProc::GetMsg(MyMsgProc::SFW_110_120_1));
	AddHistoryItem(1, _T("0075"), _T("1.2.0"), MyMsgProc::GetMsg(MyMsgProc::SFW_110_120_2));
	AddHistoryItem(1, _T("0078"), _T("1.2.0"), MyMsgProc::GetMsg(MyMsgProc::SFW_110_120_3));
	AddHistoryItem(1, _T("0079"), _T("1.2.0"), MyMsgProc::GetMsg(MyMsgProc::SFW_110_120_4));
	AddHistoryItem(1, _T("0080"), _T("1.2.0"), MyMsgProc::GetMsg(MyMsgProc::SFW_110_120_5));
	AddHistoryItem(1, _T("0081"), _T("1.2.0"), MyMsgProc::GetMsg(MyMsgProc::SFW_110_120_6));
	AddHistoryItem(0, _T("0083"), _T("1.2.0"), MyMsgProc::GetMsg(MyMsgProc::SFW_110_120_7));
	AddHistoryItem(0, _T("0084"), _T("1.2.0"), MyMsgProc::GetMsg(MyMsgProc::SFW_110_120_8));
	AddHistoryItem(1, _T("1003"), _T("1.3.0"), MyMsgProc::GetMsg(MyMsgProc::SFW_120_130_2));
	AddHistoryItem(1, _T("1004"), _T("1.3.0"), MyMsgProc::GetMsg(MyMsgProc::SFW_120_130_1));
	AddHistoryItem(1, _T("1008"), _T("1.3.0"), MyMsgProc::GetMsg(MyMsgProc::SFW_120_130_3));
	AddHistoryItem(1, _T("1010"), _T("1.3.0"), MyMsgProc::GetMsg(MyMsgProc::SFW_120_130_4));
	AddHistoryItem(1, _T("1051"), _T("1.4.0"), MyMsgProc::GetMsg(MyMsgProc::SFW_130_140_1));
	AddHistoryItem(1, _T("1055"), _T("1.4.0"), MyMsgProc::GetMsg(MyMsgProc::SFW_130_140_2));
	AddHistoryItem(0, _T("1062"), _T("1.4.0"), MyMsgProc::GetMsg(MyMsgProc::SFW_130_140_5));
	AddHistoryItem(1, _T("1063"), _T("1.4.0"), MyMsgProc::GetMsg(MyMsgProc::SFW_130_140_4));
	AddHistoryItem(1, _T("1068"), _T("1.4.0"), MyMsgProc::GetMsg(MyMsgProc::SFW_130_140_3));
	AddHistoryItem(1, _T("1073"), _T("1.4.0"), MyMsgProc::GetMsg(MyMsgProc::SFW_130_140_6));
	AddHistoryItem(1, _T("2003"), _T("1.5.0"), MyMsgProc::GetMsg(MyMsgProc::SFW_140_150_1));
	AddHistoryItem(1, _T("2008"), _T("1.5.0"), MyMsgProc::GetMsg(MyMsgProc::SFW_140_150_2));

	return 0;
}

int SetViewToDb()
{
	LowDbAccess::GetInstance()->DeleteAllRecords(_T("ViewElement"));

	for (int Loop = 0; Loop < As.GetActorStatusElementCount(); Loop++) {
		ActorStatusElement* Ase = As.GetActorStatusElement(Loop);
		int AseId = Ase->GetId();
		if (AseId == 0) {
			continue;
		}
		NetAseEx* Nase = reinterpret_cast<NetAseEx*>(Ase);
		int LoopInfo[20];
		for (int LoopLnk = 0; LoopLnk < 10; LoopLnk++) {
			if (Nase->LinkTo[LoopLnk] != -1) {
				ActorStatusElement* AseLink = As.GetActorStatusElement(Nase->LinkTo[LoopLnk]);
				LoopInfo[LoopLnk * 2] = AseLink->GetId();
			} else {
				LoopInfo[LoopLnk * 2] = -1;
			}
			LoopInfo[LoopLnk * 2 + 1] = Nase->LinkType[LoopLnk];
		}
		LowDbAccess::GetInstance()->InsertViewElement(
			AseId,
			Nase->GetName(),
			Nase->GetType(),
			Nase->GetIconId(),
			Nase->GetActorPosX(),
			Nase->GetActorPosY(),
			LoopInfo
		);
	}
	return 0;
}

int GetViewFromDb()
{
	NetAseEx* NetAse[ActorStatus::ACTOR_STATUS_COUNT];
	int TmpId[1000];
	TCHAR TmpName[1000][32];
	int TmpType[1000];
	int TmpIcon[1000];
	int TmpPosX[1000];
	int TmpPosY[1000];
	int TmpLnkId[1000][10];
	int TmpLnkTp[1000][10];
	int MaxRec = LowDbAccess::GetInstance()->GetAllViewElementRecords(TmpId, TmpName, TmpType, TmpIcon, TmpPosX, TmpPosY, TmpLnkId, TmpLnkTp);

	int NetAseCnt = 0;
	for (; NetAseCnt < MaxRec; NetAseCnt++) {
		NetAse[NetAseCnt] = new NetAseEx();
		NetAse[NetAseCnt]->SetName(TmpName[NetAseCnt]);
		NetAse[NetAseCnt]->EnableAction();
		if (GetMouseAction() >= 0) {
			NetAse[NetAseCnt]->EnableMouseAction();
		} else {
			NetAse[NetAseCnt]->DisableMouseAction();
		}
		NetAse[NetAseCnt]->SetId(TmpId[NetAseCnt]);
		NetAse[NetAseCnt]->SetActorPos(TmpPosX[NetAseCnt], TmpPosY[NetAseCnt]);
		NetAse[NetAseCnt]->SetType(TmpType[NetAseCnt]);
		NetAse[NetAseCnt]->SetIconId(TmpIcon[NetAseCnt]);
		if (TmpIcon[NetAseCnt] >= 50 && TmpIcon[NetAseCnt] < 70) {
			NetAse[NetAseCnt]->SetActorRect(8, -8, 8, -8);
		} else {
			NetAse[NetAseCnt]->SetActorRect(16, -16, 16, -16);
		}
		int LinkCnt = 0;
		for (int Loop = 0; Loop < 10; Loop++) {
			int LinkId = TmpLnkId[NetAseCnt][Loop];
			if (LinkId != -1) {
				NetAse[NetAseCnt]->LinkTo[LinkCnt] = LinkId;
				NetAse[NetAseCnt]->LinkType[LinkCnt] = TmpLnkTp[NetAseCnt][Loop];
				LinkCnt++;
			}
		}
		NetAse[NetAseCnt]->LinkCount = LinkCnt;
	}

	// Change link target-ID to target-index.
	for (int Loop = 0; Loop < NetAseCnt; Loop++) {
		for (int LoopLnk = 0; LoopLnk < 10; LoopLnk++) {
			int TargetId = NetAse[Loop]->LinkTo[LoopLnk];
			int LoopE;
			for (LoopE = 0; LoopE < NetAseCnt; LoopE++) {
				if (NetAse[LoopE]->GetId() == TargetId) {
					break;
				}
			}
			if (LoopE != NetAseCnt) {
				NetAse[Loop]->LinkTo[LoopLnk] = LoopE + 1;
			} else if (TargetId == -1) {
				NetAse[Loop]->LinkTo[LoopLnk] = -1;
			} else {
				int LinkCnt = NetAse[Loop]->LinkCount;
				NetAse[Loop]->LinkTo[LoopLnk] = NetAse[Loop]->LinkTo[LinkCnt - 1];
				NetAse[Loop]->LinkType[LoopLnk] = NetAse[Loop]->LinkType[LinkCnt - 1];
				NetAse[Loop]->LinkTo[LinkCnt - 1] = -1;
				NetAse[Loop]->LinkType[LinkCnt - 1] = -1;
				NetAse[Loop]->LinkCount--;
				LoopLnk--;
			}
		}
	}
	for (int Loop = 0; Loop < NetAseCnt; Loop++) {
		As.AddActorStatusElement((ActorStatusElement*)NetAse[Loop]);
	}

	return 0;
}

INT_PTR CALLBACK NewWorkSpaceDialog(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
		{
			int Width, Height, GridType;
			// Load size of workspace from "Property" table
			LowDbAccess* LowDbAc = LowDbAccess::GetInstance();
			LowDbAc->GetWorkspaceInfo(&Width, &Height, &GridType);
			TCHAR WidthStr[32];
			TCHAR HeightStr[32];
			wsprintf(WidthStr, _T("%d"), Width);
			wsprintf(HeightStr, _T("%d"), Height);

			SetDlgItemText(hDlg, IDC_EDIT1, WidthStr);
			SetDlgItemText(hDlg, IDC_EDIT2, HeightStr);
			SendDlgItemMessage(hDlg, IDC_EDIT1, EM_LIMITTEXT, 4, 0);
			SendDlgItemMessage(hDlg, IDC_EDIT2, EM_LIMITTEXT, 4, 0);
		}
		break;
	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK) {
			TCHAR BufE1[10];
			TCHAR BufE2[10];
			GetDlgItemText(hDlg, IDC_EDIT1, BufE1, 10);
			GetDlgItemText(hDlg, IDC_EDIT2, BufE2, 10);
			NewWidth = StrToInt(BufE1);
			NewHeight = StrToInt(BufE2);
			EndDialog(hDlg, (INT_PTR)0);
			return (INT_PTR)TRUE;
		}
		if (LOWORD(wParam) == IDCANCEL) {
			EndDialog(hDlg, (INT_PTR)0);
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

// Mode == 0 : First call
// Mode == 1 : New
// Mode == 2 : Open
// Mode == 3 : Refresh
// Mode == 4 : Workspace change
int ResetWorkspace(int Mode)
{
	int Width, Height, GridType;
	NewWidth = NewHeight = -1;
	GridType = 8;

	if (Mode == 1 || Mode == 4) {
		DialogBox(Inst, MAKEINTRESOURCE(IDD_NEW_WS), hWnd, NewWorkSpaceDialog);
	}
	if ((Mode == 1 || Mode == 4) && NewWidth == -1 && NewHeight == -1) {
		return -1;
	} else if ((Mode == 1 || Mode == 4) && NewWidth >= 512 && NewWidth <= 2048 && NewHeight >= 400 && NewHeight <= 2048) {
		Width = NewWidth;
		Height = NewHeight;
	} else if (Mode == 1 || Mode == 4) {
		MyMsgProc::StkErr(MyMsgProc::STKFW_OUTOFRANGE, hWnd);
		return -1;
	}

	// Clear all of ActorStatusElement
	As.ClearActorStatusElement();

	if (Mode == 0 || Mode == 1) {
		LowDbAccess::GetInstance()->StkFwRepositoryInitialize(DB_VERSION);
	}

	if (Mode != 1 && Mode != 4) {
		// Load size of workspace from "Property" table
		LowDbAccess* LowDbAc = LowDbAccess::GetInstance();
		LowDbAc->GetWorkspaceInfo(&Width, &Height, &GridType);
	}
	if (Mode == 4) {
		// Load size of workspace from "Property" table
		int DummyWidth, DummyHeight;
		LowDbAccess* LowDbAc = LowDbAccess::GetInstance();
		LowDbAc->GetWorkspaceInfo(&DummyWidth, &DummyHeight, &GridType);
	}
	if (Mode == 1 || Mode == 4) {
		LowDbAccess* LowDbAc = LowDbAccess::GetInstance();
		LowDbAc->ChangeWorkspace(Width, Height, GridType);
	}

	if (Mode != 3) {
		// Change window size
		GameStatusElement* Gse = Gs.GetGameStatusElement(0);
		if (Width <= 800 && Height <= 600) {
			Gse->SetCurrentWindowSize(Gs.ChangeClientToWindowX(Width, FALSE), Gs.ChangeClientToWindowY(Height, FALSE));
		} else {
			Gse->SetCurrentWindowSize(Gs.ChangeClientToWindowX(800, FALSE), Gs.ChangeClientToWindowY(600, FALSE));
		}
		Gse->SetMinWindowSize(320, 240);
		Gse->SetMaxWindowSize(Gs.ChangeClientToWindowX(Width, TRUE), Gs.ChangeClientToWindowY(Height, TRUE));
		Gse->SetActiveReverseScreen(0, 0, Width, Height);
		Gs.SetDrawScreenExFlag();
		ShowWindow(hWnd, SW_SHOWNORMAL);
	}

	// Add NetManagerAseEx
	NetManagerAseEx *NetMgr = new NetManagerAseEx();
	NetManagerAseEx::GridType = GridType;
	NetMgr->SetId(0);
	NetMgr->EnableAction();
	if (GetMouseAction() >= 0) {
		NetMgr->EnableMouseAction();
	} else {
		NetMgr->DisableMouseAction();
	}
	NetMgr->SetActorPos(Width / 2, Height / 2);
	NetMgr->SetActorRect(Height / 2, -1 * Height / 2, Width / 2, -1 * Width / 2);
	As.AddActorStatusElement((ActorStatusElement*)NetMgr);

	if (Mode == 0 || Mode == 1) {
		// Reset window title
		SetWindowTitle(NULL);
	}

	return 0;
}

void CheckExecutorLocalGroup(void)
{
	TCHAR ErrorMessage[1024] = _T("");
	TCHAR Buf[64];
	DWORD BufSize = 64;

	lstrcpy(ErrorMessage, MyMsgProc::GetMsg(MyMsgProc::NEEDADMINRIGHTS));
	lstrcat(ErrorMessage, _T("User name = "));
	GetUserName(Buf, &BufSize);
	lstrcat(ErrorMessage, Buf);
	lstrcat(ErrorMessage, _T("\r\n"));

	lstrcat(ErrorMessage, _T("Local group :\r\n"));
    DWORD EntriesRead = 0;
    DWORD TotalEntries = 0;
	LPLOCALGROUP_USERS_INFO_0 GrpBuf = NULL;
	BOOL FoundFlag = FALSE;
	NetUserGetLocalGroups(NULL, Buf, 0, LG_INCLUDE_INDIRECT, (LPBYTE*)&GrpBuf, MAX_PREFERRED_LENGTH, &EntriesRead, &TotalEntries);
	for (int Loop = 0; Loop < (int)EntriesRead; Loop++) {
		if (lstrcmp(GrpBuf->lgrui0_name, _T("Administrators")) == 0) {
			FoundFlag = TRUE;
			break;
		}
		lstrcat(ErrorMessage, _T("    "));
		lstrcat(ErrorMessage, GrpBuf->lgrui0_name);
		lstrcat(ErrorMessage, _T("\r\n"));
		GrpBuf++;
	}
	NetApiBufferFree(GrpBuf);
	if (FoundFlag == FALSE) {
		MessageBox(hWnd, ErrorMessage, _T("Error"), MB_OK | MB_ICONERROR);
		ExitProcess(0);
	}
}

void ShowRunTimeInformation(void)
{
	TCHAR RunTimeInfo[2048] = _T("");
	TCHAR Buf[MAX_PATH + 64];
	wsprintf(Buf, _T("Refresh interval = %d ms \r\n"), NetGseEx::RtiRefreshInterval);
	lstrcat(RunTimeInfo, Buf);
	wsprintf(Buf, _T("Number of elements = %d \r\n"), NetGseEx::RtiElementCount);
	lstrcat(RunTimeInfo, Buf);
	wsprintf(Buf, _T("Number of requests = %d \r\n"), NetGseEx::RtiRequestCount);
	lstrcat(RunTimeInfo, Buf);
	wsprintf(Buf, _T("Number of running elements = %d\r\n"), NetGseEx::RtiRunningCount);
	lstrcat(RunTimeInfo, Buf);
	
	TCHAR InitPath[MAX_PATH];
	GetCurrentDirectory(sizeof(InitPath), InitPath);
	wsprintf(Buf, _T("Current folder : \"%s\"\r\n"), InitPath);
	lstrcat(RunTimeInfo, Buf);
	wsprintf(Buf, _T("EXE folder : \"%s\"\r\n"), StartDir);
	lstrcat(RunTimeInfo, Buf);

	MessageBox(hWnd, RunTimeInfo, _T("RunTime Information"), MB_OK | MB_ICONINFORMATION);
}

// Display open file dialog and acquire the file name which is specified on the dialog.
// [in] WinHndl : Window handler
// [in] FileName : Acquired file name
// [in] SaveFlag : Operation flag (FALSE: Open, TRUE: Save)
// [out] int : Result code
int GetOpenSaveFileName(HWND WinHndl, TCHAR* FileName, BOOL SaveFlag)
{
	TCHAR InitPath[MAX_PATH];
	GetCurrentDirectory(sizeof(InitPath), InitPath);

	TCHAR File[32768];
	File[0] = 0;
	TCHAR Title[256] = _T("");
	OPENFILENAME Ofn;
	ZeroMemory(&Ofn, sizeof(OPENFILENAME));
	Ofn.lStructSize = sizeof(OPENFILENAME);
	Ofn.hwndOwner = WinHndl;
	Ofn.lpstrFile = File;
	Ofn.nMaxFile = 300;
	Ofn.lpstrFileTitle = Title;
	Ofn.nMaxFileTitle = 300;
	if (SaveFlag == TRUE) {
		Ofn.lpstrDefExt = _T("std");
	}
	Ofn.lpstrInitialDir = InitPath;
	Ofn.lpstrFilter = _T("Data file(*.std)\0*.std\0\0");
	if (SaveFlag == TRUE) {
		Ofn.lpstrTitle = _T("Select data file [Save As]");
	} else {
		Ofn.lpstrTitle = _T("Select data file [Open]");
		Ofn.Flags = OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
	}
	int Ret;
	if (SaveFlag == TRUE) {
		Ret = ::GetSaveFileName(&Ofn);
	} else {
		Ret = ::GetOpenFileName(&Ofn);
	}
	if (Ret != 0) {
		lstrcpy(FileName, Ofn.lpstrFile);
	} else {
		lstrcpy(FileName, _T(""));
	}
	return Ret;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	static const int HOT_KEY_DATABASE = 0x3001;
	static const int HOT_KEY_DB2VIEW  = 0x3002;
	static const int HOT_KEY_VIEW2DB  = 0x3003;
	static const int HOT_KEY_RUNTIME  = 0x3009;
	static const int HOT_KEY_DBINIT   = 0x3000;

	Gs.MessageDispatcher(hWnd, message, wParam, lParam);
	As.MessageDispatcher(hWnd, message, wParam, lParam);

	switch (message) {
	case WM_CREATE:
		RegisterHotKey(hWnd, HOT_KEY_DATABASE, MOD_CONTROL | MOD_SHIFT, '1');
		RegisterHotKey(hWnd, HOT_KEY_DB2VIEW, MOD_CONTROL | MOD_SHIFT, '2');
		RegisterHotKey(hWnd, HOT_KEY_VIEW2DB, MOD_CONTROL | MOD_SHIFT, '3');
		RegisterHotKey(hWnd, HOT_KEY_RUNTIME, MOD_CONTROL | MOD_SHIFT, '9');
		RegisterHotKey(hWnd, HOT_KEY_DBINIT, MOD_CONTROL | MOD_SHIFT, '0');
		break;
	case WM_HOTKEY:
		if (GetForegroundWindow() != hWnd) {
			break;
		}
		switch (wParam) {
		case HOT_KEY_DATABASE:
			CreateThread(NULL, 0, NthShowStkDataWindow, NULL, 0, NULL);
			break;
		case HOT_KEY_DB2VIEW:
			if (GetMouseAction() < 0) {
				MyMsgProc::StkErr(MyMsgProc::STKFW_RUNNINGORPROPOPEN, hWnd);
				break;
			}
			ResetWorkspace(3);
			GetViewFromDb();
			Var_RefreshVariables();
			ResetThreadController(TRUE);
			break;
		case HOT_KEY_VIEW2DB:
			if (GetMouseAction() < 0) {
				MyMsgProc::StkErr(MyMsgProc::STKFW_RUNNINGORPROPOPEN, hWnd);
				break;
			}
			SetViewToDb();
			break;
		case HOT_KEY_RUNTIME:
			ShowRunTimeInformation();
			break;
		case HOT_KEY_DBINIT:
			LowDbAccess::GetInstance()->StkFwRepositoryInitialize(DB_VERSION);
			break;
		}
		break;

	case WM_COMMAND:
		wmId    = LOWORD(wParam); 
		wmEvent = HIWORD(wParam); 
		switch (wmId) 
		{
		case IDM_FILE_NEW:
			if (GetMouseAction() < 0) {
				MyMsgProc::StkErr(MyMsgProc::STKFW_RUNNINGORPROPOPEN, hWnd);
				break;
			}
			if (LowDbAccess::GetInstance()->IsUpdated(0) || IsActorStatusUpdated(0)) {
				if (MyMsgProc::StkYesNo(MyMsgProc::DATAUPDATED, hWnd) == IDNO) {
					break;
				}
			}
			if (ResetWorkspace(1) == 0) {
				lstrcpy(CurrentStdFileName, _T(""));
				LowDbAccess::GetInstance()->IsUpdated(1);
				IsActorStatusUpdated(1);
			}
			Var_RefreshVariables();
			ResetThreadController(TRUE);
			break;
		case IDM_FILE_OPEN:
			if (GetMouseAction() < 0) {
				MyMsgProc::StkErr(MyMsgProc::STKFW_RUNNINGORPROPOPEN, hWnd);
				break;
			}
			if (LowDbAccess::GetInstance()->IsUpdated(0) || IsActorStatusUpdated(0)) {
				if (MyMsgProc::StkYesNo(MyMsgProc::DATAUPDATED, hWnd) == IDNO) {
					break;
				}
			}
			{
				TCHAR Buf[1024];
				int Ret = GetOpenSaveFileName(hWnd, Buf, FALSE);
				if (Ret == 0 || Buf[0] == NULL) {
					break;
				}
				lstrcpy(CurrentStdFileName, Buf);
				LockAllTable(2);
				if (LoadData(Buf) != 0) {
					UnlockAllTable();
					MyMsgProc::StkErr(MyMsgProc::STKFW_FILEINVALID, Buf, hWnd);
					break;
				}
				UnlockAllTable();
				DbMigration();
				ResetWorkspace(2);
				GetViewFromDb();
				Var_RefreshVariables();
				ResetThreadController(TRUE);
				SetWindowTitle(CurrentStdFileName);
				LowDbAccess::GetInstance()->IsUpdated(1);
				IsActorStatusUpdated(1);
			}
			break;
		case IDM_FILE_SAVE:
			if (GetMouseAction() < 0) {
				MyMsgProc::StkErr(MyMsgProc::STKFW_RUNNINGORPROPOPEN, hWnd);
				break;
			}
			if (lstrcmp(CurrentStdFileName, _T("")) != 0) {
				SetViewToDb();
				LockAllTable(1);
				if (SaveData(CurrentStdFileName) != 0) {
					UnlockAllTable();
					MyMsgProc::StkErr(MyMsgProc::STKFW_DATASAVEFAILED, hWnd);
					break;
				}
				UnlockAllTable();
				LowDbAccess::GetInstance()->IsUpdated(1);
				IsActorStatusUpdated(1);
				break;
			}
			// break is not necessary.
		case IDM_FILE_SAVEAS:
			if (GetMouseAction() < 0) {
				MyMsgProc::StkErr(MyMsgProc::STKFW_RUNNINGORPROPOPEN, hWnd);
				break;
			}
			{
				TCHAR Buf[1024];
				int Ret = GetOpenSaveFileName(hWnd, Buf, TRUE);
				if (Ret == 0 || Buf[0] == NULL) {
					break;
				}
				lstrcpy(CurrentStdFileName, Buf);
				SetViewToDb();
				LockAllTable(1);
				if (SaveData(Buf) != 0) {
					UnlockAllTable();
					MyMsgProc::StkErr(MyMsgProc::STKFW_DATASAVEFAILED, hWnd);
					break;
				}
				UnlockAllTable();
				SetWindowTitle(CurrentStdFileName);
				LowDbAccess::GetInstance()->IsUpdated(1);
				IsActorStatusUpdated(1);
			}
			break;
		case IDM_RUN_THREADCONTROLLER:
			CreateThread(NULL, 0, NthShowStkThreadController, NULL, 0, NULL);
			break;
		case IDM_RUN_STARTALLTHREADS:
			SetProcBeforeFirstStkThreadStarts(StartProc);
			StartAllStkThreads();
			break;
		case IDM_RUN_STOPALLTHREADS:
			SetProcAfterLastStkThreadStops(StopProc);
			StopAllStkThreads();
			break;
		case IDM_MAINTENANCE_IPADDRWIZARD:
			//ShowStkIpDlg(hWnd);
			break;
		case IDM_MAINTENANCE_LBADPT:
			//ShowLbadptDialog(hWnd);
			break;
		case IDM_CONFIG_COMM:
			Var_SetVariableType(0);
			CreateThread(NULL, 0, NthShowVariableController, NULL, 0, NULL);
			break;
		case IDM_CONFIG_FLAG:
			Var_SetVariableType(1);
			CreateThread(NULL, 0, NthShowVariableController, NULL, 0, NULL);
			break;
		case IDM_ABOUT_ABOUT:
			SetAboutInfo();
			ShowAboutDialog(hWnd);
			break;
		case IDM_ABOUT_MANUAL:
			{
				TCHAR HelpPath[MAX_PATH];
				lstrcpy(HelpPath, StartDir);
				lstrcat(HelpPath, MyMsgProc::GetMsg(MyMsgProc::STKFW_MANUAL_PLACE));
				ShellExecute(hWnd, _T("open"), HelpPath, NULL, NULL, SW_SHOWNOACTIVATE);
			}
			break;
		case IDM_FILE_EXIT:
			if (LowDbAccess::GetInstance()->IsUpdated(0) || IsActorStatusUpdated(0)) {
				if (MyMsgProc::StkYesNo(MyMsgProc::DATAUPDATED, hWnd) == IDNO) {
					break;
				}
			}
			DestroyWindow(hWnd);
			break;
		default:
		    return DefWindowProc( hWnd, message, wParam, lParam );
		}
		break;

	case WM_CLOSE:
		if (LowDbAccess::GetInstance()->IsUpdated(0) || IsActorStatusUpdated(0)) {
			if (MyMsgProc::StkYesNo(MyMsgProc::DATAUPDATED, hWnd) == IDNO) {
				break;
			}
		}
		DestroyWindow(hWnd);
		break;

	case WM_DESTROY:
		UnregisterHotKey(hWnd, HOT_KEY_DATABASE);
		UnregisterHotKey(hWnd, HOT_KEY_DB2VIEW);
		UnregisterHotKey(hWnd, HOT_KEY_VIEW2DB);
		UnregisterHotKey(hWnd, HOT_KEY_RUNTIME);
		PostQuitMessage(0);
		ExitProcess(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
