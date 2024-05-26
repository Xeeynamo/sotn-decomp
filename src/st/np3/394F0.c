#include "np3.h"

void TestCollisions(void) {
    s32 temp_rand;
    
    Entity* var_s0;
    
    Primitive* var_s2;
    Entity* var_s3;
    s32 *var_s4;
    Entity *var_s5;
    u16 var_s6;
    u16 var_s8;

    s32* sp50;
    u16* sp4C;
    u32 sp40;
    EnemyDef* sp3C;
    

    s16 sp5C;
    s16 sp5A;
    u16 sp58;
    u16 sp56; //sp18
    s32 sp44; //sp20
    s32 sp48;
    
    s8 sp5F;
    Entity *var_s1; //sp28
    u8 var_s7; //sp30

    
    #define SP(x) (0x1F800000 | (x))


    sp50 = (s32 *)SP(0);
    var_s4 = (s32 *)SP(0xC0);
    for(var_s1 = &g_Entities[0]; var_s1 < &g_Entities[48]; sp50++, var_s1++) {
        *sp50 = var_s1->hitboxState;
        if ((*sp50 != 0) && !(*sp50 & 0x80)) {
            *var_s4 = var_s1->posX.i.hi;
//84
            if (var_s1->facingLeft) {
                *var_s4 -= var_s1->hitboxOffX;
            } else {
                *var_s4 += var_s1->hitboxOffX;
            }
            sp44 = var_s1->posY.i.hi + var_s1->hitboxOffY;
            if ((*var_s4 < -0x20) || (*var_s4 >= 0x121) || (sp44 < -0x20) || (sp44 >= 0x101) || !var_s1->hitboxWidth || !var_s1->hitboxHeight) {
                *sp50 = 0;
                var_s4 += 4;
            } else {
                //158
                var_s4++;
                *var_s4++ = var_s1->hitboxWidth;
                *var_s4++ = sp44;
                *var_s4++ = var_s1->hitboxHeight;
            }
        } else {
            var_s4 += 4;
        }
    }

    //1dc
    for(var_s1 = &g_Entities[64]; var_s1 < &g_Entities[192]; var_s1++){
        //1f0
        sp58 = var_s1->hitboxState;
        if (!sp58 || !(var_s1->hitboxWidth) || !(var_s1->hitboxHeight) || (var_s1->flags & 0x100)) {
            continue;
        }
        //22C
        for(var_s8 = 0; var_s8 < 11; var_s8++) {
            if (var_s1->unk6D[var_s8]) {
                var_s1->unk6D[var_s8]--;
            }
        }
        //278
        sp5C = var_s1->posX.i.hi;
        if (var_s1->facingLeft) {
            sp5C -= var_s1->hitboxOffX;
        } else {
            sp5C += var_s1->hitboxOffX;
        }
        //2B4
        sp5A = var_s1->posY.i.hi + var_s1->hitboxOffY;
        if ((sp5C < -0x1F) || (sp5C >= 0x120) || (sp5A < -0x1F) || (sp5A >= 0x100)) {
            continue;
        }
        //320
        var_s7 = 0;
        var_s6 = (u16)(sp58 & 0x3E);
        sp48 = var_s1->hitboxWidth - 1;
        sp44 = var_s1->hitboxHeight - 1;
        //35c
        if (var_s6) {
            //364
            sp50 = (s32*)SP(4);
            var_s4 = (s32 *)SP(0xD0);
            for(var_s5 = &g_Entities[1]; var_s5 < &g_Entities[48]; var_s5++) {
            //390
                if ((*sp50 & var_s6) && (!var_s1->unk6D[var_s5->enemyId])) {
                    //3c0
                    if (*sp50 & 0x80) {
                        var_s1->unk44 = var_s5->hitEffect & 0x7F ;
                        var_s7 = 0xFF;
                        break;
                    } else {
                        //3FC
                        sp56 = (u16)*var_s4++ - (u16)sp5C;
                        //42C
                        sp40 = sp48 + *var_s4++;
                        //448
                        sp56 += sp40;
                        //45C
                        sp40 *= 2;
                        if (sp40 >= sp56) {
                            //480
                            sp56 = (u16)*var_s4++ - (u16)sp5A ;
                            //4B0
                            sp40 = sp44 + *var_s4++;
                            //4CC
                            sp56 += sp40;
                            //4E0
                            sp40 *= 2;
                            //4EC
                            if (sp40 >= sp56) {
                                //504
                                var_s8 = var_s5->hitEffect & 0x7F;
                                //518
                                if (!(var_s5->flags & var_s1->flags & 0x100000)) {
                                    //534
                                    var_s5->ext.generic.unkB8.entityPtr = var_s1;
                                    //538
                                    if (sp58 & 8) {
                                        //54c
                                        var_s5->hitFlags = 3;
                                    } else {
                                        //55c
                                        var_s5->hitFlags = 1;
                                    }
                                    //564
                                    if ((var_s8 == 3) && (var_s1->flags & 0x8000)) {
                                        //584
                                        g_api.PlaySfx(0x611);
                                        var_s5->hitFlags = 2;
                                    }
                                    //5a4
                                    if ((var_s8 == 4) && (var_s1->flags & 0x4000)) {
                                        //5cc
                                        g_api.PlaySfx(0x611);
                                        var_s5->hitFlags = 2;
                                    }
                                }
                                //5e8
                                var_s1->unk44 = var_s8;
                                var_s7 = 0xFF;
                                break;
                            } else {
                                sp50++;
                                continue;
                            }
                        } else {
                            //614
                            sp50++;
                            var_s4 += 2;
                            continue;
                        }
                    }
                } else {
                    sp50 ++;
                    var_s4 += 4;
                }
            }
        }

        
        //660
        if ((sp58 & 1) && (!var_s7)) {
            //67C
            var_s5 = &PLAYER;
            sp50 = (s32 *)SP(0);
            var_s4 = (s32 *)SP(0xC0);
            //69C
            if (!var_s1->unk6D[var_s5->enemyId] && (*sp50 & 1)) {
                //6c8
                sp56 = (u16)*var_s4++ - (u16)sp5C;
                //6f8
                sp40 = sp48 + *var_s4++;
                //714
                sp56 += sp40;
                //728
                sp40 *= 2;
                //734
                if (sp40 >= sp56) {
                    //74c
                    sp56 = (u16)*var_s4++ - (u16)sp5A;
                    //77c
                    sp40 = sp44 + *var_s4++;
                    //798
                    sp56 += sp40;
                    //7ac
                    sp40 *= 2;
                    //7b8
                    if (sp40 >= sp56) {
                        //7d0
                        if ((var_s1->attack) && (var_s5->hitPoints < var_s1->attack)) {
                            //7f8
                            var_s5->ext.generic.unkB8.entityPtr = var_s1;
                            //7fc
                            if (sp58 & 8) {
                                //810
                                var_s5->hitFlags = 3;
                            } else {
                                //820
                                var_s5->hitFlags = 1;
                            }
                            //828
                            var_s5->unk44 = var_s1->attackElement;
                            var_s5->hitPoints = var_s1->attack;
                        }
                        //838
                        var_s1->unk44 = var_s5->hitEffect & 0x7F;
                        var_s7 = 0xFF;
                        var_s1->hitFlags = 0x80;
                    }
                }
            }
        }
        //860
        if (var_s7) {
            //868
            if (var_s1->unk5C != NULL) {
                var_s3 = var_s1->unk5C;
                var_s3->unk44 = (u16) var_s1->unk44;
                var_s3->hitFlags = (u8) var_s1->hitFlags;
            } else {
                //894
                var_s3 = var_s1;
            }
            //898
            if (!(var_s3->flags & 0x100) && var_s7) {
                //8b0
                sp56 = var_s5->hitEffect & 0x7F;
                //8C4
                if ((sp56 == 2) || ((sp56 == 6) && (sp58 & 0x20))) {
                    //900
                    var_s0 = AllocEntity(&g_Entities[160], &g_Entities[192]);
                    if (var_s0 != NULL) {
                        CreateEntityFromEntity(7, var_s1, var_s0);
                    }
                }
                //940
                sp58 = D_80181678[var_s3->enemyId];
                if (sp58) {
                    sp58--;
                    var_s6 = 1 << (sp58 & 7);
                    g_CastleFlags[(sp58 >> 3) + 0x190] |= var_s6;
                }
                //9C4
                if ((g_Status.relics[RELIC_FAERIE_SCROLL] & 2) && !(var_s3->flags & 0x01000000)) {
                    //9F0
                    if (g_BottomCornerTextTimer != 0) {
                        g_api.FreePrimitives(g_BottomCornerTextPrims);
                        g_BottomCornerTextTimer = 0;
                    }
                    //A24
                    BottomCornerText(g_api.enemyDefs[var_s3->enemyId].name, 0);
                    var_s3->flags = (u32) (var_s3->flags | 0x01000000);
                }
                //A68
                var_s7 = 0;
                if ((var_s1->hitboxState & 8) && (var_s5->hitboxState & 4)) {
                    goto block_164;
                }
                //A9C
                if (var_s3->hitPoints) {
                    //AA8
                    if (var_s5->attack) {
                        //AB4
                        if (!(var_s5->hitboxState & 0x80)) {
                            //AC8
                            var_s4 -= 4;
                            //ACC
                            sp5C += *var_s4++;
                            //AF0
                            var_s4++;
                            //AF8
                            sp5A += *var_s4;
                            //B0C
                            sp5C /= 2;
                            sp5A /= 2;
                        }
                        //b58
                        for(var_s2 = &g_PrimBuf[D_800973F8];var_s2 != NULL; var_s2 = var_s2->next){
                            //b80
                            if (var_s2->blendMode == 8) {
                                var_s2->clut = 0x199;
                                //b9c
                                temp_rand = (Random() & 7) - 13;
                                var_s2->x0 = var_s2->x2 = sp5C + temp_rand - 3;
                                //bd4
                                var_s2->x1 = var_s2->x3 = var_s2->x0 + 0x20;
                                temp_rand = (Random() & 7) - 10;
                                var_s2->y0 = var_s2->y1 = sp5A + temp_rand - 3;
                                var_s2->y2 = var_s2->y3 = var_s2->y0 + 0x20;
                                //c3c
                                var_s2->p1 = 0;
//Mismatch???
                                if (var_s5->zPriority > var_s1->zPriority) {
                                    var_s2->priority = var_s5->zPriority + 1;
                                } else {
                                    var_s2->priority = var_s1->zPriority + 1;
                                }
                                //c8c
                                var_s2->blendMode = 2U;
                                break;
                            }
                        }
                    }
                    //ca8
                    if ((var_s5->attack) && (var_s3->hitPoints != 0x7FFF)) {
                        //cc8
                        sp58 = g_api.DealDamage(var_s1, var_s5);
                        if (var_s5->hitboxState == 4) {
                            sp58 = 0;
                        }
                        if ((g_Status.relics[RELIC_SPIRIT_ORB] & 2) && !(var_s3->flags & 0x04000000) && sp58) {
                            //d38
                            var_s0 = AllocEntity(&g_Entities[224], &g_Entities[256]);
                            if (var_s0 != NULL) {
                                DestroyEntity(var_s0);
                                var_s0->entityId = 4;
                                var_s0->pfnUpdate = EntityDamageDisplay;
                                var_s0->posX.i.hi = sp5C;
                                var_s0->posY.i.hi = sp5A;
                                var_s0->params = sp58;
                            }
                        }
                    } else {
                        //da4
                        sp58 = 0;
                    }
                    if (sp58 != 0xC000) {
                        //dbc
                        if (sp58 & 0x8000) {
                            var_s7 = 9;
                        } else {
                            var_s6 = (u16) var_s5->attackElement;
                            if (var_s6 & 0xFFC0) {
                                //E00
                                for(var_s8 = 0; var_s8 < 10; var_s8++){
                                    if (var_s6 & D_801819AC[var_s8]) {
                                        var_s7 = D_801819C0[var_s8];
                                        break;
                                    }
                                }
                            }
                        }
                    } else {
                        //e7c
                        var_s3->hitFlags |= 0x20;
                        sp58 = 0;
                    }
                    //e8c
                    if (!sp58) {
                        goto unusual_spot;
                    }
                        //e98
                        if (sp58 & 0x8000) {
                            //eac
                            var_s3->hitPoints += (sp58 & 0x3FFF);
                            //ec8
                            var_s6 = g_api.enemyDefs[var_s3 ->enemyId].hitPoints;
                            if (var_s3->hitPoints > var_s6) {
                                var_s3->hitPoints = var_s6;
                            }
                        } else {
                            //f18
                            sp58 &= 0x3FFF;
                            //f24
                            if (var_s3->flags & 0x10) {
                                //f34
                                //Different on PSP vs PSX
                                if (g_PlayableCharacter != 0) {
                                    g_api.PlaySfx(0x705);
                                } else if (var_s5->hitEffect & 0x80) {
                                    g_api.PlaySfx(0x62E);
                                } else {
                                    g_api.PlaySfx(0x678);
                                }
                            }
                            //fb8
                            if (var_s3->hitPoints != 0x7FFE) {
                                //fcc
                                if (var_s3->hitPoints < (sp58 * 2)) {
                                    //fec
                                    var_s3->hitFlags |= 3;
                                //1000
                                } else if (var_s3->hitPoints < ((sp58) * 4)) {
                                    //1020
                                    var_s3->hitFlags |= 2;
                                } else {
                                    //1034
                                    var_s3->hitFlags |= 1;
                                }
                                //1040
                                var_s3->hitPoints -= sp58;
                            }
                            //1054
                            if ((var_s5->attackElement & 0x40) && (var_s3->hitboxState & 0x10)) {
                                //107c
                                var_s0 = AllocEntity(&g_Entities[160], &g_Entities[192]);
                                if (var_s0 != NULL) {
                                    CreateEntityFromEntity(0xDU, var_s1, var_s0);
                                    if (sp5C > var_s1->posX.i.hi) {
                                        var_s0->params = 1;
                                    }
                                    var_s0->posX.i.hi = sp5C;
                                    var_s0->posY.i.hi = sp5A;
                                    var_s0->zPriority = 0xC0;
                                }
                            }
                        }
                        //10f8
                        if (var_s3->hitPoints > 0) {
                            //1108
                            var_s0 = var_s3;
                            //110c
                            var_s6 = var_s5->enemyId;
                            //1118
                            do{
                                var_s0->unk6D[var_s6] = var_s5->nFramesInvincibility;
                                if (var_s3 < var_s0) {
                                    var_s0->unk6D[var_s6]++;
                                }
                                if (!(var_s1->flags & 0x400000)) {
                                    var_s0->stunFrames = var_s5->stunFrames;
                                }
                                //1164
                                if ((!var_s0->hitEffect) && !(var_s0->flags & 0xF)) {
                                    var_s0->hitEffect = var_s0->palette;
                                }
                                var_s0->nFramesInvincibility = var_s7;
                                //118c
                                var_s0->flags |= 0xF;
                                //1198
                                var_s0 = var_s0->unk60;
                                }while ((var_s0 != NULL) && (var_s0 != var_s3));
                                //11ac
                                sp5F = ((u32)var_s3->flags >> 4) & 7 & 0xFF;
                            continue;
                        }
                }
block_164:
                //11cc
                PreventEntityFromRespawning(var_s3);
                sp3C = &g_api.enemyDefs[var_s3->enemyId];
                //11fc
                if (!(var_s3->hitFlags & 0x80)) {
                    //1210
                    g_api.func_800FE044(sp3C->exp, sp3C->level);
                    if ((var_s3->flags & 0x1000) && (g_Status.killCount < 0xF423F)) {
                        g_Status.killCount++;
                    }
                }
                //1280
                var_s6 = var_s3->flags & 0xC00;
                if (var_s6) {
                    //1298
                    if ((rand() & 0xFF) < g_api.func_800FF460(D_80181998[var_s6 >> 0xA])) {
                        //12ec
                        var_s0 = AllocEntity(&g_Entities[160], &g_Entities[192]);
                        //130c
                        sp58 = 0;
                        //1310
                        if (var_s0 != NULL) {
                            //1318
                            if (sp56 == 5) {
                                //132c
                                sp4C = &D_80181A0C;
                                var_s6 = rand() & 0xFFF;
                                //1350
                                while(1){
                                    if (*sp4C++ >= var_s6 ) {
                                        var_s6 = *sp4C;
                                        break;
                                    }
                                    sp4C++;
                                }
                                
                            } else {
                                //139c
                                var_s6 = g_api.func_800FF494(sp3C);
                                //13c0
                                if (var_s6 & 0x40) {
                                    var_s6 = sp3C->rareItemId;
                                    //13dc
                                    //Paranthropus check: Drops turquoise if game not beaten. Otherwise ring of Varda
                                    if ((var_s6 == 0x173) && (!g_IsTimeAttackUnlocked)) {
                                        var_s6 = 0x16A;
                                    } else {
                                        //140c
                                        sp58 = D_80181678[var_s3->enemyId];
                                    }
                                //1434
                                } else if (var_s6 & 0x20) {
                                    var_s6 = sp3C->uncommonItemId;
                                } else {
                                    //1458
                                    var_s6 = D_801819CC[var_s6];
                                }
                            }
                            //1474
                            if (var_s6 >= 0x80) {
                                var_s6 -= 0x80;
                                CreateEntityFromEntity(10, var_s1, var_s0);
                            } else {
                                CreateEntityFromEntity(3, var_s1, var_s0);
                            }
                            //14c4
                            var_s0->ext.relicOrb.yFloatSpeed = sp58;
                            var_s0->params = var_s6;
                            var_s0->velocityY = -0x38000;
                        }
                    }
                }
                //14e0
                var_s0 = var_s3;
                do{
                    var_s0->flags |= 0x10C100;
                    var_s0->flags &= 0xDFFFFFFF;
                    //150c
                    if (!var_s0->hitEffect) {
                        var_s0->hitEffect = var_s0->palette;
                    }
                    var_s0->nFramesInvincibility = var_s7;
                    var_s0->flags |= 0xF;
                    var_s0 = var_s0->unk60;
                //1538
                }while(var_s0 != NULL && var_s0 != var_s3);
                continue;
                
                unusual_spot:
                //1564
                if (!(var_s3->hitFlags & 0xF)) {
                    var_s3->hitFlags |= 0x10;
                }
                //1570
                if ((var_s3->flags & 0x10) && (var_s5->attack)) {
                    if (var_s5->hitEffect & 0x80) {
                        g_api.PlaySfx(0x611);
                    } else {
                        g_api.PlaySfx(0x611);
                    }
                }
                //15d8
                var_s0 = var_s3;
                var_s6 = var_s5->enemyId;
                do{
                    if (var_s1->hitPoints == 0x7FFF) {
                        if (var_s0->hitPoints == 0x7FFF) {
                            var_s0->unk6D[var_s6] = var_s5->nFramesInvincibility;
                            if (var_s3 < var_s0) {
                                //1630
                                var_s0->unk6D[var_s6]++;
                            }
                        }
                    } else {
                        //1644
                        var_s0->unk6D[var_s6] = var_s5->nFramesInvincibility;
                        if (var_s3 < var_s0) {
                            var_s0->unk6D[var_s6]++;
                        }
                    }
                    var_s0 = var_s0->unk60;
                } while((var_s0 != NULL) && (var_s0 != var_s3));
            }
        }
    }
    //16a4
    for(var_s2 = &g_PrimBuf[D_800973F8]; var_s2 != NULL; var_s2 = var_s2->next){
        //16cc
        if ((var_s2->drawMode) != 8) {
            var_s7 = var_s2->p1;
            var_s2->u0 = var_s2->u2 = D_8018199C[var_s7];
            var_s2->u1 = var_s2->u3 = var_s2->u0 + 0x20;
            var_s2->v0 = var_s2->v1 = D_801819A4[var_s7];
            var_s2->v2 = var_s2->v3 = var_s2->v0 + 0x20;
            var_s7++;
            if (var_s7 >= 7) {
                var_s2->drawMode = 8U;
            } else {
                var_s2->p1 = var_s7;
            }
        }
    }
}

