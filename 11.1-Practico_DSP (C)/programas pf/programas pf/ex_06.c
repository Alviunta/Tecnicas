// Version: 001
// Date:    2020/03/19
// Author:  Rodrigo Gonzalez <rodralez@frm.utn.edu.ar>
#include <stdio.h>
#include <float.h>
#include <math.h>
#include <signal.h>
#include <stdlib.h>

#define _GNU_SOURCE 1
#define _ISOC99_SOURCE
#include <fenv.h>

// Compile usando el siguiente comando
// compile: gcc -Wall -O3 -std=c99 ex_06.c -o ex_06 -lm -march=corei7 -frounding-math -fsignaling-nans
    
void fpe_handler(int sig){
		
  exit(EXIT_FAILURE);
}

int main(void)
{	
	
  feclearexcept (FE_ALL_EXCEPT);
	
    signal(SIGFPE, fpe_handler);
  
    feenableexcept(FE_INVALID   | 
		    FE_INEXACT   | 
                    FE_DIVBYZERO | 
                    FE_OVERFLOW  | 
                    FE_UNDERFLOW);
	                 
		
  /* Temporarily raise other exceptions. */
  feclearexcept(FE_ALL_EXCEPT);
  feraiseexcept(FE_INEXACT);
  printf ("Forzar excepción FE_INVALID. \ n"); 
  feclearexcept(FE_ALL_EXCEPT);
  feraiseexcept(FE_INVALID);

  feclearexcept(FE_ALL_EXCEPT);    
  feraiseexcept(FE_DIVBYZERO);

  feclearexcept(FE_ALL_EXCEPT);
  feraiseexcept(FE_OVERFLOW);

  feclearexcept(FE_ALL_EXCEPT);
  feraiseexcept(FE_UNDERFLOW);

  return 0;
	
}
