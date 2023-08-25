#include "sel.h"

extern s32 D_801804D0;
extern u8 D_801804D4[];
extern s32 D_801804D8[];
extern const s32 D_801A7B8C[2];
extern s32 D_801BB010;
extern s32 D_801BB014;

void TestCollisions(void) {
    Primitive* prim;
    Primitive* prim15;
    s16 primIndex;
    s32 i;
    s32 scaled_b014;

    func_801B1F34();
    switch (D_8003C9A4) {
    case 0:
        if (g_UseDisk != 0) {
            g_CdStep = 1;
            g_LoadFile = 0x8003;
            g_mapTilesetId = 0xFF;
        }
        primIndex = g_api.AllocPrimitives(PRIM_SPRT, 0x11);
        prim = &g_PrimBuf[primIndex];
        
        D_801BB010 = primIndex;
        for(i=0; i < 3; i++) {
            prim->x0 = 0x70 + i*0x80;
            prim->y0 = 0xA8;
            prim->u0 = 0x80;
            prim->v0 = i*0x10 - 0x50;
            prim->u1 = 0x80;
            if (i == 2) {
                prim->u1 = 0x20;
            }
            prim->v1 = 0x10;
            prim->tpage = 0x18;
            prim->clut = 0x20;
            prim->priority = 1;
            prim->blendMode = 8;
            prim = prim->next;
        }
        for(i=0; i < 4; i++) {
            prim->x0 = 12 + i*0x80;
            prim->y0 = 0xD6;
            prim->u0 = 0x80;
            prim->v0 = i*8 -0x70;
            prim->u1 = 0x80;
            if (i == 3) {
                prim->u1 = 0x64;
            }
            prim->v1 = 8;
            prim->tpage = 0x18;
            prim->clut = 0x21;
            prim->priority = 1;
            prim->blendMode = 8;
            prim = prim->next;
        }
        for(i=0; i < 4; i++) {
            prim->x0 = i << 7;
            prim->u1 = 0x80;
            prim->v1 = 0xF0;
            prim->tpage = i + 0x88;
            prim->clut = 0x10;
            prim->blendMode = 8;
            prim = prim->next;
        }
        for(i=0; i < 4; i++) {
            prim->x0 = i << 7;
            prim->u1 = 0x80;
            prim->y0 = 0x18;
            prim->v1 = 0x88;
            prim->tpage = i + 0x8C;
            prim->priority = 2;
            prim->blendMode = 8;
            prim = prim->next;
        }
        prim->x0 = 0x101;
        prim->y0 = 0x60;
        prim->u1 = 0xFF;
        prim->v1 = 0x90;
        prim->tpage = 0x18;
        prim->clut = 0x22;
        prim->priority = 1;
        prim->blendMode = 8;
        prim = prim->next;
        
        prim->v0 = 0x90;
        prim->u1 = 0x78;
        prim->v1 = 0x40;
        prim->tpage = 0x18;
        prim->clut = 0x22;
        prim->priority = 1;
        prim->blendMode = 8;
        func_801B18F4();
        D_801BB014 = 0;
        D_8003C9A4++;
        return;
    case 1:
        func_801B1A98();
        D_801BB014 += 8;
        for(i=0, prim = &g_PrimBuf[D_801BB010];prim != NULL; prim = prim->next, i++) {
            prim->blendMode = 4;
            func_801B1CFC((POLY_GT4* ) prim, D_801BB014);
            if (((u32) (i - 7) < 2U) || (((u32) (i - 9) < 2U) != 0)) {
                
                scaled_b014 = D_801BB014 * 3;
                if (scaled_b014 < 0) {
                    scaled_b014 += 3;
                }
                prim->r0 = (u8) (scaled_b014 >> 2);
                
                scaled_b014 = D_801BB014 * 7;
                if (scaled_b014 < 0) {
                    scaled_b014 += 7;
                }
                prim->g0 = (u8) (scaled_b014 >> 3);
                
                scaled_b014 = D_801BB014 * 3;
                if (scaled_b014 < 0) {
                    scaled_b014 += 3;
                }
                prim->b0 = (u8) (scaled_b014 >> 2);
            }
            if (i - 0xF < 2U) {
                prim->blendMode = 0x15;
            }
        }
        if (D_801BB014 == 0x80) {
            D_801804D0 = 0x800;
            D_8003C9A4++;
        }
        return;
    case 2:
        for(i = 0, prim = &g_PrimBuf[D_801BB010]; prim!=NULL; prim = prim->next, i++){
            if (i < 3) {
                prim->blendMode = 8;
                if (g_blinkTimer & 0x30) {
                    prim->blendMode = 0;
                }
            }
            if (i < 15 || i > 16) {
                continue;
            }
            if (i == 15) {
                prim15 = prim;
            }
            switch (prim->p1) {
            case 0:
                if (i == 0xF) {
                    if (!(rand() & 0x7F)) {
                        prim->p2 = 6;
                        prim->tpage = 0x19;
                        prim->p1 += 1;
                    }
                } else {
                    if ((prim15->p1 >= 2U) || ((prim15->p1 != 0) && ((u8) prim15->p2 < 3U))) {
                        prim->p2 = (rand() & 3) + 6;
                        prim->tpage = 0x19;
                        prim->p1 += 1;
                    }
                }
                break;
            case 1:
                if (!(--prim->p2 & 0xFF)) {
                    prim->p2 = 6;
                    prim->tpage = 0x1A;
                    prim->p1 += 1;
                }
                break;
            case 2:
                if (!(--prim->p2 & 0xFF)) {
                    prim->p2 = (rand() & 7) + 6;
                    prim->tpage = 0x1B;
                    prim->p1 += 1;
                }
                break;
            case 3:
                if (!(--prim->p2 & 0xFF)) {
                    prim->p2 = 5;
                    prim->tpage = 0x1A;
                    prim->p1 += 1;
                }
                break;
            case 4:
                if (!(--prim->p2 & 0xFF)) {
                    prim->p2 = 5;
                    prim->tpage = 0x19;
                    prim->p1 += 1;
                }
                break;
            case 5:
                if (!(--prim->p2 & 0xFF)) {
                    prim->p2 = 6;
                    prim->tpage = 0x18;
                    prim->p1 += 1;
                }
                break;
            case 6:
                if (!(--prim->p2 & 0xFF)) {
                    if (i != 0x10) {
                        prim->p2 = 6;
                        prim->p1 += 1;
                        if (rand() & 3) {
                            prim->p1 = 1;
                            prim->tpage = 0x19;
                        }
                    } else {
                        prim->p1 = 0;
                    }
                }
                break;
            case 7:
                if (!(--prim->p2 & 0xFF)) {
                    prim->p1 = 0;
                }
                break;
            }
            
            if (i != 0x10) {
                continue;
            }
            if (prim->tpage == 0x18){
                prim->u1 = 0x78;
            } else {
                prim->u1 = 0x70;
            } 
        }
        if (g_pads[0].tapped & 0x800) {
            g_api.PlaySfx(0x63D);
            D_8003C9A4++;
        }
        return;
    case 3:
        D_8003C9A4 = 6;
        return;
    case 4:
        if (g_pads[0].tapped & 0x6000) {
            g_api.PlaySfx(0x688);
            if (++D_800987B4 >= 2) {
                D_800987B4 = 0;
            }
        }
        if (g_pads[0].tapped & 0x9000) {
            g_api.PlaySfx(0x688);
            if (--D_800987B4 < 0) {
                D_800987B4 = 1;
            }
        }
        prim = &g_PrimBuf[D_801BB010];
        if (g_blinkTimer & 0x1C) {
            prim->blendMode = 0;
        } else {
            prim->blendMode = 8;
        }
        g_StageId = D_801804D4[D_800987B4];
        func_801B1F4C(1);
        func_801B259C(D_801804D8[D_800987B4], 1);
        if (g_pads[0].tapped & 0x820) {
            g_api.PlaySfx(0x63D);
            D_8003C9A4++;
        }
        return;
    case 5:
        func_801B18F4();
        func_801B19F4();
        func_801B1DA8();
        g_api.FreePrimitives(D_801BB010);
        STRCPY(g_Status.saveName,D_801A7B8C);
        if (g_StageId == STAGE_ST0) {
            SetGameState(Game_VideoPlayback);
        } else if (g_StageId == STAGE_MEMORYCARD) {
            SetGameState(Game_MainMenu);
        } else {
            SetGameState(Game_NowLoading);
            g_GameStep = 2;
        }
        return;
    case 6:
        D_801BB014 -= 8;
        for (i = 0, prim = &g_PrimBuf[D_801BB010]; prim != NULL; prim = prim->next, i++) {
            prim->blendMode = 4;
            func_801B1CFC((POLY_GT4* ) prim, D_801BB014);
            if ((u32) (i - 0xF) < 2U) {
                prim->blendMode = 0x15;
            }
        }
        if (D_801BB014 == 0) {
            g_StageId = STAGE_MEMORYCARD;
            D_8003C9A4 = 5;
        }
        return;
    }
}

