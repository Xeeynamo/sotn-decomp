// SPDX-License-Identifier: AGPL-3.0-or-later
#include "richter.h"

// func_060AB980
Entity* RicGetFreeEntity(s16 start, s16 end) {
    Entity* entity = &g_Entities[start];
    s16 i;

    for (i = start; i < end; i++, entity++) {
        if (entity->entityId == E_NONE) {
            return entity;
        }
    }
    return NULL;
}

// func_060AB9C0
Entity* RicGetFreeEntityReverse(s16 start, s16 end) {
    Entity* entity = &g_Entities[end - 1];
    s16 i;
    for (i = end - 1; i >= start; i--, entity--) {
        if (entity->entityId == E_NONE) {
            return entity;
        }
    }
    return NULL;
}

s32 D_80174F80[11];
// func_060ABA08
void func_8015F9F0(Entity* entity) {
    s32 i;
    s32 enemyId;

    if (entity < &g_Entities[32]) {
        entity->enemyId = 1;
        return;
    }

    for (i = 0;; i++) {
        for (enemyId = 2; enemyId < LEN(D_80174F80); ++enemyId) {
            if (D_80174F80[enemyId] == i) {
                ++D_80174F80[enemyId];
                entity->enemyId = enemyId;
                return;
            }
        }
    }
}

void func_8015FA5C(s32 arg0) {
    D_80174FAC = D_80154674[arg0][0];
    D_80174FB0 = D_80154674[arg0][1];
    D_80174FB4 = D_80154674[arg0][2];
    D_80174FB8 = D_80154674[arg0][3];
}

// RicSetSubweaponParams
void func_060ABA98(Entity* entity) {
    SubweaponDef* subwpn =
        &ric_subweapons_def[entity->ext.subweapon.subweaponId];
    if (g_Player.timers[PL_T_INVINCIBLE_SCENE]) {
        entity->attack = subwpn->attack * 2;
    } else {
        entity->attack = subwpn->attack;
    }
    entity->attackElement = subwpn->attackElement;
    entity->hitboxState = subwpn->hitboxState;
    entity->nFramesInvincibility = subwpn->nFramesInvincibility;
    entity->stunFrames = subwpn->stunFrames;
    entity->hitEffect = subwpn->hitEffect;
    entity->entityRoomIndex = subwpn->entityRoomIndex;
    entity->attack = func_800FD664(entity->attack);
    func_8015F9F0(entity);
}

// RicCheckSubweapon
s32 func_8015FB84(SubweaponDef* actualSubwpn, s32 isItemCrash, s32 useHearts) {
    SubweaponDef* subwpn;

    if (isItemCrash == 0) {
        *actualSubwpn = ric_subweapons_def[g_Status.subWeapon];
        if (g_Status.hearts >= actualSubwpn->heartCost) {
            if (useHearts) {
                g_Status.hearts -= actualSubwpn->heartCost;
            }
            return g_Status.subWeapon;
        }
        return -1;
    }
    subwpn = &ric_subweapons_def[g_Status.subWeapon];
    *actualSubwpn = ric_subweapons_def[subwpn->crashId];
    if (g_Status.hearts >= actualSubwpn->heartCost) {
        if (useHearts) {
            g_Status.hearts -= actualSubwpn->heartCost;
        }
        return g_Status.subWeapon;
    }
    return -1;
}

s32 func_8015FDB0(RicPrimitive* prim, s16 posX, s16 posY) {
    s16 offset;
    s16 xOffset;
    u16* ptr;
    u8 frame = prim->frame;

    if (frame >= 3) {
        offset = 4;
    } else {
        offset = 6;
    }

    if (frame == 6) {
        return -1;
    }

    xOffset = offset | 1;
    prim->x0 = posX - xOffset;
    prim->y0 = posY - offset;
    prim->x1 = posX + xOffset;
    prim->y1 = posY + offset;

    ptr = DAT_0605AEC0[g_RichterSpritePackage3AllocationIndex +
                       D_060BF1A4[frame]];
    prim->uv0 = ptr[0];
    prim->uv1 = ptr[1];

    prim->timer++;
    if (!(prim->timer & 1)) {
        prim->frame++;
    }
    return 0;
}

extern Point16 D_80174FBC[16];

void RicEntityHitByHoly(Entity* entity) {
    RicPrimitive* prim;
    s32 i;
    s32 temp;
    s16 hitboxX;
    s16 hitboxY;
    s16 temp_xRand;
    s16 temp_yRand;

    switch (entity->step) {
    case 0:
        entity->primIndex = (s16)AllocPrimitives(1, LEN(D_80174FBC));
        if (entity->primIndex == -1) {
            DestroyEntity(entity);
            return;
        }
        entity->flags =
            FLAG_HAS_PRIMS | FLAG_POS_PLAYER_LOCKED | FLAG_UNK_20000;
        hitboxX = PLAYER.posX.i.hi + PLAYER.hitboxOffX;
        hitboxY = PLAYER.posY.i.hi + PLAYER.hitboxOffY;
        prim = (RicPrimitive*)&g_PrimBuf[entity->primIndex];
        for (i = 0; i < LEN(D_80174FBC); i++) {
            temp_xRand = hitboxX + MTH_GetRand() % 24 - 12;
            temp_yRand = hitboxY + MTH_GetRand() % 48 - 24;
            D_80174FBC[i].x = temp_xRand;
            D_80174FBC[i].y = temp_yRand;
            prim->unk6 =
                LookupTblNoToVram(g_RichterSpriteResources[1].flags + 13);
            prim->frame = 0;
            prim->timer = 0;
            prim->x3 = 0;
            prim->y3 = (MTH_GetRand() & 7) + 1;
            prim->priority = PLAYER.zPriority + 4;
            prim->drawMode = DRAW_UNK_100 | DRAW_TPAGE | DRAW_HIDE |
                             DRAW_UNK02 | DRAW_TRANSP;
            if (MTH_GetRand() & 1) {
                prim->drawMode =
                    DRAW_UNK_100 | DRAW_UNK_40 | DRAW_TPAGE2 | DRAW_TPAGE |
                    DRAW_HIDE | DRAW_UNK02 | DRAW_TRANSP;
            }
            prim = (RicPrimitive*)prim->next;
        }
        entity->step++;
        break;
    case 1:
        if (!(g_Player.status & PLAYER_STATUS_UNK10000)) {
            DestroyEntity(entity);
            return;
        }
        break;
    }

    prim = (RicPrimitive*)&g_PrimBuf[entity->primIndex];
    for (i = 0; i < 16; i++) {
        switch (prim->x3) {
        case 0:
            if (--prim->y3 == 0) {
                prim->x3++;
            }
            break;
        case 1:
            hitboxX = D_80174FBC[i].x;
            hitboxY = D_80174FBC[i].y;
            temp = func_8015FDB0(prim, hitboxX, hitboxY);
            D_80174FBC[i].y--;
            if (temp < 0) {
                prim->drawMode |= DRAW_HIDE;
                prim->x3++;
            } else {
                prim->drawMode &= ~DRAW_HIDE;
            }
            break;
        }
        prim = (RicPrimitive*)prim->next;
    }
}

