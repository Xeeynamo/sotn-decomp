#include <common.h>
#include <psxsdk/libspu.h>
#include <log.h>

#ifndef WANT_LIBSND_LLE
void SpuSetVoiceAttr(SpuVoiceAttr* arg) { DEBUGF("SpuSetVoiceAttr"); }

long SpuMallocWithStartAddr(unsigned long addr, long size) {
    NOT_IMPLEMENTED;
    return -1;
}

SpuIRQCallbackProc SpuSetIRQCallback(SpuIRQCallbackProc in) {
    NOT_IMPLEMENTED;
    return in;
}

long SpuSetTransferMode(long mode) {
    NOT_IMPLEMENTED;
    return 0;
}

long SpuClearReverbWorkArea(long rev_mode) {
    NOT_IMPLEMENTED;
    return 0;
}

void SpuSetKey(long on_off, unsigned long voice_bit) {
    DEBUGF("on_off %d voice_bit %08X", on_off, voice_bit);
}

#else
extern s32 _spu_rev_reserve_wa;
extern s32 _spu_rev_offsetaddr;
extern s32 _spu_mem_mode_plus;
extern s32 D_8003355C;
extern s32 D_80033560;
extern s32 _spu_mem_mode_unitM;
typedef struct tagSpuMalloc {
    u32 addr;
    u32 size;
} SPU_MALLOC;

extern SPU_MALLOC* _spu_memList;

