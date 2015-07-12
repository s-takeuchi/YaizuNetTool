/*++

Copyright (c) Microsoft Corporation.  All rights reserved.

Module Name:

    devcon.cpp

Abstract:

    Device Console
    command-line interface for managing devices

--*/

#include "devcon.h"

struct GenericContext {
    DWORD count;
    DWORD control;
    BOOL  reboot;
    LPCTSTR strSuccess;
    LPCTSTR strReboot;
    LPCTSTR strFail;
};

#define FIND_DEVICE         0x00000001 // display device
#define FIND_STATUS         0x00000002 // display status of device
#define FIND_RESOURCES      0x00000004 // display resources of device
#define FIND_DRIVERFILES    0x00000008 // display drivers used by device
#define FIND_HWIDS          0x00000010 // display hw/compat id's used by device
#define FIND_DRIVERNODES    0x00000020 // display driver nodes for a device.
#define FIND_CLASS          0x00000040 // display device's setup class
#define FIND_STACK          0x00000080 // display device's driver-stack

struct SetHwidContext {
    int argc_right;
    LPTSTR * argv_right;
    DWORD prop;
    int skipped;
    int modified;
};


int FindCallback(HDEVINFO Devs,PSP_DEVINFO_DATA DevInfo,DWORD Index,LPVOID Context)
{
    GenericContext *pFindContext = (GenericContext*)Context;
	static BOOL Fnd = FALSE;
	int Loop;

    if(pFindContext->control&FIND_HWIDS) {
	    LPTSTR * hwIdArray = GetDevMultiSz(Devs,DevInfo,SPDRP_HARDWAREID);
	    LPTSTR * compatIdArray = GetDevMultiSz(Devs,DevInfo,SPDRP_COMPATIBLEIDS);

		Loop = 0;
		while (hwIdArray && hwIdArray[Loop]) {
			if (lstrcmp(hwIdArray[Loop], _T("*MSLOOP")) == 0) {
				Fnd = TRUE;
			}
			Loop++;
		}
		Loop = 0;
		while (compatIdArray && compatIdArray[Loop]) {
			if (lstrcmp(compatIdArray[Loop], _T("*MSLOOP")) == 0) {
				Fnd = TRUE;
			}
			Loop++;
		}

	    DelMultiSz(hwIdArray);
	    DelMultiSz(compatIdArray);
    }
    pFindContext->count++;
	if (Fnd) {
		return EXIT_FOUND;
	} else {
		return EXIT_OK;
	}
}

int cmdHwIds(LPCTSTR BaseName,LPCTSTR Machine,int argc,TCHAR* argv[])
{
    GenericContext context;
    int failcode;

	TCHAR* NewArgv[1];
	TCHAR TmpNewArgv[10];
	lstrcpy(TmpNewArgv, _T("=net"));
	NewArgv[0] = TmpNewArgv;

    context.count = 0;
    context.control = FIND_DEVICE | FIND_HWIDS;
    return EnumerateDevices(BaseName,Machine,DIGCF_PRESENT,1,NewArgv,FindCallback,&context);
}

int cmdUpdate(LPCTSTR BaseName,LPCTSTR Machine,int argc,TCHAR* argv[])
{
    HMODULE newdevMod = NULL;
    int failcode = EXIT_FAIL;
    UpdateDriverForPlugAndPlayDevicesProto UpdateFn;
    BOOL reboot = FALSE;
    LPCTSTR hwid = NULL;
    LPCTSTR inf = NULL;
    DWORD flags = 0;
    DWORD res;
    TCHAR InfPath[MAX_PATH];
	TCHAR newArgv[2][255];

	GetWindowsDirectory(newArgv[0], 255);
	lstrcat(newArgv[0], _T("\\Inf\\Netloop.inf"));
	lstrcpy(newArgv[1], _T("*MSLOOP"));
    inf = newArgv[0];
    hwid = newArgv[1];

	//
    // Inf must be a full pathname
    //
    res = GetFullPathName(inf,MAX_PATH,InfPath,NULL);
    if((res >= MAX_PATH) || (res == 0)) {
        //
        // inf pathname too long
        //
        return EXIT_FAIL;
    }
    if(GetFileAttributes(InfPath)==(DWORD)(-1)) {
        //
        // inf doesn't exist
        //
        return EXIT_FAIL;
    }
    inf = InfPath;
    flags |= INSTALLFLAG_FORCE;

    //
    // make use of UpdateDriverForPlugAndPlayDevices
    //
    newdevMod = LoadLibrary(TEXT("newdev.dll"));
    if(!newdevMod) {
        goto final;
    }
    UpdateFn = (UpdateDriverForPlugAndPlayDevicesProto)GetProcAddress(newdevMod,UPDATEDRIVERFORPLUGANDPLAYDEVICES);
    if(!UpdateFn)
    {
        goto final;
    }

    if(!UpdateFn(NULL,hwid,inf,flags,&reboot)) {
        goto final;
    }

    failcode = reboot ? EXIT_REBOOT : EXIT_OK;

final:

    if(newdevMod) {
        FreeLibrary(newdevMod);
    }

    return failcode;
}

