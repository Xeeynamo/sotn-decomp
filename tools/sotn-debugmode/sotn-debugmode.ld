SECTIONS
{
    __romPos = 0;
    _gp = 0x0;
    module_ROM_START = __romPos;
    module_VRAM = ADDR(.module);
    .module 0x80170000 : AT(module_ROM_START) SUBALIGN(4)
    {
        ../../build/tools/sotn-debugmode/debugmode.o(.data);
        ../../build/tools/sotn-debugmode/entity_spawn.o(.data);
        ../../build/tools/sotn-debugmode/sfx_player.o(.data);
        ../../build/tools/sotn-debugmode/collision_viewer.o(.data);
        ../../build/tools/sotn-debugmode/dra_800FD874.o(.data);
        ../../build/tools/sotn-debugmode/flag_checker.o(.data);
        ../../build/tools/sotn-debugmode/debugmode.o(.rodata);
        ../../build/tools/sotn-debugmode/entity_spawn.o(.rodata);
        ../../build/tools/sotn-debugmode/sfx_player.o(.rodata);
        ../../build/tools/sotn-debugmode/collision_viewer.o(.rodata);
        ../../build/tools/sotn-debugmode/flag_checker.o(.rodata);
        ../../build/tools/sotn-debugmode/dra_800FD874.o(.rodata);
        ../../build/tools/sotn-debugmode/debugmode.o(.text);
        ../../build/tools/sotn-debugmode/entity_spawn.o(.text);
        ../../build/tools/sotn-debugmode/sfx_player.o(.text);
        ../../build/tools/sotn-debugmode/collision_viewer.o(.text);
        ../../build/tools/sotn-debugmode/flag_checker.o(.text);
        ../../build/tools/sotn-debugmode/dra_800FD874.o(.text);
        ../../build/tools/sotn-debugmode/debugmode.o(.scommon);
        ../../build/tools/sotn-debugmode/entity_spawn.o(.scommon);
        ../../build/tools/sotn-debugmode/sfx_player.o(.scommon);
        ../../build/tools/sotn-debugmode/collision_viewer.o(.scommon);
        ../../build/tools/sotn-debugmode/flag_checker.o(.scommon);
        ../../build/tools/sotn-debugmode/dra_800FD874.o(.scommon);
        ../../build/tools/sotn-debugmode/debugmode.o(.sbss);
        ../../build/tools/sotn-debugmode/entity_spawn.o(.sbss);
        ../../build/tools/sotn-debugmode/sfx_player.o(.sbss);
        ../../build/tools/sotn-debugmode/collision_viewer.o(.sbss);
        ../../build/tools/sotn-debugmode/flag_checker.o(.sbss);
        ../../build/tools/sotn-debugmode/dra_800FD874.o(.sbss);
        ../../build/tools/sotn-debugmode/debugmode.o(.bss);
        ../../build/tools/sotn-debugmode/entity_spawn.o(.bss);
        ../../build/tools/sotn-debugmode/sfx_player.o(.bss);
        ../../build/tools/sotn-debugmode/collision_viewer.o(.bss);
        ../../build/tools/sotn-debugmode/flag_checker.o(.bss);
        ../../build/tools/sotn-debugmode/dra_800FD874.o(.bss);
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
