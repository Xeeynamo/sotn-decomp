// SPDX-License-Identifier: MIT
#include "common.h"
#include "libsnd_i.h"

void _SsGetMetaEvent(s16, s16, u8);
void _SsNoteOn(s16, s16, s32, s32);
s32 _SsReadDeltaValue(s16, s16);
void _SsSetPitchBend(s16, s16);
void _SsSetProgramChange(s16, s16, u8);
void _SsGetSeqData(s16, s16);
void _SsContPortamento(s16, s16, u8);
void _SsSndSetVabAttr(s16, s16, s16, VagAtr, struct Unk, short, unsigned char);
void _SsSetControlChange(s16, s16, u8);
void _SsContDataEntry(s16, s16, u8);
void _SsContNrpn2(s16, s16, u8);
void _SsContRpn1(s16, s16, u8);
void _SsContRpn2(s16, s16, u8);
void _SsContResetAll(s16, s16);
void _SsContNrpn1(s16, s16, s16);
void SpuVmDamperOff();
void SpuVmDamperOn();
void SpuVmSetProgVol(s16, u8, u8);
void SpuVmSetVol(s32, s16, u8, s16, s32);
void SpuVmKeyOff(s16, s16, u8, s32);
void SpuVmKeyOn(s16, s16, u8, s32, s32, s32);
void SpuVmPitchBend(s32, s16, u8, u8);

void _SsSeqPlay(s16 arg0, s16 arg1) {
    struct SeqStruct* temp_s1;
    s32 var_s0;

    temp_s1 = &_ss_score[arg0][arg1];
    if (temp_s1->delta_value - temp_s1->unk70 > 0) {
        if (temp_s1->unk6E > 0) {
            temp_s1->unk6E--;
        } else if (temp_s1->unk6E == 0) {
            temp_s1->unk6E = temp_s1->unk70;
            temp_s1->delta_value--;
        } else {
            temp_s1->delta_value -= temp_s1->unk70;
        }
    } else if (temp_s1->delta_value <= temp_s1->unk70) {
        var_s0 = temp_s1->delta_value;
        do {
            do {
                _SsGetSeqData(arg0, arg1);
            } while (temp_s1->delta_value == 0);
            var_s0 += temp_s1->delta_value;
        } while (var_s0 < temp_s1->unk70);
        temp_s1->delta_value = var_s0 - temp_s1->unk70;
    }
}

void _SsGetSeqData(s16 arg0, s16 arg1) {
    struct SeqStruct* score;
    u8 temp_s0;
    u8 temp_s0_2;
    u8 var_s3;

    score = &_ss_score[arg0][arg1];
    temp_s0 = *score->read_pos++;
    if (temp_s0 & 0x80) {
        score->channel = temp_s0 & 0xF;
        switch (temp_s0 & 0xF0) {
        case 0x90:
            score->unk11 = 0x90;
            temp_s0_2 = *score->read_pos++;
            var_s3 = *score->read_pos++;
            score->delta_value = _SsReadDeltaValue(arg0, arg1);
            _SsNoteOn(arg0, arg1, temp_s0_2, var_s3);
            return;
        case 0xB0:
            score->unk11 = 0xB0;
            _SsSetControlChange(arg0, arg1, *score->read_pos++);
            return;
        case 0xC0:
            score->unk11 = 0xC0;
            _SsSetProgramChange(arg0, arg1, *score->read_pos++);
            return;
        case 0xE0:
            score->unk11 = 0xE0;
            score->read_pos++;
            _SsSetPitchBend(arg0, arg1);
            return;
        case 0xF0:
            score->unk11 = 0xFF;
            score->channel = temp_s0 & 0xF;
            _SsGetMetaEvent(arg0, arg1, *score->read_pos++);
            return;
        }
    } else {
        switch (score->unk11) {
        case 0x90:
            var_s3 = *score->read_pos++;
            score->delta_value = _SsReadDeltaValue(arg0, arg1);
            _SsNoteOn(arg0, arg1, temp_s0, var_s3);
            return;
        case 0xB0:
            _SsSetControlChange(arg0, arg1, temp_s0);
            return;
        case 0xC0:
            _SsSetProgramChange(arg0, arg1, temp_s0);
            return;
        case 0xE0:
            _SsSetPitchBend(arg0, arg1);
            return;
        case 0xFF:
            _SsGetMetaEvent(arg0, arg1, temp_s0);
            return;
        }
    }
}

