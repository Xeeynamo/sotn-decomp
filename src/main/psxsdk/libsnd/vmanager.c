// SPDX-License-Identifier: MIT
#include "common.h"
#include "libsnd_i.h"

struct _ss_spu_vm_rec_struct {
    u32 pad[2];
    u32 D_8003BD50;
};

static u16* D_80032F10 = (u16*)0x1F801C00;
static u16 D_80032F14[] = {
    0x1000, 0x100E, 0x101D, 0x102C, 0x103B, 0x104A, 0x1059, 0x1068, 0x1078,
    0x1087, 0x1096, 0x10A5, 0x10B5, 0x10C4, 0x10D4, 0x10E3, 0x10F3, 0x1103,
    0x1113, 0x1122, 0x1132, 0x1142, 0x1152, 0x1162, 0x1172, 0x1182, 0x1193,
    0x11A3, 0x11B3, 0x11C4, 0x11D4, 0x11E5, 0x11F5, 0x1206, 0x1216, 0x1227,
    0x1238, 0x1249, 0x125A, 0x126B, 0x127C, 0x128D, 0x129E, 0x12AF, 0x12C1,
    0x12D2, 0x12E3, 0x12F5, 0x1306, 0x1318, 0x132A, 0x133C, 0x134D, 0x135F,
    0x1371, 0x1383, 0x1395, 0x13A7, 0x13BA, 0x13CC, 0x13DE, 0x13F1, 0x1403,
    0x1416, 0x1428, 0x143B, 0x144E, 0x1460, 0x1473, 0x1486, 0x1499, 0x14AC,
    0x14BF, 0x14D3, 0x14E6, 0x14F9, 0x150D, 0x1520, 0x1534, 0x1547, 0x155B,
    0x156F, 0x1583, 0x1597, 0x15AB, 0x15BF, 0x15D3, 0x15E7, 0x15FB, 0x1610,
    0x1624, 0x1638, 0x164D, 0x1662, 0x1676, 0x168B, 0x16A0, 0x16B5, 0x16CA,
    0x16DF, 0x16F4, 0x170A, 0x171F, 0x1734, 0x174A, 0x175F, 0x1775, 0x178B,
    0x17A1, 0x17B6, 0x17CC, 0x17E2, 0x17F9, 0x180F, 0x1825, 0x183B, 0x1852,
    0x1868, 0x187F, 0x1896, 0x18AC, 0x18C3, 0x18DA, 0x18F1, 0x1908, 0x191F,
    0x1937, 0x194E, 0x1965, 0x197D, 0x1995, 0x19AC, 0x19C4, 0x19DC, 0x19F4,
    0x1A0C, 0x1A24, 0x1A3C, 0x1A55, 0x1A6D, 0x1A85, 0x1A9E, 0x1AB7, 0x1ACF,
    0x1AE8, 0x1B01, 0x1B1A, 0x1B33, 0x1B4C, 0x1B66, 0x1B7F, 0x1B98, 0x1BB2,
    0x1BCC, 0x1BE5, 0x1BFF, 0x1C19, 0x1C33, 0x1C4D, 0x1C67, 0x1C82, 0x1C9C,
    0x1CB7, 0x1CD1, 0x1CEC, 0x1D07, 0x1D22, 0x1D3D, 0x1D58, 0x1D73, 0x1D8E,
    0x1DA9, 0x1DC5, 0x1DE0, 0x1DFC, 0x1E18, 0x1E34, 0x1E50, 0x1E6C, 0x1E88,
    0x1EA4, 0x1EC1, 0x1EDD, 0x1EFA, 0x1F16, 0x1F33, 0x1F50, 0x1F6D, 0x1F8A,
    0x1FA7, 0x1FC5, 0x1FE2, 0x2000};

extern struct _ss_spu_vm_rec_struct _ss_spu_vm_rec;
extern s16 _svm_vcf;
extern s16 _svm_orev1;
extern s16 _svm_orev2;
extern u8 _svm_auto_kof_mode;
extern s32 _svm_envx_hist[];
extern s32 D_8003BD08;

static inline u16 get_field_0x1a() { return _svm_cur.field_0x1a; }

u8 SpuVmAlloc(s32 arg0) {
    u8 var_t2;
    u16 var_t0;
    u16 var_t3;
    u8 cur_voice;
    u8 channel;
    u8 var_t1;
    u16 prior;

    channel = 99;
    var_t3 = -1;
    var_t2 = 0;
    var_t0 = 0;
    prior = _svm_cur.field_F_prior;
    var_t1 = 99;
    for (cur_voice = 0; cur_voice < spuVmMaxVoice; cur_voice++) {
        if (_svm_voice[cur_voice].unk1b == 0 &&
            _svm_voice[cur_voice].unk6 == 0) {
            channel = cur_voice;
            break;
        }
        if (_svm_voice[cur_voice].unk18 < prior) {
            prior = _svm_voice[cur_voice].unk18;
            var_t1 = cur_voice;
            var_t3 = _svm_voice[cur_voice].unk6;
            var_t0 = _svm_voice[cur_voice].unk2;
            var_t2 = 1;
        } else if (_svm_voice[cur_voice].unk18 == prior) {
            var_t2 += 1;
            if (_svm_voice[cur_voice].unk6 < var_t3) {
                var_t0 = _svm_voice[cur_voice].unk2;
                var_t3 = _svm_voice[cur_voice].unk6;
                var_t1 = cur_voice;
            } else if (_svm_voice[cur_voice].unk6 == var_t3) {
                if (var_t0 < _svm_voice[cur_voice].unk2) {
                    var_t0 = _svm_voice[cur_voice].unk2;
                    var_t1 = cur_voice;
                }
            }
        }
    }
    if (channel == 99) {
        if (var_t2 == 0) {
            channel = spuVmMaxVoice;
        } else {
            channel = var_t1;
        }
    }
    if (channel < spuVmMaxVoice) {
        for (cur_voice = 0; cur_voice < spuVmMaxVoice; cur_voice++) {
            _svm_voice[cur_voice].unk2++;
        }
        _svm_voice[channel].unk2 = 0;
        _svm_voice[channel].unk18 = _svm_cur.field_F_prior;
        if (_svm_voice[channel].unk1b == 2) {
            SpuSetNoiseVoice(0, 0xFFFFFF);
        }
    }
    return channel;
}

#ifndef VERSION_PC
void SpuVmKeyOnNow(u8 vagCount, u16 arg2) {
    struct SeqStruct* score =
        &_ss_score[_svm_cur.field_16_vag_idx & 0xFF]
                  [(_svm_cur.field_16_vag_idx & 0xFF00) >> 8];
    u16 pos;
    u16 bitsUpper;
    u16 bitsLower;
    u32 voll, volr;
    u32 voll_t, volr_t;
    s32 mvol_scaled;

    pos = _svm_cur.field_0x1a * 8;
    mvol_scaled = _svm_vh->mvol * 0x3FFF;
    voll_t = ((_svm_cur.field_4_voll * mvol_scaled) / 0x7F) / 0x7F;
    voll_t =
        ((voll_t * _svm_cur.field_A_mvol * _svm_cur.field_D_vol) / 0x7F) / 0x7F;
    volr_t = voll_t;

    if (_svm_cur.field_16_vag_idx != 0x21) {
        voll_t = (voll_t * score->unk74) / 0x7F;
        volr_t = (volr_t * score->unk76) / 0x7F;
    }

    if (_svm_cur.field_E_pan < 0x40) {
        voll = voll_t;
        volr = (volr_t * _svm_cur.field_E_pan) / 0x3F;
    } else {
        voll = (voll_t * (0x7F - _svm_cur.field_E_pan)) / 0x3F;
        volr = volr_t;
    }
    if (_svm_cur.field_B_mpan < 0x40) {
        volr = (volr * _svm_cur.field_B_mpan) / 0x3F;
    } else {
        voll = (voll * (0x7F - _svm_cur.field_B_mpan)) / 0x3F;
    }
    if (_svm_cur.field_0x5 < 0x40) {
        volr = (volr * _svm_cur.field_0x5) / 0x3F;
    } else {
        voll = (voll * (0x7F - _svm_cur.field_0x5)) / 0x3F;
    }
    if (_svm_stereo_mono == 1) {
        if (voll < volr) {
            voll = volr;
        } else {
            volr = voll;
        }
    }

    voll = (voll * voll) / 0x3FFF;
    volr = (volr * volr) / 0x3FFF;

    _svm_sreg_buf[pos + 2] = arg2;
    _svm_sreg_buf[pos + 0] = voll;
    _svm_sreg_buf[pos + 1] = volr;
    _svm_sreg_dirty[_svm_cur.field_0x1a] |= 7;

    _svm_voice[_svm_cur.field_0x1a].unk04 = arg2;
    _svm_voice[_svm_cur.field_0x1a].unk1b = 1;
    if (_svm_cur.field_0x1a < 0x10) {
        bitsLower = 1 << _svm_cur.field_0x1a;
        bitsUpper = 0;
    } else {
        bitsLower = 0;
        bitsUpper = 1 << (_svm_cur.field_0x1a - 0x10);
    }
    if (_svm_cur.field_14_seq_sep_no & 4) {
        _svm_orev1 |= bitsLower;
        _svm_orev2 |= bitsUpper;
    } else {
        _svm_orev1 &= ~bitsLower;
        _svm_orev2 &= ~bitsUpper;
    }
    _svm_okon1 |= bitsLower;
    _svm_okon2 |= bitsUpper;

    _svm_okof1 &= ~_svm_okon1;
    _svm_okof2 &= ~_svm_okon2;
}
#endif

