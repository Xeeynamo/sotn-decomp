#include "st0.h"

void func_801A7D64(Entity* arg0) {
    s32 temp_v0;
    ObjInit2* temp_s0 = &D_80180638[arg0->subId];

    if (arg0->step == 0) {
        InitializeEntity(D_801805BC);
        arg0->animSet = temp_s0->animSet;
        arg0->zPriority = temp_s0->zPriority;
        arg0->unk5A = temp_s0->unk4.s;
        arg0->palette = temp_s0->palette;
        arg0->unk19 = temp_s0->unk8;
        arg0->blendMode = temp_s0->blendMode;
        temp_v0 = temp_s0->unkC;
        if (temp_v0 != 0) {
            arg0->flags = temp_v0;
        }
    }
    AnimateEntity(temp_s0->unk10, arg0);
}

bool func_801A7E2C(Entity* self) {
    s16 diffX = PLAYER.posX.i.hi - self->posX.i.hi;

    diffX = ABS(diffX);
    if (self->hitboxWidth >= diffX) {
        diffX = PLAYER.posY.i.hi - self->posY.i.hi;
        diffX = ABS(diffX);
        return (self->hitboxHeight >= diffX);
    } else {
        return false;
    }
}

#ifndef NON_EQUIVALENT
INCLUDE_ASM("asm/us/st/st0/nonmatchings/27D64", EntityLockCamera);
#else
extern u16 D_801805B0[];
extern u8 D_8018065C[];
extern u8 D_80180660[];
extern u16 D_80180664[];

bool func_801A7E2C(Entity* entity);
void EntityLockCamera(Entity* entity) {
    s32 temp_v0_2;
    s32 temp_v1;
    u16* temp_v1_2;
    u16* temp_v1_5;
    u8 temp_s1;
    u8 temp_v0;
    s32 phi_v1;

    temp_s1 = entity->subId;
    if (entity->step == 0) {
        InitializeEntity(D_801805B0);
        temp_v1 = temp_s1 & 0xFFFF;
        entity->unk3C = 1;
        temp_v0 = D_80180660[temp_v1];
        entity->unk7C.modeU16 = temp_v0;
        if (temp_v0) {
            entity->hitboxWidth = D_8018065C[temp_v1];
            entity->hitboxHeight = 20;
        } else {
            entity->hitboxWidth = 20;
            entity->hitboxHeight = D_8018065C[temp_v1];
        }
    }

    if (entity->subId & 0x100) {
        temp_v1_2 = &D_80180664[(((temp_s1 & 0xFFFF) * 4) & 0xFFFF)];
        g_CurrentRoom.x = *temp_v1_2++;
        g_CurrentRoom.y = *temp_v1_2++;
        g_CurrentRoom.width = *temp_v1_2++;
        g_CurrentRoom.height = *temp_v1_2++;
        DestroyEntity(entity);
        return;
    }

    if (func_801A7E2C(entity)) {
        temp_v0_2 = func_801B4C78();
        if (entity->unk7C.modeU16) {
            phi_v1 = (temp_v0_2 & 2) * 2;
        } else {
            phi_v1 = (temp_v0_2 & 1) * 4;
        }

        temp_v1_5 = &D_80180664[(phi_v1 + temp_s1 * 8) & 0xFFFF];
        g_CurrentRoom.x = *temp_v1_5++;
        g_CurrentRoom.y = *temp_v1_5++;
        g_CurrentRoom.width = *temp_v1_5++;
        g_CurrentRoom.height = *temp_v1_5++;
    }
}
#endif

INCLUDE_ASM("asm/us/st/st0/nonmatchings/27D64", func_801A805C);

INCLUDE_ASM("asm/us/st/st0/nonmatchings/27D64", func_801A8328);

void func_801A8620(Entity* entity) {
    s16 dist;
    s32 subId = (s16)entity->subId;

    FntPrint("set:%04x\n", subId);
    FntPrint("sx:%04x\n", g_CurrentRoom.left);
    FntPrint("ex:%04x\n", g_CurrentRoom.right);

    switch (entity->step) {
    case 0:
        InitializeEntity(&D_801805BC);
        entity->animSet = 2;
        entity->animCurFrame = 1;
        entity->zPriority = 0xB0;
        break;

    case 1:
        dist = entity->posY.i.hi - PLAYER.posY.i.hi;
        dist = ABS(dist);

        if (dist < 0x20) {
            switch (subId) {
            case 0:
                if (playerX > 0x280) {
                    g_CurrentRoom.width = 0x280;
                    g_CurrentRoom.right--;
                    entity->step++;
                }
                break;

            case 1:
                if (playerX < 0x180) {
                    g_CurrentRoom.x = 0x180;
                    g_CurrentRoom.left++;
                    entity->step++;
                }
                break;

            case 3:
                if (playerX < 0x100) {
                    g_CurrentRoom.x = 0x100;
                    g_CurrentRoom.left++;
                    entity->step++;
                }
                break;

            case 5:
                if (playerX < 0x80) {
                    g_CurrentRoom.x = 0x80;
                    entity->step++;
                }
                break;

            case 6:
                if (playerX > 0x480) {
                    g_CurrentRoom.width = 0x480;
                    entity->step++;
                }
                break;

            case 7:
                if (playerX > 0x480) {
                    g_CurrentRoom.width = 0x480;
                    entity->step++;
                }
                break;

            case 8:
                if (playerX < 0x80) {
                    g_CurrentRoom.x = 0x80;
                    entity->step++;
                }
                break;

            case 9:
                if (playerX > 0x280) {
                    g_CurrentRoom.width = 0x280;
                    entity->step++;
                }
                break;

            case 10:
                if (playerX < 0x180) {
                    g_CurrentRoom.x = 0x180;
                    g_CurrentRoom.left++;
                    entity->step++;
                }
                break;

            case 11:
                if (playerX > 0x280) {
                    g_CurrentRoom.width = 0x280;
                    g_CurrentRoom.right--;
                    entity->step++;
                }
                break;

            case 12:
                if (playerX < 0x180) {
                    g_CurrentRoom.x = 0x180;
                    g_CurrentRoom.left++;
                    entity->step++;
                }
                break;

            case 2:
            case 4:
            case 13:
            case 14:
                if (playerX > 0x300) {
                    g_CurrentRoom.width = 0x300;
                    g_CurrentRoom.right--;
                    entity->step++;
                }
                break;
            }
        }
        break;
    }
}

