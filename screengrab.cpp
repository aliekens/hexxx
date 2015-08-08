#include "hexxx.h"
#include "coordinates.h"

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
    
    image = XGetImage (d, RootWindow (d, DefaultScreen (d)), 0, 0, 256, 256, AllPlanes, XYPixmap);

    for( int i = 0; i < 397; i++ ) {
      
      int red = 0;
      int green = 0;
      int blue = 0;
      int counter = 0;
      
      for( int x = -1; x <= 1; x++ )
        for( int y = -1; y <= 1; y++ )
          if( ( x >= 0 ) && ( y >= 0 ) && ( x <= 255 ) && ( y <= 255 ) ) {

            XColor c;
            c.pixel = XGetPixel (image, position2x( i ) + x * 4, 255 - position2y( i ) + y * 4 );
            XQueryColor (d, DefaultColormap(d, DefaultScreen (d)), &c);

            red += c.red / 256;
            green += c.green / 256;
            blue += c.blue / 256;
            
            counter += 1;

          }
      ws2811_led_t wsc = applyGammaCorrection( color( red / counter, green / counter, blue / counter ) );
      setColor( i, wsc );
    }
      
    XFree (image);
//    usleep(30000); // 100 per second
  }
  
  
}
