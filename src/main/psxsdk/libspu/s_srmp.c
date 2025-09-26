// SPDX-License-Identifier: MIT
#include "common.h"
#include "libspu_internal.h"

// clang-format off
static struct rev_param_entry D_800335B8[] = {
    {0x00000000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},
    {0x00000000, 0x007D, 0x005B, 0x6D80, 0x54B8, 0xBED0, 0x0000, 0x0000, 0xBA80, 0x5800, 0x5300, 0x04D6, 0x0333, 0x03F0, 0x0227, 0x0374, 0x01EF, 0x0334, 0x01B5, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x01B4, 0x0136, 0x00B8, 0x005C, 0x8000, 0x8000},
    {0x00000000, 0x0033, 0x0025, 0x70F0, 0x4FA8, 0xBCE0, 0x4410, 0xC0F0, 0x9C00, 0x5280, 0x4EC0, 0x03E4, 0x031B, 0x03A4, 0x02AF, 0x0372, 0x0266, 0x031C, 0x025D, 0x025C, 0x018E, 0x022F, 0x0135, 0x01D2, 0x00B7, 0x018F, 0x00B5, 0x00B4, 0x0080, 0x004C, 0x0026, 0x8000, 0x8000},
    {0x00000000, 0x00B1, 0x007F, 0x70F0, 0x4FA8, 0xBCE0, 0x4510, 0xBEF0, 0xB4C0, 0x5280, 0x4EC0, 0x0904, 0x076B, 0x0824, 0x065F, 0x07A2, 0x0616, 0x076C, 0x05ED, 0x05EC, 0x042E, 0x050F, 0x0305, 0x0462, 0x02B7, 0x042F, 0x0265, 0x0264, 0x01B2, 0x0100, 0x0080, 0x8000, 0x8000},
    {0x00000000, 0x00E3, 0x00A9, 0x6F60, 0x4FA8, 0xBCE0, 0x4510, 0xBEF0, 0xA680, 0x5680, 0x52C0, 0x0DFB, 0x0B58, 0x0D09, 0x0A3C, 0x0BD9, 0x0973, 0x0B59, 0x08DA, 0x08D9, 0x05E9, 0x07EC, 0x04B0, 0x06EF, 0x03D2, 0x05EA, 0x031D, 0x031C, 0x0238, 0x0154, 0x00AA, 0x8000, 0x8000},
    {0x00000000, 0x01A5, 0x0139, 0x6000, 0x5000, 0x4C00, 0xB800, 0xBC00, 0xC000, 0x6000, 0x5C00, 0x15BA, 0x11BB, 0x14C2, 0x10BD, 0x11BC, 0x0DC1, 0x11C0, 0x0DC3, 0x0DC0, 0x09C1, 0x0BC4, 0x07C1, 0x0A00, 0x06CD, 0x09C2, 0x05C1, 0x05C0, 0x041A, 0x0274, 0x013A, 0x8000, 0x8000},
    {0x00000000, 0x033D, 0x0231, 0x7E00, 0x5000, 0xB400, 0xB000, 0x4C00, 0xB000, 0x6000, 0x5400, 0x1ED6, 0x1A31, 0x1D14, 0x183B, 0x1BC2, 0x16B2, 0x1A32, 0x15EF, 0x15EE, 0x1055, 0x1334, 0x0F2D, 0x11F6, 0x0C5D, 0x1056, 0x0AE1, 0x0AE0, 0x07A2, 0x0464, 0x0232, 0x8000, 0x8000},
    {0x00000000, 0x0001, 0x0001, 0x7FFF, 0x7FFF, 0x0000, 0x0000, 0x0000, 0x8100, 0x0000, 0x0000, 0x1FFF, 0x0FFF, 0x1005, 0x0005, 0x0000, 0x0000, 0x1005, 0x0005, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x1004, 0x1002, 0x0004, 0x0002, 0x8000, 0x8000},
    {0x00000000, 0x0001, 0x0001, 0x7FFF, 0x7FFF, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x1FFF, 0x0FFF, 0x1005, 0x0005, 0x0000, 0x0000, 0x1005, 0x0005, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x1004, 0x1002, 0x0004, 0x0002, 0x8000, 0x8000},
    {0x00000000, 0x0017, 0x0013, 0x70F0, 0x4FA8, 0xBCE0, 0x4510, 0xBEF0, 0x8500, 0x5F80, 0x54C0, 0x0371, 0x02AF, 0x02E5, 0x01DF, 0x02B0, 0x01D7, 0x0358, 0x026A, 0x01D6, 0x011E, 0x012D, 0x00B1, 0x011F, 0x0059, 0x01A0, 0x00E3, 0x0058, 0x0040, 0x0028, 0x0014, 0x8000, 0x8000},
};
// clang-format on