void SpuVmDoAllocate(void) {
    s32 i;

    _svm_cur.field_0x1c = _svm_cur.field_0x1a * 8;
    _svm_cur.field_0x1e =
        _svm_cur.field_C_vag_idx + (_svm_cur.field_7_fake_program * 0x10);
    _svm_voice[_svm_cur.field_0x1a].unk6 = 0x7FFF;
    for (i = 0; i < 0x10; i++) {
        _svm_envx_hist[i] &= ~(1 << _svm_cur.field_0x1a);
    }
    if ((_svm_cur.field_18_voice_idx & 1) > 0) {
        _svm_sreg_buf[_svm_cur.field_0x1c + 3] =
            _svm_pg[(_svm_cur.field_18_voice_idx - 1) / 2].reserved2;
        _svm_sreg_dirty[_svm_cur.field_0x1a] |= 8;
    } else {
        _svm_sreg_buf[_svm_cur.field_0x1c + 3] =
            _svm_pg[(_svm_cur.field_18_voice_idx - 1) / 2].reserved3;
        _svm_sreg_dirty[_svm_cur.field_0x1a] |= 8;
    }

    _svm_sreg_buf[_svm_cur.field_0x1c + 4] =
        _svm_tn[(_svm_cur.field_7_fake_program * 0x10) +
                _svm_cur.field_C_vag_idx]
            .adsr1;
    _svm_sreg_buf[_svm_cur.field_0x1c + 5] =
        _svm_tn[(_svm_cur.field_7_fake_program * 0x10) +
                _svm_cur.field_C_vag_idx]
            .adsr2 +
        _svm_damper;
    _svm_sreg_dirty[_svm_cur.field_0x1a] |= 0x30;
}

void vmNoiseOn(u8 arg0) {
    struct SeqStruct* score =
        &_ss_score[_svm_cur.field_16_vag_idx & 0xFF]
                  [(_svm_cur.field_16_vag_idx & 0xFF00) >> 8];
    s16 voice;
    u16 bitsUpper;
    u16 bitsLower;
    u32 voll_t, volr_t;
    u32 voll, volr;
    u16 cnd;
    u32 temp;

    cnd = D_80032F10[0x1AA / 2];

    voll_t = score->unk74 * 0x81;
    volr_t = score->unk76 * 0x81;

    voll_t = (voll_t * _svm_cur.field_A_mvol) / 0x7F;
    volr_t = (volr_t * _svm_cur.field_A_mvol) / 0x7F;

    voll_t = (voll_t * _svm_cur.field_D_vol) / 0x7F;
    volr_t = (volr_t * _svm_cur.field_D_vol) / 0x7F;

    temp = _svm_cur.field_E_pan;
    if (temp < 0x40) {
        voll = voll_t;
        volr = (volr_t * temp) / 0x3F;
    } else {
        voll = (voll_t * (0x7F - temp)) / 0x3F;
        volr = volr_t;
    }
    temp = _svm_cur.field_B_mpan;
    if (temp < 0x40) {
        volr = (volr * temp) / 0x3F;
    } else {
        voll = (voll * (0x7F - temp)) / 0x3F;
    }
    temp = _svm_cur.field_0x5;
    if (temp < 0x40) {
        volr = (temp * volr) / 0x3F;
    } else {
        voll = (voll * (0x7F - temp)) / 0x3F;
    }

    if (_svm_stereo_mono == 1) {
        if (voll < volr) {
            voll = volr;
        } else {
            volr = voll;
        }
    }

    cnd &= ~0x3F00;
    cnd |= ((_svm_cur.field_2_note - _svm_cur.field_10_centre) & 0x3F) << 8;
    D_80032F10[0x1AA / 2] = cnd;

    _svm_sreg_buf[arg0 * 8 + 0] = voll;
    _svm_sreg_buf[arg0 * 8 + 1] = volr;
    _svm_sreg_dirty[arg0] |= 3;
    if (arg0 < 0x10) {
        bitsLower = 1 << arg0;
        bitsUpper = 0;
    } else {
        bitsLower = 0;
        bitsUpper = 1 << (arg0 - 0x10);
    }
    _svm_voice[arg0].unk04 = 0xA;
    for (voice = 0; voice < spuVmMaxVoice; voice++) {
        _svm_voice[voice].unk1b &= 1;
    }
    _svm_voice[arg0].unk1b = 2;

    _svm_okon1 |= bitsLower;
    _svm_okon2 |= bitsUpper;

    _svm_okof1 &= ~_svm_okon1;
    _svm_okof2 &= ~_svm_okon2;

    if (_svm_cur.field_14_seq_sep_no & 4) {
        _svm_orev1 |= bitsLower;
        _svm_orev2 |= bitsUpper;
    } else {
        _svm_orev1 &= ~bitsLower;
        _svm_orev2 &= ~bitsUpper;
    }

    D_80032F10[0x194 / 2] = bitsLower;
    D_80032F10[0x196 / 2] = bitsUpper;
}

void vmNoiseOn2(u8 voice, u16 arg1, u16 arg2, u16 arg3, u16 arg4) {
    u16 i;
    u16 bitsUpper;
    u16 bitsLower;

    _svm_sreg_buf[voice * 8 + 0] = arg1;
    _svm_sreg_buf[voice * 8 + 1] = arg2;
    _svm_sreg_dirty[voice] |= 3;

    if (voice < 0x10) {
        bitsLower = 1 << voice;
        bitsUpper = 0;
    } else {
        bitsLower = 0;
        bitsUpper = 1 << (voice - 0x10);
    }

    _svm_voice[voice].unk04 = 0xA;
    for (i = 0; i < spuVmMaxVoice; i++) {
        _svm_voice[i].unk1b &= 1;
    }
    _svm_voice[voice].unk1b = 2;
    _svm_voice[voice].unk2 = 0;

    _svm_okon1 |= bitsLower;
    _svm_okon2 |= bitsUpper;

    _svm_okof1 &= ~_svm_okon1;
    _svm_okof2 &= ~_svm_okon2;
    D_80032F10[0x194 / 2] = bitsLower;
    D_80032F10[0x196 / 2] = bitsUpper;
}

u16 note2pitch() {
    s16 new_var;
    s16 octave;
    s16 pos;

    u16 var_a2;
    u16 var_v1;

    new_var = (_svm_cur.field_2_note + 60) - _svm_cur.field_10_centre;
    octave = new_var / 12;
    pos = new_var % 12;

    var_a2 = _svm_cur.field_11_shift / 8;
    if (var_a2 > 15) {
        var_a2 = 15;
    }
    var_v1 = D_80032F14[pos * 16 + var_a2];
    octave -= 5;
    if (octave > 0) {
        var_v1 <<= octave;
    } else if (octave < 0) {
        var_v1 >>= -octave;
    }
    return var_v1;
}

