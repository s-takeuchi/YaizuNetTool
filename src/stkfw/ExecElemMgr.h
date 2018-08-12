#pragma once
#include <windows.h>
#include "server\ExecElem.h"

class ExecElemMgr
{
private:
	// This instance
	static ExecElemMgr* ThisInstance;

	// �e���s�n�v�f�C�f�[�^�n�v�f�̎��s����
	ExecElem* ExecElems[1000];
	int NumOfExecElem;

	// �N���e�B�J���Z�N�V����
	static CRITICAL_SECTION CritSect;
	static CRITICAL_SECTION CritSectExe; //#10084

private:
	// Constructor
	ExecElemMgr();
	// Destructor
	~ExecElemMgr();

	// �w�肵��ID�̗v�f�ƃ����N���Ă���S�Ă̗v�f(ExecElem)�擾����
	void GetLinkedElementIds(int, int, int, int);

	// ���s�ˑ�Id�̐ݒ�
	void SetWaitForThreadEnd(int);

	// ���̏����̃X�e�[�^�X��NotInScope����Waiting�ɕύX����
	void ChangeNotInScopeToWaiting(int, int);

	// �����N�̎�ʂ�ύX����
	void ChangeLineType(int, int, int);

public:
	// Get this instance
	static ExecElemMgr* GetInstance();

	// �w�肵��ID��ExecElem��ExecElems�z�񂩂�擾����
	ExecElem* GetExecElem(int);
	// ExecElems�z���X�Ԗڂɂ���ExecElem���擾����
	ExecElem* GetExecElemByIndex(int);
	// ExecElems�z��ɑ��݂���ExecElem�C���X�^���X�̐����擾����
	int GetExecElemCount();

	// �S�Ă̎��s�n�v�f�C�f�[�^�n�v�f��ExecElem�ɓW�J
	void AddExecElem(int);
	// �S�Ă�ExecElem���폜����
	void DeleteExecElem(int);

	// �e�v�f�̏��������s����
	void ExecuteElement(int);

	// Thread status was changed into "Start"
	void ThreadStatusChangedIntoStart(int);

	// Thread status was changed into "Stop"
	void ThreadStatusChangedIntoStop(int);

	// �����N�̎�ʂ��N���A����
	void ClearLineType(int );

};
