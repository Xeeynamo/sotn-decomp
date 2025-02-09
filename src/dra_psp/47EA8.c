// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../dra/dra.h"
#include "../dra/dra_bss.h"

// Given a range of start and end values, finds an unused entity
// slot in g_Entities to fill in. Starts at start, and goes to
// end-1. If none in the range are available, returns NULL.
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

// Like GetFreeEntity, but searches for an open spot
// starting from the end and working backward
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

void func_80118894(Entity* self) {
    s32 i;
    s32 search_value;

    if (self == &g_Entities[E_WEAPON]) {
        if (!(self->params & 0x8000)) {
            self->enemyId = 1;
        } else {
            self->enemyId = 2;
        }
        return;
    }
    // It appears we're looping over elements of the 8013800C array.
    // If the pointer to arg0 comes before the 32nd (0x20th) g_Entities,
    // we iterate through the 8013800C array, starting from element 3 and going
    // as high as 7, searching for our enemy ID. Otherwise we do the same, but
    // starting from element 7 and going up to 11. 8013800C therefore must have
    // 11 elements. It may be possible to refactor this code to remove the
    // duplication.
    // D_8013800C looks to be keeping track of how many abilities/attacks are
    // targeting a specific enemy selecting the lowest targeted entity from 3-6
    // or 7-11
    if (self < &g_Entities[UNK_ENTITY_20]) {
        for (search_value = 0; true; search_value++) {
            for (i = 3; i < 7; i++) {
                if (D_8013800C[i] == search_value) {
                    D_8013800C[i]++;
                    self->enemyId = i;
                    return;
                }
            }
        }
    } else {
        for (search_value = 0; true; search_value++) {
            for (i = 7; i < 11; i++) {
                if (D_8013800C[i] == search_value) {
                    D_8013800C[i]++;
                    self->enemyId = i;
                    return;
                }
            }
        }
    }
}

extern s32 D_80138038; // BSS
Entity* func_80118970(void) {
    s32 big_arr[128];
    Entity* ent;
    s32 i;
    s32 successes;
    s32 index;

    successes = 0;
    // Hunt through these entities looking for ones that match all criteria.
    // Call them a success and increment successes.
    ent = &g_Entities[STAGE_ENTITY_START];
    for (i = 0; i < 128; i++, ent++) {
        big_arr[i] = 0;
        if (!ent->entityId){
            continue;
        }
        if (ent->hitboxState == 0){
            continue;
        }
        if(ent->flags & FLAG_UNK_00200000){
            continue;
        }
        if(ent->posX.i.hi < -0x10){
            continue;
        } 
        if(ent->posX.i.hi > 0x110){
            continue;
        }
        if(ent->posY.i.hi > 0xF0){
            continue;
        } 
        if(ent->posY.i.hi < 0){
            continue;
        }
        if (ent->hitPoints >= 0x7000) {
            continue;
        }
        
        if (ent->flags & FLAG_UNK_80000) {
            successes++;
            big_arr[i] = 1;
        } else {
            ent->flags |= FLAG_UNK_80000;
            return ent;
        }
    }

    if (successes != 0) {
        index = D_80138038 % 128;
        for (i = 0; i < 128; i++) {
            if (big_arr[index] != 0) {
                ent = &g_Entities[STAGE_ENTITY_START + index];
                D_80138038 = (index + 1) % 128;
                return ent;
            }
            index = (index + 1) % 128;
        }
    }
    return NULL;
}

s16 func_80118B18(Entity* ent1, Entity* ent2, s16 facingLeft) {
    s16 var_a1;
    s16 posY;
    s16 posX;
    s16 temp;
    s16 diffY;
    s16 diffX;

    if (ent2 != NULL) {
        posX = ent2->posX.i.hi;
        posY = ent2->posY.i.hi;
    } else {
        posY = 112;
        if (facingLeft) {
            posX = -32;
        } else {
            posX = 288;
        }
    }

    diffX = posX - ent1->posX.i.hi;
    diffY = posY - ent1->posY.i.hi;
    temp = ratan2(-diffY, diffX) & 0xFFF;

    var_a1 = 0;
    if (ent2 != NULL) {
        if (ent2->entityId == E_NONE) {
            var_a1 = 0x1000;
        }
        if (ent2->hitboxState == 0) {
            var_a1 = 0x2000;
        }
        if (ent2->flags & FLAG_UNK_00200000) {
            var_a1 = 0x3000;
        }
    }
    if (ent1->posX.i.hi > 288) {
        var_a1 = 0x4000;
    }

    if (ent1->posX.i.hi < -32) {
        var_a1 = 0x5000;
    }
    if (ent1->posY.i.hi > 240) {
        var_a1 = 0x6000;
    }

    if (ent1->posY.i.hi < 0) {
        var_a1 = 0x7000;
    }
    return temp - var_a1;
}

