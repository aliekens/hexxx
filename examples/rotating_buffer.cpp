// my development version of SuperHeXXXagon
// an implementation of the SuperHexagon game on the HeXXX console

#include <stdbool.h>
#include <stdio.h>

#include "hexxx.h"
#include "color.h"
#include "buffer.h"
#include "buttons.h"

void render_border(int border, int ring, ws2811_led_t color, Buffer* buffer) {
  int size        = leds_in_polar_ring(ring) / 6;
  int led_in_ring = border * size;
  int first_led   = polar2led(ring, led_in_ring);
  for(int i=0; i<=size; i++) {
    if(border == 5 && i==size) {  // border case
      // last pixel doesn't go to beginning of next ring, but this ring (close)
      buffer->setPixel(polar2led(ring, 0), color);
    } else {
      buffer->setPixel(first_led + i, color);
    }
  }
}

void render_borders(int ring, ws2811_led_t color, Buffer* buffer) {
  for(int border=0; border<6; border++) {
    render_border(border, ring, color, buffer);
  }
}

void logic_thread() {
  Buffer buffer;
  int    ring  = 5;
  float  angle = 0;

  while(true) {
    // render an image, e.g. borders of a given ring
    buffer.fill(COLOR_BLACK);
    render_borders(ring, COLOR_YELLOW, &buffer);

    // rotate the buffer
    buffer.rotate(angle);

    // and render the rotated version
    buffer.render();

    // prepare rotation angle
    angle += 6.28318530718 / 48;

    // take it easy
    usleep(100000);
  }
}
