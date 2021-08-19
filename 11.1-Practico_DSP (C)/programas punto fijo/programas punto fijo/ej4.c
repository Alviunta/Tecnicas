#include <math.h>
#include <stdio.h>
#include <stdint.h>
#include <limits.h>


int32_t saturation(int32_t a,int32_t b)
{
   int32_t aux=0;

   aux=a+b;
   if(a>0&&b>0)
   {
	if(aux<0)
	{
	   aux=INT_MAX;
		}
	}
   if(a<0&&b<0)
   {
	if(aux>0)
	{
	   aux=INT_MIN;
		}
	}
  return(aux);
}

int main()
{
  int32_t a,b,c;
   
//////Caso 1

   a=21;
   b=9;
   c = saturation(a,b);
   printf("MAX= %d \n",INT_MAX);
   printf("MIN= %d \n",INT_MIN); 
   printf("Caso 1:\na= %d y b= %d\n",a,b);
   printf("c= %d \n",c); 

//////Caso 2

   a=2147483640;
   b=9;
   c = saturation(a,b);
   printf("\nCaso 2:\na= %d y b= %d\n",a,b);
   printf("c= %d \n",c); 

//////Caso 3

   a=29;
   b=-9;
   c = saturation(a,b);
   printf("\nCaso 3:\na= %d y b= %d\n",a,b);
   printf("c= %d \n",c); 

//////Caso 4

   a=-2147483640;
   b=-18;
   c = saturation(a,b);
   printf("\nCaso 4:\na= %d y b= %d\n",a,b);
   printf("c= %d \n",c); 

}