extern s32 D_80174FFC;
extern AnimationFrame anim_smoke_dark[];

void RicEntityHitByDark(Entity* entity) {
    switch (entity->step) {
    case 0:
        entity->unk0 = CreateSpriteObject(
            g_SaturnSharedSpriteBank7Resource.allocationIndex,
            g_SaturnSharedSpriteBank7Resource.flags,
            g_SaturnSharedSpriteBank7Resource.images, 2);
        if (entity->unk0 == NULL) {
            DestroyEntity(entity);
            return;
        }
        entity->ext.spriteEntity.frames = g_SaturnSharedOpaquePuffFrames0;
        entity->unk0->zPriority = PLAYER.zPriority + 2;
        entity->flags =
            FLAG_UNK_20000 | FLAG_UNK_100000 | FLAG_POS_CAMERA_LOCKED;
        entity->unk56 = 0x79;
        entity->animSet = 14;
        entity->palette = 0x819F;
        if (D_80174FFC & 1) {
            entity->unk1C = 0x70;
        } else {
            entity->unk1C = 0x10;
        }
        D_80174FFC++;
        entity->opacity = 0xFF;
        entity->drawFlags =
            ENTITY_SCALEX | ENTITY_SCALEY | ENTITY_MASK_R | ENTITY_MASK_G;
        entity->scaleX = entity->scaleY = 0x40;
        entity->anim = anim_smoke_dark;
        entity->posY.i.hi += (MTH_GetRand() % 35) - 15;
        entity->posX.i.hi += (MTH_GetRand() % 20) - 10;
        entity->velocityY = -0x6000 - (MTH_GetRand() & 0x3FFF);
        entity->step++;
        break;
    case 1:
        if (entity->opacity > 16) {
            entity->opacity -= 8;
        }
        entity->posY.val += entity->velocityY;
        entity->scaleX += 8;
        entity->scaleY += 8;
        if (entity->poseTimer < 0) {
            DestroyEntity(entity);
        }
        break;
    }
}

extern PfnEntityUpdate entity_functions[];
extern AnimationFrame* g_RicEmptyAnimGroup[];

void RicUpdatePlayerEntities(void) {
    SubweaponDef subwpn;
    s32 isPrologueTimeStopped;
    s32 enemyId;
    s32 i;
    s32 j;
    Entity* entity;

    isPrologueTimeStopped = g_unkGraphicsStruct.unk28;
    entity = g_CurrentEntity = &g_Entities[4];
    for (i = 4; i < 64; i++, g_CurrentEntity++, entity++) {
        if (entity->entityId != 0) {
            if (entity->step == 0) {
                entity->pfnUpdate = entity_functions[entity->entityId];
            }
            if (!isPrologueTimeStopped || (entity->flags & FLAG_UNK_10000)) {
                entity->pfnUpdate(entity);
                entity = g_CurrentEntity;
                if (entity->entityId != 0) {
                    if (!(entity->flags & FLAG_KEEP_ALIVE_OFFCAMERA) &&
                        (entity->posX.i.hi > 344 || entity->posX.i.hi < -24 ||
                         entity->posY.i.hi > 256 || entity->posY.i.hi < -16)) {
                        DestroyEntity(g_CurrentEntity);
                    } else if (entity->flags & FLAG_UNK_100000) {
                        func_060AA194(0, g_RicEmptyAnimGroup);
                    }
                }
            }
        }
    }
    if (D_80174FAC) {
        D_80174FAC--;
        if (D_80174FAC & 1) {
            func_800EA5AC(1, D_80174FB0, D_80174FB4, D_80174FB8);
        }
    }
    D_80174F80[1] = D_80174F80[2] = 0;
    if (g_Entities[E_WEAPON].enemyId == 1) {
        D_80174F80[1] = 1;
    } else if (g_Entities[E_WEAPON].enemyId == 2) {
        D_80174F80[2] = 1;
    }
    for (j = 3; j < 11; j++) {
        D_80174F80[j] = 0;
    }
    entity = &g_Entities[17];
    for (j = 17; j < 48; entity++, j++) {
        enemyId = entity->enemyId;
        if (enemyId > 2) {
            D_80174F80[enemyId]++;
        }
    }
    // This IF will fire if we have enough hearts to use a subweapon crash.
    // No idea what it's doing here.
    if (func_8015FB84(&subwpn, true, false) >= 0) {
        g_Player.status |= PLAYER_STATUS_UNK200000;
    }
    if (g_Player.status & (PLAYER_STATUS_DEAD | PLAYER_STATUS_UNK80000)) {
        entity = &g_Entities[4];
        for (i = 4; i < 64; i++, entity++) {
            entity->hitboxState = 0;
        }
    }
}

