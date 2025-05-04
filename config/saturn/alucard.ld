SECTIONS
{
    __romPos = 0;
    _gp = 0x0;
    alucard_ROM_START = __romPos;
    alucard_VRAM = ADDR(.alucard);
    .alucard 0x060A5000 : AT(alucard_ROM_START) SUBALIGN(2)
    {
        alucard_TEXT_START = .;
        build/saturn/alucard.o(.text);
        alucard_TEXT_END = .;
        alucard_TEXT_SIZE = ABSOLUTE(alucard_TEXT_END - alucard_TEXT_START);
    }
    __romPos += SIZEOF(.alucard);
    __romPos = ALIGN(__romPos, 16);
    alucard_ROM_END = __romPos;
    alucard_VRAM_END = .;

    /DISCARD/ :
    {
        *(*);
    }
}