void func_801A8984(void) {
    D_801C24D8 = 2;
    D_801C24D6 = 2;
    D_801C24DA = 0;
    D_801C24DE = 0;
    D_801C24E2 = 0;
    D_801C24E3 = 8;
    D_801C24D2 = D_801C24D4 + 0x14;
}

INCLUDE_ASM("asm/us/st/st0/nonmatchings/27D64", func_801A89D8);

void func_801A8B9C(s16 yOffset) {
    RECT rect;

    rect.y = (yOffset * 12) + 384;
    rect.w = 64;
    rect.x = 0;
    rect.h = 12;
    ClearImage(&rect, 0, 0, 0);
}

INCLUDE_ASM("asm/us/st/st0/nonmatchings/27D64", func_801A8BF8);

INCLUDE_ASM("asm/us/st/st0/nonmatchings/27D64", func_801A8CB0);

INCLUDE_ASM("asm/us/st/st0/nonmatchings/27D64", func_801A8E34);

INCLUDE_ASM("asm/us/st/st0/nonmatchings/27D64", func_801A8E60);

INCLUDE_ASM("asm/us/st/st0/nonmatchings/27D64", func_801A910C);

INCLUDE_ASM("asm/us/st/st0/nonmatchings/27D64", EntityDialogue);

INCLUDE_ASM("asm/us/st/st0/nonmatchings/27D64", func_801AA218);

INCLUDE_ASM("asm/us/st/st0/nonmatchings/27D64", EntityCutscene);

INCLUDE_ASM("asm/us/st/st0/nonmatchings/27D64", EntitySecretButton);

extern u16 D_80180628[];
void EntitySecretStairsEmitter(Entity* entity) {
    switch (entity->step) {
    case 0:
        InitializeEntity(D_80180628);
        entity->animCurFrame = 3;
        entity->zPriority += 2;
        if (g_isSecretStairsButtonPressed) {
            entity->animCurFrame = 0;
            entity->step = 3;
        }
        break;
    case 1:
        if (g_isSecretStairsButtonPressed) {
            g_api.PlaySfx(NA_SE_SECRET_STAIRS);
            entity->step++;
        }
        break;
    case 2:
        entity->posY.val -= 0x4000;
        if (entity->posY.i.hi < -16) {
            entity->step++;
        }
        break;
    case 3:
        entity->animCurFrame = 0;
        break;
    }
}

INCLUDE_ASM("asm/us/st/st0/nonmatchings/27D64", EntitySecretStairsChunk);

INCLUDE_ASM("asm/us/st/st0/nonmatchings/27D64", EntityStageTitleFadeout);

INCLUDE_ASM("asm/us/st/st0/nonmatchings/27D64", EntityStageTitleCard);

INCLUDE_ASM("asm/us/st/st0/nonmatchings/27D64", func_801ABBBC);

INCLUDE_ASM("asm/us/st/st0/nonmatchings/27D64", func_801AC458);

INCLUDE_ASM("asm/us/st/st0/nonmatchings/27D64", EntityDracula);

extern u16 D_801805E0[];
void EntityDraculaBody(Entity* entity) {
    if (g_isDraculaFirstFormDefeated) {
        DestroyEntity(entity);
    }

    switch (entity->step) {
    case 0:
        InitializeEntity(D_801805E0);
        entity->unk3C = 1;
        entity->hitPoints = 0x7FFF;
        entity->unk10 = 3;
        entity->unk12 = 0x27;
        entity->hitboxWidth = 12;
        entity->animCurFrame = 0;
        entity->hitboxHeight = 34;
        break;
    case 1:
        entity->facing = entity[-1].facing;
        entity->posX.i.hi = entity[-1].posX.i.hi;
        entity->posY.i.hi = entity[-1].posY.i.hi;
        entity->unk3C = entity[-1].unk3C & 0xFFFD;
        break;
    case 2:
        entity->unk3C = 0;
        break;
    }

    if (g_isDraculaFirstFormDefeated) {
        entity->unk3C = 0;
    }
}

extern u16 D_801805EC[];
extern u8 D_8018097C[];
void EntityDraculaFireball(Entity* entity) {
    u16 temp_v0;

    if (g_isDraculaFirstFormDefeated) {
        entity->flags |= 0x100;
    }

    if (entity->flags & 0x100) {
        entity->pfnUpdate = (PfnEntityUpdate)EntityExplosion;
        entity->step = 0;
        entity->subId = 2;
        return;
    }

    switch (entity->step) {
    case 0:
        InitializeEntity(D_801805EC);

        if (entity->facing == 0) {
            entity->accelerationX = -0x20000;
        } else {
            entity->accelerationX = 0x20000;
        }

        if (entity->subId == 1) {
            entity->accelerationY = -0x8000;
        }

        if (entity->subId == 2) {
            entity->accelerationY = 0x8000;
        }
        entity->unk8C.modeU16.unk0 = 0x28;

    case 1:
        AnimateEntity(D_8018097C, entity);
        MoveEntity();
        temp_v0 = entity->unk8C.modeU16.unk0 - 1;
        entity->unk8C.modeU16.unk0 = temp_v0;

        if ((temp_v0 << 0x10) == 0) {
            entity->accelerationY = 0;
        }
        return;
    }
}

