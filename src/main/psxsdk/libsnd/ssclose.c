#include "common.h"
#include "libsnd_i.h"

void _SsClose(s16 arg0) {
    u8 pad[2];
    s32 var_a2;
    SpuVmSetSeqVol(arg0, 0, 0, 1);
    SpuVmSeqKeyOff(arg0);
    _snd_openflag &= ~(1 << arg0);
    var_a2 = 0;
    if (_snd_seq_t_max > 0) {
        do {
            _ss_score[arg0][var_a2].unk90 = 0;
            _ss_score[arg0][var_a2].unk3C = 0xFF;
            _ss_score[arg0][var_a2].unk0 = 0;
            _ss_score[arg0][var_a2].unk3E = 0;
            _ss_score[arg0][var_a2].unk40 = 0;
            _ss_score[arg0][var_a2].unk94 = 0;
            _ss_score[arg0][var_a2].unk98 = 0;
            _ss_score[arg0][var_a2].unk42 = 0;
            _ss_score[arg0][var_a2].unkA4 = 0;
            _ss_score[arg0][var_a2].unkA0 = 0;
            _ss_score[arg0][var_a2].unk9C = 0;
            _ss_score[arg0][var_a2].unk44 = 0;
            _ss_score[arg0][var_a2].unk74 = 0x7f;
            _ss_score[arg0][var_a2].unk76 = 0x7f;
            var_a2 += 1;
        } while (var_a2 < _snd_seq_t_max);
    }
}

void SsSeqClose(short seq_access_num) { _SsClose(seq_access_num); }

void SsSepClose(s16 sep_access_num) { _SsClose(sep_access_num); }
