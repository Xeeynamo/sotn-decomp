SECTIONS
{
    __romPos = 0;
    _gp = 0x0;
    richter_ROM_START = __romPos;
    richter_VRAM = ADDR(.richter);
    .richter 0x060A5000 : AT(richter_ROM_START) SUBALIGN(2)
    {
        richter_TEXT_START = .;
        build/saturn/richter.o(.text);
        richter_TEXT_END = .;
        richter_TEXT_SIZE = ABSOLUTE(richter_TEXT_END - richter_TEXT_START);
    }
    __romPos += SIZEOF(.richter);
    __romPos = ALIGN(__romPos, 16);
    richter_ROM_END = __romPos;
    richter_VRAM_END = .;

    /DISCARD/ :
    {
        *(*);
    }
}
