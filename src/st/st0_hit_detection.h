// SPDX-License-Identifier: AGPL-3.0-or-later
#include <stage.h>

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
    0x02, 0x04, 0x03, 0x05, 0x06, 0x07, 0x08, 0x00, 0x02, 0x01,
};

static u16 g_eDamageDisplayClut[] = {
    PAL_DRA(0x1B2), PAL_DRA(0x1B3), PAL_DRA(0x1B6), PAL_DRA(0x1B7),
    PAL_DRA(0x1B4), PAL_DRA(0x1B5), PAL_DRA(0x1B0), PAL_DRA(0x1B1),
};

// Warning: This is different from HitDetection in other overlays.
// Some of the logic is removed since it doesn't apply in prologue.
// Attempting to de-duplicate this would involve a lot of #ifdef.
void OVL_EXPORT(HitDetection)(void) {
    s32* scratchpad_1;
    s32* scratchpad_2;
    Entity* iterEnt1;
    Entity* iterEnt2;
    Entity* otherEntity;
    Entity* entFrom5C;
    Primitive* prim;
    EnemyDef* sp3C;
    u16* randCompare;
    s32 hitboxWidth;
    s32 yCoord1;
    u32 hitboxCheck1;
    s16 xCoord;
    s16 yCoord2;
    u16 miscVar3;
    u16 i;
    u16 miscVar1;
    u16 hitboxCheck2;
    u8 uselessVar;
#ifdef VERSION_PC
    u8 sp[SP_LEN];
#endif
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
                        iterEnt1->hitParams = iterEnt2->hitEffect;
                        miscVar2 = 0xFF;
                        break;
                    } else {
                        hitboxCheck2 = (u16)*scratchpad_2++ - (u16)xCoord;
                        hitboxCheck1 = hitboxWidth + *scratchpad_2++;
                        hitboxCheck2 += hitboxCheck1;
                        hitboxCheck1 *= 2;
                        if (hitboxCheck2 <= hitboxCheck1) {
                            hitboxCheck2 = (u16)*scratchpad_2++ - (u16)yCoord2;
                            hitboxCheck1 = yCoord1 + *scratchpad_2++;
                            hitboxCheck2 += hitboxCheck1;
                            hitboxCheck1 *= 2;
                            if (hitboxCheck2 <= hitboxCheck1) {
                                // reusing the i variable here, maybe can be a
                                // different var
                                i = iterEnt2->hitEffect;
                                if (!(iterEnt2->flags & iterEnt1->flags &
                                      FLAG_UNK_100000)) {
                                    // Probably has to stay generic since
                                    // iterEnt2 could be any entity?
                                    iterEnt2->unkB8 = iterEnt1;
                                    iterEnt2->hitFlags = 1;
                                    if ((i == 12) &&
                                        (iterEnt1->flags & FLAG_UNK_8000)) {
                                        iterEnt2->hitFlags = 2;
                                    }
                                    if ((i == 10) &&
                                        (iterEnt1->flags & FLAG_UNK_4000)) {
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
                if (hitboxCheck2 <= hitboxCheck1) {
                    hitboxCheck2 = (u16)*scratchpad_2++ - (u16)yCoord2;
                    hitboxCheck1 = yCoord1 + *scratchpad_2++;
                    hitboxCheck2 += hitboxCheck1;
                    hitboxCheck1 *= 2;
                    if (hitboxCheck2 <= hitboxCheck1) {
                        iterEnt2->unkB8 = iterEnt1;
                        iterEnt2->hitFlags = 1;
                        iterEnt2->hitParams = iterEnt1->attackElement;
                        iterEnt2->hitPoints = iterEnt1->attack;
                        iterEnt1->hitParams = iterEnt2->hitEffect;
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
            } else {
                entFrom5C = iterEnt1;
            }
            if (!(entFrom5C->flags & FLAG_DEAD) && miscVar2) {
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
                                prim->x0 = prim->x2 =
                                    xCoord - 13 + (Random() & 7) - 3;
                                prim->x1 = prim->x3 = prim->x0 + 0x20;
                                prim->y0 = prim->y1 =
                                    yCoord2 - 10 + (Random() & 7) - 3;
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
                        if (miscVar1 == 0x4000) {
                            miscVar1 = 0;
                        }
                        if ((g_Status.relics[RELIC_SPIRIT_ORB] & 2) &&
                            !(entFrom5C->flags & FLAG_KEEP_ALIVE_OFFCAMERA)) {
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
                            } else {
                                miscVar2 = 0;
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
                        g_api.PlaySfx(SFX_RIC_WHIP_HIT);
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
                    }
                    if (entFrom5C->hitPoints > 0) {
                        otherEntity = entFrom5C;
                        miscVar3 = iterEnt2->enemyId;
                        do {
                            otherEntity->unk6D[miscVar3] =
                                iterEnt2->nFramesInvincibility;
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
                        uselessVar = ((u32)entFrom5C->flags >> 4) & 7;
                        continue;
                    }
                }
                PreventEntityFromRespawning(entFrom5C);
                g_api.func_800FE044(g_api.enemyDefs[entFrom5C->enemyId].exp,
                                    g_api.enemyDefs[miscVar1].level);
                if ((entFrom5C->flags & FLAG_UNK_1000) &&
                    (g_Status.killCount < 999999)) {
                    g_Status.killCount++;
                }
                if (entFrom5C->flags & (FLAG_UNK_800 | FLAG_UNK_400)) {
                    miscVar3 = rand() & 0xFF;
                    if (miscVar3 < 32) {
                        otherEntity =
                            AllocEntity(&g_Entities[160], &g_Entities[192]);
                        if (otherEntity != NULL) {
                            miscVar3 = rand() & 0xFF;
                            if (miscVar3 <
                                g_api.enemyDefs[miscVar1].rareItemDropRate) {
                                miscVar3 = 1;
                            } else {
                                miscVar3 -=
                                    g_api.enemyDefs[miscVar1].rareItemDropRate;
                                if (miscVar3 < g_api.enemyDefs[miscVar1]
                                                   .uncommonItemDropRate) {
                                    miscVar3 = 0;
                                } else {
                                    miscVar3 = 2;
                                }
                            }
                            if (miscVar3 >= 0x80) {
                                miscVar3 -= 0x80;
                                // Create an EntityEquipItemDrop
                                CreateEntityFromEntity(
                                    E_EQUIP_ITEM_DROP, iterEnt1, otherEntity);
                            } else {
                                // Create an EntityPrizeDrop
                                CreateEntityFromEntity(
                                    E_PRIZE_DROP, iterEnt1, otherEntity);
                            }
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
                otherEntity = entFrom5C;
                miscVar3 = iterEnt2->enemyId;
                do {
                    if (iterEnt1->hitPoints == 0x7FFF) {
                        if (otherEntity->hitPoints == 0x7FFF) {
                            otherEntity->unk6D[miscVar3] =
                                iterEnt2->nFramesInvincibility;
                        }
                    } else {
                        otherEntity->unk6D[miscVar3] =
                            iterEnt2->nFramesInvincibility;
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
            if (miscVar2 > 6) {
                prim->drawMode = DRAW_HIDE;
            } else {
                prim->p1 = miscVar2;
            }
        }
    }
}
