#include <math.h>
#include <stdio.h>
#include <stdint.h>
#include <limits.h>

float fx2fp(int x, int y);
int fp2fx(float x, int y);

int main()
{

  float a,b,c,d,e;

  a=2.4515;

  b=fx2fp(fp2fx(a,4),4);
  c=fx2fp(fp2fx(a,8),8);
  d=fx2fp(fp2fx(a,10),10);
  e=fx2fp(fp2fx(a,21),21);

  printf("En Q27.4, b= %f \n",b); 
  printf("En Q23.8, c= %f \n",c);
  printf("En Q21.10, d= %f \n",d);  
  printf("En Q10.21, e= %f \n",e); 
  return 0;
}
float fx2fp(int x, int y)
{
 float aux;
 aux=(float)x/(1<<y);
 return(aux);
}
int fp2fx(float x, int y)
{
  int aux;
  aux=(int)(x*(1<<y));
   printf("aux= %d \n",aux); 
  return(aux);
}


