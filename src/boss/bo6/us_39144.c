// SPDX-License-Identifier: AGPL-3.0-or-later
#include <input.h>
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
        CreateEntityFromCurrentEntity(E_ID_17, entity);
        entity->params = 1;
        RIC.step_s++;
        // fallthrough

    case 2:
        if (D_us_80181278 == 0x1E) {
            BO6_RicSetAnimation(D_us_801823C8);
            BO6_RicCreateEntFactoryFromEntity(
                g_CurrentEntity, FACTORY(E_ID_24, 0x1), 0);
            RIC.step_s++;
        }
        break;
    case 3:
        if (RIC.animCurFrame == 0xB5) {
            if (RIC.poseTimer == 1) {
                BO6_RicCreateEntFactoryFromEntity(
                    g_CurrentEntity, FACTORY(E_ID_23, 0), 0);
                g_api.PlaySfx(SFX_WEAPON_APPEAR);
            }
        }
        if (RIC.poseTimer < 0) {
            D_us_80181278 = 0x28;
            BO6_RicSetStand(0);
            BO6_RicCreateEntFactoryFromEntity(
                g_CurrentEntity, FACTORY(E_ID_21, 0x45), 0);
            g_Ric.timers[ALU_T_POISON] = 0x800;
        }
        break;
    }
}

void func_us_801B9338(void) {}

extern s16 D_us_8018221C[];

void func_us_801B9340(void) {
    switch (RIC.step_s) {
    case 0:
        BO6_RicResetPose();
        RIC.velocityY = FIX(-5);
        func_us_801B9ACC(0xFFFF1000);
        RIC.anim = D_us_8018221C;
        g_api.PlaySfx(0x83E);
        g_Ric.unk40 = 0x8166;
        g_Ric.timers[2] = 8;
        BO6_RicCreateEntFactoryFromEntity(
            g_CurrentEntity, FACTORY(E_ID_21, 0x58), 0);
        RIC.step_s += 1;
        return;
    case 1:
        if ((g_Ric.vram_flag & 2) && (FIX(-1) > RIC.velocityY)) {
            RIC.velocityY = FIX(-1);
        }
        if (BO6_RicCheckInput(0x20280) != 0) {
            RIC.step = 0x70;
            RIC.step_s = 2;
            return;
        }
        return;
    case 2:
        DecelerateX(FIX(0.125));
        if ((PLAYER.posX.i.hi - RIC.posX.i.hi) > 0) {
            RIC.facingLeft = 0;
            return;
        }
        RIC.facingLeft = 1;
        break;
    }
}

// split pl_utils

// maybe func_8015C4AC
INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", func_us_801B94CC);

// maybe func_8015C6D4
extern u8 D_us_80181298[];
extern u8 D_us_801812A8[];

void func_us_801B96F4(void) {
    byte pad[0x28];
    Primitive* prim;
    PlayerDraw* draw;
    s32 i;
    u8 var_s3;
    u8 var_s5;
    u8 resetAnim;

    resetAnim = g_Entities[65].ext.entSlot1.unk1;
    prim = &g_PrimBuf[g_Entities[65].primIndex];
    i = 0;
    draw = &g_PlayerDraw[9];
    var_s5 = D_us_80181298[g_Entities[65].ext.entSlot1.unk2];
    var_s3 = D_us_801812A8[g_Entities[65].ext.entSlot1.unk2];
    while (prim != NULL) {
        if (prim->r0 > var_s3) {
            prim->r0 -= var_s5;
        }
        if (prim->r0 < 112 && prim->b0 < 240) {
            prim->b0 += 6;
        }
        if (prim->r0 < 88) {
            prim->y1 = 16;
        } else {
            prim->y1 = 0;
        }
        if (prim->r0 <= var_s3) {
            prim->x1 = 0;
        }
        if ((i ^ g_Timer) & 1) {
            g_Entities[i / 2 + 65].posX.i.hi = prim->x0;
            g_Entities[i / 2 + 65].posY.i.hi = prim->y0;
            g_Entities[i / 2 + 65].animCurFrame = prim->x1;
            g_Entities[i / 2 + 65].drawMode = prim->y1;
            g_Entities[i / 2 + 65].facingLeft = prim->x2;
            g_Entities[i / 2 + 65].palette = prim->y2;
            g_Entities[i / 2 + 65].zPriority = RIC.zPriority - 2;
            if (resetAnim) {
                g_Entities[i / 2 + 65].animCurFrame = 0;
                prim->x1 = 0;
            }

            draw->r0 = draw->r1 = draw->r2 = draw->r3 = draw->g0 = draw->g1 =
                draw->g2 = draw->g3 = prim->r0;
            draw->b0 = draw->b1 = draw->b2 = draw->b3 = prim->b0;
            draw->enableColorBlend = true;
            draw++;
        }
        i++;
        prim = prim->next;
    }
}



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

