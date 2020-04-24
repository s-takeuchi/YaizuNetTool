@echo off

echo;
echo =========================================
echo Build YaizuNetTool
echo =========================================

if defined GITHUBACTIONS (
  echo For GitHub Actions
  set MSBUILD="C:\Program Files (x86)\Microsoft Visual Studio\2017\Enterprise\MSBuild\15.0\Bin\msbuild.exe"
  set DEVENV="C:\Program Files (x86)\Microsoft Visual Studio\2017\Enterprise\Common7\IDE\devenv.com"
  set SEVENZIP="7z.exe"
  set LCOUNTER=""
  goto definitionend
)

set LOCALMACHINE="true"

set MSBUILD="C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\MSBuild\15.0\Bin\msbuild.exe"
set DEVENV="C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\Common7\IDE\devenv.com"
set SEVENZIP="C:\Program Files\7-Zip\7z.exe"
set LCOUNTER="C:\Program Files (x86)\lcounter\lcounter.exe"

echo;
echo This batch file requires softwares shown below.
echo 1. Microsoft Visual Studio 2017
echo 2. 7-Zip 9.20
echo 3. Line Counter

if not exist %MSBUILD% (
  exit
) else if not exist %DEVENV% (
  exit
) else if not exist %SEVENZIP% (
  exit
) else if not exist %LCOUNTER% (
  exit
)

:definitionend


rem ########## Initializing ##########
echo;
echo Initializing ...
if exist stkfw rmdir /S /Q stkfw
if exist deployment rmdir /S /Q deployment


rem ########## Building ##########
echo;
echo Building stkdatagui.sln...
%MSBUILD% "..\..\YaizuComLib\src\stkdatagui\stkdatagui.sln" /t:clean;build /p:Configuration=Release
IF %ERRORLEVEL% NEQ 0 goto ERRORRAISED
echo Building fwadd.sln...
%MSBUILD% "..\src\fwadd\fwadd.sln" /t:clean;build /p:Configuration=Release
IF %ERRORLEVEL% NEQ 0 goto ERRORRAISED
echo Building fwdel.sln...
%MSBUILD% "..\src\fwdel\fwdel.sln" /t:clean;build /p:Configuration=Release
IF %ERRORLEVEL% NEQ 0 goto ERRORRAISED
echo Building lbadpt.sln...
%MSBUILD% "..\src\lbadpt\lbadpt.sln" /t:clean;build /p:Configuration=Release
IF %ERRORLEVEL% NEQ 0 goto ERRORRAISED
echo Building stk_ip_dlg.sln...
%MSBUILD% "..\src\stk_ip_dlg\stk_ip_dlg.sln" /t:clean;build /p:Configuration=Release
IF %ERRORLEVEL% NEQ 0 goto ERRORRAISED
%MSBUILD% "..\src\stk_ip_dlg\stk_ip_dlg.sln" /t:clean;build /p:Configuration=Release_win2k
IF %ERRORLEVEL% NEQ 0 goto ERRORRAISED
echo Building stklibtest.sln...
%MSBUILD% "..\src\stkfw\stklibtest.sln" /t:clean;build /p:Configuration=Release
IF %ERRORLEVEL% NEQ 0 goto ERRORRAISED


rem ########## Checking file existence ##########
echo;
echo Checking "stkdatagui.exe" existence...
if not exist "..\..\YaizuComLib\src\stkdatagui\Release\stkdatagui.exe" goto ERRORRAISED
echo Checking "fwadd.exe" existence...
if not exist "..\src\fwadd\Release\fwadd.exe" goto ERRORRAISED
echo Checking "fwdel.exe" existence...
if not exist "..\src\fwdel\Release\fwdel.exe" goto ERRORRAISED
echo Checking "lbadpt.exe, lbadpt32.exe, lbadpt64.exe" existence...
if not exist "..\src\lbadpt\Release\lbadpt.exe" goto ERRORRAISED
if not exist "..\src\lbadpt\devcon\lbadpt32.exe" goto ERRORRAISED
if not exist "..\src\lbadpt\devcon\lbadpt64.exe" goto ERRORRAISED
echo Checking "stk_ip_dlg.exe, stk_ip_dlg_win2k.exe" existence...
if not exist "..\src\stk_ip_dlg\Release_win2k\stk_ip_dlg_win2k.exe" goto ERRORRAISED
if not exist "..\src\stk_ip_dlg\Release\stk_ip_dlg.exe" goto ERRORRAISED
echo Checking "stkfw.exe" existence...
if not exist "..\src\stkfw\Release\stkfw.exe" goto ERRORRAISED
echo Checking sample data folder existence...
if not exist "..\src\sample\." goto ERRORRAISED
echo Checking manual folder existence...
if not exist "..\doc\man\eng\." goto ERRORRAISED
if not exist "..\doc\man\jpn\." goto ERRORRAISED


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
if defined LOCALMACHINE (
  echo;
  echo Making installer...
  %DEVENV% "setup\setup1.sln" /rebuild Release
  mkdir deployment
  copy ..\doc\readme\ReadmeJPN.txt deployment
  copy ..\doc\readme\ReadmeENG.txt deployment
  copy setup\Release\stkfw.msi deployment
)


rem ########## ZIP packing ##########
if defined LOCALMACHINE (
  echo;
  echo ZIP packing stage...
  cd deployment
  %SEVENZIP% a sfw170_beta.zip stkfw.msi
  %SEVENZIP% a sfw170_beta.zip ReadmeJPN.txt
  %SEVENZIP% a sfw170_beta.zip ReadmeENG.txt
  del ReadmeJPN.txt
  del ReadmeENG.txt
  del stkfw.msi
  cd..
)


rem ########## build complete ##########
if defined LOCALMACHINE (
  echo;
  %LCOUNTER% ..\src /subdir
)

echo;
echo All building processes of StkFw have been successfully finished.
if defined LOCALMACHINE (
  pause
)
exit /B %ERRORLEVEL%


rem ########## Error ##########
:ERRORRAISED
echo;
echo Build error occurred.
if defined LOCALMACHINE (
  pause
)
exit /B 1