// Runs the update function of every non-player entity slot.
void func_060AC2DC(void) {
    Entity* entity;
    s32 i;

    if (PLAYER.unk0 != NULL) {
        g_CurrentEntity = entity = &g_Entities[UNK_ENTITY_4];
        i = UNK_ENTITY_4;
        do {
            if (!(entity->flags & FLAG_UNK_20000)) {
                DestroyEntity(entity);
            }
            if ((entity->flags & FLAG_UNK_02000000) && (entity->step != 0)) {
                entity->flags |= FLAG_UNK_00200000;
                entity->pfnUpdate(entity);
                entity->flags &= ~FLAG_UNK_00200000;
            }
            i++;
            g_CurrentEntity++;
            entity++;
        } while (i <= 0x3F);
        // prevent inline
        DisableAfterImage(1, 3);
    }
}

Entity* RicCreateEntFactoryFromEntity(
    Entity* source, u32 factoryParams, s32 arg2) {
    Entity* entity;
    Entity* current;
    s16 i;
    s16 end = 16;

    current = &g_Entities[8];
    for (i = 8; i < end; i++, current++) {
        if (current->entityId == E_NONE) {
            entity = current;
            goto found;
        }
    }
    entity = NULL;
found:
    if (!entity) {
        return NULL;
    }
    DestroyEntity(entity);
    entity->entityId = 1;
    entity->ext.factory.parent = source;
    entity->posX.val = source->posX.val;
    entity->posY.val = source->posY.val;
    entity->facingLeft = source->facingLeft;
    entity->zPriority = source->zPriority;
    entity->params = factoryParams & 0xFFF;
    entity->ext.factory.paramsBase = (factoryParams & 0xFF0000) >> 8;
    if (source->flags & FLAG_POS_CAMERA_LOCKED) {
        entity->flags |= FLAG_POS_CAMERA_LOCKED;
    }
    if (source->flags & FLAG_UNK_10000) {
        entity->flags |= FLAG_UNK_10000;
    }
    return entity;
}

extern u8 blueprints[][6];
extern u8 entity_ranges[NUM_BLUEPRINT_KIND][2];

void RicEntityFactory(Entity* self) {
    Entity* newEntity;
    s16 nPerCycle;
    s16 i;
    s16 startIndex;
    s16 endIndex;
    u8* data;

    if (self->step == 0) {
        data = blueprints[self->params];
        self->ext.factory.newEntityId = *data++;
        self->ext.factory.amount = *data++;
        self->ext.factory.nPerCycle = *data & 0x3F;
        self->ext.factory.isNonCritical = (s16)(*data >> 7) & 1;
        self->ext.factory.incParamsKind = (s16)(*data++ >> 6) & 1;
        self->ext.factory.tCycle = *data++;
        self->ext.factory.kind = *data & 0x7;
        self->ext.factory.origin = (s16)(*data++ >> 3) & 0x1F;
        self->ext.factory.delay = *data;
        self->flags |= FLAG_KEEP_ALIVE_OFFCAMERA;
        self->step++;
        self->flags &= ~FLAG_POS_CAMERA_LOCKED;
        switch (self->ext.factory.origin) {
        case B_ORIGIN_DEFAULT:
            self->flags |= FLAG_POS_CAMERA_LOCKED;
            break;
        case B_ORIGIN_FOLLOW_PLAYER_WHILE_PLAYER_IS_RUNNING:
        case B_ORIGIN_SUBWEAPON_CRASH_PARTICLE:
        case B_ORIGIN_10:
            self->flags |= FLAG_UNK_20000;
        case B_ORIGIN_FOLLOW_PLAYER:
            self->flags |= FLAG_POS_PLAYER_LOCKED;
        case B_ORIGIN_FOLLOW_PLAYER_WHILE_PLAYER_IS_HIT:
        case B_ORIGIN_FOLLOW_PLAYER_WHILE_PLAYER_IS_NOT_HIT:
            self->posX.val = PLAYER.posX.val;
            self->posY.val = PLAYER.posY.val;
            break;
        case B_ORIGIN_FOLLOW_PARENT_ENTITY:
            self->flags |= FLAG_POS_PLAYER_LOCKED;
            self->posX.val = self->ext.factory.parent->posX.val;
            self->posY.val = self->ext.factory.parent->posY.val;
            break;
        }
    } else {
        switch (self->ext.factory.origin) {
        case B_ORIGIN_DEFAULT:
            break;
        case B_ORIGIN_SUBWEAPON_CRASH_PARTICLE:
            if (g_Player.unk4E) {
                DestroyEntity(self);
                return;
            }
        case B_ORIGIN_FOLLOW_PLAYER:
        case B_ORIGIN_10:
            self->posX.val = PLAYER.posX.val;
            self->posY.val = PLAYER.posY.val;
            break;
        case B_ORIGIN_FOLLOW_PLAYER_WHILE_PLAYER_IS_RUNNING:
            self->posX.val = PLAYER.posX.val;
            self->posY.val = PLAYER.posY.val;
            if (PLAYER.step != PL_S_RUN) {
                self->entityId = 0;
                return;
            }
            break;
        case B_ORIGIN_FOLLOW_PLAYER_WHILE_PLAYER_IS_HIT:
            self->posX.val = PLAYER.posX.val;
            self->posY.val = PLAYER.posY.val;
            if (PLAYER.step == PL_S_HIT) {
                self->entityId = 0;
                return;
            }
            break;
        case B_ORIGIN_FOLLOW_PLAYER_WHILE_PLAYER_IS_NOT_HIT:
            self->posX.val = PLAYER.posX.val;
            self->posY.val = PLAYER.posY.val;
            if (PLAYER.step != PL_S_HIT) {
                self->entityId = 0;
                return;
            }
            break;
        case B_ORIGIN_FOLLOW_PARENT_ENTITY:
            self->posX.val = self->ext.factory.parent->posX.val;
            self->posY.val = self->ext.factory.parent->posY.val;
            break;
        }
    }
    if (self->ext.factory.delay) {
        if (--self->ext.factory.delay) {
            return;
        }
        self->ext.factory.delay = self->ext.factory.tCycle;
    }
    nPerCycle = self->ext.factory.nPerCycle;
    for (i = 0; i < nPerCycle; i++) {
        data = entity_ranges[0];
        data += self->ext.factory.kind * 2;
        startIndex = *data++;
        endIndex = *data;
        if (self->ext.factory.kind == B_DECORATION) {
            newEntity = RicGetFreeEntityReverse(startIndex, endIndex + 1);
        } else if (self->ext.factory.kind == B_WHIP) {
            newEntity = &g_Entities[31];
        } else if (self->ext.factory.kind == B_CUTSCENE_MARIA) {
            newEntity = &g_Entities[48];
        } else {
            newEntity = RicGetFreeEntity(startIndex, endIndex + 1);
        }
        if (newEntity == NULL) {
            if (self->ext.factory.isNonCritical == 1) {
                self->entityId = 0;
            } else {
                self->ext.factory.delay = self->ext.factory.tCycle;
            }
            return;
        }
        DestroyEntity(newEntity);
        newEntity->entityId =
            self->ext.factory.newEntityId + self->ext.factory.entityIdMod;
        newEntity->params = self->ext.factory.paramsBase;
        newEntity->ext.factory.parent = self->ext.factory.parent;
        newEntity->posX.val = self->posX.val;
        newEntity->posY.val = self->posY.val;
        newEntity->facingLeft = self->facingLeft;
        newEntity->zPriority = self->zPriority;
        if (self->flags & FLAG_UNK_10000) {
            newEntity->flags |= FLAG_UNK_10000;
        }
        if (self->ext.factory.incParamsKind) {
            newEntity->params += self->ext.factory.spawnIndex;
        } else {
            newEntity->params += i;
        }
        self->ext.factory.spawnIndex++;
        if (self->ext.factory.spawnIndex == self->ext.factory.amount) {
            self->entityId = 0;
            return;
        }
    }
    self->ext.factory.delay = self->ext.factory.tCycle;
}

