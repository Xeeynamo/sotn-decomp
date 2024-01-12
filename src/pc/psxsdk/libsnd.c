#include <common.h>
#include <psxsdk/libspu.h>
#include <psxsdk/libsnd.h>
#include <log.h>

short SsUtSetVVol(short vc, short voll, short volr) {
    DEBUGF("not implemented\n");
    return 0;
}

void SsSetSerialAttr(char s_num, char attr, char mode) { NOT_IMPLEMENTED; }

#ifndef HAVE_SOUND_REV
void SsSeqPlay(s16 seq_access_num, s8 play_mode, s16 l_count) {
    NOT_IMPLEMENTED;
}
#endif

#ifndef HAVE_SOUND_REV
void SsSetMVol(short voll, short volr) { NOT_IMPLEMENTED; }
#endif

#ifndef HAVE_SOUND_REV
void SsSeqSetVol(s16 arg0, s32 arg1, s32 arg2) { NOT_IMPLEMENTED; }
#endif

#ifndef HAVE_SOUND_REV
short SsSeqOpen(u_long* addr, short vab_id) {
    NOT_IMPLEMENTED;
    return 0;
}
#endif

#ifndef HAVE_SOUND_REV
void SsSeqClose(short seq_access_num) { NOT_IMPLEMENTED; }
#endif

void SsSeqStop(short seq_access_num) { NOT_IMPLEMENTED; }

short SsUtKeyOnV(short voice, short vabId, short prog, short tone, short note,
                 short fine, short voll, short volr) {
    NOT_IMPLEMENTED;
    return 0;
}
#ifndef HAVE_SOUND_REV
void SsUtReverbOn(void) { NOT_IMPLEMENTED; }
#endif
#ifndef HAVE_SOUND_REV
void SsUtSetReverbType(short type) { NOT_IMPLEMENTED; }
#endif

#ifndef HAVE_SOUND_REV
void SsSetTableSize(char* table, short s_max, short t_max) { NOT_IMPLEMENTED; }
#endif

#ifndef HAVE_SOUND_REV
void SsStart(void) { NOT_IMPLEMENTED; }
#endif

char SsSetReservedVoice(char voices) {
    DEBUGF("%d", voices);
    return 0;
}

#ifndef HAVE_SOUND_REV
void SsSetTickMode(long tick_mode) { DEBUGF("%d", tick_mode); }
#endif

void MySsInitHot();
void SsInitHot(void) { MySsInitHot(); }

void SsSetStereo(void) { NOT_IMPLEMENTED; }

void SsSetMono(void) { NOT_IMPLEMENTED; }

void SsSetSerialVol(short s_num, short voll, short volr) {
    DEBUGF("s_num %d voll %d volr %d", s_num, voll, volr);
}

#ifndef HAVE_SOUND_REV
void SsUtSetReverbDepth(short ldepth, short rdepth) {
    DEBUGF("ldepth %d rdepth %d", ldepth, rdepth);
}
#endif

#ifndef HAVE_SOUND_REV
s32 SsVabTransCompleted(short immediateFlag) {
    NOT_IMPLEMENTED;
    return 1;
}
#endif

s32 SsVabOpenHeadSticky(u_char* addr, u_long vabid, u_long sbaddr) {
    NOT_IMPLEMENTED;
    return 0;
}

s32 SsVabTransBodyPartly(u_char* addr, u_long bufsize, u_long vabid) {
    NOT_IMPLEMENTED;
    return 0;
}

#ifndef HAVE_SOUND_REV
void SsVabClose(short vab_id) { NOT_IMPLEMENTED; }
#endif
