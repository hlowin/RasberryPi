#include "blink.h"

int MapMEM(rpi_mem *mem) {
  mem->memory_fd = open("/dev/gpiomem", O_RDWR|O_SYNC);

  if(mem->memory_fd < 0) {
    perror("Failed to open /dev/gpiomem, try change permission.");

    return 1;
  }

  mem->map = mmap(
    NULL,
    BLOCK_SIZE,
    PROT_READ|PROT_WRITE,
    MAP_SHARED,
    mem->memory_fd,
    mem->mem_base
  );

  if(mem->map == MAP_FAILED) {
    perror("mmap");
    return 1;
  }

  mem->addr = (volatile unsigned int *)mem->map;
  return 0;
}

void UnMapMEM(rpi_mem *mem) {
  munmap(mem->map, BLOCK_SIZE);
  close(mem->memory_fd);
}

static int outstate[2];
static int iostate[6];

// rpi_mem *gpio  : register mapped gpio
// int gpio_num   : GPIO number(0-26)
// bool io        : configure GPIO IN/OUT(GPIO_IN/GPIO_OUT)
// bool state     : If configure GPIO_OUT then set ON/OFF(GPIO_ON/GPIO_OFF)
bool GpioIO(rpi_mem *gpio, int gpio_num, bool io, bool state) {

  bool read = GPIO_OFF;

  if (io == GPIO_IN)
    iostate[gpio_num / 10] &= ~((0x00000001) << ((gpio_num % 10) * 3));
  else if (io == GPIO_OUT)
    iostate[gpio_num / 10] |= (0x00000001 << ((gpio_num % 10) * 3));

  *(gpio->addr + (gpio_num / 10)) = iostate[gpio_num / 10];


  if (state == GPIO_ON) {
    outstate[gpio_num / 32] |= (0x00000001 << (gpio_num % 32));
    *(gpio->addr + (7 + gpio_num / 32)) = outstate[gpio_num / 32];
  }
  else if (state == GPIO_OFF) {
    outstate[gpio_num / 32] &= ~(0x00000001 << (gpio_num % 32));
    *(gpio->addr + (10 + gpio_num / 32)) = ~outstate[gpio_num / 32];
  }

  read = (bool)((*(gpio->addr + (13 + gpio_num / 32)) >> (gpio_num % 32)) & 0x00000001 );

  return read;
}

// rpi_mem *pwm : register mapped pwm
void PWMout(rpi_mem *pwm) {

  // *(pwm->addr + 0) = 0x00000003;
  // *(pwm->addr + 4) = 0x20000000;
  // *(pwm->addr + 5) = 0x10000000;

}