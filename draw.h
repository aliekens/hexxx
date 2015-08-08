#ifndef DRAWER_H
#define DRAWER_H
#include "ws2811/ws2811.h"

struct Point{
    int X;
    int Y;
};
//returns end position
struct Point draw_line(struct Point &startP,int direction ,int length,ws2811_led_t color);
//draw from a native coordinate point
void draw_line(struct Point &startP, struct Point &endP, ws2811_led_t color);
//draw from the internal state coordinate this allowas for chaining up lines
//draw a hexigonal
void draw_hex(struct Point &centerP,int radius,ws2811_led_t color);


#endif // DRAWER_H
