#include "common.h"
#include "libsnd_i.h"

static inline u16 get_field_0x1a() { return _svm_cur.field_0x1a; }

u8 SpuVmAlloc(s32 arg0) {
    s16 temp_a2;
    u8 var_t2;
    u16 var_t0;
    u16 var_t3;
    u8 cur_voice;
    u8 channel;
    u8 var_t1;
    u16 prior;
    char temp;

    channel = 0x63;
    var_t3 = 0xFFFF;
    var_t2 = 0;
    var_t0 = 0;
    prior = _svm_cur.field_F_prior;
    var_t1 = 0x63;
    for (cur_voice = 0; cur_voice < spuVmMaxVoice; cur_voice++) {
        if (_svm_voice[cur_voice].unk1b == 0 &&
            _svm_voice[cur_voice].unk6 == 0) {
            channel = cur_voice;
            break;
        } else {
            temp_a2 = _svm_voice[cur_voice].unk18;
            if (temp_a2 < prior) {
                prior = temp_a2;
                var_t1 = cur_voice;
                var_t3 = _svm_voice[cur_voice].unk6;
                var_t0 = _svm_voice[cur_voice].unk2;
                var_t2 = 1;
            } else {
                if (temp_a2 == prior) {
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
        }
    }
    if (channel == 0x63) {
        channel = var_t1;
        if (!var_t2) {
            channel = spuVmMaxVoice;
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

INCLUDE_ASM("main/nonmatchings/psxsdk/libsnd/vmanager", SpuVmKeyOnNow);

INCLUDE_ASM("main/nonmatchings/psxsdk/libsnd/vmanager", SpuVmDoAllocate);

INCLUDE_ASM("main/nonmatchings/psxsdk/libsnd/vmanager", vmNoiseOn);

void vmNoiseOn2(u8 voice, u16 arg1, u16 arg2, u16 arg3, u16 arg4) {
    u16 i;
    u16 bitsUpper;
    u16 bitsLower;
    u8 pad[2];
    _svm_sreg_buf.buf[voice].field_0_vol_left = arg1;
    _svm_sreg_buf.buf[voice].field_2_vol_right = arg2;
    _svm_sreg_dirty[voice] = _svm_sreg_dirty[voice] | 3;
    _svm_sreg_dirty[voice] = _svm_sreg_dirty[voice] | 3;

    if (voice < 0x10) {
        bitsLower = 1 << voice;
        bitsUpper = 0;
    } else {
        bitsLower = 0;
        bitsUpper = 1 << (voice - 0x10);
    }

    _svm_voice[voice].unk04 = 0xa;
    for (i = 0; i < spuVmMaxVoice; i++) {
        _svm_voice[i].unk1b &= 1;
    }
    _svm_voice[voice].unk1b = 2;
    _svm_voice[voice].unk2 = 0;

    _svm_okon1 = bitsLower | _svm_okon1;
    _svm_okon2 = bitsUpper | _svm_okon2;

    _svm_okof1 = _svm_okof1 & ~_svm_okon1;
    _svm_okof2 = _svm_okof2 & ~_svm_okon2;
    D_80032F10[0x194 / 2] = bitsLower;
    D_80032F10[0x196 / 2] = bitsUpper;
}

extern u16 D_80032F14[];

u16 note2pitch() {
    s16 octave;
    u16 var_a2;
    s16 new_var;
    s32 temp;
    u16 var_v1;
    s16 pos;
    new_var = (_svm_cur.field_2_note + 60) - _svm_cur.field_10_centre;
    temp = new_var;
    octave = new_var / 12;
    var_a2 = ((long)_svm_cur.field_11_shift) >> 3;
    pos = (temp % 12);
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
    VagAtr* temp_v1;
    s16 octave;
    s32 temp_a1;
    u16 temp_v0;
    s16 var_a2;
    s16 var_a3;
    short new_var;
    s32 var_v0;
    u16 var_v1;
    s32 pos;
    temp_v1 = &_svm_tn[_svm_cur.field_C_vag_idx +
                       (_svm_cur.field_7_fake_program * 0x10)];
    var_v0 = arg1 + temp_v1->shift;
    if (var_v0 < 0) {
        var_v0 += 7;
    }
    temp_a1 = var_v0 >> 3;
    var_a3 = temp_a1;
    var_a2 = 0;
    if (temp_a1 >= 16) {
        var_a2 = 1;
        var_a3 = temp_a1 - 16;
    }
    temp_v0 = arg0 - (temp_v1->center - 60);
    new_var = var_a2 + temp_v0;
    octave = (new_var / 12) - 5;
    pos = (new_var % 12) * 16 + var_a3;
    var_v1 = D_80032F14[pos];
    if (octave > 0) {
        var_v1 <<= octave;
    } else if (octave < 0) {
        var_v1 = var_v1 >> (-octave);
    }
    return var_v1;
}

void SePitchBend(u8 arg0, s16 arg1) {
    s32 tone;
    s32 temp_v0_2;
    u16 note;
    u16 pbend;
    u8 temp_v0;
    int pos;
    pos = arg0 * 8;
    if (arg0 < 0x18U) {
        _svm_cur.field_7_fake_program = _svm_voice[arg0].unk10;
        _svm_cur.field_C_vag_idx = _svm_voice[arg0].tone;
        _svm_cur.field_0x1a = arg0;
        tone =
            _svm_cur.field_C_vag_idx + (_svm_cur.field_7_fake_program * 0x10);
        if (arg1 >= 0) {
            temp_v0 = _svm_tn[tone].pbmax;
            note = _svm_voice[arg0].note + ((arg1 * temp_v0) / 127);
            pbend = (arg1 * temp_v0) % 127;
        } else {
            temp_v0_2 = (arg1 * _svm_tn[tone].pbmin) / 127;
            note = (_svm_voice[arg0].note + temp_v0_2) - 1;
            pbend = temp_v0_2 + 0x7F;
        }
        _svm_sreg_buf.raw[pos + 2] = note2pitch2(note, pbend);
        _svm_sreg_dirty[arg0] |= 4;
    }
}

void SsUtVibrateOn(void) {}

void SsUtVibrateOff(void) {}

#define klabs(A) (((A) >= 0) ? (A) : -(A))

void SeAutoVol(s16 vc, s16 start_vol, s16 end_vol, s16 delta_time) {
    if (start_vol != end_vol) {
        _svm_voice[vc].auto_vol = 1;
        _svm_voice[vc].start_vol = start_vol;
        _svm_voice[vc].end_vol = end_vol;

        if (klabs(start_vol - end_vol) < delta_time) {
            _svm_voice[vc].unk1e = 1;
            _svm_voice[vc].unk20 = delta_time / (start_vol - end_vol);
            _svm_voice[vc].unk22 = delta_time / (start_vol - end_vol);
        } else {
            _svm_voice[vc].unk20 = 0;
            _svm_voice[vc].unk1e = (start_vol - end_vol) / delta_time;
        }
    }
}

INCLUDE_ASM("main/nonmatchings/psxsdk/libsnd/vmanager", SetAutoVol);

void SeAutoPan(s16 vc, s16 start_pan, s16 end_pan, s16 delta_time) {
    if (start_pan != end_pan) {
        _svm_voice[vc].auto_pan = 1;
        _svm_voice[vc].start_pan = start_pan;
        _svm_voice[vc].end_pan = end_pan;

        if (klabs(start_pan - end_pan) < delta_time) {
            _svm_voice[vc].unk2a = 1;
            _svm_voice[vc].unk2c = delta_time / (start_pan - end_pan);
            _svm_voice[vc].unk2e = delta_time / (start_pan - end_pan);
        } else {
            _svm_voice[vc].unk2c = 0;
            _svm_voice[vc].unk2a = (start_pan - end_pan) / delta_time;
        }
    }
}

INCLUDE_ASM("main/nonmatchings/psxsdk/libsnd/vmanager", SetAutoPan);

struct _ss_spu_vm_rec_struct {
    u32 pad[2];
    u32 D_8003BD50;
};

extern struct _ss_spu_vm_rec_struct _ss_spu_vm_rec;

extern s16 _svm_vcf;
extern s16 _svm_orev1;
extern s16 _svm_orev2;
extern s8 _svm_auto_kof_mode;

void SpuVmInit(u8 arg0) {
    u16 temp_v1;
    u16 var_a1;
    s32 var_v1;
    u16* temp_a0;
    s32 var_a0;
    s32 bitsUpper;
    s32 bitsLower;
    u16 temp;
    _spu_setInTransfer(0);
    _svm_vcf = 0;
    _svm_damper = 0;
    SpuInitMalloc(0x20, &_ss_spu_vm_rec.D_8003BD50);
    for (var_a1 = 0; var_a1 < 8 * NUM_SPU_CHANNELS; var_a1++) {
        _svm_sreg_buf.raw[var_a1] = 0;
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
        temp_a0 = &D_80032F10[temp];
        temp_a0[3] = 0x200;
        temp_a0[2] = 0x1000;
        temp_a0[4] = 0x80FF;
        temp_a0[0] = 0;
        temp_a0[1] = 0;
        temp_a0[5] = 0x4000;

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

        _svm_okof1 = bitsLower | _svm_okof1;
        _svm_okof2 = bitsUpper | _svm_okof2;

        _svm_okon1 = _svm_okon1 & ~_svm_okof1;
        _svm_okon2 = _svm_okon2 & ~_svm_okof2;
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
            _svm_voice[i & 0xff].unk1b = 0;
            _svm_voice[i & 0xff].unk04 = 0;
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
    s32 temp_lo;
    s32 temp_v0_2;
    u16 temp_v1;
    u16 pbend;
    s32 var_v0_2;
    u16 temp_a1;
    u16 note;
    temp_t1 = amount + 0xFFC0U;
    if (((_svm_voice[voice].unke == seq_sep_no) &&
         (_svm_voice[voice].vabId == vabId)) &&
        (_svm_voice[voice].prog == program)) {
        temp_a1 = _svm_voice[voice].note;
        temp_v1 =
            _svm_voice[voice].tone + (_svm_cur.field_7_fake_program * 0x10);
        if (temp_t1 > 0) {
            do {
                note = temp_a1 + ((temp_t1 * _svm_tn[temp_v1].pbmax) / 63);
            } while (0);
            pbend = ((temp_t1 * _svm_tn[temp_v1].pbmax) % 63) * 2;
        } else {
            note = temp_a1;
            if (temp_t1 < 0) {
                temp_lo = temp_t1 * _svm_tn[temp_v1].pbmin;
                var_v0_2 = temp_lo;
                if (temp_lo < 0) {
                    var_v0_2 = temp_lo + 0x3F;
                }
                temp_v0_2 = var_v0_2 >> 6;
                note = temp_v0_2;
                note = (temp_a1 + note) - 1;
                pbend = ((temp_lo - (temp_v0_2 << 6)) * 2) + 0x7F;
            } else {
                pbend = 0;
            }
        }
        _svm_cur.field_C_vag_idx = _svm_voice[voice].tone;
        _svm_cur.field_0x1a = voice;
        _svm_sreg_buf.buf[voice].field_4_pitch = note2pitch2(note, pbend);
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

INCLUDE_ASM("main/nonmatchings/psxsdk/libsnd/vmanager", SpuVmFlush);

INCLUDE_ASM("main/nonmatchings/psxsdk/libsnd/vmanager", SpuVmKeyOn);

s32 SpuVmKeyOff(s16 arg0, s16 vabId, s16 prog, s32 note) {
    s32 bitsUpper;
    s32 bitsLower;
    u8 var_t0;
    s32 var_t1;
    u16 temp_v1;
    u8 pad[2];

    var_t0 = 0;
    var_t1 = 0;
    if (spuVmMaxVoice != 0) {
        do {
            if ((_svm_voice[var_t0].note == (note & 0xFFFF)) &&
                (_svm_voice[var_t0].prog == prog) &&
                (_svm_voice[var_t0].unke == arg0) &&
                (_svm_voice[var_t0].vabId == vabId)) {
                if (_svm_voice[var_t0].unk0 == 0xFF) {
                    _svm_voice[var_t0].unk1b = 0;
                    _svm_voice[var_t0].unk04 = 0;
                    D_80032F10[202] = 0;
                    D_80032F10[203] = 0;
                } else {
                    _svm_cur.field_0x1a = var_t0;
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

                    _svm_okof1 = bitsLower | _svm_okof1;
                    _svm_okof2 = bitsUpper | _svm_okof2;

                    _svm_okon1 = _svm_okon1 & ~_svm_okof1;
                    _svm_okon2 = _svm_okon2 & ~_svm_okof2;
                }
                var_t1 += 1;
            }
            var_t0 += 1;
        } while (var_t0 < spuVmMaxVoice);
    }
    return var_t1;
}

void SpuVmSeKeyOn(s16 arg0, s16 arg1, u16 arg2, s32 arg3, u16 arg4, u16 arg5) {
    u16 var_v1;
    u16 var_a1;

    if (arg4 == arg5) {
        var_v1 = 0x40;
        var_a1 = arg4;
    } else if (arg5 < arg4) {
        var_a1 = arg4;
        var_v1 = (arg5 << 6) / arg4;
    } else {
        var_a1 = arg5;
        var_v1 = 0x7F - ((arg4 << 6) / arg5);
    }
    SpuVmKeyOn(0x21, arg0, arg1, arg2, var_a1, var_v1);
}

void SpuVmSeKeyOff(s16 arg0, s16 arg1, u16 arg2) {
    SpuVmKeyOff(0x21, arg0, arg1, arg2);
}

void KeyOnCheck(void) {}

s32 SpuVmSetSeqVol(s16 seq_sep_no, u16 voll, u16 volr, s16 arg3) {
    s16 voice;
    struct SeqStruct* temp_v1;
    int voll_mul;
    int volr_mul;
    u8 pad[4];
    int temp;
    s16 pos;
    temp_v1 = &_ss_score[seq_sep_no & 0xFF][(seq_sep_no >> 8) & 0xff];
    _svm_cur.field_16_vag_idx = seq_sep_no;
    temp_v1->unk74 = voll;
    temp_v1->unk76 = volr;
    temp = seq_sep_no;
    if (temp_v1->unk74 >= 0x80) {
        temp_v1->unk74 = 0x7F;
    }
    if (temp_v1->unk76 >= 0x80) {
        temp_v1->unk76 = 0x7F;
    }
    voll_mul = voll * 0x81;
    volr_mul = volr * 0x81;

    if (arg3 == 1) {
        for (voice = 0; voice < spuVmMaxVoice; voice++) {
            if ((u16)_svm_voice[voice].unke == (u16)temp) {
                pos = voice * 8;
                _svm_sreg_buf.raw[pos + 0] = voll_mul;
                _svm_sreg_buf.raw[pos + 1] = volr_mul;
                _svm_sreg_dirty[voice] = _svm_sreg_dirty[voice] | 3;
            }
        }
    }
    return _svm_cur.field_16_vag_idx;
}

s32 SpuVmGetSeqVol(s16 arg0, s16* arg1, s16* arg2) {
    struct SeqStruct* temp_v0;
    temp_v0 = &_ss_score[arg0 & 0xFF][(arg0 & 0xFF00) >> 8];
    _svm_cur.field_16_vag_idx = arg0;
    *arg1 = temp_v0->unk74;
    *arg2 = temp_v0->unk76;
    return _svm_cur.field_16_vag_idx;
}

s16 SpuVmGetSeqLVol(s16 arg0) {
    struct SeqStruct* new_var;
    new_var = _ss_score[arg0 & 0xFF];
    _svm_cur.field_16_vag_idx = arg0;
    return new_var[((s32)(arg0 & 0xFF00)) >> 8].unk74;
}

s16 SpuVmGetSeqRVol(s16 arg0) {
    struct SeqStruct* new_var;
    new_var = _ss_score[arg0 & 0xFF];
    _svm_cur.field_16_vag_idx = arg0;
    return new_var[((s32)(arg0 & 0xFF00)) >> 8].unk76;
}

void SpuVmSeqKeyOff(s16 arg0) {
    u8 voice;
    s32 bitsUpper;
    s32 bitsLower;
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

            _svm_okof1 = bitsLower | _svm_okof1;
            _svm_okof2 = bitsUpper | _svm_okof2;

            _svm_okon1 = _svm_okon1 & ~_svm_okof1;
            _svm_okon2 = _svm_okon2 & ~_svm_okof2;
        }
    }
}

s32 SpuVmSetProgVol(s16 arg0, s16 arg1, u8 arg2) {
    if (!SpuVmVSetUp(arg0, arg1)) {
        _svm_pg[arg1].mvol = arg2;
        return _svm_pg[arg1].mvol;
    }
    return -1;
}

s32 SpuVmGetProgVol(s16 arg0, s16 arg1) {
    if (!(SpuVmVSetUp(arg0, arg1))) {
        return _svm_pg[arg1].mvol;
    } else {
        return -1;
    }
}

s32 SpuVmSetProgPan(s16 arg0, s16 arg1, u8 pan) {
    if (!SpuVmVSetUp(arg0, arg1)) {
        _svm_pg[arg1].mpan = pan;
        return _svm_pg[arg1].mpan;
    }
    return -1;
}

s32 SpuVmGetProgPan(s16 arg0, s16 arg1) {
    if (!(SpuVmVSetUp(arg0, arg1))) {
        return _svm_pg[arg1].mpan;
    } else {
        return -1;
    }
}

INCLUDE_ASM("main/nonmatchings/psxsdk/libsnd/vmanager", SpuVmSetVol);

s16 SsUtKeyOn(
    s16 vabId, s16 prog, s16 tone, s16 note, s16 fine, s16 voll, s16 volr) {
    VagAtr* vagAtr;
    s16 vag;
    char vag_idx;
    ProgAtr* progAtr;
    s32 program;
    s16 voice;
    if (_snd_ev_flag == 1) {
        return -1;
    }
    _snd_ev_flag = 1;

    if ((SpuVmVSetUp(vabId, prog) == 0)) {
        _svm_cur.field_16_vag_idx = 0x21;
        _svm_cur.field_2_note = note;
        _svm_cur.field_0x3 = fine;
        _svm_cur.field_C_vag_idx = tone;
        if (voll == volr) {
            _svm_cur.field_0x5 = 0x40;
            _svm_cur.field_4_voll = voll;
        } else if (volr < voll) {
            _svm_cur.field_4_voll = voll;
            _svm_cur.field_0x5 = (volr * 64) / voll;
        } else {
            _svm_cur.field_4_voll = volr;
            _svm_cur.field_0x5 = 0x7F - ((voll * 64) / volr);
        }
        progAtr = &_svm_pg[prog];
        _svm_cur.field_A_mvol = progAtr->mvol;
        _svm_cur.field_B_mpan = progAtr->mpan;
        _svm_cur.field_0_sep_sep_no_tonecount = progAtr->tones;
        vagAtr = &_svm_tn[_svm_cur.field_C_vag_idx +
                          (_svm_cur.field_7_fake_program * 0x10)];
        _svm_cur.field_F_prior = vagAtr->prior;
        vag = (u16)vagAtr->vag;
        _svm_cur.field_18_voice_idx = vag;
        _svm_cur.field_D_vol = vagAtr->vol;
        _svm_cur.field_E_pan = vagAtr->pan;
        _svm_cur.field_10_centre = vagAtr->center;
        _svm_cur.field_11_shift = vagAtr->shift;
        _svm_cur.field_14_seq_sep_no = vagAtr->mode;
        _svm_cur.field_12_mode = vagAtr->min;
        _svm_cur.field_0x13 = vagAtr->max;
        if (vag == 0) {
            _snd_ev_flag = 0;
            return -1;
        }
    } else {
        _snd_ev_flag = 0;
        return -1;
    }

    voice = SpuVmAlloc(vag);

    if (voice == spuVmMaxVoice) {
        _snd_ev_flag = 0;
        return -1;
    }

    _svm_cur.field_0x1a = voice;
    _svm_voice[voice].unke = 0x21;
    _svm_voice[voice].vabId = vabId;
    program = _svm_cur.field_7_fake_program;
    _svm_voice[voice].prog = prog;
    _svm_voice[voice].unk10 = program;
    _svm_voice[voice].unk0 = _svm_cur.field_18_voice_idx;
    vag_idx = _svm_cur.field_C_vag_idx;
    _svm_voice[voice].note = note;
    _svm_voice[voice].unk1b = 1;
    _svm_voice[voice].unk2 = 0;
    _svm_voice[voice].tone = vag_idx;
    SpuVmDoAllocate();
    if (_svm_cur.field_18_voice_idx == 0xFF) {
        vmNoiseOn(voice & 0xFF);
    } else {
        SpuVmKeyOnNow(1, note2pitch2(note, fine) & 0xFFFF);
    }
    _snd_ev_flag = 0;
    return voice;
}

short SsUtKeyOff(s16 voice, s16 vabId, s16 prog, s16 tone, s16 note) {
    unsigned char new_var;
    s16 bitsUpper;
    s16 bitsLower;
    u16 temp_v1;
    if (_snd_ev_flag != 1) {
        _snd_ev_flag = 1;
        if ((voice >= 0) && (voice < 24)) {
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
                    _svm_okof1 = bitsLower | _svm_okof1;
                    _svm_okof2 = bitsUpper | _svm_okof2;
                    _svm_okon1 = _svm_okon1 & (~_svm_okof1);
                    _svm_okon2 = _svm_okon2 & (~_svm_okof2);
                }
                _snd_ev_flag = 0;
                return 0;
            }
        }
        _snd_ev_flag = 0;
    }
    return -1;
}

s16 SsUtKeyOnV(s16 voice, s16 vabId, s16 prog, s16 tone, s16 note, s16 fine,
               s16 voll, s16 volr) {
    VagAtr* vagAtr;
    u16 vag;
    char vag_idx;
    ProgAtr* progAtr;
    s32 program;
    if (_snd_ev_flag == 1) {
        return -1;
    }
    _snd_ev_flag = 1;
    if (((voice >= 0) && (voice <= 23)) && (SpuVmVSetUp(vabId, prog) == 0)) {
        _svm_cur.field_16_vag_idx = 0x21;
        _svm_cur.field_2_note = note;
        _svm_cur.field_0x3 = fine;
        _svm_cur.field_C_vag_idx = tone;
        if (voll == volr) {
            _svm_cur.field_0x5 = 0x40;
            _svm_cur.field_4_voll = voll;
        } else if (volr < voll) {
            _svm_cur.field_4_voll = voll;
            _svm_cur.field_0x5 = (volr * 64) / voll;
        } else {
            _svm_cur.field_4_voll = volr;
            _svm_cur.field_0x5 = 0x7F - ((voll * 64) / volr);
        }
        progAtr = &_svm_pg[prog];
        _svm_cur.field_A_mvol = progAtr->mvol;
        _svm_cur.field_B_mpan = progAtr->mpan;
        _svm_cur.field_0_sep_sep_no_tonecount = progAtr->tones;
        vagAtr = &_svm_tn[_svm_cur.field_C_vag_idx +
                          (_svm_cur.field_7_fake_program * 0x10)];
        _svm_cur.field_F_prior = vagAtr->prior;
        vag = vagAtr->vag;
        _svm_cur.field_18_voice_idx = vag;
        _svm_cur.field_D_vol = vagAtr->vol;
        _svm_cur.field_E_pan = vagAtr->pan;
        _svm_cur.field_10_centre = vagAtr->center;
        _svm_cur.field_11_shift = vagAtr->shift;
        _svm_cur.field_14_seq_sep_no = vagAtr->mode;
        _svm_cur.field_12_mode = vagAtr->min;
        _svm_cur.field_0x13 = vagAtr->max;
    } else {
        _snd_ev_flag = 0;
        return -1;
    }

    if (vag == 0) {
        _snd_ev_flag = 0;
        return -1;
    }

    _svm_cur.field_0x1a = voice;
    _svm_voice[voice].unke = 0x21;
    _svm_voice[voice].vabId = vabId;
    program = _svm_cur.field_7_fake_program;
    _svm_voice[voice].prog = prog;
    _svm_voice[voice].unk10 = program;
    _svm_voice[voice].unk0 = _svm_cur.field_18_voice_idx;
    vag_idx = _svm_cur.field_C_vag_idx;
    _svm_voice[voice].note = note;
    _svm_voice[voice].unk1b = 1;
    _svm_voice[voice].unk2 = 0;
    _svm_voice[voice].tone = vag_idx;
    SpuVmDoAllocate();
    if (_svm_cur.field_18_voice_idx == 0xFF) {
        vmNoiseOn(voice & 0xFF);
    } else {
        SpuVmKeyOnNow(1, note2pitch2(note, fine) & 0xFFFF);
    }
    _snd_ev_flag = 0;
    return voice;
}

s32 SsUtKeyOffV(u16 arg0) {
    s32 bitsUpper;
    s32 bitsLower;
    u16 temp2;

    if (_snd_ev_flag != 1) {
        _snd_ev_flag = 1;
        if (arg0 < 24) {
            _svm_cur.field_0x1a = arg0;
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

            _svm_okof1 = bitsLower | _svm_okof1;
            _svm_okof2 = bitsUpper | _svm_okof2;

            _svm_okon1 = _svm_okon1 & ~_svm_okof1;
            _svm_okon2 = _svm_okon2 & ~_svm_okof2;
            return 0;
        }
        _snd_ev_flag = 0;
        return -1;
    }
    return -1;
}

s16 SsUtPitchBend(s16 voice, s16 vabId, s16 prog, s16 note, s16 pbend) {
    SpuVmVSetUp(vabId, prog);
    _svm_cur.field_16_vag_idx = 0x21;
    return -((SpuVmPBVoice(voice, 0x21, vabId, prog, pbend) << 0x10) == 0);
}

short SsUtChangePitch(short voice, short vabId, short prog, short old_note,
                      short old_fine, short new_note, short new_fine) {
    if (voice >= 0 && voice < 24) {
        if (_svm_voice[voice].vabId == vabId) {
            if (_svm_voice[voice].prog == prog) {
                if (_svm_voice[voice].note == old_note) {
                    SpuVmVSetUp(
                        _svm_voice[voice].vabId, _svm_voice[voice].prog);
                    _svm_cur.field_16_vag_idx = 0x21;
                    _svm_cur.field_0x1a = voice;
                    _svm_cur.field_C_vag_idx = _svm_voice[voice].tone;
                    _svm_sreg_buf.buf[voice].field_4_pitch =
                        note2pitch2((u16)new_note, (u16)new_fine);
                    _svm_sreg_dirty[voice] = _svm_sreg_dirty[voice] | 4;
                    return 0;
                }
            }
        }
    }
    return -1;
}

s16 SsUtChangeADSR(
    s16 vc, s16 vabId, s16 prog, s16 old_note, u16 adsr1, u16 adsr2) {
    u8 pad[2];
    if (vc >= 0 && vc < NUM_SPU_CHANNELS) {
        if ((_svm_voice[vc].vabId == vabId) && _svm_voice[vc].prog == prog) {
            if (_svm_voice[vc].note == old_note) {
                _svm_sreg_buf.buf[vc].field_8_adsr1 = adsr1;
                _svm_sreg_buf.buf[vc].field_A_adsr2 = adsr2;
                _svm_sreg_dirty[vc] = _svm_sreg_dirty[vc] | 0x30;
                return 0;
            }
        }
    }
    return -1;
}

s16 SsUtGetDetVVol(s16 vc, s16* voll, s16* volr) {
    if (vc >= 0 && vc < NUM_SPU_CHANNELS) {
        *voll = D_80032F10[vc * 8 + 0];
        *volr = D_80032F10[vc * 8 + 1];
        return 0;
    }
    return -1;
}

s32 SsUtSetDetVVol(s16 arg0, s16 arg1, s16 arg2) {
    s32 temp[2];
    if (arg0 >= 0 && arg0 < NUM_SPU_CHANNELS) {
        _svm_sreg_buf.buf[arg0].field_0_vol_left = arg1;
        _svm_sreg_buf.buf[arg0].field_2_vol_right = arg2;
        _svm_sreg_dirty[arg0] = _svm_sreg_dirty[arg0] | 3;
        return 0;
    }

    return -1;
}

s16 SsUtGetVVol(s16 vc, s16* voll, s16* volr) {
    struct Unk* temp_v1;
    s16 temp1;
    s16 temp2;
    s16* temp;

    if (vc >= 0 && vc < NUM_SPU_CHANNELS) {
        temp = &D_80032F10[vc * 8];
        temp1 = temp[0];
        temp2 = temp[1];
        *voll = temp1 / 129;
        *volr = temp2 / 129;
        return 0;
    }
    return -1;
}

s16 SsUtSetVVol(s16 vc, s16 voll, s16 volr) {
    s32 temp[2];
    if (vc >= 0 && vc < NUM_SPU_CHANNELS) {
        voll *= 129;
        volr *= 129;
        _svm_sreg_buf.buf[vc].field_2_vol_right = volr;
        _svm_sreg_buf.buf[vc].field_0_vol_left = voll;
        _svm_sreg_dirty[vc] = _svm_sreg_dirty[vc] | 3;
        return 0;
    }

    return -1;
}

s16 SsUtAutoVol(s16 vc, s16 start_vol, s16 end_vol, s16 delta_time) {
    if (!(vc >= 0x18U)) {
        SeAutoVol(vc, start_vol, end_vol, delta_time);
        return 0;
    }
    return -1;
}

s16 SsUtAutoPan(s16 vc, s16 start_pan, s16 end_pan, s16 delta_time) {
    if (!(vc >= 0x18U)) {
        SeAutoPan(vc, start_pan, end_pan, delta_time);
        return 0;
    }
    return -1;
}

void SsUtAllKeyOff(void) {
    s16 voice;
    s32 bitsUpper;
    s32 bitsLower;
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

        _svm_okof1 = bitsLower | _svm_okof1;
        _svm_okof2 = bitsUpper | _svm_okof2;

        _svm_okon1 = _svm_okon1 & ~_svm_okof1;
        _svm_okon2 = _svm_okon2 & ~_svm_okof2;
    }
}
