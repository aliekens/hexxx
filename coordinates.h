#ifndef COORDINATES__H
#define COORDINATES__H

// this header defines a bunch of coordinte systems to translate all sorts of coordinates to LEDs and back to the physical world
// note that all coordinate systems assume the viewpoint of PLAYER 0
// renderings for another player can be drawn from player 0's viewpoint and then rotated

// LED TO PHYSICAL COORDINATE
// convert a LED's number to a physical X, Y coordinate in [0:255][0:255]

extern int coordinates_array[400][2];
int position2x( int position );
int position2y( int position );

// LED TO NEIGHBORING LED
// convert a LED's position to one of its neighbors, using the following direction:
// note that if you fall outside of the hexagon, the position remains unchanged
//
//   2   1
//    \ /
// 3 - . - 0
//    / \
//   4   5

extern int neighbors_array[400][6];

int neighbor( int position, int neighbor );

// TODO: LED-TO-NEIGHBORS ON A DONUT (or whatever shape you get when wrapping the sides of a hexagon)

// TODO: ROTATE 60DEGREES CLOCKWISE/COUNTERCLOCKWISE

// TODO: POLAR COORDINATE TO LED

// TODO: X,Y IN SLANTED RECTANGLE TO LED
// map a rectangle [0:20,0:20] to positions in the HEXXX
// equals -1 if there is no pixel at the current position

//          Y
//         /
//     21 .----.----. (22,22)
//       /******\-1/
//      /********\/
//  11 /\********/
//    /-1\******/
// 0 /____\____/____ X
//  0     11  21

// extern int coordinate2position[ 23 ][ 23 ];
// int coordinate2position( int x, int y );

#endif