#ifndef COORINDATES__H
#define COORDINATES__H

extern int coordinates[400][2];

extern int neighbors[400][6];
/*The x y cordinate are represinted by a skewed square grid i.e
 ________________
/_/_/_/_/_/_/_/_/
_/_/_/_/_/_/_/_/
/_/_/_/_/_/_/_/
_/_/_/_/_/_/_/

This fits the hexagons shape. But it creates some invalid pixels
the name is affine coordinates
*/
extern int xyToCoord[23][23];
extern int coordToXY[397][2];
#endif
