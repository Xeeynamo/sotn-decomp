// SPDX-License-Identifier: AGPL-3.0-or-later
//! PSPO=4,p
#include <game_psp.h>

#include "CompressedNumbers.h"
#include "ExceptionHandler.h"

enum { SKIP = 0, APPLY = 1 };

typedef void (*DeleteFunc)(void*);

typedef struct ActionIterator {
    ExceptionInfo info;
    ThrowContext context;
} ActionIterator;

typedef struct ex_catchblock {
    u8* catch_type;
    unsigned long pcoffset;
    long cinfo_ref;
} ex_catchblock;

typedef struct ex_activecatchblock {
    long cinfo_ref;
} ex_activecatchblock;

typedef struct ex_specification {
    unsigned long nspecs;
    unsigned long pcoffset;
    long cinfo_ref;
    char* specs;
} ex_specification;

void Branch(ExceptionInfo* info, ThrowContext* context);
void Specification(int apply, ExceptionInfo* info, ThrowContext* context);
void ActiveCatchBlock(int apply, ExceptionInfo* info, ThrowContext* context);
void CatchBlock(int apply, ExceptionInfo* info, ThrowContext* context);
void DeletePointerCond(int apply, ExceptionInfo* info, ThrowContext* context);
void DeletePointer(int apply, ExceptionInfo* info, ThrowContext* context);
void DestroyMemberArray(int apply, ExceptionInfo* info, ThrowContext* context);
void DestroyMemberCond(int apply, ExceptionInfo* info, ThrowContext* context);
void DestroyMember(int apply, ExceptionInfo* info, ThrowContext* context);
void DestroyBase(int apply, ExceptionInfo* info, ThrowContext* context);
void DestroyLocalArray(int apply, ExceptionInfo* info, ThrowContext* context);
void DestroyLocalPointer(int apply, ExceptionInfo* info, ThrowContext* context);
void DestroyLocalCond(int apply, ExceptionInfo* info, ThrowContext* context);
void DestroyLocal(int apply, ExceptionInfo* info, ThrowContext* context);
ExceptionInfo* func_psp_089368B8(ExceptionInfo* arg0, ExceptionInfo* arg1);
ThrowContext* func_psp_08936844(ThrowContext* arg0, ThrowContext* arg1);
void DecodeCatchBlock(char* ap, ex_catchblock* cb);

static ExceptionTableIndex* BinarySearch(
    ExceptionTableIndex* table, unsigned long tablesize, char* return_address) {
    ExceptionTableIndex* p;
    long i, m, n;

    for (i = 0, n = tablesize - 1; i <= n;) {
        p = &table[m = (i + n) >> 1];
        if (return_address < p->function_address)
            n = m - 1;
        else if (return_address > p->function_address + FUNCTION_SIZE(p))
            i = m + 1;
        else
            return p;
    }

    return 0;
}

void FindExceptionRecord(char* return_address, ExceptionInfo* info) {
    ExceptionTableIndex* exceptiontable;
    char* rangetable;
    unsigned long return_offset;
    unsigned long currentPC;
    unsigned long deltaPC;
    unsigned long length;
    unsigned long actions;

    info->exception_record = 0;
    info->action_pointer = 0;

    if (!__FindExceptionTable(info, return_address)) {
        return;
    }

    return_address = __AdjustReturnAddress(info, context, return_address);

    if (!(exceptiontable = BinarySearch(
              info->exception_table_start,
              info->exception_table_end - info->exception_table_start,
              return_address))) {
        return;
    }
    if (DIRECT_STORED(exceptiontable))
        info->exception_record = (char*)&exceptiontable->exception_table;
    else
        info->exception_record = exceptiontable->exception_table;

    info->current_function = exceptiontable->function_address;
    return_offset = return_address - exceptiontable->function_address;

    rangetable = __SkipUnwindInfo(info->exception_record);
    for (currentPC = 0;;) {
        rangetable = __DecodeUnsignedNumber(rangetable, &deltaPC);
        if (deltaPC == 0)
            return;
        rangetable = __DecodeUnsignedNumber(rangetable, &length);
        rangetable = __DecodeUnsignedNumber(rangetable, &actions);
        currentPC += deltaPC;
        if (return_offset < currentPC)
            return;
        currentPC += length;
        if (return_offset <= currentPC) {
            break;
        }
    }

    info->action_pointer = info->exception_record + actions;
}

