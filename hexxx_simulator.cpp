// SIMULATOR SPECIFIC INCLUDES

#include "SDL.h"
#include "SDL2_gfxPrimitives.h"
#include "coordinates.h"

// OTHER INCLUDES

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
#define HEXAGON_LED_COUNT                        397
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

uint32_t SDLcolor(uint8_t r, uint8_t g, uint8_t b, uint8_t a ) {
  return ((uint32_t)r << 24) | ((uint32_t)g <<  16) | ((uint32_t)b <<  8) | a;
}

int main(int argc, char *argv[]) {
  
  int seed = time(NULL);
  srand(seed);
  
  int ret = 0;

  // only the application runs in a thread, all others don't allow SDL in thread
  std::thread t1( logic_thread );

  /* Init SDL */
  if( SDL_Init( SDL_INIT_TIMER | SDL_INIT_VIDEO ) < 0 ) {
    std::cerr << "Couldn't initialize SDL: " << SDL_GetError() << std::endl;
    exit( 1 );
  }
  atexit( SDL_Quit );

  /* Initialize the display */
  SDL_Window *sdlWindow = SDL_CreateWindow(
    "HEXXX simulator", // SDL2
    SDL_WINDOWPOS_CENTERED,
    SDL_WINDOWPOS_CENTERED,
    400, 400,
    SDL_WINDOW_OPENGL 
  );
  SDL_Renderer *sdlRenderer = SDL_CreateRenderer(sdlWindow, -1, 0);

  int button_0_left_state = 1;
  int button_0_right_state = 1;
  int button_1_left_state = 1;
  int button_1_right_state = 1;
  int button_2_left_state = 1;
  int button_2_right_state = 1;

  while( 1 ) {

    // render HEXXX on screen
    SDL_SetRenderDrawColor(sdlRenderer, 64, 64, 64, 255);
    SDL_RenderClear(sdlRenderer);
    for( int i = 0; i < HEXAGON_LED_COUNT; i++ ) {
      // we'll simulate gamma error of ws2811 LEDs by applying "gamma error" functions which are inverted of gamma correction
      int red = applyGammaError( getRed( simulated_ledstring[ i ] ) );
      int green = applyGammaError( getGreen( simulated_ledstring[ i ] ) );
      int blue = applyGammaError( getBlue( simulated_ledstring[ i ] ) );
			filledCircleRGBA( 
        sdlRenderer, 
        200 + 180 * led2unitx(i), 
        200 - 180 * led2unity(i),
        5, // radius
        red, green, blue, 255 
      );
		}
		SDL_RenderPresent(sdlRenderer);
		
    // check for button presses
    SDL_Event event;
    while( SDL_PollEvent( &event ) ) {
      switch( event.type ) {
        case SDL_QUIT:
        	exit(0);
        break;
      }
    }
    
    const Uint8 *keystate = SDL_GetKeyboardState(NULL);

    set_button_state( 0, !keystate[ SDL_SCANCODE_V ] );
    set_button_state( 1, !keystate[ SDL_SCANCODE_B ] );
    set_button_state( 2, !keystate[ SDL_SCANCODE_O ] );
    set_button_state( 3, !keystate[ SDL_SCANCODE_P ] );
    set_button_state( 4, !keystate[ SDL_SCANCODE_Q ] );
    set_button_state( 5, !keystate[ SDL_SCANCODE_W ] );
    
    if( keystate[ SDL_SCANCODE_ESCAPE ] )
      exit( 0 );

    usleep(15000); // slow down to about 50FPS on a raspberry pi 2

  }

  return ret;
  
}

