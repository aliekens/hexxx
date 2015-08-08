#include "draw.h"
#include "coordinates.h"
#include "hexxx.h"
#include "ws2811/ws2811.h"


struct Point draw_line(struct Point &startP,int direction ,int length,ws2811_led_t color){

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
void draw_line(struct Point &point1, struct Point &point2, ws2811_led_t color){
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
void draw_hex(struct Point &centerP,int radius,ws2811_led_t color){
    //TODO add check so points are in the boundry
    //radius equals the side of the hexagon.

    //get to the hexagon edge we go in derection 4 == +Y
    // we can then start drawing from neighbour 0 to 1 etc.
    struct Point P = {centerP.X,centerP.Y+radius};

    for(int i=0;i<6;i++){
        P=draw_line(P,i,radius,color);
    }


}