void _SsNoteOn(s16 arg0, s16 arg1, s32 arg2, s32 arg3) {
    s32 temp_a0;
    s32 temp_s1;
    u8 channel;
    u8 pan;
    struct SeqStruct* temp_s0;
    temp_s0 = &_ss_score[arg0][arg1];
    pan = arg3;
    channel = temp_s0->channel;
    temp_s1 = pan & 0xFF;
    pan = temp_s0->panpot[channel];
    if ((!((temp_s0->padaa >> channel) & 1)) && (temp_s0->unk74 != 0)) {
        if (arg3 & 0xFF) {
            SpuVmKeyOn(arg0 | (arg1 << 8), temp_s0->unk4c,
                       temp_s0->programs[channel], arg2 & 0xFF, temp_s1, pan);
            temp_s0->padA6 = temp_s1;
            return;
        }
        SpuVmKeyOff(arg0 | (arg1 << 8), temp_s0->unk4c,
                    temp_s0->programs[channel], arg2 & 0xFF);
    }
}

void _SsSetProgramChange(s16 arg0, s16 arg1, u8 arg2) {
    struct SeqStruct* temp_s0;
    temp_s0 = &_ss_score[arg0][arg1];
    temp_s0->programs[temp_s0->channel] = arg2;
    temp_s0->delta_value = _SsReadDeltaValue(arg0, arg1);
}

void _SsSetControlChange(s16 arg0, s16 arg1, u8 control) {
    s16 val;
    s16 channel;
    struct SeqStruct* score;

    score = &_ss_score[arg0][arg1];
    channel = score->channel;
    val = *score->read_pos++;
    switch (control) {
    case 0x0:
        score->unk4c = val;
        score->delta_value = _SsReadDeltaValue(arg0, arg1);
        return;
    case 0x6:
        _SsContDataEntry(arg0, arg1, val);
        return;
    case 0x7:
        SpuVmSetVol((arg1 << 8) | arg0, score->unk4c, score->programs[channel],
                    val, score->panpot[channel]);
        score->vol[channel] = val;
        score->delta_value = _SsReadDeltaValue(arg0, arg1);
        return;
    case 0xA:
        SpuVmSetVol((arg1 << 8) | arg0, score->unk4c, score->programs[channel],
                    score->vol[channel], val);
        score->panpot[channel] = val;
        score->delta_value = _SsReadDeltaValue(arg0, arg1);
        return;
    case 0xB:
        SpuVmSetProgVol(score->unk4c, score->programs[channel], val);
        SpuVmSetVol((arg1 << 8) | arg0, score->unk4c, score->programs[channel],
                    score->vol[channel], score->panpot[channel]);
        score->delta_value = _SsReadDeltaValue(arg0, arg1);
        return;
    case 0x40:
        if (val < 0x40U) {
            SpuVmDamperOff();
        } else {
            SpuVmDamperOn();
        }
        score->delta_value = _SsReadDeltaValue(arg0, arg1);
        return;
    case 0x41:
        _SsContPortamento(arg0, arg1, val);
        return;
    case 0x5B:
        SsUtSetReverbDepth(val, val);
        score->delta_value = _SsReadDeltaValue(arg0, arg1);
        return;
    case 0x62:
        _SsContNrpn1(arg0, arg1, val);
        return;
    case 0x63:
        _SsContNrpn2(arg0, arg1, val);
        return;
    case 0x64:
        _SsContRpn1(arg0, arg1, val);
        return;
    case 0x65:
        _SsContRpn2(arg0, arg1, val);
        return;
    case 0x79:
        _SsContResetAll(arg0, arg1);
        return;
    default:
        score->delta_value = _SsReadDeltaValue(arg0, arg1);
        return;
    }
}

void _SsContModulation(s16 arg0, s16 arg1, u8 arg2) {
    ProgAtr progAtr;
    VagAtr vagAtr;
    s32 toneNum;
    struct SeqStruct* score;
    u8 channel;

    score = &_ss_score[arg0][arg1];
    channel = score->channel;
    SsUtGetProgAtr(score->unk4c, score->programs[channel], &progAtr);
    for (toneNum = 0; toneNum < progAtr.tones; toneNum++) {
        SsUtGetVagAtr(score->unk4c, score->programs[channel], toneNum, &vagAtr);
        vagAtr.vibW = arg2;
        SsUtSetVagAtr(score->unk4c, score->programs[channel], toneNum, &vagAtr);
    }
    score->delta_value = _SsReadDeltaValue(arg0, arg1);
}