#include "../../decelerate.h"

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", BO6_RicCheckFacing);

void BO6_RicSetSpeedX(s32 speed) {
    if (g_CurrentEntity->facingLeft == 1)
        speed = -speed;
    g_CurrentEntity->velocityX = speed;
}

// set velocity
void func_us_801B9ACC(s32 speed) {
    if (RIC.entityRoomIndex == 1)
        speed = -speed;
    RIC.velocityX = speed;
}

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

void func_us_801B9C14() {
    g_Entities[65].ext.entSlot1.unk3 = 0;
    g_Entities[65].ext.entSlot1.unk2 = 0;
    g_Entities[65].ext.entSlot1.unk1 = 0;
    g_Entities[65].ext.entSlot1.unk0 = 0;
}

void BO6_RicSetDebug() { OVL_EXPORT(RicSetStep)(PL_S_DEBUG); }

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", BO6_RicSetCrouch);

extern AnimationFrame ric_anim_stand[];

void BO6_RicSetStand(s32 velocityX) {
    RIC.velocityX = velocityX;
    RIC.velocityY = 0;
    g_Ric.unk44 = 0;
    OVL_EXPORT(RicSetStep)(PL_S_STAND);
    OVL_EXPORT(RicSetAnimation)(ric_anim_stand);
}

extern s16 D_us_801821F8[];

void func_us_801B9D74(void) {
    g_Ric.unk44 = 0;
    BO6_RicSetStep(0x1A);
    BO6_RicSetAnimation(D_us_801821F8);
    BO6_RicSetSpeedX(FIX(2.25));
    g_Ric.timers[11] = 0x28;
    RIC.velocityY = 0;
    BO6_RicCreateEntFactoryFromEntity(g_CurrentEntity, 0x50001, 0);
}

extern s16 D_us_80182010[];

void func_us_801B9DE4(void) {
    if (g_Ric.timers[8] != 0) {
        func_us_801B9D74();
    } else {
        g_Ric.timers[1] = 8;
        g_Ric.timers[1] = g_Ric.timers[8] = 12;
        g_Ric.unk44 = 0;
        BO6_RicSetStep(2);
        BO6_RicSetAnimation(D_us_80182010);
        BO6_RicSetSpeedX(FIX(1.25));
        RIC.velocityY = 0;
    }
}

extern s16 D_us_80182078[];
extern s16 D_us_80182094[];

void func_us_801B9E70(void) {
    if ((BO6_RicCheckFacing() != 0) || (RIC.step == 0x18)) {
        BO6_RicSetAnimation(D_us_80182094);
        if (RIC.step == 0x1A) {
            BO6_RicSetSpeedX(FIX(2.25));
            g_Ric.unk44 = 0x10;
        } else {
            BO6_RicSetSpeedX(0x14000);
            g_Ric.unk44 = 0;
        }
    } else {
        BO6_RicSetAnimation(D_us_80182078);
        RIC.velocityX = 0;
        g_Ric.unk44 = 4;
    }
    BO6_RicSetStep(5);
    RIC.velocityY = FIX(-4.6875);
}

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", BO6_RicSetFall);

extern s16 D_us_80182324[];

void func_us_801BA050(void) {
    BO6_RicSetStep(9);
    RIC.velocityX = 0;
    BO6_RicSetSpeedX(FIX(1.25));
    RIC.velocityY = FIX(-7.5);
    g_Ric.high_jump_timer = 0;
    BO6_RicSetAnimation(D_us_80182324);
    func_us_801B9C14();
    BO6_RicCreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0x2D, 0), 0);
    g_api.PlaySfx(0x82D);
    g_Ric.timers[12] = 4;
}

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

