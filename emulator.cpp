#include <iostream>

using namespace std;
struct Point{
    int X;
    int Y;
};
int xyToCoord[23][23]={
    { 375, 374, 373, 372, 371, 370, 369, 368, 367, 366, 365, 364,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000},
    { 376, 311, 310, 309, 308, 307, 306, 305, 304, 303, 302, 301, 363,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000},
    { 377, 312, 253, 252, 251, 250, 249, 248, 247, 246, 245, 244, 300, 362,1000,1000,1000,1000,1000,1000,1000,1000,1000},
    { 378, 313, 254, 201, 200, 199, 198, 197, 196, 195, 194, 193, 243, 299, 361,1000,1000,1000,1000,1000,1000,1000,1000},
    { 379, 314, 255, 202, 155, 154, 153, 152, 151, 150, 149, 148, 192, 242, 298, 360,1000,1000,1000,1000,1000,1000,1000},
    { 380, 315, 256, 203, 156, 115, 114, 113, 112, 111, 110, 109, 147, 191, 241, 297, 359,1000,1000,1000,1000,1000,1000},
    { 381, 316, 257, 204, 157, 116,  81,  80,  79,  78,  77,  76, 108, 146, 190, 240, 296, 358,1000,1000,1000,1000,1000},
    { 382, 317, 258, 205, 158, 117,  82,  53,  52,  51,  50,  49,  75, 107, 145, 189, 239, 295, 357,1000,1000,1000,1000},
    { 383, 318, 259, 206, 159, 118,  83,  54,  31,  30,  29,  28,  48,  74, 106, 144, 188, 238, 294, 356,1000,1000,1000},
    { 384, 319, 260, 207, 160, 119,  84,  55,  32,  15,  14,  13,  27,  47,  73, 105, 143, 187, 237, 293, 355,1000,1000},
    { 385, 320, 261, 208, 161, 120,  85,  56,  33,  16,   5,   4,  12,  26,  46,  72, 104, 142, 186, 236, 292, 354,1000},
    { 386, 321, 262, 209, 162, 121,  86,  57,  34,  17,   6,   0,   3,  11,  25,  45,  71, 103, 141, 185, 235, 291, 353},
    {1000, 387, 322, 263, 210, 163, 122,  87,  58,  35,  18,   1,   2,  10,  24,  44,  70, 102, 140, 184, 234, 290, 352},
    {1000,1000, 388, 323, 264, 211, 164, 123,  88,  59,  36,   7,   8,   9,  23,  43,  69, 101, 139, 183, 233, 289, 351},
    {1000,1000,1000, 389, 324, 265, 212, 165, 124,  89,  60,  19,  20,  21,  22,  42,  68, 100, 138, 182, 232, 288, 350},
    {1000,1000,1000,1000, 390, 325, 266, 213, 166, 125,  90,  37,  38,  39,  40,  41,  67,  99, 137, 181, 231, 287, 349},
    {1000,1000,1000,1000,1000, 391, 326, 267, 214, 167, 126,  61,  62,  63,  64,  65,  66,  98, 136, 180, 230, 286, 348},
    {1000,1000,1000,1000,1000,1000, 392, 327, 268, 215, 168,  91,  92,  93,  94,  95,  96,  97, 135, 179, 229, 285, 347},
    {1000,1000,1000,1000,1000,1000,1000, 393, 328, 269, 216, 127, 128, 129, 130, 131, 132, 133, 134, 178, 228, 284, 346},
    {1000,1000,1000,1000,1000,1000,1000,1000, 394, 329, 270, 169, 170, 171, 172, 173, 174, 175, 176, 177, 227, 283, 345},
    {1000,1000,1000,1000,1000,1000,1000,1000,1000, 395, 330, 217, 218, 219, 220, 221, 222, 223, 224, 225, 226, 282, 344},
    {1000,1000,1000,1000,1000,1000,1000,1000,1000,1000, 396, 271, 272, 273, 274, 275, 276, 277, 278, 279, 280, 281, 343},
    {1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000, 331, 332, 333, 334, 335, 336, 337, 338, 339, 340, 341, 342}
};

