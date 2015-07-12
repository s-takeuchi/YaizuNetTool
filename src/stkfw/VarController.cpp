#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <memory.h>
#include "VarController.h"

// �w�肳�ꂽId�ƈ�v����Variable�e�[�u����UdTime�������X�V����
// Variable�e�[�u���ɑ΂��\�߃��b�N���|���Ă����K�v������
// [in] : Id : �X�V�ΏۂƂȂ郌�R�[�h��ID
void LastUpdateTime(int Id)
{
	ColumnData* ColId = new ColumnDataInt(_T("ID"), Id);
	RecordData* SchRec = new RecordData(_T("Variable"), &ColId, 1);

	SYSTEMTIME SysTime;
	GetLocalTime(&SysTime);
	char Buf[20];
	sprintf_s(Buf, "%d/%02d/%02d %02d:%02d:%02d", SysTime.wYear, SysTime.wMonth, SysTime.wDay, SysTime.wHour, SysTime.wMinute, SysTime.wSecond);
	ColumnData* ColUpdt = new ColumnDataStr(_T("UdTime"), Buf);
	RecordData* UpdRec = new RecordData(_T("Variable"), &ColUpdt, 1);

	UpdateRecord(SchRec, UpdRec);
	ClearRecordData(SchRec);
	ClearRecordData(UpdRec);
}

// �w�肵��Id�ƈ�v����R�~���j�P�[�V�����p�ϐ��̃T�C�Y��ԋp����
// [in] : Id : �Ώۂ̃R�~���j�P�[�V�����p�ϐ�
// return : �R�~���j�P�[�V�����p�ϐ��̃T�C�Y (-1:�w�肵���ϐ������݂��Ȃ�, �R�~���j�P�[�V�����p�ϐ��ł͂Ȃ�)
int VarCon_GetCommunicationVariableSize(int Id)
{
	ColumnData* ColSz = new ColumnDataInt(_T("ID"), Id);
	RecordData* RecSz = new RecordData(_T("Variable"), &ColSz, 1);

	LockTable(_T("Variable"), 2);
	RecordData* GetRec = GetRecord(RecSz);
	UnlockTable(_T("Variable"));
	ClearRecordData(RecSz);
	if (GetRec == NULL) {
		return -1;
	}
	ColumnDataInt* ColType = (ColumnDataInt*)GetRec->GetColumn(3);
	ColumnDataInt* ColSize = (ColumnDataInt*)GetRec->GetColumn(5);
	int Size = ColSize->GetValue();
	int Type = ColType->GetValue();
	ClearRecordData(GetRec);

	if (Type != 0) {
		return -1;
	}

	return Size;
}

// �w�肵��ID������Variable�e�[�u�����̃��R�[�h���擾����
// [in] : Id : �擾����ϐ���ID
// [out] : RecordData�C���X�^���X
RecordData* VarCon_GetVariableRecord(int Id)
{
	ColumnData* ColId = new ColumnDataInt(_T("ID"), Id);
	RecordData* SchRec = new RecordData(_T("Variable"), &ColId, 1);
	LockTable(_T("Variable"), 1);
	RecordData* RtRecDat = GetRecord(SchRec);
	UnlockTable(_T("Variable"));
	ClearRecordData(SchRec);
	return RtRecDat;
}

// �w�肵��ID������Variable�e�[�u�����̃��R�[�h���������CName�����Description��ԋp����
// [in] Id : �擾�Ώۂ̕ϐ���ID
// [out] VarName : �ϐ���Name���ԋp�����
// [out] VarDesc : �ϐ���Description���ԋp�����
// Return (-1: �w�肵��ID�����ϐ��͑��݂��Ȃ�, 0: ����I��)
int VarCon_GetVariableNameAndDesc(int Id, TCHAR VarName[32], TCHAR VarDesc[64])
{
	ColumnData* ColId = new ColumnDataInt(_T("ID"), Id);
	RecordData* SchRec = new RecordData(_T("Variable"), &ColId, 1);
	LockTable(_T("Variable"), 1);
	RecordData* RtRecDat = GetRecord(SchRec);
	UnlockTable(_T("Variable"));
	ClearRecordData(SchRec);
	if (RtRecDat == NULL) {
		ClearRecordData(RtRecDat);
		return -1;
	}

	ColumnDataWStr* ColName = (ColumnDataWStr*)RtRecDat->GetColumn(1);
	lstrcpyn(VarName, ColName->GetValue(), 32);
	ColumnDataWStr* ColDesc = (ColumnDataWStr*)RtRecDat->GetColumn(2);
	lstrcpyn(VarDesc, ColDesc->GetValue(), 64);

	ClearRecordData(RtRecDat);

	return 0;
}

