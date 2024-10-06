@echo off
rem This file is the script to set path for ARM GNU Toolchain.

set TL_PATH=%~dp0
set PATH=%TL_PATH%;%PATH%
cmd /K cd %CD%
