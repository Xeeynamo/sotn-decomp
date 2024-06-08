#include "st0.h"

// Warning: This is different from HitDetection in other overlays.
// Some of the logic is removed since it doesn't apply in prologue.
// Attempting to de-duplicate this would involve a lot of #ifdef.
void HitDetection(void) {
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
                        iterEnt1->unk44 = iterEnt2->hitEffect;
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
                                i = iterEnt2->hitEffect;
                                if (!(iterEnt2->flags & iterEnt1->flags &
                                      FLAG_UNK_100000)) {
                                    // Probably has to stay generic since
                                    // iterEnt2 could be any entity?
                                    iterEnt2->ext.generic.unkB8.entityPtr =
                                        iterEnt1;
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
                        iterEnt2->ext.player.unkB8 = iterEnt1;
                        iterEnt2->hitFlags = 1;
                        iterEnt2->unk44 = iterEnt1->attackElement;
                        iterEnt2->hitPoints = iterEnt1->attack;
                        iterEnt1->unk44 = iterEnt2->hitEffect;
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
            } else {
                entFrom5C = iterEnt1;
            }
            if (!(entFrom5C->flags & FLAG_DEAD) && miscVar2) {
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
                        if (miscVar1 == 0x4000) {
                            miscVar1 = 0;
                        }
                        if ((g_Status.relics[RELIC_SPIRIT_ORB] & 2) &&
                            !(entFrom5C->flags & FLAG_UNK_04000000)) {
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
                        g_api.PlaySfx(SFX_RICHTER_ATTACK_HIT);
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
                        uselessVar = ((u32)entFrom5C->flags >> 4) & 7 & 0xFF;
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
                                    10, iterEnt1, otherEntity);
                            } else {
                                // Create an EntityPrizeDrop
                                CreateEntityFromEntity(
                                    3, iterEnt1, otherEntity);
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
            if (miscVar2 >= 7) {
                prim->drawMode = DRAW_HIDE;
            } else {
                prim->p1 = miscVar2;
            }
        }
    }
}

#include "../entity_damage_display.h"

#include "../libstage.h"

#include "../entity_red_door.h"

#include "../entity.h"

u8 func_801B4AF0(u8 frames[], Entity* self, u8 arg2) {
    u16 animFrameStart = self->animFrameIdx * 2;
    u8* var_s1 = &frames[animFrameStart];
    s16 var_a1 = 0;

    if (self->animFrameDuration == 0) {
        if (*var_s1 != 0) {
            if (*var_s1 == 0xFF) {
                return 0;
            }
            self->animFrameDuration = *var_s1++ + (u8)self->ext.stub[0x3F];
            self->animCurFrame = *var_s1++;
            self->animFrameIdx++;
            var_a1 = 128;
        } else {
            var_s1 = frames;
            self->animFrameIdx = 0;
            self->animFrameDuration = 0;
            self->ext.stub[0x3F] = (arg2 * Random()) >> 8;
            self->animFrameDuration = *var_s1++ + (u8)self->ext.stub[0x3F];
            self->animCurFrame = *var_s1;
            self->animFrameIdx++;
            return 0;
        }
    }
    self->animFrameDuration--;
    self->animCurFrame = var_s1[-1];
    var_a1 |= 1;
    return var_a1;
}

// Absolute distance from g_CurrentEntity to the player in the X Axis
s16 GetDistanceToPlayerX(void) {
    s16 xDistance = g_CurrentEntity->posX.i.hi - PLAYER.posX.i.hi;

    if (xDistance < 0) {
        xDistance = -xDistance;
    }
    return xDistance;
}

// Absolute distance from g_CurrentEntity to the player in the Y Axis
s32 GetDistanceToPlayerY(void) {
    s32 yDistance = g_CurrentEntity->posY.i.hi - PLAYER.posY.i.hi;

    if (yDistance < 0) {
        yDistance = -yDistance;
    }
    return yDistance;
}

s32 GetSideToPlayer(void) {
    s16 side = g_CurrentEntity->posX.i.hi > PLAYER.posX.i.hi;

    if (g_CurrentEntity->posY.i.hi > PLAYER.posY.i.hi) {
        side |= 2;
    }
    return side;
}

