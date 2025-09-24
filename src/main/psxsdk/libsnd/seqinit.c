// SPDX-License-Identifier: MIT
#include "common.h"
#include "libsnd_i.h"

s16 _SsInitSoundSeq(s16 arg0, s16 vab_id, u8* addr) {
    struct SeqStruct* score = &_ss_score[arg0][0];
    s32 channel;

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
    if ((*score->read_pos == 'S') || (*score->read_pos == 'p')) {
        score->read_pos += 8;
        if (addr[7] != 1) {
            printf("This is not SEQ Data.\n");
            return -1;
        }
    } else {
        printf("This is an old SEQ Data Format.\n");
        return 0;
    }
    score->unk4a = (*score->read_pos++) << 8 | *score->read_pos++;
    score->unk84 = (*score->read_pos++) << 0x10 | (*score->read_pos++) << 8 |
                   *score->read_pos++;
    if ((score->unk84 / 2) < (60000000 % score->unk84)) {
        score->unk84 = (60000000 / score->unk84) + 1;
    } else {
        score->unk84 = 60000000 / score->unk84;
    }
    score->unk8c = score->unk84;
    score->read_pos += 2;
    score->delta_value = score->unk7c = _SsReadDeltaValue(arg0, 0);
    score->next_sep_pos = score->read_pos;
    score->loop_pos = score->read_pos;

    if ((score->unk4a * score->unk84 * 10) < (VBLANK_MINUS * 60)) {
        score->unk70 = score->unk6E =
            (VBLANK_MINUS * 600) / (score->unk4a * score->unk84);
    } else {
        score->unk6E = -1;
        score->unk70 = (score->unk4a * score->unk84 * 10) / (VBLANK_MINUS * 60);
        if ((VBLANK_MINUS * 30) <
            (score->unk4a * score->unk84 * 10) % (VBLANK_MINUS * 60)) {
            score->unk70++;
        }
    }
    score->unk72 = score->unk70;
    return 0;
}

s16 SsSeqOpen(u32 addr, s16 vab_id) {
    s16 seq_sep_no;
    u32 bit_pos;
    u8 found;

    if (_snd_openflag == 0xFFFFFFFF) {
        printf("Can't Open Sequence data any more\n\n");
        return -1;
    }
    bit_pos = 0;
    found = 0;
    while (!found) {
        if (!((1 << bit_pos) & _snd_openflag)) {
            seq_sep_no = bit_pos;
            found = 1;
        }
        bit_pos++;
    }
    _snd_openflag |= 1 << seq_sep_no;
    if (_SsInitSoundSeq(seq_sep_no, vab_id, addr) == -1) {
        return -1;
    }
    return seq_sep_no;
}
