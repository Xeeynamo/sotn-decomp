// SPDX-License-Identifier: AGPL-3.0-or-later
#include <stage.h>
#include "sfx.h"

#if defined(VERSION_US)
static u16 g_testCollEnemyLookup[] = {
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x001E, 0x0000, 0x0000,
    0x002B, 0x0000, 0x0010, 0x0000, 0x000D, 0x0068, 0x0068, 0x0016, 0x0000,
    0x0000, 0x0000, 0x003E, 0x0000, 0x0023, 0x0050, 0x0000, 0x0000, 0x0000,
    0x0006, 0x0000, 0x000A, 0x0000, 0x007D, 0x0000, 0x0000, 0x002D, 0x0000,
    0x0000, 0x006D, 0x007B, 0x0000, 0x0017, 0x0041, 0x0000, 0x0073, 0x0000,
    0x004C, 0x0000, 0x0000, 0x0038, 0x0014, 0x005C, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0046, 0x0000,
    0x0000, 0x0003, 0x0058, 0x0044, 0x0024, 0x0037, 0x0000, 0x0002, 0x0059,
    0x0000, 0x0000, 0x0000, 0x0007, 0x0000, 0x0056, 0x0000, 0x007C, 0x0000,
    0x000B, 0x0000, 0x0026, 0x0000, 0x001D, 0x0000, 0x0000, 0x002A, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0027, 0x0000, 0x0000, 0x0000, 0x001C, 0x0000,
    0x0031, 0x0000, 0x0000, 0x001A, 0x0000, 0x008D, 0x0009, 0x002C, 0x0030,
    0x0020, 0x0000, 0x0005, 0x0047, 0x0000, 0x005E, 0x0035, 0x0034, 0x006A,
    0x0000, 0x003A, 0x0000, 0x0066, 0x0000, 0x0045, 0x0000, 0x0019, 0x0000,
    0x0071, 0x0000, 0x0029, 0x0039, 0x0000, 0x0051, 0x0000, 0x004D, 0x0000,
    0x0000, 0x003F, 0x0000, 0x0077, 0x0000, 0x0000, 0x0072, 0x0000, 0x0000,
    0x006F, 0x0000, 0x002F, 0x0000, 0x0074, 0x0000, 0x0000, 0x0079, 0x0000,
    0x007A, 0x0000, 0x0000, 0x0013, 0x0011, 0x0036, 0x0036, 0x0000, 0x005F,
    0x005F, 0x0000, 0x0000, 0x0067, 0x0000, 0x0075, 0x0000, 0x0001, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0008, 0x0000, 0x0000, 0x000E, 0x0000,
    0x002E, 0x0000, 0x0069, 0x0021, 0x0000, 0x0000, 0x0055, 0x0000, 0x0054,
    0x0000, 0x0053, 0x0000, 0x0000, 0x000F, 0x0000, 0x0076, 0x0000, 0x0000,
    0x008E, 0x0000, 0x0000, 0x0000, 0x0000, 0x004A, 0x0000, 0x0000, 0x004B,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0043, 0x0000, 0x0000, 0x003D, 0x0000,
    0x0078, 0x008A, 0x0000, 0x0000, 0x0000, 0x0052, 0x0000, 0x0000, 0x0089,
    0x0048, 0x0000, 0x003C, 0x0040, 0x008B, 0x0000, 0x0000, 0x0000, 0x001F,
    0x0000, 0x0000, 0x007E, 0x0000, 0x0000, 0x0049, 0x0000, 0x0000, 0x0000,
    0x0015, 0x0000, 0x0000, 0x000C, 0x0028, 0x0000, 0x0000, 0x0000, 0x0032,
    0x0000, 0x0022, 0x0012, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0033, 0x0060, 0x0000, 0x0064, 0x0000, 0x0000, 0x007F, 0x0000, 0x0000,
    0x0000, 0x004E, 0x0000, 0x006E, 0x0000, 0x0000, 0x0000, 0x004F, 0x0000,
    0x0000, 0x0057, 0x0000, 0x0000, 0x0000, 0x0086, 0x0065, 0x0000, 0x003B,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0025, 0x0062, 0x0062,
    0x0000, 0x0000, 0x0000, 0x0042, 0x0000, 0x0000, 0x0018, 0x001B, 0x006B,
    0x0000, 0x008C, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0061, 0x0063,
    0x0088, 0x0000, 0x0000, 0x0000, 0x0085, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0084, 0x0000, 0x0000, 0x0087, 0x0000, 0x0000, 0x0000, 0x0000,
    0x005D, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x005B,
    0x0091, 0x0000, 0x0000, 0x0000, 0x0000, 0x0090, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x005A, 0x0000, 0x0000, 0x0082, 0x0000, 0x0000,
    0x0000, 0x0083, 0x0000, 0x0081, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0092, 0x0000, 0x0000, 0x0000, 0x0000, 0x0004, 0x0000, 0x0070,
    0x0000, 0x0000, 0x006C, 0x0000, 0x0000, 0x0080, 0x0080, 0x0000, 0x0000,
    0x008F, 0x0000, 0x0000, 0x0000,
};

