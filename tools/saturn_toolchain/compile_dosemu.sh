# build object file with dosemu
HOME="." dosemu -quiet -dumb -f ./dosemurc -K . -E "GCC.EXE -c -O2 -m2 -fsigned-char $FILENAME.c -o $FILENAME.o"
