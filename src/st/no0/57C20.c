// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no0.h"

extern Entity D_us_80180BCC[];

void func_us_801D7C20(Entity* self) {
    if (self->step != 0) {
        if (self->flags & FLAG_DEAD) {
            EntityExplosionSpawn(0, 0);
            return;
        }
        self->rotZ += 0x80;
        MoveEntity(0);
        if (self->posY.i.hi > 0xF0) {
            DestroyEntity(self);
        }
    } else {
        InitializeEntity(D_us_80180BCC);
        self->posY.val -= FIX(1.0 / 16);
        GetDistanceToPlayerX();
        self->velocityX = self->facingLeft ? FIX(1.75) : FIX(-1.75);
        self->velocityY = 0;
        self->drawFlags = FLAG_DRAW_ROTZ;
    }
}

INCLUDE_ASM("st/no0/nonmatchings/57C20", func_us_801D7D00);

INCLUDE_ASM("st/no0/nonmatchings/57C20", func_us_801D7DAC);

extern u16 D_us_80180AF4;
extern AnimationFrame D_us_80182280;
extern AnimationFrame D_us_8018228C;
extern AnimationFrame D_us_801822B4;
extern AnimationFrame D_us_80182300;
extern u16 D_us_80182324[];

void func_us_801D8150(Entity* self) {
    Primitive* prim;
    s32 primIndex;
    s32 i;
    s32 posX;
    s32 posY;
    s16 temp_s0;
    u32 params;
    Entity* entity;

    params = self->params;
    if (self->step < 7) {
        entity = self - params;
        if ((entity->posX.i.hi > 0x180) || (entity->posX.i.hi < -0x80) ||
            (entity->posY.i.hi > 0x180) || (entity->posY.i.hi < 0)) {
            return;
        }
    }

    entity = self - self->params + 0xB;
    if (self->step == 1) {
        if (self->params == 0) {
            self->unk60 = entity;
        } else {
            self->unk60 = self - 1;
        }
    }
    if ((entity->hitFlags & 0xF) && (self->step < 7)) {
        if (entity->flags & FLAG_DEAD) {
            PlaySfxPositional(0x731);
            entity -= 0xB;
            for (i = 0; i < 0xC; i++, entity++) {
                entity->hitboxState = 0;
                entity->step = 7;
                entity->ext.et_801D8150.unk86 = 0xC0;
                entity->flags |= FLAG_DEAD;
            }
        } else if (
            (entity->step != 3) && (entity->step != 5) && (entity->step != 6)) {
            if ((entity->hitPoints >= 0x1F) || (params != 0xB) ||
                self->ext.et_801D8150.unk8A) {
                PlaySfxPositional(0x730);
                if ((self->step != 6) && (self->step != 5)) {
                    self->step_s = self->step;
                }
                self->step = 5;
                self->ext.et_801D8150.unk86 = 0x28;
                if ((entity->hitPoints >= 0x1F) && (params == 0xB)) {
                    self->animFrameIdx = 0;
                    self->animFrameDuration = 0;
                    self->anim = &D_us_80182280;
                }
            } else {
                self->ext.et_801D8150.unk8A = true;
                self->animFrameIdx = 0;
                self->animFrameDuration = 0;
                self->anim = &D_us_801822B4;
                self->step = 3;
                self->drawFlags |= FLAG_DRAW_ROTZ;
            }
        }
    }
    switch (self->step) {
    case 0:
        if (params == 0) {
            entity = self + 1;
            for (i = 1; i < 0xC; i++, entity++) {
                CreateEntityFromCurrentEntity(E_ID_3D, entity);
                entity->params = i;
                entity->facingLeft = self->facingLeft;
            }
        }
        self->drawFlags = FLAG_DRAW_ROTX | FLAG_DRAW_ROTY;
        InitializeEntity(&D_us_80180AF4);
        if (params == 0xB) {
            self->flags &= ~FLAG_KEEP_ALIVE_OFFCAMERA;
        }

        if (params == 0) {
            self->animCurFrame = 1;
        } else if (params == 0xB) {
            self->animCurFrame = 2;
        } else {
            self->animCurFrame = 9;
        }
        self->zPriority = PLAYER.zPriority - 0x20 + (params * 2);
        self->facingLeft = GetSideToPlayer() & 1;
        if (params == 0) {
            self->hitboxWidth = 0xC;
            self->hitboxHeight = 0xC;
            self->hitboxOffX = -8;
            self->hitboxOffY = 8;
        }
        if (params == 0xB) {
            self->hitboxWidth = 0x10;
            self->hitboxHeight = 8;
            self->hitboxOffX = 0x10;
            self->hitboxOffY = 0;
        } else {
            self->hitPoints = 0x7FFF;
        }
        self->ext.et_801D8150.unk7E = params * 0x180;
        self->ext.et_801D8150.unk88 = 0x480;
        self->ext.et_801D8150.unk82 = params * 0x40 + 0x100;
        if (params == 0) {
            self->ext.et_801D8150.unk82 = self->ext.et_801D8150.unk82 * 1 / 4;
        }
        if (params == 1) {
            self->ext.et_801D8150.unk82 = self->ext.et_801D8150.unk82 * 2 / 4;
        }
        if (params == 2) {
            self->ext.et_801D8150.unk82 = self->ext.et_801D8150.unk82 * 3 / 4;
        }
        break;
    case 1:
        if ((self->posX.i.hi < 0x120) || (self->posX.i.hi >= -0x1F) ||
            (self->posY.i.hi < 0xE8)) {
            self->ext.et_801D8150.unk84++;
        }
        self->ext.et_801D8150.unk7E += 0x30;
        if (((self->ext.et_801D8150.unk84 & 0x1F) == 0x1F) && (params == 0xB)) {
            self->animFrameIdx = 0;
            self->animFrameDuration = 0;
            self->anim = &D_us_8018228C;
            PlaySfxPositional(SFX_SEED_SPIT);
            self->step = 2;
        }
        break;
    case 2:
        self->ext.et_801D8150.unk7E += 0x30;
        g_api.UpdateAnim(NULL, NULL);
        if (self->animFrameIdx == 0x8 && self->animFrameDuration == 0x2F) {
            PlaySfxPositional(SFX_SEED_BLIP);
            func_us_801D7D00(0U);
        }
        if (self->animFrameDuration < 0) {
            self->step = 1;
            self->animCurFrame = 2;
        }
        break;
    case 3:
        self->ext.et_801D8150.unk7E += 0x100;
        self->ext.et_801D8150.unk90 += 0x180;
        self->rotZ = rsin(self->ext.et_801D8150.unk90) >> 3;
        if (self->ext.et_801D8150.unk90 >= 0x6000) {
            self->drawFlags &= ~FLAG_DRAW_ROTZ;
        }
        g_api.UpdateAnim(NULL, NULL);
        if (self->animFrameDuration < 0) {
            self->animFrameIdx = 0;
            self->animFrameDuration = 0;
            self->anim = &D_us_80182300;
            PlaySfxPositional(SFX_SEED_SPIT);
            self->step++;
        }
        break;
    case 4:
        self->hitboxWidth = 8;
        self->hitboxHeight = 0x1C;
        self->hitboxOffX = 8;
        self->hitboxOffY = 0;
        self->ext.et_801D8150.unk7E += 0x30;
        g_api.UpdateAnim(NULL, NULL);
        --self->ext.et_801D8150.unk84;
        if ((self->ext.et_801D8150.unk84 & 0x3F) == 0x1F) {
            PlaySfxPositional(SFX_SEED_BLIP);
            func_us_801D7D00(1U);
        }
        break;
    case 5:
        if (params == 0xB) {
            g_api.UpdateAnim(NULL, NULL);
        }
        self->ext.et_801D8150.unk88 -= 8;
        self->ext.et_801D8150.unk7E += 0xC0;
        if (--self->ext.et_801D8150.unk86 == 0) {
            self->ext.et_801D8150.unk86 = 0xC;
            self->step++;
        }
        break;
    case 6:
        if (params == 0xB) {
            g_api.UpdateAnim(NULL, NULL);
        }
        if (!self->ext.et_801D8150.unk86) {
            self->ext.et_801D8150.unk7E += 0x30;
            self->ext.et_801D8150.unk88 += 0x10;

            if (self->ext.et_801D8150.unk88 >= 0x480) {
                self->ext.et_801D8150.unk88 = 0x480;
                self->step = self->step_s;
                if (params == 0xB && (self->step == 2 || self->step == 1)) {
                    self->animFrameIdx = 7;
                    self->animFrameDuration = 1;
                    self->anim = &D_us_8018228C;
                    self->step = 2;
                }
            }
        } else {
            self->ext.et_801D8150.unk86--;
        }
        break;
    case 7:
        if (!(g_Timer & 7)) {
            PlaySfxPositional(SFX_EXPLODE_B);
        }
        self->ext.et_801D8150.unk7E += 0x180;
        if ((params == 0xB) && !(self->ext.et_801D8150.unk86 & 1)) {
            entity = g_api.GetFreeEntity(0xE0, 0x100);
            if (entity != NULL) {
                DestroyEntity(entity);
                CreateEntityFromCurrentEntity(E_EXPLOSION, entity);
                entity->params = 1;
                entity->zPriority = self->zPriority + 2;
                if (self->facingLeft) {
                    entity->posX.i.hi =
                        self->posX.i.hi + (rand() & 0x1F) - 0x1F;
                } else {
                    entity->posX.i.hi = self->posX.i.hi + (rand() & 0x1F) - 0xF;
                }
                entity->posY.i.hi = self->posY.i.hi + (rand() & 0x1F) - 0x10;
            }
        }
        if (--self->ext.et_801D8150.unk86 == 0) {
            self->step++;
            self->ext.et_801D8150.unk86 = (0xC - params) * 2;
        }
        break;
    case 8:
        if (--self->ext.et_801D8150.unk86 == 0) {
            if (params == 0xB) {
                PlaySfxPositional(SFX_STUTTER_EXPLODE_B);
            }
            self->step++;
            if (params != 0) {
                self->posY.i.hi += 8;
                EntityExplosionSpawn(1, 0);
                return;
            }
            func_us_801D7D00(2U);
            self->animSet = 0;
            posX = self->posX.i.hi;
            posY = self->posY.i.hi;
            self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 1);
            if (self->primIndex != -1) {
                self->flags |= FLAG_HAS_PRIMS;
                prim = &g_PrimBuf[self->primIndex];
                prim->tpage = 0x1A;
                prim->clut = 0x15F;
                prim->u0 = prim->u2 = 0;
                prim->u1 = prim->u3 = 0x3F;
                prim->v0 = prim->v1 = 0xC0;
                prim->v2 = prim->v3 = 0xFF;
                prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS |
                                 DRAW_UNK02 | DRAW_TRANSP;
                prim->priority = self->zPriority - 2;

                prim->r0 = prim->g0 = prim->b0 = prim->r1 = prim->g1 =
                    prim->b1 = prim->r2 = prim->g2 = prim->b2 = prim->r3 =
                        prim->g3 = prim->b3 = 0x80;

                prim->x0 = prim->x2 = posX - self->ext.et_801D8150.unk94;
                prim->x1 = prim->x3 = posX + self->ext.et_801D8150.unk94;
                prim->y0 = prim->y1 = posY - self->ext.et_801D8150.unk94;
                prim->y2 = prim->y3 = posY + self->ext.et_801D8150.unk94;
            }
            self->ext.et_801D8150.unk86 = 0x18;
            return;
        }
        break;
    case 9:
        if (--self->ext.et_801D8150.unk86) {
            posX = self->posX.i.hi;
            posY = self->posY.i.hi;
            if (self->primIndex != -1) {
                prim = &g_PrimBuf[self->primIndex];
                if (prim->b3 > 8) {
                    prim->b3 -= 6;
                }
                prim->r0 = prim->g0 = prim->b0 = prim->r1 = prim->g1 =
                    prim->b1 = prim->r2 = prim->g2 = prim->b2 = prim->r3 =
                        prim->g3 = prim->b3;
                self->ext.et_801D8150.unk94 += 4;
                prim->x0 = prim->x2 = posX - self->ext.et_801D8150.unk94;
                prim->x1 = prim->x3 = posX + self->ext.et_801D8150.unk94;
                prim->y0 = prim->y1 = posY - self->ext.et_801D8150.unk94;
                prim->y2 = prim->y3 = posY + self->ext.et_801D8150.unk94;
            }
        } else {
            DestroyEntity(self);
        }
        return;
    }

    if ((self->step < 7) && (params != 0) && (params != 0xB)) {
        if ((params ^ g_GameTimer) & 1) {
            self->hitboxState = 0;
        } else {
            self->hitboxState = 3;
        }
    }
    self->ext.et_801D8150.unk7C =
        self->ext.et_801D8150.unk88 +
        ((rsin(self->ext.et_801D8150.unk7E) * self->ext.et_801D8150.unk82) >>
        0xC);
    if (!(g_GameTimer & 7) || (self->step > 6)) {
        self->ext.et_801D8150.unk80++;
        self->ext.et_801D8150.unk80 &= 0xF;
    }
    i = 0;
    if (params == 0) {
        i = D_us_80182324[self->ext.et_801D8150.unk80];
    }
    if (params == 1) {
        i = 0x30;
    }
    if (params == 2) {
        i = 0x20;
    }
    if (params == 3) {
        i = 0x10;
    }
    if (params == 4) {
        i = 0x8;
    }
    i += 0x100;

    self->rotY = self->rotX = i;
    if ((params != 0) && (self->step < 8)) {
        self--;
        posX = self->posX.val;
        posY = self->posY.val;
        temp_s0 = self->ext.et_801D8150.unk7C;
        self++;
        if (params == 0xB) {
            self->posX.val = posX;
            self->posY.val = posY;
        } else {
            self->posX.val = posX + (rcos(temp_s0) << 4) * 7;
            self->posY.val = posY - (rsin(temp_s0) << 4) * 7;
        }
    }
}

