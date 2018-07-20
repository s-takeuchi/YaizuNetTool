#pragma once
#include <windows.h>
#include "ExecElem.h"

class StkPropExecMgr
{
private:
	// This instance
	static StkPropExecMgr* ThisInstance;

	// �e���s�n�v�f�C�f�[�^�n�v�f�̎��s����
	StkPropExecElem* ExecElems[1000];
	int NumOfExecElem;

	// �N���e�B�J���Z�N�V����
	static CRITICAL_SECTION CritSect;
	static CRITICAL_SECTION CritSectExe; //#10084

private:
	// Constructor
	StkPropExecMgr();
	// Destructor
	~StkPropExecMgr();

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
	static StkPropExecMgr* GetInstance();

	// �w�肵��ID��ExecElem��ExecElems�z�񂩂�擾����
	StkPropExecElem* GetExecElem(int);
	// ExecElems�z���X�Ԗڂɂ���ExecElem���擾����
	StkPropExecElem* GetExecElemByIndex(int);
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

	// Store Data�܂���Load Data�̃J�E���^�[������������
	void InitStoreAndLoadDataCounter(int);

	// Mapper�̃}�b�v�ϕϐ���ID������������
	void InitMappingIds(int);

	// Initialization of execute program
	void InitExecProgram(int Id);

	// Timer�̓����J�E���^�[������������
	void InitTimer(int);

};
