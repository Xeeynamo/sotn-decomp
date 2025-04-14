// SPDX-License-Identifier: AGPL-3.0-or-later
#include "ric.h"
#include "sfx.h"

Entity* RicGetFreeEntity(s16 start, s16 end);
Entity* RicGetFreeEntityReverse(s16 start, s16 end);

// Similar to same function in DRA
static u8 entity_ranges[][2] = {
    {0x30, 0x3F}, {0x20, 0x2F}, {0x10, 0x1E}, {0x10, 0x3F},
    {0x1F, 0x1F}, {0x30, 0x30}, {0x10, 0x2F}, {0x00, 0x00}};
void RicEntityFactory(Entity* self) {
    Entity* newEntity;
    s16 nPerCycle;
    s16 i;
    s16 startIndex;
    s16 endIndex;
    u8* data;

    if (self->step == 0) {
        data = (u8*)&g_RicFactoryBlueprints[self->params];
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
        switch (self->ext.factory.origin) {
        case 0:
            self->flags |= FLAG_POS_CAMERA_LOCKED;
            break;
        case 4:
            self->flags |= FLAG_UNK_20000;
        case 2:
        case 9:
            self->flags |= FLAG_POS_PLAYER_LOCKED;
        case 3:
        case 7:
            self->posX.val = PLAYER.posX.val;
            self->posY.val = PLAYER.posY.val;
            break;
        case 8:
            self->flags |= FLAG_POS_PLAYER_LOCKED;
            self->posX.val = self->ext.factory.parent->posX.val;
            self->posY.val = self->ext.factory.parent->posY.val;
            break;
        }
    } else {
        switch (self->ext.factory.origin) {
        case 0:
            break;
        case 9:
            if (g_Player.unk4E) {
                DestroyEntity(self);
                return;
            }
        case 2:
            self->posX.val = g_Entities->posX.val;
            self->posY.val = PLAYER.posY.val;
            break;
        case 4:
            self->posX.val = g_Entities->posX.val;
            self->posY.val = PLAYER.posY.val;
            if (PLAYER.step != PL_S_RUN) {
                self->entityId = 0;
                return;
            }
            break;
        case 3:
            self->posX.val = g_Entities->posX.val;
            self->posY.val = PLAYER.posY.val;
            if (PLAYER.step == PL_S_HIT) {
                self->entityId = 0;
                return;
            }
            break;
        case 7:
            self->posX.val = g_Entities->posX.val;
            self->posY.val = PLAYER.posY.val;
            if (PLAYER.step != PL_S_HIT) {
                self->entityId = 0;
                return;
            }
            break;
        case 8:
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
        if (self->ext.factory.kind == 0) {
            newEntity = RicGetFreeEntityReverse(startIndex, endIndex + 1);
        } else if (self->ext.factory.kind == 4) {
            newEntity = &g_Entities[31];
        } else if (self->ext.factory.kind == 5) {
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
        // The child  (newEntity) is not an ent factory, but because the
        // factory creates many entities, we can't pick a particular extension.
        // But we're not allowed to use generic, so i'll just reuse entFactory.
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
    if (PLAYER.step != PL_S_SLIDE) {
        DestroyEntity(entity);
    } else {
        entity->posX.i.hi = PLAYER.posX.i.hi;
        entity->posY.i.hi = PLAYER.posY.i.hi;
        entity->facingLeft = PLAYER.facingLeft;
        if (entity->step == 0) {
            entity->flags = FLAG_UNK_20000 | FLAG_POS_PLAYER_LOCKED |
                            FLAG_KEEP_ALIVE_OFFCAMERA;
            entity->hitboxOffX = 0x14;
            entity->hitboxOffY = 0xC;
            entity->hitboxWidth = entity->hitboxHeight = 9;
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

void func_80160D2C(Entity* self) {
    if (PLAYER.step != PL_S_SLIDE_KICK) {
        DestroyEntity(self);
        return;
    }
    self->posX.i.hi = PLAYER.posX.i.hi;
    self->posY.i.hi = PLAYER.posY.i.hi;
    self->facingLeft = PLAYER.facingLeft;
    if (self->step == 0) {
        self->flags =
            FLAG_UNK_20000 | FLAG_POS_PLAYER_LOCKED | FLAG_KEEP_ALIVE_OFFCAMERA;
        self->hitboxOffX = 0x14;
        self->hitboxWidth = self->hitboxHeight = 9;
        self->ext.subweapon.subweaponId = PL_W_23;
        RicSetSubweaponParams(self);
        self->step++;
    }

    if (PLAYER.animCurFrame == 140) {
        self->hitboxOffY = 0;
    }

    if (PLAYER.animCurFrame == 141) {
        self->hitboxOffY = 12;
    }

    if (self->hitFlags) {
        g_Player.unk44 |= 0x80;
    } else {
        g_Player.unk44 &= ~0x80;
    }
    self->hitFlags = 0;
}

// created from a blueprint, #24
void RicEntityBladeDash(Entity* self) {
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
            self->hitboxWidth = self->hitboxHeight = 20;
            // Wow! So blade dash is treated as a subweapon!
            self->ext.subweapon.subweaponId = PL_W_BIBLE_BEAM;
            RicSetSubweaponParams(self);
            self->step++;
        }
        if (PLAYER.pose > 18) {
            DestroyEntity(self);
        }
    }
}

void func_80160F0C(Entity* self) {
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
        self->hitboxOffX = 0xC;
        self->hitboxOffY = -0x1A;
        self->hitboxWidth = 12;
        self->hitboxHeight = 12;
        // High jump attack is a subweapon!
        self->ext.subweapon.subweaponId = PL_W_HIGHJUMP;
        RicSetSubweaponParams(self);
        self->step++;
    }
}

// Entity ID #2. Created by 6 blueprints:
// 0, 1, 24, 74, 75, 76.
// Matches DRA func_8011B5A4
static s16 pos_x_80154C50[] = {0, -4, -8, -12, -16, -20};
static s32 velocity_x_80154C5C[] = {
    -0x3000, -0x4000, -0x6000, -0x8000, -0xA000, -0xC000};
static s16 rot_x_80154C74[] = {0x0030, 0x0040, 0x0050, 0x0060, 0x0070, 0x0080};
static AnimationFrame anim_smoke_puff[] = {
    {1, FRAME(0x01, 0)},
    {1, FRAME(0x02, 0)},
    {1, FRAME(0x03, 0)},
    {1, FRAME(0x04, 0)},
    {1, FRAME(0x05, 0)},
    {1, FRAME(0x06, 0)},
    {1, FRAME(0x07, 0)},
    {1, FRAME(0x08, 0)},
    {1, FRAME(0x09, 0)},
    {1, FRAME(0x0A, 0)},
    {1, FRAME(0x0B, 0)},
    {1, FRAME(0x0C, 0)},
    {1, FRAME(0x0D, 0)},
    {1, FRAME(0x0E, 0)},
    {1, FRAME(0x0F, 0)},
    {1, FRAME(0x10, 0)},
    {1, FRAME(0x11, 0)},
    {1, FRAME(0x12, 0)},
    {1, FRAME(0x13, 0)},
    {1, FRAME(0x14, 0)},
    {1, FRAME(0x15, 0)},
    {1, FRAME(0x16, 0)},
    {1, FRAME(0x17, 0)},
    {1, FRAME(0x18, 0)},
    A_END};
static u8 sensors1_80154CE4[] = {2, 9, 3, 10, 1, 8, 4, 11, 0, 7, 5, 12, 6, 13};
static u8 sensors2_80154CF4[] = {2, 9, 3, 10, 4, 11, 5, 12, 6, 13};
void RicEntitySmokePuff(Entity* self) {
    s16 posX;
    s32 i;

    s16 paramsHi = self->params >> 8;
    s16 paramsLo = self->params & 0xFF;

    if ((g_Player.status & PLAYER_STATUS_UNK20000) && (paramsHi != 9)) {
        DestroyEntity(self);
        return;
    }
    switch (self->step) {
    case 0:
        self->animSet = 5;
        self->anim = anim_smoke_puff;
        self->zPriority = PLAYER.zPriority + 2;
        self->flags = FLAG_POS_CAMERA_LOCKED | FLAG_UNK_100000 | FLAG_UNK_10000;
        self->drawMode = DRAW_TPAGE2 | DRAW_TPAGE;
        self->drawFlags = FLAG_DRAW_ROTX | FLAG_DRAW_ROTY | FLAG_DRAW_UNK8;
        self->unk6C = 0x60;
        posX = pos_x_80154C50[paramsLo];
        if (paramsHi == 0) {
            posX += 6;
        }
        if (paramsHi == 1) {
            posX -= 8;
        }
        if (paramsHi == 2) {
            posX -= 6;
        }
        if (paramsHi == 5) {
            posX = -6;
        }
        if (paramsHi == 3) {
            self->posY.i.hi -= 8;
        }
        if (paramsHi == 4) {
            for (i = paramsLo * 2; i < LEN(sensors1_80154CE4); i++) {
                if (g_Player.colWall[sensors1_80154CE4[i]].effects &
                    (EFFECT_UNK_0002 | EFFECT_SOLID)) {
                    break;
                }
            }
            if (i == LEN(sensors1_80154CE4)) {
                DestroyEntity(self);
                return;
            }
            self->posX.i.hi =
                PLAYER.posX.i.hi + g_RicSensorsWall[sensors1_80154CE4[i]].x;
            self->posY.i.hi =
                PLAYER.posY.i.hi + g_RicSensorsWall[sensors1_80154CE4[i]].y;
            self->velocityY = FIX(-0.25);
            self->rotX = rot_x_80154C74[1] + 0x40;
            self->rotY = self->rotX;
            self->step++;
            return;
        }
        if (paramsHi == 8) {
            for (i = paramsLo * 2; i < LEN(sensors2_80154CF4); i++) {
                if (g_Player.colWall[sensors2_80154CF4[i]].effects &
                    (EFFECT_UNK_0002 | EFFECT_SOLID)) {
                    break;
                }
            }
            if (i == LEN(sensors2_80154CF4)) {
                DestroyEntity(self);
                return;
            }
            self->posX.i.hi =
                PLAYER.posX.i.hi + g_RicSensorsWall[sensors2_80154CF4[i]].x;
            self->posY.i.hi =
                PLAYER.posY.i.hi + g_RicSensorsWall[sensors2_80154CF4[i]].y;
            self->velocityY = velocity_x_80154C5C[paramsLo];
            self->rotX = rot_x_80154C74[paramsLo] + 0x20;
            self->rotY = self->rotX;
            self->step++;
            return;
        }
        if (paramsHi == 1) {
            if (g_Player.vram_flag & 0x8000) {
                posX /= 2;
            }
        }
        if (self->facingLeft) {
            posX = -posX;
        }
        self->posX.i.hi += posX;
        self->posY.i.hi += 0x18;
        self->rotX = rot_x_80154C74[paramsLo] + 0x40;
        self->velocityY = velocity_x_80154C5C[paramsLo];
        if (paramsHi == 1) {
            self->velocityY = FIX(-0.25);
            RicSetSpeedX(-0x3000);
            self->rotX = rot_x_80154C74[1] + 0x40;
        }
        if (paramsHi == 5) {
            self->velocityY = velocity_x_80154C5C[4 - paramsLo * 2];
        }
        if (paramsHi == 2) {
            self->velocityY = FIX(-0.5);
            RicSetSpeedX(-0x3000);
            self->rotX = rot_x_80154C74[1] + 0x40;
        }
        self->rotY = self->rotX;
        if (paramsHi == 10) {
            self->posY.i.hi -= 6;
        }
        self->step++;
        break;
    case 1:
        self->unk6C -= 2;
        self->posY.val += self->velocityY;
        self->posX.val += self->velocityX;
        if (self->poseTimer < 0) {
            DestroyEntity(self);
            return;
        }
        break;
    }
}

// Corresponding DRA function is func_8011E4BC
static unkStr_8011E4BC D_80154D00 = {
    0x08, 0xC0, 0x60, 0x00, 0x01, 0x01, 0x0004, 0x0033, 0x0003, 0x08800000};
static unkStr_8011E4BC D_80154D10 = {
    0x10, 0x7F, 0x7F, 0x7F, 0x01, 0x01, 0x0002, 0x0033, 0x0001, 0x0C800000};
static unkStr_8011E4BC D_80154D20 = {
    0x08, 0x7F, 0x7F, 0x7F, 0x02, 0x02, 0x0002, 0x0033, 0x0000, 0x08800000};
static unkStr_8011E4BC D_80154D30 = {
    0x06, 0x7F, 0xFF, 0xFF, 0x01, 0x01, 0x0004, 0x0073, 0x0003, 0x08800000};
static unkStr_8011E4BC D_80154D40 = {
    0x0C, 0xC0, 0x60, 0x00, 0x01, 0x01, 0x0004, 0x0033, 0x0003, 0x08800000};
static unkStr_8011E4BC D_80154D50 = {
    0x0C, 0x7F, 0x00, 0x00, 0x03, 0x03, 0x0002, 0x0002, 0x0004, 0x0C800000};
static unkStr_8011E4BC D_80154D60 = {
    0x08, 0x1F, 0x1F, 0x7F, 0x01, 0x01, 0x0004, 0x0033, 0x0006, 0x0C800000};
static unkStr_8011E4BC D_80154D70 = {
    0x14, 0x7F, 0x7F, 0xC0, 0x01, 0x01, 0xFFFE, 0x0033, 0x0007, 0x0C800000};
static unkStr_8011E4BC D_80154D80 = {
    0x06, 0xC0, 0xC0, 0xC0, 0x02, 0x02, 0x0002, 0x007B, 0x0008, 0x08800000};
static unkStr_8011E4BC D_80154D90 = {
    0x10, 0x7F, 0x7F, 0x7F, 0x01, 0x01, 0x0002, 0x0033, 0x0009, 0x08800000};
static unkStr_8011E4BC* D_80154DA0[] = {
    &D_80154D00, &D_80154D10, &D_80154D20, &D_80154D30, &D_80154D40,
    &D_80154D50, &D_80154D60, &D_80154D70, &D_80154D80, &D_80154D90};
void RicEntityHitByCutBlood(Entity* self) {
    byte stackpad[0x28];
    u8 thickness;
    s16 variant;
    s16 playerX;
    s16 playerY;
    s16 velocityScale;
    s16 velocityRnd;
    s32 timer;
    s16 x;
    s16 y;
    s16 rnd;
    s32 i;
    unkStr_8011E4BC* props;
    FakePrim* tilePrim;

    variant = (self->params) >> 8;
    props = D_80154DA0[variant];
    x = self->posX.i.hi;
    y = self->posY.i.hi;
    playerX = PLAYER.posX.i.hi;
    playerY = PLAYER.posY.i.hi;
    switch (self->step) {
    case 0:
        self->primIndex = g_api.func_800EDB58(PRIM_TILE_ALT, props->count + 1);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags = props->flags;
        switch (props->unkA) {
        case 8:
            self->ext.et_8011E4BC.unk7C = 0x100;
            break;
        case 7:
            self->ext.et_8011E4BC.unk7C = 0x3F;
            break;
        case 4:
            self->ext.et_8011E4BC.unk7C = 0x2F;
            break;
        case 3:
        case 6:
            self->ext.et_8011E4BC.unk7C = 0x1F;
            break;
        }
        tilePrim = (FakePrim*)&g_PrimBuf[self->primIndex];
        i = 0;
        while (1) {
            tilePrim->drawMode = props->drawMode;
            tilePrim->priority = PLAYER.zPriority + props->priority;
            if (tilePrim->next == NULL) {
                tilePrim->drawMode &= ~DRAW_HIDE;
                tilePrim->y0 = tilePrim->x0 = tilePrim->w = 0;
                break;
            }
            tilePrim->posX.i.hi = x;
            tilePrim->posY.i.hi = y;
            tilePrim->posX.i.lo = tilePrim->posY.i.lo = 0;
            switch (props->unkA) {
            case 0:
                velocityRnd = rand() & PSP_RANDMASK;
                velocityScale = (velocityRnd & 1) + 2;
                tilePrim->velocityX.val = (rcos(velocityRnd) << velocityScale);
                tilePrim->velocityY.val = -(rsin(velocityRnd) << velocityScale);
                break;
            case 1:
            case 9:
                tilePrim->velocityX.val = ((rand() & 0x1FF) - 0x100) << 8;
                tilePrim->velocityY.val = ((rand() & 0x1FF) - 0x100) << 8;
                break;
            case 3:
                tilePrim->posX.i.hi = x + (rand() & 0xF) - 7;
                tilePrim->posY.i.hi = y - (rand() & 0xF);
                tilePrim->velocityY.val = FIX(-0.75) - (rand() & 0x7FFF);
                tilePrim->velocityX.val =
                    self->ext.et_8011E4BC.parent->velocityX;
                tilePrim->delay = (rand() & 0xF) + 0x10;
                break;
            case 4:
                rnd = rand() & 0x1F;
                tilePrim->posX.i.hi = x + rnd - 0x10;
                rnd = rand() & 0x1F;
                tilePrim->posY.i.hi = y + rnd - 0x14;
                rnd = rand() & 0x1F;
                tilePrim->velocityX.val = D_80175958[rnd];
                tilePrim->velocityY.val = D_801759D8[rnd];
                break;
            case 6:
                tilePrim->posX.i.hi = self->posX.i.hi + (rand() & 0xF) - 8;
                tilePrim->posY.i.hi = self->posY.i.hi + (rand() & 0xF) - 4;
                tilePrim->velocityY.val = (rand() & PSP_RANDMASK) + FIX(0.5);
                tilePrim->delay = (rand() & 0xF) + 0x10;
                break;
            case 7:
                tilePrim->posX.i.hi = x;
                tilePrim->posY.i.hi = y;
                if (i < 10) {
                    tilePrim->velocityY.val =
                        -((i * i * FIX(0.09375)) + FIX(0.125));
                } else {
                    tilePrim->velocityY.val =
                        (i - 10) * (i - 10) * FIX(0.09375) + FIX(0.125);
                }
                tilePrim->delay = 0x3F;
                break;
            case 8:
                tilePrim->posX.i.hi = x;
                tilePrim->posY.i.hi = y;
#if defined(VERSION_PSP)
                tilePrim->velocityX.val = ((rand() & 0x7FFF) - FIX(0.25)) >> 1;
#else
                tilePrim->velocityX.val = (rand() - FIX(0.25)) >> 1;
#endif
                tilePrim->velocityY.val = -((rand() & 0x1FFF) + FIX(0.375));
                tilePrim->timer = (i * 4);
                break;
            }
            tilePrim->x0 = tilePrim->posX.i.hi;
            tilePrim->y0 = tilePrim->posY.i.hi;
            tilePrim->r0 = props->r;
            tilePrim->g0 = props->g;
            tilePrim->b0 = props->b;
            tilePrim->w = props->w;
            tilePrim->h = props->h;
            i++;
            tilePrim = tilePrim->next;
        }
        self->step++;
        break;
    case 1:
        switch (props->unkA) {
        case 3:
        case 6:
        case 7:
        case 8:
            if (--self->ext.et_8011E4BC.unk7C == 0) {
                DestroyEntity(self);
                return;
            }
        case 4:
            if (--self->ext.et_8011E4BC.unk7C == 0) {
                DestroyEntity(self);
                return;
            }
            thickness = 3;
            timer = self->ext.et_8011E4BC.unk7C;
            if (timer < 9) {
                thickness--;
            }
            if (timer < 4) {
                thickness--;
            }
        }
        tilePrim = (FakePrim*)&g_PrimBuf[self->primIndex];
        i = 0;
        while (1) {
            if (tilePrim->next == NULL) {
                tilePrim->drawMode &= ~DRAW_HIDE;
                tilePrim->y0 = tilePrim->x0 = tilePrim->w = 0;
                return;
            }
            tilePrim->posX.i.hi = tilePrim->x0;
            tilePrim->posY.i.hi = tilePrim->y0;
            switch (props->unkA) {
            case 0:
                tilePrim->posY.val += tilePrim->velocityY.val;
                tilePrim->posX.val += tilePrim->velocityX.val;
                tilePrim->r0 -= 6;
                tilePrim->g0 -= 6;
                tilePrim->b0 -= 6;
                if (tilePrim->r0 < 8) {
                    DestroyEntity(self);
                    return;
                }
                break;
            case 1:
            case 9:
                tilePrim->posY.val += tilePrim->velocityY.val;
                tilePrim->posX.val += tilePrim->velocityX.val;
                tilePrim->velocityY.val =
                    (tilePrim->velocityY.val + FIX(0.15625));
                tilePrim->r0 -= 3;
                tilePrim->g0 -= 3;
                tilePrim->b0 -= 3;
                if (tilePrim->r0 < 8) {
                    DestroyEntity(self);
                    return;
                }
                break;
            case 3:
            case 6:
            case 7:
                tilePrim->posY.val += tilePrim->velocityY.val;
                if (--tilePrim->delay < 0) {
                    tilePrim->drawMode |= DRAW_HIDE;
                }
                break;
            case 4:
                tilePrim->posX.val += tilePrim->velocityX.val;
                tilePrim->posY.val += tilePrim->velocityY.val;
                // There is probably a clever way to write this
                tilePrim->velocityY.val -= tilePrim->velocityY.val >> 5;
                if (!(timer & 7)) {
                    tilePrim->velocityX.val >>= 1;
                    tilePrim->velocityY.val >>= 1;
                    if (timer & 0x20) {
                        tilePrim->velocityY.val >>= 1;
                    }
                    if (timer == 0x18) {
                        tilePrim->drawMode = DRAW_UNK02;
                    }
                }
                tilePrim->w = tilePrim->h = thickness;
                break;
            case 8:
                if (tilePrim->timer == 0) {
                    tilePrim->drawMode &= ~DRAW_HIDE;
                    tilePrim->r0 -= 1;
                    tilePrim->g0 -= 1;
                    tilePrim->b0 -= 1;
                    tilePrim->posY.val += tilePrim->velocityY.val;
                    tilePrim->posX.val += tilePrim->velocityX.val;
                    if (*D_80097448 == 0 ||
                        !(tilePrim->posY.i.hi >
                          (PLAYER.posY.i.hi - *D_80097448 + 0x19))) {
                        tilePrim->drawMode |= DRAW_HIDE;
                    }
                } else {
                    tilePrim->timer--;
                }
                break;
            }
            tilePrim->x0 = tilePrim->posX.i.hi;
            tilePrim->y0 = tilePrim->posY.i.hi;
            i++;
            tilePrim = tilePrim->next;
        }
    }
}

// DRA function is func_8011EDA8
static AnimationFrame anim_80154DC8[] = {
    {2, FRAME(1, 0)}, {2, FRAME(2, 0)}, {2, FRAME(3, 0)},
    {2, FRAME(4, 0)}, {2, FRAME(5, 0)}, {2, FRAME(4, 0)},
    {2, FRAME(3, 0)}, {2, FRAME(4, 0)}, {2, FRAME(3, 0)},
    {2, FRAME(4, 0)}, {2, FRAME(5, 0)}, {1, FRAME(6, 0)},
    {1, FRAME(7, 0)}, {1, FRAME(8, 0)}, A_END};
static AnimationFrame anim_80154E04[] = {
    {1, FRAME(9, 0)},
    {2, FRAME(10, 0)},
    {2, FRAME(11, 0)},
    {2, FRAME(12, 0)},
    {2, FRAME(13, 0)},
    {2, FRAME(14, 0)},
    {2, FRAME(15, 0)},
    {2, FRAME(16, 0)},
    {2, FRAME(17, 0)},
    {2, FRAME(18, 0)},
    {3, FRAME(19, 0)},
    {4, FRAME(20, 0)},
    A_END};
void func_80161C2C(Entity* self) {
    s16 paramsHi;
    s16 paramsLo;

    paramsLo = self->params & 0xFF;
    paramsHi = (self->params >> 8) & 0xFF;
    switch (self->step) {
    case 0:
        if (paramsHi == 1) {
            self->rotX = 0xC0;
            self->rotY = 0xC0;
            self->drawFlags = FLAG_DRAW_ROTX | FLAG_DRAW_ROTY;
            self->animSet = ANIMSET_DRA(2);
            self->anim = anim_80154E04;
        }
        if (paramsHi == 0 || paramsHi == 2) {
            if (paramsLo & 3) {
                self->anim = anim_80154DC8;
                self->rotX = 0x120;
                self->rotY = 0x120;
                self->drawFlags = FLAG_DRAW_ROTX | FLAG_DRAW_ROTY;
                self->animSet = ANIMSET_DRA(2);
            } else {
                self->animSet = ANIMSET_DRA(5);
                self->anim = anim_smoke_puff;
                self->palette = PAL_OVL(0x170);
            }
        }
        self->flags = FLAG_UNK_20000 | FLAG_UNK_100000 | FLAG_POS_CAMERA_LOCKED;
        if (rand() & 3) {
            self->zPriority = PLAYER.zPriority + 2;
        } else {
            self->zPriority = PLAYER.zPriority - 2;
        }
        if (paramsHi == 2) {
            self->posX.i.hi = PLAYER.posX.i.hi + (rand() % 44) - 22;
        } else {
            self->posX.i.hi = PLAYER.posX.i.hi + (rand() & 15) - 8;
        }
        self->posY.i.hi =
            PLAYER.posY.i.hi + PLAYER.hitboxOffY + (rand() & 31) - 16;
        self->velocityY = FIX(-0.5);
        self->velocityX = PLAYER.velocityX >> 2;
        self->step++;
        break;
    case 1:
        self->rotX -= 4;
        self->rotY -= 4;
        self->posY.val += self->velocityY;
        self->posX.val += self->velocityX;
        if ((self->pose == 8) && (self->anim != anim_smoke_puff)) {
            self->drawMode = DRAW_TPAGE;
            if (!(paramsLo & 1) && self->poseTimer == 1) {
                RicCreateEntFactoryFromEntity(self, FACTORY(BP_EMBERS, 4), 0);
            }
        }
        if (self->pose == 16 && self->anim == anim_smoke_puff) {
            self->drawMode = DRAW_TPAGE;
        }
        if (self->poseTimer < 0) {
            DestroyEntity(self);
        }
        break;
    }
}

static AnimationFrame anim_80154E38[] = {
    {2, FRAME(1, 0)}, {2, FRAME(2, 0)}, {2, FRAME(3, 0)},
    {2, FRAME(4, 0)}, {2, FRAME(5, 0)}, {2, FRAME(6, 0)},
    {2, FRAME(7, 0)}, {2, FRAME(8, 0)}, A_END};
void func_80161EF8(Entity* self) {
    switch (self->step) {
    case 0:
        self->animSet = ANIMSET_DRA(2);
        self->anim = anim_80154E38;
        self->flags = FLAG_UNK_20000 | FLAG_UNK_100000 | FLAG_UNK_10000 |
                      FLAG_POS_PLAYER_LOCKED;
        self->zPriority = PLAYER.zPriority + 4;
        self->velocityY = (rand() & 0x3FFF) - 0x10000;
        self->step++;
        break;
    case 1:
        if (self->pose == 6) {
            if (self->poseTimer == 1 && (rand() & 1)) {
                RicCreateEntFactoryFromEntity(self, BP_EMBERS, 0);
            }
        }
        self->posY.val += self->velocityY;
        if (self->poseTimer < 0) {
            DestroyEntity(self);
        }
        break;
    }
}

typedef struct {
    s16 xPos;
    s16 yPos;
    s32 velocityX;
    s32 velocityY;
    s16 timerInit;
    s16 tpage;
    u16 clut;
    u8 uBase;
    u8 vBase;
} Props_80161FF0; // size = 0x14
static Props_80161FF0 D_80154E5C[] = {
    {-0x40, 0, +FIX(2.5), FIX(0), 0x0060, 0x1B, 0x0118, 128, 0},
    {+0x40, 0, -FIX(2.5), FIX(0), 0x0048, 0x1B, 0x0119, 0, 128},
    {0, -0x40, FIX(0), +FIX(2.5), 0x0030, 0x19, 0x011A, 0, 0},
    {0, +0x40, FIX(0), -FIX(2.5), 0x0018, 0x19, 0x011B, 128, 0}};
void RicEntityApplyMariaPowerAnim(Entity* self) {
    Primitive* prim;
    s16 posX;
    s16 posY;
    s16 params;
    Props_80161FF0* props;

    posX = self->posX.i.hi;
    posY = self->posY.i.hi;
    params = self->params;
    props = &D_80154E5C[params];
    switch (self->step) {
    case 0:
        self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 1);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        g_api.PlaySfx(0x881);
        self->ext.ricMariaPower.size = 0x100;
        prim = &g_PrimBuf[self->primIndex];
        prim->u0 = props->uBase;
        prim->v0 = props->vBase;
        prim->u1 = props->uBase + 0x7F;
        prim->v1 = props->vBase;
        prim->u2 = props->uBase;
        prim->v2 = props->vBase + 0x6F;
        prim->u3 = props->uBase + 0x7F;
        prim->v3 = props->vBase + 0x6F;
        prim->tpage = props->tpage;
        prim->clut = props->clut;
        prim->priority = PLAYER.zPriority + 8;
        prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_TRANSP;
        self->velocityX = props->velocityX;
        self->velocityY = props->velocityY;
        posX = self->posX.i.hi += props->xPos;
        posY = self->posY.i.hi += props->yPos;
        self->flags =
            FLAG_KEEP_ALIVE_OFFCAMERA | FLAG_HAS_PRIMS | FLAG_UNK_10000;
        self->step++;
        break;
    case 1:
        self->ext.ricMariaPower.size -= 8;
        self->posX.val += self->velocityX;
        self->posY.val += self->velocityY;
        if (self->ext.ricMariaPower.size < 25) {
            self->ext.ricMariaPower.timer = props->timerInit;
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
    prim->x2 =
        posX + (((rcos(0xA00) >> 4) * self->ext.ricMariaPower.size) >> 8);
    prim->y2 =
        posY - (((rsin(0xA00) >> 4) * self->ext.ricMariaPower.size) >> 8);
    prim->x3 =
        posX + (((rcos(0xE00) >> 4) * self->ext.ricMariaPower.size) >> 8);
    prim->y3 =
        posY - (((rsin(0xE00) >> 4) * self->ext.ricMariaPower.size) >> 8);
}

void func_801623E0(Entity* self) {
    Primitive* prim;

    self->posX.val = g_Entities->posX.val;
    self->posY.val = PLAYER.posY.val;
    switch (self->step) {
    case 0:
        self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 1);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->ext.circleExpand.width = self->ext.circleExpand.height = 32;
        prim = &g_PrimBuf[self->primIndex];
        prim->u0 = prim->u2 = 64;
        prim->v0 = prim->v1 = 192;
        prim->u1 = prim->u3 = 127;
        prim->v2 = prim->v3 = 255;
        prim->tpage = 0x1A;
        prim->clut = 0x13E;
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
    prim->x2 = self->posX.i.hi - self->ext.circleExpand.width;
    prim->y2 = self->posY.i.hi + self->ext.circleExpand.height;
    prim->x3 = self->posX.i.hi + self->ext.circleExpand.width;
    prim->y3 = self->posY.i.hi + self->ext.circleExpand.height;
    prim->clut = (g_Timer & 1) + 0x13E;
}

void func_80162604(Entity* self) {
    Primitive* prim;

    self->posX.val = PLAYER.posX.val;
    self->posY.val = PLAYER.posY.val;
    switch (self->step) {
    case 0:
        self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 1);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->ext.circleExpand.width = self->ext.circleExpand.height = 0;
        prim = &g_PrimBuf[self->primIndex];

        prim->u0 = prim->u2 = 0;
        prim->v0 = prim->v1 = 192;
        prim->u1 = prim->u3 = 63;
        prim->v2 = prim->v3 = 255;
        prim->tpage = 0x1A;

        prim->clut = 0x162;
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
    prim->x2 = self->posX.i.hi - self->ext.circleExpand.width;
    prim->y2 = self->posY.i.hi + self->ext.circleExpand.height;
    prim->x3 = self->posX.i.hi + self->ext.circleExpand.width;
    prim->y3 = self->posY.i.hi + self->ext.circleExpand.height;
}

static u16 D_80154EAC[] = {0x016E, 0x0161, 0x0160, 0x0162};
// 0xFFFF2AAB = -FIX(1. / 3)
// 0xFFFDAAAB = -FIX(5. / 3)
static s32 D_80154EB4[] = {FIX(5. / 3), -FIX(5. / 3), FIX(1. / 3), -0xD555};
static s32 D_80154EC4[] = {-FIX(2), -FIX(5. / 3), -FIX(3), -0x25555};
void RicEntityMariaPowers(Entity* self) {
    Primitive* prim;
    s16 params;

    params = self->params;
    switch (self->step) {
    case 0:
        self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 1);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->unk5A = 0x66;
        self->zPriority = PLAYER.zPriority - 12;
        self->palette = params + 0x149;
        self->animSet = ANIMSET_OVL(0x13);
        self->animCurFrame = params + 0x19;
        self->velocityX = D_80154EB4[params];
        self->velocityY = D_80154EC4[params];
        self->ext.et_80162870.unk7C = self->ext.et_80162870.unk7E =
            self->ext.et_80162870.unk80 = 8;

        prim = &g_PrimBuf[self->primIndex];
        prim->u0 = prim->v0 = prim->v1 = prim->u2 = 0;
        prim->u1 = prim->v2 = prim->u3 = prim->v3 = 0x1F;
        prim->tpage = 0x1A;
        prim->clut = D_80154EAC[params];
        prim->priority = PLAYER.zPriority - 16;
        prim->drawMode = DRAW_HIDE;
        self->flags = FLAG_HAS_PRIMS | FLAG_UNK_10000;
        if (params == 3) {
            self->flags |= FLAG_KEEP_ALIVE_OFFCAMERA;
        }
        g_api.PlaySfx(0x881);
        self->ext.et_80162870.unk82 = 12;
        self->step++;
        break;
    case 1:
        self->posX.val += self->velocityX;
        self->posY.val += self->velocityY;
        if (--self->ext.et_80162870.unk82 == 0) {
            self->drawFlags = FLAG_DRAW_ROTY | FLAG_DRAW_ROTX;
            self->rotX = self->rotY = 0x100;
            self->ext.et_80162870.unk82 = 0x10;
            self->step++;
            prim = &g_PrimBuf[self->primIndex];
            prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_TRANSP;
        }
        break;
    case 2:
        self->rotX = self->rotY = self->ext.et_80162870.unk82 * 0x10;
        if (--self->ext.et_80162870.unk82 == 0) {
            self->animCurFrame = 0;
            g_api.PlaySfx(SFX_MAGIC_SWITCH);
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
    prim->x2 = self->posX.i.hi - self->ext.et_80162870.unk7C;
    prim->y2 = self->posY.i.hi + self->ext.et_80162870.unk80;
    prim->x3 = self->posX.i.hi + self->ext.et_80162870.unk7C;
    prim->y3 = self->posY.i.hi + self->ext.et_80162870.unk80;
}

void RicEntityNotImplemented4(Entity* self) {}

static AnimationFrame anim_maria_walk[] = {
    {4, FRAME(1, 0)}, {4, FRAME(2, 0)}, {4, FRAME(3, 0)},
    {4, FRAME(4, 0)}, {4, FRAME(5, 0)}, {4, FRAME(6, 0)},
    {4, FRAME(7, 0)}, {4, FRAME(8, 0)}, A_LOOP_AT(0)};
static AnimationFrame anim_maria_offering_powers[] = {
    {0x08, FRAME(0x09, 0)}, {0x08, FRAME(0x0D, 0)}, {0x40, FRAME(0x0A, 0)},
    {0x02, FRAME(0x0B, 0)}, {0x02, FRAME(0x0C, 0)}, {0x06, FRAME(0x0D, 0)},
    {0x07, FRAME(0x0E, 0)}, {0x06, FRAME(0x0F, 0)}, {0x05, FRAME(0x0E, 0)},
    {0x04, FRAME(0x0D, 0)}, {0x03, FRAME(0x0F, 0)}, {0x03, FRAME(0x0E, 0)},
    {0x03, FRAME(0x0D, 0)}, {0x03, FRAME(0x0E, 0)}, {0x03, FRAME(0x0F, 0)},
    {0x03, FRAME(0x0E, 0)}, {0x03, FRAME(0x0D, 0)}, {0x04, FRAME(0x0E, 0)},
    {0x05, FRAME(0x0F, 0)}, {0x06, FRAME(0x0E, 0)}, {0x07, FRAME(0x0D, 0)},
    {0x30, FRAME(0x0E, 0)}, {0x0C, FRAME(0x09, 0)}, {0x0D, FRAME(0x10, 0)},
    {0x08, FRAME(0x11, 0)}, {0x0C, FRAME(0x12, 0)}, {0xB0, FRAME(0x13, 0)},
    {0x0A, FRAME(0x14, 0)}, {0x0A, FRAME(0x15, 0)}, {0x0A, FRAME(0x16, 0)},
    {0x30, FRAME(0x17, 0)}, {0xD0, FRAME(0x18, 0)}, A_END};

void RicEntityMaria(Entity* self) {
    switch (self->step) {
    case 0:
        self->flags = FLAG_UNK_100000 | FLAG_KEEP_ALIVE_OFFCAMERA |
                      FLAG_UNK_10000 | FLAG_POS_CAMERA_LOCKED;
        self->facingLeft = 1;
        self->unk5A = 0x66;
        self->zPriority = PLAYER.zPriority - 8;
        self->palette = PAL_OVL(0x149);
        self->animSet = ANIMSET_OVL(19);
        RicSetAnimation(anim_maria_walk);
        self->velocityX = FIX(-1.75);
        self->posY.i.hi = 0xBB;
        self->posX.i.hi = 0x148;
        self->ext.ricMaria.boolDidSound = 0;
        self->step++;
        break;
    case 1:
        if (self->pose == 0 && self->poseTimer == 1) {
            g_api.PlaySfx(0x882);
        }
        if (self->pose == 4 && self->poseTimer == 1) {
            g_api.PlaySfx(0x883);
        }

        self->posX.val += self->velocityX;
        if ((self->ext.ricMaria.boolDidSound == false) &&
            (self->posX.i.hi < 256)) {
            g_api.PlaySfx(0x87D);
            self->ext.ricMaria.boolDidSound++;
        }
        if (self->posX.i.hi < 0xE0) {
            RicSetAnimation(anim_maria_offering_powers);
            self->step++;
            self->velocityX = 0;
            RicCreateEntFactoryFromEntity(self, FACTORY(BP_SKID_SMOKE, 4), 0);
        }
        break;
    case 2:
        if (self->pose == 16) {
            g_api.PlaySfx(0x87E);
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

STATIC_PAD_RODATA(4);
