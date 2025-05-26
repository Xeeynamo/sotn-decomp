@echo off
set PATH=TOOLS\BUILDS\GCCSH;%PATH%
echo INPUT FILE: %1
TOOLS\BUILDS\GCCSH\CC1.EXE -%3 -m2 -fsigned-char %1 -o %2
