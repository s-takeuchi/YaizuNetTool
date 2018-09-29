#include "..\..\..\YaizuComLib\src\\commonfunc\msgproc.h"
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
	//2201 (NC2)
	MessageProc::AddJpn(VAR_SELECTEDNOTONE, _T("変数が指定されていないか，2つ以上の変数が指定されました。\r\n1つの変数のみ指定可能です。"));
	MessageProc::AddEng(VAR_SELECTEDNOTONE, _T("No variable or more than one variable has been specified.\r\nOnly one variable may be specified."));

	//2202 (NC2)
	MessageProc::AddJpn(VAR_AREYOUSUREDELETE, _T("指定した変数を削除しても良いですか。"));
	MessageProc::AddEng(VAR_AREYOUSUREDELETE, _T("Are you sure you want to delete the specified variable(s)?"));

	//2203 (NC2)
	MessageProc::AddJpn(VAR_NOITEMSELECTED, _T("変数が指定されていません。\r\n１つ以上の変数を指定する必要があります。"));
	MessageProc::AddEng(VAR_NOITEMSELECTED, _T("No variable has been specified.\r\nPlease specify one or more variables."));

	//2204 (NC2)
	MessageProc::AddJpn(VAR_NOTTRANSUTF8, _T("UTF-8に変換できないコードが存在するため，\r\nUFT-8表示画面に遷移できません。"));
	MessageProc::AddEng(VAR_NOTTRANSUTF8, _T("The screen cannot be changed to UTF-8 view \r\nbecause the program has found code that cannot be rendered in UTF-8."));

	//2205 (NC2)
	MessageProc::AddJpn(VAR_INVALIDNAME, _T("不正な変数名が指定されました。\r\n指定した変数名を確認して再度実行してください。"));
	MessageProc::AddEng(VAR_INVALIDNAME, _T("Invalid variable name specified.\r\nCheck the specified variable name and then try again."));

	//2206 (NC2)
	MessageProc::AddJpn(VAR_ALREADYDELETED, _T("編集対象の変数は既に削除されています。\r\n編集操作は実行できません。"));
	MessageProc::AddEng(VAR_ALREADYDELETED, _T("The edit operation can not be performed because \r\nthe edit target variable has been deleted."));

	//2207 (NC2)
	MessageProc::AddJpn(VAR_INVALIDTYPE, _T("編集対象の変数は既に異なる種別の変数として使用されています。\r\n編集操作は実行できません。"));
	MessageProc::AddEng(VAR_INVALIDTYPE, _T("The edit operation can not be performed because \r\nthe target variable has already been used as another type of variable."));

	//2208 (NC3)
	MessageProc::AddJpn(VAR_BUFOVERFLOW, _T("変数の長さが上限の10Mバイトを超えました。\r\n上限を超えたデータは切り取られます。"));
	MessageProc::AddEng(VAR_BUFOVERFLOW, _T("The length of the variable specified exceeds the upper limit of 10 MB.\r\nAny data over this limit will be omitted."));

	//2209 (NC2)
	MessageProc::AddJpn(VAR_MAXVARSIZE, _T("変数を格納するメモリ容量が上限を超えました。"));
	MessageProc::AddEng(VAR_MAXVARSIZE, _T("The memory size available for storing variable data has exceeded the upper limit."));

	//2210 (NC3)
	MessageProc::AddJpn(VAR_FLAGVARNOT, _T("フラグ用変数は，インポート／エクスポートを行うことはできません。"));
	MessageProc::AddEng(VAR_FLAGVARNOT, _T("Import/export operation of the flag variable cannot be performed."));

	//2211 (NC3)
	MessageProc::AddJpn(VAR_FOLDERSETERR, _T("指定されたインポート，エクスポートフォルダは不正です。\r\nフォルダを確認し，再度操作を実行してください。"));
	MessageProc::AddEng(VAR_FOLDERSETERR, _T("An invalid import/export folder has been specified.\r\nCheck the folder and try again."));

	//2212 (NC3)
	MessageProc::AddJpn(VAR_IMPERR, _T("インポート操作が失敗しました。\r\nフォルダのアクセス権限またはファイル名を確認してください。"));
	MessageProc::AddEng(VAR_IMPERR, _T("Import operation failed.\r\nCheck the folder permissions and file names."));

	//2213 (NC3)
	MessageProc::AddJpn(VAR_EXPERR, _T("エクスポート操作が失敗しました。\r\nフォルダのアクセス権限や空きディスク容量，選択した変数名を確認してください。"));
	MessageProc::AddEng(VAR_EXPERR, _T("Export operation failed.\r\nCheck the folder permissions, the amount of free disk space and the variable names specified."));

	//2214 (NC3)
	MessageProc::AddJpn(VAR_NOIMPTARGET, _T("指定したフォルダにはインポート対象ファイルが存在しません。\r\nインポート対象ファイルの拡張子は\".xxx\"である必要があります。"));
	MessageProc::AddEng(VAR_NOIMPTARGET, _T("No import target file exists in the folder specified.\r\nThe extension of import target files must be \".xxx\"."));

	//2215 (NC3)
	MessageProc::AddJpn(VAR_NOEXPTARGET, _T("変数が指定されていません。\r\n一つ以上の変数を指定する必要があります。"));
	MessageProc::AddEng(VAR_NOEXPTARGET, _T("No variables have been specified.\r\nMore than one variable must be specified."));

	// =====================================================================================================
	// 2300 (---)
	MessageProc::AddJpn(PROP_NAME, _T("名称"));
	MessageProc::AddEng(PROP_NAME, _T("Name"));

	// 2301 (NC2)
	MessageProc::AddJpn(PROP_CHKDAT_START, _T("入力データは...から開始する"));
	MessageProc::AddEng(PROP_CHKDAT_START, _T("Input data starts with..."));

	// 2302 (NC2)
	MessageProc::AddJpn(PROP_CHKDAT_NSTART, _T("入力データは...から開始しない"));
	MessageProc::AddEng(PROP_CHKDAT_NSTART, _T("Input data does not start with..."));

	// 2303 (NC2)
	MessageProc::AddJpn(PROP_CHKDAT_END, _T("入力データは...で終了する"));
	MessageProc::AddEng(PROP_CHKDAT_END, _T("Input data ends with..."));

	// 2304 (NC2)
	MessageProc::AddJpn(PROP_CHKDAT_NEND, _T("入力データは...で終了しない"));
	MessageProc::AddEng(PROP_CHKDAT_NEND, _T("Input data does not end with..."));

	// 2305 (NC2)
	MessageProc::AddJpn(PROP_CHKDAT_CONT, _T("入力データは...を含む"));
	MessageProc::AddEng(PROP_CHKDAT_CONT, _T("Input data contains..."));

	// 2306 (NC2)
	MessageProc::AddJpn(PROP_CHKDAT_NCONT, _T("入力データは...を含まない"));
	MessageProc::AddEng(PROP_CHKDAT_NCONT, _T("Input data does not contain..."));

	// 2307 (NC2)
	MessageProc::AddJpn(PROP_CHKDAT_EQUAL, _T("入力データは...と一致する"));
	MessageProc::AddEng(PROP_CHKDAT_EQUAL, _T("Input data is equal to..."));

	// 2308 (NC2)
	MessageProc::AddJpn(PROP_CHKDAT_NEQUAL, _T("入力データは...と一致しない"));
	MessageProc::AddEng(PROP_CHKDAT_NEQUAL, _T("Input data is not equal to..."));

	// 2311 (NC2)
	MessageProc::AddJpn(PROP_CHGDAT_INSERT, _T("入力データの開始バイトに(A)を挿入する"));
	MessageProc::AddEng(PROP_CHGDAT_INSERT, _T("Insert (A) at the start byte of the input data."));

	// 2312 (NC2)
	MessageProc::AddJpn(PROP_CHGDAT_JOIN, _T("入力データの終了バイトに(A)を連結する"));
	MessageProc::AddEng(PROP_CHGDAT_JOIN, _T("Join (A) to the end byte of the input data."));

	// 2313 (NC2)
	MessageProc::AddJpn(PROP_CHGDAT_REPLACE, _T("入力データから(A)を検索し(B)に置き換える"));
	MessageProc::AddEng(PROP_CHGDAT_REPLACE, _T("Search for (A) in the input data and replace with (B)."));

	// 2314 (NC2)
	MessageProc::AddJpn(PROP_CHGDAT_EXTRACT, _T("入力データから(A)で始まり(B)で終わる領域を抽出する"));
	MessageProc::AddEng(PROP_CHGDAT_EXTRACT, _T("Extract an area that starts with (A) and ends with (B) from the input data."));

	// 2315 (NC2)
	MessageProc::AddJpn(PROP_CHGDAT_DROP, _T("入力データを捨て空データを返す"));
	MessageProc::AddEng(PROP_CHGDAT_DROP, _T("Drop the input data and return empty data."));

	// 2316 (NC2)
	MessageProc::AddJpn(PROP_CHGDAT_RESET, _T("入力データを捨て(A)にリセットする"));
	MessageProc::AddEng(PROP_CHGDAT_RESET, _T("Drop the input data and reset to (A)."));

	// 2320 (NC2)
	MessageProc::AddJpn(PROP_CLOSEPORT, _T("クローズするソケット"));
	MessageProc::AddEng(PROP_CLOSEPORT, _T("Socket to be closed"));

	// 2321 (NC2)
	MessageProc::AddJpn(PROP_TIMER_PAST, _T("次に示す日付と時刻が経過したら次のステップに移る"));
	MessageProc::AddEng(PROP_TIMER_PAST, _T("Progress to the next step if the date and time shown below are in the past."));

	// 2322 (NC2)
	MessageProc::AddJpn(PROP_TIMER_WAIT, _T("一定時間待ったあと次のステップに移る"));
	MessageProc::AddEng(PROP_TIMER_WAIT, _T("Progress to the next step after sleeping."));

	// 2323 (---)
	MessageProc::AddJpn(PROP_TIMER_SEC, _T("(秒) 0-3600"));
	MessageProc::AddEng(PROP_TIMER_SEC, _T("(Sec) 0-3600"));

	// 2324 (NC2)
	MessageProc::AddJpn(PROP_MAP_SEARCH, _T("検索対象変数名のプレフィックス"));
	MessageProc::AddEng(PROP_MAP_SEARCH, _T("Prefix of search target variable name."));

	// 2325 (NC2)
	MessageProc::AddJpn(PROP_MAP_REPLACE, _T("置換え対象変数名のプレフィックス"));
	MessageProc::AddEng(PROP_MAP_REPLACE, _T("Prefix of replacement target variable name"));

	// 2326 (NC2)
	MessageProc::AddJpn(PROP_MAP_START, _T("次の値から自動採番される"));
	MessageProc::AddEng(PROP_MAP_START, _T("Auto numbering from the next value"));

	// 2327 (NC3)
	MessageProc::AddJpn(PROP_MAP_USEONCE, _T("各変数へのマッピングは一度だけ使用される"));
	MessageProc::AddEng(PROP_MAP_USEONCE, _T("The mapping to each variable is used only once."));

	// 2331 (NC2)
	MessageProc::AddJpn(PROP_CHECK_TRUE, _T("TRUEならば次のステップに移る"));
	MessageProc::AddEng(PROP_CHECK_TRUE, _T("If TRUE, progress to the next step."));

	// 2332 (NC2)
	MessageProc::AddJpn(PROP_CHECK_FALSE, _T("FALSEならば次のステップに移る"));
	MessageProc::AddEng(PROP_CHECK_FALSE, _T("If FALSE, progress to the next step."));

	// 2333 (NC2)
	MessageProc::AddJpn(PROP_CHANGE_TRUE, _T("フラグをTRUEにする"));
	MessageProc::AddEng(PROP_CHANGE_TRUE, _T("Change flag to TRUE."));

	// 2334 (NC2)
	MessageProc::AddJpn(PROP_CHANGE_FALSE, _T("フラグをFALSEにする"));
	MessageProc::AddEng(PROP_CHANGE_FALSE, _T("Change flag to FALSE."));

	// 2341 (NC2)
	MessageProc::AddJpn(PROP_LOAD_VAR, _T("次の変数からデータを読込む"));
	MessageProc::AddEng(PROP_LOAD_VAR, _T("Load data from the following variable."));

	// 2342 (NC2)
	MessageProc::AddJpn(PROP_LOAD_CONT, _T("次の変数から連続的にデータを読込む"));
	MessageProc::AddEng(PROP_LOAD_CONT, _T("Load data from the following variables continuously."));

	// 2343 (NC2)
	MessageProc::AddJpn(PROP_STORE_VAR, _T("次の変数にデータを書き込む"));
	MessageProc::AddEng(PROP_STORE_VAR, _T("Store data into the following variable."));

	// 2344 (NC2)
	MessageProc::AddJpn(PROP_STORE_CONT, _T("次の変数に連続的にデータを書き込む"));
	MessageProc::AddEng(PROP_STORE_CONT, _T("Store data into the following variables continuously."));

	// 2345 (---)
	MessageProc::AddJpn(PROP_DATA_COMM, _T("コミュニケーション用変数"));
	MessageProc::AddEng(PROP_DATA_COMM, _T("Communication variable"));

	// 2346 (---)
	MessageProc::AddJpn(PROP_DATA_PREF, _T("変数名のプレフィックス"));
	MessageProc::AddEng(PROP_DATA_PREF, _T("Prefix of variable name"));

	// 2347 (NC3)
	MessageProc::AddJpn(PROP_DATA_NUM, _T("次の値からの自動採番"));
	MessageProc::AddEng(PROP_DATA_NUM, _T("Auto numbering from the next value"));

	// 2351 (NC2)
	MessageProc::AddJpn(PROP_NET_RECV, _T("指定したIPアドレスとポートからデータを受信する"));
	MessageProc::AddEng(PROP_NET_RECV, _T("Receive data using the specified IP address and port."));

	// 2352 (NC5)
	MessageProc::AddJpn(PROP_NET_RECVTGT, _T("指定した送信要素の接続先からデータを受信する"));
	MessageProc::AddEng(PROP_NET_RECVTGT, _T("Receive data from the connection target of the specified sender element."));

	// 2353 (NC2)
	MessageProc::AddJpn(PROP_NET_SEND, _T("指定したIPアドレスとポートにデータを送信する"));
	MessageProc::AddEng(PROP_NET_SEND, _T("Send data to the specified IP address and port."));

	// 2354 (NC5)
	MessageProc::AddJpn(PROP_NET_SENDTGT, _T("指定した受信要素の接続先にデータを送信する"));
	MessageProc::AddEng(PROP_NET_SENDTGT, _T("Send data to the connection target of the specified receiver element."));

	// 2355 (NC2)
	MessageProc::AddJpn(PROP_NET_CLOSE_AFTERSEND, _T("データ送信後ソケットをクローズする"));
	MessageProc::AddEng(PROP_NET_CLOSE_AFTERSEND, _T("Close socket after sending data."));

	// 2356 (NC2)
	MessageProc::AddJpn(PROP_NET_CLOSE_AFTERRECV, _T("データ受信後ソケットをクローズする"));
	MessageProc::AddEng(PROP_NET_CLOSE_AFTERRECV, _T("Close socket after receiving data."));

	// 2357 (NC4)
	MessageProc::AddJpn(PROP_NET_TIMEOUT, _T("最終アクセス以降にタイムアウトを検知した"));
	MessageProc::AddEng(PROP_NET_TIMEOUT, _T("Time-out detected after last access."));

	// 2358 (---)
	MessageProc::AddJpn(PROP_NET_SENDER, _T("送信要素名"));
	MessageProc::AddEng(PROP_NET_SENDER, _T("Sender name"));

	// 2359 (---)
	MessageProc::AddJpn(PROP_NET_RECEIVER, _T("受信要素名"));
	MessageProc::AddEng(PROP_NET_RECEIVER, _T("Receiver name"));

	// 2360 (---)
	MessageProc::AddJpn(PROP_NET_ICON, _T("アイコン"));
	MessageProc::AddEng(PROP_NET_ICON, _T("Icon"));

	// 2361 (---)
	MessageProc::AddJpn(PROP_NET_IPADDR, _T("IPアドレス/ホスト名"));
	MessageProc::AddEng(PROP_NET_IPADDR, _T("IP address/hostname"));

	// 2362 (---)
	MessageProc::AddJpn(PROP_NET_PORT, _T("ポート番号"));
	MessageProc::AddEng(PROP_NET_PORT, _T("Port"));

	// 2363 (NC4)
	MessageProc::AddJpn(PROP_FILEACCESS_NAME, _T("プログラムがアクセスするファイル名を指定\r\nカレントフォルダからの相対パスを指定する必要がある。(例:\"..\\data\\test.bin\")\r\nカレントフォルダは通常，対象の\".std\"ファイルが格納されているフォルダとなる。"));
	MessageProc::AddEng(PROP_FILEACCESS_NAME, _T("Specify the file name used by the program. \r\nThe relative path from the current folder should be given (ex: \"..\\data\\test.bin\"). \r\nThe current folder is normally set as the one containing the target \".std\" file."));

	// 2364 (NC4)
	MessageProc::AddJpn(PROP_FILEACCESSW_ADD, _T("既存のファイルの最後にデータを連結する"));
	MessageProc::AddEng(PROP_FILEACCESSW_ADD, _T("Add data to the end of the existing file."));

	// 2365 (NC4)
	MessageProc::AddJpn(PROP_FILEACCESSW_INSERT, _T("既存のファイルの先頭ににデータを挿入する"));
	MessageProc::AddEng(PROP_FILEACCESSW_INSERT, _T("Insert data at the start of the existing file."));

	// 2366 (NC4)
	MessageProc::AddJpn(PROP_FILEACCESSW_OVERWRITE, _T("既存のファイルを上書きする"));
	MessageProc::AddEng(PROP_FILEACCESSW_OVERWRITE, _T("Overwrite the existing file."));

	// 2367 (NC4)
	MessageProc::AddJpn(PROP_FILEACCESSR_ADD, _T("入力データの終了バイトに読み込んだデータを連結する"));
	MessageProc::AddEng(PROP_FILEACCESSR_ADD, _T("Add loaded data to the end byte of the input data."));

	// 2368 (NC4)
	MessageProc::AddJpn(PROP_FILEACCESSR_INSERT, _T("入力データの開始バイトに読み込んだデータを挿入する"));
	MessageProc::AddEng(PROP_FILEACCESSR_INSERT, _T("Insert loaded data at the start byte of the input data."));

	// 2369 (NC4)
	MessageProc::AddJpn(PROP_FILEACCESSR_OVERWRITE, _T("ファイルから読み込んだデータを出力する"));
	MessageProc::AddEng(PROP_FILEACCESSR_OVERWRITE, _T("Output data read from the file."));

	// 2370 (NC4)
	MessageProc::AddJpn(PROP_EXECPROG_COMMAND, _T("外部プログラムへのパスを指定"));
	MessageProc::AddEng(PROP_EXECPROG_COMMAND, _T("Specify the path to the external program."));

	// 2371 (NC4)
	MessageProc::AddJpn(PROP_EXECPROG_WAIT, _T("実行したプログラムが終了するまで待機する"));
	MessageProc::AddEng(PROP_EXECPROG_WAIT, _T("Wait until the program executed is finished."));

	// 2372 (NC4)
	MessageProc::AddJpn(PROP_EXECPROG_CURRDIR, _T("外部プログラム実行時のカレントフォルダを指定\r\nカレントフォルダを指定しない場合，対象の\".std\"ファイルが配置されたフォルダがカレントフォルダとなる。"));
	MessageProc::AddEng(PROP_EXECPROG_CURRDIR, _T("Specify the current folder during external program execution. \r\nIf the current folder is not specified, the one containing the target \".std\" file will be set."));

	// 2373 (NC4)
	MessageProc::AddJpn(PROP_EXECPROG_STDOUT, _T("外部プログラムがSTDOUTへ書き込んだデータを次の処理要素に渡す"));
	MessageProc::AddEng(PROP_EXECPROG_STDOUT, _T("Pass data written by the external program to STDOUT to the next element."));

	// 2374 (NC4)
	MessageProc::AddJpn(PROP_EXECPROG_STDIN, _T("本処理要素の入力データを外部プログラムのSTDINに渡す"));
	MessageProc::AddEng(PROP_EXECPROG_STDIN, _T("Pass the input data of this processing element to STDIN."));

	// 2375 (NC4)
	MessageProc::AddJpn(PROP_NET_UNCOND, _T("無条件で次の処理要素に移る"));
	MessageProc::AddEng(PROP_NET_UNCOND, _T("Proceed unconditionally to the next processing element."));

	// 2376 (★)
	MessageProc::AddJpn(PROP_NET_EXCEEDSIZE, _T("受信データサイズが指定した値に達した [1-9,999,999 バイト]"));
	MessageProc::AddEng(PROP_NET_EXCEEDSIZE, _T("The size of the data received reached the preset value. [1-9,999,999 bytes]"));

	// 2377 (★)
	MessageProc::AddJpn(PROP_NET_RECVSTR, _T("指定したデータを受信した"));
	MessageProc::AddEng(PROP_NET_RECVSTR, _T("Specified data received."));

	// 2378 (NC4)
	MessageProc::AddJpn(PROP_NET_TERMCOND, _T("終了条件"));
	MessageProc::AddEng(PROP_NET_TERMCOND, _T("Termination condition"));

	// 2379 (NC4)
	MessageProc::AddJpn(PROP_NET_CLOSEDETECT, _T("送信側ソケットがクローズされたときだけ次の処理要素に移る"));
	MessageProc::AddEng(PROP_NET_CLOSEDETECT, _T("Proceed to the next processing element only when the sender socket is closed."));

	// 2380 (---)
	MessageProc::AddJpn(PROP_NET_CLOSEFORCE, _T("強制的にクローズする"));
	MessageProc::AddEng(PROP_NET_CLOSEFORCE, _T("Force close"));

	// 2381 (---)
	MessageProc::AddJpn(PROP_NET_CLOSEUDPPORT, _T("UDPソケットをクローズする"));
	MessageProc::AddEng(PROP_NET_CLOSEUDPPORT, _T("Close UDP socket"));

	// 2382 (---)
	MessageProc::AddJpn(PROP_NET_CLOSETCPPORT, _T("TCPソケットをクローズする"));
	MessageProc::AddEng(PROP_NET_CLOSETCPPORT, _T("Close TCP socket"));

	// 2383 (NC6)
	MessageProc::AddJpn(PROP_NET_PROCEEDEVENIFNODATARECV, _T("データ未受信でも次の処理要素に遷移する"));
	MessageProc::AddEng(PROP_NET_PROCEEDEVENIFNODATARECV, _T("Proceed even if no data are received."));

	// 2384 (NC7)
	MessageProc::AddJpn(PROP_NET_RECVMULTI, _T("指定した受信要素からデータを受信する"));
	MessageProc::AddEng(PROP_NET_RECVMULTI, _T("Receive data from the specified receiver element."));

	// 2385 (★)
	MessageProc::AddJpn(PROP_NET_HTTPCONTLEN, _T("HTTPヘッダのContent-Lengthで指定したサイズのデータを受信した"));
	MessageProc::AddEng(PROP_NET_HTTPCONTLEN, _T("Data which size specified in Content-Length in HTTP header received."));

	// 2386 (★)
	MessageProc::AddJpn(PROP_NET_TIMEOUTINTERVAL, _T("タイムアウト(msec)"));
	MessageProc::AddEng(PROP_NET_TIMEOUTINTERVAL, _T("Timeout(msec)"));

	// 2387 (★)
	MessageProc::AddJpn(PROP_HTTPHEADER_DELETEFROM, _T("入力データからHTTPヘッダを取り除く"));
	MessageProc::AddEng(PROP_HTTPHEADER_DELETEFROM, _T("Delete HTTP header from input data"));

	// 2388 (★)
	MessageProc::AddJpn(PROP_HTTPHEADER_INSERTINTO, _T("出力データにHTTPヘッダを挿入する"));
	MessageProc::AddEng(PROP_HTTPHEADER_INSERTINTO, _T("Insert HTTP header into output data"));

	// 2389 (★)
	MessageProc::AddJpn(PROP_HTTPHEADER_CONTLEN, _T("Content-Length"));
	MessageProc::AddEng(PROP_HTTPHEADER_CONTLEN, _T("Content-Length"));

	// 2390 (★)
	MessageProc::AddJpn(PROP_HTTPHEADER_DATE, _T("Date"));
	MessageProc::AddEng(PROP_HTTPHEADER_DATE, _T("Date"));

	// 2391 (★)
	MessageProc::AddJpn(PROP_HTTPHEADER_REQUEST, _T("Request"));
	MessageProc::AddEng(PROP_HTTPHEADER_REQUEST, _T("Request"));

	// 2392 (★)
	MessageProc::AddJpn(PROP_HTTPHEADER_RESPONSE, _T("Response"));
	MessageProc::AddEng(PROP_HTTPHEADER_RESPONSE, _T("Response"));

	// =====================================================================================================
	// 2400 (---)
	MessageProc::AddJpn(STKFW_LOG_TITLE, _T("StkFw - スレッドコントローラ\r\n"));
	MessageProc::AddEng(STKFW_LOG_TITLE, _T("StkFw - Thread controller\r\n"));

	// 2401 (NC3)
	MessageProc::AddJpn(STKFW_LOG_START, _T("スレッドコントローラはログの出力を開始しました。\r\n"));
	MessageProc::AddEng(STKFW_LOG_START, _T("The thread controller has started logging.\r\n"));

	// 2402 (NC3)
	MessageProc::AddJpn(STKFW_LOG_STOP, _T("スレッドコントローラはログの出力を停止しました。\r\n"));
	MessageProc::AddEng(STKFW_LOG_STOP, _T("The thread controller has stopped logging.\r\n"));

	// =====================================================================================================
	// 2500 - 2899 : Reserved by server code

	// =====================================================================================================
	//2902 (NC2)
	MessageProc::AddJpn(FILEACCESSERROR, _T("ファイルアクセスエラーが発生しました。"));
	MessageProc::AddEng(FILEACCESSERROR, _T("A file access error has occurred."));

	//2903 (NC1)
	MessageProc::AddJpn(NEEDADMINRIGHTS, _T("このプログラムを実行するためにはLocal Administratorの権限が必要です。\r\nプログラムは終了します。\r\n\r\n"));
	MessageProc::AddEng(NEEDADMINRIGHTS, _T("You need local administrator's rights to run this program.\r\nThe program will be terminated.\r\n\r\n"));

	//2904 (NC3)
	MessageProc::AddJpn(DATAUPDATED, _T("プログラムが使用するデータは更新されています。\r\nデータが失われますが操作を続けて良いですか。"));
	MessageProc::AddEng(DATAUPDATED, _T("Program data updated.\r\nData will be lost. Continue operation?"));

	//2931 (---)
	MessageProc::AddJpn(COMMON_ADD, _T("追加"));
	MessageProc::AddEng(COMMON_ADD, _T("Add"));

	//2932 (---)
	MessageProc::AddJpn(COMMON_DELETE, _T("削除"));
	MessageProc::AddEng(COMMON_DELETE, _T("Delete"));

	//2933 (---)
	MessageProc::AddJpn(COMMON_EDIT, _T("編集"));
	MessageProc::AddEng(COMMON_EDIT, _T("Edit"));

	//2934 (---)
	MessageProc::AddJpn(COMMON_REFRESH, _T("更新"));
	MessageProc::AddEng(COMMON_REFRESH, _T("Refresh"));

	//2935 (---)
	MessageProc::AddJpn(COMMON_TRUE, _T("True"));
	MessageProc::AddEng(COMMON_TRUE, _T("True"));

	//2936 (---)
	MessageProc::AddJpn(COMMON_FALSE, _T("False"));
	MessageProc::AddEng(COMMON_FALSE, _T("False"));

	//2937 (---)
	MessageProc::AddJpn(COMMON_UNKNOWN, _T("不明"));
	MessageProc::AddEng(COMMON_UNKNOWN, _T("Unknown"));

	//2941 (---)
	MessageProc::AddJpn(COMMON_OK, _T("OK"));
	MessageProc::AddEng(COMMON_OK, _T("OK"));

	//2942 (---)
	MessageProc::AddJpn(COMMON_CANCEL, _T("ｷｬﾝｾﾙ"));
	MessageProc::AddEng(COMMON_CANCEL, _T("Cancel"));

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

	//9125 (NC7)
	MessageProc::AddJpn(SFW_140_150_1, _T("インストーラプログラム（ファイル）をひとつのMSIファイルに統合した。"));
	MessageProc::AddEng(SFW_140_150_1, _T("Installer program files integrated into a single MSI file."));

	//9126 (NC7)
	MessageProc::AddJpn(SFW_140_150_2, _T("同一ポートで複数クライアントからの同時接続を可能にした。"));
	MessageProc::AddEng(SFW_140_150_2, _T("Support enabled for multiple-client connections using the same port number."));

	//9127 (NC7)
	MessageProc::AddJpn(SFW_140_150_3, _T("/openまたは/startパラメータ指定で起動したときに，カレントフォルダが.stdファイルが配置されたフォルダと異なる不良を対策した。"));
	MessageProc::AddEng(SFW_140_150_3, _T("Fixed a bug whereby the current folder was not configured as the folder where the .std file was placed when the program was launched with /open and /start parameters."));

	//9128 (NC7)
	MessageProc::AddJpn(SFW_140_150_4, _T("スレッド停止時に同じ受信要素が冗長なソケットクローズのログを出力する不良を対策した。"));
	MessageProc::AddEng(SFW_140_150_4, _T("Fixed a bug whereby redundant logs relating to socket closing were generated by the same receiver element when threads were stopped."));

	//9129 (NC7)
	MessageProc::AddJpn(SFW_140_150_5, _T("IPv6による接続をサポートした。"));
	MessageProc::AddEng(SFW_140_150_5, _T("Support for IPv6 connectivity enabled."));

	//9130 (NC5-Simular)
	MessageProc::AddJpn(SFW_140_150_6, _T("Windows 8.1, Windows 10, Windows Server 2012 R2をサポートした。"));
	MessageProc::AddEng(SFW_140_150_6, _T("Support enabled for Windows 8.1, Windows 10 and Windows Server 2012 R2."));

	//9131 (★)
	MessageProc::AddJpn(SFW_150_160_1, _T("TCP receiverの終了条件として，HTTPヘッダのContent-Lengthに指定されたサイズのデータを受信するケースを新たにサポートした。"));
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
