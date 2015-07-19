@echo off

echo;
echo =========================================
echo Build YaizuNetTool
echo =========================================

set CURRENTPATH=%cd%
set DEVENV="C:\Program Files (x86)\Microsoft Visual Studio 9.0\Common7\IDE\devenv.exe"


rem ########## Initializing ##########
echo;
echo Initializing ...
if exist stkfw rmdir /S /Q stkfw
if exist deployment rmdir /S /Q deployment


rem ########## Building ##########
echo;
echo Building stkdatagui.sln...
%DEVENV% "..\..\YaizuComLib\src\stkdatagui\stkdatagui.sln" /rebuild Release 
echo Building fwadd.sln...
%DEVENV% "..\src\fwadd\fwadd.sln" /rebuild Release
echo Building fwdel.sln...
%DEVENV% "..\src\fwdel\fwdel.sln" /rebuild Release
echo Building lbadpt.sln...
%DEVENV% "..\src\lbadpt\lbadpt.sln" /rebuild Release
echo Building stk_ip_dlg.sln...
%DEVENV% "..\src\stk_ip_dlg\stk_ip_dlg.sln" /rebuild Release
%DEVENV% "..\src\stk_ip_dlg\stk_ip_dlg.sln" /rebuild Release_win2k
echo Building stklibtest.sln...
%DEVENV% "..\src\stkfw\stklibtest.sln" /rebuild Release


rem ########## Checking file existence ##########
echo;
echo Checking "stkdatagui.exe" existence...
if not exist "..\..\YaizuComLib\src\stkdatagui\Release\stkdatagui.exe" goto FILENOTEXIST
echo Checking "fwadd.exe" existence...
if not exist "..\src\fwadd\Release\fwadd.exe" goto FILENOTEXIST
echo Checking "fwdel.exe" existence...
if not exist "..\src\fwdel\Release\fwdel.exe" goto FILENOTEXIST
echo Checking "lbadpt.exe, lbadpt32.exe, lbadpt64.exe" existence...
if not exist "..\src\lbadpt\Release\lbadpt.exe" goto FILENOTEXIST
if not exist "..\src\lbadpt\devcon\lbadpt32.exe" goto FILENOTEXIST
if not exist "..\src\lbadpt\devcon\lbadpt64.exe" goto FILENOTEXIST
echo Checking "stk_ip_dlg.exe, stk_ip_dlg_win2k.exe" existence...
if not exist "..\src\stk_ip_dlg\Release_win2k\stk_ip_dlg_win2k.exe" goto FILENOTEXIST
if not exist "..\src\stk_ip_dlg\Release\stk_ip_dlg.exe" goto FILENOTEXIST
echo Checking "stkfw.exe" existence...
if not exist "..\src\stkfw\Release\stkfw.exe" goto FILENOTEXIST
echo Checking sample data folder existence...
if not exist "..\src\sample\." goto FILENOTEXIST
echo Checking manual folder existence...
if not exist "..\doc\man\eng\." goto FILENOTEXIST
if not exist "..\doc\man\jpn\." goto FILENOTEXIST


rem ########## Deployment of files and folders ##########
echo;
echo Deployment of files and folders...
mkdir stkfw
mkdir stkfw\sample
mkdir stkfw\manual
mkdir stkfw\manual\eng
mkdir stkfw\manual\jpn
mkdir stkfw\stk_ip_dlg
mkdir stkfw\stk_ip_dlg_win2k
copy "..\..\YaizuComLib\src\stkdatagui\Release\stkdatagui.exe" stkfw
copy "..\src\fwadd\Release\fwadd.exe" setup
copy "..\src\fwdel\Release\fwdel.exe" setup
copy "..\src\lbadpt\Release\lbadpt.exe" stkfw
copy "..\src\lbadpt\devcon\lbadpt32.exe" stkfw
copy "..\src\lbadpt\devcon\lbadpt64.exe" stkfw
copy "..\src\stk_ip_dlg\Release_win2k\stk_ip_dlg_win2k.exe" stkfw\stk_ip_dlg_win2k
copy "..\src\stk_ip_dlg\Release\stk_ip_dlg.exe" stkfw\stk_ip_dlg
copy "..\src\stkfw\Release\stkfw.exe" stkfw
copy "..\src\sample\*.*" stkfw\sample
copy "..\doc\man\eng\*.*" stkfw\manual\eng
copy "..\doc\man\jpn\*.*" stkfw\manual\jpn
exit /B


