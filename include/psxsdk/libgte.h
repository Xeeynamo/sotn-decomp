#ifndef VERSION_PC
#ifndef LIBGTE_H
#define LIBGTE_H

void InitGeom();

typedef struct {
    short m[3][3]; // 3 x 3 matrix coefficient value
    long t[3];     // Parallel transfer volume
} MATRIX;          // size = 0x1E

typedef struct {
    long vx, vy, vz; // Vector coordinates
    long pad;        // System reserved
} VECTOR;            // size = 0x10

typedef struct {
    short vx, vy, vz; // Vector coordinates
    short pad;        // System reserved
} SVECTOR;            // size = 0x8

typedef struct {
    u_char r, g, b; // Color palette
    u_char cd;      // GPU code
} CVECTOR;

MATRIX* RotMatrix(SVECTOR* r, MATRIX* m);
void SetGeomOffset(long ofx, long ofy);
long RotTransPers(SVECTOR*, long*, long*, long*);
void SetGeomScreen(long h);
void SetRotMatrix(MATRIX* m);
MATRIX* RotMatrixX(long r, MATRIX* m);
MATRIX* RotMatrixY(long r, MATRIX* m);
MATRIX* RotMatrixZ(long r, MATRIX* m);
MATRIX* TransMatrix(MATRIX* m, VECTOR* v);
MATRIX* ScaleMatrix(MATRIX* m, VECTOR* v);
void SetTransMatrix(MATRIX* m);
long RotTransPers4(
    SVECTOR* v0, SVECTOR* v1, SVECTOR* v2,
    SVECTOR* v3, // Pointers to vectors (input)
    long* v10, long* v11, long* v12,
    long* v13, // Pointers to screen coordinates
    long* p,   // Pointer to interpolated value for depth cueing
    long* flag // Pointer to flag
);
long RotAverageNclip4(
    SVECTOR* v0, SVECTOR* v1, SVECTOR* v2,
    SVECTOR* v3, // Pointer to vectors (input)
    long* sxy0, long* sxy1, long* sxy2,
    long* sxy3, // Pointer to coordinates (output)
    long* p,    // Pointer to interpolation value (output)
    long* otz,  // Pointer to OTZ value (output)
    long* flag  // Pointer to flag (output)
);
void NormalColorCol(SVECTOR* v0, // Pointer to normal vector (input)
                    CVECTOR* v1, // Pointer to primary color vector (input)
                    CVECTOR* v2  // Pointer to color vector (output)
);
MATRIX* RotMatrixY(long r,   // Rotation angle(input)
                   MATRIX* m // Pointer to rotation matrix (input/output)
);
void SetBackColor(long rbk, long gbk, long bbk);
void SetColorMatrix(MATRIX* m);
void SetLightMatrix(MATRIX* m);
void SetTransMatrix(MATRIX* m);
void SetFarColor(long rfc, long gfc, long bfc); // Color values (input)
void SetFogNear(long a, long h); // Distance between visual point and screen

extern long SquareRoot0(long a);
extern long SquareRoot12(long a);
extern int rcos(int a);
extern int rsin(int a);
extern long ratan2(long y, long x);

#if !defined(VERSION_PC) && !defined(M2CTX) && !defined(PERMUTER)
#define gte_SetRotMatrix(r0)                                                   \
    __asm__ volatile(                                                          \
        "lw	$12, 0( %0 );"                                                     \
        "lw	$13, 4( %0 );"                                                     \
        "ctc2	$12, $0;"                                                        \
        "ctc2	$13, $1;"                                                        \
        "lw	$12, 8( %0 );"                                                     \
        "lw	$13, 12( %0 );"                                                    \
        "lw	$14, 16( %0 );"                                                    \
        "ctc2	$12, $2;"                                                        \
        "ctc2	$13, $3;"                                                        \
        "ctc2	$14, $4"                                                         \
        :                                                                      \
        : "r"(r0)                                                              \
        : "$12", "$13", "$14")

#define gte_SetTransMatrix(r0)                                                 \
    __asm__ volatile(                                                          \
        "lw	$12, 20( %0 );"                                                    \
        "lw	$13, 24( %0 );"                                                    \
        "ctc2	$12, $5;"                                                        \
        "lw	$14, 28( %0 );"                                                    \
        "ctc2	$13, $6;"                                                        \
        "ctc2	$14, $7"                                                         \
        :                                                                      \
        : "r"(r0)                                                              \
        : "$12", "$13", "$14")
#define gte_ldv0(r0)                                                           \
    __asm__ volatile("lwc2	$0, 0( %0 );"                                       \
                     "lwc2	$1, 4( %0 )"                                        \
                     :                                                         \
                     : "r"(r0))
#define gte_ldv1(r0)                                                           \
    __asm__ volatile("lwc2	$2, 0( %0 );"                                       \
                     "lwc2	$3, 4( %0 )"                                        \
                     :                                                         \
                     : "r"(r0))
