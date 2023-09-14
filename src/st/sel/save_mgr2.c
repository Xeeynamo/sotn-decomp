#include "sel.h"
#include "memcard.h"

void _clear_event(void);
void _clear_event_x(void);
s32 _peek_event_with_retry(void);

s32 func_801B8A8C(s32 nPort, s32 nCard) {
    s32 channel;
    MemcardInfo* memcard;
    channel = (nPort * 0x10) + nCard;
    memcard = &g_MemcardInfo[nPort];
    switch (g_MemcardStep) {
    case 0:
        memcard->unk25C = 0;
        g_MemcardRetryCount = 0x80;
        _card_info(channel);
        g_MemcardStep++;
        break;

    case 1:
        switch (_peek_event_with_retry()) {
        case 0:
            break;

        case 1:
            memcard->unk258 = 1;
            g_MemcardStep++;
            break;

        case 3:
            D_8006C3AC &= g_UnkMemcardPort[nPort];
            memcard->unk258 = -1;
            g_MemcardStep = 4;
            break;

        case 4:
            D_8006C3AC &= g_UnkMemcardPort[nPort];
            memcard->unk258 = 2;
            _clear_event_x();
            _card_clear(channel);
            _card_event_x();
            g_MemcardStep++;
            break;

        case 2:
            D_8006C3AC &= g_UnkMemcardPort[nPort];
            memcard->unk258 = -3;
            g_MemcardStep = 4;
            break;
        }

        break;

    case 2:
        _clear_event();
        _card_load(channel);
        g_MemcardRetryCount = 0x80;
        g_MemcardStep++;
        break;

    case 3:
        switch (_peek_event_with_retry()) {
        case 0:
            break;

        case 1:
            g_MemcardStep++;
            break;

        case 3:
            D_8006C3AC &= g_UnkMemcardPort[nPort];
            memcard->unk258 = -1;
            g_MemcardStep++;
            break;

        case 4:
            D_8006C3AC &= g_UnkMemcardPort[nPort];
            memcard->unk258 = -2;
            g_MemcardStep++;
            break;

        case 2:
            D_8006C3AC &= g_UnkMemcardPort[nPort];
            memcard->unk258 = -3;
            g_MemcardStep++;
            break;
        }

        break;

    case 4:
        g_MemcardStep = 0;
        memcard->unk25C = memcard->unk258;
        break;
    }

    return memcard->unk25C;
}
