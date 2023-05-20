/*
 * Overlay: NZ0
 * Boss: Slogra & Gaibon
 * Description: Low level Axe Knight
 */

#include "nz0.h"

#define BOSS_FLAG_DOORS_CLOSED (1 << 0)
#define BOSS_FLAG_DOORS_OPEN (1 << 1)
#define BOSS_FLAG_FIGHT_BEGIN (1 << 2)
#define BOSS_FLAG_GAIBON_DEAD (1 << 3)
#define BOSS_FLAG_SLOGRA_DEAD (1 << 4)

#define GAIBON self[8]

typedef enum {
    SLOGRA_INIT,
    SLOGRA_FLOOR_ALIGN,
    SLOGRA_IDLE,
    SLOGRA_TAUNT_WITH_SPEAR,
    SLOGRA_SPEAR_POKE,
    SLOGRA_SPEAR_FIRE,
    SLOGRA_ATTACK,
    SLOGRA_KNOCKBACK = 8,
    SLOGRA_WALKING_WITH_SPEAR,
    SLOGRA_TAUNT_WITHOUT_SPEAR,
    SLOGRA_WALKING_WITHOUT_SPEAR,
    SLOGRA_LOSE_SPEAR,
    SLOGRA_GAIBON_COMBO_ATTACK,
    SLOGRA_DYING = 16,
    SLOGRA_DEBUG = 255,
} SlograSteps;

typedef enum {
    SLOGRA_FIRE_FACE_PLAYER,
    SLOGRA_FIRE_PROJECTILE,
    SLOGRA_FIRE_COOLDOWN,
    SLOGRA_FIRE_END,
} SlograSpearFireSubSteps;

typedef enum {
    SLOGRA_COMBO_ATTACK_START,
    SLOGRA_COMBO_ATTACK_PLUNGE,
    SLOGRA_COMBO_ATTACK_COOLDOWN,
} SlograComboAttackSubSteps;

typedef enum {
    SLOGRA_KNOCKBACK_FLOOR_CHECK,
    SLOGRA_KNOCKBACK_ACCEL,
    SLOGRA_KNOCKBACK_ARC,
} SlograKnockbackSubSteps;

typedef enum {
    SLOGRA_DYING_START,
    SLOGRA_DYING_EXPLODING,
    SLOGRA_DYING_END,
} SlograDyingSubSteps;

// DECOMP_ME_WIP EntityCloseBossRoom https://decomp.me/scratch/bqgN9 95.04 %
// figuring out D_80181014 struct might help
// trigger to stop music and close slogra/gaibon room
INCLUDE_ASM("asm/us/st/nz0/nonmatchings/33FCC", EntityCloseBossRoom);

// blocks that move to close slogra/gaibon room
// assembler skips a nop
#ifndef NON_MATCHING
INCLUDE_ASM("asm/us/st/nz0/nonmatchings/33FCC", EntityBossRoomBlock);
#else
void EntityBossRoomBlock(Entity* self) {
    switch (self->step) {
    case 0:
        InitializeEntity(D_80180D00);
        self->animCurFrame = 8;

    case 1:
        if (g_BossFlag & 1) {
            self->ext.generic.unk80.modeS16.unk0 = 0x10;
            self->step++;
        }
        break;

    case 2:
        if (self->subId == 0) {
            self->accelerationX = 0x10000;
        } else {
            self->accelerationX = -0x10000;
        }
        MoveEntity();
        func_801BD9A0(self, 8, 8, 5);
        if (!(g_blinkTimer & 3)) {
            g_api.PlaySfx(0x608);
        }
        if (--self->ext.generic.unk80.modeS16.unk0) {
            break;
        }
        self->step++;
        break;

    case 3:
        func_801BD9A0(self, 8, 8, 5);
        if (g_BossFlag & BOSS_FLAG_DOORS_OPEN) {
            self->step++;
        }
        break;

    case 4:
        self->flags |= FLAG_DESTROY_IF_OUT_OF_CAMERA;
        if (self->subId != 0) {
            self->accelerationX = 0x10000;
        } else {
            self->accelerationX = -0x10000;
        }
        MoveEntity();
        break;
    }
}
#endif

