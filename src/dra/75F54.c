#include "common.h"
#include "dra.h"
#include "objects.h"
#include "sfx.h"

INCLUDE_ASM("asm/us/dra/nonmatchings/75F54", func_80115F54);

INCLUDE_ASM("asm/us/dra/nonmatchings/75F54", func_80116208);

INCLUDE_ASM("asm/us/dra/nonmatchings/75F54", func_80116408);

void func_801166A4(void) {
    switch (PLAYER.unk2E) {
    case 0:
        func_80113EE0();
        D_80072F60[0] = 0x8166;
        D_80072F04 = 6;
        PLAYER.accelerationX = 0;
        PLAYER.accelerationY = 0;
        PLAYER.unkAC = 0x33;
        func_8011AAFC(g_CurrentEntity, 0, 0);
        func_8011AAFC(g_CurrentEntity, 0x58002C, 0);
        PLAYER.unk2E++;
        break;

    case 1:
        if (PLAYER.animFrameDuration < 0) {
            PlaySfx(NA_SE_VO_AL_WHAT);
            func_8010E570(0);
        }
        break;

    default:
        break;
    }
}

void func_8011678C(void) {
    PLAYER.accelerationY = 0;
    PLAYER.accelerationX = 0;
    if (D_80072EF6 != 2) {
        func_8010E570(0);
    }
}

void func_801167D0(void) {
    s32* accelerationX = &PLAYER.accelerationX;
    PLAYER.accelerationY = 0;
    *accelerationX = 0;
    if (D_80072EF6 != 2) {
        PLAYER.step = 0x28;
        PLAYER.unk2E = 0;
        PLAYER.accelerationY = 0;
        *accelerationX = 0;
        PLAYER.unkAC = 0xCF;
        PLAYER.animFrameIdx = 0;
        PLAYER.animFrameDuration = 0;
    }
}

bool func_80116838(void) {
    if ((g_EntityArray->unk2E != 0) &&
        ((D_8009744C != 0) || (D_80072EEC & 8) || (func_800FEEA4(0, 1) < 0))) {
        func_8010D584(9);
        func_8010DA48(0xCA);
        D_800AFDA6 = 6;
        g_EntityArray->palette = 0x810D;
        D_80072F86 = 0;
        D_80072F88 = 0;
        func_8011AAFC(g_CurrentEntity, 0x21002C, 0);
        g_EntityArray->accelerationY = g_EntityArray->accelerationY >> 1;
        return true;
    }
    return false;
}

void func_8011690C(s16 arg0) {
    s16* player_unk1E = &PLAYER.unk1E;

    if (*player_unk1E < arg0) {
        *player_unk1E += 16;
        if (arg0 < *player_unk1E) {
            *player_unk1E = arg0;
        }
    }
    if (arg0 < *player_unk1E) {
        *player_unk1E -= 16;
        if (*player_unk1E < arg0) {
            *player_unk1E = arg0;
        }
    }
}

INCLUDE_ASM("asm/us/dra/nonmatchings/75F54", func_80116994);

INCLUDE_ASM("asm/us/dra/nonmatchings/75F54", func_80116B0C);

INCLUDE_ASM("asm/us/dra/nonmatchings/75F54", func_801177A0);

INCLUDE_ASM("asm/us/dra/nonmatchings/75F54", func_80117AC0);

INCLUDE_ASM("asm/us/dra/nonmatchings/75F54", func_80117D3C);

INCLUDE_ASM("asm/us/dra/nonmatchings/75F54", func_80117DEC);

INCLUDE_ASM("asm/us/dra/nonmatchings/75F54", func_801182F8);

void func_80118614(void) {
    if (PLAYER.animFrameDuration < 0) {
        func_8010E570(0);
    }
}

void func_80118640(void) {
    if (PLAYER.animFrameDuration < 0) {
        func_8010E470(0, 0);
    }
}

void func_80118670(void) {
    s32* animFrameIdx = (s32*)&PLAYER.animFrameIdx;

    if (*animFrameIdx == 0x10007) {
        func_8011AAFC(g_CurrentEntity, 0x160028, 0);
        PlaySfx(NA_SE_PL_MP_GAUGE);
        func_8011AAFC(g_CurrentEntity, 0x70, 0);
    }
    if (PLAYER.animFrameDuration < 0) {
        func_8010E570(0);
    }
}

void func_801186EC(void) {
    if (PLAYER.unk2E == 0) {
        if (g_EntityArray[UNK_ENTITY_10].objectId == 0) {
            D_80138008 = 0x10;
            func_8011AAFC(g_CurrentEntity, 0x15003D, 0);
            PLAYER.unk2E++;
        }
    } else if (--D_80138008 == 0) {
        PLAYER.palette = 0x8100;
        func_8010E570(0);
    }
}

Entity* GetFreeDraEntity(s16 start, s16 end) {
    Entity* entity = &g_EntityArray[start];
    s16 i;

    for (i = start; i < end; i++, entity++) {
        if (entity->objectId == ENTITY_UNALLOCATED) {
            return entity;
        }
    }
    return NULL;
}

INCLUDE_ASM("asm/us/dra/nonmatchings/75F54", func_80118810);

INCLUDE_ASM("asm/us/dra/nonmatchings/75F54", func_80118894);

INCLUDE_ASM("asm/us/dra/nonmatchings/75F54", func_80118970);