static exaction_type CurrentAction(const ActionIterator* iter) {
    return iter->info.action_pointer
               ? *(exaction_type*)iter->info.action_pointer & EXACTION_MASK
               : EXACTION_ENDOFLIST;
}

static exaction_type NextAction(ActionIterator* iter) {
    ExceptionInfo* info = &iter->info;
    ThrowContext* context = &iter->context;
    exaction_type action;

    while (true) {
        if (!info->action_pointer ||
            *(exaction_type*)info->action_pointer & EXACTION_ENDBIT) {
            FindExceptionRecord(__PopStackFrame(context, info), info);
            if (!info->exception_record) {
                terminate();
            }
            __SetupFrameInfo(context, info);
            if (!info->action_pointer)
                continue;
        } else {
            switch (*(exaction_type*)info->action_pointer & EXACTION_MASK) {
            case EXACTION_DESTROYLOCAL:
                DestroyLocal(SKIP, info, context);
                break;
            case EXACTION_DESTROYLOCALCOND:
                DestroyLocalCond(SKIP, info, context);
                break;
            case EXACTION_DESTROYLOCALPOINTER:
                DestroyLocalPointer(SKIP, info, context);
                break;
            case EXACTION_DESTROYLOCALARRAY:
                DestroyLocalArray(SKIP, info, context);
                break;
            case EXACTION_DESTROYBASE:
                DestroyBase(SKIP, info, context);
                break;
            case EXACTION_DESTROYMEMBER:
                DestroyMember(SKIP, info, context);
                break;
            case EXACTION_DESTROYMEMBERCOND:
                DestroyMemberCond(SKIP, info, context);
                break;
            case EXACTION_DESTROYMEMBERARRAY:
                DestroyMemberArray(SKIP, info, context);
                break;
            case EXACTION_DELETEPOINTER:
                DeletePointer(SKIP, info, context);
                break;
            case EXACTION_DELETEPOINTERCOND:
                DeletePointerCond(SKIP, info, context);
                break;
            case EXACTION_CATCHBLOCK:
                CatchBlock(SKIP, info, context);
                break;
            case EXACTION_ACTIVECATCHBLOCK:
                ActiveCatchBlock(SKIP, info, context);
                break;
            case EXACTION_SPECIFICATION:
                Specification(SKIP, info, context);
                break;
            default:
                terminate();
                break;
            }
        }

        while ((action = *(exaction_type*)info->action_pointer &
                         EXACTION_MASK) == EXACTION_BRANCH)
            Branch(info, context);

        return action;
    }
}

static void Branch(ExceptionInfo* info, ThrowContext* context) {
    long target;
    __DecodeSignedNumber(info->action_pointer + sizeof(exaction_type), &target);
    info->action_pointer += target;
}

static void Specification(
    int apply, ExceptionInfo* info, ThrowContext* context) {
    char* ap = info->action_pointer;
    unsigned long nspecs, pcoffset;
    long cinfo_ref;

    ap += sizeof(exaction_type);
    ap = __DecodeUnsignedNumber(ap, &nspecs);
    ap = __DecodeUnsignedNumber(ap, &pcoffset);
    ap = __DecodeSignedNumber(ap, &cinfo_ref);
    ap += nspecs * sizeof(char*);

    if (apply) {
    }

    info->action_pointer = ap;
}

static void ActiveCatchBlock(
    int apply, ExceptionInfo* info, ThrowContext* context) {
    char* ap = info->action_pointer;
    long cinfo_ref;
    CatchInfo* catchinfo;

    ap += sizeof(exaction_type);
    ap = __DecodeSignedNumber(ap, &cinfo_ref);

    if (apply) {
        catchinfo = (CatchInfo*)__LocalVariable(context, cinfo_ref);
        if (catchinfo->dtor) {
            if (context->location == catchinfo->location) {
                context->dtor = catchinfo->dtor;
            } else
                DTORCALL_COMPLETE(catchinfo->dtor, catchinfo->location);
        }
    }

    info->action_pointer = ap;
}