void RicEntitySlideKick(Entity* entity) {
    void RicSetSubweaponParams(Entity * entity);

    if (PLAYER.step != PL_S_SLIDE) {
        DestroyEntity(entity);
    } else {
        entity->posX.i.hi = PLAYER.posX.i.hi;
        entity->posY.i.hi = PLAYER.posY.i.hi;
        entity->facingLeft = PLAYER.facingLeft;
        if (entity->step == 0) {
            entity->flags = FLAG_UNK_20000 | FLAG_POS_PLAYER_LOCKED |
                            FLAG_KEEP_ALIVE_OFFCAMERA;
            entity->hitboxOffX = 25;
            entity->hitboxOffY = 12;
            entity->hitboxWidth = 11;
            entity->hitboxHeight = 9;
            entity->ext.subweapon.subweaponId = PL_W_KICK;
            RicSetSubweaponParams(entity);
            entity->ext.subweapon.timer = entity->hitboxState;
            entity->step++;
        }
        entity->hitboxState = entity->ext.subweapon.timer;
        if (PLAYER.pose < 2) {
            entity->hitboxState = 0;
        }
        if (PLAYER.pose > 7) {
            DestroyEntity(entity);
        }
    }
}

// func_80160D2C
void func_060AC908(Entity* entity) {
    if (PLAYER.step != PL_S_SLIDE_KICK) {
        DestroyEntity(entity);
        return;
    }
    entity->posX.i.hi = PLAYER.posX.i.hi;
    entity->posY.i.hi = PLAYER.posY.i.hi;
    entity->facingLeft = PLAYER.facingLeft;
    if (entity->step == 0) {
        entity->flags =
            FLAG_UNK_20000 | FLAG_POS_PLAYER_LOCKED | FLAG_KEEP_ALIVE_OFFCAMERA;
        entity->hitboxOffX = 25;
        entity->hitboxWidth = 11;
        entity->hitboxHeight = 9;
        entity->ext.subweapon.subweaponId = 23;
        func_060ABA98(entity);
        entity->step++;
    }

    if (PLAYER.animCurFrame == 140) {
        entity->hitboxOffY = 0;
    }

    if (PLAYER.animCurFrame == 141) {
        entity->hitboxOffY = 12;
    }

    if (entity->hitFlags) {
        g_Player.unk44 |= 0x80;
    } else {
        g_Player.unk44 &= ~0x80;
    }
    entity->hitFlags = 0;
}

void RicEntityBladeDash(Entity* self) {
    void RicSetSubweaponParams(Entity * entity);

    if (PLAYER.step != PL_S_BLADEDASH) {
        DestroyEntity(self);
    } else {
        self->posX.i.hi = PLAYER.posX.i.hi;
        self->posY.i.hi = PLAYER.posY.i.hi;
        self->facingLeft = PLAYER.facingLeft;
        if (self->step == 0) {
            self->flags = FLAG_UNK_20000 | FLAG_POS_PLAYER_LOCKED |
                          FLAG_KEEP_ALIVE_OFFCAMERA;
            self->hitboxOffX = self->hitboxOffY = 0;
            self->hitboxWidth = 25;
            self->hitboxHeight = 20;
            self->ext.subweapon.subweaponId = 17;
            RicSetSubweaponParams(self);
            self->step++;
        }
        if (PLAYER.pose > 18) {
            DestroyEntity(self);
        }
    }
}

