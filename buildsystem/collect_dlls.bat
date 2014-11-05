:: Copies all dlls to the dependencies directory
:: Usage: collect_dlls.bat <Debug|Release> <SourceDir>

@echo off
setlocal enabledelayedexpansion
set copyflags=/r:0 /NDL /NJH /NJS /nc /ns /np

if %1 == release goto rel
goto deb

:deb
echo Collecting Debug-Dlls from %2.
for %%i in (%2/*.dll) do (
	set file=%%~ni%%~xi
	set target=%3
	set source=%2
	set dest=!target!/!file!
	set debug=%2/%%~nid%%~xi

	if not exist !debug! (
		if not exist !dest! (
			robocopy !source:/=\! !target:/=\! !file! %copyflags%
		)
	)
)
goto end

:rel
echo Collecting Release-Dlls from %2.
for %%i in (%2/*.dll) do (
	set file=%%~ni%%~xi
	set target=%3
	set source=%2
	set dest=!target!/!file!

	set release=%2/%%~ni
	set lastchar=!release:~-1!
	set release=!release:~0,-1!
	set release=!release!%%~xi
	if not !lastchar! == d (
		if not exist  !dest! (
			robocopy !source:/=\! !target:/=\! !file! %copyflags%
		)
	) else (
		if not exist !release! (
			if not exist !dest! (
				robocopy !source:/=\! !target:/=\! !file! %copyflags%
			)
		)
	)
)
goto end

:end