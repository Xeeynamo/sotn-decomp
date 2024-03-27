#include "common.h"
#include "libsnd_i.h"

s16 _SsInitSoundSeq(s16 arg0, s16 vab_id, u8* addr) {
    s32 temp_lo;
    s32 tempo;
    s32 delta_value;
    s32 channel;
    u32 temp_a1_2;
    u32 temp_lo_2;
    u32 temp_lo_3;
    u32 temp_lo_4;
    struct SeqStruct* score;
    int new_var;
    u32 new_var2;
    u8 a;
    u8 b;
    u8 c;
    u8 t;
    u8 q;
    channel = 0;
    score = &_ss_score[arg0][0];
    score->unk4c = vab_id;
    score->unk4a = 0;
    score->unk13 = 0;
    score->unk14 = 0;
    score->unk29 = 0;
    score->unk15 = 0;
    score->unk16 = 0;
    score->unk2a = 0;
    score->channel = 0;
    score->unk7c = 0;
    score->unk80 = 0;
    score->unk84 = 0;
    score->unk72 = 0U;
    score->unk48 = 0;
    score->unk2b = 0;
    score->delta_value = 0;
    score->unk27 = 0;
    score->unk28 = 0;
    score->unk10 = 0;
    score->unk11 = 0;
    score->padA6 = 0x7F;
    score->padaa = 0;
    for (channel = 0; channel < 16; channel++) {
        score->programs[channel] = channel;
        score->panpot[channel] = 0x40;
        score->vol[channel] = 0x7f;
    }
    score->unk6E = 1;
    score->read_pos = addr;
    if ((score->read_pos[0] == 'S') || (score->read_pos[0] == 'p')) {
        score->read_pos += 8;
        if (addr[7] != 1) {
            printf("This is not SEQ Data.\n");
            return -1;
        }
    } else {
        printf("This is an old SEQ Data Format.\n");
        return 0;
    }
    t = *(score->read_pos++);
    q = *(score->read_pos++);
    score->unk4a = (s16)(q | (t << 8));
    a = *(score->read_pos++);
    b = *(score->read_pos++);
    c = *(score->read_pos++);
    tempo = ((a << 0x10) | (b << 8)) | c;
    temp_lo = 60000000 / tempo;
    score->unk84 = tempo;
    if (((s32)(((u32)tempo) >> 1)) < (60000000 % tempo)) {
        score->unk84 = (s32)(temp_lo + 1);
    } else {
        score->unk84 = temp_lo;
    }
    score->unk8c = score->unk84;
    score->read_pos += 2;
    delta_value = _SsReadDeltaValue(arg0, 0);
    temp_lo_2 = score->unk4a * score->unk84;
    new_var = temp_lo_2 * 10;
    score->next_sep_pos = score->read_pos;
    score->unk7c = delta_value;
    score->delta_value = delta_value;
    score->loop_pos = score->read_pos;
    temp_a1_2 = VBLANK_MINUS * 60;
    new_var2 = temp_a1_2;
    if (new_var < new_var2) {
        temp_lo_3 = (VBLANK_MINUS * 600) / temp_lo_2;
        score->unk6E = temp_lo_3;
        score->unk70 = temp_lo_3;
    } else {
        temp_lo_4 = ((score->unk4a * score->unk84) * 10) / new_var2;
        score->unk6E = -1;
        score->unk70 = temp_lo_4;
        if ((VBLANK_MINUS * 30) <
            (((score->unk4a * score->unk84) * 10) % new_var2)) {
            score->unk70 = (u16)(temp_lo_4 + 1);
        }
    }
    score->unk72 = score->unk70;
    return 0;
}

s16 SsSeqOpen(u32 addr, s16 vab_id) {
    s32 open_bits;
    s16 seq_sep_no;
    u32 bit_pos;
    u8 found;
    open_bits = _snd_openflag;
    if (open_bits == 0xFFFFFFFF) {
        printf("Can't Open Sequence data any more\n\n");
        return -1;
    }
    bit_pos = 0;
    found = 0;
    do {
        if (!((1 << bit_pos) & open_bits)) {
            seq_sep_no = bit_pos;
            found = 1;
        }
        bit_pos += 1;
    } while (found == 0);
    _snd_openflag |= 1 << seq_sep_no;
    if (_SsInitSoundSeq(seq_sep_no, vab_id, addr) == -1) {
        return -1;
    }
    return seq_sep_no;
}
