#include "..\..\..\YaizuComLib\src\\commonfunc\msgproc.h"
#include "MyMsgProc.h"

void MyMsgProc::AddMsg()
{
	// =====================================================================================================
	//2101 (NC2)
	MessageProc::AddJpn(STKFW_RUNNINGORPROPOPEN, _T("�X���b�h�����s�����v���p�e�B�_�C�A���O�{�b�N�X���J�����܂܂̂��ߑ�������s�ł��܂���B\r\n�X���b�h���~���邩�v���p�e�B�_�C�A���O�{�b�N�X��������ƍēx��������݂Ă��������B"));
	MessageProc::AddEng(STKFW_RUNNINGORPROPOPEN, _T("The operation cannot be performed because threads are running and/or a property dialog box is open.\r\nStop all threads and/or close the property dialog box, then try again."));

	//2102 (NC2)
	MessageProc::AddJpn(STKFW_OUTOFRANGE, _T("�͈͎w��G���[���������܂����B\r\n�K�؂ȃ��[�N�X�y�[�X�̃T�C�Y���w�肵�Ă��������B\r\n  - �� [512 �` 2048]\r\n  - ���� [400 �` 2048]"));
	MessageProc::AddEng(STKFW_OUTOFRANGE, _T("An out-of-range error has occurred.\r\nSpecify a valid workspace size.\r\n  - Width [512 to 2048]\r\n  - Height [400 to 2048]"));

	//2103 (NC1)
	MessageProc::AddJpn(STKFW_DATASAVEFAILED, _T("�f�[�^�̕ۑ��Ɏ��s���܂����B\r\n���̍��ڂ��m�F���Ă��������B\r\n- �Ώۃt�H���_�̃A�N�Z�X���������������B\r\n- �w�肵���t�@�C�������̃v���O�����Ŋ��Ɏg�p����Ă��Ȃ����B"));
	MessageProc::AddEng(STKFW_DATASAVEFAILED, _T("Data save failed.\r\nCheck the items below.\r\n- Whether the access rights of the target folder are correct.\r\n- The specified file has not already been used by another program."));

	//2104 (NC3)
	MessageProc::AddJpn(STKFW_FILEINVALID, _T("�w�肳�ꂽ�t�@�C���͕s���ł��B\r\n���̍��ڂ��m�F���Ă��������B\r\n- �K�؂ȃt�@�C���p�X���w�肳��Ă��邩�B\r\n- �w�肳�ꂽ�t�@�C���͂��̃v���O������p���Đ�������Ă��邩�B\r\n- �t�@�C���̃A�N�Z�X���������������B"));
	MessageProc::AddEng(STKFW_FILEINVALID, _T("The specified file is invalid.\r\nCheck the items below.\r\n- A valid file path is specified.\r\n- The specified file was created using this program.\r\n- The access rights of the file are correct."));

	//2106 (---)
	MessageProc::AddJpn(STKFW_RUNNING, _T("���s��..."));
	MessageProc::AddEng(STKFW_RUNNING, _T("Running..."));

	//2107 (NC1)
	MessageProc::AddJpn(STKFW_NODLL, _T("DLL�t�@�C�������݂��܂���B\r\n���̃v���O��������A�N�Z�X�\�ȓK�؂ȃt�H���_��DLL�t�@�C�����R�s�[���Ă��������B"));
	MessageProc::AddEng(STKFW_NODLL, _T("No DLL file exists.\r\nCopy the DLL file to an appropriate folder that can be accessed by this program."));

	//2108 (NC1)
	MessageProc::AddJpn(STKFW_DLLINVALID, _T("���[�h���ꂽDLL�t�@�C���͕s���ł��B\r\nDLL�����̊֐����������Ă��邩�m�F���Ă��������B\r\n[DllShowProperty]"));
	MessageProc::AddEng(STKFW_DLLINVALID, _T("The loaded DLL is invalid.\r\nCheck that the DLL implements the following function:\r\n[DllShowProperty]"));

	//2110 (---)
	MessageProc::AddJpn(STKFW_ADD_PROCESSING_ELEMENT, _T("�����v�f�̒ǉ�"));
	MessageProc::AddEng(STKFW_ADD_PROCESSING_ELEMENT, _T("Add Processing Element"));

	//2111 (---)
	MessageProc::AddJpn(STKFW_DEL_PROCESSING_ELEMENT, _T("�����v�f�̍폜"));
	MessageProc::AddEng(STKFW_DEL_PROCESSING_ELEMENT, _T("Delete Processing Element"));

	//2112 (---)
	MessageProc::AddJpn(STKFW_ADD_LINK, _T("�֘A���̒ǉ�"));
	MessageProc::AddEng(STKFW_ADD_LINK, _T("Add Link"));

	//2113 (---)
	MessageProc::AddJpn(STKFW_DEL_LINK, _T("�֘A���̍폜"));
	MessageProc::AddEng(STKFW_DEL_LINK, _T("Delete Link"));

	//2120 (NC3)
	MessageProc::AddJpn(STKFW_DBVERSION_OLD, _T("�ǂݍ��񂾃t�@�C���͌Â��o�[�W������StkFw��p���č쐬����Ă��܂��B\r\n���݂̃o�[�W�����Ŏg�p�ł���悤��StkFw�̓f�[�^��ϊ����܂��B"));
	MessageProc::AddEng(STKFW_DBVERSION_OLD, _T("The loaded file was generated with an old version of StkFw.\r\nIn order to use the file with the current version, StkFw will migrate the data."));

	//2121 (NC3)
	MessageProc::AddJpn(STKFW_DBVERSION_UNKNOWN, _T("�ǂݍ��񂾃t�@�C���͕s���ȃo�[�W������StkFw��p���č쐬����Ă��܂��B\r\nStkFw�͂��̃t�@�C�����g�p���邱�Ƃ��ł��܂���B"));
	MessageProc::AddEng(STKFW_DBVERSION_UNKNOWN, _T("The loaded file was generated with an unknown version of StkFw.\r\nStkFw cannot handle this file."));

	//2123 (NC3)
	MessageProc::AddJpn(STKFW_COMPARAM_INVALID, _T("�w�肳�ꂽ�p�����[�^�͕s���ł��B\r\n�w��\�ȃp�����[�^�́C/start�C/stopall�C/open �݂̂ł��B"));
	MessageProc::AddEng(STKFW_COMPARAM_INVALID, _T("The specified parameter is invalid.\r\nThe only valid parameters are /start, /stopall and /open."));

	//2124 (NC3)
	MessageProc::AddJpn(STKFW_COMPARAM_NOFILE, _T("�w�肳�ꂽ�p�����[�^�͕s���ł��B\r\n/start�����/open�p�����[�^�ɂ�STD�t�@�C���ւ̃p�X�w�肪�K�v�ł��B"));
	MessageProc::AddEng(STKFW_COMPARAM_NOFILE, _T("The specified parameter is invalid.\r\nThe file path to the STD file must be input after the parameters (/start and /open) are specified."));

	//2125 (---)
	MessageProc::AddJpn(STKFW_MANUAL_PLACE, _T("\\manual\\jpn\\index.htm"));
	MessageProc::AddEng(STKFW_MANUAL_PLACE, _T("\\manual\\eng\\index.htm"));

	//2126 (---)
	MessageProc::AddJpn(STKFW_CHG_WORKSPACE_SIZE, _T("���[�N�X�y�[�X�T�C�Y�ύX"));
	MessageProc::AddEng(STKFW_CHG_WORKSPACE_SIZE, _T("Change workspace size"));

	//2127 (---)
	MessageProc::AddJpn(STKFW_GRID_ONOFF, _T("�O���b�h"));
	MessageProc::AddEng(STKFW_GRID_ONOFF, _T("Grid"));

	// =====================================================================================================
	//2201 (NC2)
	MessageProc::AddJpn(VAR_SELECTEDNOTONE, _T("�ϐ����w�肳��Ă��Ȃ����C2�ȏ�̕ϐ����w�肳��܂����B\r\n1�̕ϐ��̂ݎw��\�ł��B"));
	MessageProc::AddEng(VAR_SELECTEDNOTONE, _T("No variable or more than one variable has been specified.\r\nOnly one variable may be specified."));

	//2202 (NC2)
	MessageProc::AddJpn(VAR_AREYOUSUREDELETE, _T("�w�肵���ϐ����폜���Ă��ǂ��ł����B"));
	MessageProc::AddEng(VAR_AREYOUSUREDELETE, _T("Are you sure you want to delete the specified variable(s)?"));

	//2203 (NC2)
	MessageProc::AddJpn(VAR_NOITEMSELECTED, _T("�ϐ����w�肳��Ă��܂���B\r\n�P�ȏ�̕ϐ����w�肷��K�v������܂��B"));
	MessageProc::AddEng(VAR_NOITEMSELECTED, _T("No variable has been specified.\r\nPlease specify one or more variables."));

	//2204 (NC2)
	MessageProc::AddJpn(VAR_NOTTRANSUTF8, _T("UTF-8�ɕϊ��ł��Ȃ��R�[�h�����݂��邽�߁C\r\nUFT-8�\����ʂɑJ�ڂł��܂���B"));
	MessageProc::AddEng(VAR_NOTTRANSUTF8, _T("The screen cannot be changed to UTF-8 view \r\nbecause the program has found code that cannot be rendered in UTF-8."));

	//2205 (NC2)
	MessageProc::AddJpn(VAR_INVALIDNAME, _T("�s���ȕϐ������w�肳��܂����B\r\n�w�肵���ϐ������m�F���čēx���s���Ă��������B"));
	MessageProc::AddEng(VAR_INVALIDNAME, _T("Invalid variable name specified.\r\nCheck the specified variable name and then try again."));

	//2206 (NC2)
	MessageProc::AddJpn(VAR_ALREADYDELETED, _T("�ҏW�Ώۂ̕ϐ��͊��ɍ폜����Ă��܂��B\r\n�ҏW����͎��s�ł��܂���B"));
	MessageProc::AddEng(VAR_ALREADYDELETED, _T("The edit operation can not be performed because \r\nthe edit target variable has been deleted."));

	//2207 (NC2)
	MessageProc::AddJpn(VAR_INVALIDTYPE, _T("�ҏW�Ώۂ̕ϐ��͊��ɈقȂ��ʂ̕ϐ��Ƃ��Ďg�p����Ă��܂��B\r\n�ҏW����͎��s�ł��܂���B"));
	MessageProc::AddEng(VAR_INVALIDTYPE, _T("The edit operation can not be performed because \r\nthe target variable has already been used as another type of variable."));

	//2208 (NC3)
	MessageProc::AddJpn(VAR_BUFOVERFLOW, _T("�ϐ��̒����������10M�o�C�g�𒴂��܂����B\r\n����𒴂����f�[�^�͐؂����܂��B"));
	MessageProc::AddEng(VAR_BUFOVERFLOW, _T("The length of the variable specified exceeds the upper limit of 10 MB.\r\nAny data over this limit will be omitted."));

	//2209 (NC2)
	MessageProc::AddJpn(VAR_MAXVARSIZE, _T("�ϐ����i�[���郁�����e�ʂ�����𒴂��܂����B"));
	MessageProc::AddEng(VAR_MAXVARSIZE, _T("The memory size available for storing variable data has exceeded the upper limit."));

	//2210 (NC3)
	MessageProc::AddJpn(VAR_FLAGVARNOT, _T("�t���O�p�ϐ��́C�C���|�[�g�^�G�N�X�|�[�g���s�����Ƃ͂ł��܂���B"));
	MessageProc::AddEng(VAR_FLAGVARNOT, _T("Import/export operation of the flag variable cannot be performed."));

	//2211 (NC3)
	MessageProc::AddJpn(VAR_FOLDERSETERR, _T("�w�肳�ꂽ�C���|�[�g�C�G�N�X�|�[�g�t�H���_�͕s���ł��B\r\n�t�H���_���m�F���C�ēx��������s���Ă��������B"));
	MessageProc::AddEng(VAR_FOLDERSETERR, _T("An invalid import/export folder has been specified.\r\nCheck the folder and try again."));

	//2212 (NC3)
	MessageProc::AddJpn(VAR_IMPERR, _T("�C���|�[�g���삪���s���܂����B\r\n�t�H���_�̃A�N�Z�X�����܂��̓t�@�C�������m�F���Ă��������B"));
	MessageProc::AddEng(VAR_IMPERR, _T("Import operation failed.\r\nCheck the folder permissions and file names."));

	//2213 (NC3)
	MessageProc::AddJpn(VAR_EXPERR, _T("�G�N�X�|�[�g���삪���s���܂����B\r\n�t�H���_�̃A�N�Z�X������󂫃f�B�X�N�e�ʁC�I�������ϐ������m�F���Ă��������B"));
	MessageProc::AddEng(VAR_EXPERR, _T("Export operation failed.\r\nCheck the folder permissions, the amount of free disk space and the variable names specified."));

	//2214 (NC3)
	MessageProc::AddJpn(VAR_NOIMPTARGET, _T("�w�肵���t�H���_�ɂ̓C���|�[�g�Ώۃt�@�C�������݂��܂���B\r\n�C���|�[�g�Ώۃt�@�C���̊g���q��\".xxx\"�ł���K�v������܂��B"));
	MessageProc::AddEng(VAR_NOIMPTARGET, _T("No import target file exists in the folder specified.\r\nThe extension of import target files must be \".xxx\"."));

	//2215 (NC3)
	MessageProc::AddJpn(VAR_NOEXPTARGET, _T("�ϐ����w�肳��Ă��܂���B\r\n��ȏ�̕ϐ����w�肷��K�v������܂��B"));
	MessageProc::AddEng(VAR_NOEXPTARGET, _T("No variables have been specified.\r\nMore than one variable must be specified."));

	// =====================================================================================================
	// 2300 (---)
	MessageProc::AddJpn(PROP_NAME, _T("����"));
	MessageProc::AddEng(PROP_NAME, _T("Name"));

	// 2301 (NC2)
	MessageProc::AddJpn(PROP_CHKDAT_START, _T("���̓f�[�^��...����J�n����"));
	MessageProc::AddEng(PROP_CHKDAT_START, _T("Input data starts with..."));

	// 2302 (NC2)
	MessageProc::AddJpn(PROP_CHKDAT_NSTART, _T("���̓f�[�^��...����J�n���Ȃ�"));
	MessageProc::AddEng(PROP_CHKDAT_NSTART, _T("Input data does not start with..."));

	// 2303 (NC2)
	MessageProc::AddJpn(PROP_CHKDAT_END, _T("���̓f�[�^��...�ŏI������"));
	MessageProc::AddEng(PROP_CHKDAT_END, _T("Input data ends with..."));

	// 2304 (NC2)
	MessageProc::AddJpn(PROP_CHKDAT_NEND, _T("���̓f�[�^��...�ŏI�����Ȃ�"));
	MessageProc::AddEng(PROP_CHKDAT_NEND, _T("Input data does not end with..."));

	// 2305 (NC2)
	MessageProc::AddJpn(PROP_CHKDAT_CONT, _T("���̓f�[�^��...���܂�"));
	MessageProc::AddEng(PROP_CHKDAT_CONT, _T("Input data contains..."));

	// 2306 (NC2)
	MessageProc::AddJpn(PROP_CHKDAT_NCONT, _T("���̓f�[�^��...���܂܂Ȃ�"));
	MessageProc::AddEng(PROP_CHKDAT_NCONT, _T("Input data does not contain..."));

	// 2307 (NC2)
	MessageProc::AddJpn(PROP_CHKDAT_EQUAL, _T("���̓f�[�^��...�ƈ�v����"));
	MessageProc::AddEng(PROP_CHKDAT_EQUAL, _T("Input data is equal to..."));

	// 2308 (NC2)
	MessageProc::AddJpn(PROP_CHKDAT_NEQUAL, _T("���̓f�[�^��...�ƈ�v���Ȃ�"));
	MessageProc::AddEng(PROP_CHKDAT_NEQUAL, _T("Input data is not equal to..."));

	// 2311 (NC2)
	MessageProc::AddJpn(PROP_CHGDAT_INSERT, _T("���̓f�[�^�̊J�n�o�C�g��(A)��}������"));
	MessageProc::AddEng(PROP_CHGDAT_INSERT, _T("Insert (A) at the start byte of the input data."));

	// 2312 (NC2)
	MessageProc::AddJpn(PROP_CHGDAT_JOIN, _T("���̓f�[�^�̏I���o�C�g��(A)��A������"));
	MessageProc::AddEng(PROP_CHGDAT_JOIN, _T("Join (A) to the end byte of the input data."));

	// 2313 (NC2)
	MessageProc::AddJpn(PROP_CHGDAT_REPLACE, _T("���̓f�[�^����(A)��������(B)�ɒu��������"));
	MessageProc::AddEng(PROP_CHGDAT_REPLACE, _T("Search for (A) in the input data and replace with (B)."));

	// 2314 (NC2)
	MessageProc::AddJpn(PROP_CHGDAT_EXTRACT, _T("���̓f�[�^����(A)�Ŏn�܂�(B)�ŏI���̈�𒊏o����"));
	MessageProc::AddEng(PROP_CHGDAT_EXTRACT, _T("Extract an area that starts with (A) and ends with (B) from the input data."));

	// 2315 (NC2)
	MessageProc::AddJpn(PROP_CHGDAT_DROP, _T("���̓f�[�^���̂ċ�f�[�^��Ԃ�"));
	MessageProc::AddEng(PROP_CHGDAT_DROP, _T("Drop the input data and return empty data."));

	// 2316 (NC2)
	MessageProc::AddJpn(PROP_CHGDAT_RESET, _T("���̓f�[�^���̂�(A)�Ƀ��Z�b�g����"));
	MessageProc::AddEng(PROP_CHGDAT_RESET, _T("Drop the input data and reset to (A)."));

	// 2320 (NC2)
	MessageProc::AddJpn(PROP_CLOSEPORT, _T("�N���[�Y����\�P�b�g"));
	MessageProc::AddEng(PROP_CLOSEPORT, _T("Socket to be closed"));

	// 2321 (NC2)
	MessageProc::AddJpn(PROP_TIMER_PAST, _T("���Ɏ������t�Ǝ������o�߂����玟�̃X�e�b�v�Ɉڂ�"));
	MessageProc::AddEng(PROP_TIMER_PAST, _T("Progress to the next step if the date and time shown below are in the past."));

	// 2322 (NC2)
	MessageProc::AddJpn(PROP_TIMER_WAIT, _T("��莞�ԑ҂������Ǝ��̃X�e�b�v�Ɉڂ�"));
	MessageProc::AddEng(PROP_TIMER_WAIT, _T("Progress to the next step after sleeping."));

	// 2323 (---)
	MessageProc::AddJpn(PROP_TIMER_SEC, _T("(�b) 0-3600"));
	MessageProc::AddEng(PROP_TIMER_SEC, _T("(Sec) 0-3600"));

	// 2324 (NC2)
	MessageProc::AddJpn(PROP_MAP_SEARCH, _T("�����Ώەϐ����̃v���t�B�b�N�X"));
	MessageProc::AddEng(PROP_MAP_SEARCH, _T("Prefix of search target variable name."));

	// 2325 (NC2)
	MessageProc::AddJpn(PROP_MAP_REPLACE, _T("�u�����Ώەϐ����̃v���t�B�b�N�X"));
	MessageProc::AddEng(PROP_MAP_REPLACE, _T("Prefix of replacement target variable name"));

	// 2326 (NC2)
	MessageProc::AddJpn(PROP_MAP_START, _T("���̒l���玩���̔Ԃ����"));
	MessageProc::AddEng(PROP_MAP_START, _T("Auto numbering from the next value"));

	// 2327 (NC3)
	MessageProc::AddJpn(PROP_MAP_USEONCE, _T("�e�ϐ��ւ̃}�b�s���O�͈�x�����g�p�����"));
	MessageProc::AddEng(PROP_MAP_USEONCE, _T("The mapping to each variable is used only once."));

	// 2331 (NC2)
	MessageProc::AddJpn(PROP_CHECK_TRUE, _T("TRUE�Ȃ�Ύ��̃X�e�b�v�Ɉڂ�"));
	MessageProc::AddEng(PROP_CHECK_TRUE, _T("If TRUE, progress to the next step."));

	// 2332 (NC2)
	MessageProc::AddJpn(PROP_CHECK_FALSE, _T("FALSE�Ȃ�Ύ��̃X�e�b�v�Ɉڂ�"));
	MessageProc::AddEng(PROP_CHECK_FALSE, _T("If FALSE, progress to the next step."));

	// 2333 (NC2)
	MessageProc::AddJpn(PROP_CHANGE_TRUE, _T("�t���O��TRUE�ɂ���"));
	MessageProc::AddEng(PROP_CHANGE_TRUE, _T("Change flag to TRUE."));

	// 2334 (NC2)
	MessageProc::AddJpn(PROP_CHANGE_FALSE, _T("�t���O��FALSE�ɂ���"));
	MessageProc::AddEng(PROP_CHANGE_FALSE, _T("Change flag to FALSE."));

	// 2341 (NC2)
	MessageProc::AddJpn(PROP_LOAD_VAR, _T("���̕ϐ�����f�[�^��Ǎ���"));
	MessageProc::AddEng(PROP_LOAD_VAR, _T("Load data from the following variable."));

	// 2342 (NC2)
	MessageProc::AddJpn(PROP_LOAD_CONT, _T("���̕ϐ�����A���I�Ƀf�[�^��Ǎ���"));
	MessageProc::AddEng(PROP_LOAD_CONT, _T("Load data from the following variables continuously."));

	// 2343 (NC2)
	MessageProc::AddJpn(PROP_STORE_VAR, _T("���̕ϐ��Ƀf�[�^����������"));
	MessageProc::AddEng(PROP_STORE_VAR, _T("Store data into the following variable."));

	// 2344 (NC2)
	MessageProc::AddJpn(PROP_STORE_CONT, _T("���̕ϐ��ɘA���I�Ƀf�[�^����������"));
	MessageProc::AddEng(PROP_STORE_CONT, _T("Store data into the following variables continuously."));

	// 2345 (---)
	MessageProc::AddJpn(PROP_DATA_COMM, _T("�R�~���j�P�[�V�����p�ϐ�"));
	MessageProc::AddEng(PROP_DATA_COMM, _T("Communication variable"));

	// 2346 (---)
	MessageProc::AddJpn(PROP_DATA_PREF, _T("�ϐ����̃v���t�B�b�N�X"));
	MessageProc::AddEng(PROP_DATA_PREF, _T("Prefix of variable name"));

	// 2347 (NC3)
	MessageProc::AddJpn(PROP_DATA_NUM, _T("���̒l����̎����̔�"));
	MessageProc::AddEng(PROP_DATA_NUM, _T("Auto numbering from the next value"));

	// 2351 (NC2)
	MessageProc::AddJpn(PROP_NET_RECV, _T("�w�肵��IP�A�h���X�ƃ|�[�g����f�[�^����M����"));
	MessageProc::AddEng(PROP_NET_RECV, _T("Receive data using the specified IP address and port."));

	// 2352 (NC5)
	MessageProc::AddJpn(PROP_NET_RECVTGT, _T("�w�肵�����M�v�f�̐ڑ��悩��f�[�^����M����"));
	MessageProc::AddEng(PROP_NET_RECVTGT, _T("Receive data from the connection target of the specified sender element."));

	// 2353 (NC2)
	MessageProc::AddJpn(PROP_NET_SEND, _T("�w�肵��IP�A�h���X�ƃ|�[�g�Ƀf�[�^�𑗐M����"));
	MessageProc::AddEng(PROP_NET_SEND, _T("Send data to the specified IP address and port."));

	// 2354 (NC5)
	MessageProc::AddJpn(PROP_NET_SENDTGT, _T("�w�肵����M�v�f�̐ڑ���Ƀf�[�^�𑗐M����"));
	MessageProc::AddEng(PROP_NET_SENDTGT, _T("Send data to the connection target of the specified receiver element."));

	// 2355 (NC2)
	MessageProc::AddJpn(PROP_NET_CLOSE_AFTERSEND, _T("�f�[�^���M��\�P�b�g���N���[�Y����"));
	MessageProc::AddEng(PROP_NET_CLOSE_AFTERSEND, _T("Close socket after sending data."));

	// 2356 (NC2)
	MessageProc::AddJpn(PROP_NET_CLOSE_AFTERRECV, _T("�f�[�^��M��\�P�b�g���N���[�Y����"));
	MessageProc::AddEng(PROP_NET_CLOSE_AFTERRECV, _T("Close socket after receiving data."));

	// 2357 (NC4)
	MessageProc::AddJpn(PROP_NET_TIMEOUT, _T("�ŏI�A�N�Z�X�ȍ~�Ƀ^�C���A�E�g�����m����"));
	MessageProc::AddEng(PROP_NET_TIMEOUT, _T("Time-out detected after last access."));

	// 2358 (---)
	MessageProc::AddJpn(PROP_NET_SENDER, _T("���M�v�f��"));
	MessageProc::AddEng(PROP_NET_SENDER, _T("Sender name"));

	// 2359 (---)
	MessageProc::AddJpn(PROP_NET_RECEIVER, _T("��M�v�f��"));
	MessageProc::AddEng(PROP_NET_RECEIVER, _T("Receiver name"));

	// 2360 (---)
	MessageProc::AddJpn(PROP_NET_ICON, _T("�A�C�R��"));
	MessageProc::AddEng(PROP_NET_ICON, _T("Icon"));

	// 2361 (---)
	MessageProc::AddJpn(PROP_NET_IPADDR, _T("IP�A�h���X/�z�X�g��"));
	MessageProc::AddEng(PROP_NET_IPADDR, _T("IP address/hostname"));

	// 2362 (---)
	MessageProc::AddJpn(PROP_NET_PORT, _T("�|�[�g�ԍ�"));
	MessageProc::AddEng(PROP_NET_PORT, _T("Port"));

	// 2363 (NC4)
	MessageProc::AddJpn(PROP_FILEACCESS_NAME, _T("�v���O�������A�N�Z�X����t�@�C�������w��\r\n�J�����g�t�H���_����̑��΃p�X���w�肷��K�v������B(��:\"..\\data\\test.bin\")\r\n�J�����g�t�H���_�͒ʏ�C�Ώۂ�\".std\"�t�@�C�����i�[����Ă���t�H���_�ƂȂ�B"));
	MessageProc::AddEng(PROP_FILEACCESS_NAME, _T("Specify the file name used by the program. \r\nThe relative path from the current folder should be given (ex: \"..\\data\\test.bin\"). \r\nThe current folder is normally set as the one containing the target \".std\" file."));

	// 2364 (NC4)
	MessageProc::AddJpn(PROP_FILEACCESSW_ADD, _T("�����̃t�@�C���̍Ō�Ƀf�[�^��A������"));
	MessageProc::AddEng(PROP_FILEACCESSW_ADD, _T("Add data to the end of the existing file."));

	// 2365 (NC4)
	MessageProc::AddJpn(PROP_FILEACCESSW_INSERT, _T("�����̃t�@�C���̐擪�ɂɃf�[�^��}������"));
	MessageProc::AddEng(PROP_FILEACCESSW_INSERT, _T("Insert data at the start of the existing file."));

	// 2366 (NC4)
	MessageProc::AddJpn(PROP_FILEACCESSW_OVERWRITE, _T("�����̃t�@�C�����㏑������"));
	MessageProc::AddEng(PROP_FILEACCESSW_OVERWRITE, _T("Overwrite the existing file."));

	// 2367 (NC4)
	MessageProc::AddJpn(PROP_FILEACCESSR_ADD, _T("���̓f�[�^�̏I���o�C�g�ɓǂݍ��񂾃f�[�^��A������"));
	MessageProc::AddEng(PROP_FILEACCESSR_ADD, _T("Add loaded data to the end byte of the input data."));

	// 2368 (NC4)
	MessageProc::AddJpn(PROP_FILEACCESSR_INSERT, _T("���̓f�[�^�̊J�n�o�C�g�ɓǂݍ��񂾃f�[�^��}������"));
	MessageProc::AddEng(PROP_FILEACCESSR_INSERT, _T("Insert loaded data at the start byte of the input data."));

	// 2369 (NC4)
	MessageProc::AddJpn(PROP_FILEACCESSR_OVERWRITE, _T("�t�@�C������ǂݍ��񂾃f�[�^���o�͂���"));
	MessageProc::AddEng(PROP_FILEACCESSR_OVERWRITE, _T("Output data read from the file."));

	// 2370 (NC4)
	MessageProc::AddJpn(PROP_EXECPROG_COMMAND, _T("�O���v���O�����ւ̃p�X���w��"));
	MessageProc::AddEng(PROP_EXECPROG_COMMAND, _T("Specify the path to the external program."));

	// 2371 (NC4)
	MessageProc::AddJpn(PROP_EXECPROG_WAIT, _T("���s�����v���O�������I������܂őҋ@����"));
	MessageProc::AddEng(PROP_EXECPROG_WAIT, _T("Wait until the program executed is finished."));

	// 2372 (NC4)
	MessageProc::AddJpn(PROP_EXECPROG_CURRDIR, _T("�O���v���O�������s���̃J�����g�t�H���_���w��\r\n�J�����g�t�H���_���w�肵�Ȃ��ꍇ�C�Ώۂ�\".std\"�t�@�C�����z�u���ꂽ�t�H���_���J�����g�t�H���_�ƂȂ�B"));
	MessageProc::AddEng(PROP_EXECPROG_CURRDIR, _T("Specify the current folder during external program execution. \r\nIf the current folder is not specified, the one containing the target \".std\" file will be set."));

	// 2373 (NC4)
	MessageProc::AddJpn(PROP_EXECPROG_STDOUT, _T("�O���v���O������STDOUT�֏������񂾃f�[�^�����̏����v�f�ɓn��"));
	MessageProc::AddEng(PROP_EXECPROG_STDOUT, _T("Pass data written by the external program to STDOUT to the next element."));

	// 2374 (NC4)
	MessageProc::AddJpn(PROP_EXECPROG_STDIN, _T("�{�����v�f�̓��̓f�[�^���O���v���O������STDIN�ɓn��"));
	MessageProc::AddEng(PROP_EXECPROG_STDIN, _T("Pass the input data of this processing element to STDIN."));

	// 2375 (NC4)
	MessageProc::AddJpn(PROP_NET_UNCOND, _T("�������Ŏ��̏����v�f�Ɉڂ�"));
	MessageProc::AddEng(PROP_NET_UNCOND, _T("Proceed unconditionally to the next processing element."));

	// 2376 (��)
	MessageProc::AddJpn(PROP_NET_EXCEEDSIZE, _T("��M�f�[�^�T�C�Y���w�肵���l�ɒB���� [1-9,999,999 �o�C�g]"));
	MessageProc::AddEng(PROP_NET_EXCEEDSIZE, _T("The size of the data received reached the preset value. [1-9,999,999 bytes]"));

	// 2377 (��)
	MessageProc::AddJpn(PROP_NET_RECVSTR, _T("�w�肵���f�[�^����M����"));
	MessageProc::AddEng(PROP_NET_RECVSTR, _T("Specified data received."));

	// 2378 (NC4)
	MessageProc::AddJpn(PROP_NET_TERMCOND, _T("�I������"));
	MessageProc::AddEng(PROP_NET_TERMCOND, _T("Termination condition"));

	// 2379 (NC4)
	MessageProc::AddJpn(PROP_NET_CLOSEDETECT, _T("���M���\�P�b�g���N���[�Y���ꂽ�Ƃ��������̏����v�f�Ɉڂ�"));
	MessageProc::AddEng(PROP_NET_CLOSEDETECT, _T("Proceed to the next processing element only when the sender socket is closed."));

	// 2380 (---)
	MessageProc::AddJpn(PROP_NET_CLOSEFORCE, _T("�����I�ɃN���[�Y����"));
	MessageProc::AddEng(PROP_NET_CLOSEFORCE, _T("Force close"));

	// 2381 (---)
	MessageProc::AddJpn(PROP_NET_CLOSEUDPPORT, _T("UDP�\�P�b�g���N���[�Y����"));
	MessageProc::AddEng(PROP_NET_CLOSEUDPPORT, _T("Close UDP socket"));

	// 2382 (---)
	MessageProc::AddJpn(PROP_NET_CLOSETCPPORT, _T("TCP�\�P�b�g���N���[�Y����"));
	MessageProc::AddEng(PROP_NET_CLOSETCPPORT, _T("Close TCP socket"));

	// 2383 (NC6)
	MessageProc::AddJpn(PROP_NET_PROCEEDEVENIFNODATARECV, _T("�f�[�^����M�ł����̏����v�f�ɑJ�ڂ���"));
	MessageProc::AddEng(PROP_NET_PROCEEDEVENIFNODATARECV, _T("Proceed even if no data are received."));

	// 2384 (NC7)
	MessageProc::AddJpn(PROP_NET_RECVMULTI, _T("�w�肵����M�v�f����f�[�^����M����"));
	MessageProc::AddEng(PROP_NET_RECVMULTI, _T("Receive data from the specified receiver element."));

	// 2385 (��)
	MessageProc::AddJpn(PROP_NET_HTTPCONTLEN, _T("HTTP�w�b�_��Content-Length�Ŏw�肵���T�C�Y�̃f�[�^����M����"));
	MessageProc::AddEng(PROP_NET_HTTPCONTLEN, _T("Data which size specified in Content-Length in HTTP header received."));

	// 2386 (��)
	MessageProc::AddJpn(PROP_NET_TIMEOUTINTERVAL, _T("�^�C���A�E�g(msec)"));
	MessageProc::AddEng(PROP_NET_TIMEOUTINTERVAL, _T("Timeout(msec)"));

	// 2387 (��)
	MessageProc::AddJpn(PROP_HTTPHEADER_DELETEFROM, _T("���̓f�[�^����HTTP�w�b�_����菜��"));
	MessageProc::AddEng(PROP_HTTPHEADER_DELETEFROM, _T("Delete HTTP header from input data"));

	// 2388 (��)
	MessageProc::AddJpn(PROP_HTTPHEADER_INSERTINTO, _T("�o�̓f�[�^��HTTP�w�b�_��}������"));
	MessageProc::AddEng(PROP_HTTPHEADER_INSERTINTO, _T("Insert HTTP header into output data"));

	// 2389 (��)
	MessageProc::AddJpn(PROP_HTTPHEADER_CONTLEN, _T("Content-Length"));
	MessageProc::AddEng(PROP_HTTPHEADER_CONTLEN, _T("Content-Length"));

	// 2390 (��)
	MessageProc::AddJpn(PROP_HTTPHEADER_DATE, _T("Date"));
	MessageProc::AddEng(PROP_HTTPHEADER_DATE, _T("Date"));

	// 2391 (��)
	MessageProc::AddJpn(PROP_HTTPHEADER_REQUEST, _T("Request"));
	MessageProc::AddEng(PROP_HTTPHEADER_REQUEST, _T("Request"));

	// 2392 (��)
	MessageProc::AddJpn(PROP_HTTPHEADER_RESPONSE, _T("Response"));
	MessageProc::AddEng(PROP_HTTPHEADER_RESPONSE, _T("Response"));

	// =====================================================================================================
	// 2400 (---)
	MessageProc::AddJpn(STKFW_LOG_TITLE, _T("StkFw - �X���b�h�R���g���[��\r\n"));
	MessageProc::AddEng(STKFW_LOG_TITLE, _T("StkFw - Thread controller\r\n"));

	// 2401 (NC3)
	MessageProc::AddJpn(STKFW_LOG_START, _T("�X���b�h�R���g���[���̓��O�̏o�͂��J�n���܂����B\r\n"));
	MessageProc::AddEng(STKFW_LOG_START, _T("The thread controller has started logging.\r\n"));

	// 2402 (NC3)
	MessageProc::AddJpn(STKFW_LOG_STOP, _T("�X���b�h�R���g���[���̓��O�̏o�͂��~���܂����B\r\n"));
	MessageProc::AddEng(STKFW_LOG_STOP, _T("The thread controller has stopped logging.\r\n"));

	// =====================================================================================================
	// 2500 - 2899 : Reserved by server code

	// =====================================================================================================
	//2902 (NC2)
	MessageProc::AddJpn(FILEACCESSERROR, _T("�t�@�C���A�N�Z�X�G���[���������܂����B"));
	MessageProc::AddEng(FILEACCESSERROR, _T("A file access error has occurred."));

	//2903 (NC1)
	MessageProc::AddJpn(NEEDADMINRIGHTS, _T("���̃v���O���������s���邽�߂ɂ�Local Administrator�̌������K�v�ł��B\r\n�v���O�����͏I�����܂��B\r\n\r\n"));
	MessageProc::AddEng(NEEDADMINRIGHTS, _T("You need local administrator's rights to run this program.\r\nThe program will be terminated.\r\n\r\n"));

	//2904 (NC3)
	MessageProc::AddJpn(DATAUPDATED, _T("�v���O�������g�p����f�[�^�͍X�V����Ă��܂��B\r\n�f�[�^�������܂�������𑱂��ėǂ��ł����B"));
	MessageProc::AddEng(DATAUPDATED, _T("Program data updated.\r\nData will be lost. Continue operation?"));

	//2931 (---)
	MessageProc::AddJpn(COMMON_ADD, _T("�ǉ�"));
	MessageProc::AddEng(COMMON_ADD, _T("Add"));

	//2932 (---)
	MessageProc::AddJpn(COMMON_DELETE, _T("�폜"));
	MessageProc::AddEng(COMMON_DELETE, _T("Delete"));

	//2933 (---)
	MessageProc::AddJpn(COMMON_EDIT, _T("�ҏW"));
	MessageProc::AddEng(COMMON_EDIT, _T("Edit"));

	//2934 (---)
	MessageProc::AddJpn(COMMON_REFRESH, _T("�X�V"));
	MessageProc::AddEng(COMMON_REFRESH, _T("Refresh"));

	//2935 (---)
	MessageProc::AddJpn(COMMON_TRUE, _T("True"));
	MessageProc::AddEng(COMMON_TRUE, _T("True"));

	//2936 (---)
	MessageProc::AddJpn(COMMON_FALSE, _T("False"));
	MessageProc::AddEng(COMMON_FALSE, _T("False"));

	//2937 (---)
	MessageProc::AddJpn(COMMON_UNKNOWN, _T("�s��"));
	MessageProc::AddEng(COMMON_UNKNOWN, _T("Unknown"));

	//2941 (---)
	MessageProc::AddJpn(COMMON_OK, _T("OK"));
	MessageProc::AddEng(COMMON_OK, _T("OK"));

	//2942 (---)
	MessageProc::AddJpn(COMMON_CANCEL, _T("��ݾ�"));
	MessageProc::AddEng(COMMON_CANCEL, _T("Cancel"));

	// =====================================================================================================
	//9100 (NC2)
	MessageProc::AddJpn(SFW_100_1, _T("StkFw �����o�[�W�����������[�X�����B"));
	MessageProc::AddEng(SFW_100_1, _T("StkFw initial version was released."));

	//9101 [10015] (NC2)
	MessageProc::AddJpn(SFW_100_110_1, _T("���|�W�g���f�[�^���Z�[�u�^���[�h�����t�H���_���CStkFw�ċN����̏����t�H���_�ɐݒ肳���s����C�������B"));
	MessageProc::AddEng(SFW_100_110_1, _T("The bug involving the folder for loaded/saved repository data being configured as the initial folder after restarting StkFw was fixed."));

	//9102 [10017] (NC2)
	MessageProc::AddJpn(SFW_100_110_2, _T("�A�C�R�����̕\�����A�C�R���̒��S���炸���s����C�������B"));
	MessageProc::AddEng(SFW_100_110_2, _T("The bug involving the icon name being misaligned from the center of the icon was fixed."));

	//9103 [10018, 10020, 10025] (NC2)
	MessageProc::AddJpn(SFW_100_110_3, _T("�{�\�t�g�E�F�A�̖ړI���e�X�g�E�t���[�����[�N����e�X�g�x���\�t�g�E�F�A�ɕύX�����B"));
	MessageProc::AddEng(SFW_100_110_3, _T("The purpose of the software was changed from provision of a test framework to testing support."));

	//9104 [10034] (NC2)
	MessageProc::AddJpn(SFW_100_110_4, _T("���[�v�o�b�N�l�b�g���[�N�A�_�v�^�ǉ��^�폜�_�C�A���O���T�|�[�g�����B"));
	MessageProc::AddEng(SFW_100_110_4, _T("Support for addition/removal of a loopback network adapter dialog was added."));

	//9105 [10040] (NC2)
	MessageProc::AddJpn(SFW_100_110_5, _T("OS�ċN����ɒǉ�/�폜����IP�A�h���X�����Ƃɂ��ǂ�IP�A�h���X�E�B�U�[�h�̕s����C�������B"));
	MessageProc::AddEng(SFW_100_110_5, _T("A bug in the Add/remove IP address wizard involving the flushing of added/removed IP addresses after operating system reboot was fixed."));

	//9106 [10052] (NC2)
	MessageProc::AddJpn(SFW_100_110_6, _T("�ϐ��Ǘ��@�\(Variable Controller)���T�|�[�g�����B"));
	MessageProc::AddEng(SFW_100_110_6, _T("Support for variable management functionality (Variable Controller) was added."));

	//9107 [10074] (NC3)
	MessageProc::AddJpn(SFW_110_120_1, _T("Administrators�O���[�v�ɑ����Ȃ����[�U�[��StkFw���g�p�ł���悤�ɂ����B"));
	MessageProc::AddEng(SFW_110_120_1, _T("Support enabled for StkFw operation by non-administrator-group users."));

	//9108 [10075] (NC3)
	MessageProc::AddJpn(SFW_110_120_2, _T("�X���b�h�R���g���[���ŒʐM���O�o�͋@�\���T�|�[�g�����B"));
	MessageProc::AddEng(SFW_110_120_2, _T("Support enabled for communication logging functionality on thread controller."));

	//9109 [10078] (NC3)
	MessageProc::AddJpn(SFW_110_120_3, _T("Windows 7, Windows Server 2003, Windows Server 2008���T�|�[�g�����B"));
	MessageProc::AddEng(SFW_110_120_3, _T("Support enabled for Windows 7, Windows Server 2003 and Windows Server 2008."));

	//9110 [10079] (NC3)
	MessageProc::AddJpn(SFW_110_120_4, _T("�����̃��C���R���\�[���𓯎��ɋN���ł���悤�ɂ����B"));
	MessageProc::AddEng(SFW_110_120_4, _T("Support enabled for simultaneous launch of multiple main consoles."));

	//9111 [10080] (NC3)
	MessageProc::AddJpn(SFW_110_120_5, _T("�o�b�N�O���E���h�v���Z�X�Ƃ��ăX���b�h�����s����@�\���T�|�[�g�����B"));
	MessageProc::AddEng(SFW_110_120_5, _T("Support enabled for thread execution as a background process."));

	//9112 [10081] (NC3)
	MessageProc::AddJpn(SFW_110_120_6, _T("�����̕ϐ��̃G�N�X�|�[�g�^�C���|�[�g���T�|�[�g�����B"));
	MessageProc::AddEng(SFW_110_120_6, _T("Support enabled for import and export of multiple variable specifications."));

	//9113 [10083] (NC3)
	MessageProc::AddJpn(SFW_110_120_7, _T("�����̃X���b�h��1�̃X���b�h�ɘA������f�[�^�t���[�ŁC�f�[�^�t���[�̏I�[�ƂȂ鏈���v�f�ɏ��������B���Ă��C�ꕔ�̃X���b�h�̏������������Ȃ��s����C�������B"));
	MessageProc::AddEng(SFW_110_120_7, _T("Fixed bug whereby data flow in which multiple threads leading to a single thread did not terminate even when processing reached the end of the element."));

	//9114 [10084] (NC4)
	MessageProc::AddJpn(SFW_110_120_8, _T("�����̃X���b�h��1�̃X���b�h�ɘA������f�[�^�t���[�ŁC�f�[�^���s���ɏ㏑�����ꂽ��C�]���ɏ��������s����C�������B"));
	MessageProc::AddEng(SFW_110_120_8, _T("Bugs relating to invalid data overwritten and unnecessary data processing on data flow in which multiple threads led to a single thread have been fixed."));

	//9115 (NC4)
	MessageProc::AddJpn(SFW_120_130_1, _T("�t�@�C���ւ̏������݂���уt�@�C������̓ǂݍ��݂��s�������v�f���T�|�[�g�����B"));
	MessageProc::AddEng(SFW_120_130_1, _T("Support enabled for writing/reading of file processing elements."));

	//9116 (NC4)
	MessageProc::AddJpn(SFW_120_130_2, _T("�O���v���O���������s���鏈���v�f���T�|�[�g�����B"));
	MessageProc::AddEng(SFW_120_130_2, _T("Support enabled for processing of elements that execute external programs."));

	//9117 (NC4)
	MessageProc::AddJpn(SFW_120_130_3, _T("�S�X���b�h�ꊇ�J�n�^��~�@�\���T�|�[�g�����B"));
	MessageProc::AddEng(SFW_120_130_3, _T("Support enabled for start/stop all threads function."));

	//9118 (NC4)
	MessageProc::AddJpn(SFW_120_130_4, _T("TCP receiver�̏I���������w��ł���悤�ɂ����B�V���Ƀf�[�^���������m�ƃf�[�^��v���m���I�������Ƃ��Ēǉ������B"));
	MessageProc::AddEng(SFW_120_130_4, _T("Support enabled for specification of TCP receiver termination conditions. Detection of excess data length and data matching newly added as termination conditions."));

	//9119 (NC5)
	MessageProc::AddJpn(SFW_130_140_1, _T("�����N���[�Y�Ɛڑ���̃V���b�g�_�E�����m�ɂ��N���[�Y��2�̃\�P�b�g�N���[�Y���@���T�|�[�g�����B"));
	MessageProc::AddEng(SFW_130_140_1, _T("Support enabled for two socket closure methods (forced close and peer shutdown detection close)."));

	//9120 (NC5)
	MessageProc::AddJpn(SFW_130_140_2, _T("���[�N�X�y�[�X�T�C�Y��ύX�ł���悤�ɂ����B"));
	MessageProc::AddEng(SFW_130_140_2, _T("Support enabled for workspace size change."));

	//9121 (NC5)
	MessageProc::AddJpn(SFW_130_140_3, _T("�����v�f�̒ǉ��Ɋւ���K�w�����ꂽ���j���[��񋟂����B"));
	MessageProc::AddEng(SFW_130_140_3, _T("Support enabled for hierarchical menu for addition of processing element operations."));

	//9122 (NC5)
	MessageProc::AddJpn(SFW_130_140_4, _T("UDP receiver�����v�f�����UDP sender�����v�f��V���ɃT�|�[�g�����B"));
	MessageProc::AddEng(SFW_130_140_4, _T("Support enabled for UDP receiver processing element and UDP sender processing element."));

	//9123 (NC5)
	MessageProc::AddJpn(SFW_130_140_5, _T("�\�P�b�g�N���[�Y���Ɍ���������v�f��ID�����O�ɏo�͂����s�ǂ�΍􂵂��B"));
	MessageProc::AddEng(SFW_130_140_5, _T("Logged bug relating to invalid ID for processing element fixed."));

	//9124 (NC5)
	MessageProc::AddJpn(SFW_130_140_6, _T("Windows 8, Windows Server 2012, Windows Server 2003 R2, Windows Server 2008 R2���T�|�[�g�����B"));
	MessageProc::AddEng(SFW_130_140_6, _T("Support enabled for Windows 8, Windows Server 2012, Windows Server 2003 R2 and Windows Server 2008 R2."));

	//9125 (NC7)
	MessageProc::AddJpn(SFW_140_150_1, _T("�C���X�g�[���v���O�����i�t�@�C���j���ЂƂ�MSI�t�@�C���ɓ��������B"));
	MessageProc::AddEng(SFW_140_150_1, _T("Installer program files integrated into a single MSI file."));

	//9126 (NC7)
	MessageProc::AddJpn(SFW_140_150_2, _T("����|�[�g�ŕ����N���C�A���g����̓����ڑ����\�ɂ����B"));
	MessageProc::AddEng(SFW_140_150_2, _T("Support enabled for multiple-client connections using the same port number."));

	//9127 (NC7)
	MessageProc::AddJpn(SFW_140_150_3, _T("/open�܂���/start�p�����[�^�w��ŋN�������Ƃ��ɁC�J�����g�t�H���_��.std�t�@�C�����z�u���ꂽ�t�H���_�ƈقȂ�s�ǂ�΍􂵂��B"));
	MessageProc::AddEng(SFW_140_150_3, _T("Fixed a bug whereby the current folder was not configured as the folder where the .std file was placed when the program was launched with /open and /start parameters."));

	//9128 (NC7)
	MessageProc::AddJpn(SFW_140_150_4, _T("�X���b�h��~���ɓ�����M�v�f���璷�ȃ\�P�b�g�N���[�Y�̃��O���o�͂���s�ǂ�΍􂵂��B"));
	MessageProc::AddEng(SFW_140_150_4, _T("Fixed a bug whereby redundant logs relating to socket closing were generated by the same receiver element when threads were stopped."));

	//9129 (NC7)
	MessageProc::AddJpn(SFW_140_150_5, _T("IPv6�ɂ��ڑ����T�|�[�g�����B"));
	MessageProc::AddEng(SFW_140_150_5, _T("Support for IPv6 connectivity enabled."));

	//9130 (NC5-Simular)
	MessageProc::AddJpn(SFW_140_150_6, _T("Windows 8.1, Windows 10, Windows Server 2012 R2���T�|�[�g�����B"));
	MessageProc::AddEng(SFW_140_150_6, _T("Support enabled for Windows 8.1, Windows 10 and Windows Server 2012 R2."));

	//9131 (��)
	MessageProc::AddJpn(SFW_150_160_1, _T("TCP receiver�̏I�������Ƃ��āCHTTP�w�b�_��Content-Length�Ɏw�肳�ꂽ�T�C�Y�̃f�[�^����M����P�[�X��V���ɃT�|�[�g�����B"));
	MessageProc::AddEng(SFW_150_160_1, _T("Support enabled for data reception which the specified size of Content-Length in HTTP header as a new terminate condition of TCP receiver."));

	// =====================================================================================================
}

