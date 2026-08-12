// SPDX-License-Identifier: AGPL-3.0-or-later
#include "stage_02.h"
#include "inc_asm.h"
#include "sattypes.h"

// Alchemy Laboratory

// EntityBreakable (candles)
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60DC040, func_060DC040);

// SAT: func_060DC460
// bust with red eyes that can have a candle on it
void EntityRedEyeBust(Entity* self) {
    SpriteObject* result;
    switch (self->step) {
    case 0:
        TekiInit(self, 3);
        result = CreateSpriteObject(
            (u16)entityRedEyeBustData.allocationIndex,
            entityRedEyeBustData.flags, entityRedEyeBustData.images, 1);
        self->unk0 = result;
        func_0600AFA8(result, entityRedEyeBustData2[7]);
        result->zPriority = 0x70;
        result->posX = *(u32*)(&self->posX);
        result->posY = *(u32*)(&self->posY);
        self->step++;
        break;
    case 1:
        break;
    case 2:
        break;
    }
}

void func_060DC4EC(Entity* self) {
    if (self->step == 0) {
        DestroyEntity(self);
    }
}

INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60DC510, func_060DC510);
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60DC7B4, func_060DC7B4);
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60DCA54, func_060DCA54);
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60DCCD4, func_060DCCD4);
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60DCFA4, func_060DCFA4);

// EntityCannonLever
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60DD20C, func_060DD20C);

// EntityCannon
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60DD3E8, func_060DD3E8);

// EntityCannonShot
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60DD690, func_060DD690);

// EntityCannonWall
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60DD790, func_060DD790);

INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60DD8D8, func_060DD8D8);
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60DDB80, func_060DDB80);

// SAT: func_060DDE40
// table with globe on it that can be broken
void EntityTableWithGlobe(Entity* self) {
    switch (self->step) {
    case 0:
        TekiInit(self, 5);
        self->step++;
        self->unk0 = CreateSpriteObject(
            g_Stage02TableWithGlobeResource.allocationIndex,
            g_Stage02TableWithGlobeResource.flags,
            g_Stage02TableWithGlobeResource.images, 7);
        self->unk0->zPriority = 0x6A;
        self->hitboxWidth = 10;
        self->hitboxHeight = 12;
        self->hitboxOffX = 0;
        self->hitboxOffY = -0xA;
        self->hitboxState = 2;
    case 1:
        AnimateEntityWithSpriteData(self, g_Stage02TableWithGlobeIdleAnim,
                                    g_Stage02TableWithGlobeFrames);
        if (self->hitFlags != 0) {
            PlaySfxPositional(0x61D); // sotn-lint-ignore
            self->hitboxState = 0;
            CreateEntityFromEntity(E_HEART_DROP, self, &self[1]);
            self[1].params = g_Stage02TableWithGlobeDropParams[self->params];
            SetStep(2);
        }
        break;

    case 2:
        AnimateEntityWithSpriteData(self, g_Stage02TableWithGlobeBreakAnim,
                                    g_Stage02TableWithGlobeFrames);
        break;
    }
    SyncSpriteObjectPos(self);
}

INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60DDF64, func_060DDF64);
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60DE178, func_060DE178);

// SAT func_060DE2B0
void CreateExplosionPuff() {
    Entity* entity;
    s8 temp_s4 = Random() & 3;
    s16 temp_s3 = ((Random() & 0xF) << 8) - 0x800;
    s32 i;

    for (i = 0; i < 6; i++) {
        entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (entity != NULL) {
            CreateEntityFromEntity(E_FIRE, g_CurrentEntity, entity);
            entity->params = 2;
            entity->ext.opaquePuff.unk89 = 6 - i;
            entity->ext.opaquePuff.unk84 = temp_s3;
            entity->ext.opaquePuff.unk88 = temp_s4;
        }
    }
}

INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60DE348, func_060DE348);
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60DE6CC, func_060DE6CC);
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60DE970, func_060DE970);

// EntitySubWeaponContainer
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60DEE20, func_060DEE20);

INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60DF264, func_060DF264);
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60DF3B8, func_060DF3B8);
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60DF52C, func_060DF52C);
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60DF664, func_060DF664);
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60DF798, func_060DF798);
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60DFAE4, func_060DFAE4);
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60E0304, func_060E0304);
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60E0684, func_060E0684);
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60E08B0, func_060E08B0);
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60E08E4, func_060E08E4);
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60E093C, func_060E093C);
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60E0AF0, func_060E0AF0);
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60E0B24, func_060E0B24);
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60E0B7C, func_060E0B7C);
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60E0DC8, func_060E0DC8);
void f60E0F58() {}
void f60E0F64() {}
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60E0F70, func_060E0F70);
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60E1A00, func_060E1A00);
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60E1C08, func_060E1C08);
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60E1CA8, func_060E1CA8);
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60E1D48, func_060E1D48);

struct Unk {
    u8 pad[0x38];
    u16 unk_38;
    u16 unk_3a;
    u32 unk_3c;
};

extern struct Unk DAT_060e2014; // 060F5044h

// maybe func_801B797C?
void func_060e1ff8(s32 param_1) {
    DAT_060e2014.unk_3c = param_1;
    DAT_060e2014.unk_3a = 0;
    DAT_060e2014.unk_38 = 1;
}

INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60E2018, func_060E2018);
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60E21B8, func_060E21B8);
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60E22FC, func_060E22FC);
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60E2420, func_060E2420);
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60E2898, func_060E2898);
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60E29A4, func_060E29A4);

// EntityHeartDrop
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60E2A80, func_060E2A80);

INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60E32DC, func_060E32DC);
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60E37C8, func_060E37C8);
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60E3FBC, func_060E3FBC);
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60E42FC, func_060E42FC);
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60E43F4, func_060E43F4);
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60E4908, func_060E4908);

// SAT func_060E4F78
// PSX func_801BBC3C
// Different from PSX version but same idea
s32 func_801BBC3C(Entity* e) {
    s16 diff;

    diff = PLAYER.posX.i.hi - e->posX.i.hi;
    diff = ABS(diff);

    if (diff >= 23) {
        return 0;
    } else {
        diff = PLAYER.posY.i.hi - e->posY.i.hi;
        diff = ABS(diff);
        if (diff > 32) {
            return 0;
        }
    }

    return 1;
}

INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60E4FD0, func_060E4FD0);
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60E5388, func_060E5388);
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60E5410, func_060E5410);

// EntityExplosion
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60E5AE4, func_060E5AE4);

INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60E5C4C, func_060E5C4C);
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60E5DB4, func_060E5DB4);
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60E5EA0, func_060E5EA0);
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60E600C, func_060E600C);
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60E6140, func_060E6140);
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60E625C, func_060E625C);
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60E633C, func_060E633C);
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60E6628, func_060E6628);
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60E6B00, func_060E6B00);
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60E6C0C, func_060E6C0C);
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60E7014, func_060E7014);
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60E73CC, func_060E73CC);

typedef struct {
    s32 : 32;
    s8 unk4;
    s8 unk5;
} unkStruct;

typedef struct {
    s32 unk0;
    s32 unk4;
} unkStruct2;

typedef struct {
    u16 unk0;
    u16 unk2;
} unkStruct3;

extern unkStruct DAT_060485C0;
extern s32 DAT_0605C658;
extern s32 DAT_0605C668;
extern s8 DAT_0605DD60;
extern u16 DAT_0605DD94;
extern unkStruct2 DAT_06061DE0;
extern unkStruct3 DAT_06061DE8;
extern s32 DAT_060F5088[2];
extern s32 DAT_060F1D90;

void func_060E8780(s32, s32, s32, s32);
void func_060E8DE0(s32, s32, s32);
void func_060e8330(void);
void PlaySfx(s32);
void func_060E837C(Entity*, s32);
void TekiInit(Entity*, s32);
void DestroyEntity(Entity*);
void func_060E81D4(Entity*);
void func_060E8350(Entity*);

static inline SetGeomScreen(u32 h) {
    DAT_06061DE0.unk0 = DAT_06061DE0.unk4 = h;
}

static inline void SetGeomOffset(u16 ofx, u16 ofy) {
    DAT_06061DE8.unk0 = ofx;
    DAT_06061DE8.unk2 = ofy;
}