extern u16 D_801805F8[];
extern u8 D_80180990[];
extern u8 D_801809B0[];
extern s16 D_80180A60[];
extern s16 D_80180A62[];
void EntityDraculaMeteorball(Entity* entity) {
    s32 speedX;

    if (g_isDraculaFirstFormDefeated) {
        entity->objectId = ENTITY_EXPLOSION;
        entity->pfnUpdate = EntityExplosion;
        entity->step = 0;
        entity->unk2E = 0;
        entity->subId = 1;
        return;
    }

    switch (entity->step) {
    case 0:
        InitializeEntity(D_801805F8);
        entity->unk3C = 0;
        entity->unk19 |= 4;
        break;
    case 1:
        if (AnimateEntity(D_801809B0, entity) == 0) {
            entity->unk3C = 1;
            func_801B5794(2);
        }
        break;
    case 2:
        AnimateEntity(&D_80180990, entity);
        MoveEntity();
        entity->unk1E += 4;
        speedX = 0x1000;
        if (entity->subId != 0) {
            speedX = 0xE00;
        }

        if (entity->facing != 0) {
            entity->accelerationX += speedX;
        } else {
            entity->accelerationX -= speedX;
        }

        if (!(g_blinkTimer & 3)) { // lolwut?
            Entity* newEntity = AllocEntity(D_8007D858, D_8007D858 + 0x20);
            if (newEntity != 0) {
                s32 randomPosXYIndex;
                CreateEntityFromEntity(0x1E, entity, newEntity);
                newEntity->zPriority = entity->zPriority + 1;
                randomPosXYIndex = (Random() & 3) * 2;
                newEntity->posX.i.hi =
                    newEntity->posX.i.hi + D_80180A60[randomPosXYIndex];
                newEntity->posY.i.hi =
                    newEntity->posY.i.hi + D_80180A62[randomPosXYIndex];
            }
        }
        break;
    }
}

extern u16 D_801805EC[];
extern u8 D_801809E0[];
void func_801AD838(Entity* entity) {
    if (g_isDraculaFirstFormDefeated) {
        DestroyEntity(entity);
        return;
    }

    if (entity->step == 0) {
        InitializeEntity(D_801805EC);
        entity->animCurFrame = 0;
        entity->unk3C = 0;
        entity->accelerationY = -0x10000;
    }
    MoveEntity();

    if (AnimateEntity(D_801809E0, entity) == 0) {
        DestroyEntity(entity);
    }
}

extern u16 D_801805EC[];
extern u8 D_80180A40[];
void EntityDraculaGlass(Entity* entity) {
    switch (entity->step) {
    case 0:
        InitializeEntity(D_801805EC);
        entity->animCurFrame = 0x59;
        entity->unk19 = 4;
        entity->unk3C = 0;
        entity->accelerationX = -0x10000;
        entity->accelerationY = 0;
        if (entity->subId) {
            s16 radians;
            s32 speed;
            entity->animCurFrame = 0x5C;
            speed = (Random() & 0x1F) + 0x10;
            radians = (Random() * 6) + 0x900;
            entity->accelerationX = speed * rcos(radians);
            entity->accelerationY = speed * rsin(radians);
            func_801B5794(3);
        }
    case 1:
        MoveEntity();
        entity->unk1E += 0x20;
        entity->accelerationY += 0x2000;
        if (entity->posY.i.hi >= 205) {
            g_api.PlaySfx(NA_SE_BREAK_GLASS);
            entity->posY.i.hi = 204;
            func_801B5794(2);
        }
        break;
    case 2:
        entity->unk19 = 0;
        if (AnimateEntity(D_80180A40, entity) == 0) {
            s32 i;
            for (i = 0; i < 8; i++) {
                Entity* glassShardEntity =
                    AllocEntity(D_8007D858, D_8007D858 + MaxEntityCount);
                if (glassShardEntity != 0) {
                    CreateEntityFromEntity(31, entity, glassShardEntity);
                    glassShardEntity->subId = 1;
                }
            }
            DestroyEntity(entity);
        }
        break;
    case 3:
        MoveEntity();
        entity->accelerationY += 0x2000;
        if (entity->posY.i.hi >= 205) {
            DestroyEntity(entity);
        }
        break;
    }
}

bool func_801ADAC8(s32 arg0) {
    s32 unk = 0xD0;
    Entity* entity = g_CurrentEntity;
    s16 temp_v1 = entity->posY.i.hi + arg0;

    if (temp_v1 >= unk) {
        entity->posY.i.hi = unk - temp_v1 + entity->posY.i.hi;
        return true;
    } else {
        return false;
    }
}

INCLUDE_ASM("asm/us/st/st0/nonmatchings/27D64", func_801ADB10);

INCLUDE_ASM("asm/us/st/st0/nonmatchings/27D64", EntityDraculaFinalForm);

INCLUDE_ASM("asm/us/st/st0/nonmatchings/27D64", EntityDraculaMegaFireball);

INCLUDE_ASM("asm/us/st/st0/nonmatchings/27D64", EntityDraculaRainAttack);

