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
  
  #include "ws2811/board_info.h"
  #include "ws2811/ws2811.h"
  
  #include "gpio/gpio.h"
}

#include "color.h"
#include "buttons.h"
#include "coordinates.h"

#define LED_COUNT                                400

#define BUTTON_0_LEFT_GPIO 2
#define BUTTON_0_RIGHT_GPIO 3
#define BUTTON_1_LEFT_GPIO 4
#define BUTTON_1_RIGHT_GPIO 17
#define BUTTON_2_LEFT_GPIO 27
#define BUTTON_2_RIGHT_GPIO 22

void setColor( int position, ws2811_led_t color ) {
  ledstring.channel[0].leds[position] = color;
}

ws2811_led_t getColor( int position ) {
  return ledstring.channel[0].leds[position];
}

#define SNAKES 32
int positions[SNAKES];
int directions[SNAKES];
ws2811_led_t colors[SNAKES];

void setup_snake(void) {
  for( int i = 0; i < SNAKES; i++ ) {
    positions[ i ] = rand() % LED_COUNT;
    directions[ i ] = rand() % 6;
    colors[ i ] = randomColor();
  }
}

void render_snake(void) {
  for( int i = 0; i < LED_COUNT; i++ ) {
    setColor( i, darkenColor( getColor( i ) ) );
  }
  for( int snake = 0; snake < SNAKES; snake++ ) {
    setColor( positions[ snake ], colors[ snake ] );
    positions[ snake ] = neighbors[ positions[ snake ] ][ directions[ snake ] ];
    if( ( rand() % 10 == 0 ) || ( positions[ snake ] == neighbors[ positions[ snake ] ][ directions[ snake ] ] ) ){
      if( rand() % 2 )
        directions[ snake ] = ( directions[ snake ] + 1 ) % 6;
      else
        directions[ snake ] = ( directions[ snake ] + 5 ) % 6; // smart hack
    }
  }
}

static void ctrl_c_handler(int signum) {
  ws2811_fini(&ledstring);
}

static void setup_handlers(void) {
  struct sigaction sa = {ctrl_c_handler};
  sigaction(SIGKILL, &sa, NULL);
}

void button_thread() {

  while (1) {

    set_button_state( 0, gpioRead( BUTTON_0_LEFT_GPIO ) );
    set_button_state( 1, gpioRead( BUTTON_0_RIGHT_GPIO ) );
    set_button_state( 2, gpioRead( BUTTON_1_LEFT_GPIO ) );
    set_button_state( 3, gpioRead( BUTTON_1_RIGHT_GPIO ) );
    set_button_state( 4, gpioRead( BUTTON_2_LEFT_GPIO ) );
    set_button_state( 5, gpioRead( BUTTON_2_RIGHT_GPIO ) );
    
    usleep(10000); // 100 samples per second as a simple solution to overcome debouncing
    
  }
}

#define SHOW_FPS
void render_thread() {
  
  #ifdef SHOW_FPS
    auto start = std::chrono::high_resolution_clock::now();
    int framecount = 0;
  #endif
    
  while (1) {
      ws2811_render(&ledstring);
      
      #ifdef SHOW_FPS
        framecount++;
        auto elapsed = std::chrono::high_resolution_clock::now() - start;
        long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
        if( microseconds > 1000000 ) {
          std::cout << framecount << "FPS" << std::endl;
          start = std::chrono::high_resolution_clock::now();
          framecount = 0;
        }
      #endif
      usleep(36000); // slow down to about 24FPS on a raspberry pi 2
  }
}

void logic_thread() {
  setup_snake();
  while (1) {
      render_snake();
      print_button_states();
      reset_button_states();
      usleep(100000);
  }
}

int main(int argc, char *argv[]) {
  
  int ret = 0;

  if (board_info_init() < 0) return -1;

  setup_handlers();

  if( ws2811_init( &ledstring ) ) return -1;
  
  if( gpioInitialise() < 0 ) return -1;
  
  gpioSetMode( BUTTON_0_LEFT_GPIO, PI_INPUT );
  gpioSetMode( BUTTON_0_RIGHT_GPIO, PI_INPUT );
  gpioSetMode( BUTTON_1_LEFT_GPIO, PI_INPUT );
  gpioSetMode( BUTTON_1_RIGHT_GPIO, PI_INPUT );
  gpioSetMode( BUTTON_2_LEFT_GPIO, PI_INPUT );
  gpioSetMode( BUTTON_2_RIGHT_GPIO, PI_INPUT );

  std::thread t1(button_thread);
  std::thread t2(render_thread);
  std::thread t3(logic_thread);
  
  t1.join();
  t2.join();
  t3.join();
  
  ws2811_fini(&ledstring);

  return ret;
  
}

