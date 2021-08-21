#include <stdio.h>
#include <math.h>
#include <stdint.h>
float fx2fp(int x, int y);
int fp2fx(float X, int y);
int32_t truncation(int64_t X);
int32_t roundoff(int64_t X);
int n=10,i;
int main(int argc, char *argv[]) {
	
	
	float A[5] = {1.1, 2.2, 3.3, 4.4, 5.5 },F,H;
	float B[5] = {6.6, 7.7, 8.8, 9.9, 10.10};
	double g = 0,l = 0;
	
	
	int32_t X[5], Y[5],acum_32=0;
	int64_t acum_64=0,D[5], G;
	
	
	//////////////PUNTO 2/////////////

	for(i=0;i<5;i++)
	{
		X[i]= fp2fx(A[i],n);
		Y[i]= fp2fx(B[i],n);
	}
	
	
	//////////////PUNTO 3.1/////////////
	for(i=0; i<5; i++)
	{ 
		D[i] = truncation((int64_t)X[i]*Y[i]);
		acum_32 = acum_32 + (int32_t)D[i];
	}
	
	F = fx2fp(acum_32,n);
	printf("Truncando y sumando, F= %f\n",F);
	
	
	//////////////PUNTO 3.2/////////////
	for (i=0; i<5; i++)
	{
		acum_64 = acum_64 + ( (int64_t) (X[i] * Y[i]) );
	}
	G = truncation(acum_64);
	H = fx2fp(G,n);
	printf("Sumando y truncando, H= %f\n",H);
	
	//Numero originales en punto double 

        double a[5] = {1.1, 2.2, 3.3, 4.4, 5.5 };
	double b[5] = {6.6, 7.7, 8.8, 9.9, 10.10};
	for(i=0; i<5; i++)
	{
		l = l + (a[i]*b[i]);
	}
	printf("Original = %f\n",l);
	return 0;
}

float fx2fp(int x, int y) //Punto fijo a punto flotante
{
	float a;
	a = (float)x / (1<<y);
	return a;
}
int fp2fx(float X, int y) //Punto flotante a punto fijo
{
	int a;
	a = (int)(X * (1<<y));
	return a;
}
int32_t truncation(int64_t X)
{
	int32_t a;
	a = (int32_t) (X >> n);
	return a;
}
int32_t roundoff(int64_t X)
{
	int32_t a;
	a = ( X + (1 << (n - 1) )	 );
	return truncation(a);
}
