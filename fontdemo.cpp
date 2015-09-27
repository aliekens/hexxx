#include "hexxx.h"
#include "font.h"

ws2811_led_t randColor() {
  return applyGammaCorrection( color( rand() % 255, rand() % 255, rand() % 255 ) );
}

// allows for performing initialization
void logic_init() {}

// a "logic_thread" function always has to be defined in a HEXXX application
void logic_thread() {

  // bouncing scrolly, of course
  int x = 0;
  int direction = 1;
  int counter = 0;
  ws2811_led_t c;
  while (1) {

//    fill(0);
    darkenhexagon();
    if( rand() % 20 == 0 ) c = randColor();
    
    x += direction;
    if( x == 5 )
      direction = -1;
    if( x == -40 )
      direction = 1;

    int y = 10 * sin( counter / 5.0 ) - 2;

    printString( x, y, "HEX", c );
    printString( x + 7 * 3 - 1, y, "X", c );
    printString( x + 7 * 4 - 2, y, "X", c );
        
    counter += 1;
    
    usleep(100000); // 100 per second
    
  }
  
}
