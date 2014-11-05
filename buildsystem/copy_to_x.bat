:: Copies the application binaries to the floor
:: Usage: copy_to_floor.bat <SourceDir> <DestDir> <AppName> <BuildsystemDir> <AppendDateString>

@echo off
setlocal enabledelayedexpansion
set copyflags=/r:0 /NDL /NJH /NJS /nc /ns /np
set destDir=%2
if not %5==TRUE goto copy
set timeStamp=%date%_%time%
set timeStamp=!timeStamp::=-!
set timeStamp=!timeStamp: =0!
set timeStamp=!timeStamp:.=-!
set timeStamp=!timeStamp:,=_!
set timeStamp=!timeStamp:/=-!
set destDir=%2_%timeStamp%

:copy
echo Copying "%3" to %destDir%
if not exist %destDir% mkdir %destDir%
robocopy %1 %destDir% MTQ.dll %copyflags%
robocopy %1\dependencies %destDir%\dependencies /e %copyflags%
robocopy %1\types %destDir%\types *.dll %copyflags%
robocopy %1\plugins %destDir%\plugins *.dll %copyflags%
robocopy %1\apps %destDir%\apps %3.exe %copyflags%
robocopy %1\apps\%3 %destDir%\apps\%3 /e %copyflags%
robocopy %1\apps\qml %destDir%\apps\qml /e %copyflags%

%4\create_launcher.bat . %3 %6 > %destDir%\start.bat