#define gte_ldv2(r0)                                                           \
    __asm__ volatile("lwc2	$4, 0( %0 );"                                       \
                     "lwc2	$5, 4( %0 )"                                        \
                     :                                                         \
                     : "r"(r0))

// NOTE: These are not the official defines in the SDK.
// They were identified by looking at functions which used them.
#define gte_rtps()                                                             \
    __asm__ volatile("nop;"                                                    \
                     "nop;"                                                    \
                     ".word 0x4A180001")
#define gte_rtpt()                                                             \
    __asm__ volatile("nop;"                                                    \
                     "nop;"                                                    \
                     ".word 0x4A280030")
#define gte_nclip()                                                            \
    __asm__ volatile("nop;"                                                    \
                     "nop;"                                                    \
                     ".word 0x4B400006")

#define gte_stsxy2(r0)                                                         \
    __asm__ volatile("swc2	$14, 0( %0 )" : : "r"(r0) : "memory")
#define gte_stszotz(r0)                                                        \
    __asm__ volatile(                                                          \
        "mfc2	$12, $19;"                                                       \
        "nop;"                                                                 \
        "sra	$12, $12, 2;"                                                     \
        "sw	$12, 0( %0 )"                                                      \
        :                                                                      \
        : "r"(r0)                                                              \
        : "$12", "memory")

#define gte_ldv3(r0, r1, r2)                                                   \
    __asm__ volatile(                                                          \
        "lwc2	$0, 0( %0 );"                                                    \
        "lwc2	$1, 4( %0 );"                                                    \
        "lwc2	$2, 0( %1 );"                                                    \
        "lwc2	$3, 4( %1 );"                                                    \
        "lwc2	$4, 0( %2 );"                                                    \
        "lwc2	$5, 4( %2 )"                                                     \
        :                                                                      \
        : "r"(r0), "r"(r1), "r"(r2))

#define gte_stopz(r0)                                                          \
    __asm__ volatile("swc2	$24, 0( %0 )" : : "r"(r0) : "memory")

#define gte_stsxy3(r0, r1, r2)                                                 \
    __asm__ volatile(                                                          \
        "swc2	$12, 0( %0 );"                                                   \
        "swc2	$13, 0( %1 );"                                                   \
        "swc2	$14, 0( %2 )"                                                    \
        :                                                                      \
        : "r"(r0), "r"(r1), "r"(r2)                                            \
        : "memory")
#define gte_stsxy(r0)                                                          \
    __asm__ volatile("swc2	$14, 0( %0 )" : : "r"(r0) : "memory")

#define gte_stsxy3_gt3(r0)                                                     \
    __asm__ volatile(                                                          \
        "swc2	$12, 8( %0 );"                                                   \
        "swc2	$13, 20( %0 );"                                                  \
        "swc2	$14, 32( %0 )"                                                   \
        :                                                                      \
        : "r"(r0)                                                              \
        : "memory")

#define gte_ldv3c(r0)                                                          \
    __asm__ volatile(                                                          \
        "lwc2	$0, 0( %0 );"                                                    \
        "lwc2	$1, 4( %0 );"                                                    \
        "lwc2	$2, 8( %0 );"                                                    \
        "lwc2	$3, 12( %0 );"                                                   \
        "lwc2	$4, 16( %0 );"                                                   \
        "lwc2	$5, 20( %0 )"                                                    \
        :                                                                      \
        : "r"(r0))

#define gte_SetTransVector(r0)                                                 \
    __asm__ volatile(                                                          \
        "lw	$12, 0( %0 );"                                                     \
        "lw	$13, 4( %0 );"                                                     \
        "lw	$14, 8( %0 );"                                                     \
        "ctc2	$12, $5;"                                                        \
        "ctc2	$13, $6;"                                                        \
        "ctc2	$14, $7"                                                         \
        :                                                                      \
        : "r"(r0)                                                              \
        : "$12", "$13", "$14")

#define gte_SetGeomScreen(r0) __asm__ volatile("ctc2	%0, $26" : : "r"(r0))

#else

#define gte_SetRotMatrix(r0)
#define gte_SetTransMatrix(r0)
#define gte_ldv0(r0)
#define gte_rtps()
#define gte_rtpt()
#define gte_nclip()
#define gte_stsxy2(r0)
#define gte_stszotz(r0)
#define gte_ldv3(r0, r1, r2)
#define gte_stopz(r0)
#define gte_stsxy3(r0, r1, r2)
#define gte_stsxy(r0)
#define gte_SetGeomScreen(r0)

#endif

#endif
#else
#include "../../src/pc/psxsdk/PsyCross/src/gte/psx/libgte.h"
#include "../../src/pc/psxsdk/PsyCross/src/gte/psx/inline_c.h"
#endif
