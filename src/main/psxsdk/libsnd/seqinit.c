#include "common.h"

s16 _SsInitSoundSeq(s16, s16, u32);

INCLUDE_ASM("main/nonmatchings/psxsdk/libsnd/seqinit", _SsInitSoundSeq);

extern s8 D_80010A3C;
extern u32 _snd_openflag;

s16 SsSeqOpen(u32 addr, s16 vab_id) {
    s32 open_bits;
    s16 seq_sep_no;
    u32 bit_pos;
    u8 found;
    open_bits = _snd_openflag;
    if (open_bits == 0xFFFFFFFF) {
        printf(&D_80010A3C);
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
