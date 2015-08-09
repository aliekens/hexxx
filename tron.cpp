#include "hexxx.h"
#include "players.h"

int player_direction[PLAYERS];

void setup_tron(void) {
  player_color[ 0 ] = color( 255, 0, 0 );
  player_color[ 1 ] = color( 0, 255, 0 );
  player_color[ 2 ] = color( 0, 0, 255 );
  int r = rand() % 2;
  player_position[ 0 ] = 335 + r;
  player_direction[ 0 ] = 2 - r;
  player_position[ 1 ] = 335 + 44 + r;
  player_direction[ 1 ] = ( 6 - r ) % 6;
  player_position[ 2 ] = 335 + 22 + r;
  player_direction[ 2 ] = 4 - r;
}

void randomize_direction_for_player( int player ) {
  if( rand() % 4 < 3 ) {
    if( rand() % 2 )
      player_direction[ player ] = ( player_direction[ player ] + 1 ) % 6;
    else
      player_direction[ player ] = ( player_direction[ player ] + 5 ) % 6; // smart hack
  }
}

int color_sum( ws2811_led_t c ) {
  return getRed( c ) + getGreen( c ) + getBlue( c );
}

void play_tron(void) {
  
  int sleep = 200000;
  
  while( ( player_alive[ 0 ] && player_alive[ 1 ] ) || ( player_alive[ 1 ] && player_alive[ 2 ] ) || ( player_alive[ 0 ] && player_alive[ 2 ] ) ) { // play as long as 2 players are alive
  
    // fade out player tails
    darkenhexagon();
    if( rand() % 2 )
      darkenhexagon();
  
    // update players
    for( int player = 0; player < PLAYERS; player++ ) {
      if( player_alive[ player ] ) {

        if( player_human[ player ] ) {

          if( button_rising[ player * 2 ] )
            player_direction[ player ] = ( player_direction[ player ] + 1 ) % 6;
          if (button_rising[ player * 2 + 1 ] )
            player_direction[ player ] = ( player_direction[ player ] + 5 ) % 6;

        } else {
          
          int next_position = neighbor( player_position[ player ], player_direction[ player ] );
          int next_next_position = neighbor( next_position, player_direction[ player ] );
          int next_next_next_position = neighbor( next_next_position, player_direction[ player ] );
          int next_next_next_next_position = neighbor( next_next_next_position, player_direction[ player ] );
          int next_next_next_next_next_position = neighbor( next_next_next_next_position, player_direction[ player ] );
          int next_next_next_next_next_next_position = neighbor( next_next_next_next_next_position, player_direction[ player ] );

          int next_color = color_sum( getColor( next_position ) );
          int next_next_color = color_sum( getColor( next_next_position ) );
          
          if( player_position[ player ] == next_position )
            randomize_direction_for_player( player );
          else if( next_position == next_next_position )
            randomize_direction_for_player( player );
          else if( next_next_position == next_next_next_position )
            randomize_direction_for_player( player );
          else if( next_next_next_position == next_next_next_next_position )
            randomize_direction_for_player( player );
          else if( next_next_next_next_position == next_next_next_next_next_position )
            randomize_direction_for_player( player );
          else if( next_next_next_next_next_position == next_next_next_next_next_next_position )
            randomize_direction_for_player( player );
          else if( next_color > 0 )
            randomize_direction_for_player( player );
          else if( next_next_color > 0 )
            randomize_direction_for_player( player );
          else if( rand() % 10 == 0 )
            randomize_direction_for_player( player );
        }

        int next_position = neighbor( player_position[ player ], player_direction[ player ] );
        ws2811_led_t next_position_color = getColor( next_position );
        if( ( getRed( next_position_color ) < 20 ) &&  ( getGreen( next_position_color ) < 20 ) && ( getBlue( next_position_color ) < 20 ) )
          player_position[ player ] = neighbor( player_position[ player ], player_direction[ player ] );
        else {
          player_alive[ player ] = false;
          setColor( playerLEDs[ player ], 0 );
          setColor( player_position[ player ], 0xffffff );
        }
        
      }
    
    }
    
    if( player_position[ 0 ] == player_position[ 1 ] ) {
      player_alive[ 0 ] = false;
      player_alive[ 1 ] = false;
      setColor( player_position[ 0 ], 0xffffff );
    }
    if( player_position[ 1 ] == player_position[ 2 ] ) {
      player_alive[ 1 ] = false;
      player_alive[ 2 ] = false;
      setColor( player_position[ 1 ], 0xffffff );
    }
    if( player_position[ 0 ] == player_position[ 2 ] ) {
      player_alive[ 0 ] = false;
      player_alive[ 2 ] = false;
      setColor( player_position[ 2 ], 0xffffff );
    }
    
    print_button_states();
    reset_button_states();
  
    // render players on new positions
    for( int player = 0; player < PLAYERS; player++ ) {
      if( player_alive[ player ] )
        setColor( player_position[ player ], player_color[ player ] );
      else
        setColor( player_position[ player ], 0xffffff );
    }
    
    usleep( sleep );
    sleep *= 0.99;
  
  }
  
}

void announce_winner() {
  ws2811_led_t c = 0xffffff;
  for( int player = 0; player < 3; player++ ) {
    if( player_alive[ player ] ) {
      c = player_color[ player ];
    }
  }
  for( int flash = 0; flash < 10; flash++ ) {
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