// �w�肵��ID�����ϐ������݂��邩�`�F�b�N����
// [in] : Id : �`�F�b�N����ϐ���ID
// [out] : �`�F�b�N���� (TRUE:���݂���, FALSE:���݂��Ȃ�)
BOOL VarCon_CheckVariableExistence(int Id)
{
	ColumnData* ColId = new ColumnDataInt(_T("ID"), Id);
	RecordData* SchRec = new RecordData(_T("Variable"), &ColId, 1);
	LockTable(_T("Variable"), 1);
	RecordData* RtRecDat = GetRecord(SchRec);
	UnlockTable(_T("Variable"));
	ClearRecordData(SchRec);
	BOOL Ret = TRUE;
	if (RtRecDat == NULL) {
		Ret = FALSE;
	}
	ClearRecordData(RtRecDat);
	return Ret;
}

// �w�肵���ϐ����ƈ�v����R�~���j�P�[�V�����p�ϐ���ID���擾����
// [in] : Name : �R�~���j�P�[�V�����p�ϐ��̖���
// [out] : �R�~���j�P�[�V�����p�ϐ���ID (-1:�ϐ���������Ȃ�, �R�~���j�P�[�V�����p�ϐ��ł͂Ȃ�)
int VarCon_GetCommunicationVariableId(TCHAR Name[32])
{
	// �G���[�`�F�b�N
	if (Name == NULL) {
		return -1;
	}
	if (lstrcmp(Name, _T("")) == 0) {
		return -1;
	}

	// ���R�[�h���擾����
	ColumnData* GetColDat[1];
	GetColDat[0] = new ColumnDataWStr(_T("Name"), Name);
	RecordData* RecDat = new RecordData(_T("Variable"), GetColDat, 1);
	LockTable(_T("Variable"), 1);
	RecordData* GetDat = GetRecord(RecDat);
	UnlockTable(_T("Variable"));
	ClearRecordData(RecDat);
	if (GetDat == NULL) {
		return -1;
	}
	ColumnDataInt* TmpColId = (ColumnDataInt*)GetDat->GetColumn(0);
	int FndId = TmpColId->GetValue();
	ClearRecordData(GetDat);
	return FndId;
}

// Variable�e�[�u�����̑S���R�[�h���擾����
// [out] : �A�����ꂽRecordData�C���X�^���X
RecordData* VarCon_GetVariableRecords()
{
	LockTable(_T("Variable"), 1);
	RecordData* RtRecDat = GetRecord(_T("Variable"));
	UnlockTable(_T("Variable"));
	return RtRecDat;
}

// �w�肳�ꂽId�ƈ�v����Variable���R�[�h��Name��Desc������ύX����
// [in] : Id : �X�V�ΏۂƂȂ郌�R�[�h��ID
// [in] : Name : �ύX����l
// [in] : Description : �ύX����l
// [out] : �X�V�ΏۂƂȂ郌�R�[�h��ID
int VarCon_ChangeNameAndDescription(int Id, TCHAR Name[32], TCHAR Description[64])
{
	// �G���[�`�F�b�N
	if (Name == NULL || Description == NULL) {
		return -1;
	}
	if (lstrcmp(Name, _T("")) == 0) {
		return -1;
	}

	ColumnData* ColId = new ColumnDataInt(_T("ID"), Id);
	ColumnData* ColUpdt[2];
	ColUpdt[0] = new ColumnDataWStr(_T("Name"), Name);
	ColUpdt[1] = new ColumnDataWStr(_T("Desc"), Description);
	RecordData* SchRec = new RecordData(_T("Variable"), &ColId, 1);
	RecordData* UpdRec = new RecordData(_T("Variable"), ColUpdt, 2);
	LockTable(_T("Variable"), 2);
	UpdateRecord(SchRec, UpdRec);
	LastUpdateTime(Id);
	UnlockTable(_T("Variable"));
	ClearRecordData(SchRec);
	ClearRecordData(UpdRec);
	return Id;
}

