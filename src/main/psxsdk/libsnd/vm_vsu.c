#include "libsnd_i.h"

u32 SpuVmVSetUp(s16 arg0, s16 arg1) {
    ProgAtr* temp_a0;
    u32 var_v0;

    if ((arg0 >= 0x10U) || (_svm_vab_used[arg0] != 1) ||
        (arg1 >= kMaxPrograms)) {
        return -1;
    }

    _svm_vh = _svm_vab_vh[arg0];
    temp_a0 = _svm_vab_pg[arg0];
    _svm_tn = _svm_vab_tn[arg0];
    _svm_cur.field_1_vabId = arg0;
    _svm_cur.field_6_program = arg1;
    _svm_pg = temp_a0;
    _svm_cur.field_7_fake_program = _svm_pg[arg1].reserved1;
    return 0;
}
