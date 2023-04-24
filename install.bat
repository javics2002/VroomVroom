@echo off
setlocal 


rem Fecha inicio: 
set start_time=%time% 

rem Referencia de seguridad al directorio actual: 
set RootDirectory=%CD% 



rem Elimina si existe el anterior registro
if exist "./build_Output.txt" (

    del "./build_Output.txt"

)



rem -----------------------------------
rem TODO EL PROCESO AQUI: CONFIGURACIÓN
rem -----------------------------------



rem Configuración inicial del proyecto, realiza una búsqueda de tipo clave/valor (config.txt)

rem Se crean las variables: %Game% , %GameMachine% , %Platform% , %Configuration% , %make_stops% , %run_type% , %refresh% , %recompile-game% y %recompile-motor%
for /f "tokens=1,* delims=: " %%a in ('type config.txt ^| findstr /i "Game: GameMachine: Platform: Configuration: make_stops: run_type: refresh: recompile-game: recompile-motor: "') do (

    rem Asigna a la variable de nombre 'key' el valor de 'value' 
    set "%%a=%%b" 

) 

rem Referencia a la herramienta de compresión: 
set "zip=.\%GameMachine%\Dependencies\7zip\7za.exe" 

rem Formatea la salida de pause_option 
if /i "%make_stops%"=="true" ( 
    
    set "pause_option=S" 
    
) 

rem Formatea la salida de exec_option 
if /i "%run_type%"=="Paralelo" ( 
    
    set "exec_option=P" 
    
) else if /i "%run_type%"=="Serie" ( 
    
    set "exec_option=S" 
    
) 

rem Formatea la salida de Configuration para el ejecutable final 
if /I "%Configuration%"=="Debug" ( 

    set "targetMain=Main_d" 

) else if /I "%Configuration%"=="Release" ( 

    set "targetMain=Main" 

)



rem Muestra las variables de la configuración del entorno antes de continuar:
set "source=.\%GameMachine%\Exe\Main\%Platform%\%Configuration%\" 
echo:
echo      VARIABLES DE ENTORNO PARA LA INSTALACION
echo  ------------------------------------------------ 
echo   Game: %Game% 
echo   GameMachine: %GameMachine% 
echo  ------------------------------------------------ 
echo   Platform: %Platform% 
echo   Configuration: %Configuration% 
echo  ------------------------------------------------ 
echo   make_stops: %make_stops% 
echo   run_type: %run_type% 
echo   refresh: %refresh% 
echo  ------------------------------------------------ 
echo   recompile-game: %recompile-game% 
echo   recompile-motor: %recompile-motor% 
echo  ------------------------------------------------ 
echo:
echo                    BUILD FINAL
echo  ------------------------------------------------ 
echo   target: %targetMain%.exe 
echo   source: %source% 
echo   build final: build_final_%Platform%_%Configuration%.7z 
echo  ------------------------------------------------ 
echo   7-Zip: %zip% 
echo  ------------------------------------------------ 
echo: && pause 