void func_80118C28(s32 arg0) {
    D_8013803C = D_800ACFB4[arg0][0];
    D_80138040 = D_800ACFB4[arg0][1];
    D_80138044 = D_800ACFB4[arg0][2];
    D_80138048 = D_800ACFB4[arg0][3];
}

s32 CreateHPNumMove(s16 number, s16 type) {
    Entity* entity = GetFreeEntity(0x38, 0x40);

    if (entity == NULL) {
        return -1;
    }
    DestroyEntity(entity);
    entity->entityId = ENTITY_13;
    entity->posX.val = PLAYER.posX.val;
    entity->posY.val = PLAYER.posY.val;
    entity->ext.hpNumMove.number = number;
    entity->ext.hpNumMove.type = type;
    return 0;
}

// number appears and moves to HP meter, probably for healing effects
void EntityNumberMovesToHpMeter(Entity* self) {
    const int PrimCountA = 4;
    const int PrimCountB = 16;
    const int DIGIT_WIDTH = 8;
    Primitive* prim;
    s16 x_to_meter;
    s16 y_to_meter;
    s16 s7;
    s32 i;
    s16 offset_x;
    s16 offset_y;
    u16 number;
    s32 sp3C = -1;
    u8 U_base;

    switch (self->step) {
    case 0:
        number = self->ext.hpNumMove.number;
        self->primIndex = AllocPrimitives(PRIM_GT4, PrimCountA + PrimCountB);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags =
            FLAG_KEEP_ALIVE_OFFCAMERA | FLAG_HAS_PRIMS | FLAG_UNK_10000;
        self->ext.hpNumMove.unk8C = 0;
        self->ext.hpNumMove.unk8E = 2;
        self->ext.hpNumMove.unk90 = 8;

        self->ext.hpNumMove.digits[0] = number % 10;
        number /= 10;
        if (number) {
            self->ext.hpNumMove.digits[1] = number % 10;
            number /= 10;
            self->ext.hpNumMove.nDigits++;
            if (number) {
                self->ext.hpNumMove.digits[2] = number % 10;
                number /= 10;
                self->ext.hpNumMove.nDigits++;
                if(number){
                    self->ext.hpNumMove.digits[3] = number % 10;
                    self->ext.hpNumMove.nDigits++;
                }
            }
        }

        // iterate through all 0x14 prims created by AllocPrimitives in two
        // batches
        prim = &g_PrimBuf[self->primIndex];
        for (i = 0; i < PrimCountA; i++) {
            prim->clut = 0x1B2;
            if (self->ext.hpNumMove.number == 0) {
                prim->clut = 0x1B4;
            }
            if (self->ext.hpNumMove.type == 1) {
                prim->clut = 0x1B8;
            }
            if (self->ext.hpNumMove.type == 2) {
                prim->clut = 0x1B6;
            }
            prim->tpage = 0x1A;
            prim->priority = 0x1B8;
            prim->drawMode = DRAW_DEFAULT;
            U_base = self->ext.hpNumMove.digits[i] * DIGIT_WIDTH;
            if (self->ext.hpNumMove.digits[i]) {
                // adjust zero-based indexing to one-based
                U_base -= DIGIT_WIDTH;
            } else {
                // zero digit is at the end of the UV table
                U_base += DIGIT_WIDTH * 9;
            }
            prim->u0 = U_base + 32;
            prim->v0 = 64;
            prim->u1 = U_base + 40;
            prim->v1 = 64;
            prim->u2 = U_base + 32;
            prim->v2 = 73;
            prim->u3 = U_base + 40;
            prim->v3 = 73;
            if (self->ext.hpNumMove.nDigits < i) {
                prim->drawMode = DRAW_HIDE;
            }
            prim = prim->next;
        }
        for (i = 0; i < PrimCountB; i++) {
            prim->type = PRIM_TILE;
            prim->r0 = 0xFF;
            prim->g0 = 0x40;
            prim->b0 = 0x40;
            if (self->ext.hpNumMove.number == 0) {
                prim->r0 = 0x40;
                prim->g0 = 0x40;
                prim->b0 = 0xFF;
            }
            if (self->ext.hpNumMove.type == 1) {
                prim->r0 = 0x40;
                prim->g0 = 0xFF;
                prim->b0 = 0x40;
            }
            if (self->ext.hpNumMove.type == 2) {
                prim->r0 = 0xFF;
                prim->g0 = 0x40;
                prim->b0 = 0xFF;
            }
            prim->priority = 0x1B8;
            prim->drawMode = DRAW_HIDE | DRAW_UNK02;

            
            prim->u0 = prim->v0 = 1;
            prim = prim->next;
        }

        self->step++;
        break;
    case 1:
        self->ext.hpNumMove.unk8C++;
        self->ext.hpNumMove.unk8E++;
        if (self->ext.hpNumMove.type != 2) {
            self->posY.i.hi--;
        }
        if (--self->ext.hpNumMove.unk90 == 0) {
            self->ext.hpNumMove.unk90 = 8;
            self->step++;
        }
        break;
    case 2:
        self->ext.hpNumMove.unk8C--;
        self->ext.hpNumMove.unk8E--;
        if (self->ext.hpNumMove.unk8C == 4) {
            self->step++;
            self->ext.hpNumMove.unk90 = 4;
        }
        break;
    case 3:
        self->ext.hpNumMove.unk8C++;
        self->ext.hpNumMove.unk8E++;
        if (self->ext.hpNumMove.type != 2) {
            self->posY.i.hi--;
        }
        if (--self->ext.hpNumMove.unk90 == 0) {
            self->ext.hpNumMove.unk90 = 3;
            self->step++;
        }
        break;
    case 4:
        self->ext.hpNumMove.unk8C--;
        self->ext.hpNumMove.unk8E--;
        if (self->ext.hpNumMove.unk8C == 4) {
            self->ext.hpNumMove.unk90 = 24;
            self->step++;
        }
        break;
    case 5:
        if (--self->ext.hpNumMove.unk90 == 0) {
            x_to_meter = self->posX.i.hi - 0xD;
            y_to_meter = self->posY.i.hi - 0x46;
            self->ext.hpNumMove.angleToMeter =
                ratan2(-y_to_meter, x_to_meter) & 0xFFF;
            self->ext.hpNumMove.distToMeter =
                SquareRoot0(SQ(x_to_meter) + SQ(y_to_meter));
            self->ext.hpNumMove.unk90 = 0x10;
            self->ext.hpNumMove.unk98 = 0;
            self->step++;
        }
        break;
    case 6:
        if (self->ext.hpNumMove.unk8C != 2) {
            self->ext.hpNumMove.unk8C--;
            self->ext.hpNumMove.unk8E--;
        }
        self->ext.hpNumMove.unk90--;
        sp3C = self->ext.hpNumMove.unk90;
        // Reuse of variables. X and Y are actually R and theta.
        y_to_meter = self->ext.hpNumMove.angleToMeter;
        x_to_meter = self->ext.hpNumMove.distToMeter * self->ext.hpNumMove.unk90 / 16;
        self->posX.i.hi =
            13 + (((rcos(y_to_meter) >> 4) * x_to_meter) >> 8);
        self->posY.i.hi =
            70 - (((rsin(y_to_meter) >> 4) * x_to_meter) >> 8);
        self->ext.hpNumMove.unk98 += 0x100;
        self->posX.i.hi += rcos(self->ext.hpNumMove.unk98) >> 9;
        self->posY.i.hi -= rsin(self->ext.hpNumMove.unk98) >> 9;
        if (self->ext.hpNumMove.unk90 == 0) {
            if (self->ext.hpNumMove.type == 2) {
                DestroyEntity(self);
                return;
            }
                self->step++;
        }
        break;
    case 7:
    case 9:
        self->ext.hpNumMove.unk8C++;
        self->ext.hpNumMove.unk8E++;
        if (self->ext.hpNumMove.unk8C == 7) {
            self->step++;
            self->ext.hpNumMove.unk90 = 0x18;
        }
        break;
    case 8:
        if (self->ext.hpNumMove.unk8C != 4) {
            self->ext.hpNumMove.unk8C--;
            self->ext.hpNumMove.unk8E--;
        } else {
            self->step++;
        }
        break;
    case 10:
        if (self->ext.hpNumMove.unk8C != 4) {
            self->ext.hpNumMove.unk8C--;
            self->ext.hpNumMove.unk8E--;
        }
        if (--self->ext.hpNumMove.unk90 == 0) {
            self->step++;
        }
        break;
    case 11:
        self->ext.hpNumMove.unk92 += 2;
        self->posX.i.hi -= 2;
        if (!(--self->ext.hpNumMove.unk90 & 2)) {
            self->ext.hpNumMove.unk8E--;
        }
        if (self->ext.hpNumMove.unk8E == 0) {
            DestroyEntity(self);
            return;
        }
        break;
    }

    offset_x = self->ext.hpNumMove.unk8C;
    offset_y = self->ext.hpNumMove.unk8E;
    if (self->step != 0xB) {
        self->ext.hpNumMove.unk92 = self->posX.i.hi;
    }
    x_to_meter = self->posX.i.hi + (offset_x * self->ext.hpNumMove.nDigits);
    s7 = self->ext.hpNumMove.unk92 + (offset_x * self->ext.hpNumMove.nDigits);
    y_to_meter = self->posY.i.hi - 0x10;

    // iterate through all 0x14 prims created by AllocPrimitives in two batches
    prim = &g_PrimBuf[self->primIndex];
    for (i = 0; i < PrimCountA; i++) {
        prim->x0 = x_to_meter - offset_x;
        prim->y0 = y_to_meter - offset_y;
        prim->x1 = x_to_meter + offset_x;
        prim->y1 = y_to_meter - offset_y;
        prim->x2 = s7 - offset_x;
        prim->y2 = y_to_meter + offset_y;
        prim->x3 = s7 + offset_x;
        prim->y3 = y_to_meter + offset_y;
        x_to_meter -= (offset_x * 2) - 3;
        s7 -= (offset_x * 2) - 3;
        prim = prim->next;
    }
    for (i = 0; i < PrimCountB; i++) {
        if (prim->r1) {
            if (--prim->g1 == 0) {
                prim->drawMode = DRAW_HIDE;
            }
            prim->y0++;
        } else if (sp3C == i) {
            prim->drawMode &= ~DRAW_HIDE;
            prim->x0 = self->posX.i.hi;
            prim->y0 = self->posY.i.hi;
            prim->r1++;
            prim->g1 = 0xC;
        }
        prim = prim->next;
    }
}

