#define INCLUDE_ASM_NEW
#include "dra.h"
#include "objects.h"
#include "sfx.h"

void func_80115F54(void) {
    Unkstruct_800ECBF8_1* temp_s0;
    bool var_s2;
    u8 var_v0;
    u8 var_v1;

    var_s2 = false;
    PLAYER.unk19 = 4;
    temp_s0 = D_80097D1C;
    if (*D_80097420 == 0xFFF && PLAYER.step_s != 0) {
        SetPlayerStep(Player_Unk17);
        PLAYER.velocityY = 0;
        PLAYER.velocityX = 0;
        return;
    }

    switch (PLAYER.step_s) {
    case 0:
        var_s2 = true;
        PLAYER.velocityY = 0;
        PLAYER.velocityX = 0;
        PlaySfx(NA_SE_VO_AL_DYING);
        func_80113EE0();
        PLAYER.velocityY = -0x1A000;
        PLAYER.ext.generic.unkAC = 0xC1;
        PLAYER.blendMode = 0x30;
        PLAYER.rotAngle = 0x200;
        func_80118C28(1);
        func_8011AAFC(g_CurrentEntity, 0x59002C, 0);
        func_8011AAFC(g_CurrentEntity, 0x60031, 0);
        temp_s0->unk25 = 0x80;
        temp_s0->unk26 = 0x80;
        temp_s0->unk24 = 0x80;
        temp_s0->unk21 = 0x80;
        temp_s0->unk22 = 0x80;
        temp_s0->unk20 = 0x80;
        temp_s0->unk1D = 0x80;
        temp_s0->unk1E = 0x80;
        temp_s0->unk1C = 0x80;
        temp_s0->unk19 = 0x80;
        temp_s0->unk1A = 0x80;
        temp_s0->unk18 = 0x80;
        temp_s0->unk1B = 1;
        PLAYER.step_s++;
        break;
    case 1:
        if (temp_s0->unk19 < 0xF8) {
            temp_s0->unk19++;
        }
        if (temp_s0->unk18 >= 9) {
            temp_s0->unk18--;
        }
        var_v1 = temp_s0->unk18;
        var_v0 = temp_s0->unk19;
        temp_s0->unk1D = var_v0;
        temp_s0->unk21 = var_v0;
        temp_s0->unk25 = var_v0;
        temp_s0->unk24 = var_v1;
        temp_s0->unk26 = var_v1;
        temp_s0->unk20 = var_v1;
        temp_s0->unk22 = var_v1;
        temp_s0->unk1C = var_v1;
        temp_s0->unk1E = var_v1;
        temp_s0->unk1A = var_v1;
        PLAYER.velocityY += 0x1000;
        if (PLAYER.velocityY > 0x4000) {
            PLAYER.velocityY = 0x1000;
        }
        if (PLAYER.animFrameDuration < 0) {
            StoreImage(&D_800AE130, &D_80139A7C);
            PLAYER.step = 0x10;
            D_80137FE4 = 0;
            D_80137FE8 = 0x40;
            g_CurrentEntity->step_s++;
        }
        break;
    }

    if (var_s2 && g_Player.unk72) {
        PLAYER.velocityY = 0;
    }
}

void func_80116208(void) {
    DamageParam damage;
    s32 temp_s0;

    switch (g_CurrentEntity->step_s) {
    case 0:
        func_80113EE0();
        if (g_Player.unk62 == 0) {
            PLAYER.ext.generic.unkAC = 0x37;
            g_Player.D_80072F04 = 8;
            g_Player.unk40 = 0x8166;
            PlaySfx(0x6EB);
        }
        PLAYER.step_s = 1;
        PLAYER.velocityY = 0;
        PLAYER.velocityX = 0;
        g_Player.unk60 = 2;
        return;
    case 1:
        if (g_Player.unk60 == 3) {
            temp_s0 = HandleDamage(&damage, 2, g_Player.unk64, 1);
            func_80118C84(damage.damageTaken, 0);
            if (temp_s0 == 4) {
                SetPlayerStep(Player_Unk16);
                func_80115394(&damage, 0xC, 1);
                return;
            }
            if (g_Player.unk62 == 0) {
                g_Player.D_80072F04 = 4;
                g_Player.unk40 = 0x8166;
                PlaySfx(0x6E7);
            }
            if (g_Player.unk62 == 2) {
                g_Player.D_80072F04 = 4;
                g_Player.unk40 = 0x8161;
            }
            g_Player.unk60 = 2;
            return;
        }
        if (g_Player.unk60 == 4) {
            PLAYER.step = Player_Hit;
            PLAYER.step_s = 0xF;
            g_Player.unk60 = 0;
            func_8010DA48(0x2E);
            g_Player.unk5A = g_Player.unk64;
            PlaySfx(0x6ED);
            return;
        }
        if (g_Player.unk60 == 0) {
            PLAYER.step = Player_Hit;
            PLAYER.step_s = 1;
            return;
        }
    }
}

INCLUDE_ASM("dra/nonmatchings/75F54", func_80116408);

