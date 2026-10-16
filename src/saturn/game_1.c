// SPDX-License-Identifier: AGPL-3.0-or-later
#include "inc_asm.h"
#include "sattypes.h"
#include "game.h"
#include "lib/spr/spr.h"
#include <saturn_sprite.h>

char* DAT_0607C0F0[] = {
    "本体ＲＡＭ",
    "カートリッジＲＡＭ",
};

char* DAT_0607C0F8[] = {
    "はい",
    "いいえ",
};

char* DAT_0607C100 = "バックアップＲＡＭを\x01選んで下さい。";

char* DAT_0607C104 = "の全ての記録を";

char* DAT_0607C108 = "消します。（初期化します）\x01　　　　よろしいですか？";

char* DAT_0607C10C = "　　　記録の更新をしますか？";

char* DAT_0607C110 = "　　　　セーブしますか？";

char* DAT_0607C114 = "セーブしました。";

char* DAT_0607C118 = "　データが５つ全てセーブされて　\x01　います。";

char* DAT_0607C11C = "の全ての記録を";

char* DAT_0607C120 =
    "消すことができませんでした。\x01（初期化できませんでした）";

char* DAT_0607C124 = "のバックアップ";

char* DAT_0607C128 = "の準備がまだできていません。\x01（初期化されていません）";

char* DAT_0607C12C =
    "このゲームの記録をセーブするため\x01には７０の空き容量が必要です。";

char* DAT_0607C130 = "記録を正しくセーブすることができ\x01ませんでした。";

s32 func_06066B30(Entity* self, s32 arg1) {
    s32 ret;

    if (arg1 == 0) {
        ret = func_06066CE0(self);
    } else if (arg1 == 1) {
        ret = func_06067090(self);
    } else {
        ret = func_060674B8(self, arg1);
    }
    return ret;
}

static u16 LookupTblNoToVram(u16 arg0) {
    if (arg0 & 0x4000) {
        return LocalLookupTblNoToVram(arg0 & 0xFFF);
    } else {
        return SPR_2LookupTblNoToVram(arg0 & 0xFFF);
    }
}

void func_06066B74(Primitive* prim0, Primitive* prim1, Primitive* prim2) {
    prim0->type = 0x1000;
    prim0->unk4 = 0x488;
    prim0->unk8 = DAT_0605aec0[1][0];
    prim0->unkA = 0x1840;
    prim0->unk6 =
        LookupTblNoToVram(g_SaturnSharedSpriteBank12Resource.flags + 1);
    prim0->unk4 = prim0->unk4 & 0xFFC7;
    prim0->unk6 = prim0->unk6 & 0x8FFF | 0x4000;
    prim0->priority = 0x1C0;
    prim0->drawMode = DRAW_HIDE;

    prim1->type = 0x1004;
    prim1->unk4 = 0x4C0;
    prim1->unk6 =
        1 + LookupTblNoToVram(g_SaturnSharedSpriteBank13Resource.flags + 3);
    prim1->unk6 = prim1->unk6 & 0x8FFF | 0x4000;
    prim1->priority = 0x1BE;
    prim1->drawMode = DRAW_HIDE;

    prim2->type = 0x1005;
    prim2->unk4 = 0x4C0;
    prim2->unk6 =
        LookupTblNoToVram(g_SaturnSharedSpriteBank13Resource.flags + 3);
    prim2->unk6 = prim2->unk6 & 0x8FFF | 0x4000;
    prim2->priority = 0x1BF;
    prim2->drawMode = DRAW_HIDE;
}

void PlaySfx(s32 sfxId);
void func_06067958(void);
void func_0606797C(char*, s16*, s32);
void func_06067A04(void);