INCLUDE_ASM("dra_psp/psp/dra_psp/47EA8", func_psp_09125DB8);

INCLUDE_ASM("dra_psp/psp/dra_psp/47EA8", EntityGuardText);

INCLUDE_ASM("dra_psp/psp/dra_psp/47EA8", EntitySmallRisingHeart);

INCLUDE_ASM("dra_psp/psp/dra_psp/47EA8", func_80119E78);

INCLUDE_ASM("dra_psp/psp/dra_psp/47EA8", func_80119F70);

INCLUDE_ASM("dra_psp/psp/dra_psp/47EA8", func_8011A290);

INCLUDE_ASM("dra_psp/psp/dra_psp/47EA8", func_8011A328);

INCLUDE_ASM("dra_psp/psp/dra_psp/47EA8", func_psp_09127348);

INCLUDE_ASM("dra_psp/psp/dra_psp/47EA8", func_8011A4C8);

INCLUDE_ASM("dra_psp/psp/dra_psp/47EA8", func_8011A4D0);

INCLUDE_ASM("dra_psp/psp/dra_psp/47EA8", func_psp_091279A0);

INCLUDE_ASM("dra_psp/psp/dra_psp/47EA8", func_psp_09127B50);

INCLUDE_ASM("dra_psp/psp/dra_psp/47EA8", CreateEntFactoryFromEntity);

