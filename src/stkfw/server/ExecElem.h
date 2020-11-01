#pragma once
#include <windows.h>
#include <mutex>
#include <shared_mutex>

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

public:
	static const int STATUS_DONE = 1; // 既に実行済の状態
	static const int STATUS_TRIED = 2; // 実行したが次の処理に移れず
	static const int STATUS_WAITING = 3; // 処理待ち
	static const int STATUS_NOTINSCOPE = 4; // 対象外
	static const int STATUS_CLEAR = 5; // 現在のスレッドをクリアする（終端処理が完了した状態）
	static const int STATUS_DWAITING = 6; // 次のスレッドに処理が引き継がれた直後の状態
	static const int STATUS_BWAITING = 7; // 実行結果がブロック状態(Ret==2)の場合

	static const int RECEIVER    = 1;
	static const int LOADDATA    = 2;
	static const int NOTHING_I   = 3;
	static const int SENDER_R    = 4;
	static const int STOREDATA_R = 5;
	static const int NOTHING_R   = 6;
	static const int SENDER      = 7;
	static const int STOREDATA   = 8;
	static const int NOTHING     = 9;
	static const int CHECKFLAG   = 10;
	static const int CHECKDATA   = 11;
	static const int TIMER       = 12;
	static const int CHANGEFLAG  = 13;
	static const int CHANGEDATA  = 14;
	static const int CLOSESOCKET = 16;
	static const int MAPPER      = 17;
	static const int WRITEFILE   = 18;
	static const int READFILE    = 19;
	static const int EXECPROGRAM = 20;
	static const int RECEIVERUDP = 21;
	static const int SENDERUDP_R = 22;
	static const int SENDERUDP   = 23;
	static const int HTTPHEADER  = 24;

private:
	void ErrorLog(int, TCHAR*, int);
	void SendReceiveLog(int, int, TCHAR*);

// Logging functions start
private:
	static wchar_t *log;
	static std::mutex log_mutex;
	static int max_log_size;
	static int log_update_version;
	static std::once_flag init_log_flag;
	static void init_log();

public:
	static void add_log(const wchar_t*, const wchar_t*);
	static void clear_log();
	static void get_log(wchar_t*, const int);
	static int get_log_size();
	static int get_max_log_size();
	static void change_size(const int);
// Logging functions end

// Lock management start
protected:
	class LockMgr {
	public:
		int LockTarget;
		std::shared_mutex LockObj;
		LockMgr() {
			LockTarget = -1;
		}
	};
	static std::mutex LockMutex;
	static const int MAXNUM_LOCK = 2000;
	static LockMgr LockMgrImpl[MAXNUM_LOCK];
	static int LockMgrCount;
	static LockMgr* GetLockMgr(int);
	static void LockShared(int);
	static void UnlockShared(int);
	static bool TryLockShared(int);
	static void Lock(int);
	static void Unlock(int);
	static bool TryLock(int);
// Lock management end

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
	// 戻り値: (0:Terminator以外の処理が正常終了, 1:Terminatorの処理が正常終了, 2:異常終了(処理を進めない))
	virtual int Execute() = 0;

	// Thread status was changed into "Start"
	void ThreadStatusChangedIntoStart();
	// Thread status was changed into "Stop"
	void ThreadStatusChangedIntoStop();

	// Output logs
	void StkPropOutputLog();
};