void func_060E7508(Entity* self) {
    s32 orig;
    s32 iVar6;
    s32 uVar13;
    Entity* player;
    s32 primIndex;

    player = &PLAYER;
    orig = DAT_060F5088[1];
    switch (self->step) {
    case 0:
        TekiInit(self, 5);
        self->step++;
        primIndex = AllocPrimitives(2, 0x3B);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->primIndex = primIndex;
        self->flags |= FLAG_HAS_PRIMS;
        DAT_060F1D90 = 0;
        func_060E837C(self, 0);
        self->ext.save.unk0 = 0;
        self->pad_B0 = NULL;
        self->ext.save.unk4 = 0;
        if (DAT_0605DD60 != 0) {
            DAT_0605C668 = 0;
            self->ext.save.unk4 = 0x28;
            self->ext.save.unk24 = 0x100;
            self->ext.save.unk0 = 7;
            DAT_0605DD60 = 0;
        }
        break;
    case 1:
        break;
    default:
        return;
    }

    SetGeomScreen(0x10000);
    SetGeomOffset(0xA0, self->ext.save.unk30 + 0x80);

    switch (self->ext.save.unk0) {
    case 0:
        DAT_060F5088[1] += 6;
        uVar13 = g_GameTimer & 0x7F;
        if (uVar13 == 0) {
            PlaySfx(SFX_SAVE_HEARTBEAT);
        }
        if (uVar13 & 0x40) {
            uVar13 = 0x7F - uVar13;
        }
        if (uVar13 >= 8) {
            uVar13 = 0xC0;
        } else {
            uVar13 = uVar13 * 4 + 0xA0;
        }
        func_060E8780(self->ext.save.unk8, 0, uVar13, 0);
        self->ext.save.unk24 = uVar13;
        if (func_060E82EC(0x78, 0xC8) != 0) {
            self->ext.save.unk28 = DAT_060485C0.unk4;
            self->ext.save.unk2C = DAT_060485C0.unk5;
            DAT_0605C668 = 0;
            if (DAT_060F1D90 == 0) {
                DAT_0605C658 = 0;
            }
            D_8013B5E8 = 0x10;
            g_Status.hp = g_Status.hpMax;
            g_Status.mp = g_Status.mpMax;
            self->ext.save.unk0++;
        }
        break;

    case 1:
        DAT_060F5088[1] += 7;
        if (self->ext.save.unk24 < 0xC0) {
            self->ext.save.unk24 += 4;
        }
        func_060E8780(self->ext.save.unk8, 0, self->ext.save.unk24, 0);
        if ((self->ext.save.unk30 < (g_CurrentRoom.stageID >> 1 & 0x10) + 8) &&
            (g_GameTimer != 0)) {
            self->ext.save.unk30++;
        }
        if (player->posX.i.hi < 0x9E) {
            g_Player.padSim = 0x8000;
            g_Player.demo_timer = 1;
        } else if (player->posX.i.hi > 0xA0) {
            g_Player.padSim = 0x4000;
            g_Player.demo_timer = 1;
        } else {
            if (self->ext.save.unk30 ==
                (g_CurrentRoom.stageID >> 1 & 0x10) + 8) {
                func_060e8330();
                self->ext.save.unk34 = 8;
                if ((DAT_060485C0.unk4 >= 0) && (DAT_060485C0.unk5 != 0)) {
                    func_060E8350(self);
                    self->ext.save.unk0 = 0x80;
                    if (DAT_060485C0.unk5 < 0) {
                        self->ext.save.unk2C = 0;
                        self->pad_B0 = 1;
                        self->ext.save.unk0 = 2;
                        self->ext.save.unk4 = 0xA;
                    }
                } else {
                    DAT_060485C0.unk4 = 0;
                    func_060E8350(self);
                    self->ext.save.unk0 = 0x81;
                }
            } else {
                func_060e8330();
            }
        }
        break;

    case 0x80:
        func_060e8330();
        DAT_060F5088[1] += self->ext.save.unk34;
        func_060E8780(self->ext.save.unk8, 0, self->ext.save.unk24, 0);
        if (func_06066B30(self, 3) != 0) {
            if (self->ext.save.unk1C == 0) {
                self->pad_B0 = 2;
                self->ext.save.unk0 = 2;
                self->ext.save.unk4 = 0x1E;
            } else {
                func_060E8350(self);
                self->ext.save.unk0++;
            }
        }
        break;

    case 0x81:
        func_060e8330();
        DAT_060F5088[1] += self->ext.save.unk34;
        func_060E8780(self->ext.save.unk8, 0, self->ext.save.unk24, 0);
        if (func_06066B30(self, 4) != 0) {
            if (self->ext.save.unk1C == 0) {
                DAT_060485C0.unk4 = 0;
                func_060E8350(self);
                self->ext.save.unk0 = 0x100;
            } else {
                DAT_060485C0.unk4 = self->ext.save.unk28;
                DAT_060485C0.unk5 = self->ext.save.unk2C;
                self->ext.save.unk0 = 0x101;
            }
        }
        break;

    case 0x100:
        func_060e8330();
        DAT_060F5088[1] += self->ext.save.unk34;
        func_060E8780(self->ext.save.unk8, 0, self->ext.save.unk24, 0);
        if (DAT_0605DD94 != 0) {
            iVar6 = func_06066B30(self, 1);
            if (iVar6 == 0) {
                break;
            }
            if (iVar6 == 2) {
                self->ext.save.unk0++;
                break;
            }
            self->pad_B0 = 1;
            self->ext.save.unk0 = 2;
            self->ext.save.unk4 = 0xA;
        } else {
            self->pad_B0 = 1;
            self->ext.save.unk0 = 2;
            self->ext.save.unk4 = 0xA;
        }
        break;

    case 0x101:
        DAT_060F5088[1] += self->ext.save.unk34;
        func_060E8780(self->ext.save.unk8, 0, self->ext.save.unk24, 0);
        if (g_pads[0].pressed & 0x700) {
            DAT_060485C0.unk4 = self->ext.save.unk28;
            DAT_060485C0.unk5 = self->ext.save.unk2C;
            g_Player.padSim = 0;
            g_Player.demo_timer = 1;
        } else {
            DAT_0605C668 = 1;
            DAT_0605C658 = 1;
            self->ext.save.unk0 = 0;
        }
        break;

    case 2:
        func_060e8330();
        DAT_060F5088[1] += self->ext.save.unk34;
        self->ext.save.unk24 += 4;
        if (self->ext.save.unk24 > 0x100) {
            self->ext.save.unk24 = 0x100;
        }
        func_060E8780(self->ext.save.unk8, 0, self->ext.save.unk24, 0);
        if (self->ext.save.unk24 == 0x100) {
            if ((0x1d < self->ext.save.unk4) || (DAT_060F1D90 != 0)) {
                self->ext.save.unk0++;
            } else {
                self->ext.save.unk34++;
                if (self->ext.save.unk34 > 0x80) {
                    self->ext.save.unk34 = 0x80;
                }
            }
        }
        break;

    case 3:
        func_060e8330();
        DAT_060F5088[1] += self->ext.save.unk34;
        self->ext.save.unk34++;
        if (self->ext.save.unk34 > 0x80) {
            self->ext.save.unk34 = 0x80;
        }
        func_060E8780(self->ext.save.unk8, 0, self->ext.save.unk24, 0);
        if (self->ext.save.unk34 == 0x80) {
            self->ext.save.unk0++;
            self->ext.save.unk20 = 0;
        }
        break;

    case 4:
        func_060e8330();
        DAT_060F5088[1] += self->ext.save.unk34;
        self->ext.save.unk20 += 2;
        if (self->ext.save.unk20 > 0x7F) {
            self->ext.save.unk20 = 0x7F;
        }
        func_060E8780(
            self->ext.save.unk8, 0, self->ext.save.unk24, self->ext.save.unk20);
        if (self->ext.save.unk20 >= 0x10) {
            uVar13 = (self->ext.save.unk20 - 0x10) * 0x10;
            if (uVar13 > 0x100) {
                uVar13 = 0x100;
            }
            func_060E8DE0(self->ext.save.unkC, uVar13, 0);
        }
        if (self->ext.save.unk20 != 0x7F) {
            break;
        }
        if (self->ext.save.unk4 > 0x27 || DAT_060F1D90 != 0) {
            if ((DAT_060F5088[1] & 0xFFF) >= 0x100 &&
                (DAT_060F5088[1] & 0xFFF) < 0x180) {
                self->ext.save.unk0++;
            }
        }
        break;

    case 5:
        func_060e8330();
        if (self->ext.save.unk34 > 0x40) {
            self->ext.save.unk34--;
        } else {
            if ((DAT_060F5088[1] & 0x7FF) >= 0x400) {
                self->ext.save.unk34 = (0x800 - (DAT_060F5088[1] & 0x7FF)) / 16;
            }
        }
        if (self->ext.save.unk34 < 0x10) {
            self->ext.save.unk34 = 0x10;
        }
        DAT_060F5088[1] += self->ext.save.unk34;
        self->ext.save.unk20 -= 2;
        if (self->ext.save.unk20 < 0) {
            self->ext.save.unk20 = 0;
        }
        func_060E8780(
            self->ext.save.unk8, 1, self->ext.save.unk24, self->ext.save.unk20);
        if (self->ext.save.unk20 != 0) {
            func_060E8DE0(self->ext.save.unkC, self->ext.save.unk24, 0);
        } else {
            func_060E8DE0(self->ext.save.unkC, 0, 0);
        }

        if ((self->ext.save.unk34 == 0x10) &&
            ((DAT_060F5088[1] & 0x7FF) >= 0x7F0)) {
            DAT_060F5088[1] = 0;
            func_060E8780(self->ext.save.unk8, 1, self->ext.save.unk24, 0);
            func_060E8350(self);
            self->ext.save.unk0++;
        }
        break;

    case 6:
        func_060e8330();
        if ((self->ext.save.unk4 > 0x27) && func_06066B30(self, 0)) {
            if (self->ext.save.unk4 == 0x2B) {
                func_060E8350(self);
                self->ext.save.unk0 = 0x200;
            } else if (self->ext.save.unk4 != 0x28) {
                self->ext.save.unk0 = 0x20;
                self->ext.save.unk20 = 0x60;
            } else {
                self->ext.save.unk0++;
            }
        }
        break;

    case 0x200:
        func_060e8330();
        if (func_06066B30(self, 2) != 0) {
            if (self->ext.save.unk1C == 0) {
                DAT_060485C0.unk5 = 0;
                PlaySfx(SFX_UI_CONFIRM);
                self->ext.save.unk0++;
            } else {
                self->ext.save.unk0 = 0x20;
                self->ext.save.unk20 = 0x60;
            }
        }
        break;

    case 0x201:
        func_060e8330();
        if (func_06030640(DAT_060485C0.unk4) == 0) {
            self->ext.save.unk0 = 0x30;
            self->ext.save.unk20 = 0x60;
        } else {
            self->ext.save.unk4 = 0x2A;
            func_060E8350(self);
            self->ext.save.unk0++;
        }
        break;

    case 0x202:
        func_060e8330();
        if (func_06066B30(self, 0) != 0) {
            self->ext.save.unk0 = 0x20;
            self->ext.save.unk20 = 0x60;
        }
        break;

    case 7:
        func_060e8330();
        func_060E8780(self->ext.save.unk8, 1, self->ext.save.unk24, 0);
        self->ext.save.unk0++;
        break;

    case 8:
        func_060e8330();
        DAT_060F5088[1] += self->ext.save.unk34;
        self->ext.save.unk34 += 2;
        if (self->ext.save.unk34 > 0x40) {
            self->ext.save.unk34 = 0x40;
        }
        func_060E8780(self->ext.save.unk8, 1, self->ext.save.unk24, 0);
        if (self->ext.save.unk34 == 0x40) {
            self->ext.save.unk0++;
            self->ext.save.unk20 = 0;
        }
        break;

    case 9:
        DAT_060F5088[1] += self->ext.save.unk34;
        self->ext.save.unk20++;
        if (self->ext.save.unk20 > 0x7F) {
            self->ext.save.unk20 = 0x7F;
        }
        func_060E8780(
            self->ext.save.unk8, 2, self->ext.save.unk24, self->ext.save.unk20);
        if (self->ext.save.unk20 >= 0x40) {
            func_060E8DE0(self->ext.save.unkC, self->ext.save.unk24, 0);
            DAT_0605C668 = 1;
            DAT_0605C658 = 1;
        } else {
            func_060E8DE0(self->ext.save.unkC, self->ext.save.unk24,
                          self->ext.save.unk20 * 2 + 0x80);
            func_060e8330();
        }
        if (self->ext.save.unk20 == 0x7F) {
            self->ext.save.unk0++;
            self->ext.save.unk20 = 0;
        }
        break;

    case 10:
        DAT_060F5088[1] += self->ext.save.unk34;
        self->ext.save.unk20++;
        if (self->ext.save.unk20 > 0x22) {
            self->ext.save.unk20 = 0x22;
        }
        func_060E8DE0(
            self->ext.save.unkC, self->ext.save.unk24, self->ext.save.unk20);
        if (self->ext.save.unk34 == 0) {
            self->ext.save.unk0++;
        }
        break;

    case 11:
        break;

    case 12:
        DAT_060F5088[1] = 0;
        self->ext.save.unk24 = 0x180;
        func_060E8780(self->ext.save.unk8, 1, self->ext.save.unk24, 0);
        self->ext.save.unk20 = 0;
        self->ext.save.unk0++;
        break;

    case 13:
        DAT_060F5088[1] += 9;
        func_060E8780(
            self->ext.save.unk8, 3, self->ext.save.unk24, self->ext.save.unk20);
        self->ext.save.unk20++;
        if (self->ext.save.unk20 == 0x60) {
            self->ext.save.unk0++;
        }
        break;

    case 14:
        DAT_060F5088[1] += 9;
        func_060E8780(
            self->ext.save.unk8, 3, self->ext.save.unk24, self->ext.save.unk20);
        self->ext.save.unk20--;
        if (self->ext.save.unk20 == 0) {
            self->ext.save.unk0--;
        }
        break;

    case 0x20:
    case 0x30:
        if (self->ext.save.unk0 == 0x30) {
            func_060e8330();
        }
        if (self->ext.save.unk20 > 0x30) {
            func_060e8330();
        }
        DAT_060F5088[1] += 6;
        if (self->ext.save.unk24 > 0xC0) {
            self->ext.save.unk24 -= 2;
        }
        func_060E8780(
            self->ext.save.unk8, 3, self->ext.save.unk24, self->ext.save.unk20);
        self->ext.save.unk20 -= 2;
        if ((g_Player.demo_timer == 0) && (g_pads[0].pressed & 0x700)) {
            g_Player.padSim = 0;
            g_Player.demo_timer = 1;
            if (self->ext.save.unk20 < 1) {
                self->ext.save.unk20 = 0;
            }
        } else if (self->ext.save.unk20 < 1) {
            if (self->ext.save.unk0 == 0x30) {
                self->pad_B0 = NULL;
                self->ext.save.unk4 = 0;
                self->ext.save.unk0 = 1;
            } else {
                DAT_060485C0.unk4 = self->ext.save.unk28;
                DAT_060485C0.unk5 = self->ext.save.unk2C;
                self->pad_B0 = NULL;
                self->ext.save.unk4 = 0;
                self->ext.save.unk0 = 0;
                DAT_0605C668 = 1;
                DAT_0605C658 = 1;
            }
        }
        break;

    default:
        func_060E8780(self->ext.save.unk8, 1, self->ext.save.unk24, 0);
        break;
    }

    if (((orig + 0x400) ^ (DAT_060F5088[1] + 0x400)) & 0x800) {
        if (self->ext.save.unk0 >= 3 && self->ext.save.unk0 < 10) {
            PlaySfx(SFX_SAVE_COFFIN_SWISH);
        }
    }
    func_060E81D4(self);
}

INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60E81D4, func_060E81D4);
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60E82EC, func_060E82EC);

// not seeing an obvious PSX equivalent
void func_060e8330(void) {
    g_Player.padSim = PAD_UP;
    g_Player.demo_timer = 1;
}

// not clear if this is Entity or not
struct Unk10 {
    u8 pad[0x88];
    u32* unk88;
};

void func_060E8350(Entity* self) {
    UnkStruct_060e8350* iVar1 = ((struct Unk10*)self)->unk88;
    s32 i;

    for (i = 0; i < 9; i++) {
        iVar1->unk18 = 0;
        iVar1->unk1E = 8;
        iVar1 = iVar1->unk20;
    }
}

INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60E837C, func_060E837C);

void func_060E87D0(s32, s32);
void func_060E8990(s32, s32, s32);
void func_060E8ADC(s32, s32, s32);

void func_060E8780(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    func_060E87D0(arg1, arg3);
    func_060E8990(arg1, arg2, arg3);
    func_060E8ADC(arg0, arg1, arg3);
}

INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60E87D0, func_060E87D0);
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60E8990, func_060E8990);
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60E8ADC, func_060E8ADC);

void func_060E8E1C(s32, s32);
void func_060E8EEC(s32, s32, s32);

void func_060E8DE0(s32 arg0, s32 arg1, s32 arg2) {
    func_060E8E1C(arg1, arg2);
    func_060E8EEC(arg0, arg1, arg2);
}

INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60E8E1C, func_060E8E1C);
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60E8EEC, func_060E8EEC);
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60E9058, func_060E9058);
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60E9220, func_060E9220);

void func_060E9270(Entity* self) {
    SyncSpriteObjectPos(self);
    func_0600B004(self->unk0, g_Stage02Entity38Frames[self->animCurFrame]);
}

// dupe of func_060e97c4
void func_060E92A8(u16** param_1) {

    if (*(u16*)(param_1 + 6) != 0) {
        **param_1 = **param_1 | 0x10;

    } else {
        **param_1 = **param_1 & 0xffef;
    }
}

// not sure what these are
const u16 pad_060e92d4 = 0xAAAA;
const u16 pad_060e92d6 = 0xAAAB;

// EntityBloodSkeleton
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60E92D8, func_060E92D8);

INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60E9770, func_060E9770);

// seems to saturn-only. param_1 is probably a struct?
void func_060e97c4(u16** param_1) {

    if (*(u16*)(param_1 + 6) != 0) {
        **param_1 = **param_1 | 0x10;

    } else {
        **param_1 = **param_1 & 0xffef;
    }
}

void func_060E97F0(Entity* self) {
    SyncSpriteObjectPos(self);
    func_0600B004(self->unk0, g_Stage02BoneScimitarFrames[self->animCurFrame]);
}

