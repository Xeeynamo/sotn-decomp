// SPDX-License-Identifier: MIT
#include "common.h"
#include "libspu_internal.h"

extern struct rev_param_entry D_800335B8[];

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