s32 note2pitch2(u16 arg0, u16 arg1) {
    s16 octave;
    s16 var_a2;
    s16 var_a3;
    short new_var;
    u16 var_v1;
    s32 pos;
    s32 tone;

    tone = _svm_cur.field_C_vag_idx + (_svm_cur.field_7_fake_program * 0x10);
    var_a3 = (arg1 + _svm_tn[tone].shift) / 8;
    var_a2 = 0;
    if (var_a3 >= 16) {
        var_a2 = 1;
        var_a3 -= 16;
    }
    new_var = arg0 + 60 - _svm_tn[tone].center + var_a2;
    octave = new_var / 12;
    pos = (new_var % 12) * 16;
    var_v1 = D_80032F14[pos + var_a3];

    octave -= 5;
    if (octave > 0) {
        var_v1 <<= octave;
    } else if (octave < 0) {
        var_v1 >>= -octave;
    }
    return var_v1;
}

void SePitchBend(u8 voice, s16 arg1) {
    s32 tone;
    u16 note;
    u16 pbend;
    int pos;
    pos = voice * 8;

    if (voice >= 0 && voice < NUM_SPU_CHANNELS) {
        _svm_cur.field_7_fake_program = _svm_voice[voice].unk10;
        _svm_cur.field_C_vag_idx = _svm_voice[voice].tone;
        _svm_cur.field_0x1a = voice;
        tone =
            _svm_cur.field_C_vag_idx + (_svm_cur.field_7_fake_program * 0x10);
        if (arg1 >= 0) {
            note = _svm_voice[voice].note + (arg1 * _svm_tn[tone].pbmax) / 0x7F;
            pbend = (arg1 * _svm_tn[tone].pbmax) % 0x7F;
        } else {
            note =
                (_svm_voice[voice].note + (arg1 * _svm_tn[tone].pbmin) / 0x7F) -
                1;
            pbend = ((arg1 * _svm_tn[tone].pbmin) / 0x7F) + 0x7F;
        }
        _svm_sreg_buf[pos + 2] = note2pitch2(note, pbend);
        _svm_sreg_dirty[voice] |= 4;
    }
}

static inline u8 _SsVmSelectToneAndVag(u8* toneIdx, u8* vagIdx) {
    u8 i;
    u8 vagCount;
    VagAtr* vagAttr;

    vagCount = 0;
    for (i = 0; i < _svm_cur.field_0_sep_sep_no_tonecount; i++) {
        vagAttr = &_svm_tn[(_svm_cur.field_7_fake_program * 0x10) + i];
        if (vagAttr->min > _svm_cur.field_2_note ||
            _svm_cur.field_2_note > vagAttr->max) {
            continue;
        }
        vagIdx[vagCount] = vagAttr->vag;
        toneIdx[vagCount++] = i;
    }
    return vagCount;
}

void SsUtVibrateOn(void) {}

void SsUtVibrateOff(void) {}

#define klabs(A) (((A) >= 0) ? (A) : -(A))

void SeAutoVol(s16 voice, s16 start_vol, s16 end_vol, s16 delta_time) {
    if (start_vol != end_vol) {
        _svm_voice[voice].auto_vol = 1;
        _svm_voice[voice].start_vol = start_vol;
        _svm_voice[voice].end_vol = end_vol;

        if (klabs(start_vol - end_vol) < delta_time) {
            _svm_voice[voice].unk1e = 1;
            _svm_voice[voice].unk20 = delta_time / (start_vol - end_vol);
            _svm_voice[voice].unk22 = delta_time / (start_vol - end_vol);
        } else {
            _svm_voice[voice].unk20 = 0;
            _svm_voice[voice].unk1e = (start_vol - end_vol) / delta_time;
        }
    }
}

void SetAutoVol(s16 voice) {
    s16 temp_v1_3;
    u32 voll_t, volr_t;
    u16 voll, volr;
    s16 pos;
    s32 mvol_scaled;

    pos = voice * 8;
    if (_svm_voice[voice].unk20 != 0) {
        if (_svm_voice[voice].unk22-- > 0) {
            return;
        }
        _svm_voice[voice].unk22 = _svm_voice[voice].unk20;
    }
    _svm_voice[voice].start_vol += _svm_voice[voice].unk1e;
    if (_svm_voice[voice].unk1e > 0) {
        if (_svm_voice[voice].start_vol >= _svm_voice[voice].end_vol) {
            _svm_voice[voice].start_vol = _svm_voice[voice].end_vol;
            _svm_voice[voice].auto_vol = 0;
        }
    } else if (_svm_voice[voice].unk1e < 0) {
        if (_svm_voice[voice].start_vol <= _svm_voice[voice].end_vol) {
            _svm_voice[voice].start_vol = _svm_voice[voice].end_vol;
            _svm_voice[voice].auto_vol = 0;
        }
    }
    temp_v1_3 = _svm_voice[voice].start_vol;
    _svm_cur.field_4_voll = temp_v1_3;
    mvol_scaled = _svm_vh->mvol * 0x3FFF;

    voll_t = ((temp_v1_3 * mvol_scaled) / 0x7F) / 0x7F;
    volr_t = ((temp_v1_3 * mvol_scaled) / 0x7F) / 0x7F;

    voll_t =
        ((voll_t * _svm_cur.field_A_mvol * _svm_cur.field_D_vol) / 0x7F) / 0x7F;
    volr_t =
        ((volr_t * _svm_cur.field_A_mvol * _svm_cur.field_D_vol) / 0x7F) / 0x7F;

    if (_svm_cur.field_E_pan < 0x40) {
        voll = voll_t;
        volr = (volr_t * _svm_cur.field_E_pan) / 0x40;
    } else {
        voll = (voll_t * (0x7F - _svm_cur.field_E_pan)) / 0x40;
        volr = volr_t;
    }

    if (_svm_cur.field_B_mpan < 0x40) {
        volr = (volr * _svm_cur.field_B_mpan) / 0x40;
    } else {
        voll = (voll * (0x7F - _svm_cur.field_B_mpan)) / 0x40;
    }

    if (_svm_cur.field_0x5 < 0x40) {
        volr = (volr * _svm_cur.field_0x5) / 0x40;
    } else {
        voll = (voll * (0x7F - _svm_cur.field_0x5)) / 0x40;
    }

    if (_svm_stereo_mono == 1) {
        if (volr > voll) {
            voll = volr;
        } else {
            volr = voll;
        }
    }
    _svm_sreg_buf[pos + 0] = voll;
    _svm_sreg_buf[pos + 1] = volr;
    _svm_sreg_dirty[voice] |= 3;
}

void SeAutoPan(s16 voice, s16 start_pan, s16 end_pan, s16 delta_time) {
    if (start_pan != end_pan) {
        _svm_voice[voice].auto_pan = 1;
        _svm_voice[voice].start_pan = start_pan;
        _svm_voice[voice].end_pan = end_pan;

        if (klabs(start_pan - end_pan) < delta_time) {
            _svm_voice[voice].unk2a = 1;
            _svm_voice[voice].unk2c = delta_time / (start_pan - end_pan);
            _svm_voice[voice].unk2e = delta_time / (start_pan - end_pan);
        } else {
            _svm_voice[voice].unk2c = 0;
            _svm_voice[voice].unk2a = (start_pan - end_pan) / delta_time;
        }
    }
}

