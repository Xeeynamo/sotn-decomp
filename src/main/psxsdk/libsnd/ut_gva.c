#include "common.h"
#include "libsnd_internal.h"

s16 SsUtGetVagAtr(s16 arg0, s16 arg1, s32 arg2, VagAtr* arg3) {
    s32 temp_v1;

    if (svm_vab_used[arg0] == 1) {
        SpuVmVSetUp(arg0, arg1);
        temp_v1 = (s32)((arg2 + (D_800978CF * 0x10)) << 0x10) >> 0x10;
        arg3->prior = _svm_tn[temp_v1].prior;
        arg3->mode = _svm_tn[temp_v1].mode;
        arg3->vol = _svm_tn[temp_v1].vol;
        arg3->pan = _svm_tn[temp_v1].pan;
        arg3->center = _svm_tn[temp_v1].center;
        arg3->shift = _svm_tn[temp_v1].shift;
        arg3->max = _svm_tn[temp_v1].max;
        arg3->min = _svm_tn[temp_v1].min;
        arg3->vibW = _svm_tn[temp_v1].vibW;
        arg3->vibT = _svm_tn[temp_v1].vibT;
        arg3->porW = _svm_tn[temp_v1].porW;
        arg3->porT = _svm_tn[temp_v1].porT;
        arg3->pbmin = _svm_tn[temp_v1].pbmin;
        arg3->pbmax = _svm_tn[temp_v1].pbmax;
        arg3->adsr1 = _svm_tn[temp_v1].adsr1;
        arg3->adsr2 = _svm_tn[temp_v1].adsr2;
        arg3->prog = _svm_tn[temp_v1].prog;
        arg3->vag = _svm_tn[temp_v1].vag;
        return 0;
    }

    return -1;
}