void MoveEntity(void) {
    g_CurrentEntity->posX.val += g_CurrentEntity->velocityX;
    g_CurrentEntity->posY.val += g_CurrentEntity->velocityY;
}

void FallEntity(void) {
    if (g_CurrentEntity->velocityY < FALL_TERMINAL_VELOCITY) {
        g_CurrentEntity->velocityY += FALL_GRAVITY;
    }
}

u8 func_801B4D18(void) {
    u8 unkState;
    Entity* entity;

    MoveEntity();
    FallEntity();

    entity = g_CurrentEntity;

    if (unkState & 1) {
        entity->velocityY = 0;
    }

    return unkState;
}

s32 func_801B4D5C(u16* sensors) {
    Collider col;
    Collider colBack;
    s16 x;
    s16 y;
    s16 i;

    MoveEntity();
    FallEntity();
    if (g_CurrentEntity->velocityY >= 0) {
        x = g_CurrentEntity->posX.i.hi;
        y = g_CurrentEntity->posY.i.hi;
        for (i = 0; i < 4; i++) {
            x += *sensors++;
            y += *sensors++;
            g_api.CheckCollision(x, y, &col, 0);
            if (col.effects & EFFECT_UNK_8000) {
                if (i == 1) {
                    if (col.effects & EFFECT_SOLID) {
                        g_api.CheckCollision(x, y - 8, &colBack, 0);
                        if (!(colBack.effects & EFFECT_SOLID)) {
                            g_CurrentEntity->posY.i.hi =
                                (u16)g_CurrentEntity->posY.i.hi + 4 + col.unk18;
                            g_CurrentEntity->velocityX = 0;
                            g_CurrentEntity->velocityY = 0;
                            g_CurrentEntity->flags &= ~FLAG_UNK_10000000;
                            return 1;
                        }
                    }
                    continue;
                }
            }
            if (col.effects & EFFECT_NOTHROUGH && i != 1) {
                if (col.effects & EFFECT_QUICKSAND) {
                    g_CurrentEntity->flags &= ~FLAG_UNK_10000000;
                    return 4;
                }
                g_api.CheckCollision(x, y - 8, &colBack, 0);
                if (!(colBack.effects & EFFECT_SOLID)) {
                    g_CurrentEntity->posY.i.hi =
                        g_CurrentEntity->posY.i.hi + col.unk18;
                    g_CurrentEntity->velocityX = 0;
                    g_CurrentEntity->velocityY = 0;
                    g_CurrentEntity->flags &= ~FLAG_UNK_10000000;
                    return 1;
                }
            }
        }
    }
    g_CurrentEntity->flags |= FLAG_UNK_10000000;
    return 0;
}

INCLUDE_ASM("st/st0/nonmatchings/31CA0", func_801B4FD4);

INCLUDE_ASM("st/st0/nonmatchings/31CA0", func_801B51E4);

Entity* AllocEntity(Entity* start, Entity* end) {
    Entity* current = start;
    while (current < end) {
        if (current->entityId == E_NONE) {
            DestroyEntity(current);
            return current;
        }

        current++;
    }
    return NULL;
}

s32 func_801B542C(u8 arg0, s16 arg1) { return D_80181990[arg0] * arg1; }

s16 func_801B5458(u8 arg0) { return D_80181990[arg0]; }

void func_801B5474(s32 arg0, s16 arg1) {
    g_CurrentEntity->velocityX = func_801B542C(arg0, arg1);
    g_CurrentEntity->velocityY = func_801B542C(arg0 - 0x40, arg1);
}

u8 func_801B54E0(s16 arg0, s16 arg1) {
    return (ratan2(arg1, arg0) >> 4) + 0x40;
}

u8 func_801B5518(Entity* arg0, Entity* arg1) {
    s16 a = arg1->posX.i.hi - arg0->posX.i.hi;
    s16 b = arg1->posY.i.hi - arg0->posY.i.hi;
    return func_801B54E0(a, b);
}

u8 func_801B5560(s32 arg0, s32 arg1) {
    s16 a = (arg0 - (u16)g_CurrentEntity->posX.i.hi);
    s16 b = (arg1 - (u16)g_CurrentEntity->posY.i.hi);
    return func_801B54E0(a, b);
}

#include "../adjust_value_within_threshold.h"