INCLUDE_ASM("asm/us/st/st0/nonmatchings/27D64", func_801AF380);

INCLUDE_ASM("asm/us/st/st0/nonmatchings/27D64", func_801AF6D0);

INCLUDE_ASM("asm/us/st/st0/nonmatchings/27D64", func_801AF774);

void func_801B0030(s32 arg0) {
    D_8003C734 = arg0;
    D_80073060 = 0;
    g_backbufferX = 0;
    g_backbufferY = 0;
}

void func_801B0058(void) {
    s32 index = 0;
    s32 i;
    s32 j;

    for (i = 0xF0; i < 0x100; i++) {
        for (j = 0x200; j < 0x300; j += 0x10) {
            D_8003C104[index++] = GetClut(j, i);
        }
    }

    for (i = 0xF0; i < 0x100; i++) {
        for (j = 0; j < 0x100; j += 0x10) {
            D_8003C104[index++] = GetClut(j, i);
        }
    }

    for (i = 0xF0; i < 0x100; i++) {
        for (j = 0x100; j < 0x200; j += 0x10) {
            D_8003C104[index++] = GetClut(j, i);
        }
    }
}

INCLUDE_ASM("asm/us/st/st0/nonmatchings/27D64", func_801B0180);

void func_801B01C0(void) {
    D_8003CB08.buf.draw.r0 = 0;
    D_8003CB08.buf.draw.g0 = 0;
    D_8003CB08.buf.draw.b0 = 0;
    D_800542FC.buf.draw.r0 = 0;
    D_800542FC.buf.draw.g0 = 0;
    D_800542FC.buf.draw.b0 = 0;
}

void func_801B01F8(s32 arg0) {
    D_8003CB08.buf.draw.clip.y = 0x0014;
    D_8003CB08.buf.draw.clip.h = 0x00CF;
    D_80054302 = arg0 == 0 ? 0x0014 : 0x0114;
    D_800542FC.buf.draw.clip.h = 0x00CF;
    D_800542FC.buf.draw.isbg = 1;
    D_8003CB08.buf.draw.isbg = 1;
    func_801B01C0();
    D_800542FC.buf.disp.isrgb24 = 0;
    D_8003CB08.buf.disp.isrgb24 = 0;
}

// Set stage display buffer
void func_801B0280(void) {
    SetDefDrawEnv(&D_8003CB08.buf.draw, 0, 0, DISP_STAGE_W, DISP_STAGE_H);
    SetDefDrawEnv(&D_800542FC.buf.draw, DISP_STAGE_W, 0, DISP_STAGE_W,
                  DISP_STAGE_H);
    SetDefDispEnv(&D_8003CB08.buf.disp, DISP_STAGE_W, 0, DISP_STAGE_W,
                  DISP_STAGE_H);
    SetDefDispEnv(&D_8005435C, 0, 0, DISP_STAGE_W, DISP_STAGE_H);
    func_801B01F8(0);
}

void func_801B0324(void) {
    SetDefDrawEnv(&D_8003CB08.buf.draw, 0, 0, DISP_UNK2_W, DISP_UNK2_H);
    SetDefDrawEnv(&D_800542FC.buf.draw, 0, 256, DISP_UNK2_W, DISP_UNK2_H);
    SetDefDispEnv(&D_8003CB08.buf.disp, 0, 256, DISP_UNK2_W, DISP_UNK2_H);
    SetDefDispEnv(&D_8005435C, 0, 0, DISP_UNK2_W, DISP_UNK2_H);
    D_800542FC.buf.draw.clip.y = DISP_UNK2_W / 2;
    D_800542FC.buf.draw.clip.h = DISP_UNK2_H;
    D_8003CB08.buf.draw.clip.h = DISP_UNK2_H;
    D_8003CB08.buf.draw.clip.y = 0;
    D_800542FC.buf.draw.isbg = 1;
    D_8003CB08.buf.draw.isbg = 1;
    func_801B01C0();
    D_800542FC.buf.disp.isrgb24 = 0;
    D_8003CB08.buf.disp.isrgb24 = 0;
}

INCLUDE_ASM("asm/us/st/st0/nonmatchings/27D64", func_801B0414);

INCLUDE_ASM("asm/us/st/st0/nonmatchings/27D64", func_801B0464);

INCLUDE_ASM("asm/us/st/st0/nonmatchings/27D64", func_801B101C);

void func_801B1198(s16 arg0) {
    RECT rect;
    rect.x = 0x200;
    rect.y = arg0 * 16;
    rect.w = 0x80;
    rect.h = 0x10;

    ClearImage(&rect, 0, 0, 0);
}

INCLUDE_ASM("asm/us/st/st0/nonmatchings/27D64", func_801B11E8);

INCLUDE_ASM("asm/us/st/st0/nonmatchings/27D64", func_801B1298);

s32 Random(void) {
    g_randomNext = (g_randomNext * 0x01010101) + 1;
    return g_randomNext >> 0x18;
}

