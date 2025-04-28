@echo off
set PATH=TOOLS\SATURN\GCCSH;%PATH%
echo INPUT FILE: %1
TOOLS\SATURN\GCCSH\CC1.EXE -%3 -m2 -fsigned-char %1 -o %2
