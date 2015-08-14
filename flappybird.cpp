#include "hexxx.h"

#include <iostream>

int holes[ 3 ] = { 1, 4, 7 };

double position[ 6 ] = { 0, 0, 0, 0, 0, 0 };
double inertia[ 6 ] = { 0, 0, 0, 0, 0, 0 };

int alivecounter[ 6 ];

int colors[ 6 ][ 3 ] = 
{
  { 1, 0, 0 },
  { 1, 1, 0 },
  { 0, 1, 0 },
  { 0, 1, 1 },
  { 0, 0, 1 },
  { 1, 0, 1 }
};

void antialiased_polar_pixel( int ring, double angle, int red, int green, int blue ) {
  double doubleled = angle * leds_in_polar_ring( ring ) / TAU;
  int intled = (int)doubleled;
  double realpart = doubleled - intled;
  setColor( polar2led( ring, intled + 1 ), applyGammaCorrection( color( realpart * red, realpart * green, realpart * blue ) ) );
  setColor( polar2led( ring, intled ), applyGammaCorrection( color( ( 1 - realpart ) * red, ( 1 - realpart ) * green, ( 1 - realpart ) * blue ) ) );
}

void logic_thread() {
  
  ws2811_led_t c = COLOR_WHITE;
  double angle = 0;
  
  while (1) {
    
    fill( COLOR_BLACK );
    
    for( int wall = 0; wall < 3; wall++ ) {
    
      for( int ring = 0; ring < 12; ring++ ) {
        
      if( ( ring < holes[ wall ] ) || ( ring > holes[ wall ] + 3 ) )
        antialiased_polar_pixel( ring, (double)angle + wall * TAU / 3.0, 255, 255, 255 );
      else
        antialiased_polar_pixel( ring, (double)angle + wall * TAU / 3.0, 0, 0, 0 );

      }
    
    }
    
    for( int player = 0; player < 6; player++ ) {
      
      alivecounter[ player ] += 1;

      bool button = false;
      switch( player ) {
        case 0:
          button |= button_rising[ 0 ];
          break;
        case 1:
          button |= button_rising[ 1 ];
          break;
        case 2:
          button |= button_rising[ 4 ];
          break;
        case 3:
          button |= button_rising[ 5 ];
          break;
        case 4:
          button |= button_rising[ 2 ];
          break;
        case 5:
          button |= button_rising[ 3 ];
          break;
      }
      
      if( button ) {
        inertia[ player ] += 0.5;
      }
      
      position[ player ] += inertia[ player ];
      inertia[ player ] -= 0.15;
      
      if( position[ player ] <= 0 ) {
        position[ player ] = 0;
        inertia[ player ] = 0;
      }
      
      int ring = round( position[ player ] );
      
      if( getColor( polar2led( ring, player * ring ) ) != 0 ) {
        alivecounter[ player ] = 0;
      }
        
      
      ring = position[ player ];
      double realpart = position[ player ] - ring;
      ring = 10 - ring;
      if( ring >= 0 ) {
        int shade = realpart * 255;
        setColor( 
          polar2led( ring, player * ring ), 
          applyGammaCorrection( color( shade * colors[ player][ 0 ], shade * colors[ player][ 1 ], shade * colors[ player][ 2 ] ) ) 
        );
        shade = 255 - shade;
        setColor( 
          polar2led( ring + 1, player * ( ring + 1 ) ), 
          applyGammaCorrection( color( shade * colors[ player][ 0 ], shade * colors[ player][ 1 ], shade * colors[ player][ 2 ] ) ) 
        );
      }
      
      if( position[ player ] > 10 ) {
        position[ player ] = 10;
        inertia[ player ] = 0;
      }
      
    }
    
    reset_button_states();
    
    // elect winner
    
    ws2811_led_t winner = color( 0, 0, 0 );
    int winnerscore = 10;
    for( int player = 0; player < 6; player++ ) {
      if( alivecounter[ player ] > winnerscore ) {
        winnerscore = alivecounter[ player ];
        winner = color( 255 * colors[ player ][ 0 ], 255 * colors[ player ][ 1 ], 255 * colors[ player ][ 2 ] );
      }
    }
    setColor( playerLEDs[ 0 ], winner );
    setColor( playerLEDs[ 1 ], winner );
    setColor( playerLEDs[ 2 ], winner );
    
    angle += 0.05;
    
    usleep(100000); // 100 per second

  }
  
}
