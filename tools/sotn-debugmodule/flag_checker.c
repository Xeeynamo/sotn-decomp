#include "debugmode.h"

#define MaxFlagChangeLogCount 4

const char ChToHex[] = {'0', '1', '2', '3', '4', '5', '6', '7',
                        '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

int g_FlagOffset;
int g_FlagCursor;
bool g_IsFlagEditMode;
u8 g_CastleFlagsCopy[LEN(g_CastleFlags)];
char g_CastleFlagChanges[MaxFlagChangeLogCount][8];
int g_CastleFlagChangeCursor;

void InitFlagChecker(void) {
    int i;

    g_FlagOffset = 0;
    g_FlagCursor = 0;
    g_IsFlagEditMode = true;
    g_CastleFlagChangeCursor = 0;
    for (i = 0; i < MaxFlagChangeLogCount; i++)
        g_CastleFlagChanges[i][0] = '\0';
}

void FlipBit(int offset, int bit) { g_CastleFlags[offset] ^= 1 << bit; }

void ReportFlagChange(int offset, u8 prev, u8 cur) {
    char* str =
        g_CastleFlagChanges[g_CastleFlagChangeCursor % MaxFlagChangeLogCount];
    g_CastleFlagChangeCursor++;

    str[0] = ChToHex[(offset >> 8) & 15];
    str[1] = ChToHex[(offset >> 4) & 15];
    str[2] = ChToHex[(offset >> 0) & 15];
    str[3] = ' ';
    str[4] = ChToHex[(cur >> 4) & 15];
    str[5] = ChToHex[(cur >> 0) & 15];
    str[6] = '\n';
    str[7] = '\0';
}

int UpdateFlagCheckerListenMode(void) {
    const int MenuWidth = 64;
    int i;

    if (g_pads[0].tapped & PAD_L2) {
        // exit listen mode
        g_CastleFlagChangeCursor = -1;
        return;
    }

    for (i = 0; i < LEN(g_CastleFlags); i++) {
        if (g_CastleFlagsCopy[i] != g_CastleFlags[i]) {
            ReportFlagChange(i, g_CastleFlagsCopy[i], g_CastleFlags[i]);
            g_CastleFlagsCopy[i] = g_CastleFlags[i];
        }
    }

    DbgDrawMenuRect(4, 44, MenuWidth + 10, 8 + MaxFlagChangeLogCount * 8);
    for (i = 0; i < MaxFlagChangeLogCount; i++) {
        int cursor = (i + g_CastleFlagChangeCursor) % MaxFlagChangeLogCount;
        FntPrint(g_CastleFlagChanges[cursor]);
    }

    return true;
}

void InitFlagCheckerListenMode(void) {
    g_CastleFlagChangeCursor = 0;
    __builtin_memcpy(g_CastleFlagsCopy, g_CastleFlags, LEN(g_CastleFlags));
}

void PrintFlagLine(int offset, int columnCount) {
    char buf[10];
    u8 ch;

    FntPrint("%03X ", offset);
    while (columnCount--) {
        if (offset >= sizeof(g_CastleFlags)) {
            break;
        }
        ch = g_CastleFlags[offset++];
        buf[0] = '0' + !!(ch & 0x01);
        buf[1] = '0' + !!(ch & 0x02);
        buf[2] = '0' + !!(ch & 0x04);
        buf[3] = '0' + !!(ch & 0x08);
        buf[4] = '0' + !!(ch & 0x10);
        buf[5] = '0' + !!(ch & 0x20);
        buf[6] = '0' + !!(ch & 0x40);
        buf[7] = '0' + !!(ch & 0x80);
        buf[8] = ' ';
        buf[9] = '\0';
        FntPrint(buf);
    }
    FntPrint("\n");
}

void UpdateFlagChecker(void) {
    const int MenuWidth = 236;
    const int BitsCount = 8;
    const int RowCount = 8;
    const int ColumnCount = 3;
    const int MaxOffset = LEN(g_CastleFlags) - RowCount * ColumnCount;
    const int MaxCursor = BitsCount * RowCount * ColumnCount;

    int i;
    int offset;
    int cx;
    int cy;

    if (g_CastleFlagChangeCursor >= 0) {
        g_EntitiesPaused = !UpdateFlagCheckerListenMode();
        return;
    }

    DbgDrawMenuRect(4, 44, MenuWidth + 10, 16 + RowCount * 8);
    for (i = 0, offset = g_FlagOffset; i < RowCount; i++) {
        PrintFlagLine(offset, ColumnCount);
        offset += ColumnCount;
    }

    if (g_IsFlagEditMode) {
        FntPrint("CIRCLE=View  SQUARE=Listen");

        cx = (g_FlagCursor % BitsCount) +
             ((g_FlagCursor / BitsCount) % ColumnCount) * (BitsCount + 1);
        cy = (g_FlagCursor / BitsCount) / ColumnCount;
        DbgDrawCursor(40 + cx * 8, 48 + cy * 8, 8, 8);

        if (g_pads[0].repeat & PAD_UP) {
            g_FlagCursor -= BitsCount * ColumnCount;
        }
        if (g_pads[0].repeat & PAD_DOWN) {
            g_FlagCursor += BitsCount * ColumnCount;
        }
        if (g_pads[0].repeat & PAD_LEFT) {
            g_FlagCursor--;
        }
        if (g_pads[0].repeat & PAD_RIGHT) {
            g_FlagCursor++;
        }

        if (g_FlagCursor < 0) {
            g_FlagCursor += MaxCursor;
        }
        g_FlagCursor %= MaxCursor;

        if (g_pads[0].tapped & PAD_CROSS) {
            FlipBit(g_FlagOffset + (g_FlagCursor / BitsCount),
                    g_FlagCursor % BitsCount);
        }
        if (g_pads[0].tapped & PAD_CIRCLE) {
            g_IsFlagEditMode = false;
        }
    } else {
        FntPrint("CROSS=Edit   SQUARE=Listen");
        if (g_pads[0].repeat & PAD_UP) {
            g_FlagOffset -= ColumnCount;
        }
        if (g_pads[0].repeat & PAD_DOWN) {
            g_FlagOffset += ColumnCount;
        }
        if (g_pads[0].repeat & PAD_LEFT) {
            g_FlagOffset--;
        }
        if (g_pads[0].repeat & PAD_RIGHT) {
            g_FlagOffset++;
        }
        if (g_pads[0].tapped & PAD_CROSS) {
            g_IsFlagEditMode = true;
        }
    }

    if (g_pads[0].repeat & PAD_L1) {
        g_FlagOffset -= ColumnCount * RowCount;
    }
    if (g_pads[0].repeat & PAD_R1) {
        g_FlagOffset += ColumnCount * RowCount;
    }
    if (g_pads[0].tapped & PAD_SQUARE) {
        InitFlagCheckerListenMode();
    }

    if (g_FlagOffset < 0) {
        g_FlagOffset = 0;
    } else if (g_FlagOffset > MaxOffset) {
        g_FlagOffset = MaxOffset;
    }
}
