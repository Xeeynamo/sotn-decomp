#include "common.h"
#include "dra.h"

extern s16 D_80180A94[];
extern ObjectInit *D_80193AB0;
extern ObjectInit *D_80193AB4;

INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", func_80186FD0);

INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", func_801870B0);

INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", func_8018726C);

INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", func_801873A0);

INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", func_80187F1C);

u32 func_801881E8(void) {
    D_800978B8 = (D_800978B8 * 0x01010101) + 1;
    return D_800978B8 >> 0x18;
}

INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", func_80188218);

INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", func_80188514);

INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", func_8018861C);

INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", func_80189734);

INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", func_80189DD8);

INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", func_80189E9C);

INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", func_80189FB4);

void func_8018A0CC(s32 arg0) {
    s32 a1 = 0xFFFE;
    arg0 = (s16)arg0;
loop_1:
    if (D_80193AB0->posX == a1 || D_80193AB0->posX < arg0) {
        D_80193AB0++;
        goto loop_1;
    }
}

void func_8018A118(s32 arg0) {
    s32 a2, a3;
    a3 = 0xFFFF;
    arg0 = (s16)arg0;
    a2 = 0xFFFE;
loop_1:
    if (D_80193AB0->posX == a3 || (arg0 < D_80193AB0->posX) && (D_80193AB0->posX != a2)) {
        D_80193AB0--;
        goto loop_1;
    }
}

INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", func_8018A170);

INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", func_8018A26C);

void func_8018A380(s32 arg0) {
    s32 a1 = 0xFFFE;
    arg0 = (s16)arg0;
loop_1:
    if (D_80193AB4->posY == a1 || D_80193AB4->posY < arg0) {
        D_80193AB4++;
        goto loop_1;
    }
}

void func_8018A3CC(s32 arg0) {
    while (true)
    {
        if (D_80193AB4->posY == 0xFFFF)
            D_80193AB4--;
        else if ((s16)arg0 >= D_80193AB4->posY || D_80193AB4->posY == 0xFFFE)
            break;
        else
            D_80193AB4--;
    }
}

INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", func_8018A424);

INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", func_8018A520);

INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", func_8018A634);

INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", func_8018A7AC);

INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", func_8018A860);

INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", func_8018A8D4);

INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", func_8018A950);

INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", func_8018A9C8);

void DestroyEntity(Entity* item) {
    int i, length;
    u32* ptr;

    if (item->unk34 & 0x800000) {
        D_8003C7B4(item->unk64);
    }

    ptr = item;
    length = sizeof(Entity) / sizeof(s32);
    for (i = 0; i < length; i++)
        *ptr++ = 0;
}

INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", func_8018B66C);

INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", func_8018B6E8);

INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", func_8018B730);

INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", func_8018B7E8);

s16 func_8018B900(void) {
    s16 value = D_8006C3B8->posX.Data.high - D_800733DA;
    if (value < 0) {
        value = -value;
    }
    return value;
}

s32 func_8018B93C(void) {
    s32 value = D_8006C3B8->posY.Data.high - D_800733DE;
    if (value < 0) {
        value = -value;
    }
    return value;
}

INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", func_8018B970);

void func_8018B9B4(void) {
    D_8006C3B8->posX.value = D_8006C3B8->posX.value + D_8006C3B8->accelerationX;
    D_8006C3B8->posY.value = D_8006C3B8->posY.value + D_8006C3B8->accelerationY;
}

void func_8018B9E4(void) {
    if (D_8006C3B8->accelerationY <= 0x5FFFF) {
        D_8006C3B8->accelerationY = D_8006C3B8->accelerationY + 0x4000;
    }
}

INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", func_8018BA10);

INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", func_8018BC88);

INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", func_8018BE70);

#ifndef NON_MATCHING
INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", func_8018BED0);
#else
s32 func_8018BED0(s32 arg0, s16 arg1) {
    return D_80180A94[arg0 & 0xFF] * arg1;
}
#endif

#ifndef NON_MATCHING
INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", func_8018BEFC);
#else
s16 func_8018BEFC(s32 arg0) {
    return D_80180A94[arg0 & 0xFF];
}
#endif

INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", func_8018BF18);

u8 func_8018BF84(s16 x, s16 y) {
    return ((func_800190AC(y, x) >> 4) + 0x40);
}

u8 func_8018BFBC(Entity* a, Entity* b) {
    s32 diffX = (u16)b->posX.Data.high - (u16)a->posX.Data.high;
    s32 diffY = (u16)b->posY.Data.high - (u16)a->posY.Data.high;
    return func_8018BF84(diffX, diffY);
}

u8 func_8018C004(s32 x, s32 y) {
    s32 diffX = x - (u16)D_8006C3B8->posX.Data.high;
    s32 diffY = y - (u16)D_8006C3B8->posY.Data.high;
    return func_8018BF84(diffX, diffY);
}

INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", func_8018C04C);

INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", func_8018C0A4);

u16 func_8018C130(s16 x, s16 y) {
    return func_800190AC(y, x);
}

u16 func_8018C160(Entity* a, Entity* b) {
    s32 diffX = b->posX.Data.high - a->posX.Data.high;
    s32 diffY = b->posY.Data.high - a->posY.Data.high;
    return func_800190AC(diffY, diffX);
}

u16 func_8018C198(s32 x, s32 y) {
    s16 diffX = x - (u16)D_8006C3B8->posX.Data.high;
    s16 diffY = y - (u16)D_8006C3B8->posY.Data.high;
    return func_800190AC(diffY, diffX);
}

INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", func_8018C1E0);

