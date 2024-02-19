#include "common.h"
#include "libspu_internal.h"

#define WASTE_TIME()                                                           \
    sp4 = 0xD;                                                                 \
    for (sp0 = 0; sp0 < 0xF0; sp0++) {                                         \
        sp4 *= 3;                                                              \
    }

s32 _spu_reset(void) {
    volatile s32 sp0;
    volatile s32 sp4;
    u16 temp_a0;
    volatile s16* spucnt = &_spu_RXX->rxx.spucnt;

    temp_a0 = _spu_RXX->rxx.spucnt;
    *spucnt = temp_a0 & 0x7FCF;
    WASTE_TIME();
    temp_a0 &= 0xFFCF;
    _spu_RXX->rxx.spucnt = temp_a0;
    return 0;
}

extern s32 D_80010CEC;
extern s32 D_800334FC;
extern s32* D_80033514;
extern s32 D_80033540;
extern s32 _spu_addrMode;
extern s32 _spu_mem_mode;
extern s32 _spu_mem_mode_unit;
extern s32 _spu_mem_mode_unitM;
extern s32 aWaitReset;

s32 _spu_init(s32 arg0) {
    volatile s32 sp0;
    volatile s32 sp4;
    s32 wait_count;
    s32 channel;
    s16 temp;

    *D_80033514 |= 0xB0000;
    _spu_RXX->rxx.main_vol.left = 0;
    _spu_RXX->rxx.main_vol.right = 0;
    _spu_RXX->rxx.spucnt = 0;
    _spu_transMode = 0;
    _spu_addrMode = 0;
    _spu_tsa = 0;
    WASTE_TIME();
    _spu_RXX->rxx.main_vol.left = 0;
    _spu_RXX->rxx.main_vol.right = 0;
    D_800334FC = 0;
    if (_spu_RXX->rxx.spustat & 0x7FF) {
        do {
            wait_count = D_800334FC + 1;
            D_800334FC = wait_count;
            if (wait_count > 5000) {
                printf(&D_80010CEC, &aWaitReset);
                break;
            }
        } while (_spu_RXX->rxx.spustat & 0x7FF);
    }
    _spu_mem_mode = 2;
    _spu_mem_mode_plus = 3;
    _spu_mem_mode_unit = 8;
    _spu_mem_mode_unitM = 7;
    _spu_RXX->rxx.data_trans = 4;
    _spu_RXX->rxx.rev_vol.left = 0;
    _spu_RXX->rxx.rev_vol.right = 0;
    _spu_RXX->rxx.key_off[0] = 0xFFFF;
    _spu_RXX->rxx.key_off[1] = 0xFFFF;
    _spu_RXX->rxx.rev_mode[0] = 0;
    _spu_RXX->rxx.rev_mode[1] = 0;
    if (arg0 == 0) {
        _spu_RXX->rxx.chan_fm[0] = 0;
        _spu_RXX->rxx.chan_fm[1] = 0;
        _spu_RXX->rxx.noise_mode[0] = 0;
        _spu_RXX->rxx.noise_mode[1] = 0;
        _spu_RXX->rxx.cd_vol.left = 0;
        _spu_RXX->rxx.cd_vol.right = 0;
        _spu_RXX->rxx.ex_vol.left = 0;
        _spu_RXX->rxx.ex_vol.right = 0;
        _spu_tsa = 0x200;
        _spu_writeByIO((s32)&D_80033540, 0x10);
        for (channel = 0; channel < NUM_SPU_CHANNELS; channel++) {
            _spu_RXX->raw[channel * 8 + 0] = 0;      /* left volume */
            _spu_RXX->raw[channel * 8 + 1] = 0;      /* right volume */
            _spu_RXX->raw[channel * 8 + 2] = 0x3fff; /* pitch */
            _spu_RXX->raw[channel * 8 + 3] = 0x200;  /* addr */
            _spu_RXX->raw[channel * 8 + 4] = 0;      /* adsr1 */
            _spu_RXX->raw[channel * 8 + 5] = 0;      /* adsr2 */
        }
        temp = _spu_RXX->rxx.key_on[0];
        _spu_RXX->rxx.key_on[0] = 0xFFFF;
        _spu_RXX->rxx.key_on[1] |= 0xFF;
        WASTE_TIME();
        WASTE_TIME();
        WASTE_TIME();
        WASTE_TIME();
        temp = _spu_RXX->rxx.key_off[0];
        _spu_RXX->rxx.key_off[0] = 0xFFFF;
        _spu_RXX->rxx.key_off[1] |= 0xFF;
        WASTE_TIME();
        WASTE_TIME();
        WASTE_TIME();
        WASTE_TIME();
    }
    _spu_inTransfer = 1;
    _spu_RXX->rxx.spucnt = 0xC000;
    _spu_transferCallback = NULL;
    _spu_IRQCallback = NULL;
    return 0;
}

INCLUDE_ASM("main/nonmatchings/psxsdk/libspu/spu", _spu_writeByIO);

void _spu_FiDMA(void) {
    volatile s32 sp0;
    volatile s32 sp4;
    s32 var_v1;
    volatile SPU_RXX* rxx;

    if (D_80033550 == 0) {
        WASTE_TIME();
        WASTE_TIME();
        WASTE_TIME();
    }

    rxx = &_spu_RXX->rxx;
    rxx->spucnt &= 0xFFCF;

    for (var_v1 = 0; rxx->spucnt & 0x30; var_v1++) {
        if (var_v1 + 1 > 0xF00) {
            break;
        }
    }

    if (_spu_transferCallback) {
        _spu_transferCallback();
        return;
    }
    DeliverEvent(0xF0000009U, 0x20U);
}

extern s32* D_80033508;
extern s32* D_8003350C;
extern s32* D_80033510;
extern s32* D_80033518;
extern s32 D_80033550;

void _spu_r_(s32 arg0, u16 arg1, s32 arg2) {
    volatile s32 sp0;
    volatile s32 sp4;
    _spu_RXX->rxx.trans_addr = arg1;
    WASTE_TIME();
    WASTE_TIME();

    _spu_RXX->rxx.spucnt |= 0x30;
    do {
        WASTE_TIME();
    } while (0);

    WASTE_TIME();
    *D_80033518 = (*D_80033518 & 0xF0FFFFFF) | 0x22000000;
    *D_80033508 = arg0;
    *D_8003350C = (arg2 << 0x10) | 0x10;
    D_80033550 = 1;
    *D_80033510 = 0x01000200;
}

INCLUDE_ASM("main/nonmatchings/psxsdk/libspu/spu", _spu_t);

s32 _spu_write(u32 arg0, u32 arg1) {

    if (_spu_transMode != 0) {
        _spu_writeByIO(arg0, arg1);
        return arg1;
    }
    _spu_t(2, _spu_tsa << _spu_mem_mode_plus);
    _spu_t(1);
    _spu_t(3, arg0, arg1);
    return arg1;
}

s32 _spu_read(s32 arg0, s32 arg1) {
    s32 temp = _spu_tsa << _spu_mem_mode_plus;
    _spu_t(2, temp);
    _spu_t(0);
    _spu_t(3, arg0, arg1);
    return arg1;
}

void _spu_FsetRXX(s32 arg0, u32 arg1, s32 arg2) {
    if (arg2 == 0) {
        _spu_RXX->raw[arg0] = arg1;
        return;
    }

    _spu_RXX->raw[arg0] = (arg1 >> _spu_mem_mode_plus);
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
    s32 temp2;
    if (arg1 == -1) {
        return temp;
    }
    return temp << _spu_mem_mode_plus;
}
