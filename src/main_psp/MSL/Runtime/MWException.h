// SPDX-License-Identifier: AGPL-3.0-or-later
#ifndef RUNTIME_MWEXCEPTION_H
#define RUNTIME_MWEXCEPTION_H

#include <common.h>

typedef s8 vbase_ctor_arg_type;
typedef s8 local_cond_type;

typedef struct CatchInfo {
    /* 0x00 */ void* location;
    /* 0x04 */ void* typeinfo;
    /* 0x08 */ void* dtor;
    /* 0x0C */ void* sublocation;
    /* 0x10 */ long pointercopy;
    /* 0x14 */ void* stacktop;
} CatchInfo; // size: 0x18

#define DTORARG_TYPE short
#define DTORARG_PARTIAL (0)   //	destroy non-virtual bases
#define DTORARG_COMPLETE (-1) //	destroy all bases
#define DTORARG_DELETE (1)    //	destroy all bases and delete object

#define DTORCALL_COMPLETE(dtor, objptr)                                        \
    (((void (*)(void*, DTORARG_TYPE))dtor)(objptr, DTORARG_COMPLETE))
#define DTORCALL_PARTIAL(dtor, objptr)                                         \
    (((void (*)(void*, DTORARG_TYPE))dtor)(objptr, DTORARG_PARTIAL))

#endif // RUNTIME_MWEXCEPTION_H