void SetAutoPan(s16 voice) {
    u32 voll_t, volr_t;
    u16 voll, volr;
    s16 pos;
    char new_var;
    u16 new_var2;
    s32 mvol_scaled;

    pos = voice * 8;
    if (_svm_voice[voice].unk2c != 0) {
        if (_svm_voice[voice].unk2e-- > 0) {
            return;
        }
        _svm_voice[voice].unk2e = _svm_voice[voice].unk2c;
    }
    _svm_voice[voice].start_pan += _svm_voice[voice].unk2a;
    if (_svm_voice[voice].unk2a > 0) {
        if (_svm_voice[voice].start_pan >= _svm_voice[voice].end_pan) {
            _svm_voice[voice].start_pan = _svm_voice[voice].end_pan;
            _svm_voice[voice].auto_pan = 0;
        }
    } else if (_svm_voice[voice].unk2a < 0) {
        if (_svm_voice[voice].start_pan <= _svm_voice[voice].end_pan) {
            _svm_voice[voice].start_pan = _svm_voice[voice].end_pan;
            _svm_voice[voice].auto_pan = 0;
        }
    }
    new_var = _svm_voice[voice].start_pan;
    _svm_cur.field_0x5 = new_var;
    mvol_scaled = _svm_vh->mvol * 0x3FFF;

    voll_t = ((_svm_cur.field_4_voll * mvol_scaled) / 0x7F) / 0x7F;
    volr_t = ((_svm_cur.field_4_voll * mvol_scaled) / 0x7F) / 0x7F;

    voll_t =
        ((voll_t * _svm_cur.field_A_mvol * _svm_cur.field_D_vol) / 0x7F) / 0x7F;
    volr_t =
        ((volr_t * _svm_cur.field_A_mvol * _svm_cur.field_D_vol) / 0x7F) / 0x7F;

    if (_svm_cur.field_E_pan < 0x40) {
        voll = voll_t;
        volr = (volr_t * _svm_cur.field_E_pan) / 0x40;
    } else {
        voll = (voll_t * (0x7F - _svm_cur.field_E_pan)) / 0x40;
        volr = volr_t;
    }

    if (_svm_cur.field_B_mpan < 0x40) {
        volr = (volr * _svm_cur.field_B_mpan) / 0x40;
    } else {
        voll = (voll * (0x7F - _svm_cur.field_B_mpan)) / 0x40;
    }
    new_var2 = new_var;
    if (new_var2 < 0x40) {
        volr = (volr * new_var2) / 0x40;
    } else {
        voll = (voll * (0x7F - new_var2)) / 0x40;
    }

    if (_svm_stereo_mono == 1) {
        if (volr > voll) {
            voll = volr;
        } else {
            volr = voll;
        }
    }
    _svm_sreg_buf[pos + 0] = voll;
    _svm_sreg_buf[pos + 1] = volr;
    _svm_sreg_dirty[voice] |= 3;
}

void SpuVmInit(u8 arg0) {
    u16 temp_v1;
    u16 var_a1;
    u16* temp_a0;
    s32 var_a0;
    u16 bitsUpper;
    u16 bitsLower;
    u16 temp;
    _spu_setInTransfer(0);
    _svm_vcf = 0;
    _svm_damper = 0;
    SpuInitMalloc(0x20, &_ss_spu_vm_rec.D_8003BD50);
    for (var_a1 = 0; var_a1 < 8 * NUM_SPU_CHANNELS; var_a1++) {
        _svm_sreg_buf[var_a1] = 0;
    }
    for (var_a1 = 0; var_a1 < NUM_SPU_CHANNELS; var_a1++) {
        _svm_sreg_dirty[var_a1] = 0;
    }

    _svm_vab_count = 0;

    for (var_a1 = 0; var_a1 < 16; var_a1++) {
        _svm_vab_used[var_a1] = 0;
    }

    var_a0 = arg0;
    if (arg0 >= NUM_SPU_CHANNELS) {
        spuVmMaxVoice = NUM_SPU_CHANNELS;
    } else {
        spuVmMaxVoice = var_a0;
    }
    for (var_a1 = 0; var_a1 < spuVmMaxVoice; var_a1++) {
        temp = var_a1 * 8;
        _svm_voice[var_a1].unk2 = 0x18;
        _svm_voice[var_a1].unke = -1;
        _svm_voice[var_a1].unk0 = 0xFF;
        _svm_voice[var_a1].unk1b = 0;
        _svm_voice[var_a1].unk04 = 0;
        _svm_voice[var_a1].unk6 = 0;
        _svm_voice[var_a1].unk10 = 0;
        _svm_voice[var_a1].prog = 0;
        _svm_voice[var_a1].tone = 0xff;
        _svm_voice[var_a1].unk8 = 0;
        _svm_voice[var_a1].unka = 0x40;
        _svm_voice[var_a1].auto_vol = 0;
        _svm_voice[var_a1].unk1e = 0;
        _svm_voice[var_a1].unk20 = 0;
        _svm_voice[var_a1].unk22 = 0;
        _svm_voice[var_a1].auto_pan = 0;
        _svm_voice[var_a1].unk2a = 0;
        _svm_voice[var_a1].unk2c = 0;
        _svm_voice[var_a1].unk2e = 0;
        _svm_voice[var_a1].start_pan = 0;
        _svm_voice[var_a1].start_vol = 0;

#ifdef VERSION_PC
        write_16(0x1F801C00 + var_a1 * 0x10 + 6, 0x200, __FILE__, __LINE__);
        write_16(0x1F801C00 + var_a1 * 0x10 + 4, 0x1000, __FILE__, __LINE__);
        write_16(0x1F801C00 + var_a1 * 0x10 + 8, 0x80FF, __FILE__, __LINE__);
        write_16(0x1F801C00 + var_a1 * 0x10 + 0, 0, __FILE__, __LINE__);
        write_16(0x1F801C00 + var_a1 * 0x10 + 2, 0, __FILE__, __LINE__);
        write_16(0x1F801C00 + var_a1 * 0x10 + 10, 0x4000, __FILE__, __LINE__);
#else
        // pointer to 0x1F801C00
        temp_a0 = &D_80032F10[temp];
        temp_a0[3] = 0x200;
        temp_a0[2] = 0x1000;
        temp_a0[4] = 0x80FF;
        temp_a0[0] = 0;
        temp_a0[1] = 0;
        temp_a0[5] = 0x4000;
#endif

        _svm_cur.field_0x1a = var_a1;
        temp_v1 = get_field_0x1a();
        if (temp_v1 < 0x10) {
            bitsLower = 1 << temp_v1;
            bitsUpper = 0;
        } else {
            bitsLower = 0;
            bitsUpper = 1 << (temp_v1 - 0x10);
        }

        _svm_voice[temp_v1].unk1b = 0;
        _svm_voice[temp_v1].unk04 = 0;
        _svm_voice[temp_v1].unk0 = 0;

        _svm_okof1 |= bitsLower;
        _svm_okof2 |= bitsUpper;

        _svm_okon1 &= ~_svm_okof1;
        _svm_okon2 &= ~_svm_okof2;
    }
    _svm_rattr.depth.left = 0x3FFF;
    _svm_rattr.depth.right = 0x3FFF;
    _svm_okon1 = 0;
    _svm_okon2 = 0;
    _svm_okof1 = 0;
    _svm_orev1 = 0;
    _svm_orev2 = 0;
    _svm_rattr.mask = 0;
    _svm_rattr.mode = 0;
    _svm_auto_kof_mode = 0;
    _svm_stereo_mono = 0;
    kMaxPrograms = 0x80;
    SpuVmFlush();
}

void SpuVmNoiseOnWithAdsr(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s16 temp_v0;

    _svm_cur.field_F_prior = 0x7F;
    temp_v0 = SpuVmAlloc(0xFF) & 0xFF;
    _svm_cur.field_0x1a = temp_v0;
    if (temp_v0 < (s32)spuVmMaxVoice) {
        vmNoiseOn2((u8)_svm_cur.field_0x1a, arg0, arg1, arg2, arg3);
    }
}

void SpuVmNoiseOff(void) {
    s16 i;
    for (i = 0; i < spuVmMaxVoice; i++) {
        if (_svm_voice[i].unk1b == 2) {
            _svm_voice[i & 0xFF].unk1b = 0;
            _svm_voice[i & 0xFF].unk04 = 0;
            // pointer to 0x1F801C00
            D_80032F10[0x194 / 2] = 0;
            D_80032F10[0x196 / 2] = 0;
        }
    }
}

void SpuVmNoiseOn(s32 arg0, s32 arg1) {
    _svm_cur.field_F_prior = 0x7F;
    _svm_cur.field_0x1a = SpuVmAlloc(0xFF);
    if (_svm_cur.field_0x1a < spuVmMaxVoice) {
        vmNoiseOn2(_svm_cur.field_0x1a, arg0, arg1, 0x80FF, 0x5FC8);
    }
}