s32 func_06066CE0(Entity* self) {
    Primitive* prim0;
    Primitive* prim1;
    Primitive* prim2;
    s16 sp[2];

    s32 temp;
    s32 temp2;
    s32 temp3;

    prim0 = self->ext.save.unk10;
    prim1 = self->ext.save.unk14;
    prim2 = self->ext.save.unk18;
    temp = prim0->x3;
    if (temp == 0) {
        if (self->ext.save.unk4 == 0x28) {
            PlaySfx(SFX_START_SLAM_B);
        } else {
            PlaySfx(SFX_UI_ALERT_TINK);
        }
        func_06067958();
        sp[0] = 0;
        sp[1] = 0;
        func_06066B74(prim0, prim1, prim2);
        prim0->x0 = 0x40;
        prim1->x0 = prim1->x3 = 0x3A;
        prim1->x1 = prim1->x2 = 0x106;
        prim2->x0 = prim2->x3 = 0x3A;
        prim2->x1 = prim2->x2 = 0x106;
        switch (self->ext.save.unk4) {
        case 0x28:
            func_0606797C(DAT_0607C114, sp, 0);
            prim0->x0 = 0x70;
            prim2->x0 = prim2->x3 = prim1->x0 = prim1->x3 = 0x6A;
            prim2->x1 = prim2->x2 = prim1->x1 = prim1->x2 = 0xD6;
            prim0->x3 += 2;
            break;
        case 0x29:
            func_0606797C(DAT_0607C118, sp, 0);
            prim0->x3 += 2;
            break;
        case 0x2A:
            func_0606797C(DAT_0607C0F0[1], sp, 0);
            func_0606797C(DAT_0607C11C, sp, 0);
            sp[0] = 0;
            sp[1] += 0x10;
            func_0606797C(DAT_0607C120, sp, 0);
            prim0->x3 += 2;
            break;
        case 0x2B:
            func_0606797C(DAT_0607C0F0[1], sp, 0);
            func_0606797C(DAT_0607C124, sp, 0);
            sp[0] = 0;
            sp[1] += 0x10;
            func_0606797C(DAT_0607C128, sp, 0);
            prim0->x3 += 2;
            break;
        case 0x2C:
            func_0606797C(DAT_0607C12C, sp, 0);
            prim0->x3 += 2;
            break;
        default:
        case 0x2D:
            func_0606797C(DAT_0607C130, sp, 0);
            prim0->x3 += 2;
            break;
        }

        func_06067A04();
        temp3 = sp[1] + 0x10;
        self->ext.save.unk1E = temp3;
        temp3 += 0x40;
        prim0->y0 = temp3;
        prim2->y0 = prim2->y1 = prim1->y0 = prim1->y1 = temp3 - 3;
        prim2->y2 = prim2->y3 = prim1->y2 = prim1->y3 = temp3 + 3;
    } else {
        temp2 = self->ext.save.unk1E;
        if (temp <= temp2) {
            temp2 += 0x40;
            prim0->y0 = temp2 - temp;
            prim0->unkA = temp | 0x1800;
            prim2->y0 = prim2->y1 = prim1->y0 = prim1->y1 = prim0->y0 - 3;
            prim2->drawMode = prim1->drawMode = prim0->drawMode = DRAW_DEFAULT;
            prim0->x3 += 2;
        } else {
            prim0->y0 = 0x40;
            prim0->unkA = temp2 | 0x1800;
            prim2->y0 = prim2->y1 = prim1->y0 = prim1->y1 = 0x3D;
            if (self->ext.save.unk4 == 0x28) {
                prim0->x3 += 2;
            }
            if ((temp >= 0xE0) || (g_pads[0].pressed & 0x700)) {
                prim2->drawMode = prim1->drawMode = prim0->drawMode = DRAW_HIDE;
                return 1;
            }
        }
    }
    return 0;
}

void func_06066FE0(s32 arg0, Primitive* prim, s32 arg2) {
    if (arg0 == arg2) {
        u32 temp = (g_Timer >> 3 & 7);
        prim->unk6 =
            temp + 2 +
            LookupTblNoToVram(g_SaturnSharedSpriteBank13Resource.flags + 3);
        prim->unk6 = prim->unk6 & 0x8FFF | 0x4000;
    } else {
        prim->unk6 =
            1 + LookupTblNoToVram(g_SaturnSharedSpriteBank13Resource.flags + 3);
        prim->unk6 = prim->unk6 & 0x8FFF | 0x4000;
    }
}