int cmdInstall(LPCTSTR BaseName,LPCTSTR Machine,int argc,TCHAR* argv[])
{
    HDEVINFO DeviceInfoSet = INVALID_HANDLE_VALUE;
    SP_DEVINFO_DATA DeviceInfoData;
    GUID ClassGUID;
    TCHAR ClassName[MAX_CLASS_NAME_LEN];
    TCHAR hwIdList[LINE_LEN+4];
    TCHAR InfPath[MAX_PATH];
    DWORD err;
    int failcode = EXIT_FAIL;
    BOOL reboot = FALSE;
    LPCTSTR hwid = NULL;
    LPCTSTR inf = NULL;
    DWORD flags = 0;
    DWORD len;
	TCHAR newArgv[2][255];

	GetWindowsDirectory(newArgv[0], 255);
	lstrcat(newArgv[0], _T("\\Inf\\Netloop.inf"));
	lstrcpy(newArgv[1], _T("*MSLOOP"));
    inf = newArgv[0];
    hwid = newArgv[1];

	//
    // Inf must be a full pathname
    //
    if(GetFullPathName(inf,MAX_PATH,InfPath,NULL) >= MAX_PATH) {
        //
        // inf pathname too long
        //
        return EXIT_FAIL;
    }

    //
    // List of hardware ID's must be double zero-terminated
    //
    ZeroMemory(hwIdList,sizeof(hwIdList));
    lstrcpyn(hwIdList,hwid,LINE_LEN);

    //
    // Use the INF File to extract the Class GUID.
    //
    if (!SetupDiGetINFClass(InfPath,&ClassGUID,ClassName,sizeof(ClassName)/sizeof(ClassName[0]),0))
    {
        goto final;
    }

    //
    // Create the container for the to-be-created Device Information Element.
    //
    DeviceInfoSet = SetupDiCreateDeviceInfoList(&ClassGUID,0);
    if(DeviceInfoSet == INVALID_HANDLE_VALUE)
    {
        goto final;
    }

    //
    // Now create the element.
    // Use the Class GUID and Name from the INF file.
    //
    DeviceInfoData.cbSize = sizeof(SP_DEVINFO_DATA);
    if (!SetupDiCreateDeviceInfo(DeviceInfoSet,
        ClassName,
        &ClassGUID,
        NULL,
        0,
        DICD_GENERATE_ID,
        &DeviceInfoData))
    {
        goto final;
    }

    //
    // Add the HardwareID to the Device's HardwareID property.
    //
    if(!SetupDiSetDeviceRegistryProperty(DeviceInfoSet,
        &DeviceInfoData,
        SPDRP_HARDWAREID,
        (LPBYTE)hwIdList,
        (lstrlen(hwIdList)+1+1)*sizeof(TCHAR)))
    {
        goto final;
    }

    //
    // Transform the registry element into an actual devnode
    // in the PnP HW tree.
    //
    if (!SetupDiCallClassInstaller(DIF_REGISTERDEVICE,
        DeviceInfoSet,
        &DeviceInfoData))
    {
        goto final;
    }

    //
    // update the driver for the device we just created
    //
    failcode = cmdUpdate(BaseName,Machine,argc,argv);

final:

    if (DeviceInfoSet != INVALID_HANDLE_VALUE) {
        SetupDiDestroyDeviceInfoList(DeviceInfoSet);
    }

    return failcode;
}