s16 SpuVmPBVoice(
    s16 voice, s16 seq_sep_no, s16 vabId, s16 program, u16 amount) {
    s16 temp_t1;
    u16 temp_v1;
    u16 pbend;
    u16 temp_a1;
    u16 note;

    temp_t1 = amount - 0x40;
    if ((_svm_voice[voice].unke == seq_sep_no) &&
        (_svm_voice[voice].vabId == vabId) &&
        (_svm_voice[voice].prog == program)) {
        temp_a1 = _svm_voice[voice].note;
        temp_v1 =
            _svm_voice[voice].tone + (_svm_cur.field_7_fake_program * 0x10);
        if (temp_t1 > 0) {
            do {
                note = _svm_voice[voice].note +
                       ((temp_t1 * _svm_tn[temp_v1].pbmax) / 0x3F);
            } while (0);
            pbend = ((temp_t1 * _svm_tn[temp_v1].pbmax) % 0x3F) * 2;
        } else {
            note = temp_a1;
            if (temp_t1 < 0) {
                note = ((temp_t1 * _svm_tn[temp_v1].pbmin) / 0x40);
                note = (temp_a1 + note) - 1;
                pbend =
                    (((temp_t1 * _svm_tn[temp_v1].pbmin) % 0x40) * 2) + 0x7F;
            } else {
                pbend = 0;
            }
        }
        _svm_cur.field_C_vag_idx = _svm_voice[voice].tone;
        _svm_cur.field_0x1a = voice;
        _svm_sreg_buf[voice * 8 + 2] = note2pitch2(note, pbend);
        _svm_sreg_dirty[voice] |= 4;
        return 1;
    } else {
        return 0;
    }
}

s32 SpuVmPitchBend(s16 arg0, s16 arg1, s16 arg2, s16 arg3) {
    s16 voice;
    s32 var_s1;

    SpuVmVSetUp(arg1, arg2);
    _svm_cur.field_16_vag_idx = arg0;
    var_s1 = 0;

    for (voice = 0; voice < spuVmMaxVoice; voice++) {
        var_s1 += SpuVmPBVoice(voice, arg0, arg1, arg2, arg3);
    }
    return var_s1;
}

#ifndef VERSION_PC
void SpuVmFlush(void) {
    u32 env_mask;
    s32 i;

    D_8003BD08 = (D_8003BD08 + 1) & 0xF;
    _svm_envx_hist[D_8003BD08] = 0;

    for (i = 0; i < spuVmMaxVoice; i++) {
        _svm_voice[i].unk6 = D_80032F10[i * 8 + 6];
        if (_svm_voice[i].unk6 == 0) {
            _svm_envx_hist[D_8003BD08] |= 1 << i;
        }
    }
    if (_svm_auto_kof_mode == 0) {
        env_mask = 0xFFFFFFFF;
        for (i = 0; i < 0xF; i++) {
            env_mask &= _svm_envx_hist[i];
        }

        for (i = 0; i < spuVmMaxVoice; i++) {
            if (env_mask & (1 << i)) {
                if (_svm_voice[i].unk1b == 2) {
                    SpuSetNoiseVoice(0, 0xFFFFFF);
                }
                _svm_voice[i].unk1b = 0;
            }
        }
    }

    _svm_okon1 &= ~_svm_okof1;
    _svm_okon2 &= ~_svm_okof2;
    for (i = 0; i < NUM_SPU_CHANNELS; i++) {
        if (_svm_voice[i].auto_vol != 0) {
            SetAutoVol(i);
        }
        if (_svm_voice[i].auto_pan != 0) {
            SetAutoPan(i);
        }
    }

    for (i = 0; i < NUM_SPU_CHANNELS; i++) {
        if (_svm_sreg_dirty[i] & 1) {
            D_80032F10[i * 8 + 0] = _svm_sreg_buf[i * 8 + 0];
            D_80032F10[i * 8 + 1] = _svm_sreg_buf[i * 8 + 1];
        }
        if (_svm_sreg_dirty[i] & 4) {
            D_80032F10[i * 8 + 2] = _svm_sreg_buf[i * 8 + 2];
        }
        if (_svm_sreg_dirty[i] & 8) {
            D_80032F10[i * 8 + 3] = _svm_sreg_buf[i * 8 + 3];
        }
        if (_svm_sreg_dirty[i] & 0x10) {
            D_80032F10[i * 8 + 4] = _svm_sreg_buf[i * 8 + 4];
            D_80032F10[i * 8 + 5] = _svm_sreg_buf[i * 8 + 5];
        }
        _svm_sreg_dirty[i] = 0;
    }

    D_80032F10[0x18C / 2] = _svm_okof1;
    D_80032F10[0x18E / 2] = _svm_okof2;
    D_80032F10[0x188 / 2] = _svm_okon1;
    D_80032F10[0x18A / 2] = _svm_okon2;
    D_80032F10[0x198 / 2] = _svm_orev1;
    D_80032F10[0x19A / 2] = _svm_orev2;
    _svm_okof1 = 0;
    _svm_okof2 = 0;
    _svm_okon1 = 0;
    _svm_okon2 = 0;
}
#endif

#ifndef VERSION_PC
s32 SpuVmKeyOn(s16 arg0, s16 vabId, s16 prog, u16 note, u16 voll, u16 volr) {
    struct SeqStruct* score = &_ss_score[arg0 & 0xFF][(arg0 & 0xFF00) >> 8];
    u8 vagIdx[0x80];
    u8 toneIdx[0x80];
    u8 i;
    s32 var_s2;
    s32 tone;
    u8 vagCount;

    var_s2 = 0;
    if (SpuVmVSetUp(vabId, prog)) {
        return -1;
    }
    _svm_cur.field_16_vag_idx = arg0;
    _svm_cur.field_2_note = note;
    _svm_cur.field_0x3 = 0;
    if (arg0 == 0x21) {
        _svm_cur.field_4_voll = voll;
    } else {
        _svm_cur.field_4_voll = (voll * score->vol[score->channel]) / 0x7F;
    }

    _svm_cur.field_0x5 = volr;
    _svm_cur.field_A_mvol = _svm_pg[prog].mvol;
    _svm_cur.field_B_mpan = _svm_pg[prog].mpan;
    _svm_cur.field_0_sep_sep_no_tonecount = _svm_pg[prog].tones;
    if (_svm_cur.field_7_fake_program >= _svm_vh->ps) {
        return -1;
    }
    if (voll == 0) {
        var_s2 = SpuVmKeyOff(arg0, vabId, prog, note);
    } else {
        vagCount = _SsVmSelectToneAndVag(toneIdx, vagIdx);
        for (i = 0; i < vagCount; i++) {
            _svm_cur.field_18_voice_idx = vagIdx[i];
            _svm_cur.field_C_vag_idx = toneIdx[i];

            tone = _svm_cur.field_C_vag_idx +
                   (_svm_cur.field_7_fake_program * 0x10);
            _svm_cur.field_F_prior = _svm_tn[tone].prior;
            _svm_cur.field_D_vol = _svm_tn[tone].vol;
            _svm_cur.field_E_pan = _svm_tn[tone].pan;
            _svm_cur.field_10_centre = _svm_tn[tone].center;
            _svm_cur.field_11_shift = _svm_tn[tone].shift;
            _svm_cur.field_14_seq_sep_no = _svm_tn[tone].mode;
            _svm_cur.field_12_mode = _svm_tn[tone].min;
            _svm_cur.field_0x13 = _svm_tn[tone].max;
            _svm_cur.field_0x1a = SpuVmAlloc(0);
            if (_svm_cur.field_0x1a < spuVmMaxVoice) {
                _svm_voice[_svm_cur.field_0x1a].unk1b = 1;
                _svm_voice[_svm_cur.field_0x1a].unk2 = 0;
                _svm_voice[_svm_cur.field_0x1a].unke = arg0;
                _svm_voice[_svm_cur.field_0x1a].vabId = _svm_cur.field_1_vabId;
                _svm_voice[_svm_cur.field_0x1a].unk10 =
                    _svm_cur.field_7_fake_program;
                _svm_voice[_svm_cur.field_0x1a].prog = prog;
                if (arg0 != 0x21) {
                    _svm_voice[_svm_cur.field_0x1a].unk8 = voll;
                }
                _svm_voice[_svm_cur.field_0x1a].unka = volr;
                _svm_voice[_svm_cur.field_0x1a].tone = _svm_cur.field_C_vag_idx;
                _svm_voice[_svm_cur.field_0x1a].note = note;
                _svm_voice[_svm_cur.field_0x1a].unk18 = _svm_cur.field_F_prior;
                _svm_voice[_svm_cur.field_0x1a].unk0 =
                    _svm_cur.field_18_voice_idx;
                SpuVmDoAllocate();
                if (_svm_cur.field_18_voice_idx == 0xFF) {
                    vmNoiseOn(_svm_cur.field_0x1a);
                } else {
                    SpuVmKeyOnNow(vagCount, note2pitch() & 0xFFFF);
                }
                var_s2 |= 1 << _svm_cur.field_0x1a;
            } else {
                var_s2 = -1;
            }
        }
    }
    return var_s2;
}
#endif