void Update(void) {
    s16 i;
    Entity* entity;
    s32* unk;

    for (i = 0; i < 0x20; i++) {
        if (D_801C2584[i]) {
            D_801C2584[i]--;
        }
    }

    unk = &D_80097410;
    if (*unk) {
        if (!--*unk) {
            g_api.FreePrimitives(D_80097414);
        }
    }

    for (entity = D_800762D8; entity < &D_8007EFD8; entity++) {
        if (!entity->pfnUpdate)
            continue;

        if (entity->step) {
            s32 unk34 = entity->flags;
            if (unk34 & FLAG_DESTROY_IF_OUT_OF_CAMERA) {
                s16 posX = i = entity->posX.i.hi;
                s16 posY = entity->posY.i.hi;
                if (unk34 & FLAG_DESTROY_IF_BARELY_OUT_OF_CAMERA) {
                    if ((u16)(posX + 64) > 384 || (u16)(posY + 64) > 352) {
                        DestroyEntity(entity);
                        continue;
                    }
                } else {
                    if ((u16)(posX + 128) > 512 || (u16)(posY + 128) > 480) {
                        DestroyEntity(entity);
                        continue;
                    }
                }
            }

            if ((unk34 & 0x02000000)) {
                s16 posY = entity->posY.i.hi + g_Camera.posY.i.hi;
                s16 test = (g_CurrentRoom.vSize * 256) + 128;
                if (posY > test) {
                    DestroyEntity(entity);
                    continue;
                }
            }

            if (unk34 & 0xF) {
                entity->palette =
                    D_801815EC[(entity->unk49 << 1) | (unk34 & 1)];
                entity->flags--;
                if ((entity->flags & 0xF) == 0) {
                    entity->palette = entity->unk6A;
                    entity->unk6A = 0;
                }
            }

            if (!(unk34 & 0x20000000) || (unk34 & 0x10000000) ||
                ((u16)(entity->posX.i.hi + 64) <= 384) &&
                    ((u16)(entity->posY.i.hi + 64) <= 352)) {
                if (!entity->unk58 || (entity->unk58--, unk34 & 0x100000)) {
                    if (!D_800973FC || unk34 & 0x2100 ||
                        (unk34 & 0x200 && !(D_8003C8C4 & 3))) {
                        g_CurrentEntity = entity;
                        entity->pfnUpdate(entity);
                        entity->unk44 = 0;
                        entity->unk48 = 0;
                    }
                }
            }
        } else {
            g_CurrentEntity = entity;
            entity->pfnUpdate(entity);
            entity->unk44 = 0;
            entity->unk48 = 0;
        }
    }
}

INCLUDE_ASM("asm/us/st/st0/nonmatchings/27D64", func_801B1B98);

INCLUDE_ASM("asm/us/st/st0/nonmatchings/27D64", func_801B1CA0);

INCLUDE_ASM("asm/us/st/st0/nonmatchings/27D64", EntityNumericDamage);

void CreateEntityFromLayout(Entity* entity, LayoutObject* initDesc) {
    DestroyEntity(entity);
    entity->objectId = initDesc->objectId & 0x3FF;
    entity->pfnUpdate = PfnEntityUpdates[entity->objectId];
    entity->posX.i.hi = initDesc->posX - g_Camera.posX.i.hi;
    entity->posY.i.hi = initDesc->posY - g_Camera.posY.i.hi;
    entity->subId = initDesc->subId;
    entity->objectRoomIndex = initDesc->objectRoomIndex >> 8;
    entity->unk68 = (initDesc->objectId >> 0xA) & 7;
}

void CreateEntityWhenInVerticalRange(LayoutObject* layoutObj) {
    s16 yClose;
    s16 yFar;
    s16 posY;
    Entity* entity;

    posY = g_Camera.posY.i.hi;
    yClose = posY - 0x40;
    yFar = posY + 0x120;
    if (yClose < 0) {
        yClose = 0;
    }

    posY = layoutObj->posY;
    if (posY < yClose) {
        return;
    }

    if (yFar < posY) {
        return;
    }

    switch (layoutObj->objectId & 0xE000) {
    case 0x0:
        entity = &D_800762D8[(u8)layoutObj->objectRoomIndex];
        if (entity->objectId == 0) {
            CreateEntityFromLayout(entity, layoutObj);
        }
        break;
    case 0x8000:
        break;
    case 0xA000:
        entity = &D_800762D8[(u8)layoutObj->objectRoomIndex];
        CreateEntityFromLayout(entity, layoutObj);
        break;
    }
}

void CreateEntityWhenInHorizontalRange(LayoutObject* layoutObj) {
    s16 xClose;
    s16 xFar;
    s16 posX;
    Entity* entity;

    posX = g_Camera.posX.i.hi;
    xClose = posX - 0x40;
    xFar = posX + 0x140;
    if (xClose < 0) {
        xClose = 0;
    }

    posX = layoutObj->posX;
    if (posX < xClose) {
        return;
    }

    if (xFar < posX) {
        return;
    }

    switch (layoutObj->objectId & 0xE000) {
    case 0x0:
        entity = &D_800762D8[(u8)layoutObj->objectRoomIndex];
        if (entity->objectId == 0) {
            CreateEntityFromLayout(entity, layoutObj);
        }
        break;
    case 0x8000:
        break;
    case 0xA000:
        entity = &D_800762D8[(u8)layoutObj->objectRoomIndex];
        CreateEntityFromLayout(entity, layoutObj);
        break;
    }
}

extern LayoutObject* D_801C00A0;
void func_801B33D4(s16 arg0) {
    while (true) {
        if (D_801C00A0->posX != 0xFFFE && D_801C00A0->posX >= arg0) {
            break;
        }
        D_801C00A0++;
    }
}

void func_801B3420(s16 arg0) {
    while (true) {
        if (D_801C00A0->posX != 0xFFFF &&
            (arg0 >= D_801C00A0->posX || D_801C00A0->posX == 0xFFFE)) {
            break;
        }
        D_801C00A0--;
    }
}

void func_801B3478(s16);
INCLUDE_ASM("asm/us/st/st0/nonmatchings/27D64", func_801B3478);

void func_801B3574(s16);
INCLUDE_ASM("asm/us/st/st0/nonmatchings/27D64", func_801B3574);

