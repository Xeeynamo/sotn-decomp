// SPDX-License-Identifier: AGPL-3.0-or-later
static u8 D_us_8018281C[] = {4, 1, 9, 2, 9, 3, 9, 4, 9, 5, 9, 6, 16, 1, 0, 0};
static u8 D_us_8018282C[] = {2, 1, 4, 2, 4, 3, 4, 4, 4, 5, 4, 6, 5, 1, 0, 0};
static u8 D_us_8018283C[] = {9, 6, 9, 5, 9, 4, 9, 3, 9, 2, 9, 1, 0, 0};
static u8 D_us_8018284C[] = {4, 6, 4, 5, 4, 4, 4, 3, 4, 2, 4, 1, 0, 0};
static u8* D_us_8018285C[] = {D_us_8018281C, D_us_8018282C};
static u8* D_us_80182864[] = {D_us_8018283C, D_us_8018284C};
static u8 D_us_8018286C[] = {
    6, 7, 5, 8, 5, 9, 2, 10, 2, 11, 2, 10, 6, 12, 0, 0};
static u8 D_us_8018287C[] = {8, 1, 8, 15, 8, 14, 8, 13, -1, 0};
static u8 D_us_80182888[] = {8, 13, 8, 14, 8, 15, 8, 1, -1, 0};
static u8 D_us_80182894[] = {
    1, 1, 1, 23, 1, 1,  1, 23, 1, 1,  1, 23, 6, 16, 6, 17, 6, 18, 6, 17, 6, 16,
    6, 1, 3, 19, 3, 20, 3, 21, 3, 22, 4, 21, 4, 20, 4, 19, 6, 1,  0, 0};
static u8 D_us_801828C0[] = {6, 1, 4, 24, 6, 25, 4, 24, 6, 1, 0, 0};
static u8 D_us_801828CC[] = {65, 1, 6, 26, 6, 27, 6, 28, 0, 0};
static u8 D_us_801828D8[] = {22, 13, 6, 29, 6, 30, 6, 31, 0, 0};
static u8 D_us_801828E4[] = {
    1, 32, 1, 33, 1, 34, 1, 35, 1, 36, 1, 37, 1, 38, 1, 39, 0, 0};
static s16 D_us_801828F8[] = {0, 26, 8, 0};
static s16 D_us_80182900[] = {0, 26, 0, 4, 12, -4, -24, 0};
static s16 D_us_80182910[] = {24, 32, 0xFF, 0};
static s16 unused[] = {0, 26, 8, 0, 0, 26, 0, 4, 12, -4, -24, 0};
static s16 D_us_80182930[] = {0, 6, 3, 5, 8, 2, 7, 0};
static s16 D_us_80182940[] = {0, 7, 6, 3, 5, 8, 2, 0};
static Point32 D_us_80182950[] = {
    {FIX(0), FIX(-5)},
    {FIX(0.125), FIX(-5.5)},
    {FIX(-0.5), FIX(-5.5)},
    {FIX(0.5), FIX(-5)},
    {FIX(-0.5), FIX(-5)}};
static Point16 D_us_80182978[] = {{0, 0},    {15, -27}, {33, -33}, {35, -36},
                                  {-27, -7}, {-47, -1}, {-65, 7},  {-72, 10}};

// Seems to be some kind of helper for EntityWereskeleton
void func_us_801CDDD8(u8 step) {
    g_CurrentEntity->pose = 0;
    g_CurrentEntity->poseTimer = 0;
    g_CurrentEntity->ext.wereskeleton.unk7C = 0;
    g_CurrentEntity->ext.wereskeleton.unk7D = 0;
    g_CurrentEntity->ext.wereskeleton.unk7E = 0;
    g_CurrentEntity->step = step;
}

