@echo off
setlocal


rem Pregunta si generar paradas de comprobación entre cada paso
set /p pause_option="> Quieres que se generen pausas? [S/N]: "


rem Fecha inicio: 
set start_time=%time%


rem Elimina si existe el anterior registro
if exist "./build_Output.txt" (

    del "./build_Output.txt"

)



rem -----------------------------------
rem TODO EL PROCESO AQUI: CONFIGURACIÓN
rem -----------------------------------


rem Configuración de paradas
set /p pause_option="> Quieres que se generen pausas? [S/N]: " 



rem Configuración inicial del proyecto, realiza una búsqueda de tipo clave/valor (config.txt)
rem Se crean las variables: %Game% , %Platform% , %Configuration% y %GameMachine%
for /f "tokens=1,* delims=: " %%a in ('type datos.txt ^| findstr /i "Game: Platform: Configuration: GameMachine:"') do (
    set "key=%%a"
    set "value=%%b"
    set "%key%=%value%"
) 



rem Configuración para la ejecución global 
:loop
set /p exec_option="> Quieres que se ejecute en serie o en paralelo? [S/P]: " 

rem Comprueba la opción escogida: 
if /i "%exec_option%"=="S" ( 

    echo: && echo "> COMENZANDO EN SERIE!!" && echo:

) else if /i "%exec_option%"=="P" (

    echo: && echo "> COMENZANDO EN PARALELO!!" && echo:

) else ( 

    echo: && echo "La opcion %exec_option% no es valida. Prueba otra vez." && echo:
    goto loop

)
if /i "%pause_option%"=="S" ( pause ) 



rem Configuración del shell de Visual Studio 
echo: && echo "> Buscando la version mas actualizada de Visual Studio DCP..." && echo:

rem Búsqueda y guardado de la ruta al shell Developer command prompt for Visual Studio 2022 más actualizado
call "%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe" -latest -property installationPath > "%temp%\VSWhereOutput.txt"
set /p VS_PATH=<"%temp%\VSWhereOutput.txt"

if /i "%pause_option%"=="S" ( pause )



rem -------------------------------
rem TODO EL PROCESO AQUI: EJECUCIÓN
rem -------------------------------


rem Ejecuta la instalación del motor: MotorEngine

cd .\%GameMachine% 
echo: && echo "> Instalando _%GameMachine%_" && echo: 
if /i "%exec_option%"=="S" ( call .\build_MOTOR.bat %pause_option% %exec_option% ) else if /i "%exec_option%"=="P" ( start .\build_MOTOR.bat %pause_option% %exec_option% ) 
cd .. 


rem Control de espera para asegurar que el anterior proceso que instala el motor haya terminado
:check
if not exist ".\build_Output.txt" ( 
        
    rem Esperar 1 segundo antes de volver a comprobar
    timeout /t 1 /nobreak > nul
    goto check 
        
) 


rem Copia de archivos de configuración de Ogre
set "origen=.\Dependencies\Ogre\" 

rem Copia para ejecutar desde Visual Studio: (se podría quitar)
set "destino=.\Projects\Main\" 
robocopy %origen% %destino% *.cfg 

rem Copia para ejecutar directamente:
set "destino=.\Exe\Main\%Platform%\%Configuration%\" 
robocopy %origen% %destino% *.cfg 


if /i "%pause_option%"=="S" ( pause ) 



rem Ejecuta la instalación del juego: VroomVroom

rem Copia los binarios del motor al juego
set "origen=.\%GameMachine%\Exe\Main\%Platform%\%Configuration%\" 
set "destinoMotor=.\%GameMachine%\Lib\%Platform%\%Configuration%\" 
set "destinoJuego=.\Bin\%Platform%\%Configuration%\"

if /I "%Configuration%==Debug" ( 

    robocopy %origen% %destinoMotor% %GameMachine%_d.lib 
    robocopy %origen% %destinoJuego% %GameMachine%_d.dll 
    set "targetGame=%Game%_d" 
    set "targetMain=Main_d" 

) else if /I "%Configuration%==Release" (

    robocopy %origen% %destinoMotor% %GameMachine%.lib 
    robocopy %origen% %destinoJuego% %GameMachine%.dll 
    set "targetGame=%Game%" 
    set "targetMain=Main" 

) else (
    echo ¡Algo falla en config.txt respecto a la opcion de configuracion!
)
if /i "%pause_option%"=="S" ( pause ) 


rem Llamada al DCP: Developer Command Prompt
call "%VS_PATH%\Common7\Tools\VsDevCmd.bat" 


rem Configuración preestablecida
if not exist "Bin\%Platform%\%Configuration%\%targetGame%.dll" ( 

    rem Compilación 
    msbuild %Game%.sln /t:Rebuild /p:Configuration=%Configuration% /p:Platform=%Platform% /p:PlatformToolset=v143 

    echo: && echo "> Build %Game% solucion en modo debug compilada." && echo: 
) else (
    echo: && echo "> Build %Game% solucion en modo debug ya existe." && echo: 
)
if /i "%pause_option%"=="S" ( pause ) 



rem Prepara los recursos del juego en el motor 

rem Dirección de recursos utilizados en el juego
set "origen=.\%GameMachine%\Assets\" 

rem Copia para ejecutar desde Visual Studio: (se podría quitar)
set "destino=.\%GameMachine%\Projects\Main\Assets\" 
robocopy %origen% %destino% /E 

rem Copia para ejecutar directamente:
set "destino=.\%GameMachine%\Exe\Main\%Platform%\%Configuration%\Assets\" 
robocopy %origen% %destino% /E 

if /i "%pause_option%"=="S" ( pause ) 


rem Copia el binario generado por el juego
set "origen=.\Bin\%Platform%\%Configuration%\" 
set "destino=.\%GameMachine%\Exe\Main\%Platform%\%Configuration%\" 
robocopy %origen% %destino% %targetGame%.dll 

if /i "%pause_option%"=="S" ( pause ) 



rem Ejecuta el juego desde el motor:
call .\%GameMachine%\Exe\Main\%Platform%\%Configuration%\%targetMain%.exe



rem ---------------------------
rem TODO EL PROCESO AQUI ARRIBA
rem ---------------------------


rem Fecha final: 
set end_time=%time%


echo:
echo ----------------------------
echo Fecha inicio: %start_time% 
echo Fecha final: %end_time% 
echo:


rem Check final
echo "> Build %Game% finalizada [ inicio: %start_time% // finalizado: %end_time% ]" > "./build_Output.txt"

pause
endlocal