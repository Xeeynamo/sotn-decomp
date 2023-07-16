#include "dre.h"

// ID 0x19
// INCLUDE_ASM("asm/us/st/dre/nonmatchings/12104", EntitySuccubus);
extern u16 D_8007C6E8;
extern u16 D_801804D0[];
extern u8 D_8018066C[]; // Animation
extern u8 D_80180674[]; // Animation
extern u8 D_80180680[]; // Animation
extern u8 D_80180694[]; // Animation
extern u8 D_801806A0[]; // Animation
extern u8 D_801806C4[]; // Animation
extern u8 D_801806D4[]; // Animation
extern u8 D_801806E8[]; // Animation
extern u8 D_801806F8[]; // Animation
extern u8 D_8018070C[]; // Animation
extern u8 D_8018071C[]; // Animation
extern u8 D_8018072C[]; // Animation
extern u8 D_80180734[]; // Animation
extern u8 D_80180748[]; // Animation
extern u8 D_80180760[]; // Animation
extern u8 D_80180768[]; // Animation
extern u8 D_80180770[]; // Animation
extern u8 D_80180778[]; // Animation
extern u8 D_80180780[]; // Animation
extern u8 D_8018079C[]; // Animation
extern u8 D_801807AC[]; // Animation
extern s8 D_801807D4[4][7];
extern s32 D_801807F8[];
extern u8 D_80180830[];
extern s8 D_801816C4;
extern s32 D_801A3ED4;
extern s32 D_801A3F84;
extern s32 D_80180660;