static void CatchBlock(int apply, ExceptionInfo* info, ThrowContext* context) {
    char* ap = info->action_pointer;
    void* catch_type;
    unsigned long pcoffset;
    long cinfo_ref;

    ap += sizeof(exaction_type);
    ap = __DecodeAddress(ap, &catch_type);
    ap = __DecodeUnsignedNumber(ap, &pcoffset);
    ap = __DecodeSignedNumber(ap, &cinfo_ref);

    if (apply) {
    }

    info->action_pointer = ap;
}

char* __DecodeAddress(char* p, void** paddr) {
    unsigned long addr;

    addr = ((unsigned char*)p)[0] | (((unsigned char*)p)[1] << 8) |
           (((unsigned char*)p)[2] << 0x10) | (((unsigned char*)p)[3] << 0x18);

    *paddr = (void*)addr;
    return p + 4;
}

static void DeletePointerCond(
    int apply, ExceptionInfo* info, ThrowContext* context) {
    char* ap = info->action_pointer;
    long cond, ptr;
    void* deletefunc;
    char* objectptr;
    int regptr, regcond;
    local_cond_type deleteIt;

    regcond = *(exaction_type*)ap & REGCOND;
    regptr = *(exaction_type*)ap & REGPTR;
    ap += sizeof(exaction_type);
    ap = __DecodeSignedNumber(ap, &cond);
    ap = __DecodeSignedNumber(ap, &ptr);
    ap = __DecodeAddress(ap, &deletefunc);

    if (apply) {
        if (regcond)
            deleteIt = (local_cond_type)__Register(context, cond);
        else
            deleteIt = *(local_cond_type*)__LocalVariable(context, cond);

        if (deleteIt) {
            if (regptr)
                objectptr = (char*)__Register(context, ptr);
            else
                objectptr = *(char**)__LocalVariable(context, ptr);

            ((DeleteFunc)__FunctionPointer(info, context, deletefunc))(
                objectptr);
        }
    }

    info->action_pointer = ap;
}

static void DeletePointer(
    int apply, ExceptionInfo* info, ThrowContext* context) {
    char* ap = info->action_pointer;
    long ptr;
    void* deletefunc;
    char* objectptr;
    int regptr;

    regptr = *(exaction_type*)ap & REGPTR;
    ap += sizeof(exaction_type);
    ap = __DecodeSignedNumber(ap, &ptr);
    ap = __DecodeAddress(ap, &deletefunc);

    if (apply) {
        if (regptr)
            objectptr = (char*)__Register(context, ptr);
        else
            objectptr = *(char**)__LocalVariable(context, ptr);

        ((DeleteFunc)__FunctionPointer(info, context, deletefunc))(objectptr);
    }

    info->action_pointer = ap;
}

static void DestroyMemberArray(
    int apply, ExceptionInfo* info, ThrowContext* context) {
    char* ap = info->action_pointer;
    int regptr;
    long ptr, offset;
    unsigned long nelements, elemsize, i;
    void* dtor;
    char* arrayptr;

    regptr = *(exaction_type*)ap & REGPTR;
    ap += sizeof(exaction_type);
    ap = __DecodeSignedNumber(ap, &ptr);
    ap = __DecodeSignedNumber(ap, &offset);
    ap = __DecodeUnsignedNumber(ap, &nelements);
    ap = __DecodeUnsignedNumber(ap, &elemsize);
    ap = __DecodeAddress(ap, &dtor);

    if (apply) {
        if (regptr)
            arrayptr = (char*)__Register(context, ptr) + offset;
        else
            arrayptr = *(char**)__LocalVariable(context, ptr) + offset;

        for (arrayptr += nelements * elemsize, i = nelements; i > 0; i--) {
            arrayptr -= elemsize;
            DTORCALL_COMPLETE(__FunctionPointer(info, context, dtor), arrayptr);
        }
    }

    info->action_pointer = ap;
}

