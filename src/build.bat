@ECHO OFF
:: ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
:: General Information
:: ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
:: build.bat
:: Builds project executables.

:: Params
SET ROOT_DIR=%~1
SET DEBUG_DIR=%~2
SET LIBS_DIR=%~3
SET GLFW_DIR=%~4
SET OUT_DIR_NAME=%~5

SET OUT_DIR=%DEBUG_DIR%\%OUT_DIR_NAME%

IF NOT EXIST "%OUT_DIR%" (
    MKDIR "%OUT_DIR%"
)

SET PROJECT_DIR=%ROOT_DIR%\src\%OUT_DIR_NAME%

PUSHD %PROJECT_DIR%

SET SRC_FILES=%LIBS_DIR%\glad\src\glad.c

FOR /F %%f in ('DIR /s /b "*.c"') DO (
    SET SRC_FILES=!SRC_FILES! %%f
)

POPD

SET COMPILE_FLAGS=-ggdb -m64 -Werror
SET INCLUDE_FLAGS=-I "%ROOT_DIR%\include" -I "%PROJECT_DIR%" -I "%GLFW_DIR%\include" -I "%LIBS_DIR%\glad\include"
SET LINKER_FLAGS=-Wl,--whole-archive "%GLFW_DIR%\lib-mingw-w64\libglfw3.a" -Wl,--no-whole-archive -lOpenGL32 -lgdi32
SET DEFINE_FLAGS=
SET OUTPUT=-o %OUT_DIR%\%OUT_DIR_NAME%.exe 

ECHO Building %OUT_DIR_NAME% executable

gcc %COMPILE_FLAGS% %SRC_FILES% %DEFINE_FLAGS% %OUTPUT% %INCLUDE_FLAGS% %LINKER_FLAGS%

IF "%ERRORLEVEL%" EQU "0" (
    ECHO Building %OUT_DIR_NAME% executable complete
    EXIT /b 0
) ELSE (
    ECHO Building %OUT_DIR_NAME% executable failed
    EXIT /b 1
)
