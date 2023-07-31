SECTIONS
{
    __romPos = 0;
    _gp = 0x0;
    zero_ROM_START = __romPos;
    zero_VRAM = ADDR(.zero);
    .zero 0x06004080 : AT(zero_ROM_START) SUBALIGN(2)
    {
        zero_TEXT_START = .;
        zero.o(.text);
        lib/gfs.o(.text);
        lib/spr.o(.text);
        lib/dma.o(.text);
        lib/scl.o(.text);
        lib/csh.o(.text);
        lib/per.o(.text);
        lib/cdc.o(.text);
        lib/mth.o(.text);
        lib/bup.o(.text);
        lib/sys.o(.text);
        zero_TEXT_END = .;
        zero_TEXT_SIZE = ABSOLUTE(zero_TEXT_END - zero_TEXT_START);
    }
    __romPos += SIZEOF(.zero);
    __romPos = ALIGN(__romPos, 16);
    zero_ROM_END = __romPos;
    zero_VRAM_END = .;

    /DISCARD/ :
    {
        *(*);
    }
}
