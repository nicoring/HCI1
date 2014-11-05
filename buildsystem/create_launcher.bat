:: Creates a laucher for an application
:: Usage: create_launcher.bat <Debug|Release> <AppName>

@echo off
echo @echo off
echo setlocal
echo for /f "tokens=1* delims==" %%%%a in ('set') do (

:: Use this to exclude env-vars from being reset
echo if not %%%%a==SystemDrive if not %%%%a==SISODIR5 if not %%%%a==SystemRoot set %%%%a=)

:: Set custom env-vars here
echo set PATH=..\dependencies;..\..\dependencies;..\plugins;..\..\plugins;..\type;..\..\type;..
echo cd %1\apps
echo %2.exe