int RemoveCallback(HDEVINFO Devs,PSP_DEVINFO_DATA DevInfo,DWORD Index,LPVOID Context)
{
    SP_REMOVEDEVICE_PARAMS rmdParams;
    GenericContext *pControlContext = (GenericContext*)Context;
    SP_DEVINSTALL_PARAMS devParams;
    LPCTSTR action = NULL;

    //
    // need hardware ID before trying to remove, as we wont have it after
    //
    TCHAR devID[MAX_DEVICE_ID_LEN];
    LPTSTR desc;
    BOOL b = TRUE;
    SP_DEVINFO_LIST_DETAIL_DATA devInfoListDetail;

    devInfoListDetail.cbSize = sizeof(devInfoListDetail);
    if((!SetupDiGetDeviceInfoListDetail(Devs,&devInfoListDetail)) ||
            (CM_Get_Device_ID_Ex(DevInfo->DevInst,devID,MAX_DEVICE_ID_LEN,0,devInfoListDetail.RemoteMachineHandle)!=CR_SUCCESS)) {
        //
        // skip this
        //
        return EXIT_OK;
    }

    rmdParams.ClassInstallHeader.cbSize = sizeof(SP_CLASSINSTALL_HEADER);
    rmdParams.ClassInstallHeader.InstallFunction = DIF_REMOVE;
    rmdParams.Scope = DI_REMOVEDEVICE_GLOBAL;
    rmdParams.HwProfile = 0;
    if(!SetupDiSetClassInstallParams(Devs,DevInfo,&rmdParams.ClassInstallHeader,sizeof(rmdParams)) ||
       !SetupDiCallClassInstaller(DIF_REMOVE,Devs,DevInfo)) {
        //
        // failed to invoke DIF_REMOVE
        //
        action = pControlContext->strFail;
    } else {
        //
        // see if device needs reboot
        //
        devParams.cbSize = sizeof(devParams);
        if(SetupDiGetDeviceInstallParams(Devs,DevInfo,&devParams) && (devParams.Flags & (DI_NEEDRESTART|DI_NEEDREBOOT))) {
            //
            // reboot required
            //
            action = pControlContext->strReboot;
            pControlContext->reboot = TRUE;
        } else {
            //
            // appears to have succeeded
            //
            action = pControlContext->strSuccess;
        }
        pControlContext->count++;
    }

    return EXIT_OK;
}

int cmdRemove(LPCTSTR BaseName,LPCTSTR Machine,int argc,TCHAR* argv[])
{
    GenericContext context;
    TCHAR strRemove[80];
    TCHAR strReboot[80];
    TCHAR strFail[80];
    int failcode = EXIT_FAIL;

	TCHAR* NewArgv[1];
	TCHAR TmpNewArgv[10];
	lstrcpy(TmpNewArgv, _T("*MSLOOP"));
	NewArgv[0] = TmpNewArgv;

	if(!LoadString(NULL,IDS_REMOVED,strRemove,ARRAYSIZE(strRemove))) {
        return EXIT_FAIL;
    }
    if(!LoadString(NULL,IDS_REMOVED_REBOOT,strReboot,ARRAYSIZE(strReboot))) {
        return EXIT_FAIL;
    }
    if(!LoadString(NULL,IDS_REMOVE_FAILED,strFail,ARRAYSIZE(strFail))) {
        return EXIT_FAIL;
    }

    context.reboot = FALSE;
    context.count = 0;
    context.strReboot = strReboot;
    context.strSuccess = strRemove;
    context.strFail = strFail;
    failcode = EnumerateDevices(BaseName,Machine,DIGCF_PRESENT,1,NewArgv,RemoveCallback,&context);

    if(failcode == EXIT_OK) {
        if(!context.count) {
        } else if(!context.reboot) {
        } else {
            failcode = EXIT_REBOOT;
        }
    }
    return failcode;
}

DispatchEntry DispatchTable[] = {
    { TEXT("get"),        cmdHwIds,       0,      0 },
    { TEXT("add"),      cmdInstall,     0,      0 },
    { TEXT("remove"),       cmdRemove,      0,      0 },
    { NULL,NULL }
};