INCLUDE_ASM("st/no0/nonmatchings/57C20", func_us_801D8DF0);

INCLUDE_ASM("st/no0/nonmatchings/57C20", func_us_801D8FFC);

void func_us_801D91C4(Entity* self) {
    s16 random;
    Entity* fakeEntity = self; // !FAKE

    if (self->step == 0) {
        self->params = 1;
        EntityExplosion(fakeEntity);
        self->zPriority = PLAYER.zPriority + 0x20;
        random = rand() & 0x7FF;
        self->velocityX = rcos(random) << 4 << 2;
        self->velocityY = -(rsin(random) << 4) << 2;
    } else {
        self->posX.val += self->velocityX;
        EntityExplosion(fakeEntity);
    }
}

extern u16 D_us_80180BD8[];
extern u16 D_us_80180BDE[];
extern u16 D_us_8018234C[];
extern u16 D_us_80182354[];
extern u8 D_us_80182364[];
extern u8 D_us_80182390[];
extern u8 D_us_801823A0[];
extern u8 D_us_801823B0[];
extern u8 D_us_801823B8[];
extern u8 D_us_801823C4[];
extern u8 D_us_801823E4[];
extern u8 D_us_801823F4[];
extern u8 D_us_8018243C[];
extern u16 D_us_80182454[];

