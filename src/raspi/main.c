#include <stdio.h>

#include "blink.h"

void ledset(rpi_gpio *gpio, int num)
{
  bool lednum[4];

  printf("lednum = ");
  for (int i = 0; i < 4; ++i)
  {
    lednum[i] = (bool)(0x0001 & (num >> i));

    printf("%d", lednum[i]);
  }
  printf("\n");

  (void)GpioIO(gpio, (int)27, GPIO_OUT, (bool)lednum[0]);
  (void)GpioIO(gpio, (int)22, GPIO_OUT, (bool)lednum[1]);
  (void)GpioIO(gpio, (int)19, GPIO_OUT, (bool)lednum[2]);
  (void)GpioIO(gpio, (int)26, GPIO_OUT, (bool)lednum[3]);

  printf("num = %d\n", num);
}

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

  int count = 0;

  while(GpioIO(&gpio, (int)2, GPIO_IN, GPIO_OFF)) {
    // (void)GpioIO(&gpio, (int)21, GPIO_OUT, GPIO_ON);
    // usleep(500 * 1000);
    // (void)GpioIO(&gpio, (int)21, GPIO_OUT, GPIO_OFF);
    // usleep(500 * 1000);

    ledset(&gpio, count);

    printf("gpio level = %d\n", (int)GpioIO(&gpio, (int)2, GPIO_IN, GPIO_OFF));

    count++;
    if (count >= 16)
      count = 0;
    
    usleep(500 * 1000);
  }

  // (void)GpioIO(&gpio, (int)21, GPIO_IN, GPIO_OFF);

  UnmapGPIO(&gpio);

  printf("Process end.\n");
  
  return 0;
}