// ���|�W�g����Variable�e�[�u���Ƀ��R�[�h��ǉ�����
// [in] : Name : �ǉ����郌�R�[�h��Name�J�����̒l
// [in] : Description : �ǉ����郌�R�[�h��Desc�J�����̒l
// [in] : Type : �ϐ��̎�� (0:�R�~���j�P�[�V�����p�ϐ�, 1:�t���O�p�ϐ�)
// [out] : (-1�ȊO:�ǉ��������R�[�h��ID�l, -1:�G���[������)
int VarCon_AddVariableRecord(TCHAR Name[32], TCHAR Description[64], int Type)
{
	// �G���[�`�F�b�N
	if (Name == NULL || Description == NULL || (Type > 1 || Type < 0)) {
		return -1;
	}

	if (lstrcmp(Name, _T("")) == 0) {
		return -1;
	}

	LockTable(_T("Property"), 2);
	LockTable(_T("Variable"), 2);

	// Property�e�[�u����Name=MaxVarId�ƂȂ�l���擾����
	ColumnData* FndColDat = new ColumnDataWStr(_T("Name"), _T("MaxVarId"));
	RecordData* FndRecDat = new RecordData(_T("Property"), &FndColDat, 1);
	RecordData* RetRecDat = GetRecord(FndRecDat);
	ColumnDataInt* TmpColId = (ColumnDataInt*)RetRecDat->GetColumn(1);
	int MaxId = TmpColId->GetValue();
	MaxId++;
	ClearRecordData(RetRecDat);
	ClearRecordData(FndRecDat);

	// ���R�[�h��ǉ�����
	ColumnData* AddColDat[7];
	AddColDat[0] = new ColumnDataInt(_T("ID"), MaxId);
	AddColDat[1] = new ColumnDataWStr(_T("Name"), Name);
	AddColDat[2] = new ColumnDataWStr(_T("Desc"), Description);
	AddColDat[3] = new ColumnDataInt(_T("Type"), Type);
	AddColDat[4] = new ColumnDataInt(_T("Flag"), 0);
	AddColDat[5] = new ColumnDataInt(_T("Size"), 0);
	SYSTEMTIME SysTime;
	GetLocalTime(&SysTime);
	char Buf[20];
	sprintf_s(Buf, "%d/%02d/%02d %02d:%02d:%02d", SysTime.wYear, SysTime.wMonth, SysTime.wDay, SysTime.wHour, SysTime.wMinute, SysTime.wSecond);
	AddColDat[6] = new ColumnDataStr(_T("UdTime"), Buf);
	RecordData* AddRecDat = new RecordData(_T("Variable"), AddColDat, 7);
	InsertRecord(AddRecDat);
	ClearRecordData(AddRecDat);

	// Property�e�[�u����Name=MaxVarId�ƂȂ�l���X�V����
	ColumnData* FndCol = new ColumnDataWStr(_T("Name"), _T("MaxVarId"));
	RecordData* FndRec = new RecordData(_T("Property"), &FndCol, 1);
	ColumnData* UpdCol = new ColumnDataInt(_T("ValueInt1"), MaxId);
	RecordData* UpdRec = new RecordData(_T("Property"), &UpdCol, 1);
	UpdateRecord(FndRec, UpdRec);
	ClearRecordData(FndRec);
	ClearRecordData(UpdRec);

	UnlockTable(_T("Variable"));
	UnlockTable(_T("Property"));

	return MaxId;
}

