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
MATRIX* TransMatrix(MATRIX* m, VECTOR* v);
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

#endif