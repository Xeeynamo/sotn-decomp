#include "common.h"
#include "libsnd_internal.h"

short SsUtSetVagAtr(short vabId, short progNum, s32 toneNum, VagAtr* pVagAttr) {
    s16 iVar2;
    if (svm_vab_used[vabId] == 1) {
        SpuVmVSetUp(vabId, progNum);
        iVar2 = toneNum + D_800978CF * 0x10;
        _svm_tn[iVar2].prior = pVagAttr->prior;
        _svm_tn[iVar2].mode = pVagAttr->mode;
        _svm_tn[iVar2].vol = pVagAttr->vol;
        _svm_tn[iVar2].pan = pVagAttr->pan;
        _svm_tn[iVar2].center = pVagAttr->center;
        _svm_tn[iVar2].shift = pVagAttr->shift;
        _svm_tn[iVar2].max = pVagAttr->max;
        _svm_tn[iVar2].min = pVagAttr->min;
        _svm_tn[iVar2].vibW = pVagAttr->vibW;
        _svm_tn[iVar2].vibT = pVagAttr->vibT;
        _svm_tn[iVar2].porW = pVagAttr->porW;
        _svm_tn[iVar2].porT = pVagAttr->porT;
        _svm_tn[iVar2].pbmin = pVagAttr->pbmin;
        _svm_tn[iVar2].pbmax = pVagAttr->pbmax;
        _svm_tn[iVar2].adsr1 = pVagAttr->adsr1;
        _svm_tn[iVar2].adsr2 = pVagAttr->adsr2;
        _svm_tn[iVar2].prog = pVagAttr->prog;
        _svm_tn[iVar2].vag = pVagAttr->vag;
        return 0;
    }
    return -1;
}