void OVL_EXPORT(RicSetDeadPrologue)() {
    OVL_EXPORT(RicSetStep)(PL_S_DEAD_PROLOGUE);
}

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", BO6_RicSetSlide);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", BO6_RicSetSlideKick);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", func_us_801BA9D0);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", BO6_RicCheckInput);

Entity* OVL_EXPORT(RicGetFreeEntity)(s16 start, s16 end) {
    Entity* entity = &g_Entities[start];
    s16 i;

    for (i = start; i < end; i++, entity++) {
        if (entity->entityId == E_NONE) {
            return entity;
        }
    }
    return NULL;
}

// pl_blueprints?

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

extern EInit D_us_80180448;

void func_us_801BC3E0(Entity* self) {
    if (RIC.step != PL_S_SLIDE_KICK) {
        DestroyEntity(self);
        return;
    }
    self->posX.i.hi = RIC.posX.i.hi;
    self->posY.i.hi = RIC.posY.i.hi;
    self->facingLeft = RIC.facingLeft;
    if (self->step == 0) {
        InitializeEntity(D_us_80180448);
        self->flags = 0x18000000;
        self->hitboxOffX = 0x14;
        self->hitboxWidth = self->hitboxHeight = 9;
        self->step = 1;
    }

    if (RIC.animCurFrame == 140) {
        self->hitboxOffY = 0;
    }

    if (RIC.animCurFrame == 141) {
        self->hitboxOffY = 12;
    }

    if (self->hitFlags) {
        g_Ric.unk44 |= 0x80;
    } else {
        g_Ric.unk44 &= ~0x80;
    }
    self->hitFlags = 0;
}


INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", func_us_801BC4F8);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", func_us_801BC5C8);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", func_us_801BC678);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", BO6_RicEntityHitByCutBlood);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", func_us_801BD0B8);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", func_us_801BD384);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", func_us_801BD47C);

extern s32 D_us_80181A64[];
extern s16 D_us_80181AA4[][10];
extern s16* D_us_801A39B0[];
extern u8* D_us_8018303C[];

