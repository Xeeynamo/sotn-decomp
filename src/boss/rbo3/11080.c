#include "rbo3.h"

// 0.990 - ('NZ0', 'func_801B0958') - (decompiled)
INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_80191080);

// 0.990 - ('NP3', 'func_801B2540') - (decompiled)
INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_80191148);

// 0.990 - ('NP3', 'EntityBreakable') - (decompiled)
INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_80191304);

void func_80191438(Entity* self) {
    s16 params = self->params;
    s16 posX;

    FntPrint("set:%04x\n", params);
    FntPrint("sx:%04x\n", g_CurrentRoom.left);
    FntPrint("ex:%04x\n", g_CurrentRoom.right);

    switch (self->step) {
    case 0:
        InitializeEntity(D_80180468);
        self->animSet = 2;
        self->animCurFrame = 1;
        self->zPriority = 0xB0;
        break;

    case 1:
        posX = self->posY.i.hi - PLAYER.posY.i.hi;
        posX = ABS(posX);
        if (posX < 32) {
            switch (params) {
            case 0:
                if (playerX < 384) {
                    g_CurrentRoom.x = 384;
                    g_CurrentRoom.left++;
                    self->step++;
                }
                break;

            case 1:
                if (playerX > 640) {
                    g_CurrentRoom.width = 640;
                    g_CurrentRoom.right--;
                    self->step++;
                }
                break;

            case 3:
                if (playerX > 768) {
                    g_CurrentRoom.width = 768;
                    g_CurrentRoom.right--;
                    self->step++;
                }
                break;

            case 5:
                if (playerX > 1152) {
                    g_CurrentRoom.width = 1152;
                    self->step++;
                }
                break;

            case 6:
                if (playerX < 128) {
                    g_CurrentRoom.x = 128;
                    self->step++;
                }
                break;

            case 7:
                if (playerX < 128) {
                    g_CurrentRoom.x = 128;
                    self->step++;
                }
                break;

            case 8:
                if (playerX > 640) {
                    g_CurrentRoom.width = 640;
                    self->step++;
                }
                break;

            case 9:
                if (playerX < 128) {
                    g_CurrentRoom.x = 128;
                    self->step++;
                }
                break;

            case 10:
                if (playerX > 640) {
                    g_CurrentRoom.width = 640;
                    g_CurrentRoom.right--;
                    self->step++;
                }
                break;

            case 11:
                if (playerX < 384) {
                    g_CurrentRoom.x = 384;
                    g_CurrentRoom.left++;
                    self->step++;
                }
                break;

            case 12:
                if (playerX > 640) {
                    g_CurrentRoom.width = 640;
                    g_CurrentRoom.right--;
                    self->step++;
                }
                break;

            case 2:
            case 4:
            case 13:
            case 14:
                if (playerX < 256) {
                    g_CurrentRoom.x = 256;
                    g_CurrentRoom.left++;
                    self->step++;
                }
                break;
            }
        }
        break;
    }
}

