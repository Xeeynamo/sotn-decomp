// SPDX-License-Identifier: AGPL-3.0-or-later
#include "bo6.h"

extern s32 D_us_80181278;
extern AnimationFrame D_us_80181F1C[];
extern AnimationFrame D_us_801823C8[];

// ending 2 function
void func_us_801B9144(void) {
    Entity* entity;
    switch (RIC.step_s) {
    case 0:
        BO6_RicSetAnimation(D_us_80181F1C);
        g_api.PlaySfx(0x82B);
        if (RIC.posX.i.hi < 0x80) {
            RIC.facingLeft = 0;
        } else {
            RIC.facingLeft = 1;
        }
        RIC.step_s++;
        // fallthrough

    case 1:
        D_us_80181278 = 0x14;
        entity = &g_Entities[200];
        CreateEntityFromCurrentEntity(0x17, entity);
        entity->params = 1;
        RIC.step_s++;
        // fallthrough

    case 2:
        if (D_us_80181278 == 0x1E) {
            BO6_RicSetAnimation(D_us_801823C8);
            BO6_RicCreateEntFactoryFromEntity(g_CurrentEntity, 0x10024, 0);
            RIC.step_s++;
        }
        break;
    case 3:
        if (RIC.animCurFrame == 0xB5) {
            if (RIC.poseTimer == 1) {
                BO6_RicCreateEntFactoryFromEntity(g_CurrentEntity, 0x23, 0);
                g_api.PlaySfx(SFX_WEAPON_APPEAR);
            }
        }
        if (RIC.poseTimer < 0) {
            D_us_80181278 = 0x28;
            BO6_RicSetStand(0);
            BO6_RicCreateEntFactoryFromEntity(g_CurrentEntity, 0x450021, 0);
            g_Ric.timers[ALU_T_POISON] = 0x800;
        }
        break;
    }
}

void func_us_801B9338(void) {}

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", func_us_801B9340);

// split pl_utils

// maybe func_8015C4AC
INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", func_us_801B94CC);

// maybe func_8015C6D4
INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", func_us_801B96F4);

// BO6_RicSetStep
void OVL_EXPORT(RicSetStep)(s16 step) {
    RIC.step = step;
    RIC.step_s = 0;
}

void OVL_EXPORT(RicSetAnimation)(AnimationFrame* anim) {
    g_CurrentEntity->anim = anim;
    g_CurrentEntity->poseTimer = 0;
    g_CurrentEntity->pose = 0;
}

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", DecelerateX);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", DecelerateY);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", BO6_RicCheckFacing);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", BO6_RicSetSpeedX);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", func_us_801B9ACC);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", BO6_RicSetInvincibilityFrames);

// similar to func_8010DFF0 in DRA or func_us_801C5354 in BO4
void OVL_EXPORT(DisableAfterImage)(s32 resetAnims, s32 time) {
    Primitive* prim;

    if (resetAnims) {
        g_Entities[E_ID_41].ext.disableAfterImage.unk7D = 1;
        g_Entities[E_ID_41].animCurFrame = g_Entities[E_ID_42].animCurFrame =
            g_Entities[E_ID_43].animCurFrame = 0;
        prim = &g_PrimBuf[g_Entities[E_ID_41].primIndex];
        while (prim != NULL) {
            prim->x1 = 0;
            prim = prim->next;
        }
    }
    g_Entities[E_ID_41].ext.disableAfterImage.unk7C = 1;
    g_Entities[E_ID_41].ext.disableAfterImage.unk7E = 0xA;
    if (time) {
        g_Ric.timers[ALU_T_15] = 4;
    }
}

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", func_us_801B9C14);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", func_us_801B9C3C);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", BO6_RicSetCrouch);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", BO6_RicSetStand);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", func_us_801B9D74);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", func_us_801B9DE4);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", func_us_801B9E70);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", BO6_RicSetFall);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", func_us_801BA050);