INCLUDE_ASM("asm/us/st/st0/nonmatchings/27D64", func_801B3688);

extern LayoutObject* D_801C00A4;
void func_801B36D4(s16 arg0) {
    while (true) {
        if ((D_801C00A4->posY != 0xFFFF) &&
            ((arg0 >= D_801C00A4->posY) || (D_801C00A4->posY == 0xFFFE))) {
            break;
        }
        D_801C00A4--;
    }
}

void func_801B372C(s16);
INCLUDE_ASM("asm/us/st/st0/nonmatchings/27D64", func_801B372C);

void func_801B3828(s16);
INCLUDE_ASM("asm/us/st/st0/nonmatchings/27D64", func_801B3828);

INCLUDE_ASM("asm/us/st/st0/nonmatchings/27D64", InitRoomEntities);

void func_801B3AB4(void) {
    Unkstruct8* currentRoomTileLayout = &g_CurrentRoomTileLayout;

    if (D_80097908 != 0) {
        s16 tmp = g_Camera.posX.i.hi;
        if (D_80097908 > 0)
            func_801B3478(tmp + 320);
        else
            func_801B3574(tmp - 64);
    }

    if (D_8009790C != 0) {
        s16 tmp = currentRoomTileLayout->unkE;
        if (D_8009790C > 0)
            func_801B372C(currentRoomTileLayout->unkE + 288);
        else
            func_801B3828(tmp - 64);
    }
}

void CreateEntityFromCurrentEntity(u16 objectId, Entity* entity) {
    DestroyEntity(entity);
    entity->objectId = objectId;
    entity->pfnUpdate = PfnEntityUpdates[objectId];
    entity->posX.i.hi = g_CurrentEntity->posX.i.hi;
    entity->posY.i.hi = g_CurrentEntity->posY.i.hi;
}

void CreateEntityFromEntity(u16 objectId, Entity* source, Entity* entity) {
    DestroyEntity(entity);
    entity->objectId = objectId;
    entity->pfnUpdate = PfnEntityUpdates[objectId];
    entity->posX.i.hi = source->posX.i.hi;
    entity->posY.i.hi = source->posY.i.hi;
}

s32 func_801B3C58(Entity* e) {
    s16 diff;

    diff = PLAYER.posX.i.hi - e->posX.i.hi;
    diff = ABS(diff);

    if (diff >= 17) {
        diff = 0;
    } else {
        diff = PLAYER.posY.i.hi - e->posY.i.hi;
        diff = ABS(diff);
        diff = diff < 33;
    }

    return diff;
}

INCLUDE_ASM("asm/us/st/st0/nonmatchings/27D64", EntityRedDoor);

void DestroyEntity(Entity* item) {
    s32 i;
    s32 length;
    u32* ptr;

    if (item->flags & FLAG_FREE_POLYGONS) {
        g_api.FreePrimitives(item->firstPolygonIndex);
    }

    ptr = (u32*)item;
    length = sizeof(Entity) / sizeof(s32);
    for (i = 0; i < length; i++)
        *ptr++ = 0;
}

void DestroyEntityFromIndex(s16 index) {
    Entity* entity = &g_EntityArray[index];

    while (entity < &D_8007EF1C) {
        DestroyEntity(entity);
        entity++;
    }
}

void PreventEntityFromRespawning(Entity* entity) {
    if (entity->objectRoomIndex) {
        u32 value = (entity->objectRoomIndex - 1);
        u16 index = value / 32;
        u16 bit = value % 32;
        g_entityDestroyed[index] |= 1 << bit;
    }
}

#include "st/AnimateEntity.h"

INCLUDE_ASM("asm/us/st/st0/nonmatchings/27D64", func_801B4AF0);

/*
 * Returns the absolute distance from g_CurrentEntity to player in the X Axis
 */
s16 func_801B4C08(void) {
    s16 xDistance = g_CurrentEntity->posX.i.hi - PLAYER.posX.i.hi;

    if (xDistance < 0) {
        xDistance = -xDistance;
    }
    return xDistance;
}

/*
 * Returns the absolute distance from g_CurrentEntity to player in the Y Axis
 */
s32 func_801B4C44(void) {
    s32 yDistance = g_CurrentEntity->posY.i.hi - PLAYER.posY.i.hi;

    if (yDistance < 0) {
        yDistance = -yDistance;
    }
    return yDistance;
}

s16 func_801B4C78(void) {
    s16 var_a0 = g_CurrentEntity->posX.i.hi > PLAYER.posX.i.hi;

    if (g_CurrentEntity->posY.i.hi > PLAYER.posY.i.hi) {
        var_a0 |= 2;
    }
    return var_a0;
}

void MoveEntity(void) {
    g_CurrentEntity->posX.val += g_CurrentEntity->accelerationX;
    g_CurrentEntity->posY.val += g_CurrentEntity->accelerationY;
}

void FallEntity(void) {
    if (g_CurrentEntity->accelerationY < FALL_TERMINAL_VELOCITY) {
        g_CurrentEntity->accelerationY += FALL_GRAVITY;
    }
}

u8 func_801B4D18(void) {
    u8 unkState;
    Entity* entity;

    MoveEntity();
    FallEntity();

    entity = g_CurrentEntity;

    if (unkState & 1) {
        entity->accelerationY = 0;
    }

    return unkState;
}

INCLUDE_ASM("asm/us/st/st0/nonmatchings/27D64", func_801B4D5C);

INCLUDE_ASM("asm/us/st/st0/nonmatchings/27D64", func_801B4FD4);

