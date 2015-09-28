#include "font.h"

#include <iostream>
#include <fstream>

#include "hexxx.h"
#include "coordinates.h"
#include "buffer.h"

Font::Font( const std::string& filename ) {
  std::ifstream fontfile( filename );
  if (fontfile.is_open()) {
    fontfile >> sizex;
    fontfile >> sizey;
    std::string line;
    getline (fontfile,line); // skip first line
    while ( getline (fontfile,line) ) {
      char letter = line[ 0 ];
      for( int y = 0; y < sizey; y++ ) {
        std::vector< bool > row;
        for( int x = 0; x < sizex; x++ ) {
          row.push_back( line[ y * sizex + x + 1 ] == '1' );
        }
        font[ letter ].push_back( row );
      }
    }
    fontfile.close();
  } else 
    std::cerr << "Unable to open font file " << filename << std::endl; 
}

void Font::printCharacter( Buffer* buffer, int skewedx, int skewedy, char c, ws2811_led_t color ) {
  if ( font.find( c ) != font.end() ) {
    std::vector< std::vector< bool > > character = font[ c ];
    for( int x = 0; x < sizex; x++ ) {
      for( int y = 0; y < sizey; y++ ) {
        if( character[ y ][ x ] ) {
          int led = skewed2led( skewedx + x, skewedy + sizey - y );
          buffer->setPixel( led, color );
        }
      }
    }
  }
}

void Font::printString( Buffer* buffer, int skewedx, int skewedy, std::string str, ws2811_led_t color ) {
  int counter = 0;
  for(char& c : str) {
    printCharacter( buffer, skewedx + counter * ( sizex + 1 ), skewedy, c, color );
    counter++;
  }
}
