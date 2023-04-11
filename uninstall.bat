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



rem --------------------
rem TODO EL PROCESO AQUI
rem --------------------



rem Fecha final: 
set end_time=%time%


echo:
echo ----------------------------
echo Fecha inicio: %start_time% 
echo Fecha final: %end_time% 
echo:


rem Check final
echo "> Build %project% finalizada [ inicio: %start_time% // finalizado: %end_time% ]" > "./build_Output.txt"

pause
endlocal