void BO6_RicEntityPlayerBlinkWhite(Entity* self) {
    u8 xMargin;
    u8 yMargin;
    s16 angle;
    u8 wSprite;
    u8 hSprite;
    s16 width;
    s16 height;
    s16 selfX;
    s16 selfY;
    s32 i;
    Primitive* prim;
    s16 xPivot;
    s16 yPivot;
    s16 plSpriteIndex;
    s16 upperParams;
    s16 angleRedIndex;
    s16* sp44;
    u8* plSprite;
    s16* dataPtr;
    s16 angleGreenIndex;
    s16 angleBlueIndex;
    s16 redDivide;
    s16 blueDivide;
    s16 greenDivide;
    void* dummy48;

    if (!RIC.animSet || !(RIC.animCurFrame & 0x7FFF)) {
        DestroyEntity(self);
        return;
    }
    self->posY.i.hi = RIC.posY.i.hi;
    self->posX.i.hi = RIC.posX.i.hi;
    self->facingLeft = RIC.facingLeft;
#if defined(VERSION_PSP)
    sp44 = D_92641C8[RIC.animCurFrame & 0x7FFF];
#endif
    sp44 = D_us_801A39B0[RIC.animCurFrame & 0x7FFF];
    plSpriteIndex = *sp44++;
    plSpriteIndex &= 0x7FFF;
    selfX = self->posX.i.hi;
    selfY = self->posY.i.hi;
    plSprite = D_us_8018303C[plSpriteIndex];
    xMargin = 4;
    yMargin = 1;
    wSprite = xMargin + plSprite[0];
    hSprite = yMargin + plSprite[1];
    width = wSprite - xMargin;
    height = hSprite - yMargin;
    xPivot = sp44[0] + plSprite[2];
    yPivot = sp44[1] + plSprite[3];

    self->rotate = RIC.rotate;
    self->drawFlags = RIC.drawFlags;
    self->scaleX = RIC.scaleX;
    self->scaleY = RIC.scaleY;
    self->rotPivotY = RIC.rotPivotY;
    self->rotPivotX = RIC.rotPivotX;
    upperParams = (self->params & 0x7F00) >> 8;
    dataPtr = D_us_80181AA4[upperParams & 0x3F];
    switch (self->step) {
    case 0:
        if (func_us_801BD47C(self) != 0) {
            DestroyEntity(self);
            return;
        }
        self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 8);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }

        self->flags = FLAG_UNK_10000000 | FLAG_POS_CAMERA_LOCKED | FLAG_HAS_PRIMS;

        prim = &g_PrimBuf[self->primIndex];
        for (i = 0; i < 8; i++) {
            D_us_80181A64[i] = i << 9;
            prim->tpage = 0x10;
            prim->clut = dataPtr[3];
            prim->r0 = prim->b0 = prim->g0 = prim->r1 = prim->b1 = prim->g1 =
                prim->r2 = prim->b2 = prim->g2 = prim->r3 = prim->b3 =
                    prim->g3 = 0x80;
            prim->priority = RIC.zPriority + 2;
            prim->drawMode =
                dataPtr[8] + DRAW_UNK_100 + DRAW_COLORS;
            prim = prim->next;
        }
        self->ext.playerBlink.unk8A = dataPtr[9];
        self->ext.playerBlink.unk90 = 0;
        self->step += 1;
        break;
    case 1:
        self->ext.playerBlink.unk90 += 0xA;
        if (self->ext.playerBlink.unk90 > 0x100) {
            self->ext.playerBlink.unk90 = 0x100;
            self->ext.playerBlink.unk80 = dataPtr[7];
            self->step += 1;
        }
        break;
    case 2:
        if (dataPtr[7] >= 0x7000) {
            switch ((u32)dataPtr[7]) {
            case 0x7000:
                if (g_Ric.timers[PL_T_POISON] == 0 ||
                    (RIC.step == PL_S_DEAD || RIC.step == PL_S_ENDING_3 || RIC.step == PL_S_ENDING_4)) {
                    self->step++;
                }
                break;
            case 0x7001:
                if (g_Ric.timers[PL_T_INVINCIBLE_SCENE] == 0) {
                    self->step++;
                }
                break;
            case 0x7007:
            case 0x7002:
                if (RIC.step != PL_S_HIT) {
                    self->step++;
                }
                break;
            case 0x7005:
            case 0x7006:
                if (RIC.step_s == 3) {
                    self->step++;
                }
                break;
            case 0x7003:
            case 0x7004:
            case 0x7008:

                break;
            }
            self->ext.playerBlink.unk80 = 8;
        }
        if (--self->ext.playerBlink.unk80 == 0) {
            self->step++;
        }
        break;
    case 3:
        self->ext.playerBlink.unk90 -= 10;
        if (self->ext.playerBlink.unk90 < 0) {
            DestroyEntity(self);
            return;
        }
        break;
    }
    self->ext.playerBlink.unk82 += self->ext.playerBlink.unk8A;
    if (self->facingLeft) {
        selfX = selfX - xPivot;
    } else {
        selfX = selfX + xPivot;
    }
    selfY = selfY + yPivot;
    prim = &g_PrimBuf[self->primIndex];
    for (i = 0; i < 8; i++) {
        if (upperParams & 0x40) {
            switch (i) {
            case 0:
                if (self->facingLeft) {
                    prim->x0 = selfX;
                    prim->x1 = selfX - width / 2;
                    prim->u0 = xMargin;
                    prim->u1 = xMargin + width / 2;
                } else {
                    prim->x0 = selfX;
                    prim->x1 = selfX + width / 2;
                    prim->u0 = xMargin;
                    prim->u1 = xMargin + width / 2;
                }
                prim->y0 = prim->y1 = selfY;
                prim->v0 = prim->v1 = yMargin;
                break;
            case 1:
                if (self->facingLeft) {
                    prim->x0 = selfX - width / 2;
                    prim->x1 = selfX - width;
                    prim->u0 = xMargin + width / 2;
                    prim->u1 = xMargin + width;
                } else {
                    prim->x0 = selfX + width / 2;
                    prim->x1 = selfX + width;
                    prim->u0 = xMargin + width / 2;
                    prim->u1 = xMargin + width;
                }
                prim->y0 = prim->y1 = selfY;
                prim->v0 = prim->v1 = yMargin;
                break;
            case 2:
                if (self->facingLeft) {
                    prim->x0 = prim->x1 = selfX - width;
                    prim->u0 = prim->u1 = xMargin + width;
                } else {
                    prim->x0 = prim->x1 = selfX + width;
                    prim->u0 = prim->u1 = xMargin + width;
                }
                prim->y0 = selfY;
                prim->y1 = selfY + height / 2;
                prim->v0 = yMargin;
                prim->v1 = yMargin + height / 2;
                break;
            case 3:
                if (self->facingLeft) {
                    prim->x0 = prim->x1 = selfX - width;
                    prim->u0 = prim->u1 = xMargin + width;
                } else {
                    prim->x0 = prim->x1 = selfX + width;
                    prim->u0 = prim->u1 = xMargin + width;
                }
                prim->y0 = selfY + height / 2;
                prim->y1 = selfY + height;
                prim->v0 = yMargin + height / 2;
                prim->v1 = yMargin + height;
                break;
            case 4:
                if (self->facingLeft) {
                    prim->x0 = selfX - width;
                    prim->x1 = selfX - width / 2;
                    prim->u0 = xMargin + width;
                    prim->u1 = xMargin + width / 2;
                } else {
                    prim->x0 = selfX + width;
                    prim->x1 = selfX + width / 2;
                    prim->u0 = xMargin + width;
                    prim->u1 = xMargin + width / 2;
                }
                prim->y0 = prim->y1 = selfY + height;
                prim->v0 = prim->v1 = yMargin + height;
                break;
            case 5:
                if (self->facingLeft) {
                    prim->x0 = selfX - width / 2;
                    prim->x1 = selfX;
                    prim->u0 = xMargin + width / 2;
                    prim->u1 = xMargin;
                } else {
                    prim->x0 = selfX + width / 2;
                    prim->x1 = selfX;
                    prim->u0 = xMargin + width / 2;
                    prim->u1 = xMargin;
                }
                prim->y0 = prim->y1 = selfY + height;
                prim->v0 = prim->v1 = yMargin + height;
                break;
            case 6:
                if (self->facingLeft) {
                    prim->x0 = prim->x1 = selfX;
                    prim->u0 = prim->u1 = xMargin;
                } else {
                    prim->x0 = prim->x1 = selfX;
                    prim->u0 = prim->u1 = xMargin;
                }
                prim->y0 = selfY + height;
                prim->y1 = selfY + height / 2;
                prim->v0 = yMargin + height;
                prim->v1 = yMargin + height / 2;
                break;
            case 7:
                if (self->facingLeft) {
                    prim->x0 = prim->x1 = selfX;
                    prim->u0 = prim->u1 = xMargin;
                } else {
                    prim->x0 = prim->x1 = selfX;
                    prim->u0 = prim->u1 = xMargin;
                }
                prim->y0 = selfY + height / 2;
                prim->y1 = selfY;
                prim->v0 = yMargin + height / 2;
                prim->v1 = yMargin;
                break;
            }
            if (self->facingLeft) {
                prim->x2 = prim->x3 =
                    selfX - width / 2 +
                    (((rcos(self->ext.playerBlink.unk82) >> 4) * 3) >> 0xC);
            } else {
                prim->x2 = prim->x3 =
                    selfX + width / 2 +
                    (((rcos(self->ext.playerBlink.unk82) >> 4) * 3) >> 0xC);
            }
            prim->y2 = prim->y3 =
                (selfY + height / 2) -
                ((rsin(self->ext.playerBlink.unk82) >> 4) * 3 << 1 >> 8);
            prim->u2 = prim->u3 = xMargin + width / 2;
            prim->v2 = prim->v3 = yMargin + height / 2;
        } else {
            if (self->facingLeft) {
                prim->x0 = prim->x2 = (selfX - width) + 1;
                prim->x1 = prim->x3 = selfX + 1;
            } else {
                prim->x0 = prim->x2 = selfX;
                prim->x1 = prim->x3 = selfX + width;
            }
            prim->y0 = prim->y1 = selfY + height * i / 8;
            prim->y2 = prim->y3 = selfY + height * (i + 1) / 8;
            if (self->facingLeft) {
                prim->u0 = prim->u2 = wSprite - 1;
                prim->u1 = prim->u3 = xMargin - 1;
            } else {
                prim->u0 = prim->u2 = xMargin;
                prim->u1 = prim->u3 = wSprite;
            }
            prim->v0 = prim->v1 = yMargin + height * i / 8;
            prim->v2 = prim->v3 = yMargin + height * (i + 1) / 8;
        }
        angleRedIndex = dataPtr[0];
        angleGreenIndex = dataPtr[2];
        angleBlueIndex = dataPtr[1];
        redDivide = dataPtr[4];
        greenDivide = dataPtr[6];
        blueDivide = dataPtr[5];
        if (upperParams & 0x40) {
            angle = D_us_80181A64[(i + angleRedIndex) % 8];
            prim->r0 = ((rsin(angle) + 0x1000) >> 6) *
                       self->ext.playerBlink.unk90 / redDivide;
            angle = D_us_80181A64[(i + angleGreenIndex) % 8];
            prim->g0 = ((rsin(angle) + 0x1000) >> 6) *
                       self->ext.playerBlink.unk90 / greenDivide;
            angle = D_us_80181A64[(i + angleBlueIndex) % 8];
            prim->b0 = ((rsin(angle) + 0x1000) >> 6) *
                       self->ext.playerBlink.unk90 / blueDivide;
            angle = D_us_80181A64[(i + angleRedIndex + 1) % 8];
            prim->r1 = ((rsin(angle) + 0x1000) >> 6) *
                       self->ext.playerBlink.unk90 / redDivide;
            angle = D_us_80181A64[(i + angleGreenIndex + 1) % 8];
            prim->g1 = ((rsin(angle) + 0x1000) >> 6) *
                       self->ext.playerBlink.unk90 / greenDivide;
            angle = D_us_80181A64[(i + angleBlueIndex + 1) % 8];
            prim->b1 = ((rsin(angle) + 0x1000) >> 6) *
                       self->ext.playerBlink.unk90 / blueDivide;
            prim->r2 = prim->g2 = prim->b2 = prim->r3 = prim->g3 = prim->b3 = 0;
            D_us_80181A64[i] += self->ext.playerBlink.unk8A;
        } else {
            angle = D_us_80181A64[(i + angleRedIndex) % 8];
            prim->r0 = prim->r1 = (((rsin(angle) + 0x1000) >> 6) *
                                   self->ext.playerBlink.unk90 / redDivide);
            angle = D_us_80181A64[(i + angleGreenIndex) % 8];
            prim->g0 = prim->g1 = (((rsin(angle) + 0x1000) >> 6) *
                                   self->ext.playerBlink.unk90 / greenDivide);
            angle = D_us_80181A64[(i + angleBlueIndex) % 8];
            prim->b0 = prim->b1 = (((rsin(angle) + 0x1000) >> 6) *
                                   self->ext.playerBlink.unk90 / blueDivide);
            angle = D_us_80181A64[(i + angleRedIndex + 1) % 8];
            prim->r2 = prim->r3 = (((rsin(angle) + 0x1000) >> 6) *
                                   self->ext.playerBlink.unk90 / redDivide);
            angle = D_us_80181A64[(i + angleGreenIndex + 1) % 8];
            prim->g2 = prim->g3 = (((rsin(angle) + 0x1000) >> 6) *
                                   self->ext.playerBlink.unk90 / greenDivide);
            angle = D_us_80181A64[(i + angleBlueIndex + 1) % 8];
            prim->b2 = prim->b3 = (((rsin(angle) + 0x1000) >> 6) *
                                   self->ext.playerBlink.unk90 / blueDivide);
            D_us_80181A64[i] += self->ext.playerBlink.unk8A;
        }
        prim->priority = RIC.zPriority + 2;
        prim = prim->next;
    }
    if ((upperParams & 0x3F) == 0 || (upperParams & 0x3F) == 7) {
        BO6_RicSetInvincibilityFrames(1, 10);
    }
}