s16 DAT_0607C134[][2] = {
    {0x64, 0x78},
    {0x2C, 0x6C},
    {0xA8, 0x6C},
};

s32 func_06067090(Entity* self) {
    Primitive* prim0;
    Primitive* prim1;
    Primitive* prim2;
    s16 sp[2];
    s32 i;

    s32 temp;
    s32 temp2;

    prim0 = self->ext.save.unk10;
    prim1 = self->ext.save.unk14;
    prim2 = self->ext.save.unk18;
    temp = prim0->x3;
    if (temp == 0) {
        PlaySfx(SFX_UI_ALERT_TINK);
        prim0->x3 += 2;
        func_06067958();
        for (i = 0; i < 3; i++) {
            s16 x = DAT_0607C134[i][0];
            s16 w = DAT_0607C134[i][1];
            func_06066B74(prim0, prim1, prim2);
            prim0->x0 = x;
            if (i == 0) {
                prim0->unkA = 0x1820;
            } else {
                prim0->unkA = 0x1810;
                prim0->unk8 += (i + 1) * 0xC0;
            }
            prim2->x0 = prim2->x3 = prim1->x0 = prim1->x3 = x - 6;
            prim2->x1 = prim2->x2 = prim1->x1 = prim1->x2 = x + w + 6;
            prim0 = prim0->next;
            prim1 = prim1->next;
            prim2 = prim2->next;
        }
        prim0 = self->ext.save.unk10;
        prim1 = self->ext.save.unk14;
        prim2 = self->ext.save.unk18;
        sp[0] = 0;
        sp[1] = 0;
        func_0606797C(DAT_0607C100, sp, 0x10);
        temp2 = sp[1] + 0x10;
        self->ext.save.unk1E = temp2;
        temp2 += 0x40;
        prim0->y0 = temp2;
        prim2->y0 = prim2->y1 = prim1->y0 = prim1->y1 = temp2 - 3;
        prim2->y2 = prim2->y3 = prim1->y2 = prim1->y3 = temp2 + 3;
        temp2 += 0x20;
        for (i = 0; i < 2; i++) {
            prim0 = prim0->next;
            prim1 = prim1->next;
            prim2 = prim2->next;
            if (i == 0) {
                sp[0] = 0x18;
            } else {
                sp[0] = 0;
            }
            sp[1] = 0;
            func_0606797C(DAT_0607C0F0[i], sp, i + 0x11);
            prim0->y0 = temp2;
            prim2->y0 = prim2->y1 = prim1->y0 = prim1->y1 = temp2 - 3;
            prim2->y2 = prim2->y3 = prim1->y2 = prim1->y3 = temp2 + 3;
            func_06066FE0(i, prim1, DAT_060485C0.unk4);
        }
        func_06067A04();
    } else {
        if (temp <= self->ext.save.unk1E) {
            prim0->x3 += 2;
            temp2 = self->ext.save.unk1E + 0x40;
            prim0->y0 = temp2 - temp;
            prim0->unkA = temp | 0x1800;

            prim2->y0 = prim2->y1 = prim1->y0 = prim1->y1 = prim0->y0 - 3;
            prim2->drawMode = prim1->drawMode = prim0->drawMode = DRAW_DEFAULT;
            temp2 += 0x20;
            if (temp > 0x10) {
                temp = 0x10;
            }
            for (i = 0; i < 2; i++) {
                prim0 = prim0->next;
                prim1 = prim1->next;
                prim2 = prim2->next;
                prim0->y0 = temp2 - temp;
                prim0->unkA = temp | 0x1800;
                prim2->y0 = prim2->y1 = prim1->y0 = prim1->y1 = prim0->y0 - 3;
                prim2->drawMode = prim1->drawMode = prim0->drawMode =
                    DRAW_DEFAULT;
                func_06066FE0(i, prim1, DAT_060485C0.unk4);
            }
        } else {
            if (g_pads[0].tapped & PAD_LEFT) {
                if (DAT_060485C0.unk4 != 0) {
                    PlaySfx(SFX_UI_SUBWEAPON_TINK);
                }
                DAT_060485C0.unk4 = 0;
            }
            if (g_pads[0].tapped & PAD_RIGHT) {
                if (DAT_060485C0.unk4 == 0) {
                    PlaySfx(SFX_UI_SUBWEAPON_TINK);
                }
                DAT_060485C0.unk4 = 1;
            }
            for (i = 0; i < 2; i++) {
                prim1 = prim1->next;
                func_06066FE0(i, prim1, DAT_060485C0.unk4);
            }
            if (g_pads[0].tapped & PAD_CROSS) {
                DAT_060485C0.unk4 = self->ext.save.unk28;
                for (i = 0; i < 9; i++) {
                    prim0->drawMode = DRAW_HIDE;
                    prim0 = prim0->next;
                }
                return 2;
            }
            if (g_pads[0].tapped & 0x600) {
                PlaySfx(SFX_UI_CONFIRM);
                DAT_060485C0.unk5 = 0;
                for (i = 0; i < 9; i++) {
                    prim0->drawMode = DRAW_HIDE;
                    prim0 = prim0->next;
                }
                return 1;
            }
        }
    }
    return 0;
}

