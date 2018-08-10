#include "ExecElem_ReadFile.h"
#include "..\VarController.h"
#include "..\LowDbAccess.h"
#include <windows.h>

ExecElem_ReadFile::ExecElem_ReadFile(int Id) : ExecElem(Id)
{
}

// Destructor
ExecElem_ReadFile::~ExecElem_ReadFile()
{
}

int ExecElem_ReadFile::Execute()
{
	// 読み込み対象ファイルパスの取得
	TCHAR BufPath[256];
	LowDbAccess::GetInstance()->GetElementInfoParamStr(ElementId, BufPath, 1);
	// アクセス種別の取得
	int AccessType = LowDbAccess::GetInstance()->GetElementInfoParamInt(ElementId, 1);

	// 入力データの取得
	BYTE* InputDat = (BYTE*)GetData();
	int InputDatLength = GetDataLength();

	// 作業用領域
	BYTE* WorkDat;
	int WorkDatLength;
	DWORD TmpSize = 0;

	// 読み込み対象ファイルのオープン
	HANDLE ReadFileHndl = CreateFile(BufPath, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (ReadFileHndl == INVALID_HANDLE_VALUE) {
		return 2;
	}

	// サイズのチェック
	LARGE_INTEGER ExistingFileSize;
	GetFileSizeEx(ReadFileHndl, &ExistingFileSize);

	// Overwrite data
	if (AccessType == 0) {
		if (ExistingFileSize.QuadPart >= 10000000) {
			CloseHandle(ReadFileHndl);
			return 2;
		}
		WorkDatLength = (int)ExistingFileSize.QuadPart;
		WorkDat = new BYTE[WorkDatLength];

		if (ReadFile(ReadFileHndl, (LPVOID)WorkDat, WorkDatLength, &TmpSize, NULL) == 0) {
			CloseHandle(ReadFileHndl);
			delete WorkDat;
			return 2;
		}
	}
	// Insert data / join data
	if (AccessType == 1 || AccessType == 2) {
		if (ExistingFileSize.QuadPart + InputDatLength >= 10000000) {
			CloseHandle(ReadFileHndl);
			return 2;
		}
		WorkDatLength = (int)ExistingFileSize.QuadPart + InputDatLength;
		WorkDat = new BYTE[WorkDatLength];

		if (AccessType == 1) {
			if (ReadFile(ReadFileHndl, (LPVOID)WorkDat, (int)ExistingFileSize.QuadPart, &TmpSize, NULL) == 0) {
				CloseHandle(ReadFileHndl);
				delete WorkDat;
				return 2;
			}
			memcpy(WorkDat + (int)ExistingFileSize.QuadPart, InputDat, InputDatLength);
		}
		if (AccessType == 2) {
			memcpy(WorkDat, InputDat, InputDatLength);
			if (ReadFile(ReadFileHndl, (LPVOID)(WorkDat + InputDatLength), (int)ExistingFileSize.QuadPart, &TmpSize, NULL) == 0) {
				CloseHandle(ReadFileHndl);
				delete WorkDat;
				return 2;
			}
		}
	}

	delete InputDat;
	CloseHandle(ReadFileHndl);
	SetData((void*)WorkDat);
	SetDataLength(WorkDatLength);

	return 0;
}
