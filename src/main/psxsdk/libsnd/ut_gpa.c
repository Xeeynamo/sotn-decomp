// SPDX-License-Identifier: MIT
#include "libsnd_i.h"

short SsUtGetProgAtr(short vabId, short prog, ProgAtr* pProgAttr) {
    if (_svm_vab_used[vabId] == 1) {
        SpuVmVSetUp(vabId, prog);
        pProgAttr->tones = _svm_pg[prog].tones;
        pProgAttr->mvol = _svm_pg[prog].mvol;
        pProgAttr->prior = _svm_pg[prog].prior;
        pProgAttr->mode = _svm_pg[prog].mode;
        pProgAttr->mpan = _svm_pg[prog].mpan;
        pProgAttr->attr = _svm_pg[prog].attr;
        return 0;
    }
    return -1;
}
