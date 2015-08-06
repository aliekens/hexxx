#include "hexxx.h"

#define PLAYERS 3
int position[PLAYERS];
bool humanplayer[PLAYERS];
bool alive[PLAYERS];
int direction[PLAYERS];
ws2811_led_t colors[PLAYERS];

void setup_tron(void) {
  colors[ 0 ] = color( 255, 0, 0 );
  colors[ 1 ] = color( 0, 255, 0 );
  colors[ 2 ] = color( 0, 0, 255 );
  int r = rand() % 2;
  position[ 0 ] = 335 + r;
  direction[ 0 ] = 2 - r;
  position[ 1 ] = 335 + 44 + r;
  direction[ 1 ] = ( 6 - r ) % 6;
  position[ 2 ] = 335 + 22 + r;
  direction[ 2 ] = 4 - r;
}

void darkenhexagon() {
  for( int i = 0; i < LED_COUNT - 3; i++ ) {
    setColor( i, darkenColor( getColor( i ) ) );
  }
}

void play_tron(void) {
  
  int sleep = 200000;
  
  while( ( alive[ 0 ] && alive[ 1 ] ) || ( alive[ 1 ] && alive[ 2 ] ) || ( alive[ 0 ] && alive[ 2 ] ) ) { // play as long as 2 players are alive
  
    // fade out player tails
    darkenhexagon();
  
    // update players
    for( int player = 0; player < PLAYERS; player++ ) {
      if( alive[ player ] ) {

        if( humanplayer[ player ] ) {

          if( button_rising[ player * 2 ] )
            direction[ player ] = ( direction[ player ] + 1 ) % 6;
          if (button_rising[ player * 2 + 1 ] )
            direction[ player ] = ( direction[ player ] + 5 ) % 6;

        } else {

          if( ( position[ player ] == neighbors[ position[ player ] ][ direction[ player ] ] ) )
            if( rand() % 2 )
              direction[ player ] = ( direction[ player ] + 1 ) % 6;
            else
              direction[ player ] = ( direction[ player ] + 5 ) % 6; // smart hack
          else if( rand() % 5 == 0 )
            if( rand() % 2 )
              direction[ player ] = ( direction[ player ] + 1 ) % 6;
            else
              direction[ player ] = ( direction[ player ] + 5 ) % 6; // smart hack

        }

        int next_position = neighbors[ position[ player ] ][ direction[ player ] ];
        if( getColor( next_position ) == 0 )
          position[ player ] = neighbors[ position[ player ] ][ direction[ player ] ];
        else {
          alive[ player ] = false;
          setColor( playerLEDs[ player ], 0 );
        }
        
      }
    
    }
    
    print_button_states();
    reset_button_states();
  
    // render players on new positions
    for( int player = 0; player < PLAYERS; player++ ) {
      if( alive[ player ] )
        setColor( position[ player ], colors[ player ] );
    }
    
    usleep( sleep );
    sleep *= 0.99;
  
  }
  
}

void invite_players() {
  
  reset_button_states();
  
  for( int player = 0; player < PLAYERS; player++ ) {
    humanplayer[ player ] = false;
    alive[ player ] = true;
    setColor( playerLEDs[ player ] , 0 );
  }

  int counter = 0;
  while( ( ( humanplayer[ 0 ] || humanplayer[ 1 ] || humanplayer[ 2 ] ) == false ) || ( counter < 100 ) ) { // wait a bit for players to join
    counter++;
    
    for( int player = 0; player < PLAYERS; player++ ) { // check whether player pressed buttons
      if( !humanplayer[ player ] ) // only those who haven't joined yet
        if( button_pushed[ player * 2 ] || button_pushed[ player * 2 + 1 ] ) {
          humanplayer[ player ] = true;
          setColor( playerLEDs[ player ], colors[ player ] );
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

void announce_winner() {
  ws2811_led_t c = 0xffffff;
  for( int player = 0; player < 3; player++ ) {
    if( alive[ player ] ) {
      c = colors[ player ];
    }
  }
  for( int flash = 0; flash < 5; flash++ ) {
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
