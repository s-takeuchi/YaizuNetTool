#include <windows.h>
#include <tchar.h>
#include <commctrl.h>
#include <shlwapi.h>
#include <shlobj.h>
#include <winnls.h>
#include <shfolder.h>

#include "resource.h"
#include "VarCon.h"
#include "VarController.h"
#include "..\..\..\YaizuComLib\src\\msgproc\msgproc.h"

HINSTANCE InstHndl;
HWND WndHndl;

// Button of communication
HWND ButtonCommAddWndHndl;
HWND ButtonCommDelWndHndl;
HWND ButtonCommChgWndHndl;

// Button of flag
HWND ButtonFlagAddWndHndl;
HWND ButtonFlagDelWndHndl;
HWND ButtonFlagChgWndHndl;
HWND ButtonFlagTrueWndHndl;
HWND ButtonFlagFalseWndHndl;

// List view handle
HWND ComListWndHndl;
HWND FlgListWndHndl;

// �����ڂɊւ���f�ނ̃n���h��
HWND BkGndWndHndl;
HWND BtmGndWndHndl;
HWND RadioButton1;
HWND RadioButton2;
HWND IconWndHndl;
HWND TextWndHndl;
HWND ButtonRefWndHndl;

// �R�~���j�P�[�V�����p�ݒ�_�C�A���O�Ɋ֌W����n���h��
HWND CommWndHndl;
HWND CommBkGndWndHndl;
HWND CommIconWndHndl;
HWND CommStName;
HWND CommStDesc;
HWND CommEdName;
HWND CommEdDesc;
HWND CommButtonOK;
HWND CommButtonCancel;
HWND CommEdit;

// �t���O�p�ݒ�_�C�A���O�Ɋ֌W����n���h��
HWND FlagDlgHndl;

// �I�����ꂽ�ϐ��̎�� (0:Communication, 1:Flag)
int SelVarType = 0;

// �I�����ꂽ�ϐ���ID
int SelVarId = -1;

// ���쎯�ʎq (1:Add, 2:Edit)
int OpType = 0;

// �G�f�B�b�g�{�b�N�X�ւ̏o�͎�� (0:Binary, 1:UTF-8)
int SelOutMode = 0;

// �R�~���j�P�[�V�����p�ϐ��̍�Ɨ̈�
BYTE* WorkDat = NULL;
int WorkDatActSize = 0;

// ���C���E�B���h�E�����s�����ǂ���
BOOL RunFlag = FALSE;

