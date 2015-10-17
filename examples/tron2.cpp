#include "hexxx.h"
#include "players.h"
#include "buffer.h"

#include <vector>

#define LOOKUP 6
          
int player_direction[PLAYERS];

void setup_tron(void) {
  player_color[ 0 ] = color( 255, 0, 0 );
  player_color[ 1 ] = color( 0, 255, 0 );
  player_color[ 2 ] = color( 0, 0, 255 );
  int r = rand() % 2;
  player_position[ 0 ] = 276;
  player_direction[ 0 ] = 2 - r;
  player_position[ 1 ] = 276 + 40;
  player_direction[ 1 ] = ( 6 - r ) % 6;
  player_position[ 2 ] = 276 + 20;
  player_direction[ 2 ] = 4 - r;
}

int color_sum( ws2811_led_t c ) {
  return getRed( c ) + getGreen( c ) + getBlue( c );
}

int last_turn[PLAYERS] = {0,0,0};
void randomize_direction_for_player( int player ) {
  int direction_before = player_direction[ player ];
  while( ( direction_before == player_direction[ player ] ) && ( rand() % 5 > 0 ) ) {
    if( last_turn[ player ] == 1 ) {
      if( rand() % 3 > 0 ) {
        player_direction[ player ] = ( player_direction[ player ] + 1 ) % 6;
        last_turn[ player ] = 1;
      } else {
        player_direction[ player ] = ( player_direction[ player ] + 5 ) % 6;
        last_turn[ player ] = 2;
      }
    } else {
      if( rand() % 3 > 0 ) {
        player_direction[ player ] = ( player_direction[ player ] + 5 ) % 6;
        last_turn[ player ] = 2;
      } else {
        player_direction[ player ] = ( player_direction[ player ] + 1 ) % 6;
        last_turn[ player ] = 1;
      }
    }
    if( ( 
      ( color_sum( getColor( neighbor( player_position[ player ], player_direction[ player ] ) ) ) > 0 ) || 
      ( color_sum( getColor( neighbor( neighbor( player_position[ player ], player_direction[ player ] ), player_direction[ player ] ) ) ) > 0 )
    ) && ( rand() % 3 == 0 ) ) {
      player_direction[ player ] = direction_before;
    }
  }
}

std::vector< Buffer >
play_tron(void) {
  
  int sleep = 220000;
  uint updatecounter = 0;
  // render players on initial positions
  for( int player = 0; player < PLAYERS; player++ ) {
    if( player_alive[ player ] )
      setColor( player_position[ player ], player_color[ player ] );
    else
      setColor( player_position[ player ], 0xffffff );
  }
  
  std::vector< Buffer > replay;

  int counter = 0;
  while( ( player_alive[ 0 ] && player_alive[ 1 ] ) || ( player_alive[ 1 ] && player_alive[ 2 ] ) || ( player_alive[ 0 ] && player_alive[ 2 ] )) { // play as long as 2 players are alive
    if(updatecounter==0){
        counter++;
        updatecounter=6;
    // fade out player tails

    if( rand() % 2 )
      darkenhexagon();
    
    for( int i = 0; i < 66; i++ ) {
      fillborder( 0x151515 );
    }
  
    // update players
    for( int player = 0; player < PLAYERS; player++ ) {
      if( player_alive[ player ] ) {

        if( player_human[ player ] ) {

          if( button_falling[ player * 2 ] )
            player_direction[ player ] = ( player_direction[ player ] + 1 ) % 6;
          if (button_falling[ player * 2 + 1 ] )
            player_direction[ player ] = ( player_direction[ player ] + 5 ) % 6;


        } else if( counter > 3 ) {
            if( button_falling[ player * 2 ] )
              player_human[ player ]=true;
            if (button_falling[ player * 2 + 1 ] )
              player_human[ player ]=true;

          bool change_direction = false;
          int next_position = neighbor( player_position[ player ], player_direction[ player ] );
          for( int i = 0; i < LOOKUP; i++ ) {
            int next_color = color_sum( getColor( next_position ) );
            if( color_sum( getColor( next_position ) ) > 0 )
              change_direction = true;
            next_position = neighbor( next_position, player_direction[ player ] );
          }
          if( rand() % 10 == 0 ) change_direction = true;
          
          if( change_direction )
            randomize_direction_for_player( player );
        }

        int next_position = neighbor( player_position[ player ], player_direction[ player ] );
        if( button_falling[ player * 2 ] && button_falling[ player * 2 + 1 ] && button_pushed[ player * 2 ] && button_pushed[ player * 2 + 1 ] ){//jump
              next_position = neighbor( next_position, player_direction[ player ] );
        }
        ws2811_led_t next_position_color = getColor( next_position );
        if( ( getRed( next_position_color ) < 20 ) &&  ( getGreen( next_position_color ) < 20 ) && ( getBlue( next_position_color ) < 20 ) )
          player_position[ player ] = next_position;
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
    
    reset_button_states();
  

    
    Buffer screenshot;
    screenshot.screenshot();
    replay.push_back( screenshot );
    if( replay.size() > 10 ) {
      replay.erase(replay.begin());
      replay.erase(replay.begin());
    }
    sleep = sleep*0.99+1000;
    }
   // usleep( sleep );

    // render players on new positions
    for( int player = 0; player < PLAYERS; player++ ) {
      if( player_alive[ player ] )
        setColor( player_position[ player ],  color( getRed(player_color[ player ]) / (updatecounter+1), getGreen(player_color[ player ]) / (updatecounter+1), getBlue(player_color[ player ]) / (updatecounter+1) )  );
      else
        setColor( player_position[ player ], 0xffffff );
    }
    if(updatecounter==3){
           darkenhexagon();
           Buffer screenshot;
           screenshot.screenshot();
           replay.push_back( screenshot );
    }

    usleep( sleep/6 );
    updatecounter--;
  }
  
  return replay;

}

void announce_winner( std::vector< Buffer > replay ) {
  ws2811_led_t c = 0xffffff;
  for( int player = 0; player < 3; player++ ) {
    if( player_alive[ player ] ) {
      c = player_color[ player ];
    }
  }
  for( int flash = 0; flash < 5; flash++ ) {
    for( int f = 0; f < 16; f++ ) {
      fillborder( color( f * getRed(c) / 16, f * getGreen(c) / 16, f * getBlue(c) / 16 ) );
      usleep(5000);
    }
    for( int f = 16; f > 0; f-- ) {
      fillborder( color( f * getRed(c) / 16, f * getGreen(c) / 16, f * getBlue(c) / 16 ) );
      usleep(5000);
    }
  }
  for( std::vector< Buffer >::iterator i = replay.begin(); i != replay.end(); i++ ) {
    i->render();
    fillborder( c );
    usleep(180000);
  }
}

void logic_thread() {
  std::vector< Buffer > replay;
  while (1) {
    setup_tron();
    invite_players();
    replay = play_tron();
    announce_winner( replay );
    usleep( 1000000 );
  }
}