static void DestroyMemberCond(
    int apply, ExceptionInfo* info, ThrowContext* context) {
    char* ap = info->action_pointer;
    int regptr, regcond;
    long cond, ptr, offset;
    void* dtor;
    char* objectptr;
    vbase_ctor_arg_type destroyIt;

    regcond = *(exaction_type*)ap & REGCOND;
    regptr = *(exaction_type*)ap & REGPTR;
    ap += sizeof(exaction_type);
    ap = __DecodeSignedNumber(ap, &cond);
    ap = __DecodeSignedNumber(ap, &ptr);
    ap = __DecodeSignedNumber(ap, &offset);
    ap = __DecodeAddress(ap, &dtor);

    if (apply) {
        if (regcond)
            destroyIt = (vbase_ctor_arg_type)__Register(context, cond);
        else
            destroyIt = *(vbase_ctor_arg_type*)__LocalVariable(context, cond);

        if (destroyIt) {
            if (regptr)
                objectptr = (char*)__Register(context, ptr);
            else
                objectptr = *(char**)__LocalVariable(context, ptr);

            DTORCALL_COMPLETE(
                __FunctionPointer(info, context, dtor), objectptr + offset);
        }
    }

    info->action_pointer = ap;
}

static void DestroyMember(
    int apply, ExceptionInfo* info, ThrowContext* context) {
    char* ap = info->action_pointer;
    int regptr;
    long ptr, offset;
    void* dtor;
    char* objectptr;

    regptr = *(exaction_type*)ap & REGPTR;
    ap += sizeof(exaction_type);
    ap = __DecodeSignedNumber(ap, &ptr);
    ap = __DecodeSignedNumber(ap, &offset);
    ap = __DecodeAddress(ap, &dtor);

    if (apply) {
        if (regptr)
            objectptr = (char*)__Register(context, ptr);
        else
            objectptr = *(char**)__LocalVariable(context, ptr);

        DTORCALL_COMPLETE(
            __FunctionPointer(info, context, dtor), objectptr + offset);
    }

    info->action_pointer = ap;
}

static void DestroyBase(int apply, ExceptionInfo* info, ThrowContext* context) {
    char* ap = info->action_pointer;
    int regptr;
    long ptr, offset;
    void* dtor;
    char* objectptr;

    regptr = *(exaction_type*)ap & REGPTR;
    ap += sizeof(exaction_type);
    ap = __DecodeSignedNumber(ap, &ptr);
    ap = __DecodeSignedNumber(ap, &offset);
    ap = __DecodeAddress(ap, &dtor);

    if (apply) {
        if (regptr)
            objectptr = (char*)__Register(context, ptr);
        else
            objectptr = *(char**)__LocalVariable(context, ptr);

        DTORCALL_PARTIAL(
            __FunctionPointer(info, context, dtor), objectptr + offset);
    }

    info->action_pointer = ap;
}

static void DestroyLocalArray(
    int apply, ExceptionInfo* info, ThrowContext* context) {
    char* ap = info->action_pointer;
    long array;
    unsigned long nelements, elemsize, i;
    void* dtor;
    char* arrayptr;

    ap += sizeof(exaction_type);
    ap = __DecodeSignedNumber(ap, &array);
    ap = __DecodeUnsignedNumber(ap, &nelements);
    ap = __DecodeUnsignedNumber(ap, &elemsize);
    ap = __DecodeAddress(ap, &dtor);

    if (apply) {
        arrayptr = (char*)__LocalVariable(context, array);
        for (arrayptr += nelements * elemsize, i = nelements; i > 0; i--) {
            arrayptr -= elemsize;
            DTORCALL_COMPLETE(__FunctionPointer(info, context, dtor), arrayptr);
        }
    }

    info->action_pointer = ap;
}