s32 SpuVmKeyOff(s16 arg0, s16 vabId, s16 prog, u16 note) {
    u16 bitsUpper;
    u16 bitsLower;
    u8 voice;
    s32 var_t1;
    u16 temp_v1;

    var_t1 = 0;
    for (voice = 0; voice < spuVmMaxVoice; voice++) {
        if ((_svm_voice[voice].note == note) &&
            (_svm_voice[voice].prog == prog) &&
            (_svm_voice[voice].unke == arg0) &&
            (_svm_voice[voice].vabId == vabId)) {
            if (_svm_voice[voice].unk0 == 0xFF) {
                _svm_voice[voice].unk1b = 0;
                _svm_voice[voice].unk04 = 0;
                D_80032F10[202] = 0;
                D_80032F10[203] = 0;
            } else {
                _svm_cur.field_0x1a = voice;
                temp_v1 = get_field_0x1a();
                if (temp_v1 < 0x10) {
                    bitsLower = 1 << temp_v1;
                    bitsUpper = 0;
                } else {
                    bitsLower = 0;
                    bitsUpper = 1 << (temp_v1 - 0x10);
                }

                _svm_voice[temp_v1].unk1b = 0;
                _svm_voice[temp_v1].unk04 = 0;
                _svm_voice[temp_v1].unk0 = 0;

                _svm_okof1 |= bitsLower;
                _svm_okof2 |= bitsUpper;

                _svm_okon1 &= ~_svm_okof1;
                _svm_okon2 &= ~_svm_okof2;
            }
            var_t1++;
        }
    }
    return var_t1;
}

void SpuVmSeKeyOn(s16 vabId, s16 prog, u16 note, s32 arg3, u16 voll, u16 volr) {
    u16 var_v1;
    u16 var_a1;

    if (voll == volr) {
        var_v1 = 0x40;
        var_a1 = voll;
    } else if (volr < voll) {
        var_a1 = voll;
        var_v1 = (volr * 0x40) / voll;
    } else {
        var_a1 = volr;
        var_v1 = 0x7F - ((voll * 0x40) / volr);
    }
    SpuVmKeyOn(0x21, vabId, prog, note, var_a1, var_v1);
}

void SpuVmSeKeyOff(s16 vabId, s16 prog, u16 note) {
    SpuVmKeyOff(0x21, vabId, prog, note);
}

void KeyOnCheck(void) {}

s32 SpuVmSetSeqVol(s16 seq_sep_no, u16 voll, u16 volr, s16 arg3) {
    struct SeqStruct* score =
        &_ss_score[seq_sep_no & 0xFF][(seq_sep_no >> 8) & 0xFF];
    s16 voice;
    int voll_mul;
    int volr_mul;
    u8 pad[4];
    int temp;
    s16 pos;

    _svm_cur.field_16_vag_idx = seq_sep_no;
    score->unk74 = voll;
    score->unk76 = volr;
    temp = seq_sep_no;
    if (score->unk74 >= 0x80) {
        score->unk74 = 0x7F;
    }
    if (score->unk76 >= 0x80) {
        score->unk76 = 0x7F;
    }
    voll_mul = voll * 0x81;
    volr_mul = volr * 0x81;

    if (arg3 == 1) {
        for (voice = 0; voice < spuVmMaxVoice; voice++) {
            if ((u16)_svm_voice[voice].unke == (u16)temp) {
                pos = voice * 8;
                _svm_sreg_buf[pos + 0] = voll_mul;
                _svm_sreg_buf[pos + 1] = volr_mul;
                _svm_sreg_dirty[voice] |= 3;
            }
        }
    }
    return _svm_cur.field_16_vag_idx;
}

s32 SpuVmGetSeqVol(s16 arg0, s16* arg1, s16* arg2) {
    struct SeqStruct* score = &_ss_score[arg0 & 0xFF][(arg0 & 0xFF00) >> 8];
    _svm_cur.field_16_vag_idx = arg0;
    *arg1 = score->unk74;
    *arg2 = score->unk76;
    return _svm_cur.field_16_vag_idx;
}

s16 SpuVmGetSeqLVol(s16 arg0) {
    struct SeqStruct* score = &_ss_score[arg0 & 0xFF][(arg0 & 0xFF00) >> 8];
    _svm_cur.field_16_vag_idx = arg0;
    return score->unk74;
}

s16 SpuVmGetSeqRVol(s16 arg0) {
    struct SeqStruct* score = &_ss_score[arg0 & 0xFF][(arg0 & 0xFF00) >> 8];
    _svm_cur.field_16_vag_idx = arg0;
    return score->unk76;
}

void SpuVmSeqKeyOff(s16 arg0) {
    u8 voice;
    u16 bitsUpper;
    u16 bitsLower;
    u16 temp2;

    for (voice = 0; voice < spuVmMaxVoice; voice++) {
        if (_svm_voice[voice].unke == arg0) {
            _svm_cur.field_0x1a = voice;
            temp2 = get_field_0x1a();
            if (temp2 < 0x10) {
                bitsLower = 1 << temp2;
                bitsUpper = 0;
            } else {
                bitsLower = 0;
                bitsUpper = 1 << (temp2 - 0x10);
            }

            _svm_voice[temp2].unk1b = 0;
            _svm_voice[temp2].unk04 = 0;
            _svm_voice[temp2].unk0 = 0;

            _svm_okof1 |= bitsLower;
            _svm_okof2 |= bitsUpper;

            _svm_okon1 &= ~_svm_okof1;
            _svm_okon2 &= ~_svm_okof2;
        }
    }
}

s32 SpuVmSetProgVol(s16 vabId, s16 prog, u8 arg2) {
    if (SpuVmVSetUp(vabId, prog)) {
        return -1;
    }
    _svm_pg[prog].mvol = arg2;
    return _svm_pg[prog].mvol;
}

s32 SpuVmGetProgVol(s16 vabId, s16 prog) {
    if (SpuVmVSetUp(vabId, prog)) {
        return -1;
    }
    return _svm_pg[prog].mvol;
}

s32 SpuVmSetProgPan(s16 vabId, s16 prog, u8 pan) {
    if (SpuVmVSetUp(vabId, prog)) {
        return -1;
    }
    _svm_pg[prog].mpan = pan;
    return _svm_pg[prog].mpan;
}

s32 SpuVmGetProgPan(s16 vabId, s16 prog) {
    if (SpuVmVSetUp(vabId, prog)) {
        return -1;
    }
    return _svm_pg[prog].mpan;
}

#ifndef VERSION_PC
s32 SpuVmSetVol(s16 seq_sep_no, s16 vabId, s16 prog, u16 arg3, u16 arg4) {
    s32 var_s2;
    u8 voice;
    s32 new_var;
    u32 volr;
    u32 voll;
    u32 volr_t;
    u32 voll_t;
    struct SeqStruct* temp_s1;
    s32 mvol_scaled;
    s16 new_var2;
    register u16 pan_arg asm("s3") = arg4;

    var_s2 = 0;
    temp_s1 = &_ss_score[seq_sep_no & 0xFF][(seq_sep_no & 0xFF00) >> 8];
    SpuVmVSetUp(vabId, prog);
    _svm_cur.field_16_vag_idx = seq_sep_no;
    for (voice = 0; voice < spuVmMaxVoice; voice++) {
        new_var2 = prog;
        if ((_svm_voice[voice].unke == seq_sep_no) &&
            (_svm_voice[voice].prog == new_var2) &&
            (_svm_voice[voice].vabId == vabId)) {
            if (temp_s1->vol[temp_s1->channel] != arg3) {
                if (temp_s1->vol[temp_s1->channel] == 0) {
                    temp_s1->vol[temp_s1->channel] = 1;
                }
            }
            new_var = (_svm_voice[voice].unk8 * arg3) / 0x7F;
            mvol_scaled = _svm_vh->mvol * 0x3FFF;
            voll_t = (new_var * mvol_scaled) / 0x3F01;
            volr_t = voll_t =
                (voll_t * _svm_pg[new_var2].mvol *
                 _svm_tn[_svm_voice[voice].tone + (new_var2 * 0x10)].vol) /
                0x3F01;

            voll_t = (voll_t * temp_s1->unk74) / 0x7F;
            volr_t = (volr_t * temp_s1->unk76) / 0x7F;

            if (_svm_tn[_svm_voice[voice].tone].pan < 0x40) {
                voll = voll_t;
                volr = (volr_t * _svm_tn[_svm_voice[voice].tone].pan) / 0x3F;
            } else {
                voll = (voll_t * (0x7F - _svm_tn[_svm_voice[voice].tone].pan)) /
                       0x3F;
                volr = volr_t;
            }
            if (_svm_pg[_svm_voice[voice].unk10].mpan < 0x40) {
                volr = (volr * _svm_pg[_svm_voice[voice].unk10].mpan) / 0x3F;
            } else {
                voll = (voll * (0x7F - _svm_pg[_svm_voice[voice].unk10].mpan)) /
                       0x3F;
            }
            if ((pan_arg & 0xFF) < 0x40) {
                volr = (volr * (pan_arg & 0xFF)) / 0x3F;
            } else {
                voll = (voll * (0x7F - (pan_arg & 0xFF))) / 0x3F;
            }
            if (_svm_stereo_mono == 1) {
                if (voll < volr) {
                    voll = volr;
                } else {
                    volr = voll;
                }
            }
            voll = (voll * voll) / 0x3FFF;
            volr = (volr * volr) / 0x3FFF;
            _svm_sreg_buf[voice * 8 + 0] = voll;
            _svm_sreg_buf[voice * 8 + 1] = volr;
            _svm_sreg_dirty[voice] |= 3;
            var_s2++;
        }
    }
    return var_s2;
}
#endif

