#include "sel.h"

// TODO almost matching but one single jump makes not so. The original jump
// points to a 'nop' while the current build toolchain points to the
// instruction right after the 'nop'.
#ifndef NON_MATCHING
INCLUDE_ASM("asm/st/sel/nonmatchings/func_801B8A8C", func_801B8A8C);
#else
void _clear_event(void);
void _clear_event_x(void);
s32 _peek_event_with_retry(void);

s32 func_801B8A8C(s32 arg0, s32 arg1) {
    s32 temp_s2;
    Unkstruct_801B8A8C* unk;
    temp_s2 = (arg0 * 0x10) + arg1;
    unk = &D_801BC3F0[arg0];
    switch (D_801D6B20) {
    case 0:
        unk->unk25C = 0;
        D_801BC2F8 = 0x80;
        _card_info(temp_s2);
        D_801D6B20++;
        break;

    case 1:
        switch (_peek_event_with_retry()) {
        case 0:
            break;

        case 1:
            unk->unk258 = 1;
            D_801D6B20++;
            break;

        case 3:
            D_8006C3AC &= D_801808DC[arg0];
            unk->unk258 = -1;
            D_801D6B20 = 4;
            break;

        case 4:
            D_8006C3AC &= D_801808DC[arg0];
            unk->unk258 = 2;
            _clear_event_x();
            _card_clear(temp_s2);
            _card_event_x();
            D_801D6B20++;
            break;

        case 2:
            D_8006C3AC &= D_801808DC[arg0];
            unk->unk258 = -3;
            D_801D6B20 = 4;
            break;
        }

        break;

    case 2:
        _clear_event();
        _card_load(temp_s2);
        D_801BC2F8 = 0x80;
        D_801D6B20++;
        break;

    case 3:
        switch (_peek_event_with_retry()) {
        case 0:
            break;

        case 1:
            D_801D6B20++;
            break;

        case 3:
            D_8006C3AC &= D_801808DC[arg0];
            unk->unk258 = -1;
            D_801D6B20++;
            break;

        case 4:
            D_8006C3AC &= D_801808DC[arg0];
            unk->unk258 = -2;
            D_801D6B20++;
            break;

        case 2:
            D_8006C3AC &= D_801808DC[arg0];
            unk->unk258 = -3;
            D_801D6B20++;
            break;
        }

        break;

    case 4:
        D_801D6B20 = 0;
        unk->unk25C = unk->unk258;
        break;
    }

    return unk->unk25C;
}
#endif