int coordToXY[400][2]={
    {11,11},{11,12},{12,12},{12,11},{11,10},{10,10},{10,11},{11,13},{12,13},{13,13},{13,12},{13,11},{12,10},{11, 9},{10, 9},{ 9, 9},{ 9,10},{ 9,11},{10,12},{11,14},
    {12,14},{13,14},{14,14},{14,13},{14,12},{14,11},{13,10},{12, 9},{11, 8},{10, 8},{ 9, 8},{ 8, 8},{ 8, 9},{ 8,10},{ 8,11},{ 9,12},{10,13},{11,15},{12,15},{13,15},
    {14,15},{15,15},{15,14},{15,13},{15,12},{15,11},{14,10},{13, 9},{12, 8},{11, 7},{10, 7},{ 9, 7},{ 8, 7},{ 7, 7},{ 7, 8},{ 7, 9},{ 7,10},{ 7,11},{ 8,12},{ 9,13},
    {10,14},{11,16},{12,16},{13,16},{14,16},{15,16},{16,16},{16,15},{16,14},{16,13},{16,12},{16,11},{15,10},{14, 9},{13, 8},{12, 7},{11, 6},{10, 6},{ 9, 6},{ 8, 6},
    { 7, 6},{ 6, 6},{ 6, 7},{ 6, 8},{ 6, 9},{ 6,10},{ 6,11},{ 7,12},{ 8,13},{ 9,14},{10,15},{11,17},{12,17},{13,17},{14,17},{15,17},{16,17},{17,17},{17,16},{17,15},
    {17,14},{17,13},{17,12},{17,11},{16,10},{15, 9},{14, 8},{13, 7},{12, 6},{11, 5},{10, 5},{ 9, 5},{ 8, 5},{ 7, 5},{ 6, 5},{ 5, 5},{ 5, 6},{ 5, 7},{ 5, 8},{ 5, 9},
    { 5,10},{ 5,11},{ 6,12},{ 7,13},{ 8,14},{ 9,15},{10,16},{11,18},{12,18},{13,18},{14,18},{15,18},{16,18},{17,18},{18,18},{18,17},{18,16},{18,15},{18,14},{18,13},
    {18,12},{18,11},{17,10},{16, 9},{15, 8},{14, 7},{13, 6},{12, 5},{11, 4},{10, 4},{ 9, 4},{ 8, 4},{ 7, 4},{ 6, 4},{ 5, 4},{ 4, 4},{ 4, 5},{ 4, 6},{ 4, 7},{ 4, 8},
    { 4, 9},{ 4,10},{ 4,11},{ 5,12},{ 6,13},{ 7,14},{ 8,15},{ 9,16},{10,17},{11,19},{12,19},{13,19},{14,19},{15,19},{16,19},{17,19},{18,19},{19,19},{19,18},{19,17},
    {19,16},{19,15},{19,14},{19,13},{19,12},{19,11},{18,10},{17, 9},{16, 8},{15, 7},{14, 6},{13, 5},{12, 4},{11, 3},{10, 3},{ 9, 3},{ 8, 3},{ 7, 3},{ 6, 3},{ 5, 3},
    { 4, 3},{ 3, 3},{ 3, 4},{ 3, 5},{ 3, 6},{ 3, 7},{ 3, 8},{ 3, 9},{ 3,10},{ 3,11},{ 4,12},{ 5,13},{ 6,14},{ 7,15},{ 8,16},{ 9,17},{10,18},{11,20},{12,20},{13,20},
    {14,20},{15,20},{16,20},{17,20},{18,20},{19,20},{20,20},{20,19},{20,18},{20,17},{20,16},{20,15},{20,14},{20,13},{20,12},{20,11},{19,10},{18, 9},{17, 8},{16, 7},
    {15, 6},{14, 5},{13, 4},{12, 3},{11, 2},{10, 2},{ 9, 2},{ 8, 2},{ 7, 2},{ 6, 2},{ 5, 2},{ 4, 2},{ 3, 2},{ 2, 2},{ 2, 3},{ 2, 4},{ 2, 5},{ 2, 6},{ 2, 7},{ 2, 8},
    { 2, 9},{ 2,10},{ 2,11},{ 3,12},{ 4,13},{ 5,14},{ 6,15},{ 7,16},{ 8,17},{ 9,18},{10,19},{11,21},{12,21},{13,21},{14,21},{15,21},{16,21},{17,21},{18,21},{19,21},
    {20,21},{21,21},{21,20},{21,19},{21,18},{21,17},{21,16},{21,15},{21,14},{21,13},{21,12},{21,11},{20,10},{19, 9},{18, 8},{17, 7},{16, 6},{15, 5},{14, 4},{13, 3},
    {12, 2},{11, 1},{10, 1},{ 9, 1},{ 8, 1},{ 7, 1},{ 6, 1},{ 5, 1},{ 4, 1},{ 3, 1},{ 2, 1},{ 1, 1},{ 1, 2},{ 1, 3},{ 1, 4},{ 1, 5},{ 1, 6},{ 1, 7},{ 1, 8},{ 1, 9},
    { 1,10},{ 1,11},{ 2,12},{ 3,13},{ 4,14},{ 5,15},{ 6,16},{ 7,17},{ 8,18},{ 9,19},{10,20},{11,22},{12,22},{13,22},{14,22},{15,22},{16,22},{17,22},{18,22},{19,22},
    {20,22},{21,22},{22,22},{22,21},{22,20},{22,19},{22,18},{22,17},{22,16},{22,15},{22,14},{22,13},{22,12},{22,11},{21,10},{20, 9},{19, 8},{18, 7},{17, 6},{16, 5},
    {15, 4},{14, 3},{13, 2},{12, 1},{11, 0},{10, 0},{ 9, 0},{ 8, 0},{ 7, 0},{ 6, 0},{ 5, 0},{ 4, 0},{ 3, 0},{ 2, 0},{ 1, 0},{ 0, 0},{ 0, 1},{ 0, 2},{ 0, 3},{ 0, 4},
    { 0, 5},{ 0, 6},{ 0, 7},{ 0, 8},{ 0, 9},{ 0,10},{ 0,11},{ 1,12},{ 2,13},{ 3,14},{ 4,15},{ 5,16},{ 6,17},{ 7,18},{ 8,19},{ 9,20},{10,21},{17,19},{23,23},{11,12}
};
char screen[23][23];



