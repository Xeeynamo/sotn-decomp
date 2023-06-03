# disassemble our binary
sh-elf-objdump -z -m sh2 -b binary -D $FILENAME > $FILENAME-ours.txt &&
# disassemble their binary
sh-elf-objdump -z -m sh2 -b binary -D /theirs/$FILENAME > $FILENAME-theirs.txt &&
# diff
diff $FILENAME-ours.txt $FILENAME-theirs.txt > $FILENAME-diff.txt || true
