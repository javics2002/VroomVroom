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

rem Se crean las variables: %Game% , %GameMachine% , %Platform% , %Configuration% , %debug% , %run_type% y %refresh%
for /f "tokens=1,* delims=: " %%a in ('type config.txt ^| findstr /i "Game: GameMachine: Platform: Configuration: debug: run_type: refresh: "') do (

    rem Asigna a la variable de nombre 'key' el valor de 'value' 
    set "%%a=%%b" 

) 


rem Referencia a la herramienta de compresión: 
set "zip=.\%GameMachine%\Dependencies\7zip\7za.exe" 


rem Formatea la salida de pause_option 
if /i "%debug%"=="true" ( 
    
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
echo   debug: %debug% 
echo   run_type: %run_type% 
echo   refresh: %refresh% 
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

if not exist ".\%GameMachine%\build_Output.txt" ( 

    cd .\%GameMachine% 
    echo: && echo "> Instalando: %GameMachine%" && echo: 
    if /i "%exec_option%"=="S" ( call .\install.bat %pause_option% %exec_option% ) else if /i "%exec_option%"=="P" ( start .\install.bat %pause_option% %exec_option% ) 
    cd .. 

) else (

    echo: && echo "> El motor de videojuegos %GameMachine% ya se encuentra instalado." && echo: 

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



rem Ejecuta la instalación del juego (VroomVroom)

rem Directorios involucrados 
set "origen=.\%GameMachine%\Exe\Main\%Platform%\%Configuration%\" 
set "destinoMotor=.\%GameMachine%\Lib\%Platform%\%Configuration%\" 
set "destinoJuego=.\Bin\%Platform%\%Configuration%\"


rem Copia los binarios del motor al juego 
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
if not exist "Bin\%Platform%\%Configuration%\%targetGame%.dll" ( 

    rem Compilación 
    msbuild %Game%.sln /t:Rebuild /p:Configuration=%Configuration% /p:Platform=%Platform% /p:PlatformToolset=v143 

    echo: && echo "> Build %Game% solucion en modo debug compilada." && echo: 
) else (
    echo: && echo "> Build %Game% solucion en modo debug ya existe." && echo: 
)
if /i "%pause_option%"=="S" ( pause ) 



rem Ejecuta la instalación del ejecutable (build final)
echo: && echo "> Generando build final." && echo: 


rem Dirección de archivos de configuración de Ogre 
set "origen=.\%GameMachine%\Dependencies\Ogre\" 

rem Copia para ejecutar directamente 
echo: && echo "> Copiando ficheros necesarios del motor de renderizado de %GameMachine% para: build final." && echo: 
set "destino=.\%GameMachine%\Exe\Main\%Platform%\%Configuration%\" 
robocopy /NJH %origen% %destino% *.cfg 

if /i "%pause_option%"=="S" ( pause ) 


rem Dirección de recursos utilizados en el juego
set "origen=.\%GameMachine%\Assets\" 

rem Copia para ejecutar directamente  
echo: && echo "> Copiando ficheros necesarios del videojuego %Game% para: build final." && echo: 
set "destino=.\%GameMachine%\Exe\Main\%Platform%\%Configuration%\Assets\" 
robocopy /NJH %origen% %destino% /E 

if /i "%pause_option%"=="S" ( pause ) 


rem Copia el binario generado por el juego
echo: && echo "> Copiando fichero final del videojuego %Game% para: arrancar desde motor." && echo: 
set "origen=.\Bin\%Platform%\%Configuration%\" 
set "destino=.\%GameMachine%\Exe\Main\%Platform%\%Configuration%\" 
robocopy /NJH %origen% %destino% %targetGame%.dll 

if /i "%pause_option%"=="S" ( pause ) 


rem Comprime el directorio final 
echo: && echo "> Comprimiendo build final del videojuego %Game%." && echo: 
if exist "build_final_%Platform%_%Configuration%.7z" (

    if /i "%refresh%"=="true" (

        del build_final_%Platform%_%Configuration%.7z
        %zip% a -t7z -m0=lzma -mx=9 -mfb=64 -md=32m -ms=on build_final_%Platform%_%Configuration%.7z %source%/* 
        echo - Archivo comprimido con exito.

    ) else (
        echo - Se ha encontrado una version anterior. No se genera el nuevo fichero.
    ) 

) else (

    %zip% a -t7z -m0=lzma -mx=9 -mfb=64 -md=32m -ms=on build_final_%Platform%_%Configuration%.7z %source%/* 
    echo - Archivo comprimido con exito.

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