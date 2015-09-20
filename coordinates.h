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
float led2unitx( int position );
float led2unity( int position );

// OPTION 2: X and Y coordinates are in [0:255][0:255], with the hexagon centered at ( 127.5, 127.5 )

extern int coordinates_array[397][2];
int led2bytex( int position );
int led2bytey( int position );

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
int neighbor( int position, int neighbor );

extern int warping_neighbors_array[397][6];
int warping_neighbor( int position, int neighbor );

// TODO: LED-TO-NEIGHBORS ON A DONUT (or whatever shape you get when wrapping the sides of a hexagon)

// TODO: ROTATE 60DEGREES CLOCKWISE/COUNTERCLOCKWISE

int leds_in_polar_ring( int ring );
int polar2led( int ring, int led );
int doublepolar2led( int ring, double led );

// TODO: POLAR COORDINATE TO LED

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
int led2skewedx( int position );
int led2skewedy( int position );

#endif