void _spu_setReverbAttr(struct rev_param_entry* arg0);

static inline void _memcpy(char* dst, char* src, size_t size) {
    while (size--) {
        *dst++ = *src++;
    }
}

#define SPU_REV_ATTR_DAPF1 (0x01 << 0)
#define SPU_REV_ATTR_DAPF2 (0x01 << 1)
#define SPU_REV_ATTR_VIIR (0x01 << 2)
#define SPU_REV_ATTR_VCOMB1 (0x01 << 3)
#define SPU_REV_ATTR_VCOMB2 (0x01 << 4)
#define SPU_REV_ATTR_VCOMB3 (0x01 << 5)
#define SPU_REV_ATTR_VCOMB4 (0x01 << 6)
#define SPU_REV_ATTR_VWALL (0x01 << 7)
#define SPU_REV_ATTR_VAPF1 (0x01 << 8)
#define SPU_REV_ATTR_VAPF2 (0x01 << 9)
#define SPU_REV_ATTR_MLSAME (0x01 << 10)
#define SPU_REV_ATTR_MRSAME (0x01 << 11)
#define SPU_REV_ATTR_MLCOMB1 (0x01 << 12)
#define SPU_REV_ATTR_MRCOMB1 (0x01 << 13)
#define SPU_REV_ATTR_MLCOMB2 (0x01 << 14)
#define SPU_REV_ATTR_MRCOMB2 (0x01 << 15)
#define SPU_REV_ATTR_DLSAME (0x01 << 16)
#define SPU_REV_ATTR_DRSAME (0x01 << 17)
#define SPU_REV_ATTR_MLDIFF (0x01 << 18)
#define SPU_REV_ATTR_MRDIFF (0x01 << 19)
#define SPU_REV_ATTR_MLCOMB3 (0x01 << 20)
#define SPU_REV_ATTR_MRCOMB3 (0x01 << 21)
#define SPU_REV_ATTR_MLCOMB4 (0x01 << 22)
#define SPU_REV_ATTR_MRCOMB4 (0x01 << 23)
#define SPU_REV_ATTR_DLDIFF (0x01 << 24)
#define SPU_REV_ATTR_DRDIFF (0x01 << 25)
#define SPU_REV_ATTR_MLAPF1 (0x01 << 26)
#define SPU_REV_ATTR_MRAPF1 (0x01 << 27)
#define SPU_REV_ATTR_MLAPF2 (0x01 << 28)
#define SPU_REV_ATTR_MRAPF2 (0x01 << 29)
#define SPU_REV_ATTR_VLIN (0x01 << 30)
#define SPU_REV_ATTR_VRIN (0x01 << 31)

