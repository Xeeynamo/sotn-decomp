#include "ric.h"

void DebugShowWaitInfo(const char* msg) {
    g_CurrentBuffer = g_CurrentBuffer->next;
    FntPrint(msg);
    if (g_DebugWaitInfoTimer++ & 4) {
        FntPrint("\no\n");
    }
    DrawSync(0);
    VSync(0);
    PutDrawEnv(&g_CurrentBuffer->draw);
    PutDispEnv(&g_CurrentBuffer->disp);
    FntFlush(-1);
}

void DebugInputWait(const char* msg) {
    while (PadRead(0))
        DebugShowWaitInfo(msg);
    while (PadRead(0) == 0)
        DebugShowWaitInfo(msg);
}

INCLUDE_ASM("asm/us/ric/nonmatchings/22380", func_8015E484);

void func_8015E7B4(Unkstruct_8010BF64* arg0) { // !FAKE:
    s32 temp = D_80154604[0].unk0;

    arg0->unk14 = temp;
    arg0->unk1C = temp = D_80154604[0].unk2;
    arg0->unk18 = D_801545EA[8] - 1;
    arg0->unk20 = D_801545EA[0] + 1;
}

void func_8015E800(void) {
    Collider sp10;
    s32 temp_a0;
    s32 temp_a1;
    s32 temp_s0;
    s32 temp_s7;
    s32 i;
    s32 var_s5;
    s32 var_v1;
    u16 var_a1;
    s16 argX;
    s16 argY;
    s32 sp10effects;
    s16 temp_s16;

    u16* yPosPtr = &PLAYER.posY.i.hi;
    u16* xPosPtr = &PLAYER.posX.i.hi;
    s32* vram_ptr = &g_Player.pl_vram_flag;

    var_s5 = 0;
    i = 0;
    if (D_80097418 != 0) {
        *vram_ptr = 1;
        return;
    }
    if ((PLAYER.velocityY == 0) && (g_Player.unk04 & 1)) {
        var_s5 = 4;
    } else {
        i = 1;
    }
    for (; i < 4; i++, var_s5 = 0) {
        temp_a0 = g_Player.colliders[i].effects;
        if (temp_a0 & EFFECT_SOLID_FROM_BELOW) {
            continue;
        }
        if (((temp_a0 & EFFECT_UNK_0002) || (PLAYER.velocityY >= 0) ||
             ((PLAYER.step == 26) && (temp_a0 & EFFECT_UNK_8000)))) {
            temp_s0 = g_Player.colliders[i].effects &
                      (EFFECT_UNK_8000 | EFFECT_UNK_0800 | EFFECT_SOLID);
            if ((temp_s0 == EFFECT_SOLID) ||
                (g_Player.colliders[i].effects & EFFECT_UNK_0800)) {
                argX = *xPosPtr + D_801545F4[i].unk0;
                argY = *yPosPtr + D_801545F4[i].unk2 +
                       (g_Player.colliders[i].unk18 - 1);
                g_api.CheckCollision(argX, argY, &sp10, 0);
                sp10effects = sp10.effects;
                if (!(sp10effects & EFFECT_SOLID)) {
                    if ((g_Player.colliders[i].effects != 1) ||
                        (PLAYER.velocityY >= 0) || (PLAYER.step == 26)) {
                        if (temp_s0 & EFFECT_UNK_0800) {
                            *yPosPtr += var_s5 + g_Player.colliders[i].unk8;
                        } else {
                            *yPosPtr += var_s5 + g_Player.colliders[i].unk18;
                        }
                        *vram_ptr |= 1;
                        return;
                    }
                    continue;
                } else {
                    temp_a1 = sp10effects & (EFFECT_UNK_8000 | EFFECT_UNK_0002 |
                                             EFFECT_SOLID);
                    if ((temp_a1) == (EFFECT_UNK_8000 | EFFECT_SOLID)) {
                        if (i < 2) {
                            *vram_ptr |= ((sp10effects &
                                           (EFFECT_UNK_4000 | EFFECT_UNK_2000 |
                                            EFFECT_UNK_1000)) +
                                          temp_a1);
                            *yPosPtr += g_Player.colliders[i].unk8 +
                                        sp10.unk18 + (var_s5 - 1);
                            return;
                        }
                        if ((i == 2) &&
                            ((sp10effects & (EFFECT_UNK_8000 | EFFECT_UNK_4000 |
                                             EFFECT_SOLID)) ==
                             (EFFECT_UNK_8000 | EFFECT_SOLID))) {
                            g_Player.colliders[2].effects = sp10effects;
                            g_Player.colliders[2].unk10 =
                                g_Player.colliders[2].unk8;
                        }
                        if ((i == 3) &&
                            ((sp10effects & (EFFECT_UNK_8000 | EFFECT_UNK_4000 |
                                             EFFECT_SOLID)) ==
                             (EFFECT_UNK_8000 | EFFECT_UNK_4000 |
                              EFFECT_SOLID))) {
                            g_Player.colliders[3].effects = sp10effects;
                            g_Player.colliders[3].unk10 =
                                g_Player.colliders[3].unk8;
                        }
                    }
                }
            }
            if ((temp_s0 != (EFFECT_UNK_8000 | EFFECT_SOLID)) || (i >= 2)) {
                continue;
            }
            *vram_ptr |= g_Player.colliders[i].effects &
                         (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_UNK_2000 |
                          EFFECT_UNK_1000 | EFFECT_SOLID);
            *yPosPtr += var_s5 + g_Player.colliders[i].unk18;
            return;
        }
    }
    if (g_Player.colliders[1].effects & 4) {
        *vram_ptr |= 0x11;
        if ((g_Timer & 3) == 0) {
            (*yPosPtr)++;
        }
        return;
    }
    if (g_Player.colliders[1].effects & 8) {
        *vram_ptr |= 0x80;
    }
    if (PLAYER.velocityY < 0) {
        return;
    }
    argX = *xPosPtr + D_801545F4[0].unk0;
    argY = *yPosPtr + D_801545F4[0].unk2 + 10;
    g_api.CheckCollision(argX, argY, &sp10, 0);
    if ((sp10.effects & (EFFECT_UNK_8000 | EFFECT_SOLID)) != 0) {
        return;
    }

    for (i = 2; i < 4; i++) {
        if ((g_Player.colliders[3].effects & EFFECT_UNK_8000) &&
            (g_Player.colliders[2].effects & EFFECT_UNK_8000)) {
            return;
        }
        temp_s0 = g_Player.colliders[i].effects;
        temp_s7 = ((g_Player.colliders[i].effects &
                    (EFFECT_UNK_4000 | EFFECT_UNK_2000 | EFFECT_UNK_1000)) |
                   (EFFECT_UNK_8000 | EFFECT_SOLID));
        if (!(temp_s0 & EFFECT_UNK_8000)) {
            continue;
        }
        if (i == 2) {
            temp_a0 = EFFECT_UNK_4000;
            var_a1 = g_Player.colliders[2].unk4;
            temp_s16 = g_Player.colliders[2].unk4;
            var_v1 = temp_s16 + 8;
        } else {
            temp_a0 = 0;
            var_a1 = g_Player.colliders[3].unkC;
            temp_s16 = g_Player.colliders[3].unkC;
            var_v1 = 8 - temp_s16;
        }
        if ((temp_s0 & EFFECT_UNK_4000) == temp_a0) {
            argX = var_a1 + (*xPosPtr + D_801545F4[i].unk0);
            argY = *yPosPtr + D_801545F4[i].unk2;
            g_api.CheckCollision(argX, argY, &sp10, 0);
            if (sp10.effects & 1) {
                *yPosPtr += sp10.unk18;
                *vram_ptr |= temp_s7;
                return;
            }
            continue;
        }
        if (var_v1 <= 0) {
            continue;
        }
        if (!(temp_s0 & 1)) {
            continue;
        }
        argX = var_a1 + (*xPosPtr + D_801545F4[i].unk0);
        argY = *yPosPtr + D_801545F4[i].unk2 + g_Player.colliders[i].unk10;
        g_api.CheckCollision(argX, argY, &sp10, 0);
        if (sp10.effects & 1) {
            *yPosPtr += (sp10.unk18 + g_Player.colliders[i].unk10);
            *vram_ptr |= temp_s7;
            return;
        }
    }
}

