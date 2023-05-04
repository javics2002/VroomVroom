@echo off

title VroomVroomBuilder

rem Variables de batch
set GAME_ROOT_DIR=%cd%
set ENGINE_DIR=.\MotorEngine\
set VROOM_VROOM_SOL=.\VroomVroom.sln

set VROOM_VROOM_DLL_DIR=.\Bin\x64\
set ENGINE_EXE_DIR=.\MotorEngine\Exe\Main\x64\

rem Referencia a la herramienta de compresión: 
set "zip=.\MotorEngine\Dependencies\7zip\7za.exe" 

rem Inicializamos el submódulo
git submodule init

git submodule update

cd %ENGINE_DIR%

call deleteDependencies.bat

call compile-all.bat

cd %GAME_ROOT_DIR%

rem Compilacion de la solucion del juego
msbuild %VROOM_VROOM_SOL% /p:configuration=Debug /p:Platform=x64 /p:PlatformToolset=v143
msbuild %VROOM_VROOM_SOL% /p:configuration=Release /p:Platform=x64 /p:PlatformToolset=v143

rem COPY DLL
robocopy /NJH %VROOM_VROOM_DLL_DIR%\Debug\ %ENGINE_EXE_DIR%\Debug\ "VroomVroom_d.dll"
robocopy /NJH %VROOM_VROOM_DLL_DIR%\Release\ %ENGINE_EXE_DIR%\Release\ "VroomVroom.dll"

rem CREAR BUILD DE RELEASE Y DEBUG EN 7ZIP
set "source=.\MotorEngine\Exe\Main\x64\Debug\
%zip% a -t7z -m0=lzma -mx=9 -mfb=64 -md=32m -ms=on build_final_x64_Debug.7z %source%/

set "source=.\MotorEngine\Exe\Main\x64\Release\
%zip% a -t7z -m0=lzma -mx=9 -mfb=64 -md=32m -ms=on build_final_x64_Release.7z %source%/

pause
exit