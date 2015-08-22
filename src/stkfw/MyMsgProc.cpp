#include "..\..\..\YaizuComLib\src\\msgproc\msgproc.h"
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

	//9125 (��)
	MessageProc::AddJpn(SFW_140_150_1, _T("�C���X�g�[���v���O�������ЂƂ�MSI�t�@�C���ɓ��������B"));
	MessageProc::AddEng(SFW_140_150_1, _T("Installer program integrated into one MSI file."));

	// =====================================================================================================
}

TCHAR* MyMsgProc::GetMsg(int Id)
{
	return MessageProc::GetMsg(Id);
}

void MyMsgProc::StkErr(int Id, HWND WndHndl)
{
	MessageProc::StkErr(Id, WndHndl);
}

void MyMsgProc::StkErr(int Id, TCHAR* Str, HWND WndHndl)
{
	MessageProc::StkErr(Id, Str, WndHndl);
}

void MyMsgProc::StkInf(int Id, HWND WndHndl)
{
	MessageProc::StkInf(Id, WndHndl);
}

void MyMsgProc::StkInf(int Id, TCHAR* Str, HWND WndHndl)
{
	MessageProc::StkInf(Id, Str, WndHndl);
}

int MyMsgProc::StkYesNo(int Id, HWND WndHndl)
{
	return MessageProc::StkYesNo(Id, WndHndl);
}

int MyMsgProc::StkYesNo(int Id, TCHAR* Str, HWND WndHndl)
{
	return MessageProc::StkYesNo(Id, Str, WndHndl);
}
