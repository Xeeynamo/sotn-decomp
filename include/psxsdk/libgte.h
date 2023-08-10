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
    u_char cd; // GPU code
} CVECTOR;

MATRIX* RotMatrix(SVECTOR* r, MATRIX* m);
void SetGeomOffset(long ofx, long ofy);
long RotTransPers(SVECTOR*, long*, long*, long*);
void SetGeomScreen(long h);
void SetRotMatrix(MATRIX* m);
MATRIX* TransMatrix(MATRIX* m, VECTOR* v);

#endif