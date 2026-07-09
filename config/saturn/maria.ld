SECTIONS
{
    __romPos = 0;
    _gp = 0x0;
    maria_ROM_START = __romPos;
    maria_VRAM = ADDR(.maria);
    .maria 0x060A5000 : AT(maria_ROM_START) SUBALIGN(2)
    {
        maria_TEXT_START = .;
        build/saturn/maria.o(.text);
        maria_TEXT_END = .;
        maria_TEXT_SIZE = ABSOLUTE(maria_TEXT_END - maria_TEXT_START);
    }
    __romPos += SIZEOF(.maria);
    __romPos = ALIGN(__romPos, 16);
    maria_ROM_END = __romPos;
    maria_VRAM_END = .;

    /DISCARD/ :
    {
        *(*);
    }
}
