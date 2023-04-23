SECTIONS
{
    __romPos = 0;
    _gp = 0x0;
    module_ROM_START = __romPos;
    module_VRAM = ADDR(.module);
    .module 0x80170000 : AT(module_ROM_START) SUBALIGN(4)
    {
        ../../build/tools/sotn-debugmode/debugmode.o
        ../../build/tools/sotn-debugmode/entity_spawn.o
        ../../build/tools/sotn-debugmode/sfx_player.o
        ../../build/tools/sotn-debugmode/collision_viewer.o
        ../../build/tools/sotn-debugmode/dra_800FD874.o
        ../../build/tools/sotn-debugmode/flag_checker.o
        ../../build/tools/sotn-debugmode/stage_select.o
    }
    __romPos += SIZEOF(.module);
    __romPos = ALIGN(__romPos, 16);
    module_ROM_END = __romPos;
    module_VRAM_END = .;

    /DISCARD/ :
    {
        *(*);
    }
}
