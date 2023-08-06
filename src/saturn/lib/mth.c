#include "sattypes.h"
#include "inc_asm.h"

// SEGA_MTH.A
// _MTH_MoveMatrix (hasm)
INCLUDE_ASM("asm/saturn/zero/data", d602F638, d_0602F638);

// _MTH_RotateMatrixX (hasm)
INCLUDE_ASM_NO_ALIGN("asm/saturn/zero/data", d602F692, d_0602F692);

INCLUDE_ASM("asm/saturn/zero/data", d602F758, d_0602F758);

// _MTH_RotateMatrixZ (hasm)
INCLUDE_ASM("asm/saturn/zero/data", d602F83C, d_0602F83C);
INCLUDE_ASM("asm/saturn/zero/data", d602F90C, d_0602F90C);

// _MTH_MulMatrix (hasm)
INCLUDE_ASM_NO_ALIGN("asm/saturn/zero/data", d602F922, d_0602F922);

// _MTH_CoordTrans (hasm)
INCLUDE_ASM("asm/saturn/zero/data", d602FA5C, d_0602FA5C);

// _MTH_NormalTrans (hasm)
INCLUDE_ASM("asm/saturn/zero/data", d602FAA8, d_0602FAA8);

INCLUDE_ASM("asm/saturn/zero/data", d602FAEC, d_0602FAEC);

// _MTH_ComputeBright (hasm)
INCLUDE_ASM("asm/saturn/zero/data", d602FB5C, d_0602FB5C);

INCLUDE_ASM("asm/saturn/zero/data", d602FB84, d_0602FB84);

// _MTH_Hypot (C)
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6030228, func_06030228);

// _INT_SetScuFunc
INCLUDE_ASM("asm/saturn/zero/data", d6030388, d_06030388);
