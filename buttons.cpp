#include "buttons.h"

#include <iostream>

bool button_state[ 6 ] = { 0, 0, 0, 0, 0, 0 };
bool button_rising[ 6 ] = { 0, 0, 0, 0, 0, 0 };
bool button_falling[ 6 ] = { 0, 0, 0, 0, 0, 0 };
bool button_pushed[ 6 ] = { 0, 0, 0, 0, 0, 0 };
bool button_released[ 6 ] = { 0, 0, 0, 0, 0, 0 };


bool set_button_state( int button, bool value ) {
  // HEXXX uses pull-up, so button pushes are inverted
  value = !value;
  // perists various forms of button states, like rising and falling
  if( value == true ) {
    button_pushed[ button ] = true;
    if( button_state[ button ] == false )
      button_rising[ button ] = true;
  }
  if( value == false ) {
    button_released[ button ] = true;
    if( button_state[ button ] )
      button_falling[ button ] = true;
  }
  button_state[ button ] = value;
}

void reset_button_states() { // call this function after checking rising/falling checks to get correct data in next iteration
  for( int i = 0; i < 6; i++ ) {
    button_rising[ i ] = false;
    button_falling[ i ] = false;
    button_pushed[ i ] = false;
    button_released[ i ] = false;
  }
}

void print_button_states() {
  std::cout << "STATE ";
  for( int i = 0; i < 6; i++ )
    std::cout << button_state[ i ];
  std::cout << "  RISING ";
  for( int i = 0; i < 6; i++ )
    std::cout << button_rising[ i ];
  std::cout << "  FALLING ";
  for( int i = 0; i < 6; i++ )
    std::cout << button_falling[ i ];
  std::cout << "  PUSHED ";
  for( int i = 0; i < 6; i++ )
    std::cout << button_pushed[ i ];
  std::cout << "  RELEASED ";
  for( int i = 0; i < 6; i++ )
    std::cout << button_released[ i ];
  std::cout << std::endl;
}
