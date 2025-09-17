// SPDX-License-Identifier: MIT
#include "common.h"
#include "libspu_internal.h"

extern struct rev_param_entry D_800335B8[];

static inline void _memcpy(char* dst, char* src, size_t size) {
    while (size--) {
        *dst++ = *src++;
    }
}

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
    if (bSetAll || mask & 1) {
        var_s0 = attr->mode;
        if (attr->mode & 0x100) {
            var_s0 &= ~0x100;
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
        case 7:
            _spu_rev_attr.unk24 = 0x7F;
            _spu_rev_attr.unk20 = 0x7F;
            break;
        case 8:
            _spu_rev_attr.unk24 = 0;
            _spu_rev_attr.unk20 = 0x7F;
            break;
        default:
            _spu_rev_attr.unk24 = 0;
            _spu_rev_attr.unk20 = 0;
            break;
        }
    }
    if (bSetAll || mask & 8) {
        switch (_spu_rev_attr.unk18) {
        case 7:
        case 8:
            var_s6 = true;
            if (!var_s4) {
                _memcpy(&entry, &D_800335B8[_spu_rev_attr.unk18],
                        sizeof(struct rev_param_entry));
                entry.flags = 0x0C011C00;
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
    if (bSetAll || mask & 0x10) {
        switch (_spu_rev_attr.unk18) {
        case 7:
        case 8:
            var_fp = true;
            if (!var_s4) {
                if (!var_s6) {
                    _memcpy(&entry, &D_800335B8[_spu_rev_attr.unk18],
                            sizeof(struct rev_param_entry));
                    entry.flags = 0x80;
                } else {
                    entry.flags |= 0x80;
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
        if (bSetAll || mask & 2) {
            _spu_RXX->rxx.rev_vol.left = attr->depth.left;
            _spu_rev_attr.unk1c = attr->depth.left;
        }
        if (bSetAll || mask & 4) {
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

    if (bSetAll || mask & 1) {
        _spu_RXX->rxx.dAPF1 = arg0->dAPF1;
    }
    if (bSetAll || mask & 2) {
        _spu_RXX->rxx.dAPF2 = arg0->dAPF2;
    }
    if (bSetAll || mask & 4) {
        _spu_RXX->rxx.vIIR = arg0->vIIR;
    }
    if (bSetAll || mask & 8) {
        _spu_RXX->rxx.vCOMB1 = arg0->vCOMB1;
    }
    if (bSetAll || mask & 0x10) {
        _spu_RXX->rxx.vCOMB2 = arg0->vCOMB2;
    }
    if (bSetAll || mask & 0x20) {
        _spu_RXX->rxx.vCOMB3 = arg0->vCOMB3;
    }
    if (bSetAll || mask & 0x40) {
        _spu_RXX->rxx.vCOMB4 = arg0->vCOMB4;
    }
    if (bSetAll || mask & 0x80) {
        _spu_RXX->rxx.vWALL = arg0->vWALL;
    }
    if (bSetAll || mask & 0x100) {
        _spu_RXX->rxx.vAPF1 = arg0->vAPF1;
    }
    if (bSetAll || mask & 0x200) {
        _spu_RXX->rxx.vAPF2 = arg0->vAPF2;
    }
    if (bSetAll || mask & 0x400) {
        _spu_RXX->rxx.mLSAME = arg0->mLSAME;
    }
    if (bSetAll || mask & 0x800) {
        _spu_RXX->rxx.mRSAME = arg0->mRSAME;
    }
    if (bSetAll || mask & 0x1000) {
        _spu_RXX->rxx.mLCOMB1 = arg0->mLCOMB1;
    }
    if (bSetAll || mask & 0x2000) {
        _spu_RXX->rxx.mRCOMB1 = arg0->mRCOMB1;
    }
    if (bSetAll || mask & 0x4000) {
        _spu_RXX->rxx.mLCOMB2 = arg0->mLCOMB2;
    }
    if (bSetAll || mask & 0x8000) {
        _spu_RXX->rxx.mRCOMB2 = arg0->mRCOMB2;
    }
    if (bSetAll || mask & 0x10000) {
        _spu_RXX->rxx.dLSAME = arg0->dLSAME;
    }
    if (bSetAll || mask & 0x20000) {
        _spu_RXX->rxx.dRSAME = arg0->dRSAME;
    }
    if (bSetAll || mask & 0x40000) {
        _spu_RXX->rxx.mLDIFF = arg0->mLDIFF;
    }
    if (bSetAll || mask & 0x80000) {
        _spu_RXX->rxx.mRDIFF = arg0->mRDIFF;
    }
    if (bSetAll || mask & 0x100000) {
        _spu_RXX->rxx.mLCOMB3 = arg0->mLCOMB3;
    }
    if (bSetAll || mask & 0x200000) {
        _spu_RXX->rxx.mRCOMB3 = arg0->mRCOMB3;
    }
    if (bSetAll || mask & 0x400000) {
        _spu_RXX->rxx.mLCOMB4 = arg0->mLCOMB4;
    }
    if (bSetAll || mask & 0x800000) {
        _spu_RXX->rxx.mRCOMB4 = arg0->mRCOMB4;
    }
    if (bSetAll || mask & 0x01000000) {
        _spu_RXX->rxx.dLDIFF = arg0->dLDIFF;
    }
    if (bSetAll || mask & 0x02000000) {
        _spu_RXX->rxx.dRDIFF = arg0->dRDIFF;
    }
    if (bSetAll || mask & 0x04000000) {
        _spu_RXX->rxx.mLAPF1 = arg0->mLAPF1;
    }
    if (bSetAll || mask & 0x08000000) {
        _spu_RXX->rxx.mRAPF1 = arg0->mRAPF1;
    }
    if (bSetAll || mask & 0x10000000) {
        _spu_RXX->rxx.mLAPF2 = arg0->mLAPF2;
    }
    if (bSetAll || mask & 0x20000000) {
        _spu_RXX->rxx.mRAPF2 = arg0->mRAPF2;
    }
    if (bSetAll || mask & 0x40000000) {
        _spu_RXX->rxx.vLIN = arg0->vLIN;
    }
    if (bSetAll || mask & 0x80000000) {
        _spu_RXX->rxx.vRIN = arg0->vRIN;
    }
}