void EntitySuccubus(Entity* self) {
    Entity* newEntity;
    s32 posX, posY;
    u8* ClonesPos;
    s8* hitbox;
    s32 facing;
    s16 angle;
    s32 temp_s5;
    s32 fakeTemp;
    s32 i;

    FntPrint("multiple_count %x\n", D_80180660);
    if ((self->hitFlags & 3) && (self->step & 1)) {
        SetStep(14);
    }

    if (self->flags & 0x100) {
        if (self->step != 0x12) {
            self->hitboxState = 0;
            SetStep(18);
        }
    }

    switch (self->step) {
        case 0: // Init
            InitializeEntity(D_801804D0);
            self->animCurFrame = 0x52;
            SetStep(1);
            CreateEntityFromCurrentEntity(0x1B, &self[1]);

        case 1:
            if ((D_8003BDEC[212] != 0) || (g_DemoMode != Demo_None)) {
                self->facing = 0;
                self->posX.i.hi = 0x1A0 - g_Camera.posX.i.hi;
                self->posY.i.hi = 0xAF - g_Camera.posY.i.hi;
                SetStep(4);
                self->step_s = 3;
            }
            self->animCurFrame = 0x52;
            if (D_801A3F84 & 4) {
                SetStep(2);
            }
            break;

        case 2:
            if (D_801A3ED4 != 0) {
                SetSubStep(4);
            }
            switch (self->step_s) {
                case 0:
                    AnimateEntity(D_8018079C, self);
                    if (D_801A3F84 & 0x400) {
                        SetSubStep(1);
                    }
                    break;

                case 1:
                    AnimateEntity(D_801807AC, self);
                    if (D_801A3F84 & 0x800) {
                        self->animCurFrame = 0x54;
                        SetSubStep(2);
                    }
                    break;

                case 2:
                    if (D_801A3F84 & 0x1000) {
                        SetSubStep(3);
                    }
                    break;

                case 3:
                    self->animCurFrame = 0x53;
                    if (D_801A3F84 & 0x2000) {
                        SetSubStep(4);
                    }
                    break;

                case 4:
                    self->animCurFrame = 0x54;
                    if (D_801A3F84 & 0x20) {
                        SetStep(3);
                    }
                    break;
            }
            break;

        case 3:
            if ((D_801A3ED4 == 0) || (self->step_s == 0)) {
                switch (self->step_s) {
                    case 0:
                        self->facing = 0;
                        self->posX.i.hi = 416 - g_Camera.posX.i.hi;
                        self->posY.i.hi = 175 - g_Camera.posY.i.hi;
                        self->step_s++;

                    case 1:
                        AnimateEntity(D_8018066C, self);
                        if (D_801A3F84 & 0x40) {
                            SetSubStep(2);
                        }
                        break;

                    case 2:
                        self->animCurFrame = 4;
                        if (D_801A3F84 & 0x80) {
                            SetSubStep(3);
                        }
                        break;

                    case 3:
                        AnimateEntity(D_80180674, self);
                        if (D_801A3F84 & 0x100) {
                            SetSubStep(4);
                        }
                        break;

                    case 4:
                        if (AnimateEntity(D_80180680, self) == 0) {
                            SetStep(4);
                        }
                        break;
                }
            } else {
                SetStep(4);
            }
            break;

        case 4:
            switch (self->step_s) {
                case 0:
                    if (AnimateEntity(D_80180694, self) == 0) {
                        SetSubStep(1);
                    }
                    break;

                case 1:
                    g_api.PlaySfx(0x330);
                    g_api.func_800FD4C0(9, 2);
                    self->accelerationX = 0;
                    self->accelerationY = -0x40000;
                    self->step_s++;

                case 2:
                    MoveEntity();
                    self->accelerationY += 0x2000;
                    if (self->accelerationY > 0) {
                        self->accelerationY = 0;
                    }
                    if (AnimateEntity(D_801806A0, self) == 0) {
                        SetStep(5);
                    }
                    break;

                case 3:
                    AnimateEntity(D_80180694, self);
                    if (GetDistanceToPlayerX() < 0x60) {
                        SetSubStep(1);
                    }
                    break;
            }
            break;

        case 18:
            switch (self->step_s) {
                case 0:
                    func_801A046C(0x87B);
                    CreateEntityFromCurrentEntity(0x20, &g_Entities[200]);
                    D_8007C6E8 = 1;
                    D_80180660 = 0;
                    D_80180664 |= 2;
                    g_api.func_800FD4C0(9, 1);
                    self->accelerationX = 0;
                    self->accelerationY = 0;
                    posY = self->posY.i.hi + g_Camera.posY.i.hi;
                    if (posY > 160) {
                        self->accelerationY = -0x20000;
                        self->step_s = 1;
                    } else {
                        self->step_s = 2;
                    }
                    break;

                case 1:
                    AnimateEntity(D_80180768, self);
                    MoveEntity();
                    self->accelerationY += 0x2000;
                    if (self->accelerationY > 0) {
                        self->step_s = 2;
                    }
                    break;

                case 2:
                    AnimateEntity(D_80180768, self);
                    MoveEntity();
                    self->accelerationY += 0x2000;
                    posY = self->posY.i.hi + g_Camera.posY.i.hi;
                    if (posY >= 176) {
                        func_801A046C(0x646);
                        self->posY.i.hi = 175 - g_Camera.posY.i.hi;
                        SetSubStep(3);
                        posX = self->posX.i.hi + g_Camera.posX.i.hi;
                        if (posX < 80) {
                            D_801816C4 = self->facing = 1;
                        } else if (posX > 432) {
                            D_801816C4 = self->facing = 0;
                        } else {
                            D_801816C4 = self->facing = (GetSideToPlayer() & 1) ^ 1;
                        }
                        D_801A3F84 |= 2;
                    }
                    break;

                case 3:
                    AnimateEntity(D_80180770, self);
                    if (D_801A3F84 & 0x10) {
                        SetSubStep(4);
                    }
                    break;

                case 4:
                    AnimateEntity(D_80180778, self);
                    break;
            }
            break;

        case 5:
            if (self->step_s == 0) {
                self->ext.generic.unk80.modeS16.unk0 = 64;
                self->step_s++;
            }
            AnimateEntity(D_801806C4, self);
            if (LOW(self->animFrameIdx) == 3) {
                func_801A046C(0x6C6);
            }
            posY = self->posY.i.hi - self->ext.generic.unk8C.modeS16.unk2;
            if (posY > 8) {
                self->accelerationY = -0xC000;
            }
            if (--self->ext.generic.unk80.modeS16.unk0 == 0) {
                self->ext.generic.unk88.S16.unk0 = 7;
                SetStep(15);
            }
            if ((self->ext.generic.unk80.modeS16.unk0 < 80) && (GetDistanceToPlayerX() < 80)) {
                self->ext.generic.unk88.S16.unk0 = 7;
                SetStep(15);
            }
            break;

        case 7:
            switch (self->step_s) {
                case 0:
                    self->accelerationY = 0;
                    self->ext.generic.unk80.modeS16.unk0 = (Random() & 31) + 0x20;
                    self->ext.generic.unk84.S8.unk2 = 8;
                    self->ext.generic.unk8C.modeU16.unk2 = 0x58;
                    if (!(Random() % 4)) {
                        if (Random() % 2) {
                            self->ext.generic.unk84.S8.unk2 = 12;
                            self->ext.generic.unk8C.modeU16.unk2 = 120;
                        } else {
                            self->ext.generic.unk84.S8.unk2 = 11;
                        }
                    }
                    self->ext.generic.unk84.S8.unk0 = 0;
                    self->step_s++;

                case 1:
                    AnimateEntity(D_801806E8, self);
                    if (LOW(self->animFrameIdx) == 3) {
                        func_801A046C(0x6C6);
                    }
                    MoveEntity();
                    posY = self->posY.i.hi - self->ext.generic.unk8C.modeS16.unk2;
                    if (posY >= 9) {
                        self->accelerationY = -0xC000;
                    }
                    if (posY < -8) {
                        self->accelerationY = 0xC000;
                    }

                    if (self->facing != self->ext.generic.unk84.U8.unk0) {
                        self->accelerationX += 0x1800;
                        if (self->accelerationX >= 0x16000) {
                            self->accelerationX = 0x16000;
                        }
                    } else {
                        self->accelerationX -= 0x1800;
                        if (self->accelerationX <= -0x16000) {
                            self->accelerationX = -0x16000;
                        }
                    }

                    if (self->ext.generic.unk84.U8.unk2 == 11) {
                        posX = 64;
                    } else {
                        posX = 96;
                    }

                    temp_s5 = GetDistanceToPlayerX();
                    if (self->ext.generic.unk84.U8.unk0 == 0) {
                        if (temp_s5 < posX) {
                            self->ext.generic.unk84.U8.unk0 ^= 1;
                        }
                        if (self->ext.generic.unk84.U8.unk0 != 0) {
                            if (posX < temp_s5) {
                                self->ext.generic.unk84.U8.unk0 ^= 1;
                            }
                        }
                    } else if (posX < temp_s5) {
                        self->ext.generic.unk84.U8.unk0 ^= 1;
                    }
                    
                    if (((GetSideToPlayer() & 1) ^ 1) != self->facing) { // TODO: Regalloc
                        if (temp_s5 > 16) {
                            self->ext.generic.unk88.S16.unk0 = 11;
                            SetStep(16);
                        }
                    }

                    posX = self->posX.i.hi + g_Camera.posX.i.hi;
                    if (self->facing != 0) {
                        posX = 512 - posX;
                    }
                    if (posX > 416) {
                        self->ext.generic.unk84.S8.unk0 = 0;
                        self->ext.generic.unk80.modeS16.unk0 = 96;
                        self->step_s++;
                    }

                    if (self->ext.generic.unk80.modeS16.unk0 == 0) {
                        if (GetDistanceToPlayerX() < 0x60) {
                            if (self->ext.generic.unk84.U8.unk2 == 8) {
                                SetStep(8);
                            } else {
                                self->ext.generic.unk88.S16.unk0 = self->ext.generic.unk84.U8.unk2;
                                SetStep(16);
                            }
                        }
                    } else {
                        self->ext.generic.unk80.modeS16.unk0--;
                    }
                    break;

                case 2:
                    if (self->facing != self->ext.generic.unk84.U8.unk0) {
                        self->accelerationX += 0x1800;
                        if (self->accelerationX >= 0x16000) {
                            self->accelerationX = 0x16000;
                        }
                    } else {
                        self->accelerationX -= 0x1800;
                        if (self->accelerationX <= -0x16000) {
                            self->accelerationX = -0x16000;
                        }
                    }
                    AnimateEntity(D_801806E8, self);
                    if (LOW(self->animFrameIdx) == 3) {
                        func_801A046C(0x6C6);
                    }
                    MoveEntity();
                    if (--self->ext.generic.unk80.modeS16.unk0 == 0) {
                        self->step_s = 0;
                    }
                    break;
            }
            break;

        case 15:
            if (self->step_s == 0) {
                self->facing = (GetSideToPlayer() & 1) ^ 1;
                self->step_s++;
            }
            if (AnimateEntity(D_801806D4, self) == 0) {
                if (self->ext.generic.unk88.U16.unk0 != 0) {
                    SetStep(self->ext.generic.unk88.U16.unk0);
                    self->ext.generic.unk88.S16.unk0 = 0;
                } else {
                    SetStep(7);
                }
            }
            break;

        case 16:
            if (AnimateEntity(D_801806F8, self) == 0) {
                if (self->ext.generic.unk88.U16.unk0 != 0) {
                    SetStep(self->ext.generic.unk88.U16.unk0);
                    self->ext.generic.unk88.S16.unk0 = 0;
                } else {
                    SetStep(5);
                }
            }
            break;

        case 8: // Petal attack
            switch (self->step_s) {
                case 0:
                    self->facing = (GetSideToPlayer() & 1) ^ 1;
                    if (g_Player.unk0C & 0x8000) {
                        self->ext.generic.unk84.S8.unk3 = 0;
                    } else {
                        self->ext.generic.unk84.S8.unk3 = 1;
                    }
                    D_80180668 = 0;
                    self->step_s++;

                case 1:
                    if (AnimateEntity(D_8018070C, self) == 0) {
                        self->ext.generic.unk80.modeS16.unk0 = 128;
                        func_801A046C(0x86E);
                        self->step_s++;
                    }
                    break;

                case 2:
                    if (!(self->ext.generic.unk80.modeS16.unk0 & 1)) {
                        newEntity = AllocEntity(D_8007A958, &D_8007A958[32]);
                        if (newEntity != NULL) {
                            CreateEntityFromEntity(0x1A, self, newEntity);
                            newEntity->facing = self->facing;
                            newEntity->zPriority = self->zPriority - 1;
                        }
                    }
                    if (!((u16)self->ext.generic.unk80.modeS16.unk0 % 64)) {
                        func_801A046C(0x6B0);
                    }
                    if (--self->ext.generic.unk80.modeS16.unk0 == 0) {
                        SetStep(7);
                    }
                    if (self->ext.generic.unk84.U8.unk3 != 0) {
                        if (g_Player_unk0C & 0x8000) {
                            SetStep(9);
                        }
                    } else if (D_80180668 != 0) {
                        if (!(GetDistanceToPlayerX() <= 72)) {
                            self->ext.generic.unk88.S16.unk0 = 13;
                            SetStep(15);
                        }
                    }
                    break;
            }
            break;

        case 9:
            switch (self->step_s) {
                case 0:
                    self->ext.generic.unk80.modeS16.unk0 = 112;
                    self->animCurFrame = 36;
                    func_801A046C(0x86F);
                    self->step_s++;

                case 1:
                    newEntity = &PLAYER;
                    posX = newEntity->posX.i.hi - self->posX.i.hi;
                    if (self->facing != 0) {
                        posX -= 16;
                    } else {
                        posX += 16;
                    }
                    posY = newEntity->posY.i.hi - self->posY.i.hi;
                    angle = ratan2(posY, posX);

                    self->accelerationX = (rcos(angle) << 0x11) >> 0xC;
                    self->accelerationY = (rsin(angle) << 0x11) >> 0xC;
                    posX = self->accelerationX;
                    if (self->facing != 0) {
                        posX = -posX;
                    }
                    if (posX > 0) {
                        self->accelerationX = 0;
                    }
                    
                    MoveEntity();
                    
                    posX = PLAYER.posX.i.hi - self->posX.i.hi;
                    if (self->facing == 0) {
                        posX = -posX;
                    }
                    posX -= 4;
                    if (posX < 0) {
                        posX = 512;
                    }
                    posY = PLAYER.posY.i.hi - self->posY.i.hi;
                    if (posY < 0) {
                        posY = -posY;
                    }
                    
                    if (!(g_Player_unk0C & 0x010401A2)) {
                        if ((posY < 12) && (posX < 24)) {
                            g_Player.unk60 = 1;
                            g_Player.unk64 = 0;
                            g_Player.unk62 = 0;
                            self->hitboxState = 0;
                            self->step_s++;
                        }
                    } else {
                        FntPrint("ng status\n");
                    }

                    posY = self->posY.i.hi + g_Camera.posY.i.hi;
                    if (posY > 176) {
                        self->posY.i.hi = 176 - g_Camera.posY.i.hi;
                    }

                    if (g_Player.unk60 == 0) {
                        if (--self->ext.generic.unk80.modeS16.unk0 == 0) {
                            self->ext.generic.unk84.S8.unk3 = 0;
                            SetStep(7);
                            break;
                        }
                    }
                    break;

                case 2:
                    newEntity = &PLAYER;
                    posX = newEntity->posX.i.hi;
                    if (self->facing != 0) {
                        posX -= 16;
                    } else {
                        posX += 16;
                    }
                    self->posY.i.hi = posY = newEntity->posY.i.hi;
                    self->posX.i.hi = posX;
                    func_801A046C(0x876);
                    self->step_s++;

                case 3:
                    if (AnimateEntity(D_8018071C, self) == 0) {
                        g_Player.unk64 = g_api.enemyDefs[347].attack;
                        g_Player.unk60 = 3;
                        self->ext.generic.unk80.modeS16.unk0 = 48;
                        self->step_s++;
                    }
                    break;

                case 4:
                    if (--self->ext.generic.unk80.modeS16.unk0 == 0) {
                        g_Player.unk60 = 0;
                        self->hitboxState = 3;
                        if (self->facing != 0) {
                            self->accelerationX = -0x40000;
                        } else {
                            self->accelerationX = 0x40000;
                        }
                        self->accelerationY = -0x40000;
                        self->animCurFrame = 47;
                        self->ext.generic.unk80.modeS16.unk0 = 24;
                        self->step_s++;
                    }
                    break;

                case 5:
                    MoveEntity();
                    self->accelerationX -= self->accelerationX >> 5;
                    self->accelerationY -= self->accelerationY >> 5;
                    if (--self->ext.generic.unk80.modeS16.unk0 == 0) {
                        SetStep(13);
                    }
                    break;
            }
            break;

        case 13:
            if (self->step_s == 0) {
                self->ext.generic.unk80.modeS16.unk0 = 80;
                self->facing = (GetSideToPlayer() & 1) ^ 1;
                self->step_s++;
                if (self->ext.generic.unk84.U8.unk3 != 0) {
                    func_801A046C(0x8D1);
                } else {
                    func_801A046C(0x86E);
                }
                self->ext.generic.unk84.S8.unk3 = 0;
            }
            AnimateEntity(D_8018072C, self);
            if ((--self->ext.generic.unk80.modeS16.unk0 == 0) || (GetDistanceToPlayerX() < 32)) {
                SetStep(7);
            }
            break;

        case 11: // CLONE ATTACK
            switch (self->step_s) {
                case 1:
                    posX = (self->posX.i.hi + g_Camera.posX.i.hi);
                    posX -= 192;

                    if (posX < 32) {
                        posX = 96 - ((32 - posX) % 64);
                    }

                    if ((posX + 384) > 480) {
                        posX = ((posX - 96) % 64) + 32;
                    }
#if 0
                    // !FAKE
                    ClonesPos = *D_801807D4;
                    ClonesPos += (Random() & 3) * 7;
#else
                    
#endif
                        
                    ClonesPos = &D_801807D4[Random() & 3][0];
                    newEntity = &g_Entities[112];
                    temp_s5 = self->posX.i.hi + g_Camera.posX.i.hi;

                    for (i = 0; i < 6; i++, newEntity++, ClonesPos++, posX += 64) {
                        CreateEntityFromEntity(0x1C, self, newEntity);
                        newEntity->ext.generic.unk9C = self;
                        if (posX == temp_s5) {
                            posX += 64;
                        }
                        newEntity->ext.generic.unkA0 = posX;
                        newEntity->params = *ClonesPos;
                    }
                    self->params = *ClonesPos;
                    self->ext.generic.unk80.modeS16.unk0 = 64;
                    self->hitboxState = 0;
                    D_80180660 = 6;
                    func_801A046C(0x870);
                    func_801A046C(0x6D5);
                    self->step_s++;

                case 2:
                    if (--self->ext.generic.unk80.modeS16.unk0 == 0) {
                        self->step_s = 3;
                    }

                case 0:
                    self->ext.generic.unk84.S8.unk1 = 0;
                    AnimateEntity(D_80180734, self);
                    if (LOW(self->animFrameIdx) == 4) {
                        self->step_s++;
                    }
                    break;

                case 3:
                    newEntity = &g_Entities[0x70];
                    newEntity += fakeTemp = Random() % 6; // !FAKE

                    posX = newEntity->posX.i.hi;
                    posY = newEntity->posY.i.hi;
                    newEntity->posX.i.hi = self->posX.i.hi;
                    newEntity->posY.i.hi = self->posY.i.hi;
                    self->posX.i.hi = posX;
                    self->posY.i.hi = posY;
                    self->hitboxState = 3;
                    self->step_s++;

                case 4:
                    if (AnimateEntity(D_80180734, self) == 0) {
                        SetSubStep(5);
                    }
                    break;

                case 5:
                    if (AnimateEntity(D_80180760, self) == 0) {
                        self->ext.generic.unk84.S8.unk1 = 1;
                        self->ext.generic.unk80.modeS16.unk0 = (self->params * 0x30) + 1;
                        SetSubStep(6);
                    }
                    break;

                case 6:
                    self->animCurFrame = 26;
                    if (--self->ext.generic.unk80.modeS16.unk0 == 0) {
                        self->ext.generic.unk84.S8.unk1 = 0;
                        SetSubStep(6);
                    }
                    if (D_80180660 == 0) {
                        SetStep(5);
                    }
                    break;

                case 7:
                    if (AnimateEntity(D_80180780, self) == 0) {
                        self->ext.generic.unk80.modeS16.unk0 = 288;
                        SetSubStep(4);
                    }
                    if (LOW(self->animFrameIdx) == 4) {
                        func_801A046C(0x6E2);

                        for (i = 0; i < 2; i++) {
                            newEntity = AllocEntity(D_8007A958, &D_8007A958[32]);
                            if (newEntity != NULL) {
                                CreateEntityFromEntity(0x1D, self, newEntity);
                                newEntity->params = i;
                                if (i != 0) {
                                    newEntity->posX.i.hi -= 2;
                                } else {
                                    newEntity->posX.i.hi += 2;
                                }
                                newEntity->ext.generic.unk9C = self;
                                newEntity->posY.i.hi -= 13;
                                newEntity->zPriority = self->zPriority + 1;
                            }
                        }
                    }
                    if (LOW(self->animFrameIdx) == 5) {
                        func_801A046C(0x872);
                        func_801A046C(0x87C);
                        func_801A046C(0x62C);
                        self->ext.generic.unk84.S8.unk1 = 1;
                    }
                    break;
            }
            break;

        case 12: // "spike" attack
            switch (self->step_s) {
                case 0:
                    newEntity = &g_Entities[96];
                    self->facing = 0;
                    self->ext.generic.unk84.S8.unk1 = 0;
                    D_80180668 = 0;
                    for (facing = 0; facing < 2; facing++) {
                        for (i = 0; i < 4; i++, newEntity += 2) {
                            CreateEntityFromEntity(0x1E, self, newEntity);
                            newEntity->params = i;
                            newEntity->zPriority = self->zPriority;
                            newEntity->ext.generic.unk9C = self;
                            if (facing == 0) {
                                newEntity->posX.i.hi -= 5;
                            } else {
                                newEntity->posX.i.hi += 4;
                            }
                            newEntity->posY.i.hi -= 27;
                            newEntity->facing = facing;
                        }
                    }
                    self->step_s++;

                case 1:
                    if (AnimateEntity(D_80180748, self) == 0) {
                        self->ext.generic.unk84.S8.unk1 = 1;
                        func_801A046C(0x6AF);
                        func_801A046C(0x874);
                        self->ext.generic.unk80.modeS16.unk0 = 64;
                        SetSubStep(2);
                    }
                    break;

                case 2:
                    if (--self->ext.generic.unk80.modeS16.unk0 == 0) {
                        self->ext.generic.unk84.S8.unk1 = 0;
                        self->ext.generic.unk80.modeS16.unk0 = 64;
                        self->step_s++;
                    }
                    break;

                case 3:
                    if (--self->ext.generic.unk80.modeS16.unk0 == 0) {
                        self->step_s++;
                    }
                    break;

                case 4:
                    if (AnimateEntity(D_80180760, self) == 0) {
                        SetStep(5);
                    }
                    if (D_80180668 != 0) {
                        if (GetDistanceToPlayerX() > 64) {
                            self->ext.generic.unk88.S16.unk0 = 13;
                            SetStep(15);
                        }
                    }
                    break;
            }
            break;

        case 14:
            if (self->step_s == 0) {
                if (Random() % 2) {
                    func_801A046C(0x879);
                } else {
                    func_801A046C(0x87A);
                }

                self->ext.generic.unk80.modeS16.unk0 = 32;
                D_80180660 = 0;
                if (GetSideToPlayer() & 1) {
                    self->accelerationX = 0x20000;
                } else {
                    self->accelerationX = -0x20000;
                }
                self->accelerationY = -0x20000;
                self->step_s++;
            }
            AnimateEntity(D_80180768, self);
            MoveEntity();
            self->accelerationX -= self->accelerationX >> 5;
            self->accelerationY -= self->accelerationY >> 5;
            self->accelerationY += 0x1000;
            if (--self->ext.generic.unk80.modeS16.unk0 == 0) {
                if (Random() % 2) {
                    self->ext.generic.unk88.S16.unk0 = 12;
                } else {
                    self->ext.generic.unk88.S16.unk0 = 11;
                }
                SetStep(16);
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
    posY = self->posY.i.hi + g_Camera.posY.i.hi;

    if (self->accelerationX < 0) {
        if (posX < 40) {
            self->posX.i.hi = 40 - g_Camera.posX.i.hi;
        }
    } else if (posX > 480) {
        self->posX.i.hi = 480 - g_Camera.posX.i.hi;
    }
    if ((self->accelerationY < 0) && (posY < 48)) {
        self->posY.i.hi = 48 - g_Camera.posY.i.hi;
    }
    // TODO: !FAKE
    hitbox = (s8*)&D_80180830[self->animCurFrame][D_801807F8];
    hitbox--;
    hitbox++;
    self->hitboxOffX = *hitbox++;
    self->hitboxOffY = *hitbox++;
    self->hitboxWidth = hitbox[0];
    self->hitboxHeight = hitbox[1];
}

const u32 rodataPadding = 0;

// Petal projectile shot by succubus ID 0x1A
void EntitySuccubusPetal(Entity* self) {
    Entity* newEntity;
    s32 temp_s2;
    s16 angle;

    if (D_80180664 & 2) {
        self->flags |= 0x100;
    }
    if (self->hitFlags & 0x80) {
        D_80180668 = 1;
    }

    if (self->flags & 0x100) {
        newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (newEntity != NULL) {
            CreateEntityFromEntity(E_EXPLOSION, self, newEntity);
            newEntity->params = 0;
        }
        DestroyEntity(self);
        return;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(D_801804DC);
        self->unk19 = 4;
        self->rotAngle = rand() & 0xFFF;
        temp_s2 = Random() & 3;
        if (temp_s2 >= 3) {
            temp_s2 = 0;
        }
        self->animCurFrame = temp_s2 + 64;

        angle = ((Random() & 0x1F) * 16) + 0xC0;
        if (self->facing == 0) {
            angle = 0x800 - angle;
        } else {
            angle = angle;
        }
        temp_s2 = ((rand() * 4) + 0x38000) >> 0xC;
        self->accelerationX = temp_s2 * rcos(angle);
        self->accelerationY = temp_s2 * rsin(angle);
        self->ext.generic.unk80.modeS16.unk0 = (Random() & 0x1F) + 0x10;

    case 1:
        self->accelerationX = self->accelerationX - (self->accelerationX >> 6);
        self->accelerationY = self->accelerationY - (self->accelerationY >> 6);
        MoveEntity();
        if (--self->ext.generic.unk80.modeS16.unk0 == 0) {
            self->ext.generic.unk80.modeS16.unk0 = (Random() & 0x1F) + 0x20;
            self->step++;
        }
        break;

    case 2:
        MoveEntity();
        self->rotAngle += self->ext.generic.unk80.modeS16.unk0;
        break;
    }
}

void EntityUnkId1B(Entity* entity) {
    if (entity->step == 0) {
        InitializeEntity(D_801804E8);
    }

    entity->posX.i.hi = entity[-1].posX.i.hi;
    entity->animCurFrame = 0;
    entity->posY.i.hi = entity[-1].posY.i.hi;
    entity->facing = entity[-1].facing;

    if (entity[-1].animCurFrame == 0x32) {
        entity->animCurFrame = 0x3E;
    }

    if (entity[-1].animCurFrame == 0x33) {
        entity->animCurFrame = 0x3F;
    }

    entity->zPriority = PLAYER.zPriority + 4;
}