INCLUDE_ASM("asm/us/st/st0/nonmatchings/27D64", func_801B51E4);

Entity* AllocEntity(Entity* start, Entity* end) {
    Entity* current = start;
    while (current < end) {
        if (current->objectId == 0) {
            DestroyEntity(current);
            return current;
        }

        current++;
    }
    return NULL;
}

s32 func_801B542C(u8 arg0, s16 arg1) { return D_80181990[arg0] * arg1; }

s16 func_801B5458(u8 arg0) { return D_80181990[arg0]; }

void func_801B5474(s32 arg0, s16 arg1) {
    g_CurrentEntity->accelerationX = func_801B542C(arg0, arg1);
    g_CurrentEntity->accelerationY = func_801B542C(arg0 - 0x40, arg1);
}

u8 func_801B54E0(s16 arg0, s16 arg1) {
    return ((ratan2(arg1, arg0) >> 4) + 0x40);
}

u8 func_801B5518(Entity* arg0, Entity* arg1) {
    s16 a = arg1->posX.i.hi - arg0->posX.i.hi;
    s16 b = arg1->posY.i.hi - arg0->posY.i.hi;
    return func_801B54E0(a, b);
}

u8 func_801B5560(s32 arg0, s32 arg1) {
    s16 a = (arg0 - (u16)g_CurrentEntity->posX.i.hi);
    s16 b = (arg1 - (u16)g_CurrentEntity->posY.i.hi);
    return func_801B54E0(a, b);
}

u8 func_801B55A8(u8 arg0, u8 arg1, u8 arg2) {
    u8 var_v0;
    s8 temp_a2 = arg2 - arg1;

    if (temp_a2 < 0) {
        var_v0 = -temp_a2;
    } else {
        var_v0 = temp_a2;
    }

    if (var_v0 > arg0) {
        if (temp_a2 < 0) {
            var_v0 = arg1 - arg0;
        } else {
            var_v0 = arg1 + arg0;
        }

        return var_v0;
    }

    return arg2;
}

void func_801B5600(u16 slope, s16 speed) {
    Entity* entity;
    s32 moveX;
    s32 moveY;

    moveX = rcos(slope) * speed;
    entity = g_CurrentEntity;

    if (moveX < 0) {
        moveX += 15;
    }

    entity->accelerationX = moveX >> 4;

    moveY = rsin(slope) * speed;
    entity = g_CurrentEntity;

    if (moveY < 0) {
        moveY += 15;
    }

    entity->accelerationY = moveY >> 4;
}

u16 func_801B568C(s16 x, s16 y) { return ratan2(y, x); }

u16 func_801B56BC(Entity* a, Entity* b) {
    s32 diffX = b->posX.i.hi - a->posX.i.hi;
    s32 diffY = b->posY.i.hi - a->posY.i.hi;
    return ratan2(diffY, diffX);
}

u16 func_801B56F4(s32 x, s32 y) {
    s16 diffX = x - (u16)g_CurrentEntity->posX.i.hi;
    s16 diffY = y - (u16)g_CurrentEntity->posY.i.hi;
    return ratan2(diffY, diffX);
}

#ifndef NON_MATCHING
INCLUDE_ASM("asm/us/st/st0/nonmatchings/27D64", func_801B573C);
#else
// very minor reg swap
u16 func_801B573C(u16 arg0, s16 arg1, s16 arg2) {
    u16 temp_a2 = arg2 - arg1;
    u16 var_v0 = arg1;
    u16 var_v0_2;

    if (temp_a2 & 0x800) {
        var_v0_2 = temp_a2 & 0x7FF;
    } else {
        var_v0_2 = temp_a2;
    }

    if (var_v0_2 > arg0) {
        if (temp_a2 & 0x800) {
            var_v0 = arg1 - arg0;
        } else {
            var_v0 = arg1 + arg0;
        }

        return var_v0;
    }

    return arg2;
}
#endif

void func_801B5794(u8 state) {
    g_CurrentEntity->step = state;
    g_CurrentEntity->unk2E = 0;
    g_CurrentEntity->animFrameIdx = 0;
    g_CurrentEntity->animFrameDuration = 0;
}

void func_801B57B4(u8 arg0) {
    g_CurrentEntity->unk2E = arg0;
    g_CurrentEntity->animFrameIdx = 0;
    g_CurrentEntity->animFrameDuration = 0;
}

INCLUDE_ASM("asm/us/st/st0/nonmatchings/27D64", func_801B57D0);

void InitializeEntity(u16 arg0[]) {
    u16 enemyId;
    EnemyDef* enemyDef;

    g_CurrentEntity->animSet = *arg0++;
    g_CurrentEntity->animCurFrame = *arg0++;
    g_CurrentEntity->unk5A = *arg0++;
    g_CurrentEntity->palette = *arg0++;

    enemyId = *arg0++;
    g_CurrentEntity->enemyId = enemyId;
    enemyDef = &g_api.enemyDefs[enemyId];
    g_CurrentEntity->hitPoints = enemyDef->hitPoints;
    g_CurrentEntity->attack = enemyDef->attack;
    g_CurrentEntity->attackElement = enemyDef->attackElement;
    g_CurrentEntity->unk3C = enemyDef->unkC;
    g_CurrentEntity->hitboxWidth = enemyDef->hitboxWidth;
    g_CurrentEntity->hitboxHeight = enemyDef->hitboxHeight;
    g_CurrentEntity->flags = enemyDef->unk24;
    g_CurrentEntity->unk10 = 0;
    g_CurrentEntity->unk12 = 0;
    g_CurrentEntity->unk2E = 0;
    g_CurrentEntity->step++;
    if (g_CurrentEntity->zPriority == 0) {
        g_CurrentEntity->zPriority = g_zEntityCenter.S16.unk0 - 0xC;
    }
}