void func_8018C240(s32 arg0) {
    D_8006C3B8->unk2C = (s16) (arg0 & 0xFF);
    D_8006C3B8->unk2E = 0;
    D_8006C3B8->animationFrameIndex = 0;
    D_8006C3B8->animationFrameDuration = 0;
}

void func_8018C260(s32 arg0) {
    D_8006C3B8->unk2E = (s16) (arg0 & 0xFF);
    D_8006C3B8->animationFrameIndex = 0;
    D_8006C3B8->animationFrameDuration = 0;
}

INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", func_8018C27C);

void func_8018C310(u16 *arg0) {
    u16 temp_v1;
    Unkstruct5 *temp_v0;

    D_8006C3B8->animationSet = *arg0++;
    D_8006C3B8->animationFrame = *arg0++;
    D_8006C3B8->unk5A = *arg0++;
    D_8006C3B8->palette = *arg0++;
    temp_v1 = *arg0++;
    D_8006C3B8->unk3A = temp_v1;
    temp_v0 = temp_v1 * sizeof(Unkstruct5) + (u32)D_8003C808;
    D_8006C3B8->unk3E = temp_v0->unk4;
    D_8006C3B8->unk40 = temp_v0->unk6;
    D_8006C3B8->unk42 = temp_v0->unk8;
    D_8006C3B8->unk3C = temp_v0->unkC;
    D_8006C3B8->hitboxWidth = temp_v0->hitboxWidth;
    D_8006C3B8->hitboxHeight = temp_v0->hitboxHeight;
    D_8006C3B8->unk34 = temp_v0->unk24;
    D_8006C3B8->unk10 = 0;
    D_8006C3B8->unk12 = 0;
    D_8006C3B8->unk2E = 0;
    D_8006C3B8->unk2C++;
    if (D_8006C3B8->zPriority == 0) {
        D_8006C3B8->zPriority = D_80097408 - 0xC;
    }
}

void func_8018C40C(Entity* arg0) {
    if (arg0->unk2C == 0) {
        arg0->unk2C++;
    }
}

INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", func_8018C434);

INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", func_8018C55C);

INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", func_8018C6B4);

INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", func_8018C9F8);

INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", func_8018CAB0);

INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", func_8018CB34);

INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", func_8018CC90);

INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", func_8018CD10);

INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", func_8018CDEC);

INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", func_8018CF04);

void func_8018CFA8(void) {
    D_8003C7DC(0x67A);
    D_8003C848(5, 0x8000);
    DestroyEntity(D_8006C3B8);
}

void func_8018CFF8(void) {
    DestroyEntity(D_8006C3B8);
}

INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", func_8018D020);

INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", func_8018D894);

INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", func_8018D990);

INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", func_8018DA34);

INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", func_8018E01C);

INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", func_8018E2CC);

INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", func_8018ED9C);

INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", func_8018EEC4);

INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", func_8018F420);

INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", func_8018F510);

INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", func_8018F620);

INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", func_8018F750);

INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", func_8018F838);

INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", func_8018F928);

INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", func_8018FA1C);

INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", func_8018FC4C);

INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", func_8018FD48);

INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", func_801902C8);

INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", func_801903C8);

INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", func_80190494);

INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", func_8019055C);

INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", func_80190614);

INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", func_801907EC);

INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", func_80190DCC);

INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", func_801914CC);

INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", func_801916C4);

INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", func_801917BC);

INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", func_8019198C);

INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", func_80192610);

INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", func_801929A4);

INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", func_80192E54);

INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", func_80192F40);

INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", func_80193270);

INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", func_80193658);

INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", func_801937A8);

INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", func_801937D8);

INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", func_80193854);

void func_801938DC(Unkstruct7* arg0) {
    arg0->unk13 = 0;
    arg0->unk1F = 0;
    arg0->unk2B = 0;
    ((Unkstruct6*)arg0->tag)->unk14 = 0;
    ((Unkstruct6*)arg0->tag)->unk16 = 0;
    ((Unkstruct6*)arg0->tag)->unkA = 0;
    ((Unkstruct6*)arg0->tag)->unk8 = 0;
    ((Unkstruct6*)arg0->tag)->unkE = 0;
    ((Unkstruct6*)arg0->tag)->unkC = 0;
    ((Unkstruct6*)arg0->tag)->unk12 = 0;
    ((Unkstruct6*)arg0->tag)->unk10 = 0;
    ((Unkstruct6*)arg0->tag)->unk18 = 0;
    ((Unkstruct6*)arg0->tag)->unk1A = 0;
    ((Unkstruct6*)arg0->tag)->unk1C = 0;
    ((Unkstruct6*)arg0->tag)->unk1E = 0;
    ((Unkstruct6*)arg0->tag)->unk24 = 0;
    ((Unkstruct6*)arg0->tag)->unk25 = 0;
    ((Unkstruct6*)arg0->tag)->unk28 = 0;
    ((Unkstruct6*)arg0->tag)->unk2A = 0;
    ((Unkstruct6*)arg0->tag)->unk20 = 0;
    ((Unkstruct6*)arg0->tag)->unk22 = 0;
}

void func_801939BC(Unkstruct7* arg0) {
    func_801938DC(arg0);
    arg0->unk2B = 8;
    ((Unkstruct6*)arg0->tag)->unk2B = 1;
    ((Unkstruct6*)arg0->tag)->unk7 = 2;
    ((Unkstruct6*)arg0->tag)->unk32 = 0xA;
}

void func_80193A10(Unkstruct6* arg0) {
    arg0->unk2B = 0;
    arg0->unk32 = 8;
    ((Unkstruct6*)arg0->tag)->unk2B = 0;
    ((POLY_GT4*)arg0->tag)->code = 4;
    ((POLY_GT4*)arg0->tag)->pad3 = 8;
}

INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", func_80193A3C);
