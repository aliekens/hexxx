#include "hexxx.h"

#include <iostream>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

Display *d;
XImage *image;

ws2811_led_t getPixel( int x, int y ) {
}

void logic_thread() {
  
  d = XOpenDisplay((char *) NULL);
  
  while (1) {
    
    XColor c;
    image = XGetImage (d, RootWindow (d, DefaultScreen (d)), 0, 0, 256, 256, AllPlanes, XYPixmap);

    for( int i = 0; i < 397; i++ ) {
      c.pixel = XGetPixel (image, coordinates[ i ][ 0 ], 255 - coordinates[ i ][ 1 ] );
      XQueryColor (d, DefaultColormap(d, DefaultScreen (d)), &c);
      ws2811_led_t wsc = applyGammaCorrection( color( c.red / 256, c.green / 256, c.blue / 256 ) );
      setColor( i, wsc );
    }
      
    XFree (image);
    usleep(30000); // 100 per second
  }
  
  
}