s32 EntitySlograSpecialCollision(u16* unused) {
    /**
     * This function keeps Slogra between safe
     * boundaries of the room when the player hits him.
     * EntitySlogra passes D_8018105C to this function but it's unused
     */
    s32 ret = 0;
    s32 slograPosX;

    MoveEntity();
    g_CurrentEntity->accelerationY += 0x4000;
    slograPosX = g_CurrentEntity->posX.i.hi + g_Camera.posX.i.hi;

    if ((g_CurrentEntity->accelerationX > 0) && (slograPosX > 896)) {
        g_CurrentEntity->posX.i.hi = 896 - g_Camera.posX.i.hi;
    }

    if ((g_CurrentEntity->accelerationX < 0) && (slograPosX < 64)) {
        g_CurrentEntity->posX.i.hi = 64 - g_Camera.posX.i.hi;
    }

    if ((g_CurrentEntity->posY.i.hi + g_Camera.posY.i.hi) > 416) {
        ret = 1;
        g_CurrentEntity->posY.i.hi = 416 - g_Camera.posY.i.hi;
        g_CurrentEntity->accelerationX = 0;
        g_CurrentEntity->accelerationY = 0;
    }

    return ret;
}

// assembler skips a NOP
// matching in decomp.me https://decomp.me/scratch/vaRJR
#ifndef NON_MATCHING
INCLUDE_ASM("asm/us/st/nz0/nonmatchings/33FCC", EntitySlogra);
#else
void EntitySlogra(Entity* self) {
    Entity* newEntity;
    s32 entityOnFloor;
    u8* animation;
    s32 hitPoints;
    s8* hitbox;

    self->ext.GS_Props.pickupFlag = 0;
    
    FntPrint("beri_flag %x\n", g_BossFlag);

    if (self->step >= 3) {
        if ((self->unk48 & 3) && (self->step != SLOGRA_KNOCKBACK)) {
            SetStep(SLOGRA_KNOCKBACK);
        }
        if (self->ext.GS_Props.nearDeath == false) {
            hitPoints = g_api.enemyDefs[243].hitPoints;
            if (hitPoints < 0) {
                hitPoints += 3;
            }
            if ((self->hitPoints < (hitPoints >> 2)) && (self->step != SLOGRA_LOSE_SPEAR)) {
                SetStep(SLOGRA_LOSE_SPEAR);
            }
        }
    }
    
    if ((self->flags & 0x100) && (self->step != SLOGRA_DYING)) {
        SetStep(SLOGRA_DYING);
    }
    
    if (GAIBON.ext.GS_Props.grabedAscending) {
        if (self->step != SLOGRA_DYING) {
            if (self->step != SLOGRA_GAIBON_COMBO_ATTACK) {
                SetStep(SLOGRA_GAIBON_COMBO_ATTACK);
            }
        }
    }

    switch (self->step) {
    case SLOGRA_INIT:
        InitializeEntity(D_80180D0C);
        CreateEntityFromCurrentEntity(E_SLOGRA_SPEAR, &self[1]);
        
    case SLOGRA_FLOOR_ALIGN:
        if (EntitySlograSpecialCollision(D_8018105C) & 1) {
            SetStep(SLOGRA_IDLE);
        }
        break;

    case SLOGRA_IDLE:
        AnimateEntity(D_80181080, self);
        if (self->unk48 != 0) {
            g_BossFlag |= BOSS_FLAG_FIGHT_BEGIN;
        }
        if (g_BossFlag & BOSS_FLAG_FIGHT_BEGIN) {
            SetStep(SLOGRA_WALKING_WITH_SPEAR);
        }
        break;

    case SLOGRA_TAUNT_WITH_SPEAR:
        if (AnimateEntity(D_80181080, self) == 0) {
            SetStep(SLOGRA_WALKING_WITH_SPEAR);
        }
        break;

    case SLOGRA_WALKING_WITH_SPEAR:
        if (self->step_s == 0) {
            self->facing = (GetPlayerSide() & 1) ^ 1;
            if (self->ext.GS_Props.attackMode != 0) { // shoot projectile ?
                self->ext.GS_Props.flag = 1;
            } else {
                self->ext.GS_Props.flag = 0;
            }
            self->ext.GS_Props.timer = 128;
            self->step_s++;
        }
        AnimateEntity(D_80181074, self);
        self->facing = (GetPlayerSide() & 1) ^ 1;

        if (self->facing != self->ext.GS_Props.flag) {
            self->accelerationX = 0xC000;
        } else {
            self->accelerationX = -0xC000;
        }
        func_801BCF74(&D_8018106C);
        if (self->ext.GS_Props.flag == 0) {
            if (GetPlayerDistanceX() < 72) {
                if (self->ext.GS_Props.attackMode == 0) {
                    self->ext.GS_Props.timer = 1;
                } else {
                    self->ext.GS_Props.flag ^= 1;
                }
            }
            if (self->ext.GS_Props.flag != 0) {
                goto block_63;
            }
        } else {
        block_63:
            if (GetPlayerDistanceX() > 112) {
                if (self->ext.GS_Props.attackMode != 0) {
                    self->ext.GS_Props.timer = 1;
                } else {
                    self->ext.GS_Props.flag ^= 1;
                }
            }
        }
        if (!(Random() % 64)) {
            SetStep(SLOGRA_TAUNT_WITH_SPEAR);
        }
        if (--self->ext.GS_Props.timer == 0) {
            if (self->ext.GS_Props.attackMode != 0) {
                SetStep(SLOGRA_SPEAR_FIRE);
            } else {
                SetStep(SLOGRA_SPEAR_POKE);
            }

            self->ext.GS_Props.attackMode ^= 1;
        }
        break;

    case SLOGRA_SPEAR_POKE:
        if (self->step_s == 0) {
            func_801C29B0(NA_SE_EN_SLOGRA_HISSING);
            self->step_s++;
        }
        if (AnimateEntity(D_801810B4, self) == 0) {
            SetStep(SLOGRA_WALKING_WITH_SPEAR);
        }
        if (*(s32*)&self->animFrameIdx == 4) {
            func_801C29B0(NA_SE_EN_SLOGRA_SPEAR_SLASH);
        }
        break;

    case SLOGRA_SPEAR_FIRE:
        switch (self->step_s) {
        case SLOGRA_FIRE_FACE_PLAYER:
            self->facing = (GetPlayerSide() & 1) ^ 1;
            self->step_s++;

        case SLOGRA_FIRE_PROJECTILE:
            if (AnimateEntity(D_8018108C, self) == 0) {
                func_801C29B0(NA_SE_EN_SLOGRA_SPEAR_PROJECTILE);
                newEntity = AllocEntity(D_8007A958, &D_8007A958[32]);
                if (newEntity != NULL) {
                    CreateEntityFromEntity(E_SLOGRA_SPEAR_PROJECTILE, self, newEntity);
                    if (self->facing != 0) {
                        newEntity->posX.i.hi += 68;
                    } else {
                        newEntity->posX.i.hi -= 68;
                    }
                    newEntity->posY.i.hi -= 6;
                    newEntity->facing = self->facing;
                    newEntity->zPriority = self->zPriority + 1;
                }
                SetSubStep(SLOGRA_FIRE_COOLDOWN);
            }
            break;

        case SLOGRA_FIRE_COOLDOWN:
            if (AnimateEntity(D_8018109C, self) == 0) {
                SetSubStep(SLOGRA_FIRE_END);
            }
            break;

        case SLOGRA_FIRE_END: // go back to standing position
            if (AnimateEntity(D_801810A8, self) == 0) {
                SetStep(SLOGRA_WALKING_WITH_SPEAR);
            }
        }
        break;
        
    case SLOGRA_KNOCKBACK: // Knocked up, Chance to get picked up by gaibon
        switch (self->step_s) {
        case SLOGRA_KNOCKBACK_FLOOR_CHECK:
            if (EntitySlograSpecialCollision(D_8018105C) & 1) {
                self->step_s++;
            }
            break;

        case SLOGRA_KNOCKBACK_ACCEL:
            self->accelerationY = -0x40000;
            if (!(GetPlayerSide() & 1)) {
                self->accelerationX = -0x8000;
            } else {
                self->accelerationX = 0x8000;
            }
            func_801C29B0(NA_SE_EN_SLOGRA_HURT);
            self->step_s++;

        case SLOGRA_KNOCKBACK_ARC:
            if ((0x10000 | 0x7FFF) >= self->accelerationY) {
                self->ext.GS_Props.pickupFlag = 1;
            }
            entityOnFloor = EntitySlograSpecialCollision(D_8018105C);
            self->accelerationY -= 0x2400;
            if (self->ext.GS_Props.nearDeath != 0) {
                animation = &D_80181114;
            } else {
                animation = &D_801810D4;
            }
            if ((AnimateEntity(animation, self) == 0) && (entityOnFloor & 1)) {
                SetStep(SLOGRA_WALKING_WITH_SPEAR);
                if (self->ext.GS_Props.nearDeath != 0) {
                    SetStep(SLOGRA_TAUNT_WITHOUT_SPEAR);
                }
            }
        }
        break;

    case SLOGRA_LOSE_SPEAR:
        entityOnFloor = EntitySlograSpecialCollision(D_8018105C);
        if (AnimateEntity(D_801810E8, self) == 0) {
            if (entityOnFloor & 1) {
                SetStep(SLOGRA_TAUNT_WITHOUT_SPEAR);
            }
        }
        if (self->animFrameIdx >= 2) {
            self->ext.GS_Props.nearDeath = 1;
        }
        break;

    case SLOGRA_TAUNT_WITHOUT_SPEAR:
        if (!AnimateEntity(D_80181108, self)) {
            SetStep(SLOGRA_WALKING_WITHOUT_SPEAR);
        }
        break;

    case SLOGRA_WALKING_WITHOUT_SPEAR:
        if (self->step_s == 0) {
            self->facing = (GetPlayerSide() & 1) ^ 1;
            self->ext.GS_Props.flag = 1;
            self->ext.GS_Props.timer = 128;
            self->step_s++;
        }
        AnimateEntity(D_801810FC, self);
        self->facing = (GetPlayerSide() & 1) ^ 1;

        if (!(self->facing == self->ext.GS_Props.flag)) {
            self->accelerationX = 0xC000;
        } else {
            self->accelerationX = -0xC000;
        }

        func_801BCF74(&D_8018106C);
        if (self->ext.GS_Props.flag == 0) {
            if (GetPlayerDistanceX() < 72) {
                self->ext.GS_Props.flag ^= 1;
            }
            if (self->ext.GS_Props.flag != 0) {
                if (GetPlayerDistanceX() > 112) {
                self->ext.GS_Props.flag ^= 1;
                }
            }
        } else {
            if (GetPlayerDistanceX() > 112) {
                self->ext.GS_Props.flag ^= 1;
            }
        }
        if (!(Random() % 64)) {
            SetStep(SLOGRA_TAUNT_WITHOUT_SPEAR);
        }
        if (--self->ext.GS_Props.timer == 0) {
            SetStep(SLOGRA_ATTACK);
        }
        break;

    case SLOGRA_ATTACK: // Attack without spear
        if (AnimateEntity(D_80181128, self) == 0) {
            SetStep(SLOGRA_WALKING_WITHOUT_SPEAR);
        }
        if (*(s32*)&self->animFrameIdx == 7) {
            func_801C29B0(NA_SE_EN_SLOGRA_BEAK_ATTACK);
        }
        break;

    case SLOGRA_GAIBON_COMBO_ATTACK:
        switch (self->step_s) {
        case SLOGRA_COMBO_ATTACK_START: // inmobilize, Gaibon picks him up
            if (!GAIBON.ext.GS_Props.grabedAscending) {
                self->accelerationX = 0;
                self->accelerationY = 0;
                self->step_s++;
            }
            break;

        case SLOGRA_COMBO_ATTACK_PLUNGE:
            if (self->ext.GS_Props.nearDeath != 0) {
                AnimateEntity(D_80181140, self);
            } else {
                AnimateEntity(D_80181158, self);
            }

            MoveEntity();
            self->accelerationY += 0x4000;
            if ((self->posY.i.hi + g_Camera.posY.i.hi) > 416) {
                self->posY.i.hi = 416 - g_Camera.posY.i.hi;
                func_801C29B0(NA_SE_EN_SLOGRA_FLOOR_STOMP);
                g_api.func_80102CD8(1);
                self->ext.GS_Props.timer = 16;
                self->step_s++;
            }
            break;

        case SLOGRA_COMBO_ATTACK_COOLDOWN:
            if (--self->ext.GS_Props.timer == 0) {
                SetStep(SLOGRA_WALKING_WITH_SPEAR);
                if (self->ext.GS_Props.nearDeath != 0) {
                    SetStep(SLOGRA_WALKING_WITHOUT_SPEAR);
                }
            }
            break;
        }
        break;

    case SLOGRA_DYING:
        switch (self->step_s) {
        case SLOGRA_DYING_START:
            self->unk3C = 0;
            if (self->ext.GS_Props.nearDeath == 0) {
                self->ext.GS_Props.nearDeath = 1;
            }
            self->ext.GS_Props.timer = 64;
            func_801C29B0(0x697); // Slogra Death explosion / Gaibon rapid fire
            self->step_s++;

        case SLOGRA_DYING_EXPLODING:
            EntitySlograSpecialCollision(D_8018105C);
            AnimateEntity(D_80181150, self);
            if (!(g_blinkTimer % 4)) {
                newEntity = AllocEntity(D_8007D858, &D_8007D858[32]);
                if (newEntity != NULL) {
                    CreateEntityFromEntity(ENTITY_EXPLOSION, self, newEntity);
                    newEntity->posX.i.hi -= 16 - (Random() & 31);
                    newEntity->posY.i.hi -= 16 - (Random() & 31);
                    newEntity->zPriority = self->zPriority + 1;
                    newEntity->subId = 1;
                }
            }

            if (--self->ext.GS_Props.timer == 0) {
                self->step_s++;
            }
            break;

        case SLOGRA_DYING_END:
            newEntity = AllocEntity(D_8007D858, &D_8007D858[32]);
            if (newEntity != NULL) {
                CreateEntityFromEntity(ENTITY_EXPLOSION, self, newEntity);
                newEntity->subId = 3;
                newEntity->posY.i.hi += 16;
            }
            g_BossFlag |= BOSS_FLAG_SLOGRA_DEAD;
            DestroyEntity(self);
            return;
        }
        break;

    case SLOGRA_DEBUG:
        FntPrint("charal %x\n", self->animCurFrame);
        if (g_pads[1].pressed & PAD_SQUARE) {
            if (self->subId == 0) {
                self->animCurFrame++;
                self->subId |= 1;
            } else {
                break;
            }
        } else {
            self->subId = 0;
        }
        if (g_pads[1].pressed & PAD_CIRCLE) {
            if (self->step_s == 0) {
                self->animCurFrame--;
                self->step_s |= 1;
            }
        } else {
            self->step_s = 0;
        }
        break;
    }
    hitbox = &D_801811B8[self->animCurFrame][D_80181178];
    hitbox--;
    hitbox++;
    self->unk10 = *hitbox++;
    self->unk12 = *hitbox++;
    self->hitboxWidth = hitbox[0];
    self->hitboxHeight = hitbox[1];
}
#endif

