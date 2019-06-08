//#define BLYNK_DEBUG
#define BLYNK_PRINT stdout
#ifdef RASPBERRY
  #include <BlynkApiWiringPi.h>
#else
  #include <BlynkApiLinux.h>
#endif
#include <BlynkSocket.h>
#include <BlynkOptionsParser.h>

static BlynkTransportSocket _blynkTransport;
BlynkSocket Blynk(_blynkTransport);

static const char *auth, *serv;
static uint16_t port;

#include <BlynkWidgets.h>

#include "token.h"

#include "blink.h"

BlynkTimer tmr;

static rpi_gpio static_gpio;

void ledset(rpi_gpio *gpio, int num)
{
  bool lednum[4];

  // printf("lednum = ");
  for (int i = 0; i < 4; ++i)
  {
    lednum[i] = (bool)(0x0001 & (num >> i));
  
    // printf("%d", lednum[i]);
  }
  // printf("\n");

  (void)GpioIO(gpio, (int)27, GPIO_OUT, (bool)lednum[0]);
  (void)GpioIO(gpio, (int)22, GPIO_OUT, (bool)lednum[1]);
  (void)GpioIO(gpio, (int)19, GPIO_OUT, (bool)lednum[2]);
  (void)GpioIO(gpio, (int)26, GPIO_OUT, (bool)lednum[3]);

  // printf("num = %d\n", num);
}

BLYNK_WRITE(V1)
{
  printf("Got a value: %s\n", param[0].asStr());

  ledset(&static_gpio, (int)param[0].asFloat());
}

int setup()
{
  Blynk.begin(auth, serv, port);
  tmr.setInterval(1000, [](){
    Blynk.virtualWrite(V0, BlynkMillis()/1000);
  });

  static_gpio = {GPIO_BASE};
  int map_status;

  map_status = MapGPIO(&static_gpio);
  if(map_status) {
    printf("Failed to blink LED.\n");
    return map_status;
  }

  return 0;
}

int main(int argc, char* argv[])
{
  argc = (int)2;
  argv[1] = TOKEN;

  parse_options(argc, argv, auth, serv, port);

  if(setup())
    return 1;

  while(GpioIO(&static_gpio, (int)2, GPIO_IN, GPIO_OFF)) {
    Blynk.run();
    tmr.run();
  }

  UnmapGPIO(&static_gpio);

  return 0;
}