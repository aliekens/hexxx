#include "font.h"
#include "coordinates.h"
#include "hexxx.h"

uint32_t font[5][6] = {
  { 0b111110, 0b011000, 0b111100, 0b010000, 0b110001, 0b111111 }, // E
  { 0b110011, 0b010001, 0b111111, 0b010001, 0b110011, 0b110011 }, // H
  { 0b111011, 0b001110, 0b001100, 0b001110, 0b010110, 0b110011 }, // X
  { 0b000000, 0b001110, 0b011110, 0b001110, 0b001100, 0b000000 },  // diamond
  { 0b000000, 0b000000, 0b000000, 0b000000, 0b000000, 0b000000 }  // space
};

std::string characters = "EHXx ";

int printCharacter( int position, char c, ws2811_led_t color ) {
  int fontposition = characters.find( c );
  if( fontposition != std::string::npos ) {
    for( int row = 5; row >= 0; row-- ) {
      for( int column = 0; column < 6; column++ ) {
        if( ( font[ fontposition ][ row ] >> ( 5 - column ) ) & 0x01 )
          setColor( position, color );
        position = neighbors[ position ][ 0 ]; // step right
      }
      // move to next row
      if( row % 2 )
        position = neighbors[ position ][ 1 ];
      else
        position = neighbors[ position ][ 2 ];
      for( int i = 0; i < 6; i++ ) {
        position = neighbors[ position ][ 3 ];
      }
    }
  }
  // move to position for next character
  for( int i = 0; i < 6; i++ )
    position = neighbors[ position ][ 5 ];
  for( int i = 0; i < 4; i++ )
    position = neighbors[ position ][ 0 ];
  return position;
}
