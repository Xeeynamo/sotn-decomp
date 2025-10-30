// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rtop.h"

extern EInit g_EInitSkullLord;
extern u16 D_us_801805F6;

void EntitySkullLord(Entity* self) {
    Entity* entity;
    s32 i;
    s32 offsetY;
    s32 sideToPlayer;
    s32 temp_s1_2;
    s16 angle;

    if ((self->flags & FLAG_DEAD) && self->step != 4) {
        PlaySfxPositional(SFX_SKULL_LORD_DEATH);
        SetStep(4);
    }

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitSkullLord);
        self->hitboxOffX = 4;
        entity = self + 1;
        CreateEntityFromEntity(E_SKULL_LORD_OUTLINE, self, entity);
        entity->zPriority = self->zPriority - 4;
        entity = self + 2;
        CreateEntityFromEntity(E_SKULL_LORD_FLAMES, self, entity);
        entity->zPriority = self->zPriority - 2;
        break;

    case 1:
        self->step_s = 0;
        if (GetDistanceToPlayerY() < 0x80) {
            SetStep(2);
        }
        break;

    case 2:
        switch (self->step_s) {
        case 0:
            self->velocityY = 0;
            self->ext.skullLord.timer = ((Random() & 7) * 0x10) + 0x10;
            self->ext.skullLord.unk90 = 0;
            self->step_s++;
            // fallthrough

        case 1:
            MoveEntity();
            entity = &PLAYER;
            offsetY = self->posY.i.hi - entity->posY.i.hi;
            if (self->hitFlags & 3) {
                self->velocityX >>= 1;
                self->velocityY >>= 1;
                self->ext.skullLord.unk90 = 0x40;
            }

            if (self->ext.skullLord.unk90) {
                self->ext.skullLord.unk90--;
                self->ext.skullLord.unk8C ^= 1;
            }
            if (offsetY > 0) {
                self->velocityY -= 0x400;
                if (self->velocityY < FIX(-0.5)) {
                    self->velocityY = FIX(-0.5);
                }
            } else {
                self->velocityY += 0x400;
                if (self->velocityY > FIX(0.5)) {
                    self->velocityY = FIX(0.5);
                }
            }
            if (self->facingLeft ^ self->ext.skullLord.unk8C) {
                self->velocityX += FIX(3.0 / 64.0);
                if (self->velocityX >= FIX(1.25)) {
                    self->velocityX = FIX(1.25);
                }
            } else {
                self->velocityX -= FIX(3.0 / 64.0);
                if (self->velocityX <= -FIX(1.25)) {
                    self->velocityX = -FIX(1.25);
                }
            }
            sideToPlayer = (GetSideToPlayer() & 1) ^ 1;
            if (sideToPlayer != self->facingLeft) {
                self->ext.skullLord.unk8C = 1;
                if (GetDistanceToPlayerX() > 0x20) {
                    self->facingLeft ^= 1;
                }
            } else {
                self->ext.skullLord.unk8C = 0;
            }
            if (!--self->ext.skullLord.timer) {
                self->step_s++;
            }
            break;

        case 2:
            MoveEntity();
            self->velocityX -= self->velocityX / 16;
            self->velocityY -= self->velocityY / 16;

            if (abs(self->velocityX) < 0x2000) {
                self->step_s = 0;
            }

            break;
        }

        if (!self->poseTimer) {
            if (!self->pose) {
                PlaySfxPositional(SFX_SKULL_KNOCK_B);
                self->animCurFrame = 1;
                self->poseTimer = (Random() & 0x7F) | 7;
                self->pose = 1;
            } else {
                self->animCurFrame = 2;
                self->poseTimer = (Random() & 0xF) | 3;
                self->pose = 0;
            }
        } else {
            self->poseTimer--;
        }
        if (self->hitFlags & 0x80) {
            SetStep(3);
        }
        break;

    case 3:
        if (!self->step_s) {
            if (GetSideToPlayer() & 1) {
                self->velocityX = FIX(0.75);
            } else {
                self->velocityX = FIX(-0.75);
            }
            self->velocityY = FIX(-2.0);
            self->animCurFrame = 1;
            self->ext.skullLord.timer = 0x60;
            self->step_s++;
        }
        MoveEntity();
        self->velocityX -= (self->velocityX >> 5);
        self->velocityY -= (self->velocityY >> 5);
        if (!--self->ext.skullLord.timer) {
            SetStep(2);
        }
        break;

    case 4:
        switch (self->step_s) {
        case 0:
            self->hitboxState = 0;
            self->ext.skullLord.timer = 0x10;
            self->step_s++;
            // fallthrough

        case 1:
            if (!--self->ext.skullLord.timer) {
                self->step_s++;
            }
            break;

        case 2:
            self->animCurFrame = 3;
            for (i = 0; i < 24; i++) {
                entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (entity != NULL) {
                    CreateEntityFromEntity(E_SKULL_LORD_PIECES, self, entity);
                    angle = (Random() & 0x7F) << 4;
                    temp_s1_2 = (Random() & 0x1F) + 8;
                    entity->ext.skullLord.unk82 = angle;
                    entity->posX.i.hi += ((temp_s1_2 * rcos(angle)) >> 0xC);
                    entity->posY.i.hi -= ((temp_s1_2 * rsin(angle)) >> 0xC);
                    if (Random() & 1) {
                        entity->zPriority = self->zPriority + 1;
                    } else {
                        entity->zPriority = self->zPriority - 1;
                    }
                }
            }
            PlaySfxPositional(SFX_SKELETON_DEATH_B);
            self->drawFlags = FLAG_DRAW_OPACITY;
            self->opacity = 0xC0;
            self->step_s++;
            break;

        case 3:
            self->opacity -= 4;
            if (!self->opacity) {
                self->animCurFrame = 0;
                self->drawMode = self->drawFlags = FLAG_DRAW_DEFAULT;
                self->ext.skullLord.timer = 0x100;
                PlaySfxPositional(SFX_NOISE_SWEEP_DOWN_A);
                self->step_s++;
            }
            break;

        case 4:
            if (!--self->ext.skullLord.timer) {
                DestroyEntity(self);
                return;
            }
            break;
        }
        break;

    case 0xFF:
        FntPrint("charal %x\n", self->animCurFrame);
        if (g_pads[1].pressed & PAD_SQUARE) {
            if (!self->params) {
                self->animCurFrame++;
                self->params |= 1;
            } else {
                break;
            }
        } else {
            self->params = 0;
        }
        if (g_pads[1].pressed & PAD_CIRCLE) {
            if (!self->step_s) {
                self->animCurFrame--;
                self->step_s |= 1;
            }
        } else {
            self->step_s = 0;
        }
        break;
    }

    if (!(self->palette & PAL_UNK_FLAG)) {
        self->palette = g_EInitSkullLord[3] + self->ext.skullLord.unk84;
        self->drawMode = DRAW_TPAGE2 | DRAW_TPAGE;
    } else {
        self->drawMode = DRAW_DEFAULT;
    }

    if (!(g_Timer & 3)) {
        self->ext.skullLord.unk84++;
        if (self->ext.skullLord.unk84 > 4) {
            self->ext.skullLord.unk84 = 0;
        }
    }
}

