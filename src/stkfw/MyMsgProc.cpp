#include "..\..\..\YaizuComLib\src\\msgproc\msgproc.h"
#include "MyMsgProc.h"

void MyMsgProc::AddMsg()
{
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
