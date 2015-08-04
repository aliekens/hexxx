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

#include "ws2811/ws2811.h"

#ifndef LEDSTRING__H
#define LEDSTRING__H

#define TARGET_FREQ                              WS2811_TARGET_FREQ
#define GPIO_PIN                                 18
#define DMA                                      5
#define LED_COUNT                                400

extern ws2811_t ledstring;

#endif