void EntityWereskeleton(Entity* self) {
    Entity* tempEntity;
    s32 i;

    if ((self->flags & FLAG_DEAD) && (self->step < 0xB)) {
        PlaySfxPositional(SFX_SKELETON_DEATH_B);
        if (self->step == 7) {
            self->step = 12;
        } else {
            self->step = 11;
        }
    }
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitWereskeleton);
        CreateEntityFromEntity(E_ID_42, self, self + 1);
        break;

    case 1:
        if (UnkCollisionFunc3(D_us_80182900) & 1) {
            self->step++;
        }
        break;

    case 2:
        AnimateEntity(D_us_801828C0, self);
        self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        if (GetDistanceToPlayerX() < 0x70) {
            self->ext.wereskeleton.unk80 = (Random() & 1);
            self->ext.wereskeleton.unk7F = (Random() & 1) + 1;
            func_us_801CDDD8(3);
        }
        break;

    case 3:
        UnkCollisionFunc2(D_us_801828F8);
        if (self->ext.wereskeleton.unk7D) {
            if (self->poseTimer == 0) {
                if (self->facingLeft) {
                    self->posX.i.hi += D_us_80182930[self->animCurFrame];
                } else {
                    self->posX.i.hi -= D_us_80182930[self->animCurFrame];
                }
            }
        } else {
            self->ext.wereskeleton.unk7D = 1;
        }
        if (CheckColliderOffsets(D_us_80182910, self->facingLeft) == 0) {
            self->ext.wereskeleton.unk7E |= 1;
        }
        if (!AnimateEntity(D_us_8018285C[self->ext.wereskeleton.unk80], self)) {
            if (self->facingLeft) {
                self->posX.i.hi -= D_us_80182930[self->animCurFrame];
            } else {
                self->posX.i.hi += D_us_80182930[self->animCurFrame];
            }
            if (!--self->ext.wereskeleton.unk7F) {
                self->ext.wereskeleton.unk7E |= 1;
            }
        }
        if (self->ext.wereskeleton.unk7E) {
            self->ext.wereskeleton.unk80 = (Random() & 1);
            self->ext.wereskeleton.unk7F = (Random() & 1) + 1;
            func_us_801CDDD8(4);
        }
        break;

    case 4:
        UnkCollisionFunc2(D_us_801828F8);
        if (self->poseTimer == 0) {
            if (self->facingLeft) {
                self->posX.i.hi -= D_us_80182940[self->animCurFrame];
            } else {
                self->posX.i.hi += D_us_80182940[self->animCurFrame];
            }
        }
        if (CheckColliderOffsets(D_us_80182910, self->facingLeft ^ 1) == 0) {
            self->ext.wereskeleton.unk7E |= 1;
        }
        if (!AnimateEntity(D_us_80182864[self->ext.wereskeleton.unk80], self)) {
            if (!--self->ext.wereskeleton.unk7F) {
                self->ext.wereskeleton.unk7E |= 1;
            }
        }
        if (self->ext.wereskeleton.unk7E) {
            self->animCurFrame = 1;
            if (self->facingLeft) {
                self->posX.i.hi += D_us_80182940[self->animCurFrame];
            } else {
                self->posX.i.hi -= D_us_80182940[self->animCurFrame];
            }
            if (self->step_s) {
                func_us_801CDDD8(9);
            } else {
                func_us_801CDDD8(8);
            }
            self->step_s ^= 1;
        }
        break;

    case 5:
        if (!AnimateEntity(D_us_8018287C, self)) {
            if (self->facingLeft) {
                self->velocityX = FIX(1.25);
            } else {
                self->velocityX = FIX(-1.25);
            }
            func_us_801CDDD8(7);
        }
        break;

    case 6:
        if (!AnimateEntity(D_us_80182888, self)) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            self->ext.wereskeleton.unk80 = (Random() & 1);
            self->ext.wereskeleton.unk7F = (Random() & 1) + 1;
            func_us_801CDDD8(3);
        }
        break;

    case 7:
        UnkCollisionFunc2(D_us_801828F8);
        AnimateEntity(D_us_8018286C, self);
        if (self->animCurFrame == 7) {
            if (self->facingLeft) {
                self->velocityX += FIX(5.0 / 32);
            } else {
                self->velocityX -= FIX(5.0 / 32);
            }
        }
        if (self->animCurFrame == 0xC) {
            if (self->facingLeft) {
                self->velocityX -= FIX(5.0 / 32);
            } else {
                self->velocityX += FIX(5.0 / 32);
            }
        }
        if ((g_Timer & 7) == 0) {
            PlaySfxPositional(SFX_STOMP_HARD_C);
        }
        if (self->ext.wereskeleton.unk7C++ > 0x60) {
            self->velocityX = 0;
            func_us_801CDDD8(6);
        }
        break;

    case 8:
        if (!AnimateEntity(D_us_80182894, self)) {
            func_us_801CDDD8(10);
        }
        if (!self->poseTimer && self->pose == 7) {
            PlaySfxPositional(SFX_CREAK);
        }
        if (!self->poseTimer && self->pose == 11) {
            PlaySfxPositional(SFX_WHIP_TWIRL_SWISH);
        }
        break;

    case 9:
        AnimateEntity(D_us_801828C0, self);
        if (self->ext.wereskeleton.unk7C % 7 == 0) {
            PlaySfxPositional(SFX_BONE_THROW);
            tempEntity = AllocEntity(&g_Entities[160], &g_Entities[192]);
            if (tempEntity != NULL) {
                DestroyEntity(tempEntity);
                CreateEntityFromEntity(E_ID_43, self, tempEntity);
                if (self->facingLeft) {
                    tempEntity->velocityX = FIX(1) + (Random() & 7) * 0x2800;
                } else {
                    tempEntity->velocityX = FIX(-1) - (Random() & 7) * 0x2800;
                }
                tempEntity->velocityY = FIX(-5.75);
                tempEntity->posY.i.hi -= 8;
            }
        }
        if (self->ext.wereskeleton.unk7C++ > 0x60) {
            func_us_801CDDD8(10);
        }
        break;

    case 10:
        self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        if ((GetDistanceToPlayerX() > 0x70) && (Random() & 1)) {
            func_us_801CDDD8(5);
        } else {
            self->ext.wereskeleton.unk7F = (Random() & 1) + 1;
            self->ext.wereskeleton.unk80 = (Random() & 1);
            func_us_801CDDD8(3);
        }
        break;

    case 11:
        for (i = 0; i < 5; i++) {
            tempEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (tempEntity != NULL) {
                MakeEntityFromId(E_WERESKELETON, self, tempEntity);
                tempEntity->palette = PAL_FLAG(PAL_CC_FIRE_EFFECT);
                tempEntity->hitboxState = 0;
                tempEntity->facingLeft = self->facingLeft;
                tempEntity->flags = FLAG_DESTROY_IF_OUT_OF_CAMERA |
                                    FLAG_DESTROY_IF_BARELY_OUT_OF_CAMERA |
                                    FLAG_POS_CAMERA_LOCKED | FLAG_UNK_2000;
                tempEntity->animCurFrame = i + 0x28;
                if (self->facingLeft) {
                    tempEntity->velocityX = -D_us_80182950[i].x;
                } else {
                    tempEntity->velocityX = D_us_80182950[i].x;
                }
                tempEntity->velocityY = D_us_80182950[i].y;
                tempEntity->step = 13;
                if (tempEntity->animCurFrame == 0x28) {
                    tempEntity->drawFlags |= FLAG_DRAW_ROTATE;
                    tempEntity->velocityY -= FIX(2);
                }
            }
        }
        tempEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (tempEntity != NULL) {
            CreateEntityFromEntity(E_EXPLOSION, self, tempEntity);
            tempEntity->params = 2;
        }
        DestroyEntity(self);
        break;

    case 12:
        for (i = 0; i < 4; i++) {
            tempEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (tempEntity != NULL) {
                MakeEntityFromId(E_WERESKELETON, self, tempEntity);
                tempEntity->palette = 0x226;
                tempEntity->hitboxState = 0;
                tempEntity->facingLeft = self->facingLeft;
                tempEntity->flags = FLAG_DESTROY_IF_OUT_OF_CAMERA |
                                    FLAG_DESTROY_IF_BARELY_OUT_OF_CAMERA |
                                    FLAG_POS_CAMERA_LOCKED;
                tempEntity->animCurFrame = i + 0x2D;

                if (self->facingLeft) {
                    tempEntity->velocityX = -D_us_80182950[i].x;
                } else {
                    tempEntity->velocityX = D_us_80182950[i].x;
                }
                tempEntity->velocityY = D_us_80182950[i].y;
                tempEntity->step = 13;
            }
        }
        tempEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (tempEntity != NULL) {
            CreateEntityFromEntity(E_EXPLOSION, self, tempEntity);
            tempEntity->params = 2;
        }
        DestroyEntity(self);
        break;

    case 13:
        MoveEntity();
        self->velocityY += FIX(0.25);
        self->rotate += 0x80;
        if (self->ext.wereskeleton.unk7C++ > 4) {
            tempEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (tempEntity != NULL) {
                CreateEntityFromEntity(E_EXPLOSION, self, tempEntity);
                tempEntity->params = 0;
                tempEntity->posX.i.hi += (Random() & 0x1F) - 0x10;
                tempEntity->posY.i.hi += (Random() & 0x1F) - 0x10;
            }
            self->ext.wereskeleton.unk7C = 0;
        }
        break;

    case 32:
        if (g_pads[0].pressed & PAD_SQUARE) {
            if (self->params) {
                break;
            }
            self->animCurFrame++;
            self->params |= 1;
        } else {
            self->params = 0;
        }

        if (g_pads[0].pressed & PAD_CIRCLE) {
            if (!self->step_s) {
                self->animCurFrame--;
                self->step_s |= 1;
            }
        } else {
            self->step_s = 0;
        }
        break;
    }
    if (self->animCurFrame >= 7 && self->animCurFrame < 14) {
        self->hitboxWidth = 22;
        self->hitboxHeight = 13;
        self->hitboxOffX = -15;
        self->hitboxOffY = 13;
    } else {
        self->hitboxWidth = 12;
        self->hitboxHeight = 22;
        self->hitboxOffX = 0;
        self->hitboxOffY = 0;
    }
}

