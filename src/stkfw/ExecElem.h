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

	static const int RECEIVER  = 1;
	static const int SENDER_R  = 4;
	static const int SENDER    = 7;
	static const int CHECKFLAG = 10;

public:
	// Attributes for the "Execute Program"
	PROCESS_INFORMATION ExeProcInfo;
	HANDLE StdInD, StdOutD;

private:
	int Type2Execution();
	int Type4Execution();
	void Type5Execution();
	int Type11Execution();
	int Type12Execution();
	int Type13Execution();
	int Type14Execution();
	int Type16Execution();
	int Type17Execution();
	int Type18Execution();
	int Type19Execution();
	int Type20Execution();
	int Type21Execution();
	int Type22Execution();

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
