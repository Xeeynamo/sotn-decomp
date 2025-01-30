// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no1.h"

u8 func_us_801CF57C(u8 arg0, Primitive* prim) {
    switch (arg0) {
    case 0:
        UnkPolyFunc2(prim);
        prim->tpage = 0x1A;
        prim->clut = 0x19D;
        prim->u0 = prim->u2 = 0;
        prim->u1 = prim->u3 = 0x3F;
        prim->v0 = prim->v1 = 0xC0;
        prim->v2 = prim->v3 = 0xFF;
        prim->next->x1 = g_CurrentEntity->posX.i.hi;
        prim->next->y0 = g_CurrentEntity->posY.i.hi;
        LOH(prim->next->r2) = 0x40;
        LOH(prim->next->b2) = 0x40;
        prim->next->b3 = 0x80;
        prim->p3 |= 0x10;
        prim->next->x2 = 0;
        prim->next->y2 = prim->next->x2;
        prim->priority = g_CurrentEntity->zPriority + 3;
        prim->drawMode =
            DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS | DRAW_UNK02 | DRAW_TRANSP;
        UnkPrimHelper(prim);
        PlaySfxPositional(SFX_NOISE_SWEEP_DOWN_A);
        arg0++;
        /* fallthrough */
    case 1:
        prim->next->x2 += 0x300;
        prim->next->y2 = prim->next->x2;
        if (prim->next->x2 > 0x1800) {
            prim->clut = 0x19C;
            prim->next->b3 = 0x28;
            arg0++;
        }
        break;
    case 2:
        prim->next->x2 += 0x180;
        prim->next->y2 = prim->next->x2;
        if (prim->next->x2 > 0x2000) {
            prim->clut = 0x19E;
            prim->u0 = prim->u2 = 0x40;
            prim->u1 = prim->u3 = 0x7F;
            prim->v0 = prim->v1 = 0xC0;
            prim->v2 = prim->v3 = 0xFF;
            prim->drawMode |= DRAW_UNK_400;
            prim->next->b3 = 0x40;
            arg0++;
        }
        break;
    case 3:
        prim->next->x2 += 0x40;
        if (prim->next->x2 > 0x2800) {
            arg0++;
        }
        /* fallthrough */
    case 4:
        prim->next->x2 += 0x40;
        prim->next->y2 = prim->next->x2;
        prim->next->b3 -= 1;
        if (!prim->next->b3) {
            arg0++;
        }
        break;
    }
    UnkPrimHelper(prim);
    return arg0;
}

extern u16 D_us_80182A80[];
extern u16 D_us_80182A88[][2];
extern u8 D_us_80182A98[];
extern u8 D_us_80182A9C[];
extern u8 D_us_80182AAC[];
extern u8 D_us_80182AD4[];
extern u8 D_us_80182B00[];
extern u8 D_us_80182B10[];
extern u8 D_us_80182B1C[];
extern s32 D_us_80182B34[];
extern s16 D_us_80182B4C[][2];

