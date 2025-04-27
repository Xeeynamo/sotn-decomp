SECTIONS
{
    __romPos = 0;
    _gp = 0x0;
    stage_02_ROM_START = __romPos;
    stage_02_VRAM = ADDR(.stage_02);
    .stage_02 0x060DC000 : AT(stage_02_ROM_START) SUBALIGN(2)
    {
        stage_02_TEXT_START = .;
        build/saturn/stage_02.o(.text);
        stage_02_TEXT_END = .;
        stage_02_TEXT_SIZE = ABSOLUTE(stage_02_TEXT_END - stage_02_TEXT_START);
    }
    __romPos += SIZEOF(.stage_02);
    __romPos = ALIGN(__romPos, 16);
    stage_02_ROM_END = __romPos;
    stage_02_VRAM_END = .;

    /DISCARD/ :
    {
        *(*);
    }
}
