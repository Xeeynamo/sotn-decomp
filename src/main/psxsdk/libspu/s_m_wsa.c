// SPDX-License-Identifier: MIT
#include "common.h"
#include "libspu_internal.h"

s32 _SpuMallocSeparateTo3(s32 arg0, u32 addr, s32 size) {
    s32 temp_t1;
    s32 temp_t3;
    s32 temp_t4;
    s32 var_a3;
    s32 var_v1;
    int a1 = addr;

    temp_t4 = _spu_memList[arg0].size;
    temp_t3 = _spu_memList[arg0].addr;
    temp_t1 = a1 - (_spu_memList[arg0].addr & 0x0FFFFFFF);

    if (_spu_rev_reserve_wa == 0) {
        var_v1 = 0;
    } else {
        var_v1 = (0x10000 - _spu_rev_offsetaddr) << _spu_mem_mode_plus;
    }

    if (temp_t3 & 0x40000000) {
        var_a3 = (temp_t4 - temp_t1) - var_v1;
    } else {
        var_a3 = temp_t4 - temp_t1;
    }

    if (var_a3 < size) {
        return -1;
    }

    if (temp_t3 & 0x40000000) {
        if (temp_t1 > 0) {
            if ((D_8003355C - 2) < D_80033560) {
                return -1;
            }
            _spu_memList[D_80033560].size = temp_t1;
            _spu_memList[D_80033560].addr &= 0x0FFFFFFF;
            _spu_memList[D_80033560].addr |= 0x80000000;
            D_80033560++;
            _spu_memList[D_80033560].addr = a1;
            _spu_memList[D_80033560].size = size;
        } else {
            if ((D_8003355C - 1) < D_80033560) {
                return -1;
            }
            _spu_memList[D_80033560].size = size;
            _spu_memList[D_80033560].addr &= 0x0FFFFFFF;
        }

        D_80033560++;
        _spu_memList[D_80033560].addr = (temp_t3 & 0x0FFFFFFF) + temp_t1 + size;
        _spu_memList[D_80033560].addr |= 0x40000000;
        _spu_memList[D_80033560].size = (temp_t4 - temp_t1) - size;
        _spu_gcSPU();
        return a1;
    }
    if (temp_t1 > 0) {
        if (var_a3 == size) {
            if ((D_8003355C - 2) < D_80033560) {
                return -1;
            }
        } else {
            if ((D_8003355C - 1) < D_80033560) {
                return -1;
            }
        }
        _spu_memList[arg0].size = temp_t1;
        {
            int temp_v1_3 = _spu_memList[D_80033560].addr;
            int var_a0 = _spu_memList[D_80033560].size;
            _spu_memList[D_80033560].addr = a1;
            _spu_memList[D_80033560].size = size;
            _spu_memList[D_80033560 + 1].addr = temp_v1_3;
            _spu_memList[D_80033560 + 1].size = var_a0;
            D_80033560++;
            if (var_a3 >= size) {
                u32 swapAddr = _spu_memList[D_80033560].addr;
                u32 swapSize = _spu_memList[D_80033560].size;
                _spu_memList[D_80033560].addr =
                    (temp_t3 & 0x0FFFFFFF) + temp_t1 + size;
                _spu_memList[D_80033560].addr |= 0x80000000;
                _spu_memList[D_80033560].size = var_a3 - size;
                _spu_memList[D_80033560 + 1].addr = swapAddr;
                _spu_memList[D_80033560 + 1].size = swapSize;
                D_80033560++;
            }

            _spu_gcSPU();
            return a1;
        }
    } else {
        if ((size < var_a3) && ((D_8003355C - 1) < D_80033560)) {
            return -1;
        }

        _spu_memList[arg0].size = size;
        _spu_memList[arg0].addr &= 0x0FFFFFFF;
        if (size < var_a3) {
            u32 swapAddr = _spu_memList[D_80033560].addr;
            u32 swapSize = _spu_memList[D_80033560].size;

            _spu_memList[D_80033560].addr = (temp_t3 & 0x0FFFFFFF) + size;
            _spu_memList[D_80033560].addr |= 0x80000000;
            _spu_memList[D_80033560].size = var_a3 - size;
            _spu_memList[D_80033560 + 1].addr = swapAddr;
            _spu_memList[D_80033560 + 1].size = swapSize;
            D_80033560++;
        }

        _spu_gcSPU();
        return a1;
    }

    return -1;
}