u32 _SpuMallocSeparateTo3(s32 arg0, SPU_MALLOC* arg1, s32 arg2) {
    SPU_MALLOC* temp_addr;
    SPU_MALLOC* temp_v0;
    SPU_MALLOC* temp_v0_4;
    SPU_MALLOC* temp_v0_5;
    SPU_MALLOC* temp_v1_2;
    SPU_MALLOC* var_a1;
    SPU_MALLOC* var_v0;
    SPU_MALLOC* var_v1_2;
    s32 temp_size;
    s32 temp_t1;
    s32 temp_t2;
    s32 temp_v0_2;
    s32 temp_v1;
    s32 var_a2;
    s32 var_a3;
    s32 var_v0_2;
    s32 var_v1;
    u32 temp_t3;
    u32 temp_t4;
    u32 temp_v1_3;
    u32 var_a0;
    SPU_MALLOC* temp_v0_3;
    SPU_MALLOC* temp_v0_6;
    u32 fourmask;
    u32 fmask;

    var_a1 = arg1;
    var_a2 = arg2;
    temp_size = var_a2;
    temp_addr = var_a1;
    temp_v0 = &_spu_memList[arg0];
    temp_t3 = temp_v0->addr;
    temp_t4 = temp_v0->size;
    temp_t1 = temp_addr - (temp_v0->addr & 0x0FFFFFFF);
    if (_spu_rev_reserve_wa == 0) {
        var_v1 = 0;
    } else {
        var_v1 = (0x10000 - _spu_rev_offsetaddr) << _spu_mem_mode_plus;
    }
    if (temp_v0->addr & 0x40000000) {
        var_a3 = (temp_t4 - temp_t1) - var_v1;
    } else {
        var_a3 = temp_t4 - temp_t1;
    }
    var_v0 = (SPU_MALLOC*)-1;
    if (var_a3 >= temp_size) {
        if (temp_t3 & 0x40000000) {
            if (temp_t1 > 0) {
                var_a3 = D_80033560;
                var_v0 = (SPU_MALLOC*)-1;
                if ((D_8003355C - 2) >= D_80033560) {
                    var_a2 = (s32)_spu_memList;
                    D_80033560++;
                    var_a1 = (var_a3) + var_a2;
                    var_a1->size = temp_t1;
                    var_a1->addr = (var_a1->addr & 0x0FFFFFFF) | 0x80000000;
                    _spu_memList[D_80033560].addr = temp_addr;
                    _spu_memList[D_80033560].size = temp_size;
                } else {
                    return -1;
                }
            } else {
                var_a1 = (SPU_MALLOC*)D_80033560;
                if ((D_8003355C - 1) >= D_80033560) {
                    _spu_memList[D_80033560].size = (u32)temp_size;
                    _spu_memList[D_80033560].addr &= 0x0FFFFFFF;
                } else {
                    return -1;
                }
            }

            D_80033560++;
            fmask = 0x0FFFFFFF;
            _spu_memList[D_80033560].addr =
                ((temp_t3 & fmask) + temp_t1 + temp_size);
            fourmask = 0x40000000;
            _spu_memList[D_80033560].addr |= fourmask;
            _spu_memList[D_80033560].size = (temp_t4 - temp_t1) - temp_size;
        } else if (temp_t1 > 0) {
            if (var_a3 == temp_size) {
                var_v0_2 = D_8003355C - 2;
            } else {
                var_v0_2 = D_8003355C - 1;
            }
            var_v0 = (SPU_MALLOC*)-1;
            if (var_v0_2 >= D_80033560) {
                var_a1 = _spu_memList;
                temp_t2 = D_80033560;
                _spu_memList[arg0].size = (u32)temp_t1;
                temp_v1_3 = _spu_memList[temp_t2].addr;
                var_a0 = _spu_memList[temp_t2].size;
                var_a2 = temp_t2 + 1;
                _spu_memList[temp_t2].addr = (u32)temp_addr;
                _spu_memList[temp_t2].size = (u32)temp_size;
                D_80033560 = var_a2;
                _spu_memList[temp_t2 + 1].addr = temp_v1_3;
                _spu_memList[temp_t2 + 1].size = var_a0;
                if (var_a3 >= temp_size) {
                    var_v1_2 = &_spu_memList[var_a2];
                    var_a1 = (SPU_MALLOC*)var_v1_2->addr;
                    var_a0 = var_v1_2->size;
                    var_v1_2->addr =
                        ((temp_t3 & 0x0FFFFFFF) + temp_t1 + temp_size) |
                        0x80000000;
                    var_v1_2->size = var_a3 - temp_size;
                    D_80033560 = temp_t2 + 2;
                    var_v1_2[1].addr = var_a1;
                    var_v1_2[1].size = var_a0;
                }
            } else {
                return -1;
            }
        } else if ((temp_size >= var_a3) ||
                   (var_v0 = (SPU_MALLOC*)-1,
                    (((D_8003355C - 1) < D_80033560) == 0))) {
            temp_v0_6 = &_spu_memList[arg0];
            temp_v0_6->size = temp_size;
            temp_v0_6->addr = (s32)(temp_v0_6->addr & 0x0FFFFFFF);
            if (temp_size < var_a3) {
                var_v1_2 = &_spu_memList[D_80033560];
                var_a2 = (s32)_spu_memList[D_80033560].addr;
                _spu_memList[D_80033560].addr =
                    ((temp_t3 & 0x0FFFFFFF) + temp_size) | 0x80000000;
                var_a0 = _spu_memList[D_80033560].size;
                _spu_memList[D_80033560].size = var_a3 - temp_size;
                D_80033560++;
                var_v1_2[1].addr = var_a2;
                var_v1_2[1].size = var_a0;
            }
        } else {
            return -1;
        }
        func_800286E0();
        var_v0 = temp_addr;
    } else {
        return -1;
    }
    return (u32)var_v0;
}

