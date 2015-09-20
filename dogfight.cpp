#include "hexxx.h"
#include "players.h"

#include <vector>
#include <algorithm>

int player_direction[ PLAYERS ];
bool player_shield[ PLAYERS ][ 6 ];

class Bullet {
public:
  int position;
  int direction;
  int age;
  
  Bullet( int position, int direction );
  void update();
  void render();
};

Bullet::Bullet( int position, int direction ) {
  this->position = position;
  this->direction = direction;
  this->age = 0;
}

void Bullet::update() {
  position = warping_neighbor( position, direction );
  age += 1;
}

void Bullet::render() {
  setColor( position, 0x408040 );
}

std::vector< Bullet >
removeOldBullets( std::vector< Bullet > bullets ) {
  std::vector< Bullet > result;
  for( std::vector< Bullet >::iterator i = bullets.begin(); i != bullets.end(); i++ ) {
    if( i->age < 20 ) {
      result.push_back( *i );
    }
  }
  return result;
}

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
  
  for( int player = 0; player < PLAYERS; player++ ) {
    for( int shield = 0; shield < 6; shield++ ) {
      player_shield[ player ][ shield ] = true;
    }
  }
}

int last_turn[PLAYERS] = {0,0,0};
void randomize_direction_for_player( int player ) {
  if( rand() % 4 < 3 ) {
    if( last_turn[ PLAYERS ] == 1 ) {
      if( rand() % 4 < 3 ) {
        player_direction[ player ] = ( player_direction[ player ] + 1 ) % 6;
        last_turn[ PLAYERS ] = 1;
      } else {
        player_direction[ player ] = ( player_direction[ player ] + 5 ) % 6;
        last_turn[ PLAYERS ] = 2;
      }
    } else {
      if( rand() % 4 < 3 ) {
        player_direction[ player ] = ( player_direction[ player ] + 5 ) % 6;
        last_turn[ PLAYERS ] = 2;
      } else {
        player_direction[ player ] = ( player_direction[ player ] + 1 ) % 6;
        last_turn[ PLAYERS ] = 1;
      }
    }
  }
}

int color_sum( ws2811_led_t c ) {
  return getRed( c ) + getGreen( c ) + getBlue( c );
}

void play_tron(void) {
  
  std::vector< Bullet > bullets;

  int sleep = 200000;
  int counter = 0;
  bullets.clear();
  
  while( ( player_alive[ 0 ] && player_alive[ 1 ] ) || ( player_alive[ 1 ] && player_alive[ 2 ] ) || ( player_alive[ 0 ] && player_alive[ 2 ] ) ) { // play as long as 2 players are alive
  
    counter += 1;
    
    // fade out player tails
    fillhexagon( COLOR_BLACK );
  
    // update players
    for( int player = 0; player < PLAYERS; player++ ) {
      if( player_alive[ player ] ) {
        
        if( counter % 10 == 0 ) {
          Bullet b( player_position[ player ], player_direction[ player ] );
          bullets.push_back( b );
        }

        if( player_human[ player ] ) {

          if( button_rising[ player * 2 ] )
            player_direction[ player ] = ( player_direction[ player ] + 1 ) % 6;
          if (button_rising[ player * 2 + 1 ] )
            player_direction[ player ] = ( player_direction[ player ] + 5 ) % 6;

        } else {
          if( rand()% 5 == 0 )
            randomize_direction_for_player( player );
        }

        int next_position = warping_neighbor( player_position[ player ], player_direction[ player ] );
        ws2811_led_t next_position_color = getColor( next_position );
        if( ( getRed( next_position_color ) < 20 ) &&  ( getGreen( next_position_color ) < 20 ) && ( getBlue( next_position_color ) < 20 ) )
          player_position[ player ] = warping_neighbor( player_position[ player ], player_direction[ player ] );
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
      if( player_alive[ player ] ) {
        setColor( player_position[ player ], player_color[ player ] );
//        for( int shield = 0; shield < 6; shield++ ) {
//          if( player_shield[ player ][ shield ] )
//            setColor( warping_neighbor( player_position[ player ], shield ), 0x808080 );
//        }
        setColor( 
          warping_neighbor( player_position[ player ], player_direction[ player ] + 3 ), 
          darkenColor( player_color[ player ], 1, 2, 0 )
        );
      }
    }
    
    for( int i = 0; i < 2; i++ ) {
      for( std::vector< Bullet >::iterator it = bullets.begin(); it != bullets.end(); ++it ) {
        it->update();
      }
    }
    for( std::vector< Bullet >::iterator it = bullets.begin(); it != bullets.end(); ++it ) {
      it->render();
    }
    bullets = removeOldBullets( bullets );
    
    usleep( sleep );
  
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