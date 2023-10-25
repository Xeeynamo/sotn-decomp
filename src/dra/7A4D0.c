#include "dra.h"
#include "objects.h"
#include "sfx.h"

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

void func_8011AC3C(Entity* self) {
    Entity* newEntity;
    s16 unk96Copy;
    s16 i;
    u8 endIndex;
    s16 startIndex;
    u8* data_idx;

    if (self->step == 0) {
        data_idx = &D_800AD1D4[self->params][0];
        self->ext.unkAC3C.unk90 = *data_idx++;          // index 0
        self->ext.unkAC3C.unk94 = *data_idx++;          // index 1
        self->ext.unkAC3C.unk96 = *data_idx & 0x3F;     // index 2
        self->ext.unkAC3C.unk9E = *data_idx >> 7;       // index 2
        self->ext.unkAC3C.unkA2 = *data_idx++ >> 6 & 1; // index 2
        self->ext.unkAC3C.unk98 = *data_idx++;          // index 3
        self->ext.unkAC3C.unk9C = *data_idx & 0xF;      // index 4
        self->ext.unkAC3C.unkA4 = *data_idx++ >> 4;     // index 4
        self->ext.unkAC3C.unk9A = *data_idx;            // index 5
        self->flags |= FLAG_UNK_04000000;

        self->step++;
        switch (self->ext.unkAC3C.unkA4) {
        case 0:
        case 6:
            self->flags |= FLAG_UNK_08000000;
            break;
        case 4:
        case 5:
            self->flags |= FLAG_UNK_20000;
        case 2:
        case 7:
            self->posX.val = PLAYER.posX.val;
            self->posY.val = PLAYER.posY.val;
            break;
        }
    } else {
        switch (self->ext.unkAC3C.unkA4) {
        case 0:
            break;
        case 2:
            self->posX = PLAYER.posX.val;
            self->posY = PLAYER.posY.val;
            break;
        case 4:
            self->posX = PLAYER.posX.val;
            self->posY = PLAYER.posY.val;
            if (PLAYER.step != Player_Walk) {
                self->entityId = 0;
                return;
            }
            break;
        case 5:
            self->posX = PLAYER.posX.val;
            self->posY = PLAYER.posY.val;
            if (PLAYER.step_s != 0x70) {
                self->entityId = 0;
                return;
            }
            break;
        case 7:
            self->posX = PLAYER.posX.val;
            self->posY = PLAYER.posY.val;
            if (PLAYER.step != Player_Hit) {
            setIdZeroAndReturn:
                self->entityId = 0;
                return;
            }
            break;
        }
    }
    if (self->ext.unkAC3C.unk9A != 0) {
        self->ext.unkAC3C.unk9A--;
        if (self->ext.unkAC3C.unk9A != 0) {
            return;
        }
        self->ext.unkAC3C.unk9A = self->ext.unkAC3C.unk98;
    }
    // Save this value so we don't have to re-fetch on every for-loop cycle
    unk96Copy = self->ext.unkAC3C.unk96;
    for (i = 0; i < unk96Copy; i++) {

        // !FAKE, this should probably be &D_800AD4B8[unk9C] or similar,
        // instead of doing &D_800AD4B8 followed by +=
        data_idx = &D_800AD4B8[0];
        data_idx += self->ext.unkAC3C.unk9C * 2;

        startIndex = *data_idx;
        endIndex = *(data_idx + 1);

        if (self->ext.unkAC3C.unk9C == 3 || self->ext.unkAC3C.unk9C == 10 ||
            self->ext.unkAC3C.unk9C == 11 || self->ext.unkAC3C.unk9C == 12 ||
            self->ext.unkAC3C.unk9C == 13) {
            DestroyEntity(&g_Entities[startIndex]);
            newEntity = &g_Entities[startIndex];
            g_Player.unk48 = 0;
        } else if (self->ext.unkAC3C.unk9C == 0) {
            newEntity = func_80118810(startIndex, endIndex + 1);
        } else if (self->ext.unkAC3C.unk9C == 8) {
            if ((self->ext.unkAC3C.unkA6 % 3) == 0) {
                newEntity = GetFreeDraEntity(17, 32);
            }
            if ((self->ext.unkAC3C.unkA6 % 3) == 1) {
                newEntity = GetFreeDraEntity(32, 48);
            }
            if ((self->ext.unkAC3C.unkA6 % 3) == 2) {
                newEntity = GetFreeDraEntity(48, 64);
            }
        } else {
            newEntity = GetFreeDraEntity(startIndex, endIndex + 1);
        }

        if (newEntity == NULL) {
            if (self->ext.unkAC3C.unk9E == 1) {
                goto setIdZeroAndReturn;
            }
            break;
        }
        DestroyEntity(newEntity);
        newEntity->entityId = self->ext.unkAC3C.unk90 + self->ext.unkAC3C.unkA8;
        newEntity->params = self->ext.unkAC3C.unkA0;
        newEntity->ext.unkAC3C.unk8C = self->ext.unkAC3C.unk8C;
        newEntity->posX.val = self->posX.val;
        newEntity->posY.val = self->posY.val;
        newEntity->facingLeft = self->facingLeft;
        newEntity->zPriority = self->zPriority;
        newEntity->ext.fam.cameraY = self->ext.unkAC3C.unk92 & 0x1FF;
        newEntity->ext.unkAC3C.unkB0 = self->ext.unkAC3C.unk92 >> 9;
        if (self->flags & FLAG_UNK_10000) {
            newEntity->flags |= FLAG_UNK_10000;
        }
        if (self->ext.unkAC3C.unkA2 != 0) {
            newEntity->params += self->ext.unkAC3C.unkA6;
        } else {
            newEntity->params += i;
        }
        if (++self->ext.unkAC3C.unkA6 == self->ext.unkAC3C.unk94) {
            self->entityId = 0;
            return;
        }
    }
    self->ext.unkAC3C.unk9A = self->ext.unkAC3C.unk98;
}

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

