#pragma once
#include <windows.h>
#include "server\ExecElem.h"

class ExecElemMgr
{
private:
	// This instance
	static ExecElemMgr* ThisInstance;

	// 各実行系要素，データ系要素の実行実体
	ExecElem* ExecElems[1000];
	int NumOfExecElem;

	// クリティカルセクション
	static CRITICAL_SECTION CritSect;
	static CRITICAL_SECTION CritSectExe; //#10084

private:
	// Constructor
	ExecElemMgr();
	// Destructor
	~ExecElemMgr();

	// 指定したIDの要素とリンクしている全ての要素(ExecElem)取得する
	void GetLinkedElementIds(int, int, int, int);

	// 実行依存Idの設定
	void SetWaitForThreadEnd(int);

	// 次の処理のステータスをNotInScopeからWaitingに変更する
	void ChangeNotInScopeToWaiting(int, int);

	// リンクの種別を変更する
	void ChangeLineType(int, int, int);

public:
	// Get this instance
	static ExecElemMgr* GetInstance();

	// 指定したIDのExecElemをExecElems配列から取得する
	ExecElem* GetExecElem(int);
	// ExecElems配列のX番目にあるExecElemを取得する
	ExecElem* GetExecElemByIndex(int);
	// ExecElems配列に存在するExecElemインスタンスの数を取得する
	int GetExecElemCount();

	// 全ての実行系要素，データ系要素をExecElemに展開
	void AddExecElem(int);
	// 全てのExecElemを削除する
	void DeleteExecElem(int);

	// 各要素の処理を実行する
	void ExecuteElement(int);

	// Thread status was changed into "Start"
	void ThreadStatusChangedIntoStart(int);

	// Thread status was changed into "Stop"
	void ThreadStatusChangedIntoStop(int);

	// リンクの種別をクリアする
	void ClearLineType(int );

};
