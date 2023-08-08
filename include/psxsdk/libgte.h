#ifndef LIBGTE_H
#define LIBGTE_H

void InitGeom();

typedef struct {
    short m[3][3]; // 3 x 3 matrix coefficient value
    long t[3];     // Parallel transfer volume
} MATRIX;

typedef struct {
    long vx, vy, vz; // Vector coordinates
    long pad;        // System reserved
} VECTOR;

typedef struct {
    short vx, vy, vz; // Vector coordinates
    short pad;        // System reserved
} SVECTOR;

MATRIX* RotMatrix(SVECTOR* r, MATRIX* m);
void SetGeomOffset(long ofx, long ofy);
long RotTransPers(SVECTOR*, long*, long*, long*);
void SetGeomScreen(long h);
void SetRotMatrix(MATRIX* m);
MATRIX* TransMatrix(MATRIX* m, VECTOR* v);

#endif