static void draw_screen();
static struct Point draw_line(int  position,int direction ,int length,char color);
static void draw_line(struct Point &point1, struct Point &point2, char color);
static void draw_hex(struct Point &centerP,int radius,char color);
static void setColor( int position, char color );
//the beer example
int main()
{

    for(int y=0;y<23;y++){
        for(int x=0;x<23;x++){
            cout.fill( ' ' );
            screen[x][y]=' ';
        }
    }


    Point sP={9,6};
    Point eP;
    //top
    draw_hex(sP,3,'o');
    //fill top
    draw_hex(sP,2,'s');
    draw_hex(sP,1,'s');
    draw_hex(sP,0,'s');
    draw_screen();

    //bottum
    sP={9,12};
    draw_hex(sP,3,'o');

    //handle
    sP={13,11};
    draw_hex(sP,3,'o');
    draw_hex(sP,2,'o');
    sP={6,6};
    eP={6,13};
    draw_line(sP,eP,'o');

    //sides
    sP={sP.X+1,sP.Y+2};
    eP={eP.X+1,eP.Y};
    draw_line(sP,eP,'s');
    sP={sP.X+1,sP.Y+1};
    eP={eP.X+1,eP.Y+1};
    draw_line(sP,eP,'s');

    sP={9,9};
    eP={9,16};
    draw_line(sP,eP,'o');

    sP={sP.X+1,sP.Y+1};
    eP={eP.X+1,eP.Y-1};
    draw_line(sP,eP,'s');
    sP={sP.X+1,sP.Y};
    eP={eP.X+1,eP.Y};
    draw_line(sP,eP,'s');


    sP={12,8};
    eP={12,16};
    draw_line(sP,eP,'o');

//    setColor(xyToCoord[11][11],'X');

    draw_screen();



}
static void draw_screen(){


    int space=23*2;
    for(int y=0;y<23;y++){
        cout.fill( ' ' );
        cout.width( space );
        cout<< ' ';
        space=space-2;
        for(int x=0;x<23;x++){
            cout.fill( ' ' );
            cout << screen[x][y]<<',';
        }
        cout <<endl;
    }
}
struct Point draw_line(struct Point &startP,int direction ,int length,char color){
    //TODO port to XY cordinate system
    struct Point endP;

    switch (direction) {
    case 0:
        endP.X=startP.X+length;
        endP.Y=startP.Y;
        break;
    case 1:
        endP.X=startP.X;
        endP.Y=startP.Y-length;
        break;
    case 2:
        endP.X=startP.X-length;
        endP.Y=startP.Y-length;
        break;
    case 3:
        endP.X=startP.X-length;
        endP.Y=startP.Y;
        break;
    case 4:
        endP.X=startP.X;
        endP.Y=startP.Y+length;
        break;
    case 5:
        endP.X=startP.X+length;
        endP.Y=startP.Y+length;
        break;
    default:
        break;
    }
    draw_line(startP,endP,color);
    return endP;
}