#include "../unk_entity_func0.h"

u16 func_801B568C(s16 x, s16 y) { return ratan2(y, x); }

u16 GetAngleBetweenEntities(Entity* a, Entity* b) {
    s32 diffX = b->posX.i.hi - a->posX.i.hi;
    s32 diffY = b->posY.i.hi - a->posY.i.hi;
    return ratan2(diffY, diffX);
}

u16 func_801B56F4(s32 x, s32 y) {
    s16 diffX = x - (u16)g_CurrentEntity->posX.i.hi;
    s16 diffY = y - (u16)g_CurrentEntity->posY.i.hi;
    return ratan2(diffY, diffX);
}

u16 GetNormalizedAngle(u16 arg0, s16 arg1, s16 arg2) {
    u16 temp_a2 = arg2 - arg1;
    u16 ret;

    if (temp_a2 & 0x800) {
        ret = temp_a2 & 0x7FF;
    } else {
        ret = temp_a2;
    }

    if (ret > arg0) {
        if (temp_a2 & 0x800) {
            ret = arg1 - arg0;
        } else {
            ret = arg1 + arg0;
        }

        return ret;
    }

    return arg2;
}

void SetStep(u8 step) {
    g_CurrentEntity->step = step;
    g_CurrentEntity->step_s = 0;
    g_CurrentEntity->animFrameIdx = 0;
    g_CurrentEntity->animFrameDuration = 0;
}

void SetSubStep(u8 step_s) {
    g_CurrentEntity->step_s = step_s;
    g_CurrentEntity->animFrameIdx = 0;
    g_CurrentEntity->animFrameDuration = 0;
}

void func_801B57D0(u16 params) {
    Entity* current;

    if (params == 0xFF) {
        DestroyEntity(g_CurrentEntity);
        return;
    }
    current = g_CurrentEntity;
    g_CurrentEntity->entityId = E_EXPLOSION;
    g_CurrentEntity->pfnUpdate = EntityExplosion;
    g_CurrentEntity->drawFlags = 0;
    current->params = params;
    current->animCurFrame = 0;
    g_CurrentEntity->step = 0;
    g_CurrentEntity->step_s = 0;
}

#include "../init_entity.h"

void EntityDummy(Entity* arg0) {
    if (arg0->step == 0) {
        arg0->step++;
    }
}

s32 func_801B5970(u16* hitSensors, s16 sensorCount) {
    Collider collider;
    s16 i;
    s32 velocityX;
    u16 temp_a1;
    s16 x;
    s16 y;

    velocityX = g_CurrentEntity->velocityX;
    if (velocityX != 0) {
        x = g_CurrentEntity->posX.i.hi;
        y = g_CurrentEntity->posY.i.hi;
        for (i = 0; i < sensorCount; i++) {
            if (velocityX < 0) {
                s16 newX = x + *hitSensors++;
                x = newX;
            } else {
                s16 newX = x - *hitSensors++;
                x = newX;
            }

            y += *hitSensors++;
            g_api.CheckCollision(x, y, &collider, 0);
            if (collider.effects & 2 &&
                ((!(collider.effects & 0x8000)) || (i != 0))) {
                return 2;
            }
        }
        return 0;
    }
}

void func_801B5A98(u16* hitSensors, s16 sensorCount) {
    Collider collider;
    s16 i;
    s32 velocityX;
    s16 x;
    s16 y;

    velocityX = g_CurrentEntity->velocityX;
    if (velocityX == 0)
        return;
    x = g_CurrentEntity->posX.i.hi;
    y = g_CurrentEntity->posY.i.hi;
    for (i = 0; i < sensorCount; i++) {
        if (velocityX < 0) {
            x = x + *hitSensors++;
        } else {
            x = x - *hitSensors++;
        }

        y += *hitSensors++;
        g_api.CheckCollision(x, y, &collider, 0);
        if (collider.effects & 2 && (!(collider.effects & 0x8000) || i != 0)) {
            if (velocityX < 0) {
                g_CurrentEntity->posX.i.hi += collider.unk1C;
            } else {
                g_CurrentEntity->posX.i.hi += collider.unk14;
            }
            return;
        }
    }
}

INCLUDE_ASM("st/st0/nonmatchings/31CA0", func_801B5BF0);