rem ########## Making installer ##########
echo;
echo Digital signing (1st)...
if exist ..\stkcodesign.pfx "C:\Program Files\Microsoft Platform SDK\Bin\signtool" sign /f ..\stkcodesign.pfx /a /t "http://timestamp.globalsign.com/scripts/timstamp.dll" /p happ1975 stkfw\stkfw.exe
if exist ..\stkcodesign.pfx "C:\Program Files\Microsoft Platform SDK\Bin\signtool" sign /f ..\stkcodesign.pfx /a /t "http://timestamp.globalsign.com/scripts/timstamp.dll" /p happ1975 stkfw\stkdatagui.exe
if exist ..\stkcodesign.pfx "C:\Program Files\Microsoft Platform SDK\Bin\signtool" sign /f ..\stkcodesign.pfx /a /t "http://timestamp.globalsign.com/scripts/timstamp.dll" /p happ1975 stkfw\lbadpt.exe
if exist ..\stkcodesign.pfx "C:\Program Files\Microsoft Platform SDK\Bin\signtool" sign /f ..\stkcodesign.pfx /a /t "http://timestamp.globalsign.com/scripts/timstamp.dll" /p happ1975 stkfw\lbadpt32.exe
if exist ..\stkcodesign.pfx "C:\Program Files\Microsoft Platform SDK\Bin\signtool" sign /f ..\stkcodesign.pfx /a /t "http://timestamp.globalsign.com/scripts/timstamp.dll" /p happ1975 stkfw\lbadpt64.exe
if exist ..\stkcodesign.pfx "C:\Program Files\Microsoft Platform SDK\Bin\signtool" sign /f ..\stkcodesign.pfx /a /t "http://timestamp.globalsign.com/scripts/timstamp.dll" /p happ1975 stkfw\stk_ip_dlg\stk_ip_dlg.exe
if exist ..\stkcodesign.pfx "C:\Program Files\Microsoft Platform SDK\Bin\signtool" sign /f ..\stkcodesign.pfx /a /t "http://timestamp.globalsign.com/scripts/timstamp.dll" /p happ1975 stkfw\stk_ip_dlg_win2k\stk_ip_dlg_win2k.exe

echo;
echo Making installer...
%DEVENV% "setup\setup1.sln" /rebuild Release
mkdir deployment
copy ReadmeJPN.txt deployment
copy ReadmeENG.txt deployment
copy setup\Release\stkfw.msi deployment

echo;
echo Digital signing (2nd)...
if exist ..\stkcodesign.pfx "C:\Program Files\Microsoft Platform SDK\Bin\signtool" sign /f ..\stkcodesign.pfx /a /t "http://timestamp.globalsign.com/scripts/timstamp.dll" /p happ1975 deployment\stkfw.msi


rem ########## ZIP packing ##########
echo;
echo ZIP packing stage...
copy ReadmeJPN.txt deployment
copy ReadmeENG.txt deployment
cd deployment
..\..\7za.exe a sfw150.zip stkfw.msi
..\..\7za.exe a sfw150.zip ReadmeJPN.txt
..\..\7za.exe a sfw150.zip ReadmeENG.txt
del ReadmeJPN.txt
del ReadmeENG.txt
del stkfw.msi
cd..


rem ########## build complete ##########
echo;
echo All building processes of StkFw have been successfully finished.
exit /B


:FILENOTEXIST
echo;
echo Build error occurred because some build target files do not exist.
exit /B