void func_8015EE28(void) {
    Collider collider;
    s32 temp_fp;
    u32 temp_s0;
    s32 temp_v1;
    s32 var_a0;
    s32 i;
    u16 var_a1;
    s16 temp_s16;

    s16 newY;

    s16 argX;
    s16 argY;

    u32 collidereffects;

    u16* yPosPtr = &PLAYER.posY.i.hi;
    u16* xPosPtr = &PLAYER.posX.i.hi;
    s32* vram_ptr = &g_Player.pl_vram_flag;
    // weird thing where i has to get initialized first
    i = 1;

    if (D_80097418 != 0) {
        return;
    }
    for (i = 1; i < 4; i++) {
        var_a0 = g_Player.colliders2[i].effects;
        temp_s0 = var_a0 & (EFFECT_UNK_8000 | EFFECT_UNK_0800 | EFFECT_SOLID);
        if ((var_a0 & EFFECT_SOLID_FROM_ABOVE)) {
            continue;
        }
        if ((temp_s0 == EFFECT_SOLID) || (var_a0 & EFFECT_UNK_8000)) {
            if (((PLAYER.step == 26) || (PLAYER.step == 23)) &&
                !(var_a0 & EFFECT_SOLID)) {
                continue;
            }
            argX = *xPosPtr + D_801545E4[i].unk0;
            argY = *yPosPtr + D_801545E4[i].unk2 +
                   g_Player.colliders2[i].unk10 + 1;
            g_api.CheckCollision(argX, argY, &collider, 0);
            collidereffects = collider.effects;
            if (!(collidereffects & 1)) {
                if ((g_Player.colliders2[i].effects != 1) ||
                    (PLAYER.velocityY <= 0)) {
                    *vram_ptr |= 2;
                    if (!(*vram_ptr & 1) &&
                        ((g_Player.unk04 &
                          (EFFECT_SOLID_FROM_ABOVE | EFFECT_SOLID)) !=
                         (EFFECT_SOLID_FROM_ABOVE | EFFECT_SOLID))) {
                        if (g_Player.colliders2[i].effects & EFFECT_UNK_8000) {
                            *yPosPtr += g_Player.colliders2[i].unk10;
                        } else {
                            *yPosPtr += g_Player.colliders2[i].unk20;
                        }
                    }
                    return;
                }
                continue;
            }
            if ((collider.effects &
                 (EFFECT_UNK_0800 | EFFECT_UNK_0002 | EFFECT_SOLID)) ==
                (EFFECT_UNK_0800 | EFFECT_SOLID)) {
                if (i < 2) {
                    *vram_ptr |= (EFFECT_UNK_0800 | EFFECT_UNK_0002 |
                                  ((collidereffects >> 4) &
                                   (EFFECT_UNK_0400 | EFFECT_UNK_0200 |
                                    EFFECT_UNK_0100)));
                    if (!(*vram_ptr & 1)) {
                        newY = *yPosPtr + 1 +
                               (g_Player.colliders2[i].unk10 + collider.unk20);
                        *yPosPtr = newY;
                    }
                    return;
                }
                if ((i == 2) &&
                    ((collidereffects &
                      (EFFECT_UNK_4000 | EFFECT_UNK_0800 | EFFECT_SOLID)) ==
                     (EFFECT_UNK_0800 | EFFECT_SOLID))) {
                    g_Player.colliders[2].effects = collidereffects;
                    g_Player.colliders[2].unk8 = g_Player.colliders[2].unk10;
                }
                if ((i == 3) &&
                    ((collidereffects &
                      (EFFECT_UNK_4000 | EFFECT_UNK_0800 | EFFECT_SOLID)) ==
                     (EFFECT_UNK_4000 | EFFECT_UNK_0800 | EFFECT_SOLID))) {
                    g_Player.colliders[3].effects = collidereffects;
                    g_Player.colliders[3].unk8 = g_Player.colliders[3].unk10;
                }
            }
            if ((collidereffects & EFFECT_UNK_0800) == 0) {
                *vram_ptr |=
                    (EFFECT_UNK_0800 | EFFECT_UNK_0002 |
                     ((collidereffects >> 4) &
                      (EFFECT_UNK_0400 | EFFECT_UNK_0200 | EFFECT_UNK_0100)));
                if (!(*vram_ptr & 1)) {
                    newY = *yPosPtr + 1 +
                           (g_Player.colliders2[i].unk10 + collider.unk20);
                    *yPosPtr = newY;
                }
                return;
            }
        }
        if ((temp_s0 == (EFFECT_UNK_0800 | EFFECT_SOLID)) && (i < 2)) {
            *vram_ptr |=
                (EFFECT_UNK_0800 | EFFECT_UNK_0002 |
                 ((g_Player.colliders2[i].effects >> 4) &
                  (EFFECT_UNK_0400 | EFFECT_UNK_0200 | EFFECT_UNK_0100)));
            if (!(*vram_ptr & 1)) {
                *yPosPtr += g_Player.colliders2[i].unk20;
            }
            return;
        }
    }

    if (PLAYER.velocityY > 0) {
        return;
    }
    argX = *xPosPtr + D_801545E4[0].unk0;
    argY = (*yPosPtr + D_801545E4[0].unk2) - 10;
    g_api.CheckCollision(argX, argY, &collider, 0);
    if ((collider.effects & 1) != 0) {
        return;
    }
    for (i = 2; i < 4; i++) {
        if ((g_Player.colliders[7].effects & EFFECT_UNK_0800) &&
            (g_Player.colliders[6].effects & EFFECT_UNK_0800)) {
            return;
        }
        temp_s0 = g_Player.colliders2[i].effects;
        temp_fp = ((temp_s0 >> 4) &
                   (EFFECT_UNK_0400 | EFFECT_UNK_0200 | EFFECT_UNK_0100)) +
                  (EFFECT_UNK_0800 | EFFECT_UNK_0002);
        if (temp_s0 & EFFECT_UNK_0800) {
            if (i == 2) {
                var_a0 = EFFECT_UNK_4000;
                var_a1 = g_Player.colliders[6].unk4;
                temp_s16 = g_Player.colliders[6].unk4;
                temp_v1 = temp_s16 + 8;
            } else {
                var_a0 = 0;
                var_a1 = g_Player.colliders[7].unkC;
                temp_s16 = g_Player.colliders[7].unkC;
                temp_v1 = 8 - temp_s16;
            }
            if ((temp_s0 & EFFECT_UNK_4000) == var_a0) {
                argX = var_a1 + (*xPosPtr + D_801545E4[i].unk0);
                argY = *yPosPtr + D_801545E4[i].unk2;
                g_api.CheckCollision(argX, argY, &collider, 0);
                if (collider.effects & 1) {
                    *vram_ptr |= temp_fp;
                    if (!(*vram_ptr & 1)) {
                        *yPosPtr += collider.unk20;
                    }
                    return;
                }
            } else if ((temp_v1 > 0) && (temp_s0 & 1)) {
                argX = var_a1 + (*xPosPtr + D_801545E4[i].unk0);
                argY =
                    *yPosPtr + D_801545E4[i].unk2 + g_Player.colliders2[i].unk8;
                g_api.CheckCollision(argX, argY, &collider, 0);
                if ((collider.effects & 1)) {
                    if (!(*vram_ptr & 1)) {
                        *yPosPtr +=
                            collider.unk20 + g_Player.colliders2[i].unk8;
                    }
                    *vram_ptr |= temp_fp;
                    return;
                }
            }
        }
    }
}