long SpuSetReverbModeParam(SpuReverbAttr* attr) {
    struct rev_param_entry entry;
    u32 var_s0;
    u16 cnt;

    bool var_s7 = false;
    bool var_s4 = false;
    bool var_s6 = false;
    bool sp58 = false;
    bool var_fp = false;

    u32 mask = attr->mask;
    bool bSetAll = attr->mask == 0;

    entry.flags = 0;
    if (bSetAll || mask & SPU_REV_MODE) {
        var_s0 = attr->mode;
        if (attr->mode & SPU_REV_MODE_CLEAR_WA) {
            var_s0 &= ~SPU_REV_MODE_CLEAR_WA;
            sp58 = true;
        }
        if (var_s0 >= 0xA ||
            _SpuIsInAllocateArea_(_spu_rev_startaddr[var_s0])) {
            return -1;
        }
        var_s4 = true;
        _spu_rev_attr.unk18 = var_s0;
        _spu_rev_offsetaddr = _spu_rev_startaddr[_spu_rev_attr.unk18];
        _memcpy(&entry, &D_800335B8[_spu_rev_attr.unk18],
                sizeof(struct rev_param_entry));
        switch (_spu_rev_attr.unk18) {
        case SPU_REV_MODE_ECHO:
            _spu_rev_attr.unk24 = 0x7F;
            _spu_rev_attr.unk20 = 0x7F;
            break;
        case SPU_REV_MODE_DELAY:
            _spu_rev_attr.unk24 = 0;
            _spu_rev_attr.unk20 = 0x7F;
            break;
        default:
            _spu_rev_attr.unk24 = 0;
            _spu_rev_attr.unk20 = 0;
            break;
        }
    }
    if (bSetAll || mask & SPU_REV_DELAYTIME) {
        switch (_spu_rev_attr.unk18) {
        case SPU_REV_MODE_ECHO:
        case SPU_REV_MODE_DELAY:
            var_s6 = true;
            if (!var_s4) {
                _memcpy(&entry, &D_800335B8[_spu_rev_attr.unk18],
                        sizeof(struct rev_param_entry));
                entry.flags = SPU_REV_ATTR_MLSAME | SPU_REV_ATTR_MRSAME |
                              SPU_REV_ATTR_MLCOMB1 | SPU_REV_ATTR_DLSAME |
                              SPU_REV_ATTR_MLAPF1 | SPU_REV_ATTR_MRAPF1;
            }
            _spu_rev_attr.unk20 = attr->delay;
            entry.mLSAME = ((_spu_rev_attr.unk20 << 0xD) / 0x7F) - entry.dAPF1;
            entry.mRSAME = ((_spu_rev_attr.unk20 << 0xC) / 0x7F) - entry.dAPF2;
            entry.mLCOMB1 =
                ((_spu_rev_attr.unk20 << 0xC) / 0x7F) + entry.mRCOMB1;
            entry.dLSAME = ((_spu_rev_attr.unk20 << 0xC) / 0x7F) + entry.dRSAME;
            entry.mLAPF1 = ((_spu_rev_attr.unk20 << 0xC) / 0x7F) + entry.mLAPF2;
            entry.mRAPF1 = ((_spu_rev_attr.unk20 << 0xC) / 0x7F) + entry.mRAPF2;
            break;
        default:
            _spu_rev_attr.unk20 = 0;
            break;
        }
    }
    if (bSetAll || mask & SPU_REV_FEEDBACK) {
        switch (_spu_rev_attr.unk18) {
        case SPU_REV_MODE_ECHO:
        case SPU_REV_MODE_DELAY:
            var_fp = true;
            if (!var_s4) {
                if (!var_s6) {
                    _memcpy(&entry, &D_800335B8[_spu_rev_attr.unk18],
                            sizeof(struct rev_param_entry));
                    entry.flags = SPU_REV_ATTR_VWALL;
                } else {
                    entry.flags |= SPU_REV_ATTR_VWALL;
                }
            }
            _spu_rev_attr.unk24 = attr->feedback;
            entry.vWALL = (_spu_rev_attr.unk24 * 0x8100) / 0x7F;
            break;
        default:
            _spu_rev_attr.unk24 = 0;
            break;
        }
    }
    if (var_s4) {
        var_s7 = (_spu_RXX->rxx.spucnt >> 7) & 1;
        if (var_s7) {
            cnt = _spu_RXX->rxx.spucnt;
            cnt &= ~0x80;
            _spu_RXX->rxx.spucnt = cnt;
        }
    }
    if (!var_s4) {
        if (bSetAll || mask & SPU_REV_DEPTHL) {
            _spu_RXX->rxx.rev_vol.left = attr->depth.left;
            _spu_rev_attr.unk1c = attr->depth.left;
        }
        if (bSetAll || mask & SPU_REV_DEPTHR) {
            _spu_RXX->rxx.rev_vol.right = attr->depth.right;
            _spu_rev_attr.unk1e = attr->depth.right;
        }
    } else {
        _spu_RXX->rxx.rev_vol.left = 0;
        _spu_RXX->rxx.rev_vol.right = 0;
        _spu_rev_attr.unk1c = 0;
        _spu_rev_attr.unk1e = 0;
    }
    if (var_s4 || var_s6 || var_fp) {
        _spu_setReverbAttr(&entry);
    }
    if (sp58) {
        SpuClearReverbWorkArea(_spu_rev_attr.unk18);
    }
    if (var_s4) {
        _spu_FsetRXX(0xD1, _spu_rev_offsetaddr, 0);
        if (var_s7) {
            cnt = _spu_RXX->rxx.spucnt;
            cnt |= 0x80;
            _spu_RXX->rxx.spucnt = cnt;
        }
    }
    return 0;
}