void DestroyEntity(Entity* entity) {
    s32 i;
    s32 length;
    u32* ptr;

    if (entity->flags & FLAG_HAS_PRIMS) {
        g_api.FreePrimitives(entity->primIndex);
    }

    ptr = (u32*)entity;
    length = sizeof(Entity) / sizeof(u32);
    for (i = 0; i < length; i++)
        *ptr++ = 0;
}

void func_801B4B9C(Entity* entity, s16 step) {
    entity->step = step;
    entity->step_s = 0;
    entity->animFrameIdx = 0;
    entity->animFrameDuration = 0;
}

s32 AnimateEntity(const u8 frames[], Entity* entity) {
    s32 flag = 0;
    u16 currentFrameIndex = entity->animFrameIdx * 2;
    u8* currentFrame = frames + currentFrameIndex;

    if (entity->animFrameDuration == 0) {
        if (currentFrame[0] > 0) {
            flag = 0x80;
            if (currentFrame[0] == 0xFF) {
                return false;
            }

            entity->animFrameDuration = *currentFrame++;
            entity->animCurFrame = *currentFrame++;
            entity->animFrameIdx++;
        } else {
            currentFrame = frames;
            entity->animFrameIdx = 0;
            entity->animFrameDuration = 0;
            entity->animFrameDuration = *currentFrame++;
            entity->animCurFrame = *currentFrame++;
            entity->animFrameIdx++;
            return false;
        }
    }

    entity->animFrameDuration = entity->animFrameDuration - 1;
    entity->animCurFrame = currentFrame[-1];
    flag |= true;

    return (u8)flag;
}

