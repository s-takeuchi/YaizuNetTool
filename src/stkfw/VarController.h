#pragma once
#include "..\..\..\YaizuComLib\src\\stkdata\stkdata.h"

RecordData* VarCon_GetVariableRecord(int);
RecordData* VarCon_GetVariableRecords();
int VarCon_ChangeNameAndDescription(int, TCHAR[32], TCHAR[64]);
int VarCon_AddVariableRecord(TCHAR[32], TCHAR[64], int);
void VarCon_DeleteVariableRecord(int);
void VarCon_ChangeFlagVariable(int, BOOL);
void VarCon_UpdateCommunicationVariable(int, BYTE*, int);
int VarCon_GetCommunicationVariable(int, BYTE*, int);
int VarCon_GetCommunicationVariableSize(int);
BOOL VarCon_CheckCommunicationVariableSize(int);
BOOL VarCon_CheckVariableCount();
BOOL VarCon_CheckVariableExistence(int);
int VarCon_GetCommunicationVariableId(TCHAR[32]);
int VarCon_GetFlagVariable(int);
int VarCon_GetVariableNameAndDesc(int, TCHAR[32], TCHAR[64]);
int VarCon_GetAllCommVariableNames(int[1000], TCHAR[1000][32]);