void _SsContPortaTime(s16 arg0, s16 arg1, u8 arg2) {
    ProgAtr progAtr;
    VagAtr vagAtr;
    s32 toneNum;
    struct SeqStruct* score;
    u8 channel;

    score = &_ss_score[arg0][arg1];
    channel = score->channel;
    SsUtGetProgAtr(score->unk4c, score->programs[channel], &progAtr);
    for (toneNum = 0; toneNum < progAtr.tones; toneNum++) {
        SsUtGetVagAtr(score->unk4c, score->programs[channel], toneNum, &vagAtr);
        vagAtr.porT = arg2;
        SsUtSetVagAtr(score->unk4c, score->programs[channel], toneNum, &vagAtr);
    }
    score->delta_value = _SsReadDeltaValue(arg0, arg1);
}

void _SsContPortamento(s16 arg0, s16 arg1, u8 arg2) {
    ProgAtr progAtr;
    VagAtr vagAtr;
    s32 toneNum;
    u8 channel;
    struct SeqStruct* score;

    score = &_ss_score[arg0][arg1];
    channel = score->channel;
    SsUtGetProgAtr(score->unk4c, score->programs[channel], &progAtr);
    for (toneNum = 0; toneNum < progAtr.tones; toneNum++) {
        SsUtGetVagAtr(score->unk4c, score->programs[channel], toneNum, &vagAtr);
        if (arg2 >= 0 && arg2 < 0x40) {
            vagAtr.mode = 2;
        } else if (arg2 >= 0x40 && arg2 < 0x80) {
            vagAtr.mode = 0;
        }
        SsUtSetVagAtr(score->unk4c, score->programs[channel], toneNum, &vagAtr);
    }

    score->delta_value = _SsReadDeltaValue(arg0, arg1);
}

void _SsContResetAll(s16 arg0, s16 arg1) {
    struct SeqStruct* score;

    score = &_ss_score[arg0][arg1];
    SsUtReverbOff();
    SpuVmDamperOff();
    score->programs[score->channel] = score->channel;
    score->unk13 = 0;
    score->unk14 = 0;
    score->vol[score->channel] = 0x7f;
    score->panpot[score->channel] = 0x40;
    score->delta_value = _SsReadDeltaValue(arg0, arg1);
}

typedef void (*SndSsMarkCallbackProc)(short seq_no, short sep_no, short data);

extern SndSsMarkCallbackProc _SsMarkCallback[32][16];

void _SsContNrpn1(s16 arg0, s16 arg1, s16 arg2) {
    SndSsMarkCallbackProc temp_v0;
    struct SeqStruct* temp_s0;
    temp_s0 = &_ss_score[arg0][arg1];
    if ((temp_s0->unk27 == 1) && (temp_s0->unk10 == 0)) {
        temp_s0->unk28 = arg2;
        temp_s0->unk10 = 1U;
    } else {
        if (temp_s0->unk16 != 0x1E) {
            if (temp_s0->unk16 != 0x14) {
                temp_s0->unk15 = arg2;
                temp_s0->unk2a++;
            }
        }
    }
    if (temp_s0->unk16 == 0x28) {
        temp_v0 = _SsMarkCallback[arg0][arg1];
        if (temp_v0 != NULL) {
            temp_v0(arg0, arg1, arg2 & 0xFF);
        }
    }
    temp_s0->delta_value = _SsReadDeltaValue(arg0, arg1);
}

#define NRPN_LOOP_START 20
#define NRPN_LOOP_END 30

void _SsContNrpn2(s16 arg0, s16 arg1, u8 arg2) {
    struct SeqStruct* temp_s0;

    temp_s0 = &_ss_score[arg0][arg1];
    switch (arg2) {
    case NRPN_LOOP_START:
        temp_s0->unk16 = arg2;
        temp_s0->unk27 = 1;
        temp_s0->delta_value = _SsReadDeltaValue(arg0, arg1);
        temp_s0->loop_pos = temp_s0->read_pos;
        break;

    case NRPN_LOOP_END:
        temp_s0->unk16 = arg2;
        if (temp_s0->unk28 == 0) {
            temp_s0->unk10 = 0;
            temp_s0->delta_value = _SsReadDeltaValue(arg0, arg1);
        } else if (temp_s0->unk28 < 0x7FU) {
            temp_s0->unk28--;
            temp_s0->delta_value = _SsReadDeltaValue(arg0, arg1);
            if (temp_s0->unk28 != 0) {
                temp_s0->read_pos = temp_s0->loop_pos;
            } else {
                temp_s0->unk10 = 0;
            }
        } else {
            _SsReadDeltaValue(arg0, arg1);
            temp_s0->delta_value = 0;
            temp_s0->read_pos = temp_s0->loop_pos;
        }
        break;

    default:
        temp_s0->unk16 = arg2;
        temp_s0->unk2a += 1;
        temp_s0->delta_value = _SsReadDeltaValue(arg0, arg1);
        break;
    }
}

