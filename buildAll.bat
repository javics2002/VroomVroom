@echo off

title VroomVroomBuilder

rem Variables de batch
set GAME_ROOT_DIR=%cd%
set ENGINE_DIR=.\MotorEngine\
set VROOM_VROOM_SOL=.\VroomVroom.sln

set VROOM_VROOM_DLL_DIR=.\Bin\x64\
set ENGINE_EXE_DIR=.\MotorEngine\Exe\Main\x64\

set VROOM_VROOM_ASSETS_DIR=.\Assets\

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
msbuild %VROOM_VROOM_SOL% /p:configuration=Release /p:Platform=x64 /p:PlatformToolset=v143

rem COPY DLL
robocopy /NJH %VROOM_VROOM_DLL_DIR%\Release\ %ENGINE_EXE_DIR%\Release\ "VroomVroom.dll"

rem CREAR BUILD DE RELEASE
set "source=.\MotorEngine\Exe\Main\x64\Release\
%zip% a -t7z -m0=lzma -mx=9 -mfb=64 -md=32m -ms=on Vroom_Vroom_x64_Release.zip %source%/ %VROOM_VROOM_ASSETS_DIR%

exit