static void DestroyLocalPointer(
    int apply, ExceptionInfo* info, ThrowContext* context) {
    char* ap = info->action_pointer;
    int regptr;
    long ptr;
    void* dtor;
    void* objectptr;

    regptr = *(exaction_type*)ap & REGPTR;
    ap += sizeof(exaction_type);
    ap = __DecodeSignedNumber(ap, &ptr);
    ap = __DecodeAddress(ap, &dtor);

    if (apply) {
        if (regptr)
            objectptr = (void*)__Register(context, ptr);
        else
            objectptr = *(void**)__LocalVariable(context, ptr);

        DTORCALL_COMPLETE(__FunctionPointer(info, context, dtor), objectptr);
    }

    info->action_pointer = ap;
}

static void DestroyLocalCond(
    int apply, ExceptionInfo* info, ThrowContext* context) {
    char* ap = info->action_pointer;
    int regcond;
    long cond, local;
    void* dtor;
    local_cond_type destroyIt;

    regcond = *(exaction_type*)ap & REGCOND;
    ap += sizeof(exaction_type);
    ap = __DecodeSignedNumber(ap, &cond);
    ap = __DecodeSignedNumber(ap, &local);
    ap = __DecodeAddress(ap, &dtor);

    if (apply) {
        if (regcond)
            destroyIt = (local_cond_type)__Register(context, cond);
        else
            destroyIt = *(local_cond_type*)__LocalVariable(context, cond);

        if (destroyIt) {
            DTORCALL_COMPLETE(__FunctionPointer(info, context, dtor),
                              __LocalVariable(context, local));
        }
    }

    info->action_pointer = ap;
}

static void DestroyLocal(
    int apply, ExceptionInfo* info, ThrowContext* context) {
    char* ap = info->action_pointer;
    long local;
    void* dtor;

    ap += sizeof(exaction_type);
    ap = __DecodeSignedNumber(ap, &local);
    ap = __DecodeAddress(ap, &dtor);

    if (apply) {
        DTORCALL_COMPLETE(__FunctionPointer(info, context, dtor),
                          __LocalVariable(context, local));
    }

    info->action_pointer = ap;
}

static void UnwindStack(
    ThrowContext* context, ExceptionInfo* info, char* catcher) {
    exaction_type action;

    while (true) {
        if (info->action_pointer == NULL) {
            FindExceptionRecord(__PopStackFrame(context, info), info);

            if (!info->exception_record) {
                terminate();
            }
            __SetupFrameInfo(context, info);

            if (info->action_pointer == NULL) {
                continue;
            }
        }

        action = *(exaction_type*)info->action_pointer;

        switch (action & EXACTION_MASK) {
        case EXACTION_BRANCH:
            Branch(info, context);
            break;
        case EXACTION_DESTROYLOCAL:
            DestroyLocal(APPLY, info, context);
            break;
        case EXACTION_DESTROYLOCALCOND:
            DestroyLocalCond(APPLY, info, context);
            break;
        case EXACTION_DESTROYLOCALPOINTER:
            DestroyLocalPointer(APPLY, info, context);
            break;
        case EXACTION_DESTROYLOCALARRAY:
            DestroyLocalArray(APPLY, info, context);
            break;
        case EXACTION_DESTROYBASE:
            DestroyBase(APPLY, info, context);
            break;
        case EXACTION_DESTROYMEMBER:
            DestroyMember(APPLY, info, context);
            break;
        case EXACTION_DESTROYMEMBERCOND:
            DestroyMemberCond(APPLY, info, context);
            break;
        case EXACTION_DESTROYMEMBERARRAY:
            DestroyMemberArray(APPLY, info, context);
            break;
        case EXACTION_DELETEPOINTER:
            DeletePointer(APPLY, info, context);
            break;
        case EXACTION_DELETEPOINTERCOND:
            DeletePointerCond(APPLY, info, context);
            break;
        case EXACTION_CATCHBLOCK:
            if (catcher == info->action_pointer)
                return; /*	finished unwinding	*/
            CatchBlock(SKIP, info, context);
            break;
        case EXACTION_ACTIVECATCHBLOCK:
            ActiveCatchBlock(APPLY, info, context);
            break;
        case EXACTION_SPECIFICATION:
            if (catcher == info->action_pointer)
                return; /*	finished unwinding	*/
            Specification(SKIP, info, context);
            break;
        default: /*	error	*/
            terminate();
            break;
        }
        if (action & EXACTION_ENDBIT) {
            info->action_pointer = 0;
        }
    }
}

