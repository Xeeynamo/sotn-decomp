// SPDX-License-Identifier: MIT
#include "libsnd_i.h"

u32 SpuVmVSetUp(s16 vabId, s16 prog) {
    if ((vabId >= 0x10U) || (_svm_vab_used[vabId] != 1) ||
        (prog >= kMaxPrograms)) {
        return -1;
    }

    _svm_vh = _svm_vab_vh[vabId];
    _svm_pg = _svm_vab_pg[vabId];
    _svm_tn = _svm_vab_tn[vabId];
    _svm_cur.field_1_vabId = vabId;
    _svm_cur.field_6_program = prog;
    _svm_cur.field_7_fake_program = _svm_pg[prog].reserved1;
    return 0;
}