s16 SsUtKeyOn(
    s16 vabId, s16 prog, s16 tone, s16 note, s16 fine, s16 voll, s16 volr) {
    s16 voice;
    s32 tone2;

    if (_snd_ev_flag == 1) {
        return -1;
    }
    _snd_ev_flag = 1;

    if (SpuVmVSetUp(vabId, prog)) {
        _snd_ev_flag = 0;
        return -1;
    }
    _svm_cur.field_16_vag_idx = 0x21;
    _svm_cur.field_2_note = note;
    _svm_cur.field_0x3 = fine;
    _svm_cur.field_C_vag_idx = tone;
    if (voll == volr) {
        _svm_cur.field_0x5 = 0x40;
        _svm_cur.field_4_voll = voll;
    } else if (volr < voll) {
        _svm_cur.field_4_voll = voll;
        _svm_cur.field_0x5 = (volr * 0x40) / voll;
    } else {
        _svm_cur.field_4_voll = volr;
        _svm_cur.field_0x5 = 0x7F - ((voll * 0x40) / volr);
    }
    _svm_cur.field_A_mvol = _svm_pg[prog].mvol;
    _svm_cur.field_B_mpan = _svm_pg[prog].mpan;
    _svm_cur.field_0_sep_sep_no_tonecount = _svm_pg[prog].tones;

    tone2 = _svm_cur.field_C_vag_idx + (_svm_cur.field_7_fake_program * 0x10);
    _svm_cur.field_F_prior = _svm_tn[tone2].prior;
    _svm_cur.field_18_voice_idx = _svm_tn[tone2].vag;
    _svm_cur.field_D_vol = _svm_tn[tone2].vol;
    _svm_cur.field_E_pan = _svm_tn[tone2].pan;
    _svm_cur.field_10_centre = _svm_tn[tone2].center;
    _svm_cur.field_11_shift = _svm_tn[tone2].shift;
    _svm_cur.field_14_seq_sep_no = _svm_tn[tone2].mode;
    _svm_cur.field_12_mode = _svm_tn[tone2].min;
    _svm_cur.field_0x13 = _svm_tn[tone2].max;
    if (_svm_cur.field_18_voice_idx == 0) {
        _snd_ev_flag = 0;
        return -1;
    }

    voice = SpuVmAlloc(_svm_cur.field_18_voice_idx);

    if (voice == spuVmMaxVoice) {
        _snd_ev_flag = 0;
        return -1;
    }

    _svm_cur.field_0x1a = voice;
    _svm_voice[voice].unke = 0x21;
    _svm_voice[voice].vabId = vabId;
    _svm_voice[voice].unk10 = _svm_cur.field_7_fake_program;
    _svm_voice[voice].prog = prog;
    _svm_voice[voice].unk0 = _svm_cur.field_18_voice_idx;
    _svm_voice[voice].tone = _svm_cur.field_C_vag_idx;
    _svm_voice[voice].note = note;
    _svm_voice[voice].unk1b = 1;
    _svm_voice[voice].unk2 = 0;

    SpuVmDoAllocate();
    if (_svm_cur.field_18_voice_idx == 0xFF) {
        vmNoiseOn(voice);
    } else {
        SpuVmKeyOnNow(1, note2pitch2(note, fine));
    }
    _snd_ev_flag = 0;
    return voice;
}

short SsUtKeyOff(s16 voice, s16 vabId, s16 prog, s16 tone, s16 note) {
    unsigned char new_var;
    u16 bitsUpper;
    u16 bitsLower;
    u16 temp_v1;

    if (_snd_ev_flag == 1) {
        return -1;
    }
    _snd_ev_flag = 1;

    if (voice >= 0 && voice < NUM_SPU_CHANNELS) {
        if ((_svm_voice[voice].vabId == vabId) &&
            (_svm_voice[voice].prog == prog) &&
            (_svm_voice[voice].tone == tone) &&
            (_svm_voice[voice].note == note)) {
            if (_svm_voice[voice].unk0 == 0xFF) {
                new_var = voice;
                _svm_voice[new_var].unk1b = 0;
                _svm_voice[new_var].unk04 = 0;
                D_80032F10[202] = 0;
                D_80032F10[203] = 0;
            } else {
                _svm_cur.field_0x1a = voice;
                temp_v1 = get_field_0x1a();
                if (temp_v1 < 0x10) {
                    bitsLower = 1 << temp_v1;
                    bitsUpper = 0;
                } else {
                    bitsLower = 0;
                    bitsUpper = 1 << (temp_v1 - 0x10);
                }
                _svm_voice[temp_v1].unk1b = 0;
                _svm_voice[temp_v1].unk04 = 0;
                _svm_voice[temp_v1].unk0 = 0;
                _svm_okof1 |= bitsLower;
                _svm_okof2 |= bitsUpper;
                _svm_okon1 &= ~_svm_okof1;
                _svm_okon2 &= ~_svm_okof2;
            }
            _snd_ev_flag = 0;
            return 0;
        }
    }
    _snd_ev_flag = 0;
    return -1;
}

s16 SsUtKeyOnV(s16 voice, s16 vabId, s16 prog, s16 tone, s16 note, s16 fine,
               s16 voll, s16 volr) {
    s32 tone2;

    if (_snd_ev_flag == 1) {
        return -1;
    }
    _snd_ev_flag = 1;
    if (voice < 0 || voice >= NUM_SPU_CHANNELS) {
        _snd_ev_flag = 0;
        return -1;
    }
    if (SpuVmVSetUp(vabId, prog)) {
        _snd_ev_flag = 0;
        return -1;
    }
    _svm_cur.field_16_vag_idx = 0x21;
    _svm_cur.field_2_note = note;
    _svm_cur.field_0x3 = fine;
    _svm_cur.field_C_vag_idx = tone;

    if (voll == volr) {
        _svm_cur.field_0x5 = 0x40;
        _svm_cur.field_4_voll = voll;
    } else if (volr < voll) {
        _svm_cur.field_0x5 = (volr * 0x40) / voll;
        _svm_cur.field_4_voll = voll;
    } else {
        _svm_cur.field_0x5 = 0x7F - ((voll * 0x40) / volr);
        _svm_cur.field_4_voll = volr;
    }

    _svm_cur.field_A_mvol = _svm_pg[prog].mvol;
    _svm_cur.field_B_mpan = _svm_pg[prog].mpan;
    _svm_cur.field_0_sep_sep_no_tonecount = _svm_pg[prog].tones;

    tone2 = _svm_cur.field_C_vag_idx + (_svm_cur.field_7_fake_program * 0x10);
    _svm_cur.field_F_prior = _svm_tn[tone2].prior;
    _svm_cur.field_18_voice_idx = _svm_tn[tone2].vag;
    _svm_cur.field_D_vol = _svm_tn[tone2].vol;
    _svm_cur.field_E_pan = _svm_tn[tone2].pan;
    _svm_cur.field_10_centre = _svm_tn[tone2].center;
    _svm_cur.field_11_shift = _svm_tn[tone2].shift;
    _svm_cur.field_14_seq_sep_no = _svm_tn[tone2].mode;
    _svm_cur.field_12_mode = _svm_tn[tone2].min;
    _svm_cur.field_0x13 = _svm_tn[tone2].max;

    if (_svm_cur.field_18_voice_idx == 0) {
        _snd_ev_flag = 0;
        return -1;
    }

    _svm_cur.field_0x1a = voice;
    _svm_voice[voice].unke = 0x21;
    _svm_voice[voice].vabId = vabId;
    _svm_voice[voice].unk10 = _svm_cur.field_7_fake_program;
    _svm_voice[voice].prog = prog;
    _svm_voice[voice].unk0 = _svm_cur.field_18_voice_idx;
    _svm_voice[voice].tone = _svm_cur.field_C_vag_idx;
    _svm_voice[voice].note = note;
    _svm_voice[voice].unk1b = 1;
    _svm_voice[voice].unk2 = 0;
    SpuVmDoAllocate();
    if (_svm_cur.field_18_voice_idx == 0xFF) {
        vmNoiseOn(voice);
    } else {
        SpuVmKeyOnNow(1, note2pitch2(note, fine));
    }
    _snd_ev_flag = 0;
    return voice;
}

