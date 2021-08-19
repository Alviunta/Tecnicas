/* ========================================================================
 * fir_filter.c: C functions for FIR filtering.
 *
 * Version: 001
 * Date:    2020/09/03
 * Author:  Rodrigo Gonzalez <rodralez@frm.utn.edu.ar>
 * URL:     https://github.com/rodralez/control
 *
 * ===================================================================== */

#include "./fir_filter.h"     // FIR functions prototypes
#include "./coeficientes.h"      // FIR coeficients

/* ========================================================================
 * fir_filter_float.c: FIR filtering function for floatin-point single 
 * precision.
 *
 * INPUT
 *      float *input: pointer to input vector.
 *      uint32_t N:   lenght of input vector.
 *
 *  OUTPUT
 *      float *output: pointer to output (filtered) vector.
 *
 * ===================================================================== */
int fp2fx(float x, int y);
void fir_filter_float(float *input, uint32_t N, float *output)
{
	uint32_t i, j;
	float acc;
	
    // Reset output vector
	for (i=0; i < N; i++)
	{
		output[i] = 0.0;
	}	
	
    // Convolution between input vector and FIR coefficients
    // Sweep input vector by a M-size window
	for (i=0; i < N-BL; i++)
	{
		acc = 0.0;
        
        // MAC operation between a M-size window and FIR coefficients
		for (j=0; j < BL; j++)
		{
			acc = acc + (input[j+i] * B[j]); 
		}
		
        // Save FIR filter output
		output[i+BL] = acc;
	}
}

/* ========================================================================
 * fir_filter_fixed.c: FIR filtering function for fixed-poing precision.
 *
 * INPUT
 *      float *input: pointer to input vector.
 *      uint32_t N:   lenght of input vector.
 *
 *  OUTPUT
 *      float *output: pointer to output (filtered) vector.
 *
 * ===================================================================== */
void fir_filter_fixed(float *input, uint32_t N, float *output)
{
	uint32_t i,j;
    int acum=0;
    
    //Reset output vector
	for (i=0; i < N; i++)
	{
		output[i] = 0.0;
	}	
    
    //Pasamos a punto fijo los valores de entrada
  /*  for (i=0; i < BL; i++)
	{
		inputI[i] = (int)(input[i]*(1<<15));
	}*/
     // Convolution between input vector and FIR coefficients
    // Sweep input vector by a M-size window
	for (i=0; i < N-BL; i++)
	{
		acum = 0;
        
        // MAC operation between a M-size window and FIR coefficients
		for (j=0; j < BL; j++)
		{
			acum = acum + (fp2fx(input[j+i],15) * B[j]); 
		}
		
        // Save FIR filter output
		output[i+BL] = acum;
	}
    
    //Volvemos a punto flotante
  /*  for (i=0; i < BL; i++)
	{
		output[i] = (float)outputI[i]/(1<<15);
	}*/
	
}
int fp2fx(float x, int y)
{
    int a;
    a=(int)(x*(1<<y));
    return a;
      
}