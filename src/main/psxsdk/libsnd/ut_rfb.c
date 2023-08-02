#define INCLUDE_ASM_NEW
#include "common.h"

extern s32 D_8003C758;
extern s32* _svm_rattr;

void SsUtSetReverbFeedback(s16 feedback) {
    s32* temp = &_svm_rattr;
    *temp = 0x10;
    D_8003C758 = feedback;
    func_80029300(temp);
}
