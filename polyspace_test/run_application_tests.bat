@echo off
python "%~dp0run_application_tests.py" %*
exit /b %errorlevel%
