#include "sattypes.h"
#include "inc_asm.h"
#include "sys.h"

const interrupt_t g_SysUintMacSaveStubs[32] = {
    (interrupt_t)0x06030CA4, (interrupt_t)0x06030CAA,
    (interrupt_t)0x06030CB0, (interrupt_t)0x06030CB6,
    (interrupt_t)0x06030CBC, (interrupt_t)0x06030CC2,
    (interrupt_t)0x06030CC8, (interrupt_t)0x06030CCE,
    (interrupt_t)0x06030CD4, (interrupt_t)0x06030CDA,
    (interrupt_t)0x06030CE0, (interrupt_t)0x06030CE6,
    (interrupt_t)0x06030CEC, (interrupt_t)0x06030CF2,
    NULL, NULL,
    (interrupt_t)0x06030CF8, (interrupt_t)0x06030CFE,
    (interrupt_t)0x06030D04, (interrupt_t)0x06030D0A,
    (interrupt_t)0x06030D10, (interrupt_t)0x06030D16,
    (interrupt_t)0x06030D1C, (interrupt_t)0x06030D22,
    (interrupt_t)0x06030D28, (interrupt_t)0x06030D2E,
    (interrupt_t)0x06030D34, (interrupt_t)0x06030D3A,
    (interrupt_t)0x06030D40, (interrupt_t)0x06030D46,
    (interrupt_t)0x06030D4C, (interrupt_t)0x06030D52,
};

const char* sys_version = "SYS Version 2.50 1997-06-10";
const u32 pad_06030af8 = 0x00000000;

// _SYS_SetUintMacSave
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6030AFC, func_06030AFC);

// _SYS_GetUintMacSave
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6030B88, func_06030B88);

INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6030BF4, func_06030BF4);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6030C2C, func_06030C2C);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6030C78, func_06030C78);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6030C88, func_06030C88);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6030D78, func_06030D78);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6030DAC, func_06030DAC);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6030DF0, func_06030DF0);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6031174, func_06031174);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60312EC, func_060312EC);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60313D4, func_060313D4);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60315A8, func_060315A8);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6031608, func_06031608);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f603168C, func_0603168C);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60319E8, func_060319E8);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6031A50, func_06031A50);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6031BA4, func_06031BA4);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6031C04, func_06031C04);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6031CF0, func_06031CF0);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6031D38, func_06031D38);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6031D98, func_06031D98);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6031DF8, func_06031DF8);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6031E5C, func_06031E5C);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6031EC0, func_06031EC0);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6031F20, func_06031F20);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6031F88, func_06031F88);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6032014, func_06032014);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60320A4, func_060320A4);
INCLUDE_ASM_NO_ALIGN("asm/saturn/zero/f_nonmat", f60320DE, func_060320DE);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f603210C, func_0603210C);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f603216C, func_0603216C);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60321D4, func_060321D4);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f603224C, func_0603224C);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6032314, func_06032314);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60323E4, func_060323E4);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f603247C, func_0603247C);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60325BC, func_060325BC);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6032610, func_06032610);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6032668, func_06032668);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60327B0, func_060327B0);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6032804, func_06032804);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60328C4, func_060328C4);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6032918, func_06032918);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60329EC, func_060329EC);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6032A30, func_06032A30);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6032A8C, func_06032A8C);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6032AE8, func_06032AE8);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6032B48, func_06032B48);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6032BA8, func_06032BA8);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6032C04, func_06032C04);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6032C64, func_06032C64);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6032CD4, func_06032CD4);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6032D5C, func_06032D5C);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6032D90, func_06032D90);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6032E28, func_06032E28);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6032E5C, func_06032E5C);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6032E68, func_06032E68);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6032E88, func_06032E88);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6032EFC, func_06032EFC);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6032F50, func_06032F50);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6032FAC, func_06032FAC);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6032FDC, func_06032FDC);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60330C0, func_060330C0);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60330F8, func_060330F8);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6033134, func_06033134);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60331AC, func_060331AC);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60331DC, func_060331DC);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f603327C, func_0603327C);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6035398, func_06035398);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6035434, func_06035434);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6035454, func_06035454);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6035474, func_06035474);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6035498, func_06035498);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60356EC, func_060356EC);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60357DC, func_060357DC);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6035838, func_06035838);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6035848, func_06035848);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f603586C, func_0603586C);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f603588C, func_0603588C);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60358D4, func_060358D4);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6035930, func_06035930);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60359D8, func_060359D8);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60359F4, func_060359F4);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6035A14, func_06035A14);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6035A90, func_06035A90);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6035B68, func_06035B68);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6035B94, func_06035B94);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6035BC8, func_06035BC8);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6035BF4, func_06035BF4);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6035C1C, func_06035C1C);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6035C7C, func_06035C7C);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6035D44, func_06035D44);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6035DBC, func_06035DBC);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6035DF4, func_06035DF4);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6035E7C, func_06035E7C);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6035EC8, func_06035EC8);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6035F2C, func_06035F2C);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6035F58, func_06035F58);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6035FA4, func_06035FA4);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6036010, func_06036010);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6036064, func_06036064);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6036084, func_06036084);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6036194, func_06036194);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6037774, func_06037774);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60377A8, func_060377A8);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60377E0, func_060377E0);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6037814, func_06037814);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f603784C, func_0603784C);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6037884, func_06037884);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60378BC, func_060378BC);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60378F4, func_060378F4);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6037914, func_06037914);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6037934, func_06037934);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6037954, func_06037954);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6037990, func_06037990);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60379EC, func_060379EC);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60379FC, func_060379FC);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6037A1C, func_06037A1C);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6037A3C, func_06037A3C);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6037A48, func_06037A48);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6037A54, func_06037A54);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6037A74, func_06037A74);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6037A98, func_06037A98);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6037AA4, func_06037AA4);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6037AB0, func_06037AB0);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6037AD0, func_06037AD0);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6037AF0, func_06037AF0);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6037B14, func_06037B14);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6037B34, func_06037B34);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6037B4C, func_06037B4C);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6037B68, func_06037B68);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6037B88, func_06037B88);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6037BA4, func_06037BA4);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6037BC0, func_06037BC0);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6037C44, func_06037C44);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6037C6C, func_06037C6C);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6037D38, func_06037D38);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6037DD4, func_06037DD4);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6037E40, func_06037E40);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6037EC0, func_06037EC0);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6037EE4, func_06037EE4);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60380A4, func_060380A4);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f603815C, func_0603815C);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6038244, func_06038244);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6038280, func_06038280);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6038390, func_06038390);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6038410, func_06038410);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6038500, func_06038500);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6038614, func_06038614);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60387BC, func_060387BC);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6038858, func_06038858);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60388A4, func_060388A4);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60388C4, func_060388C4);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60388F8, func_060388F8);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6038930, func_06038930);

// 68k sound driver
const u16 g_SoundDriver68k[] = {
#include "snd_driver_68k.inc"
};