// �w�肳�ꂽId�ƈ�v����Variable���R�[�h���폜����
// [in] : Id : �폜����Variable���R�[�h��ID
void VarCon_DeleteVariableRecord(int Id)
{
	LockTable(_T("Variable"), 2);
	LockTable(_T("VarCommDat"), 2);

	ColumnData* ColId = new ColumnDataInt(_T("ID"), Id);
	RecordData* SchRec = new RecordData(_T("Variable"), &ColId, 1);
	DeleteRecord(SchRec);
	ClearRecordData(SchRec);

	ColumnData* ColIdC = new ColumnDataInt(_T("ID"), Id);
	RecordData* SchRecC = new RecordData(_T("VarCommDat"), &ColIdC, 1);
	DeleteRecord(SchRecC);
	ClearRecordData(SchRecC);

	AzSortRecord(_T("Variable"), _T("ID"));

	UnlockTable(_T("VarCommDat"));
	UnlockTable(_T("Variable"));
}

// �w�肵��Id�ƈ�v����Variable���R�[�h��Flag������ύX����
// [in] : Id : Flag��ύX����Variable���R�[�h��ID
// [in] : Flag : �t���O�̒l (0:FALSE, 1:TRUE)
void VarCon_ChangeFlagVariable(int Id, BOOL Flag)
{
	LockTable(_T("Variable"), 2);
	ColumnData* ColId = new ColumnDataInt(_T("ID"), Id);
	RecordData* SchRec = new RecordData(_T("Variable"), &ColId, 1);
	ColumnData* ColUpd = new ColumnDataInt(_T("Flag"), Flag);
	RecordData* UpdRec = new RecordData(_T("Variable"), &ColUpd, 1);
	UpdateRecord(SchRec, UpdRec);
	LastUpdateTime(Id);
	ClearRecordData(SchRec);
	ClearRecordData(UpdRec);
	UnlockTable(_T("Variable"));
}

// �w�肵��Id�ƈ�v����Variable���R�[�h��Flag�����̒l���擾����
// [in] : Id : Flag��ύX����Variable���R�[�h��ID
// [out] : Flag�����̒l
int VarCon_GetFlagVariable(int Id)
{
	LockTable(_T("Variable"), 1);
	ColumnData* ColId = new ColumnDataInt(_T("ID"), Id);
	RecordData* SchRec = new RecordData(_T("Variable"), &ColId, 1);
	RecordData* Rec = GetRecord(SchRec);
	ColumnDataInt* Col= (ColumnDataInt*)Rec->GetColumn(4);
	int Ret = Col->GetValue();
	ClearRecordData(Rec);
	ClearRecordData(SchRec);
	UnlockTable(_T("Variable"));
	return Ret;
}

// Update records which associate the specified ID
// [In] Id : Target ID for update variable
// [In] Strm : Data of the communication variable
// [In] Size : Size of Strm
void VarCon_UpdateCommunicationVariable(int Id, BYTE* Strm, int Size)
{
	LockTable(_T("VarCommDat"), 2);
	LockTable(_T("Variable"), 2);

	ColumnData* UpdSCol = new ColumnDataInt(_T("ID"), Id);
	RecordData* UpdSRec = new RecordData(_T("Variable"), &UpdSCol, 1);
	ColumnData* UpdCol = new ColumnDataInt(_T("Size"), Size);
	RecordData* UpdRec = new RecordData(_T("Variable"), &UpdCol, 1);
	UpdateRecord(UpdSRec, UpdRec);
	LastUpdateTime(Id);
	ClearRecordData(UpdSRec);
	ClearRecordData(UpdRec);

	ColumnData* SchCol = new ColumnDataInt(_T("ID"), Id);
	RecordData* SchRec = new RecordData(_T("VarCommDat"), &SchCol, 1);
	DeleteRecord(SchRec);
	ClearRecordData(SchRec);

	ColumnData* ColDt[3];
	int CurPnt = 0;
	int MaxCnt = Size / 10000 + 1;
	for (int Loop = 0; Loop < MaxCnt; Loop++) {
		ColDt[0] = new ColumnDataInt(_T("ID"), Id);
		ColDt[1] = new ColumnDataInt(_T("Index"), Loop);
		ColDt[2] = new ColumnDataBin(_T("CommDat"), &Strm[CurPnt], 10000);
		RecordData* RecDat = new RecordData(_T("VarCommDat"), ColDt, 3);
		InsertRecord(RecDat);
		ClearRecordData(RecDat);
		CurPnt += 10000;
	}

	UnlockTable(_T("Variable"));
	UnlockTable(_T("VarCommDat"));
}