void func_801166A4(void) {
    switch (PLAYER.step_s) {
    case 0:
        func_80113EE0();
        g_Player.unk40 = 0x8166;
        g_Player.D_80072F04 = 6;
        PLAYER.velocityX = 0;
        PLAYER.velocityY = 0;
        PLAYER.ext.generic.unkAC = 0x33;
        func_8011AAFC(g_CurrentEntity, 0, 0);
        func_8011AAFC(g_CurrentEntity, 0x58002C, 0);
        PLAYER.step_s++;
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
    PLAYER.velocityY = 0;
    PLAYER.velocityX = 0;
    if (g_Player_D_80072EF6 != 2) {
        func_8010E570(0);
    }
}

void func_801167D0(void) {
    s32* velocityX = &PLAYER.velocityX;
    PLAYER.velocityY = 0;
    *velocityX = 0;
    if (g_Player_D_80072EF6 != 2) {
        PLAYER.step = Player_Unk40;
        PLAYER.step_s = 0;
        PLAYER.velocityY = 0;
        *velocityX = 0;
        PLAYER.ext.generic.unkAC = 0xCF;
        PLAYER.animFrameIdx = 0;
        PLAYER.animFrameDuration = 0;
    }
}

bool func_80116838(void) {
    if (g_Entities->step_s == 0) {
        return false;
    }
    if (D_80097448[1] || g_Player.padTapped & PAD_R1 ||
        func_800FEEA4(0, 1) < 0) {
        SetPlayerStep(Player_Unk9);
        func_8010DA48(0xCA);
        D_800AFDA6 = 6;
        g_Entities->palette = 0x810D;
        g_Player.unk66 = 0;
        g_Player.unk68 = 0;
        func_8011AAFC(g_CurrentEntity, 0x21002C, 0);
        g_Entities->velocityY = g_Entities->velocityY >> 1;
        return true;
    }
    return false;
}

void func_8011690C(s16 arg0) {
    if (PLAYER.rotAngle < arg0) {
        PLAYER.rotAngle += 16;
        if (arg0 < PLAYER.rotAngle) {
            PLAYER.rotAngle = arg0;
        }
    }
    if (arg0 < PLAYER.rotAngle) {
        PLAYER.rotAngle -= 16;
        if (PLAYER.rotAngle < arg0) {
            PLAYER.rotAngle = arg0;
        }
    }
}

INCLUDE_ASM("dra/nonmatchings/75F54", func_80116994);

INCLUDE_ASM("dra/nonmatchings/75F54", func_80116B0C);

INCLUDE_ASM("dra/nonmatchings/75F54", func_801177A0);

void func_80117AC0(void) {
    Collider collider;
    s32 collisionCount;

    CheckCollision(PLAYER.posX.i.hi, PLAYER.posY.i.hi + 0x19, &collider, 0);
    collisionCount = (s32)collider.effects & EFFECT_SOLID;
    CheckCollision(PLAYER.posX.i.hi + 4, PLAYER.posY.i.hi + 0x19, &collider, 0);
    if ((s32)collider.effects & EFFECT_SOLID) {
        collisionCount += 1;
    }
    CheckCollision(PLAYER.posX.i.hi - 4, PLAYER.posY.i.hi + 0x19, &collider, 0);
    if ((s32)collider.effects & EFFECT_SOLID) {
        collisionCount += 1;
    }
    if ((g_Player.pl_vram_flag & 0x41) == 0x41) {
        collisionCount += 1;
    }
    PLAYER.rotAngle = 0;
    func_8010E27C();
    if (collisionCount == 0) {
        func_8010E7AC();
        return;
    }

    switch (PLAYER.step_s) {
    case 0:
        if (PLAYER.animFrameDuration < 0) {
            func_8010DA48(0xF6);
            PLAYER.step_s += 1;
        }
        break;
    case 1:
        if (g_Player.padTapped & (PAD_UP | PAD_RIGHT | PAD_DOWN | PAD_LEFT)) {
            func_8010DA48(0xC8);
            PlaySfx(0x6EE);
            PLAYER.step_s = 0;
        } else if (g_Player.unk72 == 1) {
            PLAYER.animFrameIdx = 0;
            PLAYER.animFrameDuration = 3;
        } else if (g_Player.unk72 == 2) {
            if (PLAYER.animFrameIdx != 0) {
                PLAYER.animFrameIdx = 1;
                PLAYER.animFrameDuration = 3;
            }
        } else if (g_Player.unk72 == 3) {
            if (PLAYER.animFrameIdx >= 2) {
                PLAYER.animFrameIdx = 2;
                PLAYER.animFrameDuration = 3;
                PLAYER.step = 2;
                PLAYER.step_s = 5;
            }
        } else if (g_Player.unk72 == 4) {
            if (PLAYER.animFrameIdx >= 3) {
                PLAYER.animFrameIdx = 3;
                PLAYER.animFrameDuration = 3;
                PLAYER.step = 2;
                PLAYER.step_s = 5;
            }
        }
        break;
    }
}

s32 func_80117D3C(void) {
    if (PLAYER.step_s == 0) {
        return 0;
    }
    if (D_80097448[1] != 0 || g_Player.padTapped & PAD_L1 ||
        func_800FEEA4(1, 1) < 0 ||
        (!IsRelicActive(RELIC_POWER_OF_MIST) &&
         (D_80138004 == 0 || --D_80138004 == 0))) {
        func_8010E27C();
        SetPlayerStep(0xE);
        return 1;
    }
    return 0;
}

INCLUDE_ASM("dra/nonmatchings/75F54", func_80117DEC);

INCLUDE_ASM("dra/nonmatchings/75F54", func_801182F8);

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
    if (PLAYER.animFrameIdx == 7 && PLAYER.animFrameDuration == 1) {
        func_8011AAFC(g_CurrentEntity, 0x160028, 0);
        PlaySfx(NA_SE_PL_MP_GAUGE);
        func_8011AAFC(g_CurrentEntity, 0x70, 0);
    }
    if (PLAYER.animFrameDuration < 0) {
        func_8010E570(0);
    }
}

void func_801186EC(void) {
    if (PLAYER.step_s == 0) {
        if (g_Entities[E_WEAPON].entityId == E_NONE) {
            D_80138008 = 0x10;
            func_8011AAFC(g_CurrentEntity, 0x15003D, 0);
            PLAYER.step_s++;
        }
    } else if (--D_80138008 == 0) {
        PLAYER.palette = 0x8100;
        func_8010E570(0);
    }
}

Entity* GetFreeDraEntity(s16 start, s16 end) {
    Entity* entity = &g_Entities[start];
    s16 i;

    for (i = start; i < end; i++, entity++) {
        if (entity->entityId == E_NONE) {
            return entity;
        }
    }
    return NULL;
}

Entity* func_80118810(s16 start, s16 end) {
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
            return;
        }
        self->enemyId = 2;
        return;
    }
    // It appears we're looping over elements of the 8013800C array.
    // If the pointer to arg0 comes before the 32nd (0x20th) g_Entities,
    // we iterate through the 8013800C array, starting from element 3 and going
    // as high as 7, searching for our enemy ID. Otherwise we do the same, but
    // starting from element 7 and going up to 11. 8013800C therefore must have
    // 11 elements. It may be possible to refactor this code to remove the
    // duplication.

    search_value = 0;
    if (self < &g_Entities[UNK_ENTITY_20]) {
        while (1) {
            for (i = 3; i < 7; i++) {
                if (D_8013800C[i] == search_value) {
                    D_8013800C[i]++;
                    self->enemyId = i;
                    return;
                }
            }
            search_value++;
        }
    } else {
        while (1) {
            for (i = 7; i < 11; i++) {
                if (D_8013800C[i] == search_value) {
                    D_8013800C[i]++;
                    self->enemyId = i;
                    return;
                }
            }
            search_value++;
        }
    }
}

INCLUDE_ASM("dra/nonmatchings/75F54", func_80118970);

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
        var_a1 = (ent2->entityId == E_NONE) << 0xC;
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
        entity->entityId = ENTITY_13;
        entity->posX.val = PLAYER.posX.val;
        entity->posY.val = PLAYER.posY.val;
        entity->ext.generic.unk80.modeS16.unk0 = arg0;
        entity->ext.generic.unk80.modeS16.unk2 = arg1;
        return 0;
    }
    return -1;
}

// number appears and moves to HP meter, probably for healing effects
INCLUDE_ASM("dra/nonmatchings/75F54", EntityNumberMovesToHpMeter);

// "Guard" text displays on screen
INCLUDE_ASM("dra/nonmatchings/75F54", EntityGuardText);

void func_80119D3C(Entity* entity) {
    s32 temp;
    s32 cos;

    switch (entity->step) {
    case 0:
        entity->posY.i.hi -= 16;
        entity->zPriority = PLAYER.zPriority - 2;
        entity->ext.generic.unk7C.s = 0;
        entity->step++;
        entity->velocityY = FIX(-0.5);
        entity->ext.generic.unk7E.modeU16 = 0x40;
        entity->animCurFrame = 0xE;
        entity->animSet = ANIMSET_DRA(3);
        entity->ext.generic.unk80.modeS16.unk0 = 0x80;
        entity->flags = FLAG_UNK_08000000;
        break;

    case 1:
        if (entity->ext.generic.unk80.modeS16.unk0 < 32) {
            entity->unk19 = 128;
        }
        entity->posY.val += entity->velocityY;
        cos = rcos(entity->ext.generic.unk7C.s);
        entity->ext.generic.unk7C.s =
            entity->ext.generic.unk7C.s + entity->ext.generic.unk7E.modeU16;
        temp = cos * 8;

        if (!(D_8003C8C4 & 3)) {
            entity->ext.generic.unk7E.modeU16--;
        }
        entity->posX.val += temp;
        entity->ext.generic.unk80.modeS16.unk0--;
        if (entity->ext.generic.unk80.modeS16.unk0 == 0) {
            DestroyEntity(entity);
        }
        break;
    }
}

