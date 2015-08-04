extern "C" {
  #include "gpio.h"
}

int main()
{
   int i;

   if (gpioInitialise() < 0) return 1;

   for (i=0; i<54; i++)
   {
      printf("gpio=%d tick=%u mode=%d level=%d\n",
         i, gpioTick(), gpioGetMode(i), gpioRead(i));
   }
}