s32 func_80118B18(Entity* ent1, Entity* ent2, s32 arg2) {
    s16 var_a1;
    s16 posX;
    s16 posY;
    u16 temp;

    if (ent2 != NULL) {
        posX = ent2->posX.i.hi;
        posY = ent2->posY.i.hi;
    } else {
        posY = 112;
        if ((arg2 << 0x10) != 0) {
            posX = -32;
        } else {
            posX = 288;
        }
    }

    posX = posX - ent1->posX.i.hi;
    temp = ratan2(-(s16)(posY - ent1->posY.i.hi), posX) & 0xFFF;

    var_a1 = 0;
    if (ent2 != NULL) {
        var_a1 = (ent2->objectId == 0) << 0xC;
        if (ent2->unk3C == 0) {
            var_a1 = 0x2000;
        }
        if (ent2->flags & 0x200000) {
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
    posX = temp - var_a1;
    return posX;
}

void func_80118C28(s32 arg0) {
    D_8013803C = D_800ACFB4[arg0][0];
    D_80138040 = D_800ACFB4[arg0][1];
    D_80138044 = D_800ACFB4[arg0][2];
    D_80138048 = D_800ACFB4[arg0][3];
}

s32 func_80118C84(s16 arg0, s16 arg1) {
    Entity* entity = GetFreeDraEntity(0x38, 0x40);

    if (entity != NULL) {
        DestroyEntity(entity);
        entity->objectId = ENTITY_13;
        entity->posX.val = PLAYER.posX.val;
        entity->posY.val = PLAYER.posY.val;
        entity->unk80.modeS16.unk0 = arg0;
        entity->unk80.modeS16.unk2 = arg1;
        return 0;
    }
    return -1;
}

// number appears and moves to HP meter, probably for healing effects
INCLUDE_ASM("asm/us/dra/nonmatchings/75F54", EntityNumberMovesToHpMeter);

// "Guard" text displays on screen
INCLUDE_ASM("asm/us/dra/nonmatchings/75F54", EntityGuardText);

void func_80119D3C(Entity* entity) {
    s32 temp;
    s32 cos;

    switch (entity->step) {
    case 0:
        entity->posY.i.hi -= 16;
        entity->zPriority = PLAYER.zPriority - 2;
        entity->unk7C.s = 0;
        entity->step++;
        entity->accelerationY = -0x8000;
        entity->unk7E.modeU16 = 0x40;
        entity->animCurFrame = 0xE;
        entity->animSet = 3;
        entity->unk80.modeS16.unk0 = 0x80;
        entity->flags = FLAG_UNK_08000000;
        break;

    case 1:
        if (entity->unk80.modeS16.unk0 < 32) {
            entity->unk19 = 128;
        }
        entity->posY.val += entity->accelerationY;
        cos = rcos(entity->unk7C.s);
        entity->unk7C.s = entity->unk7C.s + entity->unk7E.modeU16;
        temp = cos * 8;

        if (!(D_8003C8C4 & 3)) {
            entity->unk7E.modeU16--;
        }
        entity->posX.val += temp;
        entity->unk80.modeS16.unk0--;
        if (entity->unk80.modeS16.unk0 == 0) {
            DestroyEntity(entity);
        }
        break;
    }
}

INCLUDE_ASM("asm/us/dra/nonmatchings/75F54", func_80119E78);

INCLUDE_ASM("asm/us/dra/nonmatchings/75F54", func_80119F70);

void func_8011A290(Entity* entity) {
    SubweaponDef subwpn;

    func_800FE3C4(&subwpn, entity->unkB0, 0);
    entity->attack = subwpn.attack;
    entity->attackElement = subwpn.attackElement;
    entity->unk3C = subwpn.sp1C;
    entity->unk49 = subwpn.sp17;
    entity->unk58 = subwpn.sp18;
    entity->unk6A = subwpn.sp1E;
    entity->objectRoomIndex = subwpn.sp22;
    entity->unkB2 = subwpn.sp20;
    func_80118894(entity);
}

void func_8011A328(Entity* entity, s32 arg1) {
    SpellDef spell;

    func_800FD9D4(&spell, arg1);
    entity->attack = spell.attack;
    entity->attackElement = spell.attackElement;
    entity->unk3C = spell.unk10;
    entity->unk49 = spell.unk0D;
    entity->unk58 = spell.unk0E;
    entity->unk6A = spell.unk12;
    entity->objectRoomIndex = spell.unk14;
    func_80118894(entity);
}

void func_8011A3AC(Entity* arg0, s32 arg1, s32 arg2, Unkstruct_8011A3AC* arg3) {
    SpellDef spell;

    *arg3 = D_80097C38[D_8006CBC4];
    if (arg2 != 0) {
        func_800FD9D4(&spell, arg1);
        arg0->attack = spell.attack;
        arg0->attackElement = spell.attackElement;
        arg0->unk3C = spell.unk10;
        arg0->unk49 = spell.unk0D;
        arg0->unk58 = spell.unk0E;
        arg0->unk6A = spell.unk12;
        arg0->objectRoomIndex = spell.unk14;
        arg0->attack = spell.attack * ((arg3->unk0 * 4 / 95) + 1);
        func_80118894(arg0);
    }
}

void func_8011A4C8(Entity* entity) {}

INCLUDE_ASM("asm/us/dra/nonmatchings/75F54", func_8011A4D0);

void func_8011A870(void) {
    Entity* entity = g_CurrentEntity = &g_EntityArray[UNK_ENTITY_4];
    u16 objectId;
    s32 i = 4;

loop_1: // !FAKE: this should be a for loop
    objectId = entity->objectId;

    if (objectId != 0) {
        if (entity->step == 0) {
            if ((u32)(entity->objectId - 0xD0) < 0x10) {
                entity->pfnUpdate = (PfnEntityUpdate)D_8016FCC0[objectId];
            } else {
                goto label;
            }
        }

        if (entity->pfnUpdate != NULL) {
            entity->pfnUpdate(entity);
            entity = g_CurrentEntity;
            if (entity->objectId != 0) {
                if ((!(entity->flags & FLAG_UNK_04000000)) &&
                    (((u32)((((u16)entity->posX.i.hi) + 0x20) & 0xFFFF) >=
                      0x141) ||
                     ((u32)((((u16)entity->posY.i.hi) + 0x10) & 0xFFFF) >=
                      0x111))) {
                    DestroyEntity(entity);
                    goto label;
                } else if (entity->flags & 0x100000) {
                    UpdateAnim(NULL, D_800ACFB4);
                }
            }
        }
    }
label:
    i++;
    g_CurrentEntity++;
    entity++;

    if (i < 8)
        goto loop_1;
}

INCLUDE_ASM("asm/us/dra/nonmatchings/75F54", func_8011A9D8);

Entity* func_8011AAFC(Entity* self, u32 flags, s32 arg2) {
    Entity* entity;
    s16 temp = arg2;

    entity = GetFreeDraEntity(8, 16);
    if (entity == NULL) {
        return NULL;
    }

    DestroyEntity(entity);
    entity->objectId = 1;
    entity->unk8C.entityPtr = self;
    entity->posX.val = self->posX.val;
    entity->posY.val = self->posY.val;
    entity->facing = self->facing;
    entity->zPriority = self->zPriority;
    entity->subId = flags & 0xFFF;
    if (flags & 0x5000) {
        entity->unkA8 = 0xE0;
    }
    if (flags & 0xA000) {
        entity->unkA8 = 0xF0;
    }
    entity->unkA0 = (flags >> 8) & 0xFF00;
    entity->unk92 = temp;
    if (self->flags & FLAG_UNK_10000) {
        entity->flags |= FLAG_UNK_10000;
    }
    if (flags & 0x1000) {
        entity->objectId = 0xEF;
    }
    if (flags & 0x2000) {
        entity->objectId = 0xFF;
    }
    if (flags & 0x4000) {
        entity->objectId = 0xED;
    }
    if (flags & 0x8000) {
        entity->objectId = 0xFD;
    }

    return entity;
}

INCLUDE_ASM("asm/us/dra/nonmatchings/75F54", func_8011AC3C);

INCLUDE_ASM("asm/us/dra/nonmatchings/75F54", func_8011B190);

void func_8011B334(Entity* entity) {
    Unkstruct_8011B334 temp;

    if (PLAYER.unk2E != 0x70) {
        DestroyEntity(entity);
        return;
    }

    entity->flags = 0x60000;
    entity->facing = PLAYER.facing;
    entity->posY.i.hi = PLAYER.posY.i.hi;
    entity->posX.i.hi = PLAYER.posX.i.hi;
    D_80072F60[2] &= 0xFF7F;

    if (entity->step == 0) {
        func_800FE728(0, &temp, 0);
        entity->attack = temp.unk8;
        entity->attackElement = temp.unkC;
        entity->unk3C = temp.unk28;
        entity->unk49 = temp.unk1A;
        entity->unk58 = temp.unk26;
        entity->unk6A = temp.unk2A;
        entity->objectRoomIndex = temp.unk30;
        func_80118894(entity);
        entity->unk10 = 9;
        entity->unk12 = 0x15;
        entity->hitboxWidth = 4;
        entity->hitboxHeight = 5;
        entity->step++;
    } else if (entity->unk48 == 1) {
        D_80072F60[2] |= 0x80;
    }
}

INCLUDE_ASM("asm/us/dra/nonmatchings/75F54", func_8011B480);

void func_8011B530(Entity* entity) {
    if (PLAYER.step != 0x25) {
        DestroyEntity(entity);
    } else if (entity->step == 0) {
        entity->flags = 0x60000;
        func_8011A328(entity, 5);
        entity->step++;
    }
}

INCLUDE_ASM("asm/us/dra/nonmatchings/75F54", func_8011B5A4);

INCLUDE_ASM("asm/us/dra/nonmatchings/75F54", func_8011BBE0);

// same as RIC/func_80162E9C
bool func_8011BD48(Entity* entity) {
    s32 i = 0x10;
    s16 objId = entity->objectId;
    s16 subId = entity->subId;
    Entity* e = &g_EntityArray[i];
    for (; i < 0x40; i++, e++) {
        if (objId == (s32)e->objectId && subId == (s32)e->subId &&
            e != entity) {
            return true;
        }
    }

    return false;
}

// player turns white for some sort of status effect
INCLUDE_ASM("asm/us/dra/nonmatchings/75F54", EntityPlayerBlinkWhite);

// blue outline around player when mp refills
INCLUDE_ASM("asm/us/dra/nonmatchings/75F54", EntityMpReplenished);

void func_8011E0E4(Entity* entity) {}

INCLUDE_ASM("asm/us/dra/nonmatchings/75F54", func_8011E0EC);

INCLUDE_ASM("asm/us/dra/nonmatchings/75F54", func_8011E390);

INCLUDE_ASM("asm/us/dra/nonmatchings/75F54", func_8011E4BC);

void func_8011EDA0(Entity* entity) {}

INCLUDE_ASM("asm/us/dra/nonmatchings/75F54", func_8011EDA8);

// same as RIC/func_801601DC
void func_8011F074(Entity* entity) {
    s16 posX;
    s16 posY;

    switch (entity->step) {
    case 0:
        entity->flags = 0x120000 | FLAG_UNK_08000000;
        entity->unk5A = 0x79;
        entity->animSet = 0xE;
        entity->zPriority = PLAYER.zPriority + 2;
        entity->palette = 0x819F;

        if (D_8013808C & 1) {
            entity->blendMode = 0x70;
        } else {
            entity->blendMode = 0x10;
        }
        entity->unk1C = 0x40;
        entity->unk1A = 0x40;
        entity->unk4C = &D_800ADC44;
        D_8013808C++;
        entity->unk6C = 0xFF;
        entity->unk19 = 0x33;
        posX = 10;
        posY = 15;
        entity->posY.i.hi = entity->posY.i.hi - posY + (rand() % 35);
        entity->posX.i.hi = entity->posX.i.hi - posX + (rand() % 20);
        entity->accelerationY = -0x6000 - (rand() & 0x3FFF);
        entity->step++;
        break;

    case 1:
        if (entity->unk6C >= 17) {
            entity->unk6C += 248;
        }
        entity->posY.val += entity->accelerationY;
        entity->unk1A += 8;
        entity->unk1C += 8;
        if (entity->animFrameDuration < 0) {
            DestroyEntity(entity);
        }
        break;
    }
}

// effect when player takes lightning damage
INCLUDE_ASM("asm/us/dra/nonmatchings/75F54", EntityHitByLightning);

// player gets frozen
INCLUDE_ASM("asm/us/dra/nonmatchings/75F54", EntityHitByIce);

// transparent white circle closes over player
INCLUDE_ASM("asm/us/dra/nonmatchings/75F54", EntityTransparentWhiteCircle);

// pink effect on player
INCLUDE_ASM("asm/us/dra/nonmatchings/75F54", EntityPlayerPinkEffect);

// player dissolves into pixels
INCLUDE_ASM("asm/us/dra/nonmatchings/75F54", EntityPlayerDissolves);

// level up animation
INCLUDE_ASM("asm/us/dra/nonmatchings/75F54", EntityLevelUpAnimation);

extern Unkstruct_80138094 D_80138094[];

void func_80121F14(s32 arg0, s32 arg1) {
    Unkstruct_80138094* ptr = D_80138094;
    s32 i;

    for (i = 0; i < 16; i++, ptr++) {
        ptr->unk0 = arg0 + ptr->unk0;
        ptr->unk4 = arg1 + ptr->unk4;
    }
}

INCLUDE_ASM("asm/us/dra/nonmatchings/75F54", func_80121F58);

// spawns mist (player transform)
INCLUDE_ASM("asm/us/dra/nonmatchings/75F54", EntityMist);

INCLUDE_ASM("asm/us/dra/nonmatchings/75F54", func_80123788);

INCLUDE_ASM("asm/us/dra/nonmatchings/75F54", func_801238CC);

void func_80123A60(Entity* entity) {
    Entity* player = &PLAYER;

    if (!(D_80072F2C & 0x01000000)) {
        DestroyEntity(entity);
        return;
    }

    entity->posX.i.hi = player->posX.i.hi;
    entity->posY.i.hi = player->posY.i.hi;
    if (entity->step == 0) {
        func_8011A328(entity, 0xB);
        entity->flags = 0x60000 | FLAG_UNK_04000000;
        entity->step++;
    }

    if (player->animCurFrame == 5) {
        entity->hitboxWidth = 12;
        entity->hitboxHeight = 32;
        entity->unk10 = 0x1C;
        entity->unk12 = -0xC;
        return;
    }

    if (player->animCurFrame == 6) {
        entity->hitboxWidth = 10;
        entity->hitboxHeight = 10;
        entity->unk10 = 0x1C;
        entity->unk12 = 0x10;
        return;
    }

    DestroyEntity(entity);
}

INCLUDE_ASM("asm/us/dra/nonmatchings/75F54", func_80123B40);

void func_80123F78(Entity* entity) {
    if (D_800973FC == 0) {
        D_80097F3F = 0;
        DestroyEntity(entity);
        return;
    }

    switch (entity->step) {
    case 0:
        entity->flags = 0x30000 | FLAG_UNK_04000000 | FLAG_UNK_08000000;
        if (PLAYER.animSet != 1) {
            DestroyEntity(entity);
            break;
        }
        entity->animSet = 1;
        entity->animCurFrame = PLAYER.animCurFrame;
        entity->unk5A = 0xD;
        entity->unk19 = PLAYER.unk19;
        entity->blendMode = 0x30;
        entity->palette = 0x815F;
        entity->zPriority = PLAYER.zPriority - 2;
        entity->facing = PLAYER.facing;
        do { // TODO: !FAKE
        } while (0);
        D_80097F4A = 0x80;
        D_80097F46 = 0x80;
        D_80097F42 = 0x80;
        D_80097F3E = 0x80;
        D_80097F49 = 0x80;
        D_80097F45 = 0x80;
        D_80097F41 = 0x80;
        D_80097F3D = 0x80;
        D_80097F48 = 0x80;
        D_80097F44 = 0x80;
        D_80097F40 = 0x80;
        D_80097F3C = 0x80;
        D_80097F3F = 1;
        do { // TODO: !FAKE
        } while (0);
        entity->step++;
        break;

    case 1:
        D_80097F4A += 255;
        if (D_80097F4A < 4) {
            D_80097F3F = 0;
            DestroyEntity(entity);
            break;
        }
        D_80097F46 = D_80097F4A;
        D_80097F42 = D_80097F4A;
        D_80097F3E = D_80097F4A;
        D_80097F49 = D_80097F4A;
        D_80097F45 = D_80097F4A;
        D_80097F41 = D_80097F4A;
        D_80097F3D = D_80097F4A;
        D_80097F48 = D_80097F4A;
        D_80097F44 = D_80097F4A;
        D_80097F40 = D_80097F4A;
        D_80097F3C = D_80097F4A;
        break;
    }
}

void func_80124164(POLY_GT4* poly, s32 colorIntensity, s32 y, s32 radius,
                   bool arg4) {
    s16 top = y - radius;
    s16 bottom = y + radius;
    s32 colorChannel;

    poly->y1 = top;
    poly->y0 = top;

    poly->y3 = bottom;
    poly->y2 = bottom;

    if (poly->y0 < 0) {
        poly->y1 = 0;
        poly->y0 = 0;
    }

    if (poly->y0 > 240) {
        poly->y3 = 240;
        poly->y2 = 240;
    }

    if (arg4 == 0) {
        colorChannel = colorIntensity * D_800AE270[0];
        if (colorChannel < 0) {
            colorChannel += 255;
        }
        poly->r3 = (u32)colorChannel >> 8;
        poly->r1 = (u32)colorChannel >> 8;

        colorChannel = colorIntensity * D_800AE270[1];
        if (colorChannel < 0) {
            colorChannel += 255;
        }
        poly->g3 = (u32)colorChannel >> 8;
        poly->g1 = (u32)colorChannel >> 8;

        colorChannel = colorIntensity * D_800AE270[2];
        if (colorChannel < 0) {
            colorChannel += 255;
        }
        poly->b3 = (u32)colorChannel >> 8;
        poly->b1 = (u32)colorChannel >> 8;

        colorChannel = colorIntensity * D_800AE270[3];
        if (colorChannel < 0) {
            colorChannel += 255;
        }
        poly->r2 = (u32)colorChannel >> 8;
        poly->r0 = (u32)colorChannel >> 8;

        colorChannel = colorIntensity * D_800AE270[4];
        if (colorChannel < 0) {
            colorChannel += 255;
        }
        poly->g2 = (u32)colorChannel >> 8;
        poly->g0 = (u32)colorChannel >> 8;

        colorChannel = colorIntensity * D_800AE270[5];
    } else {
        colorChannel = colorIntensity * D_800AE270[0];
        if (colorChannel < 0) {
            colorChannel += 255;
        }
        poly->r3 = (u32)colorChannel >> 8;
        poly->r1 = (u32)colorChannel >> 8;

        colorChannel = colorIntensity * D_800AE270[1];
        if (colorChannel < 0) {
            colorChannel += 255;
        }
        poly->g3 = (u32)colorChannel >> 8;
        poly->g1 = (u32)colorChannel >> 8;

        colorChannel = colorIntensity * D_800AE270[2];
        if (colorChannel < 0) {
            colorChannel += 255;
        }
        poly->b3 = (u32)colorChannel >> 8;
        poly->b1 = (u32)colorChannel >> 8;

        colorChannel = colorIntensity * D_800AE270[6];
        if (colorChannel < 0) {
            colorChannel += 255;
        }
        poly->r2 = (u32)colorChannel >> 8;
        poly->r0 = (u32)colorChannel >> 8;

        colorChannel = colorIntensity * D_800AE270[7];
        if (colorChannel < 0) {
            colorChannel += 255;
        }
        poly->g2 = (u32)colorChannel >> 8;
        poly->g0 = (u32)colorChannel >> 8;
        colorChannel = colorIntensity * D_800AE270[8];
    }
    if (colorChannel < 0) {
        colorChannel += 255;
    }
    poly->b2 = (u32)colorChannel >> 8;
    poly->b0 = (u32)colorChannel >> 8;
}

// teleport effect like when using library card (ID 0x42)
INCLUDE_ASM("asm/us/dra/nonmatchings/75F54", EntityTeleport);

void func_80124A8C(Entity* entity) {
#ifdef PSY_Q_3_5
    if (PLAYER.step != 0 || PLAYER.unk2E != 4) { // REAL: Matches with PSY-Q 3.5
#else
    if (*(s32*)&PLAYER.step != 0x40000) { // !FAKE: Probably ASPSX
#endif
        DestroyEntity(entity);
        return;
    }

    switch (entity->step) {
    case 0:
        entity->animSet = 0x11;
        entity->accelerationY = -0x6000;
        AccelerateX(0x4000);
        entity->unk5A = 0x50;
        entity->palette = 0x819F;
        entity->unk4C = &D_800AE294;
        entity->flags = 0x100000;
        entity->facing = 0;
        entity->posY.i.hi -= 16;
        entity->posX.val += entity->accelerationX << 5;
        entity->step++;
        break;

    case 1:
        entity->posX.val += entity->accelerationX;
        entity->posY.val += entity->accelerationY;
        if (entity->animFrameDuration < 0) {
            DestroyEntity(entity);
        }
        break;
    }
}

// dagger thrown when using subweapon
INCLUDE_ASM("asm/us/dra/nonmatchings/75F54", EntitySubwpnThrownDagger);

// axe thrown when using subweapon
INCLUDE_ASM("asm/us/dra/nonmatchings/75F54", EntitySubwpnThrownAxe);

// Matches perfectly on PSY-Q 3.5: https://decomp.me/scratch/dhDdI
#ifndef NON_MATCHING
INCLUDE_ASM("asm/us/dra/nonmatchings/75F54", func_80125A30);
#else
s32 func_80125A30(s32 baseY, s32 baseX) {
    s16 x;
    s16 y;
    Collider res1;
    Collider res2;
    s16 colRes1;
    s16 colRes2;

    x = baseX + g_CurrentEntity->posX.i.hi;
    y = baseY + g_CurrentEntity->posY.i.hi;

    CheckCollision(x, y, &res1, 0);
    colRes1 = res1.unk0 & 0xF801;
    CheckCollision(x, (s16)(y - 1 + res1.unk18), &res2, 0);
    y = baseY + (g_CurrentEntity->posY.i.hi + res1.unk18);

    if ((colRes1 & 0x8801) == 1 || (colRes1 & 0x8801) == 0x0801) {
        colRes2 = res2.unk0 & 0xF001;
        if (!(*(u16*)&res2.unk0 & 1)) {
            g_CurrentEntity->posY.i.hi = y;
            return 1;
        }
        if ((res2.unk0 & 0x8001) == 0x8001) {
            g_CurrentEntity->posY.i.hi = y + (s16)(res2.unk18 - 1);
            return colRes2;
        }
    } else if ((colRes1 & 0x8001) == 0x8001) {
        g_CurrentEntity->posY.i.hi = y;
        return colRes1 & 0xF001;
    }
    return 0;
}
#endif

s32 func_80125B6C(s16 arg0, s16 arg1) {
    Collider res;
    s16 var_a1;

    if (g_CurrentEntity->accelerationX == 0) {
        return 0;
    }

    CheckCollision(g_CurrentEntity->posX.i.hi + arg1,
                   g_CurrentEntity->posY.i.hi + arg0, &res, 0);
    if (g_CurrentEntity->accelerationX > 0) {
        var_a1 = LOH(res.unk14);
    } else {
        var_a1 = LOH(res.unk1C);
    }

    if (res.unk0 & 2) {
        g_CurrentEntity->posX.i.lo = 0;
        g_CurrentEntity->posX.i.hi += var_a1;
        return 2;
    }

    return 0;
}

void EntityHolyWater(Entity* entity) {
    s16 temp3;
    s32 temp;
    s32 temp2;

    switch (entity->step) {
    case 0:
        entity->flags = FLAG_UNK_08000000;
        entity->animSet = 9;
        entity->animCurFrame = 0x1D;
        entity->zPriority = PLAYER.zPriority - 2;
        entity->posY.i.hi += 8;
        AccelerateX(0x14000);
        entity->accelerationY = -0x32000;
        func_8011A290(entity);
        entity->hitboxHeight = 4;
        entity->hitboxWidth = 4;
        D_80072F14[0] = 4;
        entity->step++;
        break;

    case 1:
        entity->posY.val += entity->accelerationY;
        if (entity->accelerationY <= 0x3FFFF) {
            entity->accelerationY += 0x3800;
        }

        temp = func_80125A30(0, 0);
        entity->posX.val += entity->accelerationX;

        if (entity->accelerationX < 0) {
            temp3 = -4;
        } else {
            temp3 = 4;
        }
        temp |= func_80125B6C(-7, temp3);

        if (temp & 2) {
            temp = 1;
        } else {
            temp2 = 1;
        }

        temp2 = temp & 1;
        if (temp2 != 0) {
            PlaySfx(0x69A);
            func_8011AAFC(entity, 0x3B, 0);
            entity->unk7C.s = 0x10;
            entity->animSet = 0;
            entity->step = 2;
        }
        break;

    case 2:
        if (!(entity->unk7C.s & 3)) {
            func_8011AAFC(entity, (D_8013841C << 0x10) | 0x1C,
                          entity->unkB2 << 9);
            D_8013841C++;
        }
        entity->unk7C.s--;
        if (entity->unk7C.s == 0) {
            entity->unk7C.s = 4;
            entity->step++;
        }
        break;

    case 3:
        entity->unk7C.s--;
        if (entity->unk7C.s == 0) {
            DestroyEntity(entity);
        }
        break;
    }
}

// glass breaking effect for holy water
INCLUDE_ASM("asm/us/dra/nonmatchings/75F54", EntityHolyWaterBreakGlass);

// green flame when holy water explodes
INCLUDE_ASM("asm/us/dra/nonmatchings/75F54", EntityHolyWaterFlame);

// cross subweapon crash (full effect with all parts)
INCLUDE_ASM("asm/us/dra/nonmatchings/75F54", EntitySubwpnCrashCross);

// rising blue particles from cross crash
INCLUDE_ASM("asm/us/dra/nonmatchings/75F54", EntitySubwpnCrashCrossParticles);

INCLUDE_ASM("asm/us/dra/nonmatchings/75F54", func_80126ECC);

void func_801274DC(Entity* entity) {
    switch (entity->step) {
    case 0:
        if (entity->subId == 0) {
            PlaySfx(0x660);
        }
        entity->flags = 0x100000 | FLAG_UNK_08000000;
        entity->animSet = 9;
        entity->unk4C = &D_800B0798;
        entity->zPriority = PLAYER.zPriority + 2;
        entity->facing = (PLAYER.facing + 1) & 1;
        AccelerateX(D_800B0830[entity->subId]);
        entity->accelerationY = D_800B083C[entity->subId];
        entity->unk7C.s = 0x14;
        func_8011A328(entity, 2);
        entity->hitboxWidth = 4;
        entity->hitboxHeight = 4;
        entity->step++;
        break;

    case 1:
        if (entity->unk48 == 0) {
            entity->unk7C.s--;
            if ((entity->unk7C.s) == 0) {
                entity->step++;
            }
            entity->posX.val += entity->accelerationX;
            entity->posY.val += entity->accelerationY;
            break;
        }
        DestroyEntity(entity);
        break;

    case 2:
        if (entity->unk48 != 0) {
            DestroyEntity(entity);
            break;
        }
        entity->posX.val += entity->accelerationX;
        break;
    }
}

INCLUDE_ASM("asm/us/dra/nonmatchings/75F54", func_8012768C);

void func_80127840(Entity* entity) {
    switch (entity->step) {
    case 0:
        if (entity->subId != 0) {
            PlaySfx(0x683);
        }

        entity->flags = 0x100000 | FLAG_UNK_08000000;

        if (entity->subId != 0) {
            entity->posY.i.hi = entity->posY.i.hi + 16;
        } else {
            entity->posY.i.hi = entity->posY.i.hi - 4;
        }

        entity->animSet = 9;
        entity->unk1E = 0;
        entity->unk4C = &D_800B07C8;
        entity->unk19 |= 4;
        entity->zPriority = PLAYER.zPriority + 2;
        entity->facing = (PLAYER.facing + 1) & 1;
        AccelerateX(-0x10);
        func_8011A328(entity, 2);
        entity->hitboxWidth = 8;
        entity->hitboxHeight = 8;
        entity->step++;
        break;

    case 1:
        if (entity->animFrameIdx >= 23) {
            if (!(D_8003C8C4 & 3)) {
                entity->unk1E += 0x400;
            }
            if (entity->accelerationX < 0) {
                entity->accelerationX -= 0x1800;
            } else {
                entity->accelerationX += 0x1800;
            }
            if (!(D_8003C8C4 & 1) && (rand() & 1)) {
                func_8011AAFC(entity, 0x10024, 0);
            }
            entity->posX.val += entity->accelerationX;
            entity->posY.val += entity->accelerationY;
        }
        break;
    }
}

// circle expands out of player
void EntityExpandingCircle(Entity* entity) {
    POLY_GT4* poly;
    s32 firstPolygonIndex;

    if (PLAYER.facing == 0) {
        entity->posX.i.hi = PLAYER.posX.i.hi - 10;
    } else {
        entity->posX.i.hi = PLAYER.posX.i.hi + 10;
    }
    entity->posY.i.hi = PLAYER.posY.i.hi + 2;

    switch (entity->step) {
    case 0:
        firstPolygonIndex = AllocPolygons(4, 1);
        entity->firstPolygonIndex = firstPolygonIndex;
        if (firstPolygonIndex != -1) {
            entity->unk7C.s = 22;
            entity->unk7E.modeU16 = 26;
            poly = &D_80086FEC[entity->firstPolygonIndex];
            poly->u2 = 64;
            poly->u3 = 127;
            poly->u1 = 127;
            poly->v1 = 192;
            poly->v0 = 192;
            poly->v3 = 255;
            poly->v2 = 255;
            poly->r3 = 128;
            poly->r2 = 128;
            poly->r1 = 128;
            poly->r0 = 128;
            poly->g3 = 128;
            poly->g2 = 128;
            poly->g1 = 128;
            poly->g0 = 128;
            poly->u0 = 64;
            poly->b3 = 64;
            poly->b2 = 64;
            poly->b1 = 64;
            poly->b0 = 64;
            poly->tpage = 0x1A;
            poly->clut = 0x15F;
            poly->pad2 = PLAYER.zPriority + 1;
            poly->pad3 = 0x35;
            entity->flags = 0x40000 | FLAG_UNK_04000000 | FLAG_FREE_POLYGONS;
            entity->step++;
            break;
        }
        DestroyEntity(entity);
        return;

    case 1:
        entity->unk7C.s += 2;
        entity->unk7E.modeU16 += 2;
        if (entity->unk7C.s >= 0x39) {
            DestroyEntity(entity);
            return;
        }
        break;

    default:
        break;
    }

    poly = &D_80086FEC[entity->firstPolygonIndex];
    poly->x0 = entity->posX.i.hi - entity->unk7C.s;
    poly->y0 = entity->posY.i.hi - entity->unk7E.modeU16;
    poly->x1 = entity->posX.i.hi + entity->unk7C.s;
    poly->y1 = entity->posY.i.hi - entity->unk7E.modeU16;
    poly->x2 = entity->posX.i.hi - entity->unk7C.s;
    poly->y2 = entity->posY.i.hi + entity->unk7E.modeU16;
    poly->x3 = entity->posX.i.hi + entity->unk7C.s;
    poly->y3 = entity->posY.i.hi + entity->unk7E.modeU16;

    if (entity->unk7C.s >= 0x29) {
        poly->r3 += 244;
        poly->g3 += 244;
        poly->b3 += 250;
        poly->r0 = poly->r1 = poly->r2 = poly->r3;
        poly->g0 = poly->g1 = poly->g2 = poly->g3;
        poly->b0 = poly->b1 = poly->b2 = poly->b3;
    }
}

void func_80127CC8(Entity* entity) {
    POLY_GT4* poly;
    s32 ret;

    if (PLAYER.step != 34) {
        DestroyEntity(entity);
        return;
    }

    entity->posX.i.hi = PLAYER.posX.i.hi;

    switch (entity->step) {
    case 0:
        ret = AllocPolygons(3, 1);
        entity->firstPolygonIndex = ret;

        if (ret == -1) {
            DestroyEntity(entity);
            D_80072F20.unk5C = 0xFFFF;
            return;
        }

        entity->flags = 0x60000 | FLAG_UNK_04000000 | FLAG_FREE_POLYGONS;
        poly = &D_80086FEC[entity->firstPolygonIndex];
        poly->r3 = 192;
        poly->r2 = 192;
        poly->r1 = 192;
        poly->r0 = 192;
        poly->g3 = 64;
        poly->g2 = 64;
        poly->g1 = 64;
        poly->g0 = 64;
        poly->b3 = 64;
        poly->b2 = 64;
        poly->b1 = 64;
        poly->b0 = 64;
        poly->pad3 = 0x315;
        entity->zPriority = 0x1C0;
        poly->pad2 = 0x1C0;
        entity->step++;
        break;

    case 1:
        if (entity->unk7C.s++ >= 0xE) {
            DestroyEntity(entity);
            return;
        }

    default:
        break;
    }
    poly = &D_80086FEC[entity->firstPolygonIndex];
    poly->x0 = poly->x2 = entity->posX.i.hi - 3;
    poly->y0 = 0;
    poly->y1 = 0;
    poly->x1 = poly->x3 = entity->posX.i.hi + 3;
    poly->y3 = 240;
    poly->y2 = 240;

    if (D_8003C8C4 & 1) {
        poly->pad3 = poly->pad3 | 8;
    } else {
        poly->pad3 = poly->pad3 & 0xFFF7;
    }
}

void func_80127EAC(s16 arg0) {
    g_CurrentEntity->unk7C.s = (arg0 * 2) - g_CurrentEntity->unk7C.s;
    if (g_CurrentEntity->unk80.modeS16.unk2 == 0) {
        g_CurrentEntity->unk80.modeS16.unk0++;
        g_CurrentEntity->unk80.modeS16.unk2++;
    }
}

void func_80127EF0(s16 arg0) {
    if (g_CurrentEntity->unk80.modeS16.unk2 == 0) {
        g_CurrentEntity->unk7C.s = (arg0 * 2) - g_CurrentEntity->unk7C.s;
        g_CurrentEntity->unk80.modeS16.unk0++;
        g_CurrentEntity->unk80.modeS16.unk2++;
    }
}

INCLUDE_ASM("asm/us/dra/nonmatchings/75F54", EntitySubwpnReboundStone);

// ash thrown when using vibhuti subweapon
INCLUDE_ASM("asm/us/dra/nonmatchings/75F54", EntitySubwpnThrownVibhuti);

s32 func_80128BBC(Unkstruct_80128BBC* arg0, u8 value) {
    u8 ret = 0;
    s32 i;
    s32 j;
    Unkstruct_80128BBC_Sub* temp = arg0->unk04;

    for (i = 0; i < 4; i++, temp++) {
        for (j = 0; j < 3; j++) {
            temp->unk00[j] -= value;

            if (temp->unk00[j] < 16) {
                temp->unk00[j] = 16;
            } else {
                ret |= 1;
            }
        }
    }
    return ret;
}

INCLUDE_ASM("asm/us/dra/nonmatchings/75F54", func_80128C2C);

INCLUDE_ASM("asm/us/dra/nonmatchings/75F54", func_801291C4);

INCLUDE_ASM("asm/us/dra/nonmatchings/75F54", func_80129864);

// opens hole in backround and spirit comes out (ID 0x40)
INCLUDE_ASM("asm/us/dra/nonmatchings/75F54", EntitySummonSpirit);

// expanding circle effect when activating stopwatch
INCLUDE_ASM("asm/us/dra/nonmatchings/75F54", EntityStopWatchExpandingCircle);

// stopwatch subweapon effect. stops enemies (Dra Entity 0x2A)
INCLUDE_ASM("asm/us/dra/nonmatchings/75F54", EntityStopWatch);

void func_8012B78C(Entity* entity) {
    POLY_GT4* poly;
    s32 ret;

    switch (entity->step) {
    case 0:
        ret = AllocPolygons(4, 1);
        entity->firstPolygonIndex = ret;
        if (entity->firstPolygonIndex != -1) {
            entity->flags = 0x20000 | FLAG_UNK_04000000 | FLAG_FREE_POLYGONS;
            poly = &D_80086FEC[entity->firstPolygonIndex];
            poly->tpage = 0x1C;
            poly->clut = 0x19D;
            poly->u2 = 32;
            poly->u0 = 32;
            poly->u3 = 48;
            poly->u1 = 48;
            poly->v1 = 0;
            poly->v0 = 0;
            poly->v3 = 16;
            poly->v2 = 16;
            poly->x0 = poly->x2 = entity->posX.i.hi - 8;
            poly->x1 = poly->x3 = entity->posX.i.hi + 8;
            poly->y0 = poly->y1 = entity->posY.i.hi - 8;
            poly->y2 = poly->y3 = entity->posY.i.hi + 8;
            poly->pad2 = entity->zPriority;
            poly->pad3 = 0x115;
            entity->unk7E.modeU16 = 96;
            entity->step++;
        } else {
            DestroyEntity(entity);
            return;
        }
        break;

    case 1:
        if (++entity->unk7C.s > 5) {
            entity->step++;
        }
        entity->unk7E.modeU16 -= 8;
        break;

    case 2:
        DestroyEntity(entity);
        return;

    default:
        break;
    }
    poly = &D_80086FEC[entity->firstPolygonIndex];
    poly->r0 = poly->r1 = poly->r2 = poly->r3 = poly->g0 = poly->g1 = poly->g2 =
        poly->g3 = poly->b0 = poly->b1 = poly->b2 = poly->b3 =
            entity->unk7E.modeU8.unk0;
}

// book rotates around player
INCLUDE_ASM("asm/us/dra/nonmatchings/75F54", EntitySubwpnBible);

// echo of bat effect
INCLUDE_ASM("asm/us/dra/nonmatchings/75F54", EntityBatEcho);

INCLUDE_ASM("asm/us/dra/nonmatchings/75F54", func_8012C600);

bool func_8012C88C(void) {
    if ((PLAYER.unk2E != 0) && (PLAYER.unk2E != 8)) {
        if (((D_8009744C != 0) && (func_800FE3A8(0xE) == 0)) ||
            (D_80072EEC & 2) || (func_800FEEA4(2, 1) < 0)) {
            func_8010D584(25);
            func_8010DA48(0xCA);
            D_800AFDA6 = 1;
            PLAYER.palette = 0x810D;
            D_80072F86 = 0;
            D_80072F88 = 0;
            func_8011AAFC(g_CurrentEntity, 0x24002C, 0);
            PLAYER.accelerationY >>= 1;
            return true;
        }
    }
    return false;
}

INCLUDE_ASM("asm/us/dra/nonmatchings/75F54", func_8012C97C);

INCLUDE_ASM("asm/us/dra/nonmatchings/75F54", func_8012CA64);

void func_8012CB0C(void) {
    PLAYER.unkAC = 0xDE;
    PLAYER.accelerationY = 0;
    D_800B0914 = 0;
    PLAYER.animFrameIdx = 0;
    PLAYER.animFrameDuration = 0;
    PLAYER.unk2E = 7;
}

INCLUDE_ASM("asm/us/dra/nonmatchings/75F54", func_8012CB4C);

void func_8012CC30(s32 arg0) {
    if (arg0 == 0) {
        D_80138444 = 1;
        if ((D_80138FC4 == 255) && (func_800FE3A8(6)) && (func_800FDC94(4))) {
            func_8010E27C();
            PLAYER.unk2E = 2;
            D_800B0914 = 4;
            AccelerateX(0x50000);
            g_CurrentEntity->accelerationY = 0;
            func_8010DA48(0xEDU);
            func_800FDCE0(4);
        }
    } else {
        D_80138444 = 1;
    }
}

INCLUDE_ASM("asm/us/dra/nonmatchings/75F54", func_8012CCE4);

void func_8012CED4(void) {
    if ((PLAYER.unk2E == 2) && (D_800B0914 == PLAYER.unk2E)) {
        func_8010DA48(0xE7);
        D_800B0914 = 1;
    } else {
        func_8010DA48(0xE8);
        AccelerateX(0x10000);
        D_800B0914 = 0;
        if (D_80138438 & 0x40) {
            PLAYER.animFrameIdx = 4;
            PLAYER.accelerationX = 0;
            PLAYER.animFrameDuration = 1;
        }
    }
    PLAYER.unk2E = 5;
    D_80072F0A[0] = 8;
    PLAYER.accelerationY = 0;
    D_80138430 -= 0x100;
}

void func_8012CFA8(void) {
    func_8010DA48(0xEA);
    PLAYER.unk2E = 6;
    D_800B0914 = 0;
    PLAYER.accelerationX = 0;
    D_80072F0A[0] = 8;
}

void func_8012CFF0(void) {
    PLAYER.unk2E = 3;
    func_8010DA48(0xE3);
    D_800B0914 = 0;
}

INCLUDE_ASM("asm/us/dra/nonmatchings/75F54", func_8012D024);

void func_8012D178(void) {
    s32 var_v0;

    if (D_80072EEC & 0x40) {
        func_8012CCE4();
        return;
    } else if (!(D_80072F20.pl_vram_flag & 1)) {
        func_8012CFA8();
        return;
    } else if (PLAYER.facing != 0) {
        var_v0 = D_80072EE8 & 0x8000;
    } else {
        var_v0 = D_80072EE8 & 0x2000;
    }

    if (var_v0 != 0) {
        func_8012CB4C();
        return;
    } else if (D_80072F20.unk04 & 0x40) {
        func_8012CA64();
        return;
    } else if (D_8003C8C4 == ((D_8003C8C4 / 6) * 6)) {
        func_8011AAFC(g_CurrentEntity, 0x10045, 0);
    }
}

INCLUDE_ASM("asm/us/dra/nonmatchings/75F54", func_8012D28C);

INCLUDE_ASM("asm/us/dra/nonmatchings/75F54", func_8012D3E8);

INCLUDE_ASM("asm/us/dra/nonmatchings/75F54", func_8012DBBC);

INCLUDE_ASM("asm/us/dra/nonmatchings/75F54", func_8012DF04);

INCLUDE_ASM("asm/us/dra/nonmatchings/75F54", func_8012E040);

INCLUDE_ASM("asm/us/dra/nonmatchings/75F54", func_8012E550);

INCLUDE_ASM("asm/us/dra/nonmatchings/75F54", func_8012E7A4);

INCLUDE_ASM("asm/us/dra/nonmatchings/75F54", func_8012E9C0);

INCLUDE_ASM("asm/us/dra/nonmatchings/75F54", func_8012EAD0);

INCLUDE_ASM("asm/us/dra/nonmatchings/75F54", func_8012ED30);

INCLUDE_ASM("asm/us/dra/nonmatchings/75F54", func_8012EF2C);

INCLUDE_ASM("asm/us/dra/nonmatchings/75F54", func_8012F178);

s32 func_8012F83C(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 temp_a0 = arg0 - arg2;
    s32 temp_a1 = arg1 - arg3;

    return ((SquareRoot12((SQ(temp_a0) + SQ(temp_a1)) << 12, temp_a1) >> 12) <
            arg4) ^
           1;
}

INCLUDE_ASM("asm/us/dra/nonmatchings/75F54", func_8012F894);

INCLUDE_ASM("asm/us/dra/nonmatchings/75F54", func_80130264);

INCLUDE_ASM("asm/us/dra/nonmatchings/75F54", func_80130618);

INCLUDE_ASM("asm/us/dra/nonmatchings/75F54", func_801309B4);

INCLUDE_ASM("asm/us/dra/nonmatchings/75F54", func_80130E94);

// https://decomp.me/scratch/cu30D
// TODO: branching is wrong jpt_ needs a file split
#ifndef NON_EQUIVALENT
INCLUDE_ASM("asm/us/dra/nonmatchings/75F54", func_8013136C);
#else
void func_8012C600(void);
extern u16 D_8007412E;
extern s32 D_800741CC;
extern s32 D_800741D0;

void func_8013136C(Entity* entity) {
    if (!(D_80072F2C & 4)) {
        DestroyEntity(entity);
        return;
    }
    if (entity->step == 0) {
        entity->animSet = 0xF;
        entity->unk5A = 0x7E;
        entity->palette = PLAYER.palette;
        entity->flags = 0x60000 | FLAG_UNK_04000000;
        entity->unk19 = 4;
        entity->unk20 = -8;
        entity->step++;
    }
    entity->animCurFrame = 80;
    entity->facing = PLAYER.facing;
    entity->posX.val = g_EntityArray[UNK_ENTITY_13].posX.val; // D_800741CC
    entity->posY.val = g_EntityArray[UNK_ENTITY_13].posY.val; // D_800741D0
    if (PLAYER.facing == 0) {
        entity->zPriority = PLAYER.zPriority - 5;
        entity->posX.i.hi += 8;
    } else {
        entity->zPriority = PLAYER.zPriority + 5;
        entity->posX.i.hi -= 8;
    }
    entity->posY.i.hi += 3;
    entity->unk1E = g_EntityArray[UNK_ENTITY_13].unk1E;
    switch (PLAYER.unk2E - 1) {
    case 1:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
        break;

    case 0:
        if (D_800B0914 == 1) {
            entity->posY.i.hi -= 2;
            if (PLAYER.facing == 0) {
                entity->posX.i.hi -= 8;
            } else {
                entity->posX.i.hi += 8;
            }
        }
        break;

    case 2:
        switch (D_800B0914) {
        case 1:
            break;

        case 0:
            if (PLAYER.animCurFrame == 33) {
                entity->animCurFrame = 81;
                if (PLAYER.facing == 0) {
                    entity->posX.i.hi += 3;
                } else {
                    entity->posX.i.hi += 6;
                }
            }
            if (PLAYER.animCurFrame == 34) {
                if (PLAYER.facing == 0) {
                    entity->posX.i.hi += 3;
                } else {
                    entity->posX.i.hi += 13;
                }
                entity->animCurFrame = 82;
            }
        case 2:
            break;
        }
        break;
    }
    entity->palette = PLAYER.palette;
    func_8012C600();
}
#endif

// one rotating cross from the cross subweapon crash
INCLUDE_ASM("asm/us/dra/nonmatchings/75F54", func_801315F8);

void func_80131EBC(const char* str, s16 id) { D_80138784[id] = str; }

void func_80131ED8(s32 value) { D_80138F20 = value; }

void func_80131EE8(void) {
    D_80139020 = 1;
    D_8013B694 = 0;
}

void func_80131F04(void) {
    D_80139020 = 0;
    D_8013B694++;
}

s32 func_80131F28(void) { return D_80138F7C; }

u16 func_80131F38(void) {
    if (D_80139810 == 0) {
        return 0;
    }
    return D_80139810 | 0x200;
}

bool func_80131F68(void) {
    if (D_8013B61C == 0) {
        return D_8013901C != 0;
    }
    return true;
}

s16 func_80131F94(void) { return D_8013B668; }

void func_80131FA4(s16 arg0) { func_80021F6C(arg0, arg0); }

void func_80131FCC(void) {
    if (D_8013B680 == 0) {
        D_80138F7C = 0;
    } else {
        s32 temp_v1 = D_8013B680;
        s32 temp_v0 = D_8013B680;
        if (temp_v0 >= 0 && temp_v1 < 3)
            D_80138F7C++;
    }
    D_8013B680 = 0;
}

u8 func_80132028(u_char com, u_char* param, u_char* result) {
    s32 ret = CdSync(1, D_80138F2C);

    D_801396F0 = ret;

    if (com == CdlGetlocL) {
        if (ret == 2) {
            goto block_9;
        } else {
            goto block_6;
        }
    } else if ((*D_80138F2C & 0x10) || (*D_80138F2C & 4)) {
    block_6:
        CdControl(CdlNop, 0, 0);
        D_8013B680 = 2;
        return D_8013B680;
    } else if (ret == 2) {
    block_9:
        if (CdControl(com, param, result)) {
            D_8013B680 = 0;
            return D_8013B680;
        }
        goto block_12;
    }
block_12:
    D_8013B680 = 1;

    return D_8013B680;
}

void func_80132134(void) {
    g_volumeL = 127;
    g_volumeR = 127;
    SsSetMVol(g_volumeL, g_volumeR);
}

void func_8013216C(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        D_8013B620[i] = 0;
        D_8013B614[i] = 0;
        D_8013AE84[i] = 0;
        D_8013B66C[i] = 0;
        D_8013B5EC[i] = 0;
        D_8013B628[i] = 0;
        D_8013B648[i] = 0;
        D_8013AEA0[i] = 0;
    }
}

void func_801321FC(void) {
    s32 i;

    func_8013216C();
    D_8013B690 = 0;

    for (i = 0; i < 4; i++) {
        D_8013B650[i] = 0;
        D_8013AED4[i] = 0;
    }
    D_80139804 = 0;
    D_8013B664 = 0;
}

void func_80132264(void) {
    func_801321FC();
    D_8013B684 = 0;
    D_80138454 = 0;
    do {
        D_80138F84[D_80138454] = 0;
    } while (++D_80138454 < 0xA);
    D_80138454 = 0;
    do {
        D_80139868[D_80138454] = 0;
    } while (++D_80138454 < 0x100);
    D_801396F4 = 0;
    D_8013AEE8 = 0;
    D_80138454 = 0;
    do {
        g_sfxRingBuffer2[D_80138454] = 0;
    } while (++D_80138454 < 0x100);
    D_80139A68 = 0;
    g_sfxRingBufferPos2 = 0;
    D_80138454 = 0;
    do {
        g_sfxRingBuffer1[D_80138454].unk00 = 0;
        g_sfxRingBuffer1[D_80138454].unk02 = 0;
        g_sfxRingBuffer1[D_80138454].unk04 = 0;
    } while (++D_80138454 < 0x100);
    D_80139A6C = 0x20;
    D_8013AE7C = 0x7F;
    D_80138FAC = 0;
    g_sfxRingBufferPos1 = 0;
    D_801390C4 = 0;
    D_8013AEE0 = 0;
    D_8013AE94 = 0;
    D_801390A4 = 0;
    D_80139010 = 0;
    D_80139A74 = 0;
    D_8013B69C = 0;
    D_8013B658 = 0;
    D_80138FBC = 0;
    D_8013901C = 0;
    D_80139800 = 0;
    D_80138F80 = 0;
    D_80139014 = 0;
    D_8013B618 = 0;
    D_8013980C = 0;
    D_8013AE80 = 0;
    D_801390A0 = 0;
    D_8013909C = 0x70;
    D_8013AEF0 = 0x70;
    D_8013B680 = 0;
    D_80138F7C = 0;
    D_801390D8 = 0;
    D_80138F28 = 0;
    D_80139020 = 0;
    D_8013B694 = 0;
    D_8013B61C = 0;
}

void func_801324B4(s8 s_num, s16 arg1, s16 arg2) {
    short voll = D_800BD07C[arg1];
    short volr = D_800BD07C[arg2];

    SsSetSerialVol(s_num, voll, volr);
}

void func_80132500(u8 soundMode) {
    CdlATV audioVolume;

    switch (soundMode) {
    case MONO:
        if (D_801390A8 != 0) { // D_801390A8 fake symbol or part of another
            func_80021174();
            audioVolume.val2 = 128; // CD (R) --> SPU (R)
            audioVolume.val0 = 128; // CD (L) --> SPU (L)
            audioVolume.val3 = 128; // CD Right sound transferred to left
            audioVolume.val1 = 128; // CD Left sound transferred to right
            CdMix(&audioVolume);
            D_8013AE7C = 108;
            D_801390A8 = 0;
        }
        break;
    case STEREO:
        if (D_801390A8 != 1) {
            func_80021188();
            audioVolume.val2 = 224; // CD (R) --> SPU (R)
            audioVolume.val0 = 224; // CD (L) --> SPU (L)
            audioVolume.val3 = 0;
            audioVolume.val1 = 0;
            CdMix(&audioVolume);
            D_8013AE7C = 127;
            D_801390A8 = 1;
        }
        break;
    }
}

/**
 * Called by entrypoint_sotn, seems to be initializing
 * various parts of the sound system
 */
void func_801325D8(void) {
    D_8013AEEC = 1;
    SsInitHot();
    SsSetTickMode(1);
    func_80132500(1);
    SsSetReservedVoice(0x10);
    SsStart();
    func_800209B4(&D_80138460, 0x10, 1);
    func_80021E38(3);
    SpuClearReverbWorkArea(3);
    func_80021EEC();
    func_80132134();
    D_8013B668 = 0x78;
    SsSetSerialAttr(0, 0, 1);
    func_801324B4(0, D_8013B668, D_8013B668);
    D_80138F24[0] = -0x38; // !FAKE: D_80138F24 part of an array / struct
    func_80132028(0xE, D_80138F24, 0);
    func_80132264();
    func_80131FA4(0xA);
    func_8002ABF4(0);
    func_80029FBC(0);
    CdReadyCallback(NULL);
    func_80028D3C(0x1010, 0x10000);
}

s32 func_801326D8(void) {
    if (D_8013901C != 0)
        return 1;
    if (D_80139810 != 0)
        return 3;
    return (D_801390D8 != 0) * 2;
}

void func_8013271C(void) {
    while (!(func_801326D8() & 0xFF) == 0) {
        VSync(0);
        func_801361F8();
    }
}

void func_80132760(void) {
    SsSetMVol(0, 0);
    SsSetSerialAttr(0, 0, 0);
    func_801324B4(0, 0, 0);
    func_80132134();
    func_80132264();
}

INCLUDE_ASM("asm/us/dra/nonmatchings/75F54", func_801327B4);

// https://decomp.me/scratch/0X5YL
// Matches with gcc 2.6.0 + aspsx 2.3.4
#ifndef NON_MATCHING
INCLUDE_ASM("asm/us/dra/nonmatchings/75F54", func_80132A04);
#else
void func_801327B4(s16, s16, s16, s16, s16, s16, s16, s16);
extern s16 D_800BD19C[];
extern s16 D_800BD19E[];
extern s16 D_80138FB8; // vol_l
extern s16 D_80139004; // vol_r

void func_80132A04(s16 voice, s16 vabId, s16 prog, s16 tone, u16 note,
                   s16 volume, s16 distance) {
    s16 var_a0;
    s16 var_a1;
    volatile short pad;

    if (distance == 0) {
        D_80138FB8 = volume;
        D_80139004 = volume;
    } else {
        D_80139004 = (volume * D_800BD19C[distance * 2]) >> 7;
        D_80138FB8 = (volume * D_800BD19E[distance * 2]) >> 7;
    }

    if (voice < 0x18) {
        SsUtKeyOnV(voice, vabId, prog, tone, note, 0, D_80138FB8, D_80139004);
        SsUtKeyOnV(voice + 1, vabId, prog, 1 + tone, note, 0, D_80138FB8,
                   D_80139004);
        return;
    }
    switch (voice) {
    case 0x1E:
        var_a0 = 0;
        var_a1 = 4;
        break;
    case 0x1F:
        var_a0 = 4;
        var_a1 = 8;
        break;
    case 0x20:
        var_a0 = 8;
        var_a1 = 0xC;
        break;
    case 0x21:
        var_a0 = 0xE;
        var_a1 = 0x12;
        break;
    default:
        return;
    }
    func_801327B4(var_a0, var_a1, vabId, prog, tone, note, D_80138FB8,
                  D_80139004);
}
#endif

INCLUDE_ASM("asm/us/dra/nonmatchings/75F54", func_80132C2C);

extern s16 D_80139868[];

u16 func_80132E38(void) {
    s32 i;

    for (i = 0; i < 255; i++) {
        D_80139868[i] = D_80139868[i + 1];
    }
    D_801396F4--;

    return D_801396F4;
}

void func_80132E90(u32 arg0, s8* arg1) {
    u16 temp;
    u16 temp2;

    arg1[2] = (((arg0 % 75) / 10) * 0x10) + ((arg0 % 75) % 10);
    arg1[1] = ((((arg0 / 75) % 60) / 10) * 0x10) + (((arg0 / 75) % 60) % 10);
    temp = ((arg0 / 75) / 60) % 10;
    arg1[0] = (temp2 = (((arg0 / 75) / 60) / 10) * 0x10) + temp;
}

INCLUDE_ASM("asm/us/dra/nonmatchings/75F54", func_80132F60);
void func_80132F60();

INCLUDE_ASM("asm/us/dra/nonmatchings/75F54", func_80133290);
void func_80133290();

INCLUDE_ASM("asm/us/dra/nonmatchings/75F54", func_80133488);
void func_80133488();

INCLUDE_ASM("asm/us/dra/nonmatchings/75F54", func_80133604);
void func_80133604();

void func_80133780(s8 arg0) { SsSetSerialAttr(0, 1, arg0 == 1); }

void func_801337B4(void) {
    if (D_80139810 != 0) {
        func_80020F44(D_8013B658);
        SsSeqClose(D_8013B658);
        func_8013415C();
        D_80139810 = 0;
        D_801390C4 = 0;
    }
}

INCLUDE_ASM("asm/us/dra/nonmatchings/75F54", func_80133810);

bool func_80133940(void) { return D_801396F4 == 0; }

bool func_80133950(void) { return D_8013980C == 0; }

INCLUDE_ASM("asm/us/dra/nonmatchings/75F54", func_80133960);
void func_80133960();

INCLUDE_ASM("asm/us/dra/nonmatchings/75F54", func_80133BDC);
void func_80133BDC();

INCLUDE_ASM("asm/us/dra/nonmatchings/75F54", func_80133FCC);

extern Unkstruct_80138FB4* D_80138FB4;

void func_80134104(void) {
    D_80138FB4->unk4 = 0x4000;
    D_80138FB4->unk0 = 0xFFFFFF;
    D_80138FB4->unk36 = 0xE;
    func_8002A09C(D_80138FB4);
    D_80138F28 = 0xFFFFFF;
    func_801321FC();
}

void func_8013415C(void) {
    D_80138FB4->unk4 = 0x4000;
    D_80138FB4->unk0 = 0xFFFFFF;
    D_80138FB4->unk36 = 8;
    func_8002A09C(D_80138FB4);
    D_80138F28 = 0xFFFFFF;
    func_801321FC();
}

void func_801341B4(void) {
    s32 temp;

    switch (D_8013AE80) {
    case 0:
        D_801390A0 = 1;
        D_80139A78 = 0;
        D_8013AE80++;
        break;

    case 1:
        D_80139A78++;
        if (g_volumeL > 0) {
            temp = g_volumeR * D_80139A6C * D_80139A78;
            if (temp < 0) {
                temp += 0x1FF;
            }
            g_volumeL = g_volumeR - (temp >> 9);
            if (g_volumeL >> 0x10) {
                g_volumeL = 0;
            }
        } else {
            g_volumeL = 0;
        }
        SsSetMVol(g_volumeL, g_volumeL);
        if (g_volumeL == 0) {
            D_8013AE80++;
        }
        break;

    case 2:
        func_80131FA4(0);
        func_801337B4();
        func_80132C2C(3);
        D_800BD1C4 = 3;
        D_8013AE80++;
        break;

    case 3:
        D_800BD1C4--;
        if (D_800BD1C4 == 0) {
            func_8013415C();
        default:
            D_8013AE80 = 0;
            D_801390A0 = D_8013AE80;
            D_8013B61C = 0;
            func_80132E38();
        }
        break;
    }
}

void func_80134388(void) {
    s32 temp;

    switch (D_8013AE80) {
    case 0:
        D_8013AE80++;
        D_801390A0 = 1;
        D_80139A78 = 0;
        break;

    case 1:
        D_80139A78++;
        if (D_8013B668 > 0) {
            temp = D_80139820 * D_80139A6C * D_80139A78;
            if (temp < 0) {
                temp += 0x1FF;
            }
            D_8013B668 = D_80139820 - (temp >> 9);
            if (D_8013B668 >> 0x10) {
                D_8013B668 = 0;
            }
        } else {
            D_8013B668 = 0;
        }
        func_801324B4(0, D_8013B668, D_8013B668);
        if (D_8013B668 == 0) {
            D_8013AE80++;
        }
        break;

    case 2:
        func_80132C2C(2);

    default:
        D_8013AE80 = 0;
        D_801390A0 = D_8013AE80;
        D_8013B61C = 0;
        func_80132E38();
        break;
    }
}

extern Unkstruct_80138FB4* D_801390C8;

void func_80134508(void) {
    D_801390C8->unk0 = 0x300000;
    D_801390C8->unk4 = 0x4000;
    D_801390C8->unk36 = 0xE;
    func_8002A09C(D_801390C8);
    D_80138F28 |= 0x300000;
}

extern Unkstruct_80138FB4* D_801390CC;

void func_80134564(void) {
    D_801390CC->unk0 = 0xC00000;
    D_801390CC->unk4 = 0x4000;
    D_801390CC->unk36 = 0xE;
    func_8002A09C(D_801390CC);
    D_80138F28 |= 0xC00000;
}

extern Unkstruct_80138FB4* D_801390C8;

void func_801345C0(void) {
    D_801390C8->unk0 = 0x300000;
    D_801390C8->unk4 = 0x4000;
    D_801390C8->unk36 = 8;
    func_8002A09C(D_801390C8);
    D_80138F28 |= 0x300000;
}

extern Unkstruct_80138FB4* D_801390CC;

void func_8013461C(void) {
    D_801390CC->unk0 = 0xC00000;
    D_801390CC->unk4 = 0x4000;
    D_801390CC->unk36 = 8;
    func_8002A09C(D_801390CC);
    D_80138F28 |= 0xC00000;
}

s32 func_80134678(s16 arg0, u16 arg1) {
    s32 ret = -2;
    u16 temp;

    if (D_80139804 != 0) {
        ret = 0;
        temp = arg1 + 8;

        if (temp >= 0x11) {
            arg1 = 0;
            ret = -1;
        }

        D_8013AE94 = arg1;
        D_8013AEE0 = arg0;
        g_sfxRingBuffer2[g_sfxRingBufferPos2] = 1;
        g_sfxRingBufferPos2++;

        if (g_sfxRingBufferPos2 == 0x100) {
            g_sfxRingBufferPos2 = 0;
        }
    }
    return ret;
}

u32 func_80134714(s32 arg0, s32 arg1, u16 arg2) {
    u32 ret;
    u32 var_v0;
    s16 temp_v0;
    s32 temp_a0;
    u16 var;

    ret = 0;
    if (D_8013AEEC == 0) {
        return -2;
    }
    if ((u32)((arg0 - 0x601) & 0xFFFF) < 0x2E0) {
        g_sfxRingBuffer1[g_sfxRingBufferPos1].unk00 = arg0 - 0x600;
        g_sfxRingBuffer1[g_sfxRingBufferPos1].unk02 = arg1 & 0x7F;
        var = (arg2 + 8);
        if (var > 16) {
            g_sfxRingBuffer1[g_sfxRingBufferPos1].unk04 = 0;
            ret = -1;
        } else {
            g_sfxRingBuffer1[g_sfxRingBufferPos1].unk04 = arg2;
        }
        if (++g_sfxRingBufferPos1 == 0x100) {
            g_sfxRingBufferPos1 = 0;
        }
    } else {
        ret = -3;
    }
    return ret;
}

void PlaySfx(s16 sfxId) {
    u16 offset;

    if (D_8013AEEC != 0) {
        offset = (u32)(sfxId - 0x601);
        if (offset < 0x2E0) {
            g_sfxRingBuffer1[g_sfxRingBufferPos1].unk00 = sfxId - 0x600;
            g_sfxRingBuffer1[g_sfxRingBufferPos1].unk02 = 0xFFFF;
            g_sfxRingBuffer1[g_sfxRingBufferPos1].unk04 = 0;
            g_sfxRingBufferPos1++;
            if (g_sfxRingBufferPos1 == 0x100) {
                g_sfxRingBufferPos1 = 0;
            }
        } else {
            switch (sfxId) {
            case 0x10:
            case 0x11:
                D_8013980C = 1;
                break;

            case 0x80:
            case 0x81:
            case 0x82:
            case 0x83:
            case 0x84:
            case 0x90:
            case 0x91:
            case 0x92:
            case 0x93:
            case 0x94:
                D_8013B61C = 1;
                break;

            default:
                break;
            }

            g_sfxRingBuffer2[g_sfxRingBufferPos2] = sfxId;
            g_sfxRingBufferPos2++;
            if (g_sfxRingBufferPos2 == 0x100) {
                g_sfxRingBufferPos2 = 0;
            }
        }
    }
}

void func_8013493C(s16 arg0, s16 arg1) {
    D_8013AE84[arg1] = D_8013B678[arg0];
    D_8013B620[arg1] = D_801390AC[arg0];
    D_8013B614[arg1] = D_80139058[arg0];
    D_8013B66C[arg1] = D_80139814[arg0];
    D_8013B5EC[arg1] = D_80139018[arg0];
    D_8013B628[arg1] = D_801390B4[arg0];
}

INCLUDE_ASM("asm/us/dra/nonmatchings/75F54", func_801349F4);

INCLUDE_ASM("asm/us/dra/nonmatchings/75F54", func_80134B48);

INCLUDE_ASM("asm/us/dra/nonmatchings/75F54", func_80134C60);

INCLUDE_ASM("asm/us/dra/nonmatchings/75F54", func_80134D14);

INCLUDE_ASM("asm/us/dra/nonmatchings/75F54", func_80134E64);

INCLUDE_ASM("asm/us/dra/nonmatchings/75F54", func_80134F50);
void func_80134F50();