s32 func_80119E78(Primitive* poly, s32 xCenter, s32 yCenter) {
    s16 left;
    s16 top;
    s16 right;
    s32 size;
    u8* idx;
    // 800AD094 is a read-only array of bytes in 8-byte groups.
    // These are sets of 4 pairs of u,v values.
    // the ->b0 value is very likely fake.
    idx = D_800AD094;
    idx += poly->b0 * 8;
    size = 6;
    if (poly->b0 >= 3U) {
        size = 4;
    }
    if (poly->b0 == 6) {
        return -1;
    }
    left = xCenter - size;
    top = yCenter - size;
    poly->y0 = top;            // a
    poly->y1 = top;            // 16
    poly->x0 = left;           // 8
    poly->x1 = xCenter + size; // 14
    poly->x2 = left;           // 20
    poly->y2 = yCenter + size; // 22
    poly->x3 = xCenter + size; // 2c
    poly->y3 = yCenter + size; // 2e

    poly->u0 = *idx++;
    poly->v0 = *idx++;
    poly->u1 = *idx++;
    poly->v1 = *idx++;
    poly->u2 = *idx++;
    poly->v2 = *idx++;
    poly->u3 = *idx++;
    poly->v3 = *idx;
    if (!(++poly->b1 & 1)) {
        poly->b0++;
    }
    return 0;
}

INCLUDE_ASM("dra/nonmatchings/75F54", func_80119F70);

void func_8011A290(Entity* entity) {
    SubweaponDef subwpn;

    func_800FE3C4(&subwpn, entity->ext.generic.unkB0, 0);
    entity->attack = subwpn.attack;
    entity->attackElement = subwpn.attackElement;
    entity->hitboxState = subwpn.hitboxState;
    entity->nFramesInvincibility = subwpn.nFramesInvincibility;
    entity->stunFrames = subwpn.stunFrames;
    entity->hitEffect = subwpn.hitEffect;
    entity->entityRoomIndex = subwpn.entityRoomIndex;
    entity->ext.generic.unkB2 = subwpn.crashId;
    func_80118894(entity);
}

void func_8011A328(Entity* entity, s32 arg1) {
    SpellDef spell;

    func_800FD9D4(&spell, arg1);
    entity->attack = spell.attack;
    entity->attackElement = spell.attackElement;
    entity->hitboxState = spell.hitboxState;
    entity->nFramesInvincibility = spell.nFramesInvincibility;
    entity->stunFrames = spell.stunFrames;
    entity->hitEffect = spell.hitEffect;
    entity->entityRoomIndex = spell.entityRoomIndex;
    func_80118894(entity);
}

void func_8011A3AC(Entity* arg0, s32 arg1, s32 arg2, Unkstruct_8011A3AC* arg3) {
    SpellDef spell;

    *arg3 = D_80097C38[D_8006CBC4];
    if (arg2 != 0) {
        func_800FD9D4(&spell, arg1);
        arg0->attack = spell.attack;
        arg0->attackElement = spell.attackElement;
        arg0->hitboxState = spell.hitboxState;
        arg0->nFramesInvincibility = spell.nFramesInvincibility;
        arg0->stunFrames = spell.stunFrames;
        arg0->hitEffect = spell.hitEffect;
        arg0->entityRoomIndex = spell.entityRoomIndex;
        arg0->attack = spell.attack * ((arg3->unk0 * 4 / 95) + 1);
        func_80118894(arg0);
    }
}

void func_8011A4C8(Entity* entity) {}

void func_8011A4D0(void) {
    Entity* entity;
    s32 temp_s2;
    s32 i;
    s32 i2;
    s32 i3;
    u16 entityId;
    s32 enemy;
    s32 enemy2;

    temp_s2 = *D_80097420;
    entity = g_CurrentEntity = &g_Entities[4];
    for (i = 4; i < 64; i++, g_CurrentEntity++, entity++) {
        if (i == 16 && entity->entityId == E_NONE) {
            g_Player.unk48 = 0;
        }
        if (entity->entityId == E_NONE) {
            continue;
        }
        if (entity->step == 0) {
            entityId = entity->entityId;
            if (entityId < 0xD0) {
                // Objects 00-CF
                entity->pfnUpdate = D_800AD0C4[entityId];
            } else if (entityId < 0xE0) {
                // Objects D0-DF
                entity->pfnUpdate = D_8016FCC0[entityId];
            } else if (entityId == 0xEF || entityId == 0xFF ||
                       entityId == 0xED || entityId == 0xFD) {
                entity->pfnUpdate = D_800AD0C4[1];
            } else if (entityId == 0xEE || entityId == 0xFE) {
                entity->pfnUpdate = D_800AD0C4[15];
            } else if (entityId >= 0xF0) {
                // Objects F0-FC
                entity->pfnUpdate = D_8017CC40[entityId];
            } else {
                // Objects E0-EC
                entity->pfnUpdate = D_80179C80[entityId];
            }
        }
        if ((temp_s2 == 0) || (entity->flags & FLAG_UNK_10000)) {
            entity->pfnUpdate(entity);
            entity = g_CurrentEntity;
            if (entity->entityId != 0) {
                if (!(entity->flags & FLAG_UNK_04000000) &&
                    ((u16)(entity->posX.i.hi + 32) > 320 ||
                     (u16)(entity->posY.i.hi + 16) > 272)) {
                    DestroyEntity(entity);
                } else {
                    if (entity->flags & 0x100000) {
                        UpdateAnim(NULL, (s32*)D_800ACFB4);
                    }
                }
            }
        }
    }
    if (D_8013803C != 0) {
        if (--D_8013803C & 1) {
            func_800EA5AC(1U, D_80138040, D_80138044, D_80138048);
        }
    }
    D_8013800C[1] = D_8013800C[2] = 0;
    enemy = g_Entities[16].enemyId;
    if (enemy == 1) {
        D_8013800C[1] = 1;
    } else if (enemy == 2) {
        D_8013800C[2] = 1;
    }
    for (i2 = 3; i2 < 11; i2++) {
        D_8013800C[i2] = 0;
    }
    entity = &g_Entities[17];
    for (i3 = 17; i3 < 48; entity++, i3++) {
        enemy2 = entity->enemyId;
        if (enemy2 >= 3) {
            D_8013800C[enemy2]++;
        }
    }
    // Appears to be a temporary debugging block that was left in.
    if ((g_Player.unk0C & 0xC0000) ||
        (PLAYER.step == 0x12 && PLAYER.step_s == 0)) {
        // prints "atari nuki", Japanese for "without hit".
        FntPrint(&aAtariNuki);
        entity = &g_Entities[4];
        // Disable all hitboxes!
        for (i = 4; i < 64; i++, entity++) {
            entity->hitboxState = 0;
        }
    }
}