rem Configuración para la ejecución global de los procesos 
if /i "%exec_option%"=="P" ( 

    echo: && echo "> COMENZANDO EN PARALELO!!" && echo: 

) else if /i "%exec_option%"=="S" ( 
    
    echo: && echo "> COMENZANDO EN SERIE!!" && echo: 

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


rem Ejecuta la instalación del motor (MotorEngine)
echo: && echo "> Instalando: %GameMachine%" && echo: 

set "instalar-motor=false" 
if not exist ".\%GameMachine%\build_Output.txt" ( set "instalar-motor=true" ) 
if /i "%recompile-motor%"=="true" ( set "instalar-motor=true" ) 

if /i "%instalar-motor%"=="true" ( 

    rem Instalación del motor 
    cd .\%GameMachine% 
    del "./build_Output.txt" 
    if /i "%exec_option%"=="S" ( call .\install.bat %pause_option% %exec_option% %Configuration% %recompile-motor% ) else if /i "%exec_option%"=="P" ( start .\install.bat %pause_option% %exec_option% %Configuration% %recompile-motor% ) 
    cd .. 

    echo: && echo "> Instalacion de %GameMachine% en modo %Platform%_%Configuration% completada!" && echo: 
) else (
    echo: && echo "> El motor de videojuegos %GameMachine% en modo %platform%_%Configuration% ya se encontraba instalado." && echo: 
)
if /i "%pause_option%"=="S" ( pause ) 



rem Espera hasta que finalicen los scripts 
echo: && echo "> Espere a que finalicen los scripts..." && echo: 
:check
if not exist ".\%GameMachine%\build_Output.txt" ( 
        
    rem Esperar 1 segundo antes de volver a comprobar
    timeout /t 1 /nobreak > nul
    goto check 
        
)
rem Continuar con el archivo por lotes 
echo: && echo "> Todos los scripts han terminado!!" && echo: 



rem Ejecuta la instalación del videojuego (%Game%)

rem Directorios involucrados 
set "origen=.\%GameMachine%\Exe\Main\%Platform%\%Configuration%\" 
set "destinoMotor=.\%GameMachine%\Lib\%Platform%\%Configuration%\" 
set "destinoJuego=.\Bin\%Platform%\%Configuration%\"



rem Copia los binarios del motor al juego (motor --> juego) 
if /I "%Configuration%"=="Debug" ( 

    echo: && echo "> Copiando ficheros necesarios del motor %GameMachine% para: debug configuration." && echo: 
    robocopy /NJH %origen% %destinoMotor% %GameMachine%_d.lib 
    robocopy /NJH %origen% %destinoJuego% %GameMachine%_d.dll 
    set "targetGame=%Game%_d" 

) else if /I "%Configuration%"=="Release" (

    echo: && echo "> Copiando ficheros necesarios del motor %GameMachine% para: release configuration." && echo: 
    robocopy /NJH %origen% %destinoMotor% %GameMachine%.lib 
    robocopy /NJH %origen% %destinoJuego% %GameMachine%.dll 
    set "targetGame=%Game%" 

) else (
    echo ¡Algo falla en config.txt respecto a la opcion de configuracion!
)
if /i "%pause_option%"=="S" ( pause ) 



rem Llamada al DCP: Developer Command Prompt
call "%VS_PATH%\Common7\Tools\VsDevCmd.bat" 


rem Configuración preestablecida 
echo: && echo "> Instalando: %Game%" && echo: 

set "instalar-juego=false" 
if not exist "Bin\%Platform%\%Configuration%\%targetGame%.dll" ( set "instalar-juego=true" ) 
if /i "%recompile-game%"=="true" ( set "instalar-juego=true" ) 

if /i "%instalar-juego%"=="true" ( 

    rem Compilación del videojuego 
    msbuild %Game%.sln /t:Rebuild /p:Configuration=%Configuration% /p:Platform=%Platform% /p:PlatformToolset=v143 

    echo: && echo "> Instalacion %Game% en modo %Platform%_%Configuration% completada!" && echo: 
) else (
    echo: && echo "> El videojuego %Game% en modo %Platform%_%Configuration% ya se encontraba instalado." && echo: 
)
if /i "%pause_option%"=="S" ( pause ) 



rem Ejecuta la instalación del ejecutable (build final)
echo: && echo "> Actualizando directorio ASSETS." && echo: 

rem Dirección de recursos utilizados en el juego ( actualiza ASSETS ) 
set "origen=.\Assets\" 

rem Copia para ejecutar directamente  
echo: && echo "> Copiando recursos utilizados por %Game% para: build final." && echo: 
set "destino=.\%GameMachine%\Exe\Main\%Platform%\%Configuration%\Assets\" 
robocopy /NJH %origen% %destino% /E 

if /i "%pause_option%"=="S" ( pause ) 

rem Copia para ejecutar desde Visual Studio 
echo: && echo "> Copiando recursos utilizados por %Game% para: desarrollador." && echo: 
set "destino=.\%GameMachine%\Projects\Main\Assets\" 
robocopy /NJH %origen% %destino% /E 

if /i "%pause_option%"=="S" ( pause ) 



rem Copia el binario generado por el juego (juego --> motor) 
echo: && echo "> Copiando fichero final del videojuego %Game% para: arrancar desde motor." && echo: 
set "origen=.\Bin\%Platform%\%Configuration%\" 
set "destino=.\%GameMachine%\Exe\Main\%Platform%\%Configuration%\" 
robocopy /NJH %origen% %destino% %targetGame%.dll 

if /i "%pause_option%"=="S" ( pause ) 



rem Comprime el directorio final 
echo: && echo "> Comprimiendo build final del videojuego: %Game%." && echo: 

set "comprimir-build=false" 
if not exist "build_final_%Platform%_%Configuration%.7z" ( set "comprimir-build=true" ) 
if /i "%refresh%"=="true" ( set "comprimir-build=true" ) 

if /i "%comprimir-build%"=="true" (

    del build_final_%Platform%_%Configuration%.7z
    %zip% a -t7z -m0=lzma -mx=9 -mfb=64 -md=32m -ms=on build_final_%Platform%_%Configuration%.7z %source%/* 
    echo - Build %Platform%_%Configuration% comprimida con éxito!

) else (
    echo - Se ha encontrado una version anterior de la build %Platform%_%Configuration%. No se genera el nuevo fichero.
) 
if /i "%pause_option%"=="S" ( pause ) 



rem Arranca el juego desde el motor!! 
echo: && echo "> Ejecutando %Game%!!!" && echo: 
cd .\%GameMachine%\Exe\Main\%Platform%\%Configuration%\
call .\%targetMain%.exe 
cd %RootDirectory% 

if /i "%pause_option%"=="S" ( pause ) 


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