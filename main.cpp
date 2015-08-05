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

int playerLEDs[ 3 ] = { 397, 398, 399 };

void setColor( int position, ws2811_led_t color ) {
  ledstring.channel[0].leds[position] = color;
}

ws2811_led_t getColor( int position ) {
  return ledstring.channel[0].leds[position];
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

#define PLAYERS 3
int position[PLAYERS];
bool humanplayer[PLAYERS];
bool alive[PLAYERS];
int direction[PLAYERS];
ws2811_led_t colors[PLAYERS];

void setup_tron(void) {
  colors[ 0 ] = color( 255, 255, 0 );
  colors[ 1 ] = color( 0, 255, 255 );
  colors[ 2 ] = color( 255, 0, 255 );
  int r = rand() % 2;
  position[ 0 ] = 335 + r;
  direction[ 0 ] = 2 - r;
  position[ 1 ] = 335 + 44 + r;
  direction[ 1 ] = ( 6 - r ) % 6;
  position[ 2 ] = 335 + 22 + r;
  direction[ 2 ] = 4 - r;
}

void darkenhexagon() {
  for( int i = 0; i < LED_COUNT - 3; i++ ) {
    setColor( i, darkenColor( getColor( i ) ) );
  }
}

void play_tron(void) {
  
  int sleep = 200000;
  
  while( ( alive[ 0 ] && alive[ 1 ] ) || ( alive[ 1 ] && alive[ 2 ] ) || ( alive[ 0 ] && alive[ 2 ] ) ) { // play as long as 2 players are alive
  
    // fade out player tails
    darkenhexagon();
  
    // update players
    for( int player = 0; player < PLAYERS; player++ ) {
      if( alive[ player ] ) {

        if( humanplayer[ player ] ) {

          if( button_rising[ player * 2 ] )
            direction[ player ] = ( direction[ player ] + 1 ) % 6;
          if (button_rising[ player * 2 + 1 ] )
            direction[ player ] = ( direction[ player ] + 5 ) % 6;

        } else {

          if( ( position[ player ] == neighbors[ position[ player ] ][ direction[ player ] ] ) )
            if( rand() % 2 )
              direction[ player ] = ( direction[ player ] + 1 ) % 6;
            else
              direction[ player ] = ( direction[ player ] + 5 ) % 6; // smart hack
          else if( rand() % 5 == 0 )
            if( rand() % 2 )
              direction[ player ] = ( direction[ player ] + 1 ) % 6;
            else
              direction[ player ] = ( direction[ player ] + 5 ) % 6; // smart hack

        }

        int next_position = neighbors[ position[ player ] ][ direction[ player ] ];
        if( getColor( next_position ) == 0 )
          position[ player ] = neighbors[ position[ player ] ][ direction[ player ] ];
        else {
          alive[ player ] = false;
          setColor( playerLEDs[ player ], 0 );
        }
        
      }
    
    }
    
    print_button_states();
    reset_button_states();
  
    // render players on new positions
    for( int player = 0; player < PLAYERS; player++ ) {
      if( alive[ player ] )
        setColor( position[ player ], colors[ player ] );
    }
    
    usleep( sleep );
    sleep *= 0.99;
  
  }
  
}

void invite_players() {
  
  reset_button_states();
  
  for( int player = 0; player < PLAYERS; player++ ) {
    humanplayer[ player ] = false;
    alive[ player ] = true;
    setColor( playerLEDs[ player ] , 0 );
  }

  int counter = 0;
  while( ( ( humanplayer[ 0 ] || humanplayer[ 1 ] || humanplayer[ 2 ] ) == false ) || ( counter < 100 ) ) { // wait a bit for players to join
    counter++;
    
    for( int player = 0; player < PLAYERS; player++ ) { // check whether player pressed buttons
      if( !humanplayer[ player ] ) // only those who haven't joined yet
        if( button_pushed[ player * 2 ] || button_pushed[ player * 2 + 1 ] ) {
          humanplayer[ player ] = true;
          setColor( playerLEDs[ player ], colors[ player ] );
          counter = 0;
        }
    }
    
    reset_button_states();
    
    darkenhexagon();
    if( counter > 100 )
      counter = 100;
    for( int i = 0; i < ( 100 - counter ) / 10 + 1; i++ ) {
      setColor( rand() % 397, color( 127 + ( rand() % 2 ) * 127 , 127 + ( rand() % 2 ) * 127 , 127 + ( rand() % 2 ) * 127 ) );
    }

    usleep( 20000 );
  }
  
  fillhexagon( 0 );
  for( int player = 0; player < PLAYERS; player++ )
    setColor( playerLEDs[ player ], colors[ player ] );
}

void announce_winner() {
  ws2811_led_t c = 0xffffff;
  for( int player = 0; player < 3; player++ ) {
    if( alive[ player ] ) {
      c = colors[ player ];
    }
  }
  for( int flash = 0; flash < 5; flash++ ) {
    for( int i = 0; i < 16; i++ ) {
      fillborder( color( i * getRed(c) / 16, i * getGreen(c) / 16, i * getBlue(c) / 16 ) );
      usleep(5000);
    }
    for( int i = 16; i > 0; i-- ) {
      fillborder( color( i * getRed(c) / 16, i * getGreen(c) / 16, i * getBlue(c) / 16 ) );
      usleep(5000);
    }
  }
  fillborder( 0 );
}

void logic_thread() {
  while (1) {
    setup_tron();
    invite_players();
    play_tron();
    announce_winner();
    usleep(200000);
  }
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

static void ctrl_c_handler(int signum) {
  ws2811_fini(&ledstring);
}

static void setup_handlers(void) {
  struct sigaction sa = {ctrl_c_handler};
  sigaction(SIGKILL, &sa, NULL);
}

int main(int argc, char *argv[]) {
  
  int seed = time(NULL);
  srand(seed);
  
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