void _SsContRpn1(s16 arg0, s16 arg1, u8 arg2) {
    struct SeqStruct* temp_s0;

    temp_s0 = &_ss_score[arg0][arg1];
    temp_s0->unk13 = arg2;
    temp_s0->unk29 += 1;
    temp_s0->delta_value = _SsReadDeltaValue(arg0, arg1);
}

void _SsContRpn2(s16 arg0, s16 arg1, u8 arg2) {
    struct SeqStruct* temp_s0;

    temp_s0 = &_ss_score[arg0][arg1];
    temp_s0->unk14 = arg2;
    temp_s0->unk29 += 1;
    temp_s0->delta_value = _SsReadDeltaValue(arg0, arg1);
}

INCLUDE_ASM("main/nonmatchings/psxsdk/libsnd/seqread", _SsContDataEntry);

#define DE_PRIORITY 0
#define DE_MODE 1
#define DE_LIMITL 2
#define DE_LIMITH 3
#define DE_ADSR_AR_L 4
#define DE_ADSR_AR_E 5
#define DE_ADSR_DR 6
#define DE_ADSR_SL 7
#define DE_ADSR_SR_L 8
#define DE_ADSR_SR_E 9
#define DE_ADSR_RR_L 10
#define DE_ADSR_RR_E 11
#define DE_ADSR_SR 12
#define DE_VIB_TIME 13
#define DE_PORTA_DEPTH 14
#define DE_REV_TYPE 15
#define DE_REV_DEPTH 16
#define DE_ECHO_FB 17
#define DE_ECHO_DELAY 18
#define DE_DELAY 19

void _SsSndSetVabAttr(s16 vabId, s16 progNum, s16 toneNum, VagAtr vagAtr,
                      struct Unk adsrBuffer, short idx, unsigned char attr) {
    SsUtGetVagAtr(vabId, progNum, toneNum, &vagAtr);
    switch (idx) {
    case DE_PRIORITY:
        vagAtr.prior = attr;
        SsUtSetVagAtr(vabId, progNum, toneNum, &vagAtr);
        break;
    case DE_MODE:
        vagAtr.mode = attr;
        SsUtSetVagAtr(vabId, progNum, toneNum, &vagAtr);

        if (attr == 0) {
            SsUtReverbOff();
        } else if (attr == 1) {
        } else if (attr == 2) {
        } else if (attr == 3) {
        } else if (attr == 4) {
            SsUtReverbOn();
        }
        break;
    case DE_LIMITL:
        vagAtr.min = attr;
        SsUtSetVagAtr(vabId, progNum, toneNum, &vagAtr);
        break;
    case DE_LIMITH:
        vagAtr.max = attr;
        SsUtSetVagAtr(vabId, progNum, toneNum, &vagAtr);
        break;
    case DE_ADSR_AR_L:
    case DE_ADSR_AR_E:
    case DE_ADSR_DR:
    case DE_ADSR_SL:
    case DE_ADSR_SR_L:
    case DE_ADSR_SR_E:
    case DE_ADSR_RR_L:
    case DE_ADSR_RR_E:
    case DE_ADSR_SR:
    case DE_VIB_TIME:
    case DE_PORTA_DEPTH:
        _SsUtResolveADSR(vagAtr.adsr1, vagAtr.adsr2, &adsrBuffer);
        switch (idx) {
        case DE_ADSR_AR_L:
            adsrBuffer.unkA = 0;
            adsrBuffer.unk0 = attr;
            break;
        case DE_ADSR_AR_E:
            adsrBuffer.unkA = 1;
            adsrBuffer.unk0 = attr;
            break;
        case DE_ADSR_DR:
            adsrBuffer.unk2 = attr;
            break;
        case DE_ADSR_SL:
            adsrBuffer.unk4 = attr;
            break;
        case DE_ADSR_SR_L:
            adsrBuffer.unkC = 0;
            adsrBuffer.unk6 = attr;
            break;
        case DE_ADSR_SR_E:
            adsrBuffer.unkC = 1;
            adsrBuffer.unk6 = attr;
            break;
        case DE_ADSR_RR_L:
            adsrBuffer.unkE = 0;
            adsrBuffer.unk8 = attr;
            break;
        case DE_ADSR_RR_E:
            adsrBuffer.unkE = 1;
            adsrBuffer.unk8 = attr;
            break;
        case DE_ADSR_SR:
            if (attr > 0 && attr < 0x40) {
                adsrBuffer.unk10 = 0;
            } else if (attr >= 0x40 && attr < 0x80) {
                adsrBuffer.unk10 = 1;
            }
            break;
        case DE_VIB_TIME:
            vagAtr.vibT = attr;
            break;
        case DE_PORTA_DEPTH:
            vagAtr.porW = attr;
            break;
        }

        _SsUtBuildADSR(&adsrBuffer, &vagAtr.adsr1, &vagAtr.adsr2);
        SsUtSetVagAtr(vabId, progNum, toneNum, &vagAtr);
        break;
    case DE_REV_TYPE:
        SsUtSetReverbType(attr);
        break;
    case DE_REV_DEPTH:
        SsUtSetReverbDepth(attr, attr);
        break;
    case DE_ECHO_FB:
        SsUtSetReverbFeedback(attr);
        break;
    case DE_ECHO_DELAY:
    case DE_DELAY:
        SsUtSetReverbDelay(attr);
        break;
    case 20:
    case 21:
    case 22:
        break;
    }
}