void func_8015F414(void) {
    Collider collider;
    s32 temp_s0;
    s32 i;

    s16 argX;
    s16 argY;

    u16* yPosPtr = &PLAYER.posY.i.hi;
    u16* xPosPtr = &PLAYER.posX.i.hi;
    s32* vram_ptr = &g_Player.pl_vram_flag;

    if (D_80097418 != 0) {
        return;
    }
    temp_s0 =
        g_Player.unk04 & (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_UNK_0800 |
                          EFFECT_UNK_0400 | EFFECT_UNK_0002 | EFFECT_SOLID);
    if ((temp_s0 == (EFFECT_UNK_8000 | EFFECT_UNK_0002 | EFFECT_SOLID)) ||
        (temp_s0 == (EFFECT_UNK_0800 | EFFECT_UNK_0002 | EFFECT_SOLID)) ||
        (temp_s0 == (EFFECT_UNK_8000 | EFFECT_UNK_0800 | EFFECT_UNK_0002 |
                     EFFECT_SOLID))) {
        *vram_ptr |= 4;
        return;
    }

    for (i = 0; i < 7; i++) {
        temp_s0 = g_Player.colliders3[i].effects &
                  (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_UNK_0800 |
                   EFFECT_UNK_0002 | EFFECT_SOLID);
        if ((temp_s0 == (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_SOLID)) ||
            (temp_s0 == (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_UNK_0002 |
                         EFFECT_SOLID)) ||
            (temp_s0 == (EFFECT_UNK_4000 | EFFECT_UNK_0800 | EFFECT_SOLID)) ||
            (temp_s0 == (EFFECT_UNK_4000 | EFFECT_UNK_0800 | EFFECT_UNK_0002 |
                         EFFECT_SOLID)) ||
            (temp_s0 == (EFFECT_UNK_8000 | EFFECT_UNK_0002 | EFFECT_SOLID)) ||
            (temp_s0 == (EFFECT_UNK_0002 | EFFECT_SOLID))) {
            argX =
                *xPosPtr + D_80154604[i].unk0 + g_Player.colliders3[i].unk4 - 1;
            argY = *yPosPtr + D_80154604[i].unk2;
            g_api.CheckCollision(argX, argY, &collider, 0);
            if ((collider.effects & 1) == 0) {
                *vram_ptr |= 4;
                *xPosPtr += g_Player.colliders3[i].unk4;
                return;
            }
        }

        if (!(*vram_ptr & 1)) {
            if ((temp_s0 & (EFFECT_UNK_8000 | EFFECT_UNK_4000 |
                            EFFECT_UNK_0800)) == EFFECT_UNK_8000 &&
                (i != 0) &&
                ((g_Player.colliders3[0].effects & EFFECT_UNK_0800) ||
                 !(g_Player.colliders3[0].effects &
                   (EFFECT_UNK_8000 | EFFECT_UNK_0800 | EFFECT_UNK_0002)))) {
                *vram_ptr |= 4;
                *xPosPtr += g_Player.colliders3[i].unk4;
                return;
            }
            if (((temp_s0 & (EFFECT_UNK_8000 | EFFECT_UNK_4000 |
                             EFFECT_UNK_0800)) == EFFECT_UNK_0800) &&
                (i != 6) &&
                ((g_Player.colliders3[6].effects & EFFECT_UNK_8000) ||
                 !(g_Player.colliders3[6].effects &
                   (EFFECT_UNK_8000 | EFFECT_UNK_0800 | EFFECT_UNK_0002)))) {
                *vram_ptr |= 4;
                *xPosPtr += g_Player.colliders3[i].unk4;
                return;
            }
        }
    }
}

