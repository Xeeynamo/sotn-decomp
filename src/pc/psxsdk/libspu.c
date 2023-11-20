#include <common.h>
#include <psxsdk/libspu.h>
#include "../log.h"

short SsUtSetVVol(short vc, short voll, short volr) {
    DEBUGF("not implemented\n");
    return 0;
}

void SsSetSerialAttr(char s_num, char attr, char mode) {
    DEBUGF("not implemented\n");
}

void SsSeqPlay(s16 seq_access_num, s8 play_mode, s16 l_count) {
    DEBUGF("not implemented");
}

void SsSetMVol(short voll, short volr) { DEBUGF("not implemented"); }

void SsSeqSetVol(s16 arg0, s32 arg1, s32 arg2) { DEBUGF("not implemented"); }

short SsSeqOpen(u_long* addr, short vab_id) {
    DEBUGF("not implemented");
    return 0;
}

void SsSeqClose(short seq_access_num) { DEBUGF("not implemented"); }

void SsSeqStop(short seq_access_num) { DEBUGF("not implemented"); }

short SsUtKeyOnV(short voice, short vabId, short prog, short tone, short note,
                 short fine, short voll, short volr) {
    DEBUGF("not implemented");
    return 0;
}

void SsUtReverbOn(void) { DEBUGF("not implemented"); }

void SsUtSetReverbType(short type) { DEBUGF("not implemented"); }

void SsSetTableSize(char* table, short s_max, short t_max) {
    DEBUGF("not implemented");
}

void SsStart(void) { DEBUGF("not implemented"); }

char SsSetReservedVoice(char voices) {
    DEBUGF("%d", voices);
    return 0;
}

void SsSetTickMode(long tick_mode) { DEBUGF("%d", tick_mode); }

void SsInitHot(void) { DEBUGF("not implemented"); }

void SsSetStereo(void) { DEBUGF("not implemented"); }

void SsSetMono(void) { DEBUGF("not implemented"); }

void SsSetSerialVol(short s_num, short voll, short volr) {
    DEBUGF("s_num %d voll %d volr %d", s_num, voll, volr);
}

void SsUtSetReverbDepth(short ldepth, short rdepth) {
    DEBUGF("ldepth %d rdepth %d", ldepth, rdepth);
}