void _SsSetPitchBend(s16 arg0, s16 arg1) {
    struct SeqStruct* score;
    u8* temp_v1;
    u8 channel;
    score = &_ss_score[arg0][arg1];
    channel = score->channel;
    temp_v1 = score->read_pos++;
    SpuVmPitchBend(
        (arg1 << 8) | arg0, score->unk4c, score->programs[channel], *temp_v1);
    score->delta_value = _SsReadDeltaValue(arg0, arg1);
}

void _SsGetMetaEvent(s16 arg0, s16 arg1, u8 arg2) {
    struct SeqStruct* score;

    score = &_ss_score[arg0][arg1];
    switch (arg2) {
    case 0x51:
        score->unk8c = (*score->read_pos++) << 0x10 |
                       (*score->read_pos++) << 8 | *score->read_pos++;
        score->unk8c = 60000000 / score->unk8c;
        if ((score->unk4a * score->unk8c * 10) < VBLANK_MINUS * 60) {
            score->unk70 = score->unk6E =
                (VBLANK_MINUS * 600) / (score->unk4a * score->unk8c);
        } else {
            score->unk6E = -1;
            score->unk70 =
                (score->unk4a * score->unk8c * 10) / (VBLANK_MINUS * 60);
            if ((VBLANK_MINUS * 30) <
                (score->unk4a * score->unk8c * 10) % (VBLANK_MINUS * 60)) {
                score->unk70++;
            }
        }
        score->delta_value = _SsReadDeltaValue(arg0, arg1);
        return;
    case 0x2F:
        score->unk48++;
        if (score->unk46 == 0) {
            score->unk80 = 0;
            score->unk27 = 0;
            score->delta_value = 0;
            score->read_pos = score->next_sep_pos;
            return;
        }
        if (score->unk48 < score->unk46) {
            score->unk80 = 0;
            score->unk27 = 0;
            score->delta_value = 0;
            score->read_pos = score->next_sep_pos;
            score->loop_pos = score->next_sep_pos;
            return;
        }
        _ss_score[arg0][arg1].unk90 &= ~1;
        _ss_score[arg0][arg1].unk90 &= ~8;
        _ss_score[arg0][arg1].unk90 &= ~2;
        _ss_score[arg0][arg1].unk90 |= 0x200;
        _ss_score[arg0][arg1].unk90 |= 4;
        score->unk2b = 0;
        score->loop_pos = score->next_sep_pos;
        if (score->unk3C != 0xFF) {
            score->unk2b = 0;
            _SsSndNextSep(score->unk3C, score->unk0);
            SpuVmSeqKeyOff((arg1 << 8) | arg0);
        }
        SpuVmSeqKeyOff((arg1 << 8) | arg0);
        score->delta_value = score->unk70;
        return;
    }
}

s32 _SsReadDeltaValue(s16 arg0, s16 arg1) {
    s32 temp_v0;
    u8 temp_v1_2;
    u32 var_a0;
    struct SeqStruct* temp_a1 = &_ss_score[arg0][arg1];
    var_a0 = *temp_a1->read_pos++;
    if (var_a0 == 0) {
        return 0;
    }

    // variable length quantity decoding (midi)
    if (var_a0 & 0x80) {
        var_a0 &= 0x7F;
        do {
            temp_v1_2 = *temp_a1->read_pos++;
            var_a0 = (var_a0 << 7) + (temp_v1_2 & 0x7F);
        } while (temp_v1_2 & 0x80);
    }

    temp_v0 = var_a0 * 10;
    temp_a1->unk80 += temp_v0;
    return temp_v0;
}
