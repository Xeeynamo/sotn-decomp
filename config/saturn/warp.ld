SECTIONS
{
    __romPos = 0;
    _gp = 0x0;
    warp_ROM_START = __romPos;
    warp_VRAM = ADDR(.warp);
    .warp 0x060DC000 : AT(warp_ROM_START) SUBALIGN(2)
    {
        warp_TEXT_START = .;
        build/saturn/warp.o(.text);
        warp_TEXT_END = .;
        warp_TEXT_SIZE = ABSOLUTE(warp_TEXT_END - warp_TEXT_START);
    }
    __romPos += SIZEOF(.warp);
    __romPos = ALIGN(__romPos, 16);
    warp_ROM_END = __romPos;
    warp_VRAM_END = .;

    /DISCARD/ :
    {
        *(*);
    }
}