static CatchInfo* FindMostRecentException(
    ThrowContext* context, ExceptionInfo* info) {
    ActionIterator iter;
    exaction_type action;
    CatchInfo* catchinfo;
    ex_activecatchblock acb;

    func_psp_089368B8(&iter.info, info);
    func_psp_08936844(&iter.context, context);

    for (action = CurrentAction(&iter);; action = NextAction(&iter)) {
        switch (action) {
        case EXACTION_ACTIVECATCHBLOCK:
            break;

        case EXACTION_ENDOFLIST:
        case EXACTION_DESTROYLOCAL:
        case EXACTION_DESTROYLOCALCOND:
        case EXACTION_DESTROYLOCALPOINTER:
        case EXACTION_DESTROYLOCALARRAY:
        case EXACTION_DESTROYBASE:
        case EXACTION_DESTROYMEMBER:
        case EXACTION_DESTROYMEMBERCOND:
        case EXACTION_DESTROYMEMBERARRAY:
        case EXACTION_DELETEPOINTER:
        case EXACTION_DELETEPOINTERCOND:
        case EXACTION_CATCHBLOCK:
        case EXACTION_SPECIFICATION:
            continue;

        case EXACTION_TERMINATE:
        default:
            terminate();
        }
        break;
    }

    DecodeActiveCatchBlock(iter.info.action_pointer, &acb);
    catchinfo = (CatchInfo*)__LocalVariable(&iter.context, acb.cinfo_ref);
    context->throwtype = (s8*)catchinfo->typeinfo;
    context->location = catchinfo->location;
    context->dtor = 0;
    context->catchinfo = catchinfo;

    return catchinfo;
}

INCLUDE_ASM("main_psp/nonmatchings/main_psp/MSL/Runtime/ExceptionHandler", DecodeActiveCatchBlock);

ThrowContext* func_psp_08936844(ThrowContext* arg0, ThrowContext* arg1) {
    arg0->throwtype = arg1->throwtype;
    arg0->location = arg1->location;
    arg0->dtor = arg1->dtor;
    arg0->catchinfo = arg1->catchinfo;
    arg0->returnaddr = arg1->returnaddr;
    arg0->SP = arg1->SP;
    arg0->FP = arg1->FP;
    arg0->throwSP = arg1->throwSP;
    arg0->target = arg1->target;
    return arg0;
}

ExceptionInfo* func_psp_089368B8(ExceptionInfo* arg0, ExceptionInfo* arg1) {
    arg0->current_function = arg1->current_function;
    arg0->exception_record = arg1->exception_record;
    arg0->action_pointer = arg1->action_pointer;
    arg0->exception_table_start = arg1->exception_table_start;
    arg0->exception_table_end = arg1->exception_table_end;
    arg0->target.dummy = arg1->target.dummy;
    return arg0;
}

static int IsInSpecification(char* extype, ex_specification* spec) {
    char* specptr = spec->specs;
    char* spectype;
    long dummy;
    int i;

    for (i = 0; i < spec->nspecs; i++) {
        __DecodeAddress(specptr, (void**)&spectype);
        if (__throw_catch_compare((u8*)extype, (u8*)spectype, &dummy)) {
            return true;
        }
        specptr += 4;
    }
    return false;
}

INCLUDE_ASM("main_psp/nonmatchings/main_psp/MSL/Runtime/ExceptionHandler", __unexpected);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/MSL/Runtime/ExceptionHandler", func_psp_08936A44);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/MSL/Runtime/ExceptionHandler", func_psp_08936AC8);

static void DecodeSpecification(char* ap, ex_specification* sp) {
    ap += sizeof(exaction_type);
    ap = __DecodeUnsignedNumber(ap, &sp->nspecs);
    ap = __DecodeUnsignedNumber(ap, &sp->pcoffset);
    ap = __DecodeSignedNumber(ap, &sp->cinfo_ref);
    sp->specs = ap;
}

