// SPDX-License-Identifier: AGPL-3.0-or-later
#include <game_psp.h>

u16 D_psp_089466AC[][2] = {
    {0x8140, 0x0000}, {0x8180, 0x003F}, {0x81B8, 0x006C}, {0x81C8, 0x0074},
    {0x81DA, 0x007B}, {0x81F0, 0x008A}, {0x81FC, 0x0092}, {0x824F, 0x0093},
    {0x8260, 0x009D}, {0x8281, 0x00B7}, {0x829F, 0x00D1}, {0x8340, 0x0124},
    {0x8380, 0x0163}, {0x839F, 0x017A}, {0x83BF, 0x0192}, {0x8440, 0x01AA},
    {0x8470, 0x01CB}, {0x8480, 0x01DA}, {0x849F, 0x01EC},
};

u16 D_psp_089466F8[][2] = {
    {0x8540, 0x0000}, {0x8546, 0x0005}, {0x8548, 0x0006}, {0x854B, 0x0008},
    {0x8550, 0x0009}, {0x85A0, 0x0015}, {0x85B0, 0x0022}, {0x8640, 0x002F},
    {0x8643, 0x0031}, {0x8645, 0x0032}, {0x8647, 0x0033}, {0x864A, 0x0035},
    {0x864E, 0x0038}, {0x8660, 0x003A}, {0x869F, 0x004A}, {0x86B8, 0x0062},
    {0x8740, 0x00A0}, {0x875C, 0x00BB}, {0x8764, 0x00C2},
};

u16 D_psp_08946744[][2] = {
    {0x889F, 0x0000}, {0x8940, 0x005E}, {0x899F, 0x00BC}, {0x8A40, 0x011A},
    {0x8A9F, 0x0178}, {0x8B40, 0x01D6}, {0x8B9F, 0x0234}, {0x8C40, 0x0292},
    {0x8C9F, 0x02F0}, {0x8D40, 0x034E}, {0x8D9F, 0x03AC}, {0x8E40, 0x040A},
    {0x8E9F, 0x0468}, {0x8F40, 0x04C6}, {0x8F9F, 0x0524}, {0x9040, 0x0582},
    {0x909F, 0x05E0}, {0x9140, 0x063E}, {0x919F, 0x069C}, {0x9240, 0x06FA},
    {0x929F, 0x0758}, {0x9340, 0x07B6}, {0x939F, 0x0814}, {0x9440, 0x0872},
    {0x949F, 0x08D0}, {0x9540, 0x092E}, {0x959F, 0x098C}, {0x9640, 0x09EA},
    {0x969F, 0x0A48}, {0x9740, 0x0AA6}, {0x979F, 0x0B04}, {0x9840, 0x0B62},
};

u8 D_psp_089467C4[] = {
#include "gen/D_psp_089467C4.h"
};

u8 D_psp_0894A52C[] = {
#include "gen/D_psp_0894A52C.h"
};

u8 D_psp_089600A4[] = {
#include "gen/D_psp_089600A4.h"
};