void func_80160F0C(Entity* self) {
    void RicSetSubweaponParams(Entity * entity);

    if (PLAYER.step != PL_S_HIGHJUMP) {
        DestroyEntity(self);
        return;
    }
    self->posX.i.hi = PLAYER.posX.i.hi;
    self->posY.i.hi = PLAYER.posY.i.hi;
    self->facingLeft = PLAYER.facingLeft;
    if (self->step == 0) {
        self->flags =
            FLAG_UNK_20000 | FLAG_POS_PLAYER_LOCKED | FLAG_KEEP_ALIVE_OFFCAMERA;
        self->hitboxOffX = 15;
        self->hitboxOffY = -26;
        self->hitboxWidth = 15;
        self->hitboxHeight = 12;
        self->ext.subweapon.subweaponId = PL_W_HIGHJUMP;
        RicSetSubweaponParams(self);
        self->step++;
    }
}

const u16 pad_60ACB6C[] = {0x8888, 0x8889};

// RicEntitySmokePuff
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60ACB70, func_060ACB70);

// RicEntityHitByCutBlood
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60ACFA0, func_060ACFA0);

extern AnimationFrame anim_80154E04[];
extern AnimationFrame anim_80154DC8[];
extern AnimationFrame anim_smoke_puff[];
extern SaturnSpriteFrameHeader* g_SaturnSharedSpriteBank5Frames[];

void func_80161C2C(Entity* self) {
    s16 paramsHi;
    s16 paramsLo;

    paramsLo = self->params & 0xFF;
    paramsHi = (self->params >> 8) & 0xFF;
    switch (self->step) {
    case 0:
        if (paramsHi == 1) {
            self->scaleX = 0xC0;
            self->scaleY = 0xC0;
            self->drawFlags = ENTITY_SCALEX | ENTITY_SCALEY;
            self->animSet = 2;
            self->anim = anim_80154E04;
        } else if (paramsLo & 3) {
            self->anim = anim_80154DC8;
            self->scaleX = 0x120;
            self->scaleY = 0x120;
            self->drawFlags = ENTITY_SCALEX | ENTITY_SCALEY;
            self->animSet = 2;
        } else {
            self->unk0 = CreateSpriteObject(
                g_SaturnSharedSpriteBank5Resource.allocationIndex,
                g_SaturnSharedSpriteBank5Resource.flags,
                g_SaturnSharedSpriteBank5Resource.images, 1);
            if (self->unk0 == NULL) {
                DestroyEntity(self);
                return;
            }
            // likely a typo of an assignment in the original source
            self->scaleX = self->scaleY == 0x100;
            self->ext.spriteEntity.frames = g_SaturnSharedSpriteBank5Frames;
            self->animSet = 5;
            self->anim = anim_smoke_puff;
            self->palette = 0x8170;
        }
        if (self->unk0 == NULL) {
            self->unk0 = CreateSpriteObject(
                g_SaturnSharedSpriteBank1Resource.allocationIndex,
                g_SaturnSharedSpriteBank1Resource.flags,
                g_SaturnSharedSpriteBank1Resource.images, 5);
            if (self->unk0 == NULL) {
                DestroyEntity(self);
                return;
            }
            self->ext.spriteEntity.frames = g_SaturnSharedSpriteBank1Frames;
        }
        self->flags = FLAG_UNK_20000 | FLAG_UNK_100000 | FLAG_POS_CAMERA_LOCKED;
        if (MTH_GetRand() & 3) {
            self->unk0->zPriority = PLAYER.zPriority + 2;
        } else {
            self->unk0->zPriority = PLAYER.zPriority - 2;
        }
        if (paramsHi == 2) {
            self->posX.i.hi = PLAYER.posX.i.hi + (MTH_GetRand() % 44) - 22;
        } else {
            self->posX.i.hi = PLAYER.posX.i.hi + (MTH_GetRand() & 15) - 8;
        }
        self->posY.i.hi =
            PLAYER.posY.i.hi + PLAYER.hitboxOffY + (MTH_GetRand() & 31) - 16;
        self->velocityY = FIX(-0.5);
        self->velocityX = PLAYER.velocityX >> 2;
        self->step++;
        break;
    case 1:
        self->scaleX -= 4;
        self->scaleY -= 4;
        self->posY.val += self->velocityY;
        self->posX.val += self->velocityX;
        if ((self->pose == 8) && (self->anim != anim_smoke_puff)) {
            self->unk1C = 0x10;
            if (!(paramsLo & 1) && self->poseTimer == 1) {
                RicCreateEntFactoryFromEntity(self, FACTORY(BP_EMBERS, 4), 0);
            }
        }
        if (self->pose == 16 && self->anim == anim_smoke_puff) {
            self->unk1C = 0x10;
        }
        if (self->poseTimer < 0) {
            DestroyEntity(self);
        }
        break;
    }
}

// func_80161EF8
void func_060ADA34(Entity* self) {
    switch (self->step) {
    case 0:
        self->unk0 = CreateSpriteObject(
            g_SaturnSharedSpriteBank1Resource.allocationIndex,
            g_SaturnSharedSpriteBank1Resource.flags,
            g_SaturnSharedSpriteBank1Resource.images, 5);
        if (self->unk0 != NULL) {
            self->ext.spriteEntity.frames = g_SaturnSharedSpriteBank1Frames;
            self->unk0->zPriority = g_Entities->zPriority + 4;
            self->animSet = 2;
            self->anim = anim_80154E38;
            self->flags = 0x170000;
            self->velocityY = (MTH_GetRand() & 0x3FFF) - FIX(1);
            self->step++;
        } else {
            DestroyEntity(self);
        }
        break;

    case 1:
        if (self->pose == 6) {
            if (self->poseTimer == 1 && (MTH_GetRand() & 1)) {
                RicCreateEntFactoryFromEntity(self, 4, 0);
            }
        }
        self->posY.val += self->velocityY;
        if (self->poseTimer < 0) {
            DestroyEntity(self);
        }
        break;
    }
}

extern RicMariaPowerProperties D_80154E5C[];