static s32 OVL_EXPORT(RicCheckSubwpnChainLimit)(s16 subwpnId, s16 limit) {
    Entity* entity;
    s32 i;
    u32 nEmpty;
    s32 nFound;

    entity = &g_Entities[0x60];
    for (i = 0, nFound = 0, nEmpty = 0; i < 32; i++, entity++) {
        if (!entity->entityId) {
            nEmpty++;
        }

        if (entity->ext.subweapon.subweaponId != 0 &&
            entity->ext.subweapon.subweaponId == subwpnId) {
            nFound++;
        }

        if (nFound >= limit) {
            return -1;
        }
    }

    if (nEmpty < 1) {
        return -1;
    } else {
        return 0;
    }
}

extern u16 D_us_80182170[][2];
extern u16 D_us_801821C0[][2];

s32 OVL_EXPORT(RicDoSubweapon)(void) {
    SubweaponDef subweapon;
    s16 subweaponId;
    s16 chainLimit;

    if (!(g_Ric.padPressed & PAD_UP)) {
        return 1;
    }

    subweaponId = BO6_RicCheckSubweapon(&subweapon, 0, 0);
    chainLimit = subweapon.chainLimit;
    if (OVL_EXPORT(RicCheckSubwpnChainLimit)(subweaponId, chainLimit) < 0) {
        return 2;
    }

    OVL_EXPORT(RicCreateEntFactoryFromEntity)
    (g_CurrentEntity, subweapon.blueprintNum, 0);
    g_Ric.timers[PL_T_10] = 4;
    switch (RIC.step) {
    case PL_S_RUN:
        RIC.step = PL_S_STAND;
        OVL_EXPORT(RicCreateEntFactoryFromEntity)(g_CurrentEntity, 0U, 0);
        BO6_RicSetAnimation(D_us_80182170);
        break;
    case PL_S_STAND:
    case PL_S_WALK:
    case PL_S_CROUCH:
        RIC.step = PL_S_STAND;
        BO6_RicSetAnimation(D_us_80182170);
        break;
    case PL_S_FALL:
    case PL_S_JUMP:
        RIC.step = PL_S_JUMP;
        BO6_RicSetAnimation(D_us_801821C0);
        break;
    }
    g_Ric.unk46 = 3;
    RIC.step_s = 0x42;
    // n.b.! this was just set before the switch
    g_Ric.timers[PL_T_10] = 4;
    return 0;
}

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", BO6_RicDoAttack);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", BO6_RicDoCrash);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", BO6_RicSetDeadPrologue);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", BO6_RicSetSlide);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", BO6_RicSetSlideKick);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", func_us_801BA9D0);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", BO6_RicCheckInput);

static Entity* OVL_EXPORT(RicGetFreeEntity)(s16 start, s16 end) {
    Entity* entity = &g_Entities[start];
    s16 i;

    for (i = start; i < end; i++, entity++) {
        if (entity->entityId == E_NONE) {
            return entity;
        }
    }
    return NULL;
}

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", BO6_RicGetFreeEntityReverse);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", func_us_801BB314);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", func_us_801BB370);

extern SubweaponDef subweapons_def[];

s32 BO6_RicCheckSubweapon(
    SubweaponDef* actualSubwpn, s32 isItemCrash, s32 useHearts) {
    SubweaponDef* subwpn;
    SubweaponDef* wpn;
    s32 i;
    s32 subweaponId;
    s32 distanceX;

    distanceX = abs(RIC.posX.i.hi - PLAYER.posX.i.hi);

    if (isItemCrash == 0) {
        if (distanceX < 0x50) {
            subweaponId = 3;
        } else {
            subweaponId = 4;
        }
        if ((RIC.posY.i.hi - PLAYER.posY.i.hi) > 0x18) {
            subweaponId = 2;
        }
        if ((RIC.posY.i.hi - PLAYER.posY.i.hi) < -0x18) {
            subweaponId = 3;
        }
        if (g_Player.status & PLAYER_STATUS_BAT_FORM) {
            subweaponId = 2;
        }

        *actualSubwpn = subweapons_def[subweaponId];
    } else {
        subweaponId = 4;
        if (g_Ric.padPressed & 4) {
            subweaponId = 2;
        } else {
            if (g_Ric.padPressed & 1) {
                subweaponId = 3;
            }
            if (g_Ric.padPressed & 0x800) {
                subweaponId = 9;
            }
            if (g_Ric.padPressed & 0x100) {
                subweaponId = 5;
            }
        }

        subwpn = &subweapons_def[subweaponId];
        *actualSubwpn = subweapons_def[subwpn->crashId];
    }
    return subweaponId;
}

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", func_us_801BB5BC);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", BO6_RicEntityHitByHoly);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", BO6_RicEntityHitByDark);

