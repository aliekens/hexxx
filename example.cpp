// Example HEXXX application that shows random walking on the hexagon and button presses
// Note that button pressing and rendering is handled by separate threads and do not need to be called

#include "hexxx.h"

// little helper to pick a random color
ws2811_led_t randomcolor() {
  return color( rand() % 256, rand() % 256, rand() % 256 );
}

// a "logic_thread" function always has to be defined in a HEXXX application
void logic_thread() {
  
  int position = 0; // start in the center of the hexagon
  ws2811_led_t c = randomcolor(); // pick a random color
  
  while (1) {
    
    // draw a pixel and move to a neighboring pixel
    setColor( position, c ); // set the LED at the current position to the current color
    position = neighbors[ position][ rand() % 6 ]; // move to a random neighbor pixel (0 = go right, 1 = go top right, ...)
    
    // if left button of player 0 (red buttons) is pressed, change color
    // player 0 has buttons 0 and 1, player 1 (clockwise neighbor of player 0) has 2 and 3, ...
    if( button_rising[ 0 ] ) // there's also button_falling, button_pushed and button_released
      c = randomcolor();
    reset_button_states(); // make sure to clear out button states everytime after having handled all of them in the current iteration
    
    usleep(10000); // 100 per second
    
  }
  
}
