#include <fcntl.h>
#include <stdio.h>
#include <sys/mman.h>
#include <unistd.h>

// #define bool _Bool

#define BLOCK_SIZE      4 * 1024
// #define PERIPHERAL_BASE 0x3F000000 // For Rasberry Pi 2
#define PERIPHERAL_BASE 0x20000000    // For Rasberry Pi Zero
#define GPIO_BASE       PERIPHERAL_BASE + 0x00200000
#define PWM_BASE        PERIPHERAL_BASE + 0x0020C000

#define GPIO_IN  (bool)1
#define GPIO_OUT (bool)0

#define GPIO_ON  (bool)1
#define GPIO_OFF (bool)0

typedef struct {
  unsigned long         mem_base;
  int                   memory_fd;
  void                  *map;
  volatile unsigned int *addr;
} rpi_mem;

int MapMEM(rpi_mem *mem);
void UnMapMEM(rpi_mem *mem);
bool GpioIO(rpi_mem *gpio, int gpio_num, bool io, bool state);
void PWMout(rpi_mem *pwm);