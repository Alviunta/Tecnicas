#include <stdio.h>
#include <math.h>
#include <stdint.h>

double fx2fp(int x, int y);
int fp2fx(double X, int y);
int32_t roundoff(int64_t X);
int32_t truncation(int64_t X);

int n=15; //Definir la cantidad de decimales 
int main(int argc, char *argv[]) {
	
	double A = 0.3751, B = -0.5623,F,I,J,K;
	int32_t C,D,G,H;
	int64_t E;
	
	//Pasamos ambos numeros a punto fijo en Q21.10
	C = fp2fx(A,n);
	D = fp2fx(B,n);
	printf("Nro A en punto fijo, C = %d\n",C);
	printf("Nro B en punto fijo, D = %d\n",D);
	//Realizamos la multiplicacion en numero punto fijo
	E = C*D;
	//Realizamos la multiplicacion en numero punto flotante
	F = A*B;
	
	//Realizamos Roundoff
	G = roundoff(E);
	//Realizamos Truncacion
	H = truncation(E);
	I = fx2fp(G,n);
	J = fx2fp(H,n);
	printf("Nros en punto flotante: A = %f, B = %f \n",A,B);
	printf("Multiplicacion en punto fijo = %ld \n",E);
	printf("Multiplicacion en punto flotante= %f \n",F);
	printf("Truncamiento en punto fijo = %d\n",H);
	printf("Truncamiento en punto flotante= %f\n",J);
	printf("Redondeo en punto fijo= %d\n",G);
	printf("Redondeo en punto flotante= %f\n",I);

	return 0;
}

double fx2fp(int x, int y) //Punto fijo a punto flotante
{
	return (double)x / (1<<y);
}
int fp2fx(double X, int y) //Punto flotante a punto fijo
{
	return (int)(X * (1<<y));
}
int32_t roundoff(int64_t X)
{
	int32_t a;
	a = ( X + (1 << (n - 1) ));
	return truncation(a);
}

int32_t truncation(int64_t X)
{
	int32_t a;
	a = (int32_t) (X >> n);
	return a;
}
