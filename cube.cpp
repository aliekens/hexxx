#include "hexxx.h"

// ===== CUBE =====

#define COORDS 8
#define TRIANGLES 12

float coords3D[ COORDS ][ 3 ] = 
  { 
    // top four
    {  1,  1,  1 },
    {  1, -1,  1 },
    { -1, -1,  1 },
    { -1,  1,  1 },
    // bottom four
    {  1,  1, -1 },
    {  1, -1, -1 },
    { -1, -1, -1 },
    { -1,  1, -1 }
  };

float coords2D[ COORDS ][ 2 ] = 
  { 
    // top four
    {  1,  1 },
    {  1, -1 },
    { -1, -1 },
    { -1,  1 },
    // bottom four
    {  1,  1 },
    {  1, -1 },
    { -1, -1 },
    { -1,  1 }
  };

char triangles[ 12 ][ 3 ] = 
  {
    { 0, 1, 2 },
    { 0, 2, 3 },
    { 0, 4, 5 },
    { 0, 5, 1 },
    { 0, 3, 7 },
    { 0, 7, 4 },
    { 6, 5, 4 },
    { 7, 6, 4 },
    { 6, 7, 3 },
    { 2, 6, 3 },
    { 6, 2, 1 },
    { 5, 6, 1 }
  };

// ======ENDCUBE======

#define TAU 6.28318530718
  
uint8_t costable[ 256 ] = { 0, 0, 0, 0, 1, 1, 1, 2, 2, 3, 4, 5, 6, 6, 8, 9, 10, 11, 12, 14, 15, 17, 18, 20, 22, 23, 25, 27, 29, 31, 33, 35, 38, 40, 42, 45, 47, 49, 52, 54, 57, 60, 62, 65, 68, 71, 73, 76, 79, 82, 85, 88, 91, 94, 97, 100, 103, 106, 109, 113, 116, 119, 122, 125, 128, 131, 135, 138, 141, 144, 147, 150, 153, 156, 159, 162, 165, 168, 171, 174, 177, 180, 183, 186, 189, 191, 194, 197, 199, 202, 204, 207, 209, 212, 214, 216, 218, 221, 223, 225, 227, 229, 231, 232, 234, 236, 238, 239, 241, 242, 243, 245, 246, 247, 248, 249, 250, 251, 252, 252, 253, 253, 254, 254, 255, 255, 255, 255, 255, 255, 255, 255, 254, 254, 253, 253, 252, 252, 251, 250, 249, 248, 247, 246, 245, 243, 242, 241, 239, 238, 236, 234, 232, 231, 229, 227, 225, 223, 221, 218, 216, 214, 212, 209, 207, 204, 202, 199, 197, 194, 191, 189, 186, 183, 180, 177, 174, 171, 168, 165, 162, 159, 156, 153, 150, 147, 144, 141, 138, 135, 131, 128, 125, 122, 119, 116, 113, 109, 106, 103, 100, 97, 94, 91, 88, 85, 82, 79, 76, 73, 71, 68, 65, 62, 60, 57, 54, 52, 49, 47, 45, 42, 40, 38, 35, 33, 31, 29, 27, 25, 23, 22, 20, 18, 17, 15, 14, 12, 11, 10, 9, 8, 6, 6, 5, 4, 3, 2, 2, 1, 1, 1, 0, 0, 0, 0};
  

uint32_t rainbowColor( int i ) {
  int r = 0;
  if( i <= 170 )
    r = costable[ i * 3 / 2 ];
  int g = 0;
  if( i >= 85 )
    g = costable[ ( i - 85 ) * 3 / 2 ];
  int b = 0;
  if( ( i <= 85 ) || ( i > 170 ) )
    b = costable[ ( ( (i + 85 ) % 256 ) * 3 / 2 ) % 256 ];
  return color( r, g, b );
}

void map3Dto2D() {
  for( int c = 0; c < COORDS; c++ ) {
    coords2D[ c ][ 0 ] = 128 + 150 * coords3D[ c ][ 0 ] / ( coords3D[ c ][ 2 ] - 3 );
    coords2D[ c ][ 1 ] = 128 + 150 * coords3D[ c ][ 1 ] / ( coords3D[ c ][ 2 ] - 3 );
  }
}

void rotateZ() {
  for( int c = 0; c < COORDS; c++ ) {
    float x =  cos( TAU * 0.5 / 360 ) * coords3D[ c ][ 0 ] + sin( TAU * 0.5 / 360 ) * coords3D[ c ][ 1 ];
    float y = -sin( TAU * 0.5 / 360 ) * coords3D[ c ][ 0 ] + cos( TAU * 0.5 / 360 ) * coords3D[ c ][ 1 ];
    coords3D[ c ][ 0 ] = x;
    coords3D[ c ][ 1 ] = y;
  }
}

void rotateX() {
  for( int c = 0; c < COORDS; c++ ) {
    float y =  cos( TAU * 1.0 / 360 ) * coords3D[ c ][ 1 ] + sin( TAU * 1.0 / 360 ) * coords3D[ c ][ 2 ];
    float z = -sin( TAU * 1.0 / 360 ) * coords3D[ c ][ 1 ] + cos( TAU * 1.0 / 360 ) * coords3D[ c ][ 2 ];
    coords3D[ c ][ 1 ] = y;
    coords3D[ c ][ 2 ] = z;
  }
}

bool clockwise( int16_t x1, int16_t y1, int16_t x2, int16_t y2, int16_t x3, int16_t y3 )
{
  return ( (x2 - x1) * (y3 - y1) ) <= ( (y2 - y1) * (x3 - x1) );
}

bool inClockwiseTriangle( int16_t x, int16_t y, int16_t x1, int16_t y1, int16_t x2, int16_t y2, int16_t x3, int16_t y3 ) {
  return clockwise( x, y, x1, y1, x2, y2 ) && clockwise( x, y, x2, y2, x3, y3 ) && clockwise( x, y, x3, y3, x1, y1 );
}

void logic_thread() {
  while( true ) {
    map3Dto2D();
    darkenhexagon();
    bool found;
    for( int i = 0; i < 397; i++ ) {
      found = false;
      for( int t = 0; t < 12; t++ ) {
        if( !found ) {
          if( 
            inClockwiseTriangle( 
              led2bytex(i), led2bytey( i ), 
              coords2D[ triangles[ t ][ 0 ] ][ 0 ], coords2D[ triangles[ t ][ 0 ] ][ 1 ], 
              coords2D[ triangles[ t ][ 1 ] ][ 0 ], coords2D[ triangles[ t ][ 1 ] ][ 1 ], 
              coords2D[ triangles[ t ][ 2 ] ][ 0 ], coords2D[ triangles[ t ][ 2 ] ][ 1 ]
            )
          ) {
            setColor( i, rainbowColor( ( t / 2 ) * 40 ) );
            found = true;
          }
        }
      }
    }
    rotateZ();
    rotateX();
    usleep(20000);
  }
}
