@echo off

echo;
echo =========================================
echo Build YaizuNetTool
echo =========================================

set CURRENTPATH=%cd%
set MSBUILD="C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\MSBuild\15.0\Bin\msbuild.exe"
set DEVENV="C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\Common7\IDE\devenv.exe"
set SEVENZIP="C:\Program Files\7-Zip\7z.exe"
set LCOUNTER="C:\Program Files (x86)\lcounter\lcounter.exe"

echo;
echo This batch file requires softwares shown below.
echo (1) Microsoft Visual Studio 2017
echo (2) 7-Zip 9.20
echo (3) Line Counter

if not exist %MSBUILD% exit
if not exist %DEVENV% exit
if not exist %SEVENZIP% exit
if not exist %LCOUNTER% exit


rem ########## Initializing ##########
echo;
echo Initializing ...
if exist stkfw rmdir /S /Q stkfw
if exist deployment rmdir /S /Q deployment


rem ########## Building ##########
echo;
echo Building stkdatagui.sln...
%MSBUILD% "..\..\YaizuComLib\src\stkdatagui\stkdatagui.sln" /t:clean;build /p:Configuration=Release
echo Building fwadd.sln...
%MSBUILD% "..\src\fwadd\fwadd.sln" /t:clean;build /p:Configuration=Release
echo Building fwdel.sln...
%MSBUILD% "..\src\fwdel\fwdel.sln" /t:clean;build /p:Configuration=Release
echo Building lbadpt.sln...
%MSBUILD% "..\src\lbadpt\lbadpt.sln" /t:clean;build /p:Configuration=Release
echo Building stk_ip_dlg.sln...
%MSBUILD% "..\src\stk_ip_dlg\stk_ip_dlg.sln" /t:clean;build /p:Configuration=Release
%MSBUILD% "..\src\stk_ip_dlg\stk_ip_dlg.sln" /t:clean;build /p:Configuration=Release_win2k
echo Building stklibtest.sln...
%MSBUILD% "..\src\stkfw\stklibtest.sln" /t:clean;build /p:Configuration=Release


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


rem ########## Making installer ##########
echo;
echo Making installer...
%DEVENV% "setup\setup1.sln" /rebuild Release
mkdir deployment
copy ..\doc\readme\ReadmeJPN.txt deployment
copy ..\doc\readme\ReadmeENG.txt deployment
copy setup\Release\stkfw.msi deployment


rem ########## ZIP packing ##########
echo;
echo ZIP packing stage...
cd deployment
%SEVENZIP% a sfw170.zip stkfw.msi
%SEVENZIP% a sfw170.zip ReadmeJPN.txt
%SEVENZIP% a sfw170.zip ReadmeENG.txt
del ReadmeJPN.txt
del ReadmeENG.txt
del stkfw.msi
cd..


rem ########## build complete ##########
echo;
%LCOUNTER% ..\src /subdir
echo;
echo All building processes of StkFw have been successfully finished.
pause
exit /B


rem ########## Error ##########
:FILENOTEXIST
echo;
echo Build error occurred because some build target files do not exist.
pause
exit /B