extern EInit D_us_801805FC;
extern u8 D_us_8018151C[];

void EntitySkullLordOutline(Entity* self) {
    Entity* entity;
    s32 scale;
    s32 opacity;
    s32 shouldDestroy;

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_801805FC);
        self->hitboxState = 0;
        self->drawFlags = FLAG_DRAW_SCALEY | FLAG_DRAW_SCALEX;
        self->drawMode = DRAW_UNK_40 | DRAW_TPAGE2 | DRAW_TPAGE;
        if (self->params) {
            self->drawFlags |= FLAG_DRAW_OPACITY;
            self->animCurFrame = (s16)self->params;
            self->step = 2;
            return;
        }
        self->scaleX = self->scaleY = 0x1E0;
        // fallthrough

    case 1:
        AnimateEntity(D_us_8018151C, self);
        entity = self - 1;

        if (entity->entityId != 0x26) {
            DestroyEntity(self);
            return;
        }

        self->facingLeft = entity->facingLeft;
        self->posX.i.hi = entity->posX.i.hi;
        self->posY.i.hi = entity->posY.i.hi;
        self->ext.skullLord.timer++;
        if (self->ext.skullLord.timer & 2) {
            self->posX.i.hi += 3;
        } else {
            self->posX.i.hi -= 3;
        }

        switch (self->step_s) {
        case 0:
            scale = (rcos(self->ext.skullLord.timer) << 6) >> 0xC;
            self->scaleY = scale + 0x1E0;
            opacity = 0x80;
            if (entity->flags & FLAG_DEAD) {
                self->scaleX = self->scaleY = 0x1E0;
                self->opacity = 0x80;
                self->step_s++;
            } else {
            }
            break;

        case 1:
            opacity = self->opacity;
            self->opacity += 2;
            if (self->opacity > 0xF0) {

                self->step_s++;
            }
            break;

        case 2:
            shouldDestroy = false;
            self->opacity -= 1;

            if (!self->opacity) {
                shouldDestroy = true;
            }

            scale = self->scaleX;
            scale -= 8;

            if (scale < 0) {
                shouldDestroy = true;
                scale = 0;
            }
            self->scaleX = scale;

            scale = self->scaleY;
            scale -= 8;
            if (scale < 0) {
                shouldDestroy = true;
                scale = 0;
            }
            self->scaleY = scale;

            if (shouldDestroy) {
                DestroyEntity(self);
                return;
            }
            break;
        }

        if (!(self->ext.skullLord.timer & 0xF)) {
            entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (entity != NULL) {
                CreateEntityFromEntity(E_SKULL_LORD_OUTLINE, self, entity);
                entity->params = self->animCurFrame;
                entity->facingLeft = self->facingLeft;
                entity->scaleX = self->scaleX;
                entity->scaleY = self->scaleY;
                entity->opacity = opacity;
                entity->zPriority = self->zPriority;
                return;
            }
        }
        break;

    case 2:
        scale = self->opacity;
        scale -= 4;
        if (scale <= 0) {
            DestroyEntity(self);
            return;
        }
        self->opacity = scale;
        break;
    }
}

