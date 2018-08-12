#include "ExecElem_WriteFile.h"
#include "LowDbAccess.h"
#include <windows.h>

ExecElem_WriteFile::ExecElem_WriteFile(int Id) : ExecElem(Id)
{
}

// Destructor
ExecElem_WriteFile::~ExecElem_WriteFile()
{
}

int ExecElem_WriteFile::Execute()
{
	// �������ݑΏۃt�@�C���p�X�̎擾
	TCHAR BufPath[256];
	LowDbAccess::GetInstance()->GetElementInfoParamStr(ElementId, BufPath, 1);
	// �A�N�Z�X��ʂ̎擾
	int AccessType = LowDbAccess::GetInstance()->GetElementInfoParamInt(ElementId, 1);

	// ���̓f�[�^�̎擾
	BYTE* InputDat = (BYTE*)GetData();
	int InputDatLength = GetDataLength();

	// ��Ɨp�̈�
	BYTE* WorkDat;
	int WorkDatLength;
	int WorkDatLenForFile;
	int WorkDatLenForInput;
	DWORD TmpSize = 0;

	// ��Ɨp�̈�ւ̃f�[�^�̊i�[
	if (AccessType == 0) {
		WorkDat = InputDat;
		WorkDatLength = InputDatLength;
	} else {
		HANDLE ReadFileHndl = CreateFile(BufPath, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		if (ReadFileHndl != INVALID_HANDLE_VALUE) {
			LARGE_INTEGER ExistingFileSize;
			GetFileSizeEx(ReadFileHndl, &ExistingFileSize);
			if (ExistingFileSize.QuadPart + InputDatLength >= 10000000) {
				CloseHandle(ReadFileHndl);
				return 2;
			}

			WorkDatLength = (int)(ExistingFileSize.QuadPart + InputDatLength);
			WorkDat = new BYTE[WorkDatLength];

			if (AccessType == 1) {
				WorkDatLenForFile = (int)ExistingFileSize.QuadPart;
				WorkDatLenForInput = WorkDatLength - WorkDatLenForFile;
				memcpy(WorkDat, InputDat, WorkDatLenForInput);
				if (ReadFile(ReadFileHndl, (LPVOID)(WorkDat + WorkDatLenForInput), WorkDatLenForFile, &TmpSize, NULL) == 0) {
					delete WorkDat;
					CloseHandle(ReadFileHndl);
					return 2;
				}
			}
			if (AccessType == 2) {
				WorkDatLenForInput = InputDatLength;
				WorkDatLenForFile = WorkDatLength - WorkDatLenForInput;
				if (ReadFile(ReadFileHndl, (LPVOID)WorkDat, WorkDatLenForFile, &TmpSize, NULL) == 0) {
					delete WorkDat;
					CloseHandle(ReadFileHndl);
					return 2;
				}
				memcpy(WorkDat + WorkDatLenForFile, InputDat, WorkDatLenForInput);
			}

			delete InputDat;
			SetData((void*)WorkDat);
			SetDataLength(WorkDatLength);

			CloseHandle(ReadFileHndl);
		} else {
			// �����̃t�@�C�������݂��Ȃ��ꍇ
			WorkDat = InputDat;
			WorkDatLength = InputDatLength;
		}
	}

	// �t�@�C���ւ̏�������
	HANDLE FileHndl = CreateFile(BufPath, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (FileHndl == INVALID_HANDLE_VALUE) {
		delete WorkDat;
		SetData(NULL);
		SetDataLength(0);
		return 2;
	};
	if (WriteFile(FileHndl, (LPCVOID)WorkDat, WorkDatLength, &TmpSize, NULL) == 0) {
		delete WorkDat;
		SetData(NULL);
		SetDataLength(0);
		CloseHandle(FileHndl);
		return 2;
	}
	CloseHandle(FileHndl);

	return 0;
}
