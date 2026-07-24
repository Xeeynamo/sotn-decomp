@echo off
set PATH=TOOLS\BUILDS\GCCSH;%PATH%
TOOLS\BUILDS\GCCSH\CC1.EXE -%3 -m2 -fsigned-char -quiet %1 -o %2
