#ifndef FONT__H
#define FONT__H

#include <stdint.h>

#include <string>
#include <map>
#include <vector>

#include "hexxx.h"
#include "buffer.h"

// Font made to work with the Buffer class
// Because of the way this font works (slanted blocks with micro fonts) it is most compatible with the skewed coordinate system
// The skewed coordinate system allows to draw outside of the hexagon, which is helpful with longer strings
// Convert LED positions from other coordinate systems using led2skewedx( led ) and led2skewedy( led ) from coordinates.h

class Font{
private:
  int sizex, sizey;
  std::map< char, std::vector< std::vector< bool > > > font;
public:
  Font( const std::string& filename );
  void printCharacter( Buffer* buffer, int skewedx, int skewedy, char c, ws2811_led_t color );
  void printString( Buffer* buffer, int skewedx, int skewedy, std::string str, ws2811_led_t color );
};

#endif