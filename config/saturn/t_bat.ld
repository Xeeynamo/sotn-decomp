SECTIONS
{
    __romPos = 0;
    _gp = 0x0;
    t_bat_ROM_START = __romPos;
    t_bat_VRAM = ADDR(.t_bat);
    .t_bat 0x060CF000 : AT(t_bat_ROM_START) SUBALIGN(2)
    {
        t_bat_TEXT_START = .;
        build/saturn/t_bat.o(.text);
        t_bat_TEXT_END = .;
        t_bat_TEXT_SIZE = ABSOLUTE(t_bat_TEXT_END - t_bat_TEXT_START);
    }
    __romPos += SIZEOF(.t_bat);
    __romPos = ALIGN(__romPos, 16);
    t_bat_ROM_END = __romPos;
    t_bat_VRAM_END = .;

    /DISCARD/ :
    {
        *(*);
    }
}
