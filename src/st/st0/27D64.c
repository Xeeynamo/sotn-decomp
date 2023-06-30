#include "st0.h"

void func_801A7D64(Entity* arg0) {
    s32 temp_v0;
    ObjInit2* temp_s0 = &D_80180638[arg0->params];

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

    temp_s1 = entity->params;
    if (entity->step == 0) {
        InitializeEntity(D_801805B0);
        temp_v1 = temp_s1 & 0xFFFF;
        entity->unk3C = 1;
        temp_v0 = D_80180660[temp_v1];
        entity->ext.generic.unk7C.modeU16 = temp_v0;
        if (temp_v0) {
            entity->hitboxWidth = D_8018065C[temp_v1];
            entity->hitboxHeight = 20;
        } else {
            entity->hitboxWidth = 20;
            entity->hitboxHeight = D_8018065C[temp_v1];
        }
    }

    if (entity->params & 0x100) {
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
        if (entity->ext.generic.unk7C.modeU16) {
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
    s32 params = (s16)entity->params;

    FntPrint("set:%04x\n", params);
    FntPrint("sx:%04x\n", g_CurrentRoom.left);
    FntPrint("ex:%04x\n", g_CurrentRoom.right);

    switch (entity->step) {
    case 0:
        InitializeEntity(D_801805BC);
        entity->animSet = 2;
        entity->animCurFrame = 1;
        entity->zPriority = 0xB0;
        break;

    case 1:
        dist = entity->posY.i.hi - PLAYER.posY.i.hi;
        dist = ABS(dist);

        if (dist < 0x20) {
            switch (params) {
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
