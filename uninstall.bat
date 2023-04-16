@echo off
setlocal

rem Configuración de paradas
if /I "%1"=="" (

    set /p pause_option="> Quieres que se generen pausas? [S/N]: "

) else ( set "pause_option=%1" ) 



echo:
echo Se va ha proceder a borrar el directorio BIN de ./root_project:
if /i "%pause_option%"=="S" ( pause ) && echo:

rmdir /s /q .\Bin 2>nul && echo - Borrado el directorio ./Bin || echo - No se ha encontrado el directorio ./Bin 


echo:
echo Se va ha proceder a borrar el directorio TEMP de ./root_project:
if /i "%pause_option%"=="S" ( pause ) && echo:

rmdir /s /q .\Temp 2>nul && echo - Borrado el directorio ./Temp || echo - No se ha encontrado el directorio ./Temp 



echo:
echo Se va ha proceder a borrar el registro de la build del juego:
if /i "%pause_option%"=="S" ( pause ) && echo:

rem Elimina si existe el anterior registro del juego
if exist "./build_Output.txt" (

    del "./build_Output.txt"
    echo - Borrado el registro del juego 

) else (
    echo - No se ha encontrado el registro del juego  
)



echo: && pause 
endlocal