void EntityDummy(Entity* arg0) {
    if (arg0->step == 0) {
        arg0->step++;
    }
}

s32 func_801B5970(u16* hitSensors, s16 sensorCount) {
    Collider collider;
    s16 i;
    s32 accelerationX;
    u16 temp_a1;
    s16 x;
    s16 y;

    accelerationX = g_CurrentEntity->accelerationX;
    if (accelerationX != 0) {
        x = g_CurrentEntity->posX.i.hi;
        y = g_CurrentEntity->posY.i.hi;
        for (i = 0; i < sensorCount; i++) {
            if (accelerationX < 0) {
                s16 newX = x + *hitSensors++;
                x = newX;
            } else {
                s16 newX = x - *hitSensors++;
                x = newX;
            }

            y += *hitSensors++;
            g_api.CheckCollision(x, y, &collider, 0);
            if (collider.unk0 & 2 &&
                ((!(collider.unk0 & 0x8000)) || (i != 0))) {
                return 2;
            }
        }
        return 0;
    }
}

void func_801B5A98(u16* hitSensors, s16 sensorCount) {
    Collider collider;
    s16 i;
    s32 accelerationX;
    s16 x;
    s16 y;

    accelerationX = g_CurrentEntity->accelerationX;
    if (accelerationX == 0)
        return;
    x = g_CurrentEntity->posX.i.hi;
    y = g_CurrentEntity->posY.i.hi;
    for (i = 0; i < sensorCount; i++) {
        if (accelerationX < 0) {
            x = x + *hitSensors++;
        } else {
            x = x - *hitSensors++;
        }

        y += *hitSensors++;
        g_api.CheckCollision(x, y, &collider, 0);
        if (collider.unk0 & 2 && (!(collider.unk0 & 0x8000) || i != 0)) {
            if (accelerationX < 0) {
                g_CurrentEntity->posX.i.hi += collider.unk1C;
            } else {
                g_CurrentEntity->posX.i.hi += collider.unk14;
            }
            return;
        }
    }
}

INCLUDE_ASM("asm/us/st/st0/nonmatchings/27D64", func_801B5BF0);

void ReplaceBreakableWithItemDrop(Entity* self) {
    u16 subId;

    PreventEntityFromRespawning(self);

#if STAGE != STAGE_ST0
    if (!(g_Status.relics[10] & 2)) {
        DestroyEntity(self);
        return;
    }
#endif

    subId = self->subId &= 0xFFF;

    if (subId < 0x80) {
        self->objectId = ENTITY_PRICE_DROP;
        self->pfnUpdate = (PfnEntityUpdate)EntityPrizeDrop;
        self->animFrameDuration = 0;
        self->animFrameIdx = 0;
    } else {
        subId -= 0x80;
        self->objectId = ENTITY_INVENTORY_DROP;
        self->pfnUpdate = (PfnEntityUpdate)EntityEquipItemDrop;
    }

    self->subId = subId;
    self->unk6D = 0x10;
    self->step = 0;
}

void func_801B5EC8(void) {
    s32 temp_v1;
    Entity* entity;

    entity = g_CurrentEntity;
    if (entity->accelerationY >= 0) {
        temp_v1 = entity->unk88.S16.unk0 + entity->unk84.unk;
        entity->unk84.unk = temp_v1;
        entity->accelerationX = temp_v1;
        if (temp_v1 == 0x10000 || temp_v1 == -0x10000) {
            entity->unk88.S16.unk0 = -entity->unk88.S16.unk0;
        }
        entity = g_CurrentEntity;
    }
    NOP;

    if (entity->accelerationY < 0x00004000) {
        entity->accelerationY += 0x2000;
    }
}

void func_801B5F4C(u16 arg0) {
    Collider res;

    if (g_CurrentEntity->accelerationX < 0) {
        g_api.CheckCollision(g_CurrentEntity->posX.i.hi,
                             g_CurrentEntity->posY.i.hi - 7, &res, 0);
        if (res.unk0 & 5) {
            g_CurrentEntity->accelerationY = 0;
        }
    }

    g_api.CheckCollision(g_CurrentEntity->posX.i.hi,
                         g_CurrentEntity->posY.i.hi + 7, &res, 0);

    if (arg0) {
        if (!(res.unk0 & 5)) {
            MoveEntity();
            FallEntity();
            return;
        }

        g_CurrentEntity->accelerationX = 0;
        g_CurrentEntity->accelerationY = 0;

        if (res.unk0 & 4) {
            g_CurrentEntity->posY.val += 0x2000;
            return;
        }

        g_CurrentEntity->posY.i.hi += res.unk18;
        return;
    }

    if (!(res.unk0 & 5)) {
        MoveEntity();
        func_801B5EC8();
    }
}

INCLUDE_ASM("asm/us/st/st0/nonmatchings/27D64", CollectHeart);

INCLUDE_ASM("asm/us/st/st0/nonmatchings/27D64", CollectGold);

void func_801B61D4(void) {}

void func_801B61DC(void) { DestroyEntity(g_CurrentEntity); }

INCLUDE_ASM("asm/us/st/st0/nonmatchings/27D64", CollectSubweapon);

void CollectDummy(void) { DestroyEntity(g_CurrentEntity); }

Entity* func_801B633C(void) {
    g_CurrentEntity->step = 3;
    g_CurrentEntity->subId = 4;
    return g_CurrentEntity;
}
