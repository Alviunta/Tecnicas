// Version: 001
// Date:    2020/03/19
// Author:  Rodrigo Gonzalez <rodralez@frm.utn.edu.ar>

#include <stdio.h>
#include <float.h>
#include <math.h>
#include <signal.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdint.h>
#include <string.h>

// Compile usando el siguiente comando
// compile: gcc -Wall -O3 -std=c99 ex_05.c -o ex_05 -lm -march=corei7 -frounding-math -fsignaling-nans

#define _GNU_SOURCE 1
#define _ISOC99_SOURCE
#include <fenv.h>

void show_fe_exceptions(void)
{
	int raised;
	
    printf("Current exceptions raised: ");
    
    raised = fetestexcept (FE_DIVBYZERO);
    if(raised & FE_DIVBYZERO)     printf("FE_DIVBYZERO");
    
    raised = fetestexcept (FE_INEXACT);
    if(raised & FE_INEXACT)       printf("FE_INEXACT");
    
    raised = fetestexcept (FE_INVALID);
    if(raised & FE_INVALID)       printf("FE_INVALID");
    
    raised = fetestexcept (FE_OVERFLOW);
    if(raised & FE_OVERFLOW)      printf("FE_OVERFLOW");
    
    raised = fetestexcept (FE_UNDERFLOW);
    if(raised & FE_UNDERFLOW)     printf("FE_UNDERFLOW");
    
    raised = fetestexcept (FE_ALL_EXCEPT);
    if( (raised & FE_ALL_EXCEPT) == 0) printf("None exceptions");
    
    printf("\n");
}
     
int main(void)
{	

  show_fe_exceptions();
      
 /* printf("MATH_ERREXCEPT IS %s\n", math_errhandling & MATH_ERREXCEPT ? "set":"not set");*/

  printf("0.0/0.0 = %f\n",0.0/0.0);
  show_fe_exceptions();

  printf("1.0/0.0 = %f\n",1.0/0.0);
  show_fe_exceptions();
 
  printf("1.0/10.0 = %f\n",1.0/10.0);
  show_fe_exceptions();

  printf("sqrt(-1) = %f\n",sqrt(-1));
  show_fe_exceptions();

  printf("DBL_MAX*2.0 = %f\n",DBL_MAX*2.0);
  show_fe_exceptions();

  printf("nextafter(DBL_MIN/pow(2.0,52),0.0) = %lf\n", nextafter(DBL_MIN/pow(2.0,52),0.0));
  show_fe_exceptions();
	return 0;	
}
