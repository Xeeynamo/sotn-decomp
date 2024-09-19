#include "chi.h"
#include "collision_data.h"

/*
 * File: collision.c
 * Overlay: CHI
 * Description: Abandoned Mine
 */

void func_8019F3C0(void);

u16 g_testCollPrizeTable[] = {
    0x0003, 0x0000, 0x0002, 0x0003, 0x0003, 0x0003, 0x0003, 0x0003,
    0x0003, 0x0004, 0x0004, 0x0004, 0x0004, 0x0005, 0x0005, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0001, 0x0001, 0x0002, 0x0006, 0x0007, 0x00C6,
};

u16 g_testCollRandTable[] = {
    0x0C00, 0x0168, 0x0F00, 0x0169, 0x0FD0, 0x016A, 0x0FF0,
    0x016B, 0x0FF8, 0x016C, 0x0FFD, 0x016D, 0x0FFF, 0x016E,
};

//TODO: Centralize this instead of what's in ../collision.h?
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
                        iterEnt1->unk44 = iterEnt2->hitEffect & 0x7F;
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
                                    iterEnt2->ext.generic.unkB8.entityPtr =
                                        iterEnt1;
                                    // reminder: iterEnt1->hitboxState
                                    if (miscVar1 & 8) {
                                        iterEnt2->hitFlags = 3;
                                    } else {
                                        iterEnt2->hitFlags = 1;
                                    }
                                    if ((i == 3) &&
                                        (iterEnt1->flags & FLAG_UNK_8000)) {
                                        g_api.PlaySfx(SFX_CLANK);
                                        iterEnt2->hitFlags = 2;
                                    }
                                    if ((i == 4) &&
                                        (iterEnt1->flags & FLAG_UNK_4000)) {
                                        g_api.PlaySfx(SFX_CLANK);
                                        iterEnt2->hitFlags = 2;
                                    }
                                }
                                iterEnt1->unk44 = i;
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
                            iterEnt2->ext.player.unkB8 = iterEnt1;
                            if (miscVar1 & 8) {
                                iterEnt2->hitFlags = 3;
                            } else {
                                iterEnt2->hitFlags = 1;
                            }
                            iterEnt2->unk44 = iterEnt1->attackElement;
                            iterEnt2->hitPoints = iterEnt1->attack;
                        }
                        iterEnt1->unk44 = iterEnt2->hitEffect & 0x7F;
                        miscVar2 = 0xFF;
                        iterEnt1->hitFlags = 0x80;
                    }
                }
            }
        }
        if (miscVar2) {
            if (iterEnt1->unk5C != NULL) {
                entFrom5C = iterEnt1->unk5C;
                entFrom5C->unk44 = (u16)iterEnt1->unk44;
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
                    g_CastleFlags[(miscVar1 >> 3) + 0x190] |= miscVar3;
                }
                if ((g_Status.relics[RELIC_FAERIE_SCROLL] & 2) &&
                    !(entFrom5C->flags & FLAG_UNK_01000000)) {
                    if (g_unkGraphicsStruct.BottomCornerTextTimer != 0) {
                        g_api.FreePrimitives(
                            g_unkGraphicsStruct.BottomCornerTextPrims);
                        g_unkGraphicsStruct.BottomCornerTextTimer = 0;
                    }
                    BottomCornerText(
                        g_api.enemyDefs[entFrom5C->enemyId].name, 0);
                    entFrom5C->flags |= FLAG_UNK_01000000;
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
                            !(entFrom5C->flags & FLAG_UNK_04000000) &&
                            miscVar1) {
                            otherEntity =
                                AllocEntity(&g_Entities[224], &g_Entities[256]);
                            if (otherEntity != NULL) {
                                DestroyEntity(otherEntity);
                                otherEntity->entityId = 4;
                                otherEntity->pfnUpdate = func_8019F3C0;
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
                                for (i = 0; i < 10;
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
                                g_api.PlaySfx(SE_WEAPON_STAB);
                            } else {
                                g_api.PlaySfx(SE_WEAPON_WHACK);
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
                if ((entFrom5C->flags & 0x10) && (iterEnt2->attack)) {
                    if (iterEnt2->hitEffect & 0x80) {
                        g_api.PlaySfx(SFX_CLANK);
                    } else {
                        g_api.PlaySfx(SFX_CLANK);
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
//#ifndef NON_MATCHING
INCLUDE_ASM("st/chi/nonmatchings/collision", func_8019F3C0);    // EntityDamageDisplay()
//#else
// extern /*?*/s32 D_80180DFC;
// extern u16 EntityInit_80180670;
// extern s32 PLAYER_posY_val;

// void func_8019F3C0(Entity* arg0)
// {
//     Primitive* var_a3;
//     Primitive* var_a3_2;
//     s16 temp_a0_5;
//     s16 temp_a0_6;
//     s16 temp_a1_3;
//     s16 temp_a2_2;
//     s16 temp_v0;
//     s16 temp_v0_4;
//     s16 temp_v1_7;
//     s16 var_t0;
//     s32 temp_a1;
//     s32 temp_a1_4;
//     s32 temp_a2;
//     s32 temp_t0;
//     s32 temp_t0_2;
//     s32 temp_v0_3;
//     s32 temp_v1_3;
//     s32 temp_v1_4;
//     s32 temp_v1_6;
//     s32 var_a0;
//     s32 var_t2;
//     s32 var_v0;
//     s32 var_v0_2;
//     s32 var_v1;
//     s8 temp_a0;
//     s8 temp_a0_2;
//     s8 temp_a0_3;
//     u16 temp_a0_4;
//     u16 temp_s1;
//     u16 temp_t0_3;
//     u16 temp_v1;
//     u16 temp_v1_2;
//     u16 temp_v1_5;
//     u16 var_v0_4;
//     u16 var_v0_5;
//     u16 var_v0_6;
//     u16 var_v1_2;
//     u16* temp_s2;
//     u8 temp_a1_2;
//     u8 temp_v0_2;
//     u8 var_v0_3;

//     if (arg0->ext.factory.unk88 != 0) {
//         arg0->posX.val = g_Entities->posX.val;
//         arg0->posY.val = PLAYER_posY_val + 0xFFF00000;
//     }
//     temp_v1 = arg0->step;
//     switch (temp_v1) {                              // irregular
//         case 0:
//             temp_v1_2 = arg0->step_s;
//             if (temp_v1_2 != 9) {
//                 temp_s1 = arg0->params;
//                 temp_s2 = arg0 + 0x7E;
//                 if (temp_v1_2 == 0) {
//                     InitializeEntity(&EntityInit_80180670);
//                     arg0->step = 0;
//                     if ((temp_s1 & 0xFFFF) != 0xC000) {
//                         temp_a0 = (temp_s1 & 0x3FFF) / 1000;
//                         temp_a1 = temp_a0 & 0xFFFF;
//                         var_v0 = temp_a1 << 5;
//                         if (temp_a1 != 0) {
//                             arg0->ext.timer.t += 1;
//                             arg0->ext.factory.unk7E += 1;
//                             var_v0 = temp_a1 << 5;
//                         }
//                         temp_t0 = (temp_s1 & 0x3FFF) - ((((var_v0 - temp_a1) * 4) + temp_a1) * 8);
//                         arg0->ext.stub[4] = temp_a0;
//                         temp_a0_2 = (temp_t0 & 0xFFFF) / 100;
//                         if ((temp_a0_2 & 0xFFFF) || (var_v1 = temp_a0_2 & 0xFFFF, (arg0->ext.factory.unk7E != 0))) {
//                             arg0->ext.timer.t += 1;
//                             arg0->ext.factory.unk7E += 1;
//                             var_v1 = temp_a0_2 & 0xFFFF;
//                         }
//                         temp_t0_2 = temp_t0 - (var_v1 * 0x64);
//                         arg0->ext.stub[5] = temp_a0_2;
//                         temp_a0_3 = (temp_t0_2 & 0xFFFF) / 10;
//                         if ((temp_a0_3 & 0xFFFF) || (*temp_s2 != 0)) {
//                             arg0->ext.timer.t += 1;
//                             *temp_s2 += 1;
//                         }
//                         arg0->ext.stub[6] = temp_a0_3;
//                         arg0->ext.timer.t += 1;
//                         *temp_s2 += 1;
//                         arg0->ext.stub[7] = temp_t0_2 - ((temp_a0_3 & 0xFFFF) * 0xA);
//                         if (temp_s1 & 0x4000) {
//                             goto block_17;
//                         }
//                     } else {
// block_17:
//                         arg0->ext.timer.t += 1;
//                     }
//                 }
//                 temp_v0 = g_api_AllocPrimitives(PRIM_GT4, (s32) arg0->ext.timer.t);
//                 if (temp_v0 != 0) {
//                     var_a3 = &g_PrimBuf[temp_v0];
//                     var_t2 = 0;
//                     arg0->primIndex = (s32) temp_v0;
//                     arg0->flags |= 0x800000;
//                     var_a0 = 4 - *temp_s2;
//                     var_t0 = -(*temp_s2 * 2);
//                     if (var_a3 != NULL) {
//                         temp_v1_3 = temp_s1 & 0x4000;
//                         var_v0_2 = 0 & 0xFFFF;
//                         do {
//                             if (var_v0_2 == 0) {
//                                 var_t2 += 1;
//                                 if ((temp_s1 & 0xC000) == 0xC000) {
//                                     var_a3->u2 = 0x43;
//                                     var_a3->u0 = 0x43;
//                                     var_a3->u3 = 0x59;
//                                     var_a3->u1 = 0x59;
//                                     var_a3->v1 = 0x4A;
//                                     var_a3->v0 = 0x4A;
//                                     var_a3->v3 = 0x52;
//                                     var_a3->v2 = 0x52;
//                                     var_a3->unk1C = 0xB;
//                                     var_a3->unk1E = 5;
//                                     var_a3->unk10 = 0;
//                                     var_a3->unk12 = -0x10;
//                                     goto block_33;
//                                 }
//                                 if (temp_v1_3 != 0) {
//                                     var_a3->u2 = 0x20;
//                                     var_a3->u0 = 0x20;
//                                     var_a3->u3 = 0x42;
//                                     var_a3->u1 = 0x42;
//                                     var_a3->unk1C = 0x11;
//                                     var_a3->v1 = 0x4A;
//                                     var_a3->v0 = 0x4A;
//                                     var_a3->v3 = 0x52;
//                                     var_a3->v2 = 0x52;
//                                     var_a3->unk1E = 5;
//                                     var_a3->unk10 = 0;
//                                     var_a3->unk12 = -0x18;
//                                     goto block_33;
//                                 }
//                             } else {
//                                 var_a3->unk10 = var_t0;
//                                 var_a3->unk12 = -0x10;
//                                 if (temp_v1_3 != 0) {
//                                     var_a3->unk1C = 3;
//                                     var_a3->unk1E = 5;
//                                 } else {
//                                     var_a3->unk1C = 0x17;
//                                     var_a3->unk1E = 0;
//                                 }
//                                 temp_v0_2 = (arg0 + (var_a0 & 0xFFFF))->unk80;
//                                 temp_v0_3 = temp_v0_2 * 8;
//                                 if (temp_v0_2 != 0) {
//                                     temp_a1_2 = temp_v0_3 + 0x18;
//                                     var_v0_3 = temp_v0_3 + 0x1E;
//                                     var_a3->u2 = temp_a1_2;
//                                     var_a3->u0 = temp_a1_2;
//                                 } else {
//                                     var_a3->u2 = 0x68;
//                                     var_a3->u0 = 0x68;
//                                     var_v0_3 = 0x6E;
//                                 }
//                                 var_a3->u3 = var_v0_3;
//                                 var_a3->u1 = var_v0_3;
//                                 var_t0 += 4;
//                                 var_a0 += 1;
//                                 var_a3->v1 = 0x40;
//                                 var_a3->v0 = 0x40;
//                                 var_a3->v3 = 0x49;
//                                 var_a3->v2 = 0x49;
// block_33:
//                                 var_a3->tpage = 0x1A;
//                                 var_a3->priority = 0x1F8;
//                                 var_a3->drawMode = 8;
//                                 var_a3 = var_a3->next;
//                             }
//                             var_v0_2 = var_t2 & 0xFFFF;
//                         } while (var_a3 != NULL);
//                     }
//                     arg0->step_s = 0;
//                     arg0->ext.factory.unk84 = 0x40;
//                     arg0->step += 1;
//                 }
//                 arg0->step_s += 1;
//                 return;
//             }
// block_38:
//             DestroyEntity(arg0);
//             return;
//         case 1:
//             temp_a0_4 = arg0->ext.factory.unk84 + 0xFFFF;
//             arg0->ext.factory.unk84 = temp_a0_4;
//             if (!(temp_a0_4 & 0xFFFF)) {
//                 goto block_38;
//             }
//             var_a3_2 = &g_PrimBuf[arg0->primIndex];
//             temp_v1_4 = ((u16) arg0->params >> 0xD) & 6;
//             temp_t0_3 = *(&D_80180DFC + ((temp_v1_4 | (temp_a0_4 & 1)) * 2));
//             if ((temp_v1_4 != 0) && (temp_v1_4 != 4)) {
//                 if (var_a3_2 != NULL) {
//                     do {
//                         temp_v1_5 = arg0->ext.factory.unk84;
//                         if (temp_v1_5 >= 0x3CU) {
//                             var_v0_4 = var_a3_2->unk1C + 1;
//                             var_v1_2 = var_a3_2->unk1E + 1;
//                             goto block_47;
//                         }
//                         if (temp_v1_5 >= 0x38U) {
//                             var_v0_4 = var_a3_2->unk1C + 0xFFFF;
//                             var_v1_2 = var_a3_2->unk1E + 0xFFFF;
// block_47:
//                             var_a3_2->unk1C = var_v0_4;
//                             var_a3_2->unk1E = var_v1_2;
//                         }
//                         temp_v1_6 = arg0->posX.i.hi + var_a3_2->unk10;
//                         temp_a1_3 = temp_v1_6 - var_a3_2->unk1C;
//                         temp_a0_5 = var_a3_2->unk1C + temp_v1_6;
//                         var_a3_2->clut = temp_t0_3;
//                         var_a3_2->x2 = temp_a1_3;
//                         var_a3_2->x0 = temp_a1_3;
//                         var_a3_2->x3 = temp_a0_5;
//                         var_a3_2->x1 = temp_a0_5;
//                         temp_a2 = arg0->posY.i.hi + var_a3_2->unk12;
//                         temp_v1_7 = var_a3_2->unk1E + temp_a2;
//                         var_a3_2->y3 = temp_v1_7;
//                         var_a3_2->y2 = temp_v1_7;
//                         temp_v0_4 = temp_a2 - var_a3_2->unk1E;
//                         var_a3_2->y1 = temp_v0_4;
//                         var_a3_2->y0 = temp_v0_4;
//                         var_v0_5 = 0x13;
//                         if ((u16) arg0->ext.factory.unk84 >= 6U) {
//                             var_v0_5 = 2;
//                         }
//                         var_a3_2->drawMode = var_v0_5;
//                         var_a3_2 = var_a3_2->next;
//                     } while (var_a3_2 != NULL);
//                 }
//                 if (arg0->ext.factory.unk88 != 0) {
//                     return;
//                 }
//                 goto block_61;
//             }
//             if (var_a3_2 != NULL) {
//                 do {
//                     if ((u16) var_a3_2->unk1C >= 4U) {
//                         var_a3_2->unk1C = (u16) (var_a3_2->unk1C - 1);
//                     }
//                     if ((u16) var_a3_2->unk1E < 0xAU) {
//                         var_a3_2->unk1E = (u16) (var_a3_2->unk1E + 1);
//                     }
//                     var_a3_2->clut = temp_t0_3;
//                     temp_a0_6 = (arg0->posY.i.hi + var_a3_2->unk12) - (var_a3_2->unk1E - 5);
//                     temp_a2_2 = var_a3_2->unk1E + temp_a0_6;
//                     var_a3_2->y1 = temp_a0_6;
//                     var_a3_2->y0 = temp_a0_6;
//                     var_a3_2->y3 = temp_a2_2;
//                     var_a3_2->y2 = temp_a2_2;
//                     temp_a1_4 = arg0->posX.i.hi + var_a3_2->unk10;
//                     var_a3_2->x1 = temp_a1_4 + var_a3_2->unk1C;
//                     var_a3_2->x0 = temp_a1_4 - var_a3_2->unk1C;
//                     var_a3_2->x2 = temp_a1_4 - 3;
//                     var_a3_2->x3 = temp_a1_4 + 3;
//                     var_v0_6 = 0x13;
//                     if ((u16) arg0->ext.factory.unk84 >= 6U) {
//                         var_v0_6 = 2;
//                     }
//                     var_a3_2->drawMode = var_v0_6;
//                     var_a3_2 = var_a3_2->next;
//                 } while (var_a3_2 != NULL);
//             }
// block_61:
//             arg0->posY.val -= 0x8000;
//             return;
//     }
// }
//#endif
//#include "../entity_damage_display.h"
//#include "../collision.h"

#include "../create_entity.h"

INCLUDE_ASM("st/chi/nonmatchings/collision", func_801A05DC);    // EntityIsNearPlayer2()
INCLUDE_ASM("st/chi/nonmatchings/collision", func_801A0654);    // EntityRedDoor()
//#include "../e_red_door.h"

#include "../entity.h"

INCLUDE_ASM("st/chi/nonmatchings/collision", func_801A1474);    // [Duplicate]

// "Current entity" functions?
#include "../get_distance_to_player_x.h"
#include "../get_distance_to_player_y.h"
#include "../get_side_to_player.h"
#include "../move_entity.h"
#include "../fall_entity.h"

INCLUDE_ASM("st/chi/nonmatchings/collision", func_801A169C);    // [Duplicate]

INCLUDE_ASM("st/chi/nonmatchings/collision", func_801A1914);    // [Duplicate]

#include "../../alloc_entity.h"

INCLUDE_ASM("st/chi/nonmatchings/collision", func_801A1B5C);    // [Duplicate]

INCLUDE_ASM("st/chi/nonmatchings/collision", func_801A1B88);    // [Duplicate]

INCLUDE_ASM("st/chi/nonmatchings/collision", func_801A1BA4);    // [Duplicate]

INCLUDE_ASM("st/chi/nonmatchings/collision", func_801A1C10);    // [Duplicate]

INCLUDE_ASM("st/chi/nonmatchings/collision", func_801A1C48);    // [Duplicate]

INCLUDE_ASM("st/chi/nonmatchings/collision", func_801A1C90);    // [Duplicate]

#include "../adjust_value_within_threshold.h"
#include "../unk_entity_func0.h"

INCLUDE_ASM("st/chi/nonmatchings/collision", func_801A1DBC);    // [Duplicate]

#include "../get_angle_between_entities.h"
INCLUDE_ASM("st/chi/nonmatchings/collision", func_801A1E24);    // [Duplicate]
#include "../get_normalized_angle.h"

#include "../set_step.h"
#include "../set_sub_step.h"

INCLUDE_ASM("st/chi/nonmatchings/collision", func_801A1F08);    // EntityExplosionSpawn()
//#include "../entity_explosion_spawn.h"

#include "../init_entity.h"
#include "../entity_dummy.h"

INCLUDE_ASM("st/chi/nonmatchings/collision", func_801A20C0);    // [Duplicate]

#include "../check_field_collision.h"
#include "../get_player_collision_with.h"

INCLUDE_ASM("st/chi/nonmatchings/collision", func_801A2684);    // ReplaceBreakableWithItemDrop()
//#include "../replace_breakable_with_item_drop.h"

INCLUDE_ASM("st/chi/nonmatchings/collision", func_801A273C);    // [Duplicate]
INCLUDE_ASM("st/chi/nonmatchings/collision", func_801A27C0);    // [Duplicate]
INCLUDE_ASM("st/chi/nonmatchings/collision", func_801A291C);    // CollectHeart()
INCLUDE_ASM("st/chi/nonmatchings/collision", func_801A299C);    // CollectGold()
INCLUDE_ASM("st/chi/nonmatchings/collision", func_801A2A78);    // CollectSubweapon()
INCLUDE_ASM("st/chi/nonmatchings/collision", func_801A2B90);    // CollectHeartVessel()
INCLUDE_ASM("st/chi/nonmatchings/collision", func_801A2C34);    // CollectLifeVessel()
INCLUDE_ASM("st/chi/nonmatchings/collision", func_801A2C84);    // DestroyCurrentEntity()

// POSSIBLE FILE BREAK

INCLUDE_ASM("st/chi/nonmatchings/collision", func_801A2CAC);    // EntityPrizeDrop()
INCLUDE_ASM("st/chi/nonmatchings/collision", func_801A3520);    // EntityExplosion()
//#include "../entity_explosion.h"
#include "../blink_item.h"
INCLUDE_ASM("st/chi/nonmatchings/collision", func_801A36C0);    // EntityEquipItemDrop()
//#include "../e_collect.h"

#include "../blit_char.h"

INCLUDE_ASM("st/chi/nonmatchings/collision", func_801A3F58);    // EntityRelicOrb()
//#include "../entity_relic_orb.h"

INCLUDE_ASM("st/chi/nonmatchings/collision", func_801A4A28);    // EntityHeartDrop()

INCLUDE_ASM("st/chi/nonmatchings/collision", func_801A4B50);    // EntityMessageBox()
//#include "../entity_message_box.h"

#include "../check_coll_offsets.h"

INCLUDE_ASM("st/chi/nonmatchings/collision", func_801A519C);    // EntityUnkId13()
//#include "../entity_unkId13.h"

INCLUDE_ASM("st/chi/nonmatchings/collision", func_801A52AC);    // EntityUnkId14Spawner()
//#include "../entity_unkId14_spawner.h"

INCLUDE_ASM("st/chi/nonmatchings/collision", func_801A53DC);    // EntityUnkId15Spawner()
//#include "../entity_unkId15_spawner.h"

INCLUDE_ASM("st/chi/nonmatchings/collision", func_801A54C4);    // EntityUnkId14()
//#include "../entity_unkId14.h"

INCLUDE_ASM("st/chi/nonmatchings/collision", func_801A55B4);    // EntityUnkId15()
//#include "../entity_unkId15.h"

INCLUDE_ASM("st/chi/nonmatchings/collision", func_801A56A8);    // EntityOlroxDrool()
//#include "../entity_olrox_drool.h"

INCLUDE_ASM("st/chi/nonmatchings/collision", func_801A58D8);    // [Duplicate]

INCLUDE_ASM("st/chi/nonmatchings/collision", func_801A59D4);    // [Duplicate]

INCLUDE_ASM("st/chi/nonmatchings/collision", func_801A5F54);    // EntityIntenseExplosion()
//#include "../entity_intense_explosion.h"

INCLUDE_ASM("st/chi/nonmatchings/collision", func_801A6054);    // [Duplicate]

// [Duplicate]
void func_801A6120(u16 entityId, Entity* src, Entity* dst)
{
    DestroyEntity(dst);
    dst->entityId = entityId;
    dst->pfnUpdate = PfnEntityUpdates[entityId - 1];
    dst->posX.i.hi = src->posX.i.hi;
    dst->posY.i.hi = src->posY.i.hi;
    dst->unk5A = src->unk5A;
    dst->zPriority = src->zPriority;
    dst->animSet = src->animSet;
    dst->flags = FLAG_UNK_2000 | FLAG_UNK_01000000 | FLAG_UNK_04000000 |
                 FLAG_UNK_08000000 | FLAG_DESTROY_IF_BARELY_OUT_OF_CAMERA |
                 FLAG_DESTROY_IF_OUT_OF_CAMERA;

    if (src->palette & 0x8000) {
        dst->palette = src->hitEffect;
    } else {
        dst->palette = src->palette;
    }
}

INCLUDE_ASM("st/chi/nonmatchings/collision", func_801A61E8);    // [Duplicate]

INCLUDE_ASM("st/chi/nonmatchings/collision", func_801A62A0);    // EntityBigRedFireball()
//#include "../entity_big_red_fireball.h"

INCLUDE_ASM("st/chi/nonmatchings/collision", func_801A6478);    // UnkRecursivePrimFunc1()
//#include "../unk_recursive_primfunc_1.h"

INCLUDE_ASM("st/chi/nonmatchings/collision", func_801A6A58);    // UnkRecursivePrimFunc2()
//#include "../unk_recursive_primfunc_2.h"

#include "../clut_lerp.h"

#include "../play_sfx_with_pos_args.h"

INCLUDE_ASM("st/chi/nonmatchings/collision", func_801A7448);    // EntitySoulStealOrb()
//#include "../entity_soul_steal_orb.h"

INCLUDE_ASM("st/chi/nonmatchings/collision", func_801A77DC);    // EntityEnemyBlood()
//#include "../entity_enemy_blood.h"

INCLUDE_ASM("st/chi/nonmatchings/collision", func_801A7C8C);    // EntityRoomForeground()
//#include "../e_room_fg.h"

#include "../bottom_corner_text.h"

INCLUDE_ASM("st/chi/nonmatchings/collision", func_801A80A8);

// POSSIBLE FILE BREAK

INCLUDE_ASM("st/chi/nonmatchings/collision", func_801A813C);    // [Entity]

INCLUDE_ASM("st/chi/nonmatchings/collision", func_801A8DE8);    // [Entity]

INCLUDE_ASM("st/chi/nonmatchings/collision", func_801A8EAC);    // [Entity]

INCLUDE_ASM("st/chi/nonmatchings/collision", func_801A93D4);    // [Entity]

INCLUDE_ASM("st/chi/nonmatchings/collision", func_801A9588);    // [Entity]

INCLUDE_ASM("st/chi/nonmatchings/collision", func_801A97C8);    // [Entity]

INCLUDE_ASM("st/chi/nonmatchings/collision", func_801A9D40);    // [Entity]

INCLUDE_ASM("st/chi/nonmatchings/collision", func_801A9E94);    // [Entity]

INCLUDE_ASM("st/chi/nonmatchings/collision", func_801AA020);    // [Entity]

INCLUDE_ASM("st/chi/nonmatchings/collision", func_801AA390);    // [Entity]

INCLUDE_ASM("st/chi/nonmatchings/collision", func_801AB0C0);    // [Entity]

INCLUDE_ASM("st/chi/nonmatchings/collision", func_801AB548);

// POSSIBLE FILE BREAK

INCLUDE_ASM("st/chi/nonmatchings/collision", func_801AB7CC);    // [Entity]

INCLUDE_ASM("st/chi/nonmatchings/collision", func_801AC074);    // [Entity]

INCLUDE_ASM("st/chi/nonmatchings/collision", func_801AC730);    // [Entity]

INCLUDE_ASM("st/chi/nonmatchings/collision", func_801ACB6C);    // [Entity]

INCLUDE_ASM("st/chi/nonmatchings/collision", func_801ACEF4);    // [Entity]

s32 func_801AE70C(Primitive* prim, u8 arg1);
void StageNamePopupHelper(Primitive* prim)  // [Duplicate]
{
    u8 xPos;
    s32 i;
    s32 j;

    switch (prim->p3) {
    case 0:
        if (prim->p1 < 0x80) {
            if (--prim->p1 == 0) {
                prim->p3 = 1;
            }
        } else {
            if (++prim->p1 == 0) {
                prim->p3 = 2;
            }
        }

        if (prim->p3 != 0) {
            u8* dst = prim->p3 == 1 ? &prim->r1 : &prim->r0;
            for (i = 0; i < 2; i++) {
                for (j = 0; j < 3; j++) {
                    dst[j] = 0x50;
                }
                dst += 0x18;
            }
            prim->p2 = 0;
        }
        break;
    case 1:
        if (prim->p2 < 0x14) {
            prim->p2++;
        }
        xPos = prim->p2 / 5;
        prim->x2 = prim->x0 = prim->x0 + xPos;
        prim->x1 = prim->x1 + xPos;
        prim->x3 = prim->x0;
        func_801AE70C(prim, 4);
        break;
    case 2:
        if (prim->p2 < 0x14) {
            prim->p2++;
        }
        xPos = prim->p2 / 5;
        prim->x2 = prim->x0 = prim->x0 - xPos;
        prim->x1 = prim->x1 - xPos;
        prim->x3 = prim->x0;
        func_801AE70C(prim, 4);
        break;
    }
}

// POSSIBLE FILE BREAK

//#ifndef NON_MATCHING
INCLUDE_ASM("st/chi/nonmatchings/collision", func_801AD2BC);    // EntityStageNamePopup()
//#else
// /*?*/ void func_801AD0EC(?*);                                // extern
// extern u8 D_8003BE40;
// extern s8 D_8019B3C0;
// extern s8 D_8019B3D0;
// extern u16 EntityInit_80180640;

// void func_801AD2BC(Entity* arg0)
// {
//     Primitive* temp_s0;
//     Primitive* temp_s0_2;
//     Primitive* temp_s0_3;
//     Primitive* temp_s0_6;
//     Primitive* var_s0;
//     Primitive* var_s0_10;
//     Primitive* var_s0_11;
//     Primitive* var_s0_2;
//     Primitive* var_s0_3;
//     Primitive* var_s0_6;
//     Primitive* var_s0_7;
//     Primitive* var_s0_8;
//     Primitive* var_s0_9;
//     s16 temp_a0_2;
//     s16 temp_a0_3;
//     s16 temp_v0;
//     s16 temp_v0_10;
//     s16 temp_v0_12;
//     s16 temp_v0_17;
//     s16 temp_v0_18;
//     s16 temp_v0_19;
//     s16 temp_v0_4;
//     s16 temp_v0_5;
//     s16 temp_v0_6;
//     s16 temp_v0_7;
//     s16 temp_v0_8;
//     s16 temp_v1_2;
//     s16 temp_v1_3;
//     s16 var_v0_2;
//     s16 var_v1;
//     s16 var_v1_2;
//     s32 temp_s0_4;
//     s32 temp_s0_5;
//     s32 temp_v0_15;
//     s32 temp_v0_20;
//     s32 temp_v0_21;
//     s32 temp_v0_22;
//     s32 temp_v0_3;
//     s32 var_a0;
//     s32 var_s0_4;
//     s32 var_s0_5;
//     s32 var_s1;
//     s32 var_s1_10;
//     s32 var_s1_11;
//     s32 var_s1_12;
//     s32 var_s1_13;
//     s32 var_s1_3;
//     s32 var_s1_4;
//     s32 var_s1_5;
//     s32 var_s1_6;
//     s32 var_s1_7;
//     s32 var_s1_8;
//     s32 var_s1_9;
//     s32 var_v0;
//     u16 temp_a0;
//     u16 temp_v0_2;
//     u16 temp_v1;
//     u16 temp_v1_4;
//     u8 temp_a1;
//     u8 temp_a1_2;
//     u8 temp_a2;
//     u8 temp_v0_11;
//     u8 temp_v0_13;
//     u8 temp_v0_14;
//     u8 temp_v0_16;
//     u8 temp_v0_9;
//     u8 var_a1;
//     u8 var_a1_2;
//     u8 var_s1_2;

//     temp_a0 = arg0->step;
//     switch (temp_a0) {                              // switch 1; irregular
//         case 0:                                     // switch 1
//             if ((g_DemoMode == Demo_None) && (D_8003BE40 == 0)) {
//                 InitializeEntity(&EntityInit_80180640);
//                 temp_v0 = g_api_AllocPrimitives(PRIM_GT4, 0x57);
//                 if (temp_v0 != -1) {
//                     var_s0 = &g_PrimBuf[temp_v0];
//                     arg0->primIndex = (s32) temp_v0;
//                     arg0->ext.prim = var_s0;
//                     arg0->flags |= 0x800000;
//                     if (var_s0 != NULL) {
//                         do {
//                             var_s0->drawMode = 8;
//                             var_s0 = var_s0->next;
//                         } while (var_s0 != NULL);
//                     }
//                     var_s0_2 = arg0->ext.prim;
//                     var_s1 = 0;
//                     do {
//                         temp_v0_2 = 0xC0 - var_s1;
//                         var_s1 += 1;
//                         var_s0_2->tpage = 0x11;
//                         var_s0_2->clut = 0x19F;
//                         var_s0_2->u2 = 4;
//                         var_s0_2->u0 = 4;
//                         var_s0_2->u3 = 0x78;
//                         var_s0_2->u1 = 0x78;
//                         var_s0_2->v1 = 0;
//                         var_s0_2->v0 = 0;
//                         var_s0_2->v3 = 0x28;
//                         var_s0_2->v2 = 0x28;
//                         var_s0_2->x0 = 0xC;
//                         var_s0_2->x2 = 0xC;
//                         var_s0_2->y0 = 0x9D;
//                         var_s0_2->y1 = 0x9D;
//                         var_s0_2->x1 = 0x80;
//                         var_s0_2->x3 = 0x80;
//                         var_s0_2->y2 = 0xC5;
//                         var_s0_2->y3 = 0xC5;
//                         var_s0_2->priority = temp_v0_2;
//                         var_s0_2->drawMode = 8;
//                         temp_s0 = var_s0_2->next;
//                         temp_s0->tpage = 0x11;
//                         temp_s0->clut = 0x19F;
//                         temp_s0->u2 = 8;
//                         temp_s0->u0 = 8;
//                         temp_s0->u3 = 0x7C;
//                         temp_s0->u1 = 0x7C;
//                         temp_s0->v1 = 0x40;
//                         temp_s0->v0 = 0x40;
//                         temp_s0->v3 = 0x68;
//                         temp_s0->v2 = 0x68;
//                         temp_s0->x0 = 0x80;
//                         temp_s0->x2 = 0x80;
//                         temp_s0->y0 = 0x9D;
//                         temp_s0->priority = temp_v0_2;
//                         temp_s0->y1 = 0x9D;
//                         temp_s0->x1 = 0xF4;
//                         temp_s0->x3 = 0xF4;
//                         temp_s0->y2 = 0xC5;
//                         temp_s0->y3 = 0xC5;
//                         temp_s0->drawMode = 8;
//                         var_s0_2 = temp_s0->next;
//                     } while (var_s1 < 2);
//                     var_s1_2 = 0;
//                     arg0->ext.generic.unk88.unk = var_s0_2;
//                     var_s0_2->u2 = 4;
//                     var_s0_2->u0 = 4;
//                     var_s0_2->u3 = 0x78;
//                     var_s0_2->u1 = 0x78;
//                     var_s0_2->tpage = 0x11;
//                     var_s0_2->clut = 0x19D;
//                     var_s0_2->v1 = 0;
//                     var_s0_2->v0 = 0;
//                     var_s0_2->v3 = 0x28;
//                     var_s0_2->v2 = 0x28;
//                     var_s0_2->x0 = 0xC;
//                     var_s0_2->x2 = 0xC;
//                     var_s0_2->y0 = 0x9D;
//                     var_s0_2->y1 = 0x9D;
//                     var_s0_2->x1 = 0x80;
//                     var_s0_2->x3 = 0x80;
//                     var_s0_2->y2 = 0xC5;
//                     var_s0_2->y3 = 0xC5;
//                     var_s0_2->priority = 0xBF;
//                     var_s0_2->drawMode = 8;
//                     temp_s0_2 = var_s0_2->next;
//                     temp_s0_2->clut = 0x19D;
//                     temp_s0_2->tpage = 0x11;
//                     temp_s0_2->u2 = 8;
//                     temp_s0_2->u0 = 8;
//                     temp_s0_2->u3 = 0x7C;
//                     temp_s0_2->u1 = 0x7C;
//                     temp_s0_2->v1 = 0x40;
//                     temp_s0_2->v0 = 0x40;
//                     temp_s0_2->v3 = 0x68;
//                     temp_s0_2->v2 = 0x68;
//                     temp_s0_2->x0 = 0x80;
//                     temp_s0_2->x2 = 0x80;
//                     temp_s0_2->y0 = 0x9D;
//                     temp_s0_2->y1 = 0x9D;
//                     temp_s0_2->x1 = 0xF4;
//                     temp_s0_2->x3 = 0xF4;
//                     temp_s0_2->y2 = 0xC5;
//                     temp_s0_2->y3 = 0xC5;
//                     temp_s0_2->priority = 0xBF;
//                     temp_s0_2->drawMode = 8;
//                     temp_s0_3 = temp_s0_2->next;
//                     arg0->ext.generic.unk84.unk = temp_s0_3;
//                     temp_s0_3->u0 = 0;
//                     temp_s0_3->u1 = 0x40;
//                     temp_s0_3->type = 3;
//                     temp_s0_3->tpage = 0x1A;
//                     temp_s0_3->clut = 0x15F;
//                     temp_s0_3->v0 = 0xC0;
//                     temp_s0_3->v1 = 0xC0;
//                     temp_s0_3->v2 = 0xFF;
//                     temp_s0_3->v3 = 0xFF;
//                     temp_s0_3->y0 = 0x9B;
//                     temp_s0_3->y1 = 0x9B;
//                     temp_s0_3->y2 = 0xC7;
//                     temp_s0_3->y3 = 0xC7;
//                     temp_s0_3->x0 = 0xC;
//                     temp_s0_3->x2 = 0xC;
//                     temp_s0_3->x1 = 0xF4;
//                     temp_s0_3->x3 = 0xF4;
//                     temp_s0_3->r0 = 0x10;
//                     temp_s0_3->g0 = 0x28;
//                     temp_s0_3->u2 = temp_s0_3->u0;
//                     temp_s0_3->u3 = temp_s0_3->u1;
//                     temp_s0_3->b0 = 0;
//                     temp_s0_3->r2 = 8;
//                     temp_s0_3->g2 = 0;
//                     temp_s0_3->b2 = 0x38;
//                     temp_s0_3->priority = 0xB0;
//                     temp_s0_3->drawMode = 0x1D;
//                     temp_s0_3->unk10 = (s32) temp_s0_3->unk4;
//                     temp_s0_3->unk28 = (s32) temp_s0_3->unk1C;
//                     var_s0_3 = temp_s0_3->next;
//                     arg0->ext.factory.parent = var_s0_3;
//                     var_v1 = 0x9D;
//                     do {
//                         temp_a0_2 = var_s1_2 + 0x9E;
//                         temp_a1 = var_s1_2;
//                         var_s1_2 += 1;
//                         var_s0_3->v3 = var_s1_2;
//                         var_s0_3->v2 = var_s1_2;
//                         var_s0_3->y0 = var_v1;
//                         var_s0_3->y1 = var_v1;
//                         var_s0_3->r0 = 0x78;
//                         var_s0_3->g0 = 0x78;
//                         var_s0_3->b0 = 0xA8;
//                         var_s0_3->y2 = temp_a0_2;
//                         var_s0_3->y3 = temp_a0_2;
//                         var_s0_3->v1 = temp_a1;
//                         var_s0_3->v0 = temp_a1;
//                         var_s0_3->priority = 0xC0;
//                         var_s0_3->tpage = 0x11;
//                         var_s0_3->clut = 0x19F;
//                         var_s0_3->x0 = 0xC;
//                         var_s0_3->x2 = 0xC;
//                         var_s0_3->x1 = 0x80;
//                         var_s0_3->x3 = 0x80;
//                         var_s0_3->u0 = 4;
//                         var_s0_3->u2 = 4;
//                         var_s0_3->u3 = 0x78;
//                         var_s0_3->u1 = 0x78;
//                         var_s0_3->drawMode = 0xC;
//                         var_s0_3->unk10 = (s32) var_s0_3->unk4;
//                         var_s0_3->unk1C = (s32) var_s0_3->unk4;
//                         var_s0_3->unk28 = (s32) var_s0_3->unk4;
//                         var_s0_3 = var_s0_3->next;
//                         var_v1 = var_s1_2 + 0x9D;
//                     } while ((s32) var_s1_2 < 0x28);
//                     var_s1_3 = 0;
//                     var_v1_2 = 0x9D;
//                     do {
//                         temp_a0_3 = var_s1_3 + 0x9E;
//                         temp_a1_2 = var_s1_3 + 0x40;
//                         var_s0_3->clut = 0x19F;
//                         var_s0_3->y0 = var_v1_2;
//                         var_s0_3->y1 = var_v1_2;
//                         var_s0_3->r0 = 0x78;
//                         var_s0_3->g0 = 0x78;
//                         var_s0_3->b0 = 0xA8;
//                         temp_a2 = var_s1_3 + 0x41;
//                         var_s0_3->y2 = temp_a0_3;
//                         var_s0_3->y3 = temp_a0_3;
//                         var_s1_3 += 1;
//                         var_s0_3->v1 = temp_a1_2;
//                         var_s0_3->v0 = temp_a1_2;
//                         var_s0_3->priority = 0xC0;
//                         var_s0_3->drawMode = 0xC;
//                         var_s0_3->tpage = 0x11;
//                         var_s0_3->x0 = 0x80;
//                         var_s0_3->x2 = 0x80;
//                         var_s0_3->x1 = 0xF4;
//                         var_s0_3->x3 = 0xF4;
//                         var_s0_3->u0 = 8;
//                         var_s0_3->u2 = 8;
//                         var_s0_3->u3 = 0x7C;
//                         var_s0_3->u1 = 0x7C;
//                         var_s0_3->v3 = temp_a2;
//                         var_s0_3->v2 = temp_a2;
//                         var_s0_3->unk10 = (s32) var_s0_3->unk4;
//                         var_s0_3->unk1C = (s32) var_s0_3->unk4;
//                         var_s0_3->unk28 = (s32) var_s0_3->unk4;
//                         var_s0_3 = var_s0_3->next;
//                         var_v1_2 = var_s1_3 + 0x9D;
//                     } while (var_s1_3 < 0x28);
//                     arg0->ext.generic.unk80.modeS32 = 0x20;
//                 case 1:                             // switch 1
//                     temp_v1 = arg0->step_s;
//                     switch (temp_v1) {
//                         case 0:
//                             temp_v0_3 = arg0->ext.generic.unk80.modeS32;
//                             if (temp_v0_3 != 0) {
//                                 arg0->ext.generic.unk80.modeS32 = temp_v0_3 - 1;
//                             } else {
//                                 temp_s0_4 = arg0->ext.generic.unk84.unk;
//                                 temp_s0_4->unk20 = 0x80;
//                                 temp_s0_4->unk8 = 0x80;
//                                 temp_s0_4->unk2C = 0x80;
//                                 temp_s0_4->unk14 = 0x80;
//                                 temp_s0_4->unk16 = 0xB1;
//                                 temp_s0_4->unkA = 0xB1;
//                                 temp_s0_4->unk2E = 0xB1;
//                                 temp_s0_4->unk22 = 0xB1;
//                                 temp_s0_4->unk32 = 0x15;
// block_78:
// block_79:
//                                 arg0->step_s += 1;
//                             }
//                             break;
//                         case 1:
//                             temp_s0_5 = arg0->ext.generic.unk84.unk;
//                             temp_v0_4 = temp_s0_5->unkA;
//                             var_a0 = 0;
//                             if (temp_v0_4 >= 0x9C) {
//                                 var_a0 = 1;
//                                 temp_v1_2 = temp_v0_4 - 4;
//                                 temp_s0_5->unkA = temp_v1_2;
//                                 temp_s0_5->unk16 = temp_v1_2;
//                                 temp_v0_5 = (u16) temp_s0_5->unk22 + 4;
//                                 temp_s0_5->unk22 = temp_v0_5;
//                                 temp_s0_5->unk2E = temp_v0_5;
//                             }
//                             temp_v0_6 = temp_s0_5->unk8;
//                             var_v0 = var_a0 & 0xFF;
//                             if (temp_v0_6 >= 0xD) {
//                                 temp_v1_3 = temp_v0_6 - 8;
//                                 temp_s0_5->unk8 = temp_v1_3;
//                                 temp_s0_5->unk20 = temp_v1_3;
//                                 temp_v0_7 = (u16) temp_s0_5->unk14 + 8;
//                                 temp_s0_5->unk14 = temp_v0_7;
//                                 temp_s0_5->unk2C = temp_v0_7;
//                                 var_v0 = (var_a0 | 1) & 0xFF;
//                             }
//                             if (var_v0 == 0) {
//                                 arg0->ext.generic.unk80.modeS32 = 0;
//                                 arg0->ext.factory.childId = 0;
//                                 arg0->ext.factory.unk92 = 0;
//                                 goto block_79;
//                             }
//                             break;
//                         case 2:
//                             temp_v0_8 = (u16) arg0->ext.factory.childId + 3;
//                             arg0->ext.factory.childId = temp_v0_8;
//                             var_s1_4 = 0;
//                             if (temp_v0_8 >= 0x80) {
//                                 arg0->step_s += 1;
//                             }
//                             var_s0_4 = arg0->ext.generic.unk88.unk;
//                             var_s0_4->unk32 = 0x75;
// loop_34:
//                             temp_v0_9 = (u8) arg0->ext.stub[0x14];
//                             var_s1_4 += 1;
//                             var_s0_4->unk2A = temp_v0_9;
//                             var_s0_4->unk29 = temp_v0_9;
//                             var_s0_4->unk28 = temp_v0_9;
//                             var_s0_4->unk1E = temp_v0_9;
//                             var_s0_4->unk1D = temp_v0_9;
//                             var_s0_4->unk1C = temp_v0_9;
//                             var_s0_4->unk12 = temp_v0_9;
//                             var_s0_4->unk11 = temp_v0_9;
//                             var_s0_4->unk10 = temp_v0_9;
//                             var_s0_4->unk6 = temp_v0_9;
//                             var_s0_4->unk5 = temp_v0_9;
//                             var_s0_4->unk4 = temp_v0_9;
//                             var_s0_4 = var_s0_4->unk0;
//                             if (var_s1_4 < 2) {
//                                 var_s0_4->unk32 = 0x75;
//                                 goto loop_34;
//                             }
//                             break;
//                         case 3:
//                             temp_v0_10 = (u16) arg0->ext.factory.childId - 2;
//                             arg0->ext.factory.childId = temp_v0_10;
//                             var_s1_5 = 0;
//                             if (temp_v0_10 & 0x8000) {
//                                 arg0->ext.factory.childId = 0;
//                             }
//                             var_s0_5 = arg0->ext.generic.unk88.unk;
//                             do {
//                                 var_s0_5->unk32 = 0x35;
//                                 temp_v0_11 = (u8) arg0->ext.stub[0x14];
//                                 var_s1_5 += 1;
//                                 var_s0_5->unk2A = temp_v0_11;
//                                 var_s0_5->unk29 = temp_v0_11;
//                                 var_s0_5->unk28 = temp_v0_11;
//                                 var_s0_5->unk1E = temp_v0_11;
//                                 var_s0_5->unk1D = temp_v0_11;
//                                 var_s0_5->unk1C = temp_v0_11;
//                                 var_s0_5->unk12 = temp_v0_11;
//                                 var_s0_5->unk11 = temp_v0_11;
//                                 var_s0_5->unk10 = temp_v0_11;
//                                 var_s0_5->unk6 = temp_v0_11;
//                                 var_s0_5->unk5 = temp_v0_11;
//                                 var_s0_5->unk4 = temp_v0_11;
//                                 var_s0_5 = var_s0_5->unk0;
//                             } while (var_s1_5 < 2);
//                             temp_v0_12 = arg0->ext.factory.childId;
//                             if (temp_v0_12 != 0) {
//                                 var_v0_2 = 0x80 - temp_v0_12;
//                             } else {
//                                 var_v0_2 = (u16) arg0->ext.factory.unk92 + 4;
//                             }
//                             arg0->ext.factory.unk92 = var_v0_2;
//                             var_s1_6 = 0;
//                             if (arg0->ext.factory.unk92 >= 0x80) {
//                                 arg0->ext.factory.unk92 = 0x80;
//                                 arg0->step_s += 1;
//                             }
//                             var_s0_6 = arg0->ext.prim;
//                             do {
//                                 var_s0_6->drawMode = 0x35;
//                                 temp_v0_13 = (u8) arg0->ext.stub[0x16];
//                                 var_s1_6 += 1;
//                                 var_s0_6->b3 = temp_v0_13;
//                                 var_s0_6->g3 = temp_v0_13;
//                                 var_s0_6->r3 = temp_v0_13;
//                                 var_s0_6->b2 = temp_v0_13;
//                                 var_s0_6->g2 = temp_v0_13;
//                                 var_s0_6->r2 = temp_v0_13;
//                                 var_s0_6->b1 = temp_v0_13;
//                                 var_s0_6->g1 = temp_v0_13;
//                                 var_s0_6->r1 = temp_v0_13;
//                                 var_s0_6->b0 = temp_v0_13;
//                                 var_s0_6->g0 = temp_v0_13;
//                                 var_s0_6->r0 = temp_v0_13;
//                                 var_s0_6 = var_s0_6->next;
//                             } while (var_s1_6 < 2);
//                             var_s1_7 = 0;
//                             var_s0_6->drawMode = 0x15;
// loop_48:
//                             temp_v0_14 = (u8) arg0->ext.stub[0x16];
//                             var_s1_7 += 1;
//                             var_s0_6->b3 = temp_v0_14;
//                             var_s0_6->g3 = temp_v0_14;
//                             var_s0_6->r3 = temp_v0_14;
//                             var_s0_6->b2 = temp_v0_14;
//                             var_s0_6->g2 = temp_v0_14;
//                             var_s0_6->r2 = temp_v0_14;
//                             var_s0_6->b1 = temp_v0_14;
//                             var_s0_6->g1 = temp_v0_14;
//                             var_s0_6->r1 = temp_v0_14;
//                             var_s0_6->b0 = temp_v0_14;
//                             var_s0_6->g0 = temp_v0_14;
//                             var_s0_6->r0 = temp_v0_14;
//                             var_s0_6 = var_s0_6->next;
//                             if (var_s1_7 < 2) {
//                                 var_s0_6->drawMode = 0x15;
//                                 goto loop_48;
//                             }
//                             break;
//                         case 4:
//                             arg0->ext.generic.unk88.unk->unk32 = 8;
//                             arg0->ext.generic.unk80.modeS32 = 0x40;
//                             arg0->step = 2;
//                             arg0->step_s = 0;
//                             D_8003BE40 = 1;
//                             break;
//                     }
//                 default:                            // switch 1
// block_84:
//                     FntPrint(&D_8019B3C0, arg0->step);
//                     FntPrint(&D_8019B3D0, arg0->step_s);
//                     return;
//                 }
//             }
// block_83:
//             DestroyEntity(arg0);
//             return;
//         case 2:                                     // switch 1
//             temp_v0_15 = arg0->ext.generic.unk80.modeS32 - 1;
//             arg0->ext.generic.unk80.modeS32 = temp_v0_15;
//             if (temp_v0_15 == 0) {
//                 arg0->step_s = 0;
//                 arg0->step = 3;
//             }
//             goto block_84;
//         case 3:                                     // switch 1
//             temp_v1_4 = arg0->step_s;
//             if (temp_v1_4 != 1) {
//                 if ((s32) temp_v1_4 < 2) {
//                     var_s1_8 = 0;
//                     if (temp_v1_4 != 0) {

//                     } else {
//                         var_s0_7 = arg0->ext.prim->next->next;
//                         do {
//                             var_s0_7->drawMode = 0x15;
//                             temp_v0_16 = arg0->ext.stub[0x16];
//                             var_s1_8 += 1;
//                             var_s0_7->b3 = temp_v0_16;
//                             var_s0_7->g3 = temp_v0_16;
//                             var_s0_7->r3 = temp_v0_16;
//                             var_s0_7->b2 = temp_v0_16;
//                             var_s0_7->g2 = temp_v0_16;
//                             var_s0_7->r2 = temp_v0_16;
//                             var_s0_7->b1 = temp_v0_16;
//                             var_s0_7->g1 = temp_v0_16;
//                             var_s0_7->r1 = temp_v0_16;
//                             var_s0_7->b0 = temp_v0_16;
//                             var_s0_7->g0 = temp_v0_16;
//                             var_s0_7->r0 = temp_v0_16;
//                             var_s0_7 = var_s0_7->next;
//                         } while (var_s1_8 < 2);
//                         temp_v0_17 = (u16) arg0->ext.factory.unk92 - 4;
//                         arg0->ext.factory.unk92 = temp_v0_17;
//                         if (temp_v0_17 & 0x8000) {
//                             arg0->ext.factory.unk92 = 0;
//                             goto block_79;
//                         }
//                     }
//                     goto block_84;
//                 }
//                 if (temp_v1_4 != 2) {
//                     if (temp_v1_4 != temp_a0) {
//                         goto block_84;
//                     }
//                     var_s0_8 = arg0->ext.factory.parent;
//                     if (var_s0_8 != NULL) {
//                         do {
//                             func_801AD0EC((?* ) var_s0_8);
//                             var_s0_8 = var_s0_8->next;
//                         } while (var_s0_8 != NULL);
//                     }
//                     temp_s0_6 = arg0->ext.generic.unk84.unk;
//                     temp_v0_18 = (u16) temp_s0_6->y0 + 2;
//                     temp_s0_6->y0 = temp_v0_18;
//                     temp_s0_6->y1 = temp_v0_18;
//                     temp_s0_6->x0 = (u16) temp_s0_6->x0 - 2;
//                     temp_v0_19 = (u16) temp_s0_6->y2 - 2;
//                     temp_s0_6->y2 = temp_v0_19;
//                     temp_s0_6->y3 = temp_v0_19;
//                     temp_s0_6->x2 = (u16) temp_s0_6->x2 - 2;
//                     temp_s0_6->x1 = (u16) temp_s0_6->x1 + 2;
//                     temp_s0_6->x3 = (u16) temp_s0_6->x3 + 2;
//                     if (temp_s0_6->y2 < temp_s0_6->y0) {
//                         goto block_83;
//                     }
//                     goto block_84;
//                 }
//                 var_s0_9 = arg0->ext.factory.parent;
//                 if (var_s0_9 != NULL) {
//                     do {
//                         func_801AD0EC((?* ) var_s0_9);
//                         var_s0_9 = var_s0_9->next;
//                     } while (var_s0_9 != NULL);
//                 }
//                 temp_v0_20 = arg0->ext.generic.unk80.modeS32 - 1;
//                 arg0->ext.generic.unk80.modeS32 = temp_v0_20;
//                 if (temp_v0_20 == 0) {
//                     goto block_78;
//                 }
//                 goto block_84;
//             }
//             var_s0_10 = arg0->ext.prim;
//             var_s1_9 = 1;
//             do {
//                 var_s0_10->drawMode = 8;
//                 var_s0_10 = var_s0_10->next;
//                 var_s1_9 += 1;
//             } while (var_s1_9 < 4);
//             var_s0_11 = arg0->ext.factory.parent;
//             var_s1_10 = 0;
//             var_a1 = 0 * 4;
//             do {
//                 var_s0_11->r0 = 0x80;
//                 var_s0_11->g0 = 0x80;
//                 var_s0_11->b0 = 0x80;
//                 var_s1_10 += 1;
//                 var_s0_11->unk10 = (s32) var_s0_11->unk4;
//                 var_s0_11->unk1C = (s32) var_s0_11->unk4;
//                 var_s0_11->unk28 = (s32) var_s0_11->unk4;
//                 var_s0_11->p1 = var_a1;
//                 var_s0_11->p2 = Random() & 3;
//                 var_s0_11->p3 = 0;
//                 var_s0_11->drawMode = 0x35;
//                 var_s0_11 = var_s0_11->next;
//                 var_a1 = var_s1_10 * 4;
//             } while (var_s1_10 < 0x14);
//             var_s1_11 = 0;
//             do {
//                 temp_v0_21 = 0x14 - var_s1_11;
//                 var_s1_11 += 1;
//                 var_s0_11->r0 = 0x80;
//                 var_s0_11->g0 = 0x80;
//                 var_s0_11->b0 = 0x80;
//                 var_s0_11->unk10 = (s32) var_s0_11->unk4;
//                 var_s0_11->unk1C = (s32) var_s0_11->unk4;
//                 var_s0_11->unk28 = (s32) var_s0_11->unk4;
//                 var_s0_11->p1 = (u8) -(temp_v0_21 * 4);
//                 var_s0_11->p2 = Random() & 3;
//                 var_s0_11->drawMode = 0x35;
//                 var_s0_11->p3 = 0;
//                 var_s0_11 = var_s0_11->next;
//             } while (var_s1_11 < 0x14);
//             var_s1_12 = 0;
//             var_a1_2 = 0 * 4;
//             do {
//                 var_s0_11->r0 = 0x80;
//                 var_s0_11->g0 = 0x80;
//                 var_s0_11->b0 = 0x80;
//                 var_s1_12 += 1;
//                 var_s0_11->unk10 = (s32) var_s0_11->unk4;
//                 var_s0_11->unk1C = (s32) var_s0_11->unk4;
//                 var_s0_11->unk28 = (s32) var_s0_11->unk4;
//                 var_s0_11->p1 = var_a1_2;
//                 var_s0_11->p2 = Random() & 3;
//                 var_s0_11->p3 = 0;
//                 var_s0_11->drawMode = 0x35;
//                 var_s0_11 = var_s0_11->next;
//                 var_a1_2 = var_s1_12 * 4;
//             } while (var_s1_12 < 0x14);
//             var_s1_13 = 0;
//             do {
//                 temp_v0_22 = 0x14 - var_s1_13;
//                 var_s1_13 += 1;
//                 var_s0_11->r0 = 0x80;
//                 var_s0_11->g0 = 0x80;
//                 var_s0_11->b0 = 0x80;
//                 var_s0_11->unk10 = (s32) var_s0_11->unk4;
//                 var_s0_11->unk1C = (s32) var_s0_11->unk4;
//                 var_s0_11->unk28 = (s32) var_s0_11->unk4;
//                 var_s0_11->p1 = (u8) -(temp_v0_22 * 4);
//                 var_s0_11->p2 = Random() & 3;
//                 var_s0_11->drawMode = 0x35;
//                 var_s0_11->p3 = 0;
//                 var_s0_11 = var_s0_11->next;
//             } while (var_s1_13 < 0x14);
//             arg0->ext.generic.unk80.modeS32 = 0x70;
//             goto block_79;
//     }
// }
// Warning: struct draculaPrimitive is not defined (only forward-declared)
//#endif
//#include "../e_stage_name.h"

//NOTE: The remaining functions are all contained in "../prim_helpers.h" but
//      UnkPrimHelper and PrimDecreaseBrightness don't match.
INCLUDE_ASM("st/chi/nonmatchings/collision", func_801ADF40);    // UnkPrimHelper()
//INCLUDE_ASM("st/chi/nonmatchings/collision", func_801AE328);    // UpdateAnimation()
s32 UpdateAnimation(u8* texAnimations, Primitive* prim) {
    s16 sp0;
    s16 tempUv;
    u8 new_var;
    u8* nextAnimation = texAnimations + ((prim->p1 * 5) & 0xFF);
    u8 new_var2;
    s32 retVal = 0;

    if (prim->p2 == 0) {
        if (*nextAnimation) {
            if (*nextAnimation == 0xFF) {
                return 0;
            }
            retVal = 0x80;
            prim->p2 = nextAnimation[0];
            ++nextAnimation;
            tempUv = nextAnimation[0] + (nextAnimation[1] << 8);
            nextAnimation += 2;
            sp0 = nextAnimation[0] + (nextAnimation[1] << 8);
            LOH(prim->u0) = tempUv;
            LOH(prim->u1) = tempUv + *((u8*)(&sp0));
            new_var = *((u8*)&sp0 + 1);
            LOH(prim->u3) = tempUv + sp0;
            LOH(prim->u2) = tempUv + (new_var << 8);
            ++prim->p1;
        } else {
            prim->p1 = 0;
            prim->p2 = 0;
            prim->p2 = texAnimations[0];
            tempUv = texAnimations[1] + (texAnimations[2] << 8);
            sp0 = texAnimations[3] + (texAnimations[4] << 8);
            LOH(prim->u0) = tempUv;
            LOH(prim->u1) = tempUv + (*(u8*)&sp0);
            new_var2 = *((u8*)&sp0 + 1);
            LOH(prim->u3) = tempUv + sp0;
            LOH(prim->u2) = tempUv + (new_var2 << 8);
            ++prim->p1;
            return 0;
        }
    }

    retVal |= 1;
    --prim->p2;
    return (retVal | 1) & 0xFF;
}
//INCLUDE_ASM("st/chi/nonmatchings/collision", func_801AE478);    // FindFirstUnkPrim()
Primitive* FindFirstUnkPrim(Primitive* poly) {
    while (poly != NULL) {
        if (poly->p3 != 0) {
            poly = poly->next;
        } else {
            return poly;
        }
    }
    return NULL;
}
//INCLUDE_ASM("st/chi/nonmatchings/collision", func_801AE4A8);    // FindFirstUnkPrim2()
Primitive* FindFirstUnkPrim2(Primitive* prim, u8 index) {

    Primitive* ret;
    int i;

    for (; prim; prim = prim->next) {
        if (!prim->p3) {
            ret = prim;
            for (i = 1; i < index; ++i) {
                prim = prim->next;
                if (!prim) {
                    return NULL;
                }
                if (prim->p3) {
                    break;
                }
            }
            if (i == index) {
                return ret;
            }
        }
    }
    return NULL;
}
//INCLUDE_ASM("st/chi/nonmatchings/collision", func_801AE524);    // PrimToggleVisibility()
Primitive* PrimToggleVisibility(Primitive* firstPrim, s32 count) {
    Primitive* prim;
    s8 isVisible;
    s32 i;

    if (firstPrim->p3) {
        firstPrim->p3 = 0;
    } else {
        firstPrim->p3 = 1;
    }

    prim = firstPrim;
    for (i = 0; i < count; i++) {
        if (prim->p3) {
            prim->drawMode &= ~DRAW_HIDE;
            isVisible = false;
        } else {
            prim->drawMode |= DRAW_HIDE;
            isVisible = true;
        }

        prim = prim->next;
        if (prim == NULL)
            return 0;
        prim->p3 = isVisible;
    }

    return prim;
}
//INCLUDE_ASM("st/chi/nonmatchings/collision", func_801AE5AC);    // PrimResetNext()
void PrimResetNext(Primitive* prim) {
    prim->p1 = 0;
    prim->p2 = 0;
    prim->p3 = 0;
    prim->next->x1 = 0;
    prim->next->y1 = 0;
    prim->next->y0 = 0;
    prim->next->x0 = 0;
    prim->next->clut = 0;
    LOHU(prim->next->u0) = 0;
    LOHU(prim->next->b1) = 0;
    LOHU(prim->next->r1) = 0;
    LOHU(prim->next->u1) = 0;
    prim->next->tpage = 0;
    LOHU(prim->next->r2) = 0;
    LOHU(prim->next->b2) = 0;
    prim->next->u2 = 0;
    prim->next->v2 = 0;
    prim->next->r3 = 0;
    prim->next->b3 = 0;
    prim->next->x2 = 0;
    prim->next->y2 = 0;
}
//TODO: Find first "init not started" prim?
//INCLUDE_ASM("st/chi/nonmatchings/collision", func_801AE68C);    // UnkPolyFunc2()
void UnkPolyFunc2(Primitive* prim) {
    PrimResetNext(prim);
    prim->p3 = 8;
    prim->next->p3 = 1;
    prim->next->type = PRIM_LINE_G2;
    prim->next->drawMode = 0xA;
}
//INCLUDE_ASM("st/chi/nonmatchings/collision", func_801AE6E0);    // UnkPolyFunc0()
void UnkPolyFunc0(Primitive* prim) {
    prim->p3 = 0;
    prim->drawMode = DRAW_HIDE;
    prim->next->p3 = 0;
    prim->next->type = PRIM_GT4;
    prim->next->drawMode = DRAW_HIDE;
}
INCLUDE_ASM("st/chi/nonmatchings/collision", func_801AE70C);    // PrimDecreaseBrightness()
//#include "../prim_helpers.h"