#include "../entity_damage_display.h"

#include "../libstage.h"

#include "../entity_red_door.h"

#include "../entity.h"

u8 func_801BC6BC(u8 frames[], Entity* self, u8 arg2) {
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
s32 GetDistanceToPlayerX(void) {
    s16 yDistance = g_CurrentEntity->posX.i.hi - PLAYER.posX.i.hi;

    if (yDistance < 0) {
        yDistance = -yDistance;
    }
    return yDistance;
}

// Absolute distance from g_CurrentEntity to the player in the Y Axis
s32 GetDistanceToPlayerY(void) {
    s32 yDistance = g_CurrentEntity->posY.i.hi - PLAYER.posY.i.hi;

    if (yDistance < 0) {
        yDistance = -yDistance;
    }
    return yDistance;
}

#include "../get_side_to_player.h"

void MoveEntity(void) {
    g_CurrentEntity->posX.val += g_CurrentEntity->velocityX;
    g_CurrentEntity->posY.val += g_CurrentEntity->velocityY;
}

void FallEntity(void) {
    if (g_CurrentEntity->velocityY < FALL_TERMINAL_VELOCITY) {
        g_CurrentEntity->velocityY += FALL_GRAVITY;
    }
}

s32 func_801BC8E4(u16* sensors) {
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

s32 func_801BCB5C(s16* posX) {
    Collider collider;
    s16 temp2;
    s16 temp4;
    s16 x, y;

    g_CurrentEntity->posX.val += g_CurrentEntity->velocityX;
    temp2 = g_CurrentEntity->posY.i.hi + 3;
    g_CurrentEntity->posY.i.hi = temp2;
    x = g_CurrentEntity->posX.i.hi + *posX;
    posX++;
    y = temp2 + *posX;
    g_api.CheckCollision(x, y, &collider, 0);
    if (!(collider.effects & EFFECT_SOLID)) {
        return 0;
    }
    posX++;

    g_CurrentEntity->posY.i.hi = g_CurrentEntity->posY.i.hi + collider.unk18;
    if (g_CurrentEntity->velocityX != 0) {
        if (g_CurrentEntity->velocityX < 0) {
            temp4 = x - *posX;
            posX++;
        } else {
            temp4 = x + *posX;
            posX++;
        }
        y = y + *posX - 7;
        g_api.CheckCollision(temp4, y, &collider, 0);
        if (collider.effects & EFFECT_SOLID) {
            if ((collider.effects & (EFFECT_UNK_8000 | EFFECT_UNK_0002)) ==
                EFFECT_UNK_0002) {
                g_CurrentEntity->posX.val =
                    g_CurrentEntity->posX.val - g_CurrentEntity->velocityX;
                g_CurrentEntity->velocityX = 0;
                return 0xFF;
            }
            return 0x61;
        }
        y += 15;
        g_api.CheckCollision(temp4, y, &collider, 0);
        if (collider.effects & EFFECT_SOLID) {
            if (collider.effects & EFFECT_UNK_8000) {
                return 0x61;
            }
            return 1;
        }
        g_CurrentEntity->posX.val -= g_CurrentEntity->velocityX;
        g_CurrentEntity->velocityX = 0;

        return 0x80;
    }
    return 1;
}

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

s32 func_801BCDA4(u8 arg0, s16 arg1) { return D_80181A50[arg0] * arg1; }

s16 func_801BCDD0(u8 arg0) { return D_80181A50[arg0]; }

void func_801BCDEC(s32 arg0, s16 arg1) {
    g_CurrentEntity->velocityX = func_801BCDA4(arg0, arg1);
    g_CurrentEntity->velocityY = func_801BCDA4(arg0 - 0x40, arg1);
}

u8 func_801BCE58(s16 x, s16 y) { return ((ratan2(y, x) >> 4) + 0x40); }

u8 func_801BCE90(Entity* a, Entity* b) {
    s32 diffX = (u16)b->posX.i.hi - (u16)a->posX.i.hi;
    s32 diffY = (u16)b->posY.i.hi - (u16)a->posY.i.hi;
    return func_801BCE58(diffX, diffY);
}

u8 func_801BCED8(s32 x, s32 y) {
    s32 diffX = x - (u16)g_CurrentEntity->posX.i.hi;
    s32 diffY = y - (u16)g_CurrentEntity->posY.i.hi;
    return func_801BCE58(diffX, diffY);
}

#include "../adjust_value_within_threshold.h"

#include "../unk_entity_func0.h"

u16 func_801BD004(s16 x, s16 y) { return ratan2(y, x); }

u16 func_801BD034(Entity* a, Entity* b) {
    s32 diffX = b->posX.i.hi - a->posX.i.hi;
    s32 diffY = b->posY.i.hi - a->posY.i.hi;
    return ratan2(diffY, diffX);
}

u16 func_801BD06C(s32 x, s32 y) {
    s16 diffX = x - (u16)g_CurrentEntity->posX.i.hi;
    s16 diffY = y - (u16)g_CurrentEntity->posY.i.hi;
    return ratan2(diffY, diffX);
}

u16 func_801BD0B4(u16 arg0, s16 arg1, s16 arg2) {
    u16 var_v0 = arg1;
    u16 temp_a2 = arg2 - arg1;
    u16 var_v0_2;

    if (temp_a2 & 0x800) {
        var_v0_2 = (0x800 - temp_a2) & 0x7FF;
    } else {
        var_v0_2 = temp_a2;
    }

    if (var_v0_2 > arg0) {
        if (temp_a2 & 0x800) {
            var_v0 = arg1 - arg0;
        } else {
            var_v0 = arg1 + arg0;
        }

        return var_v0;
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

void EntityExplosionSpawn(u16 arg0, u16 sfxId) {
    if (sfxId != 0) {
        func_801C2598(sfxId);
    }

    if (arg0 == 0xFF) {
        DestroyEntity(g_CurrentEntity);
        return;
    }

    g_CurrentEntity->entityId = E_EXPLOSION;
    g_CurrentEntity->pfnUpdate = (PfnEntityUpdate)EntityExplosion;
    g_CurrentEntity->params = arg0;
    g_CurrentEntity->animCurFrame = 0;
    g_CurrentEntity->drawFlags = 0;
    g_CurrentEntity->step = 0;
    g_CurrentEntity->step_s = 0;
}

#include "../init_entity.h"

void EntityDummy(Entity* arg0) {
    if (arg0->step == 0) {
        arg0->step++;
    }
}

s32 func_801BD308(u16* hitSensors, s16 sensorCount) {
    s32 velocityX = g_CurrentEntity->velocityX;
    Collider collider;
    u16 temp_a1;
    s16 x;
    s16 y;
    s16 i;

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
            if (collider.effects & EFFECT_UNK_0002 &&
                ((!(collider.effects & EFFECT_UNK_8000)) || (i != 0))) {
                return 2;
            }
        }
        return 0;
    }
}

void func_801BD430(u16* hitSensors, s16 sensorCount) {
    s32 velocityX = g_CurrentEntity->velocityX;
    Collider collider;
    s16 x;
    s16 y;
    s16 i;

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
        if (collider.effects & EFFECT_UNK_0002 &&
            (!(collider.effects & EFFECT_UNK_8000) || i != 0)) {
            if (velocityX < 0) {
                g_CurrentEntity->posX.i.hi += collider.unk1C;
            } else {
                g_CurrentEntity->posX.i.hi += collider.unk14;
            }
            return;
        }
    }
}

INCLUDE_ASM("st/np3/nonmatchings/394F0", func_801BD588);

#include "../replace_breakable_with_item_drop.h"

void func_801BD984(void) {
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

void func_801BDA08(u16 arg0) {
    Collider collider;

    if (g_CurrentEntity->velocityX < 0) {
        g_api.CheckCollision(g_CurrentEntity->posX.i.hi,
                             g_CurrentEntity->posY.i.hi - 7, &collider, 0);
        if (collider.effects & EFFECT_NOTHROUGH) {
            g_CurrentEntity->velocityY = 0;
        }
    }

    g_api.CheckCollision(g_CurrentEntity->posX.i.hi,
                         g_CurrentEntity->posY.i.hi + 7, &collider, 0);

    if (arg0) {
        if (!(collider.effects & EFFECT_NOTHROUGH)) {
            MoveEntity();
            FallEntity();
            return;
        }

        g_CurrentEntity->velocityX = 0;
        g_CurrentEntity->velocityY = 0;

        if (collider.effects & EFFECT_QUICKSAND) {
            g_CurrentEntity->posY.val += FIX(0.125);
        } else {
            g_CurrentEntity->posY.i.hi += collider.unk18;
        }
    } else {
        if (!(collider.effects & EFFECT_NOTHROUGH)) {
            MoveEntity();
            func_801BD984();
        }
    }
}

#include "../collect_heart.h"

void CollectGold(u16 goldSize) {
    s32 *gold, *unk;
    u16 goldSizeIndex;

    g_api.PlaySfx(NA_SE_PL_COLLECT_GOLD);
    gold = &g_Status.gold;
    goldSizeIndex = goldSize - 2;
    *gold += c_GoldPrizes[goldSizeIndex];
    if (*gold > MAX_GOLD) {
        *gold = MAX_GOLD;
    }

    unk = &g_unkGraphicsStruct.BottomCornerTextTimer;
    if (*unk) {
        g_api.FreePrimitives(g_unkGraphicsStruct.BottomCornerTextPrims);
        *unk = 0;
    }

    BottomCornerText(D_80181DC4[goldSizeIndex], 1);
    DestroyEntity(g_CurrentEntity);
}

void CollectSubweapon(u16 subWeaponIdx) {
    Entity* player = &PLAYER;
    u16 subWeapon;

    g_api.PlaySfx(NA_SE_PL_IT_PICKUP);
    subWeapon = g_Status.subWeapon;
    g_Status.subWeapon = D_80181D80[subWeaponIdx];

    if (subWeapon == g_Status.subWeapon) {
        subWeapon = 1;
        g_CurrentEntity->unk6D[0] = 0x10;
    } else {
        subWeapon = D_80181DB0[subWeapon];
        g_CurrentEntity->unk6D[0] = 0x60;
    }

    if (subWeapon != 0) {
        g_CurrentEntity->params = subWeapon;
        g_CurrentEntity->posY.i.hi = player->posY.i.hi + 12;
        SetStep(7);
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

#include "../collect_heart_vessel.h"

void CollectLifeVessel(void) {
    g_api.PlaySfx(NA_SE_PL_COLLECT_HEART);
    g_api.func_800FE044(5, 0x8000);
    DestroyEntity(g_CurrentEntity);
}

void DestroyCurrentEntity(void) { DestroyEntity(g_CurrentEntity); }
