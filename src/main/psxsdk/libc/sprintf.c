#include "common.h"
#include <stdarg.h>

typedef struct {
    bool leftJustified : 1;
    bool prependPlus : 1;
    bool alternativeForm : 1;
    bool leadingZeros : 1;
    bool usePrecision : 1;
    bool isHalf : 1;
    bool isLong : 1;
    bool isLongLong : 1;
    char leadingChar;
    s32 padding;
    s32 precision;
} printf_info;

static printf_info D_8002D3A8 = {0};

s32 sprintf(char* out, char* f, ...) {
    char buf[0x200];
    printf_info info;
    va_list args;
    char* hexChars;
    s32 written;
    s32 num;
    s32 len;
    char* bufPtr;
    u32 ch;

    va_start(args, f);
    ch = *f;
    written = 0;
    for (; ch = *f, ch != 0; ++f) {
        if (ch != '%') {
            out[written++] = ch;
            continue;
        }
        info = D_8002D3A8;

        while (true) {
            ch = *++f;
            if (ch == '-') {
                info.leftJustified = true;
            } else if (ch == '+') {
                info.prependPlus = true;
            } else if (ch == ' ') {
                info.leadingChar = ' ';
            } else if (ch == '#') {
                info.alternativeForm = true;
            } else if (ch == '0') {
                info.leadingZeros = true;
            } else {
                break;
            }
        }

        if (ch == '*') {
            info.padding = va_arg(args, s32);
            if (info.padding < 0) {
                info.padding = -info.padding;
                info.leftJustified = true;
            }
            ch = *++f;
        } else {
            while (ch >= '0' && ch <= '9') {
                info.padding = (info.padding * 10) + (ch - '0');
                ch = *++f;
            }
        }
        if (ch == '.') {
            ch = *++f;
            if (ch == '*') {
                info.precision = va_arg(args, s32);
                ch = *++f;
            } else {
                while (ch >= '0' && ch <= '9') {
                    info.precision = (info.precision * 10) + (ch - '0');
                    ch = *++f;
                }
            }
            if (info.precision >= 0) {
                info.usePrecision = true;
            }
        }

        bufPtr = &args - 4;

        if (info.leftJustified) {
            info.leadingZeros = false;
        }

    loop_30:
        switch (ch) {
        case 'h':
            info.isHalf = true;
            ch = *++f;
            goto loop_30;

        case 'l':
            info.isLong = true;
            ch = *++f;
            goto loop_30;

        case 'L':
            info.isLongLong = true;
            ch = *++f;
            goto loop_30;

        case 'd':
        case 'i':
            num = va_arg(args, s32);
            do {
                if (info.isHalf) {
                    num = (s16)num;
                }
            } while (0);
            if (num < 0) {
                num = -num;
                info.leadingChar = '-';
            } else {
                do {
                    if (info.prependPlus) {
                        info.leadingChar = '+';
                    }
                } while (0);
            }
            goto block_44;

        case 'u':
            num = va_arg(args, u32);
            do {
                if (info.isHalf) {
                    num = (u16)num;
                }
            } while (0);
            info.leadingChar = '\0';
        block_44:
            if (!info.usePrecision) {
                if (info.leadingZeros) {
                    info.precision = info.padding;
                    if (info.leadingChar != '\0') {
                        info.precision = info.padding - 1;
                    }
                }
                if (info.precision <= 0) {
                    info.precision = 1;
                }
            }
            len = 0;
            while (num != 0) {
                *--bufPtr = (num % 10U) + '0';
                num /= 10U;
                len++;
            }
            while (len < info.precision) {
                *--bufPtr = '0';
                len++;
            }
            if (info.leadingChar != '\0') {
                *--bufPtr = info.leadingChar;
                len++;
            }
            break;

        case 'o':
            num = va_arg(args, u32);
            do {
                if (info.isHalf) {
                    num = (u16)num;
                }
            } while (0);
            if (!info.usePrecision) {
                if (info.leadingZeros) {
                    info.precision = info.padding;
                }
                if (info.precision <= 0) {
                    info.precision = 1;
                }
            }
            len = 0;
            while (num != 0) {
                *--bufPtr = (num % 8U) + '0';
                num /= 8U;
                len++;
            }
            if (info.alternativeForm && (len != 0) && (*bufPtr != '0')) {
                *--bufPtr = '0';
                len++;
            }
            while (len < info.precision) {
                *--bufPtr = '0';
                len++;
            }
            break;

        case 'p':
            info.precision = 8;
            info.usePrecision = true;
            info.isLong = true;
            /* fallthrough */
        case 'X':
            hexChars = "0123456789ABCDEF";
            goto block_79;
        case 'x':
            hexChars = "0123456789abcdef";
        block_79:
            num = va_arg(args, u32);
            do {
                if (info.isHalf) {
                    num = (u16)num;
                }
            } while (0);
            if (!info.usePrecision) {
                if (info.leadingZeros) {
                    info.precision = info.padding;
                    if (info.alternativeForm) {
                        info.precision = info.padding - 2;
                    }
                }
                if (info.precision <= 0) {
                    info.precision = 1;
                }
            }
            len = 0;
            while (num != 0) {
                *--bufPtr = hexChars[num % 16U];
                num /= 16U;
                len++;
            }
            while (len < info.precision) {
                *--bufPtr = '0';
                len++;
            }
            if (info.alternativeForm) {
                *--bufPtr = ch;
                *--bufPtr = '0';
                len += 2;
            }
            break;

        case 'c':
            *--bufPtr = va_arg(args, char);
            len = 1;
            break;

        case 's':
            bufPtr = va_arg(args, char*);
            if (info.alternativeForm) {
                len = *bufPtr++;
                if (info.usePrecision) {
                    if (info.precision < len) {
                        len = info.precision;
                    }
                }
            } else if (!info.usePrecision) {
                len = strlen(bufPtr);
            } else {
                char* ptr = memchr(bufPtr, 0, info.precision);
                len = ptr - bufPtr;
                if (ptr == NULL) {
                    len = info.precision;
                }
            }
            break;

        case 'n':
            bufPtr = va_arg(args, s32*);
            if (info.isHalf) {
                LOH(*bufPtr) = written;
            } else if (info.isLong) {
                LOW(*bufPtr) = written;
            } else if (info.isLongLong) {
                LOW(*bufPtr) = written;
            } else {
                LOW(*bufPtr) = written;
            }
            continue;

        default:
            if (ch == '%') {
                out[written++] = ch;
                continue;
            } else {
                goto end;
            }
        }
        if (len < info.padding && !info.leftJustified) {
            while (len < info.padding) {
                out[written++] = ' ';
                info.padding--;
            }
        }
        memmove(&out[written], bufPtr, len);
        written += len;
        while (len < info.padding) {
            out[written++] = ' ';
            len++;
        }
    }
end:
    out[written] = 0;
    return written;
}
