#pragma once
#include <windows.h>

class ExecElem
{
protected:
	// エレメントID
	int ElementId;

	// 根となる要素のID
	int RootId;

	// 要素の種別
	int ElementType;

	// エレメントの状態
	int Status;

	// 実行依存Id
	int WaitForExecId;

	// 処理するデータ
	void* Data;
	int DataLength;

	// Thread start/stop flag
	BOOL StartStopFlag;

public:
	static const int STATUS_DONE = 1; // 既に実行済の状態
	static const int STATUS_TRIED = 2; // 実行したが次の処理に移れず
	static const int STATUS_WAITING = 3; // 処理待ち
	static const int STATUS_NOTINSCOPE = 4; // 対象外
	static const int STATUS_CLEAR = 5; // 現在のスレッドをクリアする（終端処理が完了した状態）
	static const int STATUS_DWAITING = 6; // 次のスレッドに処理が引き継がれた直後の状態
	static const int STATUS_BWAITING = 7; // 実行結果がブロック状態(Ret==2)の場合

	static const int RECEIVER    = 1;
	static const int SENDER_R    = 4;
	static const int STOREDATA_R = 5;
	static const int SENDER      = 7;
	static const int STOREDATA   = 8;
	static const int CHECKFLAG   = 10;
	static const int CHECKDATA   = 11;
	static const int CHANGEFLAG  = 13;
	static const int CHANGEDATA  = 14;
	static const int RECEIVERUDP = 21;
	static const int SENDERUDP_R = 22;
	static const int SENDERUDP   = 23;

public:
	// Attributes for the "Execute Program"
	PROCESS_INFORMATION ExeProcInfo;
	HANDLE StdInD, StdOutD;

private:
	int Type2Execution();
	int Type12Execution();
	int Type16Execution();
	int Type17Execution();
	int Type18Execution();
	int Type19Execution();
	int Type20Execution();

	void ErrorLog(int, TCHAR*, int);
	void SendReceiveLog(int, int, TCHAR*);

public:
	// Constructor
	ExecElem(int);
	// Destructor
	virtual ~ExecElem();

	// Create ExecElem instance
	static ExecElem* CreateExecElem(int, int);

	// エレメントの状態を取得する
	int GetStatus();
	// エレメントの状態を設定する
	void SetStatus(int);

	// 実行依存Idを取得する
	int GetWaitForExecId();
	// 実行依存Idを設定する
	void SetWaitForExecId(int);

	// 根となる要素のIDを取得する
	int GetRootId();
	// 根となる要素のIDを設定する
	void SetRootId(int);

	// 要素の種別を取得する
	int GetType();
	// 要素の種別を設定する
	void SetType(int);

	// データを取得する
	void* GetData();
	int GetDataLength();
	// データを設定する
	void SetData(void*);
	void SetDataLength(int);

	// ElementIdを取得する
	int GetElementId();

	// 要素の処理を実行する
	virtual int Execute();

	// Thread status was changed into "Start"
	void ThreadStatusChangedIntoStart();
	// Thread status was changed into "Stop"
	void ThreadStatusChangedIntoStop();

	// Output logs
	void StkPropOutputLog();
};
