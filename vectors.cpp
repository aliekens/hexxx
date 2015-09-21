#include "hexxx.h"
#include "color.h"

#include "coordinate.h"
#include "vector.h"
#include "circle.h"
#include "line.h"

#include "buffer.h"

// draw circles and lines in the unit coordinate system

float random_float() {
  return static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
}

void logic_thread() {
  
  int counter = 0;
  Line borders[ 6 ];
  for( int i = 0; i < 6; i++ ) {
    borders[ i ] = Line( 
      Coordinate( cos( i * TAU / 6 ), sin( i * TAU / 6 ) ), 
      Vector( ( i + 2 ) * TAU / 6, 1 ) 
    );
  }
  
  Buffer* buffer = new Buffer();

  while (1) {
    
    buffer->fill( 0 );
    
    counter += 1;
    
    Line l( Coordinate( sin( counter / 97.0 ) / 2, cos( counter / 73.0 ) / 2 ), Vector( counter / 100.0, 1 ) );
    l.render( buffer, COLOR_BLUE );
    
    Circle c2( Coordinate( sin( counter / 97.0 ) / 2, cos( counter / 73.0 ) / 2 ), 0.3 );
    c2.render( buffer, COLOR_GREEN );
    
    for( int i = 0; i < 6; i++ ) {
      borders[ i ].render( buffer, COLOR_YELLOW );
    }
    
    buffer->render();

    usleep(10000); // 100 per second
    
  }
  
}
