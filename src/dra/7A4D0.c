#include "dra.h"
#include "dra_bss.h"
#include "objects.h"
#include "sfx.h"

PfnEntityUpdate g_DraEntityTbl[] = {
    func_8011A4C8,
    EntityEntFactory,
    func_8011B5A4,
    EntityGravityBootBeam,
    EntitySubwpnThrownDagger,
    func_8011E4BC,
    EntityDiveKickAttack,
    EntityGiantSpinningCross,
    EntitySubwpnCrashCross,
    EntitySubwpnCrashCrossParticles,
    EntitySubwpnThrownAxe,
    EntityPlayerBlinkWhite,
    EntitySubwpnThrownVibhuti,
    func_8011E0E4,
    func_8011EDA0,
    EntityUnarmedAttack,
    func_8011EDA8,
    EntitySubwpnAgunea,
    EntityAguneaHitEnemy,
    EntityNumberMovesToHpMeter,
    EntitySubwpnReboundStone,
    EntityLevelUpAnimation,
    EntityHolyWater,
    EntityHolyWaterFlame,
    EntityUnkId24,
    EntityHellfireHandler,
    EntityHellfireNormalFireball,
    EntityHellfireBigFireball,
    EntityExpandingCircle,
    func_80127CC8,
    EntityHitByLightning,
    EntityPlayerOutline,
    EntityPlayerDissolves,
    EntityHitByIce,
    EntityMist,
    EntityWingSmashTrail,
    func_8011B480,
    EntityGuardText,
    EntityTransparentWhiteCircle,
    EntityPlayerPinkEffect,
    EntityHolyWaterBreakGlass,
    EntityStopWatch,
    EntityStopWatchExpandingCircle,
    EntitySubwpnBible,
    func_8012B78C,
    EntityBatFireball,
    func_80123B40,
    func_80119F70,
    UnknownEntId48,
    UnknownEntId49,
    func_80123A60,
    func_80119D3C,
    EntityBatEcho,
    func_8011B530,
    func_8011F074,
    func_80130264,
    func_8012F894,
    func_80130618,
    func_801309B4,
    func_80130E94,
    func_8013136C,
    func_80129864,
    func_8011A4C8,
    EntitySummonSpirit,
    func_80123F78,
    EntityTeleport,
    func_80124A8C,
    func_8011A4C8};

// Corresponding RIC function is RicUpdatePlayerEntities
void UpdatePlayerEntities(void) {
    Entity* entity;
    s32 temp_s2;
    s32 i;
    s32 i2;
    s32 enemy;

    temp_s2 = g_unkGraphicsStruct.unk20;
    entity = g_CurrentEntity = &g_Entities[4];
    for (i = 4; i < 64; i++, g_CurrentEntity++, entity++) {
        if (i == 16 && entity->entityId == E_NONE) {
            g_Player.unk48 = 0;
        }
        if (entity->entityId == E_NONE) {
            continue;
        }
        if (entity->step == 0) {
            if (entity->entityId < 0xD0) {
                // Objects 00-CF
                entity->pfnUpdate = g_DraEntityTbl[entity->entityId];
            } else if (entity->entityId < 0xE0) {
                // Objects D0-DF
                entity->pfnUpdate =
                    ((PfnEntityUpdate*)&D_80170000)[entity->entityId - 0xD0];
            } else if (entity->entityId == 0xEF || entity->entityId == 0xFF ||
                       entity->entityId == 0xED || entity->entityId == 0xFD) {
                entity->pfnUpdate = g_DraEntityTbl[1];
            } else if (entity->entityId == 0xEE || entity->entityId == 0xFE) {
                entity->pfnUpdate = g_DraEntityTbl[15];
            } else if (entity->entityId >= 0xF0) {
                // Objects F0-FC
                entity->pfnUpdate =
                    ((PfnEntityUpdate*)&D_8017D000)[entity->entityId - 0xF0];
            } else {
                // Objects E0-EC
                entity->pfnUpdate =
                    ((PfnEntityUpdate*)&D_8017A000)[entity->entityId - 0xE0];
            }
        }
        if ((temp_s2 == 0) || (entity->flags & FLAG_UNK_10000)) {
            entity->pfnUpdate(entity);
            entity = g_CurrentEntity;
            if (entity->entityId != 0) {
                if (!(entity->flags & FLAG_UNK_04000000) &&
                    (entity->posX.i.hi > 288 || entity->posX.i.hi < -32 ||
                     entity->posY.i.hi > 256 || entity->posY.i.hi < -16)) {
                    DestroyEntity(g_CurrentEntity);
                } else {
                    if (entity->flags & 0x100000) {
                        UpdateAnim(NULL, D_800ACFB4);
                    }
                }
            }
        }
    }
    if (D_8013803C) {
        D_8013803C--;
        if (D_8013803C & 1) {
            func_800EA5AC(1U, D_80138040, D_80138044, D_80138048);
        }
    }
    D_8013800C[1] = D_8013800C[2] = 0;
    if (g_Entities[16].enemyId == 1) {
        D_8013800C[1] = 1;
    } else if (g_Entities[16].enemyId == 2) {
        D_8013800C[2] = 1;
    }
    for (i2 = 3; i2 < 11; i2++) {
        D_8013800C[i2] = 0;
    }
    entity = &g_Entities[17];
    for (i2 = 17; i2 < 48; entity++, i2++) {
        enemy = entity->enemyId;
        if (2 < enemy) {
            D_8013800C[enemy]++;
        }
    }
    // Appears to be a temporary debugging block that was left in.
    if ((g_Player.unk0C & 0xC0000) ||
        (PLAYER.step == Player_Teleport && PLAYER.step_s == 0)) {
#if defined(VERSION_US)
        // Japanese for "without hit".
        FntPrint("atari nuki\n");
#elif defined(VERSION_HD)
        FntPrint("dead player\n");
#endif
        entity = &g_Entities[4];
        // Disable all hitboxes!
        for (i = 4; i < 64; i++, entity++) {
            entity->hitboxState = 0;
        }
    }
}