INCLUDE_ASM("asm/us/st/sel/nonmatchings/3410C", func_801B4C68);

void func_801B4D78(void) {
    Entity* e = &g_Entities[UNK_ENTITY_3];

    if (e->step == 0) {
        e->animSet = ANIMSET_OVL(1);
        e->animCurFrame = 1;
        e->palette = 0x200;
        e->ext.generic.unk80.modeS32 = 0x5C0000;
        e->posY.i.hi = 208;
        e->zPriority = 0x80;
        e->step = 1;
    }
}

void func_801B4DE0(void) {
    Entity* unkEntity = &g_Entities[UNK_ENTITY_2];
    s16 primIndex;
    POLY_GT4* poly;

    switch (unkEntity->step) {
    case 0:
        primIndex = g_api.AllocPrimitives(PRIM_G4, 1);
        if (primIndex != -1) {
            poly = &g_PrimBuf[primIndex];
            unkEntity->primIndex = primIndex;
            unkEntity->flags |= FLAG_HAS_PRIMS;
            *(s32*)&unkEntity->ext.generic.unk7C = poly;

            poly->x1 = poly->x3 = 255;
            poly->y0 = poly->y1 = 4;
            poly->y2 = poly->y3 = 228;

            poly->r0 = poly->r1 = poly->r2 = poly->r3 = poly->g0 = poly->g1 =
                poly->g2 = poly->g3 = poly->b0 = poly->b1 = poly->b2 =
                    poly->b3 = 255;

            poly->pad2 = 0xC8;
            poly->x0 = poly->x2 = 0;
            poly->pad3 = 81;
            D_801BC3E4 = 0;
            unkEntity->step++;
        }
        break;

    case 1:
        poly = *(s32*)&unkEntity->ext.generic.unk7C;
        if (D_801BC3E4 != 0) {
            poly->r1 = poly->r2 = poly->r3 = poly->g0 = poly->g1 = poly->g2 =
                poly->g3 = poly->b0 = poly->b1 = poly->b2 = poly->b3 =
                    poly->r0 = poly->b3 - 2;
            if (poly->r0 < 5) {
                D_801BC3E4 = 0;
                unkEntity->step++;
            }
        }
        break;

    case 2:
        poly = *(s32*)&unkEntity->ext.generic.unk7C;
        if (D_801BC3E4 != 0) {
            poly->r1 = poly->r2 = poly->r3 = poly->g0 = poly->g1 = poly->g2 =
                poly->g3 = poly->b0 = poly->b1 = poly->b2 = poly->b3 =
                    poly->r0 = poly->b3 + 1;
            if (poly->r0 >= 254) {
                D_801BC3E4 = 0;
                unkEntity->step++;
            }
        }
    }
}

