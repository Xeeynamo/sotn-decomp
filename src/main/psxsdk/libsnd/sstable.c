#include "libsnd_i.h"

void SsSetTableSize(char* table, short s_max, short t_max) {
    s32 i;
    s32 j;
    struct SeqStruct* pTypedTable;

    _snd_seq_s_max = s_max;
    _snd_seq_t_max = t_max;
    pTypedTable = (struct SeqStruct*)table;
    for (i = 0; i < s_max; i++) {
        _ss_score[i] = &pTypedTable[i * t_max];
    }

    for (i = 0; i < _snd_seq_s_max; i++) {
        for (j = 0; _snd_seq_t_max > j; j++) {
            _ss_score[i][j].unk90 = 0;
            _ss_score[i][j].unk3C = 0xFF;
            _ss_score[i][j].unk0 = 0;
            _ss_score[i][j].unk3E = 0;
            _ss_score[i][j].unk40 = 0;
            _ss_score[i][j].unk94 = 0;
            _ss_score[i][j].unk98 = 0;
            _ss_score[i][j].unk42 = 0;
            _ss_score[i][j].unkA4 = 0;
            _ss_score[i][j].unkA0 = 0;
            _ss_score[i][j].unk9C = 0;
            _ss_score[i][j].unk44 = 0;
            _ss_score[i][j].unk74 = 0x7F;
            _ss_score[i][j].unk76 = 0x7F;
            _ss_score[i][j].unk78 = 0x7F;
            _ss_score[i][j].unk7A = 0x7F;
        }
    }
}
