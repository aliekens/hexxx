#include "hexxx.h"
#include "color.h"

#include "coordinate.h"
#include "vector.h"
#include "circle.h"
#include "line.h"

#include "buffer.h"

#define PLAYER_SIZE 0.25

// draw circles and lines in the unit coordinate system

float random_float() {
  return static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
}

class Player {
public:
  bool alive;
  int id;
  double position;
  Coordinate leftCoordinate, rightCoordinate;
  int leftButton, rightButton;
  ws2811_led_t color;
  
  Player();
  Player( int id );
  
  Coordinate getCoordinate();
  
  void update();
  void render( Buffer* buffer, double size = PLAYER_SIZE );
};

Player::Player() {
}

Player::Player( int id ) {
  alive = true;
  this->id = id;
  position = 0.5;
  leftCoordinate = Coordinate( 1.1 * cos( ( 4 - id * 2 ) * TAU / 6 ), 1.1 * sin( ( 4 - id * 2 ) * TAU / 6 ) );
  rightCoordinate = Coordinate( 1.1 * cos( ( 5 - id * 2 ) * TAU / 6 ), 1.1 * sin( ( 5 - id * 2 ) * TAU / 6 ) );
  leftButton = id * 2;
  rightButton = id * 2 + 1;
  switch(id) {
    case 0:
      color = COLOR_RED;
    break;
    case 1:
      color = COLOR_GREEN;
    break;
    case 2:
      color = COLOR_BLUE;
    break;
  }
}

void Player::update() {
  
  if( button_pushed[ leftButton ] ) {
    position -= 0.025;
    if( position < 0.15 )
      position = 0.15;
  }
  if( button_pushed[ rightButton ] ) {
    position += 0.025;
    if( position > 0.85 )
      position = 0.85;
  }
  
}

Coordinate Player::getCoordinate() {
  return leftCoordinate * ( 1 - position ) + rightCoordinate * position;
}

void Player::render( Buffer* buffer, double size ) {
  Circle circle( getCoordinate(), size );
  circle.render( buffer, color );
}

void logic_thread() {
    
  int counter = 0;
  Line borders[ 6 ];
  for( int i = 0; i < 6; i++ ) {
    borders[ i ] = Line( 
      Coordinate( 1.0 * cos( i * TAU / 6 ), 1.0 * sin( i * TAU / 6 ) ), 
      Vector( ( i + 2 ) * TAU / 6, 1 ) 
    );
  }
  
  Buffer* buffer = new Buffer();
  
  while( 1 ) {
  
    Player players[ 3 ] = { Player( 0 ), Player( 1 ), Player( 2 ) };
  
    Line ball;
    float spin = 0.0;
    
    ball = Line( 
      Coordinate( 0,0 ), 
      Vector( ( 3 + 4 * ( rand() % 3 ) ) * TAU / 12 + random_float() * 0.1 - 0.05, 0.04 ) 
    );
    
    // render the arena and show it without animation for half a second
    buffer->fill( 0 );
    for( int i = 0; i < 3; i++ ) {
      borders[ i * 2 + 1 ].render( buffer, COLOR_WHITE );
      players[ i ].render( buffer );
    }
    Circle c( ball.coordinate, 1/12.0 );
    c.render( buffer, COLOR_YELLOW );
    buffer->render();
    usleep(500000); 
    reset_button_states();

    while ( 
      ( players[ 0 ].alive || players[ 1 ].alive ) && 
      ( players[ 1 ].alive || players[ 2 ].alive ) && 
      ( players[ 2 ].alive || players[ 0 ].alive )
    ) {
    
      buffer->fill( 0 );
    
      counter += 1;

      ball.coordinate = ball.coordinate + ball.vector;

      for( int i = 0; i < 6; i++ ) {
        if( borders[ i ].side( ball.coordinate ) ) { // the ball has crossed the line
          // reflect the vector with respect to the border
          ball.coordinate = ball.intersection( borders[ i ] );
          ball.vector.angle = 2 * borders[ i ].vector.angle - ball.vector.angle;
          spin *= 0.9;
          // kill the player to whom the border belongs to
          if( i == 4 )
            players[ 0 ].alive = false;
          if( i == 2 )
            players[ 1 ].alive = false;
          if( i == 0 )
            players[ 2 ].alive = false;
          borders[ i ].render( buffer, COLOR_WHITE ); // flash wall
        }
      
        // check if we bounce into a circle
        for( int player = 0; player < 3; player++ ) 
        if( players[ player ].alive ) {
          Coordinate position = players[ player ].getCoordinate();
          if( position.distance( ball.coordinate ) < PLAYER_SIZE ) {
            // mirror the vector angle of the ball
            double circle_edge_angle = atan2( ball.coordinate.x - position.x, - ball.coordinate.y + position.y );
            double circle_norm_angle = circle_edge_angle - TAU / 4;
            ball.coordinate.x = position.x + PLAYER_SIZE * cos( circle_norm_angle );
            ball.coordinate.y = position.y + PLAYER_SIZE * sin( circle_norm_angle );
            ball.vector.angle = 2 * circle_edge_angle - ball.vector.angle;
            if( button_state[ players[ player ].leftButton ] )
              spin -= 0.005;
            if( button_state[ players[ player ].rightButton ] )
              spin += 0.005;
            players[ player ].render( buffer, PLAYER_SIZE * 1.5 ); // flash player
          }
        }
        
      }
      
      // collect button states, move players and reset button states ASAP
      for( int player = 0; player < 3; player ++ ) players[ player ].update(); // do not put these for loops in 1 loop
      reset_button_states();

      // render the walls
      for( int i = 0; i < 3; i++ ) {
        borders[ i * 2 + 1 ].render( buffer, COLOR_WHITE );
      }
      if( !players[ 0 ].alive ) {
        borders[ 4 ].render( buffer, COLOR_WHITE );
      }
      if( !players[ 1 ].alive ) {
        borders[ 2 ].render( buffer, COLOR_WHITE );
      }
      if( !players[ 2 ].alive ) {
        borders[ 0 ].render( buffer, COLOR_WHITE );
      }

      for( int player = 0; player < 3; player ++ ) if( players[ player ].alive ) players[ player ].render( buffer );
    
      // render the ball
      Circle c( ball.coordinate, 1/12.0 );
      c.render( buffer, COLOR_YELLOW );

      // increase ball speed
      ball.vector.norm = 1.002 * ball.vector.norm;
      
      // use spin to change directions
      ball.vector.angle += spin;

      buffer->render();
    
      usleep(20000); // 50 per second
      
    }
    
    int winner = 0;
    for( int player = 0; player < 3 ; player++ )if( players[ player ].alive ) { winner = player; }
    for( int i = 0; i < 10; i++ ) {
      if( i % 2 ) {
        Circle circle( players[ winner ].getCoordinate(), PLAYER_SIZE );
        circle.render( buffer, players[ winner ].color );
      } else { 
        Circle circle( players[ winner ].getCoordinate(), PLAYER_SIZE * 1.5 );
        circle.render( buffer, 0 );
      }
      buffer->render();
      usleep(200000);
    }    
    
  }
  
}
