#include "libsnd_i.h"

void SsSeqCalledTbyT(void) {
    int i;
    int j;
    if (_snd_ev_flag != 1) {
        _snd_ev_flag = 1;

        SpuVmFlush();

        /* For each SEP block */
        for (i = 0; i < _snd_seq_s_max; i++) {
            /* Is it on? */
            if ((1 << i) & _snd_openflag) {
                /* Go through each SEQ track */
                for (j = 0; j < _snd_seq_t_max; j++) {
                    if (_ss_score[i][j].unk90 & 1) {
                        _SsSndPlay(i, j);

                        if (_ss_score[i][j].unk90 & 0x10) {
                            _SsSndCrescendo(i, j);
                        }

                        if (_ss_score[i][j].unk90 & 0x20) {
                            _SsSndDecrescendo(i, j);
                        }

                        if (_ss_score[i][j].unk90 & 0x40) {
                            _SsSndTempo(i, j);
                        }

                        if (_ss_score[i][j].unk90 & 0x80) {
                            _SsSndTempo(i, j);
                        }
                    }

                    if (_ss_score[i][j].unk90 & 2) {
                        _SsSndPause(i, j);
                    }

                    if (_ss_score[i][j].unk90 & 8) {
                        _SsSndReplay(i, j);
                    }

                    if (_ss_score[i][j].unk90 & 4) {
                        _SsSndStop(i, j);
                        _ss_score[i][j].unk90 = 0;
                    }
                }
            }
        }
        _snd_ev_flag = 0;
    }
}
