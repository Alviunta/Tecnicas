// Versión: 002
// Fecha: 20/08/2020
// Autor: Rodrigo Gonzalez <rodralez@frm.utn.edu.ar>

#ifdef LINUX
/* _GNU_SOURCE es necesario (supuestamente) para el feenableexcepto
	* prototipo a definir en fenv.h en sistemas GNU.
	* Es de suponer que no hará daño a otros sistemas.
	*/
#ifndef _GNU_SOURCE
#define _GNU_SOURCE

	
#endif // LINUX
	
#include <fenv.h>
#include <stdio.h>
#include <float.h>
#include <math.h>
#include <signal.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdint.h>
#include <string.h>
	
	// compilar: gcc -Wall -O3 ej6.c -o ej6 -lm -DLINUX
	
	// ~ jmp_buf fpe;
	
	void fpe_handler (int sig) {
	
	// ~ longjmp (fpe, 1);
	
	salir (EXIT_FAILURE);
}

int main ()
{	
	feclearexcept (FE_ALL_EXCEPT);
	
	// ~ señal (SIGFPE, fpe_handler);
	// ~ señal (SIGFPE, SIG_DFL);
	
	// ~ feenableexcept (FE_INVALID | 
	// ~ FE_INEXACT | 
	// ~ FE_DIVBYZERO | 
	// ~ FE_OVERFLOW | 
	// ~ FE_UNDERFLOW);
	
	/ * Generar temporalmente otras excepciones. * /
		
		printf ("Forzar excepción FE_INEXACT. \ n");
	feclearexcept (FE_ALL_EXCEPT);
	feraiseexcept (FE_INEXACT);
	
	printf ("Forzar excepción FE_INVALID. \ n");    
	feclearexcept (FE_ALL_EXCEPT);
	feraiseexcept (FE_INVALID);
	
	printf ("Forzar excepción FE_DIVBYZERO. \ n");
	feclearexcept (FE_ALL_EXCEPT);    
	feraiseexcept (FE_DIVBYZERO);
	
	printf ("Forzar excepción FE_OVERFLOW. \ n");
	feclearexcept (FE_ALL_EXCEPT);
	feraiseexcept (FE_OVERFLOW);
	
	printf ("Forzar excepción FE_UNDERFLOW. \ n");
	feclearexcept (FE_ALL_EXCEPT);
	feraiseexcept (FE_UNDERFLOW);
	
	return 0;
	
}
