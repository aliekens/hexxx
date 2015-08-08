#include "hexxx.h"
#include "font.h"

ws2811_led_t randColor() {
  ws2811_led_t c = 0;
  while( c == 0 )
    c = color( ( rand() % 2 ) * 255, ( rand() % 2 ) * 255, ( rand() % 2 ) * 255 );
  return c;
}

// a "logic_thread" function always has to be defined in a HEXXX application
void logic_thread() {
  
  while (1) {
    
    int position = 0;
    for( int i = 0; i < 3; i++ )
      position = neighbor( position, 2 );
    for( int i = 0; i < 5; i++ )
      position = neighbor( position, 3 );
    
    position = printCharacter( position, 'H', randColor() );
    position = printCharacter( position, 'E', randColor() );

    position = 0;
    for( int i = 0; i < 4; i++ )
      position = neighbor( position, 4 );
    for( int i = 0; i < 7; i++ )
      position = neighbor( position, 3 );
    position = printCharacter( position, 'X', randColor() );
    position = neighbor( position, 3 );
    position = printCharacter( position, 'X', randColor() );
    position = neighbor( position, 3);
    position = printCharacter( position, 'X', randColor() );

    for( int i = 0; i < 6; i++ )
      position = neighbor( position, 4 );
    for( int i = 0; i < 9; i++ )
      position = neighbor( position, 3 );
    position = printCharacter( position, 'x', randColor() );

    usleep(100000); // 100 per second
    
  }
  
}
