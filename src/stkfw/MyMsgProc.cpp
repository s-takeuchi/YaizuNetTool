#include "..\..\..\YaizuComLib\src\\msgproc\msgproc.h"
#include "MyMsgProc.h"

void MyMsgProc::AddMsg()
{
	// =====================================================================================================
	//9100 (NC2)
	MessageProc::AddJpn(SFW_100_1, _T("StkFw 初期バージョンをリリースした。"));
	MessageProc::AddEng(SFW_100_1, _T("StkFw initial version was released."));

	//9101 [10015] (NC2)
	MessageProc::AddJpn(SFW_100_110_1, _T("リポジトリデータをセーブ／ロードしたフォルダが，StkFw再起動後の初期フォルダに設定される不具合を修正した。"));
	MessageProc::AddEng(SFW_100_110_1, _T("The bug involving the folder for loaded/saved repository data being configured as the initial folder after restarting StkFw was fixed."));

	//9102 [10017] (NC2)
	MessageProc::AddJpn(SFW_100_110_2, _T("アイコン名の表示がアイコンの中心からずれる不具合を修正した。"));
	MessageProc::AddEng(SFW_100_110_2, _T("The bug involving the icon name being misaligned from the center of the icon was fixed."));

	//9103 [10018, 10020, 10025] (NC2)
	MessageProc::AddJpn(SFW_100_110_3, _T("本ソフトウェアの目的をテスト・フレームワークからテスト支援ソフトウェアに変更した。"));
	MessageProc::AddEng(SFW_100_110_3, _T("The purpose of the software was changed from provision of a test framework to testing support."));

	//9104 [10034] (NC2)
	MessageProc::AddJpn(SFW_100_110_4, _T("ループバックネットワークアダプタ追加／削除ダイアログをサポートした。"));
	MessageProc::AddEng(SFW_100_110_4, _T("Support for addition/removal of a loopback network adapter dialog was added."));

	//9105 [10040] (NC2)
	MessageProc::AddJpn(SFW_100_110_5, _T("OS再起動後に追加/削除したIPアドレスがもとにもどるIPアドレスウィザードの不具合を修正した。"));
	MessageProc::AddEng(SFW_100_110_5, _T("A bug in the Add/remove IP address wizard involving the flushing of added/removed IP addresses after operating system reboot was fixed."));

	//9106 [10052] (NC2)
	MessageProc::AddJpn(SFW_100_110_6, _T("変数管理機能(Variable Controller)をサポートした。"));
	MessageProc::AddEng(SFW_100_110_6, _T("Support for variable management functionality (Variable Controller) was added."));

	//9107 [10074] (NC3)
	MessageProc::AddJpn(SFW_110_120_1, _T("Administratorsグループに属さないユーザーがStkFwを使用できるようにした。"));
	MessageProc::AddEng(SFW_110_120_1, _T("Support enabled for StkFw operation by non-administrator-group users."));

	//9108 [10075] (NC3)
	MessageProc::AddJpn(SFW_110_120_2, _T("スレッドコントローラで通信ログ出力機能をサポートした。"));
	MessageProc::AddEng(SFW_110_120_2, _T("Support enabled for communication logging functionality on thread controller."));

	//9109 [10078] (NC3)
	MessageProc::AddJpn(SFW_110_120_3, _T("Windows 7, Windows Server 2003, Windows Server 2008をサポートした。"));
	MessageProc::AddEng(SFW_110_120_3, _T("Support enabled for Windows 7, Windows Server 2003 and Windows Server 2008."));

	//9110 [10079] (NC3)
	MessageProc::AddJpn(SFW_110_120_4, _T("複数のメインコンソールを同時に起動できるようにした。"));
	MessageProc::AddEng(SFW_110_120_4, _T("Support enabled for simultaneous launch of multiple main consoles."));

	//9111 [10080] (NC3)
	MessageProc::AddJpn(SFW_110_120_5, _T("バックグラウンドプロセスとしてスレッドを実行する機能をサポートした。"));
	MessageProc::AddEng(SFW_110_120_5, _T("Support enabled for thread execution as a background process."));

	//9112 [10081] (NC3)
	MessageProc::AddJpn(SFW_110_120_6, _T("複数の変数のエクスポート／インポートをサポートした。"));
	MessageProc::AddEng(SFW_110_120_6, _T("Support enabled for import and export of multiple variable specifications."));

	//9113 [10083] (NC3)
	MessageProc::AddJpn(SFW_110_120_7, _T("複数のスレッドが1つのスレッドに連結するデータフローで，データフローの終端となる処理要素に処理が到達しても，一部のスレッドの処理が完了しない不具合を修正した。"));
	MessageProc::AddEng(SFW_110_120_7, _T("Fixed bug whereby data flow in which multiple threads leading to a single thread did not terminate even when processing reached the end of the element."));

	//9114 [10084] (NC4)
	MessageProc::AddJpn(SFW_110_120_8, _T("複数のスレッドが1つのスレッドに連結するデータフローで，データが不正に上書きされたり，余分に処理される不具合を修正した。"));
	MessageProc::AddEng(SFW_110_120_8, _T("Bugs relating to invalid data overwritten and unnecessary data processing on data flow in which multiple threads led to a single thread have been fixed."));

	//9115 (NC4)
	MessageProc::AddJpn(SFW_120_130_1, _T("ファイルへの書き込みおよびファイルからの読み込みを行う処理要素をサポートした。"));
	MessageProc::AddEng(SFW_120_130_1, _T("Support enabled for writing/reading of file processing elements."));

	//9116 (NC4)
	MessageProc::AddJpn(SFW_120_130_2, _T("外部プログラムを実行する処理要素をサポートした。"));
	MessageProc::AddEng(SFW_120_130_2, _T("Support enabled for processing of elements that execute external programs."));

	//9117 (NC4)
	MessageProc::AddJpn(SFW_120_130_3, _T("全スレッド一括開始／停止機能をサポートした。"));
	MessageProc::AddEng(SFW_120_130_3, _T("Support enabled for start/stop all threads function."));

	//9118 (NC4)
	MessageProc::AddJpn(SFW_120_130_4, _T("TCP receiverの終了条件を指定できるようにした。新たにデータ長超え検知とデータ一致検知を終了条件として追加した。"));
	MessageProc::AddEng(SFW_120_130_4, _T("Support enabled for specification of TCP receiver termination conditions. Detection of excess data length and data matching newly added as termination conditions."));

	//9119 (NC5)
	MessageProc::AddJpn(SFW_130_140_1, _T("強制クローズと接続先のシャットダウン検知によるクローズの2つのソケットクローズ方法をサポートした。"));
	MessageProc::AddEng(SFW_130_140_1, _T("Support enabled for two socket closure methods (forced close and peer shutdown detection close)."));

	//9120 (NC5)
	MessageProc::AddJpn(SFW_130_140_2, _T("ワークスペースサイズを変更できるようにした。"));
	MessageProc::AddEng(SFW_130_140_2, _T("Support enabled for workspace size change."));

	//9121 (NC5)
	MessageProc::AddJpn(SFW_130_140_3, _T("処理要素の追加に関する階層化されたメニューを提供した。"));
	MessageProc::AddEng(SFW_130_140_3, _T("Support enabled for hierarchical menu for addition of processing element operations."));

	//9122 (NC5)
	MessageProc::AddJpn(SFW_130_140_4, _T("UDP receiver処理要素およびUDP sender処理要素を新たにサポートした。"));
	MessageProc::AddEng(SFW_130_140_4, _T("Support enabled for UDP receiver processing element and UDP sender processing element."));

	//9123 (NC5)
	MessageProc::AddJpn(SFW_130_140_5, _T("ソケットクローズ時に誤った処理要素のIDがログに出力される不良を対策した。"));
	MessageProc::AddEng(SFW_130_140_5, _T("Logged bug relating to invalid ID for processing element fixed."));

	//9124 (NC5)
	MessageProc::AddJpn(SFW_130_140_6, _T("Windows 8, Windows Server 2012, Windows Server 2003 R2, Windows Server 2008 R2をサポートした。"));
	MessageProc::AddEng(SFW_130_140_6, _T("Support enabled for Windows 8, Windows Server 2012, Windows Server 2003 R2 and Windows Server 2008 R2."));

	//9125 (★)
	MessageProc::AddJpn(SFW_140_150_1, _T("インストーラプログラムをひとつのMSIファイルに統合した。"));
	MessageProc::AddEng(SFW_140_150_1, _T("Installer program integrated into one MSI file."));

	// =====================================================================================================
}

TCHAR* MyMsgProc::GetMsg(int Id)
{
	return MessageProc::GetMsg(Id);
}