#elif defined(VERSION_HD)
static u16 g_testCollEnemyLookup[] = {
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x001E, 0x0000, 0x0000,
    0x002A, 0x0000, 0x0011, 0x0000, 0x000E, 0x0068, 0x0068, 0x0016, 0x0000,
    0x0000, 0x0000, 0x003D, 0x0000, 0x0028, 0x0052, 0x0000, 0x0000, 0x0000,
    0x0008, 0x0000, 0x000B, 0x0000, 0x007B, 0x0000, 0x0000, 0x002D, 0x0000,
    0x0000, 0x006F, 0x007A, 0x0000, 0x0018, 0x0041, 0x0000, 0x0070, 0x0000,
    0x004D, 0x0000, 0x0000, 0x0035, 0x0015, 0x005C, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0046, 0x0000,
    0x0000, 0x0005, 0x0056, 0x0042, 0x0025, 0x0034, 0x0000, 0x0002, 0x0059,
    0x0000, 0x0000, 0x0000, 0x0007, 0x0000, 0x0057, 0x0000, 0x007D, 0x0000,
    0x0009, 0x0000, 0x0023, 0x0000, 0x001D, 0x0000, 0x0000, 0x002B, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0021, 0x0000, 0x0000, 0x0000, 0x001B, 0x0000,
    0x0031, 0x0000, 0x0000, 0x0019, 0x0000, 0x008D, 0x000A, 0x002C, 0x0030,
    0x0020, 0x0000, 0x0004, 0x0048, 0x0000, 0x005E, 0x0037, 0x0036, 0x0069,
    0x0000, 0x003B, 0x0000, 0x0065, 0x0000, 0x0045, 0x0000, 0x001A, 0x0000,
    0x006E, 0x0000, 0x0026, 0x0038, 0x0000, 0x004F, 0x0000, 0x004C, 0x0000,
    0x0000, 0x0040, 0x0000, 0x0076, 0x0000, 0x0000, 0x006D, 0x0000, 0x0000,
    0x0071, 0x0000, 0x002F, 0x0000, 0x0075, 0x0000, 0x0000, 0x0079, 0x0000,
    0x007C, 0x0000, 0x0000, 0x0013, 0x000F, 0x0039, 0x0039, 0x0000, 0x005B,
    0x005B, 0x0000, 0x0000, 0x0067, 0x0000, 0x0077, 0x0000, 0x0001, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0006, 0x0000, 0x0000, 0x000D, 0x0000,
    0x002E, 0x0000, 0x006A, 0x0029, 0x0000, 0x0000, 0x0054, 0x0000, 0x0053,
    0x0000, 0x0055, 0x0000, 0x0000, 0x0010, 0x0000, 0x0074, 0x0000, 0x0000,
    0x008E, 0x0000, 0x0000, 0x0000, 0x0000, 0x004A, 0x0000, 0x0000, 0x0047,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0043, 0x0000, 0x0000, 0x003F, 0x0000,
    0x0078, 0x008B, 0x0000, 0x0000, 0x0000, 0x004E, 0x0000, 0x0000, 0x008A,
    0x004B, 0x0000, 0x003E, 0x003C, 0x0089, 0x0000, 0x0000, 0x0000, 0x001F,
    0x0000, 0x0000, 0x007E, 0x0000, 0x0000, 0x0049, 0x0000, 0x0000, 0x0000,
    0x0014, 0x0000, 0x0000, 0x000C, 0x0027, 0x0000, 0x0000, 0x0000, 0x0033,
    0x0000, 0x0024, 0x0012, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0032, 0x0061, 0x0000, 0x0063, 0x0000, 0x0000, 0x0082, 0x0000, 0x0000,
    0x0000, 0x0051, 0x0000, 0x0073, 0x0000, 0x0000, 0x0000, 0x0050, 0x0000,
    0x0000, 0x0058, 0x0000, 0x0000, 0x0000, 0x0084, 0x0066, 0x0000, 0x003A,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0022, 0x0064, 0x0064,
    0x0000, 0x0000, 0x0000, 0x0044, 0x0000, 0x0000, 0x0017, 0x001C, 0x006B,
    0x0000, 0x008C, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0060, 0x0062,
    0x0088, 0x0000, 0x0000, 0x0000, 0x0086, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0085, 0x0000, 0x0000, 0x0087, 0x0000, 0x0000, 0x0000, 0x0000,
    0x005F, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x005D,
    0x0091, 0x0000, 0x0000, 0x0000, 0x0000, 0x0090, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x005A, 0x0000, 0x0000, 0x0083, 0x0000, 0x0000,
    0x0000, 0x0080, 0x0000, 0x007F, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0092, 0x0000, 0x0000, 0x0000, 0x0000, 0x0003, 0x0000, 0x0072,
    0x0000, 0x0000, 0x006C, 0x0000, 0x0000, 0x0081, 0x0081, 0x0000, 0x0000,
    0x008F, 0x0000, 0x0000, 0x0000,
};