INCLUDE_ASM("dra/nonmatchings/7A4D0", func_8011B5A4);

void EntityUnkId24(Entity* self) {
    u16 upperparams = self->params >> 8;
    if (self->step == 0) {
        self->animSet = 2;
        self->unk4C = D_800AD5FC;

        // Weird thing here where we have to set flags to the same value twice
        self->flags = FLAG_UNK_08000000 | FLAG_UNK_100000;
        self->zPriority = PLAYER.zPriority + 2;
        self->flags = FLAG_UNK_08000000 | FLAG_UNK_100000;

        self->velocityY = FIX(-1);
        if (upperparams == 0) {
            self->posX.i.hi -= 32 - (rand() & 63);
            self->posY.i.hi -= 48 - (rand() & 63);
            self->blendMode = 0x10;
            self->palette = 0x8195;
        } else {
            self->posY.i.hi -= 12 - rand() % 24;
            self->drawFlags = 3;
            self->rotX = self->rotY = 0x80;
            self->palette = 0x8170;
        }
        self->step++;
        return;
    }
    if (self->animFrameDuration < 0) {
        DestroyEntity(self);
    }
    self->posY.val += self->velocityY;
    self->posX.val += self->velocityX;
}

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
INCLUDE_ASM("dra/nonmatchings/7A4D0", EntityPlayerBlinkWhite);

// blue outline around player when mp refills
INCLUDE_ASM("dra/nonmatchings/7A4D0", EntityMpReplenished);

void func_8011E0E4(Entity* entity) {}

void EntityGravityBootBeam(Entity* self) {
    Primitive* prim;
    s16 halfWidth;
    s32 i;
    s32 yOffset = -12;

    switch (self->step) {
    case 0:
        self->posY.i.hi = PLAYER.posY.i.hi + 37;
        self->ext.bootBeam.timer = 1536;
        self->primIndex = func_800EDB58(PRIM_G4_ALT, 4);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags = FLAG_UNK_08000000 | FLAG_UNK_04000000 | FLAG_HAS_PRIMS |
                      FLAG_UNK_20000;
        for (prim = &g_PrimBuf[self->primIndex]; prim != NULL;
             prim = prim->next) {
            prim->g0 = prim->r0 = 0;
            prim->b0 = 0xC0;
            prim->g1 = prim->r1 = 0;
            prim->b1 = 0xC0;
            prim->b3 = prim->g3 = prim->r3 = prim->b2 = prim->g2 = prim->r2 =
                0x40;
            prim->priority = PLAYER.zPriority - 2;
            prim->blendMode = 0x537;
        }
        self->step++;
        break;

    case 1:
        if (PLAYER.velocityY > FIX(-1.5)) {
            self->step = 2;
        }
        // If transformed, timer drains faster
        if (g_Player.unk0C & PLAYER_STATUS_TRANSFORM) {
            self->step = 3;
        }
        break;
    case 3:
        // note that with the fallthrough these decrements stack
        self->ext.bootBeam.timer -= 160;
    case 2:
        self->ext.bootBeam.timer -= 96;
        if (self->ext.bootBeam.timer < 0) {
            DestroyEntity(self);
            return;
        }
        break;
    }
    for (i = 0, prim = &g_PrimBuf[self->primIndex]; prim != NULL; i++,
        prim = prim->next) {
        // As timer counts down, beam gets narrower.
        halfWidth = (self->ext.bootBeam.timer >> 8) - i;
        if (halfWidth << 16 < 0) {
            halfWidth = 0;
        }
        prim->x0 = self->posX.i.hi - halfWidth;
        prim->x1 = halfWidth + self->posX.i.hi;
        prim->x2 = PLAYER.posX.i.hi - halfWidth;
        prim->x3 = halfWidth + PLAYER.posX.i.hi;
        prim->y2 = prim->y3 = PLAYER.posY.i.hi - yOffset;
        prim->y0 = prim->y1 = self->posY.i.hi;
    }
}

// The blue outlines of the bat that show up when wing smashing
void EntityWingSmashTrail(Entity* entity) {
    // Make sure we are currently wing smashing.
    if (!(PLAYER.step == Player_MorphBat && PLAYER.step_s == 3)) {
        DestroyEntity(entity);
        return;
    }
    if (entity->step == 0) {
        entity->flags = FLAG_UNK_08000000;
        entity->animSet = PLAYER.animSet;
        entity->animCurFrame = PLAYER.animCurFrame | 0x8000;
        entity->zPriority = PLAYER.zPriority - 2;
        entity->drawFlags = PLAYER.drawFlags | 0xB;
        entity->unk6C = 0x80; // a lifetime counter
        entity->blendMode = 0x30;
        entity->rotZ = PLAYER.rotZ;
        entity->facingLeft = PLAYER.facingLeft;
        entity->palette = 0x8102;
        entity->rotX = entity->rotY = 0x100;
        entity->step++;
        return;
    }
    // This actually makes the wing smashes shrink over time, not rotate.
    entity->rotX -= 8;
    entity->rotY -= 8;
    entity->animCurFrame = PLAYER.animCurFrame | 0x8000;
    // Unclear why we count down by 5's instead of just making unk6C start
    // smaller
    if (entity->unk6C >= 5) {
        entity->unk6C -= 5;
    } else {
        DestroyEntity(entity);
    }
}