long SpuMallocWithStartAddr(unsigned long _addr, long size) {
    s32 temp_a2;
    s32 addr;
    s32 var_s2;
    s32 i;

    if (_spu_rev_reserve_wa == 0) {
        var_s2 = 0;
    } else {
        var_s2 = (0x10000 - _spu_rev_offsetaddr) << _spu_mem_mode_plus;
    }

    size += (size & ~_spu_mem_mode_unitM) ? _spu_mem_mode_unitM : 0;
    size >>= _spu_mem_mode_plus;
    size <<= _spu_mem_mode_plus;

    addr = _addr;
    addr += (addr & ~_spu_mem_mode_unitM) ? _spu_mem_mode_unitM : 0;
    addr >>= _spu_mem_mode_plus;
    addr <<= _spu_mem_mode_plus;

    if (addr < 0x1010) {
        return -1;
    }

    if (addr + size > (0x10000 << _spu_mem_mode_plus) - var_s2) {
        return -1;
    }

    if (_spu_memList[0].addr & 0x40000000) {
        temp_a2 = _spu_memList[0].size - (addr - 0x1010) - size;
        if ((addr - 0x1010) > 0) {
            if ((D_8003355C - 2) < D_80033560) {
                return -1;
            }
            _spu_memList[0].addr = 0x80001010;
            _spu_memList[0].size = addr - 0x1010;

            _spu_memList[1].addr = addr;
            _spu_memList[1].size = size;

            _spu_memList[2].addr = (addr + size) | 0x40000000;
            _spu_memList[2].size = temp_a2;

            D_80033560 = 2;
        } else {
            if ((D_8003355C - 1) < D_80033560) {
                return -1;
            }
            _spu_memList[0].addr = addr;
            _spu_memList[0].size = size;

            _spu_memList[1].addr = (addr + size) | 0x40000000;
            _spu_memList[1].size = temp_a2;

            D_80033560 = 1;
        }
        _spu_gcSPU();
        return addr;
    }

    _spu_gcSPU();
    for (i = 0; true;) {
        if (_spu_memList[i].addr & 0x80000000) {
            if (addr >= (_spu_memList[i].addr & 0x0FFFFFFF)) {
                if (addr >= (_spu_memList[i].addr & 0x0FFFFFFF) +
                                _spu_memList[i].size) {
                    if (!(_spu_memList[i + 1].addr & 0x40000000)) {
                        i++;
                        continue;
                    }
                }
                temp_a2 = _spu_memList[i].size -
                          (addr - (_spu_memList[i].addr & 0x0FFFFFFF));
                if (temp_a2 < size) {
                    i++;
                    continue;
                }
                addr = _SpuMallocSeparateTo3(i, addr, size);
                break;
            }
            temp_a2 = _spu_memList[i].size;
            if (temp_a2 < size) {
                i++;
                continue;
            }
            addr = _SpuMallocSeparateTo3(
                i, _spu_memList[i].addr & 0x0FFFFFFF, size);
            break;
        }
        if (!(_spu_memList[i].addr & 0x40000000)) {
            i++;
            continue;
        } else {
            temp_a2 = _spu_memList[i].size - var_s2;
            if (temp_a2 < size) {
                return -1;
            }

            addr = _SpuMallocSeparateTo3(
                i, _spu_memList[i].addr & 0x0FFFFFFF, size);
            break;
        }
    }

    _spu_gcSPU();
    return addr;
}