#endif

static u8 g_testCollLuckCutoff[] = {
    0x00,
    0x40,
    0x20,
    0x10,
};

static u8 g_testColluCoords[] = {
    0x80, 0x80, 0xA0, 0xA0, 0xC0, 0xC0, 0x00, 0x00,
};

static u8 g_testCollvCoords[] = {
    0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x00, 0x00,
};

static u16 g_testCollElementLookup[] = {
    ELEMENT_FIRE,  ELEMENT_THUNDER, ELEMENT_ICE,    ELEMENT_HOLY,  ELEMENT_DARK,
    ELEMENT_STONE, ELEMENT_CURSE,   ELEMENT_POISON, ELEMENT_WATER, ELEMENT_CUT,
};

static u8 g_testColliFrames[] = {
    0x02, 0x04, 0x03, 0x05, 0x06, 0x07, 0x08, 0x0A, 0x02, 0x01,
};

static u16 g_testCollPrizeTable[] = {
    0x0003, 0x0000, 0x0002, 0x0003, 0x0003, 0x0003, 0x0003, 0x0003,
    0x0003, 0x0004, 0x0004, 0x0004, 0x0004, 0x0005, 0x0005, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0001, 0x0001, 0x0002, 0x0006, 0x0007, 0x00C6,
};

static u16 g_testCollRandTable[] = {
    0x0C00, 0x0168, 0x0F00, 0x0169, 0x0FD0, 0x016A, 0x0FF0,
    0x016B, 0x0FF8, 0x016C, 0x0FFD, 0x016D, 0x0FFF, 0x016E,
};

static u16 g_eDamageDisplayClut[] = {
    PAL_DRA(0x1B2), PAL_DRA(0x1B3), PAL_DRA(0x1B6), PAL_DRA(0x1B7),
    PAL_DRA(0x1B4), PAL_DRA(0x1B5), PAL_DRA(0x1B0), PAL_DRA(0x1B1),
};