void func_us_801BBBC0(void) {}

void func_us_801BBBC8(void) {}

extern AnimationFrame* D_us_801812B8[];
extern PfnEntityUpdate D_us_8018158C[];
extern u8 D_us_801D0800;
extern u8 D_us_801D0804;
extern u8 D_us_801D0808;
extern u8 D_us_801D07FC;

void func_us_801BBBD0(void) {
    Entity* entity;
    PfnEntityUpdate entityUpdate;
    s32 i;

    entity = g_CurrentEntity = &g_Entities[E_ID_44];

    for (i = E_ID_44; i < E_ID_90; i++, g_CurrentEntity++, entity++) {
        if (entity->entityId) {
            entityUpdate = D_us_8018158C[entity->entityId];
            entityUpdate(entity);
            entity = g_CurrentEntity;

            if (entity->entityId) {
                if (!(entity->flags & FLAG_UNK_10000000) &&
                    (entity->posX.i.hi > 288 || entity->posX.i.hi < -32 ||
                     entity->posY.i.hi > 256 || entity->posY.i.hi < -16)) {
                    DestroyEntity(entity);
                } else {
                    if (entity->flags & FLAG_UNK_20000000) {
                        g_api.UpdateAnim(NULL, D_us_801812B8);
                    }
                    entity->flags |= FLAG_NOT_AN_ENEMY;
                }
            }
        }
    }

    if (D_us_801D07FC) {
        D_us_801D07FC--;
        if (D_us_801D07FC & 1) {
            g_api.func_800EA5AC(1, D_us_801D0800, D_us_801D0804, D_us_801D0808);
        }
    }
    if ((RIC.step == 0x11) || (RIC.step == 0x60) || (RIC.step == 0x70)) {
        FntPrint("dead boss\n");
        entity = &g_Entities[E_ID_44];
        for (i = E_ID_44; i < E_ID_90; i++, entity++) {
            entity->hitboxState = 0;
        };
    }
}

Entity* OVL_EXPORT(RicCreateEntFactoryFromEntity)(
    Entity* source, u32 factoryParams, s32 arg2) {
    Entity* entity = OVL_EXPORT(RicGetFreeEntity)(68, 80);
    if (!entity) {
        return NULL;
    }
    DestroyEntity(entity);
    entity->entityId = E_FACTORY;
    // the parent pointer must align for anything the factory creates
    entity->ext.factory.parent = source;
    entity->posX.val = source->posX.val;
    entity->posY.val = source->posY.val;
    entity->facingLeft = source->facingLeft;
    entity->zPriority = source->zPriority;
    entity->params = factoryParams & 0xFFF;
    entity->ext.factory.paramsBase = (factoryParams & 0xFF0000) >> 8;
    return entity;
}

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", BO6_RicEntityFactory);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", func_us_801BC2F0);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", func_us_801BC3E0);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", func_us_801BC4F8);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", func_us_801BC5C8);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", func_us_801BC678);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", BO6_RicEntityHitByCutBlood);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", func_us_801BD0B8);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", func_us_801BD384);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", func_us_801BD47C);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", BO6_RicEntityPlayerBlinkWhite);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", func_us_801BE79C);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", BO6_RicEntityShrinkingPowerUpRing);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", BO6_RicEntityHitByIce);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", BO6_RicEntityHitByLightning);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", func_us_801C03E8);

#ifdef VERSION_PSP
extern s32 D_pspeu_0927BAF8;
#define E_ID_17 D_pspeu_0927BAF8
#else
#endif

extern s32 g_CutsceneFlags;

