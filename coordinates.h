#ifndef COORDINATES__H
#define COORDINATES__H

// convert a LED's number to a physical X, Y coordinate in [0:255][0:255]

extern int coordinates[400][2];

// convert a LED's position to one of its neighbors, using the following direction:
// note that if you fall outside of the hexagon, the position remains unchanged
//
//   2   1
//    \ /
// 3 - . - 0
//    / \
//   4   5

extern int neighbors[400][6];

#endif