void RicEntityApplyMariaPowerAnim(Entity* self) {
    Primitive* prim;
    s16 posX;
    s16 posY;
    s16 params;
    RicMariaPowerProperties* props;
    u16* uv;

    posX = self->posX.i.hi;
    posY = self->posY.i.hi;
    params = self->params;
    props = &D_80154E5C[params];
    switch (self->step) {
    case 0:
        self->primIndex = AllocPrimitives(1, 1);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        PlaySfx(0x582);
        self->ext.ricMariaPower.size = 0x100;
        prim = &g_PrimBuf[self->primIndex];
        uv = DAT_0605AEC0[g_RichterSpritePackage10Resource.allocationIndex +
                          props->textureIndex];
        prim->unk8 = uv[0];
        prim->unkA = uv[1];
        prim->unk6 = LookupTblNoToVram(
            g_RichterSpritePackage10Resource.flags + props->paletteIndex);
        prim->priority = PLAYER.zPriority + 8;
        prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_TRANSP;
        self->velocityX = props->velocityX;
        self->velocityY = props->velocityY;
        posX = self->posX.i.hi += props->xOffset;
        posY = self->posY.i.hi += props->yOffset;
        self->flags =
            FLAG_KEEP_ALIVE_OFFCAMERA | FLAG_HAS_PRIMS | FLAG_UNK_10000;
        self->step++;
        break;
    case 1:
        self->ext.ricMariaPower.size -= 8;
        self->posX.val += self->velocityX;
        self->posY.val += self->velocityY;
        if (self->ext.ricMariaPower.size < 25) {
            self->ext.ricMariaPower.timer = props->timer;
            self->step++;
        }
        break;
    case 2:
        if (--self->ext.ricMariaPower.timer == 0) {
            self->step++;
        }
        break;
    case 3:
        self->ext.ricMariaPower.size -= 2;
        if (self->ext.ricMariaPower.size < 0) {
            DestroyEntity(self);
            return;
        }
        break;
    }
    prim = &g_PrimBuf[self->primIndex];
    prim->x0 =
        posX + (((rcos(0x600) >> 4) * self->ext.ricMariaPower.size) >> 8);
    prim->y0 =
        posY - (((rsin(0x600) >> 4) * self->ext.ricMariaPower.size) >> 8);
    prim->x1 =
        posX + (((rcos(0x200) >> 4) * self->ext.ricMariaPower.size) >> 8);
    prim->y1 =
        posY - (((rsin(0x200) >> 4) * self->ext.ricMariaPower.size) >> 8);
    prim->x3 =
        posX + (((rcos(0xA00) >> 4) * self->ext.ricMariaPower.size) >> 8);
    prim->y3 =
        posY - (((rsin(0xA00) >> 4) * self->ext.ricMariaPower.size) >> 8);
    prim->x2 =
        posX + (((rcos(0xE00) >> 4) * self->ext.ricMariaPower.size) >> 8);
    prim->y2 =
        posY - (((rsin(0xE00) >> 4) * self->ext.ricMariaPower.size) >> 8);
}

void func_801623E0(Entity* self) {
    Primitive* prim;
    u16* uv;

    self->posX.val = PLAYER.posX.val;
    self->posY.val = PLAYER.posY.val;
    switch (self->step) {
    case 0:
        self->primIndex = AllocPrimitives(1, 1);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->ext.circleExpand.width = self->ext.circleExpand.height = 32;
        prim = &g_PrimBuf[self->primIndex];
        uv = DAT_0605AEC0[g_RichterSpritePackage5Resource.allocationIndex + 1];
        prim->unk8 = uv[0];
        prim->unkA = uv[1];
        prim->unk6 =
            LookupTblNoToVram(g_RichterSpritePackage5Resource.flags + 1);
        prim->priority = PLAYER.zPriority + 8;
        prim->drawMode = DRAW_DEFAULT;
        self->flags = FLAG_UNK_10000 | FLAG_POS_PLAYER_LOCKED |
                      FLAG_KEEP_ALIVE_OFFCAMERA | FLAG_HAS_PRIMS;
        self->step++;
        break;

    case 1:
        self->ext.circleExpand.width++;
        self->ext.circleExpand.height++;
        if (self->ext.circleExpand.width > 44) {
            DestroyEntity(self);
            return;
        }
        break;
    }

    prim = &g_PrimBuf[self->primIndex];
    prim->x0 = self->posX.i.hi - self->ext.circleExpand.width;
    prim->y0 = self->posY.i.hi - self->ext.circleExpand.height;
    prim->x1 = self->posX.i.hi + self->ext.circleExpand.width;
    prim->y1 = self->posY.i.hi - self->ext.circleExpand.height;
    prim->x3 = self->posX.i.hi - self->ext.circleExpand.width;
    prim->y3 = self->posY.i.hi + self->ext.circleExpand.height;
    prim->x2 = self->posX.i.hi + self->ext.circleExpand.width;
    prim->y2 = self->posY.i.hi + self->ext.circleExpand.height;
}

void func_80162604(Entity* self) {
    Primitive* prim;
    u16* uv;

    self->posX.val = PLAYER.posX.val;
    self->posY.val = PLAYER.posY.val;
    switch (self->step) {
    case 0:
        self->primIndex = AllocPrimitives(1, 1);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->ext.circleExpand.width = self->ext.circleExpand.height = 0;
        prim = &g_PrimBuf[self->primIndex];
        uv = DAT_0605AEC0[g_RichterSpritePackage5Resource.allocationIndex + 1];
        prim->unk8 = uv[0];
        prim->unkA = uv[1];
        prim->unk6 =
            LookupTblNoToVram(g_RichterSpritePackage5Resource.flags + 1);
        prim->priority = PLAYER.zPriority - 4;
        prim->drawMode = DRAW_DEFAULT;
        self->flags = FLAG_UNK_10000 | FLAG_POS_PLAYER_LOCKED |
                      FLAG_KEEP_ALIVE_OFFCAMERA | FLAG_HAS_PRIMS;
        self->step++;
        break;
    case 1:
        self->ext.circleExpand.width += 8;
        self->ext.circleExpand.height += 8;
        if (self->ext.circleExpand.width >= 0x20) {
            self->step++;
        }
        break;
    case 2:
        self->step++;
        break;
    case 3:
        self->ext.circleExpand.width -= 8;
        self->ext.circleExpand.height -= 8;
        if (self->ext.circleExpand.width < 5) {
            DestroyEntity(self);
            return;
        }
        break;
    }
    prim = &g_PrimBuf[self->primIndex];
    prim->x0 = self->posX.i.hi - self->ext.circleExpand.width;
    prim->y0 = self->posY.i.hi - self->ext.circleExpand.height;
    prim->x1 = self->posX.i.hi + self->ext.circleExpand.width;
    prim->y1 = self->posY.i.hi - self->ext.circleExpand.height;
    prim->x3 = self->posX.i.hi - self->ext.circleExpand.width;
    prim->y3 = self->posY.i.hi + self->ext.circleExpand.height;
    prim->x2 = self->posX.i.hi + self->ext.circleExpand.width;
    prim->y2 = self->posY.i.hi + self->ext.circleExpand.height;
}