// TODO: I AM SHAFT!
void EntityShaft(Entity* self) {
    Entity* entity;
    FntPrint("I AM SHAFT\n");
    switch (self->step) {
    case 0:
#ifdef VERSION_PSP
        self->flags = FLAG_UNK_10000000 | FLAG_HAS_PRIMS;
#else
        self->flags = FLAG_UNK_10000000;
#endif
        self->animSet = -0x7FFB;
        self->animCurFrame = 0x8B;
        self->unk5A = 0x48;
        self->palette = PAL_OVL(0x250);
        self->zPriority = RIC.zPriority + 2;
        self->opacity = 0;
        self->drawFlags = FLAG_DRAW_OPACITY;
        self->drawMode = DRAW_TPAGE2 | DRAW_TPAGE;
        self->step++;
        break;

    case 1:
        self->opacity += 4;
        if (self->opacity > 48) {
            self->step++;
            entity = &g_Entities[0xC8];
            CreateEntityFromCurrentEntity(E_ID_17, entity);
            entity->params = 3;
            self->ext.ILLEGAL.s16[0] = 0x100;
        }
        self->posY.val += rsin(self->ext.ILLEGAL.s16[1]) * 4;
        self->ext.ILLEGAL.s16[1] += 0x20;
        break;

    case 2:
        if (!self->ext.ILLEGAL.s16[0]) {
            if ((g_CutsceneFlags & 0x40) || (g_DemoMode != Demo_None)) {
                self->drawFlags |= FLAG_DRAW_SCALEY | FLAG_DRAW_SCALEX;
                self->scaleX = self->scaleY = 0x100;
                self->step++;
            }
        } else {
            self->ext.ILLEGAL.s16[0]--;
        }
        self->posY.val += rsin(self->ext.ILLEGAL.s16[1]) * 4;
        self->ext.ILLEGAL.s16[1] += 0x20;
        break;

    case 3:
        self->scaleX -= 0x20;
        if (self->scaleX < 0x10) {
            self->scaleX = 0x10;
        }

        self->scaleY += 64;
        if (self->scaleY > 0x800) {
            self->scaleY = 0x800;
        }
        self->opacity += 6;
        if ( self->opacity > 0xF0) {
            self->step++;
        }
        break;

    case 4:
        self->opacity -= 3;
        if (self->opacity < 4) {
            DestroyEntity(self);
        }
        break;
    }
}

// TODO: rename ShaftOrb
Entity* BO6_RicGetFreeEntity(s16, s16);
extern u8 D_us_80181E9C[];

void func_us_801C0FE8(Entity* self) {
    Entity* entity;
    Primitive* prim;
    s32 posX;
    s32 posY;
    s32 accelX;
    s32 accelY;
    s16 primIndex;
    s16 params;
    s32 velocity;

    params = self->params & 0xFF;
    switch (self->step) {
    case 0:
        self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 1);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        prim = &g_PrimBuf[self->primIndex];
        prim->clut = 0x252;
        prim->tpage = 0x12;

        // temp_a1 = &D_us_80181E9C[temp_a0];
        prim->u0 = prim->u2 = D_us_80181E9C[params * 2] - 2;
        prim->u1 = prim->u3 = D_us_80181E9C[params * 2] + 2;

        prim->v0 = prim->v1 = D_us_80181E9C[params * 2 + 1] - 2;
        prim->v2 = prim->v3 = D_us_80181E9C[params * 2 + 1] + 2;

        prim->priority = RIC.zPriority + 4;
        prim->drawMode = DRAW_UNK02;

        accelX = D_us_80181E9C[params * 2] - 16;
        accelY = D_us_80181E9C[params * 2 + 1] - 16;
        self->posX.i.hi += accelX;
        self->posY.i.hi += accelY;

        velocity = ratan2(-accelY, accelX);
        velocity += ((rand() & 0x7F) - 0x40);
        self->ext.shaftOrb.velocityAngle = velocity;
        self->flags = FLAG_UNK_10000000 | FLAG_HAS_PRIMS;
        self->ext.shaftOrb.timer = 8;
        self->step++;
        break;

    case 1:
        if (--self->ext.shaftOrb.timer == 0) {
            self->ext.shaftOrb.timer = 16;
            velocity = self->ext.shaftOrb.velocityAngle;
            self->velocityX = (rcos(velocity) * 32) + (rand() & 0xF);
            self->velocityY = -((rsin(velocity) * 32) + (rand() & 0xF));
            self->step++;
        }
        break;

    case 2:
        self->posX.val += self->velocityX;
        self->posY.val += self->velocityY;
        if (--self->ext.shaftOrb.timer == 0) {
            BO6_RicCreateEntFactoryFromEntity(self, 0x4A, 0);
            self->velocityY = (rand() & 0x7FFF) + 0xFFFF0000;
            self->velocityX = self->velocityX >> 2;
            self->ext.shaftOrb.timer = 1;
            self->step++;
        }
        break;
    case 3:
        if ((self->ext.shaftOrb.timer % 4) == 0) {
            entity = BO6_RicGetFreeEntity(0x50, 0x8F);
            if (entity != NULL) {
                DestroyEntity(entity);
                entity->entityId = 0x43;
                entity->params = 0x100;
                // not shaft orb
                entity->ext.shaftOrb.parent = self->ext.shaftOrb.parent;
                entity->posX.val = self->posX.val;
                entity->posY.val = self->posY.val;
            }
        }
        self->ext.shaftOrb.timer += 1;
        self->velocityY += 0xC00;
        self->posY.val += self->velocityY;
        self->posX.val += self->velocityX;
        self->flags &= ~FLAG_UNK_10000000;
        break;
    }

    posX = self->posX.i.hi;
    posY = self->posY.i.hi;
    prim = &g_PrimBuf[self->primIndex];
    prim->x0 = prim->x2 = posX - 2;
    prim->x1 = prim->x3 = posX + 2;
    prim->y0 = prim->y1 = posY - 2;
    prim->y2 = prim->y3 = posY + 2;
}

