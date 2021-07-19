@echo off
setlocal enabledelayedexpansion

call .\setPath.bat
set delimiter= 


rem ==================================================================================================================


rem Get cpp files
set pathFiles=
if exist "..\src\*.cpp" (
    for /f "tokens=* delims=" %%x in ('dir ..\src\*.cpp /S /B') do (
        set pathFiles=!pathFiles!%%x!delimiter!
    )
)

rem If no file will be compiled, exit
if "!pathFiles!"=="" (
    echo There is no file which should be compiled.
    exit /B
)

rem Compile
!kCL! /EHsc /c !kOptInclude! !pathFiles!


rem ==================================================================================================================


rem Get objs
set pathObjs=
for /f "tokens=* delims=" %%x in ('dir *.obj /S /B') do (
    set pathObjs=!pathObjs!%%x!delimiter!
)

rem Link
!kCL! /EHsc /Fe:main.exe !kOptInclude! !pathObjs! !kOptLibrary!

del *.obj

if exist main.exe (
    main.exe
)