s32 func_psp_08926A08(u16 ch16) {
    u8 ch[2];
    u8 idx;
    s32 var_s1;
    s32 var_s2;

    var_s1 = 0;
    memcpy(ch, &ch16, 2);
    switch (ch[1]) {
    case 0x81:
        if (ch[0] >= 0x40 && ch[0] < 0x7F) {
            idx = 0;
        } else if (ch[0] >= 0x80 && ch[0] < 0xAD) {
            idx = 1;
        } else if (ch[0] >= 0xB8 && ch[0] < 0xC0) {
            idx = 2;
        } else if (ch[0] >= 0xC8 && ch[0] < 0xCF) {
            idx = 3;
        } else if (ch[0] >= 0xDA && ch[0] < 0xE9) {
            idx = 4;
        } else if (ch[0] >= 0xF0 && ch[0] < 0xF8) {
            idx = 5;
        } else if (ch[0] == 0xFC) {
            idx = 6;
        } else {
            var_s1 = -1;
            break;
        }
        var_s1 = ch16 - D_psp_089466AC[idx][0] + D_psp_089466AC[idx][1];
        break;

    case 0x82:
        if (ch[0] >= 0x4F && ch[0] < 0x59) {
            idx = 7;
        } else if (ch[0] >= 0x60 && ch[0] < 0x7A) {
            idx = 8;
        } else if (ch[0] >= 0x81 && ch[0] < 0x9B) {
            idx = 9;
        } else if (ch[0] >= 0x9F && ch[0] < 0xF2) {
            idx = 10;
        } else {
            var_s1 = -1;
            break;
        }
        var_s1 = ch16 - D_psp_089466AC[idx][0] + D_psp_089466AC[idx][1];
        break;

    case 0x83:
        if (ch[0] >= 0x40 && ch[0] < 0x7F) {
            idx = 11;
        } else if (ch[0] >= 0x80 && ch[0] < 0x97) {
            idx = 12;
        } else if (ch[0] >= 0x9F && ch[0] < 0xB7) {
            idx = 13;
        } else if (ch[0] >= 0xBF && ch[0] < 0xD7) {
            idx = 14;
        } else {
            var_s1 = -1;
            break;
        }
        var_s1 = ch16 - D_psp_089466AC[idx][0] + D_psp_089466AC[idx][1];
        break;

    case 0x84:
        if (ch[0] >= 0x40 && ch[0] < 0x61) {
            idx = 15;
        } else if (ch[0] >= 0x70 && ch[0] < 0x7F) {
            idx = 16;
        } else if (ch[0] >= 0x80 && ch[0] < 0x92) {
            idx = 17;
        } else if (ch[0] >= 0x9F && ch[0] < 0xBF) {
            idx = 18;
        }
        var_s1 = ch16 - D_psp_089466AC[idx][0] + D_psp_089466AC[idx][1];
        break;

    case 0x85:
    case 0x86:
        var_s1 = (ch16 - 0x8000) - 0x540;
        break;

    case 0x87:
        if (ch[0] >= 0x40 && ch[0] < 0x5B) {
            idx = 16;
        } else if (ch[0] >= 0x5C && ch[0] < 0x63) {
            idx = 17;
        } else if (ch[0] >= 0x64 && ch[0] < 0x97) {
            idx = 18;
        } else {
            var_s1 = -1;
            break;
        }
        var_s1 = ch16 - D_psp_089466F8[idx][0] + D_psp_089466F8[idx][1];
        break;

    default:
        if (ch[1] >= 0x99 || (ch[1] == 0x98 && ch[0] >= 0x73) || ch[1] < 0x88 ||
            (ch[1] == 0x88 && ch[0] < 0x9F) || ch[0] >= 0xFD || ch[0] < 0x40 ||
            (ch[0] > 0x7E && ch[0] < 0x80)) {
            var_s1 = -1;
        } else {
            if (ch[0] < 0x7F) {
                var_s2 = 0;
            } else {
                var_s2 = 1;
            }
            var_s1 = (ch[1] - 0x88) * 2;
            idx = (var_s1 + var_s2) - 1;
            var_s1 = ch16 - D_psp_08946744[idx][0] + D_psp_08946744[idx][1];
        }
        break;
    }
    if (var_s1 == -1) {
        var_s1 = 0;
    }
    return var_s1;
}

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", Krom2RawAdd);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", ApplyRotMatrix);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", ScaleMatrix);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", CompMatrix);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", DpqColor);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", NormalColorDpq);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", NormalClip);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", RotTrans);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", RotTransPers);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", RotTransPers3);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", RotTransPers4);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", RotAverage3);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", RotAverage4);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", RotAverageNclip3);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", RotAverageNclip4);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", func_psp_08927C5C);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", SquareRoot0);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", SquareRoot12);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", ratan2);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", VectorNormalS);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", rcos);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", rsin);

void gte_stub(void) {}

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", InitGeom);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", SetGeomScreen);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", SetGeomOffset);

void SetFarColor(void) {}

void SetFogNear(void) {}

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", func_psp_089280CC);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", func_psp_0892827C);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", func_psp_08928428);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", func_psp_08928498);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", func_psp_0892851C);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", func_psp_089285A0);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", RotMatrixX);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", RotMatrixY);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", RotMatrixZ);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", RotMatrix);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", RotMatrixYXZ);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", SetRotMatrix);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", TransMatrix);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", SetTransMatrix);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", gte_SetTransVector);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", gte_ldv0);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", gte_ldv1);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", gte_ldv2);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", gte_ldv3c);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", gte_ldtx);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", gte_ldty);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", gte_ldtz);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", gte_ldtr);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", func_psp_08928980);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", gte_rtps);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", gte_rtpt);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", gte_stsxy);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", gte_stsxy3_gt3);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", gte_stsxy3);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", gte_stszotz);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", gte_stotz);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", gte_stopz);

