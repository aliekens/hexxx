#include "players.h"
#include "buffer.h"
#include "circle.h"
#include "line.h"

int player_position[PLAYERS] = { 0, 0, 0 };
bool player_human[PLAYERS] = { false, false, false };
bool player_alive[PLAYERS] = { false, false, false };
ws2811_led_t player_color[PLAYERS] = { 0, 0, 0 };

class Particle {
public:
  int led;
  int direction;
  ws2811_led_t color;
  Particle() { 
    led = 0;
    direction = rand() % 6;
    switch( rand() % 6 ) {
      case 0:
        color = COLOR_RED;
      break;
      case 1:
        color = COLOR_GREEN;
      break;
      case 2:
        color = COLOR_BLUE;
      break;
      case 3:
        color = COLOR_CYAN;
      break;
      case 4:
        color = COLOR_MAGENTA;
      break;
      case 5:
        color = COLOR_YELLOW;
      break;
    }
  }
  void update() {
    direction += rand() % 3 - 1;
    led = warping_neighbor( led, direction );
  }
  void render( Buffer* buffer ) {
    buffer->setPixel( led, color );
  }
};

#define NPARTICLES 10

void invite_players() {
  
  reset_button_states();
  
  for( int player = 0; player < PLAYERS; player++ ) {
    player_human[ player ] = false;
    player_alive[ player ] = true;
    setColor( playerLEDs[ player ], 0 );
  }
  
  Buffer buffer;
  Circle player1( Coordinate( 0.8 * cos( 3 * TAU / 4 ), 0.8 * sin( 3 * TAU / 4 ) ), 0.14 );
  Circle player2( Coordinate( 0.8 * cos( 5 * TAU / 12 ), 0.8 * sin( 5 * TAU / 12 ) ), 0.14 );
  Circle player3( Coordinate( 0.8 * cos( 1 * TAU / 12 ), 0.8 * sin( 1 * TAU / 12 ) ), 0.14 );
  
  Particle particles[ NPARTICLES ];
  
  int counter100 = 0;
  int counter = rand() % 1000;
  while( 
    !( player_human[ 0 ] || player_human[ 1 ] || player_human[ 2 ] ) ||
    ( ( ( player_human[ 0 ] || player_human[ 1 ] || player_human[ 2 ] ) == false ) || ( counter100 < 100 ) )
  ) { // wait a bit for players to join
    if( player_human[ 0 ] || player_human[ 1 ] || player_human[ 2 ] ) 
      counter100++;
    if( counter100 > 100 ) counter100 = 100;
    counter++;
    
    for( int player = 0; player < PLAYERS; player++ ) { // check whether player pressed buttons
      if( !player_human[ player ] ) // only those who haven't joined yet
        if( button_pushed[ player * 2 ] || button_pushed[ player * 2 + 1 ] ) {
          player_human[ player ] = true;
          setColor( playerLEDs[ player ], player_color[ player ] );
          counter100 = 0;
        }
    }
    
    reset_button_states();
    
    // animate
    
    buffer.darken( 0.96 );
    
    if( player_human[ 0 ] ) {
      player1.radius = 0.05 + 0.5 * ( 100.0 - counter100 ) / 100.0;
      player1.render( &buffer, COLOR_RED );
    } else {
      if( counter % 45 == 0 ) {
        player1.render( &buffer, COLOR_RED );
      }
    }
    if( player_human[ 1 ] ) {
      player2.radius = 0.05 + 0.5 * ( 100.0 - counter100 ) / 100.0;
      player2.render( &buffer, COLOR_GREEN );
    } else {
      if( counter % 45 == 15 ) {
        player2.render( &buffer, COLOR_GREEN );
      }
    }
    if( player_human[ 2 ] ) {
      player3.radius = 0.05 + 0.5 * ( 100.0 - counter100 ) / 100.0;
      player3.render( &buffer, COLOR_BLUE );
    } else {
      if( counter % 45 == 30 ) {
        player3.render( &buffer, COLOR_BLUE );
      }
    }
    
    for( int i = 0; i < 1 + counter100 / 20; i++ ) {
      if( rand() % 10 == 0 )
        buffer.setPixel( rand() % 397, COLOR_WHITE );
    }
    
    buffer.render();

    usleep( 20000 );
  }
  
  fillhexagon( COLOR_WHITE );
  usleep( 50000 );
  fillhexagon( COLOR_BLACK );
  
}