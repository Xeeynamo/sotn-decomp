// SPDX-License-Identifier: MIT
#include "common.h"
#include "libspu_internal.h"

#ifndef VERSION_PC
long SpuMalloc(long size) {
    s32 var_s2;
    s32 var_s3;
    s32 i;

    i = 0; // why tho?
    var_s2 = -1;

    if (_spu_rev_reserve_wa == 0) {
        var_s3 = 0;
    } else {
        var_s3 = (0x10000 - _spu_rev_offsetaddr) << _spu_mem_mode_plus;
    }

    size += (size & ~_spu_mem_mode_unitM) ? _spu_mem_mode_unitM : 0;
    size >>= _spu_mem_mode_plus;
    size <<= _spu_mem_mode_plus;

    if (_spu_memList[0].addr & 0x40000000) {
        var_s2 = 0;
    } else {
        _spu_gcSPU();

        for (; i < D_8003355C; i++) {
            if (_spu_memList[i].addr & 0x40000000 ||
                (_spu_memList[i].addr & 0x80000000 &&
                 _spu_memList[i].size >= size)) {
                var_s2 = i;
                break;
            }
        }
    }

    if (var_s2 == -1)
        return -1;

    if (_spu_memList[var_s2].addr & 0x40000000) {
        if (var_s2 < D_8003355C && _spu_memList[var_s2].size - var_s3 >= size) {
            s32 next = var_s2 + 1;

            // Why the volatile?
            _spu_memList[next].addr =
                (*(volatile int*)&_spu_memList[var_s2].addr & 0x0FFFFFFF) +
                    size |
                0x40000000;
            _spu_memList[next].size = _spu_memList[var_s2].size - size;

            _spu_memList[var_s2].addr &= 0x0FFFFFFF;
            _spu_memList[var_s2].size = size;

            D_80033560 = next;
            _spu_gcSPU();

            return _spu_memList[var_s2].addr;
        }
    } else {
        if (size < _spu_memList[var_s2].size && D_80033560 < D_8003355C) {
            u32 _addr = _spu_memList[var_s2].addr + size;
            u32 _size = _spu_memList[var_s2].size - size;

            u32 swapAddr = _spu_memList[D_80033560].addr;
            u32 swapSize = _spu_memList[D_80033560].size;

            _spu_memList[D_80033560].addr = _addr | 0x80000000;
            _spu_memList[D_80033560].size = _size;

            _spu_memList[D_80033560 + 1].addr = swapAddr;
            _spu_memList[D_80033560 + 1].size = swapSize;

            D_80033560++;
        }

        _spu_memList[var_s2].size = size;
        _spu_memList[var_s2].addr &= 0x0FFFFFFF;
        _spu_gcSPU();

        return _spu_memList[var_s2].addr;
    }
    return -1;
}
#endif

void _spu_gcSPU(void) {
    s32 i, j;

    for (i = 0; i <= D_80033560;) {
        if (_spu_memList[i].addr & 0x80000000) {
            for (j = i + 1; true; j++) {
                if (_spu_memList[j].addr != 0x2FFFFFFF) {
                    break;
                }
            }
            if ((_spu_memList[j].addr & 0x80000000) &&
                ((_spu_memList[j].addr & 0x0FFFFFFF) ==
                 ((_spu_memList[i].addr & 0x0FFFFFFF) +
                  _spu_memList[i].size))) {
                _spu_memList[j].addr = 0x2FFFFFFF;
                _spu_memList[i].size += _spu_memList[j].size;
                continue;
            }
        }
        i++;
    }
    for (i = 0; i <= D_80033560; i++) {
        if (_spu_memList[i].size == 0) {
            _spu_memList[i].addr = 0x2FFFFFFF;
        }
    }
    for (i = 0; i <= D_80033560; i++) {
        if (_spu_memList[i].addr & 0x40000000) {
            break;
        }
        for (j = i + 1; j <= D_80033560; j++) {
            if (_spu_memList[j].addr & 0x40000000) {
                break;
            }
            if ((_spu_memList[j].addr & 0x0FFFFFFF) <
                (_spu_memList[i].addr & 0x0FFFFFFF)) {
                u32 swapAddr = _spu_memList[i].addr;
                u32 swapSize = _spu_memList[i].size;
                _spu_memList[i].addr = _spu_memList[j].addr;
                _spu_memList[i].size = _spu_memList[j].size;
                _spu_memList[j].addr = swapAddr;
                _spu_memList[j].size = swapSize;
            }
        }
    }
    for (i = 0; i <= D_80033560; i++) {
        if (_spu_memList[i].addr & 0x40000000) {
            break;
        }
        if (_spu_memList[i].addr == 0x2FFFFFFF) {
            _spu_memList[i].addr = _spu_memList[D_80033560].addr;
            _spu_memList[i].size = _spu_memList[D_80033560].size;
            D_80033560 = i;
            break;
        }
    }
    for (i = D_80033560 - 1; i >= 0; i--) {
        if (!(_spu_memList[i].addr & 0x80000000)) {
            break;
        }
        _spu_memList[i].addr &= 0x0FFFFFFF;
        _spu_memList[i].addr |= 0x40000000;
        _spu_memList[i].size += _spu_memList[D_80033560].size;
        D_80033560 = i;
    }
}