void HitDetection(void) {
#ifdef VERSION_PC
    u8 sp[SP_LEN];
#endif
    s32 temp_rand;
    Entity* otherEntity;
    Primitive* prim;
    Entity* entFrom5C;
    s32* scratchpad_2;
    Entity* iterEnt2;
    u16 miscVar3;
    u16 i;
    s32* scratchpad_1;
    u16* randCompare;
    u32 hitboxCheck1;
    EnemyDef* sp3C;
    s16 xCoord;
    s16 yCoord2;
    u16 miscVar1;
    u16 hitboxCheck2;
    s32 yCoord1;
    s32 hitboxWidth;
    s8 uselessVar;
    Entity* iterEnt1;
    u8 miscVar2;

    scratchpad_1 = (s32*)SP(0);
    scratchpad_2 = (s32*)SP(0xC0);
    for (iterEnt1 = &g_Entities[0]; iterEnt1 < &g_Entities[48]; scratchpad_1++,
        iterEnt1++) {
        *scratchpad_1 = iterEnt1->hitboxState;
        if ((*scratchpad_1 != 0) && !(*scratchpad_1 & 0x80)) {
            *scratchpad_2 = iterEnt1->posX.i.hi;
            if (iterEnt1->facingLeft) {
                *scratchpad_2 -= iterEnt1->hitboxOffX;
            } else {
                *scratchpad_2 += iterEnt1->hitboxOffX;
            }
            yCoord1 = iterEnt1->posY.i.hi + iterEnt1->hitboxOffY;
            if ((*scratchpad_2 < -32) || (*scratchpad_2 > 288) ||
                (yCoord1 < -32) || (yCoord1 > 256) || !iterEnt1->hitboxWidth ||
                !iterEnt1->hitboxHeight) {
                *scratchpad_1 = 0;
                scratchpad_2 += 4;
            } else {
                scratchpad_2++;
                *scratchpad_2++ = iterEnt1->hitboxWidth;
                *scratchpad_2++ = yCoord1;
                *scratchpad_2++ = iterEnt1->hitboxHeight;
            }
        } else {
            scratchpad_2 += 4;
        }
    }
    for (iterEnt1 = &g_Entities[64]; iterEnt1 < &g_Entities[192]; iterEnt1++) {
        miscVar1 = iterEnt1->hitboxState;
        if (!miscVar1 || !(iterEnt1->hitboxWidth) ||
            !(iterEnt1->hitboxHeight) || (iterEnt1->flags & FLAG_DEAD)) {
            continue;
        }
        for (i = 0; i < 11; i++) {
            if (iterEnt1->unk6D[i]) {
                iterEnt1->unk6D[i]--;
            }
        }
        xCoord = iterEnt1->posX.i.hi;
        if (iterEnt1->facingLeft) {
            xCoord -= iterEnt1->hitboxOffX;
        } else {
            xCoord += iterEnt1->hitboxOffX;
        }
        yCoord2 = iterEnt1->posY.i.hi + iterEnt1->hitboxOffY;
        if ((xCoord <= -32) || (xCoord >= 288) || (yCoord2 <= -32) ||
            (yCoord2 >= 256)) {
            continue;
        }
        miscVar2 = 0;
        miscVar3 = (u16)(miscVar1 & 0x3E);
        hitboxWidth = iterEnt1->hitboxWidth - 1;
        yCoord1 = iterEnt1->hitboxHeight - 1;
        if (miscVar3) {
            scratchpad_1 = (s32*)SP(4);
            scratchpad_2 = (s32*)SP(0xD0);
            for (iterEnt2 = &g_Entities[1]; iterEnt2 < &g_Entities[48];
                 iterEnt2++) {
                if ((*scratchpad_1 & miscVar3) &&
                    (!iterEnt1->unk6D[iterEnt2->enemyId])) {
                    if (*scratchpad_1 & 0x80) {
                        iterEnt1->hitParams = iterEnt2->hitEffect & 0x7F;
                        miscVar2 = 0xFF;
                        break;
                    } else {
                        hitboxCheck2 = (u16)*scratchpad_2++ - (u16)xCoord;
                        hitboxCheck1 = hitboxWidth + *scratchpad_2++;
                        hitboxCheck2 += hitboxCheck1;
                        hitboxCheck1 *= 2;
                        if (hitboxCheck1 >= hitboxCheck2) {
                            hitboxCheck2 = (u16)*scratchpad_2++ - (u16)yCoord2;
                            hitboxCheck1 = yCoord1 + *scratchpad_2++;
                            hitboxCheck2 += hitboxCheck1;
                            hitboxCheck1 *= 2;
                            if (hitboxCheck1 >= hitboxCheck2) {
                                // reusing the i variable here, maybe can be a
                                // different var
                                i = iterEnt2->hitEffect & 0x7F;
                                if (!(iterEnt2->flags & iterEnt1->flags &
                                      FLAG_UNK_100000)) {
                                    // Probably has to stay generic since
                                    // iterEnt2 could be any entity?
                                    iterEnt2->unkB8 = iterEnt1;
                                    // reminder: iterEnt1->hitboxState
                                    if (miscVar1 & 8) {
                                        iterEnt2->hitFlags = 3;
                                    } else {
                                        iterEnt2->hitFlags = 1;
                                    }
                                    if ((i == 3) &&
                                        (iterEnt1->flags & FLAG_UNK_8000)) {
                                        g_api.PlaySfx(SFX_METAL_CLANG_E);
                                        iterEnt2->hitFlags = 2;
                                    }
                                    if ((i == 4) &&
                                        (iterEnt1->flags & FLAG_UNK_4000)) {
                                        g_api.PlaySfx(SFX_METAL_CLANG_E);
                                        iterEnt2->hitFlags = 2;
                                    }
                                }
                                iterEnt1->hitParams = i;
                                miscVar2 = 0xFF;
                                break;
                            } else {
                                scratchpad_1++;
                                continue;
                            }
                        } else {
                            scratchpad_1++;
                            scratchpad_2 += 2;
                            continue;
                        }
                    }
                } else {
                    scratchpad_1++;
                    scratchpad_2 += 4;
                }
            }
        }

        if ((miscVar1 & 1) && (!miscVar2)) {
            // Note that in this block, iterEnt2 is never advanced, so it's
            // always the player.
            iterEnt2 = &PLAYER;
            scratchpad_1 = (s32*)SP(0);
            scratchpad_2 = (s32*)SP(0xC0);
            if (!iterEnt1->unk6D[iterEnt2->enemyId] && (*scratchpad_1 & 1)) {
                hitboxCheck2 = (u16)*scratchpad_2++ - (u16)xCoord;
                hitboxCheck1 = hitboxWidth + *scratchpad_2++;
                hitboxCheck2 += hitboxCheck1;
                hitboxCheck1 *= 2;
                if (hitboxCheck1 >= hitboxCheck2) {
                    hitboxCheck2 = (u16)*scratchpad_2++ - (u16)yCoord2;
                    hitboxCheck1 = yCoord1 + *scratchpad_2++;
                    hitboxCheck2 += hitboxCheck1;
                    hitboxCheck1 *= 2;
                    if (hitboxCheck1 >= hitboxCheck2) {
                        if ((iterEnt1->attack) &&
                            (iterEnt2->hitPoints < iterEnt1->attack)) {
                            iterEnt2->unkB8 = iterEnt1;
                            if (miscVar1 & 8) {
                                iterEnt2->hitFlags = 3;
                            } else {
                                iterEnt2->hitFlags = 1;
                            }
                            iterEnt2->hitParams = iterEnt1->attackElement;
                            iterEnt2->hitPoints = iterEnt1->attack;
                        }
                        iterEnt1->hitParams = iterEnt2->hitEffect & 0x7F;
                        miscVar2 = 0xFF;
                        iterEnt1->hitFlags = 0x80;
                    }
                }
            }
        }
        if (miscVar2) {
            if (iterEnt1->unk5C != NULL) {
                entFrom5C = iterEnt1->unk5C;
                entFrom5C->hitParams = (u16)iterEnt1->hitParams;
                entFrom5C->hitFlags = (u8)iterEnt1->hitFlags;
            } else {
                entFrom5C = iterEnt1;
            }
            if (!(entFrom5C->flags & FLAG_DEAD) && miscVar2) {
                hitboxCheck2 = iterEnt2->hitEffect & 0x7F;
                if ((hitboxCheck2 == 2) ||
                    ((hitboxCheck2 == 6) && (miscVar1 & 0x20))) {
                    otherEntity =
                        AllocEntity(&g_Entities[160], &g_Entities[192]);
                    if (otherEntity != NULL) {
                        // EntitySoulStealOrb
                        CreateEntityFromEntity(7, iterEnt1, otherEntity);
                    }
                }
                miscVar1 = g_testCollEnemyLookup[entFrom5C->enemyId];
                if (miscVar1) {
                    miscVar1--;
                    miscVar3 = 1 << (miscVar1 & 7);
                    g_CastleFlags[(miscVar1 >> 3) + COLLISION_FLAGS_START] |=
                        miscVar3;
                }
                if ((g_Status.relics[RELIC_FAERIE_SCROLL] & 2) &&
                    !(entFrom5C->flags & FLAG_NOT_AN_ENEMY)) {
                    if (g_unkGraphicsStruct.BottomCornerTextTimer != 0) {
                        g_api.FreePrimitives(
                            g_unkGraphicsStruct.BottomCornerTextPrims);
                        g_unkGraphicsStruct.BottomCornerTextTimer = 0;
                    }
                    BottomCornerText(
                        g_api.enemyDefs[entFrom5C->enemyId].name, 0);
                    entFrom5C->flags |= FLAG_NOT_AN_ENEMY;
                }
                miscVar2 = 0;
                if ((iterEnt1->hitboxState & 8) &&
                    (iterEnt2->hitboxState & 4)) {
                    goto block_164;
                }
                if (entFrom5C->hitPoints) {
                    if (iterEnt2->attack) {
                        if (!(iterEnt2->hitboxState & 0x80)) {
                            scratchpad_2 -= 4;
                            xCoord += *scratchpad_2++;
                            scratchpad_2++;
                            yCoord2 += *scratchpad_2;
                            xCoord /= 2;
                            yCoord2 /= 2;
                        }
                        for (prim = &g_PrimBuf[g_unkGraphicsStruct.D_800973F8];
                             prim != NULL; prim = prim->next) {
                            if (prim->drawMode == DRAW_HIDE) {
                                prim->clut = 0x199;
                                temp_rand = (Random() & 7) - 13;
                                prim->x0 = prim->x2 = xCoord + temp_rand - 3;
                                prim->x1 = prim->x3 = prim->x0 + 0x20;
                                temp_rand = (Random() & 7) - 10;
                                prim->y0 = prim->y1 = yCoord2 + temp_rand - 3;
                                prim->y2 = prim->y3 = prim->y0 + 0x20;
                                prim->p1 = 0;
                                if (iterEnt2->zPriority > iterEnt1->zPriority) {
                                    prim->priority = iterEnt2->zPriority + 1;
                                } else {
                                    prim->priority = iterEnt1->zPriority + 1;
                                }
                                prim->drawMode = DRAW_UNK02;
                                break;
                            }
                        }
                    }
                    if ((iterEnt2->attack) &&
                        (entFrom5C->hitPoints != 0x7FFF)) {
                        miscVar1 = g_api.DealDamage(iterEnt1, iterEnt2);
                        if (iterEnt2->hitboxState == 4) {
                            miscVar1 = 0;
                        }
                        if ((g_Status.relics[RELIC_SPIRIT_ORB] & 2) &&
                            !(entFrom5C->flags & FLAG_KEEP_ALIVE_OFFCAMERA) &&
                            miscVar1) {
                            otherEntity =
                                AllocEntity(&g_Entities[224], &g_Entities[256]);
                            if (otherEntity != NULL) {
                                DestroyEntity(otherEntity);
                                otherEntity->entityId = 4;
                                otherEntity->pfnUpdate = EntityDamageDisplay;
                                otherEntity->posX.i.hi = xCoord;
                                otherEntity->posY.i.hi = yCoord2;
                                otherEntity->params = miscVar1;
                            }
                        }
                    } else {
                        miscVar1 = 0;
                    }
                    if (miscVar1 != 0xC000) {
                        if (miscVar1 & 0x8000) {
                            miscVar2 = 9;
                        } else {
                            miscVar3 = (u16)iterEnt2->attackElement;
                            // includes all elements 0x40 and up
                            if (miscVar3 & 0xFFC0) {
                                for (i = 0; i < LEN(g_testCollElementLookup);
                                     i++) {
                                    if (miscVar3 & g_testCollElementLookup[i]) {
                                        miscVar2 = g_testColliFrames[i];
                                        break;
                                    }
                                }
                            }
                        }
                    } else {
                        entFrom5C->hitFlags |= 0x20;
                        miscVar1 = 0;
                    }
                    if (!miscVar1) {
                        goto unusual_spot;
                    }
                    if (miscVar1 & 0x8000) {
                        entFrom5C->hitPoints += (miscVar1 & 0x3FFF);
                        miscVar3 =
                            g_api.enemyDefs[entFrom5C->enemyId].hitPoints;
                        if (entFrom5C->hitPoints > miscVar3) {
                            entFrom5C->hitPoints = miscVar3;
                        }
                    } else {
                        miscVar1 &= 0x3FFF;
                        if (entFrom5C->flags & FLAG_UNK_10) {
                            // Different on PSP vs PSX
                            if (g_PlayableCharacter != PLAYER_ALUCARD) {
                                // normally this is Alucard shouting "Dark
                                // Metamorphosis" but obviously if not playing
                                // as Alucard, this won't match
                                g_api.PlaySfx(SFX_RICHTER_ATTACK_HIT);
                            } else if (iterEnt2->hitEffect & 0x80) {
                                g_api.PlaySfx(SFX_WEAPON_STAB_B);
                            } else {
                                g_api.PlaySfx(SFX_WEAPON_HIT_A);
                            }
                        }
                        if (entFrom5C->hitPoints != 0x7FFE) {
                            if (entFrom5C->hitPoints < (miscVar1 * 2)) {
                                entFrom5C->hitFlags |= 3;
                            } else if (entFrom5C->hitPoints < (miscVar1 * 4)) {
                                entFrom5C->hitFlags |= 2;
                            } else {
                                entFrom5C->hitFlags |= 1;
                            }
                            entFrom5C->hitPoints -= miscVar1;
                        }
                        if ((iterEnt2->attackElement & ELEMENT_CUT) &&
                            (entFrom5C->hitboxState & 0x10)) {
                            otherEntity =
                                AllocEntity(&g_Entities[160], &g_Entities[192]);
                            if (otherEntity != NULL) {
                                // EntityEnemyBlood
                                CreateEntityFromEntity(
                                    13, iterEnt1, otherEntity);
                                if (xCoord > iterEnt1->posX.i.hi) {
                                    otherEntity->params = 1;
                                }
                                otherEntity->posX.i.hi = xCoord;
                                otherEntity->posY.i.hi = yCoord2;
                                otherEntity->zPriority = 192;
                            }
                        }
                    }
                    if (entFrom5C->hitPoints > 0) {
                        otherEntity = entFrom5C;
                        miscVar3 = iterEnt2->enemyId;
                        do {
                            otherEntity->unk6D[miscVar3] =
                                iterEnt2->nFramesInvincibility;
                            if (entFrom5C < otherEntity) {
                                otherEntity->unk6D[miscVar3]++;
                            }
                            if (!(iterEnt1->flags & FLAG_UNK_400000)) {
                                otherEntity->stunFrames = iterEnt2->stunFrames;
                            }
                            if ((!otherEntity->hitEffect) &&
                                !(otherEntity->flags & 0xF)) {
                                otherEntity->hitEffect = otherEntity->palette;
                            }
                            otherEntity->nFramesInvincibility = miscVar2;
                            otherEntity->flags |= 0xF;
                            otherEntity = otherEntity->unk60;
                        } while ((otherEntity != NULL) &&
                                 (otherEntity != entFrom5C));
                        // I don't understand this; we write to a spot but we
                        // never reference it again.
                        uselessVar = ((u32)entFrom5C->flags >> 4) & 7 & 0xFF;
                        continue;
                    }
                }
            block_164:
                PreventEntityFromRespawning(entFrom5C);
                sp3C = &g_api.enemyDefs[entFrom5C->enemyId];
                if (!(entFrom5C->hitFlags & 0x80)) {
                    g_api.func_800FE044(sp3C->exp, sp3C->level);
                    if ((entFrom5C->flags & FLAG_UNK_1000) &&
                        (g_Status.killCount < 999999)) {
                        g_Status.killCount++;
                    }
                }
                miscVar3 = entFrom5C->flags & (FLAG_UNK_800 | FLAG_UNK_400);
                if (miscVar3) {
                    if ((rand() & 0xFF) <
                        g_api.func_800FF460(
                            g_testCollLuckCutoff[miscVar3 >> 0xA])) {
                        otherEntity =
                            AllocEntity(&g_Entities[160], &g_Entities[192]);
                        miscVar1 = 0;
                        if (otherEntity != NULL) {
                            if (hitboxCheck2 == 5) {
                                // This little block is weird, especially since
                                // the g_testCollRandTable is not any obvious
                                // number pattern.
                                randCompare = g_testCollRandTable;
                                miscVar3 = rand() & 0xFFF;
                                while (1) {
                                    if (*randCompare++ >= miscVar3) {
                                        miscVar3 = *randCompare;
                                        break;
                                    }
                                    randCompare++;
                                }

                            } else {
                                miscVar3 = g_api.func_800FF494(sp3C);
                                if (miscVar3 & 0x40) {
                                    miscVar3 = sp3C->rareItemId;
                                    // Paranthropus check: Drops turquoise if
                                    // game not beaten. Otherwise ring of Varda
                                    if ((miscVar3 == 0x173) &&
                                        (!g_IsTimeAttackUnlocked)) {
                                        miscVar3 = 0x16A;
                                    } else {
                                        miscVar1 = g_testCollEnemyLookup
                                            [entFrom5C->enemyId];
                                    }
                                } else if (miscVar3 & 0x20) {
                                    miscVar3 = sp3C->uncommonItemId;
                                } else {
                                    // select a prize from the table. This
                                    // covers heart, money, etc drops.
                                    miscVar3 = g_testCollPrizeTable[miscVar3];
                                }
                            }
                            if (miscVar3 >= 0x80) {
                                miscVar3 -= 0x80;
                                // Create an EntityEquipItemDrop
                                CreateEntityFromEntity(
                                    10, iterEnt1, otherEntity);
                            } else {
                                // Create an EntityPrizeDrop
                                CreateEntityFromEntity(
                                    3, iterEnt1, otherEntity);
                            }
                            otherEntity->ext.drop.unk94 = miscVar1;
                            otherEntity->params = miscVar3;
                            // item pops up in the air a bit when spawned
                            otherEntity->velocityY = FIX(-3.5);
                        }
                    }
                }
                otherEntity = entFrom5C;
                do {
                    otherEntity->flags |= (FLAG_UNK_100000 + FLAG_UNK_8000 +
                                           FLAG_UNK_4000 + FLAG_DEAD);
                    otherEntity->flags &= ~FLAG_UNK_20000000;
                    if (!otherEntity->hitEffect) {
                        otherEntity->hitEffect = otherEntity->palette;
                    }
                    otherEntity->nFramesInvincibility = miscVar2;
                    otherEntity->flags |= 0xF;
                    otherEntity = otherEntity->unk60;
                } while (otherEntity != NULL && otherEntity != entFrom5C);
                continue;
            // this spot is unusual because of where it appears in the code. I
            // would have expected this to be included in the spot with the
            // goto, since there is no way to reach this without using that one
            // single goto.
            unusual_spot:
                if (!(entFrom5C->hitFlags & 0xF)) {
                    entFrom5C->hitFlags |= 0x10;
                }
                if ((entFrom5C->flags & FLAG_UNK_10) && (iterEnt2->attack)) {
                    if (iterEnt2->hitEffect & 0x80) {
                        g_api.PlaySfx(SFX_METAL_CLANG_E);
                    } else {
                        g_api.PlaySfx(SFX_METAL_CLANG_E);
                    }
                }
                otherEntity = entFrom5C;
                miscVar3 = iterEnt2->enemyId;
                do {
                    if (iterEnt1->hitPoints == 0x7FFF) {
                        if (otherEntity->hitPoints == 0x7FFF) {
                            otherEntity->unk6D[miscVar3] =
                                iterEnt2->nFramesInvincibility;
                            if (entFrom5C < otherEntity) {
                                otherEntity->unk6D[miscVar3]++;
                            }
                        }
                    } else {
                        otherEntity->unk6D[miscVar3] =
                            iterEnt2->nFramesInvincibility;
                        if (entFrom5C < otherEntity) {
                            otherEntity->unk6D[miscVar3]++;
                        }
                    }
                    otherEntity = otherEntity->unk60;
                } while ((otherEntity != NULL) && (otherEntity != entFrom5C));
            }
        }
    }
    for (prim = &g_PrimBuf[g_unkGraphicsStruct.D_800973F8]; prim != NULL;
         prim = prim->next) {
        if ((prim->drawMode) != DRAW_HIDE) {
            miscVar2 = prim->p1;
            prim->u0 = prim->u2 = g_testColluCoords[miscVar2];
            prim->u1 = prim->u3 = prim->u0 + 0x20;
            prim->v0 = prim->v1 = g_testCollvCoords[miscVar2];
            prim->v2 = prim->v3 = prim->v0 + 0x20;
            miscVar2++;
            if (miscVar2 >= 7) {
                prim->drawMode = DRAW_HIDE;
            } else {
                prim->p1 = miscVar2;
            }
        }
    }
}

#include "entity_damage_display.h"