void EntitySwordLord(Entity* self) {
    Collider collider;
    Entity* tempEntity;
    Primitive* prim;
    s16 posX, posY;
    s32 primIndex;
    u8 colRet;
    s32 i;
    s16 xDistance;
    s32 s8;

    if ((self->flags & FLAG_DEAD) && (self->step < 6)) {
        PlaySfxPositional(0x77F);
        self->hitboxState = 0;
        (self + 1)->hitboxState = 0;
        self->animFrameIdx = 0;
        self->animFrameDuration = 0;
        self->step_s = 0;
        self->step = 6;
        self->zPriority -= 1;
        self->ext.et_801CF850.unk84 = 0;
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 2);
        if (primIndex != -1) {
            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = primIndex;
            prim = &g_PrimBuf[primIndex];
            self->ext.et_801CF850.unk88 = prim;
            while (prim != NULL) {
                prim->drawMode = DRAW_HIDE;
                prim = prim->next;
            }
        } else {
            self->ext.et_801CF850.unk88 = NULL;
        }
    }
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitSwordLord);
        self->facingLeft = GetSideToPlayer() & 1;
        tempEntity = self + 1;
        DestroyEntity(tempEntity);
        CreateEntityFromEntity(E_ID_49, self, tempEntity);
        break;
    case 1:
        if (UnkCollisionFunc3(D_us_80182A88) & 1) {
            self->step = 2;
        }
        break;
    case 2:
        AnimateEntity(D_us_80182B1C, self);
        self->facingLeft = GetSideToPlayer() & 1;
        if (GetDistanceToPlayerX() < 0x60) {
            self->animFrameDuration = 0;
            self->animFrameIdx = 0;
            self->ext.et_801CF850.unk7D = D_us_80182A98[Random() & 3];
            self->step = 3;
            if (self->facingLeft) {
                self->velocityX = FIX(1.0);
            } else {
                self->velocityX = FIX(-1.0);
            }
        }
        break;
    case 3:
        AnimateEntity(D_us_80182A9C, self);
        colRet = UnkCollisionFunc2(D_us_80182A80);
        if (colRet & 0x60) {
            self->posX.val -= self->velocityX;
            self->velocityX = -self->velocityX;
        }
        xDistance = GetDistanceToPlayerX();
        if (xDistance > 0x60) {
            if (self->facingLeft) {
                self->velocityX = FIX(-1.0);
            } else {
                self->velocityX = FIX(1.0);
            }
        }
        if (xDistance < 0x40) {
            if (self->facingLeft) {
                self->velocityX = FIX(1.0);
            } else {
                self->velocityX = FIX(-1.0);
            }
        }
        if (self->ext.et_801CF850.unk7C++ > self->ext.et_801CF850.unk7D) {
            self->animFrameIdx = 0;
            self->animFrameDuration = 0;
            self->ext.et_801CF850.unk7C = 0;
            self->velocityX = 0;
            if (Random() % 2) {
                self->step = 4;
            } else {
                self->ext.et_801CF850.unk7E = 1;
                self->step = 5;
            }
        }
        break;
    case 4:
        colRet = UnkCollisionFunc2(D_us_80182A80);
        if (colRet & 0x60) {
            self->posX.val -= self->velocityX;
            self->velocityX = 0;
        }
        if (AnimateEntity(D_us_80182AAC, self) == 0) {
            self->animFrameIdx = 0;
            self->animFrameDuration = 0;
            self->ext.et_801CF850.unk7D = D_us_80182A98[Random() & 3];
            if (self->facingLeft) {
                self->velocityX = FIX(1.0);
            } else {
                self->velocityX = FIX(-1.0);
            }
            self->ext.et_801CF850.unk7E = 0;
            self->step_s = 0;
            self->step = 3;
        }
        if (self->animCurFrame == 9 && !self->step_s) {
            PlaySfxPositional(0x77D);
            PlaySfxPositional(SFX_WHIP_TWIRL_SWISH);
            if (self->facingLeft) {
                self->velocityX = FIX(-4.0);
            } else {
                self->velocityX = FIX(4.0);
            }
            self->step_s = 1;
        }
        if (self->animCurFrame == 0xD) {
            self->velocityX = 0;
            if (!self->ext.et_801CF850.unk7E) {
                if (self->facingLeft) {
                    EntityExplosionVariantsSpawner(self, 4, 1, -16, 30, 1, 4);
                    EntityExplosionVariantsSpawner(self, 4, 1, 16, 30, 1, 4);
                } else {
                    EntityExplosionVariantsSpawner(self, 4, 1, -16, 30, 1, -4);
                    EntityExplosionVariantsSpawner(self, 4, 1, 16, 30, 1, -4);
                }
                self->ext.et_801CF850.unk7E = 1;
            }
        }
        break;
    case 5:
        colRet = UnkCollisionFunc2(D_us_80182A80);
        if (colRet & 0x60) {
            self->posX.val -= self->velocityX;
            self->velocityX = 0;
        }
        self->step_s ^= 1;
        if (AnimateEntity(D_us_80182AD4, self) == 0) {
            self->animFrameIdx = 0;
            self->animFrameDuration = 0;
            self->ext.et_801CF850.unk7D = D_us_80182A98[Random() & 3];
            if (self->facingLeft) {
                self->velocityX = FIX(1.0);
            } else {
                self->velocityX = FIX(-1.0);
            }
            self->ext.et_801CF850.unk7E = 0;
            self->step_s = 0;
            self->step = 3;
        }
        if (self->animCurFrame == 0x13 && self->step_s) {
            if (!self->animFrameDuration) {
                PlaySfxPositional(SFX_STOMP_HARD_E);
            }
            if (self->facingLeft) {
                EntityExplosionVariantsSpawner(self, 2, 1, 8, 30, 0, 4);
            } else {
                EntityExplosionVariantsSpawner(self, 2, 1, -8, 30, 0, -4);
            }
        }
        if (self->animCurFrame == 0x12) {
            if (self->facingLeft) {
                self->velocityX = FIX(-4.0);
            } else {
                self->velocityX = FIX(4.0);
            }
            self->ext.et_801CF850.unk7E = 0;
        }
        if (self->animCurFrame == 0x11) {
            self->velocityX = 0;
            if (!self->ext.et_801CF850.unk7E) {
                if (self->facingLeft) {
                    EntityExplosionVariantsSpawner(self, 5, 3, -16, 30, 0, 4);
                    EntityExplosionVariantsSpawner(self, 5, 3, 16, 30, 0, 4);
                } else {
                    EntityExplosionVariantsSpawner(self, 5, 3, -16, 30, 0, -4);
                    EntityExplosionVariantsSpawner(self, 5, 3, 16, 30, 0, -4);
                }
                PlaySfxPositional(0x77E);
                PlaySfxPositional(SFX_WEAPON_SWISH_B);
                PlaySfxPositional(SFX_STOMP_HARD_D);
                self->ext.et_801CF850.unk7E = 1;
            }
        }
        break;
    case 6:
        switch (self->step_s) {
        case 0:
            if (!(Random() & 7)) {
                tempEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (tempEntity != NULL) {
                    CreateEntityFromEntity(
                        E_INTENSE_EXPLOSION, self, tempEntity);
                    tempEntity->posX.i.hi += 0x20 - (Random() & 0x2F);
                    tempEntity->posY.i.hi += 0x20 - (Random() & 0x3F);
                }
            }
            if (AnimateEntity(D_us_80182B00, self) == 0) {
                tempEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (tempEntity != NULL) {
                    CreateEntityFromEntity(E_EXPLOSION, self, tempEntity);
                    tempEntity->params = 3;
                    PlaySfxPositional(SFX_FAST_STUTTER_EXPLODE);
                }
                self->animFrameIdx = 0;
                self->animFrameDuration = 0;
                self->step_s++;
            }
            break;
        case 1:
            if (self->animCurFrame == 0x1D) {
                tempEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (tempEntity != NULL) {
                    CreateEntityFromEntity(E_SWORD_LORD, self, tempEntity);
                    tempEntity->params = 0;
                    tempEntity->facingLeft = self->facingLeft;
                    tempEntity->step = 7;
                    tempEntity->flags |= FLAG_UNK_2000;
                }
                self->step_s++;
            }
        case 2:
            if (!self->animFrameDuration && self->animFrameIdx == 1) {
                PlaySfxPositional(SFX_ANIME_SWORD_B);
            }
            if (AnimateEntity(D_us_80182B10, self) == 0) {
                s8 = 0;
                for (i = s8; i < 5; i++) {
                    tempEntity =
                        AllocEntity(&g_Entities[224], &g_Entities[256]);
                    if (tempEntity != NULL) {
                        CreateEntityFromEntity(E_SWORD_LORD, self, tempEntity);
                        tempEntity->params = i + 1;
                        tempEntity->facingLeft = self->facingLeft;
                        tempEntity->step = 7;
                        tempEntity->flags |= FLAG_UNK_2000;
                    }
                }
                self->animCurFrame = 0;
                self->ext.et_801CF850.unk7C = 0x30;
                self->step_s++;
            }
            break;
        case 3:
            if (!--self->ext.et_801CF850.unk7C) {
                PlaySfxPositional(SFX_FM_MULTI_EXPLODE);
                DestroyEntity(self);
                return;
            }
            break;
        }
        if (self->step_s) {
            if (self->ext.et_801CF850.unk88 != NULL) {
                prim = self->ext.et_801CF850.unk88;
                self->ext.et_801CF850.unk84 =
                    func_us_801CF57C(self->ext.et_801CF850.unk84, prim);
            }
        }
        break;
    case 7:
        InitializeEntity(g_EInitSwordLord);
        self->hitboxState = 0;
        self->animCurFrame = self->params + 0x1E;
        self->flags |= FLAG_DESTROY_IF_OUT_OF_CAMERA |
                       FLAG_DESTROY_IF_BARELY_OUT_OF_CAMERA |
                       FLAG_UNK_00200000 | FLAG_UNK_2000;
        self->ext.et_801CF850.unk80 = D_us_80182B34[self->params];
        self->zPriority--;
        self->unk6C = 0xA0;
        break;
    case 8:
        MoveEntity();
        self->velocityY += self->ext.et_801CF850.unk80;
        posX = self->posX.i.hi;
        posY = self->posY.i.hi;
        if (self->facingLeft) {
            posX += D_us_80182B4C[self->params][0];
        } else {
            posX -= D_us_80182B4C[self->params][0];
        }
        posY += D_us_80182B4C[self->params][1];
        g_api.CheckCollision(posX, posY, &collider, 0);
        if (self->params < 2) {
            if (collider.effects != EFFECT_NONE) {
                tempEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (tempEntity != NULL) {
                    CreateEntityFromCurrentEntity(E_EXPLOSION, tempEntity);
                    tempEntity->params = 2;
                    tempEntity->posX.i.hi = posX;
                    tempEntity->posY.i.hi = posY;
                }
                DestroyEntity(self);
            }
        } else if (collider.effects != EFFECT_NONE) {
            self->drawFlags |= FLAG_DRAW_UNK8;
            self->step++;
        }
        break;
    case 9:
        posX = self->posX.i.hi;
        posY = self->posY.i.hi;
        if (self->facingLeft) {
            posX += D_us_80182B4C[self->params][0];
        } else {
            posX -= D_us_80182B4C[self->params][0];
        }
        posY += D_us_80182B4C[self->params][1];
        if (Random() & 0xF) {
            tempEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (tempEntity != NULL) {
                CreateEntityFromCurrentEntity(E_EXPLOSION, tempEntity);
                tempEntity->params = 2;
                tempEntity->posX.i.hi = posX;
                tempEntity->posY.i.hi = posY;
            }
        }
        self->unk6C += 0xFC;
        if (!self->unk6C) {
            DestroyEntity(self);
        }
        break;
    case 16:
#include "../pad2_anim_debug.h"
    }
}

extern s8 D_us_80182B64[][4];
extern u8 D_us_80182BB8[];

void func_us_801D04B8(Entity* self) {
    s32 curFrame;
    s8* hitboxPtr;
    Entity* tempEntity;

    if (!self->step) {
        InitializeEntity(D_us_80180AB8);
    }
    tempEntity = self - 1;
    curFrame = tempEntity->animCurFrame;
    if (curFrame > 0x1D) {
        curFrame = 0;
    }
    hitboxPtr = D_us_80182B64[0];
    hitboxPtr += D_us_80182BB8[curFrame] * 4;
    self->hitboxOffX = *hitboxPtr++;
    self->hitboxOffY = *hitboxPtr++;
    self->hitboxWidth = *hitboxPtr++;
    self->hitboxHeight = *hitboxPtr++;
    self->facingLeft = tempEntity->facingLeft;
    self->posX.i.hi = tempEntity->posX.i.hi;
    self->posY.i.hi = tempEntity->posY.i.hi;
    if (tempEntity->entityId != E_SWORD_LORD) {
        DestroyEntity(self);
    }
}