// Likely the bone throw attack
void func_us_801CE958(Entity* self) {
    Entity* tempEntity;

    if (self->flags & FLAG_DEAD) {
        tempEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (tempEntity != NULL) {
            DestroyEntity(tempEntity);
            CreateEntityFromEntity(E_EXPLOSION, self, tempEntity);
            tempEntity->params = 0;
            DestroyEntity(self);
        }
    } else {
        if (self->step) {
            AnimateEntity(D_us_801828E4, self);
            MoveEntity();
            self->velocityY += FIX(0.125);
        } else {
            InitializeEntity(D_us_80180A88);
        }
    }
}

// Some wereskeleton helper
void func_us_801CEA2C(Entity* self) {
    u8 curFrame;
    Entity* tempEntity;

    if (!self->step) {
        InitializeEntity(g_EInitInteractable);
        self->hitboxState = 1;
        self->attack = 1;
        self->attackElement = 1;
    }
    tempEntity = self - 1;
    curFrame = tempEntity->animCurFrame;
    if (curFrame >= 16 && curFrame < 23) {
        curFrame -= 15;
    } else {
        curFrame = 0;
    }
    self->hitboxOffX = D_us_80182978[curFrame].x;
    self->hitboxOffY = D_us_80182978[curFrame].y;
    if (curFrame) {
        self->hitboxWidth = 6;
        self->hitboxHeight = 6;
    } else {
        self->hitboxWidth = 0;
        self->hitboxHeight = 0;
    }
    self->facingLeft = tempEntity->facingLeft;
    self->posX.i.hi = tempEntity->posX.i.hi;
    self->posY.i.hi = tempEntity->posY.i.hi;
    if (tempEntity->entityId != E_WERESKELETON) {
        DestroyEntity(self);
    }
}