void func_8011A870(void) {
    Entity* entity;
    s32 i;

    g_CurrentEntity = &g_Entities[UNK_ENTITY_4];
    entity = g_CurrentEntity;
    for (i = UNK_ENTITY_4; i < UNK_ENTITY_8; i++, g_CurrentEntity++, entity++) {
        if (entity->entityId == 0) {
            continue;
        }

        if (entity->step == 0) {
            if (entity->entityId >= 0xD0 && entity->entityId < 0xE0) {
                entity->pfnUpdate =
                    ((PfnEntityUpdate*)&D_80170000)[entity->entityId - 0xD0];
            } else {
                continue;
            }
        }

        if (entity->pfnUpdate) {
            entity->pfnUpdate(entity);
            entity = g_CurrentEntity;
            if (entity->entityId != 0) {
                if (!(entity->flags & FLAG_UNK_04000000) &&
                    (entity->posX.i.hi < -0x20 || entity->posX.i.hi > 0x120 ||
                     entity->posY.i.hi < -0x10 || entity->posY.i.hi > 0x100)) {
                    DestroyEntity(entity);
                } else if (entity->flags & FLAG_UNK_100000) {
                    UpdateAnim(NULL, D_800ACFB4);
                }
            }
        }
    }
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

Entity* CreateEntFactoryFromEntity(
    Entity* source, u32 factoryParams, s32 arg2_raw) {
    Entity* newFactory;
    // Weird thing needed for callers to match
    s16 arg2 = arg2_raw;

    newFactory = GetFreeEntity(8, 16);
    if (newFactory == NULL) {
        return NULL;
    }

    DestroyEntity(newFactory);
    newFactory->entityId = E_ENTITYFACTORY;
    newFactory->ext.factory.parent = source;
    newFactory->posX.val = source->posX.val;
    newFactory->posY.val = source->posY.val;
    newFactory->facingLeft = source->facingLeft;
    newFactory->zPriority = source->zPriority;
    newFactory->params = factoryParams & 0xFFF;
    if (factoryParams & 0x5000) {
        newFactory->ext.factory.unkA8 = 0xE0;
    }
    if (factoryParams & 0xA000) {
        newFactory->ext.factory.unkA8 = 0xF0;
    }
    newFactory->ext.factory.unkA0 = (factoryParams >> 8) & 0xFF00;
    newFactory->ext.factory.unk92 = arg2;
    if (source->flags & FLAG_UNK_10000) {
        newFactory->flags |= FLAG_UNK_10000;
    }
    if (factoryParams & 0x1000) {
        newFactory->entityId = 0xEF;
    }
    if (factoryParams & 0x2000) {
        newFactory->entityId = 0xFF;
    }
    if (factoryParams & 0x4000) {
        newFactory->entityId = 0xED;
    }
    if (factoryParams & 0x8000) {
        newFactory->entityId = 0xFD;
    }

    return newFactory;
}

// This is a complicated function with ongoing research.
// This function is created with its self->params which defines
// what blueprint to read in order to create an entity. Then, based on
// that blueprint, it creates some number of child entities.
// This entity has an ID of 1, but is not an "entity" of an independent
// variety. It is only responsible for creating child entities.
void EntityEntFactory(Entity* self) {
    Entity* newEntity;
    s16 unk96Copy;
    s16 i;
    u8 endIndex;
    s16 startIndex;
    u8* data_idx;

    if (self->step == 0) {
        data_idx = &g_FactoryBlueprints[self->params];
        self->ext.factory.childId = *data_idx++;
        self->ext.factory.unk94 = *data_idx++;          // index 1
        self->ext.factory.unk96 = *data_idx & 0x3F;     // index 2, lower 6 bits
        self->ext.factory.unk9E = *data_idx >> 7;       // index 2, top bit
        self->ext.factory.unkA2 = *data_idx++ >> 6 & 1; // index 2, 2nd-top bit
        self->ext.factory.unk98 = *data_idx++;          // index 3
        self->ext.factory.unk9C = *data_idx & 0xF;      // index 4, lower 4 bits
        self->ext.factory.unkA4 = *data_idx++ >> 4;     // index 4, upper 4 bits
        self->ext.factory.unk9A = *data_idx;            // index 5
        self->flags |= FLAG_UNK_04000000;

        self->step++;
        switch (self->ext.factory.unkA4) {
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
        switch (self->ext.factory.unkA4) {
        case 0:
            break;
        case 2:
            self->posX.val = PLAYER.posX.val;
            self->posY.val = PLAYER.posY.val;
            break;
        case 4:
            self->posX.val = PLAYER.posX.val;
            self->posY.val = PLAYER.posY.val;
            if (PLAYER.step != Player_Walk) {
                self->entityId = 0;
                return;
            }
            break;
        case 5:
            self->posX.val = PLAYER.posX.val;
            self->posY.val = PLAYER.posY.val;
            if (PLAYER.step_s != 0x70) {
                self->entityId = 0;
                return;
            }
            break;
        case 7:
            self->posX.val = PLAYER.posX.val;
            self->posY.val = PLAYER.posY.val;
            if (PLAYER.step != Player_Hit) {
            setIdZeroAndReturn:
                self->entityId = 0;
                return;
            }
            break;
        }
    }
    if (self->ext.factory.unk9A != 0) {
        self->ext.factory.unk9A--;
        if (self->ext.factory.unk9A != 0) {
            return;
        }
        self->ext.factory.unk9A = self->ext.factory.unk98;
    }
    // Save this value so we don't have to re-fetch on every for-loop cycle
    unk96Copy = self->ext.factory.unk96;
    for (i = 0; i < unk96Copy; i++) {

        // !FAKE, this should probably be &D_800AD4B8[unk9C] or similar,
        // instead of doing &D_800AD4B8 followed by +=
        data_idx = &D_800AD4B8[0];
        data_idx += self->ext.factory.unk9C * 2;

        startIndex = *data_idx;
        endIndex = *(data_idx + 1);

        if (self->ext.factory.unk9C == 3 || self->ext.factory.unk9C == 10 ||
            self->ext.factory.unk9C == 11 || self->ext.factory.unk9C == 12 ||
            self->ext.factory.unk9C == 13) {
            DestroyEntity(&g_Entities[startIndex]);
            newEntity = &g_Entities[startIndex];
            g_Player.unk48 = 0;
        } else if (self->ext.factory.unk9C == 0) {
            newEntity = GetFreeEntityReverse(startIndex, endIndex + 1);
        } else if (self->ext.factory.unk9C == 8) {
            if ((self->ext.factory.unkA6 % 3) == 0) {
                newEntity = GetFreeEntity(17, 32);
            }
            if ((self->ext.factory.unkA6 % 3) == 1) {
                newEntity = GetFreeEntity(32, 48);
            }
            if ((self->ext.factory.unkA6 % 3) == 2) {
                newEntity = GetFreeEntity(48, 64);
            }
        } else {
            newEntity = GetFreeEntity(startIndex, endIndex + 1);
        }

        if (newEntity == NULL) {
            if (self->ext.factory.unk9E == 1) {
                goto setIdZeroAndReturn;
            }
            break;
        }
        DestroyEntity(newEntity);
        // unkA8 never gets set so is always zero
        newEntity->entityId =
            self->ext.factory.childId + self->ext.factory.unkA8;
        newEntity->params = self->ext.factory.unkA0;
        // The child  (newEntity) is not an ent factory, but because the factory
        // creates many entities, we can't pick a particular extension. But
        // we're not allowed to use generic, so i'll just reuse entFactory.
        newEntity->ext.factory.parent = self->ext.factory.parent;
        newEntity->posX.val = self->posX.val;
        newEntity->posY.val = self->posY.val;
        newEntity->facingLeft = self->facingLeft;
        newEntity->zPriority = self->zPriority;
        newEntity->ext.factory.unkAE = self->ext.factory.unk92 & 0x1FF;
        newEntity->ext.factory.unkB0 = self->ext.factory.unk92 >> 9;
        if (self->flags & FLAG_UNK_10000) {
            newEntity->flags |= FLAG_UNK_10000;
        }
        if (self->ext.factory.unkA2 != 0) {
            newEntity->params += self->ext.factory.unkA6;
        } else {
            newEntity->params += i;
        }
        if (++self->ext.factory.unkA6 == self->ext.factory.unk94) {
            self->entityId = 0;
            return;
        }
    }
    self->ext.factory.unk9A = self->ext.factory.unk98;
}

extern WeaponAnimation D_800AD53C[];
void EntityUnarmedAttack(Entity* entity) {
    Equipment equip;
    WeaponAnimation* anim;
    u16 handId;
    s16 subType;

    entity->posX.val = PLAYER.posX.val;
    entity->posY.val = PLAYER.posY.val;
    entity->facingLeft = PLAYER.facingLeft;
    handId = entity->params >> 0xF;
    subType = entity->params & 0x7FFF;
    subType >>= 8;
    anim = &D_800AD53C[subType];

    if (PLAYER.ext.player.anim < anim->frameStart ||
        (anim->frameStart + 7) <= PLAYER.ext.player.anim ||
        g_Player.unk46 == 0) {
        DestroyEntity(entity);
        return;
    }

    if (entity->step == 0) {
        entity->flags = FLAG_UNK_20000 | FLAG_UNK_40000;
        GetEquipProperties(handId, &equip, 0);
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
    entity->ext.weapon.anim = PLAYER.ext.player.anim - anim->frameStart;
    if ((PLAYER.animFrameDuration == 1) &&
        (PLAYER.animFrameIdx == anim->soundFrame)) {
        PlaySfx(anim->soundId);
    }
    if (UpdateUnarmedAnim(anim->frameProps, anim->frames) < 0) {
        DestroyEntity(entity);
    }
}

void EntityDiveKickAttack(Entity* self) {
    Equipment equip;
    s32 zero = 0; // needed for PSP

    if (PLAYER.step_s != 0x70) {
        DestroyEntity(self);
        return;
    }

    self->flags = FLAG_UNK_20000 | FLAG_UNK_40000;
    self->facingLeft = PLAYER.facingLeft;
    self->posY.i.hi = PLAYER.posY.i.hi;
    self->posX.i.hi = PLAYER.posX.i.hi;
    g_Player.unk44 &= ~0x80;

    if (self->step == 0) {
        GetEquipProperties(zero, &equip, 0);
        self->attack = equip.attack;
        self->attackElement = equip.element;
        self->hitboxState = equip.hitType;
        self->nFramesInvincibility = equip.enemyInvincibilityFrames;
        self->stunFrames = equip.stunFrames;
        self->hitEffect = equip.hitEffect;
        self->entityRoomIndex = equip.criticalRate;
        func_80118894(self);
        self->hitboxOffX = 9;
        self->hitboxOffY = 21;
        self->hitboxWidth = 4;
        self->hitboxHeight = 5;
        self->step++;
    } else if (self->hitFlags == 1) {
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

// Entity #2. Many blueprints. Matches RIC func_80160FC4
void func_8011B5A4(Entity* self) {
    byte stackpad[40];
    s16 posX;
    s32 i;
    s16 paramsLo;
    s16 paramsHi;

    switch (self->step) {
    case 0:
        // Note that paramsHi is uninitialized here - possible bug?
        if ((g_Player.unk0C & 0x20000) && (paramsHi != 9)) {
            DestroyEntity(self);
            return;
        }

        self->animSet = 5;
        self->anim = D_800AD57C;
        self->zPriority = PLAYER.zPriority + 2;
        self->flags = FLAG_UNK_08000000 | FLAG_UNK_100000 | FLAG_UNK_10000;
        self->palette = 0x8195;
        paramsHi = self->params >> 8;
        paramsLo = self->params & 0xFF;
        self->drawMode = DRAW_TPAGE;
        self->drawFlags = FLAG_DRAW_ROTY | FLAG_DRAW_ROTX;

        posX = D_800AD54C[paramsLo];
        if (paramsHi == 0) {
            posX += 6;
        }
        if (paramsHi == 1) {
            posX -= 8;
        }
        if ((paramsHi == 2) || (paramsHi == 0xA)) {
            posX -= 2;
        }
        if (paramsHi == 5) {
            posX = -6;
        }
        if (paramsHi == 6) {
            posX = -24;
        }
        if (paramsHi == 3) {
            posX = (rand() % 30) - 0xE;
            paramsLo = (rand() & 3) + 2;
            self->posY.i.hi -= rand() % 4;
        }
        if (paramsHi == 7) {
            posX = (rand() % 60) - 0x1E;
            paramsLo = (rand() & 3) + 2;
            self->posY.i.hi -= rand() % 4;
        }
        if (paramsHi == 9) {
            posX = rand() % 16 - 8;
            paramsLo = (rand() & 3) + 2;
            self->posY.i.hi -= (20 + (rand() % 4));
        }
        if (paramsHi == 4) {
            for (i = paramsLo * 2; i < 14; i++) {
                if (g_Player.colliders3[D_800AD5E0[i]].effects & 3) {
                    break;
                }
            }
            if (i == 14) {
                DestroyEntity(self);
                return;
            }
            self->posX.i.hi = PLAYER.posX.i.hi + D_800ACEE0[D_800AD5E0[i]].x;
            self->posY.i.hi = PLAYER.posY.i.hi + D_800ACEE0[D_800AD5E0[i]].y;
            self->velocityY = FIX(-0.25);
            self->rotY = self->rotX = D_800AD570[1] + 0x40;
            self->step++;
            return;
        }
        if (paramsHi == 8) { /* switch 1 */
            for (i = paramsLo * 2; i < 10; i++) {
                if (g_Player.colliders3[D_800AD5F0[i]].effects & 3) {
                    break;
                }
            }
            if (i == 10) {
                DestroyEntity(self);
                return;
            }
            self->posX.i.hi = PLAYER.posX.i.hi + D_800ACEE0[D_800AD5F0[i]].x;
            self->posY.i.hi = PLAYER.posY.i.hi + D_800ACEE0[D_800AD5F0[i]].y;
            self->velocityY = D_800AD558[paramsLo];
            self->rotY = self->rotX = D_800AD570[paramsLo] + 0x20;
            self->step++;
            return;
        }
        if (paramsHi == 1) {
            if (g_Player.pl_vram_flag & 0x8000) {
                posX /= 2;
            }
        }
        if (paramsHi == 6) {
            if (PLAYER.velocityX > 0) {
                posX = -posX;
            }
        } else {
            if (self->facingLeft) {
                posX = -posX;
            }
        }
        self->posX.i.hi += posX;
        self->posY.i.hi += 0x18;
        self->rotX = D_800AD570[paramsLo] + 0x40;
        self->velocityY = D_800AD558[paramsLo];
        if (paramsHi == 1) {
            self->velocityY = FIX(-0.25);
            SetSpeedX(-0x3000);
            self->rotX = D_800AD570[1] + 0x40;
        }
        if (paramsHi == 5) {
            self->velocityY = D_800AD558[4 - paramsLo * 2];
        }
        self->rotY = self->rotX;
        if (paramsHi == 10) {
            self->posY.i.hi -= 6;
        }
        self->step++;
        return;
    case 1:
        self->posY.val += self->velocityY;
        self->posX.val += self->velocityX;
        if (self->animFrameDuration < 0) {
            DestroyEntity(self);
            return;
        }
        break;
    }
}

void EntityUnkId24(Entity* self) {
    u16 upperparams = self->params >> 8;
    if (self->step == 0) {
        self->animSet = 2;
        self->anim = D_800AD5FC;

        // Weird thing here where we have to set flags to the same value twice
        self->flags = FLAG_UNK_08000000 | FLAG_UNK_100000;
        self->zPriority = PLAYER.zPriority + 2;
        self->flags = FLAG_UNK_08000000 | FLAG_UNK_100000;

        self->velocityY = FIX(-1);
        if (upperparams == 0) {
            self->posX.i.hi -= 32 - (rand() & 63);
            self->posY.i.hi -= 48 - (rand() & 63);
            self->drawMode = DRAW_TPAGE;
            self->palette = 0x8195;
        } else {
            self->posY.i.hi -= 12 - rand() % 24;
            self->drawFlags = FLAG_DRAW_ROTY | FLAG_DRAW_ROTX;
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
void EntityPlayerBlinkWhite(Entity* self) {
    Primitive* prim;
    u8 var_s7;
    u8 var_s6;
    u8 sp7f;
    u8 sp7e;
    s16 sp7c;
    s16 sp7a;
    s16 var_s2;
    s16 var_s5;
    s16 sp78;
    s16 sp76;
    s16 sp74;
    s16 sp72;
    s16 var_s3;
    s16 var_s8;
    s32 sp54;
    s32 sp50;
    s16 sp70;
    s16* sp4c;
    s16 sp6e;
    s16 sp6c;
    s16 sp6a;
    s16 sp68;
    s16 sp66;
    s16 sp64;
    s16 sp62;
    s16 sp60;
    s16* sp5c;
    u8* sp58;
    s32 sp48;
    s32 sp44;
    s32 sp40;
    Entity* sp3C;
    s32 sp38;
    s32 var_s1;

    sp70 = (self->params & 0x7F00) >> 8;
    sp48 = 0;
    if ((PLAYER.animSet == 0xF) && (sp70 == 0x23) && g_Player.unk66 < 2) {
        sp48 = 1;
    }
    if ((((sp70 & 0x3F) != 0x1D) &&
         (g_Player.unk0C & PLAYER_STATUS_MIST_FORM)) ||
        (g_Player.unk0C & PLAYER_STATUS_AXEARMOR)) {
        goto block_229;
    }
    if ((g_Player.unk6C) && sp70 != 0x20 && sp70 != 0x21 &&
        ((sp70 & 0x3F) != 0x1D)) {
        g_Player.unk6E = 0;
        goto block_231;
    }
    if ((g_Player.unk6E) && sp70 != 0x23 && sp70 != 0x24 &&
        ((sp70 & 0x3F) != 0x1D)) {
        g_Player.unk6C = 0;
        goto block_231;
    }
    if (((PLAYER.step == Player_SpellHellfire) && (PLAYER.palette == 0x810D)) ||
        (!PLAYER.animSet) || !(PLAYER.animCurFrame & 0x7FFF)) {
        goto block_229;
    }
    var_s8 = self->posY.i.hi = PLAYER.posY.i.hi;
    var_s3 = self->posX.i.hi = PLAYER.posX.i.hi;
    self->facingLeft = PLAYER.facingLeft;
    if (PLAYER.animSet == 1) {
        sp5c = D_800CF324[PLAYER.animCurFrame & 0x7FFF];
    }
    if (PLAYER.animSet == 0xD) {
        sp5c = D_800CFE48[PLAYER.animCurFrame & 0x7FFF];
    }
    if (PLAYER.animSet == 0xF) {
        if (sp48 != 0) {
            if (D_801396E0 == 0xD) {
                sp5c = D_800CFE48[D_801396EC & 0x7FFF];
#ifdef VER_PSP
                if (sp5c) {
#endif
                    sp72 = *sp5c++;
                    sp72 &= 0x7FFF;
                    sp58 = (*g_PlOvlAluBatSpritesheet)[sp72];
#ifdef VER_PSP
                } else {
                    sp58 = 0;
                }
#endif
            } else {
                sp5c = D_800CF324[D_801396EC & 0x7FFF];
#ifdef VER_PSP
                if (sp5c) {
#endif
                    sp72 = *sp5c++;
                    sp72 &= 0x7FFF;
                    sp58 = ((u8**)SPRITESHEET_PTR)[sp72];
#ifdef VER_PSP
                } else {
                    sp58 = 0;
                }
#endif
            }
        } else {
            sp7c = 0x2C;
            if (PLAYER.facingLeft) {
                sp7c = 0x14;
            }
            var_s7 = sp7c + D_8013AEBC[2];
            sp7f = sp7c + D_8013AEBC[0];
            var_s6 = D_8013AEBC[3] - 40;
            sp7e = D_8013AEBC[3] + 24;
            var_s2 = D_8013AEBC[0] - D_8013AEBC[2];
            var_s5 = D_8013AEBC[1] - D_8013AEBC[3];
            sp7c = D_8013AEBC[2];
            sp7a = D_8013AEBC[3];
            self->facingLeft = 0;
            self->drawFlags = 0;
            goto block_748;
        }
    } else {
        sp72 = *sp5c++;
        sp72 &= 0x7FFF;
        if (PLAYER.animSet == 1) {
            sp58 = ((u8**)SPRITESHEET_PTR)[sp72];
        }
        if (PLAYER.animSet == 0xD) {
            sp58 = (*g_PlOvlAluBatSpritesheet)[sp72];
        }
    }
#ifdef VER_PSP
    if (sp58) {
#endif
        var_s7 = 4;
        var_s6 = 1;
        sp7f = var_s7 + sp58[0];
        sp7e = var_s6 + sp58[1];
        var_s2 = sp7f - var_s7;
        var_s5 = sp7e - var_s6;
        sp7c = sp5c[0] + sp58[2];
        sp7a = sp5c[1] + sp58[3];
#ifdef VER_PSP

    } else {
        var_s7 = 4 & 0xFF;
        var_s6 = 1 & 0xFF;
        sp7f = var_s7 & 0xFF;
        sp7e = var_s6 & 0xFF;
        var_s2 = sp7f - var_s7;
        var_s5 = sp7e - var_s6;
        sp7c = 0;
        sp7a = 0;
    }
#endif

    self->rotZ = PLAYER.rotZ;
    self->drawFlags = PLAYER.drawFlags;
    self->rotX = PLAYER.rotX;
    self->rotY = PLAYER.rotY;
    self->rotPivotY = PLAYER.rotPivotY;
    self->rotPivotX = PLAYER.rotPivotX;
block_748:
    sp4c = D_800AD670[sp70 & 0x3F];
    switch (self->step) {
    case 0:
        if (func_8011BD48(self) != 0) {
            goto block_231;
        }
        self->primIndex = AllocPrimitives(PRIM_GT4, 8);
        if (self->primIndex == -1) {
#ifdef VERSION_HD
            DestroyEntity(self);
#endif
            return;
        }
        self->flags = FLAG_UNK_04000000 | FLAG_HAS_PRIMS | FLAG_UNK_40000 |
                      FLAG_UNK_20000 | FLAG_UNK_10000;
        prim = &g_PrimBuf[self->primIndex];
        for (var_s1 = 0; var_s1 < 8; var_s1++) {
            D_800AD630[var_s1] = var_s1 << 9;
            prim->clut = sp4c[3];
            prim->r0 = prim->b0 = prim->g0 = prim->r1 = prim->b1 = prim->g1 =
                prim->r2 = prim->b2 = prim->g2 = prim->r3 = prim->b3 =
                    prim->g3 = 0x80;
            prim->priority = PLAYER.zPriority + 2;
            if (sp70 == 0x20 || sp70 == 0x21 || sp70 == 0x23 || sp70 == 0x24) {
                prim->priority = PLAYER.zPriority + 4;
            }
            prim->drawMode =
                sp4c[8] + DRAW_UNK_200 + DRAW_UNK_100 + DRAW_COLORS;
            prim = prim->next;
        }
        self->ext.playerBlink.unk8A = sp4c[9];
        self->ext.playerBlink.unk90 = 0;
        self->ext.playerBlink.unk98 = 0;
        self->ext.playerBlink.unk9A = 0x100;
        self->step += 1;
        if (sp70 == 0x20) {
            self->step = 8;
        }
        if (sp70 == 0x21) {
            self->step = 0xA;
        }
        if (sp70 == 0x23) {
            self->step = 0xC;
        }
        if (sp70 == 0x24) {
            self->step = 0xE;
        }
        if (sp70 == 0x26) {
            self->step = 0x10;
        }
        if (sp70 == 0x29) {
            self->ext.playerBlink.unk90 = 0xFF;
            self->step = 0x13;
        }
        break;
    case 1:
        if (sp4c[7] == 0x7008) {
            self->ext.playerBlink.unk90 += 0x50;
        } else {
            self->ext.playerBlink.unk90 += 0xA;
        }
        if (self->ext.playerBlink.unk90 >= 0x101) {
            self->ext.playerBlink.unk90 = 0x100;
            self->ext.playerBlink.unk80 = sp4c[7];
            self->step += 1;
        }
        break;
    case 2:
        if (sp4c[7] >= 0x7000) {
            self->ext.playerBlink.unk80 = 8;
            switch ((u32)sp4c[7]) {
            case 0x7000:
                if (g_Player.D_80072F00[1] == 0) {
                    self->step += 1;
                }
                break;
            case 0x7001:
            case 0x7007:
                if (PLAYER.step != Player_Hit) {
                    self->step += 1;
                }
                break;
            case 0x7002:
                sp40 = g_Player.D_80072F00[0];
                if (sp40 == 0) {
                    self->step += 1;
                }
                self->ext.playerBlink.unk90 = ((sp40 * 192) / 4095) + 0x10;
                break;
            case 0x7003:
                sp38 = 0;
                sp3C = &g_Entities[32];
                for (var_s1 = 0; var_s1 < 16; var_s1++) {
                    if (sp3C->entityId == 0x11) {
                        sp38 += 1;
                    }
                    sp3C++;
                }
                if (sp38 == 0) {
                    self->ext.playerBlink.unk80 = 0x14;
                    self->step += 1;
                }
                break;
            case 0x7004:
                if (D_80097448[1] == 0 ||
                    IsRelicActive(RELIC_HOLY_SYMBOL) != 0) {
                    self->step += 1;
                }
                break;
            case 0x7005:
            case 0x7006:
                if (PLAYER.ext.player.anim != 0xC0) {
                    self->step += 1;
                }
                break;
            case 0x7008:
                if ((g_Player.unk0C & PLAYER_STATUS_UNK400000) == 0) {
                    self->step += 1;
                }
                break;
            case 0x7009: // Hold this step until player is out of state (5,3)
                // This state corresponds to wing smashing.
                if (PLAYER.step_s != 3 || PLAYER.step != Player_MorphBat) {
                    self->step += 1;
                }
                /* fallthrough */
            case 0x700B:
                if ((g_Player.unk0C & PLAYER_STATUS_UNK40000000) == 0) {
                    self->step += 1;
                }
                break;
            }
        }
        if (--self->ext.playerBlink.unk80 == 0) {
            self->step += 1;
        }
        break;
    case 3:
        self->ext.playerBlink.unk90 -= 10;
        if (self->ext.playerBlink.unk90 < 0) {
            goto block_231;
        }
        break;
    case 8:
        g_Player.unk6C = 1;
        self->ext.playerBlink.unk9C += 0x100;
        if (PLAYER.animSet == 0xF) {
            sp62 = 0x100;
            sp60 = 0x10;
        } else {
            sp62 = 0x80;
            sp60 = 8;
        }
        self->ext.playerBlink.unk98 += sp60;
        if (self->ext.playerBlink.unk98 > sp62) {
            self->ext.playerBlink.unk98 = sp62;
            g_Player.unk66 = 2;
            self->step += 1;
        }
        break;
    case 9:
    case 11:
        self->ext.playerBlink.unk98 -= 8;
        self->ext.playerBlink.unk9C += 0x100;
        if (self->ext.playerBlink.unk98 < 0) {
            g_Player.unk66 = 3;
            self->params = 0x1B00;
            self->step = 1;
            prim = &g_PrimBuf[self->primIndex];
            for (var_s1 = 0; var_s1 < 8; var_s1++) {
                prim->clut = 0x15F;
                prim = prim->next;
            }
            g_Player.unk6C = 0;
            return;
        }
        break;
    case 10:
        g_Player.unk6C = 1;
        self->ext.playerBlink.unk98 += 8;
        self->ext.playerBlink.unk9C += 0x100;
        if (self->ext.playerBlink.unk98 > 0x80) {
            self->ext.playerBlink.unk98 = 0x80;
        }
        if (g_Player.unk66 == 1) {
            self->step += 1;
        }
        break;
    case 12:
        g_Player.unk6E = 1;
        self->ext.playerBlink.unk9C += 0x100;
        self->ext.playerBlink.unk98 += 0x10;
        if (self->ext.playerBlink.unk98 > 0x100) {
            self->ext.playerBlink.unk98 = 0x100;
            g_Player.unk66 = 2;
            self->step += 1;
        }
        break;
    case 13:
        self->ext.playerBlink.unk98 -= 8;
        self->ext.playerBlink.unk9C += 0x100;
        if (self->ext.playerBlink.unk98 < 0) {
            g_Player.unk66 = 3;
            self->params = 0x2500;
            self->step = 1;
            g_Player.unk6E = 0;
            return;
        }
        break;
    case 14:
        g_Player.unk6E = 1;
        self->ext.playerBlink.unk98 += 0x10;
        self->ext.playerBlink.unk9C += 0x100;
        if (self->ext.playerBlink.unk98 > 0x100) {
            self->ext.playerBlink.unk98 = 0x100;
        }
        if (g_Player.unk66 == 1) {
            self->step += 1;
        }
        break;
    case 15:
        self->ext.playerBlink.unk98 -= 8;
        self->ext.playerBlink.unk9C += 0x100;
        if (self->ext.playerBlink.unk98 < 0) {
            g_Player.unk66 = 3;
            self->params = 0x1B00;
            self->step = 1;
            prim = &g_PrimBuf[self->primIndex];
            for (var_s1 = 0; var_s1 < 8; var_s1++) {
                prim->clut = 0x15F;
                prim = prim->next;
            }
            g_Player.unk6E = 0;
            return;
        }
        break;
    case 17:
        self->ext.playerBlink.unk98 += 4;
        self->ext.playerBlink.unk9C += 0x100;
        if (self->ext.playerBlink.unk98 > 0x60) {
            self->step += 1;
        }
        break;
    case 19:
        self->ext.playerBlink.unk90 -= 2;
        if (self->ext.playerBlink.unk90 < 0) {
            DestroyEntity(self);
            return;
        }
        break;
    }
    sp44 = 0;
    if (sp70 == 0x20 || sp70 == 0x21 || sp70 == 0x23 || sp70 == 0x24 ||
        sp70 == 0x26) {
        sp44 = 1;
    }
    sp78 = self->ext.playerBlink.unk9C;
    sp76 = self->ext.playerBlink.unk98;
    sp54 = 3;
    sp50 = 6;
    if (sp4c[7] == 0x700A) {
        sp50 = 0;
        sp54 = 0;
    }
    self->ext.playerBlink.unk82 += self->ext.playerBlink.unk8A;
    if (self->facingLeft) {
        var_s3 = var_s3 - sp7c;
    } else {
        var_s3 = var_s3 + sp7c;
    }
    var_s8 = var_s8 + sp7a;
    prim = &g_PrimBuf[self->primIndex];
    for (var_s1 = 0; var_s1 < 8; var_s1++) {
        if (PLAYER.animSet == 0xF && sp48 == 0) {
            prim->tpage = 0x118;
        } else {
            prim->tpage = 0x18;
        }
        if (sp70 & 0x40) {
            switch (var_s1) {
            case 0:
                if (self->facingLeft) {
                    prim->x1 = var_s3 - var_s2 / 2;
                } else {
                    prim->x1 = var_s3 + var_s2 / 2;
                }
                prim->x0 = var_s3;
                prim->u0 = var_s7;
                prim->u1 = var_s7 + var_s2 / 2;
                prim->y1 = var_s8;
                prim->y0 = var_s8;
                prim->v1 = var_s6;
                prim->v0 = var_s6;
                break;
            case 1:
                if (self->facingLeft) {
                    prim->x0 = var_s3 - var_s2 / 2;
                    prim->x1 = var_s3 - var_s2;
                } else {
                    prim->x0 = var_s3 + var_s2 / 2;
                    prim->x1 = var_s3 + var_s2;
                }
                prim->u0 = var_s7 + var_s2 / 2;
                prim->u1 = var_s7 + var_s2;
                prim->y1 = var_s8;
                prim->y0 = var_s8;
                prim->v1 = var_s6;
                prim->v0 = var_s6;
                break;
            case 2:
                if (self->facingLeft) {
                    prim->x0 = prim->x1 = var_s3 - var_s2;
                } else {
                    prim->x0 = prim->x1 = var_s3 + var_s2;
                }
                prim->u0 = prim->u1 = var_s7 + var_s2;
                prim->y0 = var_s8;
                prim->y1 = var_s8 + var_s5 / 2;
                prim->v0 = var_s6;
                prim->v1 = var_s6 + var_s5 / 2;
                break;
            case 3:
                if (self->facingLeft) {
                    prim->x0 = prim->x1 = var_s3 - var_s2;
                } else {
                    prim->x0 = prim->x1 = var_s3 + var_s2;
                }

                prim->u0 = prim->u1 = var_s7 + var_s2;
                prim->y0 = var_s8 + var_s5 / 2;
                prim->y1 = var_s8 + var_s5;
                prim->v0 = var_s6 + var_s5 / 2;
                prim->v1 = var_s6 + var_s5;
                break;
            case 4:
                if (self->facingLeft) {
                    prim->x0 = var_s3 - var_s2;
                    prim->x1 = var_s3 - var_s2 / 2;
                } else {
                    prim->x0 = var_s3 + var_s2;
                    prim->x1 = var_s3 + var_s2 / 2;
                }
                prim->u0 = var_s7 + var_s2;
                prim->u1 = var_s7 + var_s2 / 2;
                prim->y0 = prim->y1 = var_s8 + var_s5;
                prim->v0 = prim->v1 = var_s6 + var_s5;
                break;
            case 5:
                if (self->facingLeft) {
                    prim->x0 = var_s3 - var_s2 / 2;
                } else {
                    prim->x0 = var_s3 + var_s2 / 2;
                }
                prim->x1 = var_s3;
                prim->u0 = var_s7 + var_s2 / 2;
                prim->u1 = var_s7;
                prim->y0 = prim->y1 = var_s8 + var_s5;
                prim->v0 = prim->v1 = var_s6 + var_s5;

                break;
            case 6:
                prim->x1 = var_s3;
                prim->x0 = var_s3;
                prim->u1 = var_s7;
                prim->u0 = var_s7;
                prim->y0 = var_s8 + var_s5;
                prim->y1 = var_s8 + var_s5 / 2;
                prim->v0 = var_s6 + var_s5;
                prim->v1 = var_s6 + var_s5 / 2;
                break;
            case 7:
                prim->x1 = var_s3;
                prim->x0 = var_s3;
                prim->u1 = var_s7;
                prim->u0 = var_s7;
                prim->y0 = var_s8 + var_s5 / 2;
                prim->y1 = var_s8;
                prim->v0 = var_s6 + var_s5 / 2;
                prim->v1 = var_s6;
                break;
            }
            if (self->facingLeft) {
                prim->x2 = prim->x3 =
                    var_s3 - var_s2 / 2 +
                    ((rcos(self->ext.playerBlink.unk82) >> 4) * sp54 >> 0xC);
            } else {
                prim->x2 = prim->x3 =
                    var_s3 + var_s2 / 2 +
                    ((rcos(self->ext.playerBlink.unk82) >> 4) * sp54 >> 0xC);
            }
            prim->y2 = prim->y3 =
                (var_s8 + var_s5 / 2) -
                ((rsin(self->ext.playerBlink.unk82) >> 4) * sp50 >> 8);
            prim->u2 = prim->u3 = var_s7 + var_s2 / 2;
            prim->v2 = prim->v3 = var_s6 + var_s5 / 2;
        } else {
            if (self->facingLeft) {
                prim->x0 = prim->x2 = (var_s3 - var_s2) + 1;
                prim->x1 = prim->x3 = var_s3 + 1;
            } else {
                prim->x2 = var_s3;
                prim->x0 = var_s3;
                prim->x1 = prim->x3 = var_s3 + var_s2;
            }
            if (sp44 != 0) {
                sp74 = (rsin(sp78) >> 7) * sp76 / 256;
                prim->x0 += sp74;
                prim->x1 += sp74;
                sp78 += 0x600;
                sp74 = (rsin(sp78) >> 7) * sp76 / 256;
                prim->x2 += sp74;
                prim->x3 += sp74;
            }
            prim->y0 = prim->y1 = var_s8 + var_s5 * var_s1 / 8;
            prim->y2 = prim->y3 = var_s8 + var_s5 * (var_s1 + 1) / 8;
            if (self->facingLeft) {
                prim->u0 = prim->u2 = sp7f - 1;
                prim->u1 = prim->u3 = var_s7 - 1;
            } else {
                prim->u0 = prim->u2 = var_s7;
                prim->u1 = prim->u3 = sp7f;
            }
            prim->v0 = prim->v1 = var_s6 + var_s5 * var_s1 / 8;
            prim->v2 = prim->v3 = var_s6 + var_s5 * (var_s1 + 1) / 8;
        }
        if (self->drawFlags &
            (FLAG_DRAW_ROTX | FLAG_DRAW_ROTY | FLAG_DRAW_ROTZ)) {
            func_800EB758(self->posX.i.hi, self->posY.i.hi, self,
                          self->drawFlags, prim, self->facingLeft);
        }
        if (sp44 == 0) {
            if (sp70 == 0x29) {
                prim->r0 = prim->b0 = prim->g0 = prim->r1 = prim->b1 =
                    prim->g1 = prim->r2 = prim->b2 = prim->g2 = prim->r3 =
                        prim->b3 = prim->g3 = self->ext.playerBlink.unk90;
            } else {
                sp6e = sp4c[0];
                sp6c = sp4c[2];
                sp6a = sp4c[1];
                sp68 = sp4c[4];
                sp64 = sp4c[6];
                sp66 = sp4c[5];
                // clang-format off
                if (sp70 & 0x40) {
                    prim->r0 = (((rsin((s16)D_800AD630[(var_s1 + sp6e) % 8]) + 0x1000) >> 6) * self->ext.playerBlink.unk90 / sp68);
                    prim->g0 = (((rsin((s16)D_800AD630[(var_s1 + sp6c) % 8]) + 0x1000) >> 6) * self->ext.playerBlink.unk90 / sp64);
                    prim->b0 = (((rsin((s16)D_800AD630[(var_s1 + sp6a) % 8]) + 0x1000) >> 6) * self->ext.playerBlink.unk90 / sp66);
                    prim->r1 = (((rsin((s16)D_800AD630[(var_s1 + sp6e + 1) % 8]) + 0x1000) >> 6) * self->ext.playerBlink.unk90 / sp68);
                    prim->g1 = (((rsin((s16)D_800AD630[(var_s1 + sp6c + 1) % 8]) + 0x1000) >> 6) * self->ext.playerBlink.unk90 / sp64);
                    prim->b1 = (((rsin((s16)D_800AD630[(var_s1 + sp6a + 1) % 8]) + 0x1000) >> 6) * self->ext.playerBlink.unk90 / sp66);
                    prim->r2 = prim->g2 = prim->b2 = prim->r3 = prim->g3 = prim->b3 = 0;
                    D_800AD630[var_s1] += self->ext.playerBlink.unk8A;
                } else {
                    prim->r0 = prim->r1 =(((rsin((s16)D_800AD630[(var_s1 + sp6e) % 8]) + 0x1000) >> 6) * self->ext.playerBlink.unk90 / sp68);
                    prim->g0 = prim->g1 =(((rsin((s16)D_800AD630[(var_s1 + sp6c) % 8]) + 0x1000) >> 6) * self->ext.playerBlink.unk90 / sp64);
                    prim->b0 = prim->b1 =(((rsin((s16)D_800AD630[(var_s1 + sp6a) % 8]) + 0x1000) >> 6) * self->ext.playerBlink.unk90 / sp66);
                    prim->r2 = prim->r3 =(((rsin((s16)D_800AD630[(var_s1 + sp6e + 1) % 8]) + 0x1000) >> 6) * self->ext.playerBlink.unk90 / sp68);
                    prim->g2 = prim->g3 =(((rsin((s16)D_800AD630[(var_s1 + sp6c + 1) % 8]) + 0x1000) >> 6) * self->ext.playerBlink.unk90 / sp64);
                    prim->b2 = prim->b3 =(((rsin((s16)D_800AD630[(var_s1 + sp6a + 1) % 8]) + 0x1000) >> 6) * self->ext.playerBlink.unk90 / sp66);
                    D_800AD630[var_s1] += self->ext.playerBlink.unk8A;
                }
                // clang-format on
            }
        }
        prim = prim->next;
    }
    func_8010DFF0(1, 1);
    if (((sp70 & 0x3F) == 0) || ((sp70 & 0x3F) == 7)) {
        func_8010E168(1, 0xA);
    }
    return;

block_229:
    g_Player.unk6C = g_Player.unk6E = 0;
block_231:
    DestroyEntity(self);
}

// Draws an outline around the player which grows or shrinks.
// Outline can be several colors depending on the blueprint used.
// Entity #31. Blueprints: 40, 57, 61
// Many use cases. Known examples:
// MP Refilled, blueprint 40, upperparams = 0
// Cursed and trying to attack, blueprint 57, upperparams = 1
// Agunea subweapon, blueprint 61, upperparams = 2
// Dark Metamorphosis, blueprint 40, upperparams = 17
// Sword warp spell, blueprint 61, upperparams = 20
// Sword warp spell, blueprint 61, upperparams = 21
// Soul steal, blueprint 40, upperparams = 22
// Sword Brothers, blueprint 40, upperparams = 23

void EntityPlayerOutline(Entity* self) {
    s16* animFramePtr;
    u8* spritesheetPtr;
    s16 xOffset;
    s16 yOffset;
    s16 width;
    Primitive* prim;
    s16 spriteIdx;
    s32 i;
    s16 upperparams;
    u8 spriteX;
    s16* primData;
    s16 xVar;
    s16 yVar;
    u8 four;
    u8 one;
    s16 height;
    u8 spriteY;
    s16 selfX;
    s16 selfY;

    if ((g_Player.unk0C & (PLAYER_STATUS_AXEARMOR | PLAYER_STATUS_UNK40000 |
                           PLAYER_STATUS_STONE | PLAYER_STATUS_TRANSFORM)) ||
        !(PLAYER.animCurFrame & 0x7FFF) || (!PLAYER.animSet) ||
        ((PLAYER.step == Player_SpellHellfire) && (PLAYER.palette == 0x810D))) {
        DestroyEntity(self);
        return;
    }
    upperparams = (self->params & 0x7F00) >> 8;
    self->posX.i.hi = PLAYER.posX.i.hi;
    self->posY.i.hi = PLAYER.posY.i.hi;
    self->facingLeft = PLAYER.facingLeft;
    animFramePtr = D_800CF324[PLAYER.animCurFrame & 0x7FFF];
    spriteIdx = *animFramePtr++;
    spriteIdx &= 0x7FFF;
    selfX = self->posX.i.hi;
    selfY = self->posY.i.hi;
    spritesheetPtr = ((u8**)SPRITESHEET_PTR)[spriteIdx];
    four = 4;
    one = 1;
    spriteX = four + spritesheetPtr[0];
    spriteY = one + spritesheetPtr[1];
    width = spriteX - four;
    height = spriteY - one;
    xOffset = *animFramePtr++ + spritesheetPtr[2];
    yOffset = *animFramePtr++ + spritesheetPtr[3];
    self->rotZ = PLAYER.rotZ;
    self->drawFlags |= (FLAG_DRAW_ROTX | FLAG_DRAW_ROTY);
    primData = D_800AD9B8[upperparams];
    switch (self->step) {
    case 0: // Initialization
        self->primIndex = AllocPrimitives(PRIM_GT4, 1);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags = FLAG_UNK_04000000 | FLAG_HAS_PRIMS | FLAG_UNK_40000 |
                      FLAG_UNK_20000 | FLAG_UNK_10000;
        prim = &g_PrimBuf[self->primIndex];
        // This is just not a for-loop, that's weird
        for (i = 0; i < 1; i++) {
            prim->tpage = 0x18;
            prim->clut = primData[3]; // Always 259
            prim->priority = PLAYER.zPriority + 2;
            // primData[4] is always 49; DRAW_UNK_40 | DRAW_HIDE | DRAW_TRANSP
            prim->drawMode =
                primData[4] + (DRAW_UNK_200 | DRAW_UNK_100 | DRAW_COLORS);
            prim = prim->next;
        }
        switch (upperparams) {
        case 0: // MP refill
        case 8:
        case 9:
        case 10:
        case 11:
        case 12:
        case 13:
        case 17: // Dark Metamorphosis
        case 18:
        case 20: // Sword Warp Spell (#1)
        case 22: // Soul Steal
        case 23: // Sword Brothers
            self->ext.playerOutline.brightness = 0x80;
            self->rotX = PLAYER.rotX; // Player rotX is (always?) 0x100
            self->rotY = PLAYER.rotY; // Player rotY is (always?) 0x100
            self->rotPivotY = PLAYER.rotPivotY;
            self->rotPivotX = PLAYER.rotPivotX;
            self->ext.playerOutline.timer = 8;
            break;
        case 2: // Agunea
            self->ext.playerOutline.brightness = 0xC0;
            self->rotX = PLAYER.rotX; // Player rotX is (always?) 0x100
            self->rotY = PLAYER.rotY; // Player rotY is (always?) 0x100
            self->rotPivotY = PLAYER.rotPivotY;
            self->rotPivotX = PLAYER.rotPivotX;
            self->ext.playerOutline.timer = 8;
            break;
        case 1: // Curse attack
            self->ext.playerOutline.brightness = 0x100;
            self->rotX = PLAYER.rotX; // Player rotX is (always?) 0x100
            self->rotY = PLAYER.rotY; // Player rotY is (always?) 0x100
            self->rotPivotY = PLAYER.rotPivotY;
            self->rotPivotX = PLAYER.rotPivotX;
            self->ext.playerOutline.timer = 8;
            break;
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 14:
        case 15:
        case 16:
        case 19:
        case 21: // Sword Warp Spell (#2)
            self->ext.playerOutline.brightness = 0x80;
            self->rotX = PLAYER.rotX + 0x60;
            self->rotY = PLAYER.rotY + 0x60;
            self->rotPivotY = PLAYER.rotPivotY;
            self->rotPivotX = PLAYER.rotPivotX;
            self->ext.playerOutline.timer = 8;
            break;
        }
        self->step++;
        break;

    case 1: // 8 frames at constant size
        switch (upperparams) {
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 14:
        case 15:
        case 16:
        case 18:
        case 21: // Sword Warp Spell (#2)
            self->ext.playerOutline.brightness += 16;
        case 0: // MP refill
        case 1: // Curse attack
        case 2: // Agunea
        case 8:
        case 9:
        case 10:
        case 11:
        case 12:
        case 13:
        case 17: // Dark Metamorphosis
        case 19:
        case 20: // Sword Warp Spell (#1)
        case 22: // Soul Steal
        case 23: // Sword Brothers
            if (--self->ext.playerOutline.timer == 0) {
                self->step++;
            }
        }
        break;
    case 2: // Outline grows/shrinks, and dims
        switch (upperparams) {
        case 0: // MP refill
        case 2: // Agunea
        case 8:
        case 9:
        case 10:
        case 11:
        case 12:
        case 13:
        case 15:
        case 16:
        case 17: // Dark Metamorphosis
        case 18:
        case 20: // Sword Warp Spell (#1)
        case 22: // Soul Steal
        case 23: // Sword Brothers
            self->rotX += 8;
            self->rotY += 8;
            self->ext.playerOutline.brightness -= 5;
            if (self->ext.playerOutline.brightness < 0) {
                DestroyEntity(self);
                return;
            }
            break;
        case 1: // Curse attack, grows slower and dims faster
            self->rotX += 2;
            self->rotY += 2;
            self->ext.playerOutline.brightness -= 16;
            if (self->ext.playerOutline.brightness < 0) {
                DestroyEntity(self);
                return;
            }
            break;
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 14:
        case 19:
        case 21: // Sword Warp Spell (#2)
            // Shrinks inward, and when at size 0x100, holds there for 8 frames
            // in step 3
            self->rotX -= 8;
            self->rotY -= 8;
            if (self->rotX <= 0x100) {
                self->rotY = self->rotX = 0x100;
                self->ext.playerOutline.timer = 8;
                self->step++;
            }
        }
        break;
    case 3: // Outline continues static until done
        if (--self->ext.playerOutline.timer == 0) {
            DestroyEntity(self);
            return;
        }
        break;
    }
    if (self->facingLeft) {
        selfX = selfX - xOffset;
    } else {
        selfX = selfX + xOffset;
    }
    selfY = selfY + yOffset;
    prim = &g_PrimBuf[self->primIndex];
    for (i = 0; i <= 0; i++) {
        if (self->facingLeft) {
            prim->x0 = prim->x2 = (selfX - width) + 1;
            prim->x1 = prim->x3 = selfX + 1;
        } else {
            prim->x0 = prim->x2 = selfX;
            prim->x1 = prim->x3 = selfX + width;
        }

        prim->y0 = prim->y1 = selfY;
        prim->y2 = prim->y3 = selfY + height;
        if (self->facingLeft) {
            prim->u0 = prim->u2 = spriteX - 1;
            prim->u1 = prim->u3 = four - 1;
        } else {
            prim->u0 = prim->u2 = four;
            prim->u1 = prim->u3 = spriteX;
        }
        prim->v0 = prim->v1 = one;
        prim->v2 = prim->v3 = one + height;
        func_800EB758(self->posX.i.hi, self->posY.i.hi, self, self->drawFlags,
                      prim, (u16)self->facingLeft);
        prim->r0 = prim->r1 = prim->r2 = prim->r3 =
            primData[0] * self->ext.playerOutline.brightness / 256;
        prim->g0 = prim->g1 = prim->g2 = prim->g3 =
            primData[1] * self->ext.playerOutline.brightness / 256;
        prim->b0 = prim->b1 = prim->b2 = prim->b3 =
            primData[2] * self->ext.playerOutline.brightness / 256;
        prim->priority = PLAYER.zPriority + 2;
        prim = prim->next;
    }
    func_8010DFF0(1, 1);
}

void func_8011E0E4(Entity* entity) {}

void EntityGravityBootBeam(Entity* self) {
    Primitive* prim;
    s16 halfWidth;
    s32 i;
    s32 yOffset = -12;

    switch (self->step) {
    case 0:
        self->posY.i.hi = PLAYER.posY.i.hi + 37;
        self->ext.timer.t = 1536;
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
            prim->drawMode =
                DRAW_UNK_400 | DRAW_UNK_100 | DRAW_TPAGE2 | DRAW_TPAGE |
                DRAW_COLORS | DRAW_UNK02 | DRAW_TRANSP;
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
        self->ext.timer.t -= 160;
    case 2:
        self->ext.timer.t -= 96;
        if (self->ext.timer.t < 0) {
            DestroyEntity(self);
            return;
        }
        break;
    }
    for (i = 0, prim = &g_PrimBuf[self->primIndex]; prim != NULL; i++,
        prim = prim->next) {
        // As timer counts down, beam gets narrower.
        halfWidth = (self->ext.timer.t >> 8) - i;
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
        entity->animCurFrame = PLAYER.animCurFrame | ANIM_FRAME_LOAD;
        entity->zPriority = PLAYER.zPriority - 2;
        entity->drawFlags = PLAYER.drawFlags |
                            (FLAG_DRAW_UNK8 | FLAG_DRAW_ROTY | FLAG_DRAW_ROTX);
        entity->unk6C = 0x80; // a lifetime counter
        entity->drawMode = DRAW_TPAGE2 | DRAW_TPAGE;
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
    entity->animCurFrame = PLAYER.animCurFrame | ANIM_FRAME_LOAD;
    // Unclear why we count down by 5's instead of just making unk6C start
    // smaller
    if (entity->unk6C >= 5) {
        entity->unk6C -= 5;
    } else {
        DestroyEntity(entity);
    }
}
