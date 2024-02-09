#include "libsnd_i.h"

short SsUtGetProgAtr(short vabId, short programNum, ProgAtr* pProgAttr) {
    if (_svm_vab_used[vabId] == 1) {
        SpuVmVSetUp(vabId, programNum);
        pProgAttr->tones = _svm_pg[programNum].tones;
        pProgAttr->mvol = _svm_pg[programNum].mvol;
        pProgAttr->prior = _svm_pg[programNum].prior;
        pProgAttr->mode = _svm_pg[programNum].mode;
        pProgAttr->mpan = _svm_pg[programNum].mpan;
        pProgAttr->attr = _svm_pg[programNum].attr;
        return 0;
    }
    return -1;
}