INCLUDE_ASM("dra_psp/psp/dra_psp/47EA8", EntityEntFactory);

INCLUDE_ASM("dra_psp/psp/dra_psp/47EA8", EntityUnarmedAttack);

INCLUDE_ASM("dra_psp/psp/dra_psp/47EA8", EntityDiveKickAttack);

INCLUDE_ASM("dra_psp/psp/dra_psp/47EA8", func_8011B480);

INCLUDE_ASM("dra_psp/psp/dra_psp/47EA8", func_8011B530);

INCLUDE_ASM("dra_psp/psp/dra_psp/47EA8", func_8011B5A4);

INCLUDE_ASM("dra_psp/psp/dra_psp/47EA8", EntityUnkId24);

INCLUDE_ASM("dra_psp/psp/dra_psp/47EA8", func_psp_091295F0);

INCLUDE_ASM("dra_psp/psp/dra_psp/47EA8", EntityPlayerBlinkWhite);

INCLUDE_ASM("dra_psp/psp/dra_psp/47EA8", EntityPlayerOutline);

INCLUDE_ASM("dra_psp/psp/dra_psp/47EA8", func_8011E0E4);

INCLUDE_ASM("dra_psp/psp/dra_psp/47EA8", EntityGravityBootBeam);

INCLUDE_ASM("dra_psp/psp/dra_psp/47EA8", EntityWingSmashTrail);
