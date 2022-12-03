@echo off

setlocal EnableDelayedExpansion

set AVAILABLE_BUILDS=(debug, release, relwithdebinfo)

set ARGC_MIN=2
set ARGC_MAX=3

set ARGC_ACTUAL=0
for %%i in (%*) do set /A ARGC_ACTUAL+=1
if %ARGC_ACTUAL% lss %ARGC_MIN% goto wrong_arg
if %ARGC_ACTUAL% gtr %ARGC_MAX% goto wrong_arg

set SCRIPT_DIR=%~dp0
set SCRIPT_DIR=%SCRIPT_DIR:~0,-1%

for %%F in ("%SCRIPT_DIR%") do set WORK_DIR=%%~dpF
set WORK_DIR=%WORK_DIR:~0,-1%

set CONAN_PROFILE=%1
set BUILD_TYPE=%2
set TESTS=%3

for %%L in %AVAILABLE_BUILDS% do (
	if %BUILD_TYPE%==%%L goto match
)
echo Correct build type is required!
goto usage

:match
set "BUILD_DETAILS=-DCMAKE_BUILD_TYPE=%BUILD_TYPE%"
set BUILD_DIR="%WORK_DIR%\cmake-build-%BUILD_TYPE%"

set result=False
if "%TESTS%" equ "1" (
	set result=True
) else (
	if [%TESTS%] neq [] if "%TESTS%" neq "0" (
		echo Incorrect 'tests' value!
		goto usage
	)
)

if "%result%" equ "True" (
	set "BUILD_DETAILS=%BUILD_DETAILS% -DTESTS=1"
) else (
	set "BUILD_DETAILS=%BUILD_DETAILS% -DTESTS=0"
)

if exist %BUILD_DIR% rd /s /q "%BUILD_DIR%"
mkdir %BUILD_DIR%

conan install "%WORK_DIR%" -if="%BUILD_DIR%" -pr="%CONAN_PROFILE%" --build missing
if %errorlevel% neq 0 exit /b %errorlevel%

cmake -G "Ninja" %BUILD_DETAILS% -S "%WORK_DIR%" -B "%BUILD_DIR%"
if %errorlevel% neq 0 exit /b %errorlevel%

ninja -C "%BUILD_DIR%" -j4
if %errorlevel% neq 0 exit /b %errorlevel%

if "%TESTS%" equ "1" (
	set "TESTS_DIR=%WORK_DIR%\out\tests"
	set "OUT_FILE=%TESTS_DIR%\out.txt"

	for /f %%F in ('dir %TESTS_DIR%\*.exe /s/b ') do (
		echo "%%F"
		type NUL > "%OUT_FILE%"
		start "%%F" /b /wait %%F >> "%OUT_FILE%"
		findstr "FAILED" %OUT_FILE%>nul 2>&1
		if !errorlevel!==0 (
			type %OUT_FILE%
			exit /b 1
		) else (
		    echo Success
		)
	)
	DEL "%OUT_FILE%"
)

echo cpp server built!
exit /b 0

:wrong_arg
echo Wrong number of arguments.
goto usage

:usage
set AVAILABLE_BUILDS_PARSED=""
for %%s in %AVAILABLE_BUILDS% do call set "AVAILABLE_BUILDS_PARSED=%%AVAILABLE_BUILDS_PARSED%%, %%s"
set AVAILABLE_BUILDS_PARSED=%AVAILABLE_BUILDS_PARSED:~4%
echo Usage: %~nx0 [conan_profile] [build_type: %AVAILABLE_BUILDS_PARSED%] [tests (optional): 0, 1]
exit /b 1
