#include "dra.h"
#include "objects.h"
#include "sfx.h"

PfnEntityUpdate g_DraEntityTbl[] = {
    func_8011A4C8,
    EntityEntFactory,
    func_8011B5A4,
    EntityGravityBootBeam,
    EntitySubwpnThrownDagger,
    func_8011E4BC,
    func_8011B334,
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
    EntityMpReplenished,
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

// Corresponding RIC function is func_801603C4
void func_8011A4D0(void) {
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
                    ((PfnEntityUpdate*)FAMILIAR_PTR)[entity->entityId - 0xD0];
            } else if (entity->entityId == 0xEF || entity->entityId == 0xFF ||
                       entity->entityId == 0xED || entity->entityId == 0xFD) {
                entity->pfnUpdate = g_DraEntityTbl[1];
            } else if (entity->entityId == 0xEE || entity->entityId == 0xFE) {
                entity->pfnUpdate = g_DraEntityTbl[15];
            } else if (entity->entityId >= 0xF0) {
                // Objects F0-FC
                entity->pfnUpdate =
                    ((PfnEntityUpdate*)WEAPON1_PTR)[entity->entityId - 0xF0];
            } else {
                // Objects E0-EC
                entity->pfnUpdate =
                    ((PfnEntityUpdate*)WEAPON0_PTR)[entity->entityId - 0xE0];
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
                    ((PfnEntityUpdate*)FAMILIAR_PTR)[entity->entityId - 0xD0];
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

    if (PLAYER.ext.generic.unkAC < anim->frameStart ||
        (anim->frameStart + 7) <= PLAYER.ext.generic.unkAC ||
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
    entity->ext.generic.unkAC = PLAYER.ext.generic.unkAC - anim->frameStart;
    if ((PLAYER.animFrameDuration == 1) &&
        (PLAYER.animFrameIdx == anim->soundFrame)) {
        PlaySfx(anim->soundId);
    }
    if (UpdateUnarmedAnim(anim->frameProps, anim->frames) < 0) {
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
        self->unk4C = D_800AD57C;
        self->zPriority = PLAYER.zPriority + 2;
        self->flags = FLAG_UNK_08000000 | FLAG_UNK_100000 | FLAG_UNK_10000;
        self->palette = 0x8195;
        paramsHi = self->params >> 8;
        paramsLo = self->params & 0xFF;
        self->drawMode = DRAW_TPAGE;
        self->drawFlags = 3;

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
            self->posX.i.hi = PLAYER.posX.i.hi + D_800ACEE0[D_800AD5E0[i]].unk0;
            self->posY.i.hi = PLAYER.posY.i.hi + D_800ACEE0[D_800AD5E0[i]].unk2;
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
            self->posX.i.hi = PLAYER.posX.i.hi + D_800ACEE0[D_800AD5F0[i]].unk0;
            self->posY.i.hi = PLAYER.posY.i.hi + D_800ACEE0[D_800AD5F0[i]].unk2;
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
        self->unk4C = D_800AD5FC;

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
            prim->drawMode = 0x537;
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
        entity->animCurFrame = PLAYER.animCurFrame | 0x8000;
        entity->zPriority = PLAYER.zPriority - 2;
        entity->drawFlags = PLAYER.drawFlags | 0xB;
        entity->unk6C = 0x80; // a lifetime counter
        entity->drawMode = 0x30;
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