void EntitySlograSpear(Entity* self) {
    s8* hitbox;

    switch (self->step) {
    case 0:
        InitializeEntity(D_80180D18);

    case 1:
        self->facing = self[-1].facing;
        self->posX.i.hi = self[-1].posX.i.hi;
        self->posY.i.hi = self[-1].posY.i.hi;
        hitbox = D_801811E0;
        hitbox += 4 * D_80181218[self[-1].animCurFrame];
        self->unk10 = *hitbox++;
        self->unk12 = *hitbox++;
        self->hitboxWidth = *hitbox++;
        self->hitboxHeight = *hitbox++;
        if (self[-1].ext.generic.unk84.U8.unk2 != 0) {
            self->step++;
        }
        break;

    case 2:
        switch (self->step_s) {
        case 0:
            self->unk19 = 4;
            self->unk3C = 0;
            if (self->facing != 0) {
                self->accelerationX = -0x24000;
            } else {
                self->accelerationX = 0x24000;
            }
            self->accelerationY = -0x40000;
            self->animCurFrame = 0x23;
            self->flags |= FLAG_DESTROY_IF_OUT_OF_CAMERA;
            self->step_s++;

        case 1:
            MoveEntity();
            self->accelerationY += 0x2800;
            self->unk1E += 0x80;
            if (!(self->unk1E & 0xFFF)) {
                func_801C29B0(0x625);
            }
        }
    }
}

