#include "rbo3.h"

INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_80191080);

INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_80191148);

INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_80191304);

INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_80191438);

// EntityMedusa
// INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_8019179C);
extern u16 D_80180480[]; // Init
extern u8 D_801805F0[];
extern u8 D_801805FC[];
extern u8 D_8018060C[];
extern u8 D_80180618[];
extern u8 D_80180624[];
extern u8 D_80180630[];
extern u8 D_8018063C[];
extern s32 D_80180648[];
extern u8 D_80180670[];
extern s32 D_80180728;
extern s8 D_80190EE4;

void EntityMedusa(Entity* self) {
    Entity* newEntity;
    s8* hitbox;
    s16 rotAngle;
    s32 posX;
    s32 i;

    if (self->flags & 0x100) {
        if (self->step != 7) {
            func_801971F0(7);
        }
    }

    switch (self->step) {
        case 0:
            func_801972C0(D_80180480);
            self->animCurFrame = 1;
            self->hitboxState = 0;
            func_80195884(0x19, self, &self[1]);
            func_801971F0(1);

        case 1:
            if (D_80180728 & 1) {
                func_801971F0(2);
            }
            break;

        case 2:
            if (func_801966E0(D_801805F0, self) == 0) {
                self->hitboxState = 3;
                func_801971F0(3);
            }
            break;

        case 3:
            func_801966E0(D_801805FC, self);

            if (self->step_s == 0) {
                self->ext.generic.unk80.modeS16.unk0 = 64;
                self->step_s++;
            }

            if (func_801968B0() < 104) {
                self->ext.generic.unk84.S8.unk0 = 1;
            }

            if (func_801968B0() > 128) {
                self->ext.generic.unk84.S8.unk0 = 0;
            }

            if (func_801968B0() > 32) {
                self->facing = func_80196920() & 1;
            }

            func_80196964();
            if (self->facing == self->ext.generic.unk84.U8.unk0) {
                self->velocityX = 0x8000;
            } else {
                self->velocityX = -0x8000;
            }

            if (self->hitFlags & 3) {
                func_801971F0(6);
            }

            posX = PLAYER.posX.i.hi - self->posX.i.hi;
            if ((g_Player.unk0C & 0x2000) && ((posX * PLAYER.velocityX) < 0)) {
                if (ABS(posX) < 80) {
                    func_801971F0(5);
                }
            }

            if (--self->ext.generic.unk80.modeS16.unk0 == 0) {
                func_80196920();
                if (func_801968B0() <= 64) {
                    func_801971F0(5);
                } else {
                    func_801971F0(4);
                }
            }
            break;

        case 5:
            if (self->step_s == 0) {
                if (func_80193198() & 1) {
                    func_8019C668(0x7FE);
                } else {
                    func_8019C668(0x7FF);
                }
                func_8019C668(0x7C8);
                self->step_s++;
            }
            self->ext.generic.unk84.S8.unk1 = 1;
            if (func_801966E0(D_80180624, self) == 0) {
                self->ext.generic.unk84.S8.unk1 = 0;
                func_801971F0(3);
            }
            break;

        case 4:
            if (self->step_s == 0) {
                if (!(func_80193198() & 3)) {
                    func_8019C668(0x7FB);
                }
                self->step_s++;
            }

            if (func_801966E0(D_8018060C, self) == 0) {
                func_801971F0(3);
                if (g_Player.unk0C & 0x80) {
                    func_801971F0(8);
                }
            }

            if (LOW(self->animFrameIdx) == 4) {
                newEntity = func_80196E20(D_8007A958, &D_8007A958[32]);
                if (newEntity != NULL) {
                    func_80195884(0x18, self, newEntity);
                    newEntity->facing = self->facing;
                    if (self->facing != 0) {
                        newEntity->posX.i.hi -= 13;
                    } else {
                        newEntity->posX.i.hi += 13;
                    }
                    newEntity->posY.i.hi -= 28;
                    func_8019C668(0x61F);
                }
            }
            break;

        case 8:
            if (self->step_s == 0) {
                func_8019C668(0x7FD);
                self->step_s++;
            }

            if (func_801966E0(D_80180618, self) == 0) {
                func_801971F0(3);
            }

            if (LOW(self->animFrameIdx) == 3) {
                func_8019C668(0x7D1);
                for (i = 0; i < 2; i++, rotAngle += 0x400) {
                    newEntity = func_80196E20(&g_Entities[160], &g_Entities[192]);
                    if (newEntity != NULL) {
                        func_80195884(0x1A, self, newEntity);
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
                if (func_80193198() & 1) {
                    func_8019C668(0x801);
                } else {
                    func_8019C668(0x802);
                }
                self->step_s++;
            }

            if (func_801966E0(D_80180630, self) == 0) {
                self->facing = func_80196920() & 1;
                func_801971F0(4);
            }
            break;

        case 7: // FUCKING_DEAD
            switch (self->step_s) {
                case 0:
                    func_8019C668(0x804);
                    self->hitboxState = 0;
                    D_80180728 |= 2;
                    self->step_s++;

                case 1:
                    if (func_801966E0(D_8018063C, self) == 0) {
                        self->ext.generic.unk80.modeS16.unk0 = 80;
                        func_8019C668(0x7C5);
                        self->step_s++;
                    }
                    break;

                case 2:
                    newEntity = func_80196E20(D_8007C0D8, &D_8007C0D8[64]);
                    if (newEntity != NULL) {
                        func_80195884(0x1B, self, newEntity);
                        newEntity->params = 0;
                        newEntity->zPriority = self->zPriority + 1;
                        newEntity->posX.i.hi -= 16 - (func_80193198() & 31);
                        newEntity->posY.i.hi += 24;
                    }

                    if (!(self->ext.generic.unk80.modeS16.unk0 & 0xF)) {
                        func_8019C668(0x661);
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

INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_80192020);

INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_801922EC);

INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_801923DC);

INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_80192998);

INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_80192B38);

INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_80192D64);

INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_80193050);

INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_80193198);

INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_801931C8);

INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_801934C4);

INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_801935CC);

INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_801946E4);

INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_80194D88);

INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_80194E4C);

INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_80194F64);

INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_8019507C);

INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_801950C8);

INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_80195120);

INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_8019521C);

INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_80195330);

INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_8019537C);

INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_801953D4);

INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_801954D0);

INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_801955E4);

INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_8019575C);

INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_80195810);

INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_80195884);

INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_80195900);

INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_80195978);

INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_801965B0);

INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_8019661C);

INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_80196698);

INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_801966E0);

INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_80196798);

INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_801968B0);

INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_801968EC);

INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_80196920);

INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_80196964);

INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_80196994);

INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_801969C0);

INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_80196C38);

INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_80196E20);

INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_80196E80);

INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_80196EAC);

INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_80196EC8);

INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_80196F34);

INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_80196F6C);

INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_80196FB4);

INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_80196FFC);

INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_80197054);

INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_801970E0);

INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_80197110);

INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_80197148);

INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_80197190);

INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_801971F0);

INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_80197210);

INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_8019722C);

INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_801972C0);

INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_801973BC);

INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_801973E4);

INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_8019750C);

INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_80197664);

INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_801979A8);

INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_80197A60);

INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_80197AE4);

INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_80197C40);

INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_80197CC0);

INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_80197D9C);

INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_80197EB4);

INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_80197F58);

void func_80197FA8(void) {
    func_801965B0(g_CurrentEntity);
}

INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_80197FD0);

INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_80198844);

INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_80198940);

INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_801989E4);

INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_80198FCC);

INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_8019927C);

INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_80199D4C);

INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_80199E68);

INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_8019A3C4);

INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_8019A4B4);

INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_8019A5C4);

INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_8019A6F4);

INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_8019A7DC);

INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_8019A8CC);

INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_8019A9C0);

INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_8019ABF0);

INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_8019ACEC);

INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_8019B26C);

INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_8019B36C);

INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_8019B438);

INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_8019B500);

INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_8019B5B8);

INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_8019B790);

INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_8019BD70);

INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_8019C470);

INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_8019C668);

INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_8019C760);

INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_8019C930);

INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_8019D5B4);

INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_8019D948);

INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_8019DDF8);

INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_8019DEE4);

INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_8019E214);

INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_8019E5FC);

INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_8019E74C);

INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_8019E77C);

INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_8019E7F8);

INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_8019E880);

INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_8019E960);

INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_8019E9B4);

INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_8019E9E0);

INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_8019EA44);

INCLUDE_ASM("asm/us/boss/rbo3/nonmatchings/11080", func_8019F2F8);
