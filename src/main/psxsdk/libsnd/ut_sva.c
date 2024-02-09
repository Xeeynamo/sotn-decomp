#include "libsnd_i.h"

short SsUtSetVagAtr(
    short vabId, short progNum, short toneNum, VagAtr* pVagAttr) {
    s16 toneIndex;
    if (_svm_vab_used[vabId] == 1) {
        SpuVmVSetUp(vabId, progNum);
        toneIndex = toneNum + _svm_cur.field_7_fake_program * 0x10;
        _svm_tn[toneIndex].prior = pVagAttr->prior;
        _svm_tn[toneIndex].mode = pVagAttr->mode;
        _svm_tn[toneIndex].vol = pVagAttr->vol;
        _svm_tn[toneIndex].pan = pVagAttr->pan;
        _svm_tn[toneIndex].center = pVagAttr->center;
        _svm_tn[toneIndex].shift = pVagAttr->shift;
        _svm_tn[toneIndex].max = pVagAttr->max;
        _svm_tn[toneIndex].min = pVagAttr->min;
        _svm_tn[toneIndex].vibW = pVagAttr->vibW;
        _svm_tn[toneIndex].vibT = pVagAttr->vibT;
        _svm_tn[toneIndex].porW = pVagAttr->porW;
        _svm_tn[toneIndex].porT = pVagAttr->porT;
        _svm_tn[toneIndex].pbmin = pVagAttr->pbmin;
        _svm_tn[toneIndex].pbmax = pVagAttr->pbmax;
        _svm_tn[toneIndex].adsr1 = pVagAttr->adsr1;
        _svm_tn[toneIndex].adsr2 = pVagAttr->adsr2;
        _svm_tn[toneIndex].prog = pVagAttr->prog;
        _svm_tn[toneIndex].vag = pVagAttr->vag;
        return 0;
    }
    return -1;
}