s16 DAT_0607C140[][2] = {
    {0x40, 0xC0},
    {0x5C, 0x24},
    {0xC0, 0x24},
};

s32 func_060674B8(Entity* self, s32 arg1) {
    Primitive* prim0;
    Primitive* prim1;
    Primitive* prim2;
    s16 sp[2];
    s32 i;

    s32 temp;
    s32 temp2;

    prim0 = self->ext.save.unk10;
    prim1 = self->ext.save.unk14;
    prim2 = self->ext.save.unk18;
    temp = prim0->x3;
    if (temp == 0) {
        PlaySfx(SFX_UI_ALERT_TINK);
        prim0->x3 += 2;
        func_06067958();
        for (i = 0; i < 3; i++) {
            s32 x = DAT_0607C140[i][0];
            s32 w = DAT_0607C140[i][1];
            func_06066B74(prim0, prim1, prim2);
            prim0->x0 = x;
            if (i == 0) {
                prim0->unkA = 0x1830;
            } else {
                prim0->unkA = 0xC10;
                prim0->unk8 += (i + 5) * 0x60;
            }
            prim2->x0 = prim2->x3 = prim1->x0 = prim1->x3 = x - 6;
            prim2->x1 = prim2->x2 = prim1->x1 = prim1->x2 = x + w + 6;
            prim0 = prim0->next;
            prim1 = prim1->next;
            prim2 = prim2->next;
        }
        prim0 = self->ext.save.unk10;
        prim1 = self->ext.save.unk14;
        prim2 = self->ext.save.unk18;
        sp[0] = 0;
        sp[1] = 0;
        if (arg1 == 2) {
            func_0606797C(DAT_0607C0F0[1], sp, 0x20);
            func_0606797C(DAT_0607C104, sp, 0x20);
            sp[0] = 0;
            sp[1] += 0x10;
            func_0606797C(DAT_0607C108, sp, 0x20);
            self->ext.save.unk1C = 1;
        } else if (arg1 == 3) {
            func_0606797C(DAT_0607C10C, sp, 0x20);
            self->ext.save.unk1C = 0;
        } else if (arg1 == 4) {
            func_0606797C(DAT_0607C110, sp, 0x20);
            self->ext.save.unk1C = 0;
        }
        temp2 = sp[1] + 0x10;
        self->ext.save.unk1E = temp2;
        temp2 += 0x40;
        prim0->y0 = temp2;
        prim2->y0 = prim2->y1 = prim1->y0 = prim1->y1 = temp2 - 3;
        prim2->y2 = prim2->y3 = prim1->y2 = prim1->y3 = temp2 + 3;
        temp2 += 0x20;
        for (i = 0; i < 2; i++) {
            prim0 = prim0->next;
            prim1 = prim1->next;
            prim2 = prim2->next;
            if (i == 0) {
                sp[0] = 8;
            } else {
                sp[0] = 0;
            }
            sp[1] = 0;
            func_0606797C(DAT_0607C0F8[i], sp, i + 0x21);
            prim0->y0 = temp2;
            prim2->y0 = prim2->y1 = prim1->y0 = prim1->y1 = temp2 - 3;
            prim2->y2 = prim2->y3 = prim1->y2 = prim1->y3 = temp2 + 3;
            func_06066FE0(i, prim1, self->ext.save.unk1C);
        }
        func_06067A04();
    } else {
        if (temp <= self->ext.save.unk1E) {
            prim0->x3 += 2;
            temp2 = self->ext.save.unk1E + 0x40;
            prim0->y0 = temp2 - temp;
            prim0->unkA = temp | 0x1800;
            prim2->y0 = prim2->y1 = prim1->y0 = prim1->y1 = prim0->y0 - 3;
            prim2->drawMode = prim1->drawMode = prim0->drawMode = DRAW_DEFAULT;
            temp2 += 0x20;
            if (temp > 0x10) {
                temp = 0x10;
            }
            for (i = 0; i < 2; i++) {
                prim0 = prim0->next;
                prim1 = prim1->next;
                prim2 = prim2->next;
                prim0->y0 = temp2 - temp;
                prim0->unkA = temp | 0xC00;
                prim2->y0 = prim2->y1 = prim1->y0 = prim1->y1 = prim0->y0 - 3;
                prim2->drawMode = prim1->drawMode = prim0->drawMode =
                    DRAW_DEFAULT;
                func_06066FE0(i, prim1, self->ext.save.unk1C);
            }
        } else {
            if (g_pads[0].tapped & PAD_LEFT) {
                if (self->ext.save.unk1C != 0) {
                    PlaySfx(SFX_UI_SUBWEAPON_TINK);
                }
                self->ext.save.unk1C = 0;
            }
            if (g_pads[0].tapped & PAD_RIGHT) {
                if (self->ext.save.unk1C == 0) {
                    PlaySfx(SFX_UI_SUBWEAPON_TINK);
                }
                self->ext.save.unk1C = 1;
            }
            for (i = 0; i < 2; i++) {
                prim1 = prim1->next;
                func_06066FE0(i, prim1, self->ext.save.unk1C);
            }
            if (g_pads[0].tapped & PAD_CROSS) {
                self->ext.save.unk1C = 1;
                for (i = 0; i < 9; i++) {
                    prim0->drawMode = DRAW_HIDE;
                    prim0 = prim0->next;
                }
                return 1;
            }
            if (g_pads[0].tapped & 0x600) {
                PlaySfx(SFX_UI_CONFIRM);
                for (i = 0; i < 9; i++) {
                    prim0->drawMode = DRAW_HIDE;
                    prim0 = prim0->next;
                }
                return 1;
            }
        }
    }
    return 0;
}