void _spu_setReverbAttr(struct rev_param_entry* arg0) {
    u32 mask = arg0->flags;
    bool bSetAll = arg0->flags == 0;

    if (bSetAll || mask & SPU_REV_ATTR_DAPF1) {
        _spu_RXX->rxx.dAPF1 = arg0->dAPF1;
    }
    if (bSetAll || mask & SPU_REV_ATTR_DAPF2) {
        _spu_RXX->rxx.dAPF2 = arg0->dAPF2;
    }
    if (bSetAll || mask & SPU_REV_ATTR_VIIR) {
        _spu_RXX->rxx.vIIR = arg0->vIIR;
    }
    if (bSetAll || mask & SPU_REV_ATTR_VCOMB1) {
        _spu_RXX->rxx.vCOMB1 = arg0->vCOMB1;
    }
    if (bSetAll || mask & SPU_REV_ATTR_VCOMB2) {
        _spu_RXX->rxx.vCOMB2 = arg0->vCOMB2;
    }
    if (bSetAll || mask & SPU_REV_ATTR_VCOMB3) {
        _spu_RXX->rxx.vCOMB3 = arg0->vCOMB3;
    }
    if (bSetAll || mask & SPU_REV_ATTR_VCOMB4) {
        _spu_RXX->rxx.vCOMB4 = arg0->vCOMB4;
    }
    if (bSetAll || mask & SPU_REV_ATTR_VWALL) {
        _spu_RXX->rxx.vWALL = arg0->vWALL;
    }
    if (bSetAll || mask & SPU_REV_ATTR_VAPF1) {
        _spu_RXX->rxx.vAPF1 = arg0->vAPF1;
    }
    if (bSetAll || mask & SPU_REV_ATTR_VAPF2) {
        _spu_RXX->rxx.vAPF2 = arg0->vAPF2;
    }
    if (bSetAll || mask & SPU_REV_ATTR_MLSAME) {
        _spu_RXX->rxx.mLSAME = arg0->mLSAME;
    }
    if (bSetAll || mask & SPU_REV_ATTR_MRSAME) {
        _spu_RXX->rxx.mRSAME = arg0->mRSAME;
    }
    if (bSetAll || mask & SPU_REV_ATTR_MLCOMB1) {
        _spu_RXX->rxx.mLCOMB1 = arg0->mLCOMB1;
    }
    if (bSetAll || mask & SPU_REV_ATTR_MRCOMB1) {
        _spu_RXX->rxx.mRCOMB1 = arg0->mRCOMB1;
    }
    if (bSetAll || mask & SPU_REV_ATTR_MLCOMB2) {
        _spu_RXX->rxx.mLCOMB2 = arg0->mLCOMB2;
    }
    if (bSetAll || mask & SPU_REV_ATTR_MRCOMB2) {
        _spu_RXX->rxx.mRCOMB2 = arg0->mRCOMB2;
    }
    if (bSetAll || mask & SPU_REV_ATTR_DLSAME) {
        _spu_RXX->rxx.dLSAME = arg0->dLSAME;
    }
    if (bSetAll || mask & SPU_REV_ATTR_DRSAME) {
        _spu_RXX->rxx.dRSAME = arg0->dRSAME;
    }
    if (bSetAll || mask & SPU_REV_ATTR_MLDIFF) {
        _spu_RXX->rxx.mLDIFF = arg0->mLDIFF;
    }
    if (bSetAll || mask & SPU_REV_ATTR_MRDIFF) {
        _spu_RXX->rxx.mRDIFF = arg0->mRDIFF;
    }
    if (bSetAll || mask & SPU_REV_ATTR_MLCOMB3) {
        _spu_RXX->rxx.mLCOMB3 = arg0->mLCOMB3;
    }
    if (bSetAll || mask & SPU_REV_ATTR_MRCOMB3) {
        _spu_RXX->rxx.mRCOMB3 = arg0->mRCOMB3;
    }
    if (bSetAll || mask & SPU_REV_ATTR_MLCOMB4) {
        _spu_RXX->rxx.mLCOMB4 = arg0->mLCOMB4;
    }
    if (bSetAll || mask & SPU_REV_ATTR_MRCOMB4) {
        _spu_RXX->rxx.mRCOMB4 = arg0->mRCOMB4;
    }
    if (bSetAll || mask & SPU_REV_ATTR_DLDIFF) {
        _spu_RXX->rxx.dLDIFF = arg0->dLDIFF;
    }
    if (bSetAll || mask & SPU_REV_ATTR_DRDIFF) {
        _spu_RXX->rxx.dRDIFF = arg0->dRDIFF;
    }
    if (bSetAll || mask & SPU_REV_ATTR_MLAPF1) {
        _spu_RXX->rxx.mLAPF1 = arg0->mLAPF1;
    }
    if (bSetAll || mask & SPU_REV_ATTR_MRAPF1) {
        _spu_RXX->rxx.mRAPF1 = arg0->mRAPF1;
    }
    if (bSetAll || mask & SPU_REV_ATTR_MLAPF2) {
        _spu_RXX->rxx.mLAPF2 = arg0->mLAPF2;
    }
    if (bSetAll || mask & SPU_REV_ATTR_MRAPF2) {
        _spu_RXX->rxx.mRAPF2 = arg0->mRAPF2;
    }
    if (bSetAll || mask & SPU_REV_ATTR_VLIN) {
        _spu_RXX->rxx.vLIN = arg0->vLIN;
    }
    if (bSetAll || mask & SPU_REV_ATTR_VRIN) {
        _spu_RXX->rxx.vRIN = arg0->vRIN;
    }
}