extern u16 D_80154EAC[];
extern s32 D_80154EB4[];
extern s32 D_80154EC4[];

void RicEntityMariaPowers(Entity* self) {
    Primitive* prim;
    s16 params;
    u16* uv;

    params = self->params;
    switch (self->step) {
    case 0:
        self->primIndex = AllocPrimitives(1, 1);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->unk0 = CreateSpriteObject(
            g_RichterSpritePackage9Resource.allocationIndex,
            g_RichterSpritePackage9Resource.flags,
            g_RichterSpritePackage9Images, 2);
        if (self->unk0 == NULL) {
            DestroyEntity(self);
            return;
        }
        self->ext.spriteEntity.frames = g_RichterSpritePackage9Frames;
        self->unk0->zPriority = PLAYER.zPriority - 12;
        self->unk56 = 0x66;
        self->palette = params + 0x149;
        self->animSet = 0x8013;
        self->animCurFrame = params + 0x19;
        self->velocityX = D_80154EB4[params];
        self->velocityY = D_80154EC4[params];
        self->ext.et_80162870.unk7C = self->ext.et_80162870.unk7E =
            self->ext.et_80162870.unk80 = 8;

        prim = &g_PrimBuf[self->primIndex];
        uv = DAT_0605AEC0[g_RichterSpritePackage3AllocationIndex + 13];
        prim->unk8 = uv[0];
        prim->unkA = uv[1];
        prim->unk6 = LookupTblNoToVram(
            g_RichterSpritePackage9Resource.flags + D_80154EAC[params]);
        prim->priority = PLAYER.zPriority - 16;
        prim->drawMode = DRAW_HIDE;
        self->flags = FLAG_HAS_PRIMS | FLAG_UNK_10000;
        if (params == 3) {
            self->flags |= FLAG_KEEP_ALIVE_OFFCAMERA;
        }
        PlaySfx(0x582);
        self->ext.et_80162870.unk82 = 12;
        self->step++;
        break;
    case 1:
        self->posX.val += self->velocityX;
        self->posY.val += self->velocityY;
        if (--self->ext.et_80162870.unk82 == 0) {
            self->drawFlags = ENTITY_SCALEY | ENTITY_SCALEX;
            self->scaleX = self->scaleY = 0x100;
            self->ext.et_80162870.unk82 = 0x10;
            self->step++;
            prim = &g_PrimBuf[self->primIndex];
            prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_TRANSP;
        }
        break;
    case 2:
        self->scaleX = self->scaleY = self->ext.et_80162870.unk82 * 0x10;
        if (--self->ext.et_80162870.unk82 == 0) {
            self->animCurFrame = 0;
            PlaySfx(0x69D);
            self->step++;
            self->velocityY = FIX(-9);
        }
        break;
    case 3:
        self->posY.val += self->velocityY;
        if (self->ext.et_80162870.unk7C > 0 && !(g_Timer & 1)) {
            self->ext.et_80162870.unk7C--;
        }
        if (!(g_Timer & 1)) {
            self->ext.et_80162870.unk7E++;
        }
        self->ext.et_80162870.unk80 += 2;
        if ((params == 3) && (self->posY.i.hi < -0x20)) {
            D_801545AC = 8;
            DestroyEntity(self);
            return;
        }
        break;
    }
    prim = &g_PrimBuf[self->primIndex];
    prim->x0 = self->posX.i.hi - self->ext.et_80162870.unk7C;
    prim->y0 = self->posY.i.hi - self->ext.et_80162870.unk7E;
    prim->x1 = self->posX.i.hi + self->ext.et_80162870.unk7C;
    prim->y1 = self->posY.i.hi - self->ext.et_80162870.unk7E;
    prim->x3 = self->posX.i.hi - self->ext.et_80162870.unk7C;
    prim->y3 = self->posY.i.hi + self->ext.et_80162870.unk80;
    prim->x2 = self->posX.i.hi + self->ext.et_80162870.unk7C;
    prim->y2 = self->posY.i.hi + self->ext.et_80162870.unk80;
    UpdateEntitySprite(self);
}

s32 DestroyEntity();

void func_060AE538(void) { DestroyEntity(); }

extern AnimationFrame anim_maria_walk[];
extern AnimationFrame anim_maria_offering_powers[];