static void HandleUnexpected(ThrowContext* context, ExceptionInfo* info,
                             ex_specification* spec, char* unexp) {
    CatchInfo* catchinfo;

    UnwindStack(context, info, unexp);

    catchinfo = (CatchInfo*)__LocalVariable(context, spec->cinfo_ref);
    catchinfo->location = context->location;
    catchinfo->typeinfo = context->throwtype;
    catchinfo->dtor = context->dtor;
    catchinfo->stacktop = unexp;

    __TransferControl(context, info, info->current_function + spec->pcoffset);
}

static char* FindExceptionHandler(
    ThrowContext* context, ExceptionInfo* info, long* result_offset) {
    ActionIterator iter;
    exaction_type action;
    ex_catchblock handler;
    ex_specification spec;

    func_psp_089368B8(&iter.info, info);
    func_psp_08936844(&iter.context, context);

    for (action = CurrentAction(&iter);; action = NextAction(&iter)) {
        switch (action) {
        case EXACTION_CATCHBLOCK:
            DecodeCatchBlock(iter.info.action_pointer, &handler);
            if (__throw_catch_compare(context->throwtype, handler.catch_type,
                                      result_offset) == 0) {
                continue;
            }
            break;
        case EXACTION_SPECIFICATION:
            DecodeSpecification(iter.info.action_pointer, &spec);
            if (IsInSpecification((char*)context->throwtype, &spec) == false) {
                HandleUnexpected(
                    context, info, &spec, iter.info.action_pointer);
            }
            continue;
        case EXACTION_ENDOFLIST:
        case EXACTION_DESTROYLOCAL:
        case EXACTION_DESTROYLOCALCOND:
        case EXACTION_DESTROYLOCALPOINTER:
        case EXACTION_DESTROYLOCALARRAY:
        case EXACTION_DESTROYBASE:
        case EXACTION_DESTROYMEMBER:
        case EXACTION_DESTROYMEMBERCOND:
        case EXACTION_DESTROYMEMBERARRAY:
        case EXACTION_DELETEPOINTER:
        case EXACTION_DELETEPOINTERCOND:
        case EXACTION_ACTIVECATCHBLOCK:
            continue;
        case EXACTION_TERMINATE:
        default:
            terminate();
            break;
        }
        break;
    }
    return iter.info.action_pointer;
}

static void DecodeCatchBlock(char* ap, ex_catchblock* cb) {
    ap = __DecodeAddress(ap + sizeof(exaction_type), (void**)&cb->catch_type);

    cb->catch_type = cb->catch_type != NULL ? cb->catch_type : NULL;

    ap = __DecodeUnsignedNumber(ap, &cb->pcoffset);
    ap = __DecodeSignedNumber(ap, &cb->cinfo_ref);
}

static void SetupCatchInfo(
    ThrowContext* context, long cinfo_ref, long result_offset) {
    CatchInfo* catchinfo = (CatchInfo*)__LocalVariable(context, cinfo_ref);

    catchinfo->location = context->location;
    catchinfo->typeinfo = context->throwtype;
    catchinfo->dtor = context->dtor;
    if (*context->throwtype == '*') {
        catchinfo->sublocation = &catchinfo->pointercopy;
        catchinfo->pointercopy = *(long*)context->location + result_offset;
    } else {
        catchinfo->sublocation = (char*)context->location + result_offset;
    }
}

INCLUDE_ASM("main_psp/nonmatchings/main_psp/MSL/Runtime/ExceptionHandler", __ThrowHandler);

void __end_catch(CatchInfo* catchinfo) {
    if (catchinfo->location != NULL && catchinfo->dtor != NULL) {
        DTORCALL_COMPLETE(catchinfo->dtor, catchinfo->location);
    }
}

INCLUDE_RODATA("main_psp/nonmatchings/main_psp/MSL/Runtime/ExceptionHandler", D_psp_0893C1A0);

INCLUDE_RODATA("main_psp/nonmatchings/main_psp/MSL/Runtime/ExceptionHandler", D_psp_0893C1AC);

const char D_psp_0893C1B4[] = "bad_exception";

INCLUDE_ASM("main_psp/nonmatchings/main_psp/MSL/Runtime/ExceptionHandler", func_psp_08936E8C);
