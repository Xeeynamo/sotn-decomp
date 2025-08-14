#include "common.h"

const char a0123456789abcd_0[] = "0123456789ABCDEF";
const char a0123456789abcd_1[] = "0123456789abcdef";

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
} tempStrct;

extern tempStrct D_8002D3A8;

typedef s32* va_list;
#define va_start(v, l) v = &l + 1
#define va_arg(v, l) (++v, *(l*)(v - 1))

s32 sprintf(char* out, char* f, ...) {
    char buf[0x200];
    tempStrct s;
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
        s = D_8002D3A8;

        while (true) {
            ch = *++f;
            if (ch == '-') {
                s.leftJustified = true;
            } else if (ch == '+') {
                s.prependPlus = true;
            } else if (ch == ' ') {
                s.leadingChar = ' ';
            } else if (ch == '#') {
                s.alternativeForm = true;
            } else if (ch == '0') {
                s.leadingZeros = true;
            } else {
                break;
            }
        }

        if (ch == '*') {
            s.padding = va_arg(args, s32);
            if (s.padding < 0) {
                s.padding = -s.padding;
                s.leftJustified = true;
            }
            ch = *++f;
        } else {
            while (ch >= '0' && ch <= '9') {
                s.padding = (s.padding * 10) + (ch - '0');
                ch = *++f;
            }
        }
        if (ch == '.') {
            ch = *++f;
            if (ch == '*') {
                s.precision = va_arg(args, s32);
                ch = *++f;
            } else {
                while (ch >= '0' && ch <= '9') {
                    s.precision = (s.precision * 10) + (ch - '0');
                    ch = *++f;
                }
            }
            if (s.precision >= 0) {
                s.usePrecision = true;
            }
        }

        bufPtr = &args - 4;

        if (s.leftJustified) {
            s.leadingZeros = false;
        }

    loop_30:
        switch (ch) {
        case 'h':
            s.isHalf = true;
            ch = *++f;
            goto loop_30;

        case 'l':
            s.isLong = true;
            ch = *++f;
            goto loop_30;

        case 'L':
            s.isLongLong = true;
            ch = *++f;
            goto loop_30;

        case 'd':
        case 'i':
            num = va_arg(args, s32);
            do {
                if (s.isHalf) {
                    num = (s16)num;
                }
            } while (0);
            if (num < 0) {
                num = -num;
                s.leadingChar = '-';
            } else {
                do {
                    if (s.prependPlus) {
                        s.leadingChar = '+';
                    }
                } while (0);
            }
            goto block_44;

        case 'u':
            num = va_arg(args, u32);
            do {
                if (s.isHalf) {
                    num = (u16)num;
                }
            } while (0);
            s.leadingChar = '\0';
        block_44:
            if (!s.usePrecision) {
                if (s.leadingZeros) {
                    s.precision = s.padding;
                    if (s.leadingChar != '\0') {
                        s.precision = s.padding - 1;
                    }
                }
                if (s.precision <= 0) {
                    s.precision = 1;
                }
            }
            len = 0;
            while (num != 0) {
                *--bufPtr = (num % 10U) + '0';
                num /= 10U;
                len++;
            }
            while (len < s.precision) {
                *--bufPtr = '0';
                len++;
            }
            if (s.leadingChar != '\0') {
                *--bufPtr = s.leadingChar;
                len++;
            }
            break;

        case 'o':
            num = va_arg(args, u32);
            do {
                if (s.isHalf) {
                    num = (u16)num;
                }
            } while (0);
            if (!s.usePrecision) {
                if (s.leadingZeros) {
                    s.precision = s.padding;
                }
                if (s.precision <= 0) {
                    s.precision = 1;
                }
            }
            len = 0;
            while (num != 0) {
                *--bufPtr = (num % 8U) + '0';
                num /= 8U;
                len++;
            }
            if (s.alternativeForm && (len != 0) && (*bufPtr != '0')) {
                *--bufPtr = '0';
                len++;
            }
            while (len < s.precision) {
                *--bufPtr = '0';
                len++;
            }
            break;

        case 'p':
            s.precision = 8;
            s.usePrecision = true;
            s.isLong = true;
            /* fallthrough */
        case 'X':
            hexChars = a0123456789abcd_0;
            goto block_79;
        case 'x':
            hexChars = a0123456789abcd_1;
        block_79:
            num = va_arg(args, u32);
            do {
                if (s.isHalf) {
                    num = (u16)num;
                }
            } while (0);
            if (!s.usePrecision) {
                if (s.leadingZeros) {
                    s.precision = s.padding;
                    if (s.alternativeForm) {
                        s.precision = s.padding - 2;
                    }
                }
                if (s.precision <= 0) {
                    s.precision = 1;
                }
            }
            len = 0;
            while (num != 0) {
                *--bufPtr = hexChars[num % 16U];
                num /= 16U;
                len++;
            }
            while (len < s.precision) {
                *--bufPtr = '0';
                len++;
            }
            if (s.alternativeForm) {
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
            if (s.alternativeForm) {
                len = *bufPtr++;
                if (s.usePrecision) {
                    if (s.precision < len) {
                        len = s.precision;
                    }
                }
            } else if (!s.usePrecision) {
                len = strlen(bufPtr);
            } else {
                char* ptr = memchr(bufPtr, 0, s.precision);
                len = ptr - bufPtr;
                if (ptr == NULL) {
                    len = s.precision;
                }
            }
            break;

        case 'n':
            bufPtr = va_arg(args, s32*);
            if (s.isHalf) {
                LOH(*bufPtr) = written;
            } else if (s.isLong) {
                LOW(*bufPtr) = written;
            } else if (s.isLongLong) {
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
        if (len < s.padding && !s.leftJustified) {
            while (len < s.padding) {
                out[written++] = ' ';
                s.padding--;
            }
        }
        memmove(&out[written], bufPtr, len);
        written += len;
        while (len < s.padding) {
            out[written++] = ' ';
            len++;
        }
    }
end:
    out[written] = 0;
    return written;
}
