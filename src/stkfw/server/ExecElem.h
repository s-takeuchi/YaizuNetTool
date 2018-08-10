#pragma once
#include <windows.h>

class ExecElem
{
protected:
	// �G�������gID
	int ElementId;

	// ���ƂȂ�v�f��ID
	int RootId;

	// �v�f�̎��
	int ElementType;

	// �G�������g�̏��
	int Status;

	// ���s�ˑ�Id
	int WaitForExecId;

	// ��������f�[�^
	void* Data;
	int DataLength;

	// Thread start/stop flag
	BOOL StartStopFlag;

public:
	static const int STATUS_DONE = 1; // ���Ɏ��s�ς̏��
	static const int STATUS_TRIED = 2; // ���s���������̏����Ɉڂꂸ
	static const int STATUS_WAITING = 3; // �����҂�
	static const int STATUS_NOTINSCOPE = 4; // �ΏۊO
	static const int STATUS_CLEAR = 5; // ���݂̃X���b�h���N���A����i�I�[����������������ԁj
	static const int STATUS_DWAITING = 6; // ���̃X���b�h�ɏ����������p���ꂽ����̏��
	static const int STATUS_BWAITING = 7; // ���s���ʂ��u���b�N���(Ret==2)�̏ꍇ

	static const int RECEIVER    = 1;
	static const int LOADDATA    = 2;
	static const int SENDER_R    = 4;
	static const int STOREDATA_R = 5;
	static const int SENDER      = 7;
	static const int STOREDATA   = 8;
	static const int CHECKFLAG   = 10;
	static const int CHECKDATA   = 11;
	static const int TIMER       = 12;
	static const int CHANGEFLAG  = 13;
	static const int CHANGEDATA  = 14;
	static const int CLOSESOCKET = 16;
	static const int WRITEFILE   = 18;
	static const int READFILE    = 19;
	static const int RECEIVERUDP = 21;
	static const int SENDERUDP_R = 22;
	static const int SENDERUDP   = 23;

public:
	// Attributes for the "Execute Program"
	PROCESS_INFORMATION ExeProcInfo;
	HANDLE StdInD, StdOutD;

private:
	int Type17Execution();
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

	// �G�������g�̏�Ԃ��擾����
	int GetStatus();
	// �G�������g�̏�Ԃ�ݒ肷��
	void SetStatus(int);

	// ���s�ˑ�Id���擾����
	int GetWaitForExecId();
	// ���s�ˑ�Id��ݒ肷��
	void SetWaitForExecId(int);

	// ���ƂȂ�v�f��ID���擾����
	int GetRootId();
	// ���ƂȂ�v�f��ID��ݒ肷��
	void SetRootId(int);

	// �v�f�̎�ʂ��擾����
	int GetType();
	// �v�f�̎�ʂ�ݒ肷��
	void SetType(int);

	// �f�[�^���擾����
	void* GetData();
	int GetDataLength();
	// �f�[�^��ݒ肷��
	void SetData(void*);
	void SetDataLength(int);

	// ElementId���擾����
	int GetElementId();

	// �v�f�̏��������s����
	virtual int Execute();

	// Thread status was changed into "Start"
	void ThreadStatusChangedIntoStart();
	// Thread status was changed into "Stop"
	void ThreadStatusChangedIntoStop();

	// Output logs
	void StkPropOutputLog();
};