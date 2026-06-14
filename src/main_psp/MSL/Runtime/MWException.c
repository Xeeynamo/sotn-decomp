// SPDX-License-Identifier: AGPL-3.0-or-later
#include <game_psp.h>

typedef void (*unexpected_handler)();
typedef void (*terminate_handler)();
void terminate();

static void dthandler() { abort(); }

static terminate_handler thandler = dthandler;

static void duhandler() { terminate(); }

static unexpected_handler uhandler = duhandler;

void terminate(void) { thandler(); }

void unexpected(void) { uhandler(); }

#define CONST_CHAR 'C'

s32 __throw_catch_compare(s8* throwtype, s8* catchtype, s32* offset_result) {
    s8* cptr1;
    s8* cptr2;
    s8* var_s3;

    *offset_result = 0;
    if ((cptr2 = catchtype) == 0) {
        return true;
    }
    cptr1 = throwtype;

    if (*cptr2 == 'P') {
        cptr2++;

        if (*cptr2 == CONST_CHAR)
            cptr2++;
        if (*cptr2 == 'V')
            cptr2++;
        if (*cptr2 == 'v') {
            if (*cptr1 == 'P' || *cptr1 == '*') {
                return true;
            }
        }
        cptr2 = catchtype;
    }

    switch (*cptr1) {
    case '*':
    case '!':
        if (*cptr1++ != *cptr2++) {
            return false;
        }
        for (;;) {
            if (*cptr1 == *cptr2++) {
                if (*cptr1++ == '!') {
                    s32 offset;

                    for (offset = 0; *cptr1 != '!';) {
                        offset = (offset * 10) + *cptr1++ - '0';
                    }
                    *offset_result = offset;
                    return true;
                }
            } else {
                while (*cptr1++ != '!')
                    ;
                while (*cptr1++ != '!')
                    ;
                if (*cptr1 == 0) {
                    return false;
                }
                cptr2 = catchtype + 1;
            }
        }
        return false;
    }
    while ((*cptr1 == 'P' || *cptr1 == 'R') && *cptr1 == *cptr2) {
        cptr1++;
        cptr2++;
        if (*cptr2 == CONST_CHAR) {
            if (*cptr1 == CONST_CHAR)
                cptr1++;
            cptr2++;
        }
        if (*cptr1 == CONST_CHAR) {
            return false;
        }
        if (*cptr2 == 'V') {
            if (*cptr1 == 'V')
                cptr1++;
            cptr2++;
        }
        if (*cptr1 == 'V') {
            return false;
        }
    }
    while (*cptr1 == *cptr2) {
        if (*cptr1 == 0) {
            return true;
        }
        cptr1++;
        var_s3 = cptr2;
        cptr2 = var_s3 + 1;
    }
    return false;
}
