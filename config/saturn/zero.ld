SECTIONS
{
    __romPos = 0;
    _gp = 0x0;
    zero_ROM_START = __romPos;
    zero_VRAM = ADDR(.zero);
    .zero 0x06004080 : AT(zero_ROM_START) SUBALIGN(4)
    {
        zero_TEXT_START = .;
        build/saturn/zero.o(.text);
        build/saturn/lib/gfs.o(.text);
        build/saturn/lib/spr/spr_1c.o(.text);
        build/saturn/lib/spr/spr_2c.o(.text);
        build/saturn/lib/spr/spr_slv.o(.text);
        build/saturn/lib/dma/dma_cpum.o(.text);
        build/saturn/lib/dma/dma_scu1.o(.text);
        build/saturn/lib/dma/dma_scu0.o(.text);
        build/saturn/lib/dma/dma_cpu0.o(.text);
        build/saturn/lib/scl.o(.text);
        build/saturn/lib/csh.o(.text);
        build/saturn/lib/per.o(.text);
        build/saturn/lib/cdc.o(.text);
        build/saturn/lib/mth.o(.text);
        build/saturn/lib/int.o(.text);
        build/saturn/lib/bup.o(.text);
        build/saturn/lib/sys.o(.text);
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