// projectile fired from slogra's spear
void EntitySlograSpearProjectile(Entity* self) {
    Entity* entity;

    if (self->flags & 0x100) {
        entity = AllocEntity(D_8007D858, &D_8007D858[32]);
        if (entity != NULL) {
            CreateEntityFromEntity(ENTITY_EXPLOSION, self, entity);
            entity->subId = 1;
        }
        DestroyEntity(self);
        return;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(D_80180D24);
        if (self->facing == 0) {
            self->accelerationX = -0x40000;
        } else {
            self->accelerationX = 0x40000;
        }

    case 1:
        if (AnimateEntity(D_80181160, self) == 0) {
            SetStep(2);
        }
        break;

    case 2:
        MoveEntity();
        AnimateEntity(D_80181170, self);
        break;
    }
}

// gaibon boss
INCLUDE_ASM("asm/us/st/nz0/nonmatchings/33FCC", EntityGaibon);

void func_801B69E8(Entity* self) {
    Entity* prevEntity;
    s16 animCurFrame;

    if (self->step == 0) {
        InitializeEntity(D_80180D30);
        self->unk3C = 0;
    }

    prevEntity = &self[-1];
    self->facing = prevEntity->facing;
    self->palette = prevEntity->palette;
    self->posX.i.hi = prevEntity->posX.i.hi;
    self->posY.i.hi = prevEntity->posY.i.hi;
    self->animCurFrame = 0;

    if ((prevEntity->animCurFrame - 32) < 3U) {
        self->animCurFrame = 0x26;
    } else if (prevEntity->animCurFrame == 35) {
        self->animCurFrame = 0x27;
    } else if ((prevEntity->animCurFrame - 36) < 2U) {
        self->animCurFrame = 0x28;
    }

    if (prevEntity->objectId != 0x43) {
        DestroyEntity(self);
    }
}