// Acquire data of the specified communication variable
// [in] Id : Target ID for variable
// [out] Strm : Aquired data of communication variable
// [in] Size : Size of Strm
int VarCon_GetCommunicationVariable(int Id, BYTE* Strm, int Size)
{
	if (Size < 0 || Size > 10000000) {
		return -1;
	}

	BYTE *TmpStrm = new BYTE[10000000];

	int ActSize = VarCon_GetCommunicationVariableSize(Id);

	LockTable(_T("VarCommDat"), 2);
	LockTable(_T("Variable"), 2);
	int CurPnt = 0;
	ColumnData* ColDt[2];
	for (int Loop = 0; Loop < 1000; Loop++) {
		ColDt[0] = new ColumnDataInt(_T("ID"), Id);
		ColDt[1] = new ColumnDataInt(_T("Index"), Loop);
		RecordData* RecDat = new RecordData(_T("VarCommDat"), ColDt, 2);
		RecordData* GetDat = GetRecord(RecDat);
		if (GetDat == NULL) {
			ClearRecordData(RecDat);
			break;
		}
		ColumnDataBin* DatBin = (ColumnDataBin*)GetDat->GetColumn(2);
		BYTE* DatBinPnt = DatBin->GetValue();
		memcpy(&TmpStrm[CurPnt], DatBinPnt, 10000);
		ClearRecordData(RecDat);
		ClearRecordData(GetDat);
		CurPnt += 10000;
	}
	UnlockTable(_T("Variable"));
	UnlockTable(_T("VarCommDat"));

	memcpy(Strm, TmpStrm, Size);

	delete TmpStrm;

	return ActSize;
}

// Check the specified size + current size exceeds the limitation or not.
// Totally 100M Bytes data can be stored into the VarCommDat table.
// [in] Size : Size in byte
// [out] : TRUE : Not exceeded, FALSE : Exceeded
BOOL VarCon_CheckCommunicationVariableSize(int Size)
{
	if (Size != -1) {
		if ((GetNumOfRecords(_T("VarCommDat")) + Size / 10000 + 1) > 10000) {
			return FALSE;
		}
	}
	return TRUE;
}

// Check the variable count exceeds the limitation (1000) or not.
// [out] : TRUE: Count is less than 1000, FALSE: Count equals to or greater than 1000
BOOL VarCon_CheckVariableCount()
{
	if ((GetNumOfRecords(_T("Variable")) + 1) > 1000) {
		return FALSE;
	}
	return TRUE;
}

// Acquire all communication variable IDs and names.
// Ids[n] is the ID of the variable associats Names[n].
// Ids [out] : Acquired IDs. Totally, 1000 IDs can be acquired.
// Names [out] : Acquired names. Totally, 1000 names can be acquired.
// Return : Number of acquired names
int VarCon_GetAllCommVariableNames(int Ids[1000], TCHAR Names[1000][32])
{
	int MaxIndex = 0;
	RecordData* VarRecs = VarCon_GetVariableRecords();
	RecordData* CurVarRec = VarRecs;
	while (CurVarRec != NULL) {
		ColumnDataInt* VarTypeCol = (ColumnDataInt*)CurVarRec->GetColumn(3);
		int VarType = VarTypeCol->GetValue();
		if (VarType == 0) {
			ColumnDataInt* VarIdCol = (ColumnDataInt*)CurVarRec->GetColumn(0);
			ColumnDataWStr* VarNameCol = (ColumnDataWStr*)CurVarRec->GetColumn(1);
			lstrcpyn(Names[MaxIndex], VarNameCol->GetValue(), 32);
			Ids[MaxIndex] = VarIdCol->GetValue();
			MaxIndex++;
		}
		CurVarRec = CurVarRec->GetNextRecord();
	}
	ClearRecordData(VarRecs);
	return MaxIndex;
}
