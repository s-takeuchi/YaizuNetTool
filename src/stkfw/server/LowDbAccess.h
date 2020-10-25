#pragma once
#include <tchar.h>
#include "..\..\..\..\YaizuComLib\src\\stkdata\stkdata.h"

class LowDbAccess
{
private:
	// This instance
	static LowDbAccess* ThisInstance;

private:
	// Constructor
	LowDbAccess();
	// Destructor
	~LowDbAccess();

public:
	// Get this instance
	static LowDbAccess* GetInstance();

	// Propertyテーブル
	int GetPropertyInteger(TCHAR*, int);
	void SetPropertyInteger(TCHAR*, int, int);
	void InsertProperty(TCHAR*, int, int, int, TCHAR*, TCHAR*, TCHAR*);
	void DeleteProperty(TCHAR*);
	void DeleteProperty(TCHAR*, int, int, int, TCHAR*, TCHAR*, TCHAR*);
	int GetIconTypeByViewElementType(int);
	int GetViewElementBasicInfoFromProperty(int[100], int[100], TCHAR[100][256]);
	int GetAllLinkInfos(int[500], int[500], int[500], int[500]);
	int GetViewElementMenus(int[100], TCHAR[100][256], TCHAR[100][256]);

	// ViewElementテーブル
	int GetViewElementIdsFromType(int*, int, int);
	int GetViewElementIds(int[256], int);
	int GetViewElementNamesAndIdsFromUdpType(TCHAR[256][32], int[256], int);
	int GetViewElementNamesAndIdsFromType(TCHAR[256][32], int[256], int);
	int GetViewElementTypeFromId(int);
	void GetViewElementNameFromId(int, TCHAR[32]);
	void UpdateViewElementName(int, TCHAR[32]);
	int GetViewElementLinkInfo(int, int*, int[10], int[10]);
	int GetViewElementLinkOriginInfo(int, int*, int*);
	int UpdateViewElementLinkType(int, int, int, int);
	int GetTargetTcpUdpNameAndId(TCHAR[256][32], int[256], int);
	int GetTcpSenderReceiver(TCHAR[256][32], int[256], BOOL, BOOL, int);
	int GetIconId(int);
	void SetIconId(int, int);
	void InsertViewElement(int, TCHAR[32], int, int, int, int, int[20]);
	int GetAllViewElementRecords(int[1000], TCHAR[1000][32], int[1000], int[1000], int[1000], int[1000], int[1000][10], int[1000][10]);
	void GetMaxLinkInfo(int[100], int[100]);

	// ElementInfoテーブル
	int GetElementInfoParamInt(int, int);
	void SetElementInfoParamInt(int, int, int);
	void GetElementInfoParamStr(int, TCHAR[256], int);
	void SetElementInfoParamStr(int, TCHAR[256], int);
	void GetElementInfoBin(int, BYTE[4096]);
	void SetElementInfoBin(int, BYTE[4096]);
	int GetElementInfoParamStrAsInt(int, int);
	void SetElementInfoParamStrAsInt(int, int, int);
	int GetHostIpAddrPort(int, TCHAR[256], int*);
	int GetTcpRecvOperationTypeInElementInfo(int);
	void SetTcpRecvOperationTypeInElementInfo(int, int);
	int GetTcpRecvCorrespodingIdInElementInfo(int);
	void SetTcpRecvCorrespodingIdInElementInfo(int, int);
	void ModifyElementInfoScheme();
	void UpdateHttpHeaderInfo(int, int, wchar_t[1024]);
	void GetHttpHeaderInfo(int, int*, wchar_t[1024]);

	// Does corresponding element exist?
	bool DoesCorrespondingElementExist(int);
		
	// Delete all records of specified table
	int DeleteAllRecords(TCHAR[TABLE_NAME_SIZE]);

	// テーブルが更新されている場合TRUEを返す
	BOOL IsUpdated(int);

	// ワークスペースサイズおよびグリッド状態を返却・設定する
	BOOL GetWorkspaceInfo(int*, int*, int*);
	BOOL ChangeWorkspace(int, int, int);
	void SetWorkspaceGridType(int);

	// Initialize & Create StkFw Repository
	int StkFwRepositoryCreateTable();
	int StkFwRepositoryInitialize(int);

	// Sync ElementInfo with ViewElement
	void UpdateElementInfoFromViewElement();

	// Std file access
	int LoadStdFile(TCHAR*);
	int SaveStdFile(TCHAR*);
};