void RicEntityMaria(Entity* self) {
    switch (self->step) {
    case 0:
        self->unk0 = CreateSpriteObject(
            g_RichterSpritePackage9Resource.allocationIndex,
            g_RichterSpritePackage9Resource.flags,
            g_RichterSpritePackage9Images, 2);
        if (self->unk0 == NULL) {
            DestroyEntity(self);
            return;
        }
        self->ext.spriteEntity.frames = g_RichterSpritePackage9Frames;
        self->unk0->zPriority = PLAYER.zPriority - 8;
        self->flags = FLAG_UNK_100000 | FLAG_KEEP_ALIVE_OFFCAMERA |
                      FLAG_UNK_10000 | FLAG_POS_CAMERA_LOCKED;
        self->facingLeft = 1;
        self->unk56 = 0x66;
        self->zPriority = PLAYER.zPriority - 8;
        self->palette = 0x8149;
        self->animSet = 0x8013;
        RicSetAnimation(anim_maria_walk);
        self->velocityX = FIX(-2.1875);
        self->posY.i.hi = 0xBB;
        self->posX.i.hi = 0x19A;
        self->ext.ricMaria.boolDidSound = 0;
        self->step++;
        break;
    case 1:
        if (self->pose == 0 && self->poseTimer == 1) {
            PlaySfx(0x586);
        }
        self->posX.val += self->velocityX;
        if ((self->ext.ricMaria.boolDidSound == false) &&
            (self->posX.i.hi < 320)) {
            self->ext.ricMaria.boolDidSound++;
        }
        if (self->posX.i.hi < 0x118) {
            RicSetAnimation(anim_maria_offering_powers);
            self->step++;
            self->velocityX = 0;
            RicCreateEntFactoryFromEntity(self, FACTORY(BP_SKID_SMOKE, 4), 0);
        }
        break;
    case 2:
        if (self->pose == 16) {
            PlaySfx(0x584);
            self->ext.ricMaria.timer = 0x80;
            self->step++;
        }
        break;
    case 3:
        if (--self->ext.ricMaria.timer == 0) {
            RicCreateEntFactoryFromEntity(self, BP_MARIA_POWERS_INVOKED, 0);
            self->step++;
        }
        break;
    case 4:
        break;
    }
}

#define E_WEAPON 0x10
#define STAGE_ENTITY_START 64

// func_060AE714
bool func_80162E9C(Entity* entity) {
    Entity* e;
    s32 i;
    s16 objId;
    s16 params;

    objId = entity->entityId;
    params = entity->params;
    for (e = &g_Entities[E_WEAPON], i = E_WEAPON; i < STAGE_ENTITY_START; e++,
        i++) {
        if (objId == e->entityId && params == e->params && e != entity) {
            return true;
        }
    }
    return false;
}

// RicEntityPlayerBlinkWhite
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60AE768, func_060AE768);

void func_801641A0(Entity* self) {
    Primitive* prim;
    u16* uv;

    self->posX.i.hi = PLAYER.posX.i.hi - 0;
    self->posY.i.hi = PLAYER.posY.i.hi - 8;
    switch (self->step) {
    case 0:
        self->primIndex = AllocPrimitives(1, 1);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        prim = &g_PrimBuf[self->primIndex];
        uv = DAT_0605AEC0[g_RichterSpritePackage5Resource.allocationIndex + 1];
        prim->unk8 = uv[0];
        prim->unkA = uv[1];
        prim->unk6 =
            LookupTblNoToVram(g_RichterSpritePackage5Resource.flags + 1);
        self->ext.circleExpand.width = 16;
        self->ext.circleExpand.height = 12;
        prim = &g_PrimBuf[self->primIndex];
        prim->priority = PLAYER.zPriority + 8;
        prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS | DRAW_TRANSP;
        self->flags =
            FLAG_POS_PLAYER_LOCKED | FLAG_KEEP_ALIVE_OFFCAMERA | FLAG_HAS_PRIMS;
        self->step++;
        break;

    case 1:
        self->ext.circleExpand.width += 2;
        self->ext.circleExpand.height += 2;
        if (self->ext.circleExpand.width > 56) {
            DestroyEntity(self);
            return;
        }
        break;
    }

    prim = &g_PrimBuf[self->primIndex];
    prim->x0 = self->posX.i.hi - self->ext.circleExpand.width;
    prim->y0 = self->posY.i.hi - self->ext.circleExpand.height;
    prim->x1 = self->posX.i.hi + self->ext.circleExpand.width;
    prim->y1 = self->posY.i.hi - self->ext.circleExpand.height;
    prim->x3 = self->posX.i.hi - self->ext.circleExpand.width;
    prim->y3 = self->posY.i.hi + self->ext.circleExpand.height;
    prim->x2 = self->posX.i.hi + self->ext.circleExpand.width;
    prim->y2 = self->posY.i.hi + self->ext.circleExpand.height;
}

// RicEntityShrinkingPowerUpRing
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60AEDCC, func_060AEDCC);

// RicEntityHitByIce
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60AF094, func_060AF094);

// Copies a primitive together with its gouraud shading entry
void func_060AF704(Primitive* src, Primitive* dst) {
    u16* srcGour;
    u16* dstGour;

    dst->unk4 = src->unk4;
    dst->unk6 = src->unk6;
    dst->unk8 = src->unk8;
    dst->unkA = src->unkA;
    dst->x0 = src->x0;
    dst->y0 = src->y0;
    dst->x1 = src->x1;
    dst->y1 = src->y1;
    dst->x2 = src->x2;
    dst->y2 = src->y2;
    dst->x3 = src->x3;
    dst->y3 = src->y3;
    dst->drawMode = src->drawMode;
    srcGour = ((u16(*)[4])SpGourTbl)[src->unk1C];
    dstGour = ((u16(*)[4])SpGourTbl)[dst->unk1C];
    dstGour[0] = srcGour[0];
    dstGour[1] = srcGour[1];
    dstGour[2] = srcGour[2];
    dstGour[3] = srcGour[3];
}

// RicEntityHitByLightning
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60AF7F4, func_060AF7F4);

INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60AFE70, func_060AFE70);
INCLUDE_ASM_NO_ALIGN("asm/saturn/richter/f_nonmat", f60B00C4, func_060B00C4);

// ===== ???

void RicEntityDummy(void) { DestroyEntity(); }

void func_060B0604() {}

const u16 pad_60B060E = 0; // file split?

s32 func_060B0610() { return 0; }

const u16 pad_60B061A = 0; // file split!
