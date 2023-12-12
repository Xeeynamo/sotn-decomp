#include "common.h"
#include "libsnd_internal.h"

short SsUtGetProgAtr(short vabId, short programNum, ProgAtr* pProgAttr) {
    if (svm_vab_used[vabId] == 1) {
        SpuVmVSetUp(vabId, programNum);
        pProgAttr->tones = D_8006C3B4[programNum].tones;
        pProgAttr->mvol = D_8006C3B4[programNum].mvol;
        pProgAttr->prior = D_8006C3B4[programNum].prior;
        pProgAttr->mode = D_8006C3B4[programNum].mode;
        pProgAttr->mpan = D_8006C3B4[programNum].mpan;
        pProgAttr->attr = D_8006C3B4[programNum].attr;
        return 0;
    }
    return -1;
}
