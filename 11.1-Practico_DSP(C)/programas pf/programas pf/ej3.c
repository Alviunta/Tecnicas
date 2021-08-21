#include <stdio.h>
#include <float.h>
#include <math.h>
#include <signal.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdint.h>
#include <string.h>

int main()
{
  float f=-INFINITY;
  uint32_t fn; memcpy(&fn, &f, sizeof f);
  printf("INFINITY: %f %" PRIx32 "\n", f,fn);
  
  float a =NAN;
  uint32_t an; memcpy(&an, &a, sizeof a);
  printf("NaN: %f %" PRIx32 "\n", a,an);

  return 0;
}
