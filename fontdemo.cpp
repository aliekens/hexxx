#include "hexxx.h"
#include "font.h"

ws2811_led_t randColor() {
  return color( ( rand() % 2 ) * 255, ( rand() % 2 ) * 255, ( rand() % 2 ) * 255 );
}

// a "logic_thread" function always has to be defined in a HEXXX application
void logic_thread() {
  
  while (1) {
    
    int position = 0;
    for( int i = 0; i < 3; i++ )
      position = neighbors[ position ][ 2 ];
    for( int i = 0; i < 5; i++ )
      position = neighbors[ position ][ 3 ];
    
    position = printCharacter( position, 'H', randColor() );
    position = printCharacter( position, 'E', randColor() );

    position = 0;
    for( int i = 0; i < 4; i++ )
      position = neighbors[ position ][ 4 ];
    for( int i = 0; i < 7; i++ )
      position = neighbors[ position ][ 3 ];
    position = printCharacter( position, 'X', randColor() );
    position = neighbors[ position ][ 3 ];
    position = printCharacter( position, 'X', randColor() );
    position = neighbors[ position ][ 3 ];
    position = printCharacter( position, 'X', randColor() );

    usleep(100000); // 100 per second
    
  }
  
}