void EntityMedusa(Entity* self) {
    Entity* newEntity;
    s8* hitbox;
    s16 rotAngle;
    s32 posX;
    s32 i;

    if (self->flags & 0x100) {
        if (self->step != 7) {
            SetStep(7);
        }
    }

    switch (self->step) {
    case 0:
        InitializeEntity(D_80180480);
        self->animCurFrame = 1;
        self->hitboxState = 0;
        CreateEntityFromEntity(0x19, self, &self[1]);
        SetStep(1);

    case 1:
        if (D_80180728 & 1) {
            SetStep(2);
        }
        break;

    case 2:
        if (AnimateEntity(D_801805F0, self) == 0) {
            self->hitboxState = 3;
            SetStep(3);
        }
        break;

    case 3:
        AnimateEntity(D_801805FC, self);

        if (self->step_s == 0) {
            self->ext.generic.unk80.modeS16.unk0 = 64;
            self->step_s++;
        }

        if (GetDistanceToPlayerX() < 104) {
            self->ext.generic.unk84.S8.unk0 = 1;
        }

        if (GetDistanceToPlayerX() > 128) {
            self->ext.generic.unk84.S8.unk0 = 0;
        }

        if (GetDistanceToPlayerX() > 32) {
            self->facing = GetSideToPlayer() & 1;
        }

        MoveEntity();
        if (self->facing == self->ext.generic.unk84.U8.unk0) {
            self->velocityX = 0x8000;
        } else {
            self->velocityX = -0x8000;
        }

        if (self->hitFlags & 3) {
            SetStep(6);
        }

        posX = PLAYER.posX.i.hi - self->posX.i.hi;
        if ((g_Player.unk0C & 0x2000) && ((posX * PLAYER.velocityX) < 0)) {
            if (ABS(posX) < 80) {
                SetStep(5);
            }
        }

        if (--self->ext.generic.unk80.modeS16.unk0 == 0) {
            GetSideToPlayer();
            if (GetDistanceToPlayerX() <= 64) {
                SetStep(5);
            } else {
                SetStep(4);
            }
        }
        break;

    case 5:
        if (self->step_s == 0) {
            if (Random() & 1) {
                PlaySfxAtPos(0x7FE);
            } else {
                PlaySfxAtPos(0x7FF);
            }
            PlaySfxAtPos(0x7C8);
            self->step_s++;
        }
        self->ext.generic.unk84.S8.unk1 = 1;
        if (AnimateEntity(D_80180624, self) == 0) {
            self->ext.generic.unk84.S8.unk1 = 0;
            SetStep(3);
        }
        break;

    case 4:
        if (self->step_s == 0) {
            if (!(Random() & 3)) {
                PlaySfxAtPos(0x7FB);
            }
            self->step_s++;
        }

        if (AnimateEntity(D_8018060C, self) == 0) {
            SetStep(3);
            if (g_Player.unk0C & 0x80) {
                SetStep(8);
            }
        }

        if (LOW(self->animFrameIdx) == 4) {
            newEntity = AllocEntity(D_8007A958, &D_8007A958[32]);
            if (newEntity != NULL) {
                CreateEntityFromEntity(0x18, self, newEntity);
                newEntity->facing = self->facing;
                if (self->facing != 0) {
                    newEntity->posX.i.hi -= 13;
                } else {
                    newEntity->posX.i.hi += 13;
                }
                newEntity->posY.i.hi -= 28;
                PlaySfxAtPos(0x61F);
            }
        }
        break;

    case 8:
        if (self->step_s == 0) {
            PlaySfxAtPos(0x7FD);
            self->step_s++;
        }

        if (AnimateEntity(D_80180618, self) == 0) {
            SetStep(3);
        }

        if (LOW(self->animFrameIdx) == 3) {
            PlaySfxAtPos(0x7D1);
            for (i = 0; i < 2; i++, rotAngle += 0x400) {
                newEntity = AllocEntity(&g_Entities[160], &g_Entities[192]);
                if (newEntity != NULL) {
                    CreateEntityFromEntity(0x1A, self, newEntity);
                    newEntity->rotAngle = 0x400 * i - 0x200;
                    if (self->facing == 0) {
                        newEntity->rotAngle = (i * 0x400) + 0x600;
                    }
                    newEntity->posY.i.hi -= 16;
                    newEntity->zPriority = self->zPriority - 2;
                }
            }
        }
        break;

    case 6:
        if (self->step_s == 0) {
            if (Random() & 1) {
                PlaySfxAtPos(0x801);
            } else {
                PlaySfxAtPos(0x802);
            }
            self->step_s++;
        }

        if (AnimateEntity(D_80180630, self) == 0) {
            self->facing = GetSideToPlayer() & 1;
            SetStep(4);
        }
        break;

    case 7: // FUCKING_DEAD
        switch (self->step_s) {
        case 0:
            PlaySfxAtPos(0x804);
            self->hitboxState = 0;
            D_80180728 |= 2;
            self->step_s++;

        case 1:
            if (AnimateEntity(D_8018063C, self) == 0) {
                self->ext.generic.unk80.modeS16.unk0 = 80;
                PlaySfxAtPos(0x7C5);
                self->step_s++;
            }
            break;

        case 2:
            newEntity = AllocEntity(D_8007C0D8, &D_8007C0D8[64]);
            if (newEntity != NULL) {
                CreateEntityFromEntity(0x1B, self, newEntity);
                newEntity->params = 0;
                newEntity->zPriority = self->zPriority + 1;
                newEntity->posX.i.hi -= 16 - (Random() & 31);
                newEntity->posY.i.hi += 24;
            }

            if (!(self->ext.generic.unk80.modeS16.unk0 & 0xF)) {
                PlaySfxAtPos(0x661);
            }

            if (--self->ext.generic.unk80.modeS16.unk0 == 0) {
                self->animCurFrame = 0;
                D_80180728 |= 4;
                self->step_s++;
            }
            break;
        }
        break;

    case 255:
        /**
         * Debug: Press SQUARE / CIRCLE on the second controller
         * to advance/rewind current animation frame
         */
        FntPrint("charal %x\n", self->animCurFrame);
        if (g_pads[1].pressed & PAD_SQUARE) {
            if (self->params == 0) {
                self->animCurFrame++;
                self->params |= 1;
            } else {
                break;
            }
        } else {
            self->params = 0;
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

    posX = self->posX.i.hi + g_Camera.posX.i.hi;

    if (self->velocityX < 0) {
        if (posX < 128) {
            self->posX.i.hi = 128 - g_Camera.posX.i.hi;
        }
    } else if (posX > 384) {
        self->posX.i.hi = 384 - g_Camera.posX.i.hi;
    }

    hitbox = &D_80180670[self->animCurFrame][D_80180648];
    hitbox--;
    hitbox++;
    self->hitboxOffX = *hitbox++;
    self->hitboxOffY = *hitbox++;
    self->hitboxWidth = hitbox[0];
    self->hitboxHeight = hitbox[1];
}

void func_80192020(Entity* self) {
    Primitive* prim;
    s32 posX, posY;
    s16 primIndex;
    s32 var_a2;
    s16 angle;
    u16 angle2;
    u16 var_v0;

    if (self->flags & 0x100) {
        SetStep(2);
    }

    switch (self->step) {
    case 0:
        InitializeEntity(D_80180498);
        self->hitboxHeight = 1;
        primIndex = g_api.AllocPrimitives(PRIM_LINE_G2, 1);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        prim = &g_PrimBuf[primIndex];
        self->primIndex = primIndex;
        self->ext.prim = prim;
        self->flags |= FLAG_HAS_PRIMS;
        prim->x0 = prim->x1 = self->posX.i.hi;
        prim->y0 = prim->y1 = self->posY.i.hi;
        prim->r0 = 255;
        prim->g0 = 64;
        prim->b0 = 128;
        prim->b1 = prim->g1 = prim->r1 = 0;
        prim->priority = self->zPriority;
        prim->blendMode = 0x33;
        posX = PLAYER.posX.i.hi - self->posX.i.hi;
        posY = PLAYER.posY.i.hi - self->posY.i.hi;

        angle = ratan2(posY, posX);
        if (self->facing != 0) {
            angle2 = angle - 1;
            if (angle2 < 0x5FF) {
                angle = 0x600;
                angle2 = 0x600;
            }
            var_v0 = angle + 0x5FF;
            if (var_v0 < 0x5FF) {
                angle = -0x600;
            }
        } else {
            if (angle > 0x200) {
                angle = 0x200;
                angle = 0x200;
            }
            if (angle < -0x200) {
                angle = -0x200;
            }
        }
        self->velocityX = rcos(angle) << 7;
        self->velocityY = rsin(angle) << 7;

    case 1:
        MoveEntity();

        prim = self->ext.prim;
        posX = prim->x0 = self->posX.i.hi;
        posY = prim->y0 = self->posY.i.hi;

        var_a2 = 0;
        if (self->velocityX > 0) {
            var_a2 = (posX <= 288) ^ 1;
        } else if (posX < -32) {
            var_a2 = 1;
        }
        if (self->velocityY > 0) {
            if (posY > 288) {
                var_a2 = 1;
            }
        } else if (posY < -32) {
            var_a2 = 1;
        }
        if (var_a2 != 0) {
            self->hitboxState = 0;
            self->step++;
        }
        break;

    case 2:
        if (func_8019E9E0(self->ext.prim, 16) == 0) {
            DestroyEntity(self);
        }
        break;
    }
}

void func_801922EC(Entity* self) {
    Entity* prevEntity;
    s8* hitbox;

    if (self->step == 0) {
        InitializeEntity(D_8018048C);
    }
    prevEntity = &self[-1];
    self->posX.i.hi = prevEntity->posX.i.hi;
    self->posY.i.hi = prevEntity->posY.i.hi;
    self->facing = prevEntity->facing;

    if (*(u8*)&prevEntity->ext.stub[0x9] != 0) {
        self->hitboxState = 1;
    } else {
        self->hitboxState = 2;
    }

    hitbox = &D_801806B0[prevEntity->animCurFrame][D_80180684];
    hitbox++;
    hitbox--;
    self->hitboxOffX = *hitbox++;
    self->hitboxOffY = *hitbox++;
    self->hitboxWidth = hitbox[0];
    self->hitboxHeight = hitbox[1];
    if (prevEntity->entityId != 0x17) {
        DestroyEntity(self);
    }
}

INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_801923DC);

void func_80192998(Entity* self) {
    s32 objParams;
    u32 priorityParams;
    Unkstruct_80180FE0* obj;

    switch (self->step) {
    case 0:
        InitializeEntity(D_8018042C);
        objParams = self->params & 0xF;
        obj = &D_8018071C[objParams];
        self->palette = obj->palette + 0x2E0;
        self->blendMode = obj->blendMode;
        self->animSet = obj->animSet;
        self->unk5A = obj->unk2;
        *(s32*)&self->ext.stub[0x4] = obj->unk8;
        self->step = objParams + 1;
        priorityParams = self->params & 0xFF00;
        if (priorityParams != 0) {
            self->zPriority = priorityParams >> 8;
        }

        if (self->params & 0xF0) {
            self->palette = 0x819F;
            self->blendMode = 0x10;
            self->facing = 1;
        }
        break;

    case 1:
        if (self->step_s == 0) {
            self->unk19 = 8;
            self->unk6C = 0xC0;
            self->facing = Random() & 1;
            self->velocityX = (Random() << 8) - 0x8000;
            self->velocityY = -0xC000;
            *(s32*)&self->ext.stub[0x10] = -(Random() * 16) - 0x4000;
            self->step_s++;
        }
        MoveEntity();
        self->velocityY = self->velocityY + *(s32*)&self->ext.stub[0x10];
        self->unk6C += 0xFF;
        if (AnimateEntity(*(s32*)&self->ext.stub[0x4], self) == 0) {
            DestroyEntity(self);
        }
        break;
    }
}

// 0.990 - ('NZ0', 'EntityUnkId0E')
INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_80192B38);