void func_8015F680(void) {
    Collider collider;
    s32 temp_s0;
    s32 i;
    s16 argX;
    s16 argY;

    u16* yPosPtr = &PLAYER.posY.i.hi;
    u16* xPosPtr = &PLAYER.posX.i.hi;
    s32* vram_ptr = &g_Player.pl_vram_flag;

    if (D_80097418 != 0) {
        return;
    }
    temp_s0 =
        g_Player.unk04 & (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_UNK_0800 |
                          EFFECT_UNK_0400 | EFFECT_UNK_0002 | EFFECT_SOLID);
    if ((temp_s0 == (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_UNK_0002 |
                     EFFECT_SOLID)) ||
        (temp_s0 == (EFFECT_UNK_0800 | EFFECT_UNK_0400 | EFFECT_UNK_0002 |
                     EFFECT_SOLID)) ||
        (temp_s0 == (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_UNK_0800 |
                     EFFECT_UNK_0400 | EFFECT_UNK_0002 | EFFECT_SOLID))) {
        *vram_ptr |= 8;
        return;
    }
    for (i = 7; i < 14; i++) {
        temp_s0 = g_Player.colliders3[i].effects &
                  (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_UNK_0800 |
                   EFFECT_UNK_0002 | EFFECT_SOLID);
        if ((temp_s0 == (EFFECT_UNK_8000 | EFFECT_SOLID)) ||
            (temp_s0 == (EFFECT_UNK_8000 | EFFECT_UNK_0002 | EFFECT_SOLID)) ||
            (temp_s0 == (EFFECT_UNK_0800 | EFFECT_SOLID)) ||
            (temp_s0 == (EFFECT_UNK_0800 | EFFECT_UNK_0002 | EFFECT_SOLID)) ||
            (temp_s0 == (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_UNK_0002 |
                         EFFECT_SOLID)) ||
            (temp_s0 == (EFFECT_UNK_4000 | EFFECT_UNK_0800 | EFFECT_UNK_0002 |
                         EFFECT_SOLID)) ||
            (temp_s0 == (EFFECT_UNK_0002 | EFFECT_SOLID))) {
            argX =
                *xPosPtr + D_80154604[i].unk0 + g_Player.colliders3[i].unkC + 1;
            argY = *yPosPtr + D_80154604[i].unk2;
            g_api.CheckCollision(argX, argY, &collider, 0);
            if ((collider.effects & 1) == 0) {
                *vram_ptr |= 8;
                *xPosPtr += g_Player.colliders3[i].unkC;
                return;
            }
        }
        if (!(*vram_ptr & 1)) {
            if (((temp_s0 &
                  (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_UNK_0800)) ==
                 (EFFECT_UNK_8000 | EFFECT_UNK_4000)) &&
                (i != 7) &&
                ((g_Player.colliders3[7].effects & EFFECT_UNK_0800) ||
                 !(g_Player.colliders3[7].effects &
                   (EFFECT_UNK_8000 | EFFECT_UNK_0800 | EFFECT_UNK_0002)))) {
                *vram_ptr |= 8;
                *xPosPtr += g_Player.colliders3[i].unkC;
                return;
            }
            if (((temp_s0 &
                  (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_UNK_0800)) ==
                 (EFFECT_UNK_4000 | EFFECT_UNK_0800)) &&
                (i != 13) &&
                ((g_Player.colliders3[13].effects & EFFECT_UNK_8000) ||
                 !(g_Player.colliders3[13].effects &
                   (EFFECT_UNK_8000 | EFFECT_UNK_0800 | EFFECT_UNK_0002)))) {
                *vram_ptr |= 8;
                *xPosPtr += g_Player.colliders3[i].unkC;
                return;
            }
        }
    }
}