TCHAR* MyMsgProc::GetMsg(int Id)
{
	return MessageProc::GetMsg(Id);
}

void MyMsgProc::StkErr(int Id, HWND WndHndl)
{
	TCHAR Buf[32];
	wsprintf(Buf, _T("Message ID : %d"), Id);
	MessageBox(WndHndl, GetMsg(Id), Buf, MB_OK | MB_ICONSTOP);
}

void MyMsgProc::StkErr(int Id, TCHAR* Str, HWND WndHndl)
{
	TCHAR Buf[32];
	wsprintf(Buf, _T("Message ID : %d"), Id);
	TCHAR MsgBuf[1024];
	wsprintf(MsgBuf, _T("%s\r\n[%s]"),  GetMsg(Id), Str);
	MessageBox(WndHndl, MsgBuf, Buf, MB_OK | MB_ICONSTOP);
}

void MyMsgProc::StkInf(int Id, HWND WndHndl)
{
	TCHAR Buf[32];
	wsprintf(Buf, _T("Message ID : %d"), Id);
	MessageBox(WndHndl, GetMsg(Id), Buf, MB_OK | MB_ICONINFORMATION);
}

void MyMsgProc::StkInf(int Id, TCHAR* Str, HWND WndHndl)
{
	TCHAR Buf[32];
	wsprintf(Buf, _T("Message ID : %d"), Id);
	TCHAR MsgBuf[1024];
	wsprintf(MsgBuf, _T("%s\r\n[%s]"),  GetMsg(Id), Str);
	MessageBox(WndHndl, MsgBuf, Buf, MB_OK | MB_ICONINFORMATION);
}

int MyMsgProc::StkYesNo(int Id, HWND WndHndl)
{
	TCHAR Buf[32];
	wsprintf(Buf, _T("Message ID : %d"), Id);
	int Ret = MessageBox(WndHndl, GetMsg(Id), Buf, MB_YESNO | MB_ICONQUESTION);
	return Ret;
}

int MyMsgProc::StkYesNo(int Id, TCHAR* Str, HWND WndHndl)
{
	TCHAR Buf[32];
	wsprintf(Buf, _T("Message ID : %d"), Id);
	TCHAR MsgBuf[1024];
	wsprintf(MsgBuf, _T("%s\r\n[%s]"),  GetMsg(Id), Str);
	int Ret = MessageBox(WndHndl, MsgBuf, Buf, MB_YESNO | MB_ICONQUESTION);
	return Ret;
}
