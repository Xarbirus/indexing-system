@echo off

set SCRIPT_DIR=%~dp0
set SCRIPT_DIR=%SCRIPT_DIR:~0,-1%

call "%SCRIPT_DIR%\generate-python-grpc.bat"  || exit /b 1

for %%F in ("%SCRIPT_DIR%") do set WORK_DIR=%%~dpF
set WORK_DIR=%WORK_DIR:~0,-1%

set CLIENT_DIR="%WORK_DIR%\pyclient\app"
set OUT_DIR="%WORK_DIR%\out\bin"
set BUILD_DIR="%WORK_DIR%\pybuild"

pyinstaller --distpath "%OUT_DIR%" ^
            --specpath "%BUILD_DIR%" ^
            --workpath "%BUILD_DIR%" ^
            --paths "%CLIENT_DIR%" ^
            --noconfirm ^
			--log-level WARN ^
            --onefile ^
            --name pyclient "%CLIENT_DIR%\main.py"

rd /s /q "%BUILD_DIR%"

echo python client built!