//Bresenham's line algorithm
static void draw_line(struct Point &point1, struct Point &point2, char color){
    //TODO add check so points are in the boundry
    struct Point startP,endP;

    if(point1.X<point2.X){
        startP.X=point1.X;
        endP.X=point2.X;
    }
    else{
        startP.X=point2.X;
        endP.X=point1.X;
    }
    if(point1.Y<point2.Y){
        startP.Y=point1.Y;
        endP.Y=point2.Y;
    }
    else{
        startP.Y=point2.Y;
        endP.Y=point1.Y;
    }



    int deltaX=endP.X-startP.X;
    int deltaY=endP.Y-startP.Y;

    int D = 2*deltaY - deltaX;

    setColor(xyToCoord[startP.X][startP.Y],color);

    if(deltaX!=0){
        int y=startP.Y;
        for (int x=startP.X+1; x<endP.X; x++){
            if (D > 0){
                y = y+1;
                D = D + (2*deltaY-2*deltaX);
            }
            else{
                D = D + (2*deltaY);
            }
            setColor(xyToCoord[x][y],color);
        }
    }
    else{
        int x=startP.X;
        for (int y=startP.Y+1; y<endP.Y; y++){
            setColor(xyToCoord[x][y],color);
        }
    }


}


//draw from the internal state coordinate this allowas for chaining up lines
//draw a hexigonal
static void draw_hex(struct Point &centerP,int radius,char color){
    //TODO add check so points are in the boundry
    //radius equals the side of the hexagon.

    //get to the hexagon edge we go in derection 4 == +Y
    // we can then start drawing from neighbour 0 to 1 etc.
    struct Point P = {centerP.X,centerP.Y+radius};

    for(int i=0;i<6;i++){
        P=draw_line(P,i,radius,color);
    }
}

static void setColor( int position, char color ) {
    int x,y;

    x = coordToXY[position][0];
    y = coordToXY[position][1];
    screen[y][x]=color;
}
/*   int xyToNativecoord[23][23];
   int NativecoordToXY[397][2];

    for(int j=0;j<23;j++){
        cout << '{' ;
        for(int i=0;i<23;i++){
            xyToNativecoord[j][i]=1000;
            cout << xyToNativecoord[j][i]<<',';
        }
        cout << "}\n" ;
    }
    cout << "\n\n\n\n\n\n";
    //xyToNativecoord[11][11]=0;
    int count=0;
    for(int j=0;j<12;j++){
        xyToNativecoord[11][11+j]=count;
        NativecoordToXY[count][0]=11;
        NativecoordToXY[count][1]=11+j;
        count++;
        for(int i = 1;i<=j;i++){
            NativecoordToXY[count][0]=11+i;
            NativecoordToXY[count][1]=11+j;

            xyToNativecoord[11+i][11+j]=count;
            count++;
        }

       for(int k = 1;k<=j;k++){
           NativecoordToXY[count][0]=11+j;
           NativecoordToXY[count][1]=11+j-k;

            xyToNativecoord[11+j][11+j-k]=count;
            count++;
        }

        for(int i = 1;i<=j;i++){
            NativecoordToXY[count][0]=11+j-i;
            NativecoordToXY[count][1]=11-i;

            xyToNativecoord[11+j-i][11-i]=count;
            count++;
        }

        for(int i = 1;i<=j;i++){
            NativecoordToXY[count][0]=11-i;
            NativecoordToXY[count][1]=11-j;
            xyToNativecoord[11-i][11-j]=count;
            count++;
        }

        for(int i = 1;i<=j;i++){
            NativecoordToXY[count][0]=11-j;
            NativecoordToXY[count][1]=11-j+i;

            xyToNativecoord[11-j][11-j+i]=count;
            count++;
        }
        for(int i = 1;i<=j-1;i++){
            NativecoordToXY[count][0]=11-j+i;
            NativecoordToXY[count][1]=11+i;

            xyToNativecoord[11-j+i][11+i]=count;
            count++;
        }

        if(j==11){
            break;
        }
    }
    for(int y=0;y<23;y++){
        cout << '{' ;
        for(int x=0;x<23;x++){
            cout.fill( ' ' );
            cout.width( 4 );
            cout << xyToNativecoord[x][y]<<',';
        }
        cout << "}\n" ;
    }
    for(int i=0;i<20;i++){
        for(int k=0;k<20;k++){

       cout <<'{';
       cout.fill( ' ' );
       cout.width( 2 );
       cout<< NativecoordToXY[i*20+k][0]<<',';

       cout.fill( ' ' );
       cout.width( 2 );
       cout<< NativecoordToXY[i*20+k][1]<<"},";
    }
        cout<<endl;
    }
    return 0;
*/