Entity* GetFreeEntity(s16 start, s16 end) {
    Entity* entity = &g_Entities[start];
    s16 i;

    for (i = start; i < end; i++, entity++) {
        if (entity->entityId == E_NONE) {
            return entity;
        }
    }
    return NULL;
}

Entity* GetFreeEntityReverse(s16 start, s16 end) {
    Entity* entity = &g_Entities[end - 1];
    s16 i;
    for (i = end - 1; i >= start; i--, entity--) {
        if (entity->entityId == E_NONE) {
            return entity;
        }
    }
    return NULL;
}

INCLUDE_ASM("asm/us/ric/nonmatchings/22380", func_8015F9F0);

void func_8015FA5C(s32 arg0) {
    D_80174FAC = D_80154674[arg0][0];
    D_80174FB0 = D_80154674[arg0][1];
    D_80174FB4 = D_80154674[arg0][2];
    D_80174FB8 = D_80154674[arg0][3];
}

void func_8015FAB8(Entity* entity) {
    u16 attack;
    SubweaponDef* subwpn = &D_80154688[entity->ext.generic.unkB0];

    if ((g_Player.D_80072F1A) != NULL) {
        attack = subwpn->attack * 2;
    } else {
        attack = subwpn->attack;
    }

    entity->attack = attack;
    entity->attackElement = subwpn->attackElement;
    entity->hitboxState = subwpn->hitboxState;
    entity->nFramesInvincibility = subwpn->nFramesInvincibility;
    entity->stunFrames = subwpn->stunFrames;
    entity->hitEffect = subwpn->hitEffect;
    entity->entityRoomIndex = subwpn->entityRoomIndex;
    entity->attack = g_api.func_800FD664(entity->attack);
    func_8015F9F0(entity);
}

// We're playing as Richter and we used a subweapon (normal or crash)
s32 func_8015FB84(SubweaponDef* subwpn, s32 isItemCrash, s32 useHearts) {
    s32 pad[2]; // Needed so stack pointer moves properly
    u8 crashId;
    // Not an item crash. Just read the item in.
    if (isItemCrash == 0) {
        *subwpn = D_80154688[g_Status.subWeapon];
        if (g_Status.hearts >= subwpn->heartCost) {
            if (useHearts) {
                g_Status.hearts -= subwpn->heartCost;
            }
            return g_Status.subWeapon;
        }
    } else {
        // If it's a crash, load the subweapon by referencing our
        // subweapon's crash ID and loading that.
        crashId = D_80154688[g_Status.subWeapon].crashId;
        *subwpn = D_80154688[crashId];
        if (g_Status.hearts >= subwpn->heartCost) {
            if (useHearts) {
                g_Status.hearts -= subwpn->heartCost;
            }
            return g_Status.subWeapon;
        }
    }
    return -1;
}

INCLUDE_ASM("asm/us/ric/nonmatchings/22380", func_8015FDB0);

INCLUDE_ASM("asm/us/ric/nonmatchings/22380", func_8015FEA8);

// same as DRA/func_8011F074
void func_801601DC(Entity* entity) {
    s16 posX;
    s16 posY;

    switch (entity->step) {
    case 0:
        entity->flags = FLAG_UNK_20000 | FLAG_UNK_100000 | FLAG_UNK_08000000;
        entity->unk5A = 0x79;
        entity->animSet = ANIMSET_DRA(14);
        entity->zPriority = PLAYER.zPriority + 2;
        entity->palette = 0x819F;

        if (D_80174FFC & 1) {
            entity->blendMode = 0x70;
        } else {
            entity->blendMode = 0x10;
        }
        entity->rotY = 0x40;
        entity->rotX = 0x40;
        entity->unk4C = &D_80154924;
        D_80174FFC++;
        entity->unk6C = 0xFF;
        entity->drawFlags =
            FLAG_DRAW_ROTX | FLAG_DRAW_ROTY | FLAG_DRAW_UNK10 | FLAG_DRAW_UNK20;
        posX = 10;
        posY = 15;
        entity->posY.i.hi = entity->posY.i.hi - posY + (rand() % 35);
        entity->posX.i.hi = entity->posX.i.hi - posX + (rand() % 20);
        entity->velocityY = -0x6000 - (rand() & 0x3FFF);
        entity->step++;
        break;

    case 1:
        if (entity->unk6C >= 17) {
            entity->unk6C += 248;
        }
        entity->posY.val += entity->velocityY;
        entity->rotX += 8;
        entity->rotY += 8;
        if (entity->animFrameDuration < 0) {
            DestroyEntity(entity);
        }
        break;
    }
}