extern AnimationFrame D_us_80181EDC[];

void func_us_801C13A8(Entity* self) {
    s16 params = self->params & 0x7F00;
    switch (self->step) {
    case 0:
        self->flags = FLAG_UNK_20000000 | FLAG_POS_CAMERA_LOCKED;
        self->unk5A = 0x79;
        self->animSet = 0xE;
        self->zPriority = RIC.zPriority + 6;
        self->palette = PAL_OVL(0x25E);
        self->drawMode = DRAW_UNK_40 | DRAW_TPAGE2 | DRAW_TPAGE;
        self->drawFlags = FLAG_DRAW_SCALEY | FLAG_DRAW_SCALEX;
        self->scaleX = self->scaleY = 0xC0;
        self->anim = D_us_80181EDC;
        if (params) {
            self->scaleX = self->scaleY = 0x80;
            self->anim = D_us_80181EDC;
        }
        self->velocityY = -FIX(0.25);
        self->step++;
        break;

    case 1:
        self->posY.val += self->velocityY;
        if (self->poseTimer < 0) {
            DestroyEntity(self);
        }
        break;
    }
}


INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", BO6_RicEntityWhip);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", BO6_RicEntityArmBrandishWhip);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", func_us_801C2688);

void func_us_801C277C(void) {}

void func_us_801C2784(void) {}

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", BO6_RicEntitySubwpnHolyWaterBreakGlass);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", BO6_RicEntityCrashHydroStorm);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", BO6_DebugShowWaitInfo);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", BO6_DebugInputWait);
INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", func_us_801C310C);

int WarpBackgroundBrightness() {
    return 0;
}

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", func_us_801C32C4);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", BO6_RicEntitySubwpnHolyWaterFlame);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", BO6_RicEntitySubwpnCrashCross);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", func_us_801C4200);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", func_us_801C488C);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", BO6_RicEntitySubwpnCrossTrail);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", BO6_RicEntitySubwpnCrashCrossParticles);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", BO6_RicEntitySubwpnThrownAxe);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", func_us_801C560C);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", BO6_RicEntitySubwpnKnife);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", BO6_ReboundStoneBounce1);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", BO6_ReboundStoneBounce2);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", BO6_RicEntitySubwpnReboundStone);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", BO6_RicEntitySubwpnThrownVibhuti);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", BO6_PrimDecreaseBrightness);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", BO6_RicEntitySubwpnAgunea);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", BO6_RicEntityAguneaHitEnemy);

extern AnimationFrame D_us_801829D4[];

