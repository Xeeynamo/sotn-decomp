// SPDX-License-Identifier: MIT
#include "common.h"
#include "libspu_internal.h"

INCLUDE_ASM("main/nonmatchings/psxsdk/libspu/s_m_m", SpuMalloc);

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