void func_801603B4(void) {}

void func_801603BC(void) {}

// Corresponding DRA function is func_8011A4D0
void func_801603C4(void) {
    SubweaponDef subwpn;
    Entity* entity;
    s32 i;
    s32 i2;
    s32 i3;
    s32 temp_s2;
    s32 enemy;
    s32 enemy2;

    temp_s2 = *D_80097420;
    entity = g_CurrentEntity = &g_Entities[4];
    for (i = 4; i < 0x40; i++, g_CurrentEntity++, entity++) {
        if (entity->entityId != 0) {
            if (entity->step == 0) {
                entity->pfnUpdate = D_8015495C[entity->entityId];
            }
            if ((temp_s2 == 0) || (entity->flags & 0x10000)) {
                entity->pfnUpdate(entity);
                entity = g_CurrentEntity;
                if (entity->entityId != 0) {
                    if (!(entity->flags & FLAG_UNK_04000000) &&
                        ((u16)(entity->posX.i.hi + 32) > 320 ||
                         (u16)(entity->posY.i.hi + 16) > 272)) {
                        DestroyEntity(entity);
                    } else if (entity->flags & 0x100000) {
                        g_api.UpdateAnim(0, (s32*)D_80154674);
                    }
                }
            }
        }
    }

    if (D_80174FAC != 0) {
        if (--D_80174FAC & 1) {
            g_api.g_pfn_800EA5AC(1, D_80174FB0, D_80174FB4, D_80174FB8);
        }
    }

    D_80174F80[1] = D_80174F80[2] = 0;
    enemy = g_Entities[16].enemyId;
    if (enemy == 1) {
        D_80174F80[1] = 1;
    } else if (enemy == 2) {
        D_80174F80[2] = 1;
    }

    for (i2 = 3; i2 < 11; i2++) {
        D_80174F80[i2] = 0;
    }

    entity = &g_Entities[17];
    for (i3 = 17; i3 < 48; entity++, i3++) {
        enemy2 = entity->enemyId;
        if (enemy2 >= 3) {
            D_80174F80[entity->enemyId]++;
        }
    }
    // This IF will fire if we have enough hearts to use a subweapon crash.
    // No idea what it's doing here.
    if (func_8015FB84(&subwpn, 1, 0) >= 0) {
        g_Player.unk0C |= 0x200000;
    }
    if (g_Player.unk0C & 0xC0000) {
        FntPrint("dead player\n");
        entity = &g_Entities[17]; // Weird code here. Set entity to #17 but...
        entity -= 13; // then change to #4 before the for-loop starting with 4?
        for (i = 4; i < 64; i++, entity++) {
            entity->hitboxState = 0;
        }
    }
}

// Similar to the version in DRA but with some logic removed
Entity* CreateEntFactoryFromEntity(
    Entity* source, u32 factoryParams, s32 arg2) {
    /**
     * arg2 is unused, but needed to match other functions that call
     * this function, probably part of the code for a debug build
     */
    Entity* entity = GetFreeEntity(8, 0x10);

    if (entity != NULL) {
        DestroyEntity(entity);
        entity->entityId = E_ENTITYFACTORY;
        entity->ext.generic.unk8C.entityPtr = source;
        entity->posX.val = source->posX.val;
        entity->posY.val = source->posY.val;
        entity->facingLeft = source->facingLeft;
        entity->zPriority = source->zPriority;
        entity->params = factoryParams & 0xFFF;
        entity->ext.generic.unkA0 = (factoryParams >> 8) & 0xFF00;

        if (source->flags & FLAG_UNK_10000) {
            entity->flags |= FLAG_UNK_10000;
        }
    } else {
        return NULL;
    }
    return entity;
}

INCLUDE_ASM("asm/us/ric/nonmatchings/22380", func_80160788);

void func_80160C38(Entity* entity) {
    if (PLAYER.step != 23) {
        DestroyEntity(entity);
    } else {
        entity->posX.i.hi = PLAYER.posX.i.hi;
        entity->posY.i.hi = PLAYER.posY.i.hi;
        entity->facingLeft = PLAYER.facingLeft;
        if (entity->step == 0) {
            entity->flags = FLAG_UNK_20000 | FLAG_UNK_40000 | FLAG_UNK_04000000;
            entity->hitboxOffX = 0x14;
            entity->hitboxOffY = 0xC;
            entity->hitboxHeight = 9;
            entity->hitboxWidth = 9;
            entity->ext.generic.unkB0 = 0x12;
            func_8015FAB8(entity);
            entity->ext.generic.unk7C.s = entity->hitboxState;
            entity->step++;
        }
        entity->hitboxState = entity->ext.generic.unk7C.s;
        if (PLAYER.animFrameIdx < 2) {
            entity->hitboxState = 0;
        }
        if (PLAYER.animFrameIdx >= 8) {
            DestroyEntity(entity);
        }
    }
}

