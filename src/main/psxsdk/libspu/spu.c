// SPDX-License-Identifier: MIT
#include "common.h"
#include "libspu_internal.h"
#include <psxsdk/kernel.h>
#include <psxsdk/stdarg.h>

#define WASTE_TIME()                                                           \
    sp4 = 0xD;                                                                 \
    for (sp0 = 0; sp0 < 0xF0; sp0++) {                                         \
        sp4 *= 3;                                                              \
    }

s32 _spu_reset(void) {
    volatile s32 sp0;
    volatile s32 sp4;
    u16 cnt;

    cnt = _spu_RXX->rxx.spucnt;
    _spu_RXX->rxx.spucnt = cnt & 0x7FCF;
    WASTE_TIME();
    cnt &= 0xFFCF;
    _spu_RXX->rxx.spucnt = cnt;
    return 0;
}

extern s32 D_800334FC;
extern s32* D_80033514;
extern u16 D_80033540[];
extern s32 _spu_addrMode;
extern s32 _spu_mem_mode;
extern s32 _spu_mem_mode_unit;

s32 _spu_init(s32 arg0) {
    volatile s32 sp0;
    volatile s32 sp4;
    s32 channel;

#ifdef VERSION_PC
    // dma controller write, ignore for now
#else
    *D_80033514 |= 0xB0000;
#endif
#ifdef VERSION_PC
    write_16(0x1F801D80, 0, __FILE__, __LINE__);
    write_16(0x1F801D80 + 2, 0, __FILE__, __LINE__);
    write_16(0x1F801DAA, 0, __FILE__, __LINE__);
#else
    _spu_RXX->rxx.main_vol.left = 0;
    _spu_RXX->rxx.main_vol.right = 0;
    _spu_RXX->rxx.spucnt = 0;
#endif
    _spu_transMode = 0;
    _spu_addrMode = 0;
    _spu_tsa = 0;
    WASTE_TIME();
#ifdef VERSION_PC
    write_16(0x1F801D80 + 0, 0, __FILE__, __LINE__);
    write_16(0x1F801D80 + 2, 0, __FILE__, __LINE__);
#else
    _spu_RXX->rxx.main_vol.left = 0;
    _spu_RXX->rxx.main_vol.right = 0;
#endif
    D_800334FC = 0;
#ifdef VERSION_PC
    while (read_16(0x1AA, __FILE__, __LINE__) & 0x7FF) {
#else
    while (_spu_RXX->rxx.spustat & 0x7FF) {
#endif
        if (++D_800334FC > 5000) {
            printf("SPU:T/O [%s]\n", "wait (reset)");
            break;
        }
    }
    _spu_mem_mode = 2;
    _spu_mem_mode_plus = 3;
    _spu_mem_mode_unit = 8;
    _spu_mem_mode_unitM = 7;
#ifdef VERSION_PC
    write_16(0x1F801DAC, 4, __FILE__, __LINE__);
    write_16(0x1F801D84, 0, __FILE__, __LINE__);
    write_16(0x1F801D86, 0, __FILE__, __LINE__);
    write_16(0x1F801D8C, 0xffff, __FILE__, __LINE__);
    write_16(0x1F801D8E, 0xffff, __FILE__, __LINE__);
    write_16(0x1F801D98, 0, __FILE__, __LINE__);
    write_16(0x1F801D98 + 2, 0, __FILE__, __LINE__);
#else
    _spu_RXX->rxx.data_trans = 4;
    _spu_RXX->rxx.rev_vol.left = 0;
    _spu_RXX->rxx.rev_vol.right = 0;
    _spu_RXX->rxx.key_off[0] = 0xFFFF;
    _spu_RXX->rxx.key_off[1] = 0xFFFF;
    _spu_RXX->rxx.rev_mode[0] = 0;
    _spu_RXX->rxx.rev_mode[1] = 0;
#endif
    if (arg0 == 0) {
#ifdef VERSION_PC
        write_16(0x1F801D90 + 0, 0, __FILE__, __LINE__);
        write_16(0x1F801D90 + 2, 0, __FILE__, __LINE__);
        write_16(0x1F801D94 + 0, 0, __FILE__, __LINE__);
        write_16(0x1F801D94 + 2, 0, __FILE__, __LINE__);
        write_16(0x1F801DB0 + 0, 0, __FILE__, __LINE__);
        write_16(0x1F801DB0 + 2, 0, __FILE__, __LINE__);
        write_16(0x1F801DB4 + 0, 0, __FILE__, __LINE__);
        write_16(0x1F801DB4 + 2, 0, __FILE__, __LINE__);
#else
        _spu_RXX->rxx.chan_fm[0] = 0;
        _spu_RXX->rxx.chan_fm[1] = 0;
        _spu_RXX->rxx.noise_mode[0] = 0;
        _spu_RXX->rxx.noise_mode[1] = 0;
        _spu_RXX->rxx.cd_vol.left = 0;
        _spu_RXX->rxx.cd_vol.right = 0;
        _spu_RXX->rxx.ex_vol.left = 0;
        _spu_RXX->rxx.ex_vol.right = 0;
#endif
        _spu_tsa = 0x200;
        _spu_writeByIO((u8*)&D_80033540[0], 0x10);
        for (channel = 0; channel < NUM_SPU_CHANNELS; channel++) {
#ifdef VERSION_PC
            write_16(0x1F801C00 + channel * 16 + 0, 0, __FILE__, __LINE__);
            write_16(0x1F801C00 + channel * 16 + 2, 0, __FILE__, __LINE__);
            write_16(0x1F801C00 + channel * 16 + 4, 0x3fff, __FILE__, __LINE__);
            write_16(0x1F801C00 + channel * 16 + 6, 0x200, __FILE__, __LINE__);
            write_16(0x1F801C00 + channel * 16 + 8, 0, __FILE__, __LINE__);
            write_16(0x1F801C00 + channel * 16 + 10, 0, __FILE__, __LINE__);
#else
            _spu_RXX->rxx.voice[channel].volume.left = 0;
            _spu_RXX->rxx.voice[channel].volume.right = 0;
            _spu_RXX->rxx.voice[channel].pitch = 0x3fff;
            _spu_RXX->rxx.voice[channel].addr = 0x200;
            _spu_RXX->rxx.voice[channel].adsr[0] = 0;
            _spu_RXX->rxx.voice[channel].adsr[1] = 0;
#endif
        }
#ifdef VERSION_PC
        s32 temp = read_16(0x1F801D88, __FILE__, __LINE__);
        write_16(0x1F801D88 + 0, 0xFFFF, __FILE__, __LINE__);
        s32 temp2 = read_16(0x1F801D88 + 2, __FILE__, __LINE__);
        write_16(0x1F801D88 + 2, temp2 | 0xFF, __FILE__, __LINE__);
#else
        _spu_RXX->rxx.key_on[0] |= 0xFFFF;
        _spu_RXX->rxx.key_on[1] |= 0xFF;
#endif
        WASTE_TIME();
        WASTE_TIME();
        WASTE_TIME();
        WASTE_TIME();
#ifdef VERSION_PC
        temp = read_16(0x1F801D8C, __FILE__, __LINE__);
        write_16(0x1F801D8C + 0, 0xFFFF, __FILE__, __LINE__);
        temp2 = read_16(0x1F801D8C + 2, __FILE__, __LINE__);
        write_16(0x1F801D8C + 2, temp2 | 0xFF, __FILE__, __LINE__);
#else
        _spu_RXX->rxx.key_off[0] |= 0xFFFF;
        _spu_RXX->rxx.key_off[1] |= 0xFF;
#endif
        WASTE_TIME();
        WASTE_TIME();
        WASTE_TIME();
        WASTE_TIME();
    }
    _spu_inTransfer = 1;
#ifdef VERSION_PC
    write_16(0x1F801DAA, 0xC000, __FILE__, __LINE__);
#else
    _spu_RXX->rxx.spucnt = 0xC000;
#endif
    _spu_transferCallback = NULL;
    _spu_IRQCallback = NULL;
    return 0;
}

s32 _spu_writeByIO(u8* addr, u32 size) {
    volatile s32 sp0;
    volatile s32 sp4;
    u16 spustat;
    s32 num_to_trans;
    u16* cur_pos;
    s32 spustat_cur;
    s32 i;
    u16 cnt;

    cur_pos = addr;
#ifdef VERSION_PC
    spustat = read_16(0x1F801DAE, __FILE__, __LINE__) & 0x7FF;
    write_16(0x1F801DA6, _spu_tsa, __FILE__, __LINE__);
#else
    spustat = _spu_RXX->rxx.spustat & 0x7FF;
    _spu_RXX->rxx.trans_addr = _spu_tsa;
#endif
    WASTE_TIME();
    while (size != 0) {
        num_to_trans = (size > 0x40) ? 0x40 : size;
        for (i = 0; i < num_to_trans; i += 2) {
#ifndef VERSION_PC
            _spu_RXX->rxx.trans_fifo = *cur_pos++;
#else
            write_16(0x1F801DA8, *cur_pos++, __FILE__, __LINE__);
#endif
        }
#ifndef VERSION_PC
        cnt = _spu_RXX->rxx.spucnt;
        cnt &= ~0x30;
        cnt |= 0x10;
        _spu_RXX->rxx.spucnt = cnt;
#else
        cnt = read_16(0x1F801DAA, __FILE__, __LINE__);
        cnt &= ~0x30;
        cnt |= 0x10;
        write_16(0x1F801DAA, cnt, __FILE__, __LINE__);
#endif
        WASTE_TIME();
        D_800334FC = 0;
#ifndef VERSION_PC
        while (_spu_RXX->rxx.spustat & 0x400) {
#else
        while (read_16(0x1ae, __FILE__, __LINE__) & 0x400) {
#endif
            D_800334FC++;
            if (D_800334FC > 5000) {
                printf("SPU:T/O [%s]\n", "wait (wrdy H -> L)");
                break;
            }
        }
        WASTE_TIME();
        WASTE_TIME();
        size -= num_to_trans;
    }
#ifndef VERSION_PC
    cnt = _spu_RXX->rxx.spucnt;
    cnt &= ~0x30;
    _spu_RXX->rxx.spucnt = cnt;
    D_800334FC = 0;
    spustat_cur = _spu_RXX->rxx.spustat & 0x7FF;
#else
    cnt = read_16(0x1F801DAA, __FILE__, __LINE__);
    cnt &= ~0x30;
    write_16(0x1F801DAA, cnt, __FILE__, __LINE__);
    D_800334FC = 0;
    spustat_cur = read_16(0x1ae, __FILE__, __LINE__) & 0x7FF;
#endif
// ignore this busy loop for now
#ifndef VERSION_PC
    while (spustat_cur != spustat) {
        D_800334FC++;
        if (D_800334FC > 5000) {
            printf("SPU:T/O [%s]\n", "wait (dmaf clear/W)");
            return;
        }
        spustat_cur = _spu_RXX->rxx.spustat & 0x7FF;
    }
#endif
    return spustat_cur;
}

void _spu_FiDMA(void) {
    volatile s32 sp0;
    volatile s32 sp4;
    s32 i;

    if (D_80033550 == 0) {
        WASTE_TIME();
        WASTE_TIME();
        WASTE_TIME();
    }

    _spu_RXX->rxx.spucnt &= 0xFFCF;

    i = 0;
    while (_spu_RXX->rxx.spucnt & 0x30) {
        if (++i > 0xF00) {
            break;
        }
    }

    if (_spu_transferCallback) {
        _spu_transferCallback();
        return;
    }
    DeliverEvent(HwSPU, EvSpCOMP);
}

extern s32* D_80033508;
extern s32* D_8003350C;
extern s32* D_80033510;
extern s32* D_80033518;
extern s32 D_80033550;
extern s32 D_80033554;
extern s32 D_80033558;

static inline void _spu_FsetDelayW(void) {
    *D_80033518 = (*D_80033518 & 0xF0FFFFFF) | 0x20000000;
}

static inline void _spu_FsetDelayR(void) {
    *D_80033518 = (*D_80033518 & 0xF0FFFFFF) | 0x22000000;
}

void _spu_r_(s32 arg0, u16 arg1, s32 arg2) {
    volatile s32 sp0;
    volatile s32 sp4;

    _spu_RXX->rxx.trans_addr = arg1;

    WASTE_TIME();
    WASTE_TIME();

    _spu_RXX->rxx.spucnt |= 0x30;

    WASTE_TIME();
    WASTE_TIME();

    _spu_FsetDelayR();
    *D_80033508 = arg0;
    *D_8003350C = (arg2 << 0x10) | 0x10;
    D_80033550 = 1;
    *D_80033510 = 0x01000200;
}

#ifndef VERSION_PC
s32 _spu_t(s32 arg0, ...) {
    s32 var_a2;
    s32 i;
    u32 addr;
    va_list args;
    u32 count;
    u16 ck2;
    u16 cnt;

    va_start(args, arg0);

    switch (arg0) {
    case 2:
        count = va_arg(args, u32);
        _spu_tsa = count >> _spu_mem_mode_plus;
        _spu_RXX->rxx.trans_addr = _spu_tsa;
        break;

    case 1:
        D_80033550 = 0;
        i = 0;
        while (_spu_RXX->rxx.trans_addr != _spu_tsa) {
            if (++i > 0xF00) {
                return -2;
            }
        }

        cnt = _spu_RXX->rxx.spucnt;
        cnt &= ~0x30;
        cnt |= 0x20;
        _spu_RXX->rxx.spucnt = cnt;
        break;

    case 0:
        D_80033550 = 1;

        i = 0;
        while (_spu_RXX->rxx.trans_addr != _spu_tsa) {
            if (++i > 0xF00) {
                return -2;
            }
        }

        cnt = _spu_RXX->rxx.spucnt;
        cnt &= ~0x30;
        cnt |= 0x30;
        _spu_RXX->rxx.spucnt = cnt;
        break;

    case 3:
        if (D_80033550 == 1) {
            ck2 = 0x30;
        } else {
            ck2 = 0x20;
        }

        i = 0;
        while ((_spu_RXX->rxx.spucnt & 0x30) != ck2) {
            if (++i > 0xF00) {
                return -2;
            }
        }

        if (D_80033550 == 1) {
            _spu_FsetDelayR();
        } else {
            _spu_FsetDelayW();
        }

        count = va_arg(args, u32);
        D_80033554 = count;
        count = va_arg(args, u32);
        D_80033558 = (count / 64);
        D_80033558 += ((count % 64) ? 1 : 0);
        *D_80033508 = D_80033554;
        *D_8003350C = (D_80033558 << 0x10) | 0x10;
        if (D_80033550 == 1) {
            var_a2 = 0x01000200;
        } else {
            var_a2 = 0x01000201;
        }
        *D_80033510 = var_a2;
        break;
    }
    return 0;
}
#endif

s32 _spu_write(u8* arg0, u32 size) {

    if (_spu_transMode != 0) {
        _spu_writeByIO(arg0, size);
        return size;
    }
    _spu_t(2, _spu_tsa << _spu_mem_mode_plus);
    _spu_t(1);
    _spu_t(3, arg0, size);
    return size;
}

s32 _spu_read(s32 arg0, u32 size) {
    _spu_t(2, _spu_tsa << _spu_mem_mode_plus);
    _spu_t(0);
    _spu_t(3, arg0, size);
    return size;
}

void _spu_FsetRXX(s32 arg0, u32 arg1, s32 arg2) {
    if (arg2 == 0) {
#ifdef VERSION_PC
        write_16(0x1F801C00 + arg0 * 2, arg1, __FILE__, __LINE__);
#else
        _spu_RXX->raw[arg0] = arg1;
#endif
        return;
    }

    _spu_RXX->raw[arg0] = arg1 >> _spu_mem_mode_plus;
}

u32 _spu_FsetRXXa(s32 arg0, u32 arg1) {
    u32 temp_a3;
    u32 var_a1;

    var_a1 = arg1;
    if ((_spu_mem_mode != 0) && ((var_a1 % _spu_mem_mode_unit) != 0)) {
        var_a1 += _spu_mem_mode_unit;
        var_a1 &= ~_spu_mem_mode_unitM;
    }
    temp_a3 = var_a1 >> _spu_mem_mode_plus;

    switch (arg0) {
    case -1:
        return temp_a3 & 0xFFFF;
    case -2:
        return var_a1;
    default:
        _spu_RXX->raw[arg0] = temp_a3;
        return var_a1;
    }
}

u32 _spu_FgetRXXa(s32 arg0, s32 arg1) {
    u16 temp = _spu_RXX->raw[arg0];
    if (arg1 == -1) {
        return temp;
    } else {
        return temp << _spu_mem_mode_plus;
    }
}