// 0.990 - ('NO3', 'EntityUnkId2F')
INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_80192D64);

// 0.990 - ('NZ0', 'func_801BD9A0')
INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_80193050);

// 1.000 - ('NZ0', 'Random') - (decompiled)
INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", Random);

// 0.990 - ('NZ0', 'Update') - (decompiled)
INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_801931C8);

// 0.990 - ('NZ0', 'func_801B9800') - (decompiled)
INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_801934C4);

// 0.990 - ('NZ0', 'TestCollisions')
INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_801935CC);

// 0.990 - ('NZ0', 'EntityNumericDamage')
INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_801946E4);

// 0.990 - ('NZ0', 'CreateEntityFromLayout') - (decompiled)
INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_80194D88);

// 0.990 - ('NZ0', 'CreateEntityWhenInVerticalRange') - (decompiled)
INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_80194E4C);

// 0.990 - ('NZ0', 'CreateEntityWhenInHorizontalRange') - (decompiled)
INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_80194F64);

// 0.990 - ('NZ0', 'func_801BB3B8') - (decompiled)
INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_8019507C);

// 0.990 - ('NZ0', 'func_801BB404') - (decompiled)
INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_801950C8);

// 0.990 - ('NZ0', 'func_801BB45C') - (decompiled)
INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_80195120);

