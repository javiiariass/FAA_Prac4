@echo off
setlocal

echo Compilando proyecto FAA_Prac4 usando MSBuild directamente...

:: Rutas de posibles ubicaciones de MSBuild según la versión de Visual Studio
set MSBUILD_VS2019="C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\MSBuild\Current\Bin\MSBuild.exe"
set MSBUILD_VS2022="C:\Program Files\Microsoft Visual Studio\2022\Community\MSBuild\Current\Bin\MSBuild.exe"

:: Verificar si existe MSBuild en alguna de las ubicaciones
if exist %MSBUILD_VS2022% (
    set MSBUILD=%MSBUILD_VS2022%
) else if exist %MSBUILD_VS2019% (
    set MSBUILD=%MSBUILD_VS2019%
) else (
    echo ERROR: No se encontró MSBuild. Asegúrate de tener Visual Studio instalado.
    exit /b 1
)

:: Configuración y plataforma
set CONFIG=Release
set PLATFORM=x64

if not "%1"=="" set CONFIG=%1
if not "%2"=="" set PLATFORM=%2

echo Utilizando MSBuild: %MSBUILD%
echo Configuración: %CONFIG%
echo Plataforma: %PLATFORM%

echo.
echo Información sobre el modo de compilación:
if /i "%CONFIG%"=="Debug" (
    echo - Modo DEBUG: Incluye información de depuración, sin optimizaciones.
    echo - Útil para: Encontrar errores, ver variables durante depuración.
    echo - ADVERTENCIA: El rendimiento será significativamente menor que en Release.
) else if /i "%CONFIG%"=="Release" (
    echo - Modo RELEASE: Código optimizado para máximo rendimiento.
    echo - Útil para: Pruebas de rendimiento, distribución final.
    echo - Nota: Para experimentos de tiempo de ejecución, siempre usar Release.
)
echo.

:: Compilar el proyecto
%MSBUILD% FAA_Prac4.vcxproj /p:Configuration=%CONFIG% /p:Platform=%PLATFORM% /v:minimal

if %ERRORLEVEL% NEQ 0 (
    echo Error durante la compilación.
    exit /b 1
)

echo.
echo Compilación exitosa.
echo El ejecutable se encuentra en: %PLATFORM%\%CONFIG%\FAA_Prac4.exe

:: Preguntar si quiere ejecutar el programa
set /p EJECUTAR=¿Desea ejecutar el programa ahora? (S/N): 
if /i "%EJECUTAR%"=="S" (
    echo.
    echo Ejecutando programa...
    echo.
    start %PLATFORM%\%CONFIG%\FAA_Prac4.exe
)

endlocal
