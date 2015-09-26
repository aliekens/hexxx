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

#include "color.h"
#include "buttons.h"
#include "coordinates.h"
#include "hexxx.h"

#define LED_COUNT                                400
ws2811_led_t simulated_ledstring[ LED_COUNT ];

#define BUTTON_0_LEFT_GPIO 2
#define BUTTON_0_RIGHT_GPIO 3
#define BUTTON_1_LEFT_GPIO 4
#define BUTTON_1_RIGHT_GPIO 17
#define BUTTON_2_LEFT_GPIO 27
#define BUTTON_2_RIGHT_GPIO 22

int playerLEDs[ 3 ] = { 397, 398, 399 };

void setColor( int position, ws2811_led_t color ) {
  simulated_ledstring[position] = color;
}

ws2811_led_t getColor( int position ) {
  return simulated_ledstring[position];
}

void fill( ws2811_led_t color ) {
  for( int i = 0; i < LED_COUNT; i++ ) {
    setColor( i, color );
  }
}

void fillhexagon( ws2811_led_t color ) {
  for( int i = 0; i < LED_COUNT - 3; i++ ) {
    setColor( i, color );
  }
}

void fillborder( ws2811_led_t color ) {
  for( int i = LED_COUNT - 69; i < LED_COUNT - 3; i++ ) {
    setColor( i, color );
  }
}

void button_thread() {
  
  while (1) {

    /*
    set_button_state( 0, gpioRead( BUTTON_0_LEFT_GPIO ) );
    set_button_state( 1, gpioRead( BUTTON_0_RIGHT_GPIO ) );
    set_button_state( 2, gpioRead( BUTTON_1_LEFT_GPIO ) );
    set_button_state( 3, gpioRead( BUTTON_1_RIGHT_GPIO ) );
    set_button_state( 4, gpioRead( BUTTON_2_LEFT_GPIO ) );
    set_button_state( 5, gpioRead( BUTTON_2_RIGHT_GPIO ) );
    */
    
    usleep(10000); // 100 samples per second as a simple solution to overcome debouncing
    
  }
}

void render_thread() {
  
  while (1) {
//      ws2811_render(&ledstring);
      
      usleep(15000); // slow down to about 50FPS on a raspberry pi 2
  }
}

int main(int argc, char *argv[]) {
  
  int seed = time(NULL);
  srand(seed);
  
  int ret = 0;

  std::thread t1( button_thread );
  std::thread t2( render_thread );
  std::thread t3( logic_thread );
  
  t1.join();
  t2.join();
  t3.join();

//  ws2811_fini(&ledstring);

  return ret;
  
}

