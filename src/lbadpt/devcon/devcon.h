/*++

Copyright (c) Microsoft Corporation.  All rights reserved.

Module Name:

    devcon.h

Abstract:

    Device Console header

--*/

#include <windows.h>
#include <tchar.h>
#include <stdlib.h>
#include <stdio.h>
#include <setupapi.h>
#include <regstr.h>
#include <cfgmgr32.h>
#include <string.h>
#include <malloc.h>
#include <newdev.h>

#include "rc_ids.h"

#ifndef ARRAYSIZE
#define ARRAYSIZE(a)                (sizeof(a)/sizeof(a[0]))
#endif

typedef int (*DispatchFunc)(LPCTSTR BaseName,LPCTSTR Machine,int argc,LPTSTR argv[]);
typedef int (*CallbackFunc)(HDEVINFO Devs,PSP_DEVINFO_DATA DevInfo,DWORD Index,LPVOID Context);

typedef struct {
    LPCTSTR         cmd;
    DispatchFunc    func;
    DWORD           shortHelp;
    DWORD           longHelp;
} DispatchEntry;

extern DispatchEntry DispatchTable[];


#define INSTANCEID_PREFIX_CHAR TEXT('@') // character used to prefix instance ID's
#define CLASS_PREFIX_CHAR      TEXT('=') // character used to prefix class name
#define WILD_CHAR              TEXT('*') // wild character
#define QUOTE_PREFIX_CHAR      TEXT('\'') // prefix character to ignore wild characters
#define SPLIT_COMMAND_SEP      TEXT(":=") // whole word, indicates end of id's

int EnumerateDevices(LPCTSTR BaseName,LPCTSTR Machine,DWORD Flags,int argc,LPTSTR argv[],CallbackFunc Callback,LPVOID Context);
LPTSTR GetDeviceStringProperty(HDEVINFO Devs,PSP_DEVINFO_DATA DevInfo,DWORD Prop);
LPTSTR GetDeviceDescription(HDEVINFO Devs,PSP_DEVINFO_DATA DevInfo);
LPTSTR * GetDevMultiSz(HDEVINFO Devs,PSP_DEVINFO_DATA DevInfo,DWORD Prop);
LPTSTR * GetRegMultiSz(HKEY hKey,LPCTSTR Val);
LPTSTR * GetMultiSzIndexArray(LPTSTR MultiSz);
void DelMultiSz(LPTSTR * Array);
LPTSTR * CopyMultiSz(LPTSTR * Array);

BOOL DumpDeviceHwIds(HDEVINFO Devs,PSP_DEVINFO_DATA DevInfo);
BOOL Reboot();


//
// UpdateDriverForPlugAndPlayDevices
//
typedef BOOL (WINAPI *UpdateDriverForPlugAndPlayDevicesProto)(HWND hwndParent,
                                                         LPCTSTR HardwareId,
                                                         LPCTSTR FullInfPath,
                                                         DWORD InstallFlags,
                                                         PBOOL bRebootRequired OPTIONAL
                                                         );
typedef BOOL (WINAPI *SetupSetNonInteractiveModeProto)(IN BOOL NonInteractiveFlag
                                                      );


#ifdef _UNICODE
#define UPDATEDRIVERFORPLUGANDPLAYDEVICES "UpdateDriverForPlugAndPlayDevicesW"
#else
#define UPDATEDRIVERFORPLUGANDPLAYDEVICES "UpdateDriverForPlugAndPlayDevicesA"
#endif
#define SETUPSETNONINTERACTIVEMODE "SetupSetNonInteractiveMode"


//
// exit codes
//
#define EXIT_OK       (0)
#define EXIT_REBOOT   (1)
#define EXIT_FAIL     (2)
#define EXIT_USAGE    (3)
#define EXIT_FOUND    (10)