#include "../replace_breakable_with_item_drop.h"

void func_801B5EC8(void) {
    s32 temp_v1;
    Entity* entity;

    entity = g_CurrentEntity;
    if (entity->velocityY >= 0) {
        temp_v1 =
            entity->ext.generic.unk88.S16.unk0 + entity->ext.generic.unk84.unk;
        entity->ext.generic.unk84.unk = temp_v1;
        entity->velocityX = temp_v1;
        if (temp_v1 == 0x10000 || temp_v1 == -0x10000) {
            entity->ext.generic.unk88.S16.unk0 =
                -entity->ext.generic.unk88.S16.unk0;
        }
        entity = g_CurrentEntity;
    }

    if (entity->velocityY < FIX(0.25)) {
        entity->velocityY += FIX(0.125);
    }
}

void func_801B5F4C(u16 arg0) {
    Collider res;

    if (g_CurrentEntity->velocityX < 0) {
        g_api.CheckCollision(g_CurrentEntity->posX.i.hi,
                             g_CurrentEntity->posY.i.hi - 7, &res, 0);
        if (res.effects & 5) {
            g_CurrentEntity->velocityY = 0;
        }
    }

    g_api.CheckCollision(
        g_CurrentEntity->posX.i.hi, g_CurrentEntity->posY.i.hi + 7, &res, 0);

    if (arg0) {
        if (!(res.effects & 5)) {
            MoveEntity();
            FallEntity();
            return;
        }

        g_CurrentEntity->velocityX = 0;
        g_CurrentEntity->velocityY = 0;

        if (res.effects & 4) {
            g_CurrentEntity->posY.val += FIX(0.125);
            return;
        }

        g_CurrentEntity->posY.i.hi += res.unk18;
        return;
    }

    if (!(res.effects & 5)) {
        MoveEntity();
        func_801B5EC8();
    }
}

// Can't be deduped with the other instances due to the extra memcpy
void CollectHeart(u16 index) {
    s8 hearts[10];

    __builtin_memcpy(&hearts[0], &c_HeartPrizes[0], 2);
    __builtin_memcpy(&hearts[8], &c_HeartPrizes[4], 2);
    g_api.PlaySfx(NA_SE_PL_COLLECT_HEART);
    g_Status.hearts = hearts[index] + g_Status.hearts;
    if (g_Status.heartsMax < g_Status.hearts) {
        g_Status.hearts = g_Status.heartsMax;
    }
    DestroyEntity(g_CurrentEntity);
}

#include "../collect_gold.h"

void func_801B61D4(void) {}

void func_801B61DC(void) { DestroyEntity(g_CurrentEntity); }

void CollectSubweapon(u16 subWeaponIdx) {
    Entity* player = &PLAYER;
    u16 subWeapon;

    g_api.PlaySfx(NA_SE_PL_IT_PICKUP);
    subWeapon = g_Status.subWeapon;
    g_Status.subWeapon = D_80181CAC[subWeaponIdx];

    if (subWeapon == g_Status.subWeapon) {
        subWeapon = 1;
        g_CurrentEntity->unk6D[0] = 0x10;
    } else {
        subWeapon = D_80181CDC[subWeapon];
        g_CurrentEntity->unk6D[0] = 0x60;
    }

    if (subWeapon != 0) {
        g_CurrentEntity->params = subWeapon;
        g_CurrentEntity->posY.i.hi = player->posY.i.hi + 12;
        g_CurrentEntity->step = 7;
        g_CurrentEntity->step_s = 0;
        g_CurrentEntity->velocityY = FIX(-2.5);
        g_CurrentEntity->animCurFrame = 0;
        g_CurrentEntity->ext.generic.unk88.S16.unk2 = 5;
        if (player->facingLeft != 1) {
            g_CurrentEntity->velocityX = FIX(-2);
            return;
        }
        g_CurrentEntity->velocityX = FIX(2);
        return;
    }
    DestroyEntity(g_CurrentEntity);
}

void CollectDummy(void) { DestroyEntity(g_CurrentEntity); }

Entity* func_801B633C(void) {
    g_CurrentEntity->step = 3;
    g_CurrentEntity->params = 4;
    return g_CurrentEntity;
}
