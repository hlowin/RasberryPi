#include <stdio.h>

#include "blink.h"

int main()
{
  printf("Process start.\n");

  rpi_gpio gpio = {GPIO_BASE};
  int map_status;

  map_status = MapGPIO(&gpio);
  if(map_status) {
    printf("Failed to blink LED.\n");
    return map_status;
  }

  while(GpioIO(&gpio, (int)20, GPIO_IN, GPIO_OFF)) {
    (void)GpioIO(&gpio, (int)21, GPIO_OUT, GPIO_ON);
    usleep(500 * 1000);
    (void)GpioIO(&gpio, (int)21, GPIO_OUT, GPIO_OFF);
    usleep(500 * 1000);

    printf("gpio level = %d\n", (int)GpioIO(&gpio, (int)20, GPIO_IN, GPIO_OFF));
  }

  (void)GpioIO(&gpio, (int)21, GPIO_IN, GPIO_OFF);

  UnmapGPIO(&gpio);

  printf("Process end.\n");
  
  return 0;
}