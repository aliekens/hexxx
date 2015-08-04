#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <signal.h>

#include "ledstring.h"

#include "board_info.h"
#include "clk.h"
#include "gpio.h"
#include "pwm.h"
#include "ws2811.h"

#define ARRAY_SIZE(stuff)                        (sizeof(stuff) / sizeof(stuff[0]))

#define WIDTH                                    40
#define HEIGHT                                   10
#define LED_COUNT                                400

ws2811_led_t matrix[WIDTH][HEIGHT];


void matrix_render(void)
{
    int x, y;

    for (x = 0; x < WIDTH; x++)
    {
        for (y = 0; y < HEIGHT; y++)
        {
            ledstring.channel[0].leds[(y * WIDTH) + x] = matrix[x][y];
        }
    }
}

void matrix_raise(void)
{
    int x, y;

    for (y = 0; y < (HEIGHT - 1); y++)
    {
        for (x = 0; x < WIDTH; x++)
        {
            matrix[x][y] = matrix[x][y + 1];
        }
    }
}

int dotspos[] = { 0, 1, 2, 3, 4, 5, 6, 7 };
ws2811_led_t dotcolors[] =
{
    0x200000,  // red
    0x202000,  // yellow
    0x002020,  // lightblue
    0x200010,  // pink
    0x002000,  // green
    0x100010,  // purple
    0x000020,  // blue
    0x201000,  // orange
};

void matrix_bottom(void)
{
    int i;
    static int x = 0;

    for (i = 0; i < WIDTH; i++)
    {
        matrix[i][HEIGHT - 1] = dotcolors[x & 7];
    }
    x++;
}

static void ctrl_c_handler(int signum)
{
  ws2811_fini(&ledstring);
}

static void setup_handlers(void)
{
  struct sigaction sa = {ctrl_c_handler};
  sigaction(SIGKILL, &sa, NULL);
}

int main(int argc, char *argv[])
{
  int ret = 0;

  if (board_info_init() < 0)
  {
      return -1;
  }

  setup_handlers();

  if (ws2811_init(&ledstring))
  {
      return -1;
  }
  if (0)
  {
      void *p = malloc(32000000);
      memset(p, 42, 32000000);
      free(p);
  }

  while (1)
  {
      matrix_raise();
      matrix_bottom();
      if (0)
      {
          void *p = malloc(64000000);
          memset(p, 42, 64000000);
          free(p);
      }
      matrix_render();

      if (ws2811_render(&ledstring))
      {
          ret = -1;
          break;
      }

      // 15 frames /sec
      usleep(500000);
  }

  ws2811_fini(&ledstring);

  return ret;
}