// 0.990 - ('NZ0', 'func_801BB558') - (decompiled)
INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_8019521C);

// 0.990 - ('NZ0', 'func_801BB3B8') - (decompiled)
INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_80195330);

// 0.990 - ('NZ0', 'func_801BB404') - (decompiled)
INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_8019537C);

// 0.990 - ('NZ0', 'func_801BB710') - (decompiled)
INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_801953D4);

// 0.990 - ('NZ0', 'func_801BB558') - (decompiled)
INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_801954D0);

// 0.990 - ('NZ0', 'InitRoomEntities') - (decompiled)
INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_801955E4);

// 0.990 - ('NZ0', 'func_801BBA98') - (decompiled)
INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_8019575C);

// 0.990 - ('NZ0', 'CreateEntityFromCurrentEntity') - (decompiled)
INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_80195810);

// 0.990 - ('NZ0', 'CreateEntityFromEntity') - (decompiled)
INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", CreateEntityFromEntity);

// 1.000 - ('NZ0', 'func_801BBC3C') - (decompiled)
INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_80195900);

// 0.990 - ('NZ0', 'EntityRedDoor')
INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_80195978);

INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", DestroyEntity);

// 0.990 - ('NZ0', 'DestroyEntityFromIndex') - (decompiled)
INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_8019661C);