void func_us_801D9264(Entity* self) {
    RECT clipRect;
    DRAWENV drawEnv;
    DR_ENV* dr_env;
    Entity* newEntity;
    Primitive* prim;
    s16 angle;
    s32 i;
    s32 posX;
    s32 posY;
    s32 colRet;
    s32 primIndex;
    u16 temp_v0_13;
    u16 temp_v0_15;

    if ((g_Player.status & PLAYER_STATUS_UNK40000) && (self->step < 9)) {
        SetStep(9);
    }
    if ((self->flags & FLAG_DEAD) && (self->step < 10)) {
        self->hitboxState = 0;
        PlaySfxPositional(0x757);
        SetStep(10);
    }
    switch (self->step) {
    case 0:
        InitializeEntity(&D_us_80180BD8);
        self->animCurFrame = 1;
        /* fallthrough */
    case 1:
        if (UnkCollisionFunc3(D_us_80182354) & 1) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            SetStep(2);
        }
        break;
    case 2:
        if (self->step_s == 0) {
            self->ext.et_801D9264.timer = 0x40;
            self->step_s++;
        }
        AnimateEntity(D_us_80182390, self);
        if (self->ext.et_801D9264.timer == 0x20) {
            self->facingLeft ^= 1;
        }
        if ((self->facingLeft == ((GetSideToPlayer() & 1) ^ 1)) &&
            (GetDistanceToPlayerX() < 0x48)) {
            SetStep(5);
        }
        if (!--self->ext.et_801D9264.timer) {
            SetStep(3);
        }
        break;
    case 3:
        switch (self->step_s) {
        case 0:
            if (!AnimateEntity(D_us_801823E4, self)) {
                self->ext.et_801D9264.y =
                    self->posY.i.hi + g_Tilemap.scrollY.i.hi - 0x20;
                SetSubStep(1);
            }
            break;
        case 1:
            self->velocityY = FIX(-4);
            self->velocityX = 0;
            self->animCurFrame = 0x15;
            self->step_s++;
            /* fallthrough */
        case 2:
            MoveEntity();
            self->velocityY += FIX(3.0 / 16);
            posY = self->posY.i.hi + g_Tilemap.scrollY.i.hi;
            posY -= self->ext.et_801D9264.y;
            if ((posY <= 0) || (self->velocityY > 0)) {
                self->step_s++;
            }
            break;
        case 3:
            AnimateEntity(D_us_801823B8, self);
            if (self->animFrameIdx == 3 && self->animFrameDuration == 0) {
                PlaySfxPositional(SFX_WING_FLAP_A);
            }
            posY = self->posY.i.hi + g_Tilemap.scrollY.i.hi;
            posY -= self->ext.et_801D9264.y;
            if (posY == 0) {
                self->ext.et_801D9264.timer = 0x80;
                self->velocityY = 0;
                self->step_s++;
            } else if (posY < 0) {
                self->posY.i.hi++;
            } else {
                self->posY.i.hi--;
            }
            break;
        case 4:
            AnimateEntity(D_us_801823B8, self);
            if (self->animFrameIdx == 3 && self->animFrameDuration == 0) {
                PlaySfxPositional(SFX_WING_FLAP_A);
            }
            colRet = UnkCollisionFunc2(D_us_8018234C);
            if (colRet & 0x80) {
                self->facingLeft ^= 1;
            }
            if (self->facingLeft) {
                self->velocityX = FIX(0.75);
            } else {
                self->velocityX = FIX(-0.75);
            }

            if (self->ext.et_801D9264.timer == 0) {
                if (colRet == 1) {
                    SetSubStep(5);
                }
            } else {
                self->ext.et_801D9264.timer--;
            }
            break;
        case 5:
            self->animCurFrame = 6;
            if (UnkCollisionFunc3(D_us_80182354) & 1) {
                PlaySfxPositional(SFX_EXPLODE_B);
                SetSubStep(6);
            }
            break;
        case 6:
            if (!AnimateEntity(D_us_8018243C, self)) {
                SetStep(2);
            }
            break;
        }
        break;
    case 5:
        switch (self->step_s) {
        case 0:
            if (self->facingLeft) {
                self->velocityX = FIX(1.5);
            } else {
                self->velocityX = FIX(-1.5);
            }
            self->velocityY = FIX(-4);
            self->animCurFrame = 0x15;
            self->step_s++;
            /* fallthrough */
        case 1:
            MoveEntity();
            self->velocityY += FIX(3.0 / 16);
            if (self->velocityY > 0) {
                self->step_s++;
                if (self->ext.et_801D9264.unk84 == 0) {
                    self->ext.et_801D9264.unk84 = 2;
                    SetStep(7);
                } else {
                    self->ext.et_801D9264.unk84--;
                }
            }
            break;
        case 2:
            self->animCurFrame = 6;
            if (UnkCollisionFunc3(D_us_80182354) & 1) {
                PlaySfxPositional(SFX_EXPLODE_B);
                SetSubStep(3);
            }
            break;
        case 3:
            if (!AnimateEntity(D_us_8018243C, self)) {
                if (GetDistanceToPlayerX() > 0x40) {
                    self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
                }
                SetSubStep(0);

                if (self->ext.et_801D9264.unk84 == 1) {
                    SetStep(6);
                    posX = self->posX.i.hi + g_Tilemap.scrollX.i.hi;
                    if (posX > 0x400) {
                        self->facingLeft = 1;
                        self->ext.et_801D9264.unk85 = 3;
                    }
                    if (++self->ext.et_801D9264.unk85 > 2) {
                        self->ext.et_801D9264.unk85 = 0;
                        SetStep(8);
                    }
                } else {
                    posX = self->posX.i.hi + g_Tilemap.scrollX.i.hi;
                    if (self->facingLeft && posX > g_Tilemap.width - 0x80) {
                        self->facingLeft = 0;
                    } else if (!self->facingLeft && posX < g_Tilemap.x + 0x80) {
                        self->facingLeft = 1;
                    }
                }
            }
        }
        break;
    case 7:
        if (!AnimateEntity(D_us_801823C4, self)) {
            SetStep(5);
            self->step_s = 2;
        }
        if (self->animFrameIdx == 8 && self->animFrameDuration == 0) {
            newEntity = &PLAYER;
            posX = newEntity->posX.i.hi - self->posX.i.hi;
            posY = newEntity->posY.i.hi - self->posY.i.hi;
            if (!self->facingLeft) {
                posX = -posX;
            }
            angle = ratan2(-posY, posX);
            if (angle > 0x280) {
                angle = 0x280;
            }
            if (angle < -0x280) {
                angle = -0x280;
            }
            if (GetDistanceToPlayerY() < 0x60) {
                PlaySfxPositional(SFX_FM_EXPLODE_SWISHES);
                newEntity = AllocEntity(&g_Entities[160], &g_Entities[192]);
                if (newEntity != NULL) {
                    CreateEntityFromEntity(E_ID_44, self, newEntity);
                    newEntity->facingLeft = self->facingLeft;
                    if (self->facingLeft) {
                        newEntity->posX.i.hi += 0x10;
                    } else {
                        newEntity->posX.i.hi -= 0x10;
                    }
                    newEntity->rotZ = angle;
                    newEntity->posY.i.hi -= 0x16;
                    newEntity->zPriority = self->zPriority + 1;
                }
            }
        }
        break;
    case 6:
        if (!AnimateEntity(D_us_801823F4, self)) {
            SetStep(5);
        }
        if ((GetDistanceToPlayerY() < 0x60) && (self->animCurFrame == 0x24) &&
            (self->animFrameDuration == 0)) {
            PlaySfxPositional(SFX_FM_EXPLODE_SWISHES);
            for (i = 0; i < 3; i++) {
                newEntity = AllocEntity(&g_Entities[160], &g_Entities[192]);
                if (newEntity != NULL) {
                    CreateEntityFromEntity(E_ID_44, self, newEntity);
                    newEntity->facingLeft = self->facingLeft;
                    if (self->facingLeft) {
                        newEntity->posX.i.hi += 0x10;
                    } else {
                        newEntity->posX.i.hi -= 0x10;
                    }
                    newEntity->posY.i.hi -= 0x14;
                    newEntity->rotZ = D_us_80182454[i];
                }
            }
        }
        break;
    case 8:
        if (AnimateEntity(D_us_80182364, self) == 0) {
            SetStep(2);
        }
        if ((GetDistanceToPlayerY() < 0x60) &&
            (self->animFrameIdx == 0x9 && self->animFrameDuration == 0)) {
            PlaySfxPositional(0x758);
            PlaySfxPositional(SFX_FM_THUNDER_EXPLODE);
            newEntity = AllocEntity(&g_Entities[160], &g_Entities[192]);
            if (newEntity != NULL) {
                CreateEntityFromEntity(E_ID_45, self, newEntity);
                newEntity->facingLeft = self->facingLeft;
                newEntity->zPriority = self->zPriority + 1;
                if (self->facingLeft) {
                    newEntity->posX.i.hi += 0x20;
                } else {
                    newEntity->posX.i.hi -= 0x20;
                }
                newEntity->posY.i.hi = newEntity->posY.i.hi;
            }
        }
        break;
    case 9:
        switch (self->step_s) {
        case 0:
            if (UnkCollisionFunc3(D_us_80182354) & 1) {
                PlaySfxPositional(0x758);
                self->step_s++;
            }
            break;
        case 1:
            if (!AnimateEntity(D_us_801823A0, self)) {
                SetSubStep(2);
            }
            break;
        case 2:
            if (!(g_Timer & 0xF)) {
                PlaySfxPositional(0x759);
            }
            AnimateEntity(D_us_801823B0, self);
            if ((g_Player.status & PLAYER_STATUS_UNK40000) == 0) {
                SetStep(2);
            }
        }
        break;
    case 10:
        switch (self->step_s) {
        case 0:
            if (self->animCurFrame > 8 && self->animCurFrame < 19) {
                self->animCurFrame = 0x14;
            }
            primIndex = g_api.AllocPrimitives(PRIM_GT4, 8);
            if (primIndex == -1) {
                self->step_s = 0;
                return;
            }
            prim = &g_PrimBuf[primIndex];
            self->primIndex = primIndex;
            self->ext.prim = prim;
            self->flags |= FLAG_HAS_PRIMS;
            dr_env = g_api.func_800EDB08((POLY_GT4*)prim);
            if (dr_env == NULL) {
                DestroyEntity(self);
                return;
            }

            prim->type = PRIM_ENV;
            prim->priority = 0xF;
            if (self->params) {
                prim->priority += 4;
            }
            prim->drawMode = DRAW_DEFAULT;
            drawEnv = g_CurrentBuffer->draw;

            drawEnv.isbg = 1;
            drawEnv.r0 = drawEnv.g0 = drawEnv.b0 = 0;

            posY = self->params ? 0x180 : 0x100;

            clipRect.x = 0;
            clipRect.y = posY;
            clipRect.w = 0x80;
            clipRect.h = 0x80;
            drawEnv.clip = clipRect;
            drawEnv.ofs[0] = 0;
            drawEnv.ofs[1] = 0x100;
            SetDrawEnv(dr_env, &drawEnv);

            prim = prim->next;
            if (g_api.func_800EDB08((POLY_GT4*)prim) == NULL) {
                DestroyEntity(self);
                return;
            }
            prim->type = PRIM_ENV;

            prim->priority = 0x12;
            if (self->params) {
                prim->priority += 4;
            }

            prim->drawMode = DRAW_UNK_800;
            prim = prim->next;
            self->ext.et_801D9264.unkA4 = prim;
            posY = self->params ? 0xFF : 0x7F;
            prim->type = PRIM_GT4;
            prim->tpage = 0x110;
            prim->u1 = prim->u3 = 0x3F;
            prim->u0 = prim->u2 = 0;
            prim->v0 = prim->v1 = posY - 0x70;
            prim->v2 = prim->v3 = posY;
            temp_v0_13 = (u16)self->posX.i.hi;
            prim->x0 = prim->x2 = temp_v0_13 - 0x20;
            prim->x1 = prim->x3 = temp_v0_13 + 0x20;
            temp_v0_15 = (u16)self->posY.i.hi;
            prim->y2 = prim->y3 = temp_v0_15 + 0x28;
            prim->y0 = prim->y1 = temp_v0_15 - 0x48;
            prim->priority = self->zPriority;
            prim->drawMode = DRAW_UNK02;

            prim = prim->next;
            prim->type = PRIM_TILE;
            posY = (self->params != 0) << 7;
            prim->x0 = 0;
            prim->y0 = posY;
            prim->v0 = prim->u0 = 0x80;
            prim->r0 = prim->g0 = prim->b0 = 0;

            prim->priority = 0x11;
            if (self->params) {
                prim->priority += 4;
            }

            prim->drawMode = DRAW_UNK_40 | DRAW_TPAGE | DRAW_TRANSP;

            prim = prim->next;
            while (prim != NULL) {
                prim->drawMode = DRAW_HIDE;
                prim = prim->next;
            }

            self->zPriority = 0x10;

            if (self->params) {
                self->zPriority += 4;
            }

            posY = self->params ? 0x100 : 0x80;

            self->posX.i.hi = 0x20;
            self->posY.i.hi = posY - 0x28;

            self->palette = *D_us_80180BDE;
            self->flags &= ~FLAG_POS_CAMERA_LOCKED;
            self->step_s++;
            break;
        case 1:
            prim = self->ext.prim;
            self->animCurFrame = 0;
            prim->type = PRIM_ENV;

            dr_env = LOW(prim->r1);
            drawEnv = g_CurrentBuffer->draw;
            drawEnv.isbg = 0;
            drawEnv.dtd = 0;

            posY = self->params ? 0x180 : 0x100;

            clipRect.x = 0;
            clipRect.y = posY;
            clipRect.w = 0x80;
            clipRect.h = 0x80;
            drawEnv.clip = clipRect;
            drawEnv.ofs[0] = 0;
            drawEnv.ofs[1] = 0x100;
            SetDrawEnv(dr_env, &drawEnv);

            prim->priority = 0xF;
            if (self->params) {
                prim->priority += 4;
            }

            prim->drawMode = DRAW_DEFAULT;
            self->ext.et_801D9264.y = 0x28;
            self->ext.et_801D9264.timer = 0x10;
            self->step_s++;
            /* fallthrough */
        case 2:
            if (!(g_Timer & 7)) {
                PlaySfxPositional(SFX_FM_EXPLODE_B);
            }
            prim = self->ext.et_801D9264.unkA4;
            posX = Random() & 0x3F;
            posY = self->ext.et_801D9264.y;
            if (!(g_Timer & 0xF)) {
                newEntity = AllocEntity(&g_Entities[STAGE_ENTITY_START],
                                        &g_Entities[TOTAL_ENTITY_COUNT]);
                if (newEntity != NULL) {
                    CreateEntityFromCurrentEntity(E_EXPLOSION, newEntity);
                    newEntity->posX.i.hi = prim->x0 + posX;
                    newEntity->posY.i.hi = prim->y2 + posY - 0x30;
                    newEntity->params = 3;
                }
            }
            newEntity = AllocEntity(&g_Entities[STAGE_ENTITY_START],
                                    &g_Entities[TOTAL_ENTITY_COUNT]);
            if (newEntity != NULL) {
                CreateEntityFromCurrentEntity(E_ID_46, newEntity);
                newEntity->posX.i.hi = (self->posX.i.hi - 0x20) + posX;
                newEntity->posY.i.hi = (self->posY.i.hi + posY) + 4;
                newEntity->params = 1;
                newEntity->facingLeft = colRet;
                newEntity->zPriority = 0x10;
                if (self->params) {
                    newEntity->zPriority += 4;
                }
            }
            if (!--self->ext.et_801D9264.timer) {
                self->ext.et_801D9264.timer = 2;
                self->ext.et_801D9264.y -= 2;
                if (self->ext.et_801D9264.y < -0x28) {
                    self->ext.et_801D9264.timer = 0x40;
                    self->step_s++;
                }
            }
            break;
        case 3:
            if (!--self->ext.et_801D9264.timer) {
                DestroyEntity(self);
                return;
            }
        }
        break;
    case 255:
#include "../pad2_anim_debug.h"
    }
    if (self->animCurFrame > 10 && self->animCurFrame < 15) {
        LOH(self->hitboxOffX) = -0x12;
        LOH(self->hitboxOffY) = 0x11;
        self->hitboxWidth = 0x16;
        self->hitboxHeight = 0x16;
    } else {
        LOH(self->hitboxOffX) = -1;
        LOH(self->hitboxOffY) = 1;
        self->hitboxWidth = 0x13;
        self->hitboxHeight = 0x26;
    }
}

INCLUDE_ASM("st/no0/nonmatchings/57C20", func_us_801DA488);

INCLUDE_ASM("st/no0/nonmatchings/57C20", func_us_801DA6B4);

INCLUDE_ASM("st/no0/nonmatchings/57C20", func_us_801DADD0);
