#ifndef TYPES_H
#define TYPES_H

#ifndef VERSION_PC
typedef char int8_t;
typedef short int16_t;
typedef int int32_t;
typedef long long int64_t;
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long long uint64_t;
typedef unsigned char u_char;
typedef unsigned short u_short;
typedef unsigned long u_long;
typedef unsigned int size_t;
#else
#include <stdint.h>
#endif

#ifdef _MSC_VER
typedef unsigned char u_char;
typedef unsigned short u_short;
typedef unsigned long long u_long;
#endif

typedef signed char s8;
typedef signed short s16;
typedef signed int s32;
typedef signed long long s64;
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

typedef signed char byte;
#ifndef __cplusplus
typedef enum { false, true } bool;
#endif

#ifndef NULL
#define NULL (0)
#endif

typedef union {
    s32 val;
    struct {
        s16 lo;
        s16 hi;
    } i;
} f32;

typedef struct {
    /* 0x0 */ s16 x;
    /* 0x2 */ s16 y;
} Point16; // size = 0x4

typedef struct {
    u8 u;
    u8 v;
} uvPair;

typedef struct {
    u8 r;
    u8 g;
    u8 b;
    u8 pad; // could be an A for RGBA but unused so unknown
} rgb_set;

#endif
