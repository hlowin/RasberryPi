#include <fcntl.h>
#include <stdio.h>
#include <sys/mman.h>
#include <unistd.h>

#define bool _Bool

#define BLOCK_SIZE      4 * 1024
// #define PERIPHERAL_BASE 0x3F000000 // For Rasberry Pi 2
#define PERIPHERAL_BASE 0x20000000    // For Rasberry Pi Zero
#define GPIO_BASE       PERIPHERAL_BASE + 0x00200000

#define GPIO_IN  1
#define GPIO_OUT 0

#define GPIO_ON  1
#define GPIO_OFF 0

typedef struct {
  unsigned long         gpio_base;
  int                   memory_fd;
  void                  *map;
  volatile unsigned int *addr;
} rpi_gpio;

int MapGPIO(rpi_gpio *gpio);
void UnmapGPIO(rpi_gpio *gpio);
void BlinkLED(rpi_gpio *gpio);