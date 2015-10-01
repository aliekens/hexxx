#include "hexxx.h"
#include "buffer.h"
#include "font.h"

ws2811_led_t randColor() {
  return color( rand() % 255, rand() % 255, rand() % 255 );
}

// a "logic_thread" function always has to be defined in a HEXXX application
void logic_thread() {
  
  Buffer* buffer = new Buffer();
  Font font( "util/fonts/font3by5.txt" );

  // bouncing scrolly, of course
  int counter = 0;
  ws2811_led_t c;
  while (1) {

    buffer->fill(0);

    if( rand() % 20 == 0 ) c = randColor();
    
    int x = 10 * sin( counter / 61.0 ) - 12;
    int y = 10 * cos( counter / 97.0 ) - 2;

    font.printString( buffer, x, y, "HEXXX", c );
    
    buffer->render();
        
    counter += 1;
    
    usleep(10000); // 100 per second
    
  }
  
}