void BO6_RicEntityVibhutiCrashCloud(Entity* self) {
    s32 angle;

    switch (self->step) {
    case 0:
        self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 1);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }

        self->flags = FLAG_POS_CAMERA_LOCKED | FLAG_HAS_PRIMS;
        self->posX.val = self->ext.vibCrashCloud.parent->ext.vibhutiCrash.x;
        self->posY.val = self->ext.vibCrashCloud.parent->ext.vibhutiCrash.y;
        self->facingLeft = self->ext.vibCrashCloud.parent->ext.vibhutiCrash.facing;
        self->flags |= FLAG_UNK_20000000;
        self->unk5A = 0x64;
        self->animSet = 0xE;
        self->palette = PAL_OVL(0x19E);
        self->anim = D_us_801829D4;
        self->drawMode = DRAW_TPAGE2 | DRAW_TPAGE;
        self->drawFlags = FLAG_DRAW_OPACITY;
        self->opacity = 0x60;
        self->hitboxWidth = 8;
        self->hitboxHeight = 8;

        angle = (rand() % 512) + 0x300;
        self->velocityX = rcos(angle) << 5;
        self->velocityY = -(rsin(angle) << 5);
        self->step++;
        break;

    case 1:
        self->ext.vibCrashCloud.unk7C++;
        if (self->ext.vibCrashCloud.unk7C > 38) {
            DestroyEntity(self);
        } else {
            self->posX.val += self->velocityX;
            self->posY.val += self->velocityY;
        }
        break;
    }
}

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", BO6_RicEntityCrashVibhuti);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", func_us_801C8590);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", func_us_801C8618);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", BO6_RicEntityCrashReboundStoneExplosion);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", BO6_RicEntityCrashReboundStone);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", BO6_RicEntityCrashBibleBeam);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", BO6_RicEntityCrashBible);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", func_us_801C9DE8);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", func_us_801CA340);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", BO6_GetAguneaLightningAngle);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", BO6_AguneaShuffleParams);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", BO6_RicEntityAguneaLightning);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", BO6_RicEntityAguneaCircle);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", BO6_RicEntitySubwpnStopwatchCircle);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", BO6_EntityStopWatch);

void OVL_EXPORT(RicEntitySubwpnBibleTrail)(Entity* entity) {
    Primitive* prim;

    switch (entity->step) {
    case 0:
        entity->primIndex = g_api.AllocPrimitives(PRIM_GT4, 1);
        if (entity->primIndex == -1) {
            DestroyEntity(entity);
            return;
        }
        entity->flags = FLAG_UNK_10000000 | FLAG_HAS_PRIMS;
        prim = &g_PrimBuf[entity->primIndex];
        prim->tpage = 0x1C;
        prim->clut = 0x19D;
        prim->u0 = prim->u2 = 0x20;
        prim->v0 = prim->v1 = 0;
        prim->u1 = prim->u3 = 0x30;
        prim->v2 = prim->v3 = 0x10;
        prim->x0 = prim->x2 = entity->posX.i.hi - 8;
        prim->x1 = prim->x3 = entity->posX.i.hi + 8;
        prim->y0 = prim->y1 = entity->posY.i.hi - 8;
        prim->y2 = prim->y3 = entity->posY.i.hi + 8;
        prim->priority = entity->zPriority;
        prim->drawMode = DRAW_TPAGE | DRAW_COLORS | DRAW_TRANSP;
        entity->ext.et_BibleSubwpn.unk7E = 0x60;
        entity->step++;
        break;
    case 1:
        entity->ext.et_BibleSubwpn.unk7C++;
        if (entity->ext.et_BibleSubwpn.unk7C > 5) {
            entity->step++;
        }
        entity->ext.et_BibleSubwpn.unk7E -= 8;
        break;
    case 2:
        DestroyEntity(entity);
        return;
    }
    prim = &g_PrimBuf[entity->primIndex];
    PCOL(prim) = entity->ext.et_BibleSubwpn.unk7E;
}

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", BO6_RicEntitySubwpnBible);

INCLUDE_RODATA("boss/bo6/nonmatchings/us_39144", D_us_801A7028);

INCLUDE_RODATA("boss/bo6/nonmatchings/us_39144", D_us_801A7030);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", BO6_RicEntityCrashCrossBeam);
