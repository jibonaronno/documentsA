
#include <stdio.h>
#include <stdint.h>

int16_t do_math(int16_t A,int16_t B,char operator)
{
    int32_t result = 0;
    if (operator == '+'){result = A+B;}
    if (operator == '-'){result = A-B;}
    if (operator == '*'){result = A*B;}
    if (operator == '/'){result = A/B;}
    int16_t i =  ((result >> 0) & 0xffff);
    return i;
}

int main (void)
{
  printf ("math test\n");
  printf ("2+2 = ");
  printf ( "%d", do_math(2,2,'+'));
  printf ("\n65535+1 = ");
  printf ( "%d", do_math(65535,1,'+'));
  printf ("\n-32768-1 = ");
  printf ( "%d", do_math(-32768,-1,'+'));
  printf ("\n-32768+1 = ");
  printf ( "%d", do_math(-32768,1,'+'));
  printf ("\n0-8 = ");
  printf ( "%d", do_math(0,-8,'+'));
  printf ("\n65535+50 = ");
  printf ( "%d", do_math(65535,50,'+'));
  printf ("\n32767+50 = ");
  printf ( "%d", do_math(32767,50,'+'));
  printf ("\n");
  return 0;
}