// 1.000 - ('NZ0', 'PreventEntityFromRespawning') - (decompiled)
INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_80196698);

// 0.990 - ('NZ0', 'AnimateEntity') - (decompiled)
INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", AnimateEntity);

// 0.990 - ('NZ0', 'func_801BCAD4') - (decompiled)
INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_80196798);

// 1.000 - ('NZ0', 'GetDistanceToPlayerX') - (decompiled)
INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", GetDistanceToPlayerX);

// 1.000 - ('NZ0', 'GetDistanceToPlayerY') - (decompiled)
INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", GetDistanceToPlayerY);

// 1.000 - ('NZ0', 'GetSideToPlayer') - (decompiled)
INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", GetSideToPlayer);

// 1.000 - ('NZ0', 'MoveEntity') - (decompiled)
INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", MoveEntity);

// 1.000 - ('NZ0', 'FallEntity') - (decompiled)
INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_80196994);

// 0.990 - ('NZ0', 'func_801BCCFC') - (decompiled)
INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_801969C0);

// 0.990 - ('NZ0', 'func_801BCF74') - (decompiled)
INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_80196C38);

// 0.990 - ('NZ0', 'AllocEntity') - (decompiled)
INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", AllocEntity);

// 0.990 - ('NZ0', 'func_801BD1BC') - (decompiled)
INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_80196E80);

// 0.990 - ('NZ0', 'func_801BD1E8') - (decompiled)
INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_80196EAC);

// 0.990 - ('NZ0', 'func_801BD204') - (decompiled)
INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_80196EC8);

// 1.000 - ('NZ0', 'func_801BD270') - (decompiled)
INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_80196F34);

// 0.990 - ('NZ0', 'func_8019AD64') - (decompiled)
INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_80196F6C);

// 0.990 - ('NZ0', 'func_801BD484') - (decompiled)
INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_80196FB4);

// 0.990 - ('NZ0', 'func_801BD338') - (decompiled)
INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_80196FFC);

// 1.000 - ('NZ0', 'func_801BD390') - (decompiled)
INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_80197054);

// 1.000 - ('NZ0', 'func_801BD41C') - (decompiled)
INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_801970E0);

// 1.000 - ('NZ0', 'func_801BD44C') - (decompiled)
INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_80197110);

// 0.990 - ('NZ0', 'func_801BD2F0') - (decompiled)
INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_80197148);

// 0.990 - ('NZ0', 'func_801BD4CC') - (decompiled)
INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_80197190);

void SetStep(u8 step) {
    Entity* entity = g_CurrentEntity;

    entity->step = step;
    entity->step_s = 0;
    entity->animFrameIdx = 0;
    entity->animFrameDuration = 0;
}

// 1.000 - ('NZ0', 'SetSubStep') - (decompiled)
INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_80197210);

// 0.990 - ('NZ0', 'func_801BD568') - (decompiled)
INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_8019722C);

INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", InitializeEntity);

void func_801973BC(Entity* self) {
    if (self->step == 0) {
        self->step++;
    }
}

// 0.990 - ('NZ0', 'func_801BD720') - (decompiled)
INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_801973E4);

// 0.990 - ('NZ0', 'func_801BD848') - (decompiled)
INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_8019750C);

// 0.990 - ('NZ0', 'func_801BD9A0')
INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_80197664);

// 0.990 - ('NZ0', 'ReplaceBreakableWithItemDrop') - (decompiled)
INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_801979A8);

// 1.000 - ('NZ0', 'func_801BDD9C') - (decompiled)
INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_80197A60);

// 0.990 - ('NZ0', 'func_801BDE20') - (decompiled)
INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_80197AE4);

// 0.990 - ('NZ0', 'CollectHeart') - (decompiled)
INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_80197C40);

// 0.990 - ('NZ0', 'CollectGold') - (decompiled)
INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_80197CC0);

// 0.990 - ('NZ0', 'CollectSubweapon') - (decompiled)
INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_80197D9C);

// 0.990 - ('NZ0', 'CollectHeartVessel') - (decompiled)
INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_80197EB4);

// 0.990 - ('NZ0', 'CollectLifeVessel') - (decompiled)
INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_80197F58);

void func_80197FA8(void) { DestroyEntity(g_CurrentEntity); }