long SpuMallocWithStartAddr(unsigned long addr, long size) {
    s32 temp_a1;
    s32 temp_a3_2;
    s32 list_pos;
    s32 var_a2;
    s32 addr_temp;
    s32 var_s2;
    s32 var_v0;
    s32 var_v0_2;
    u32 size_temp;
    u32 sep_size;
    u32 var_a1;
    u32 sep_addr;
    u32 fmask;
    u32 fourmask;
    if (_spu_rev_reserve_wa == 0) {
        var_s2 = 0;
    } else {
        var_s2 = (0x10000 - _spu_rev_offsetaddr) << _spu_mem_mode_plus;
    }
    var_a2 = size;
    if (size & ~_spu_mem_mode_unitM) {
        var_a2 = size + _spu_mem_mode_unitM;
    }
    var_a1 = addr;
    sep_size = (var_a2 >> _spu_mem_mode_plus) << _spu_mem_mode_plus;
    if (addr & ~_spu_mem_mode_unitM) {
        var_a1 = addr + _spu_mem_mode_unitM;
    }
    addr_temp = ((s32)var_a1 >> _spu_mem_mode_plus) << _spu_mem_mode_plus;
    var_v0 = -1;
    if (addr_temp >= 0x1010) {
        temp_a3_2 = addr_temp + sep_size;
        var_v0 = -1;
        if (((0x10000 << _spu_mem_mode_plus) - var_s2) >= temp_a3_2) {
            temp_a1 = addr_temp - 0x1010;
            if (_spu_memList->addr & 0x40000000) {
                size_temp =
                    ((_spu_memList->size + 0x1010) - addr_temp) - sep_size;
                if (temp_a1 > 0) {
                    var_v0 = -1;
                    if ((D_8003355C - 2) >= D_80033560) {
                        _spu_memList->addr = 0x80001010;
                        _spu_memList[2].addr = (s32)(temp_a3_2 | 0x40000000);
                        var_v0_2 = 2;
                        _spu_memList->size = (u32)temp_a1;
                        _spu_memList[1].addr = addr_temp;
                        _spu_memList[1].size = sep_size;
                        _spu_memList[2].size = size_temp;
                        goto block_15;
                    } else {
                        return -1;
                    }
                } else {
                    var_v0 = -1;
                    if ((D_8003355C - 1) >= D_80033560) {
                        _spu_memList[1].addr = (s32)(temp_a3_2 | 0x40000000);
                        var_v0_2 = 1;
                        _spu_memList->addr = (u32)addr_temp;
                        _spu_memList->size = sep_size;
                        _spu_memList[1].size = size_temp;
                    block_15:
                        D_80033560 = var_v0_2;
                        goto block_30;
                    }
                }
                return var_v0;
            }
            func_800286E0();
            list_pos = 0;
        loop_18:
            fmask = 0x0FFFFFFF;
            fourmask = 0x40000000;
            if ((s32)_spu_memList[list_pos].addr < 0) {
                sep_addr = _spu_memList[list_pos].addr & fmask;
                if ((u32)addr_temp >= sep_addr) {
                    if (((u32)addr_temp <
                         (u32)(sep_addr + _spu_memList[list_pos].size)) ||
                        (_spu_memList[list_pos + 1].addr & fourmask)) {
                        sep_addr = (u32)addr_temp;
                        if ((_spu_memList[list_pos].size -
                             (addr_temp - (_spu_memList[list_pos].addr &
                                           fmask))) >= (s32)sep_size) {
                            goto block_29;
                        }
                    }
                    goto block_27;
                }
                if ((s32)_spu_memList[list_pos].size < (s32)sep_size) {
                    list_pos += 1;
                    goto loop_18;
                }
                goto block_29;
            }
            if (!(_spu_memList[list_pos].addr & fourmask)) {
            block_27:
                list_pos += 1;
                goto loop_18;
            }
            sep_addr = _spu_memList[list_pos].addr & fmask;
            if ((_spu_memList[list_pos].size - var_s2) >= (s32)sep_size) {
            block_29:
                addr_temp = _SpuMallocSeparateTo3(list_pos, sep_addr, sep_size);
            block_30:
                func_800286E0();
                var_v0 = addr_temp;
                return var_v0;
            }
            return -1;
        }
    } else {
        return -1;
    }

    return var_v0;
}
#include <assert.h>
void _SpuSetVoiceAttr(SpuVoiceAttr* arg0, s32 arg1, s32 arg2, s32 arg3) { NOT_IMPLEMENTED; }
#endif