void EntitySkullLordFlames(Entity* self) {
    Entity* entity;
    Primitive* prim;
    s32 offsetX;
    s32 offsetY;
    s32 distance;
    s32 primIndex;
    s16 angle;

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_801805FC);
        self->palette = 0x1CF;
        self->animCurFrame = 4;
        primIndex = g_api.AllocPrimitives(PRIM_SPRT, 1);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }

        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.prim = prim;
        prim->type = PRIM_GT4;
        prim->tpage = 0x13;
        prim->clut = 0x220; // n.b.! double assignment
        prim->clut = 0x16D;
        prim->u0 = prim->u2 = 0x40;
        prim->u1 = prim->u3 = 0x47;
        prim->v0 = prim->v1 = 0x70;
        prim->v2 = prim->v3 = 0x77;
        prim->priority = self->zPriority + 1;
        prim->drawMode = DRAW_UNK02;
        // fallthrough

    case 1:

        entity = self - 2;
        self->facingLeft = entity->facingLeft;
        offsetX = entity->posX.i.hi;

        if (entity->animCurFrame == 1) {
            if (entity->facingLeft) {
                offsetX += 2;
            } else {
                offsetX -= 2;
            }
            offsetY = entity->posY.i.hi - 5;
        } else {
            if (entity->facingLeft) {
                offsetX++;
            } else {
                offsetX--;
            }
            offsetY = entity->posY.i.hi - 9;
        }
        self->posX.i.hi = offsetX;
        self->posY.i.hi = offsetY;

        if (entity->entityId != 0x26) {
            DestroyEntity(self);
            return;
        }

        if (entity->flags & FLAG_DEAD) {
            self->step++;
        }

        entity = &PLAYER;
        angle = GetAngleBetweenEntities(self, entity);
        offsetX = (rcos(angle) * 4) >> 12;
        self->posX.i.hi += offsetX / 2;
        offsetX = self->posX.i.hi + offsetX;
        offsetY = self->posY.i.hi + (rsin(angle) >> 0xC);

        prim = self->ext.prim;
        prim->x0 = prim->x2 = offsetX - 3;
        prim->x1 = prim->x3 = offsetX + 3;
        prim->y0 = prim->y1 = offsetY - 3;
        prim->y2 = prim->y3 = offsetY + 3;
        break;

    case 2:
        entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (entity != NULL) {
            CreateEntityFromEntity(2, self, entity);
            entity->zPriority = self->zPriority;
            entity->params = 2;
        }
        DestroyEntity(self);
        break;
    }
}

void EntitySkullLordPieces(Entity* self) {
    s32 rand;
    s16 angle;

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_801805FC);
        self->flags |= FLAG_DESTROY_IF_OUT_OF_CAMERA;
        rand = Random() & 3;
        if (rand == 3) {
            rand = 2;
        }
        self->animCurFrame = rand + 9;
        angle = self->ext.skullLord.unk82;
        rand = (Random() & 0xF) + 2;
        self->velocityX = rand * rcos(angle);
        rand = 0x20 - (Random() & 0x1F);
        self->velocityY = -rand * rsin(angle);
        self->drawMode = DRAW_TPAGE2 | DRAW_TPAGE;
        self->drawFlags = FLAG_DRAW_ROTATE;
        break;

    case 1:
        MoveEntity();
        self->velocityY += FIX(0.125);
        if (self->velocityX > 0) {
            self->rotate += 0x80;
        } else {
            self->rotate -= 0x80;
        }
        break;
    }
}