void gte_dpcs(void) {}

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", gte_strgb);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", gte_ldrgb);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", gte_nclip);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", gte_avsz3);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", func_psp_089295E4);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", gte_avsz4);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", gte_ldv01c);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", gte_stsxy01c);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", SetColorMatrix);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", SetLightMatrix);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", SetBackColor);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", func_psp_08929838);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", func_psp_08929860);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", NormalColorCol);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", func_psp_08929FA8);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", func_psp_0892A018);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", func_psp_0892A0C4);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", func_psp_0892A0F0);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", func_psp_0892A1EC);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", func_psp_0892A21C);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", func_psp_0892A28C);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", func_psp_0892A2D8);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", func_psp_0892A3D4);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", func_psp_0892A414);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", func_psp_0892A620);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", func_psp_0892A70C);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", func_psp_0892A76C);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", func_psp_0892A7E0);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", func_psp_0892A8C0);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", func_psp_0892A8FC);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", func_psp_0892A97C);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", func_psp_0892A998);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", SsSetSerialVol);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", func_psp_0892A9E0);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", strFileOpen);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", strFileClose);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", strFileRead);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", strFileLseek);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", play_bgm);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", init_atrac3plus);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", play_atrac3plus);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", createPlayModeFlag);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", setPlayMode);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", checkPlayMode);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", waitPlayMode);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", clearPlayMode);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", release_arg);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", at3plus_addData);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", reset_position);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", fadeoutOperation);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", DvdUmdIoInit);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", DvdUmdIoTerm);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", DvdUmdRetryOpenCB);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", DvdUmdRetryRead);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", func_psp_0892BF14);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", func_psp_0892BF48);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", func_psp_0892BFD0);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", func_psp_0892BFD8);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", func_psp_0892C168);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", func_psp_0892C174);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", func_psp_0892C188);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", func_psp_0892C214);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", func_psp_0892C3D4);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", func_psp_0892C4F8);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", func_psp_0892C524);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", func_psp_0892C540);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", func_psp_0892C62C);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", func_psp_0892C660);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", func_psp_0892C860);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", func_psp_0892CA28);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", func_psp_0892CA90);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", func_psp_0892CAD8);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", func_psp_0892CB10);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", func_psp_0892CB1C);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", func_psp_0892CB30);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", func_psp_0892CB40);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", func_psp_0892CC48);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", func_psp_0892CD48);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", func_psp_0892CDE0);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", func_psp_0892CEB0);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", func_psp_0892CF0C);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", func_psp_0892CF34);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", func_psp_0892CF7C);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", func_psp_0892CF88);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", func_psp_0892CF90);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", func_psp_0892D030);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", func_psp_0892D130);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", func_psp_0892D154);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", func_psp_0892D1B0);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", func_psp_0892D1D8);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", func_psp_0892D220);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", func_psp_0892D2E8);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", func_psp_0892D3B8);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", func_psp_0892D4A8);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", func_psp_0892D518);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", func_psp_0892D520);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", func_psp_0892D598);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", func_psp_0892D5F0);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", func_psp_0892D674);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", func_psp_0892D818);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", func_psp_0892D844);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", func_psp_0892D96C);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", func_psp_0892DADC);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", func_psp_0892DB90);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", func_psp_0892DBE4);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", func_psp_0892DC40);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", func_psp_0892DCD8);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", func_psp_0892DD54);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", func_psp_0892DDB0);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", func_psp_0892DF08);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", func_psp_0892DF70);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", func_psp_0892DFCC);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", func_psp_0892E498);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", func_psp_0892E6A4);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", func_psp_0892E718);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", func_psp_0892E798);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", func_psp_0892E818);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", func_psp_0892E8B8);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", func_psp_0892E914);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", func_psp_0892E978);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", func_psp_0892E994);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", func_psp_0892E9B0);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", func_psp_0892E9E4);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", GsClearVcount);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", func_psp_0892EA24);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", func_psp_0892EAFC);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", func_psp_0892EB04);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", func_psp_0892EBE8);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", func_psp_0892EC7C);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", SpuGetAllKeysStatus);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", SsUtKeyOnV);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", SsUtSetVVol);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", SpuSetKey);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", SpuSetVoiceAttr);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/280FC", func_psp_0892F83C);