// small red projectile from gaibon
void EntitySmallGaibonProjectile(Entity* self) {
    if (self->flags & 0x100) {
        self->pfnUpdate = EntityExplosion;
        self->unk19 = 0;
        self->step = 0;
        self->objectId = 2;
        self->subId = 0;
        return;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(D_80180D3C);
        self->animSet = 2;
        self->animCurFrame = 1;
        self->unk19 = 5;
        self->unk1A = 0xC0;
        self->accelerationX = (rcos(self->unk1E) * 0x28000) >> 0xC;
        self->accelerationY = (rsin(self->unk1E) * 0x28000) >> 0xC;
        self->palette = 0x81B6;
        self->unk1E -= 0x400;

    case 1:
        MoveEntity();
        AnimateEntity(D_8018136C, self);
        break;
    }
}

// large red projectile from gaibon
void EntityLargeGaibonProjectile(Entity* self) {
    Entity* newEntity;

    if (self->flags & 0x100) {
        self->pfnUpdate = EntityExplosion;
        self->objectId = 2;
        self->unk19 = 0;
        self->step = 0;
        self->subId = 1;
        return;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(D_80180D48);
        if (self->subId == 0) {
            self->animSet = 2;
            self->unk19 = 4;
            self->accelerationX = (rcos(self->unk1E) * 0x38000) >> 0xC;
            self->accelerationY = (rsin(self->unk1E) * 0x38000) >> 0xC;
            self->palette = 0x81B6;
            self->unk1E -= 0x400;
        } else {
            self->animSet = 14;
            self->unk5A = 0x79;
            self->unk19 = 0xD;
            self->unk1A = 0x100;
            self->unk6C = 0x80;
            self->palette = 0x81F3;
            self->blendMode = 0x30;
            self->step = 2;
            self->unk3C = 0;
            self->flags |= 0x2000;
        }
        break;

    case 1:
        MoveEntity();
        AnimateEntity(D_80181378, self);
        if (!(g_blinkTimer & 3)) {
            newEntity = AllocEntity(D_8007D858, &D_8007D858[32]);
            if (newEntity != NULL) {
                CreateEntityFromEntity(0x46, self, newEntity);
                newEntity->subId = 1;
                newEntity->unk1E = self->unk1E;
                newEntity->zPriority = self->zPriority + 1;
            }
        }
        break;

    case 2:
        self->unk6C += 0xFE;
        self->unk1A -= 4;
        if (AnimateEntity(D_80181388, self) == 0) {
            DestroyEntity(self);
        }
        break;
    }
}
