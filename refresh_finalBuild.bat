@echo off
setlocal


rem Variables necesarias: 
if not exist "config.txt" (

    rem Variables del proyecto: 
    set "Game=VroomVroom" 
    set "GameMachine=MotorEngine" 
    set "Platform=x64" 
    set "Configuration=Debug" 

) else (

    rem Se crean las variables: %Game% , %GameMachine% , %Platform% y %Configuration% 
    for /f "tokens=1,* delims=: " %%a in ('type config.txt ^| findstr /i "Game: GameMachine: Platform: Configuration: "') do (

        rem Asigna a la variable de nombre 'key' el valor de 'value' 
        set "%%a=%%b" 

    ) 

)


rem Referencia a la herramienta de compresión: 
set "zip=.\%GameMachine%\Dependencies\7zip\7za.exe" 


rem Comprime el directorio final: 
echo: && echo "> Comprimiendo build final del videojuego %Game%." && echo: 
set "source=.\%GameMachine%\Exe\Main\%Platform%\%Configuration%\" 
%zip% a -t7z -m0=lzma -mx=9 -mfb=64 -md=32m -ms=on build_final_%Platform%_%Configuration%.7z %source%/* 


endlocal 
exit 