void func_801B4FFC(void) {
    Entity* unkEntity = &g_Entities[UNK_ENTITY_2];
    s16 primIndex;
    POLY_GT4* poly;

    switch (unkEntity->step) {
    case 0:
        primIndex = g_api.AllocPrimitives(PRIM_G4, 1);
        if (primIndex != -1) {
            poly = &g_PrimBuf[primIndex];
            unkEntity->primIndex = primIndex;
            unkEntity->flags |= FLAG_HAS_PRIMS;
            *(s32*)&unkEntity->ext.generic.unk7C = poly;

            poly->x1 = poly->x3 = 384;
            poly->y0 = poly->y1 = 4;
            poly->y2 = poly->y3 = 228;

            poly->r0 = poly->r1 = poly->r2 = poly->r3 = poly->g0 = poly->g1 =
                poly->g2 = poly->g3 = poly->b0 = poly->b1 = poly->b2 =
                    poly->b3 = poly->x0 = poly->x2 = 0;

            poly->pad2 = 0xC8;
            poly->pad3 = 0x51;

            unkEntity->step++;
        }
        break;

    case 1:
        poly = *(s32*)&unkEntity->ext.generic.unk7C;
        if (D_801BC3E4 != 0) {
            poly->r1 = poly->r2 = poly->r3 = poly->g0 = poly->g1 = poly->g2 =
                poly->g3 = poly->b0 = poly->b1 = poly->b2 = poly->b3 =
                    poly->r0 = poly->b3 + 2;
            if (poly->r0 >= 254) {
                D_801BC3E4 = 0;
                unkEntity->step++;
            }
        }

    case 2:
        break;
    }
}

INCLUDE_ASM("asm/us/st/sel/nonmatchings/3410C", func_801B519C);

void func_801B5350(void) {
    Entity* entity = &g_Entities[UNK_ENTITY_5];

    switch (entity->step) {
    case 0:
        entity->animSet = ANIMSET_DRA(1);
        entity->animCurFrame = 142;
        entity->ext.generic.unk80.modeS32 = 0x800000;
        entity->posY.i.hi = 159;
        entity->zPriority = 0xC0;
        entity->unk5A = 0;
        entity->palette = 0x8100;
        entity->step = 1;
        break;

    case 1:
        entity->animCurFrame = 142;
        break;

    case 2:
        if (!(AnimateEntity(D_80180528, entity) & 0xFF)) {
            func_801B4B9C(entity, 3);
        }
        entity->ext.generic.unk80.modeS32 += 0xFFFE8000;
        break;

    case 3:
        AnimateEntity(D_80180504, entity);
        entity->ext.generic.unk80.modeS32 += 0xFFFE8000;
        if (entity->ext.generic.unk80.modeS16.unk2 < 0x40) {
            entity->step = 255;
        }
        break;
    }
}

void func_801B54C8(void) {
    Entity* e = &g_Entities[UNK_ENTITY_7];

    if (e->step == 0) {
        e->animSet = ANIMSET_OVL(2);
        e->animCurFrame = 38;
        e->facing = 1;
        e->unk5A = 0xF;
        e->ext.generic.unk80.modeS32 = 0x780000;
        e->posY.i.hi = 158;
        e->zPriority = 0xC0;
        e->palette = 0x8210;
        e->step = 1;
    }
}

void func_801B5548(void) {
    Entity* e = &g_Entities[UNK_ENTITY_7];

    if (e->step == 0) {
        e->animSet = ANIMSET_OVL(2);
        e->animCurFrame = 7;
        e->unk5A = 0xF;
        e->ext.generic.unk80.modeS32 = 0x780000;
        e->posY.i.hi = 158;
        e->zPriority = 0xC0;
        e->palette = 0x8210;
        e->facing = 0;
        e->step = 1;
    }
}

INCLUDE_ASM("asm/us/st/sel/nonmatchings/3410C", func_801B55C8);
