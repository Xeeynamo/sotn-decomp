#include "stage_02.h"
#include "inc_asm.h"
#include "sattypes.h"

// Alchemy Laboratory

INCLUDE_ASM("asm/saturn/stage_02/data", d60DC000, d_060DC000);

// EntityBreakable (candles)
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60DC040, func_060DC040);

// SAT: func_060DC460
// bust with red eyes that can have a candle on it
REDACTED
    struct Unk0600B344* result;
    switch (self->step) {
    case 0:
        func_0607B264(self, 3);
        result =
            func_0600B344(entityRedEyeBustData.unk8, entityRedEyeBustData.unk10,
                          entityRedEyeBustData.unk0, 1);
        self->unk0 = result;
        func_0600AFA8(result, entityRedEyeBustData2.unk28);
        result->zPriority = 0x70;
        result->unk14 = *(u32*)(&self->posX);
        result->unk18 = *(u32*)(&self->posY);
        self->step++;
        break;
    case 1:
        break;
    case 2:
        break;
    }
}

REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60DC510, func_060DC510);
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60DC7B4, func_060DC7B4);
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60DCA54, func_060DCA54);
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60DCCD4, func_060DCCD4);
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60DCFA4, func_060DCFA4);
REDACTED
REDACTED
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60DD20C, func_060DD20C);
REDACTED
REDACTED
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60DD3E8, func_060DD3E8);
REDACTED
REDACTED
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60DD690, func_060DD690);
REDACTED
REDACTED
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60DD790, func_060DD790);
REDACTED
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60DD8D8, func_060DD8D8);
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60DDB80, func_060DDB80);

// SAT: func_060DDE40
// table with globe on it that can be broken
REDACTED
    switch (self->step) {
    case 0:
        func_0607B264(self, 5);
        self->step++;
REDACTED
            D_060ED26C.unk8, D_060ED26C.unk10, D_060ED26C.unk0, 7);
REDACTED
        self->hitboxWidth = 10;
        self->hitboxHeight = 12;
        self->hitboxOffX = 0;
        self->hitboxOffY = -0xA;
        self->hitboxState = 2;
    case 1:
        AnimateEntity(self, D_80180EF8, D_80180EF0);
        if (self->hitFlags != 0) {
            func_801C29B0(0x61D);
            self->hitboxState = 0;
            CreateEntityFromEntity(E_HEART_DROP, self, &self[1]);
REDACTED
            SetStep(2);
        }
        break;

    case 2:
        AnimateEntity(self, dat_060ed174, D_80180EF0);
        break;
    }
    func_06079BB4(self);
}

INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60DDF64, func_060DDF64);
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60DE178, func_060DE178);
REDACTED
REDACTED
void AxeKnightDeath(void) {
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60DE348, func_060DE348);
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60DE6CC, func_060DE6CC);
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60DE970, func_060DE970);
REDACTED
REDACTED
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60DEE20, func_060DEE20);
REDACTED
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
INCLUDE_ASM("asm/saturn/stage_02/data", d60E2A80, d_060E2A80);

INCLUDE_ASM("asm/saturn/stage_02/data", d60E32DC, d_060E32DC);
INCLUDE_ASM("asm/saturn/stage_02/data", d60E47A4, d_060E47A4);
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60E4908, func_060E4908);

// SAT func_060E4F78
// PSX func_801BBC3C
// Different from PSX version but same idea
s32 func_801BBC3C(Entity* e) {
    s16 diff;

REDACTED
    diff = ABS(diff);

    if (diff >= 23) {
        return 0;
    } else {
REDACTED
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
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60E7508, func_060E7508);
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60E81D4, func_060E81D4);
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60E82EC, func_060E82EC);

s32 arr_0605C140[];

// not seeing an obvious PSX equivalent
void func_060e8330(void) {
    arr_0605C140[0xEF] = 0x1000;
    arr_0605C140[0xF1] = 1;
}

REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60E837C, func_060E837C);

void func_060E87D0(s32, s32);
void func_060E8990(s32, s32, s32);
void func_060E8ADC(s32, s32, s32);

void func_060E8780(s32 param_1, s32 param_2, s32 param_3, s32 param_4) {
    func_060E87D0(param_2, param_4);
    func_060E8990(param_2, param_3, param_4);
    func_060E8ADC(param_1, param_2, param_4);
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
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED

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

REDACTED
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60E92D8, func_060E92D8);
REDACTED
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60E9770, func_060E9770);

// seems to saturn-only. param_1 is probably a struct?
void func_060e97c4(u16** param_1) {

    if (*(u16*)(param_1 + 6) != 0) {
        **param_1 = **param_1 | 0x10;

    } else {
        **param_1 = **param_1 & 0xffef;
    }
}

REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60E9828, func_060E9828);
REDACTED
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
    self->unk0->unk0 |= 0x40;

    if (self->params != 0) {
        self->unk0->unk8 += 0x80;
    } else {
        self->unk0->unk8 -= 0x80;
    }
    if (self->params != 0) {
        self->rotZ += 0x80;
    } else {
        self->rotZ -= 0x80;
    }

    self->rotZ &= 0xFFF;
}

INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60EACC0, func_060EACC0);

INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60EAF2C, func_060EAF2C);
REDACTED
REDACTED
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60EAFAC, func_060EAFAC);
REDACTED
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60EB5C4, func_060EB5C4);
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60EB6E4, func_060EB6E4);
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60EB8D0, func_060EB8D0);
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60EB950, func_060EB950);
REDACTED
REDACTED
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60EB9EC, func_060EB9EC);
REDACTED
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60EBEB0, func_060EBEB0);
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60EC030, func_060EC030);
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60EC1F0, func_060EC1F0);
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60EC278, func_060EC278);
REDACTED
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60EC730, func_060EC730);
INCLUDE_ASM("asm/saturn/stage_02/data", d60ECA94, d_060ECA94);
INCLUDE_ASM("asm/saturn/stage_02/data", d60ECC50, d_060ECC50);
