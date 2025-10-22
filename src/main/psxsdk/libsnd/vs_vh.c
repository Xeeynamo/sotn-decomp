// SPDX-License-Identifier: MIT
#include "common.h"
#include "libsnd_i.h"

s16 SsVabOpenHeadWithMode(u8* addr, s16 vabid, s16 arg2, u32 sbaddr);

s16 SsVabOpenHead(u8* arg1, s16 vabid) {
    return SsVabOpenHeadWithMode(arg1, vabid, 0, 0);
}

s16 SsVabOpenHeadSticky(u8* addr, s16 vabid, u32 sbaddr) {
    return SsVabOpenHeadWithMode(addr, vabid, 1, sbaddr);
}

s16 SsVabFakeHead(u8* addr, s16 vabid, u32 sbaddr) {
    return SsVabOpenHeadWithMode(addr, vabid, 1, sbaddr);
}

s16 SsVabOpenHeadWithMode(u8* addr, s16 vabid, s16 arg2, u32 sbaddr) {
    int vagLens[256];
    s32 i;
    s32 var_s0;
    s16 vabId_2;
    u16 temp_v1;
    u16* ptr_vag_off_table;
    u32 magic;
    u32 spuAllocMem;
    u8 num_vags;
    ProgAtr* pProgTable;
    u8* var_a2;
    VabHdr* vab_hdr_2;
    vabId_2 = 0x10;
    if (_spu_getInTransfer() == 1) {
        return -1;
    }
    _spu_setInTransfer(1);
    if (vabid >= 0x10) {
        _spu_setInTransfer(0);
        return -1;
    }
    if (vabid == -1) {
        for (i = 0; i < 16; i++) {
            if (_svm_vab_used[i] == 0) {
                _svm_vab_used[i] = 1;
                vabId_2 = i;
                _svm_vab_count++;
                break;
            }
        }
    } else {
        var_a2 = _svm_vab_used;
        if (var_a2[vabid] == 0) {
            _svm_vab_used[vabid] = 1;
            vabId_2 = vabid;
            _svm_vab_count++;
        }
    }
    if (vabId_2 >= 0x10) {
        _spu_setInTransfer(0);
        return -1;
    }
    var_a2 = addr;
    _svm_vab_vh[vabId_2] = var_a2;

    var_a2 = var_a2 + 0x20;
    vab_hdr_2 = addr;
    magic = vab_hdr_2->form;
    if ((magic >> 8) != ('V' << 0x10 | 'A' << 0x8 | 'B')) {
        _svm_vab_used[vabId_2] = 0;
        _spu_setInTransfer(0);
        _svm_vab_count -= 1;
        return -1;
    }
    if ((magic & 0xFF) == 'p') {
        if (vab_hdr_2->ver >= 5) {
            kMaxPrograms = 0x80;
        } else {
            kMaxPrograms = 0x40;
        }
    } else {
        kMaxPrograms = 0x40;
    }
    if (vab_hdr_2->ps <= kMaxPrograms) {
        _svm_vab_pg[vabId_2] = var_a2;
        pProgTable = var_a2;
        var_a2 = var_a2 + (kMaxPrograms * 0x10);
        var_s0 = 0;
        for (i = 0; i < kMaxPrograms; i++) {
            pProgTable[i].reserved1 = var_s0;
            if (pProgTable[i].tones != 0) {
                var_s0++;
            }
        }
        var_s0 = 0;
        _svm_vab_tn[vabId_2] = var_a2;
        ptr_vag_off_table = var_a2 + (vab_hdr_2->ps << 9);
        num_vags = vab_hdr_2->vs;
        for (i = 0; i < 256; i++) {
            if (num_vags >= i) {
                temp_v1 = *ptr_vag_off_table;
                if (vab_hdr_2->ver >= 5) {
                    vagLens[i] = temp_v1 * 8;
                } else {
                    vagLens[i] = temp_v1 * 4;
                }
                var_s0 += vagLens[i];
            }
            ptr_vag_off_table++;
        }

        _svm_brr_start_addr[vabId_2] = ptr_vag_off_table;
        spuAllocMem = sbaddr;
        if (arg2 == 0) {
            spuAllocMem = SpuMalloc(var_s0);
            if (spuAllocMem == -1) {
                _svm_vab_used[vabId_2] = 0;
                _spu_setInTransfer(0);
                _svm_vab_count -= 1;
                return -1;
            }
        }
        if ((spuAllocMem + var_s0) > 0x80000U) {
        end:
            _svm_vab_used[vabId_2] = 0;

            _spu_setInTransfer(0);
            _svm_vab_count -= 1;
            return -1;
        }
        _svm_vab_start[vabId_2] = spuAllocMem;
        var_s0 = 0;
        for (i = 0; i <= num_vags; i++) {
            var_s0 += vagLens[i];
            if (!(i & 1)) {
                pProgTable[i / 2].reserved2 = (spuAllocMem + var_s0) >> 3;
            } else {
                pProgTable[i / 2].reserved3 = (spuAllocMem + var_s0) >> 3;
            }
        }

        _svm_vab_total[vabId_2] = var_s0;
        _svm_vab_used[vabId_2] = 2;
    } else {
        goto end;
    }
    return vabId_2;
}
