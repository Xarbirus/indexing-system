@echo off

set SCRIPT_DIR=%~dp0
set SCRIPT_DIR=%SCRIPT_DIR:~0,-1%

for %%F in ("%SCRIPT_DIR%") do set WORK_DIR=%%~dpF
set WORK_DIR=%WORK_DIR:~0,-1%

set PROTO_DIR=%WORK_DIR%\proto
set OUT_DIR=%WORK_DIR%\pyclient\app

python -B -m pip install -q -r "%WORK_DIR%\requirements.txt"

for /f %%F in ('dir /s/b %PROTO_DIR%\*.proto') do (
	python -B -m grpc_tools.protoc --proto_path generated/grpc="%PROTO_DIR%" ^
								--python_out="%OUT_DIR%" ^
								--pyi_out="%OUT_DIR%" ^
								--grpc_python_out="%OUT_DIR%" ^
								%%F
	if %errorlevel% neq 0 exit /b %errorlevel%
)

REM. >"%OUT_DIR%\generated\__init__.py"
REM. >"%OUT_DIR%\generated\grpc\__init__.py"

echo python grpc generated!
