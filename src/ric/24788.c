#include "ric.h"

Entity* RicGetFreeEntity(s16 start, s16 end);
Entity* RicGetFreeEntityReverse(s16 start, s16 end);

// Similar to same function in DRA
void RicEntityEntFactory(Entity* self) {
    Entity* newEntity;
    s16 unk96Copy;
    s16 i;
    u8 endIndex;
    s16 startIndex;
    u8* data_idx;

    if (self->step == 0) {
        data_idx = &g_RicFactoryBlueprints[self->params];
        self->ext.factory.childId = *data_idx++;
        self->ext.factory.unk94 = *data_idx++;          // index 1
        self->ext.factory.unk96 = *data_idx & 0x3F;     // index 2, lower 6 bits
        self->ext.factory.unk9E = *data_idx >> 7;       // index 2, top bit
        self->ext.factory.unkA2 = *data_idx++ >> 6 & 1; // index 2, 2nd-top bit
        self->ext.factory.unk98 = *data_idx++;          // index 3
        self->ext.factory.unk9C = *data_idx & 0x7;      // index 4, lower 4 bits
        self->ext.factory.unkA4 = *data_idx++ >> 3;     // index 4, upper 4 bits
        self->ext.factory.unk9A = *data_idx;            // index 5
        self->flags |= FLAG_UNK_04000000;

        self->step++;
        switch (self->ext.factory.unkA4) {
        case 0:
            self->flags |= FLAG_UNK_08000000;
            break;
        case 4:
            self->flags |= FLAG_UNK_20000;
        case 2:
        case 9:
            self->flags |= FLAG_UNK_40000;
        case 3:
        case 7:
            self->posX.val = PLAYER.posX.val;
            self->posY.val = PLAYER.posY.val;
            break;
        case 8:
            self->flags |= FLAG_UNK_40000;
            self->posX.val = self->ext.factory.parent->posX.val;
            self->posY.val = self->ext.factory.parent->posY.val;
            break;
        }
    } else {
        switch (self->ext.factory.unkA4) {
        case 0:
            break;
        case 9:
            if (g_Player.unk4E != 0) {
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
            if (PLAYER.step != 25) {
                self->entityId = 0;
                return;
            }
            break;
        case 3:
            self->posX.val = g_Entities->posX.val;
            self->posY.val = PLAYER.posY.val;
            if (PLAYER.step == 0xA) {
                self->entityId = 0;
                return;
            }
            break;
        case 7:
            self->posX.val = g_Entities->posX.val;
            self->posY.val = PLAYER.posY.val;
            if (PLAYER.step != 10) {
            setIdZeroAndReturn:
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

        // !FAKE, this should probably be &D_80154C40[unk9C] or similar,
        // instead of doing &D_80154C40 followed by +=
        data_idx = &D_80154C40[0];
        data_idx += self->ext.factory.unk9C * 2;

        startIndex = *data_idx;
        endIndex = *(data_idx + 1);

        if (self->ext.factory.unk9C == 0) {
            newEntity = RicGetFreeEntityReverse(startIndex, endIndex + 1);
        } else if (self->ext.factory.unk9C == 4) {
            newEntity = &g_Entities[31];
        } else if (self->ext.factory.unk9C == 5) {
            newEntity = &g_Entities[48];
        } else {
            newEntity = RicGetFreeEntity(startIndex, endIndex + 1);
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

void func_80160C38(Entity* entity) {
    if (PLAYER.step != 23) {
        DestroyEntity(entity);
    } else {
        entity->posX.i.hi = PLAYER.posX.i.hi;
        entity->posY.i.hi = PLAYER.posY.i.hi;
        entity->facingLeft = PLAYER.facingLeft;
        if (entity->step == 0) {
            entity->flags = FLAG_UNK_20000 | FLAG_UNK_40000 | FLAG_UNK_04000000;
            entity->hitboxOffX = 0x14;
            entity->hitboxOffY = 0xC;
            entity->hitboxHeight = 9;
            entity->hitboxWidth = 9;
            entity->ext.generic.unkB0 = 0x12;
            func_8015FAB8(entity);
            entity->ext.generic.unk7C.s = entity->hitboxState;
            entity->step++;
        }
        entity->hitboxState = entity->ext.generic.unk7C.s;
        if (PLAYER.animFrameIdx < 2) {
            entity->hitboxState = 0;
        }
        if (PLAYER.animFrameIdx >= 8) {
            DestroyEntity(entity);
        }
    }
}

void func_80160D2C(Entity* self) {
    if (PLAYER.step != 26) {
        DestroyEntity(self);
        return;
    }
    self->posX.i.hi = PLAYER.posX.i.hi;
    self->posY.i.hi = PLAYER.posY.i.hi;
    self->facingLeft = PLAYER.facingLeft;

    if (self->step == 0) {
        self->flags = FLAG_UNK_20000 | FLAG_UNK_40000 | FLAG_UNK_04000000;
        self->hitboxOffX = 0x14;
        self->hitboxHeight = 9;
        self->hitboxWidth = 9;
        self->ext.generic.unkB0 = 0x17;
        func_8015FAB8(self);
        self->step++;
    }

    if (PLAYER.animCurFrame == 140) {
        self->hitboxOffY = 0;
    }

    if (PLAYER.animCurFrame == 141) {
        self->hitboxOffY = 12;
    }

    if (self->hitFlags != 0) {
        g_Player.unk44 |= 0x80;
    } else {
        g_Player.unk44 &= ~0x80;
    }
    self->hitFlags = 0;
}

void func_80160E4C(Entity* self) {
    if (PLAYER.step != 24) {
        DestroyEntity(self);
    } else {
        self->posX.i.hi = PLAYER.posX.i.hi;
        self->posY.i.hi = PLAYER.posY.i.hi;
        self->facingLeft = PLAYER.facingLeft;
        if (self->step == 0) {
            self->flags = FLAG_UNK_20000 | FLAG_UNK_40000 | FLAG_UNK_04000000;
            self->hitboxHeight = 20;
            self->hitboxWidth = 20;
            self->hitboxOffY = 0;
            self->hitboxOffX = 0;
            self->ext.generic.unkB0 = 0x11;
            func_8015FAB8(self);
            self->step++;
        }
        if (PLAYER.animFrameIdx >= 19) {
            DestroyEntity(self);
        }
    }
}

void func_80160F0C(Entity* self) {
    if (PLAYER.step != 8) {
        DestroyEntity(self);
        return;
    }
    self->posX.i.hi = PLAYER.posX.i.hi;
    self->posY.i.hi = PLAYER.posY.i.hi;
    self->facingLeft = PLAYER.facingLeft;
    if (self->step == 0) {
        self->flags = FLAG_UNK_20000 | FLAG_UNK_40000 | FLAG_UNK_04000000;
        self->hitboxOffX = 0xC;
        self->hitboxOffY = -0x1A;
        self->hitboxWidth = 12;
        self->hitboxHeight = 12;
        self->ext.generic.unkB0 = 0x16;
        func_8015FAB8(self);
        self->step++;
    }
}

// Entity ID #2. Created by 6 blueprints:
// 0, 1, 24, 74, 75, 76.
// Matches DRA func_8011B5A4
void func_80160FC4(Entity* self) {
    s16 posX;
    s32 i;

    s16 paramsLo = self->params & 0xFF;
    s16 paramsHi = self->params >> 8;

    if ((g_Player.unk0C & 0x20000) && (paramsHi != 9)) {
        DestroyEntity(self);
        return;
    }
    switch (self->step) {
    case 0:
        self->animSet = 5;
        self->unk4C = D_80154C80;
        self->zPriority = PLAYER.zPriority + 2;
        self->flags = FLAG_UNK_08000000 | FLAG_UNK_100000 | FLAG_UNK_10000;
        self->drawMode = 0x30;
        self->drawFlags = 0xB;
        self->unk6C = 0x60;
        posX = D_80154C50[paramsLo];
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
            for (i = paramsLo * 2; i < 14; i++) {
                if (g_Player.colliders3[D_80154CE4[i]].effects & 3) {
                    break;
                }
            }
            if (i == 14) {
                DestroyEntity(self);
                return;
            }
            self->posX.i.hi = PLAYER.posX.i.hi + D_80154604[D_80154CE4[i]].x;
            self->posY.i.hi = PLAYER.posY.i.hi + D_80154604[D_80154CE4[i]].y;
            self->velocityY = FIX(-0.25);
            self->rotY = self->rotX = D_80154C74[1] + 0x40;
            self->step++;
            return;
        }
        if (paramsHi == 8) {
            for (i = paramsLo * 2; i < 10; i++) {
                if (g_Player.colliders3[D_80154CF4[i]].effects & 3) {
                    break;
                }
            }
            if (i == 10) {
                DestroyEntity(self);
                return;
            }
            self->posX.i.hi = PLAYER.posX.i.hi + D_80154604[D_80154CF4[i]].x;
            self->posY.i.hi = PLAYER.posY.i.hi + D_80154604[D_80154CF4[i]].y;
            self->velocityY = D_80154C5C[paramsLo];
            self->rotY = self->rotX = D_80154C74[paramsLo] + 0x20;
            self->step++;
            return;
        }
        if (paramsHi == 1) {
            if (g_Player.pl_vram_flag & 0x8000) {
                posX /= 2;
            }
        }
        if (self->facingLeft != 0) {
            posX = -posX;
        }
        self->posX.i.hi += posX;
        self->posY.i.hi += 0x18;
        self->rotX = D_80154C74[paramsLo] + 0x40;
        self->velocityY = D_80154C5C[paramsLo];
        if (paramsHi == 1) {
            self->velocityY = FIX(-0.25);
            RicSetSpeedX(-0x3000);
            self->rotX = D_80154C74[1] + 0x40;
        }
        if (paramsHi == 5) {
            self->velocityY = D_80154C5C[4 - paramsLo * 2];
        }
        if (paramsHi == 2) {
            self->velocityY = FIX(-0.5);
            RicSetSpeedX(-0x3000);
            self->rotX = D_80154C74[1] + 0x40;
        }
        self->rotY = self->rotX;
        if (paramsHi == 10) {
            self->posY.i.hi -= 6;
        }
        self->step++;
        return;
    case 1:
        self->unk6C += 0xFE;
        self->posY.val += self->velocityY;
        self->posX.val += self->velocityX;
        if (self->animFrameDuration < 0) {
            DestroyEntity(self);
            return;
        }
        break;
    }
}

// Corresponding DRA function is func_8011E4BC
void func_8016147C(Entity* self) {
    byte stackpad[0x28];
    FakePrim* tilePrim;
    s16 randVar;
    s32 randAngleShift;
    s32 i;
    u16 selfYPos;
    u16 selfXPos;
    u32 upperParams;
    unkStr_8011E4BC* temp_s5;
    u8 thickness;
    s32 var_a2;
    s32 selfstep;

    selfXPos = self->posX.i.hi;
    selfstep = self->step;
    selfYPos = self->posY.i.hi;
    temp_s5 = D_80154DA0[self->params >> 8];
    switch (selfstep) {
    case 0:
        self->primIndex =
            g_api.func_800EDB58(PRIM_TILE_ALT, temp_s5->count + 1);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags = temp_s5->flags;
        switch ((s16)(temp_s5->unkA - 3)) {
        case 5:
            self->ext.et_8011E4BC.unk7C = 0x100;
            break;
        case 4:
            self->ext.et_8011E4BC.unk7C = 0x3F;
            break;
        case 1:
            self->ext.et_8011E4BC.unk7C = 0x2F;
            break;
        case 0:
        case 3:
            self->ext.et_8011E4BC.unk7C = 0x1F;
            break;
        }
        i = 0;
        tilePrim = (FakePrim*)&g_PrimBuf[self->primIndex];
        while (1) {
            tilePrim->drawMode = temp_s5->drawMode;
            tilePrim->priority = PLAYER.zPriority + temp_s5->priority;
            if (tilePrim->next == NULL) {
                tilePrim->w = 0;
                tilePrim->x0 = 0;
                tilePrim->y0 = 0;
                tilePrim->drawMode &= ~DRAW_HIDE;
                break;
            }
            tilePrim->posX.i.hi = selfXPos;
            tilePrim->posY.i.hi = selfYPos;
            tilePrim->posY.i.lo = 0;
            tilePrim->posX.i.lo = 0;
            switch (temp_s5->unkA) {
            case 0:
                randVar = rand();
                randAngleShift = (randVar & 1) + 2;
                tilePrim->velocityX.val = (rcos(randVar) << randAngleShift);
                tilePrim->velocityY.val = -(rsin(randVar) << randAngleShift);
                break;
            case 1:
            case 9:
                tilePrim->velocityX.val = (((rand() & 0x1FF) - 0x100) << 8);
                tilePrim->velocityY.val = (((rand() & 0x1FF) - 0x100) << 8);
                break;
            case 3:
                tilePrim->posX.i.hi = ((selfXPos + (rand() & 0xF)) - 7);
                tilePrim->posY.i.hi = selfYPos - (rand() & 0xF);
                tilePrim->velocityY.val = (FIX(-0.75) - (rand() & 0x7FFF));
                tilePrim->velocityX.val = self->ext.et_8011E4BC.unk8C->unk8;
                tilePrim->delay = ((rand() & 0xF) + 0x10);
                break;
            case 4:
                tilePrim->posX.i.hi = ((selfXPos + (rand() & 0x1F)) - 0x10);
                tilePrim->posY.i.hi = (selfYPos + (rand() & 0x1F)) - 0x14;
                randVar = rand() & 0x1F;
                tilePrim->velocityX.val = D_80175958[randVar];
                tilePrim->velocityY.val = D_801759D8[randVar];
                break;
            case 6:
                tilePrim->posX.i.hi = ((self->posX.i.hi + (rand() & 0xF)) - 8);
                tilePrim->posY.i.hi = (self->posY.i.hi + (rand() & 0xF)) - 4;
                tilePrim->velocityY.val = (rand() + FIX(0.5));
                tilePrim->delay = ((rand() & 0xF) + 0x10);
                break;
            case 7:
                tilePrim->posX.i.hi = selfXPos;
                tilePrim->posY.i.hi = selfYPos;
                if (i < 10) {
                    tilePrim->velocityY.val =
                        -((i * i * FIX(0.09375)) + FIX(0.125));
                } else {
                    tilePrim->velocityY.val =
                        ((i - 10) * (i - 10) * FIX(0.09375)) + FIX(0.125);
                }
                tilePrim->delay = 0x3F;
                break;
            case 8:
                tilePrim->posX.i.hi = selfXPos;
                tilePrim->posY.i.hi = selfYPos;
                tilePrim->velocityX.val = ((rand() - FIX(0.25)) >> 1);
                tilePrim->velocityY.val = -((rand() & 0x1FFF) + FIX(0.375));
                tilePrim->timer = (i * 4);
                break;
            }
            tilePrim->x0 = tilePrim->posX.i.hi;
            tilePrim->y0 = tilePrim->posY.i.hi;
            tilePrim->r0 = temp_s5->r;
            tilePrim->g0 = temp_s5->g;
            tilePrim->b0 = temp_s5->b;
            tilePrim->w = temp_s5->w;
            tilePrim->h = temp_s5->h;
            tilePrim = tilePrim->next;
            i++;
        }
        self->step++;
        break;
    case 1:
        switch (temp_s5->unkA) {
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
            var_a2 = self->ext.et_8011E4BC.unk7C;
            thickness = 3;
            if (var_a2 < 9) {
                thickness = 2;
            }
            if (var_a2 < 4) {
                thickness -= 1;
            }
        }
        tilePrim = (FakePrim*)&g_PrimBuf[self->primIndex];
        while (1) {
            if (tilePrim->next == NULL) {
                tilePrim->w = 0;
                tilePrim->x0 = 0;
                tilePrim->y0 = 0;
                tilePrim->drawMode &= ~DRAW_HIDE;
                return;
            }
            tilePrim->posX.i.hi = tilePrim->x0;
            tilePrim->posY.i.hi = tilePrim->y0;
            switch (temp_s5->unkA) {
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
                tilePrim->posY.val =
                    (tilePrim->posY.val + tilePrim->velocityY.val);
                if (--tilePrim->delay < 0) {
                    tilePrim->drawMode |= 8;
                }
                break;
            case 4:
                tilePrim->posX.val += tilePrim->velocityX.val;
                tilePrim->posY.val += tilePrim->velocityY.val;
                // There is probably a clever way to write this
                tilePrim->velocityY.val =
                    (tilePrim->velocityY.val - (tilePrim->velocityY.val >> 5));
                if (!(var_a2 & 7)) {
                    tilePrim->velocityX.val = (tilePrim->velocityX.val >> 1);
                    tilePrim->velocityY.val >>= 1;
                    if (var_a2 & 0x20) {
                        tilePrim->velocityY.val >>= 1;
                    }
                    if (var_a2 == 0x18) {
                        tilePrim->drawMode = 2;
                    }
                }
                tilePrim->h = thickness;
                tilePrim->w = thickness;
                break;
            case 8:
                if (tilePrim->timer == 0) {
                    tilePrim->drawMode &= ~DRAW_HIDE;
                    tilePrim->r0 += 0xFF;
                    tilePrim->g0 += 0xFF;
                    tilePrim->b0 += 0xFF;
                    tilePrim->posY.val =
                        (tilePrim->posY.val + tilePrim->velocityY.val);
                    tilePrim->posX.val =
                        (tilePrim->posX.val + tilePrim->velocityX.val);
                    if ((*D_80097448 == 0) ||
                        (((PLAYER.posY.i.hi - *D_80097448) + 0x19) >=
                         tilePrim->posY.i.hi)) {
                        tilePrim->drawMode |= DRAW_HIDE;
                    }
                } else {
                    tilePrim->timer--;
                }
                break;
            }

            tilePrim->x0 = tilePrim->posX.i.hi;
            tilePrim->y0 = tilePrim->posY.i.hi;
            tilePrim = tilePrim->next;
        }
    }
}

// DRA function is func_8011EDA8
void func_80161C2C(Entity* self) {
    u16 params = self->params;
    s16 paramsHi = self->params >> 8;
    s32 step = self->step;
    s32 rnd;

    switch (step) {
    case 0:
        if (paramsHi == 1) {
            self->rotX = 0xC0;
            self->rotY = 0xC0;
            self->drawFlags = FLAG_DRAW_ROTX | FLAG_DRAW_ROTY;
            self->animSet = ANIMSET_DRA(2);
            self->unk4C = D_80154E04;
        }

        if ((paramsHi == 0) || (paramsHi == 2)) {
            if (params & 3) {
                self->unk4C = D_80154DC8;
                self->rotX = 0x120;
                self->rotY = 0x120;
                self->drawFlags = FLAG_DRAW_ROTX | FLAG_DRAW_ROTY;
                self->animSet = ANIMSET_DRA(2);
            } else {
                self->animSet = ANIMSET_DRA(5);
                self->unk4C = D_80154C80;
                self->palette = 0x8170;
            }
        }
        self->flags = FLAG_UNK_20000 | FLAG_UNK_100000 | FLAG_UNK_08000000;

        if (rand() % 4) {
            self->zPriority = PLAYER.zPriority + 2;
        } else {
            self->zPriority = PLAYER.zPriority - 2;
        }

        if (paramsHi == 2) {
            self->posX.i.hi = PLAYER.posX.i.hi + (rand() % 44) - 22;
        } else {
            self->posX.i.hi = PLAYER.posX.i.hi + (rand() & 15) - 8;
        }

        rnd = rand() & 31;
        self->posY.i.hi = PLAYER.posY.i.hi + PLAYER.hitboxOffY + rnd - 16;
        self->velocityY = FIX(-0.5);
        self->velocityX = PLAYER.velocityX >> 2;
        self->step++;
        break;

    case 1:
        self->rotX -= 4;
        self->rotY -= 4;
        self->posY.val += self->velocityY;
        self->posX.val += self->velocityX;
        if ((self->animFrameIdx == 8) && (self->unk4C != D_80154C80)) {
            self->drawMode = DRAW_TPAGE;
            if (!(params & 1) && (self->animFrameDuration == step)) {
                RicCreateEntFactoryFromEntity(self, FACTORY(0x400, 4), 0);
            }
        }

        if ((self->animFrameIdx == 16) && (self->unk4C == D_80154C80)) {
            self->drawMode = DRAW_TPAGE;
        }

        if (self->animFrameDuration < 0) {
            DestroyEntity(self);
        }
        break;
    }
}

void func_80161EF8(Entity* self) {
    switch (self->step) {
    case 0:
        self->animSet = ANIMSET_DRA(2);
        self->unk4C = &D_80154E38;
        self->flags =
            FLAG_UNK_20000 | FLAG_UNK_100000 | FLAG_UNK_10000 | FLAG_UNK_40000;
        self->zPriority = PLAYER.zPriority + 4;
        self->velocityY = (rand() & 0x3FFF) - 0x10000;
        self->step++;
        break;

    case 1:
        if ((self->animFrameIdx == 6) &&
            (self->animFrameDuration == self->step) && (rand() & 1)) {
            RicCreateEntFactoryFromEntity(self, FACTORY(0, 4), 0);
        }
        self->posY.val += self->velocityY;
        if (self->animFrameDuration < 0) {
            DestroyEntity(self);
        }
        break;
    }
}

void func_80161FF0(Entity* self) {
    Primitive* prim;

    u16 posX = self->posX.i.hi;
    u16 posY = self->posY.i.hi;
    unkStr80154E5C* temp_s2 = &D_80154E5C[(s16)self->params];

    switch (self->step) {
    case 0:
        self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 1);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        g_api.PlaySfx(0x881);
        self->ext.et_80161FF0.unk7C = 0x100;
        prim = &g_PrimBuf[self->primIndex];
        prim->u0 = temp_s2->uBase;
        prim->v0 = temp_s2->vBase;
        prim->u1 = temp_s2->uBase + 0x7F;
        prim->v1 = temp_s2->vBase;
        prim->u2 = temp_s2->uBase;
        prim->v2 = temp_s2->vBase + 0x6F;
        prim->u3 = temp_s2->uBase + 0x7F;
        prim->v3 = temp_s2->vBase + 0x6F;
        prim->tpage = temp_s2->tpage;
        prim->clut = temp_s2->clut;
        prim->priority = PLAYER.zPriority + 8;
        prim->drawMode = 0x31;
        self->velocityX = temp_s2->velocityX;
        self->velocityY = temp_s2->velocityY;
        self->posX.i.hi += temp_s2->xOffset;
        posX = self->posX.i.hi;
        posY = self->posY.i.hi + temp_s2->yOffset;
        self->posY.i.hi = posY;
        self->flags = FLAG_UNK_04000000 | FLAG_HAS_PRIMS | FLAG_UNK_10000;
        self->step++;
        break;
    case 1:
        self->ext.et_80161FF0.unk7C -= 8;
        self->posX.val += self->velocityX;
        self->posY.val += self->velocityY;
        if (self->ext.et_80161FF0.unk7C < 25) {
            self->ext.et_80161FF0.unk7E = temp_s2->timerInit;
            self->step++;
        }
        break;
    case 2:
        if (--self->ext.et_80161FF0.unk7E == 0) {
            self->step++;
        }
        break;
    case 3:
        self->ext.et_80161FF0.unk7C -= 2;
        if (self->ext.et_80161FF0.unk7C < 0) {
            DestroyEntity(self);
            return;
        }
        break;
    }
    prim = &g_PrimBuf[self->primIndex];
    prim->x0 = posX + (((rcos(0x600) >> 4) * self->ext.et_80161FF0.unk7C) >> 8);
    prim->y0 = posY - (((rsin(0x600) >> 4) * self->ext.et_80161FF0.unk7C) >> 8);
    prim->x1 = posX + (((rcos(0x200) >> 4) * self->ext.et_80161FF0.unk7C) >> 8);
    prim->y1 = posY - (((rsin(0x200) >> 4) * self->ext.et_80161FF0.unk7C) >> 8);
    prim->x2 = posX + (((rcos(0xA00) >> 4) * self->ext.et_80161FF0.unk7C) >> 8);
    prim->y2 = posY - (((rsin(0xA00) >> 4) * self->ext.et_80161FF0.unk7C) >> 8);
    prim->x3 = posX + (((rcos(0xE00) >> 4) * self->ext.et_80161FF0.unk7C) >> 8);
    prim->y3 = posY - (((rsin(0xE00) >> 4) * self->ext.et_80161FF0.unk7C) >> 8);
    return;
}

void func_801623E0(Entity* entity) {
    Primitive* prim;
    s16 primIndex;

    entity->posX.val = g_Entities->posX.val;
    entity->posY.val = PLAYER.posY.val;
    switch (entity->step) {
    case 0:
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 1);
        entity->primIndex = primIndex;
        if (primIndex == -1) {
            DestroyEntity(entity);
            return;
        }
        entity->ext.generic.unk7E.modeU16 = 32;
        entity->ext.generic.unk7C.s = 32;
        prim = &g_PrimBuf[entity->primIndex];
        prim->u2 = 64;
        prim->u0 = 64;
        prim->v1 = 192;
        prim->v0 = 192;
        prim->u3 = 127;
        prim->u1 = 127;
        prim->v3 = 255;
        prim->v2 = 255;
        prim->tpage = 0x1A;
        prim->clut = 0x13E;
        prim->priority = PLAYER.zPriority + 8;
        prim->drawMode = DRAW_DEFAULT;
        entity->flags = FLAG_UNK_10000 | FLAG_UNK_40000 | FLAG_UNK_04000000 |
                        FLAG_HAS_PRIMS;
        entity->step++;
        break;

    case 1:
        entity->ext.generic.unk7C.s++;
        entity->ext.generic.unk7E.modeU16++;
        if (entity->ext.generic.unk7C.s >= 45) {
            DestroyEntity(entity);
            return;
        }
        break;
    }

    prim = &g_PrimBuf[entity->primIndex];
    prim->x0 = entity->posX.i.hi - entity->ext.generic.unk7C.s;
    prim->y0 = entity->posY.i.hi - entity->ext.generic.unk7E.modeU16;
    prim->x1 = entity->posX.i.hi + entity->ext.generic.unk7C.s;
    prim->y1 = entity->posY.i.hi - entity->ext.generic.unk7E.modeU16;
    prim->x2 = entity->posX.i.hi - entity->ext.generic.unk7C.s;
    prim->y2 = entity->posY.i.hi + entity->ext.generic.unk7E.modeU16;
    prim->x3 = entity->posX.i.hi + entity->ext.generic.unk7C.s;
    prim->y3 = entity->posY.i.hi + entity->ext.generic.unk7E.modeU16;
    prim->clut = (LOH(g_Timer) & 1) + 0x13E;
}

void func_80162604(Entity* entity) {
    Primitive* prim;
    s16 primIndex;

    entity->posX.val = g_Entities->posX.val;
    entity->posY.val = PLAYER.posY.val;
    switch (entity->step) {
    case 0:
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 1);
        entity->primIndex = primIndex;
        if (primIndex != -1) {
            entity->ext.generic.unk7E.modeU16 = 0;
            entity->ext.generic.unk7C.s = 0;
            prim = &g_PrimBuf[entity->primIndex];
            prim->v1 = 192;
            prim->v0 = 192;
            prim->u3 = 63;
            prim->u1 = 63;
            prim->v3 = 255;
            prim->v2 = 255;
            prim->tpage = 0x1A;
            prim->u2 = 0;
            prim->u0 = 0;
            prim->clut = 0x162;
            prim->priority = PLAYER.zPriority - 4;
            prim->drawMode = DRAW_DEFAULT;
            entity->flags = FLAG_UNK_10000 | FLAG_UNK_40000 |
                            FLAG_UNK_04000000 | FLAG_HAS_PRIMS;
            entity->step++;
            goto def;
        } else {
            DestroyEntity(entity);
            break;
        }

    case 1:
        entity->ext.generic.unk7C.s += 8;
        entity->ext.generic.unk7E.modeU16 += 8;
        if (entity->ext.generic.unk7C.s < 0x20) {
            goto def;
        }

    case 2:
        entity->step++;
        goto def;

    case 3:
        entity->ext.generic.unk7C.s -= 8;
        entity->ext.generic.unk7E.modeU16 -= 8;
        if (entity->ext.generic.unk7C.s >= 5) {
            goto def;
        } else {

            DestroyEntity(entity);
        }
        break;

    def:
    default:
        prim = &g_PrimBuf[entity->primIndex];
        prim->x0 = entity->posX.i.hi - entity->ext.generic.unk7C.s;
        prim->y0 = entity->posY.i.hi - entity->ext.generic.unk7E.modeU16;
        prim->x1 = entity->posX.i.hi + entity->ext.generic.unk7C.s;
        prim->y1 = entity->posY.i.hi - entity->ext.generic.unk7E.modeU16;
        prim->x2 = entity->posX.i.hi - entity->ext.generic.unk7C.s;
        prim->y2 = entity->posY.i.hi + entity->ext.generic.unk7E.modeU16;
        prim->x3 = entity->posX.i.hi + entity->ext.generic.unk7C.s;
        prim->y3 = entity->posY.i.hi + entity->ext.generic.unk7E.modeU16;
        break;
    }
}

void func_80162870(Entity* self) {
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
        prim->drawMode = 8;
        self->flags = FLAG_HAS_PRIMS | FLAG_UNK_10000;
        if (params == 3) {
            self->flags |= FLAG_UNK_04000000;
        }
        g_api.PlaySfx(0x881);
        self->ext.et_80162870.unk82 = 12;
        self->step++;
        break;
    case 1:
        self->posX.val += self->velocityX;
        self->posY.val += self->velocityY;
        if (--self->ext.et_80162870.unk82 == 0) {
            self->drawFlags = 3;
            self->rotX = self->rotY = 0x100;
            self->ext.et_80162870.unk82 = 0x10;
            self->step++;
            g_PrimBuf[self->primIndex].drawMode = 0x31;
        }
        break;
    case 2:
        self->rotX = self->rotY = self->ext.et_80162870.unk82 * 0x10;
        if (--self->ext.et_80162870.unk82 == 0) {
            self->animCurFrame = 0;
            g_api.PlaySfx(0x69D);
            self->velocityY = FIX(-9);
            self->step++;
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
    return;
}

void func_80162C7C(Entity* self) {}
