#include "players.h"

int player_position[PLAYERS] = { 0, 0, 0 };
bool player_human[PLAYERS] = { false, false, false };
bool player_alive[PLAYERS] = { false, false, false };
ws2811_led_t player_color[PLAYERS] = { 0, 0, 0 };

void invite_players() {
  
  reset_button_states();
  
  for( int player = 0; player < PLAYERS; player++ ) {
    player_human[ player ] = false;
    player_alive[ player ] = true;
    setColor( playerLEDs[ player ], 0 );
  }

  int counter = 0;
  while( 
    !( player_human[ 0 ] || player_human[ 1 ] || player_human[ 2 ] ) ||
    ( ( ( player_human[ 0 ] || player_human[ 1 ] || player_human[ 2 ] ) == false ) || ( counter < 100 ) )
  ) { // wait a bit for players to join
    counter++;
    
    for( int player = 0; player < PLAYERS; player++ ) { // check whether player pressed buttons
      if( !player_human[ player ] ) // only those who haven't joined yet
        if( button_pushed[ player * 2 ] || button_pushed[ player * 2 + 1 ] ) {
          player_human[ player ] = true;
          setColor( playerLEDs[ player ], player_color[ player ] );
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
}