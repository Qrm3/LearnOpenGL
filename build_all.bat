@ECHO OFF
SETLOCAL ENABLEDELAYEDEXPANSION
:: ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
:: General Information
:: ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
:: build_all.bat
:: Builds the projects in the src directory. Will eventually move to using 
:: MAKE/CMAKE.

SET ROOT_DIR=%~dp0
:: Remove trailing slash.
SET ROOT_DIR=%ROOT_DIR:~0,-1%

SET DEBUG_DIR=%ROOT_DIR%\bin\debug
SET RELEASE_DIR=%ROOT_DIR%\bin\release

IF NOT EXIST "%DEBUG_DIR%" (
    MKDIR "%DEBUG_DIR%"
)

IF NOT EXIST "%RELEASE_DIR%" (
    MKDIR "%RELEASE_DIR%"
)

SET SRC_DIR=%ROOT_DIR%\src

SET LIBS_DIR=%ROOT_DIR%\libs
SET GLFW_DIR=%LIBS_DIR%\glfw-3.4.bin.WIN64

FOR /F %%d in ('DIR /AD /b "%SRC_DIR%"') DO ( 
    CALL "%SRC_DIR%\build.bat" "%ROOT_DIR%" "%DEBUG_DIR%" "%LIBS_DIR%" "%GLFW_DIR%" "%%d"

    IF "!ERRORLEVEL!" EQU "1" ( EXIT /b 1 )
)

EXIT /b 0