// EntityBoneScimitar
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60E9828, func_060E9828);

INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60EA058, func_060EA058);
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60EA1E0, func_060EA1E0);

// dupe of func_060e97c4
void func_060EA234(u16** param_1) {
    if (*(u16*)(param_1 + 6) != 0) {
        **param_1 = **param_1 | 0x10;
    } else {
        **param_1 = **param_1 & 0xffef;
    }
}

// not sure what these are
const u16 pad_060EA260 = 0xCCCC;
const u16 pad_060EA262 = 0xCCCD;

// EntityAxeKnight
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60EA264, func_060EA264);

// EntityAxeKnightThrowingAxe
// SAT: func_060EAC54
void EntityAxeKnightRotateAxe(Entity* self) {
    self->unk0->flags |= FLAG_UNK_40;

    if (self->params != 0) {
        self->unk0->rotate += 0x80;
    } else {
        self->unk0->rotate -= 0x80;
    }
    if (self->params != 0) {
        self->rotate += 0x80;
    } else {
        self->rotate -= 0x80;
    }

    self->rotate &= 0xFFF;
}

INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60EACC0, func_060EACC0);

INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60EAF2C, func_060EAF2C);

// EntityBloodyZombie
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60EAFAC, func_060EAFAC);

INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60EB5C4, func_060EB5C4);
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60EB6E4, func_060EB6E4);
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60EB8D0, func_060EB8D0);
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60EB950, func_060EB950);

// EntitySkeleton
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60EB9EC, func_060EB9EC);

INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60EBEB0, func_060EBEB0);
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60EC030, func_060EC030);
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60EC1F0, func_060EC1F0);

void func_060EC240(Entity* self) {
    SyncSpriteObjectPos(self);
    func_0600B004(self->unk0, g_Stage02SpittleBoneFrames[self->animCurFrame]);
}

// EntitySpittleBone
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60EC278, func_060EC278);

INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60EC730, func_060EC730);
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60EC888, func_060EC888);
