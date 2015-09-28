#ifndef COORDINATES__H
#define COORDINATES__H

#define TAU 6.28318530718

// this header defines a bunch of coordinte systems to translate all sorts of coordinates to LEDs and back to the physical world
// note that all coordinate systems assume the viewpoint of PLAYER 0
// renderings for another player can be drawn from player 0's viewpoint and then rotated

// LED TO PHYSICAL COORDINATE

// OPTION 1: normalized coordinate system

// Center LED is at origin with coordinate ( 0.0, 0.0 )
// The outer corner LEDs fit within a unity circle around this origin
// E.g., the coordinate for the rightmost LED from the RED player's POV is at position ( 1.0, 0.0 ) and the leftmost at ( -1.0, 0.0 )
// The coordinates of the other corner LEDs are at ( ± 1/2, ± √3/2 )
// The distance between two neighboring LEDs equals 1/11

//              | Y
//              |
//              |
//           .--|--.
//          /   |   \
//   ______/____|____\________ X
// -1.0,0.0\    |    /1.0,0.0
//          \   |   /
//           '--|--'
//              |
//              |

extern float unit_coordinates_array[397][2];
float led2unitx( int led );
float led2unity( int led );

// OPTION 2: X and Y coordinates are in [0:255][0:255], with the hexagon centered at ( 127.5, 127.5 )

extern int coordinates_array[397][2];
int led2bytex( int led );
int led2bytey( int led );

// LED TO NEIGHBORING LED
// convert a LED's position to one of its neighbors, using the following direction:
// note that if you fall outside of the hexagon, the position remains unchanged
//
//   2   1
//    \ /
// 3 - . - 0
//    / \
//   4   5

extern int neighbors_array[397][6];
int neighbor( int led, int neighbor );

// convert a LED to a neighbor, employing edge warping

extern int warping_neighbors_array[397][6];
int warping_neighbor( int led, int neighbor );

// TODO: ROTATE 60DEGREES CLOCKWISE/COUNTERCLOCKWISE

// POLAR COORDINATE TO LED

// The HEXXX has 12 "rings", numbered 0 .. 11
// The inner ring (ring 0) is the center RGB LED. 
// The first ring (ring 1) has 6 LEDs, surrounding the center. The LED closest to the left button of user 0 (red buttons) is LED 0 in this ring. The LEDs are numbered counter-clockwise from 0 to 6.
// The nth ring has n*6 LEDs, numbered similarly to the first ring, from 0 to n*6-1

// compute the number of LEDs in ring
int leds_in_polar_ring( int ring );

// convert a ring-LED coordinate to the LED's ID, in 0 .. n*6-1 (circularized in the function)
int polar2led( int ring, int led );

// convert a ring-angle coordinate to the LED's ID, angle in 0 .. tau (circularized in the function)
int doublepolar2led( int ring, double angle );

// HEXXX IN A SKEWED AXIS COORDINATE SYSTEM

//                  Y
//                 /
//      -11,11    /
//         .-----/0,11
//        /     / \
// ______/_____/___\________ X
//  -11,0\    /0,0 /11,0
//        \  /    /
//         \/____/
//    0,-11/     11,-11
//        /

extern int skewed2led_array[23][23];
int skewed2led( int x, int y ); // returns LED number in [-11:11][-11:11], or -1 if no LED, or -1 if out of range
int led2skewedx( int led );
int led2skewedy( int led );

#endif