void func_8011A870(void) {
    Entity* entity = g_CurrentEntity = &g_Entities[UNK_ENTITY_4];
    u16 entityId;
    s32 i = 4;

loop_1: // !FAKE: this should be a for loop
    entityId = entity->entityId;

    if (entityId != 0) {
        if (entity->step == 0) {
            if ((u32)(entity->entityId - 0xD0) < 0x10) {
                entity->pfnUpdate = (PfnEntityUpdate)D_8016FCC0[entityId];
            } else {
                goto label;
            }
        }

        if (entity->pfnUpdate != NULL) {
            entity->pfnUpdate(entity);
            entity = g_CurrentEntity;
            if (entity->entityId != 0) {
                if ((!(entity->flags & FLAG_UNK_04000000)) &&
                    (((u32)((((u16)entity->posX.i.hi) + 0x20) & 0xFFFF) >=
                      0x141) ||
                     ((u32)((((u16)entity->posY.i.hi) + 0x10) & 0xFFFF) >=
                      0x111))) {
                    DestroyEntity(entity);
                    goto label;
                } else if (entity->flags & FLAG_UNK_100000) {
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

void func_8011A9D8(void) {
    Entity* entity;
    s32 i;

    entity = &g_Entities[4];
    g_CurrentEntity = &g_Entities[4];
    for (i = 4; i < 0x40; i++, g_CurrentEntity++, entity++) {
        if (!(entity->flags & FLAG_UNK_20000)) {
            DestroyEntity(entity);
        }
#if defined(VERSION_US)
        if (g_PlayableCharacter == PLAYER_ALUCARD && 0x36 < entity->entityId &&
            entity->entityId < 0x3D && entity->step != 0) {
            entity->pfnUpdate(entity);
        }
#endif
        if (entity->flags & FLAG_UNK_02000000 && entity->step != 0) {
            entity->flags |= FLAG_UNK_00200000;  // set a flag
            entity->pfnUpdate(entity);           // update
            entity->flags &= ~FLAG_UNK_00200000; // unset that same flag
        }
    }
}

Entity* func_8011AAFC(Entity* self, u32 flags, s32 arg2) {
    Entity* entity;
    s16 temp = arg2;

    entity = GetFreeDraEntity(8, 16);
    if (entity == NULL) {
        return NULL;
    }

    DestroyEntity(entity);
    entity->entityId = E_UNK_1;
    entity->ext.generic.unk8C.entityPtr = self;
    entity->posX.val = self->posX.val;
    entity->posY.val = self->posY.val;
    entity->facingLeft = self->facingLeft;
    entity->zPriority = self->zPriority;
    entity->params = flags & 0xFFF;
    if (flags & 0x5000) {
        entity->ext.generic.unkA8 = 0xE0;
    }
    if (flags & 0xA000) {
        entity->ext.generic.unkA8 = 0xF0;
    }
    entity->ext.generic.unkA0 = (flags >> 8) & 0xFF00;
    entity->ext.generic.unk92 = temp;
    if (self->flags & FLAG_UNK_10000) {
        entity->flags |= FLAG_UNK_10000;
    }
    if (flags & 0x1000) {
        entity->entityId = 0xEF;
    }
    if (flags & 0x2000) {
        entity->entityId = 0xFF;
    }
    if (flags & 0x4000) {
        entity->entityId = 0xED;
    }
    if (flags & 0x8000) {
        entity->entityId = 0xFD;
    }

    return entity;
}

INCLUDE_ASM("dra/nonmatchings/75F54", func_8011AC3C);

// Name comes purely from emulator breakpoint experiments, could be wrong
void EntityUnarmedAttack(Entity* entity) {
    Equipment equip;
    AnimSoundEvent* temp_s1;
    u16 paramsTopBit;

    entity->posX.val = PLAYER.posX.val;
    entity->posY.val = PLAYER.posY.val;
    paramsTopBit = entity->params >> 0xF;
    entity->facingLeft = PLAYER.facingLeft;
    temp_s1 = &D_800AD53C[(entity->params >> 6) & 0x1FC];

    if (PLAYER.ext.generic.unkAC < temp_s1->ACshift ||
        (temp_s1->ACshift + 7) <= PLAYER.ext.generic.unkAC ||
        g_Player.unk46 == 0) {
        DestroyEntity(entity);
        return;
    }

    if (entity->step == 0) {
        entity->flags = FLAG_UNK_20000 | FLAG_UNK_40000;
        GetEquipProperties(paramsTopBit, &equip, 0);
        entity->attack = equip.attack;
        entity->attackElement = equip.element;
        entity->hitboxState = equip.hitType;
        entity->nFramesInvincibility = equip.enemyInvincibilityFrames;
        entity->stunFrames = equip.stunFrames;
        entity->hitEffect = equip.hitEffect;
        entity->entityRoomIndex = equip.criticalRate;
        func_80118894(entity);
        entity->step++;
    }
    entity->ext.generic.unkAC = PLAYER.ext.generic.unkAC - temp_s1->ACshift;
    if ((PLAYER.animFrameDuration == 1) &&
        (PLAYER.animFrameIdx == temp_s1->soundFrame)) {
        PlaySfx(temp_s1->soundId);
    }
    if (UpdateUnarmedAnim(temp_s1->frameProps, temp_s1->frames) < 0) {
        DestroyEntity(entity);
    }
}

void func_8011B334(Entity* entity) {
    Equipment equip;

    if (PLAYER.step_s != 0x70) {
        DestroyEntity(entity);
        return;
    }

    entity->flags = FLAG_UNK_20000 | FLAG_UNK_40000;
    entity->facingLeft = PLAYER.facingLeft;
    entity->posY.i.hi = PLAYER.posY.i.hi;
    entity->posX.i.hi = PLAYER.posX.i.hi;
    g_Player.unk44 &= ~0x80;

    if (entity->step == 0) {
        GetEquipProperties(0, &equip, 0);
        entity->attack = equip.attack;
        entity->attackElement = equip.element;
        entity->hitboxState = equip.hitType;
        entity->nFramesInvincibility = equip.enemyInvincibilityFrames;
        entity->stunFrames = equip.stunFrames;
        entity->hitEffect = equip.hitEffect;
        entity->entityRoomIndex = equip.criticalRate;
        func_80118894(entity);
        entity->hitboxOffX = 9;
        entity->hitboxOffY = 21;
        entity->hitboxWidth = 4;
        entity->hitboxHeight = 5;
        entity->step++;
    } else if (entity->hitFlags == 1) {
        g_Player.unk44 |= 0x80;
    }
}

void func_8011B480(Entity* entity) {
    if (PLAYER.step != 5 || PLAYER.step_s != 3) {
        DestroyEntity(entity);
    } else {
        entity->flags = FLAG_UNK_20000 | FLAG_UNK_40000;
        entity->facingLeft = PLAYER.facingLeft;
        entity->posY.i.hi = PLAYER.posY.i.hi;
        entity->posX.i.hi = PLAYER.posX.i.hi;
        if (entity->step == 0) {
            func_8011A328(entity, 6);
            entity->hitboxOffX = 4;
            entity->hitboxOffY = 0;
            entity->hitboxWidth = 12;
            entity->hitboxHeight = 12;
            entity->step++;
        }
    }
}

void func_8011B530(Entity* entity) {
    if (PLAYER.step != 0x25) {
        DestroyEntity(entity);
    } else if (entity->step == 0) {
        entity->flags = FLAG_UNK_20000 | FLAG_UNK_40000;
        func_8011A328(entity, 5);
        entity->step++;
    }
}

INCLUDE_ASM("dra/nonmatchings/75F54", func_8011B5A4);

INCLUDE_ASM("dra/nonmatchings/75F54", func_8011BBE0);

// same as RIC/func_80162E9C
bool func_8011BD48(Entity* entity) {
    s32 i = 0x10;
    s16 objId = entity->entityId;
    s16 params = entity->params;
    Entity* e = &g_Entities[i];
    for (; i < 0x40; i++, e++) {
        if (objId == (s32)e->entityId && params == (s32)e->params &&
            e != entity) {
            return true;
        }
    }

    return false;
}

// player turns white for some sort of status effect
INCLUDE_ASM("dra/nonmatchings/75F54", EntityPlayerBlinkWhite);

// blue outline around player when mp refills
INCLUDE_ASM("dra/nonmatchings/75F54", EntityMpReplenished);

void func_8011E0E4(Entity* entity) {}

INCLUDE_ASM("dra/nonmatchings/75F54", func_8011E0EC);

INCLUDE_ASM("dra/nonmatchings/75F54", func_8011E390);

INCLUDE_ASM("dra/nonmatchings/75F54", func_8011E4BC);

void func_8011EDA0(Entity* entity) {}

INCLUDE_ASM("dra/nonmatchings/75F54", func_8011EDA8);

// same as RIC/func_801601DC
void func_8011F074(Entity* entity) {
    s16 posX;
    s16 posY;

    switch (entity->step) {
    case 0:
        entity->flags = FLAG_UNK_100000 | FLAG_UNK_20000 | FLAG_UNK_08000000;
        entity->unk5A = 0x79;
        entity->animSet = ANIMSET_DRA(14);
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
        entity->velocityY = -0x6000 - (rand() & 0x3FFF);
        entity->step++;
        break;

    case 1:
        if (entity->unk6C >= 17) {
            entity->unk6C += 248;
        }
        entity->posY.val += entity->velocityY;
        entity->unk1A += 8;
        entity->unk1C += 8;
        if (entity->animFrameDuration < 0) {
            DestroyEntity(entity);
        }
        break;
    }
}

// effect when player takes lightning damage
INCLUDE_ASM("dra/nonmatchings/75F54", EntityHitByLightning);

// player gets frozen
INCLUDE_ASM("dra/nonmatchings/75F54", EntityHitByIce);

// transparent white circle closes over player
INCLUDE_ASM("dra/nonmatchings/75F54", EntityTransparentWhiteCircle);

// pink effect on player
INCLUDE_ASM("dra/nonmatchings/75F54", EntityPlayerPinkEffect);

// player dissolves into pixels
INCLUDE_ASM("dra/nonmatchings/75F54", EntityPlayerDissolves);

// level up animation
INCLUDE_ASM("dra/nonmatchings/75F54", EntityLevelUpAnimation);

extern Unkstruct_80138094 D_80138094[];

void func_80121F14(s32 arg0, s32 arg1) {
    Unkstruct_80138094* ptr = D_80138094;
    s32 i;

    for (i = 0; i < 16; i++, ptr++) {
        ptr->unk0 = arg0 + ptr->unk0;
        ptr->unk4 = arg1 + ptr->unk4;
    }
}

INCLUDE_ASM("dra/nonmatchings/75F54", func_80121F58);

// spawns mist (player transform)
INCLUDE_ASM("dra/nonmatchings/75F54", EntityMist);

INCLUDE_ASM("dra/nonmatchings/75F54", func_80123788);

// Appears as D_800AD0C4[49].
void UnknownEntId49(Entity* self) {
    s32 x_offset;

    if (!(g_Player.unk0C & 0x01000000) || (PLAYER.step != 0x2B)) {
        DestroyEntity(self);
        return;
    }
    if (self->step == 0) {
        self->animSet = PLAYER.animSet;
        self->animCurFrame = 7;
        self->unk5A = PLAYER.unk5A;
        self->palette = PLAYER.palette;
        self->facingLeft = PLAYER.facingLeft;
        self->zPriority = PLAYER.zPriority;
        self->flags = 0x04060000;
        self->step++;
    }
    self->unk19 = PLAYER.unk19 & 8;
    self->unk6C = PLAYER.unk6C;

    if (ABS(PLAYER.rotAngle) == 0x200) {
        x_offset = PLAYER.entityRoomIndex != 0 ? 0x10 : -0x10;
        self->posX.i.hi = x_offset + PLAYER.posX.i.hi;
        self->posY.i.hi = PLAYER.posY.i.hi + 9 + ((D_8003C8C4 >> 1) & 1);
    } else {
        x_offset = PLAYER.entityRoomIndex != 0 ? 0x18 : -0x18;
        self->posX.i.hi = x_offset + PLAYER.posX.i.hi;
        self->posY.i.hi = PLAYER.posY.i.hi + 16 + ((D_8003C8C4 >> 1) & 1);
    }
}

void func_80123A60(Entity* entity) {
    Entity* player = &PLAYER;

    if (!(g_Player.unk0C & 0x01000000)) {
        DestroyEntity(entity);
        return;
    }

    entity->posX.i.hi = player->posX.i.hi;
    entity->posY.i.hi = player->posY.i.hi;
    if (entity->step == 0) {
        func_8011A328(entity, 0xB);
        entity->flags = FLAG_UNK_20000 | FLAG_UNK_40000 | FLAG_UNK_04000000;
        entity->step++;
    }

    if (player->animCurFrame == 5) {
        entity->hitboxWidth = 12;
        entity->hitboxHeight = 32;
        entity->hitboxOffX = 0x1C;
        entity->hitboxOffY = -0xC;
        return;
    }

    if (player->animCurFrame == 6) {
        entity->hitboxWidth = 10;
        entity->hitboxHeight = 10;
        entity->hitboxOffX = 0x1C;
        entity->hitboxOffY = 0x10;
        return;
    }

    DestroyEntity(entity);
}

INCLUDE_ASM("dra/nonmatchings/75F54", func_80123B40);

void func_80123F78(Entity* entity) {
    if (D_800973FC == 0) {
        D_80097F3F = 0;
        DestroyEntity(entity);
        return;
    }

    switch (entity->step) {
    case 0:
        entity->flags = FLAG_UNK_10000 | FLAG_UNK_20000 | FLAG_UNK_04000000 |
                        FLAG_UNK_08000000;
        if (PLAYER.animSet != 1) {
            DestroyEntity(entity);
            break;
        }
        entity->animSet = ANIMSET_DRA(1);
        entity->animCurFrame = PLAYER.animCurFrame;
        entity->unk5A = 0xD;
        entity->unk19 = PLAYER.unk19;
        entity->blendMode = 0x30;
        entity->palette = 0x815F;
        entity->zPriority = PLAYER.zPriority - 2;
        entity->facingLeft = PLAYER.facingLeft;
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

void func_80124164(
    POLY_GT4* poly, s32 colorIntensity, s32 y, s32 radius, bool arg4) {
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
INCLUDE_ASM("dra/nonmatchings/75F54", EntityTeleport);

void func_80124A8C(Entity* entity) {
#ifdef PSY_Q_3_5
    if (PLAYER.step != 0 ||
        PLAYER.step_s != 4) { // REAL: Matches with PSY-Q 3.5
#else
    if (*(s32*)&PLAYER.step != 0x40000) { // !FAKE: Probably ASPSX
#endif
        DestroyEntity(entity);
        return;
    }

    switch (entity->step) {
    case 0:
        entity->animSet = ANIMSET_DRA(17);
        entity->velocityY = FIX(-0.375);
        SetSpeedX(0x4000);
        entity->unk5A = 0x50;
        entity->palette = 0x819F;
        entity->unk4C = &D_800AE294;
        entity->flags = FLAG_UNK_100000;
        entity->facingLeft = 0;
        entity->posY.i.hi -= 16;
        entity->posX.val += entity->velocityX << 5;
        entity->step++;
        break;

    case 1:
        entity->posX.val += entity->velocityX;
        entity->posY.val += entity->velocityY;
        if (entity->animFrameDuration < 0) {
            DestroyEntity(entity);
        }
        break;
    }
}

// dagger thrown when using subweapon
INCLUDE_ASM("dra/nonmatchings/75F54", EntitySubwpnThrownDagger);

// axe thrown when using subweapon
INCLUDE_ASM("dra/nonmatchings/75F54", EntitySubwpnThrownAxe);

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
    colRes1 = res1.effects & 0xF801;
    CheckCollision(x, (s16)(y - 1 + res1.unk18), &res2, 0);
    y = baseY + (g_CurrentEntity->posY.i.hi + res1.unk18);

    if ((colRes1 & 0x8801) == 1 || (colRes1 & 0x8801) == 0x0801) {
        colRes2 = res2.effects & 0xF001;
        if (!((s16)res2.effects & 1)) {
            g_CurrentEntity->posY.i.hi = y;
            return 1;
        }
        if ((res2.effects & 0x8001) == 0x8001) {
            g_CurrentEntity->posY.i.hi = y + (s16)(res2.unk18 - 1);
            return colRes2;
        }
    } else if ((colRes1 & 0x8001) == 0x8001) {
        g_CurrentEntity->posY.i.hi = y;
        return colRes1 & 0xF001;
    }
    return 0;
}

s32 func_80125B6C(s16 arg0, s16 arg1) {
    Collider collider;
    s16 var_a1;

    if (g_CurrentEntity->velocityX == 0) {
        return 0;
    }

    CheckCollision(g_CurrentEntity->posX.i.hi + arg1,
                   g_CurrentEntity->posY.i.hi + arg0, &collider, 0);
    if (g_CurrentEntity->velocityX > 0) {
        var_a1 = collider.unk14;
    } else {
        var_a1 = collider.unk1C;
    }

    if (collider.effects & EFFECT_UNK_0002) {
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
        entity->animSet = ANIMSET_DRA(9);
        entity->animCurFrame = 0x1D;
        entity->zPriority = PLAYER.zPriority - 2;
        entity->posY.i.hi += 8;
        SetSpeedX(0x14000);
        entity->velocityY = FIX(-3.125);
        func_8011A290(entity);
        entity->hitboxHeight = 4;
        entity->hitboxWidth = 4;
        g_Player.D_80072F14 = 4;
        entity->step++;
        break;

    case 1:
        entity->posY.val += entity->velocityY;
        if (entity->velocityY <= 0x3FFFF) {
            entity->velocityY += FIX(0.21875);
        }

        temp = func_80125A30(0, 0);
        entity->posX.val += entity->velocityX;

        if (entity->velocityX < 0) {
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
            entity->ext.generic.unk7C.s = 0x10;
            entity->animSet = ANIMSET_DRA(0);
            entity->step = 2;
        }
        break;

    case 2:
        if (!(entity->ext.generic.unk7C.s & 3)) {
            func_8011AAFC(entity, (D_8013841C << 0x10) | 0x1C,
                          entity->ext.generic.unkB2 << 9);
            D_8013841C++;
        }
        entity->ext.generic.unk7C.s--;
        if (entity->ext.generic.unk7C.s == 0) {
            entity->ext.generic.unk7C.s = 4;
            entity->step++;
        }
        break;

    case 3:
        entity->ext.generic.unk7C.s--;
        if (entity->ext.generic.unk7C.s == 0) {
            DestroyEntity(entity);
        }
        break;
    }
}

// glass breaking effect for holy water
INCLUDE_ASM("dra/nonmatchings/75F54", EntityHolyWaterBreakGlass);

// green flame when holy water explodes
INCLUDE_ASM("dra/nonmatchings/75F54", EntityHolyWaterFlame);

// cross subweapon crash (full effect with all parts)
INCLUDE_ASM("dra/nonmatchings/75F54", EntitySubwpnCrashCross);

// rising blue particles from cross crash
void EntitySubwpnCrashCrossParticles(Entity* self) {
    Primitive* poly;
    u16 rand63;

    if (self->step == 0) {
        self->primIndex = AllocPrimitives(PRIM_GT4, 64);
        if (self->primIndex != -1) {
            self->flags = FLAG_UNK_04000000 | FLAG_HAS_PRIMS;
            // entity lives for 192 frames
            self->ext.generic.unk7C.s = 192;
            self->step++;
            return;
        }
        DestroyEntity(self);
        return;
    }
    // This is some kind of time to live, since it decrements and if 0 gets
    // destroyed.
    if (--self->ext.generic.unk7C.s == 0) {
        DestroyEntity(self);
        return;
    }
    // On every third frame, as long as we have over 9 frames left alive
    if ((self->ext.generic.unk7C.s >= 9) && !(self->ext.generic.unk7C.s & 3)) {
        // iterate through primtives until we find one where r0 == 0, and set to
        // 1
        for (poly = &g_PrimBuf[self->primIndex]; poly != NULL;
             poly = poly->next) {
            if (poly->r0 == 0) {
                poly->r0 = 1;
                poly->r1 = 0;
                break;
            }
        }
    }

    for (poly = &g_PrimBuf[self->primIndex]; poly != NULL; poly = poly->next) {
        // for any of those prims with nonzero r0 values,
        if (poly->r0 != 0) {
            // r1 acts as a flag to show whether this has happened.
            if (poly->r1 == 0) {
                rand63 = rand() & 0x3F; // random integer 0-63
                poly->g0 = (rand() % 237) + 9;
                poly->g1 = -0x10 - (rand() & 0x20);
                poly->clut = 0x1B0;
                poly->tpage = 0x1A;
                poly->b0 = 0;
                poly->b1 = 0;
                poly->priority = (rand63 + PLAYER.zPriority) - 0x20;
                poly->blendMode = 0;
                poly->g3 = (rand63 >> 2) + 4; // rand15 + 4 means 4 to 19
                poly->r1++;
            } else {
                poly->g1 -= poly->g3;
                if (((u8)poly->b0 >= 6U) || ((u8)poly->g1 < 0x18U)) {
                    poly->blendMode = BLEND_VISIBLE;
                    poly->r0 = 0;
                }
            }
            if (poly->r0 != 0) {
                func_80119E78(poly, poly->g0, poly->g1);
            }
        }
    }
}

INCLUDE_ASM("dra/nonmatchings/75F54", func_80126ECC);

void func_801274DC(Entity* entity) {
    switch (entity->step) {
    case 0:
        if (entity->params == 0) {
            PlaySfx(0x660);
        }
        entity->flags = FLAG_UNK_100000 | FLAG_UNK_08000000;
        entity->animSet = ANIMSET_DRA(9);
        entity->unk4C = &D_800B0798;
        entity->zPriority = PLAYER.zPriority + 2;
        entity->facingLeft = (PLAYER.facingLeft + 1) & 1;
        SetSpeedX(D_800B0830[entity->params]);
        entity->velocityY = D_800B083C[entity->params];
        entity->ext.generic.unk7C.s = 0x14;
        func_8011A328(entity, 2);
        entity->hitboxWidth = 4;
        entity->hitboxHeight = 4;
        entity->step++;
        break;

    case 1:
        if (entity->hitFlags == 0) {
            entity->ext.generic.unk7C.s--;
            if ((entity->ext.generic.unk7C.s) == 0) {
                entity->step++;
            }
            entity->posX.val += entity->velocityX;
            entity->posY.val += entity->velocityY;
            break;
        }
        DestroyEntity(entity);
        break;

    case 2:
        if (entity->hitFlags != 0) {
            DestroyEntity(entity);
            break;
        }
        entity->posX.val += entity->velocityX;
        break;
    }
}

INCLUDE_ASM("dra/nonmatchings/75F54", func_8012768C);

void func_80127840(Entity* entity) {
    switch (entity->step) {
    case 0:
        if (entity->params != 0) {
            PlaySfx(0x683);
        }

        entity->flags = FLAG_UNK_100000 | FLAG_UNK_08000000;

        if (entity->params != 0) {
            entity->posY.i.hi = entity->posY.i.hi + 16;
        } else {
            entity->posY.i.hi = entity->posY.i.hi - 4;
        }

        entity->animSet = ANIMSET_DRA(9);
        entity->rotAngle = 0;
        entity->unk4C = &D_800B07C8;
        entity->unk19 |= 4;
        entity->zPriority = PLAYER.zPriority + 2;
        entity->facingLeft = (PLAYER.facingLeft + 1) & 1;
        SetSpeedX(-0x10);
        func_8011A328(entity, 2);
        entity->hitboxWidth = 8;
        entity->hitboxHeight = 8;
        entity->step++;
        break;

    case 1:
        if (entity->animFrameIdx >= 23) {
            if (!(D_8003C8C4 & 3)) {
                entity->rotAngle += 0x400;
            }
            if (entity->velocityX < 0) {
                entity->velocityX -= FIX(0.09375);
            } else {
                entity->velocityX += FIX(0.09375);
            }
            if (!(D_8003C8C4 & 1) && (rand() & 1)) {
                func_8011AAFC(entity, 0x10024, 0);
            }
            entity->posX.val += entity->velocityX;
            entity->posY.val += entity->velocityY;
        }
        break;
    }
}

// circle expands out of player
void EntityExpandingCircle(Entity* entity) {
    POLY_GT4* poly;
    s32 primIndex;

    if (PLAYER.facingLeft == 0) {
        entity->posX.i.hi = PLAYER.posX.i.hi - 10;
    } else {
        entity->posX.i.hi = PLAYER.posX.i.hi + 10;
    }
    entity->posY.i.hi = PLAYER.posY.i.hi + 2;

    switch (entity->step) {
    case 0:
        primIndex = AllocPrimitives(PRIM_GT4, 1);
        entity->primIndex = primIndex;
        if (primIndex != -1) {
            entity->ext.generic.unk7C.s = 22;
            entity->ext.generic.unk7E.modeU16 = 26;
            poly = &g_PrimBuf[entity->primIndex];
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
            entity->flags = FLAG_UNK_40000 | FLAG_UNK_04000000 | FLAG_HAS_PRIMS;
            entity->step++;
            break;
        }
        DestroyEntity(entity);
        return;

    case 1:
        entity->ext.generic.unk7C.s += 2;
        entity->ext.generic.unk7E.modeU16 += 2;
        if (entity->ext.generic.unk7C.s >= 0x39) {
            DestroyEntity(entity);
            return;
        }
        break;

    default:
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

    if (entity->ext.generic.unk7C.s >= 0x29) {
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
        ret = AllocPrimitives(PRIM_G4, 1);
        entity->primIndex = ret;

        if (ret == -1) {
            DestroyEntity(entity);
            g_Player.unk5C = 0xFFFF;
            return;
        }

        entity->flags = FLAG_UNK_20000 | FLAG_UNK_40000 | FLAG_UNK_04000000 |
                        FLAG_HAS_PRIMS;
        poly = &g_PrimBuf[entity->primIndex];
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
        if (entity->ext.generic.unk7C.s++ >= 0xE) {
            DestroyEntity(entity);
            return;
        }

    default:
        break;
    }
    poly = &g_PrimBuf[entity->primIndex];
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
    g_CurrentEntity->ext.generic.unk7C.s =
        (arg0 * 2) - g_CurrentEntity->ext.generic.unk7C.s;
    if (g_CurrentEntity->ext.generic.unk80.modeS16.unk2 == 0) {
        g_CurrentEntity->ext.generic.unk80.modeS16.unk0++;
        g_CurrentEntity->ext.generic.unk80.modeS16.unk2++;
    }
}

void func_80127EF0(s16 arg0) {
    if (g_CurrentEntity->ext.generic.unk80.modeS16.unk2 == 0) {
        g_CurrentEntity->ext.generic.unk7C.s =
            (arg0 * 2) - g_CurrentEntity->ext.generic.unk7C.s;
        g_CurrentEntity->ext.generic.unk80.modeS16.unk0++;
        g_CurrentEntity->ext.generic.unk80.modeS16.unk2++;
    }
}

INCLUDE_ASM("dra/nonmatchings/75F54", EntitySubwpnReboundStone);

// ash thrown when using vibhuti subweapon
INCLUDE_ASM("dra/nonmatchings/75F54", EntitySubwpnThrownVibhuti);

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

INCLUDE_ASM("dra/nonmatchings/75F54", func_80128C2C);

INCLUDE_ASM("dra/nonmatchings/75F54", func_801291C4);

INCLUDE_ASM("dra/nonmatchings/75F54", func_80129864);

// opens hole in backround and spirit comes out (ID 0x40)
INCLUDE_ASM("dra/nonmatchings/75F54", EntitySummonSpirit);

// expanding circle effect when activating stopwatch
INCLUDE_ASM("dra/nonmatchings/75F54", EntityStopWatchExpandingCircle);

// stopwatch subweapon effect. stops enemies (Dra Entity 0x2A)
INCLUDE_ASM("dra/nonmatchings/75F54", EntityStopWatch);

void func_8012B78C(Entity* entity) {
    POLY_GT4* poly;
    s32 ret;

    switch (entity->step) {
    case 0:
        ret = AllocPrimitives(PRIM_GT4, 1);
        entity->primIndex = ret;
        if (entity->primIndex != -1) {
            entity->flags = FLAG_UNK_20000 | FLAG_UNK_04000000 | FLAG_HAS_PRIMS;
            poly = &g_PrimBuf[entity->primIndex];
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
            entity->ext.generic.unk7E.modeU16 = 96;
            entity->step++;
        } else {
            DestroyEntity(entity);
            return;
        }
        break;

    case 1:
        if (++entity->ext.generic.unk7C.s > 5) {
            entity->step++;
        }
        entity->ext.generic.unk7E.modeU16 -= 8;
        break;

    case 2:
        DestroyEntity(entity);
        return;

    default:
        break;
    }
    poly = &g_PrimBuf[entity->primIndex];
    poly->r0 = poly->r1 = poly->r2 = poly->r3 = poly->g0 = poly->g1 = poly->g2 =
        poly->g3 = poly->b0 = poly->b1 = poly->b2 = poly->b3 =
            entity->ext.generic.unk7E.modeU8.unk0;
}

// book rotates around player
INCLUDE_ASM("dra/nonmatchings/75F54", EntitySubwpnBible);

// echo of bat effect
INCLUDE_ASM("dra/nonmatchings/75F54", EntityBatEcho);

INCLUDE_ASM("dra/nonmatchings/75F54", func_8012C600);

bool func_8012C88C(void) {
    if (PLAYER.step_s == 0) {
        return false;
    }
    if (PLAYER.step_s == 8) {
        return false;
    }
    if (D_80097448[1] != 0 && !IsRelicActive(RELIC_HOLY_SYMBOL) ||
        g_Player.padTapped & PAD_R2 || func_800FEEA4(2, 1) < 0) {
        SetPlayerStep(Player_Unk25);
        func_8010DA48(0xCA);
        D_800AFDA6 = 1;
        PLAYER.palette = 0x810D;
        g_Player.unk66 = 0;
        g_Player.unk68 = 0;
        func_8011AAFC(g_CurrentEntity, 0x24002C, 0);
        PLAYER.velocityY >>= 1;
        return true;
    }
    return false;
}

void func_8012C97C(void) {
    if (g_Entities[PLAYER_CHARACTER].step_s == 0) {
        return;
    }
    if (g_Entities[PLAYER_CHARACTER].step_s >= 8 &&
        g_Entities[PLAYER_CHARACTER].step_s < 10) {
        return;
    }
    if (D_80097448[1] < 13) {
        return;
    }
    if (!IsRelicActive(RELIC_HOLY_SYMBOL)) {
        return;
    }
    if (!IsRelicActive(RELIC_SKILL_OF_WOLF)) {
        return;
    }
    if (g_Player.pl_vram_flag & 1) {
        return;
    }
    if (!(g_Player.padPressed & PAD_TRIANGLE)) {
        return;
    }
    if (D_80138440 != 0) {
        return;
    }

    PLAYER.step_s = 9;
    D_800B0914 = 0;
    func_8010DA48(0xEC);
    PLAYER.velocityY = 0;
}

void func_8012CA64(void) {
    u32 var_a0;

    PLAYER.step_s = 1;
    D_800B0914 = 0;

    if (g_Player.pl_vram_flag & 0x20) {
        var_a0 = 0xDF;
    } else {
        var_a0 = 0xDE;
    }
    func_8010DA48(var_a0);

    PLAYER.velocityY = 0;
    PLAYER.velocityX /= 2;

    D_800B0918 = 0x200;
    if (g_Player.pl_vram_flag & 0x40) {
        D_800B0914 = 1;
        func_8010DA48(0xE9U);
    }
}

void func_8012CB0C(void) {
    PLAYER.ext.generic.unkAC = 0xDE;
    PLAYER.velocityY = 0;
    D_800B0914 = 0;
    PLAYER.animFrameIdx = 0;
    PLAYER.animFrameDuration = 0;
    PLAYER.step_s = 7;
}

void func_8012CB4C(void) {
    PLAYER.step_s = 2;
    if ((PLAYER.facingLeft != 0 && g_Player.padPressed & PAD_RIGHT) ||
        (PLAYER.facingLeft == 0 && g_Player.padPressed & PAD_LEFT)) {
        func_8010DA48(0xE1);
        D_800B0914 = 0;
        D_8013842C = 0;
        return;
    } else if (D_8013842C != 0) {
        func_8010DA48(0xE2);
        D_800B0914 = 2;
        SetSpeedX(0x20000);
        return;
    } else {
        func_8010DA48(0xE0);
        D_800B0914 = 1;
        D_8013842C = 0xC;
    }
}

void func_8012CC30(s32 arg0) {
    if (arg0 == 0) {
        D_80138444 = 1;
        if (D_80138FC0[1].x == 255 && IsRelicActive(RELIC_SKILL_OF_WOLF) &&
            CastSpell(SPELL_WOLF_CHARGE)) {
            func_8010E27C();
            PLAYER.step_s = 2;
            D_800B0914 = 4;
            SetSpeedX(0x50000);
            g_CurrentEntity->velocityY = 0;
            func_8010DA48(0xEDU);
            LearnSpell(4);
        }
    } else {
        D_80138444 = 1;
    }
}

void func_8012CCE4(void) {
    PLAYER.velocityY = FIX(-3.5);
    if ((PLAYER.step_s == 2) & (D_800B0914 == 2)) {
        func_8010DA48(0xE7);
        // Might be possible to rewrite this block to reduce duplication with
        // some clever && and ||
        if (PLAYER.facingLeft) {
            if ((g_Player.pl_vram_flag & 0xF000) == 0xC000) {
                PLAYER.velocityY = -(ABS(PLAYER.velocityX) + FIX(3.5));
            }
            if ((g_Player.pl_vram_flag & 0xF000) == 0x8000) {
                PLAYER.velocityY = FIX(-0.5);
            }
        } else {
            if ((g_Player.pl_vram_flag & 0xF000) == 0x8000) {
                PLAYER.velocityY = -(ABS(PLAYER.velocityX) + FIX(3.5));
            }
            if ((g_Player.pl_vram_flag & 0xF000) == 0xC000) {
                PLAYER.velocityY = FIX(-0.5);
            }
        }
        D_800B0914 = 2;
    } else if (
        (g_Player.padPressed & (PAD_RIGHT | PAD_LEFT)) &&
        ((PLAYER.step_s != 2) || (D_800B0914 != 0)) && (PLAYER.step_s != 9)) {
        func_8010DA48(0xE7);
        D_800B0914 = 1;
        if (g_Player.padPressed & PAD_UP) {
            PLAYER.velocityY = FIX(-4.875);
        }
    } else {
        func_8010DA48(0xE6);
        D_800B0914 = 0;
        if (g_Player.padPressed & PAD_UP) {
            PLAYER.velocityY = FIX(-4.875);
        }
    }
    PLAYER.step_s = 4;
    D_80138430 += 0x80;
}

void func_8012CED4(void) {
    if (PLAYER.step_s == 2 && D_800B0914 == PLAYER.step_s) {
        func_8010DA48(0xE7);
        D_800B0914 = 1;
    } else {
        func_8010DA48(0xE8);
        SetSpeedX(0x10000);
        D_800B0914 = 0;
        if (D_80138438 & 0x40) {
            PLAYER.animFrameIdx = 4;
            PLAYER.velocityX = 0;
            PLAYER.animFrameDuration = 1;
        }
    }
    PLAYER.step_s = 5;
    g_Player.D_80072F0A = 8;
    PLAYER.velocityY = 0;
    D_80138430 -= 0x100;
}

void func_8012CFA8(void) {
    func_8010DA48(0xEA);
    PLAYER.step_s = 6;
    D_800B0914 = 0;
    PLAYER.velocityX = 0;
    g_Player.D_80072F0A = 8;
}

void func_8012CFF0(void) {
    PLAYER.step_s = 3;
    func_8010DA48(0xE3);
    D_800B0914 = 0;
}

void func_8012D024(void) {
    s32 separation;
    func_8010E1EC(0x2000);
    if (g_Player.padTapped & PAD_CROSS) {
        func_8012CCE4();
        return;
    }
    if (!(g_Player.pl_vram_flag & 1)) {
        func_8012CED4();
        return;
    }
    if (g_Player.padTapped & PAD_SQUARE) {
        func_8012CC30(0);
        return;
    }
    if (g_Player.padPressed & (PAD_RIGHT | PAD_LEFT)) {
        func_8012CB4C();
        return;
    }
    if (g_Player.padPressed & PAD_DOWN) {
        func_8012CFF0();
        return;
    }
    if (D_800B0914 != 0) {
        return;
    }
    separation = (PLAYER.posY.i.hi - g_Entities[17].posY.i.hi);
    if (ABS(separation) < 4 && --D_800B0918 == 0) {
        D_800B0914 = 1;
        func_8010DA48(0xE9);
        return;
    }
    if (g_Player.pl_vram_flag & 0x40) {
        D_800B0914 = 1;
        func_8010DA48(0xE9);
    }
}

void func_8012D178(void) {
    s32 var_v0;

    if (g_Player.padTapped & PAD_CROSS) {
        func_8012CCE4();
    } else if (!(g_Player.pl_vram_flag & 1)) {
        func_8012CFA8();
    } else {
#if defined(VERSION_US)
        if (PLAYER.facingLeft != 0) {
            var_v0 = g_Player.padPressed & PAD_LEFT;
        } else {
            var_v0 = g_Player.padPressed & PAD_RIGHT;
        }
#elif defined(VERSION_HD)
        var_v0 = g_Player.padPressed & (PAD_LEFT | PAD_RIGHT);
#endif
        if (var_v0 != 0) {
            func_8012CB4C();
        } else if (g_Player.unk04 & 0x40) {
            func_8012CA64();
        } else if (D_8003C8C4 == (D_8003C8C4 / 6) * 6) {
            func_8011AAFC(g_CurrentEntity, 0x10045, 0);
        }
    }
}

void func_8012D28C(bool exitEarly) {
    bool bitNotFound;
    s32 i;

    func_80102CD8(2);
    PlaySfx(0x644);
    PLAYER.velocityX = 0;
    g_Player.D_80072EFC = 0x20;
    g_Player.D_80072EF4 = 0;
    // Odd logic, if we exit early, we force an R2-tap. Strange!
    if (exitEarly) {
        g_Player.padTapped = PAD_R2;
        func_8012C88C();
        return;
    }
    // Start a routine where we look through this array for a value.
    bitNotFound = 0;
    for (i = 3; i < 7; i++) {
        if ((g_Player.D_80072CF0[i][0] & 2)) {
            break;
        }
    }
    // If we made it through that loop without finding one, skip i=7,8,9
    // and keep searching.
    if (i == 7) {
        for (i = 10; i < 14; i++) {
            if ((g_Player.D_80072CF0[i][0] & 2)) {
                break;
            }
        }
    }
    // If we even made it through that one, then conclude the bit was not found.
    if (i == 14) {
        bitNotFound++;
    }

    SetSpeedX(FIX(1));
    func_8011AAFC(g_CurrentEntity, 0x90004U, 0);
    D_800B0914 = 0;
    // Finally make use of that bit to control if X is positive or negative.
    if (bitNotFound) {
        func_8012CED4();
        SetSpeedX(FIX(1));
    } else {
        func_8012CFA8();
        SetSpeedX(FIX(-1));
    }
    PLAYER.velocityY = FIX(-3.5);
}
