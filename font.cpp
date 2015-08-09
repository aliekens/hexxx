#include "font.h"

#include <string>

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

void printCharacter( int skewedx, int skewedy, char c, ws2811_led_t color ) {
  int fontposition = characters.find( c );
  if( fontposition != std::string::npos ) {
    for( int x = 0; x < 6; x++ ) {
      for( int y = 0; y < 6; y++ ) {
        if( ( font[ fontposition ][ 5 - y ] >> ( 5 - x ) ) & 0x01 )
          setColor( skewed2led( skewedx + x - ( y / 2 ), skewedy + y ), color );
      }
    }
  }
}

void printString( int skewedx, int skewedy, std::string str, ws2811_led_t color ) {
  int counter = 0;
  for(char& c : str) {
    printCharacter( skewedx + counter * 7, skewedy, c, color );
    counter++;
  }
}
