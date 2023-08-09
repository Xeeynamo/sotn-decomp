#include "common.h"

void func_80029300(s32*);
extern s32 D_8003C754;
extern s32* _svm_rattr;

void SsUtSetReverbDelay(s16 arg0) {
    s32* temp = &_svm_rattr;
    *temp = 8;
    D_8003C754 = arg0;
    func_80029300(temp);
}
