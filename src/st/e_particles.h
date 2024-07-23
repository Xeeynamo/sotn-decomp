#include <stage.h>

#if defined(VERSION_HD)
static u32 padding = 0;
#endif

u16 g_ESoulStealOrbAngles[] = {
    0x820, 0x840, 0x860, 0x880, 0x8C0, 0x900, 0x940, 0xA00,
};

s16 g_ESoulStealOrbSprt[] = {
    0xFFFD, 0xFFFD, 0x0008, 0x0008, 0x00D0, 0x0068, 0x00D8, 0x0070,
    0xFFFD, 0xFFFD, 0x0008, 0x0008, 0x00C8, 0x0068, 0x00D0, 0x0070,
    0xFFF9, 0xFFF9, 0x0010, 0x000F, 0x00C8, 0x0070, 0x00D8, 0x007F,
    0xFFF5, 0xFFF5, 0x0018, 0x0017, 0x0080, 0x0068, 0x0098, 0x007F,
    0xFFF5, 0xFFF5, 0x0018, 0x0017, 0x0098, 0x0068, 0x00B0, 0x007F,
    0xFFF5, 0xFFF5, 0x0018, 0x0017, 0x00B0, 0x0068, 0x00C8, 0x007F,
};

u8 g_ESoulStealOrbAnim[] = {
    0x04, 0x02, 0x03, 0x03, 0x03, 0x04, 0x03,
    0x05, 0x03, 0x06, 0x03, 0x03, 0x00,
};

#ifdef VERSION_PSP
void func_psp_0923AD68(Entity*);
void func_psp_0923B2F0(Entity*);

#endif

extern u16 g_InitializeData0[];

#include "entity_soul_steal_orb.h"

#include "entity_enemy_blood.h"
