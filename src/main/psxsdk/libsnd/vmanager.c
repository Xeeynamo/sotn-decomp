#include "common.h"
#include "libsnd_i.h"

static inline u16 get_field_0x1a() { return _svm_cur.field_0x1a; }

INCLUDE_ASM("main/nonmatchings/psxsdk/libsnd/vmanager", SpuVmAlloc);

INCLUDE_ASM("main/nonmatchings/psxsdk/libsnd/vmanager", SpuVmKeyOnNow);

INCLUDE_ASM("main/nonmatchings/psxsdk/libsnd/vmanager", SpuVmDoAllocate);

INCLUDE_ASM("main/nonmatchings/psxsdk/libsnd/vmanager", vmNoiseOn);

INCLUDE_ASM("main/nonmatchings/psxsdk/libsnd/vmanager", vmNoiseOn2);

INCLUDE_ASM("main/nonmatchings/psxsdk/libsnd/vmanager", note2pitch);

INCLUDE_ASM("main/nonmatchings/psxsdk/libsnd/vmanager", note2pitch2);

INCLUDE_ASM("main/nonmatchings/psxsdk/libsnd/vmanager", SePitchBend);

void SsUtVibrateOn(void) {}

void SsUtVibrateOff(void) {}

INCLUDE_ASM("main/nonmatchings/psxsdk/libsnd/vmanager", SeAutoVol);

INCLUDE_ASM("main/nonmatchings/psxsdk/libsnd/vmanager", SetAutoVol);

INCLUDE_ASM("main/nonmatchings/psxsdk/libsnd/vmanager", SeAutoPan);

INCLUDE_ASM("main/nonmatchings/psxsdk/libsnd/vmanager", SetAutoPan);

INCLUDE_ASM("main/nonmatchings/psxsdk/libsnd/vmanager", SpuVmInit);

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

INCLUDE_ASM("main/nonmatchings/psxsdk/libsnd/vmanager", SpuVmPBVoice);

INCLUDE_ASM("main/nonmatchings/psxsdk/libsnd/vmanager", SpuVmPitchBend);

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

INCLUDE_ASM("main/nonmatchings/psxsdk/libsnd/vmanager", SpuVmSetSeqVol);

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

INCLUDE_ASM("main/nonmatchings/psxsdk/libsnd/vmanager", SpuVmSeqKeyOff);

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

INCLUDE_ASM("main/nonmatchings/psxsdk/libsnd/vmanager", SsUtKeyOn);

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

INCLUDE_ASM("main/nonmatchings/psxsdk/libsnd/vmanager", SsUtKeyOnV);

INCLUDE_ASM("main/nonmatchings/psxsdk/libsnd/vmanager", SsUtKeyOffV);

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
                    _svm_sreg_buf[voice].field_4_pitch =
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
                _svm_sreg_buf[vc].field_8_adsr1 = adsr1;
                _svm_sreg_buf[vc].field_A_adsr2 = adsr2;
                _svm_sreg_dirty[vc] = _svm_sreg_dirty[vc] | 0x30;
                return 0;
            }
        }
    }
    return -1;
}

s16 SsUtGetDetVVol(s16 vc, s16* voll, s16* volr) {
    if (vc >= 0 && vc < 24) {
        *voll = D_80032F10[vc * 8 + 0];
        *volr = D_80032F10[vc * 8 + 1];
        return 0;
    }
    return -1;
}

s32 SsUtSetDetVVol(s16 arg0, s16 arg1, s16 arg2) {
    s32 temp[2];
    if (arg0 >= 0 && arg0 < 24) {
        _svm_sreg_buf[arg0].field_0_vol_left = arg1;
        _svm_sreg_buf[arg0].field_2_vol_right = arg2;
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

    if (vc >= 0 && vc < 24) {
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
    if (vc >= 0 && vc < 24) {
        voll *= 129;
        volr *= 129;
        _svm_sreg_buf[vc].field_2_vol_right = volr;
        _svm_sreg_buf[vc].field_0_vol_left = voll;
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

INCLUDE_ASM("main/nonmatchings/psxsdk/libsnd/vmanager", SsUtAllKeyOff);