LRESULT CALLBACK VarConWndProc( HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK CommProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK FlagDlg(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK SetFontProc(HWND, LPARAM);


BOOL CALLBACK SetFontProc(HWND hwnd, LPARAM lParam)
{
	static HFONT FontHndl = CreateFont(16, 0, 0, 0, FW_REGULAR, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_DONTCARE, _T("Arial"));
	SendMessage(hwnd, WM_SETFONT, (WPARAM)FontHndl, (LPARAM)TRUE);
	return TRUE;
}

void SetFontCourier(HWND WndHndl)
{
	static HFONT FontHndl = CreateFont(16, 0, 0, 0, FW_REGULAR, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_DONTCARE, _T("Courier"));
	SendMessage(WndHndl, WM_SETFONT, (WPARAM)FontHndl, (LPARAM)TRUE);
}

void SetIconToWnd(HWND TargetWndHndl)
{
	static HICON IconHndlrS = NULL;
	static HICON IconHndlrB = NULL;
	if (IconHndlrS == NULL) {
		IconHndlrS = (HICON)LoadImage(InstHndl, (LPCTSTR)IDI_VARICON4, IMAGE_ICON, 16, 16, LR_DEFAULTCOLOR);
	}
	if (IconHndlrB == NULL) {
		IconHndlrB = (HICON)LoadImage(InstHndl, (LPCTSTR)IDI_VARICON4, IMAGE_ICON, 32, 32, LR_DEFAULTCOLOR);
	}
	if (IconHndlrS != NULL && IconHndlrB != NULL) {
		SendMessage(TargetWndHndl, WM_SETICON, ICON_SMALL, (LPARAM)IconHndlrS);
		SendMessage(TargetWndHndl, WM_SETICON, ICON_BIG, (LPARAM)IconHndlrB);
	}
}

// �R�~���j�P�[�V�����p�ϐ��ݒ�E�B���h�E�̃��j���[�̃`�F�b�N��Ԃ�ύX����
// [in] : Type : ���j���[�̃`�F�b�N��� (0:Binary, 1:UTF-8)
void ChangeMenuCheckStatus(int Type)
{
	CheckMenuItem(GetSubMenu(GetMenu(CommWndHndl), 1), (Type == 0) ? 1 : 0, MF_BYPOSITION | MF_UNCHECKED);
	CheckMenuItem(GetSubMenu(GetMenu(CommWndHndl), 1), (Type == 0) ? 0 : 1, MF_BYPOSITION | MF_CHECKED);
}

// �ϐ���ID���擾����
// [in] : WndHndl : �R�~���j�P�[�V�����p�ϐ��ꗗ�܂��̓t���O�ϐ��ꗗ��ListView�E�B���h�E�n���h��
// [in] : LvIndex : �I������Ă���ListView�A�C�e���̃C���f�b�N�X�l
// [out] : �ϐ���ID
int GetSelectedVariableId(HWND WndHndl, int LvIndex)
{
	TCHAR IdBuf[11];
	ListView_GetItemText(WndHndl, LvIndex, 0, IdBuf, 10);
	int Ret = StrToInt(IdBuf);
	return Ret;
}

void MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;
	wcex.cbSize        = sizeof(WNDCLASSEX); 
	wcex.style         = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc   = (WNDPROC)VarConWndProc;
	wcex.cbClsExtra    = 0;
	wcex.cbWndExtra    = 0;
	wcex.hInstance     = hInstance;
	wcex.hIcon         = LoadIcon(NULL, MAKEINTRESOURCE(IDI_APPLICATION));
	wcex.hIconSm       = LoadIcon(NULL, MAKEINTRESOURCE(IDI_APPLICATION));
	wcex.hCursor       = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName  = MAKEINTRESOURCE(IDR_VARCON_MENU);
	wcex.lpszClassName = _T("Variable controller");
	RegisterClassEx(&wcex);

	WNDCLASSEX CommWc;
	CommWc.cbSize      = sizeof(WNDCLASSEX);
	CommWc.style       = CS_HREDRAW | CS_VREDRAW;
	CommWc.lpfnWndProc   = (WNDPROC)CommProc;
	CommWc.cbClsExtra    = 0;
	CommWc.cbWndExtra    = 0;
	CommWc.hInstance     = hInstance;
	CommWc.hIcon         = LoadIcon(NULL, MAKEINTRESOURCE(IDI_APPLICATION));
	CommWc.hIconSm       = LoadIcon(NULL, MAKEINTRESOURCE(IDI_APPLICATION));
	CommWc.hCursor       = LoadCursor(NULL, IDC_ARROW);
	CommWc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
	CommWc.lpszMenuName  = MAKEINTRESOURCE(IDR_VARCOMM_MENU);
	CommWc.lpszClassName = _T("Communication");
	RegisterClassEx(&CommWc);
}

void Var_DisplayMainWindow()
{
	InstHndl = GetModuleHandle(NULL);
	if (RunFlag == FALSE) {
		RunFlag = TRUE;
		MSG msg;
		MyRegisterClass(InstHndl);
		WndHndl = CreateWindow(_T("Variable controller"), _T("Variable controller"), WS_CAPTION | WS_SYSMENU | WS_DLGFRAME | WS_MAXIMIZEBOX | WS_MINIMIZEBOX | WS_SYSMENU | WS_SIZEBOX, CW_USEDEFAULT, CW_USEDEFAULT, 512, 450, NULL, NULL, InstHndl, NULL);
		SetIconToWnd(WndHndl);
		ShowWindow(WndHndl, SW_SHOW);
		UpdateWindow(WndHndl);
		while (GetMessage(&msg, NULL, 0, 0)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	} else {
		ShowWindow(WndHndl, SW_SHOWNORMAL);
		UpdateWindow(WndHndl);
		SetForegroundWindow(WndHndl);
	}
}

void SetMinWindowSize(LPARAM lParam)
{
	LPMINMAXINFO lpmmi;
	lpmmi = (LPMINMAXINFO)lParam;
	lpmmi->ptMinTrackSize.x = 560;
	lpmmi->ptMinTrackSize.y = 300;
}

// This function refreshes List-View on the client area of the window.
// [in] BOOL : Initialization flag
void ViewData(BOOL Init)
{
	LV_COLUMN LvColm;
	LV_ITEM LvItem;

	if (Init == TRUE) {
		// Insert columns (1st column)
		LvColm.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		LvColm.fmt = LVCFMT_LEFT;

		// Insert columns (2nd and later column)
		TCHAR ColName[10][32] = {
			_T("ID"), _T("Name"), _T("Description"), _T("Size"), _T("Last update time"),
			_T("ID"), _T("Name"), _T("Description"), _T("Flag"), _T("Last update time")
		};
		int ColSize[10] = {
			40, 100, 180, 65, 135,
			40, 100, 180, 65, 135
		};

		int Loop;
		for (Loop = 0; Loop < 5; Loop++) {
			LvColm.cx = ColSize[Loop];
			LvColm.pszText = ColName[Loop];
			LvColm.iSubItem = Loop + 1;
			ListView_InsertColumn(ComListWndHndl, Loop, &LvColm);
		}
		for (Loop = 0; Loop < 5; Loop++) {
			LvColm.cx = ColSize[5 + Loop];
			LvColm.pszText = ColName[5 + Loop];
			LvColm.iSubItem = Loop + 1;
			ListView_InsertColumn(FlgListWndHndl, Loop, &LvColm);
		}
	}

	// Delete items
	ListView_DeleteAllItems(ComListWndHndl);
	ListView_DeleteAllItems(FlgListWndHndl);

	RecordData* RtRecDat = VarCon_GetVariableRecords();
	// Insert records
	int RecLoop[2] = {0, 0};
	RecordData *CurRecDat = RtRecDat;
	while(CurRecDat != NULL) {
		// for "Type"
		HWND CurListView;
		ColumnDataInt* ColType = (ColumnDataInt*)CurRecDat->GetColumn(3);
		int Type = ColType->GetValue();
		if (Type == 0) {
			CurListView = ComListWndHndl;
		} else {
			CurListView = FlgListWndHndl;
		}
		LvItem.mask = LVIF_IMAGE | LVIF_TEXT;
		LvItem.pszText = _T("");
		LvItem.iImage = 0;
		LvItem.iItem = RecLoop[Type];
		LvItem.iSubItem = 0;
		ListView_InsertItem(CurListView, &LvItem);

		TCHAR Val[256];

		// for "ID"
		ColumnDataInt* ColId = (ColumnDataInt*)CurRecDat->GetColumn(0);
		int Id = ColId->GetValue();
		wsprintf(Val, _T("%d"), Id);
		LvItem.mask = LVIF_TEXT;
		LvItem.pszText = Val;
		LvItem.iItem = RecLoop[Type];
		LvItem.iSubItem = 0;
		ListView_SetItem(CurListView, &LvItem);

		// for "Name"
		ColumnDataWStr* ColName = (ColumnDataWStr*)CurRecDat->GetColumn(1);
		TCHAR* Name = ColName->GetValue();
		LvItem.mask = LVIF_TEXT;
		LvItem.pszText = Name;
		LvItem.iItem = RecLoop[Type];
		LvItem.iSubItem = 1;
		ListView_SetItem(CurListView, &LvItem);

		// for "Description"
		ColumnDataWStr* ColDesc = (ColumnDataWStr*)CurRecDat->GetColumn(2);
		TCHAR* Desc = ColDesc->GetValue();
		LvItem.pszText = Desc;
		LvItem.iItem = RecLoop[Type];
		LvItem.iSubItem = 2;
		ListView_SetItem(CurListView, &LvItem);

		// for "Last update time"
		ColumnDataStr* ColUpt = (ColumnDataStr*)CurRecDat->GetColumn(6);
		char* Udt = ColUpt->GetValue();
		wsprintf(Val, _T("%S"), Udt);
		LvItem.pszText = Val;
		LvItem.iItem = RecLoop[Type];
		LvItem.iSubItem = 4;
		ListView_SetItem(CurListView, &LvItem);

		if (Type == 0) {
			// for "Size"
			ColumnDataInt* ColSize = (ColumnDataInt*)CurRecDat->GetColumn(5);
			int Size = ColSize->GetValue();
			wsprintf(Val, _T("%d"), Size);
			LvItem.pszText = Val;
			LvItem.iItem = RecLoop[Type];
			LvItem.iSubItem = 3;
			ListView_SetItem(CurListView, &LvItem);
		} else {
			// for "Flag"
			ColumnDataInt* ColFlag = (ColumnDataInt*)CurRecDat->GetColumn(4);
			int Flag = ColFlag->GetValue();
			if (Flag == 0) {
				LvItem.pszText = _T("False");
			} else if (Flag == 1) {
				LvItem.pszText = _T("True");
			} else {
				LvItem.pszText = _T("Invalid");
			}
			LvItem.iItem = RecLoop[Type];
			LvItem.iSubItem = 3;
			ListView_SetItem(CurListView, &LvItem);
		}

		RecLoop[Type]++;

		CurRecDat = CurRecDat->GetNextRecord();
	};
	ClearRecordData(RtRecDat);
}

int ChangeRadioButton()
{
	static HICON IconHndlComm = NULL;
	static HICON IconHndlFlag = NULL;

	if (IconHndlComm == NULL) {
		IconHndlComm = (HICON)LoadImage(InstHndl,  MAKEINTRESOURCE(IDI_VARICON3), IMAGE_ICON, 32, 32, LR_DEFAULTCOLOR);
	}
	if (IconHndlFlag == NULL) {
		IconHndlFlag = (HICON)LoadImage(InstHndl,  MAKEINTRESOURCE(IDI_VARICON1), IMAGE_ICON, 32, 32, LR_DEFAULTCOLOR);
	}

	if (SelVarType == 0) {
		SendMessage(RadioButton1, BM_SETCHECK, BST_CHECKED, 0L);
		SendMessage(RadioButton2, BM_SETCHECK, BST_UNCHECKED, 0L);
		SendMessage(IconWndHndl, STM_SETICON, (WPARAM)IconHndlComm, (LPARAM)NULL);
		ShowWindow(ButtonCommAddWndHndl, SW_SHOW);
		ShowWindow(ButtonCommDelWndHndl, SW_SHOW);
		ShowWindow(ButtonCommChgWndHndl, SW_SHOW);
		ShowWindow(ComListWndHndl, SW_SHOW);
		ShowWindow(ButtonFlagAddWndHndl, SW_HIDE);
		ShowWindow(ButtonFlagDelWndHndl, SW_HIDE);
		ShowWindow(ButtonFlagChgWndHndl, SW_HIDE);
		ShowWindow(ButtonFlagTrueWndHndl, SW_HIDE);
		ShowWindow(ButtonFlagFalseWndHndl, SW_HIDE);
		ShowWindow(FlgListWndHndl, SW_HIDE);
	}
	if (SelVarType == 1) {
		SendMessage(RadioButton1, BM_SETCHECK, BST_UNCHECKED, 0L);
		SendMessage(RadioButton2, BM_SETCHECK, BST_CHECKED, 0L);
		SendMessage(IconWndHndl, STM_SETICON, (WPARAM)IconHndlFlag, (LPARAM)NULL);
		ShowWindow(ButtonCommAddWndHndl, SW_HIDE);
		ShowWindow(ButtonCommDelWndHndl, SW_HIDE);
		ShowWindow(ButtonCommChgWndHndl, SW_HIDE);
		ShowWindow(ComListWndHndl, SW_HIDE);
		ShowWindow(ButtonFlagAddWndHndl, SW_SHOW);
		ShowWindow(ButtonFlagDelWndHndl, SW_SHOW);
		ShowWindow(ButtonFlagChgWndHndl, SW_SHOW);
		ShowWindow(ButtonFlagTrueWndHndl, SW_SHOW);
		ShowWindow(ButtonFlagFalseWndHndl, SW_SHOW);
		ShowWindow(FlgListWndHndl, SW_SHOW);
	}

	return 0;
}

void Var_RefreshVariables()
{
	if (RunFlag == TRUE) {
		ViewData(FALSE);
	}
}

void Var_SetVariableType(int Type)
{
	SelVarType = Type;
	if (RunFlag == TRUE) {
		ChangeRadioButton();
	}
}

// �I������Ă���P�̃A�C�e���̍s�ԍ����擾����
// [in] : LstViwHndl : �Ώۃ��X�g�r���[�̃n���h��
// [out] : �I�����ꂽ�A�C�e���̍s�ԍ��B�����̃A�C�e�����I������Ă���ꍇ -1��ԋp����B
int GetSelectedVlItem(HWND LstViwHndl)
{
	// �I������Ă���A�C�e���̐����擾����
	int ItemCount = 0; // �I������Ă���A�C�e���̐�
	int FndItem = 0; // �I�����ꂽ�A�C�e���̐���1�̏ꍇ�C���̃A�C�e���̔ԍ�
	for (int RowLoop = 0; RowLoop < ListView_GetItemCount(LstViwHndl); RowLoop++) {
		if (ListView_GetItemState(LstViwHndl, RowLoop, LVIS_SELECTED) == LVIS_SELECTED) {
			FndItem = RowLoop;
			ItemCount++;
		}
	}
	if (ItemCount != 1) {
		FndItem = -1;
	}
	return FndItem;
}

// ���X�g�r���[�̕������ڎw�莞�̋��ʏ����i�폜����CTrue����CFalse����ɓK�p�j
// [in] : LstViwHndl: ���X�g�r���[�n���h��
// [in] : Operation (0:FALSE, 1:TRUE, 2:Delete)
void CommonProcedureAboutMultiItemsSelection(HWND LstViwHndl, int Operation)
{
	TCHAR IdBuf[10];
	int FoundCount = 0;
	UINT ret;

	// �Œ�P�ȏ�̍��ڂ��I������Ă��邩�`�F�b�N���C����Ă��Ȃ���΃G���[�𔭐�������
	for (int RowLoop = 0; RowLoop < ListView_GetItemCount(LstViwHndl); RowLoop++) {
		ret = ListView_GetItemState(LstViwHndl, RowLoop, LVIS_SELECTED);
		if (ret == LVIS_SELECTED) {
			FoundCount++;
		}
	}
	if (FoundCount == 0) {
		MessageProc::StkErr(MessageProc::VAR_NOITEMSELECTED, WndHndl);
		return;
	}

	// ���ڂ̍폜����̏ꍇ�C���[�U�[�Ɋm�F�𑣂�
	if (Operation == 2) {
		if (MessageProc::StkYesNo(MessageProc::VAR_AREYOUSUREDELETE, WndHndl) == IDNO) {
			return;
		}
	}

	// �J��Ԃ�����
	for (int RowLoop = 0; RowLoop < ListView_GetItemCount(LstViwHndl); RowLoop++) {
		ret = ListView_GetItemState(LstViwHndl, RowLoop, LVIS_SELECTED);
		if (ret == LVIS_SELECTED) {
			ListView_GetItemText(LstViwHndl, RowLoop, 0, IdBuf, 10);
			int Id = StrToInt(IdBuf);
			if (Operation == 2) {
				VarCon_DeleteVariableRecord(Id);
			} else if (Operation == 0) {
				VarCon_ChangeFlagVariable(Id, FALSE);
			} else if (Operation == 1) {
				VarCon_ChangeFlagVariable(Id, TRUE);
			}
		}
	}

	// �Ō�ɕϐ��ꗗ�\���X�V����
	ViewData(FALSE);
}

// �w�肳�ꂽ"Name"�����"Description"�G�f�B�b�g�{�b�N�X�ɒl��ݒ肷��
// [in] : LstViwHndl : ���擾���̃��X�g�r���[�̃n���h��
// [in] : Row : ���擾���̃��X�g�r���[�̍s�ԍ�
// [in] : OwnerHndl : �I�[�i�[�ƂȂ�_�C�A���O�܂��̓E�B���h�E�̃n���h��
// [in] : NameEbxId : "Name"�G�f�B�b�g�{�b�N�X��ID
// [in] : DescEbxId : "Description"�G�f�B�b�g�{�b�N�X��ID
// [out] : �ύX�ΏۂƂȂ����ϐ���ID��Ԃ�
int SetNameAndDescription(HWND LstViwHndl, int Row, HWND OwnerHndl, int NameEbxId, int DescEbxId)
{
	TCHAR IdBuf[10];
	TCHAR Name[32];
	TCHAR Description[64];

	ListView_GetItemText(LstViwHndl, Row, 0, IdBuf, 10);
	ListView_GetItemText(LstViwHndl, Row, 1, Name, 32);
	ListView_GetItemText(LstViwHndl, Row, 2, Description, 64);
	SetDlgItemText(OwnerHndl, NameEbxId, Name);
	SetDlgItemText(OwnerHndl, DescEbxId, Description);
	int Ret = StrToInt(IdBuf);
	return Ret;
}

// �G�f�B�b�g�{�b�N�X�ɓ��͂��ꂽ����������|�W�g���Ɋi�[����
// [in] : LstViwHndl : ID(�I�����ꂽ�s��ID)�̎擾���ƂȂ郊�X�g�r���[�̃n���h��
// [in] : OwnerHndl : �I�[�i�[�ƂȂ�_�C�A���O�܂��̓E�B���h�E�̃n���h��
// [in] : NameEbxId : "Name"�G�f�B�b�g�{�b�N�X��ID
// [in] : DescEbxId : "Description"�G�f�B�b�g�{�b�N�X��ID
// [in] : Id : ����ΏۂƂȂ�ϐ���ID
// [out] : ����Ώۂ̕ϐ���ID (-1:�i�[�Ɏ��s)
int StoreNameAndDescriptionWithId(HWND LstViwHndl, HWND OwnerHndl, int NameEbxId, int DescEbxId, int Id)
{
	TCHAR Name[32];
	TCHAR Description[64];

	GetDlgItemText(OwnerHndl, NameEbxId, Name, 32);
	GetDlgItemText(OwnerHndl, DescEbxId, Description, 64);
	return VarCon_ChangeNameAndDescription(Id, Name, Description);
}

// �E�B���h�E�^�C�g����ύX����
// [in] : TargetWndHndl : �ύX����E�B���h�E�̃n���h��
// [in] : Id : �E�B���h�E�^�C�g����ɕt�����Ƃ��ĕ\������ϐ���ID�B-1�̂Ƃ��\�����Ȃ�
// [in] : Operation : ���쎯�ʎq (1:Add, 2:Edit)
void ChangeWindowTitle(HWND TargetWndHndl, int Id, int Operation)
{
	TCHAR OrgBuf[128]; // ���̕�����
	TCHAR ChgBuf[128]; // �ύX��̕�����
	TCHAR Ope[16]; // �I�y���[�V������

	GetWindowText(TargetWndHndl, OrgBuf, 128);
	// �I�y���[�V��������ݒ肷��
	if (Operation == 1) {
		lstrcpy(Ope, MessageProc::GetMsg(MessageProc::COMMON_ADD));
	} else if (Operation == 2) {
		lstrcpy(Ope, MessageProc::GetMsg(MessageProc::COMMON_EDIT));
	} else {
		lstrcpy(Ope, MessageProc::GetMsg(MessageProc::COMMON_UNKNOWN));
	}
	// �E�B���h�E�^�C�g���̐ݒ�
	if (Id != -1) {
		wsprintf(ChgBuf, _T("%s %s  (ID=%d)"), Ope, OrgBuf, Id);
	} else {
		wsprintf(ChgBuf, _T("%s %s"), Ope, OrgBuf, Id);
	}
	SetWindowText(TargetWndHndl, ChgBuf);
}

// �ϐ���ǉ�����
// [in] : TargetWndHndl : ���O���́^�������̓G�f�B�b�g�{�b�N�X�̐e�̃n���h��
// [in] : NameId : ���O���̓G�f�B�b�g�{�b�N�X��ID
// [in] : DescId : �������̓G�f�B�b�g�{�b�N�X��ID
// [in] : Type : �ϐ��̎�� (0: �R�~���j�P�[�V�����p�ϐ�, 1:�t���O�p�ϐ�)
// [out] : �ǉ������ϐ���ID�l (-1:�ǉ��Ɏ��s)
int AddVariable(HWND TargetWndHndl, int NameId, int DescId, int Type)
{
	TCHAR Name[32];
	TCHAR Desc[64];

	GetDlgItemText(TargetWndHndl, NameId, Name, 32);
	GetDlgItemText(TargetWndHndl, DescId, Desc, 64);
	return VarCon_AddVariableRecord(Name, Desc, Type);
}

// ���X�g�r���[�̍��ڂ��_�u���N���b�N���ꂽ�Ƃ��̏���
// [in] : ListViewHndl : ���X�g�r���[�̃n���h��
// [in] : lParam : ���b�Z�[�W���f�B�X�p�b�`�����Ƃ���LPARAM�l
// [out] : �_�u���N���b�N���ꂽ���X�g�r���[�̍��ڂ̍s�ԍ���Ԃ� (-1:�_�u���N���b�N�����ӏ����L���͈͊O)
int ListViewDoubleClicked(HWND ListViewHndl, LPARAM lParam)
{
	NMITEMACTIVATE* NmItemActivate = (NMITEMACTIVATE*)lParam;
	if ((NmItemActivate->hdr).code == NM_DBLCLK) {
		int MaxItem = ListView_GetItemCount(ListViewHndl);
		if (NmItemActivate->iSubItem < 0 || NmItemActivate->iSubItem > 5) {
			return -1;
		}
		int ItemNum = NmItemActivate->iItem;
		if (ItemNum < 0 || ItemNum >= MaxItem) {
			return -1;
		}
		return GetSelectedVlItem(ListViewHndl);
	}
	return -1;
}

// �G�f�B�b�g�{�b�N�X�̓��e���R�~���j�P�[�V�����p��Ɨ̈�ɔ��f����
// [in] : EdBxHndl : �ΏۂƂȂ�G�f�B�b�g�{�b�N�X�̃n���h��
// [in] : Type : �G�f�B�b�g�{�b�N�X�̎�� (0:�o�C�i��(16�i��)�o��, 1:�e�L�X�g�o��)
void ReplaceCommVariable(HWND EdBxHndl, int Type)
{
	if (Type == 0) {
	} else if (Type == 1) {
		int ActLen = GetWindowTextLength(EdBxHndl);
		TCHAR* WcBuf = new TCHAR[ActLen + 1];
		GetWindowText(EdBxHndl, WcBuf, ActLen + 1);
		WcBuf[ActLen] = 0;

		WorkDatActSize = WideCharToMultiByte(CP_UTF8, 0, WcBuf, ActLen, (LPSTR)WorkDat, 9999999, NULL, NULL);
		if (ActLen != 0 && WorkDatActSize == 0) {
			MessageProc::StkErr(MessageProc::VAR_BUFOVERFLOW, WndHndl);
			WorkDatActSize = 9999999; // �G���[�����������Ƃ���WorkDat�̓��e���ς��Ȃ����Ƃ����ҁB��荇�������Ȃ������B
		}
		delete WcBuf;
	}
}

// �G�f�B�b�g�{�b�N�X�ɃR�~���j�P�[�V�����p��Ɨ̈���o�͂���
// [in] : EdBxHndl : �o�͂���G�f�B�b�g�{�b�N�X�̃n���h��
// [in] : Type : �o�͌`�� (0:�o�C�i��(16�i��)�o��, 1:�e�L�X�g�o��)
void OutputCommVariable(HWND EdBxHndl, int Type)
{
	if (Type == 1) {
		if (WorkDatActSize == 0) {
			SendMessage(EdBxHndl, EM_SETREADONLY, (WPARAM)FALSE, (LPARAM)0);
			SendMessage(EdBxHndl, WM_SETTEXT, (WPARAM)0, (LPARAM)_T(""));
			RedrawWindow(CommWndHndl, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW | RDW_FRAME | RDW_ALLCHILDREN);
		} else {
			TCHAR* OutDat = new TCHAR[WorkDatActSize * 2 + 1]; // UTF-8�o�͂̕K�v�e�ʂ��m��
			int TransSize = MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, (LPCSTR)WorkDat, WorkDatActSize, OutDat, WorkDatActSize * 2);
			if (TransSize != 0) {
				OutDat[TransSize] = 0;
				SendMessage(EdBxHndl, EM_SETREADONLY, (WPARAM)FALSE, (LPARAM)0);
				SendMessage(EdBxHndl, WM_SETTEXT, (WPARAM)0, (LPARAM)OutDat);
				RedrawWindow(CommWndHndl, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW | RDW_FRAME | RDW_ALLCHILDREN);
			} else {
				MessageProc::StkErr(MessageProc::VAR_NOTTRANSUTF8, WndHndl);
				Type = 0;
				SelOutMode = 0;
				ChangeMenuCheckStatus(0);
			}
			delete OutDat;
		}
	}

	if (Type == 0) {
		int NumOfLine = WorkDatActSize / 32 + 1;
		TCHAR* OutDat = new TCHAR[NumOfLine * 85]; // �o�C�i��(16�i��)�o�͂̕K�v�e�ʂ��m��
		int OrgCurPtr = 0;
		TCHAR* OutCurPtr = OutDat;
		for (int CurLine = 0; CurLine < NumOfLine; CurLine++) {
			wsprintf((LPTSTR)OutCurPtr, _T("%06x:"), CurLine * 32);
			OutCurPtr += 7;
			int EndPtr = OrgCurPtr + 32;
			if (EndPtr >= WorkDatActSize) {
				EndPtr = WorkDatActSize;
			}
			for (int LoopSect = OrgCurPtr; LoopSect < EndPtr; LoopSect++) {
				if (LoopSect % 4 == 0) {
					wsprintf(OutCurPtr, _T(" "));
					OutCurPtr++;
				}
				wsprintf(OutCurPtr, _T("%02x"), WorkDat[OrgCurPtr]);
				OrgCurPtr++;
				OutCurPtr += 2;
			}
			wsprintf((LPTSTR)OutCurPtr, _T("\r\n"));
			OutCurPtr += 2;
		}
		OutCurPtr = NULL;
		SendMessage(EdBxHndl, EM_SETREADONLY, (WPARAM)TRUE, (LPARAM)0);
		SendMessage(EdBxHndl, WM_SETTEXT, (WPARAM)0, (LPARAM)OutDat);
		RedrawWindow(CommWndHndl, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW | RDW_FRAME | RDW_ALLCHILDREN);
		delete OutDat;
	}
}

// �t�@�C���I���_�C�A���O�Ŏw�肵���t�@�C�����G�f�B�b�g�{�b�N�X�ɓǍ���
// [in] WinHndl : �t�@�C���I���_�C�A���O�̐e�ƂȂ�E�B���h�E�̃n���h��
// [out] int : Result code (0: Sucess, -1: Error)
int OpenFileX(HWND WinHndl)
{
	TCHAR InitPath[MAX_PATH];
	GetCurrentDirectory(sizeof(InitPath), InitPath);

	TCHAR File[32768] = _T("");
	File[0] = 0;
	TCHAR Title[256] = _T("");
	OPENFILENAME Ofn;
	ZeroMemory(&Ofn, sizeof(OPENFILENAME));
	Ofn.lStructSize = sizeof(OPENFILENAME);
	Ofn.hwndOwner = WinHndl;
	Ofn.lpstrFile = File;
	Ofn.nMaxFile = 300;
	Ofn.lpstrFileTitle =Title;
	Ofn.nMaxFileTitle = 300;
	Ofn.lpstrInitialDir = InitPath;
	Ofn.lpstrFilter = _T("Import file(*.*)\0*.*\0\0");
	Ofn.lpstrTitle = _T("Select import file [Open]");
	Ofn.Flags = OFN_FILEMUSTEXIST | OFN_HIDEREADONLY | OFN_NOCHANGEDIR;
	if (GetOpenFileName(&Ofn) == 0) {
		return 0;
	}

	HANDLE FileHndl = CreateFile(File, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (FileHndl == INVALID_HANDLE_VALUE) {
		return -1;
	};

	//�t�@�C���T�C�Y���`�F�b�N����
	DWORD HighSize = 0;
	DWORD LowSize = 0;
	LowSize = GetFileSize(FileHndl, &HighSize);
	if (HighSize != 0 || LowSize >= 10000000) {
		MessageProc::StkErr(MessageProc::VAR_BUFOVERFLOW, WndHndl);
	}

	SetFilePointer(FileHndl, NULL, NULL, FILE_BEGIN);
	DWORD TmpSize = 0;
	if (ReadFile(FileHndl, (LPVOID)WorkDat, 9999999, &TmpSize, NULL) == 0) {
		CloseHandle(FileHndl);
		return -1;
	}
	WorkDatActSize = (int)TmpSize;
	CloseHandle(FileHndl);

	SelOutMode = 0;
	ChangeMenuCheckStatus(0);
	OutputCommVariable(CommEdit, 0);

	return 0;
}

// �G�f�B�b�g�{�b�N�X�̓��e���t�@�C���I���_�C�A���O�Ŏw�肵���t�@�C���ɏ�������
// [in] WinHndl : �t�@�C���I���_�C�A���O�̐e�ƂȂ�E�B���h�E�̃n���h��
// [out] int : Result code (0: Sucess, -1: Error)
int SaveFileX(HWND WinHndl)
{
	TCHAR InitPath[MAX_PATH];
	GetCurrentDirectory(sizeof(InitPath), InitPath);

	TCHAR File[32768] = _T("");
	File[0] = 0;
	TCHAR Title[256] = _T("");
	OPENFILENAME Ofn;
	ZeroMemory(&Ofn, sizeof(OPENFILENAME));
	Ofn.lStructSize = sizeof(OPENFILENAME);
	Ofn.hwndOwner = WinHndl;
	Ofn.lpstrFile = File;
	Ofn.nMaxFile = 300;
	Ofn.lpstrFileTitle =Title;
	Ofn.nMaxFileTitle = 300;
	Ofn.lpstrDefExt = NULL;
	Ofn.lpstrInitialDir = InitPath;
	Ofn.lpstrFilter = _T("Export file(*.*)\0*.*\0\0");
	Ofn.lpstrTitle = _T("Select export file [Save]");
	Ofn.Flags = OFN_NOCHANGEDIR;
	if (GetSaveFileName(&Ofn) == 0) {
		return 0;
	}

	if (SelOutMode == 1) {
		ReplaceCommVariable(CommEdit, 1);
	}
	HANDLE FileHndl = CreateFile(File, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (FileHndl == INVALID_HANDLE_VALUE) {
		return -1;
	};
	DWORD TmpSize = 0;
	if (WriteFile(FileHndl, (LPCVOID)WorkDat, WorkDatActSize, &TmpSize, NULL) == 0) {
		CloseHandle(FileHndl);
		return -1;
	}
	CloseHandle(FileHndl);

	return 0;
}


// Return: (TRUE: Success, FALSE: Other)
BOOL VarConEdit_SelectFolder(TCHAR* FolderPath)
{
	LPITEMIDLIST PidlBrowse;
	BROWSEINFO Browse;
	Browse.hwndOwner = WndHndl;
	Browse.pidlRoot = NULL;
	Browse.pszDisplayName = FolderPath;
	Browse.lpszTitle = _T("Select folder");
	Browse.ulFlags = 0;
	Browse.lpfn = 0;
	Browse.lParam = 0;
    PidlBrowse = SHBrowseForFolder(&Browse);
	if (PidlBrowse != NULL) {
		if (SHGetPathFromIDList(PidlBrowse, FolderPath) == FALSE) {
			MessageProc::StkErr(MessageProc::VAR_FOLDERSETERR, WndHndl);
			return FALSE;
		}
	} else {
		return FALSE;
	}
	return TRUE;
}

void VarConEdit_Export(HWND LstViwHndl)
{
	// �t���O�p�ϐ��Ȃ�Ώ������I����
	if (SelVarType == 1) {
		MessageProc::StkErr(MessageProc::VAR_FLAGVARNOT, WndHndl);
		return;
	}

	// �t�H���_�w��_�C�A���O���J��
	TCHAR ExportPath[MAX_PATH];
	if (VarConEdit_SelectFolder(ExportPath) == FALSE) {
		return;
	}

	int SelCnt = 0;
	TCHAR IdBuf[10];
	for (int RowLoop = 0; RowLoop < ListView_GetItemCount(LstViwHndl); RowLoop++) {
		if (ListView_GetItemState(LstViwHndl, RowLoop, LVIS_SELECTED) == LVIS_SELECTED) {
			ListView_GetItemText(LstViwHndl, RowLoop, 0, IdBuf, 10);
			int Id = StrToInt(IdBuf);

			// Name��Description�̎擾
			TCHAR Name[32];
			TCHAR Desc[64];
			VarCon_GetVariableNameAndDesc(Id, Name, Desc);

			// �R�~���j�P�[�V�����p�ϐ��i�[�̈�̐���
			int CommDatLength = VarCon_GetCommunicationVariableSize(Id);
			BYTE* CommDat = new BYTE[CommDatLength + 1];
			VarCon_GetCommunicationVariable(Id, CommDat, CommDatLength);

			// �t�@�C������
			TCHAR TmpPath[MAX_PATH];
			lstrcpy(TmpPath, ExportPath);
			lstrcat(TmpPath, _T("\\"));
			lstrcat(TmpPath, Name);
			lstrcat(TmpPath, _T(".xxx"));
			HANDLE FileHndl = CreateFile(TmpPath, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
			if (FileHndl == INVALID_HANDLE_VALUE) {
				MessageProc::StkErr(MessageProc::VAR_EXPERR, TmpPath, WndHndl);
				delete CommDat;
				return;
			};
			DWORD TmpSize = 0;
			if (WriteFile(FileHndl, (LPCVOID)CommDat, CommDatLength, &TmpSize, NULL) == 0) {
				MessageProc::StkErr(MessageProc::VAR_EXPERR, TmpPath, WndHndl);
				CloseHandle(FileHndl);
				delete CommDat;
				return;
			}
			CloseHandle(FileHndl);
			delete CommDat;
			SelCnt++;
		}
	}
	if (SelCnt == 0) {
		MessageProc::StkErr(MessageProc::VAR_NOEXPTARGET, WndHndl);
	}
}

void VarConEdit_Import()
{
	// �t���O�p�ϐ��Ȃ�Ώ������I����
	if (SelVarType == 1) {
		MessageProc::StkErr(MessageProc::VAR_FLAGVARNOT, WndHndl);
		return;
	}

	// �t�H���_�w��_�C�A���O���J��
	TCHAR ImportPath[MAX_PATH];
	if (VarConEdit_SelectFolder(ImportPath) == FALSE) {
		return;
	}

	TCHAR TmpPath[MAX_PATH];
	lstrcpy(TmpPath, ImportPath);
	lstrcat(TmpPath, _T("\\*.xxx"));
	WIN32_FIND_DATAW Fd;
	HANDLE FileNameHndl = FindFirstFileW(TmpPath, &Fd);
	if (FileNameHndl == INVALID_HANDLE_VALUE) {
		MessageProc::StkErr(MessageProc::VAR_NOIMPTARGET, WndHndl);
		return;
	}
	do {
		// �w�肳�ꂽ�t�H���_�ɑ��݂���.xxx�t�@�C���̖��̂��擾����
		TCHAR TmpFileName[MAX_PATH];
		lstrcpy(TmpFileName, Fd.cFileName);
		lstrcpy(TmpPath, ImportPath);
		lstrcat(TmpPath, _T("\\"));
		lstrcat(TmpPath, TmpFileName);

		// �R�~���j�P�[�V�����p�ϐ������擾����
		TCHAR VarName[50];
		lstrcpyn(VarName, TmpFileName, 36); //�g���q�܂�
		VarName[lstrlen(VarName) - 4] = 0;

		// �t�@�C����ǂݍ���
		HANDLE FileHndl = CreateFile(TmpPath, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		if (FileHndl == INVALID_HANDLE_VALUE) {
			MessageProc::StkErr(MessageProc::VAR_IMPERR, TmpPath, WndHndl);
			FindClose(FileNameHndl);
			return ;
		};
		DWORD HighSize = 0;
		DWORD LowSize = 0;
		LowSize = GetFileSize(FileHndl, &HighSize);
		if (HighSize != 0 || LowSize >= 10000000) {
			MessageProc::StkErr(MessageProc::VAR_BUFOVERFLOW, WndHndl);
			LowSize = 9999999;
		}
		BYTE* CommDat = new BYTE[LowSize + 10000]; // 10000�����Z���闝�R�́CVarCon_UpdateCommunicationVariable��10000�o�C�g���̏������݂��s������
		SetFilePointer(FileHndl, NULL, NULL, FILE_BEGIN);
		DWORD TmpSize = 0;
		if (ReadFile(FileHndl, (LPVOID)CommDat, LowSize, &TmpSize, NULL) == 0) {
			MessageProc::StkErr(MessageProc::VAR_IMPERR, TmpPath, WndHndl);
			CloseHandle(FileHndl);
			delete CommDat;
			FindClose(FileNameHndl);
			return;
		}
		CloseHandle(FileHndl);

		if (VarCon_CheckCommunicationVariableSize(LowSize) == FALSE || VarCon_CheckVariableCount() == FALSE) {
			MessageProc::StkErr(MessageProc::VAR_MAXVARSIZE, WndHndl);
			delete CommDat;
			FindClose(FileNameHndl);
			return;
		}
		int NewId = VarCon_AddVariableRecord(VarName, _T(""), 0);
		VarCon_UpdateCommunicationVariable(NewId, CommDat, LowSize);
		delete CommDat;
	} while (FindNextFile(FileNameHndl, &Fd));
	FindClose(FileNameHndl);
}

/****************************************************************************/
// �t���O�p�ϐ��ݒ�_�C�A���O�{�b�N�X
LRESULT CALLBACK FlagDlg(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	int WmId    = LOWORD(wParam); 
	int WmEvent = HIWORD(wParam);

	if (message == WM_CREATE) {
		EnumChildWindows(hDlg, SetFontProc, NULL);
		return TRUE;
	}
	if (message == WM_COMMAND) {
		if (HIWORD(wParam) == BN_CLICKED) {
			// OK�{�^���������ꂽ�Ƃ�
			if (LOWORD(wParam) == IDC_VARFLAGBTNOK) {
				if (OpType == 1) {
					if (VarCon_CheckCommunicationVariableSize(-1) == FALSE || VarCon_CheckVariableCount() == FALSE) {
						MessageProc::StkErr(MessageProc::VAR_MAXVARSIZE, WndHndl);
						return TRUE;
					}
					if (AddVariable(hDlg, IDC_VARFLAGNAMEEDIT, IDC_VARFLAGDESCEDIT, 1) == -1) {
						MessageProc::StkErr(MessageProc::VAR_INVALIDNAME, WndHndl);
						return TRUE;
					}
					EnableWindow(WndHndl, TRUE);
					DestroyWindow(hDlg);
					ViewData(FALSE);
					return TRUE;
				} else if (OpType == 2) {
					RecordData* ChkRec = VarCon_GetVariableRecord(SelVarId);
					if (ChkRec == NULL) {
						MessageProc::StkErr(MessageProc::VAR_ALREADYDELETED, WndHndl);
						return TRUE;
					}
					if (((ColumnDataInt*)ChkRec->GetColumn(3))->GetValue() != 1) {
						MessageProc::StkErr(MessageProc::VAR_INVALIDTYPE, WndHndl);
						return TRUE;
					}
					ClearRecordData(ChkRec);
					if (StoreNameAndDescriptionWithId(FlgListWndHndl, hDlg, IDC_VARFLAGNAMEEDIT, IDC_VARFLAGDESCEDIT, SelVarId) == -1) {
						MessageProc::StkErr(MessageProc::VAR_INVALIDNAME, WndHndl);
						return TRUE;
					}
					EnableWindow(WndHndl, TRUE);
					DestroyWindow(hDlg);
					ViewData(FALSE);
					return TRUE;
				}
			}
			// Cancel�{�^���������ꂽ�Ƃ�
			if (LOWORD(wParam) == IDC_VARFLAGBTNCANCEL) {
				EnableWindow(WndHndl, TRUE);
				DestroyWindow(hDlg);
				return TRUE;
			}
		}
	}

	if (message == WM_CLOSE) {
		EnableWindow(WndHndl, TRUE);
		DestroyWindow(hDlg);
	}

	// Initialize dialog
	if (message == WM_INITDIALOG) {
		return TRUE;
	}

	return FALSE;
}

/****************************************************************************/
// �R�~���j�P�[�V�����p�ϐ��ݒ�_�C�A���O�{�b�N�X
LRESULT CALLBACK CommProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	RECT Wrect;

	switch (message) {
	case WM_CREATE:
		InitCommonControls();

		CommBkGndWndHndl = CreateWindow(_T("STATIC"), _T(""), WS_CHILD | WS_VISIBLE, 0, 0, 0, 0, hWnd, NULL, InstHndl, NULL);
		CommStName       = CreateWindow(_T("STATIC"), _T("Name"), WS_CHILD | WS_VISIBLE, 50, 11, 100, 20, CommBkGndWndHndl, NULL, InstHndl, NULL);
		CommStDesc       = CreateWindow(_T("STATIC"), _T("Description"), WS_CHILD | WS_VISIBLE, 50, 46, 100, 20, CommBkGndWndHndl, NULL, InstHndl, NULL);
		CommEdName       = CreateWindowEx(WS_EX_CLIENTEDGE, _T("EDIT"), _T(""), WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL, 0, 0, 0, 0, CommBkGndWndHndl, (HMENU)IDC_VARCOMMNAMEEDIT, InstHndl, NULL);
		CommEdDesc       = CreateWindowEx(WS_EX_CLIENTEDGE, _T("EDIT"), _T(""), WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL, 0, 0, 0, 0, CommBkGndWndHndl, (HMENU)IDC_VARCOMMDESCEDIT, InstHndl, NULL);
		CommEdit         = CreateWindowEx(WS_EX_CLIENTEDGE, _T("EDIT"), _T(""), WS_CHILD | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL | ES_AUTOHSCROLL | ES_AUTOVSCROLL | ES_MULTILINE, 0, 0, 0, 0, hWnd, NULL, InstHndl, NULL);
		CommIconWndHndl  = CreateWindow(_T("STATIC"), _T(""), WS_CHILD | WS_VISIBLE | SS_ICON, 10, 7, 32, 32, hWnd, NULL, InstHndl, NULL);
		CommButtonOK     = CreateWindow(_T("BUTTON"), MessageProc::GetMsg(MessageProc::COMMON_OK), WS_CHILD | WS_VISIBLE, 0, 0, 0, 0, hWnd, (HMENU)IDC_VARCOMMBTNOK, InstHndl, NULL);
		CommButtonCancel = CreateWindow(_T("BUTTON"), MessageProc::GetMsg(MessageProc::COMMON_CANCEL), WS_CHILD | WS_VISIBLE, 0, 0, 0, 0, hWnd, (HMENU)IDC_VARCOMMBTNCANCEL, InstHndl, NULL);

		SendMessage(CommIconWndHndl, STM_SETICON, (WPARAM)LoadImage(InstHndl, MAKEINTRESOURCE(IDI_VARICON5), IMAGE_ICON, 32, 32, LR_DEFAULTCOLOR), (LPARAM)NULL);

		EnumChildWindows(hWnd, SetFontProc, NULL);
		SetFontCourier(CommEdit);

		if (OpType != 1) {
			TCHAR IdBuf[10];
			ListView_GetItemText(ComListWndHndl, GetSelectedVlItem(ComListWndHndl), 0, IdBuf, 10);
			SelVarId = StrToInt(IdBuf);
			WorkDatActSize = VarCon_GetCommunicationVariableSize(SelVarId);
			VarCon_GetCommunicationVariable(SelVarId, WorkDat, WorkDatActSize);
		} else {
			WorkDatActSize = 0;
		}

		break;
	case WM_SIZE:
		GetClientRect(hWnd, &Wrect);
		MoveWindow(CommBkGndWndHndl, 0, 0, Wrect.right, Wrect.bottom, TRUE);
		MoveWindow(CommEdName, 160, 7, Wrect.right - 350, 26, TRUE);
		MoveWindow(CommEdDesc, 160, 43, Wrect.right - 170, 26, TRUE);
		MoveWindow(CommButtonOK, Wrect.right - 170, 6, 70, 25, TRUE);
		MoveWindow(CommButtonCancel, Wrect.right - 90, 6, 70, 25, TRUE);
		MoveWindow(CommEdit, 4, 80, Wrect.right - 8, Wrect.bottom - 84, TRUE);
		break;
	case WM_GETMINMAXINFO:
		SetMinWindowSize(lParam);
		break;
	case WM_COMMAND:
		if (HIWORD(wParam) == BN_CLICKED) {
			if (LOWORD(wParam) == ID_VARVIEW_BINARY) {
				if (SelOutMode == 1) {
					ReplaceCommVariable(CommEdit, 1);
				}
				SelOutMode = 0;
				ChangeMenuCheckStatus(0);
				OutputCommVariable(CommEdit, 0);
				break;
			}
			if (LOWORD(wParam) == ID_VARVIEW_UTF8) {
				SelOutMode = 1;
				ChangeMenuCheckStatus(1);
				OutputCommVariable(CommEdit, 1);
				break;
			}
			// OK�{�^���������ꂽ�Ƃ�
			if (LOWORD(wParam) == IDC_VARCOMMBTNOK) {
				if (OpType == 1) {
					ReplaceCommVariable(CommEdit, SelOutMode);
					if (VarCon_CheckCommunicationVariableSize(WorkDatActSize) == FALSE || VarCon_CheckVariableCount() == FALSE) {
						MessageProc::StkErr(MessageProc::VAR_MAXVARSIZE, WndHndl);
						return TRUE;
					}
					int New = AddVariable(CommBkGndWndHndl, IDC_VARCOMMNAMEEDIT, IDC_VARCOMMDESCEDIT, 0);
					if (New == -1) {
						MessageProc::StkErr(MessageProc::VAR_INVALIDNAME, WndHndl);
						return TRUE;
					}
					VarCon_UpdateCommunicationVariable(New, WorkDat, WorkDatActSize);
					EnableWindow(WndHndl, TRUE);
					DestroyWindow(hWnd);
					ViewData(FALSE);
					break;
				} else if (OpType == 2) {
					RecordData* ChkRec = VarCon_GetVariableRecord(SelVarId);
					if (ChkRec == NULL) {
						MessageProc::StkErr(MessageProc::VAR_ALREADYDELETED, WndHndl);
						return TRUE;
					}
					if (((ColumnDataInt*)ChkRec->GetColumn(3))->GetValue() != 0) {
						MessageProc::StkErr(MessageProc::VAR_INVALIDTYPE, WndHndl);
						return TRUE;
					}
					ClearRecordData(ChkRec);
					if (StoreNameAndDescriptionWithId(ComListWndHndl, CommBkGndWndHndl, IDC_VARCOMMNAMEEDIT, IDC_VARCOMMDESCEDIT, SelVarId) == -1) {
						MessageProc::StkErr(MessageProc::VAR_INVALIDNAME, WndHndl);
						return TRUE;
					}
					int PrevPlaneCnt = VarCon_GetCommunicationVariableSize(SelVarId) / 10000;
					ReplaceCommVariable(CommEdit, SelOutMode);
					int CurrPlaneCnt = WorkDatActSize / 10000;
					int AddSize = (CurrPlaneCnt - PrevPlaneCnt) * 1000;
					if (VarCon_CheckCommunicationVariableSize((AddSize > 0) ? AddSize : -1) == FALSE) {
						MessageProc::StkErr(MessageProc::VAR_MAXVARSIZE, WndHndl);
						return TRUE;
					}
					VarCon_UpdateCommunicationVariable(SelVarId, WorkDat, WorkDatActSize);
					EnableWindow(WndHndl, TRUE);
					DestroyWindow(hWnd);
					ViewData(FALSE);
					break;
				}
			}
			// Cancel�{�^���������ꂽ�Ƃ�
			if (LOWORD(wParam) == IDC_VARCOMMBTNCANCEL) {
				EnableWindow(WndHndl, TRUE);
				DestroyWindow(hWnd);
				// ViewData(FALSE); // ##10085
				break;
			}
			// Close���j���[���I�����ꂽ�Ƃ�
			if (LOWORD(wParam) == ID_VARFILE_CLOSEX) {
				EnableWindow(WndHndl, TRUE);
				DestroyWindow(hWnd);
				// ViewData(FALSE); // ##10085
				break;
			}
			// Open���j���[���I�����ꂽ�Ƃ�
			if (LOWORD(wParam) == ID_VARFILE_OPENX) {
				if (OpenFileX(WndHndl) == -1) {
					MessageProc::StkErr(MessageProc::FILEACCESSERROR, WndHndl);
				}
				break;
			}
			// Save���j���[���I�����ꂽ�Ƃ�
			if (LOWORD(wParam) == ID_VARFILE_SAVEX) {
				if (SaveFileX(WndHndl) == -1) {
					MessageProc::StkErr(MessageProc::FILEACCESSERROR, WndHndl);
				}
				break;
			}
		}
		return DefWindowProc(hWnd, message, wParam, lParam);
	case WM_CLOSE:
		EnableWindow(WndHndl, TRUE);
		DestroyWindow(hWnd);
		// ViewData(FALSE); // ##10085
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

/****************************************************************************/
// �ϐ��ꗗ�_�C�A���O�{�b�N�X
LRESULT CALLBACK VarConWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	RECT Wrect;

	switch (message) {
	case WM_CREATE:
		InitCommonControls();

		BkGndWndHndl  = CreateWindow(_T("STATIC"), _T(""), WS_CHILD | WS_VISIBLE, 0, 0, 0, 0, hWnd, NULL, InstHndl, NULL);
		BtmGndWndHndl = CreateWindow(_T("STATIC"), _T(""), WS_CHILD | WS_VISIBLE | WS_DLGFRAME, 0, 0, 0, 0, hWnd, NULL, InstHndl, NULL);
		TextWndHndl   = CreateWindow(_T("STATIC"), _T("variables"), WS_CHILD | WS_VISIBLE, 50, 8, 100, 20, hWnd, NULL, InstHndl, NULL);
		IconWndHndl   = CreateWindow(_T("STATIC"), _T(""), WS_CHILD | WS_VISIBLE | SS_ICON, 10, 0, 32, 32, hWnd, NULL, InstHndl, NULL);
		RadioButton1 = CreateWindow(_T("BUTTON"), _T("Communication"), WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON , 0, 0, 0, 0, hWnd, (HMENU)IDC_VARRADIO_COMM, InstHndl, NULL);
		RadioButton2 = CreateWindow(_T("BUTTON"), _T("Flag"), WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON , 0, 0, 0, 0, hWnd, (HMENU)IDC_VARRADIO_FLAG, InstHndl, NULL);
		ButtonRefWndHndl = CreateWindow(_T("BUTTON"), MessageProc::GetMsg(MessageProc::COMMON_REFRESH), WS_CHILD | WS_VISIBLE, 0, 0, 0, 0, hWnd, (HMENU)IDC_VARREFRESH, InstHndl, NULL);

		// Button of communication
		ButtonCommAddWndHndl   = CreateWindow(_T("BUTTON"), MessageProc::GetMsg(MessageProc::COMMON_ADD), WS_CHILD | WS_VISIBLE, 0, 0, 0, 0, hWnd, (HMENU)IDC_VARCOMMADDBUTTON, InstHndl, NULL);
		ButtonCommDelWndHndl   = CreateWindow(_T("BUTTON"), MessageProc::GetMsg(MessageProc::COMMON_DELETE), WS_CHILD | WS_VISIBLE, 0, 0, 0, 0, hWnd, (HMENU)IDC_VARCOMMDELBUTTON, InstHndl, NULL);
		ButtonCommChgWndHndl   = CreateWindow(_T("BUTTON"), MessageProc::GetMsg(MessageProc::COMMON_EDIT), WS_CHILD | WS_VISIBLE, 0, 0, 0, 0, hWnd, (HMENU)IDC_VARCOMMEDITBUTTON, InstHndl, NULL);

		// Button of flag
		ButtonFlagAddWndHndl   = CreateWindow(_T("BUTTON"), MessageProc::GetMsg(MessageProc::COMMON_ADD), WS_CHILD | WS_VISIBLE, 0, 0, 0, 0, hWnd, (HMENU)IDC_VARFLAGADDBUTTON, InstHndl, NULL);
		ButtonFlagDelWndHndl   = CreateWindow(_T("BUTTON"), MessageProc::GetMsg(MessageProc::COMMON_DELETE), WS_CHILD | WS_VISIBLE, 0, 0, 0, 0, hWnd, (HMENU)IDC_VARFLAGDELBUTTON, InstHndl, NULL);
		ButtonFlagChgWndHndl   = CreateWindow(_T("BUTTON"), MessageProc::GetMsg(MessageProc::COMMON_EDIT), WS_CHILD | WS_VISIBLE, 0, 0, 0, 0, hWnd, (HMENU)IDC_VARFLAGEDITBUTTON, InstHndl, NULL);
		ButtonFlagTrueWndHndl  = CreateWindow(_T("BUTTON"), MessageProc::GetMsg(MessageProc::COMMON_TRUE), WS_CHILD | WS_VISIBLE, 0, 0, 0, 0, hWnd, (HMENU)IDC_VARFLAGTRUE, InstHndl, NULL);
		ButtonFlagFalseWndHndl = CreateWindow(_T("BUTTON"), MessageProc::GetMsg(MessageProc::COMMON_FALSE), WS_CHILD | WS_VISIBLE, 0, 0, 0, 0, hWnd, (HMENU)IDC_VARFLAGFALSE, InstHndl, NULL);

		// ���X�g�r���[���쐬����
		ComListWndHndl = CreateWindowEx(0, WC_LISTVIEW, _T(""), WS_CHILD | WS_VISIBLE | LVS_REPORT | LVS_SHOWSELALWAYS, 0, 0, 0, 0, hWnd, (HMENU)IDC_VARCOMMLV, InstHndl, NULL);
		ListView_SetExtendedListViewStyle(ComListWndHndl, LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
		FlgListWndHndl = CreateWindowEx(0, WC_LISTVIEW, _T(""), WS_CHILD | WS_VISIBLE | LVS_REPORT | LVS_SHOWSELALWAYS, 0, 0, 0, 0, hWnd, (HMENU)IDC_VARFLAGLV, InstHndl, NULL);
		ListView_SetExtendedListViewStyle(FlgListWndHndl, LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

		// ���X�g�r���[�̃A�C�e���̍����𒲐߂���
		{
			HIMAGELIST ImLstHndl = ImageList_Create(1, 20, ILC_COLOR8 | ILC_MASK, 1, 0);
			ImageList_AddIcon(ImLstHndl, LoadIcon(InstHndl,  MAKEINTRESOURCE(IDI_VARICON2)));
			ListView_SetImageList(ComListWndHndl, ImLstHndl, LVSIL_SMALL);
			ListView_SetImageList(FlgListWndHndl, ImLstHndl, LVSIL_SMALL);
		}

		ChangeRadioButton();

		EnumChildWindows(hWnd, SetFontProc, NULL);

		ViewData(TRUE);

		WorkDat = new BYTE[10000000]; // ��Ɨ̈�m��

		break;
	case WM_CLOSE:
		DestroyWindow(hWnd);
		break;
	case WM_SIZE:
		GetClientRect(WndHndl, &Wrect);
		MoveWindow(BkGndWndHndl, 0, 0, Wrect.right, 32, TRUE);
		MoveWindow(BtmGndWndHndl, 0, Wrect.bottom - 70, Wrect.right, 70, TRUE);
		MoveWindow(ComListWndHndl, 0, 32, Wrect.right, Wrect.bottom - 102, TRUE);
		MoveWindow(FlgListWndHndl, 0, 32, Wrect.right, Wrect.bottom - 102, TRUE);
		MoveWindow(RadioButton1, Wrect.right - 230, 8, 150, 20, TRUE);
		MoveWindow(RadioButton2, Wrect.right - 80, 8, 80, 20, TRUE);
		MoveWindow(ButtonRefWndHndl, 20, Wrect.bottom - 50, 80, 30, TRUE);
		MoveWindow(ButtonCommAddWndHndl, Wrect.right - 230,  Wrect.bottom - 50, 70, 30, TRUE);
		MoveWindow(ButtonCommDelWndHndl, Wrect.right - 160,  Wrect.bottom - 50, 70, 30, TRUE);
		MoveWindow(ButtonCommChgWndHndl, Wrect.right - 90, Wrect.bottom - 50, 70, 30, TRUE);
		MoveWindow(ButtonFlagAddWndHndl, Wrect.right - 380,  Wrect.bottom - 50, 70, 30, TRUE);
		MoveWindow(ButtonFlagDelWndHndl, Wrect.right - 310,  Wrect.bottom - 50, 70, 30, TRUE);
		MoveWindow(ButtonFlagChgWndHndl, Wrect.right - 240,  Wrect.bottom - 50, 70, 30, TRUE);
		MoveWindow(ButtonFlagTrueWndHndl, Wrect.right - 160, Wrect.bottom - 50, 70, 30, TRUE);
		MoveWindow(ButtonFlagFalseWndHndl, Wrect.right - 90, Wrect.bottom - 50, 70, 30, TRUE);
		break;
	case WM_GETMINMAXINFO:
		SetMinWindowSize(lParam);
		break;
	case WM_NOTIFY:
		if (wParam == IDC_VARCOMMLV) {
			if (ListViewDoubleClicked(ComListWndHndl, lParam) != -1) {
				goto COMMEDIT;
			}
			break;
		} else if (wParam == IDC_VARFLAGLV) {
			int SelItem = ListViewDoubleClicked(FlgListWndHndl, lParam);
			if (SelItem != -1) {
				TCHAR Flag[10];
				ListView_GetItemText(FlgListWndHndl, SelItem, 3, Flag, 10);
				if (lstrcmp(Flag, _T("True")) == 0) {
					CommonProcedureAboutMultiItemsSelection(FlgListWndHndl, 0);
				} else {
					CommonProcedureAboutMultiItemsSelection(FlgListWndHndl, 1);
				}
			}
			break;
		}
		return DefWindowProc(hWnd, message, wParam, lParam);
	case WM_COMMAND:
		if (LOWORD(wParam) == ID_VARCON_COPY) {
			VarConEdit_Export(ComListWndHndl);
		}
		if (LOWORD(wParam) == ID_VARCON_PASTE) {
			VarConEdit_Import();
			ViewData(FALSE);
		}
		if (HIWORD(wParam) == BN_CLICKED) {
			if (LOWORD(wParam) == IDC_VARRADIO_COMM) {
				SelVarType = 0;
				ChangeRadioButton();
				break;
			} else if (LOWORD(wParam) == IDC_VARRADIO_FLAG) {
				SelVarType = 1;
				ChangeRadioButton();
				break;
			} else if (LOWORD(wParam) == IDC_VARREFRESH) {
				ViewData(FALSE);
				break;
			} else if (LOWORD(wParam) == IDC_VARFLAGADDBUTTON) {
				OpType = 1;
				// �t���O�p�ϐ��ݒ�_�C�A���O���N������
				FlagDlgHndl = CreateDialog(InstHndl, MAKEINTRESOURCE(IDD_VARFLAGDLG), hWnd, (DLGPROC)FlagDlg);
				SetIconToWnd(FlagDlgHndl);
				ShowWindow(FlagDlgHndl, SW_SHOW);
				EnableWindow(WndHndl, FALSE);
				// �E�B���h�E�^�C�g����ύX����
				ChangeWindowTitle(FlagDlgHndl, -1, 1);
				break;
			} else if (LOWORD(wParam) == IDC_VARCOMMADDBUTTON) {
				OpType = 1;
				SelOutMode = 0;
				// �R�~���j�P�[�V�����p�ϐ��ݒ�E�B���h�E���N������
				RECT WndRect;
				GetWindowRect(WndHndl, &WndRect);
				CommWndHndl = CreateWindow(_T("Communication"), _T("communication variable"), WS_CAPTION | WS_SYSMENU | WS_DLGFRAME | WS_MAXIMIZEBOX | WS_MINIMIZEBOX | WS_SYSMENU | WS_SIZEBOX, CW_USEDEFAULT, CW_USEDEFAULT, 770, 450, WndHndl, NULL, InstHndl, NULL);
				SendMessage(CommEdit, EM_SETLIMITTEXT, (WPARAM)0, (LPARAM)0);
				SetIconToWnd(CommWndHndl);
				ShowWindow(CommWndHndl, SW_SHOW);
				EnableWindow(WndHndl, FALSE);
				// �E�B���h�E�^�C�g����ύX����
				ChangeWindowTitle(CommWndHndl, -1, 1);
				// ���j���[�`�F�b�N
				ChangeMenuCheckStatus(0);
				// �G�f�B�b�g�{�b�N�X�̍X�V
				OutputCommVariable(CommEdit, 0);
				break;
			} else if (LOWORD(wParam) == IDC_VARFLAGEDITBUTTON) {
				OpType = 2;
				// �I������Ă���P�̃A�C�e���̍s�ԍ����擾����
				int SelItem = GetSelectedVlItem(FlgListWndHndl);
				if (SelItem == -1) {
					MessageProc::StkErr(MessageProc::VAR_SELECTEDNOTONE, hWnd);
					break;
				}
				// �Ώۂ̕ϐ������|�W�g���ɑ��݂��邩�m�F����
				if (VarCon_CheckVariableExistence(GetSelectedVariableId(FlgListWndHndl, SelItem)) == FALSE) {
					MessageProc::StkErr(MessageProc::VAR_ALREADYDELETED, WndHndl);
					break;
				}
				// �t���O�p�ϐ��ݒ�_�C�A���O���N������
				FlagDlgHndl = CreateDialog(InstHndl, MAKEINTRESOURCE(IDD_VARFLAGDLG), hWnd, (DLGPROC)FlagDlg);
				SetIconToWnd(FlagDlgHndl);
				ShowWindow(FlagDlgHndl, SW_SHOW);
				EnableWindow(WndHndl, FALSE);
				// "Name"��"Description"�̐ݒ�
				SelVarId = SetNameAndDescription(FlgListWndHndl, SelItem, FlagDlgHndl, IDC_VARFLAGNAMEEDIT, IDC_VARFLAGDESCEDIT);
				// �E�B���h�E�^�C�g����ύX����
				ChangeWindowTitle(FlagDlgHndl, SelVarId, 2);
				break;
			} else if (LOWORD(wParam) == IDC_VARCOMMEDITBUTTON) {
COMMEDIT:
				OpType = 2;
				SelOutMode = 0;
				// �I������Ă���P�̃A�C�e���̍s�ԍ����擾����
				int SelItem = GetSelectedVlItem(ComListWndHndl);
				if (SelItem == -1) {
					MessageProc::StkErr(MessageProc::VAR_SELECTEDNOTONE, hWnd);
					break;
				}
				// �Ώۂ̕ϐ������|�W�g���ɑ��݂��邩�m�F����
				if (VarCon_CheckVariableExistence(GetSelectedVariableId(ComListWndHndl, SelItem)) == FALSE) {
					MessageProc::StkErr(MessageProc::VAR_ALREADYDELETED, WndHndl);
					break;
				}
				// �R�~���j�P�[�V�����p�ϐ��ݒ�E�B���h�E���N������
				RECT WndRect;
				GetWindowRect(WndHndl, &WndRect);
				CommWndHndl = CreateWindow(_T("Communication"), _T("communication variable"), WS_CAPTION | WS_SYSMENU | WS_DLGFRAME | WS_MAXIMIZEBOX | WS_MINIMIZEBOX | WS_SYSMENU | WS_SIZEBOX, CW_USEDEFAULT, CW_USEDEFAULT, 770, 450, WndHndl, NULL, InstHndl, NULL);
				SendMessage(CommEdit, EM_SETLIMITTEXT, (WPARAM)0, (LPARAM)0);
				SetIconToWnd(CommWndHndl);
				ShowWindow(CommWndHndl, SW_SHOW);
				EnableWindow(WndHndl, FALSE);
				// "Name"��"Description"�̐ݒ�
				SelVarId = SetNameAndDescription(ComListWndHndl, SelItem, CommBkGndWndHndl, IDC_VARCOMMNAMEEDIT, IDC_VARCOMMDESCEDIT);
				// �E�B���h�E�^�C�g����ύX����
				ChangeWindowTitle(CommWndHndl, SelVarId, 2);
				// ���j���[�`�F�b�N
				ChangeMenuCheckStatus(0);
				// �G�f�B�b�g�{�b�N�X�̍X�V
				OutputCommVariable(CommEdit, 0);
				break;
			} else if (LOWORD(wParam) == IDC_VARFLAGDELBUTTON) {
				CommonProcedureAboutMultiItemsSelection(FlgListWndHndl, 2);
				break;
			} else if (LOWORD(wParam) == IDC_VARCOMMDELBUTTON) {
				CommonProcedureAboutMultiItemsSelection(ComListWndHndl, 2);
				break;
			} else if (LOWORD(wParam) == IDC_VARFLAGTRUE) {
				CommonProcedureAboutMultiItemsSelection(FlgListWndHndl, 1);
				break;
			} else if (LOWORD(wParam) == IDC_VARFLAGFALSE) {
				CommonProcedureAboutMultiItemsSelection(FlgListWndHndl, 0);
				break;
			} else if (LOWORD(wParam) == ID_VARCON_CLOSE) {
				DestroyWindow(hWnd);
				break;
			}
		}
		return DefWindowProc(hWnd, message, wParam, lParam);
	case WM_DESTROY:
		delete WorkDat; // ��Ɨ̈�J��
		RunFlag = FALSE;
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