// 0.990 - ('CEN', 'EntityPrizeDrop')
INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_80197FD0);

// 0.990 - ('NZ0', 'EntityExplosion') - (decompiled)
INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_80198844);

// 0.990 - ('NZ0', 'func_801BEC7C') - (decompiled)
INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_80198940);

// 0.990 - ('CEN', 'EntityEquipItemDrop')
INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_801989E4);

// 0.990 - ('NZ0', 'func_801BF308')
INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_80198FCC);

// 0.990 - ('NP3', 'EntityRelicOrb')
INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_8019927C);

// 0.990 - ('MAD', 'EntityHeartDrop')
INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_80199D4C);

// 0.990 - ('NZ0', 'EntityUnkId0E')
INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_80199E68);

// 0.990 - ('NZ0', 'func_801C070C') - (decompiled)
INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_8019A3C4);

// 0.990 - ('NZ0', 'func_801C07FC') - (decompiled)
INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_8019A4B4);

// 0.990 - ('NZ0', 'func_801C090C') - (decompiled)
INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_8019A5C4);

// 0.990 - ('NZ0', 'func_801C0A3C')
INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_8019A6F4);

// 0.990 - ('NZ0', 'func_801C0B24') - (decompiled)
INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_8019A7DC);

// 0.990 - ('NZ0', 'func_801C0C14') - (decompiled)
INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_8019A8CC);

// 0.990 - ('NZ0', 'func_801C0D08') - (decompiled)
INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_8019A9C0);

// 0.990 - ('NZ0', 'func_801C0F38') - (decompiled)
INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_8019ABF0);

// 0.990 - ('NZ0', 'func_801C1034') - (decompiled)
INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_8019ACEC);

// 0.990 - ('NZ0', 'EntityIntenseExplosion') - (decompiled)
INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_8019B26C);

// 0.990 - ('NZ0', 'func_801C16B4') - (decompiled)
INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_8019B36C);

// 0.990 - ('NZ0', 'func_801C1780') - (decompiled)
INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_8019B438);

// 0.990 - ('NZ0', 'func_801C1848') - (decompiled)
INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_8019B500);

// 0.990 - ('NZ0', 'func_801C1900') - (decompiled)
INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_8019B5B8);

// 0.990 - ('NZ0', 'func_801C1AD8')
INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_8019B790);

// 0.990 - ('NZ0', 'func_801C20B8')
INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_8019BD70);

// 1.000 - ('NZ0', 'ClutLerp') - (decompiled)
INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_8019C470);

// 0.990 - ('NZ0', 'func_801C29B0') - (decompiled)
INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", PlaySfxAtPos);

// 0.990 - ('NZ0', 'func_801C8ADC') - (decompiled)
INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_8019C760);

// 0.990 - ('NZ0', 'EntityStageNamePopup')
INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_8019C930);

// 0.990 - ('NZ0', 'EntitySoulStealOrb') - (decompiled)
INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_8019D5B4);

// 0.990 - ('NZ0', 'EntityEnemyBlood') - (decompiled)
INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_8019D948);

// 0.990 - ('NZ0', 'EntityRoomForeground') - (decompiled)
INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_8019DDF8);

// 0.990 - ('NZ0', 'func_801C33D8')
INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_8019DEE4);

// 0.990 - ('NZ0', 'func_801C9930')
INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_8019E214);

// 0.990 - ('NZ0', 'func_801C9D18')
INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_8019E5FC);

// 1.000 - ('NZ0', 'func_801C9E68') - (decompiled)
INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_8019E74C);

// 1.000 - ('NZ0', 'func_801C9E98') - (decompiled)
INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_8019E77C);

// 0.990 - ('NZ0', 'func_801C9F14') - (decompiled)
INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_8019E7F8);

// 1.000 - ('NZ0', 'func_801C9F9C') - (decompiled)
INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_8019E880);

// 0.990 - ('NZ0', 'func_801CA07C') - (decompiled)
INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_8019E960);

// 1.000 - ('NZ0', 'func_801CA0D0') - (decompiled)
INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_8019E9B4);

// 0.990 - ('NZ0', 'func_801CA0FC') - (decompiled)
INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_8019E9E0);

// 0.990 - ('NZ0', 'EntityMagicallySealedDoor')
INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_8019EA44);

// Unique, has co-processor instructions
INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_8019F2F8);
