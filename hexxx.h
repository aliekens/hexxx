#ifndef HEXXX__H
#define HEXXX__H

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
#include <math.h>

#include <iostream>
#include <thread>

extern "C" {
  #include "ledstring.h"
}

#include "color.h"
#include "buttons.h"
#include "coordinates.h"

#define LED_COUNT 400
#define HEXAGON_LED_COUNT 397

#define BUTTON_0_LEFT_GPIO 2
#define BUTTON_0_RIGHT_GPIO 3
#define BUTTON_1_LEFT_GPIO 4
#define BUTTON_1_RIGHT_GPIO 17
#define BUTTON_2_LEFT_GPIO 27
#define BUTTON_2_RIGHT_GPIO 22

extern int playerLEDs[ 3 ];

void setColor( int position, ws2811_led_t color );
ws2811_led_t getColor( int position );

void fill( ws2811_led_t color );
void fillhexagon( ws2811_led_t color );
void fillborder( ws2811_led_t color );

void button_thread();
void render_thread();
extern void logic_thread();

static void ctrl_c_handler(int signum);
static void setup_handlers(void);

int main(int argc, char *argv[]);

#endif