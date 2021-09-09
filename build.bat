@echo off

echo Compilation started at %date% %time%

if not exist build mkdir build
pushd build
if "%1" == "" g++ -O2 ../src/watch.c -o watch.exe
if "%1" == "debug" cl -Zi -Od ../src/watch.c
popd

IF %ERRORLEVEL% NEQ 0 goto :compilation_failed

echo.
echo Compilation [1m[32mfinished[0m at %date% %time%

if "%1" == "debug" goto :debug

goto :done

:compilation_failed
echo.
echo Compilation [1m[31mfailed[0m at %date% %time%
goto :done_err

:debug
tasklist /fi "ImageName eq devenv.exe" /fo csv 2>NUL | find /I "devenv.exe">NUL
if %ERRORLEVEL% NEQ 0 echo [1mRunning debugger...[0m && call devenv build/watch.exe
goto :done

:done
EXIT /B 0

:done_err
EXIT /B -1