s32 SsUtKeyOffV(s16 voice) {
    u16 bitsUpper;
    u16 bitsLower;
    u16 temp2;

    if (_snd_ev_flag == 1) {
        return -1;
    }
    _snd_ev_flag = 1;

    if (voice >= 0 && voice < NUM_SPU_CHANNELS) {
        _svm_cur.field_0x1a = voice;
        temp2 = get_field_0x1a();
        if (temp2 < 0x10) {
            bitsLower = 1 << temp2;
            bitsUpper = 0;
        } else {
            bitsLower = 0;
            bitsUpper = 1 << (temp2 - 0x10);
        }

        _svm_voice[temp2].unk1b = 0;
        _svm_voice[temp2].unk04 = 0;
        _svm_voice[temp2].unk0 = 0;

        _snd_ev_flag = 0;

        _svm_okof1 |= bitsLower;
        _svm_okof2 |= bitsUpper;

        _svm_okon1 &= ~_svm_okof1;
        _svm_okon2 &= ~_svm_okof2;
        return 0;
    }
    _snd_ev_flag = 0;
    return -1;
}

s16 SsUtPitchBend(s16 voice, s16 vabId, s16 prog, s16 note, s16 pbend) {
    SpuVmVSetUp(vabId, prog);
    _svm_cur.field_16_vag_idx = 0x21;
    return -((SpuVmPBVoice(voice, 0x21, vabId, prog, pbend) << 0x10) == 0);
}

short SsUtChangePitch(short voice, short vabId, short prog, short old_note,
                      short old_fine, short new_note, short new_fine) {
    if (voice >= 0 && voice < NUM_SPU_CHANNELS) {
        if ((_svm_voice[voice].vabId == vabId) &&
            (_svm_voice[voice].prog == prog) &&
            (_svm_voice[voice].note == old_note)) {
            SpuVmVSetUp(_svm_voice[voice].vabId, _svm_voice[voice].prog);
            _svm_cur.field_16_vag_idx = 0x21;
            _svm_cur.field_0x1a = voice;
            _svm_cur.field_C_vag_idx = _svm_voice[voice].tone;
            _svm_sreg_buf[voice * 8 + 2] = note2pitch2(new_note, new_fine);
            _svm_sreg_dirty[voice] |= 4;
            return 0;
        }
    }
    return -1;
}

s16 SsUtChangeADSR(
    s16 voice, s16 vabId, s16 prog, s16 old_note, u16 adsr1, u16 adsr2) {
    if (voice >= 0 && voice < NUM_SPU_CHANNELS) {
        if ((_svm_voice[voice].vabId == vabId) &&
            (_svm_voice[voice].prog == prog) &&
            (_svm_voice[voice].note == old_note)) {
            _svm_sreg_buf[voice * 8 + 4] = adsr1;
            _svm_sreg_buf[voice * 8 + 5] = adsr2;
            _svm_sreg_dirty[voice] |= 0x30;
            return 0;
        }
    }
    return -1;
}

s16 SsUtGetDetVVol(s16 voice, s16* voll, s16* volr) {
    if (voice >= 0 && voice < NUM_SPU_CHANNELS) {
        *voll = D_80032F10[voice * 8 + 0];
        *volr = D_80032F10[voice * 8 + 1];
        return 0;
    }
    return -1;
}

s32 SsUtSetDetVVol(s16 voice, s16 arg1, s16 arg2) {
    if (voice >= 0 && voice < NUM_SPU_CHANNELS) {
        _svm_sreg_buf[voice * 8 + 0] = arg1;
        _svm_sreg_buf[voice * 8 + 1] = arg2;
        _svm_sreg_dirty[voice] |= 3;
        return 0;
    }

    return -1;
}

s16 SsUtGetVVol(s16 voice, s16* voll, s16* volr) {
    if (voice >= 0 && voice < NUM_SPU_CHANNELS) {
        s16 temp1 = D_80032F10[voice * 8 + 0];
        s16 temp2 = D_80032F10[voice * 8 + 1];
        *voll = temp1 / 0x81;
        *volr = temp2 / 0x81;
        return 0;
    }
    return -1;
}

s16 SsUtSetVVol(s16 voice, s16 voll, s16 volr) {
    if (voice >= 0 && voice < NUM_SPU_CHANNELS) {
        voll *= 0x81;
        volr *= 0x81;
        _svm_sreg_buf[voice * 8 + 1] = volr;
        _svm_sreg_buf[voice * 8 + 0] = voll;
        _svm_sreg_dirty[voice] |= 3;
        return 0;
    }

    return -1;
}

s16 SsUtAutoVol(s16 voice, s16 start_vol, s16 end_vol, s16 delta_time) {
    if (voice >= 0 && voice < NUM_SPU_CHANNELS) {
        SeAutoVol(voice, start_vol, end_vol, delta_time);
        return 0;
    }
    return -1;
}

s16 SsUtAutoPan(s16 voice, s16 start_pan, s16 end_pan, s16 delta_time) {
    if (voice >= 0 && voice < NUM_SPU_CHANNELS) {
        SeAutoPan(voice, start_pan, end_pan, delta_time);
        return 0;
    }
    return -1;
}

void SsUtAllKeyOff(void) {
    s16 voice;
    u16 bitsUpper;
    u16 bitsLower;
    u16 temp2;
    s16 pos;

    for (voice = 0; voice < spuVmMaxVoice; voice++) {
        _svm_voice[voice].unk2 = 0x18;
        _svm_voice[voice].unk0 = 0xFF;
        _svm_voice[voice].unk1b = 0;
        _svm_voice[voice].unk04 = 0;
        _svm_voice[voice].unk6 = 0;
        _svm_voice[voice].unke = 0xFF;
        _svm_voice[voice].unk10 = 0;
        _svm_voice[voice].prog = 0;
        _svm_voice[voice].tone = 0xFF;

        pos = voice * 8;
        D_80032F10[pos + 0x6 / 2] = 0x200;
        D_80032F10[pos + 0x4 / 2] = 0x1000;
        D_80032F10[pos + 0x8 / 2] = 0x80ff;
        D_80032F10[pos + 0x0] = 0;
        D_80032F10[pos + 0x2 / 2] = 0;
        D_80032F10[pos + 0xa / 2] = 0x4000;

        _svm_cur.field_0x1a = voice;
        temp2 = get_field_0x1a();
        if (temp2 < 0x10) {
            bitsLower = 1 << temp2;
            bitsUpper = 0;
        } else {
            bitsLower = 0;
            bitsUpper = 1 << (temp2 - 0x10);
        }

        _svm_voice[temp2].unk1b = 0;
        _svm_voice[temp2].unk04 = 0;
        _svm_voice[temp2].unk0 = 0;

        _svm_okof1 |= bitsLower;
        _svm_okof2 |= bitsUpper;

        _svm_okon1 &= ~_svm_okof1;
        _svm_okon2 &= ~_svm_okof2;
    }
}
