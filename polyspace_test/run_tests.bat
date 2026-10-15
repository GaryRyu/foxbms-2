@echo off
setlocal enableextensions
python "%~dp0run_tests.py" %*
exit /b %errorlevel%
