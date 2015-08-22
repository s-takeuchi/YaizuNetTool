#include "..\..\..\YaizuComLib\src\\msgproc\msgproc.h"
#include "MyMsgProc.h"

void MyMsgProc::AddMsg()
{
	// =====================================================================================================
	//2101 (NC2)
	MessageProc::AddJpn(STKFW_RUNNINGORPROPOPEN, _T("スレッドが実行中かプロパティダイアログボックスが開いたままのため操作を実行できません。\r\nスレッドを停止するかプロパティダイアログボックスを閉じたあと再度操作を試みてください。"));
	MessageProc::AddEng(STKFW_RUNNINGORPROPOPEN, _T("The operation cannot be performed because threads are running and/or a property dialog box is open.\r\nStop all threads and/or close the property dialog box, then try again."));

	//2102 (NC2)
	MessageProc::AddJpn(STKFW_OUTOFRANGE, _T("範囲指定エラーが発生しました。\r\n適切なワークスペースのサイズを指定してください。\r\n  - 幅 [512 ～ 2048]\r\n  - 高さ [400 ～ 2048]"));
	MessageProc::AddEng(STKFW_OUTOFRANGE, _T("An out-of-range error has occurred.\r\nSpecify a valid workspace size.\r\n  - Width [512 to 2048]\r\n  - Height [400 to 2048]"));

	//2103 (NC1)
	MessageProc::AddJpn(STKFW_DATASAVEFAILED, _T("データの保存に失敗しました。\r\n次の項目を確認してください。\r\n- 対象フォルダのアクセス権限が正しいか。\r\n- 指定したファイルが他のプログラムで既に使用されていないか。"));
	MessageProc::AddEng(STKFW_DATASAVEFAILED, _T("Data save failed.\r\nCheck the items below.\r\n- Whether the access rights of the target folder are correct.\r\n- The specified file has not already been used by another program."));

	//2104 (NC3)
	MessageProc::AddJpn(STKFW_FILEINVALID, _T("指定されたファイルは不正です。\r\n次の項目を確認してください。\r\n- 適切なファイルパスが指定されているか。\r\n- 指定されたファイルはこのプログラムを用いて生成されているか。\r\n- ファイルのアクセス権限が正しいか。"));
	MessageProc::AddEng(STKFW_FILEINVALID, _T("The specified file is invalid.\r\nCheck the items below.\r\n- A valid file path is specified.\r\n- The specified file was created using this program.\r\n- The access rights of the file are correct."));

	//2106 (---)
	MessageProc::AddJpn(STKFW_RUNNING, _T("実行中..."));
	MessageProc::AddEng(STKFW_RUNNING, _T("Running..."));

	//2107 (NC1)
	MessageProc::AddJpn(STKFW_NODLL, _T("DLLファイルが存在しません。\r\nこのプログラムからアクセス可能な適切なフォルダにDLLファイルをコピーしてください。"));
	MessageProc::AddEng(STKFW_NODLL, _T("No DLL file exists.\r\nCopy the DLL file to an appropriate folder that can be accessed by this program."));

	//2108 (NC1)
	MessageProc::AddJpn(STKFW_DLLINVALID, _T("ロードされたDLLファイルは不正です。\r\nDLLが次の関数を実装しているか確認してください。\r\n[DllShowProperty]"));
	MessageProc::AddEng(STKFW_DLLINVALID, _T("The loaded DLL is invalid.\r\nCheck that the DLL implements the following function:\r\n[DllShowProperty]"));

	//2110 (---)
	MessageProc::AddJpn(STKFW_ADD_PROCESSING_ELEMENT, _T("処理要素の追加"));
	MessageProc::AddEng(STKFW_ADD_PROCESSING_ELEMENT, _T("Add Processing Element"));

	//2111 (---)
	MessageProc::AddJpn(STKFW_DEL_PROCESSING_ELEMENT, _T("処理要素の削除"));
	MessageProc::AddEng(STKFW_DEL_PROCESSING_ELEMENT, _T("Delete Processing Element"));

	//2112 (---)
	MessageProc::AddJpn(STKFW_ADD_LINK, _T("関連線の追加"));
	MessageProc::AddEng(STKFW_ADD_LINK, _T("Add Link"));

	//2113 (---)
	MessageProc::AddJpn(STKFW_DEL_LINK, _T("関連線の削除"));
	MessageProc::AddEng(STKFW_DEL_LINK, _T("Delete Link"));

	//2120 (NC3)
	MessageProc::AddJpn(STKFW_DBVERSION_OLD, _T("読み込んだファイルは古いバージョンのStkFwを用いて作成されています。\r\n現在のバージョンで使用できるようにStkFwはデータを変換します。"));
	MessageProc::AddEng(STKFW_DBVERSION_OLD, _T("The loaded file was generated with an old version of StkFw.\r\nIn order to use the file with the current version, StkFw will migrate the data."));

	//2121 (NC3)
	MessageProc::AddJpn(STKFW_DBVERSION_UNKNOWN, _T("読み込んだファイルは不明なバージョンのStkFwを用いて作成されています。\r\nStkFwはこのファイルを使用することができません。"));
	MessageProc::AddEng(STKFW_DBVERSION_UNKNOWN, _T("The loaded file was generated with an unknown version of StkFw.\r\nStkFw cannot handle this file."));

	//2123 (NC3)
	MessageProc::AddJpn(STKFW_COMPARAM_INVALID, _T("指定されたパラメータは不正です。\r\n指定可能なパラメータは，/start，/stopall，/open のみです。"));
	MessageProc::AddEng(STKFW_COMPARAM_INVALID, _T("The specified parameter is invalid.\r\nThe only valid parameters are /start, /stopall and /open."));

	//2124 (NC3)
	MessageProc::AddJpn(STKFW_COMPARAM_NOFILE, _T("指定されたパラメータは不正です。\r\n/startおよび/openパラメータにはSTDファイルへのパス指定が必要です。"));
	MessageProc::AddEng(STKFW_COMPARAM_NOFILE, _T("The specified parameter is invalid.\r\nThe file path to the STD file must be input after the parameters (/start and /open) are specified."));

	//2125 (---)
	MessageProc::AddJpn(STKFW_MANUAL_PLACE, _T("\\manual\\jpn\\index.htm"));
	MessageProc::AddEng(STKFW_MANUAL_PLACE, _T("\\manual\\eng\\index.htm"));

	//2126 (---)
	MessageProc::AddJpn(STKFW_CHG_WORKSPACE_SIZE, _T("ワークスペースサイズ変更"));
	MessageProc::AddEng(STKFW_CHG_WORKSPACE_SIZE, _T("Change workspace size"));

	//2127 (---)
	MessageProc::AddJpn(STKFW_GRID_ONOFF, _T("グリッド"));
	MessageProc::AddEng(STKFW_GRID_ONOFF, _T("Grid"));

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
