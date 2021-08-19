/*
 * Filter Coefficients (C Source) generated by the Filter Design and Analysis Tool
 * Generated by MATLAB(R) 9.6 and DSP System Toolbox 9.8.
 * Generated on: 17-Sep-2020 11:56:12
 */

/*
 * Discrete-Time FIR Filter (real)
 * -------------------------------
 * Filter Structure  : Direct-Form FIR
 * Filter Length     : 101
 * Stable            : Yes
 * Linear Phase      : Yes (Type 1)
 * Arithmetic        : fixed
 * Numerator         : s16,18 -> [-1.250000e-01 1.250000e-01)
 * Input             : s16,15 -> [-1 1)
 * Filter Internals  : Full Precision
 *   Output          : s35,33 -> [-2 2)  (auto determined)
 *   Product         : s31,33 -> [-1.250000e-01 1.250000e-01)  (auto determined)
 *   Accumulator     : s35,33 -> [-2 2)  (auto determined)
 *   Round Mode      : No rounding
 *   Overflow Mode   : No overflow
 */

/* General type conversion for MATLAB generated C-code  */
#include "tmwtypes.h"
/* 
 * Expected path to tmwtypes.h 
 * C:\Program Files\Polyspace\R2019a\extern\include\tmwtypes.h 
 */
const int BL = 101;
const int32_T B[101] = {
             0,          -4,          -7,         -10,         -8,           0,
            15,          35,        57,         77,         89,         89,
           75,         51,          23,           0,         -7,          8,
           47,         106,         170,        220,        239,        210,
           128,           0,        -153,       -302,       -412,       -457,
         -423,       -319,       -173,        -35,         40,           0,
         -186,       -516,       -951,      -1417,      -1813,      -2033,
        -1988,      -1624,       -941,           0,        1088,       2173,
         3095,       3715,       3932,       3715,       3095,       2173,
          1088,           0,       -941,      -1624,      -1988,      -2033,
           -1813,        -1417,       -951,       -516,       -186,       0,
         40,       -35,        -173,          -319,         -423,        -457,
          -412,        -302,         -153,         0,         128,          210,
           239,           220,          170,         106,         47,         8,
           -7,         0,         23,          51,          75,           89,
           89,         77,          57,          35,           15,         0,
           -8,         -10,         -7,          -4,             0,
};
