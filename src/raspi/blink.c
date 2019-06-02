#include "blink.h"

int MapGPIO(rpi_gpio *gpio) {
  // gpio->memory_fd = open("/dev/mem", O_RDWR|O_SYNC);
  gpio->memory_fd = open("/dev/gpiomem", O_RDWR|O_SYNC);

  if(gpio->memory_fd < 0) {
    // perror("Failed to open /dev/mem, try change permission.");
    perror("Failed to open /dev/gpiomem, try change permission.");

    return 1;
  }

  gpio->map = mmap(
    NULL,
    BLOCK_SIZE,
    PROT_READ|PROT_WRITE,
    MAP_SHARED,
    gpio->memory_fd,
    gpio->gpio_base
  );

  if(gpio->map == MAP_FAILED) {
    perror("mmap");
    return 1;
  }

  gpio->addr = (volatile unsigned int *)gpio->map;
  return 0;
}

void UnmapGPIO(rpi_gpio *gpio) {
  munmap(gpio->map, BLOCK_SIZE);
  close(gpio->memory_fd);
}

void BlinkLED(rpi_gpio *gpio) {
  int n = 5;

  while(n -= 1) {
    GpioIO(&gpio, (int)21, GPIO_OUT, GPIO_ON);
    usleep(500 * 1000);
    GpioIO(&gpio, (int)21, GPIO_OUT, GPIO_OFF);
    usleep(500 * 1000);
  }

  GpioIO(&gpio, (int)21, GPIO_IN, GPIO_OFF);

#if 0
  *(gpio->addr + 2)  = 0x00000200;

  while(n -= 1) {
    *(gpio->addr + 7)  = 0x00800000;
    usleep(500 * 1000);
    *(gpio->addr + 10) = 0x00800000;
    usleep(500 * 1000);
  }

  *(gpio->addr + 2)  = 0x00000000;
#endif
}

void GpioIO(rpi_gpio *gpio, int gpio_num, bool io, bool state) {
  if (io == GPIO_IN)
    *(gpio->addr + (gpio_num / 10)) = 0x00000000 << ((gpio_num % 10) * 3);
  if (io == GPIO_OUT)
    *(gpio->addr + (gpio_num / 10)) = 0x00000001 << ((gpio_num % 10) * 3);

  if (io == GPIO_OUT) {
    if (state == GPIO_ON)
      *(gpio->addr + (7 + gpio_num / 32)) = 0x00000001 << (gpio_num % 32);
    if (state == GPIO_OFF)
      *(gpio->addr + (10 + gpio_num / 32)) = 0x00000001 << (gpio_num % 32);
  }
}