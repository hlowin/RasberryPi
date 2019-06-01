#include <stdio.h>

#include "blink.h"

int main()
{
  printf("Hello, World!\n");

  rpi_gpio gpio = {GPIO_BASE};
  int map_status;

  map_status = MapGPIO(&gpio);
  if(map_status) {
    printf("Failed to blink LED.\n");
    return map_status;
  }

  BlinkLED(&gpio);
  UnmapGPIO(&gpio);
  return 0;
}