void func_06067958(void) { memset(DAT_0604E5E0, 0, 0x1800); }

void func_0606797C(char* str, s16* arg1, s32 arg2) {
    s32 temp_r0;
    u32 temp_r2;
    u8* dst;
    s16 sp[2];

    dst = &DAT_0604E5E0[0];
    sp[0] = 0xC0;
    sp[1] = 0x40;
    temp_r2 = arg2 & 0xF;
    temp_r0 = arg2 >> 4;
    if (temp_r0 == 1) {
        if (temp_r2 == 0) {
            sp[1] = 0x20;
        } else {
            sp[1] = 0x10;
            dst = &DAT_0604E5E0[(temp_r2 + 1) * 0x600];
        }
    } else if (temp_r0 == 2) {
        if (temp_r2 == 0) {
            sp[1] = 0x30;
        } else {
            sp[0] = 0x60;
            sp[1] = 0x10;
            dst = &DAT_0604E5E0[(temp_r2 + 5) * 0x300];
        }
    }
    func_0601960C(str, dst, sp, arg1, 1);
}

void func_06067A04(void) {
    s32 temp = 1;
    s32 temp2 = (DAT_0605aec0[temp][0] * 8) + VRAM_ADDR;

    QueueVramTransfer(temp2, DAT_0604E5E0, 0x1800);
}