void func_80160D2C(Entity* self) {
    if (PLAYER.step != 26) {
        DestroyEntity(self);
        return;
    }
    self->posX.i.hi = PLAYER.posX.i.hi;
    self->posY.i.hi = PLAYER.posY.i.hi;
    self->facingLeft = PLAYER.facingLeft;

    if (self->step == 0) {
        self->flags = FLAG_UNK_20000 | FLAG_UNK_40000 | FLAG_UNK_04000000;
        self->hitboxOffX = 0x14;
        self->hitboxHeight = 9;
        self->hitboxWidth = 9;
        self->ext.generic.unkB0 = 0x17;
        func_8015FAB8(self);
        self->step++;
    }

    if (PLAYER.animCurFrame == 140) {
        self->hitboxOffY = 0;
    }

    if (PLAYER.animCurFrame == 141) {
        self->hitboxOffY = 12;
    }

    if (self->hitFlags != 0) {
        g_Player.unk44 |= 0x80;
    } else {
        g_Player.unk44 &= ~0x80;
    }
    self->hitFlags = 0;
}

void func_80160E4C(Entity* self) {
    if (PLAYER.step != 24) {
        DestroyEntity(self);
    } else {
        self->posX.i.hi = PLAYER.posX.i.hi;
        self->posY.i.hi = PLAYER.posY.i.hi;
        self->facingLeft = PLAYER.facingLeft;
        if (self->step == 0) {
            self->flags = FLAG_UNK_20000 | FLAG_UNK_40000 | FLAG_UNK_04000000;
            self->hitboxHeight = 20;
            self->hitboxWidth = 20;
            self->hitboxOffY = 0;
            self->hitboxOffX = 0;
            self->ext.generic.unkB0 = 0x11;
            func_8015FAB8(self);
            self->step++;
        }
        if (PLAYER.animFrameIdx >= 19) {
            DestroyEntity(self);
        }
    }
}

void func_80160F0C(Entity* self) {
    if (PLAYER.step != 8) {
        DestroyEntity(self);
        return;
    }
    self->posX.i.hi = PLAYER.posX.i.hi;
    self->posY.i.hi = PLAYER.posY.i.hi;
    self->facingLeft = PLAYER.facingLeft;
    if (self->step == 0) {
        self->flags = FLAG_UNK_20000 | FLAG_UNK_40000 | FLAG_UNK_04000000;
        self->hitboxOffX = 0xC;
        self->hitboxOffY = -0x1A;
        self->hitboxWidth = 12;
        self->hitboxHeight = 12;
        self->ext.generic.unkB0 = 0x16;
        func_8015FAB8(self);
        self->step++;
    }
}

INCLUDE_ASM("asm/us/ric/nonmatchings/22380", func_80160FC4);

INCLUDE_ASM("asm/us/ric/nonmatchings/22380", func_8016147C);

void func_80161C2C(Entity* self) {
    u16 params = self->params;
    s16 paramsHi = self->params >> 8;
    s32 step = self->step;
    s32 rnd;

    switch (step) {
    case 0:
        if (paramsHi == 1) {
            self->rotX = 0xC0;
            self->rotY = 0xC0;
            self->drawFlags = FLAG_DRAW_ROTX | FLAG_DRAW_ROTY;
            self->animSet = ANIMSET_DRA(2);
            self->unk4C = D_80154E04;
        }

        if ((paramsHi == 0) || (paramsHi == 2)) {
            if (params & 3) {
                self->unk4C = D_80154DC8;
                self->rotX = 0x120;
                self->rotY = 0x120;
                self->drawFlags = FLAG_DRAW_ROTX | FLAG_DRAW_ROTY;
                self->animSet = ANIMSET_DRA(2);
            } else {
                self->animSet = ANIMSET_DRA(5);
                self->unk4C = D_80154C80;
                self->palette = 0x8170;
            }
        }
        self->flags = FLAG_UNK_20000 | FLAG_UNK_100000 | FLAG_UNK_08000000;

        if (rand() % 4) {
            self->zPriority = PLAYER.zPriority + 2;
        } else {
            self->zPriority = PLAYER.zPriority - 2;
        }

        if (paramsHi == 2) {
            self->posX.i.hi = PLAYER.posX.i.hi + (rand() % 44) - 22;
        } else {
            self->posX.i.hi = PLAYER.posX.i.hi + (rand() & 15) - 8;
        }

        rnd = rand() & 31;
        self->posY.i.hi = PLAYER.posY.i.hi + PLAYER.hitboxOffY + rnd - 16;
        self->velocityY = FIX(-0.5);
        self->velocityX = PLAYER.velocityX >> 2;
        self->step++;
        break;

    case 1:
        self->rotX -= 4;
        self->rotY -= 4;
        self->posY.val += self->velocityY;
        self->posX.val += self->velocityX;
        if ((self->animFrameIdx == 8) && (self->unk4C != D_80154C80)) {
            self->blendMode = 0x10;
            if (!(params & 1) && (self->animFrameDuration == step)) {
                CreateEntFactoryFromEntity(self, 0x40004, 0);
            }
        }

        if ((self->animFrameIdx == 16) && (self->unk4C == D_80154C80)) {
            self->blendMode = 0x10;
        }

        if (self->animFrameDuration < 0) {
            DestroyEntity(self);
        }
        break;
    }
}

void func_80161EF8(Entity* self) {
    switch (self->step) {
    case 0:
        self->animSet = ANIMSET_DRA(2);
        self->unk4C = &D_80154E38;
        self->flags =
            FLAG_UNK_20000 | FLAG_UNK_100000 | FLAG_UNK_10000 | FLAG_UNK_40000;
        self->zPriority = PLAYER.zPriority + 4;
        self->velocityY = (rand() & 0x3FFF) - 0x10000;
        self->step++;
        break;

    case 1:
        if ((self->animFrameIdx == 6) &&
            (self->animFrameDuration == self->step) && (rand() & 1)) {
            CreateEntFactoryFromEntity(self, 4, 0);
        }
        self->posY.val += self->velocityY;
        if (self->animFrameDuration < 0) {
            DestroyEntity(self);
        }
        break;
    }
}

