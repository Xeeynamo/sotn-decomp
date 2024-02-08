#include "libsnd_i.h"

short SsUtGetVagAtr(
    short vabId, short progNum, short toneNum, VagAtr* vagatrptr) {
    s16 temp_v1;
    if (_svm_vab_used[vabId] == 1) {
        SpuVmVSetUp(vabId, progNum);
        temp_v1 = toneNum + _svm_cur.field_7_fake_program * 0x10;
        vagatrptr->prior = _svm_tn[temp_v1].prior;
        vagatrptr->mode = _svm_tn[temp_v1].mode;
        vagatrptr->vol = _svm_tn[temp_v1].vol;
        vagatrptr->pan = _svm_tn[temp_v1].pan;
        vagatrptr->center = _svm_tn[temp_v1].center;
        vagatrptr->shift = _svm_tn[temp_v1].shift;
        vagatrptr->max = _svm_tn[temp_v1].max;
        vagatrptr->min = _svm_tn[temp_v1].min;
        vagatrptr->vibW = _svm_tn[temp_v1].vibW;
        vagatrptr->vibT = _svm_tn[temp_v1].vibT;
        vagatrptr->porW = _svm_tn[temp_v1].porW;
        vagatrptr->porT = _svm_tn[temp_v1].porT;
        vagatrptr->pbmin = _svm_tn[temp_v1].pbmin;
        vagatrptr->pbmax = _svm_tn[temp_v1].pbmax;
        vagatrptr->adsr1 = _svm_tn[temp_v1].adsr1;
        vagatrptr->adsr2 = _svm_tn[temp_v1].adsr2;
        vagatrptr->prog = _svm_tn[temp_v1].prog;
        vagatrptr->vag = _svm_tn[temp_v1].vag;
        return 0;
    }

    return -1;
}
