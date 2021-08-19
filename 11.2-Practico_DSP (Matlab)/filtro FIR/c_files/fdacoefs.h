/*
 * Filter Coefficients (C Source) generated by the Filter Design and Analysis Tool
 * Generated by MATLAB(R) 9.6 and DSP System Toolbox 9.8.
 * Generated on: 10-Sep-2020 11:58:34
 */

/*
 * Discrete-Time FIR Filter (real)
 * -------------------------------
 * Filter Structure  : Direct-Form FIR
 * Filter Length     : 101
 * Stable            : Yes
 * Linear Phase      : Yes (Type 1)
 * Arithmetic        : fixed
 * Numerator         : s16,17 -> [-2.500000e-01 2.500000e-01)
 * Input             : s16,15 -> [-1 1)
 * Filter Internals  : Full Precision
 *   Output          : s34,32 -> [-2 2)  (auto determined)
 *   Product         : s31,32 -> [-2.500000e-01 2.500000e-01)  (auto determined)
 *   Accumulator     : s34,32 -> [-2 2)  (auto determined)
 *   Round Mode      : No rounding
 *   Overflow Mode   : No overflow
 */

/* General type conversion for MATLAB generated C-code  */
#include "tmwtypes.h"
/* 
 * Expected path to tmwtypes.h 
 * C:\Program Files\Polyspace\R2019a\extern\include\tmwtypes.h 
 */
/*
 * Warning - Filter coefficients were truncated to fit specified data type.  
 *   The resulting response may not match generated theoretical response.
 *   Use the Filter Design & Analysis Tool to design accurate
 *   int16 filter coefficients.
 */
const int BL = 101;
const int B[101] = {
        0,    -11,    -24,    -36,    -43,    -40,    -26,     -4,     21,
       37,     34,      5,    -53,   -133,   -223,   -301,   -349,   -350,
     -300,   -210,   -105,    -20,      6,    -57,   -217,   -461,   -746,
    -1012,  -1193,  -1233,  -1106,   -829,   -461,   -100,    142,    161,
     -107,   -660,  -1422,  -2245,  -2929,  -3267,  -3079,  -2261,   -816,
     1136,   3369,   5584,   7462,   8720,   9162,   8720,   7462,   5584,
     3369,   1136,   -816,  -2261,  -3079,  -3267,  -2929,  -2245,  -1422,
     -660,   -107,    161,    142,   -100,   -461,   -829,  -1106,  -1233,
    -1193,  -1012,   -746,   -461,   -217,    -57,      6,    -20,   -105,
     -210,   -300,   -350,   -349,   -301,   -223,   -133,    -53,      5,
       34,     37,     21,     -4,    -26,    -40,    -43,    -36,    -24,
      -11,      0
};