INCLUDE_ASM("asm/us/ric/nonmatchings/22380", func_80161FF0);

void func_801623E0(Entity* entity) {
    POLY_GT4* poly;
    s16 primIndex;

    entity->posX.val = g_Entities->posX.val;
    entity->posY.val = PLAYER.posY.val;
    switch (entity->step) {
    case 0:
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 1);
        entity->primIndex = primIndex;
        if (primIndex == -1) {
            DestroyEntity(entity);
            return;
        }
        entity->ext.generic.unk7E.modeU16 = 32;
        entity->ext.generic.unk7C.s = 32;
        poly = &g_PrimBuf[entity->primIndex];
        poly->u2 = 64;
        poly->u0 = 64;
        poly->v1 = 192;
        poly->v0 = 192;
        poly->u3 = 127;
        poly->u1 = 127;
        poly->v3 = 255;
        poly->v2 = 255;
        poly->tpage = 0x1A;
        poly->clut = 0x13E;
        poly->pad2 = PLAYER.zPriority + 8;
        poly->pad3 = 0;
        entity->flags = FLAG_UNK_10000 | FLAG_UNK_40000 | FLAG_UNK_04000000 |
                        FLAG_HAS_PRIMS;
        entity->step++;
        break;

    case 1:
        entity->ext.generic.unk7C.s++;
        entity->ext.generic.unk7E.modeU16++;
        if (entity->ext.generic.unk7C.s >= 45) {
            DestroyEntity(entity);
            return;
        }
        break;
    }

    poly = &g_PrimBuf[entity->primIndex];
    poly->x0 = entity->posX.i.hi - entity->ext.generic.unk7C.s;
    poly->y0 = entity->posY.i.hi - entity->ext.generic.unk7E.modeU16;
    poly->x1 = entity->posX.i.hi + entity->ext.generic.unk7C.s;
    poly->y1 = entity->posY.i.hi - entity->ext.generic.unk7E.modeU16;
    poly->x2 = entity->posX.i.hi - entity->ext.generic.unk7C.s;
    poly->y2 = entity->posY.i.hi + entity->ext.generic.unk7E.modeU16;
    poly->x3 = entity->posX.i.hi + entity->ext.generic.unk7C.s;
    poly->y3 = entity->posY.i.hi + entity->ext.generic.unk7E.modeU16;
    poly->clut = (LOH(g_Timer) & 1) + 0x13E;
}

void func_80162604(Entity* entity) {
    POLY_GT4* poly;
    s16 primIndex;

    entity->posX.val = g_Entities->posX.val;
    entity->posY.val = PLAYER.posY.val;
    switch (entity->step) {
    case 0:
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 1);
        entity->primIndex = primIndex;
        if (primIndex != -1) {
            entity->ext.generic.unk7E.modeU16 = 0;
            entity->ext.generic.unk7C.s = 0;
            poly = &g_PrimBuf[entity->primIndex];
            poly->v1 = 192;
            poly->v0 = 192;
            poly->u3 = 63;
            poly->u1 = 63;
            poly->v3 = 255;
            poly->v2 = 255;
            poly->tpage = 0x1A;
            poly->u2 = 0;
            poly->u0 = 0;
            poly->clut = 0x162;
            poly->pad2 = PLAYER.zPriority - 4;
            poly->pad3 = 0;
            entity->flags = FLAG_UNK_10000 | FLAG_UNK_40000 |
                            FLAG_UNK_04000000 | FLAG_HAS_PRIMS;
            entity->step++;
            goto def;
        } else {
            DestroyEntity(entity);
            break;
        }

    case 1:
        entity->ext.generic.unk7C.s += 8;
        entity->ext.generic.unk7E.modeU16 += 8;
        if (entity->ext.generic.unk7C.s < 0x20) {
            goto def;
        }

    case 2:
        entity->step++;
        goto def;

    case 3:
        entity->ext.generic.unk7C.s -= 8;
        entity->ext.generic.unk7E.modeU16 -= 8;
        if (entity->ext.generic.unk7C.s >= 5) {
            goto def;
        } else {

            DestroyEntity(entity);
        }
        break;

    def:
    default:
        poly = &g_PrimBuf[entity->primIndex];
        poly->x0 = entity->posX.i.hi - entity->ext.generic.unk7C.s;
        poly->y0 = entity->posY.i.hi - entity->ext.generic.unk7E.modeU16;
        poly->x1 = entity->posX.i.hi + entity->ext.generic.unk7C.s;
        poly->y1 = entity->posY.i.hi - entity->ext.generic.unk7E.modeU16;
        poly->x2 = entity->posX.i.hi - entity->ext.generic.unk7C.s;
        poly->y2 = entity->posY.i.hi + entity->ext.generic.unk7E.modeU16;
        poly->x3 = entity->posX.i.hi + entity->ext.generic.unk7C.s;
        poly->y3 = entity->posY.i.hi + entity->ext.generic.unk7E.modeU16;
        break;
    }
}

INCLUDE_ASM("asm/us/ric/nonmatchings/22380", func_80162870);

void func_80162C7C(void) {}
