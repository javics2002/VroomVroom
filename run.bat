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


rem Selecciona el objetivo a ejecutar según la configuración 
if /I "%Configuration%"=="Debug" ( 
    set "targetMain=Main_d"
) else if /I "%Configuration%"=="Release" ( 
    set "targetMain=Main" 
) else (
    echo ¡Algo falla en config.txt respecto a la opcion de configuracion!
)


rem Arranca el juego desde el motor!! 
echo: && echo "> Ejecutando %Game%!!!" && echo: 
cd .\%GameMachine%\Exe\Main\%Platform%\%Configuration%\
call .\%targetMain%.exe 


pause
endlocal