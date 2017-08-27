@echo off

setlocal

REM %1 is {fileDirname}
REM %2 is {fileBasename}
REM %3 is {fileBasenameNoExtension}

set fileDirname=%1
set fileBasename=%2
set file=%fileDirname%\%fileBasename%
set outputfile=%3

REM Set the environment to call the MSVC compiler

call "%ProgramFiles(x86)%\Microsoft Visual Studio\2017\Enterprise\VC\Auxiliary\Build\vcvarsall.bat" x64
set compilerflags=/Od /Zi /EHsc
set linkerflags=/OUT:%fileDirname%\%outputfile%.exe

cl.exe %compilerflags% %file% /link %linkerflags%

endlocal